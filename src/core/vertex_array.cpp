#include "vertex_array.hpp"

#include <cstdint>

#include <glad/gl.h>
#include <stdexcept>


namespace core {
void VertexArray::Unbind() {
  glBindVertexArray(0);
}

void VertexArray::Bind() const {
  glBindVertexArray(id_);
}

void VertexArray::Destroy() {
  glDeleteVertexArrays(1, &id_);
  id_ = 0;
}

void VertexArray::EnableAttribute(uint32_t index) {
  glEnableVertexArrayAttrib(id_, index);
}

void VertexArray::DisableAttribute(uint32_t index) {
  glDisableVertexArrayAttrib(id_, index);
}

VertexArrayBuilder &VertexArrayBuilder::CreateVertexArrayObject() {
  glCreateVertexArrays(1, &id_);
  return *this;
}

VertexArrayBuilder &VertexArrayBuilder::WithBuffer(VertexBuffer buffer) {
  buffer.Bind();
  return *this;
}

VertexArrayBuilder &VertexArrayBuilder::WithVertexArrayAttributeInfo(const VertexAttributeInfo &info, bool enabled) {
  glBindVertexArray(id_);
  glVertexAttribPointer(info.index, 
                        info.size, static_cast<GLenum>(info.type), 
                        info.is_data_normalized, 
                        info.stride, 
                        reinterpret_cast<void *>(info.offset_ptr)
                        );
  if (enabled) {
    glEnableVertexArrayAttrib(id_, info.index);
  }

  return  *this;
}

VertexArray VertexArrayBuilder::Finish() {
  VertexBuffer::Unbind();
  return VertexArray(id_);
}

}