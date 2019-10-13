#pragma once

#include <cstdint>
#include <cstdio>

#define _USE_MATH_DEFINES
#include "math.h"
#include <cmath>
#include <algorithm>
#include <cassert>

#if !defined(_XBOX) && (_MSC_VER >= 1900)
#define HLSLPP_HAS_CHRONO
#endif

#if defined(HLSLPP_HAS_CHRONO)
#include <chrono>
#endif

// Force hlslpp and std to live in the same namespace to account for name clashes and ambiguities
using namespace std;
using namespace hlslpp;

// Temporary until we properly do it multiplatform
#if defined(_MSC_VER) && defined(_WIN64)
extern "C" unsigned __int64 __rdtsc();
#pragma intrinsic(__rdtsc)
inline uint64_t ClockCycleCount()
{
	return __rdtsc();
}
#else
inline uint64_t ClockCycleCount()
{
	return 0;
}
#endif

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

	class Timer
	{
		private:

		#if defined(HLSLPP_HAS_CHRONO)
		std::chrono::high_resolution_clock::time_point m_startTime;
		std::chrono::high_resolution_clock::time_point m_endTime;
		#endif

		public:
		void Start()
		{
			#if defined(HLSLPP_HAS_CHRONO)
			m_startTime = std::chrono::high_resolution_clock::now();
			#endif
		}

		double Get()
		{
			#if defined(HLSLPP_HAS_CHRONO)
			m_endTime = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime).count() / 1e9f;
			#else
			return 0.0f;
			#endif
		}
	};

	void eq(float a, float b, float tolerance = 0.0f);

	void eq(const float2& v, float x, float y, float tolerance = 0.0f);

	void eq(const float3& v, float x, float y, float z, float tolerance = 0.0f);

	void eq(const float4& v, float x, float y, float z, float w, float tolerance = 0.0f);

#if defined(HLSLPP_FLOAT8)

	void eq(const float8& v, float x, float y, float z, float w, float a, float b, float c, float d, float tolerance = 0.0f);

#endif

	void eq(double a, double b, double tolerance = 0.0);

#if defined(HLSLPP_DOUBLE)

	void eq(const double2& v, double x, double y, double tolerance = 0.0);

	void eq(const double3& v, double x, double y, double z, double tolerance = 0.0);

	void eq(const double4& v, double x, double y, double z, double w, double tolerance = 0.0);

#endif

	void eq(const float1x1& m, float m00, float tolerance = 0.0f);

	void eq(const float1x2& m, float m00, float m01, float tolerance = 0.0f);

	void eq(const float1x3& m, float m00, float m01, float m02, float tolerance = 0.0f);

	void eq(const float1x4& m, float m00, float m01, float m02, float m03, float tolerance = 0.0f);

	void eq(const float2x1& m, float m00, float m01, float tolerance = 0.0f);

	void eq(const float2x2& m,
		float m00, float m01,
		float m10, float m11, float tolerance = 0.0f);

	void eq(const float2x3& m,
		float m00, float m01, float m02,
		float m10, float m11, float m12, float tolerance = 0.0f);

	void eq(const float2x4& m,
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13, float tolerance = 0.0f);

	void eq(const float3x1& m, float m00, float m01, float m02, float tolerance = 0.0f);

	void eq(const float3x2& m, 
		float m00, float m01, 
		float m10, float m11,
		float m20, float m21, float tolerance = 0.0f);

	void eq(const float3x3& m,
		float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22, float tolerance = 0.0f);

	void eq(const float3x4& m,
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23, 
		float tolerance = 0.0f);

	void eq(const float4x1& m, float m00, float m01, float m02, float m03, float tolerance = 0.0f);

	void eq(const float4x2& m, 
		float m00, float m01,
		float m10, float m11,
		float m20, float m21,
		float m30, float m31, float tolerance = 0.0f);

	void eq(const float4x3& m,
		float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22,
		float m30, float m31, float m32, 
		float tolerance = 0.0f);

	void eq(const float4x4& m,
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33,
		float tolerance = 0.0f);

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

	float lerpf(float x, float y, float a);

	typedef float4(*Vec4Func)(const float4&);
	typedef float(*ScalarFunc)(float);

	void maxErrorExhaustive(Vec4Func vectorFunction, ScalarFunc scalarFunction, const char* funcName, float rangeStart, float rangeEnd);

	template<typename T>
	struct TimingStats
	{
		uint64_t totalCycles;
		double cyclesPerLoop;
		double totalTime;
		double timePerLoop;

		T result;
	};

	template<typename T, uint32_t iterations, typename Fn>
	TimingStats<T> benchmark(const char* functionName, Fn fn)
	{
		TimingStats<T> stats;
		Timer timer;
		uint64_t startCycles = ClockCycleCount();

		T result;
		timer.Start();

		for (uint32_t i = 0; i < iterations; ++i)
		{
			result = fn();
		}

		double elapsedTime = timer.Get();
		uint64_t endCycles = ClockCycleCount();

		stats.totalCycles = endCycles - startCycles;
		stats.result = result;
		stats.cyclesPerLoop = (double)stats.totalCycles / (double)iterations;
		stats.totalTime = elapsedTime;
		stats.timePerLoop = (double)stats.totalTime / (double)iterations;

		printf("%20s: Cycles: %10.6f Elapsed: %3.6f\n", functionName, stats.cyclesPerLoop, stats.totalTime);

		return stats;
	}
}