#pragma once

#include <nw/math/Vector2.h>

#include <iostream>

namespace nw { namespace math {

struct Vector3
{
	union
	{
		float x; float r;
	};
	union
	{
		float y; float g;
	};
	union
	{
		float z; float b;
	};

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3(const Vector2& vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		this->z = 0;
	}

#pragma region Additions, Subtractions, ...

	inline Vector3& Subtract(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	inline Vector3& Multiply(const Vector3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

#pragma endregion

#pragma region Operators

	friend Vector3 operator-(Vector3 left, const Vector3& right)
	{
		return left.Subtract(right);
	}
	Vector3 operator-()
	{
		return (*this * (-1));
	}

	friend Vector3 operator*(Vector3 left, const Vector3 right)
	{
		return left.Multiply(right);
	}
	friend Vector3 operator*(Vector3 left, float value)
	{
		return left.Multiply(Vector3(value, value, value));
	}

#pragma endregion

#pragma region Stream

	friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector)
	{
		stream << "[" << vector.x << " : " << vector.y << " : " << vector.z << "]";
		return stream;
	}

#pragma endregion

};

} }