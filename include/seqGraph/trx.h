/*
 * libTRX - 1.0 - public domain
 * trx.h: Matrix and vector functions
 */

#ifndef __TRX_H__
#define __TRX_H__

#include <libosw/osw.h>
#include <seqGraph/types.h>

#define CLAMP(x, a, b) x < a ? a : (x > b ? b : x)

/* Vector related functions */
f32 *vec3_add(vec3 dest, const vec3 v, const vec3 u);
f32 *vec3_sub(vec3 dest, const vec3 v, const vec3 u);
f32 *vec3_mul(vec3 dest, const vec3 v, const vec3 u);
f32 *vec3_smul(vec3 dest, float k, const vec3 v);
int vec3_eq(const vec3 u, const vec3 v);
f32 *vec3_clamp(vec3 v, float a, float b);
f32 *vec3_lerp(vec3 dest, const vec3 v, const vec3 u, f32 a);
float vec3_dot(const vec3 v, const vec3 u);
f32 *vec3_cross(vec3 dest, const vec3 v, const vec3 u);
f32 *vec3_reflect(vec3 dest, const vec3 m, const vec3 p);
void vec3_normalize(vec3 v);
f32 *vec3_matMul(vec3 dest, const mat3 m, vec3 p);
f32 *vec3_mat3Mul(vec3 dest, const mat4 m, vec3 p);
float vec3_mat4Mul(vec3 dest, const mat4 m, vec3 p);
f32 *vec3_homogenize(vec3 v, float w);

f32 vec4_normalize(vec4 v);
f32 vec4_matMul(vec4 dest, const mat4 m, vec4 p);
f32 vec4_homogenize(vec4 v);

/* Matrix related functions */
void mat4_identity(mat4 m);
void mat4_mul(mat4 dest, const mat4 m1, const mat4 m2);
void mat4_normalMat(mat3 dest, const mat4 m);

void mat4_translate(mat4 m, vec3 v);
void mat4_rotate(mat4 m, vec3 v, float angle);
void mat4_scale(mat4 m, vec3 v);

void mat4_ortho(mat4 m, float left, float right, float bottom, float top, float near, float far);
void mat4_perspective(mat4 m, float fovy, float aspect, float znear, float zfar);

// /// Spatial transformations

// f32* mat4Scale(mat4 m, vec3 scaling);

// f32* mat4Rotate(mat4 m, vec3 direction, u32 angle);

// f32* mat4Translate(mat4 m, vec3 translation);

// f32* mat4Orto();

// f32* mat4_perspective();
#endif /*__TRX_H__*/
