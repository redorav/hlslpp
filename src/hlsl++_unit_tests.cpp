#include "hlsl++.h"

// Hacky but needs FLOAT64
#include "hlsl++_unit_tests.h"

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

#if defined(HLSLPP_FLOAT8)

	void eq(const float8& v, float x, float y, float z, float w, float a, float b, float c, float d, float tolerance /*= 0.0f*/)
	{
		eq(v.f32[0], x, tolerance);
		eq(v.f32[1], y, tolerance);
		eq(v.f32[2], z, tolerance);
		eq(v.f32[3], w, tolerance);

		eq(v.f32[4], a, tolerance);
		eq(v.f32[5], b, tolerance);
		eq(v.f32[6], c, tolerance);
		eq(v.f32[7], d, tolerance);
	}

#endif

	void eq(double a, double b, double tolerance /*= 0.0*/)
	{
		bool withinTolerance = abs(a - b) <= tolerance;
		assert(withinTolerance);
	}

#if defined(HLSLPP_DOUBLE)

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


	void eq(const float1x1& m, float m00, float tolerance /*= 0.0f*/)
	{
		eq(m.f32[0], m00, tolerance);
	}

	void eq(const float1x2& m, float m00, float m01, float tolerance /*= 0.0f*/)
	{
		eq(m.f32[0], m00, tolerance);
		eq(m.f32[1], m01, tolerance);
	}

	void eq(const float1x3& m, float m00, float m01, float m02, float tolerance /*= 0.0f*/)
	{
		eq(m.f32[0], m00, tolerance);
		eq(m.f32[1], m01, tolerance);
		eq(m.f32[2], m02, tolerance);
	}
	
	void eq(const float1x4& m, float m00, float m01, float m02, float m03, float tolerance /*= 0.0f*/)
	{
		eq(m.f32[0], m00, tolerance);
		eq(m.f32[1], m01, tolerance);
		eq(m.f32[2], m02, tolerance);
		eq(m.f32[3], m03, tolerance);
	}

	void eq(const float2x1& m, float m00, float m01, float tolerance /*= 0.0f*/)
	{
		eq(m.f32[0], m00, tolerance);
		eq(m.f32[1], m01, tolerance);
	}

	void eq(const float2x2& m, float m00, float m01, float m10, float m11, float tolerance /*= 0.0f*/)
	{
		eq(m.f32[0], m00, tolerance);
		eq(m.f32[1], m01, tolerance);

		eq(m.f32[2], m10, tolerance);
		eq(m.f32[3], m11, tolerance);
	}

	void eq(const float2x3& m, float m00, float m01, float m02, float m10, float m11, float m12, float tolerance /*= 0.0f*/)
	{
		eq(m.f32_0[0], m00, tolerance);
		eq(m.f32_0[1], m01, tolerance);
		eq(m.f32_0[2], m02, tolerance);

		eq(m.f32_1[0], m10, tolerance);
		eq(m.f32_1[1], m11, tolerance);
		eq(m.f32_1[2], m12, tolerance);
	}

	void eq(const float2x4& m, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float tolerance /*= 0.0f*/)
	{
		eq(m.f32_0[0], m00, tolerance);
		eq(m.f32_0[1], m01, tolerance);
		eq(m.f32_0[2], m02, tolerance);
		eq(m.f32_0[3], m03, tolerance);

		eq(m.f32_1[0], m10, tolerance);
		eq(m.f32_1[1], m11, tolerance);
		eq(m.f32_1[2], m12, tolerance);
		eq(m.f32_1[3], m13, tolerance);
	}

	void eq(const float3x1& m, float m00, float m01, float m02, float tolerance /*= 0.0f*/)
	{
		eq(m.f32[0], m00, tolerance);
		eq(m.f32[1], m01, tolerance);
		eq(m.f32[2], m02, tolerance);
	}

	void eq(const float3x2& m, float m00, float m01, float m10, float m11, float m20, float m21, float tolerance /*= 0.0f*/)
	{
		eq(m.f32_0[0], m00, tolerance); eq(m.f32_1[0], m01, tolerance);
		eq(m.f32_0[1], m10, tolerance); eq(m.f32_1[1], m11, tolerance);
		eq(m.f32_0[2], m20, tolerance); eq(m.f32_1[2], m21, tolerance);
	}

	void eq(const float3x3& m, float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22, float tolerance /*= 0.0f*/)
	{
		eq(m._m00, m00, tolerance); eq(m._m01, m01, tolerance); eq(m._m02, m02, tolerance);
		eq(m._m10, m10, tolerance); eq(m._m11, m11, tolerance); eq(m._m12, m12, tolerance);
		eq(m._m20, m20, tolerance); eq(m._m21, m21, tolerance); eq(m._m22, m22, tolerance);
	}

	void eq(const float3x4& m, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float tolerance /*= 0.0f*/)
	{
		eq(m.f32_0[0], m00, tolerance); eq(m.f32_0[1], m01, tolerance); eq(m.f32_0[2], m02, tolerance); eq(m.f32_0[3], m03, tolerance);
		eq(m.f32_1[0], m10, tolerance); eq(m.f32_1[1], m11, tolerance); eq(m.f32_1[2], m12, tolerance); eq(m.f32_1[3], m13, tolerance);
		eq(m.f32_2[0], m20, tolerance); eq(m.f32_2[1], m21, tolerance); eq(m.f32_2[2], m22, tolerance); eq(m.f32_2[3], m23, tolerance);
	}

	void eq(const float4x1& m, float m00, float m01, float m02, float m03, float tolerance /*= 0.0f*/)
	{
		eq(m.f32[0], m00, tolerance);
		eq(m.f32[1], m01, tolerance);
		eq(m.f32[2], m02, tolerance);
		eq(m.f32[3], m03, tolerance);
	}

	void eq(const float4x2& m, 
		float m00, float m01, 
		float m10, float m11,
		float m20, float m21,
		float m30, float m31, float tolerance /*= 0.0f*/)
	{
		eq(m.f32_0[0], m00, tolerance); eq(m.f32_1[0], m01, tolerance);
		eq(m.f32_0[1], m10, tolerance); eq(m.f32_1[1], m11, tolerance);
		eq(m.f32_0[2], m20, tolerance); eq(m.f32_1[2], m21, tolerance);
		eq(m.f32_0[3], m30, tolerance); eq(m.f32_1[3], m31, tolerance);
	}

	void eq(const float4x3& m,
		float m00, float m01, float m02, 
		float m10, float m11, float m12, 
		float m20, float m21, float m22,
		float m30, float m31, float m32, float tolerance /*= 0.0f*/)
	{
		eq(m.f32_0[0], m00, tolerance); eq(m.f32_1[0], m01, tolerance); eq(m.f32_2[0], m02, tolerance);
		eq(m.f32_0[1], m10, tolerance); eq(m.f32_1[1], m11, tolerance); eq(m.f32_2[1], m12, tolerance);
		eq(m.f32_0[2], m20, tolerance); eq(m.f32_1[2], m21, tolerance); eq(m.f32_2[2], m22, tolerance);
		eq(m.f32_0[3], m30, tolerance); eq(m.f32_1[3], m31, tolerance); eq(m.f32_2[3], m32, tolerance);
	}

	void eq(const float4x4& m, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33, float tolerance /*= 0.0f*/)
	{
		eq(m._m00, m00, tolerance); eq(m._m01, m01, tolerance); eq(m._m02, m02, tolerance); eq(m._m03, m03, tolerance);
		eq(m._m10, m10, tolerance); eq(m._m11, m11, tolerance); eq(m._m12, m12, tolerance); eq(m._m13, m13, tolerance);
		eq(m._m20, m20, tolerance); eq(m._m21, m21, tolerance); eq(m._m22, m22, tolerance); eq(m._m23, m23, tolerance);
		eq(m._m30, m30, tolerance); eq(m._m31, m31, tolerance); eq(m._m32, m32, tolerance); eq(m._m33, m33, tolerance);
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

	float lerpf(float x, float y, float a)
	{
		return x + (y - x) * a;
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

void RunExperiments()
{
	printf("1) Experiments started\n");

	float4x4 m1 = float4x4(
		1, 2, 3, 4, 
		5, 6, 7, 8, 
		9, 10, 11, 12, 
		13, 14, 15, 16);

	float4x4 m2 = float4x4(
		17, 18, 19, 20, 
		21, 22, 23, 24, 
		25, 26, 27, 28, 
		29, 30, 31, 32);

	float4x4 m3 = float4x4(
		3.01799f, 3.27862f, 1.23535f, 3.32619f,
		0.56666f, 0.00888f, 0.42457f, 6.82070f,
		2.56136f, 3.06511f, 3.61529f, 4.85567f,
		4.81689f, 7.60904f, 7.15124f, 2.06395f
	);

	float4x4 m4x4_mul = mul(m1, m2);

	float3x4 m3x4_1 = float3x4(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12
	);

	float3x4 m3x4_2 = mul(m3x4_1, m2);

	float4x1 m4x1_1 = float4x1(
		5, 6, 7, 8
	);

	float4x1 m4x1_2 = mul(m2, m4x1_1);

	float4x2 m4x2_1 = float4x2(
		5, 6, 7, 8,
		21, 22, 23, 24
	);

	float4x2 m4x2_2 = mul(m2, m4x2_1);

	float1 d = determinant(m3);

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

	//float3 perry;
	//perry.x *= 0.5f;

	float3 intTexCoord = float3(1, 2, 3);

	const float M = 10.0f;

	float4 pato = float4(10.0f, 5.0f, 0.5f, 4.0f);

	//pato.zw += pato.yx;

	//pato.z = 1.0f / pato.z;

	float1 integerPart, fracPart;

	fracPart = modf(-testq.y, integerPart);

	//float checker = fmod(float1(10.0f), float1(3.0f)) > 0.5f;// ^ fmod(intTexCoord.y * M, 1.0f) > 0.5f;
	//
	//float checker2 = max(intTexCoord.x * M, 1.0f);// > 0.5f ^ fmod(intTexCoord.y * M, 1.0f) > 0.5f;

	//float2 p = (float2) q1.xyzw;

	//printf("%f %f %f %f\n", q3.x, q3.y, q3.z, q3.w);

	printf("Experiments completed\n\n");
}

void RunUnitTestsMatrixFloat();

void RunUnitTestsVectorFloat();

void RunUnitTestsVectorInt();

void RunUnitTestsVectorDouble();

void RunUnitTests()
{
	printf("2) Unit tests started\n");

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

	printf("Unit tests completed\n\n");
}

void RunPerformanceTests()
{
	printf("3) Performance tests started\n");

	using namespace hlslpp_unit;

	float f1  = (rand() % 1000) / 100.0f;
	float f2  = (rand() % 1000) / 100.0f;
	float f3  = (rand() % 1000) / 100.0f;
	float f4  = (rand() % 1000) / 100.0f;
	float f5  = (rand() % 1000) / 100.0f;
	float f6  = (rand() % 1000) / 100.0f;
	float f7  = (rand() % 1000) / 100.0f;
	float f8  = (rand() % 1000) / 100.0f;
	float f9  = (rand() % 1000) / 100.0f;
	float f10 = (rand() % 1000) / 100.0f;
	float f11 = (rand() % 1000) / 100.0f;
	float f12 = (rand() % 1000) / 100.0f;
	float f13 = (rand() % 1000) / 100.0f;
	float f14 = (rand() % 1000) / 100.0f;
	float f15 = (rand() % 1000) / 100.0f;
	float f16 = (rand() % 1000) / 100.0f;

	float1 v1_1(f1);
	float1 v1_2(f2);
	float1 v1_3(f3);
	float1 v1_4(f4);

	float2 v2_1(f1);
	float2 v2_2(f2);
	float2 v2_3(f3);
	float2 v2_4(f4);

	float3 v3_1(f1);
	float3 v3_2(f2);
	float3 v3_3(f3);
	float3 v3_4(f4);

	float4 v4_1(f1);
	float4 v4_2(f2);
	float4 v4_3(f3);
	float4 v4_4(f4);

	float3x4 m3x4_1;

	float4x4 m4x4_1(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16);
	float4x4 m4x4_2(f2);

	const float2x4 m2x4_1 = float2x4(1, 2, 3, 4, 5, 6, 7, 8);
	const float4x4 m2 = float4x4(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);

	const float2x4 m3 = mul(m2x4_1, m2);

	bool b1 = false;

	quaternion q1 = quaternion(f1, f2, f3, f4);
	quaternion q2 = quaternion(f4, f1, f3, f2);

	float4x4 mat_foo_4x4 = float4x4(10, 20, 1, 1,
		78, 5, 2, 8,
		14, 5, 5, 6,
		8, 4, 5, 6);

	float1 t1_1 = f1;
	float1 t1_2 = f2;
	float1 t1_3 = f3;

	const long int iter = 100000000;

	//printf("float4: %f, %f, %f, %f = %f\n", (float)v4.x, (float)v4.y, (float)v4.z, (float)v4.w, time);
	//printf("Vector4: %f, %f, %f, %f\n\n", (float)v4f.x, (float)v4f.y, (float)v4f.z, (float)v4f.w);
	//printf("float4x4: %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n\n", 
	//	(float)mat_foo_4x4._m00, (float)mat_foo_4x4._m01, (float)mat_foo_4x4._m02, (float)mat_foo_4x4._m03,
	//	(float)mat_foo_4x4._m10, (float)mat_foo_4x4._m11, (float)mat_foo_4x4._m12, (float)mat_foo_4x4._m13,
	//	(float)mat_foo_4x4._m20, (float)mat_foo_4x4._m21, (float)mat_foo_4x4._m22, (float)mat_foo_4x4._m23,
	//	(float)mat_foo_4x4._m30, (float)mat_foo_4x4._m31, (float)mat_foo_4x4._m32, (float)mat_foo_4x4._m33);
	//printf("Result: %f, Cycles/Loop: %f, Elapsed: %f\n", (float)dp.x, cyclesPerOperation, time);

	benchmark<float4x4, iter>("m4x4 add", [&]() -> float4x4 { m4x4_1 = m4x4_1 + m4x4_2; return m4x4_1; });
	benchmark<float4x4, iter>("m4x4 div", [&]() -> float4x4 { m4x4_1 = mul(m4x4_1, m4x4_2); return m4x4_1; });
	benchmark<float1, iter>("m4x4 det", [&]() -> float1 { v1_1 = determinant(m4x4_1); m4x4_1 = m4x4_1 + v1_1; return v1_1; });
	benchmark<float4x4, iter>("m4x4 inverse", [&]() -> float4x4 { m4x4_1 = inverse(m4x4_1); return m4x4_1; });
	benchmark<float4x4, iter>("m4x4 transp", [&]() -> float4x4 { m4x4_1 = transpose(m4x4_1); return m4x4_1; });
	benchmark<float3x4, iter>("mul(m3x4, m4x4)", [&]() -> float3x4 { m3x4_1 = mul(m3x4_1, m4x4_1); return m3x4_1; });
	benchmark<float4x4, iter>("mul(m4x4, m4x4)", [&]() -> float4x4 { m4x4_1 = mul(m4x4_1, m4x4_2); return m4x4_1; });

	benchmark<float4, iter>("mul(m4x4, m4x1)", [&]() -> float4 { v4_1 = mul(m4x4_1, v4_1); return v4_1; });
	benchmark<float4, iter>("mul(m1x4, m4x4)", [&]() -> float4 { v4_1 = mul(v4_1, m4x4_1); return v4_1; });

	//benchmark<float4x4, iter>("f4x1 x f1x4", [&]() -> float4x4 { m4x4_1 = transpose(m4x4_1); return m4x4_1; });
	benchmark<float1, iter>("m4x4 trace", [&]() -> float1 { v1_1 = trace(m4x4_1) + v1_1; return v1_1; });
	benchmark<float4x4, iter>("m4x4 quaternion", [&]() -> float4x4 { m4x4_1 = float4x4(q1); return m4x4_1; });

	benchmark<float4, iter>("wzyx", [&]() -> float4 { v4_1 = v4_1.wzyx; return v4_1; });

	benchmark<float4, iter>(">", [&]() -> float4 { v4_1 = v4_1 > v4_2; return v4_1; });

	benchmark<float4, iter>("abs", [&]() -> float4 { v4_1 = abs(v4_1); return v4_1; });
	benchmark<float4, iter>("acos", [&]() -> float4 { v4_1 = acos(v4_1); return v4_1; });
	benchmark<float4, iter>("all", [&]() -> float4 { v4_1 = all(v4_1); return v4_1; });
	benchmark<float4, iter>("any", [&]() -> float4 { v4_1 = any(v4_1); return v4_1; });
	benchmark<float4, iter>("asin", [&]() -> float4 { v4_1 = asin(v4_1); return v4_1; });
	benchmark<float4, iter>("atan", [&]() -> float4 { v4_1 = atan(v4_1); return v4_1; });
	benchmark<float4, iter>("ceil", [&]() -> float4 { v4_1 = ceil(v4_1); return v4_1; });
	benchmark<float4, iter>("clamp", [&]() -> float4 { v4_1 = clamp(v4_1, v4_2, v4_3); return v4_1; });
	benchmark<float4, iter>("cos", [&]() -> float4 { v4_1 = cos(v4_1); return v4_1; });
	benchmark<float4, iter>("cosh", [&]() -> float4 { v4_1 = cosh(v4_1); return v4_1; });
	benchmark<float3, iter>("cross", [&]() -> float3 { v3_1 = cross(v3_1, v3_2); return v3_1; });
	benchmark<float4, iter>("degrees", [&]() -> float4 { v4_1 = degrees(v4_1); return v4_1; });
	benchmark<float4, iter>("dot", [&]() -> float4 { v4_1 = dot(v4_1, v4_2).xxxx; return v4_1; });
	benchmark<float4, iter>("floor", [&]() -> float4 { v4_1 = floor(v4_1); return v4_1; });
	benchmark<float4, iter>("fmod", [&]() -> float4 { v4_1 = fmod(v4_1, v4_2); return v4_1; });
	benchmark<float4, iter>("frac", [&]() -> float4 { v4_1 = frac(v4_1); return v4_1; });
	benchmark<float4, iter>("exp", [&]() -> float4 { v4_1 = exp(v4_1); return v4_1; });
	benchmark<float4, iter>("exp2", [&]() -> float4 { v4_1 = exp2(v4_1); return v4_1; });
	benchmark<float4, iter>("isfinite", [&]() -> float4 { v4_1 = isfinite(v4_1); return v4_1; });
	benchmark<float4, iter>("isinf", [&]() -> float4 { v4_1 = isinf(v4_1); return v4_1; });
	benchmark<float4, iter>("isnan", [&]() -> float4 { v4_1 = isnan(v4_1); return v4_1; });
	benchmark<float4, iter>("length", [&]() -> float4 { v4_1 = length(v4_1).xxxx; return v4_1; });
	benchmark<float4, iter>("lerp", [&]() -> float4 { v4_1 = lerp(v4_1, v4_2, v4_3); return v4_1; });
	benchmark<float4, iter>("log", [&]() -> float4 { v4_1 = log(v4_1); return v4_1; });
	benchmark<float4, iter>("log2", [&]() -> float4 { v4_1 = log2(v4_1); return v4_1; });
	benchmark<float4, iter>("log10", [&]() -> float4 { v4_1 = log10(v4_1); return v4_1; });
	benchmark<float4, iter>("max", [&]() -> float4 { v4_1 = max(v4_1, v4_2); return v4_1; });
	benchmark<float4, iter>("min", [&]() -> float4 { v4_1 = min(v4_1, v4_2); return v4_1; });
	benchmark<float4, iter>("normalize", [&]() -> float4 { v4_1 = normalize(v4_1); return v4_1; });
	benchmark<float4, iter>("pow", [&]() -> float4 { v4_1 = pow(v4_1, v4_2); return v4_1; });
	benchmark<float4, iter>("radians", [&]() -> float4 { v4_1 = radians(v4_1); return v4_1; });
	benchmark<float4, iter>("rcp", [&]() -> float4 { v4_1 = rcp(v4_1); return v4_1; });
	benchmark<float4, iter>("reflect", [&]() -> float4 { v4_1 = reflect(v4_1, v4_2); return v4_1; });
	benchmark<float4, iter>("refract", [&]() -> float4 { v4_1 = refract(v4_1, v4_2, t1_1); return v4_1; });
	benchmark<float4, iter>("round", [&]() -> float4 { v4_1 = round(v4_1); return v4_1; });
	benchmark<float4, iter>("rsqrt", [&]() -> float4 { v4_1 = rsqrt(v4_1); return v4_1; });
	benchmark<float4, iter>("saturate", [&]() -> float4 { v4_1 = saturate(v4_1); return v4_1; });
	benchmark<float4, iter>("sign", [&]() -> float4 { v4_1 = sign(v4_1); return v4_1; });
	benchmark<float4, iter>("sin", [&]() -> float4 { v4_1 = sin(v4_1); return v4_1; });
	benchmark<float4, iter>("sinh", [&]() -> float4 { v4_1 = sinh(v4_1); return v4_1; });
	benchmark<float4, iter>("smoothstep", [&]() -> float4 { v4_1 = smoothstep(v4_1, v4_2, v4_3); return v4_1; });
	benchmark<float4, iter>("sqrt", [&]() -> float4 { v4_1 = sqrt(v4_1); return v4_1; });
	benchmark<float4, iter>("step", [&]() -> float4 { v4_1 = step(v4_1, v4_2); return v4_1; });
	benchmark<float4, iter>("trunc", [&]() -> float4 { v4_1 = trunc(v4_1); return v4_1; });
	benchmark<float4, iter>("tan", [&]() -> float4 { v4_1 = tan(v4_1); return v4_1; });
	benchmark<float4, iter>("tanh", [&]() -> float4 { v4_1 = tan(v4_1); return v4_1; });

	benchmark<float4, iter>("add", [&]() -> float4 { v4_1 = v4_1 + v4_2; return v4_1; });
	benchmark<float4, iter>("sub", [&]() -> float4 { v4_1 = v4_1 - v4_2; return v4_1; });
	benchmark<float4, iter>("mul", [&]() -> float4 { v4_1 = v4_1 * v4_2; return v4_1; });
	benchmark<float4, iter>("div", [&]() -> float4 { v4_1 = v4_1 / v4_2; return v4_1; });
	
	benchmark<quaternion, iter>("axisangle", [&]() -> quaternion { q1 = axisangle(q1.xyz, t1_1); return q1; });
	benchmark<quaternion, iter>("euler", [&]() -> quaternion { q1 = euler(q1.xyz); return q1; });
	benchmark<quaternion, iter>("conjugate", [&]() -> quaternion { q1 = conjugate(q1); return q1; });
	benchmark<quaternion, iter>("slerp", [&]() -> quaternion { q1 = slerp(q1, q2, t1_1); return q1; });

	printf("Performance tests completed\n\n");
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
	RunExperiments();
	RunUnitTests();
	RunPerformanceTests();

	getchar();
}

#if defined(__ANDROID__)
#if defined(__cplusplus)
}
#endif
#endif