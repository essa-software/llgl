#include "Transform.hpp"

namespace llgl
{

void Transform::move(Vector3f vector)
{
    Matrix4x4f translation_matrix { { { 1, 0, 0, vector.x },
        { 0, 1, 0, vector.y },
        { 0, 0, 1, vector.z },
        { 0, 0, 0, 1 } } };
    m_matrix *= translation_matrix;
}

void Transform::rotate_x(float angle)
{
    Matrix4x4f rotation_matrix { { { 1, 0, 0, 0 },
        { 0, std::cos(angle), -std::sin(angle), 0 },
        { 0, std::sin(angle), std::cos(angle), 0 },
        { 0, 0, 0, 1 } } };
    m_matrix *= rotation_matrix;
}

void Transform::rotate_y(float angle)
{
    Matrix4x4f rotation_matrix { { { std::cos(angle), 0, std::sin(angle), 0 },
        { 0, 1, 0, 0 },
        { -std::sin(angle), 0, std::cos(angle), 0 },
        { 0, 0, 0, 1 } } };
    m_matrix *= rotation_matrix;
}

}
