//
// Created by 李文涛 on 2024/1/28.
//

#include "Texture.h"

#include "Renderer.h"
#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string &path): file_path(path), m_RendererId(0),
                                           mLocalBuffer(nullptr), m_width(0), m_height(0), m_bpp(0) {
    stbi_set_flip_vertically_on_load(1);
    mLocalBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

    glCall(glGenTextures(1, &m_RendererId));
    glCall(glBindTexture(GL_TEXTURE_2D , m_RendererId));

    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,m_width,m_height,0,GL_RGBA,GL_UNSIGNED_BYTE, mLocalBuffer));
    glCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (mLocalBuffer) {
        stbi_image_free(mLocalBuffer);
    }
}

Texture::~Texture() {
    glCall(glDeleteTextures(1, &m_RendererId));
}

void Texture::Bind(unsigned int slot) const {
    glCall(glActiveTexture(GL_TEXTURE0 + slot));
    glCall(glBindTexture(GL_TEXTURE_2D , m_RendererId));
}

void Texture::UnBind() const {
    glCall(glBindTexture(GL_TEXTURE_2D, 0));
}
