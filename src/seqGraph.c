#include <seqGraph/seqGraph.h>
#include <stdio.h>

#ifdef DEBUG
#define LOG(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define LOG(fmt, ...)
#endif

#ifdef DEBUG
#define LOGV3(NAME, P) fprintf(stderr, "%s=(%f, %f, %f)\n", NAME, P[0], P[1], P[2])
#else
#define LOGV3(NAME, P)
#endif

#ifdef DEBUG
#define LOGV4(NAME, P) fprintf(stderr, "%s=(%f, %f, %f, %f)\n", NAME, P[0], P[1], P[2], P[3])
#else
#define LOGV4(NAME, P)
#endif

// Local variables
u32 viewPort_x;
u32 viewPort_y;
u32 viewPort_w;
u32 viewPort_h;

Color fBuffer[W * H] = {0};
Color clearColor;

void sgDrawBuffer(void) { OSW_VideoDrawBuffer(fBuffer, W, H); }

void sgSetClearColor(Color c) { clearColor = c; }

void sgClearColor()
{
  for (int i = 0; i < W * H; i++)
  {
    fBuffer[i] = clearColor;
  }
}

void sgPokePixel(u32 x, u32 y, Color c)
{
  int dest = W * y + x;
  if (dest < W * H && dest > 0)
  {
    LOG("Drawing at: (%d, %d)\n", x, y);
    fBuffer[dest] = c;
  }
  else if (dest == W * H)
  {
    LOG("Drawing at: (%d, %d)\n", x, y);
    fBuffer[dest - 1] = c;
  }
  else if (dest == 0)
  {
    LOG("Drawing at: (%d, %d)\n", x, y);
    fBuffer[0] = c;
  }
  else
  {
    LOG("Out of bounds: %d\n", dest);
  }
}

void sgViewport(u32 x_0, u32 y_0, u32 w, u32 h)
{
  viewPort_x = x_0;
  viewPort_y = y_0;
  viewPort_w = w;
  viewPort_h = h;
}

/// Utility function
void perspectiveCorrection(f32 *x, f32 *y, f32 w)
{
  x[0] = x[0] / w;
  x[1] = x[1] / w;
}

void viewportTransformation(f32 *x, f32 *y)
{
  *x = (viewPort_w / 2) * (*x + 1) + viewPort_x;
  *y = (viewPort_h / 2) * (1 - *y) + viewPort_y;
}

/// Internal function
void _sgDrawPoints(vec3 *vertex, u32 count)
{
  for (int i = 0; i < count; i++)
  {

    vec3 current = {vertex[i][0], vertex[i][1]};
    LOG("Current point: (%f, %f)\n", current[0], current[1]);
    vec4 vert;
    Buffer buffer = {0};

    // Vertex shader
    __default_vert_shader(vert, current, buffer);

    f32 w = vert[3];

    // Clipping
    if (fabs(current[1]) > w || fabs(current[0]) > w)
    {
      LOG("Clipped point: (%f, %f)\n", current[0], current[1]);
      break;
    }

    perspectiveCorrection(&current[0], &current[1], w);
    LOG("Perspective correction result:\n", 0);
    LOGV3("P", current);

    viewportTransformation(&current[0], &current[1]);
    LOG("Vieport transformation result:\n", 0);
    LOGV3("P", current);

    // Fragment shader
    Color finalColor = 0x00000000;
    vec4 color = {0.0, 0.0, 0.0, 0.0};

    __default_frag_shader(color, current[0], current[1], buffer);
    LOGV4("COLOR", color);

    finalColor |= (u32)(color[0] * 255.0f);
    finalColor |= (u32)(color[1] * 255.0f) << 8;
    finalColor |= (u32)(color[2] * 255.0f) << 16;

    sgPokePixel((int)current[0], (int)current[1], finalColor);
  }
}

int _rasterizeLine(f32 x0, f32 y0, f32 x1, f32 y1, Fragment *dest)
{
  f32 m_new = 2 * fabs(y1 - y0);
  f32 slope_error = m_new - fabs(x1 - x0);
  int current = 0;

  if (x0 == x1 && y0 == y1)
  {
    dest[current][0] = x0;
    dest[current][1] = y0;

    return current;
  }

  if (x0 == x1)
  {
    float start = MIN(y0, y1);
    float end = MAX(y0, y1);

    for (float i = start; i < end; i++)
    {
      dest[current][0] = x0;
      dest[current][1] = i;
      current += 1;
    }
    return current;
  }

  float xStart = MIN(x0, x1);
  float xEnd = MAX(x0, x1);
  float yStart = x0 < x1 ? y0 : y1;
  float yEnd = x0 < x1 ? y1 : y0;

  for (float x = xStart, y = yStart; x < xEnd; x += 1)
  {
    LOG("Current: (%f, %f)\n", x, y);

    slope_error += m_new;
    if (slope_error >= 0)
    {
      if (yStart < yEnd)
      {
        y++;
      }
      else
      {
        y--;
      }
      slope_error -= 2 * fabs(x1 - x0);
    }

    dest[current][0] = x;
    dest[current][1] = y;
    current += 1;
  }

  return current;
}

void _sgDrawLines(vec3 vertex[], u32 count)
{
  /// Iterate over pairs of points.
  for (int i = 0; i < count - 1; i++)
  {
    vec3 first = {vertex[i][0], vertex[i][1], vertex[i][2]};
    vec3 next = {vertex[i + 1][0], vertex[i + 1][1], vertex[i + 1][2]};

    Buffer bufferFirst = {0};
    Buffer bufferNext = {0};

    vec4 firstOut;
    vec4 nextOut;

    LOG("Current: (%f, %f) - (%f, %f)\n", first[0], first[1], next[0], next[1]);

    // Vertex shader
    __default_vert_shader(firstOut, first, bufferFirst);
    __default_vert_shader(nextOut, next, bufferNext);

    f32 w = firstOut[3];

    LOG("Vertex Shader: (%f, %f) - (%f, %f)\n", firstOut[0], firstOut[1], nextOut[0], nextOut[1]);

    // Clipping
    if (firstOut[1] > w || firstOut[1] < -w || firstOut[0] > w ||
        firstOut[0] < -w)
    {
      LOG("Clipped point (%f, %f)", firstOut[0], firstOut[1]);
      break;
    }

    LOG("Clipping: (%f, %f) - (%f, %f)\n", firstOut[0], firstOut[1], nextOut[0], nextOut[1]);

    perspectiveCorrection(&firstOut[0], &firstOut[1], firstOut[3]);
    perspectiveCorrection(&nextOut[0], &nextOut[1], nextOut[3]);

    LOG("Perspective: (%f, %f) - (%f, %f)\n", firstOut[0], firstOut[1], nextOut[0], nextOut[1]);

    viewportTransformation(&firstOut[0], &firstOut[1]);
    viewportTransformation(&nextOut[0], &nextOut[1]);

    LOG("Viewport: (%f, %f) - (%f, %f)\n", firstOut[0], firstOut[1], nextOut[0], nextOut[1]);

    // Rasterization.
    Fragment fragments[(int)ceil(sqrt(W * W + H * H))];
    int size = _rasterizeLine(firstOut[0], firstOut[1], nextOut[0], nextOut[1], fragments);

    LOG("\nCOMPLETED RASTERIZATION STAGE.\n\n", 0);

    // TODO: Implement fragment shader.
    for (int i = 0; i < size; i++)
    {
      sgPokePixel(fragments[i][0], fragments[i][1], 0x000);
    }
  }
}

bool isInTriangle(vec2 a, vec2 b, vec2 c, f32 x, f32 y)
{
  f32 denom = (b[1] - c[1]) * (a[0] - c[0]) + (c[0] - b[0]) * (a[1] - c[1]);
  f32 alpha = ((b[1] - c[1]) * (x - c[0]) + (c[0] - b[0]) * (y - c[1])) / denom;
  f32 beta = ((c[1] - a[1]) * (x - c[0]) + (a[0] - c[0]) * (y - c[1])) / denom;
  f32 gamma = 1.0f - alpha - beta;
  return alpha >= 0 && beta >= 0 && gamma >= 0;
}

int _rasterizeTriangle(vec2 x, vec2 y, vec2 z, Fragment dest[])
{
  // TODO: Use a more efficient approach.
  int current = 0;
  LOG("Computing bounding box limits\n", 0);
  // Getting bounding box limits.
  f32 xMin = MIN(x[0], MIN(y[0], z[0]));
  f32 xMax = MAX(x[0], MAX(y[0], z[0]));
  f32 yMin = MIN(x[1], MIN(y[1], z[1]));
  f32 yMax = MAX(x[1], MAX(y[1], z[1]));

  LOG("Result: [%f,%f]x[%f,%f]\n", xMin, yMin, xMax, yMax);

  for (int i = xMin; i < xMax; i++)
  {
    for (int j = yMin; j < yMax; j++)
    {
      if (isInTriangle(x, y, z, i, j))
      {
        dest[current][0] = i;
        dest[current][1] = j;
        current += 1;
      }
    }
  }

  return current;
}

void _sgDrawTriangles(vec3 vertex[], u32 count)
{
  LOG("Starting triangle drawing\n", 0);

  for (int i = 0; i < count - 2; i++)
  {
    vec3 a = {vertex[i][0], vertex[i][1], vertex[i][2]};
    vec3 b = {vertex[i + 1][0], vertex[i + 1][1], vertex[i + 1][2]};
    vec3 c = {vertex[i + 2][0], vertex[i + 2][1], vertex[i + 2][2]};

    LOGV3("A", a);
    LOGV3("B", b);
    LOGV3("C", c);

    Buffer bufA = {0};
    Buffer bufB = {0};
    Buffer bufC = {0};

    vec4 outA;
    vec4 outB;
    vec4 outC;

    // Vertex Shader.
    __default_vert_shader(outA, a, bufA);
    __default_vert_shader(outB, b, bufB);
    __default_vert_shader(outC, c, bufC);

    f32 w = outA[3];
    LOG("Vertex shader results: \n", 0);

    LOGV4("A", outA);
    LOGV4("B", outB);
    LOGV4("C", outC);

    // Clipping
    // TODO: Clip all points?
    if (fabs(outA[0]) > w || fabs(outB[1]) > w)
    {
      LOG("Clipped point (%f, %f)", outA[0], outA[1]);
      break;
    }

    LOG("No points clipped\n", 0);

    perspectiveCorrection(&outA[0], &outA[1], w);
    perspectiveCorrection(&outB[0], &outB[1], w);
    perspectiveCorrection(&outC[0], &outC[1], w);

    LOG("Perspective correction result\n", 0);
    LOGV4("A", outA);
    LOGV4("B", outB);
    LOGV4("C", outC);

    viewportTransformation(&outA[0], &outA[1]);
    viewportTransformation(&outB[0], &outB[1]);
    viewportTransformation(&outC[0], &outC[1]);
    LOG("Viewport transformation result\n", 0);
    LOGV4("A", outA);
    LOGV4("B", outB);
    LOGV4("C", outC);

    vec2 rasterA = {outA[0], outA[1]};
    vec2 rasterB = {outB[0], outB[1]};
    vec2 rasterC = {outC[0], outC[1]};

    /// Rasterization
    Fragment fragments[W * H];
    int size = _rasterizeTriangle(rasterA, rasterB, rasterC, fragments);

    LOG("Completed rasterization stage.\n\n", 0);
    LOG("%d rasterized fragments", size);

    for (int i = 0; i < size; i++)
    {
      sgPokePixel(fragments[i][0], fragments[i][1], 0x000);
    }
  }
}

void sgDrawVertex(enum PrimitiveType type, vec3 vertex[], u32 count)
{
  switch (type)
  {
  case sgPoint:
    _sgDrawPoints(vertex, count);
  case sgLine:
    _sgDrawLines(vertex, count);
  case sgTriangle:
    _sgDrawTriangles(vertex, count);
  }
}

void __default_vert_shader(vec4 out, vec3 vert, Buffer buffer)
{
  out[0] = vert[0];
  out[1] = vert[1];
  out[2] = vert[2];
  out[3] = 1.0;
}

bool __default_frag_shader(vec4 color, f32 x_r, f32 y_r, Buffer buffer)
{
  color[0] = 0.0;
  color[1] = 0.0;
  color[2] = 1.0;
  color[3] = 1.0;

  return true;
}
