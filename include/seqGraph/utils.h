#ifndef __UTILS__
#define __UTILS__

#include <libosw/types.h>
#include <seqGraph/types.h>
#include <seqGraph/debug.h>
#include <stdbool.h>

// Graphics utils

void perspectiveCorrection(f32 *x, f32 *y, f32 w);
/// @brief Check if a point (x,y) is in the triangle formed by `a`,`b`,`c`.
/// @param a
/// @param b
/// @param c
/// @param x
/// @param y
/// @return
bool isInTriangle(vec2 a, vec2 b, vec2 c, f32 x, f32 y);

/// @brief Transforms a `vec4` into a `Color`.
/// @param color
/// @return
Color vec4ToColor(vec4 color);

void getBarycentricCoordinates(vec3 dest, vec2 A, vec2 B, vec2 C, vec2 D);

f32 areaOfTriangle(vec3 A, vec3 B, vec3 C);
#endif