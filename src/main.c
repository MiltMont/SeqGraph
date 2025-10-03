#include <libosw/osw.h>
#include <math.h>
#include <seqGraph/seqGraph.h>
#include <seqGraph/ds.h>

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

  f32 timer = 0;

  Vertex a = {.position = {0.0, 0.0, 0.0}, .color = {1.0, 0.0, 0.0}};
  Vertex b = {.position = {1.0, 0.0, 0.0}, .color = {0.0, 1.0, 0.0}};
  Vertex c = {.position = {0.0, 1.0, 0.0}, .color = {0.0, 0.0, 1.0}};
  Vertex points[] = {a, b, c};

  while (1)
  {
    timer += 0.01;

    sgClearColor();
    OSW_Poll();
    sgDrawVertex(sgTriangle, points, 3);
    sgDrawBuffer();
    OSW_VideoSwapBuffers();

    points[0].color[0] = fabs(cos(timer));
    points[1].color[1] = fabs(sin(timer));
  }
  return 0;
}
