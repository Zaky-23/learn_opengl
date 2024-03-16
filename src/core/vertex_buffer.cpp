#include "vertex_buffer.hpp"
#include "glad/gl.h"

namespace core {
void VertexBuffer::Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Bind() const {
  glBindBuffer(static_cast<GLenum>(target_), id_);
}

void VertexBuffer::Destroy() {
  glDeleteBuffers(1, &id_);
}

VertexBufferBuilder::VertexBufferBuilder() {
  id_ = 0;
  target_ = VertexBufferTarget::kNone;
  data_ = nullptr;
  size_ = 0;
  usage_ = VertexBufferUsage::kNone;
}

VertexBufferBuilder &VertexBufferBuilder::CreateBuffer() {
  glCreateBuffers(1, &id_);
  return *this;
}

VertexBufferBuilder &VertexBufferBuilder::WithTarget(VertexBufferTarget target) {
  target_ = target;
  return *this;
}

VertexBufferBuilder &VertexBufferBuilder::WithData(void * data) {
  data_ = data;
  return *this;
}

VertexBufferBuilder &VertexBufferBuilder::WithSize(size_t size) {
  size_ = size;
  return *this;
}

VertexBufferBuilder &VertexBufferBuilder::WithUsage(VertexBufferUsage usage) {
  usage_ = usage;
  return *this;
}

VertexBuffer VertexBufferBuilder::Finish() {
  glNamedBufferData(id_, size_, data_, static_cast<GLenum>(usage_));
  return VertexBuffer(id_, target_);
}

}