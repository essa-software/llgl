#include "Transform.hpp"

namespace llgl
{

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

}
