//
// Created by 李文涛 on 2024/1/27.
//

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include "VertexBuffer.h"
#include "VertextArrayLayout.h"


class VertexArray {
private:
    unsigned int m_RendererId;
public:
    VertexArray();

    ~VertexArray();


    void Bind() const;

    void UnBind() const;


    void AddLayout(const VertexBuffer &vb, const VertextArrayLayout &layout);
};


#endif //VERTEXARRAY_H
