#include <seqGraph/seqGraph.h>

// Local variables 
u32 viewPort_x; 
u32 viewPort_y; 
u32 viewPort_w; 
u32 viewPort_h; 

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
  printf("Drawing at (%d, %d)\n", x, y);
  fBuffer[W * y + x] = c;
}

void sgViewport(u32 x_0, u32 y_0, u32 w, u32 h) {
  viewPort_x = x_0;
  viewPort_y = y_0; 
  viewPort_w = w;  
  viewPort_h = h; 
}

void sgDrawVertex(enum PrimitiveType type, vec3 vertex[], u32 count) { 
  switch (type) {
    case sgPoint: 
      _sgDrawPoints(vertex, count);
      break;
    default: 
      printf("Not implemented");
  }
}

/// Internal function
void _sgDrawPoints(vec3 * vertex, u32 count) {
  for (int i = 0; i < count; i++) {
  printf("Processing (%f, %f)\n", vertex[i][0], vertex[i][1] );

    vec3 current = {vertex[i][0], vertex[i][1]};
  // Vertex shader

  // Coordinate transformation
    current[0] = (viewPort_w / 2) * (current[0] + 1) + viewPort_x;
    current[1] = (viewPort_h / 2) * (-current[1] + 1) + viewPort_y;

  // Fragment shader
    Color final = 0x00000000;

    Color red = (u32)((current[0] + 1)/2 * 255.0f);
    Color blue = (u32)((current[1] + 1)/2 * 255.0f);

    final |= red;
    final |= blue << 16;
    // final |= (blue + green)/2;

    sgPokePixel(current[0], current[1], final);
  }

}