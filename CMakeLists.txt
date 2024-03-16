cmake_minimum_required(VERSION 3.28)

project("learn_opengl")

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_DIR "src")

set(SPDLOG_DIR "third_party/spdlog")
set(GLFW_DIR "third_party/glfw")
set(GLM_DIR "third_party/glm")

file(GLOB_RECURSE SRC ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.hpp)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_compile_definitions("LEARN_OPENGL_ENABLE_LOGGING")
endif()

# stb_image
include_directories("third_party/stb_image/include")
set(STB_IMAGE_SRC "third_party/stb_image/src/stb_image.cpp")

# spdlog
add_subdirectory(${SPDLOG_DIR})

# opengl
find_package(OpenGL REQUIRED)

# glad
include_directories("third_party/glad/include")
set(GLAD_SRC "third_party/glad/src/gl.c")

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_DIR})

# glm
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLM_DIR})

add_executable(${PROJECT_NAME} ${SRC} ${GLAD_SRC} ${STB_IMAGE_SRC})

target_link_libraries(${PROJECT_NAME} glfw OpenGL::OpenGL glm::glm spdlog::spdlog)