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

void __default_vert_shader(vec4 out, vec3 vert, Buffer buffer) {
  out[0] = vert[0];
  out[1] = vert[1];
  out[2] = vert[2];
  out[3] = 1.0;
}

void __default_frag_shader(vec4 color, f32 x_r, f32 y_r, Buffer buffer) {
  f32 tempX = (x_r + 1) / 2; 
  f32 tempY = (y_r + 1) / 2; 
  color[0] = tempX;
  color[1] = 0.0;
  color[2] = tempY;
  color[3] = 1.0;
}

/// Internal function
void _sgDrawPoints(vec3 * vertex, u32 count) {
  for (int i = 0; i < count; i++) {

    vec3 current = {vertex[i][0], vertex[i][1]};
    printf("Current point: (%f, %f)\n", current[0], current[1]);
    vec4 vert; 
    Buffer buffer = {0};

    // Vertex shader
    __default_vert_shader(&vert, current, buffer);

    f32 w = vert[3];

    // Clipping
    if (current[1] > w || current[1] < - w || current[0] > w || current[0] < -w)  {
      printf("BREAK!!! : (%f, %f)\n",current[0], current[1]);
      break;
    }

    // Perspective correction
    current[0] = current[0]/w;
    current[1] = current[1]/w;

    // Viewport transformation
    current[0] = (viewPort_w / 2) * (current[0] + 1) + viewPort_x;
    current[1] = (viewPort_h / 2) * (-current[1] + 1) + viewPort_y;

    // Fragment shader
    Color finalColor = 0x00000000;
    vec4 color = {0.0,0.0,0.0,0.0};

    __default_frag_shader(color, current[0], current[1], buffer);

    finalColor |= (u32)(color[0] * 255.0f); 
    finalColor |= (u32)(color[1] * 255.0f) << 8;
    finalColor |= (u32)(color[2] * 255.0f) << 16;

    printf("Final color: %f\n", finalColor);
    sgPokePixel(current[0], current[1], finalColor);
  }

}
