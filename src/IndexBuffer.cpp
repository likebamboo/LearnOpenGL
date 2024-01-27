//
// Created by 李文涛 on 2024/1/27.
//

#include "IndexBuffer.h"

#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_count(count) {
    glCall(glGenBuffers(1, &m_RendererId));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    glCall(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::Bind() const {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::UnBind() const {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
