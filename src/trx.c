#include <seqGraph/trx.h>

#include <math.h>

f32 *vec3_add(vec3 dest, const vec3 v, const vec3 u) {
  vec3 res;
  res[0] = v[0] + u[0];
  res[1] = v[1] + u[1];
  res[2] = v[2] + u[2];

  dest[0] = res[0];
  dest[1] = res[1];
  dest[2] = res[2];

  return dest;
};

f32 *vec3_sub(vec3 dest, const vec3 v, const vec3 u) {
  vec3 temp;
  temp[0] = v[0] - u[0];
  temp[1] = v[1] - u[1];
  temp[2] = v[2] - u[2];

  dest[0] = temp[0];
  dest[1] = temp[1];
  dest[2] = temp[2];

  return dest;
};

f32 *vec3_mul(vec3 dest, const vec3 v, const vec3 u) {
  for (int i = 0; i < 3; i++) {
    dest[i] = v[i] * u[i];
  }
  return dest;
}

f32 *vec3_smul(vec3 dest, float k, const vec3 v) {
  vec3 temp;
  temp[0] = k * v[0];
  temp[1] = k * v[1];
  temp[2] = k * v[2];

  dest[0] = temp[0];
  dest[1] = temp[1];
  dest[2] = temp[2];

  return dest;
};

int vec3_eq(const vec3 u, const vec3 v) {
  return (u[0] == v[0]) && (u[1] == v[1]) && (u[2] == v[2]);
};

f32 *vec3_clamp(vec3 v, float a, float b) {
  for (int i = 0; i < 3; i++) {
    v[i] = CLAMP(v[i], a, b);
  }

  return v;
};

f32 *vec3_lerp(vec3 dest, const vec3 v, const vec3 u, f32 a) {
  // v + a(u - v)
  dest = vec3_add(dest, v, vec3_smul(dest, a, vec3_sub(dest, u, v)));
  return dest;
};

f32 vec3_dot(const vec3 v, const vec3 u) {
  f32 sum = v[0] * u[0] + v[1] * u[1] + v[2] * u[2];

  return sum;
}

void vec3Cross(vec3 dest, const vec3 v, const vec3 u) {
  dest[0] = v[1] * u[2] - v[2] * u[1];
  dest[1] = v[2] * u[0] - v[0] * u[2];
  dest[2] = v[0] * u[1] - v[1] * u[0];
}

f32 *vec3_cross(vec3 dest, const vec3 v, const vec3 u) {
  // (v_2u_3 - v_3u_2, v_3u_1 - v_1u_3, v_1u_2 - v_2u_1)
  dest[0] = v[1] * u[2] - v[2] * u[1];
  dest[1] = v[2] * u[0] - v[0] * u[2];
  dest[0] = v[0] * u[1] - v[1] * u[0];

  return dest;
};

f32 *vec3_reflect(vec3 dest, const vec3 m, const vec3 p);

void vec3_normalize(vec3 v) {
  float norm = sqrt(vec3_dot(v, v));
  vec3_smul(v, 1 / norm, v);
};

/// Matrix-vector multiplication: A(x).
f32 *vec3_matMul(vec3 dest, const mat3 m, vec3 p) {
  vec3 tmp;
  tmp[0] = vec3_dot(m[0], p);
  tmp[1] = vec3_dot(m[1], p);
  tmp[2] = vec3_dot(m[2], p);
  dest[0] = tmp[0];
  dest[1] = tmp[1];
  dest[2] = tmp[2];
  return dest;
};

/// M((p_x, p_y, p_z, 0))
f32 *vec3_mat3Mul(vec3 dest, const mat4 m, vec3 p) {
  vec4 res;
  res[0] = p[0];
  res[1] = p[1];
  res[2] = p[2];
  res[3] = 0;

  vec4 ret;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ret[i] = m[i][j] * res[j];
    }
  }

  dest[0] = ret[0];
  dest[1] = ret[1];
  dest[2] = ret[2];

  return dest;
};

f32 vec4_dot(const vec4 a, const vec4 b) {
  f32 res = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
  return res;
}

/// M((p_x, p_y, p_z, 1))
float vec3_mat4Mul(vec3 dest, const mat4 m, vec3 p) {
  vec4 ret;
  vec4 temp;
  temp[0] = p[0];
  temp[1] = p[1];
  temp[2] = p[2];
  temp[3] = 1;

  ret[0] = vec4_dot(m[0], temp);
  ret[1] = vec4_dot(m[1], temp);
  ret[2] = vec4_dot(m[2], temp);
  ret[3] = vec4_dot(m[3], temp);

  dest[0] = ret[0];
  dest[1] = ret[1];
  dest[2] = ret[2];

  return ret[3];
};

/// w must be greater than zero.
f32 *vec3_homogenize(vec3 v, float w) {
  for (int i = 0; i < 3; i++) {
    v[i] = v[i] / w;
  }

  return v;
};

f32 vec4_normalize(vec4 v);
/// Matrix by vector multiplication.
void vec4_matMul(vec4 dest, const mat4 m, vec4 p) {
  vec4 temp;

  temp[0] = vec4_dot(m[0], p);
  temp[1] = vec4_dot(m[1], p);
  temp[2] = vec4_dot(m[2], p);
  temp[3] = vec4_dot(m[3], p);

  dest[0] = temp[0];
  dest[1] = temp[1];
  dest[2] = temp[2];
  dest[3] = temp[3];
}
f32 vec4_homogenize(vec4 v);

// Matrix related functions

void mat4_identity(mat4 m) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      m[i][j] = (i == j) ? 1 : 0;
    }
  }
}

void mat4_mul(mat4 dest, const mat4 m1, const mat4 m2) {
  mat4 temp;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        temp[i][j] += m1[i][k] * m2[k][j];
      }
    }
  }

  dest = temp;
}

f32 vec4_normalize(vec4 v) { return 0; }

f32 *mat4Scale(mat4 m, vec3 scaling) {
  mat4 scalingMatrix = {{scaling[0], 0, 0, 0},
                        {0, scaling[1], 0, 0},
                        {0, 0, scaling[2], 0},
                        {0, 0, 0, 1}};

  vec3 result;

  vec3_mat3Mul(result, m, scaling);
  return result;
}

f32 *mat4Rotate(mat4 m, vec3 direction, u32 angle) {}

f32 *mat4Translate(mat4 m, vec3 translation) {
  mat4 translationMatrix = {{1, 0, 0, translation[0]},
                            {0, 1, 0, translation[0]},
                            {0, 0, 1, translation[0]},
                            {0, 0, 0, 1}};

  vec3 result;
  vec3_mat3Mul(result, m, translation);

  return result;
}

/// Spatial transformations
void mat4_normalMat(mat3 dest, const mat4 m) {

};

void mat4_translate(mat4 m, vec3 v) {
  vec3 result;
  mat4 translationMatrix = {
      {1, 0, 0, v[0]}, {0, 1, 0, v[1]}, {0, 0, 1, v[2]}, {0, 0, 0, 1}};

  mat4_mul(m, m, translationMatrix);
};

void mat4_rotate(mat4 m, vec3 v, float angle);
void mat4_scale(mat4 m, vec3 v) {}

void mat4_ortho(mat4 m, float left, float right, float bottom, float top,
                float near, float far);
void mat4_perspective(mat4 m, float fovy, float aspect, float znear,
                      float zfar);
