#include <seqGraph/seqGraph.h>
#include <stdio.h>

// Local variables
u32 viewPort_x;
u32 viewPort_y;
u32 viewPort_w;
u32 viewPort_h;

Color fBuffer[W * H] = {0};
Color clearColor;

void sgDrawBuffer(void) { OSW_VideoDrawBuffer(fBuffer, W, W); }

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
  printf("Drawing at (%d, %d)\n", x, y);
  fBuffer[W * y + x] = c;
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
    printf("Current point: (%f, %f)\n", current[0], current[1]);
    vec4 vert;
    Buffer buffer = {0};

    // Vertex shader
    __default_vert_shader(vert, current, buffer);

    f32 w = vert[3];

    // Clipping
    if (current[1] > w || current[1] < -w || current[0] > w ||
        current[0] < -w)
    {
      printf("BREAK!!! : (%f, %f)\n", current[0], current[1]);
      break;
    }

    perspectiveCorrection(&current[0], &current[1], w);
    viewportTransformation(&current[0], &current[1]);

    // Fragment shader
    Color finalColor = 0x00000000;
    vec4 color = {0.0, 0.0, 0.0, 0.0};

    __default_frag_shader(color, current[0], current[1], buffer);

    finalColor |= (u32)(color[0] * 255.0f);
    finalColor |= (u32)(color[1] * 255.0f) << 8;
    finalColor |= (u32)(color[2] * 255.0f) << 16;

    sgPokePixel(current[0], current[1], finalColor);
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
  float yStart = MIN(y0, y1);
  float yEnd = MAX(y0, y1);

  for (float x = xStart, y = yStart; x < xEnd; x += 1)
  {
    printf("Current: (%f, %f)\n", x, y);

    slope_error += m_new;
    if (slope_error >= 0)
    {
      y++;
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

    printf("Current: (%f, %f) - (%f, %f)\n", first[0], first[1], next[0], next[1]);
    // Vertex shader
    __default_vert_shader(firstOut, first, bufferFirst);
    __default_vert_shader(nextOut, next, bufferNext);
    f32 w = firstOut[3];
    printf("Vertex Shade: (%f, %f) - (%f, %f)\n", firstOut[0], firstOut[1], nextOut[0], nextOut[1]);

    // Clipping
    if (firstOut[1] > w || firstOut[1] < -w || firstOut[0] > w ||
        firstOut[0] < -w)
    {
      printf("Break!\n");
      break;
    }
    printf("Clipping: (%f, %f) - (%f, %f)\n", firstOut[0], firstOut[1], nextOut[0], nextOut[1]);

    perspectiveCorrection(&firstOut[0], &firstOut[1], firstOut[3]);
    perspectiveCorrection(&nextOut[0], &nextOut[1], nextOut[3]);

    printf("Perspective: (%f, %f) - (%f, %f)\n", firstOut[0], firstOut[1], nextOut[0], nextOut[1]);

    viewportTransformation(&firstOut[0], &firstOut[1]);
    viewportTransformation(&nextOut[0], &nextOut[1]);

    printf("Viewport: (%f, %f) - (%f, %f)\n", firstOut[0], firstOut[1], nextOut[0], nextOut[1]);

    // Rasterization.

    // TODO : Remove magic number.
    Fragment fragments[1000];
    int size = _rasterizeLine(firstOut[0], firstOut[1], nextOut[0], nextOut[1], fragments);

    printf("Completed rasterization stage...\n");

    for (int i = 0; i < size; i++)
    {
      printf("Drawing (%f, %f)\n", fragments[i][0], fragments[i][1]);
      sgPokePixel(fragments[i][0], fragments[i][1], 0x000);
    }
  }
}

void _sgDrawTriangles(vec3 *vertex, u32 count)
{
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
  f32 tempX = (x_r + 1) / 2;
  f32 tempY = (y_r + 1) / 2;
  color[0] = tempX;
  color[1] = 0.0;
  color[2] = tempY;
  color[3] = 1.0;

  return true;
}
