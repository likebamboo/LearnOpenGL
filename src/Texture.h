//
// Created by 李文涛 on 2024/1/28.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>


class Texture {
private:
    unsigned int m_RendererId;

    std::string file_path;

    unsigned char *mLocalBuffer;

    int m_width;
    int m_height;
    int m_bpp;

public:
    Texture(const std::string &path);

    ~Texture();

    void Bind(unsigned int slot = 0) const;

    void UnBind() const;

    inline int GetWidth() const {
        return m_width;
    }

    inline int GetHeight() const {
        return m_height;
    }
};

#endif //TEXTURE_H
