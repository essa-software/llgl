#include "Image.hpp"
#include <utility>

namespace llgl {

Image::Image(Image&& other)
{
    m_pixels = std::exchange(other.m_pixels, nullptr);
    m_size = std::exchange(other.m_size, {});
}

Image& Image::operator=(Image&& other)
{
    if (this == &other)
        return *this;

    this->~Image();
    m_pixels = std::exchange(other.m_pixels, nullptr);
    m_size = std::exchange(other.m_size, {});

    return *this;
}

Image Image::create_uninitialized(Util::Vector2u size)
{
    Image image { size };
    return image;
}

Image Image::create_filled_with_color(Util::Vector2u size, Util::Color color)
{
    Image image { size };
    for (unsigned x = 0; x < image.size().x(); x++) {
        for (unsigned y = 0; y < image.size().y(); y++) {
            image.set_pixel({ x, y }, color);
        }
    }
    return image;
}

Image::Image(Util::Vector2u size)
{
    m_size = size;
    m_pixels = new Util::Color[pixel_count()];
}

Image::~Image()
{
    delete[] m_pixels;
}

}
