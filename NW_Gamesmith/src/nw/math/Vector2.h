#pragma once

#include <iostream>

namespace nw { namespace math {

struct Vector2
{
	float x, y;

	Vector2() : x(0), y(0) {}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	static inline Vector2 Up()
	{
		return Vector2(0.0f, 1.0f);
	}
	static inline Vector2 Down()
	{
		return Vector2(0.0f, -1.0f);
	}
	static inline Vector2 Left()
	{
		return Vector2(-1.0f, 0.0f);
	}
	static inline Vector2 Right()
	{
		return Vector2(1.0f, 0.0f);
	}

	static inline Vector2 Zero()
	{
		return Vector2(0, 0);
	}

#pragma region Additions, Subtractions, ...

	inline Vector2& Add(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	inline Vector2& Subtract(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	inline Vector2& Multiply(const Vector2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	inline Vector2& Divide(const Vector2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

#pragma endregion

#pragma region Operators

	friend Vector2 operator+(Vector2 left, const Vector2& right)
	{
		return left.Add(right);
	}
	friend Vector2 operator+(Vector2 left, float value)
	{
		return left.Add(Vector2(value, value));
	}
	const Vector2& operator+=(const Vector2& right)
	{
		return Add(right);
	}
	const Vector2& operator+=(float value)
	{
		return Add(Vector2(value, value));
	}

	friend Vector2 operator-(Vector2 left, const Vector2& right)
	{
		return left.Subtract(right);
	}
	friend Vector2 operator-(Vector2 left, float value)
	{
		return left.Subtract(Vector2(value, value));
	}

	friend Vector2 operator*(Vector2 left, const Vector2& right)
	{
		return left.Multiply(right);
	}
	friend Vector2 operator*(Vector2 left, float value)
	{
		return left.Multiply(Vector2(value, value));
	}

	friend Vector2 operator/(Vector2 left, const Vector2& right)
	{
		return left.Divide(right);
	}
	friend Vector2 operator/(Vector2 left, float value)
	{
		return left.Divide(Vector2(value, value));
	}

	friend bool operator==(Vector2 left, const Vector2& right)
	{
		return (left.x == right.x && left.y == right.y);
	}
	friend bool operator!=(Vector2 left, const Vector2& right)
	{
		return (!(left == right));
	}

#pragma endregion

#pragma region Stream

	friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
	{
		stream << "[" << vector.x << " : " << vector.y << "]";
		return stream;
	}

#pragma endregion

};

} }