#include <libosw/osw.h>
#include <math.h>
#include <seqGraph/seqGraph.h>

int main(int argc, char *argv[]) {
  // Create window and check for errors
  u32 err = OSW_Init("SeqGraph Window", W * 2, H * 2, 0);

  if (err != OSW_OK) {
    return err;
  }

  Color background = 0x00;

  sgSetClearColor(background);
  sgViewport(0, 0, W, H);

  f32 timer = 0;

  Vertex zero = {.position = {0.0, 0.0, 2.0}, .color = {1.0, 0.0, 0.0}};
  Vertex e_x = {.position = {1.0, 0.0, 2.0}, .color = {0.0, 1.0, 0.0}};
  Vertex e_y = {.position = {0.0, 1.0, 2.0}, .color = {0.0, 0.0, 1.0}};
  Vertex e_z = {.position = {0.0, 0.0, 4.0}, .color = {1.0, 0.0, 0.0}};

  Vertex points[] = {
    e_x, e_y, e_z, // f1 
    e_x, zero, e_y, // f2
    e_x, zero, e_z,  // f3
    zero, e_x, e_z
  };


  while (1) {
    timer += 0.01;

    sgClearColor();
    OSW_Poll();
    sgDrawVertex(sgTriangle, points, 12);
    sgDrawBuffer();
    OSW_VideoSwapBuffers();
  }
  return 0;
}
