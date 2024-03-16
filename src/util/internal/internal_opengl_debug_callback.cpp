#include "internal_opengl_debug_callback.hpp"

#include <glad/gl.h>

#include "../log.hpp"

namespace util::internal {
void OpenGLDebugCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, 
                          const char *message, const void *userParam) {
  
  if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

  switch (source) {
  case GL_DEBUG_SOURCE_API:             
    LOG_ERROR("Source: API");
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   
    LOG_ERROR("Source: Window System");
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER: 
    LOG_ERROR("Source: Shader Compiler");
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:     
    LOG_ERROR("Source: Third Party");
    break;
  case GL_DEBUG_SOURCE_APPLICATION:     
    LOG_ERROR("Source: Application");
    break;
  case GL_DEBUG_SOURCE_OTHER:           
    LOG_ERROR("Source: Other");
    break;
  }

  switch (type) {
  case GL_DEBUG_TYPE_ERROR:               
    LOG_ERROR("Type: Error"); 
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: 
    LOG_ERROR("Type: Deprecated Behaviour"); 
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  
    LOG_ERROR("Type: Undefined Behaviour"); 
    break;
  case GL_DEBUG_TYPE_PORTABILITY:         
    LOG_ERROR("Type: Portability"); 
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:         
    LOG_ERROR("Type: Performance"); 
    break;
  case GL_DEBUG_TYPE_MARKER:              
    LOG_ERROR("Type: Marker"); 
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:          
    LOG_ERROR("Type: Push Group"); 
    break;
  case GL_DEBUG_TYPE_POP_GROUP:           
    LOG_ERROR("Type: Pop Group"); 
    break;
  case GL_DEBUG_TYPE_OTHER:               
    LOG_ERROR("Type: Other"); 
    break;
  }
    
  switch (severity) {
  case GL_DEBUG_SEVERITY_HIGH:         
    LOG_ERROR("Severity: high"); 
      break;
  case GL_DEBUG_SEVERITY_MEDIUM:       
    LOG_ERROR("Severity: medium"); 
      break;
  case GL_DEBUG_SEVERITY_LOW:          
    LOG_ERROR("Severity: low"); 
      break;
  case GL_DEBUG_SEVERITY_NOTIFICATION: 
    LOG_ERROR("Severity: notification"); 
      break;
  }
}
}