#pragma once

#include <cstdint>
#include <cstdio>

#define _USE_MATH_DEFINES
#include "math.h"
#include <cmath>
#include <algorithm>
#include <cassert>

// Force hlslpp and std to live in the same namespace to account for name clashes and ambiguities
using namespace std;
using namespace hlslpp;

namespace hlslpp
{
	struct float1;
	struct float2;
	struct float3;
	struct float4;

	struct float2x2;
	struct float3x3;
	struct float4x4;

	struct int1;
	struct int2;
	struct int3;
	struct int4;

	struct double1;
	struct double2;
	struct double3;
	struct double4;
}

namespace hlslpp_unit
{
	using namespace hlslpp;

	// Copied from https://randomascii.wordpress.com/2014/01/27/theres-only-four-billion-floatsso-test-them-all/
	union float_t
	{
		float_t(float num = 0.0f) : f(num) {}
		// Portable extraction of components.
		bool negative() const { return (i >> 31) != 0; }
		int32_t mantissa() const { return i & ((1 << 23) - 1); }
		int32_t exponent() const { return (i >> 23) & 0xFF; }

		int32_t i;
		float f;

		struct
		{
			uint32_t mantissa : 23;
			uint32_t exponent : 8;
			uint32_t sign : 1;
		} parts;

	};

	void eq(float a, float b, float tolerance = 0.0f);

	void eq(const float2& v, float x, float y, float tolerance = 0.0f);

	void eq(const float3& v, float x, float y, float z, float tolerance = 0.0f);

	void eq(const float4& v, float x, float y, float z, float w, float tolerance = 0.0f);

	void eq(double a, double b, double tolerance = 0.0);

#if defined(HLSLPP_FLOAT64)

	void eq(const double2& v, double x, double y, double tolerance = 0.0);

	void eq(const double3& v, double x, double y, double z, double tolerance = 0.0);

	void eq(const double4& v, double x, double y, double z, double w, double tolerance = 0.0);

#endif

	void eq(const float2x2& v,
		float m00, float m01,
		float m10, float m11, float tolerance = 0.0f);

	void eq(const float3x3& v,
		float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22, float tolerance = 0.0f);

	void eq(const float4x4& v,
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33, float tolerance = 0.0f);

	float div(float a, float b);

	double div(double a, double b);

	void eq(bool a, bool c);

	void eq(float a, bool c);

	void eq(const float2& v, bool x, bool y);

	void eq(const float3& v, bool x, bool y, bool z);

	void eq(const float4& v, bool x, bool y, bool z, bool w);

	void eq(int32_t a, int32_t b);

	void eq(const int2& v, int32_t x, int32_t y);

	void eq(const int3& v, int32_t x, int32_t y, int32_t z);

	void eq(const int4& v, int32_t x, int32_t y, int32_t z, int32_t w);

	int32_t shift_left(int32_t a, int32_t b);

	int32_t shift_right(int32_t a, int32_t b);

	const float PI = 3.14159265358979f;

	float frac(float x);

	typedef float4(*Vec4Func)(const float4&);
	typedef float(*ScalarFunc)(float);

	void maxErrorExhaustive(Vec4Func vectorFunction, ScalarFunc scalarFunction, const char* funcName, float rangeStart, float rangeEnd);
}