#include "StateScope.hpp"
#include <algorithm>

namespace llgl
{

StateScope::StateScope(DrawState const& state, View const& view)
: m_shader_scope(*state.shader)
{
    m_shader_scope.set_uniform("projectionMatrix", view.matrix());
    m_shader_scope.set_uniform("modelviewMatrix", state.modelview_matrix);
    if (state.texture)
    {
        m_texture_binder.construct(*state.texture);
        m_shader_scope.set_uniform("texture", opengl::ShaderScope::CurrentTexture);
        m_shader_scope.set_uniform("textureSet", true);
    }
    else
        m_shader_scope.set_uniform("textureSet", false);
}

}
