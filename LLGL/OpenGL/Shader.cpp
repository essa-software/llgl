#include "Shader.hpp"

#include "Error.hpp"
#include "Extensions.hpp"

#include <cassert>
#include <iostream>
#include <memory>

namespace llgl::opengl
{

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
    if(!success)
    {
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

Shader::Shader(std::span<ShaderObject const> shader_objects, AttributeMapping attribute_mapping)
: m_attribute_mapping(attribute_mapping)
{
    std::cout << "Shader: Linking " << shader_objects.size() << " shader objects" << std::endl;
    m_id = glCreateProgram();
    handle_error();
    for(auto& shader_object : shader_objects)
    {
        assert(shader_object.valid());
        glAttachShader(m_id, shader_object.id());
        handle_error();
    }

    // TODO: Attrib locations if supported
    glLinkProgram(m_id);
    handle_error();
    GLint success = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if(!success)
    {
	    GLint max_length = 0;
	    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &max_length);
        handle_error();
        std::string error_message;
        error_message.resize(max_length);
        glGetProgramInfoLog(m_id, max_length, &max_length, error_message.data());
        handle_error();
        std::cout << "Shader: Failed to link shader program: " << error_message << std::endl;
        glDeleteProgram(m_id);
        handle_error();
        return;
    }

    for(auto& shader_object : shader_objects)
    {
        glDetachShader(m_id, shader_object.id());
        handle_error();
    }

    m_valid = true;
}

static Shader const* s_current_shader = nullptr;

Shader::~Shader()
{
    glDeleteProgram(m_id);
    handle_error();
    if(s_current_shader == this)
        s_current_shader = nullptr;
}

void Shader::bind() const
{
    assert(valid());
    glUseProgram(id());
    s_current_shader = this;
    handle_error();
}

Shader const* Shader::current()
{
    return s_current_shader;
}

int ShaderScope::uniform_location(std::string const& name)
{
    ErrorHandler handler;
    return glGetUniformLocation(m_shader.id(), name.c_str());
}

void ShaderScope::set_uniform(std::string const& name, Matrix4x4f matrix)
{
    ErrorHandler handler;
    glUniformMatrix4fv(uniform_location(name), 1, true, (float*)matrix.data);
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

namespace shaders
{

Shader& basic_330_core()
{
    static std::unique_ptr<Shader> shader;
    if(!shader)
    {
        static char const* VERTEX_SHADER = R"~~~(
#version 410 core

layout(location=1) in vec4 position;
layout(location=2) in vec4 color;
layout(location=3) in vec2 texCoord;
layout(location=4) in vec3 normal;
out vec4 f_color;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

void main()
{
    mat4 matrix = projectionMatrix * modelviewMatrix;
    f_color = color;
    gl_Position = matrix * position;
}
)~~~";
        static char const* FRAGMENT_SHADER = R"~~~(
#version 410 core

in vec4 f_color;

void main()
{
    // TODO: Textures
    gl_FragColor = f_color;
}
)~~~";
        auto objects = {
            ShaderObject{VERTEX_SHADER, ShaderObject::Vertex},
            ShaderObject{FRAGMENT_SHADER, ShaderObject::Fragment}
        };
        shader = std::make_unique<Shader>(objects, AttributeMapping{1,2,3,4});
    }
    return *shader;
}

Shader& shade_flat()
{
    static std::unique_ptr<Shader> shader;
    if(!shader)
    {
        static char const* VERTEX_SHADER = R"~~~(
#version 410 core
layout(location=1) in vec4 position;
layout(location=2) in vec4 color;
layout(location=3) in vec2 texCoord;
layout(location=4) in vec3 normal;
out vec3 f_position;
out vec4 f_color;
out vec2 f_texCoord;
out vec3 f_normal;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

void main()
{
    mat4 matrix = projectionMatrix * modelviewMatrix;
    f_position = vec3(position);
    f_normal = normal;
    f_color = color;
    f_texCoord = texCoord;
    
    gl_Position = matrix * vec4(f_position, 1.0);
}
)~~~";
        static char const* FRAGMENT_SHADER = R"~~~(
#version 410 core
in vec3 f_position;
in vec4 f_color;
in vec2 f_texCoord;
in vec3 f_normal;
uniform sampler2D texture;
uniform bool textureSet;
uniform mat4 modelviewMatrix;

uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    vec3 lightPosVS = vec3(inverse(modelviewMatrix) * lightPos);

    float ambientStrength = 0.2; // TODO: Make it configurable
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(f_normal);
    vec3 lightDir = normalize(lightPosVS - f_position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
        
    vec3 result = (ambient + diffuse) * vec3(f_color);
    gl_FragColor = vec4(result, 1.0);
}
)~~~";
        auto objects = {
            ShaderObject{VERTEX_SHADER, ShaderObject::Vertex},
            ShaderObject{FRAGMENT_SHADER, ShaderObject::Fragment}
        };
        shader = std::make_unique<Shader>(objects, AttributeMapping{1,2,3,4});
    }
    return *shader;
}
}

}
