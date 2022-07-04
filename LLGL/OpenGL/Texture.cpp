#include "Texture.hpp"

#include "Error.hpp"

#include <GL/gl.h>
#include <cassert>
#include <iostream>

namespace llgl::opengl {

Texture& Texture::operator=(Texture&& other)
{
    if (this == &other)
        return *this;
    if (m_id != 0) {
        // std::cout << "glDeleteTextures(" << m_id << ") in move=" << std::endl;
        glDeleteTextures(1, &m_id);
    }
    m_id = std::exchange(other.m_id, 0);
    m_size = std::exchange(other.m_size, {});
    m_initialized = std::exchange(other.m_initialized, {});
    return *this;
}

Texture::~Texture()
{
    if (m_id != 0) {
        // std::cout << "glDeleteTextures(" << m_id << ")" << std::endl;
        glDeleteTextures(1, &m_id);
    }
}

Texture Texture::create_from_color_array(Vector2u size, Colorf const* array, Format format)
{
    Texture texture = create_empty(size);
    texture.update({}, size, array, format);
    return texture;
}

Texture Texture::create_empty(Vector2u size, Format format)
{
    Texture texture;
    texture.m_size = size;
    glGenTextures(1, &texture.m_id);
    // std::cout << "glGenTextures() = " << texture.m_id << std::endl;
    texture.recreate(size, format);
    return texture;
}

void Texture::update(Vector2u dst_pos, Vector2u src_size, Colorf const* array, Format format)
{
    assert(dst_pos.x + src_size.x <= m_size.x);
    assert(dst_pos.y + src_size.y <= m_size.y);

    auto gl_format = [&]() {
        switch (format) {
            case Format::RGBA:
                return GL_RGBA;
            case Format::RGB:
                return GL_RGB;
        }
        return 0;
    }();

    TextureBinder binder(*this);
    if (dst_pos == Vector2u {}) {
        std::cerr << "Texture::update dstPos=[0] srcSize=[" << src_size.x << "," << src_size.y << "] <- " << array << " id=" << m_id << std::endl;
        // Disable mipmaps for now
        // FIXME: Code dupe
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        handle_error();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        handle_error();
        glTexImage2D(GL_TEXTURE_2D, 0, gl_format, m_size.x, m_size.y, 0, gl_format, GL_FLOAT, array);
        handle_error();
        m_initialized = true;
        return;
    } else {
        if (!m_initialized) {
            // Disable mipmaps for now
            // FIXME: Code dupe
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            handle_error();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            handle_error();
            glTexImage2D(GL_TEXTURE_2D, 0, gl_format, m_size.x, m_size.y, 0, gl_format, GL_FLOAT, nullptr);
            handle_error();
            m_initialized = true;
        }
        std::cerr << "Texture::update dstPos=[" << dst_pos.x << "," << dst_pos.y << "] srcSize=[" << src_size.x << "," << src_size.y << "] <- " << array << " id=" << m_id << std::endl;
        glTexSubImage2D(GL_TEXTURE_2D, 0, dst_pos.x, dst_pos.y, src_size.x, src_size.y, gl_format, GL_FLOAT, array);
        handle_error();
    }
}

void Texture::recreate(Vector2u size, Format format)
{
    m_size = size;
    update({}, size, nullptr, format);
}

void Texture::bind(Texture const* texture)
{
    ErrorHandler handler;
    glBindTexture(GL_TEXTURE_2D, texture ? texture->id() : 0);
}

}
