#include <trx.h>
#include <math.h>

f32 *vec3_add(vec3 dest, const vec3 v, const vec3 u)
{
    for (int i = 0; i < 3; i++)
    {
        dest[i] = v[i] + u[i];
    }
    return dest;
};

f32 *vec3_sub(vec3 dest, const vec3 v, const vec3 u)
{
    for (int i = 0; i < 3; i++)
    {
        dest[i] = v[i] - u[i];
    }
    return dest;
};

f32 *vec3_mul(vec3 dest, const vec3 v, const vec3 u)
{
    for (int i = 0; i < 3; i++)
    {
        dest[i] = v[i] * u[i];
    }
    return dest;
}

f32 *vec3_smul(vec3 dest, float k, const vec3 v)
{
    for (int i = 0; i < 3; i++)
    {
        dest[i] = k * v[i];
    }
    return dest;
};

int vec3_eq(const vec3 u, const vec3 v)
{
    return (u[0] == v[0]) && (u[1] == v[1]) && (u[2] == v[2]);
};

f32 *vec3_clamp(vec3 v, float a, float b)
{
    for (int i = 0; i < 3; i++)
    {
        v[i] = CLAMP(v[i], a, b);
    }

    return v;
};

f32 *vec3_lerp(vec3 dest, const vec3 v, const vec3 u, f32 a)
{
    // v + a(u - v)
    dest = vec3_add(dest, v, vec3_smul(dest, a, vec3_sub(dest, u, v)));
    return dest;
};

float vec3_dot(const vec3 v, const vec3 u)
{
    float sum;

    for (int i = 0; i < 3; i++)
    {
        sum += v[i] * u[i];
    }

    return sum;
}

f32 *vec3_cross(vec3 dest, const vec3 v, const vec3 u)
{
    // (v_2u_3 - v_3u_2, v_3u_1 - v_1u_3, v_1u_2 - v_2u_1)
    dest[0] = v[1] * u[2] - v[2] * u[1];
    dest[1] = v[2] * u[0] - v[0] * u[2];
    dest[0] = v[0] * u[1] - v[1] * u[0];

    return dest;
};

f32 *vec3_reflect(vec3 dest, const vec3 m, const vec3 p);

void vec3_normalize(vec3 v)
{
    float norm = sqrt(vec3_dot(v, v));
    vec3_smul(v, 1 / norm, v);
};

/// Matrix-vector multiplication: A(x).
f32 *vec3_matMul(vec3 dest, const mat3 m, vec3 p)
{
    for (int i = 0; i < 3; i++)
    {
        dest[i] = vec3_dot(m[i], p);
    }
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

/// M((p_x, p_y, p_z, 1))
float vec3_mat4Mul(vec3 dest, const mat4 m, vec3 p) 
{
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

    return ret[3];
 };

/// w must be greater than zero.
f32 *vec3_homogenize(vec3 v, float w)
{
    for (int i = 0; i < 3; i++)
    {
        v[i] = v[i] / w;
    }

    return v;
};

f32 vec4_normalize(vec4 v);
/// Matrix by vector multiplication.
f32 vec4_matMul(vec4 dest, const mat4 m, vec4 p);
f32 vec4_homogenize(vec4 v);

// Matrix related functions

void mat4_identity(mat4 m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = (i == j) ? 1 : 0;
        }
    }
}

void mat4_mul(mat4 dest, const mat4 m1, const mat4 m2)
{
    mat4 temp; 
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                temp[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    dest = temp;
}

f32 vec4_normalize(vec4 v) {

};