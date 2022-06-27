#pragma once

#include <LLGL/Core/Matrix.hpp>
#include <LLGL/Core/Vector3.hpp>

namespace llgl
{

class Transform
{
public:
    explicit Transform(Matrix4x4f matrix = Matrix4x4f::identity())
    : m_matrix(matrix) {}

    [[nodiscard]] Transform translate(Vector3f vector) const;

    // Angle is in radians.
    [[nodiscard]] Transform rotate_x(float angle) const;
    [[nodiscard]] Transform rotate_y(float angle) const;

    [[nodiscard]] Transform scale(float) const;

    Matrix4x4f matrix() const { return m_matrix; }

private:
    Matrix4x4f m_matrix = Matrix4x4f::identity();
};

}
