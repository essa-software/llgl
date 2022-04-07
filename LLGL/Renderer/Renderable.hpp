#pragma once

namespace llgl
{

class Renderer;

class Renderable
{
public:
    virtual ~Renderable() = default;
    virtual void render(Renderer&) const = 0;
};

}
