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

  sgSetClearColor(background);
  sgViewport(0, 0, W, H);

  f32 timer = 0;

  Vertex zero = {.position = {0.0, 0.0, 4.0}, .color = {0.0, 0.0, 0.0}};
  Vertex e_x = {.position = {1.0, 0.0, 4.0}, .color = {1.0, 0.0, 0.0}};
  Vertex e_y = {.position = {0.0, 1.0, 4.0}, .color = {0.0, 1.0, 0.0}};
  Vertex e_z = {.position = {0.0, 0.0, 12.0}, .color = {0.0, 0.0, 1.0}};

  Vertex points[] = {
    zero, e_x, e_y, e_z
  };

  u32 indices[] = {
    0, 1, 2, 
    0, 3, 2,
    0, 3, 1, 

  };


  while (1) {
    timer += 0.01;

    sgClearColor();
    OSW_Poll();
    sgDrawIndexedVertex(sgTriangle, points, indices, 9);
    sgDrawBuffer();
    OSW_VideoSwapBuffers();

    // rotateZ(points[0].position, 1);
    rotateZ(points[3].position, 1);
    rotateZ(points[2].position, 1);
    // rotateZ(points[3].position, 1);
    // rotateZ(points[3].position, 1);

  }

  return 0;
}
