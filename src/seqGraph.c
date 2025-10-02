#include <libosw/osw.h>
#include <seqGraph/seqGraph.h>
#include <seqGraph/utils.h>

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

void sgDrawVertex(enum PrimitiveType type, vec3 vertex[], u32 count)
{
  switch (type)
  {
  case sgPoint:
    _sgDrawPoints(vertex, count);
    break;
  case sgLine:
    _sgDrawLines(vertex, count);
    break;
  case sgTriangle:
    _sgDrawTriangles(vertex, count);
    break;
  }
}

/// Internal functions
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

    // Color finalColor = vec4ToColor(color);
    finalColor |= (u32)(color[0] * 255.0f);
    finalColor |= (u32)(color[1] * 255.0f) << 8;
    finalColor |= (u32)(color[2] * 255.0f) << 16;

    sgPokePixel((int)current[0], (int)current[1], finalColor);
  }
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
    int size = _rasterizeLine((int)firstOut[0], (int)firstOut[1], (int)nextOut[0], (int)nextOut[1], fragments);

    LOG("\nCOMPLETED RASTERIZATION STAGE.\n\n", 0);

    vec4 color = {1.0, 0.0, 0.0, 1.0};
    Color finalColor = vec4ToColor(color);

    // TODO: Implement fragment shader.
    for (int i = 0; i < size; i++)
    {
      sgPokePixel(fragments[i][0], fragments[i][1], finalColor);
    }
  }
}

void _sgDrawTriangles(vec3 vertex[], u32 count)
{
  LOG("Starting triangle drawing\n", 0);

  if (count < 3)
  {
    return;
  }

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
    if (fabs(outA[0]) > w || fabs(outA[1]) > w)
    {
      LOG("Clipped point (%f, %f)", outA[0], outA[1]);
      break;
    }
    if (fabs(outB[0]) > w || fabs(outB[1]) > w)
    {
      LOG("Clipped point (%f, %f)", outA[0], outA[1]);
      break;
    }
    if (fabs(outC[0]) > w || fabs(outC[1]) > w)
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

    /// Fragment shader
    vec4 colorA = {1.0, 0.0, 0.0, 1.0};
    vec4 colorB = {0.0, 1.0, 0.0, 1.0};
    vec4 colorC = {0.0, 0.0, 1.0, 1.0};

    for (u32 i = 0; i < size; i++)
    {
      vec3 coords;
      vec2 current = {(float)fragments[i][0], (float)fragments[i][1]};

      getBarycentricCoordinates(coords, rasterA, rasterB, rasterC, current);

      vec4 interpColor = {coords[0], coords[1], coords[2], 1.0};
      Color finalColor = vec4ToColor(interpColor);

      sgPokePixel(fragments[i][0], fragments[i][1], finalColor);
    }
  }
}

/// Rasterization functions
int _rasterizeLine(int x0, int y0, int x1, int y1, Fragment *dest)
{
  int dx = abs(x0 - x1);
  int dy = abs(y1 - y0);
  int p = 2 * (dy - dx);

  int twoDy = 2 * dy;
  int twoDx = 2 * dx;
  int twoDyDx = 2 * (dy - dx);
  int twoDxDy = 2 * (dx - dy);

  int x = x0, y = y0;

  int xIncrement = (x1 > x0) ? 1 : -1;
  int yIncrement = (y1 > y0) ? 1 : -1;

  int current = 0;

  if (dx > dy)
  {
    for (int i = 0; i < dx; i++)
    {
      x += xIncrement;

      if (p < 0)
      {
        p += twoDy;
      }
      else
      {
        y += yIncrement;
        p += twoDyDx;
      }

      dest[current][0] = x;
      dest[current][1] = y;
      current += 1;
    }
  }
  else
  {
    for (int i = 0; i < dy; i++)
    {
      y += yIncrement;

      if (p < 0)
      {
        p += twoDx;
      }
      else
      {
        x += xIncrement;
        p += twoDxDy;
      }

      dest[current][0] = x;
      dest[current][1] = y;
      current += 1;
    }
  }
  return current;
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

/// Shaders
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

/// Utility functions

/// @brief [-1,1] x [-1,1] -> [0, W] x [0, H] transformation.
/// @param x
/// @param y
void viewportTransformation(f32 *x, f32 *y)
{
  *x = (viewPort_w / 2) * (*x + 1) + viewPort_x;
  *y = (viewPort_h / 2) * (1 - *y) + viewPort_y;
}