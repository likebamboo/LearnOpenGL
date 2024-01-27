cmake_minimum_required(VERSION 3.20)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 14)

# ------------------------------------------------------------------------

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# 添加 glew
add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/glew-2.2.0/build/cmake)

# 添加 glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/glfw)

# 设置一些OpenGL头文件所在目录的宏
set(GLEW_H ${PROJECT_SOURCE_DIR}/dependencies/glew-2.2.0/include)
set(GLFW_H ${PROJECT_SOURCE_DIR}/dependencies/glfw/include)

# 指定头文件搜索路径
include_directories(${GLEW_H} ${GLFW_H})

add_executable(LearnOpenGL ${PROJECT_SOURCE_DIR}/src/Application.cpp
        src/Renderer.cpp
        src/Renderer.h
        src/VertexBuffer.cpp
        src/VertexBuffer.h
        src/IndexBuffer.cpp
        src/IndexBuffer.h
        src/VertextArrayLayout.h
        src/VertexArray.cpp
        src/VertexArray.h
        src/Shader.cpp
        src/Shader.h)
# glew 使用静态库, glfw 也使用静态库
target_link_libraries(LearnOpenGL ${OPENGL_LIBRARIES} glfw glew_s)
target_compile_options(LearnOpenGL PRIVATE -DGLEW_STATIC)
