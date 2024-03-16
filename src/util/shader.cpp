#include "shader.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include "glad/gl.h"

#include "exit.hpp"
#include "file.hpp"
#include "glad/gl.h"
#include "log.hpp"

constexpr size_t kBufferSize = 2048;

static std::vector<GLchar> info_log(kBufferSize);

namespace shader {
uint32_t CreateShaderFromPath(std::string_view path, ShaderType type) {
  auto source = file::LoadSourceFromFile(path);
  
  if (source.empty()) {
    LOG_CRITICAL("Failed to create shader from path: {}", path);
    return 0;
  }

  std::string str = source;
  const GLchar *c_str = str.c_str();

  uint32_t id = glCreateShader(static_cast<GLenum>(type));
  glShaderSource(id, 1, &c_str, nullptr);
  glCompileShader(id);

  GLint status{ GL_FALSE };

  glGetShaderiv(id, GL_COMPILE_STATUS, &status);

  if (status != GL_TRUE) {
    glGetShaderInfoLog(id, kBufferSize, nullptr, info_log.data());
    LOG_ERROR("Failed to create shader from path: {}", path);
    LOG_ERROR("OpenGL: {}", info_log.data());
    FAIL_AND_EXIT(1);
  }

  return id;
}

uint32_t CreateShaderProgramFromShaders(std::vector<uint32_t> shaders) {
  uint32_t program_id = glCreateProgram();

  for (auto shader_id : shaders) {
    if (0 == shader_id) {
      continue;
    }
    glAttachShader(program_id, shader_id);
  }

  glLinkProgram(program_id);

  GLint status{ GL_FALSE };

  glGetProgramiv(program_id, GL_LINK_STATUS, &status);

  if (status != GL_TRUE) {
    glGetShaderInfoLog(program_id, kBufferSize, nullptr, info_log.data());
    LOG_ERROR("Failed to link shader");
    LOG_ERROR("OpenGL: {}", info_log.data());
    FAIL_AND_EXIT(1);
  }

  return program_id;
}

void DeleteShaders(std::vector<uint32_t> shaders) {
  for (auto shader_id : shaders) {
    if (0 == shader_id) {
      continue;
    }
    glDeleteShader(shader_id);
  }
}

}