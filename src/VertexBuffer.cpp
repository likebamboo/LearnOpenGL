//
// Created by 李文涛 on 2024/1/27.
//

#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned size) {
    glCall(glGenBuffers(1, &m_RendererId));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    glCall(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::Bind() const {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::UnBind() const {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
