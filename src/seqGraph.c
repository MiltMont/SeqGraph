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

void sgPokePixel(u32 x,u32 y, Color c) {
  // printf("%d, %d\n", x, y);
  fBuffer[W * y + x] = c;
}

void sgViewport(u32 x_0, u32 y_0, u32 w, u32 h) {
}