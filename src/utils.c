#include "seqGraph/types.h"
#include <seqGraph/utils.h>

#include <math.h>
#include <seqGraph/debug.h>
#include <seqGraph/trx.h>
#include <seqGraph/constants.h>

bool shouldClip(vec3 point, f32 FOV, f32 n, f32 f) {
  LOGV3("Clipping:", point);
  f32 fovRad = FOV * (PI/180);

  vec3 r = {-sin(fovRad), 0.0, cos(fovRad)};
  vec3 l = {sin(fovRad), 0.0, cos(fovRad)};
  vec3 z = {0.0,0.0,1.0};

  if(vec3_dot(point, r)<=0) {
    return true;
  }

  if(vec3_dot(point, l)<=0) {
    return true;
  }

  if (vec3_dot(point, z) <= n) {
    return true;
  }

  if (vec3_dot(point, z) >= f) {
    return true;
  }

  return false;
}; 

void perspectiveCorrection(vec4 point) {
  if (point[3] != 0) {
    point[0] = point[0] / point[3];
    point[1] = point[1] / point[3];
  } else {
    LOG("point[3] == 0!", 0);
  }
}

/// @brief Check if a point (x,y) is in the triangle formed by `a`,`b`,`c`.
/// @param a
/// @param b
/// @param c
/// @param x
/// @param y
/// @return
bool isInTriangle(vec2 a, vec2 b, vec2 c, f32 x, f32 y) {
  f32 denom = (b[1] - c[1]) * (a[0] - c[0]) + (c[0] - b[0]) * (a[1] - c[1]);
  f32 alpha = ((b[1] - c[1]) * (x - c[0]) + (c[0] - b[0]) * (y - c[1])) / denom;
  f32 beta = ((c[1] - a[1]) * (x - c[0]) + (a[0] - c[0]) * (y - c[1])) / denom;
  f32 gamma = 1.0f - alpha - beta;
  return alpha >= 0 && beta >= 0 && gamma >= 0;
}

Color vec4ToColor(vec4 color) {
  u8 r = (u8)(color[0] * 255.0f);
  u8 g = (u8)(color[1] * 255.0f);
  u8 b = (u8)(color[2] * 255.0f);
  u8 a = (u8)(color[3] * 255.0f);

  return (a << 24) | (b << 16) | (g << 8) | r;
}

void getBarycentricCoordinates(vec3 dest, vec3 A, vec3 B, vec3 C, vec2 D) {
  vec3 D3 = {D[0], D[1], (A[2] + B[2] + C[2]) / 3};

  f32 totalArea = areaOfTriangle(A, B, C);
  f32 alpha = areaOfTriangle(A, B, D3);
  f32 beta = areaOfTriangle(A, D3, C);
  f32 gamma = areaOfTriangle(C, B, D3);

  dest[2] = alpha / totalArea;
  dest[1] = beta / totalArea;
  dest[0] = gamma / totalArea;
  if(dest[2] + dest[1] + dest[0] == 1) {
    LOG("GOOD", 0);
  }
}

f32 areaOfTriangle(vec3 A, vec3 B, vec3 C) {
  vec3 cross;
  vec3 AB;
  vec3 AC;
  vec3Cross(cross, vec3_sub(AB, B, A), vec3_sub(AC, C, A));
  f32 dot = vec3_dot(cross, cross);
  f32 norm = sqrt(dot);

  return norm / 2;
}

void interpolate(vec3 dest, vec3 A, vec3 B, vec3 C, vec3 coefficients) {
  f32 t1 = coefficients[0];
  f32 t2 = coefficients[1];
  f32 t3 = coefficients[2];

  vec3 t1A, t2B, t3C;
  vec3_smul(t1A, t1, A);
  vec3_smul(t2B, t2, B);
  vec3_smul(t3C, t3, C);

  vec3 sum;
  vec3_add(sum, t1A, t2B);
  vec3_add(sum, sum, t3C);

  dest[0] = sum[0];
  dest[1] = sum[1];
  dest[2] = sum[2];
}
