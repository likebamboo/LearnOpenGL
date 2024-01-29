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

void Renderer::Clear() const {
    /* Render here */
    glCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
