cmake_minimum_required(VERSION 3.27)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 14)

# ------------------------------------------------------------------------

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# 添加 glfw
add_subdirectory(dependencies/glfw)

# 设置一些OpenGL头文件所在目录的宏
set(GLEW_H ${PROJECT_SOURCE_DIR}/dependencies/glew-2.2.0_1/include)
set(GLFW_H ${PROJECT_SOURCE_DIR}/dependencies/glfw/include)

# 指定头文件搜索路径
include_directories(${GLEW_H} ${GLFW_H})

# 设置GLEW库所在位置，并链接
set(GLEW_LINK ${PROJECT_SOURCE_DIR}/dependencies/glew-2.2.0_1/lib/libGLEW.a)

link_libraries(${GLEW_LINK})

add_executable(LearnOpenGL src/main.cpp)
target_link_libraries(LearnOpenGL ${OPENGL_LIBRARIES} glfw)

# ---------------------------------------------------------------------

#find_package(OpenGL REQUIRED)
#include_directories(${OPENGL_INCLUDE_DIRS})
#
### 设置一些OpenGL头文件所在目录的宏
#set(GLEW_H ${PROJECT_SOURCE_DIR}/dependencies/glew-2.2.0_1/include)
#set(GLFW_H ${PROJECT_SOURCE_DIR}/dependencies/glfw-3.3.9.bin.MACOS/include)
#
## 指定头文件搜索路径
#include_directories(${GLEW_H} ${GLFW_H})
#
##设置OpenGL库所在位置，并链接
#set(GLEW_LINK ${PROJECT_SOURCE_DIR}/dependencies/glew-2.2.0_1/lib/libGLEW.dylib)
#set(GLFW_LINK ${PROJECT_SOURCE_DIR}/dependencies/glfw-3.3.9.bin.MACOS/lib-arm64/libglfw.3.dylib)
#
#link_libraries(${GLEW_LINK} ${GLFW_LINK})
#
#add_executable(LearnOpenGL src/main.cpp)
#target_link_libraries(LearnOpenGL ${OPENGL_LIBRARIES})

