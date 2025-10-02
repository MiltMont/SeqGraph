#include <seqGraph/utils.h>

void perspectiveCorrection(f32 *x, f32 *y, f32 w)
{
    x[0] = x[0] / w;
    x[1] = x[1] / w;
}

/// @brief Check if a point (x,y) is in the triangle formed by `a`,`b`,`c`.
/// @param a
/// @param b
/// @param c
/// @param x
/// @param y
/// @return
bool isInTriangle(vec2 a, vec2 b, vec2 c, f32 x, f32 y)
{
    f32 denom = (b[1] - c[1]) * (a[0] - c[0]) + (c[0] - b[0]) * (a[1] - c[1]);
    f32 alpha = ((b[1] - c[1]) * (x - c[0]) + (c[0] - b[0]) * (y - c[1])) / denom;
    f32 beta = ((c[1] - a[1]) * (x - c[0]) + (a[0] - c[0]) * (y - c[1])) / denom;
    f32 gamma = 1.0f - alpha - beta;
    return alpha >= 0 && beta >= 0 && gamma >= 0;
}
