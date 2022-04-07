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

    void move(Vector3f vector);

    // FIXME: This assumes rotation by Y axis. Allow another axises.
    // (Angle is in radians)
    void rotate(float angle);

    Matrix4x4f matrix() const { return m_matrix; }

private:
    Matrix4x4f m_matrix = Matrix4x4f::identity();
};

}
