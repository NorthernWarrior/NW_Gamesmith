#pragma once

#include <iostream>

namespace gamesmith { namespace maths {

	template <class T>
	struct vec3
	{
		union
		{
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		vec3<T>()
		{
			x = 0;
			y = 0;
			z = 0;
		}
		vec3<T>(const T& x, const T& y, const T& z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		vec3<T>(const vec2<T>& other, const T& z = 0)
		{
			this->x = other.x;
			this->y = other.y;
			this->z = z;
		}

		vec3<T>& add(const vec3<T>& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}
		vec3<T>& subtract(const vec3<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}
		vec3<T>& multiply(const vec3<T>& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}
		vec3<T>& divide(const vec3<T>& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;

			return *this;
		}

		friend vec3<T> operator+(vec3<T> left, const vec3<T>& right)
		{
			return left.add(right);
		}
		friend vec3<T> operator-(vec3<T> left, const vec3<T>& right)
		{
			return left.subtract(right);
		}
		friend vec3<T> operator*(vec3<T> left, const vec3<T>& right)
		{
			return left.multiply(right);
		}
		friend vec3<T> operator/(vec3<T> left, const vec3<T>& right)
		{
			return left.divide(right);
		}

		friend vec3<T> operator+(vec3<T> left, T value)
		{
			return vec3(left.x + value, left.y + value, left.z * value);
		}
		friend vec3<T> operator*(vec3<T> left, T value)
		{
			return vec3(left.x * value, left.y * value, left.z * value);
		}

		bool operator==(const vec3<T>& other)
		{
			return x == other.x && y == other.y && z == other.z;
		}
		bool operator!=(const vec3<T>& other)
		{
			return !(*this == other);
		}

		vec3<T>& operator+=(const vec3<T>& other)
		{
			return add(other);
		}
		vec3<T>& operator-=(const vec3<T>& other)
		{
			return subtract(other);
		}
		vec3<T>& operator*=(const vec3<T>& other)
		{
			return multiply(other);
		}
		vec3<T>& operator/=(const vec3<T>& other)
		{
			return divide(other);
		}

		T magnitude() const
		{
			return sqrt(x * x + y * y + z * z);
		}
		vec3<T> normalise() const
		{
			T length = magnitude();
			return vec3(x / length, y / length, z / length);
		}
		T distance(const vec3<T>& other) const
		{
			T a = x - other.x;
			T b = y - other.y;
			T c = z - other.z;
			return sqrt(a * a + b * b + c * c);
		}
		T dot(const vec3<T>& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		friend std::ostream& operator<<(std::ostream& stream, const vec3<T>& vector)
		{
			stream << "[" << vector.x << " : " << vector.y << " : " << vector.z << "]";
			return stream;
		}
	};

	typedef vec3<float> vec3f;
	typedef vec3<int> vec3i;

} }
