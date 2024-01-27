//
// Created by 李文涛 on 2024/1/27.
//

#include "Renderer.h"
#include <iostream>

/**
 * \brief 清理错误
 */
void glClearError() {
    while (GLenum err = glGetError());
}

/**
 * \brief 检查错误
 */
bool glLogCall(const char *function, const char *file, int line) {
    while (const GLenum err = glGetError()) {
        std::cout << "[OpenGL Err]: " << function << "(" << file << "#" << line << ")" << err << std::endl;
        return false;
    }
    return true;
}
