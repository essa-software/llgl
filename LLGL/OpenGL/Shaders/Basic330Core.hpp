#pragma once

#include "../Shader.hpp"

namespace llgl::opengl::shaders
{

class Basic330Core : public Shader
{
public:
    Basic330Core();

private:
    virtual AttributeMapping attribute_mapping() const override;
    virtual void on_bind(ShaderScope&) const override;
};

}
