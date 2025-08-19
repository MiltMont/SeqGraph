#include <trx.h>
#include <math.h>

f32*  vec3_add(vec3 dest, const vec3 v, const vec3 u) {
    for (int i=0; i < 3; i++) {
        dest[i] = v[i] + u[i];
    }
    return dest; 
};

f32* vec3_sub(vec3 dest, const vec3 v, const vec3 u) {
    for (int i=0; i < 3; i++) {
        dest[i] = v[i] - u[i];
    }
    return dest; 
};

f32* vec3_mul(vec3 dest, const vec3 v, const vec3 u) {
    for (int i=0; i < 3; i++) {
        dest[i] = v[i] * u[i];
    }
    return dest; 
}

/// Scalar multiplication.
f32* vec3_smul(vec3 dest, float k, const vec3 v) {
    for (int i=0; i < 3; i++) {
        dest[i] = k * v[i];
    }
    return dest; 
};

int vec3_eq(const vec3 u, const vec3 v) {
    return (u[0] == v[0]) && (u[1] == v[1]) && (u[2] == v[2]);
};

f32* vec3_clamp(vec3 v, float a, float b) {
    for (int i = 0; i < 3; i++) {
        v[i] = CLAMP(v[i], a, b);
    }

    return v;
};

f32* vec3_lerp(vec3 dest, const vec3 v, const vec3 u, f32 a) {
    // v + a(u - v)
    dest = vec3_add(dest, v, vec3_smul(dest, a, vec3_sub(dest, u, v)));
    return dest;
};

float vec3_dot(const vec3 v, const vec3 u) {
    float sum; 

    for (int i = 0; i < 3; i++) {
        sum += v[i] * u[i];
    }

    return sum; 
}

f32* vec3_cross(vec3 dest, const vec3 v, const vec3 u);
f32* vec3_reflect(vec3 dest, const vec3 m, const vec3 p);

void  vec3_normalize(vec3 v) {
    float norm = sqrt(vec3_dot(v, v));
    vec3_smul(v, 1/norm, v);
};

f32* vec3_matMul(vec3 dest, const mat3 m, vec3 p);
f32* vec3_mat3Mul(vec3 dest, const mat4 m, vec3 p);
float vec3_mat4Mul(vec3 dest, const mat4 m, vec3 p);

/// w must be greater than zero. 
f32* vec3_homogenize(vec3 v, float w) {
    for (int i = 0; i < 3; i++) {
        v[i] = v[i]/ w; 
    }

    return v;
};