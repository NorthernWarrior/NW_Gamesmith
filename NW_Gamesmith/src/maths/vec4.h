#pragma once

#include <iostream>

namespace gamesmith { namespace maths {

	template <class T>
	struct vec4
	{
		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};

		vec4<T>()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}
		vec4<T>(const T& x, const T& y, const T& z, const T& w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		vec4<T>& add(const vec4<T>& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}
		vec4<T>& subtract(const vec4<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;

			return *this;
		}
		vec4<T>& multiply(const vec4<T>& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;

			return *this;
		}
		vec4<T>& divide(const vec4<T>& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;

			return *this;
		}

		friend vec4<T> operator+(vec4<T> left, const vec4<T>& right)
		{
			return left.add(right);
		}
		friend vec4<T> operator-(vec4<T> left, const vec4<T>& right)
		{
			return left.subtract(right);
		}
		friend vec4<T> operator*(vec4<T> left, const vec4<T>& right)
		{
			return left.multiply(right);
		}
		friend vec4<T> operator/(vec4<T> left, const vec4<T>& right)
		{
			return left.divide(right);
		}

		friend vec4<T> operator+(vec4<T> left, T value)
		{
			return vec4(left.x + value, left.y + value, left.z * value, left.w * value);
		}
		friend vec4<T> operator*(vec4<T> left, T value)
		{
			return vec4(left.x * value, left.y * value, left.z * value, left.w * value);
		}

		bool operator==(const vec4<T>& other)
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}
		bool operator!=(const vec4<T>& other)
		{
			return !(*this == other);
		}

		vec4<T>& operator+=(const vec4<T>& other)
		{
			return add(other);
		}
		vec4<T>& operator-=(const vec4<T>& other)
		{
			return subtract(other);
		}
		vec4<T>& operator*=(const vec4<T>& other)
		{
			return multiply(other);
		}
		vec4<T>& operator/=(const vec4<T>& other)
		{
			return divide(other);
		}

		T magnitude() const
		{
			return sqrt(x * x + y * y + z * z + w * w);
		}
		vec4<T> normalise() const
		{
			T length = magnitude();
			return vec4(x / length, y / length, z / length, w / length);
		}
		T distance(const vec4<T>& other) const
		{
			T a = x - other.x;
			T b = y - other.y;
			T c = z - other.z;
			T c = w - other.w;
			return sqrt(a * a + b * b + c * c + w * w);
		}
		T dot(const vec4<T>& other) const
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		friend std::ostream& operator<<(std::ostream& stream, const vec4<T>& vector)
		{
			stream << "[" << vector.x << " : " << vector.y << " : " << vector.z << " : " << vector.w << "]";
			return stream;
		}
	};

	typedef vec4<float> vec4f;
	typedef vec4<int> vec4i;

} }
