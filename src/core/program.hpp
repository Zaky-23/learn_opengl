#pragma once

#include <cstdint>
#include <string_view>
#include <unordered_map>

#include "glad/gl.h"
#include "glm/glm.hpp"

namespace core {
class ShaderProgram {
friend class ShaderProgramBuilder; 

using string_view = std::string_view;
template<typename K, typename V> 
using unordered_map = std::unordered_map<K, V>;

public:
  static 
  void Unbind();
  void Bind() const;
  void Destroy();
  void SetFloat(std::string_view name, float value);

private:
  ShaderProgram(uint32_t id) : id_(id) {};
  int32_t GetUnifromLocation(std::string_view uniform);

private:
  uint32_t id_;
  unordered_map<string_view, int32_t> uniform_locations_;
};

class ShaderProgramBuilder {
using string_view = std::string_view;

public:
  static
  ShaderProgramBuilder Begin() { 
    return ShaderProgramBuilder(); 
  }

public:
  ShaderProgramBuilder &WithVertexShaderFromPath(string_view path);
  ShaderProgramBuilder &WithFragmentShaderFromPath(string_view path);
  ShaderProgramBuilder &WithComputeShaderFromPath(string_view path);
  ShaderProgramBuilder &WithGeometryShaderFromPath(string_view path);
  ShaderProgram Finish();
  
private:
  ShaderProgramBuilder();

private:
  uint32_t id_;
  uint32_t vertex_id_;
  uint32_t fragment_id_;
  uint32_t compute_id_;
  uint32_t geometry_id_;  
};
}