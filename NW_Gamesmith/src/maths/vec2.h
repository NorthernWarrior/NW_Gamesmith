#pragma once

#include <iostream>

namespace gamesmith { namespace maths {

	template <class T>
	struct vec2
	{
		T x, y;

		vec2<T>()
		{
			x = 0;
			y = 0;
		}
		vec2<T>(const T& x, const T& y)
		{
			this->x = x;
			this->y = y;
		}

		vec2<T>& add(const vec2<T>& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}
		vec2<T>& subtract(const vec2<T>& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}
		vec2<T>& multiply(const vec2<T>& other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}
		vec2<T>& divide(const vec2<T>& other)
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}

		friend vec2<T> operator+(vec2<T> left, const vec2<T>& right)
		{
			return left.add(right);
		}
		friend vec2<T> operator-(vec2<T> left, const vec2<T>& right)
		{
			return left.subtract(right);
		}
		friend vec2<T> operator*(vec2<T> left, const vec2<T>& right)
		{
			return left.multiply(right);
		}
		friend vec2<T> operator/(vec2<T> left, const vec2<T>& right)
		{
			return left.divide(right);
		}

		friend vec2<T> operator+(vec2<T> left, T value)
		{
			return vec2(left.x + value, left.y + value);
		}
		friend vec2<T> operator*(vec2<T> left, T value)
		{
			return vec2(left.x * value, left.y * value);
		}
		friend vec2<T> operator/(vec2<T> left, T value)
		{
			return vec2(left.x / value, left.y / value);
		}

		bool operator==(const vec2<T>& other)
		{
			return x == other.x && y == other.y;
		}
		bool operator!=(const vec2<T>& other)
		{
			return !(*this == other);
		}

		vec2<T>& operator+=(const vec2<T>& other)
		{
			return add(other);
		}
		vec2<T>& operator-=(const vec2<T>& other)
		{
			return subtract(other);
		}
		vec2<T>& operator*=(const vec2<T>& other)
		{
			return multiply(other);
		}
		vec2<T>& operator/=(const vec2<T>& other)
		{
			return divide(other);
		}

		T magnitude() const
		{
			return sqrt(x * x + y * y);
		}
		vec2<T> normalise() const
		{
			T length = magnitude();
			return vec2(x / length, y / length);
		}
		T distance(const vec2<T>& other) const
		{
			T a = x - other.x;
			T b = y - other.y;
			return sqrt(a * a + b * b);
		}
		T dot(const vec2<T>& other) const
		{
			return x * other.x + y * other.y;
		}

		friend std::ostream& operator<<(std::ostream& stream, const vec2<T>& vector)
		{
			stream << "[" << vector.x << " : " << vector.y << "]";
			return stream;
		}
	};

	typedef vec2<float> vec2f;
	typedef vec2<int> vec2i;

} }