#include "Transform.hpp"
#include <LLGL/Core/Matrix.hpp>

namespace llgl {

Transform Transform::translate(Vector3f vector) const
{
    Matrix4x4f translation_matrix { { { 1, 0, 0, vector.x },
        { 0, 1, 0, vector.y },
        { 0, 0, 1, vector.z },
        { 0, 0, 0, 1 } } };
    return Transform { m_matrix * translation_matrix };
}

Transform Transform::rotate_x(float angle) const
{
    Matrix4x4f rotation_matrix { { { 1, 0, 0, 0 },
        { 0, std::cos(angle), -std::sin(angle), 0 },
        { 0, std::sin(angle), std::cos(angle), 0 },
        { 0, 0, 0, 1 } } };
    return Transform { m_matrix * rotation_matrix };
}

Transform Transform::rotate_y(float angle) const
{
    Matrix4x4f rotation_matrix { { { std::cos(angle), 0, std::sin(angle), 0 },
        { 0, 1, 0, 0 },
        { -std::sin(angle), 0, std::cos(angle), 0 },
        { 0, 0, 0, 1 } } };
    return Transform { m_matrix * rotation_matrix };
}

Transform Transform::scale(float scale) const
{
    Matrix4x4f scale_matrix {
        { { scale, 0, 0, 0 },
            { 0, scale, 0, 0 },
            { 0, 0, scale, 0 },
            { 0, 0, 0, 1 } }
    };
    return Transform { m_matrix * scale_matrix };
}

Vector3f Transform::transform_point(Vector3f const& vector) const
{
    if (m_matrix == Matrix4x4f::identity())
        return vector;
    auto result = m_matrix * Vector4f { vector };
    result /= result.w;
    return Vector3f { result };
}

}
