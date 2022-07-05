#include "Window.hpp"

#include "Impls/SDLWindow.hpp"
#include "Impls/WindowImpl.hpp"
#include <LLGL/Renderer/CoreRenderer.hpp>
#include <iostream>

namespace llgl
{

Window::Window(Vector2i size, std::u8string const& title, ContextSettings const& settings)
    : m_impl { std::make_unique<SDLWindowImpl>() }
{
    m_renderer = std::make_unique<CoreRenderer>(*this);
    create(size, title, settings);
}

void Window::create(Vector2i size, std::u8string const& title, ContextSettings const& settings)
{
    m_size = size;
    m_title = title;
    m_impl->create(size, title, settings);
}

void Window::close()
{
    m_impl->close();
}

void Window::set_title(std::u8string const& title)
{
    m_title = title;
    m_impl->set_title(title);
}

void Window::set_size(Vector2i size)
{
    m_size = size;
    m_impl->set_size(size);
}

void Window::display()
{
    m_impl->display();
}

bool Window::poll_event(Event& event)
{
    auto result = m_impl->poll_event(event);
    if (!result)
        return false;
    if (event.type == Event::Type::Resize)
        m_size = event.resize.size;
    return true;
}

void Window::set_mouse_position(Vector2i pos)
{
    m_impl->set_mouse_position(pos);
}

bool Window::is_focused() const
{
    return m_impl->is_focused();
}

}
