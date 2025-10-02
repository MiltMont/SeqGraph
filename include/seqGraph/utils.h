#ifndef __UTILS__
#define __UTILS__

#include <libosw/types.h>
#include <seqGraph/types.h>
#include <stdio.h>
#include <stdbool.h>

/// Logging
#ifdef DEBUG
#define LOG(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define LOG(fmt, ...)
#endif

#ifdef DEBUG
#define LOGV3(NAME, P) fprintf(stderr, "%s=(%f, %f, %f)\n", NAME, P[0], P[1], P[2])
#else
#define LOGV3(NAME, P)
#endif

#ifdef DEBUG
#define LOGV4(NAME, P) fprintf(stderr, "%s=(%f, %f, %f, %f)\n", NAME, P[0], P[1], P[2], P[3])
#else
#define LOGV4(NAME, P)
#endif

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

#endif