#pragma once

#include "../ContextSettings.hpp"
#include "../Event.hpp"

#include <LLGL/Core/Vector2.hpp>
#include <string>

namespace llgl
{

class WindowImpl
{
public:
    virtual void create(Vector2i size, std::u8string const& title, ContextSettings const&) = 0;
    virtual void close() = 0;
    virtual void set_title(std::u8string const&) = 0;
    virtual void set_size(Vector2i) = 0;
    virtual void display() = 0;
    virtual bool poll_event(Event&) = 0;
};

}
