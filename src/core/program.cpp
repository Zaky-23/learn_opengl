#include "program.hpp"

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "../util/exit.hpp"
#include "../util/shader.hpp"

namespace core {
void ShaderProgram::Unbind() {
	glUseProgram(0);
}

void ShaderProgram::Bind() const {
	glUseProgram(id_);
}

void ShaderProgram::Destroy() {
	glDeleteProgram(id_);
	id_ = 0;
}

void ShaderProgram::SetFloat(std::string_view name, float value) {
  glUniform1f(glGetUniformLocation(id_, name.data()), value);
}

int32_t ShaderProgram::GetUnifromLocation(std::string_view uniform) {
  if (uniform_locations_.contains(uniform)) {
    return uniform_locations_[uniform];
  }

  int32_t location = glGetUniformLocation(id_, uniform.data());

  if (-1 == location) {
    return location;
  }

  uniform_locations_[uniform] = location;

  return location;
}

ShaderProgramBuilder::ShaderProgramBuilder() {
  id_ = 0;
  vertex_id_ = 0;
  fragment_id_ = 0;
  compute_id_ = 0;
  geometry_id_ = 0;
}

ShaderProgramBuilder &ShaderProgramBuilder::WithVertexShaderFromPath(
	string_view path
	) {
  vertex_id_= shader::CreateShaderFromPath(path, shader::ShaderType::kVertex); 
  return *this;
}

ShaderProgramBuilder &ShaderProgramBuilder::WithFragmentShaderFromPath(
  string_view path
  ) {
  fragment_id_ = shader::CreateShaderFromPath(path, shader::ShaderType::kFragment); 
  return *this;
}

ShaderProgramBuilder &ShaderProgramBuilder::WithComputeShaderFromPath(
  string_view path
  ) {
  compute_id_ = shader::CreateShaderFromPath(path, shader::ShaderType::kCompute); 
  return *this;
}

ShaderProgramBuilder &ShaderProgramBuilder::WithGeometryShaderFromPath(
  string_view path
  ) {
  geometry_id_= shader::CreateShaderFromPath(path, shader::ShaderType::kGeometry); 
  return *this;
}

ShaderProgram ShaderProgramBuilder::Finish() {
  id_ = shader::CreateShaderProgramFromShaders({vertex_id_, fragment_id_, compute_id_, geometry_id_});
  shader::DeleteShaders({vertex_id_, fragment_id_, compute_id_, geometry_id_});
  ShaderProgram program(id_);
  return program;
}

}