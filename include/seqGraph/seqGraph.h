#ifndef __SG_H__
#define __SG_H__
#include <libosw/osw.h>
#include <trx.h>

#define W 400
#define H 400
#define SHADER_BUFF_SIZE 32

typedef f32 Buffer[32];

/// Types
typedef u32 Color;

enum PrimitiveType
{
    sgPoint,
    sgLine,
    sgTriangle
};

/// Draws the framebuffer.
void sgDrawBuffer(void);

/// Set the framebuffer color.
void sgSetClearColor(Color c);

/// Clear the frambuffer color.
void sgClearColor(void);

/// Sets pixel at coordinate (x,y) to Color.
void sgPokePixel(u32 x, u32 y, Color c);

/// Sets viewport variables.
void sgViewport(u32 x_0, u32 y_0, u32 w, u32 h);

/// Internal function
void _sgDrawPoints(vec3 *vertex, u32 count);
/// Pipeline implementation.
void sgDrawVertex(enum PrimitiveType type, vec3 *vertex, u32 count);

// Buffer debe ser de tipo f32 buffer[32];
void __default_vert_shader(vec4 out, vec3 vert, Buffer buffer);

// Buffer debe ser de tipo f32 buffer[32];
void __default_frag_shader(vec4 color, f32 x_r, f32 y_r, Buffer buffer);
#endif // !__SG_H__
