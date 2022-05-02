#pragma once

#include <cstddef>

namespace llgl
{

template<class T, size_t Size>
struct Matrix
{
    T data[Size][Size] {};

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
    for (size_t i = 0; i < Size; i++)
    {
        for (size_t j = 0; j < Size; j++)
        {
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

}
