#pragma once

#include "vertex_buffer.hpp"
#include <cstdint>
#include <cstddef>

#include <glad/gl.h>

namespace core {
enum class VertexArrayDataType : GLenum {
  kByte                = GL_BYTE,
  kUnsignedByte        = GL_UNSIGNED_BYTE,
  kShort               = GL_SHORT,
  kUnsignedShort       = GL_UNSIGNED_SHORT,
  kInteger             = GL_INT,
  kUnsignedInteger     = GL_UNSIGNED_INT,
  kHalfFloat           = GL_HALF_FLOAT,
  kFloat               = GL_FLOAT,
  kDouble              = GL_DOUBLE,
  kFixed               = GL_FIXED,
  kIntegerRev          = GL_INT_2_10_10_10_REV,
  kUnsignedIntegerRev  = GL_UNSIGNED_INT_2_10_10_10_REV,
  kUnsignedIntegerRev2 = GL_UNSIGNED_INT_10F_11F_11F_REV,
};

struct VertexAttributeInfo {
  uint32_t index;
  int32_t size;
  VertexArrayDataType type;
  bool is_data_normalized;
  int32_t stride;
  size_t offset_ptr;
};

class VertexArray {
friend class VertexArrayBuilder;

public:
  static
  void Unbind();
  void Bind() const;
  void Destroy();
  void EnableAttribute(uint32_t index);
  void DisableAttribute(uint32_t index);

private:
  VertexArray(uint32_t id) : id_(id) {};

private:
  uint32_t id_;
};

class VertexArrayBuilder {
public:
  static
  VertexArrayBuilder Begin() {
    return VertexArrayBuilder();
  }
  VertexArrayBuilder &CreateVertexArrayObject();
  VertexArrayBuilder &WithBuffer(VertexBuffer buffer);
  VertexArrayBuilder &WithVertexArrayAttributeInfo(const VertexAttributeInfo &info, bool enabled);
  VertexArray         Finish();

private:
  VertexArrayBuilder() : id_(0) {};

private:
  uint32_t id_;
};
}