#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace gamesmith { namespace maths {

		static inline float toRadians(float degrees)
		{
			return (float)(degrees * (M_PI / 180.0));
		}

		static inline float toDegrees(float radians)
		{
			return (float)(radians * (180.0f / M_PI));
		}

		template<typename t>
		static inline t clamp(t val, t min, t max)
		{

			if (val < min)
				val = min;
			else if (val > max)
				val = max;

			return val;
		}

		template<typename t>
		static inline t lerp(t current, t goal, float step)
		{
			return current + (goal - current) * step;
		}

} }