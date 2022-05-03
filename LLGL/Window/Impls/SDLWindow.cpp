#include "SDLWindow.hpp"

#include "../Event.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_video.h>
#include <iostream>

namespace llgl
{

SDLWindowImpl::~SDLWindowImpl()
{
    close();
}

void SDLWindowImpl::create(Vector2i size, std::u8string const& title, ContextSettings const& settings)
{
    static bool initialized = false;
    if (!initialized && SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDLWindow: Failed to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    if (SDL_GL_LoadLibrary(nullptr) < 0)
    {
        std::cout << "SDLWindow: Failed to load GL library" << std::endl;
        exit(1);
    }
    initialized = true;

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, settings.major_version);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, settings.minor_version);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    m_window = SDL_CreateWindow((char*)title.c_str(), 0, 0, size.x, size.y, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    int major, minor;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
    std::cout << "SDLWindow: Created OpenGL context version " << major << "." << minor << std::endl;
    m_context = SDL_GL_CreateContext(m_window);
}

void SDLWindowImpl::close()
{
    if (!m_window)
        return;
    SDL_DestroyWindow(m_window);
    SDL_GL_DeleteContext(m_context);
}

void SDLWindowImpl::set_title(std::u8string const& title)
{
    if (!m_window)
        return;
    SDL_SetWindowTitle(m_window, (char*)title.c_str());
}

void SDLWindowImpl::set_size(Vector2i size)
{
    if (!m_window)
        return;
    SDL_SetWindowSize(m_window, size.x, size.y);
}

void SDLWindowImpl::display()
{
    SDL_GL_SwapWindow(m_window);
}

bool SDLWindowImpl::poll_event(Event& event)
{
    while (true)
    {
        SDL_Event sdl_event;
        auto is_event = SDL_PollEvent(&sdl_event);
        if (!is_event)
            return false;
        if (sdl_event.type == SDL_QUIT)
        {
            // TODO: This is a hack to make Ctrl+C working. This should be
            // properly exposed to user.
            std::cout << "Exit requested" << std::endl;
            exit(0);
        }
        else if (sdl_event.type == SDL_WINDOWEVENT)
        {
            // TODO: Proper multiple window support
            if (sdl_event.window.windowID != SDL_GetWindowID(m_window))
                continue;
            switch (sdl_event.window.event)
            {
                case SDL_WINDOWEVENT_RESIZED:
                    event.type = Event::Type::Resize;
                    event.resize.size = Vector2i { sdl_event.window.data1, sdl_event.window.data2 };
                    break;
                default:
                    std::cout << "SDLWindow: Unhandled window event (type=" << (int)sdl_event.window.event << ")" << std::endl;
                    return false;
            }
            return true;
        }
        else if (sdl_event.type == SDL_KEYDOWN)
        {
            event.type = Event::Type::KeyPress;
            event.key.keycode = static_cast<KeyCode>(sdl_event.key.keysym.sym);
            return true;
        }
        else if (sdl_event.type == SDL_KEYUP)
        {
            event.type = Event::Type::KeyRelease;
            event.key.keycode = static_cast<KeyCode>(sdl_event.key.keysym.sym);
            return true;
        }
        else if (sdl_event.type == SDL_MOUSEMOTION)
        {
            event.type = Event::Type::MouseMove;
            event.mouse_move.position = { sdl_event.motion.x, sdl_event.motion.y };
            event.mouse_move.relative = { sdl_event.motion.xrel, sdl_event.motion.yrel };
            return true;
        }
        // TODO
        std::cout << "SDLWindow: Unhandled event (type=" << sdl_event.type << ")" << std::endl;
        return false;
    }
}

void SDLWindowImpl::set_mouse_position(Vector2i pos)
{
    SDL_WarpMouseInWindow(m_window, pos.x, pos.y);
}

}
