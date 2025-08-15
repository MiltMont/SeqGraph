#include <seqGraph/seqGraph.h>

Color fBuffer[W * H] = {0};
Color clearColor;

void sgDrawBuffer(void) { OSW_VideoDrawBuffer(fBuffer, W, W); }

void sgSetClearColor(Color c) { clearColor = c; }

void sgClearColor() {
  for (int i = 0; i < W * H; i++) {
    fBuffer[i] = clearColor;
  }
}
