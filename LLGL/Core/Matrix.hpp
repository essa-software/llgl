#pragma once

#include <cstddef>

#include "Vector4.hpp"

namespace llgl {

template<class T, size_t Size>
struct Matrix {
    T data[Size][Size] {};

    T& element(size_t row, size_t column) { return data[column][row]; }
    T const& element(size_t row, size_t column) const { return data[column][row]; }

    static constexpr Matrix identity()
    {
        Matrix output;
        for (size_t s = 0; s < Size; s++)
            output.data[s][s] = 1;
        return output;
    }
};

using Matrix4x4f = Matrix<float, 4>;

template<class T, size_t Size>
Matrix<T, Size>& operator*=(Matrix<T, Size>& left, Matrix<T, Size> const& right)
{
    // FIXME: I am naive
    Matrix<T, Size> result;
    for (size_t i = 0; i < Size; i++) {
        for (size_t j = 0; j < Size; j++) {
            T sum = 0;
            for (size_t k = 0; k < Size; k++)
                sum += left.data[i][k] * right.data[k][j];
            result.data[i][j] = sum;
        }
    }
    left = result;
    return left;
}

template<class T, size_t Size>
Matrix<T, Size> operator*(Matrix<T, Size> left, Matrix<T, Size> const& right)
{
    left *= right;
    return left;
}

template<class T>
inline Vector4<T> operator*(Matrix<T, 4> const& mat, Vector4<T> const& vec)
{
    Vector4<T> result;
    result.x = vec.x * mat.element(0, 0) + vec.y * mat.element(1, 0) + vec.z * mat.element(2, 0) + vec.w * mat.element(3, 0);
    result.y = vec.x * mat.element(0, 1) + vec.y * mat.element(1, 1) + vec.z * mat.element(2, 1) + vec.w * mat.element(3, 1);
    result.z = vec.x * mat.element(0, 2) + vec.y * mat.element(1, 2) + vec.z * mat.element(2, 2) + vec.w * mat.element(3, 2);
    result.w = vec.x * mat.element(0, 3) + vec.y * mat.element(1, 3) + vec.z * mat.element(2, 3) + vec.w * mat.element(3, 3);
    return result;
}

}
