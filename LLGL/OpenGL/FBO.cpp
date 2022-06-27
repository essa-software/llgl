#include "FBO.hpp"
#include "LLGL/OpenGL/Texture.hpp"

#include <GL/gl.h>
#include <iostream>

namespace llgl::opengl {

FBO::FBO(Vector2i size)
{
    glGenFramebuffers(1, &m_fbo);

    resize(size);
    FBOScope scope { *this };
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_renderbuffer);

    GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, buffers);

    auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "FBO: Failed to create framebuffer (status=" << std::hex << status << std::dec << ")" << std::endl;
        return;
    }
}

FBO::~FBO()
{
    glDeleteFramebuffers(1, &m_fbo);
    if (m_depth_renderbuffer)
        glDeleteRenderbuffers(1, &m_depth_renderbuffer);
}

void FBO::bind(Target target) const
{
    glBindFramebuffer(static_cast<GLenum>(target), m_fbo);
}

void FBO::resize(Vector2i size)
{
    FBOScope scope { *this };
    if (Vector2i { m_color_texture.size() } == size)
        return;
    if (!m_color_texture.id())
        m_color_texture = Texture::create_empty(Vector2u { size }, Texture::Format::RGBA);
    else
        m_color_texture.recreate(Vector2u { size }, Texture::Format::RGBA);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_color_texture.id(), 0);
    if (m_depth_renderbuffer)
        glDeleteRenderbuffers(1, &m_depth_renderbuffer);
    glGenRenderbuffers(1, &m_depth_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depth_renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);

    // std::cout << "FBO: recreated with size " << size.x << "," << size.y << std::endl;
}

void FBO::set_label(std::string const& str)
{
    glObjectLabel(GL_FRAMEBUFFER, m_fbo, str.size(), str.data());
}

static unsigned s_current_fbo = 0;

FBOScope::FBOScope(FBO const& fbo, FBO::Target target)
    : m_old_fbo(s_current_fbo)
    , m_target(target)
{
    fbo.bind(m_target);
}

FBOScope::~FBOScope()
{
    glBindFramebuffer(static_cast<GLenum>(m_target), m_old_fbo);
    s_current_fbo = m_old_fbo;
}

}
