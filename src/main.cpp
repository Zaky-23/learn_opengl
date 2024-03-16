
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "core/program.hpp"
#include "core/vertex_array.hpp"
#include "core/vertex_buffer.hpp"
#include "util/log.hpp"
#include "util/opengl_debug.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void OnWindowResize(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  if (glfwInit() == GLFW_FALSE) {
    LOG_ERROR("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); 

  GLFWwindow *window = glfwCreateWindow(
    WINDOW_WIDTH, 
    WINDOW_HEIGHT, 
    "[3D Engine]", 
    nullptr, 
    nullptr
    );

  if(nullptr == window) {
    const char *msg = nullptr;
    glfwGetError(&msg);
    LOG_ERROR("Failed create window");
    LOG_ERROR("glfwError: {}", msg);
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGL(static_cast<GLADloadfunc>(glfwGetProcAddress))) {
    LOG_ERROR("Failed to load OpenGL");
  }

  if (util::opengl::DebugContextEnabled()) {
    util::opengl::RegisterDebugCallback();
  }

  LOG_INFO("GPU Vendor: {}", 
    reinterpret_cast<const char *>(glGetString(GL_VENDOR))
    );
  LOG_INFO("GPU Model: {}", 
    reinterpret_cast<const char *>(glGetString(GL_RENDERER))
    );
  LOG_INFO("OpenGL Version: {}", 
    reinterpret_cast<const char *>(glGetString(GL_VERSION))
    );
  LOG_INFO("OpenGL Shading Language Version: {}", 
    reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION))
    );

  glfwSetFramebufferSizeCallback(window, OnWindowResize);

  float vertices[] = {
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
   -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
  };

  uint8_t indices[] = {
    0, 1, 2,
  };

  core::VertexBuffer vbo = core::VertexBufferBuilder::Begin()
                            .CreateBuffer()
                            .WithTarget(core::VertexBufferTarget::kArray)
                            .WithData(vertices)
                            .WithSize(sizeof(vertices))
                            .WithUsage(core::VertexBufferUsage::kStaticDraw)
                            .Finish();

  core::VertexBuffer ebo = core::VertexBufferBuilder::Begin()
                            .CreateBuffer()
                            .WithTarget(core::VertexBufferTarget::kElementArray)
                            .WithData(indices)
                            .WithSize(sizeof(indices))
                            .WithUsage(core::VertexBufferUsage::kStaticDraw)
                            .Finish();

  core::VertexArray vao = core::VertexArrayBuilder::Begin()
                            .CreateVertexArrayObject()
                            .WithBuffer(vbo)
                            .WithBuffer(ebo)
                            .WithVertexArrayAttributeInfo(core::VertexAttributeInfo {
                              .index = 0,
                              .size = 3,
                              .type = core::VertexArrayDataType::kFloat,
                              .is_data_normalized = false,
                              .stride = 6 * sizeof(float),
                              .offset_ptr = 0
                            }, true)
                            .WithVertexArrayAttributeInfo(core::VertexAttributeInfo {
                              .index = 1,
                              .size = 3,
                              .type = core::VertexArrayDataType::kFloat,
                              .is_data_normalized = false,
                              .stride = 6 * sizeof(float),
                              .offset_ptr = 3 * sizeof(float)
                            }, true)
                            .Finish();

  core::ShaderProgram program = core::ShaderProgramBuilder::Begin()
                                .WithVertexShaderFromPath("shaders/shader.vert")
                                .WithFragmentShaderFromPath("shaders/shader.frag")
                                .Finish();

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 0.5f, 0.25f, 1.0f);

    program.Bind();
    vao.Bind();
    ebo.Bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}