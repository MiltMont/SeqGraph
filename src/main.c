#include <libosw/osw.h>
#include <math.h>
#include <seqGraph/seqGraph.h>

int main(int argc, char *argv[])
{
  // Create window and check for errors
  u32 err = OSW_Init("SeqGraph Window", W * 2, H * 2, 0);

  if (err != OSW_OK)
  {
    return err;
  }

  Color background = 0xfffffffff;

  sgSetClearColor(background);
  sgViewport(0, 0, W, H);

  vec3 points[] = {
      {0.0, 0.0, 0.0},
      {-1.0, -1.0, 0.0},
      {1.0, 0.0, 0.0}};

  f32 timer = 0;

  while (1)
  {
    timer += 0.05;

    sgClearColor();
    OSW_Poll();

    sgDrawVertex(sgTriangle, points, 3);
    sgDrawBuffer();
    OSW_VideoSwapBuffers();
  }
  return 0;
}
