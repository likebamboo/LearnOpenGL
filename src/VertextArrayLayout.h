//
// Created by 李文涛 on 2024/1/27.
//

#ifndef VERTEXTARRAYLAYOUT_H
#define VERTEXTARRAYLAYOUT_H
#include <vector>

#include "GL/glew.h"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
    }
};

class VertextArrayLayout {
private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;

public:
    VertextArrayLayout(): stride(0) {
    }

    template<typename T>
    void Push(unsigned int count) {
    }

    template<>
    void Push<float>(unsigned int count) {
        elements.push_back({
            GL_FLOAT, count, GL_FALSE
        });
        stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template<>
    void Push<unsigned int>(unsigned int count) {
        elements.push_back({
            GL_UNSIGNED_INT, count, GL_FALSE
        });
        stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void Push<unsigned char>(unsigned int count) {
        elements.push_back({
            GL_UNSIGNED_BYTE, count, GL_TRUE
        });
        stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    const std::vector<VertexBufferElement> GetElements() const {
        return elements;
    }

    const unsigned int GetStride() const {
        return stride;
    }
};

#endif //VERTEXTARRAYLAYOUT_H
