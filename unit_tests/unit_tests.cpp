#include "hlsl++.h"

// Hacky but needs FLOAT64
#include "unit_tests.h"

// For strcmp
#include <string.h>

// For std::system
#include <cstdlib>

//#define NOMINMAX
//#include <windows.h>

extern "C"
{
	long IsDebuggerPresent(void);
	void Sleep(unsigned long dwMilliseconds);
}

const float deg2rad = 3.14159265f / 180.0f;

#if defined(_MSC_VER)
	#define sprintf_safe(dst, dst_size, format, ...) sprintf_s(dst, dst_size, format, __VA_ARGS__)
#else
	#define sprintf_safe(dst, dst_size, format, ...) snprintf(dst, dst_size, format, __VA_ARGS__)
#endif

namespace hlslpp_unit
{
	using namespace hlslpp;

	Config UnitTestConfig;
	CurrentTest TestState;
	CurrentTestCase TestCaseState;

	void BeginTestImpl(const char* testName, const char* filename)
	{
		TestState.filename = filename;
		TestState.name = testName;
		TestState.testFailureMessages.clear();
		TestState.testSuccessMessages.clear();
		TestState.testPassed = true;
		TestState.testRunning = true;
	}

	void EndTest()
	{
		if (UnitTestConfig.appveyor)
		{
			TestState.scratchAppveyorCommand = "powershell -Command \" & { Add-AppveyorTest -Framework Hlslpp";

			TestState.scratchAppveyorCommand += " -Name '";
			TestState.scratchAppveyorCommand += TestState.name;
			TestState.scratchAppveyorCommand += "'";

			TestState.scratchAppveyorCommand += " -Filename '";
			TestState.scratchAppveyorCommand += TestState.filename;
			TestState.scratchAppveyorCommand += "'";

			if (TestState.testPassed)
			{
				TestState.scratchAppveyorCommand += " -Outcome Passed";

				if (!TestState.testSuccessMessages.empty())
				{
					TestState.scratchAppveyorCommand += " -StdOut \"";

					TestState.scratchAppveyorCommand += TestState.testSuccessMessages[0];

					for (size_t i = 1; i < TestState.testSuccessMessages.size(); ++i)
					{
						TestState.scratchAppveyorCommand += "`n";
						TestState.scratchAppveyorCommand += TestState.testSuccessMessages[i];
					}

					TestState.scratchAppveyorCommand += "\"";
				}
			}
			else
			{
				UnitTestConfig.anyTestFailed = true;

				TestState.scratchAppveyorCommand += " -Outcome Failed";

				if (!TestState.testFailureMessages.empty())
				{
					TestState.scratchAppveyorCommand += " -StdErr (";

					TestState.scratchAppveyorCommand += "'";
					TestState.scratchAppveyorCommand += TestState.testFailureMessages[0];
					TestState.scratchAppveyorCommand += "'";

					for (size_t i = 1; i < TestState.testFailureMessages.size(); ++i)
					{
						TestState.scratchAppveyorCommand += ",'";
						TestState.scratchAppveyorCommand += TestState.testFailureMessages[i];
						TestState.scratchAppveyorCommand += "'";
					}

					TestState.scratchAppveyorCommand += " | out-string)";
				}
			}

			TestState.scratchAppveyorCommand += " } \"";

			printf("%s\n", TestState.scratchAppveyorCommand.c_str());
			int result = std::system(TestState.scratchAppveyorCommand.c_str());
			hlslpp_unit_unused(result);
		}
	}

	void BeginTestCase(const char* testString, int lineNumber, const char* filename)
	{
		TestCaseState.testString = testString;
		TestCaseState.lineNumber = lineNumber;
		TestCaseState.filename = filename;
		TestCaseState.passed = true;
		TestCaseState.testFailureMessage.clear();
	}

	void EndTestCase()
	{
		bool testPassed = TestCaseState.passed;

		if (UnitTestConfig.appveyor)
		{
			// Register failure and add to the message list
			if (!testPassed)
			{
				TestState.testPassed = false;

				char functionLine[512] = {};
				sprintf_safe(functionLine, sizeof(functionLine), "%s %s(%d)", TestCaseState.testString, TestCaseState.filename, TestCaseState.lineNumber);

				TestState.testFailureMessages.push_back(functionLine);
				TestState.testFailureMessages.push_back(TestCaseState.testFailureMessage);
			}
		}
		else
		{
			if (!testPassed)
			{
				printf("%s %s\n", TestCaseState.testString, TestCaseState.testFailureMessage.c_str());
				fflush(0);
				assert(false);
			}
		}
	}

	float div(float a, float b)
	{
		return a / b;
	}

	double div(double a, double b)
	{
		return a / b;
	}

	bool eq(float a, float b, float tolerance /*= 0.0f*/)
	{
		bool withinTolerance = abs(a - b) <= tolerance;

		if (!withinTolerance)
		{
			char assertMessage[512] = {};
			sprintf_safe(assertMessage, sizeof(assertMessage), "Assertion failed! Values are not equal: a = %f, b = %f, tolerance = %f", a, b, tolerance);
			TestCaseState.testFailureMessage += assertMessage;
		}

		return withinTolerance;
	}

	bool eq(const float2& v, float x, float y, float tolerance /*= 0.0f*/)
	{
		return eq(v.x, x, tolerance)
			&& eq(v.y, y, tolerance);
	}

	bool eq(const float3& v, float x, float y, float z, float tolerance /*= 0.0f*/)
	{
		return eq(v.x, x, tolerance)
			&& eq(v.y, y, tolerance)
			&& eq(v.z, z, tolerance);
	}

	bool eq(const float4& v, float x, float y, float z, float w, float tolerance /*= 0.0f*/)
	{
		return eq(v.x, x, tolerance)
			&& eq(v.y, y, tolerance)
			&& eq(v.z, z, tolerance)
			&& eq(v.w, w, tolerance);
	}

#if defined(HLSLPP_FLOAT8)

	bool eq(const float8& v, float x, float y, float z, float w, float a, float b, float c, float d, float tolerance /*= 0.0f*/)
	{
		return eq(v.f32[0], x, tolerance)
		&& eq(v.f32[1], y, tolerance)
		&& eq(v.f32[2], z, tolerance)
		&& eq(v.f32[3], w, tolerance)
		&& eq(v.f32[4], a, tolerance)
		&& eq(v.f32[5], b, tolerance)
		&& eq(v.f32[6], c, tolerance)
		&& eq(v.f32[7], d, tolerance);
	}

#endif

	bool eq(double a, double b, double tolerance /*= 0.0*/)
	{
		bool withinTolerance = abs(a - b) <= tolerance;
		return withinTolerance;
	}

#if defined(HLSLPP_DOUBLE)

	bool eq(const double2& v, double x, double y, double tolerance /*= 0.0*/)
	{
		return eq((double)v.x, x, tolerance)
			&& eq((double)v.y, y, tolerance);
	}

	bool eq(const double3& v, double x, double y, double z, double tolerance /*= 0.0*/)
	{
		return eq((double)v.x, x, tolerance)
			&& eq((double)v.y, y, tolerance)
			&& eq((double)v.z, z, tolerance);
	}

	bool eq(const double4& v, double x, double y, double z, double w, double tolerance /*= 0.0*/)
	{
		return eq((double)v.x, x, tolerance)
			&& eq((double)v.y, y, tolerance)
			&& eq((double)v.z, z, tolerance)
			&& eq((double)v.w, w, tolerance);
	}

#endif

	bool eq(float a, bool c)
	{
		bool equals = (a != 0.0f ? true : false) == c;
		return equals;
	}

	bool eq(const float2& v, bool x, bool y)
	{
		return eq(v.x, x)
			&& eq(v.y, y);
	}

	bool eq(const float3& v, bool x, bool y, bool z)
	{
		return eq(v.x, x)
			&& eq(v.y, y)
			&& eq(v.z, z);
	}

	bool eq(const float4& v, bool x, bool y, bool z, bool w)
	{
		return eq(v.x, x)
			&& eq(v.y, y)
			&& eq(v.z, z)
			&& eq(v.w, w);
	}

	bool eq(int32_t a, int32_t b)
	{
		return a == b;
	}

	bool eq(const int2& v, int32_t x, int32_t y)
	{
		return eq(v.x, x)
			&& eq(v.y, y);
	}

	bool eq(const int3& v, int32_t x, int32_t y, int32_t z)
	{
		return eq(v.x, x)
			&& eq(v.y, y)
			&& eq(v.z, z);
	}

	bool eq(const int4& v, int32_t x, int32_t y, int32_t z, int32_t w)
	{
		return eq(v.x, x)
			&& eq(v.y, y)
			&& eq(v.z, z)
			&& eq(v.w, w);
	}

	bool eq(uint32_t a, uint32_t b)
    {
		return a == b;
    }

	bool eq(const uint2& v, uint32_t x, uint32_t y)
    {
		return eq(v.x, x)
			&& eq(v.y, y);
    }

	bool eq(const uint3& v, uint32_t x, uint32_t y, uint32_t z)
    {
		return eq(v.x, x)
			&& eq(v.y, y)
			&& eq(v.z, z);
    }

	bool eq(const uint4& v, uint32_t x, uint32_t y, uint32_t z, uint32_t w)
    {
		return eq(v.x, x)
			&& eq(v.y, y)
			&& eq(v.z, z)
			&& eq(v.w, w);
    }

	bool eq(bool a, bool c)
	{
		return a == c;
	}


	bool eq(const float1x1& m, float m00, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32[0], m00, tolerance);
	}

	bool eq(const float1x2& m, float m00, float m01, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32[0], m00, tolerance)
			&& eq(m.f32[1], m01, tolerance);
	}

	bool eq(const float1x3& m, float m00, float m01, float m02, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32[0], m00, tolerance)
			&& eq(m.f32[1], m01, tolerance)
			&& eq(m.f32[2], m02, tolerance);
	}
	
	bool eq(const float1x4& m, float m00, float m01, float m02, float m03, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32[0], m00, tolerance)
			&& eq(m.f32[1], m01, tolerance)
			&& eq(m.f32[2], m02, tolerance)
			&& eq(m.f32[3], m03, tolerance);
	}

	bool eq(const float2x1& m, float m00, float m01, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32[0], m00, tolerance)
			&& eq(m.f32[1], m01, tolerance);
	}

	bool eq(const float2x2& m, float m00, float m01, float m10, float m11, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32[0], m00, tolerance)
			&& eq(m.f32[1], m01, tolerance)
			&& eq(m.f32[2], m10, tolerance)
			&& eq(m.f32[3], m11, tolerance);
	}

	bool eq(const float2x3& m, float m00, float m01, float m02, float m10, float m11, float m12, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32_0[0], m00, tolerance)
			&& eq(m.f32_0[1], m01, tolerance)
			&& eq(m.f32_0[2], m02, tolerance)

			&& eq(m.f32_1[0], m10, tolerance)
			&& eq(m.f32_1[1], m11, tolerance)
			&& eq(m.f32_1[2], m12, tolerance);
	}

	bool eq(const float2x4& m, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32_0[0], m00, tolerance)
			&& eq(m.f32_0[1], m01, tolerance)
			&& eq(m.f32_0[2], m02, tolerance)
			&& eq(m.f32_0[3], m03, tolerance)

			&& eq(m.f32_1[0], m10, tolerance)
			&& eq(m.f32_1[1], m11, tolerance)
			&& eq(m.f32_1[2], m12, tolerance)
			&& eq(m.f32_1[3], m13, tolerance);
	}

	bool eq(const float3x1& m, float m00, float m01, float m02, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32[0], m00, tolerance)
			&& eq(m.f32[1], m01, tolerance)
			&& eq(m.f32[2], m02, tolerance);
	}

	bool eq(const float3x2& m, float m00, float m01, float m10, float m11, float m20, float m21, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32_0[0], m00, tolerance) && eq(m.f32_1[0], m01, tolerance)
			&& eq(m.f32_0[1], m10, tolerance) && eq(m.f32_1[1], m11, tolerance)
			&& eq(m.f32_0[2], m20, tolerance) && eq(m.f32_1[2], m21, tolerance);
	}

	bool eq(const float3x3& m, float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22, float tolerance /*= 0.0f*/)
	{
		return eq(m._m00, m00, tolerance) && eq(m._m01, m01, tolerance) && eq(m._m02, m02, tolerance)
			&& eq(m._m10, m10, tolerance) && eq(m._m11, m11, tolerance) && eq(m._m12, m12, tolerance)
			&& eq(m._m20, m20, tolerance) && eq(m._m21, m21, tolerance) && eq(m._m22, m22, tolerance);
	}

	bool eq(const float3x4& m, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32_0[0], m00, tolerance) && eq(m.f32_0[1], m01, tolerance) && eq(m.f32_0[2], m02, tolerance) && eq(m.f32_0[3], m03, tolerance)
			&& eq(m.f32_1[0], m10, tolerance) && eq(m.f32_1[1], m11, tolerance) && eq(m.f32_1[2], m12, tolerance) && eq(m.f32_1[3], m13, tolerance)
			&& eq(m.f32_2[0], m20, tolerance) && eq(m.f32_2[1], m21, tolerance) && eq(m.f32_2[2], m22, tolerance) && eq(m.f32_2[3], m23, tolerance);
	}

	bool eq(const float4x1& m, float m00, float m01, float m02, float m03, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32[0], m00, tolerance)
			&& eq(m.f32[1], m01, tolerance)
			&& eq(m.f32[2], m02, tolerance)
			&& eq(m.f32[3], m03, tolerance);
	}

	bool eq(const float4x2& m,
		float m00, float m01, 
		float m10, float m11,
		float m20, float m21,
		float m30, float m31, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32_0[0], m00, tolerance) && eq(m.f32_1[0], m01, tolerance)
			&& eq(m.f32_0[1], m10, tolerance) && eq(m.f32_1[1], m11, tolerance)
			&& eq(m.f32_0[2], m20, tolerance) && eq(m.f32_1[2], m21, tolerance)
			&& eq(m.f32_0[3], m30, tolerance) && eq(m.f32_1[3], m31, tolerance);
	}

	bool eq(const float4x3& m,
		float m00, float m01, float m02, 
		float m10, float m11, float m12, 
		float m20, float m21, float m22,
		float m30, float m31, float m32, float tolerance /*= 0.0f*/)
	{
		return eq(m.f32_0[0], m00, tolerance) && eq(m.f32_1[0], m01, tolerance) && eq(m.f32_2[0], m02, tolerance)
			&& eq(m.f32_0[1], m10, tolerance) && eq(m.f32_1[1], m11, tolerance) && eq(m.f32_2[1], m12, tolerance)
			&& eq(m.f32_0[2], m20, tolerance) && eq(m.f32_1[2], m21, tolerance) && eq(m.f32_2[2], m22, tolerance)
			&& eq(m.f32_0[3], m30, tolerance) && eq(m.f32_1[3], m31, tolerance) && eq(m.f32_2[3], m32, tolerance);
	}

	bool eq(const float4x4& m, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33, float tolerance /*= 0.0f*/)
	{
		return eq(m._m00, m00, tolerance) && eq(m._m01, m01, tolerance) && eq(m._m02, m02, tolerance) && eq(m._m03, m03, tolerance)
			&& eq(m._m10, m10, tolerance) && eq(m._m11, m11, tolerance) && eq(m._m12, m12, tolerance) && eq(m._m13, m13, tolerance)
			&& eq(m._m20, m20, tolerance) && eq(m._m21, m21, tolerance) && eq(m._m22, m22, tolerance) && eq(m._m23, m23, tolerance)
			&& eq(m._m30, m30, tolerance) && eq(m._m31, m31, tolerance) && eq(m._m32, m32, tolerance) && eq(m._m33, m33, tolerance);
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

	float round_f(float x)
	{
		float t = trunc_f(x);
		float frac = x - t;
		float abs_frac = frac >= 0.0f ? frac : -frac;
		return abs_frac <= 0.5f ? t : x >= 0.0f ? t + 1.0f : t - 1.0f;
	}

	float trunc_f(float x)
	{
		return (float)((int)x);
	}

	float sign_f(float x)
	{
		if (x > 0.0) return 1.0;
		if (x < 0.0) return -1.0;
		return x;
	}

	double round_d(double x)
	{
		double t = trunc_d(x);
		double frac = x - t;
		double abs_frac = frac >= 0.0 ? frac : -frac;
		return abs_frac <= 0.5 ? t : x >= 0.0 ? t + 1.0 : t - 1.0;
	}

	double trunc_d(double x)
	{
		return (double)((int64_t)x);
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

		for (int32_t i = posRangeStart; i < posRangeEnd; ++i)
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

HLSLPP_UNIT_UNUSED_VARIABLE_BEGIN
void RunExperiments()
{
	printf("1) Experiments started\n");

	float4x4 testm = float4x4::rotation_axis(normalize(float3(1, 2, 3)), 30.0f * 3.1415f / 180.0f);

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

	float f1 = (float)(rand() % 1000) / 100.0f; 
	float f2 = (float)(rand() % 1000) / 100.0f;
	float f3 = (float)(rand() % 1000) / 100.0f;
	float f4 = (float)(rand() % 1000) / 100.0f;

	float4 test;
	float4 testResult;
	test = float4(52730508.0f);
	testResult = sin(test);

	float4 nan = float4(1.0f) / float4(0.0f);
	float4 subtractNan = float4(1.0f) - nan;

	quaternion q1 = quaternion::rotation_euler_zxy(float3(90.0f * deg2rad, 45.0f * deg2rad, 0.0f * deg2rad));
	quaternion q2 = quaternion::rotation_euler_zxy(float3(180.0f * deg2rad, 0.0f * deg2rad, 0.0f * deg2rad));
	quaternion fax = quaternion::rotation_axis(float3(0.0f, 1.0f, 0.0f), 1.57f);

	quaternion slerp1 = slerp(q1, q2, 0.0f);
	quaternion slerp2 = slerp(q1, q2, 1.0f);

	quaternion slerp3 = slerp(q1, q2, 0.5f);

	quaternion testq = quaternion(0.66519f, 0.1881441f, 0.282216f, 0.665190f);

	float3x3 matSlerp(testq);

	// Quaternion vector tests
	quaternion qEuler = quaternion::rotation_euler_zxy(float3(0.0f * deg2rad, 90 * deg2rad, 0 * deg2rad));
	quaternion qPure = quaternion(1.0f, 0.0f, 0.0f, 0.0f);

	float3 vector = float3(1, 0, 0);

	float3 rotatedVector = mul(qEuler, vector);

	float4 p = rcp(test);

	float2 a;

	float3 lorry(1, 2, 3);

	float3 intTexCoord = float3(1, 2, 3);

	printf("Experiments completed\n\n");
}
HLSLPP_UNIT_UNUSED_VARIABLE_END

void RunUnitTestsMatrixFloat();

void RunUnitTestsMatrixTransform();

void RunUnitTestsVectorFloat();

void RunUnitTestsVectorDouble();

void RunUnitTestsVectorInt();

void RunUnitTestsQuaternion();

void RunUnitTests()
{
	printf("2) Unit tests started\n");

	using namespace hlslpp_unit;

	int seed = 0;// (int)time(NULL);
	srand(seed);

	RunUnitTestsVectorFloat();

	RunUnitTestsVectorDouble();

	RunUnitTestsVectorInt();

	//n128 a = _hlslpp_set_ps(1, 2, 3, 4);
	//n128 b = _hlslpp_set_ps(5, 6, 7, 8);
	//n128 c = _hlslpp_set_ps(9, 10, 11, 12);
	//n128 d = _hlslpp_set_ps(13, 14, 15, 16);
	//
	//n512 v = _hlslpp512_set128_ps(a, b, c, d);

	//printf("%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
	//	v.m512_f32[0], v.m512_f32[1], v.m512_f32[2], v.m512_f32[3],
	//	v.m512_f32[4], v.m512_f32[5], v.m512_f32[6], v.m512_f32[7],
	//	v.m512_f32[8], v.m512_f32[9], v.m512_f32[10], v.m512_f32[11],
	//	v.m512_f32[12], v.m512_f32[13], v.m512_f32[14], v.m512_f32[15]);

	RunUnitTestsMatrixFloat();

	RunUnitTestsQuaternion();

	RunUnitTestsMatrixTransform();

	printf("Unit tests completed\n\n");
}

void RunPerformanceTests()
{
	printf("3) Performance tests started\n");

	using namespace hlslpp_unit;

	float f1  = (float)(rand() % 1000) / 100.0f;
	float f2  = (float)(rand() % 1000) / 100.0f;
	float f3  = (float)(rand() % 1000) / 100.0f;
	float f4  = (float)(rand() % 1000) / 100.0f;
	float f5  = (float)(rand() % 1000) / 100.0f;
	float f6  = (float)(rand() % 1000) / 100.0f;
	float f7  = (float)(rand() % 1000) / 100.0f;
	float f8  = (float)(rand() % 1000) / 100.0f;
	float f9  = (float)(rand() % 1000) / 100.0f;
	float f10 = (float)(rand() % 1000) / 100.0f;
	float f11 = (float)(rand() % 1000) / 100.0f;
	float f12 = (float)(rand() % 1000) / 100.0f;
	float f13 = (float)(rand() % 1000) / 100.0f;
	float f14 = (float)(rand() % 1000) / 100.0f;
	float f15 = (float)(rand() % 1000) / 100.0f;
	float f16 = (float)(rand() % 1000) / 100.0f;

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

	float3x3 m3x3_1(f1, f2, f3, f4, f5, f6, f7, f8, f9);

	float3x4 m3x4_1;

	float4x4 m4x4_1(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16);
	float4x4 m4x4_2(f2);

	quaternion q1 = quaternion(f1, f2, f3, f4);
	quaternion q2 = quaternion(f4, f1, f3, f2);

	float1 t1_1 = f1;

	const long int iter = 100000000;

	float3x3 m = float3x3::rotation_y(3.1415f / 2.0f);

	benchmark<float4x4, iter>("m4x4 add", [&]() -> float4x4 { m4x4_1 = m4x4_1 + m4x4_2; return m4x4_1; });

	benchmark<float4, iter>("normalize", [&]() -> float4 { v4_1 = normalize(v4_1); return v4_1; });

	benchmark<float4, iter>("floor", [&]() -> float4 { v4_1 = floor(v4_1); return v4_1; });
	benchmark<float4, iter>("round", [&]() -> float4 { v4_1 = round(v4_1); return v4_1; });
	benchmark<float4, iter>("ceil", [&]() -> float4 { v4_1 = ceil(v4_1); return v4_1; });

	benchmark<quaternion, iter>("quaternion slerp", [&]() -> quaternion { q1 = slerp(q1, q2, t1_1); return q1; });
	benchmark<quaternion, iter>("quaternion nlerp", [&]() -> quaternion { q1 = nlerp(q1, q2, t1_1); return q1; });
	benchmark<quaternion, iter>("quaternion lerp", [&]() -> quaternion { q1 = lerp(q1, q2, t1_1); return q1; });
	benchmark<quaternion, iter>("rotation_euler_zxy", [&]() -> quaternion { q1 = quaternion::rotation_euler_zxy(q1.xyz); return q1; });
	benchmark<float3x3, iter>("m3x3 inverse", [&]() -> float3x3 { m3x3_1 = inverse(m3x3_1); return m3x3_1; });
	benchmark<float4x4, iter>("m4x4 inverse", [&]() -> float4x4 { m4x4_1 = inverse(m4x4_1); return m4x4_1; });
	benchmark<quaternion, iter>("rotation_axis_cosangle", [&]() -> quaternion { q1 = quaternion::rotation_axis_cosangle(q1.xyz, f1, 1.0f); return q1; });
	benchmark<quaternion, iter>("rotation_axis", [&]() -> quaternion { q1 = quaternion::rotation_axis(q1.xyz, t1_1); return q1; });
	benchmark<quaternion, iter>("conjugate", [&]() -> quaternion { q1 = conjugate(q1); return q1; });
	
	benchmark<quaternion, iter>("quaternion(m3x3)", [&]() -> quaternion { q1 = quaternion(m); return q1; });

	benchmark<float4x4, iter>("m4x4 add", [&]() -> float4x4 { m4x4_1 = m4x4_1 + m4x4_2; return m4x4_1; });
	benchmark<float4x4, iter>("m4x4 div", [&]() -> float4x4 { m4x4_1 = m4x4_1 / m4x4_2; return m4x4_1; });
	benchmark<float1, iter>("m4x4 det", [&]() -> float1 { v1_1 = determinant(m4x4_1); m4x4_1 = m4x4_1 + v1_1; return v1_1; });

	benchmark<float4x4, iter>("m4x4 transp", [&]() -> float4x4 { m4x4_1 = transpose(m4x4_1); return m4x4_1; });
	benchmark<float3x4, iter>("mul(m3x4, m4x4)", [&]() -> float3x4 { m3x4_1 = mul(m3x4_1, m4x4_1); return m3x4_1; });
	benchmark<float4x4, iter>("mul(m4x4, m4x4)", [&]() -> float4x4 { m4x4_1 = mul(m4x4_1, m4x4_2); return m4x4_1; });

	benchmark<float4, iter>("mul(m4x4, m4x1)", [&]() -> float4 { v4_1 = mul(m4x4_1, v4_1); return v4_1; });
	benchmark<float4, iter>("mul(m1x4, m4x4)", [&]() -> float4 { v4_1 = mul(v4_1, m4x4_1); return v4_1; });

	//benchmark<float4x4, iter>("f4x1 x f1x4", [&]() -> float4x4 { m4x4_1 = transpose(m4x4_1); return m4x4_1; });
	benchmark<float1, iter>("m4x4 trace", [&]() -> float1 { v1_1 = trace(m4x4_1) + v1_1; return v1_1; });
	benchmark<float4x4, iter>("m4x4(quaternion)", [&]() -> float4x4 { m4x4_1 = float4x4(q1); return m4x4_1; });

	benchmark<float4, iter>("wzyx", [&]() -> float4 { v4_1 = v4_1.wzyx; return v4_1; });

	benchmark<float4, iter>(">", [&]() -> float4 { v4_1 = v4_1 > v4_2; return v4_1; });

	benchmark<float4, iter>("abs", [&]() -> float4 { v4_1 = abs(v4_1); return v4_1; });
	benchmark<float4, iter>("acos", [&]() -> float4 { v4_1 = acos(v4_1); return v4_1; });
	benchmark<float4, iter>("all", [&]() -> float4 { v4_1 = all(v4_1); return v4_1; });
	benchmark<float4, iter>("any", [&]() -> float4 { v4_1 = any(v4_1); return v4_1; });
	benchmark<float4, iter>("asin", [&]() -> float4 { v4_1 = asin(v4_1); return v4_1; });
	benchmark<float4, iter>("atan", [&]() -> float4 { v4_1 = atan(v4_1); return v4_1; });
	benchmark<float4, iter>("atan2", [&]() -> float4 { v4_1 = atan2(v4_1, v4_2); return v4_1; });
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
	
	printf("Performance tests completed\n\n");
}

using namespace hlslpp;

#if defined(__ANDROID__)

#if defined(__cplusplus)
extern "C" {
#endif

void android_main(struct android_app* app)

#else

int main(int argc, char** argv)

#endif
{
	bool runExperiments = true;
	bool runUnitTests = true;
	bool runPerformanceTests = true;
	bool appveyor = false;

#if !defined(__ANDROID__)
	if (argc > 1)
	{
		runUnitTests = false;
		runExperiments = false;
		runPerformanceTests = false;

		for (int i = 1; i < argc; ++i)
		{
			if (strcmp(argv[i], "experiments") == 0)
			{
				runExperiments = true;
			}
			else if (strcmp(argv[i], "unit_tests") == 0)
			{
				runUnitTests = true;
			}
			else if (strcmp(argv[i], "perf_tests") == 0)
			{
				runPerformanceTests = true;
			}
			else if (strcmp(argv[i], "appveyor") == 0)
			{
				appveyor = true;
			}
		}
}
#endif

	hlslpp_unit::UnitTestConfig.appveyor = appveyor;

	if (runExperiments)
	{
		RunExperiments();
	}

	if (runUnitTests)
	{
		RunUnitTests();
	}

	if (runPerformanceTests)
	{
		RunPerformanceTests();
	}

#if !defined(__ANDROID__)

	if (hlslpp_unit::UnitTestConfig.anyTestFailed)
	{
		return -1;
	}
	else
	{
		return 0;
	}

#endif
}

#if defined(__ANDROID__)
#if defined(__cplusplus)
}
#endif
#endif