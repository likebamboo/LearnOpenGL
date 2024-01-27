//
// Created by 李文涛 on 2024/1/27.
//

#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H


class IndexBuffer {
private:
    unsigned int m_RendererId = 0;
    unsigned int m_count = 0;

public:
    IndexBuffer(const unsigned int *data, unsigned int count);

    ~IndexBuffer();

    void Bind() const;

    void UnBind() const;

    unsigned int GetCount() const {
        return m_count;
    }
};


#endif //INDEXBUFFER_H
