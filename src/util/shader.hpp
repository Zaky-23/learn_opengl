#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

#include "glad/gl.h"

namespace shader {
enum class ShaderType : GLenum {
  kVertex = GL_VERTEX_SHADER,
  kFragment = GL_FRAGMENT_SHADER,
  kCompute = GL_COMPUTE_SHADER,
  kGeometry = GL_GEOMETRY_SHADER,
};

uint32_t CreateShaderFromPath(std::string_view path, ShaderType type);
uint32_t CreateShaderProgramFromShaders(std::vector<uint32_t> shaders);
void     DeleteShaders(std::vector<uint32_t> shaders);
}