#pragma once

template<typename T>
struct Vector2
{
    T x{};
    T y{};
};

using Vector2i = Vector2<int8_t>;

template<typename T>
constexpr Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
constexpr Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
constexpr bool operator==(const Vector2<T>& rhs, const Vector2<T>& lhs);

template<typename T>
constexpr bool operator!=(const Vector2<T>& rhs, const Vector2<T>& lhs);

#include "Vector2.inl"
