#ifndef __SG_H__
#define __SG_H__

#include <math.h>
#include <stdlib.h>
#include <seqGraph/types.h>
#include <seqGraph/utils.h>

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

/// @brief Graphics pipeline implementation.
/// @param type The type of primitive to render.
/// @param vertex An array of vertices.
/// @param count The size of the provided vertex array.
void sgDrawVertex(enum PrimitiveType type, Vertex vertex[], u32 count);

void __default_vert_shader(vec4 out, vec3 vert, Buffer buffer);
bool __default_frag_shader(vec4 color, f32 x_r, f32 y_r, Buffer buffer);

/// Utility functions
void viewportTransformation(f32 *x, f32 *y);

/// Internal functions
void _sgDrawPoints(Vertex vertex[], u32 count);
void _sgDrawLines(Vertex vertex[], u32 count);
void _sgDrawTriangles(Vertex vertex[], u32 count);

/// @brief This function fills a Fragment array and returns the length of the
/// resulting array.
/// @param x0
/// @param y0
/// @param x1
/// @param y1
/// @param dest
/// @return
int _rasterizeLine(int x0, int y0, int x1, int y1, Fragment dest[]);

/// @brief  This function fills a Fragment array and returns the number of
/// processed fragments.
/// @param x
/// @param y
/// @param z
/// @param dest
/// @return
int _rasterizeTriangle(vec2 x, vec2 y, vec2 z, Fragment dest[]);

#endif // !__SG_H__
