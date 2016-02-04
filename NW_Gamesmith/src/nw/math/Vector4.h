#pragma once

namespace nw { namespace math {

struct Vector4
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
	union
	{
		float w; float a;
	};

	Vector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

#pragma region Stream

	friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
	{
		stream << "[" << vector.x << " : " << vector.y << " : " << vector.z << " : " << vector.w << "]";
		return stream;
	}

#pragma endregion

};

} }