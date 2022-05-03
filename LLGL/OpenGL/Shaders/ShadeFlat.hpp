#pragma once

#include "../Shader.hpp"

namespace llgl::opengl::shaders
{

class ShadeFlat : public Shader
{
public:
    ShadeFlat();

    void set_light_position(Vector3f lp) { m_light_position = lp; }
    void set_light_color(Colorf lc) { m_light_color = lc; }

private:
    virtual AttributeMapping attribute_mapping() const override;
    virtual void on_bind(ShaderScope& scope) const override;

    Vector3f m_light_position;
    Colorf m_light_color;
};

}
