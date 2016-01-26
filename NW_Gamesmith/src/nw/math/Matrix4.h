#pragma once

#include "Vector4.h"

namespace nw { namespace math {

struct Matrix4
{
	union
	{
		float elements[4 * 4];
		Vector4 columns[4];
	};

	Matrix4()
	{
		memset(elements, 0, 4 * 4 * sizeof(float));
	}
	Matrix4(float diagonal)
	{
		memset(elements, 0, 4 * 4 * sizeof(float));

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	static Matrix4 Identity()
	{
		return Matrix4(1.0f);
	}

	static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix4 result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);

		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}
};

} }