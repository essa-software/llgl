#pragma once

#include <EssaUtil/Matrix.hpp>
#include <LLGL/Core/Vector3.hpp>

namespace llgl {

class Transform {
public:
    explicit Transform(Util::Matrix4x4f matrix = Util::Matrix4x4f::identity())
        : m_matrix(matrix)
    {
    }

    [[nodiscard]] Transform translate(Vector3f vector) const;

    // Angle is in radians.
    [[nodiscard]] Transform rotate_x(float angle) const;
    [[nodiscard]] Transform rotate_y(float angle) const;

    [[nodiscard]] Transform scale(float) const;

    Util::Matrix4x4f matrix() const { return m_matrix; }

    Vector3f transform_point(Vector3f const&) const;

private:
    Util::Matrix4x4f m_matrix = Util::Matrix4x4f::identity();
};

}
