#include "math.h"
#include <math.h>
#include <algorithm>

namespace Math
{
	float Clamp(float v, float low, float high)
	{
		return std::min<float>(high, std::max<float>(v, low));
	}

	float Clamp01(float v)
	{
		return std::min<float>(1.0f, std::max<float>(v, 0.0f));
	}

	float GetRandom01()
	{
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

	float GetRandomRange(float min, float max)
	{
		return min + (max - min) * GetRandom01();
	}

	float Lerp(float v1, float v2, float t)
	{
		t = Clamp01(t);
		return (v1 * (1.0f - t) + v2 * t);
	}

	float LerpUnclamped(float v1, float v2, float t)
	{
		return (v1 * (1.0f - t) + v2 * t);
	}
	
	bool IsZero(float value)
	{
		return (::fabs(value) < std::numeric_limits<float>::epsilon());
	}
}
