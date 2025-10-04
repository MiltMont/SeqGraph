#ifndef __TYPES__
#define __TYPES__
#include <libosw/types.h>

#define W 601
#define H 601
#define SHADER_BUFF_SIZE 32

/// Math
typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];
typedef float mat3[3][3];
typedef float mat4[4][4];

typedef f32 Buffer[SHADER_BUFF_SIZE];

typedef u32 Color;

enum PrimitiveType { sgPoint, sgLine, sgTriangle };
typedef struct {
  vec3 position;
  vec3 color;
} Vertex;

typedef u32 Fragment[2];

#endif
