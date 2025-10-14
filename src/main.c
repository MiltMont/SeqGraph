#include <libosw/osw.h>
#include <seqGraph/seqGraph.h>
#include <seqGraph/trx.h>

int main(int argc, char *argv[]) {
  // Create window and check for errors
  u32 err = OSW_Init("SeqGraph", W * 2, H * 2, 0);

  if (err != OSW_OK) {
    return err;
  }

  Color background = 0x0;

  sgSetClearColor(background, 100.0);
  sgViewport(0, 0, W, H);

  f32 timer = 0;

  Vertex cubePoints[] = {

      // Bottom
      {.position = {0.0, 0.0, 0.0}, .color = {1.0, 0.0, 0.0}},
      {.position = {0.0, 0.0, 1.0}, .color = {0.0, 1.0, 0.0}},
      {.position = {1.0, 0.0, 1.0}, .color = {1.0, 1.0, 0.0}},
      {.position = {1.0, 0.0, 0.0}, .color = {0.0, 0.0, 1.0}},

      // Top
      {.position = {0.0, 1.0, 0.0}, .color = {1.0, 1.0, 0.0}},
      {.position = {0.0, 1.0, 1.0}, .color = {0.0, 0.0, 1.0}},
      {.position = {1.0, 1.0, 1.0}, .color = {1.0, 0.0, 0.0}},
      {.position = {1.0, 1.0, 0.0}, .color = {0.0, 1.0, 0.0}},
  };

  u32 cubeIndices[] = {
      0, 4, 3, // front face
      4, 7, 3, // front face
      0, 1, 5, // left
      0, 5, 4, // left
      1, 2, 5, // back
      2, 5, 6, // back
      2, 3, 7, // right
      2, 7, 6, // right
      4, 5, 7, // top
      5, 6, 7, // top
      0, 1, 3, // bottom
      1, 2, 3, // bottom
  };

  u32 cubeEdgeIndices[] = {
      0, 1, //
      1, 2, //
      2, 3, //
      3, 0, //
      0, 4, //
      1, 5, //
      2, 6, //
      3, 7, //
      4, 5, //
      5, 6, //
      6, 7, //
      7, 4,
  };

  Vertex trianglePoints[] = {
      {.position = {1.0, 1.0, 1.0}, .color = {1.0, 1.0, 0.0}},
      {.position = {2.0, 1.0, 1.0}, .color = {1.0, 0.0, 0.0}},
      {.position = {1.0, 2.0, 1.0}, .color = {0.0, 1.0, 0.0}},
      {.position = {1.0, 1.0, 2.0}, .color = {0.0, 0.0, 1.0}},
  };

  u32 indices[] = {
      0, 1, 2, 0, 2, 3, // f3
      1, 2, 3,          // f1
      3, 0, 1,          // f2
      0, 3, 2,
  };

  while (1) {
    timer += 1;
    sgClear();

    OSW_Poll();
    sgSetVertexBytes(timer, 0);
    sgDrawIndexedVertex(sgTriangle, cubePoints, cubeIndices, 36);
    sgDrawIndexedVertex(sgLine, cubePoints, cubeEdgeIndices, 24);
    sgDrawBuffer();
    OSW_VideoSwapBuffers();
  }

  return 0;
}
