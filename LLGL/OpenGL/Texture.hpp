#pragma once

#include <LLGL/Core/Color.hpp>
#include <LLGL/Core/Vector2.hpp>
#include <utility>

namespace llgl::opengl
{

class Texture
{
public:
    Texture();
    ~Texture();
    Texture(const Texture& other) = delete;
    Texture& operator=(const Texture& other) = delete;

    Texture(Texture&& other)
    {
        *this = std::move(other);
    }

    Texture& operator=(Texture&& other)
    {
        if(this == &other)
            return *this;
        m_id = std::exchange(other.m_id, 0);
        m_size = std::exchange(other.m_size, {});
        m_initialized = std::exchange(other.m_initialized, {});
        m_owner = std::exchange(other.m_owner, {});
        return *this;
    }

    // TODO: createFromImage
    // TODO: Add some Image/Bitmap class
    static Texture create_from_color_array(Vector2u size, Colorf const* array);
    static Texture create_empty(Vector2u size, Colorf init_color = {});
    static Texture create_from_id(int);

    void update(Vector2u dst_pos, Vector2u src_size, Colorf const* array);

    unsigned id() const { return m_id; }
    Vector2u size() const { return m_size; }

    static void bind(Texture const* texture);

private:
    unsigned m_id { 0 };
    Vector2u m_size;
    bool m_initialized = false;
    bool m_owner = false;
};

class TextureBinder
{
public:
    TextureBinder(Texture const& texture) { Texture::bind(&texture); }
    ~TextureBinder() { Texture::bind(nullptr); }
};

}
