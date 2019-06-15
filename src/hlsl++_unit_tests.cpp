#include "hlsl++.h"

// Hacky but needs FLOAT64
#include "hlsl++_unit_tests.h"

#if !defined(_XBOX) && (_MSC_VER >= 1900)
#define HLSLPP_HAS_CHRONO
#endif

#if defined(HLSLPP_HAS_CHRONO)
#include <chrono>
#endif

const float deg2rad = 3.14159265f / 180.0f;

namespace hlslpp_unit
{
	using namespace hlslpp;

	float div(float a, float b)
	{
		return a / b;
	}

	double div(double a, double b)
	{
		return a / b;
	}

	void eq(float a, float b, float tolerance /*= 0.0f*/)
	{
		bool withinTolerance = abs(a - b) <= tolerance;
		assert(withinTolerance);
	}

	void eq(const float2& v, float x, float y, float tolerance /*= 0.0f*/)
	{
		eq(v.x, x, tolerance);
		eq(v.y, y, tolerance);
	}

	void eq(const float3& v, float x, float y, float z, float tolerance /*= 0.0f*/)
	{
		eq(v.x, x, tolerance);
		eq(v.y, y, tolerance);
		eq(v.z, z, tolerance);
	}

	void eq(const float4& v, float x, float y, float z, float w, float tolerance /*= 0.0f*/)
	{
		eq(v.x, x, tolerance);
		eq(v.y, y, tolerance);
		eq(v.z, z, tolerance);
		eq(v.w, w, tolerance);
	}

	void eq(double a, double b, double tolerance /*= 0.0*/)
	{
		bool withinTolerance = abs(a - b) <= tolerance;
		assert(withinTolerance);
	}

#if defined(HLSLPP_FLOAT64)

	void eq(const double2& v, double x, double y, double tolerance /*= 0.0*/)
	{
		eq((double)v.x, x, tolerance);
		eq((double)v.y, y, tolerance);
	}

	void eq(const double3& v, double x, double y, double z, double tolerance /*= 0.0*/)
	{
		eq((double)v.x, x, tolerance);
		eq((double)v.y, y, tolerance);
		eq((double)v.z, z, tolerance);
	}

	void eq(const double4& v, double x, double y, double z, double w, double tolerance /*= 0.0*/)
	{
		eq((double)v.x, x, tolerance);
		eq((double)v.y, y, tolerance);
		eq((double)v.z, z, tolerance);
		eq((double)v.w, w, tolerance);
	}

#endif

	void eq(const float2x2& v, float m00, float m01, float m10, float m11, float tolerance /*= 0.0f*/)
	{
		eq(v.f32[0], m00, tolerance);
		eq(v.f32[1], m01, tolerance);

		eq(v.f32[2], m10, tolerance);
		eq(v.f32[3], m11, tolerance);
	}

	void eq(const float3x3& v, float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22, float tolerance /*= 0.0f*/)
	{
		eq(v._m00, m00, tolerance);
		eq(v._m01, m01, tolerance);
		eq(v._m02, m02, tolerance);

		eq(v._m10, m10, tolerance);
		eq(v._m11, m11, tolerance);
		eq(v._m12, m12, tolerance);

		eq(v._m20, m20, tolerance);
		eq(v._m21, m21, tolerance);
		eq(v._m22, m22, tolerance);
	}

	void eq(const float4x4& v, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33, float tolerance /*= 0.0f*/)
	{
		eq(v._m00, m00, tolerance);
		eq(v._m01, m01, tolerance);
		eq(v._m02, m02, tolerance);
		eq(v._m03, m03, tolerance);

		eq(v._m10, m10, tolerance);
		eq(v._m11, m11, tolerance);
		eq(v._m12, m12, tolerance);
		eq(v._m13, m13, tolerance);

		eq(v._m20, m20, tolerance);
		eq(v._m21, m21, tolerance);
		eq(v._m22, m22, tolerance);
		eq(v._m23, m23, tolerance);

		eq(v._m30, m30, tolerance);
		eq(v._m31, m31, tolerance);
		eq(v._m32, m32, tolerance);
		eq(v._m33, m33, tolerance);
	}

	void eq(float a, bool c)
	{
		bool equals = (a != 0.0f ? true : false) == c;
		assert(equals);
	}

	void eq(const float2& v, bool x, bool y)
	{
		eq(v.x, x);
		eq(v.y, y);
	}

	void eq(const float3& v, bool x, bool y, bool z)
	{
		eq(v.x, x);
		eq(v.y, y);
		eq(v.z, z);
	}

	void eq(const float4& v, bool x, bool y, bool z, bool w)
	{
		eq(v.x, x);
		eq(v.y, y);
		eq(v.z, z);
		eq(v.w, w);
	}

	void eq(int32_t a, int32_t b)
	{
		assert(a == b);
	}

	void eq(const int2& v, int32_t x, int32_t y)
	{
		eq(v.x, x);
		eq(v.y, y);
	}

	void eq(const int3& v, int32_t x, int32_t y, int32_t z)
	{
		eq(v.x, x);
		eq(v.y, y);
		eq(v.z, z);
	}

	void eq(const int4& v, int32_t x, int32_t y, int32_t z, int32_t w)
	{
		eq(v.x, x);
		eq(v.y, y);
		eq(v.z, z);
		eq(v.w, w);
	}

	void eq(bool a, bool c)
	{
		bool equals = a == c;
		assert(equals);
	}

	int32_t shift_left(int32_t a, int32_t b)
	{
		return a << b;
	}

	int32_t shift_right(int32_t a, int32_t b)
	{
		return a >> b;
	}

	float frac(float x)
	{
		float fracPart = x - std::floor(x);
		return fracPart;
	}

	void maxErrorExhaustive(Vec4Func vectorFunction, ScalarFunc scalarFunction, const char* funcName, float rangeStart, float rangeEnd)
	{
		struct ErrorInfo
		{
			float maxError;
			float input;
			float refValue;
			float testValue;
		};

		ErrorInfo absErrorInfo = {};
		ErrorInfo relativeErrorInfo = {};

		float_t rangeStart_t = rangeStart;
		float_t rangeEnd_t = rangeEnd;

		// Negative values

		int32_t negRangeStart = rangeStart_t.i >= 0 ? int32_t(0x80000000) : rangeStart_t.i;

		for (int64_t i = negRangeStart; i > int32_t(0x80000000); --i)
		{
			float_t input;
			input.i = (int32_t)i;

			float_t testValue = (float)vectorFunction(float4(input.f, input.f, input.f, input.f)).x;
			float_t refValue = scalarFunction(input.f);

			float absError = abs(testValue.f - refValue.f);
			float relativeError = abs((testValue.f - refValue.f) / testValue.f);

			if (absError > absErrorInfo.maxError)
			{
				absErrorInfo.maxError = absError;
				absErrorInfo.input = input.f;
				absErrorInfo.refValue = refValue.f;
				absErrorInfo.testValue = testValue.f;
			}

			if (relativeError > relativeErrorInfo.maxError)
			{
				relativeErrorInfo.maxError = relativeError;
				relativeErrorInfo.input = input.f;
				relativeErrorInfo.refValue = refValue.f;
				relativeErrorInfo.testValue = testValue.f;
			}
		}

		// Positive values

		int32_t posRangeStart = std::max<int32_t>(0, rangeStart_t.i);
		int32_t posRangeEnd = std::max<int32_t>(0, rangeEnd_t.i);

		for (uint64_t i = posRangeStart; i < posRangeEnd; ++i)
		{
			float_t input;
			input.i = (int32_t)i;

			float_t testValue = (float)vectorFunction(float4(input.f, input.f, input.f, input.f)).x;
			float_t refValue = scalarFunction(input.f);

			float absError = abs(testValue.f - refValue.f);
			float relativeError = abs((testValue.f - refValue.f) / testValue.f);

			if (absError > absErrorInfo.maxError)
			{
				absErrorInfo.maxError = absError;
				absErrorInfo.input = input.f;
				absErrorInfo.refValue = refValue.f;
				absErrorInfo.testValue = testValue.f;
			}

			if (relativeError > relativeErrorInfo.maxError)
			{
				relativeErrorInfo.maxError = relativeError;
				relativeErrorInfo.input = input.f;
				relativeErrorInfo.refValue = refValue.f;
				relativeErrorInfo.testValue = testValue.f;
			}
		}

		printf("%s Max Error: %1.9g, In: %.9g, Exptd: %.9g, Rslt: %1.9g\n", funcName, absErrorInfo.maxError, absErrorInfo.input, absErrorInfo.refValue, absErrorInfo.testValue);
		printf("%s Relative Error: %1.9g, In: %.9g, Exptd: %.9g, Rslt: %1.9g\n", funcName, relativeErrorInfo.maxError, relativeErrorInfo.input, relativeErrorInfo.refValue, relativeErrorInfo.testValue);
	}

}

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

void RunUnitTestsMatrixFloat();

void RunUnitTestsVectorFloat();

void RunUnitTestsVectorInt();

void RunUnitTestsVectorDouble();

void RunUnitTests()
{
	using namespace hlslpp_unit;

	int seed = 0;// (int)time(NULL);
	srand(seed);

	RunUnitTestsVectorFloat();

	RunUnitTestsVectorInt();

	RunUnitTestsVectorDouble();

	RunUnitTestsMatrixFloat();

	// Quaternion tests

	quaternion q1 = quaternion::identity();
	quaternion q2 = quaternion(0.0f, 1.0f, 1.0f, 1.0f);

	quaternion qeuler1 = euler(float3(90.0f * deg2rad, 45.0f * deg2rad, 0.0f * deg2rad));
	quaternion qeuler2 = euler(float3(180.0f * deg2rad, 0.0f * deg2rad, 0.0f * deg2rad));

	quaternion qaxisangle = axisangle(float3(0.0f, 1.0f, 0.0f), 1.57f);

	quaternion slerp1 = slerp(q1, q2, 0.0f);
	quaternion slerp2 = slerp(q1, q2, 1.0f);
	
	quaternion slerp3 = slerp(q1, q2, 0.5f);
	
	quaternion testq = quaternion(0.66519f, 0.1881441f, 0.282216f, 0.665190f);

	float3x3 mat3x3FromQuat = float3x3(q1);
	float4x4 mat4x4FromQuat = float4x4(q1);
}

void RunExperiments()
{
	float f1 = (rand() % 1000) / 100.0f;
	float f2 = (rand() % 1000) / 100.0f;
	float f3 = (rand() % 1000) / 100.0f;
	float f4 = (rand() % 1000) / 100.0f;

	float4 test;
	float4 testResult;
	test = float4(52730508.0f);
	testResult = sin(test);

	float4 nan = float4(1.0f) / float4(0.0f);
	float4 subtractNan = float4(1.0f) - nan;

	quaternion q1 = euler(float3(90.0f * deg2rad, 45.0f * deg2rad, 0.0f * deg2rad));
	quaternion q2 = euler(float3(180.0f * deg2rad, 0.0f * deg2rad, 0.0f * deg2rad));
	quaternion fax = axisangle(float3(0.0f, 1.0f, 0.0f), 1.57f);

	quaternion q3 = q1 * q2;

	quaternion slerp1 = slerp(q1, q2, 0.0f);
	quaternion slerp2 = slerp(q1, q2, 1.0f);

	quaternion slerp3 = slerp(q1, q2, 0.5f);

	quaternion testq = quaternion(0.66519f, 0.1881441f, 0.282216f, 0.665190f);

	float3x3 matSlerp(testq);

	// Quaternion vector tests
	quaternion qEuler = euler(float3(0.0f * deg2rad, 90 * deg2rad, 0 * deg2rad));
	quaternion qPure = quaternion(1.0f, 0.0f, 0.0f, 0.0f);

	float3 vector = float3(1, 0, 0);

	quaternion normalMultiply = qEuler * qPure;

	float3 rotatedVector = mul(qEuler, vector);

	float4 p = rcp(test);

	float2 a;

	float3 lorry(1, 2, 3);

	float3 perry;
	perry.x *= 0.5f;

	float3 intTexCoord = float3(1, 2, 3);

	const float M = 10.0f;

	float4 pato = float4(10.0f, 5.0f, 0.5f, 4.0f);

	//pato.zw += pato.yx;

	pato.z = 1.0f / pato.z;

	float1 integerPart, fracPart;

	fracPart = modf(-testq.y, integerPart);

	//float checker = fmod(float1(10.0f), float1(3.0f)) > 0.5f;// ^ fmod(intTexCoord.y * M, 1.0f) > 0.5f;
	//
	//float checker2 = max(intTexCoord.x * M, 1.0f);// > 0.5f ^ fmod(intTexCoord.y * M, 1.0f) > 0.5f;

	//float2 p = (float2) q1.xyzw;

	//printf("%f %f %f %f\n", q3.x, q3.y, q3.z, q3.w);
}

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

void RunSpeedTests()
{
	float f1 = (rand() % 1000) / 100.0f;
	float f2 = (rand() % 1000) / 100.0f;
	float f3 = (rand() % 1000) / 100.0f;
	float f4 = (rand() % 1000) / 100.0f;

	float4 v1(f1);
	float4 v2(2.1f);
	float4 v3(f3);
	float4 v4(f4);

	float3 v5(f4);

	float4x4 mat_foo_4x4 = float4x4(10, 20, 1, 1,
		78, 5, 2, 8,
		14, 5, 5, 6,
		8, 4, 5, 6);

	float1 dp = 1.0f;

	float1 verify = dot(v3, v4);

	quaternion q1 = quaternion(f1, f2, f3, f4);
	quaternion q2 = quaternion(f4, f1, f3, f2);

	const long int iter = 1000000000;
	Timer timer;

	timer.Start();

	uint64_t clockStart = ClockCycleCount();

	for (long int i = 0; i < iter; ++i)
	{
		q1 = slerp(q1, q2, verify);// *v5;
		//mat_foo1_4x4 = inverse(mat_foo_4x4);
		//dp = dot(v1, v4 * dp);
		//v4 = v4.xxxx + v3.yyzw;
		//Vector4 yyzw = Vector4(v3f.y, v3f.y, v3f.z, v3f.w);
		//Vector4 xxxx = Vector4(v4f.x, v4f.x, v4f.x, v4f.x);
		//v4f = xxxx + yyzw;
	}
	double time = timer.Get();

	uint64_t clockEnd = ClockCycleCount();

	uint64_t totalCycles = clockEnd - clockStart;

	double cyclesPerOperation = totalCycles / (double)iter;

	printf("float4: %f, %f, %f, %f = %f\n", (float)q1.x, (float)q1.y, (float)q1.z, (float)q1.w, time);
	//printf("Vector4: %f, %f, %f, %f\n\n", (float)v4f.x, (float)v4f.y, (float)v4f.z, (float)v4f.w);
	//printf("float4x4: %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n\n", 
	//	(float)mat_foo_4x4._m00, (float)mat_foo_4x4._m01, (float)mat_foo_4x4._m02, (float)mat_foo_4x4._m03,
	//	(float)mat_foo_4x4._m10, (float)mat_foo_4x4._m11, (float)mat_foo_4x4._m12, (float)mat_foo_4x4._m13,
	//	(float)mat_foo_4x4._m20, (float)mat_foo_4x4._m21, (float)mat_foo_4x4._m22, (float)mat_foo_4x4._m23,
	//	(float)mat_foo_4x4._m30, (float)mat_foo_4x4._m31, (float)mat_foo_4x4._m32, (float)mat_foo_4x4._m33);
	printf("Result: %f, Cycles/Loop: %f, Elapsed: %f\n", (float)dp.x, cyclesPerOperation, time);
}

using namespace hlslpp;

#if defined(__ANDROID__)

#if defined(__cplusplus)
extern "C" {
#endif

void android_main(struct android_app* app)

#else

int main(int /*argc*/, char** /*argv*/)

#endif
{
	//RunUnitTests();
	//RunExperiments();
	//RunSpeedTests();

	printf("All tests completed successfully.\n");

	getchar();
}

#if defined(__ANDROID__)
#if defined(__cplusplus)
}
#endif
#endif