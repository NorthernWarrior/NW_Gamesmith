#pragma once

namespace nw { namespace math {

struct Vector3
{
	float x, y, z;

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

} }