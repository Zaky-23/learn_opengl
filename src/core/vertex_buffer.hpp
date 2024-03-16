#pragma once

#include <cstdint>
#include <cstddef>

#include "glad/gl.h"

namespace core {
enum class VertexBufferTarget : GLenum {
  kNone               = 0,
  kArray              = GL_ARRAY_BUFFER,
  kAtomicCounter      = GL_ATOMIC_COUNTER_BUFFER,
  kCopyRead           = GL_COPY_READ_BUFFER,
  kCopyWrite          = GL_COPY_WRITE_BUFFER,
  kDispatchIndirect   = GL_DISPATCH_INDIRECT_BUFFER,
  kDrawIndirect       = GL_DRAW_INDIRECT_BUFFER,
  kElementArray       = GL_ELEMENT_ARRAY_BUFFER,
  kPixelPackBuffer    = GL_PIXEL_PACK_BUFFER,
  kPixelUnpackBuffer  = GL_PIXEL_UNPACK_BUFFER,
  kQuery              = GL_QUERY_BUFFER,
  kShaderStorage      = GL_SHADER_STORAGE_BUFFER,
  kTexture            = GL_TEXTURE_BUFFER,
  kTransfromFeedback  = GL_TRANSFORM_FEEDBACK_BUFFER,
  kUniform            = GL_UNIFORM_BUFFER,
};

enum class VertexBufferUsage : GLenum {
  kNone        = 0,
  kStreamDraw  = GL_STREAM_DRAW,
  kStreamRead  = GL_STREAM_READ,
  kStreamCopy  = GL_STREAM_COPY,
  kStaticDraw  = GL_STATIC_DRAW,
  kStaticRead  = GL_STATIC_READ,
  kStaticCopy  = GL_STATIC_COPY,
  kDynamicDraw = GL_DYNAMIC_DRAW,
  kDynamicRead = GL_DYNAMIC_READ,
  kDynamicCopy = GL_DYNAMIC_COPY,
};

class VertexBuffer {
friend class VertexBufferBuilder;

public:
  static
  void Unbind();
  void Bind() const;
  void Destroy();

private:
	VertexBuffer(uint32_t id, VertexBufferTarget target) : id_(id), target_(target) {};

private:
  uint32_t id_;
  VertexBufferTarget target_;

};

class VertexBufferBuilder {
public:
  static
    VertexBufferBuilder Begin() {
    return VertexBufferBuilder();
  }
  VertexBufferBuilder &CreateBuffer();
  VertexBufferBuilder &WithTarget(VertexBufferTarget target);
  VertexBufferBuilder &WithData(void *data);
  VertexBufferBuilder &WithSize(size_t size);
  VertexBufferBuilder &WithUsage(VertexBufferUsage usage);
  VertexBuffer         Finish();

private:
  VertexBufferBuilder();

private:
  uint32_t id_;
  VertexBufferTarget target_;
  void *data_;
  size_t size_;
  VertexBufferUsage usage_;
};
}