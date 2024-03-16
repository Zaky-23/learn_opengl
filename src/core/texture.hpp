#pragma once

#include <cstdint>

#include <glad/gl.h>

#include "image.hpp"

namespace core {
enum class TextureWrapMode : GLenum {
  kClampToEdge       = GL_CLAMP_TO_EDGE, 
  kClampToBorder     = GL_CLAMP_TO_BORDER, 
  kMirroredRepeat    = GL_MIRRORED_REPEAT, 
  kRepeat            = GL_REPEAT, 
  kMirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE,
};

enum class TextureFilterMode : GLenum {
  kNearest = GL_NEAREST,
  kLinear  = GL_LINEAR,
};

class Texture {
friend class TextureBuilder;  

public:
  static
  void Unbind();
  void Bind() const;
  void Destroy();

private:
  Texture(uint32_t id);

private:
  uint32_t id_;

};

class TextureBuilder {
public:
  static
  TextureBuilder  Begin();
  TextureBuilder &CreateTexture();
  TextureBuilder &WithWrapS(TextureWrapMode wrap_mode);
  TextureBuilder &WithWrapT(TextureWrapMode wrap_mode);
  TextureBuilder &WithWrapR(TextureWrapMode wrap_mode);
  TextureBuilder &WithMagnifyFilter(TextureFilterMode filter_mode);
  TextureBuilder &WithMinimizeFilter(TextureFilterMode filter_mode);
  TextureBuilder &WithImage();
  TextureBuilder &WithMipmap(bool with_mipmap);
  Texture         Finish();

private:
  
};
}