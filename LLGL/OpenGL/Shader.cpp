#include "Shader.hpp"

#include "Error.hpp"
#include "Extensions.hpp"

#include <cassert>
#include <iostream>
#include <memory>

namespace llgl::opengl {

ShaderObject::ShaderObject(std::string const& source, Type type)
    : m_type(type)
{
    ensure_glew();
    // TODO: Check if shader type is supported

    m_id = glCreateShader(static_cast<GLenum>(type));
    handle_error();

    char const* sources[] = {
        source.c_str()
    };
    int const lengths[] = {
        static_cast<int>(source.size())
    };
    glShaderSource(m_id, 1, sources, lengths);
    handle_error();
    glCompileShader(m_id);
    handle_error();

    GLint success = 0;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    handle_error();
    if (!success) {
        GLint max_length = 0;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &max_length);
        handle_error();
        std::string error_message;
        error_message.resize(max_length);
        glGetShaderInfoLog(m_id, max_length, &max_length, error_message.data());
        handle_error();
        std::cout << "ShaderObject: Failed to compile: " << error_message << std::endl;
        glDeleteShader(m_id);
        handle_error();
        return;
    }

    m_valid = true;
}

ShaderObject::~ShaderObject()
{
    glDeleteShader(m_id);
    handle_error();
}

Program::Program(std::span<ShaderObject const> shader_objects)
{
    std::cout << "Program: Linking " << shader_objects.size() << " shader objects" << std::endl;
    m_id = glCreateProgram();
    handle_error();
    for (auto& shader_object : shader_objects) {
        assert(shader_object.valid());
        glAttachShader(m_id, shader_object.id());
        handle_error();
    }

    // TODO: Attrib locations if supported
    glLinkProgram(m_id);
    handle_error();
    GLint success = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        GLint max_length = 0;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &max_length);
        handle_error();
        std::string error_message;
        error_message.resize(max_length);
        glGetProgramInfoLog(m_id, max_length, &max_length, error_message.data());
        handle_error();
        std::cout << "Program: Failed to link shader program: " << error_message << std::endl;
        glDeleteProgram(m_id);
        handle_error();
        return;
    }

    for (auto& shader_object : shader_objects) {
        glDetachShader(m_id, shader_object.id());
        handle_error();
    }

    m_valid = true;
}

static Program const* s_current_shader = nullptr;

Program::~Program()
{
    glDeleteProgram(m_id);
    handle_error();
    if (s_current_shader == this)
        s_current_shader = nullptr;
}

void Program::bind() const
{
    assert(valid());
    glUseProgram(id());
    s_current_shader = this;
    handle_error();
}

Program const* Program::current()
{
    return s_current_shader;
}

int ShaderScope::uniform_location(std::string const& name)
{
    ErrorHandler handler;
    return glGetUniformLocation(m_shader.program().id(), name.c_str());
}

void ShaderScope::set_uniform(std::string const& name, Util::Matrix4x4f matrix)
{
    ErrorHandler handler;
    glUniformMatrix4fv(uniform_location(name), 1, true, matrix.raw_data());
}

void ShaderScope::set_uniform(std::string const& name, CurrentTextureTag)
{
    ErrorHandler handler;
    glUniform1i(uniform_location(name), 0);
}

void ShaderScope::set_uniform(std::string const& name, bool value)
{
    ErrorHandler handler;
    glUniform1i(uniform_location(name), value);
}

void ShaderScope::set_uniform(std::string const& name, Vector2f vec)
{
    ErrorHandler handler;
    glUniform2f(uniform_location(name), vec.x, vec.y);
}

void ShaderScope::set_uniform(std::string const& name, Vector3f vec)
{
    ErrorHandler handler;
    glUniform3f(uniform_location(name), vec.x, vec.y, vec.z);
}

void ShaderScope::set_uniform(std::string const& name, Colorf color)
{
    ErrorHandler handler;
    glUniform4f(uniform_location(name), color.r, color.g, color.b, color.a);
}

void Shader::bind(ShaderScope& scope) const
{
    m_program.bind();
    on_bind(scope);
}

}
