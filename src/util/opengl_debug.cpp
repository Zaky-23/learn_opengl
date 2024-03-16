#include "opengl_debug.hpp"

#include <glad/gl.h>

#include "internal/internal_opengl_debug_callback.hpp"

namespace util::opengl {
bool DebugContextEnabled() {
  int flags{ 0 };
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  return flags & GL_CONTEXT_FLAG_DEBUG_BIT;
}

void RegisterDebugCallback() {
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
  glDebugMessageCallback(util::internal::OpenGLDebugCallback, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}
}