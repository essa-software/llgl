#pragma once

#include <LLGL/Core/Image.hpp>
#include <optional>
#include <string_view>

namespace llgl {

class ImageLoader {
public:
    static std::optional<Image> load_from_file(std::string const& path);
};

}
