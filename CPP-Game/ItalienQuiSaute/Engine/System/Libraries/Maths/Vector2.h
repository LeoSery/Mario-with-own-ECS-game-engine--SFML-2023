#pragma once

#include <utility>

template <typename T>
class Vector2 final
{
public:
	constexpr Vector2() = default;

	constexpr Vector2(T x, T y) noexcept
		: x(std::move(x)), y(std::move(y)) {}

	~Vector2() = default;

	constexpr Vector2(const Vector2& other) = default;
	constexpr Vector2(Vector2&& other) noexcept = default;
	constexpr Vector2& operator=(const Vector2& other) = default;
	constexpr Vector2& operator=(Vector2&& other) noexcept = default;

	// Comparison operators
	constexpr auto operator<=>(const Vector2& other) const noexcept;

	// Arithmetic operators
	constexpr Vector2 operator+(const Vector2& other) const noexcept;
	constexpr Vector2 operator-(const Vector2& other) const noexcept;
	constexpr Vector2 operator*(const Vector2& other) const noexcept;
	constexpr Vector2 operator/(const Vector2& other) const noexcept;
	constexpr Vector2 operator*(const T& value) const noexcept;
	constexpr Vector2 operator/(const T& value) const noexcept;

	// Compound assignment operators
	constexpr Vector2& operator+=(const Vector2& other) noexcept;
	constexpr Vector2& operator-=(const Vector2& other) noexcept;
	constexpr Vector2& operator*=(const Vector2& other) noexcept;
	constexpr Vector2& operator/=(const T& value) noexcept;

	// Unary operators
	constexpr Vector2 operator-() const noexcept;
	constexpr Vector2 operator+() const noexcept;

	// Misc
	friend constexpr void swap(Vector2& lhs, Vector2& rhs) noexcept
	{
		std::swap(lhs.x, rhs.x);
		std::swap(lhs.y, rhs.y);
	}

public:
	T x, y;
};

template <typename T>
constexpr auto Vector2<T>::operator<=>(const Vector2& other) const noexcept
{
	return x <=> other.x && y <=> other.y;
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator+(const Vector2& other) const noexcept
{
	return Vector2(x + other.x, y + other.y);
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator-(const Vector2& other) const noexcept
{
	return Vector2(x - other.x, y - other.y);
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator*(const Vector2& other) const noexcept
{
	return Vector2(x * other.x, y * other.y);
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator/(const Vector2& other) const noexcept
{
	return Vector2(x / other.x, y / other.y);
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator*(const T& value) const noexcept
{
	return Vector2(x * value, y * value);
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator/(const T& value) const noexcept
{
	return Vector2(x / value, y / value);
}

template <typename T>
constexpr Vector2<T>& Vector2<T>::operator+=(const Vector2& other) noexcept
{
	x += other.x;
	y += other.y;
	return *this;
}

template <typename T>
constexpr Vector2<T>& Vector2<T>::operator-=(const Vector2& other) noexcept
{
	x -= other.x;
	y -= other.y;
	return *this;
}

template <typename T>
constexpr Vector2<T>& Vector2<T>::operator*=(const Vector2& other) noexcept
{
	x *= other.x;
	y *= other.y;
	return *this;
}

template <typename T>
constexpr Vector2<T>& Vector2<T>::operator/=(const T& value) noexcept
{
	x /= value;
	y /= value;
	return *this;
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator-() const noexcept
{
	return Vector2(-x, -y);
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator+() const noexcept
{
	return *this;
}
