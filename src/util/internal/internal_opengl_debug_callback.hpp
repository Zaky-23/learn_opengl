#pragma once

#include <glad/gl.h>

namespace util::internal {
void OpenGLDebugCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, 
                          const char *message, const void *userParam);
}