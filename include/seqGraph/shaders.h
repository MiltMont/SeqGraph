#ifndef __SHADERS__
#define __SHADERS__
#include <seqGraph/types.h>
#include <stdbool.h>

/// Vertex shader type.
typedef void (*VertShader)(vec4 out, vec3 in, f32 buffer[SHADER_BUFF_SIZE]);

/// Fragment shader type.
typedef bool (*FragShader)(vec4 out, vec3 in, f32 buffer[SHADER_BUFF_SIZE]);

typedef struct {
  VertShader vertexShader;
  FragShader fragmentShader;
} ShaderProgram;

#endif
