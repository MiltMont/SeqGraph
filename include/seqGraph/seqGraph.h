#ifndef __SG_H__
#define __SG_H__
#include <libosw/osw.h>
#include <trx.h>
#include <stdbool.h>
#include <math.h>

#define W 400
#define H 400
#define SHADER_BUFF_SIZE 32

typedef f32 Buffer[SHADER_BUFF_SIZE];

/// Types
typedef u32 Color;

enum PrimitiveType
{
    sgPoint,
    sgLine,
    sgTriangle
};

typedef f32 Fragment[2];

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

/// Internal functions
void _sgDrawPoints(vec3 *vertex, u32 count);
void _sgDrawLines(vec3 *vertex, u32 count);
void _sgDrawTriangles(vec3 *vertex, u32 count);

/// @brief Graphics pipeline implementation.
/// @param type This is of type `PrimitiveType`
/// @param vertex An array of vertices.
/// @param count The size of the provided vertex array.
void sgDrawVertex(enum PrimitiveType type, vec3 vertex[], u32 count);

void __default_vert_shader(vec4 out, vec3 vert, Buffer buffer);

bool __default_frag_shader(vec4 color, f32 x_r, f32 y_r, Buffer buffer);

/// Utility functions
void perspectiveCorrection(f32 *x, f32 *y, f32 w);

void viewportTranformation(f32 *x, f32 *y);

/// Rasterization functions
int _rasterizeLine(f32 x0, f32 y0, f32 x1, f32 y1, Fragment *dest);

#endif // !__SG_H__
