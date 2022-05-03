#pragma once

#include "WindowImpl.hpp"

#include <LLGL/Core/Size.hpp>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <string>

namespace llgl
{

class SDLWindowImpl : public WindowImpl
{
public:
    ~SDLWindowImpl();
    virtual void create(Vector2i size, std::u8string const& title, ContextSettings const&) override;
    virtual void close() override;
    virtual void set_title(std::u8string const&) override;
    virtual void set_size(Vector2i) override;
    virtual void display() override;
    virtual bool poll_event(Event&) override;
    virtual void set_mouse_position(Vector2i) override;

private:
    SDL_Window* m_window;
    SDL_GLContext m_context;
};

}
