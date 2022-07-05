#pragma once

#include <LLGL/Core/Color.hpp>
#include <LLGL/Core/Vector2.hpp>
#include <string>
#include <utility>

namespace llgl::opengl {

class Texture {
public:
    Texture() = default;
    ~Texture();
    Texture(const Texture& other) = delete;
    Texture& operator=(const Texture& other) = delete;

    Texture(Texture&& other)
    {
        *this = std::move(other);
    }

    Texture& operator=(Texture&& other);

    // TODO: createFromImage
    // TODO: Add some Image/Bitmap class
    enum class Format {
        RGBA,
        RGB
    };

    static Texture create_from_color_array(Vector2u size, Colorf const* array, Format);
    static Texture create_empty(Vector2u size, Format = Format::RGBA);
    static Texture create_from_id(int);

    void update(Vector2u dst_pos, Vector2u src_size, Colorf const* array, Format);
    void recreate(Vector2u, Format);

    unsigned id() const { return m_id; }
    Vector2u size() const { return m_size; }

    void set_label(std::string const&);

    static void bind(Texture const* texture);

private:
    unsigned m_id { 0 };
    Vector2u m_size;
    bool m_initialized = false;
};

class TextureBinder {
public:
    TextureBinder(Texture const& texture) { Texture::bind(&texture); }
    ~TextureBinder() { Texture::bind(nullptr); }
};

}
