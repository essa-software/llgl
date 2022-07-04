#pragma once

#include "ContextSettings.hpp"
#include "Event.hpp"
#include "Impls/WindowImpl.hpp"

#include <LLGL/Core/Vector2.hpp>
#include <LLGL/Renderer/Renderer.hpp>
#include <memory>
#include <string>

namespace llgl {

class Window {
public:
    Window(Vector2i size, std::u8string const& title, ContextSettings const& = {});

    // These are passed to WindowImpl
    void create(Vector2i size, std::u8string const& title, ContextSettings const& = {});
    void close();
    void set_title(std::u8string const&);
    void set_size(Vector2i);
    void display();
    bool poll_event(Event&);
    void set_mouse_position(Vector2i);
    bool is_focused() const;

    Renderer& renderer() { return *m_renderer; }
    Vector2i size() const { return m_size; }
    Vector2f center() const { return Vector2f { m_size } / 2.f; }
    float aspect() const { return (float)m_size.x / m_size.y; }
    Recti rect() const { return { 0, 0, size().x, size().y }; }

private:
    std::unique_ptr<WindowImpl> m_impl;
    std::unique_ptr<Renderer> m_renderer;
    std::u8string m_title;
    Vector2i m_size;
};

}
