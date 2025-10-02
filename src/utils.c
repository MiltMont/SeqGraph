#include <seqGraph/utils.h>
#include <seqGraph/trx.h>

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

Color vec4ToColor(vec4 color)
{
    u8 r = (u8)(color[0] * 255.0f);
    u8 g = (u8)(color[1] * 255.0f);
    u8 b = (u8)(color[2] * 255.0f);
    u8 a = (u8)(color[3] * 255.0f);

    return (a << 24) | (b << 16) | (g << 8) | r;
}

f32 *getBarycentrycCoordinates(vec2 A, vec2 B, vec2 C, vec3 D)
{
    f32 totalArea = areaOfTriangle(A, B, C);
    LOG("Area ABC=%f", totalArea);
}

f32 areaOfTriangle(vec3 A, vec3 B, vec3 C)
{
    vec3 cross;
    vec3 AB;
    vec3 AC;
    vec3Cross(cross, vec3_sub(AB, B, A), vec3_sub(AC, C, A));
    f32 dot = vec3_dot(cross, cross);
    f32 norm = sqrt(dot);

    return norm / 2;
}
