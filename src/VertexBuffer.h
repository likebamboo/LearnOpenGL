//
// Created by 李文涛 on 2024/1/27.
//

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class VertexBuffer {
private:
    unsigned int m_RendererId = 0;

public:
    VertexBuffer(const void *data, unsigned int size);

    ~VertexBuffer();

    void Bind() const;

    void UnBind() const;
};

#endif //VERTEXBUFFER_H
