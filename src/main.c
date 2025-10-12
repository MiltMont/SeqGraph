#include <libosw/osw.h>
#include <math.h>
#include <seqGraph/seqGraph.h>
#include <seqGraph/trx.h>

int main(int argc, char *argv[]) {
  // Create window and check for errors
  u32 err = OSW_Init("SeqGraph", W * 2, H * 2, 0);

  if (err != OSW_OK) {
    return err;
  }

  Color background = 0xffffff;

  sgSetClearColor(background, 100.0);
  sgViewport(0, 0, W, H);

  f32 timer = 0;


  Vertex points[] = {

  // Bottom
  {.position = {0.0, 0.0, 0.0}, .color = {0.0, 0.0, 0.0}},
  {.position = {1.0, 0.0, 0.0}, .color = {1.0, 0.0, 0.0}}, 
  {.position = {0.0, 0.0, 1.0}, .color = {0.0, 0.0, 1.0}}, 
  {.position = {1.0, 0.0, 1.0}, .color = {0.0, 0.0, 1.0}}, 

  // Top
  {.position = {0.0, 1.0, 0.0}, .color = {0.0, 0.0, 0.0}},
  {.position = {1.0, 1.0, 0.0}, .color = {1.0, 0.0, 0.0}}, 
  {.position = {0.0, 1.0, 1.0}, .color = {0.0, 0.0, 1.0}}, 
  {.position = {1.0, 1.0, 1.0}, .color = {0.0, 0.0, 1.0}}, 
  };

  Vertex trianglePoints[] = {
  {.position = {0.0, 0.0, 0.0}, .color = {0.0, 0.0, 0.0}},
  {.position = {1.0, 0.0, 0.0}, .color = {1.0, 0.0, 0.0}}, 
  {.position = {0.0, 1.0, 0.0}, .color = {0.0, 1.0, 0.0}}, 
  {.position = {0.0, 0.0, 1.0}, .color = {0.0, 0.0, 1.0}}, 
  };

  u32 indices[] = {
    0,1,2,
    0, 2, 3, // f3
    1,2,3,  // f1
    3, 0, 1, // f2
    0, 3, 2,
  };


  while (1) {
    timer += 0.01;
    sgClear();

    OSW_Poll();
    sgDrawIndexedVertex(sgTriangle, trianglePoints, indices, 12);
    sgDrawBuffer();
    OSW_VideoSwapBuffers();

    // rotateY(trianglePoints[3].position, 1);
    // rotateY(trianglePoints[2].position, 1);
    // rotateY(trianglePoints[1].position, 1);
    rotateZ(trianglePoints[3].position, 1);
    rotateZ(trianglePoints[2].position, 1);
    rotateZ(trianglePoints[1].position, 1);
    rotateX(trianglePoints[3].position, 1);
    rotateX(trianglePoints[2].position, 1);
    rotateX(trianglePoints[1].position, 1);
  }

  return 0;
}
