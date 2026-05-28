#pragma once

#if defined(_MSC_VER)
extern "C"
{
	double __cdecl sqrt(double _X);
	double __cdecl sin(double _X);
	double __cdecl cos(double _X);
}
#endif

namespace hlslpp
{
	// Helpers for the scalar functions
	namespace detail
	{
		hlslpp_inline float trunc_float(float f)
		{
			return (float)(int)f;
		}

		hlslpp_inline float floor_float(float f)
		{
			float trunc = (float)(int)f;
			return trunc > f ? trunc - 1.0f : trunc;
		}

		hlslpp_inline float ceil_float(float f)
		{
			float trunc = (float)(int)f;
			return trunc < f ? trunc + 1.0f : trunc;
		}

		hlslpp_inline float round_float(float f)
		{
			float trunc = (float)(int)f;
			float frac = f - trunc;
			float abs_frac = frac >= 0.0f ? frac : -frac;
			return abs_frac <= 0.5f ? trunc : f >= 0.0f ? trunc + 1.0f : trunc - 1.0f;
		}

		hlslpp_inline float sqrt_float(float x)
		{
	#if defined(__clang__) || defined(__GNUC__)
			return __builtin_sqrtf(x);
	#else
			return (float)sqrt(x);
	#endif
		}

		hlslpp_inline float sin_float(float x)
		{
	#if defined(__clang__) || defined(__GNUC__)
			return __builtin_sinf(x);
	#else
			return (float)sin(x);
	#endif
		}

		hlslpp_inline float cos_float(float x)
		{
	#if defined(__clang__) || defined(__GNUC__)
			return __builtin_cosf(x);
	#else
			return (float)cos(x);
	#endif
		}
	};
}