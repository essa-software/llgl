#include "Texture.hpp"

#include "Error.hpp"

#include <GL/gl.h>
#include <cassert>
#include <iostream>

namespace llgl::opengl {

Texture::Texture()
{
}

Texture::~Texture()
{
    std::cerr << "Texture::~Texture(" << m_id << ",owner=" << m_owner << ")" << std::endl;
    if (m_owner && m_id != 0) {
        glDeleteTextures(1, &m_id);
        handle_error();
    }
}

Texture Texture::create_from_color_array(Vector2u size, Colorf const* array)
{
    Texture texture = create_empty(size);
    texture.update({}, size, array);
    return texture;
}

Texture Texture::create_empty(Vector2u size, Colorf init_color)
{
    (void)init_color;
    Texture texture;
    texture.m_size = size;
    glGenTextures(1, &texture.m_id);
    handle_error();
    texture.m_owner = true;
    return texture;
}

Texture Texture::create_from_id(int id)
{
    Texture texture;
    if (!glIsTexture(id)) {
        std::cerr << id << " is not a texture" << std::endl;
        return {};
    }
    texture.m_id = id;
    int w, h;
    {
        TextureBinder binder { texture };
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
        handle_error();
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
        handle_error();
        std::cout << w << "," << h << std::endl;
    }
    texture.m_size = { static_cast<unsigned int>(w), static_cast<unsigned int>(h) };
    return texture;
}

void Texture::update(Vector2u dst_pos, Vector2u src_size, Colorf const* array)
{
    assert(dst_pos.x + src_size.x <= m_size.x);
    assert(dst_pos.y + src_size.y <= m_size.y);
    TextureBinder binder(*this);
    if (dst_pos == Vector2u {}) {
        std::cerr << "Texture::update dstPos=[0] srcSize=[" << src_size.x << "," << src_size.y << "] <- " << array << " id=" << m_id << std::endl;
        // Disable mipmaps for now
        // FIXME: Code dupe
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        handle_error();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        handle_error();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_FLOAT, array);
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
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_FLOAT, nullptr);
            handle_error();
            m_initialized = true;
        }
        std::cerr << "Texture::update dstPos=[" << dst_pos.x << "," << dst_pos.y << "] srcSize=[" << src_size.x << "," << src_size.y << "] <- " << array << " id=" << m_id << std::endl;
        glTexSubImage2D(GL_TEXTURE_2D, 0, dst_pos.x, dst_pos.y, src_size.x, src_size.y, GL_RGBA8, GL_FLOAT, array);
        handle_error();
    }
}

void Texture::bind(Texture const* texture)
{
    ErrorHandler handler;
    glBindTexture(GL_TEXTURE_2D, texture ? texture->id() : 0);
}

}
