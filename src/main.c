#include <libosw/osw.h>
#include <math.h>
#include <seqGraph/seqGraph.h>
#include <seqGraph/trx.h>

int main(int argc, char *argv[]) {
  // Create window and check for errors
  u32 err = OSW_Init("SeqGraph Window", W * 2, H * 2, 0);

  if (err != OSW_OK) {
    return err;
  }

  Color background = 0xffffff;

  sgSetClearColor(background, 100.0);
  sgViewport(0, 0, W, H);

  f32 timer = 0;


  Vertex points[] = {
  {.position = {0.0, 0.0, 0.0}, .color = {0.0, 0.0, 0.0}},
  {.position = {1.0, 0.0, 0.0}, .color = {1.0, 0.0, 0.0}},
  {.position = {0.0, 1.0, 0.0}, .color = {0.0, 1.0, 0.0}},
  {.position = {0.0, 0.0, 1.0}, .color = {0.0, 0.0, 1.0}},
  };

  u32 indices[] = {
    1,2,3,  // f1
    2, 0, 1, // f2
    0, 2, 3, // f3
    // 0, 3, 2,
  };

    rotateY(points[3].position, 25);
    rotateY(points[2].position, 25);
    rotateY(points[1].position, 25);

  while (1) {
    timer += 0.01;
    sgClear();

    OSW_Poll();
    sgDrawIndexedVertex(sgTriangle, points, indices, 6);
    sgDrawBuffer();
    OSW_VideoSwapBuffers();

  }

  return 0;
}
