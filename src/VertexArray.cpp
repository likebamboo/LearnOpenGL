//
// Created by 李文涛 on 2024/1/27.
//

#include "VertexArray.h"

#include "Renderer.h"

VertexArray::VertexArray() {
    glCall(glGenVertexArrays(1, &m_RendererId));
}

VertexArray::~VertexArray() {
    glCall(glDeleteVertexArrays(1, &m_RendererId));
}

void VertexArray::Bind() const {
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glCall(glBindVertexArray(m_RendererId));
}

void VertexArray::UnBind() const {
    glCall(glBindVertexArray(0));
}

void VertexArray::AddLayout(const VertexBuffer &vb, const VertextArrayLayout &layout) {
    Bind();
    vb.Bind();
    const auto &elements = layout.GetElements();
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); ++i) {
        const auto &element = elements[i];

        glCall(glEnableVertexAttribArray(i));
        glCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
            layout.GetStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}
