#include <libosw/osw.h>
#include <math.h>
#include <seqGraph/seqGraph.h>

int main(int argc, char *argv[])
{
  // Create window and check for errors
  u32 err = OSW_Init("Game window", W * 2, H * 2, 0);

  if (err != OSW_OK)
  {
    return err;
  }

  Color background = 0xfffffffff;

  sgSetClearColor(background);
  sgViewport(0, 0, W, H);

  int numPoints = 1000;
  vec3 points[1000] = {{0.0, 0.0, 0.0}};
  enum PrimitiveType point = sgPoint;

  f32 timer = 0;

  while (1)
  {
    timer += 0.05;

    sgClearColor();
    OSW_Poll();

    for (int i = 0; i < numPoints; i++)
    {
      points[i][0] = cos(timer / (i + 1)) / (i + 1);
      points[i][1] = sin(timer / (i + 1)) / (i + 1);
    }

    _sgDrawPoints(points, 1000);
    sgDrawBuffer();
    OSW_VideoSwapBuffers();
  }
  return 0;
}
