#pragma once


#include <GL/glew.h>
#include <LLGL/Core/Matrix.hpp>
#include <span>
#include <string>

namespace llgl::opengl
{

class ShaderObject
{
public:
    enum Type
    {
        Vertex = GL_VERTEX_SHADER,
        TessControl = GL_TESS_CONTROL_SHADER,
        TessEvaluation = GL_TESS_EVALUATION_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Compute = GL_COMPUTE_SHADER
    };

    ShaderObject(std::string const& source, Type type);
    ShaderObject(ShaderObject const&) = delete;
    ShaderObject& operator=(ShaderObject const&) = delete;
    ShaderObject(ShaderObject&& other) = default;
    ShaderObject& operator=(ShaderObject&&) = default;
    ~ShaderObject();

    Type type() const { return m_type; }
    bool valid() const { return m_valid; }
    unsigned id() const { return m_id; }

private:
    Type m_type;
    bool m_valid = false;
    unsigned m_id = 0;
};

struct AttributeMapping
{
    unsigned position;
    unsigned color;
    unsigned tex_coord;
    unsigned normal;
};

class Shader
{
public:
    ~Shader();
    explicit Shader(std::span<ShaderObject const> shader_objects, AttributeMapping);
    Shader(Shader const&) = delete;
    Shader& operator=(Shader const&) = delete;
    Shader(Shader&& other) = default;
    Shader& operator=(Shader&&) = default;

    void bind() const;
    static Shader const* current();

    bool valid() const { return m_valid; }
    unsigned id() const { return m_id; }
    AttributeMapping attribute_mapping() const { return m_attribute_mapping; }

private:
    bool m_valid = false;
    unsigned m_id = 0;
    AttributeMapping m_attribute_mapping;
};

class ShaderScope
{
public:
    ShaderScope(Shader const& shader) : m_shader(shader)
    { shader.bind(); }
    ~ShaderScope() { /*Not applicable since OpenGL 3.2*/ }

    int uniform_location(std::string const&);
    void set_uniform(std::string const&, Matrix4x4f);
    enum CurrentTextureTag { CurrentTexture };
    void set_uniform(std::string const&, CurrentTextureTag);
    void set_uniform(std::string const&, bool);

private:
    Shader const& m_shader;
};

namespace shaders
{

// Basic shader, with no lighting etc.
Shader& basic_330_core();

// Shade smooth lighting (single light source)
Shader& shade_smooth();

}

}
