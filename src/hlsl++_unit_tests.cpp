#if defined(_WIN32)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

//#include "DirectXMath.h"
#endif

#include <cassert>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "hlsl++.h"

using std::cout;
using namespace hlslpp;

// Copied from https://randomascii.wordpress.com/2014/01/27/theres-only-four-billion-floatsso-test-them-all/
union Float_t
{
	Float_t(float num = 0.0f) : f(num) {}
	// Portable extraction of components.
	bool Negative() const { return (i >> 31) != 0; }
	int32_t RawMantissa() const { return i & ((1 << 23) - 1); }
	int32_t RawExponent() const { return (i >> 23) & 0xFF; }

	int32_t i;
	float f;
#ifdef _DEBUG
	struct
	{   // Bitfields for exploration. Do not use in production code.
		uint32_t mantissa : 23;
		uint32_t exponent : 8;
		uint32_t sign : 1;
	} parts;
#endif
};

typedef float(*Transform)(float);
typedef n128(*Transform4)(n128);

// Pass in a uint32_t range of float representations to test. start and stop are inclusive. Pass in 0, 0xFFFFFFFF to scan all
// floats. The floats are iterated through by incrementing their integer representation.
void ExhaustiveTest(uint32_t start, uint32_t stop, Transform4 TestFunc, Transform RefFunc, const char* desc)
{
	printf("Testing %s from %u to %u (inclusive).\n", desc, start, stop);
	// Use long long to let us loop over all positive integers.
	float maxError = 0.0f;
	float maxErrorInput = 0.0f;
	float maxErrorRefValue = 0.0f;
	float maxErrorTestValue = 0.0f;

	long long i = start;
	while (i <= stop)
	{
		Float_t input;
		input.i = (int32_t)i;
		Float_t testValue = 0.0f;// TestFunc(_hlslpp_set1_ps(input.f));
		Float_t refValue = RefFunc(input.f);
		
		//if  (testValue.f != refValue.f && // If the results don’t match then report an error.
		//	(testValue.f == testValue.f || refValue.f == refValue.f)) // If both results are NaNs then we treat that as a match.
		//{
		float absError = abs(testValue.f - refValue.f);
		
		if (absError > maxError)
		{
			maxError = absError;
			maxErrorInput = input.f;
			maxErrorRefValue = refValue.f;
			maxErrorTestValue = testValue.f;
			//printf("Input %.9g, expected %.9g, got %1.9g. Error: %1.9g\n", input.f, refValue.f, testValue.f, absError);
		}

		if (i % 1000000 == 0)
		{
			//printf("Progress: %f%%\n", i * 100.f / stop);
		}

		++i;
	}

	printf("%s Max Error: %1.9g, In: %.9g, Exptd: %.9g, Rslt: %1.9g.\n", desc, maxError, maxErrorInput, maxErrorRefValue, maxErrorTestValue);
}

namespace hlslpp_unit
{
	bool eq(float a, float b, float tolerance = 0.0f)
	{
		float error = abs(a - b);
		bool withinTolerance = abs(a - b) <= tolerance;
		return withinTolerance;
	}

	bool eq(const float2& v, float x, float y, float tolerance = 0.0f)
	{
		return eq(v.x, x, tolerance) && eq(v.y, y, tolerance);
	}

	bool eq(const float3& v, float x, float y, float z, float tolerance = 0.0f)
	{
		return eq(v.x, x, tolerance) && eq(v.y, y, tolerance) && eq(v.z, z, tolerance);
	}

	bool eq(const float4& v, float x, float y, float z, float w, float tolerance = 0.0f)
	{
		return eq(v.x, x, tolerance) && eq(v.y, y, tolerance) && eq(v.z, z, tolerance) && eq(v.w, w, tolerance);
	}

	float div(float a, float b)
	{
		return a / b;
	}

	bool eq(int32_t a, int32_t b)
	{
		return a == b;
	}

	bool eq(const int2& v, int32_t x, int32_t y)
	{
		return eq(v.x, x) && eq(v.y, y);
	}

	bool eq(const int3& v, int32_t x, int32_t y, int32_t z)
	{
		return eq(v.x, x) && eq(v.y, y) && eq(v.z, z);
	}

	bool eq(const int4& v, int32_t x, int32_t y, int32_t z, int32_t w)
	{
		return eq(v.x, x) && eq(v.y, y) && eq(v.z, z) && eq(v.w, w);
	}
}

class Timer
{
private:
	//LARGE_INTEGER m_startTime, m_endTime, m_elapsedMicroseconds;
	//LARGE_INTEGER m_frequency;
	std::chrono::high_resolution_clock::time_point m_startTime;
	std::chrono::high_resolution_clock::time_point m_endTime;

public:
	void Start()
	{
		//QueryPerformanceFrequency(&m_frequency);
		//QueryPerformanceCounter(&m_startTime);

		m_startTime = std::chrono::high_resolution_clock::now();
	}

	double Get()
	{
		//QueryPerformanceCounter(&m_endTime);
		//m_elapsedMicroseconds.QuadPart = m_endTime.QuadPart - m_startTime.QuadPart;
		//m_elapsedMicroseconds.QuadPart *= 1000000;
		//m_elapsedMicroseconds.QuadPart /= m_frequency.QuadPart;
		//
		//return double(m_elapsedMicroseconds.QuadPart) / 1.0e6;

		m_endTime = std::chrono::high_resolution_clock::now();

		return std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime).count() / 1e9f;
	}
};

void RunUnitTests()
{
	using namespace hlslpp_unit;

	float f1 = (float) (rand() % 1000); float f5 = (float) (rand() % 1000); float f9 =  (float) (rand() % 1000); float f13 = (float) (rand() % 1000); float f17 = (float) (rand() % 1000); 
	float f2 = (float) (rand() % 1000); float f6 = (float) (rand() % 1000); float f10 = (float) (rand() % 1000); float f14 = (float) (rand() % 1000); float f18 = (float) (rand() % 1000);
	float f3 = (float) (rand() % 1000); float f7 = (float) (rand() % 1000); float f11 = (float) (rand() % 1000); float f15 = (float) (rand() % 1000); float f19 = (float) (rand() % 1000);
	float f4 = (float) (rand() % 1000); float f8 = (float) (rand() % 1000); float f12 = (float) (rand() % 1000); float f16 = (float) (rand() % 1000); float f20 = (float) (rand() % 1000);

	// Initialization

	float1 vfoo1 = float1(f1);												assert(eq(vfoo1, f1));
	float2 vfoo2 = float2(f2, f3);											assert(eq(vfoo2, f2, f3));
	float3 vfoo3 = float3(f4, f5, f6);										assert(eq(vfoo3, f4, f5, f6));
	float4 vfoo4 = float4(f7, f8, f9, f10);									assert(eq(vfoo4, f7, f8, f9, f10));

	vfoo1 = float1(f1);														assert(eq(vfoo1, f1));
	vfoo2 = float2(f2, f3);													assert(eq(vfoo2, f2, f3));
	vfoo3 = float3(f4, f5, f6);												assert(eq(vfoo3, f4, f5, f6));
	vfoo4 = float4(f7, f8, f9, f10);										assert(eq(vfoo4, f7, f8, f9, f10));

	float1 vbar1 = vfoo1.x;													assert(eq(vbar1, f1));
	float2 vbar2 = vfoo2.gr;												assert(eq(vbar2, f3, f2));
	float3 vbar3 = vfoo3.zyx;												assert(eq(vbar3, f6, f5, f4));
	float4 vbar4 = vfoo4.bgra;												assert(eq(vbar4, f9, f8, f7, f10));

	vbar1 = f11;															assert(eq(vbar1, f11));
	vbar2 = float2(f12, f13);												assert(eq(vbar2, f12, f13));
	vbar3 = float3(f14, f15, f16);											assert(eq(vbar3, f14, f15, f16));
	vbar4 = float4(f17, f18, f19, f20);										assert(eq(vbar4, f17, f18, f19, f20));

	float1 vbaz1 = float1(0.2f);											assert(eq(vbaz1, 0.2f));
	float2 vbaz2 = float2(0.3f, 0.7f);										assert(eq(vbaz2, 0.3f, 0.7f));
	float3 vbaz3 = float3(0.1f, 0.4f, 0.8f);								assert(eq(vbaz3, 0.1f, 0.4f, 0.8f));
	float4 vbaz4 = float4(0.0f, 0.2f, 0.6f, 1.0f);							assert(eq(vbaz4, 0.0f, 0.2f, 0.6f, 1.0f));

	float2 vfoo_mix_2_a	= float2(vfoo1, vbar1);								assert(eq(vfoo_mix_2_a, vfoo1, vbar1));
	float2 vfoo_mix_2_b	= float2(vfoo2.y, vbar1);							assert(eq(vfoo_mix_2_b, vfoo2.y, vbar1));
	float2 vfoo_mix_2_c	= float2(vfoo1, vbar1.x);							assert(eq(vfoo_mix_2_c, vfoo1, vbar1.x));
	float2 vfoo_mix_2_d	= float2(vfoo1.x, vbar2.y);							assert(eq(vfoo_mix_2_d, vfoo1.x, vbar2.y));

	float2 vfoo_mix_2_f_a = float2(vfoo1, f1);								assert(eq(vfoo_mix_2_f_a, vfoo1.x, f1));
	float2 vfoo_mix_2_f_b = float2(f2, vbar1);								assert(eq(vfoo_mix_2_f_b, f2, vbar1));
	float2 vfoo_mix_2_f_c = float2(vfoo2.y, f1);							assert(eq(vfoo_mix_2_f_c, vfoo2.y, f1));
	float2 vfoo_mix_2_f_d = float2(f2, vbar3.z);							assert(eq(vfoo_mix_2_f_d, f2, vbar3.z));
	float2 vfoo_mix_2_f_e = float2(f3, f4);									assert(eq(vfoo_mix_2_f_e, f3, f4));

	float3 vfoo_mix_3_a = float3(vfoo1, vbar1, vbaz1);						assert(eq(vfoo_mix_3_a, vfoo1.x, vbar1.x, vbaz1.x));
	float3 vfoo_mix_3_b = float3(vfoo2, vbar1);								assert(eq(vfoo_mix_3_b, vfoo2.x, vfoo2.y, vbar1.x));
	float3 vfoo_mix_3_c = float3(vbar1, vbar2);								assert(eq(vfoo_mix_3_c, vbar1.x, vbar2.x, vbar2.y));

	float3 vfoo_mix_3_d = float3(vfoo1, vbar1, vbaz1.x);					assert(eq(vfoo_mix_3_d, vfoo1.x, vbar1.x, vbaz1.x));
	float3 vfoo_mix_3_e = float3(vfoo1, vbar1.x, vbaz1);					assert(eq(vfoo_mix_3_e, vfoo1.x, vbar1.x, vbaz1.x));
	float3 vfoo_mix_3_f = float3(vfoo1.x, vbar1, vbaz1);					assert(eq(vfoo_mix_3_f, vfoo1.x, vbar1.x, vbaz1.x));

	float3 vfoo_mix_3_g = float3(vfoo1, vbar1.x, vbaz1.x);					assert(eq(vfoo_mix_3_g, vfoo1.x, vbar1.x, vbaz1.x));
	float3 vfoo_mix_3_h = float3(vfoo1.x, vbar1, vbaz1.x);					assert(eq(vfoo_mix_3_h, vfoo1.x, vbar1.x, vbaz1.x));
	float3 vfoo_mix_3_i = float3(vfoo1.x, vbar1.x, vbaz1);					assert(eq(vfoo_mix_3_i, vfoo1.x, vbar1.x, vbaz1.x));
	float3 vfoo_mix_3_j = float3(vfoo1.x, vbar1.x, vbaz1.x);				assert(eq(vfoo_mix_3_j, vfoo1.x, vbar1.x, vbaz1.x));
	
	float3 vfoo_mix_3_f_a = float3(vfoo1, vbar1, f1);						assert(eq(vfoo_mix_3_f_a, vfoo1.x, vbar1.x, f1));
	float3 vfoo_mix_3_f_b = float3(vfoo1, f1, vbaz1);						assert(eq(vfoo_mix_3_f_b, vfoo1.x, f1, vbaz1.x));
	float3 vfoo_mix_3_f_c = float3(f1, vbar1, vbaz1);						assert(eq(vfoo_mix_3_f_c, f1, vbar1.x, vbaz1.x));

	float3 vfoo_mix_3_f_d = float3(vfoo1, f1, f2);							assert(eq(vfoo_mix_3_f_d, vfoo1.x, f1, f2));
	float3 vfoo_mix_3_f_e = float3(f1, vbar1, f2);							assert(eq(vfoo_mix_3_f_e, f1, vbar1.x, f2));
	float3 vfoo_mix_3_f_f = float3(f1, f2, vbaz1);							assert(eq(vfoo_mix_3_f_f, f1, f2, vbaz1));

	float3 vfoo_mix_3_f_g = float3(vfoo1.x, f1, f2);						assert(eq(vfoo_mix_3_f_g, vfoo1.x, f1, f2));
	float3 vfoo_mix_3_f_h = float3(f1, vbar2.y, f2);						assert(eq(vfoo_mix_3_f_h, f1, vbar2.y, f2));
	float3 vfoo_mix_3_f_i = float3(f1, f2, vbaz3.z);						assert(eq(vfoo_mix_3_f_i, f1, f2, vbaz3.z));

	float3 vfoo_mix_3_f_j = float3(vfoo1.x, vbar2.y, f2);					assert(eq(vfoo_mix_3_f_j, vfoo1.x, vbar2.y, f2));
	float3 vfoo_mix_3_f_k = float3(f1, vbar2.y, vbaz3.x);					assert(eq(vfoo_mix_3_f_k, f1, vbar2.y, vbaz3.x));
	float3 vfoo_mix_3_f_l = float3(vfoo1.x, f2, vbaz3.z);					assert(eq(vfoo_mix_3_f_l, vfoo1.x, f2, vbaz3.z));

	float3 vfoo_mix_3_f_m = float3(vfoo2, f1);								assert(eq(vfoo_mix_3_f_m, vfoo2.x, vfoo2.y, f1));
	float3 vfoo_mix_3_f_n = float3(f2, vbar2);								assert(eq(vfoo_mix_3_f_n, f2, vbar2.x, vbar2.y));

	float3 vfoo_mix_3_f_o = float3(vfoo2.xy, f1);							assert(eq(vfoo_mix_3_f_o, vfoo2.x, vfoo2.y, f1));
	float3 vfoo_mix_3_f_p = float3(f2, vbar2.xy);							assert(eq(vfoo_mix_3_f_p, f2, vbar2.x, vbar2.y));

	float4 vfoo_mix_4_a = float4(vbaz1, vbaz2.x, vbaz3.x, 0.5f);			assert(eq(vfoo_mix_4_a, vbaz1.x, vbaz2.x, vbaz3.x, 0.5f));
	float4 vfoo_mix_4_b = float4(vbaz1, vbaz3);								assert(eq(vfoo_mix_4_b, vbaz1.x, vbaz3.x, vbaz3.y, vbaz3.z));
	float4 vfoo_mix_4_c = float4(vbaz3, vbaz1);								assert(eq(vfoo_mix_4_c, vbaz3.x, vbaz3.y, vbaz3.z, vbaz1.x));
	float4 vfoo_mix_4_d = float4(vbaz2, vbar2);								assert(eq(vfoo_mix_4_d, vbaz2.x, vbaz2.y, vbar2.x, vbar2.y));
	float4 vfoo_mix_4_e = float4(vbaz2, vbar1, vbaz1);						assert(eq(vfoo_mix_4_e, vbaz2.x, vbaz2.y, vbar1.x, vbaz1.x));
	float4 vfoo_mix_4_f = float4(vbar1, vbaz2, vbaz1);						assert(eq(vfoo_mix_4_f, vbar1.x, vbaz2.x, vbaz2.y, vbaz1.x));
	float4 vfoo_mix_4_g = float4(vbar1, vbaz1, vbaz2);						assert(eq(vfoo_mix_4_g, vbar1.x, vbaz1.x, vbaz2.x, vbaz2.y));

	float4 vfoo_mix_4_f_a = float4(f1, vfoo1, vbar1, vbaz1);				assert(eq(vfoo_mix_4_f_a, f1, vfoo1, vbar1, vbaz1));
	float4 vfoo_mix_4_f_b = float4(f2, f3, vbar1, vbaz1);					assert(eq(vfoo_mix_4_f_b, f2, f3, vbar1, vbaz1));
	float4 vfoo_mix_4_f_c = float4(f4, f5, f6, vbaz1);						assert(eq(vfoo_mix_4_f_c, f4, f5, f6, vbaz1));

	float4 vfoo_mix_4_f_d = float4(f1, vfoo1.x, vbar2.y, vbaz3.z);			assert(eq(vfoo_mix_4_f_d, f1, vfoo1, vbar2.y, vbaz3.z));
	float4 vfoo_mix_4_f_e = float4(f2, f3, vbar2.y, vbaz3.z);				assert(eq(vfoo_mix_4_f_e, f2, f3, vbar2.y, vbaz3.z));
	float4 vfoo_mix_4_f_f = float4(f4, f5, f6, vbaz3.z);					assert(eq(vfoo_mix_4_f_f, f4, f5, f6, vbaz3.z));

	float4 vfoo_mix_4_f_g = float4(f1, vfoo1, vbar2.y, vbaz3.z);			assert(eq(vfoo_mix_4_f_g, f1, vfoo1, vbar2.y, vbaz3.z));
	float4 vfoo_mix_4_f_h = float4(f2, vfoo1, vbar1, vbaz3.z);				assert(eq(vfoo_mix_4_f_h, f2, vfoo1, vbar1, vbaz3.z));
	float4 vfoo_mix_4_f_i = float4(f3, vfoo1.x, vbar1, vbaz3.z);			assert(eq(vfoo_mix_4_f_i, f3, vfoo1.x, vbar1, vbaz3.z));
	float4 vfoo_mix_4_f_j = float4(f4, vfoo1.x, vbar2.y, vbaz1);			assert(eq(vfoo_mix_4_f_j, f4, vfoo1.x, vbar2.y, vbaz1));

	float4 vfoo_mix_4_f_k = float4(f1, f2, vbar1, vbaz3.z);					assert(eq(vfoo_mix_4_f_k, f1, f2, vbar1, vbaz3.z));
	float4 vfoo_mix_4_f_l = float4(f3, f4, vbar2.y, vbaz1);					assert(eq(vfoo_mix_4_f_l, f3, f4, vbar2.y, vbaz1));

	// Assignment and swizzle

	float1 vassign1 = vfoo1.x;												assert(eq(vassign1.x, vfoo1.x));
	vassign1 = vfoo1.r;														assert(eq(vassign1.x, vfoo1.x));
	vassign1.r = vfoo1;														assert(eq(vassign1.x, vfoo1.x));
	vassign1.r = vfoo1.r;													assert(eq(vassign1.x, vfoo1.x));

	float2 vassign2 = vfoo2.yx;												assert(eq(vassign2, vfoo2.y, vfoo2.x));
	vassign2 = vfoo2.yy;													assert(eq(vassign2, vfoo2.y, vfoo2.y));
	vassign2.rg = vfoo2;													assert(eq(vassign2, vfoo2.x, vfoo2.y));
	vassign2.rg = vfoo2.gr;													assert(eq(vassign2, vfoo2.y, vfoo2.x));

	float3 vassign3 = vfoo3.yxz;											assert(eq(vassign3, vfoo3.y, vfoo3.x, vfoo3.z));
	vassign3 = vfoo3.yyx;													assert(eq(vassign3, vfoo3.y, vfoo3.y, vfoo3.x));
	vassign3.rbg = vfoo3;													assert(eq(vassign3, vfoo3.x, vfoo3.z, vfoo3.y));
	vassign3.rgb = vfoo3.grr;												assert(eq(vassign3, vfoo3.y, vfoo3.x, vfoo3.x));

	float4 vassign4 = vfoo4.yxzw;											assert(eq(vassign4, vfoo4.y, vfoo4.x, vfoo4.z, vfoo4.w));
	vassign4 = vfoo4.yyxx;													assert(eq(vassign4, vfoo4.y, vfoo4.y, vfoo4.x, vfoo4.x));
	vassign4.bgra = vfoo4;													assert(eq(vassign4, vfoo4.b, vfoo4.g, vfoo4.r, vfoo4.a));
	vassign4.rgba = vfoo4.grba;												assert(eq(vassign4, vfoo4.g, vfoo4.r, vfoo4.b, vfoo4.a));

	float2 vneg_swiz_2 = -vfoo2.yx;											//assert(vassign2.x == (float)vfoo2.y && vassign2.y == (float)vfoo2.x);

	// Addition

	float1 vadd1 = vfoo1 + vbar1;											assert(eq(vadd1, (float)vfoo1.x + (float)vbar1.x));
	float2 vadd2 = vfoo2 + vbar2;											assert(eq(vadd2, (float)vfoo2.x + (float)vbar2.x, (float)vfoo2.y + (float)vbar2.y));
	float3 vadd3 = vfoo3 + vbar3;											assert(eq(vadd3, (float)vfoo3.x + (float)vbar3.x, (float)vfoo3.y + (float)vbar3.y, (float)vfoo3.z + (float)vbar3.z));
	float4 vadd4 = vfoo4 + vbar4;											assert(eq(vadd4, (float)vfoo4.x + (float)vbar4.x, (float)vfoo4.y + (float)vbar4.y, (float)vfoo4.z + (float)vbar4.z, (float)vfoo4.w + (float)vbar4.w));

	float1 vadd_f_1 = vfoo1 + 0.1f;											assert(eq(vadd_f_1, (float)vfoo1.x + 0.1f));
	float2 vadd_f_2 = vfoo2 + 0.2f;											assert(eq(vadd_f_2, (float)vfoo2.x + 0.2f, (float)vfoo2.y + 0.2f));
	float3 vadd_f_3 = vfoo3 + 0.3f;											assert(eq(vadd_f_3, (float)vfoo3.x + 0.3f, (float)vfoo3.y + 0.3f, (float)vfoo3.z + 0.3f));
	float4 vadd_f_4 = vfoo4 + 0.4f;											assert(eq(vadd_f_4, (float)vfoo4.x + 0.4f, (float)vfoo4.y + 0.4f, (float)vfoo4.z + 0.4f, (float)vfoo4.w + 0.4f));

	vadd_f_1 += 0.1f;														assert(eq(vadd_f_1, (float)vfoo1.x + 0.1f + 0.1f));
	vadd_f_2 += 0.2f;														assert(eq(vadd_f_2, (float)vfoo2.x + 0.2f + 0.2f, (float)vfoo2.y + 0.2f + 0.2f));
	vadd_f_3 += 0.3f;														assert(eq(vadd_f_3, (float)vfoo3.x + 0.3f + 0.3f, (float)vfoo3.y + 0.3f + 0.3f, (float)vfoo3.z + 0.3f + 0.3f));
	vadd_f_4 += 0.4f;														assert(eq(vadd_f_4, (float)vfoo4.x + 0.4f + 0.4f, (float)vfoo4.y + 0.4f + 0.4f, (float)vfoo4.z + 0.4f + 0.4f, (float)vfoo4.w + 0.4f + 0.4f));

	float1 vadd_swiz_a_1 = vfoo1 + vbar1.x;									assert(eq(vadd_swiz_a_1, (float)vfoo1 + (float)vbar1.x));
	float1 vadd_swiz_b_1 = vfoo1.r + vbar1.x;								assert(eq(vadd_swiz_b_1, (float)vfoo1.r + (float)vbar1.x));
	float1 vadd_swiz_c_1 = vfoo1.r + vbar1;									assert(eq(vadd_swiz_c_1, (float)vfoo1.r + (float)vbar1));

	float2 vadd_swiz_a_2 = vfoo2 + vbar2.yx;								assert(eq(vadd_swiz_a_2, (float)vfoo2.x + (float)vbar2.y, (float)vfoo2.y + (float)vbar2.x));
	float2 vadd_swiz_b_2 = vfoo2.gr + vbar2.yx;								assert(eq(vadd_swiz_b_2, (float)vfoo2.g + (float)vbar2.y, (float)vfoo2.r + (float)vbar2.x));
	float2 vadd_swiz_c_2 = vfoo2.rg + vbar2;								assert(eq(vadd_swiz_c_2, (float)vfoo2.r + (float)vbar2.x, (float)vfoo2.g + (float)vbar2.y));

	float3 vadd_swiz_a_3 = vfoo3 + vbar3.yxz;								assert(eq(vadd_swiz_a_3, (float)vfoo3.x + (float)vbar3.y, (float)vfoo3.y + (float)vbar3.x, (float)vfoo3.z + (float)vbar3.z));
	float3 vadd_swiz_b_3 = vfoo3.bgr + vbar3.xyz;							assert(eq(vadd_swiz_b_3, (float)vfoo3.b + (float)vbar3.x, (float)vfoo3.g + (float)vbar3.y, (float)vfoo3.r + (float)vbar3.z));
	float3 vadd_swiz_c_3 = vfoo3.bgr + vbar3;								assert(eq(vadd_swiz_c_3, (float)vfoo3.b + (float)vbar3.x, (float)vfoo3.g + (float)vbar3.y, (float)vfoo3.r + (float)vbar3.z));

	float4 vadd_swiz_a_4 = vfoo4 + vbar4.yxzw;								assert(eq(vadd_swiz_a_4, (float)vfoo4.x + (float)vbar4.y, (float)vfoo4.y + (float)vbar4.x, (float)vfoo4.z + (float)vbar4.z, (float)vfoo4.w + (float)vbar4.w));
	float4 vadd_swiz_b_4 = vfoo4.bgra + vbar4.yxzw;							assert(eq(vadd_swiz_b_4, (float)vfoo4.b + (float)vbar4.y, (float)vfoo4.g + (float)vbar4.x, (float)vfoo4.r + (float)vbar4.z, (float)vfoo4.a + (float)vbar4.w));
	float4 vadd_swiz_c_4 = vfoo4.bgra + vbar4;								assert(eq(vadd_swiz_c_4, (float)vfoo4.b + (float)vbar4.x, (float)vfoo4.g + (float)vbar4.y, (float)vfoo4.r + (float)vbar4.z, (float)vfoo4.a + (float)vbar4.w));

	vadd_swiz_a_1 += vfoo1;
	vadd_swiz_b_1 += vfoo1.x;
	vadd_swiz_c_1.x += vfoo1;
	vadd_swiz_c_1.r += vfoo1.r;

	vadd_swiz_a_2 += vfoo2;
	vadd_swiz_b_2 += vfoo2.xy;
	vadd_swiz_c_2.xy += vfoo2;
	vadd_swiz_c_2.gr += vfoo2.rg;

	// Subtraction

	float1 vsub1 = vfoo1 - vbar1;											assert(eq(vsub1, (float)vfoo1.x - (float)vbar1.x));
	float2 vsub2 = vfoo2 - vbar2;											assert(eq(vsub2, (float)vfoo2.x - (float)vbar2.x, (float)vfoo2.y - (float)vbar2.y));
	float3 vsub3 = vfoo3 - vbar3;											assert(eq(vsub3, (float)vfoo3.x - (float)vbar3.x, (float)vfoo3.y - (float)vbar3.y, (float)vfoo3.z - (float)vbar3.z));
	float4 vsub4 = vfoo4 - vbar4;											assert(eq(vsub4, (float)vfoo4.x - (float)vbar4.x, (float)vfoo4.y - (float)vbar4.y, (float)vfoo4.z - (float)vbar4.z, (float)vfoo4.w - (float)vbar4.w));

	float1 vsub_f_1 = vfoo1 - 0.1f;											assert(eq(vsub_f_1, (float)vfoo1.x - 0.1f));
	float2 vsub_f_2 = vfoo2 - 0.2f;											assert(eq(vsub_f_2, (float)vfoo2.x - 0.2f,(float)vfoo2.y - 0.2f));
	float3 vsub_f_3 = vfoo3 - 0.3f;											assert(eq(vsub_f_3, (float)vfoo3.x - 0.3f,(float)vfoo3.y - 0.3f, (float)vfoo3.z - 0.3f));
	float4 vsub_f_4 = vfoo4 - 0.4f;											assert(eq(vsub_f_4, (float)vfoo4.x - 0.4f,(float)vfoo4.y - 0.4f, (float)vfoo4.z - 0.4f, (float)vfoo4.w - 0.4f));

	vsub_f_1 -= 0.1f;														assert(eq(vsub_f_1, (float)vfoo1.x - 0.1f - 0.1f));
	vsub_f_2 -= 0.2f;														assert(eq(vsub_f_2, (float)vfoo2.x - 0.2f - 0.2f, (float)vfoo2.y - 0.2f - 0.2f));
	vsub_f_3 -= 0.3f;														assert(eq(vsub_f_3, (float)vfoo3.x - 0.3f - 0.3f, (float)vfoo3.y - 0.3f - 0.3f, (float)vfoo3.z - 0.3f - 0.3f));
	vsub_f_4 -= 0.4f;														assert(eq(vsub_f_4, (float)vfoo4.x - 0.4f - 0.4f, (float)vfoo4.y - 0.4f - 0.4f, (float)vfoo4.z - 0.4f - 0.4f, (float)vfoo4.w - 0.4f - 0.4f));

	float1 vsub_swiz_a_1 = vfoo1 - vbar1.x;									assert(eq(vsub_swiz_a_1, (float)vfoo1 - (float)vbar1.x));
	float1 vsub_swiz_b_1 = vfoo1.r - vbar1.x;								assert(eq(vsub_swiz_b_1, (float)vfoo1.r - (float)vbar1.x));
	float1 vsub_swiz_c_1 = vfoo1.r - vbar1;									assert(eq(vsub_swiz_c_1, (float)vfoo1.r - (float)vbar1));
	vsub_swiz_c_1.r = vfoo4.r - vbar4.r;

	float2 vsub_swiz_a_2 = vfoo2 - vbar2.yx;								assert(eq(vsub_swiz_a_2, (float)vfoo2.x - (float)vbar2.y, (float)vfoo2.y - (float)vbar2.x));
	float2 vsub_swiz_b_2 = vfoo2.gr - vbar2.yx;								assert(eq(vsub_swiz_b_2, (float)vfoo2.g - (float)vbar2.y, (float)vfoo2.r - (float)vbar2.x));
	float2 vsub_swiz_c_2 = vfoo2.rg - vbar2;								assert(eq(vsub_swiz_c_2, (float)vfoo2.r - (float)vbar2.x, (float)vfoo2.g - (float)vbar2.y));
	vsub_swiz_c_2.gr = vfoo4.rg - vbar4.gr;

	float3 vsub_swiz_a_3 = vfoo3 - vbar3.yxz;								assert(eq(vsub_swiz_a_3, (float)vfoo3.x - (float)vbar3.y, (float)vfoo3.y - (float)vbar3.x, (float)vfoo3.z - (float)vbar3.z));
	float3 vsub_swiz_b_3 = vfoo3.bgr - vbar3.xyz;							assert(eq(vsub_swiz_b_3, (float)vfoo3.b - (float)vbar3.x, (float)vfoo3.g - (float)vbar3.y, (float)vfoo3.r - (float)vbar3.z));
	float3 vsub_swiz_c_3 = vfoo3.bgr - vbar3;								assert(eq(vsub_swiz_c_3, (float)vfoo3.b - (float)vbar3.x, (float)vfoo3.g - (float)vbar3.y, (float)vfoo3.r - (float)vbar3.z));
	vsub_swiz_c_3.bgr = vfoo4.grb - vbar4.gbr;

	float4 vsub_swiz_a_4 = vfoo4 - vbar4.yxzw;								assert(eq(vsub_swiz_a_4, (float)vfoo4.x - (float)vbar4.y, (float)vfoo4.y - (float)vbar4.x, (float)vfoo4.z - (float)vbar4.z, (float)vfoo4.w - (float)vbar4.w));
	float4 vsub_swiz_b_4 = vfoo4.bgra - vbar4.yxzw;							assert(eq(vsub_swiz_b_4, (float)vfoo4.b - (float)vbar4.y, (float)vfoo4.g - (float)vbar4.x, (float)vfoo4.r - (float)vbar4.z, (float)vfoo4.a - (float)vbar4.w));
	float4 vsub_swiz_c_4 = vfoo4.bgra - vbar4;								assert(eq(vsub_swiz_c_4, (float)vfoo4.b - (float)vbar4.x, (float)vfoo4.g - (float)vbar4.y, (float)vfoo4.r - (float)vbar4.z, (float)vfoo4.a - (float)vbar4.w));
	vsub_swiz_c_4.bgra = vfoo4.argb - vbar4.ggbr;

	vadd_swiz_a_1 -= vfoo1;
	vadd_swiz_b_1 -= vfoo1.x;
	vadd_swiz_c_1.x -= vfoo1;
	vadd_swiz_c_1.r -= vfoo1.r;

	vsub_swiz_a_2 -= vfoo2;
	vsub_swiz_b_2 -= vfoo2.xy;
	vsub_swiz_c_2.xy -= vfoo2;
	vsub_swiz_c_2.gr -= vfoo2.rg;

	// Multiplication

	float1 vmul1 = vfoo1 * vbar1;											assert(eq(vmul1, (float)vfoo1.x * (float)vbar1.x));
	float2 vmul2 = vfoo2 * vbar2;											assert(eq(vmul2, (float)vfoo2.x * (float)vbar2.x, (float)vfoo2.y * (float)vbar2.y));
	float3 vmul3 = vfoo3 * vbar3;											assert(eq(vmul3, (float)vfoo3.x * (float)vbar3.x, (float)vfoo3.y * (float)vbar3.y, (float)vfoo3.z * (float)vbar3.z));
	float4 vmul4 = vfoo4 * vbar4;											assert(eq(vmul4, (float)vfoo4.x * (float)vbar4.x, (float)vfoo4.y * (float)vbar4.y, (float)vfoo4.z * (float)vbar4.z, (float)vfoo4.w * (float)vbar4.w));

	float1 vmul_f_1 = vfoo1 * 0.1f;											assert(eq(vmul_f_1, (float)vfoo1.x * 0.1f));
	float2 vmul_f_2 = vfoo2 * 0.2f;											assert(eq(vmul_f_2, (float)vfoo2.x * 0.2f, (float)vfoo2.y * 0.2f));
	float3 vmul_f_3 = vfoo3 * 0.3f;											assert(eq(vmul_f_3, (float)vfoo3.x * 0.3f, (float)vfoo3.y * 0.3f, (float)vfoo3.z * 0.3f));
	float4 vmul_f_4 = vfoo4 * 0.4f;											assert(eq(vmul_f_4, (float)vfoo4.x * 0.4f, (float)vfoo4.y * 0.4f, (float)vfoo4.z * 0.4f, (float)vfoo4.w * 0.4f));

	vmul_f_1 *= 0.1f;														assert(eq(vmul_f_1, (float)vfoo1.x * 0.1f * 0.1f));
	vmul_f_2 *= 0.2f;														assert(eq(vmul_f_2, (float)vfoo2.x * 0.2f * 0.2f, (float)vfoo2.y * 0.2f * 0.2f));
	vmul_f_3 *= 0.3f;														assert(eq(vmul_f_3, (float)vfoo3.x * 0.3f * 0.3f, (float)vfoo3.y * 0.3f * 0.3f, (float)vfoo3.z * 0.3f * 0.3f));
	vmul_f_4 *= 0.4f;														assert(eq(vmul_f_4, (float)vfoo4.x * 0.4f * 0.4f, (float)vfoo4.y * 0.4f * 0.4f, (float)vfoo4.z * 0.4f * 0.4f, (float)vfoo4.w * 0.4f * 0.4f));

	float1 vmul_swiz_a_1 = vfoo1 * vbar1.x;
	float1 vmul_swiz_b_1 = vfoo1.r * vbar1.x;
	float1 vmul_swiz_c_1 = vfoo1.r * vbar1;

	float2 vmul_swiz_a_2 = vfoo2 * vbar2.yx;
	float2 vmul_swiz_b_2 = vfoo2.gr * vbar2.yx;
	float2 vmul_swiz_c_2 = vfoo2.rg * vbar2;

	float3 vmul_swiz_a_3 = vfoo3 * vbar3.yxz;
	float3 vmul_swiz_b_3 = vfoo3.rgb * vbar3.xyz;
	float3 vmul_swiz_c_3 = vfoo3.bgr * vbar3;

	float4 vmul_swiz_a_4 = vfoo4 * vbar4.yxzw;
	float4 vmul_swiz_b_4 = vfoo4.bgra * vbar4.yxzw;
	float4 vmul_swiz_c_4 = vfoo4.bgra * vbar4;

	vmul_swiz_a_2 *= vfoo2;
	vmul_swiz_b_2 *= vfoo2.xy;
	vmul_swiz_c_2.xy *= vfoo2;
	vmul_swiz_c_2.gr *= vfoo2.rg;

	// Division

	float tolDiv = 1e-2f;

	float1 vdiv1 = vfoo1 / vbar1;							assert(eq(vdiv1, div(vfoo1.x, vbar1.x), tolDiv));
	float2 vdiv2 = vfoo2 / vbar2;							assert(eq(vdiv2, div(vfoo2.x, vbar2.x), div(vfoo2.y, vbar2.y), tolDiv));
	float3 vdiv3 = vfoo3 / vbar3;							assert(eq(vdiv3, div(vfoo3.x, vbar3.x), div(vfoo3.y, vbar3.y), div(vfoo3.z, vbar3.z), tolDiv));
	float4 vdiv4 = vfoo4 / vbar4;							assert(eq(vdiv4, div(vfoo4.x, vbar4.x), div(vfoo4.y, vbar4.y), div(vfoo4.z, vbar4.z), div(vfoo4.w, vbar4.w), tolDiv));

	float1 vdiv_f_1 = vfoo1 / 0.1f;							assert(eq(vdiv_f_1, div(vfoo1.x, 0.1f), tolDiv));
	float2 vdiv_f_2 = vfoo2 / 0.2f;							assert(eq(vdiv_f_2, div(vfoo2.x, 0.2f), div(vfoo2.y, 0.2f), tolDiv));
	float3 vdiv_f_3 = vfoo3 / 0.3f;							assert(eq(vdiv_f_3, div(vfoo3.x, 0.3f), div(vfoo3.y, 0.3f), div(vfoo3.z, 0.3f), tolDiv));
	float4 vdiv_f_4 = vfoo4 / 0.4f;							assert(eq(vdiv_f_4, div(vfoo4.x, 0.4f), div(vfoo4.y, 0.4f), div(vfoo4.z, 0.4f), div(vfoo4.w, 0.4f), tolDiv));

	vdiv_f_1 /= 0.1f;										assert(eq(vdiv_f_1, div(div(vfoo1.x, 0.1f), 0.1f), tolDiv));
	vdiv_f_2 /= 0.2f;										assert(eq(vdiv_f_2, div(div(vfoo2.x, 0.2f), 0.2f), div(div(vfoo2.y, 0.2f), 0.2f), tolDiv));
	vdiv_f_3 /= 0.3f;										assert(eq(vdiv_f_3, div(div(vfoo3.x, 0.3f), 0.3f), div(div(vfoo3.y, 0.3f), 0.3f), div(div(vfoo3.z, 0.3f), 0.3f), tolDiv));
	vdiv_f_4 /= 0.4f;										assert(eq(vdiv_f_4, div(div(vfoo4.x, 0.4f), 0.4f), div(div(vfoo4.y, 0.4f), 0.4f), div(div(vfoo4.z, 0.4f), 0.4f), div(div(vfoo4.w, 0.4f), 0.4f), tolDiv));

	float1 vdiv_swiz_a_1 = vfoo1 / vbar1.x;
	float1 vdiv_swiz_b_1 = vfoo1.r / vbar1.x;
	float1 vdiv_swiz_c_1 = vfoo1.r / vbar1;

	float2 vdiv_swiz_a_2 = vfoo2 / vbar2.yx;
	float2 vdiv_swiz_b_2 = vfoo2.gr / vbar2.yx;
	float2 vdiv_swiz_c_2 = vfoo2.rg / vbar2;

	float3 vdiv_swiz_a_3 = vfoo3 / vbar3.yxz;
	float3 vdiv_swiz_b_3 = vfoo3.rgb / vbar3.xyz;
	float3 vdiv_swiz_c_3 = vfoo3.bgr / vbar3;

	float4 vdiv_swiz_a_4 = vfoo4 / vbar4.yxzw;
	float4 vdiv_swiz_b_4 = vfoo4.bgra / vbar4.yxzw;
	float4 vdiv_swiz_c_4 = vfoo4.bgra / vbar4;

	vdiv_swiz_a_2 /= vfoo2;
	vdiv_swiz_b_2 /= vfoo2.xy;
	vdiv_swiz_c_2.xy /= vfoo2;
	vdiv_swiz_c_2.gr /= vfoo2.rg;

	// Comparison

	float1 vgt1 = vfoo1 > vbar1;											assert(vgt1.x == (float)vfoo1.x > (float)vbar1.x);
	float2 vgt2 = vfoo2 > vbar2;											assert(vgt2.x == (float)vfoo2.x > (float)vbar2.x && vgt2.y == (float)vfoo2.y > (float)vbar2.y);
	float3 vgt3 = vfoo3 > vbar3;											assert(vgt3.x == (float)vfoo3.x > (float)vbar3.x && vgt3.y == (float)vfoo3.y > (float)vbar3.y && vgt3.z == (float)vfoo3.z > (float)vbar3.z);
	float4 vgt4 = vfoo4 > vbar4;											assert(vgt4.x == (float)vfoo4.x > (float)vbar4.x && vgt4.y == (float)vfoo4.y > (float)vbar4.y && vgt4.z == (float)vfoo4.z > (float)vbar4.z && vgt4.w == (float)vfoo4.w > (float)vbar4.w);
	
	float1 vlt1 = vfoo1 < vbar1;											assert(vlt1.x == (float)vfoo1.x < (float)vbar1.x);
	float2 vlt2 = vfoo2 < vbar2;											assert(vlt2.x == (float)vfoo2.x < (float)vbar2.x && vlt2.y == (float)vfoo2.y < (float)vbar2.y);
	float3 vlt3 = vfoo3 < vbar3;											assert(vlt3.x == (float)vfoo3.x < (float)vbar3.x && vlt3.y == (float)vfoo3.y < (float)vbar3.y && vlt3.z == (float)vfoo3.z < (float)vbar3.z);
	float4 vlt4 = vfoo4 < vbar4;											assert(vlt4.x == (float)vfoo4.x < (float)vbar4.x && vlt4.y == (float)vfoo4.y < (float)vbar4.y && vlt4.z == (float)vfoo4.z < (float)vbar4.z && vlt4.w == (float)vfoo4.w < (float)vbar4.w);

	float1 vge1 = vfoo1 >= vbar1;											assert(vge1.x == (float)vfoo1.x >= (float)vbar1.x);
	float2 vge2 = vfoo2 >= vbar2;											assert(vge2.x == (float)vfoo2.x >= (float)vbar2.x && vge2.y == (float)vfoo2.y >= (float)vbar2.y);
	float3 vge3 = vfoo3 >= vbar3;											assert(vge3.x == (float)vfoo3.x >= (float)vbar3.x && vge3.y == (float)vfoo3.y >= (float)vbar3.y && vge3.z == (float)vfoo3.z >= (float)vbar3.z);
	float4 vge4 = vfoo4 >= vbar4;											assert(vge4.x == (float)vfoo4.x >= (float)vbar4.x && vge4.y == (float)vfoo4.y >= (float)vbar4.y && vge4.z == (float)vfoo4.z >= (float)vbar4.z && vge4.w == (float)vfoo4.w >= (float)vbar4.w);

	float1 vle1 = vfoo1 <= vbar1;											assert(vle1.x == (float)vfoo1.x <= (float)vbar1.x);
	float2 vle2 = vfoo2 <= vbar2;											assert(vle2.x == (float)vfoo2.x <= (float)vbar2.x && vle2.y == (float)vfoo2.y <= (float)vbar2.y);
	float3 vle3 = vfoo3 <= vbar3;											assert(vle3.x == (float)vfoo3.x <= (float)vbar3.x && vle3.y == (float)vfoo3.y <= (float)vbar3.y && vle3.z == (float)vfoo3.z <= (float)vbar3.z);
	float4 vle4 = vfoo4 <= vbar4;											assert(vle4.x == (float)vfoo4.x <= (float)vbar4.x && vle4.y == (float)vfoo4.y <= (float)vbar4.y && vle4.z == (float)vfoo4.z <= (float)vbar4.z && vle4.w == (float)vfoo4.w <= (float)vbar4.w);

	float1 veq1 = vfoo1 == vbar1;											assert(veq1.x == ((float)vfoo1.x == (float)vbar1.x));
	float2 veq2 = vfoo2 == vbar2;											assert(veq2.x == ((float)vfoo2.x == (float)vbar2.x) && veq2.y == ((float)vfoo2.y == (float)vbar2.y));
	float3 veq3 = vfoo3 == vbar3;											assert(veq3.x == ((float)vfoo3.x == (float)vbar3.x) && veq3.y == ((float)vfoo3.y == (float)vbar3.y) && veq3.z == ((float)vfoo3.z == (float)vbar3.z));
	float4 veq4 = vfoo4 == vbar4;											assert(veq4.x == ((float)vfoo4.x == (float)vbar4.x) && veq4.y == ((float)vfoo4.y == (float)vbar4.y) && veq4.z == ((float)vfoo4.z == (float)vbar4.z) && veq4.w == ((float)vfoo4.w == (float)vbar4.w));

	float1 vneq1 = vfoo1 != vbar1;											assert(vneq1.x == (float)vfoo1.x != (float)vbar1.x);
	float2 vneq2 = vfoo2 != vbar2;											assert(vneq2.x == (float)vfoo2.x != (float)vbar2.x && vneq2.y == (float)vfoo2.y != (float)vbar2.y);
	float3 vneq3 = vfoo3 != vbar3;											assert(vneq3.x == (float)vfoo3.x != (float)vbar3.x && vneq3.y == (float)vfoo3.y != (float)vbar3.y && vneq3.z == (float)vfoo3.z != (float)vbar3.z);
	float4 vneq4 = vfoo4 != vbar4;											assert(vneq4.x == (float)vfoo4.x != (float)vbar4.x && vneq4.y == (float)vfoo4.y != (float)vbar4.y && vneq4.z == (float)vfoo4.z != (float)vbar4.z && vneq4.w == (float)vfoo4.w != (float)vbar4.w);

	vfoo1 = -vbar1.r;														assert(eq(vfoo1, -vbar1.r));
	vfoo2 = -vbar2.gr;														assert(eq(vfoo2, (float)-vbar2.g, (float)-vbar2.r));
	vfoo3 = -vbar3.bgg;														assert(eq(vfoo3, (float)-vbar3.b, (float)-vbar3.g, (float)-vbar3.g));
	vfoo4 = -vbar4.rbgr;													assert(eq(vfoo4, (float)-vbar4.r, (float)-vbar4.b, (float)-vbar4.g, (float)-vbar4.r));

	using std::abs;

	float1 vabs1 = abs(vfoo1);												assert(eq(vabs1, abs((float)vfoo1.x)));
	float2 vabs2 = abs(vfoo2);												assert(eq(vabs2, abs((float)vfoo2.x), abs((float)vfoo2.y)));
	float3 vabs3 = abs(vfoo3);												assert(eq(vabs3, abs((float)vfoo3.x), abs((float)vfoo3.y), abs((float)vfoo3.z)));
	float4 vabs4 = abs(vfoo4);												assert(eq(vabs4, abs((float)vfoo4.x), abs((float)vfoo4.y), abs((float)vfoo4.z), abs((float)vfoo4.w)));

	vfoo1 = abs(-vfoo1);													assert(eq(vabs1, abs((float)-vfoo1)));
	vfoo2 = abs(-vfoo2);													assert(eq(vabs2, abs((float)-vfoo2.x), abs((float)-vfoo2.y)));
	vfoo3 = abs(-vfoo3);													assert(eq(vabs3, abs((float)-vfoo3.x), abs((float)-vfoo3.y), abs((float)-vfoo3.z)));
	vfoo4 = abs(-vfoo4);													assert(eq(vabs4, abs((float)-vfoo4.x), abs((float)-vfoo4.y), abs((float)-vfoo4.z), abs((float)-vfoo4.w)));

	float1 vabs_swiz_1 = abs(vfoo1.r);										assert(eq(vabs_swiz_1, abs((float)vfoo1.x)));
	float2 vabs_swiz_2 = abs(vfoo2.yx);										assert(eq(vabs_swiz_2, abs((float)vfoo2.g), abs((float)vfoo2.r)));
	float3 vabs_swiz_3 = abs(vfoo3.bgr);									assert(eq(vabs_swiz_3, abs((float)vfoo3.b), abs((float)vfoo3.g), abs((float)vfoo3.r)));
	float4 vabs_swiz_4 = abs(vfoo4.wwww);									assert(eq(vabs_swiz_4, abs((float)vfoo4.a), abs((float)vfoo4.a), abs((float)vfoo4.a), abs((float)vfoo4.a)));

	float1 vacos1 = acos(vfoo1);
	float2 vacos2 = acos(vfoo2);
	float3 vacos3 = acos(vfoo3);
	float4 vacos4 = acos(vfoo4);

	float1 vacos_swiz_1 = acos(vfoo1.r);
	float2 vacos_swiz_2 = acos(vfoo2.yx);
	float3 vacos_swiz_3 = acos(vfoo3.bgr);
	float4 vacos_swiz_4 = acos(vfoo4.wwww);

	float1 vall1 = all(vfoo1);
	float2 vall2 = all(vfoo2);
	float3 vall3 = all(vfoo3);
	float4 vall4 = all(vfoo4);

	float1 vall_swiz_1 = all(vfoo1.r);
	float2 vall_swiz_2 = all(vfoo2.yx);
	float3 vall_swiz_3 = all(vfoo3.bgr);
	float4 vall_swiz_4 = all(vfoo4.wwww);

	float1 vany1 = any(vfoo1);
	float2 vany2 = any(vfoo2);
	float3 vany3 = any(vfoo3);
	float4 vany4 = any(vfoo4);

	float1 vany_swiz_1 = any(vfoo1.r);
	float2 vany_swiz_2 = any(vfoo2.yx);
	float3 vany_swiz_3 = any(vfoo3.bgr);
	float4 vany_swiz_4 = any(vfoo4.wwww);

	float1 vasin1 = asin(vfoo1);
	float2 vasin2 = asin(vfoo2);
	float3 vasin3 = asin(vfoo3);
	float4 vasin4 = asin(vfoo4);

	float1 vasin_swiz_1 = asin(vfoo1.r);
	float2 vasin_swiz_2 = asin(vfoo2.yx);
	float3 vasin_swiz_3 = asin(vfoo3.bgr);
	float4 vasin_swiz_4 = asin(vfoo4.wwww);

	float1 vatan1 = atan(vfoo1);
	float2 vatan2 = atan(vfoo2);
	float3 vatan3 = atan(vfoo3);
	float4 vatan4 = atan(vfoo4);

	float1 vatan_swiz_1 = atan(vfoo1.r);
	float2 vatan_swiz_2 = atan(vfoo2.yx);
	float3 vatan_swiz_3 = atan(vfoo3.bgr);
	float4 vatan_swiz_4 = atan(vfoo4.wwww);

	float1 vceil1 = ceil(vfoo1);
	float2 vceil2 = ceil(vfoo2);
	float3 vceil3 = ceil(vfoo3);
	float4 vceil4 = ceil(vfoo4);

	float1 vceil_swiz_1 = ceil(vfoo1.r);
	float2 vceil_swiz_2 = ceil(vfoo2.xx);
	float3 vceil_swiz_3 = ceil(vfoo3.rrg);
	float4 vceil_swiz_4 = ceil(vfoo4.yzwx);

	float1 vclamp1 = clamp(vfoo1, vbar1, vbaz1);
	float2 vclamp2 = clamp(vfoo2, vbar2, vbaz2);
	float3 vclamp3 = clamp(vfoo3, vbar3, vbaz3);
	float4 vclamp4 = clamp(vfoo4, vbar4, vbaz4);

	float1 vclamp_swiz_1 = clamp(vfoo1.r, vbar1, vbaz1);
	float2 vclamp_swiz_2 = clamp(vfoo2.yx, vbar2, vbaz2);
	float3 vclamp_swiz_3 = clamp(vfoo3.xxy, vbar3, vbaz3);
	float4 vclamp_swiz_4 = clamp(vfoo4.wwxy, vbar4, vbaz4);

	float1 vcos1 = cos(vfoo1);
	float2 vcos2 = cos(vfoo2);
	float3 vcos3 = cos(vfoo3);
	float4 vcos4 = cos(vfoo4);

	float1 vcos_swiz_1 = cos(vfoo1.x);
	float2 vcos_swiz_2 = cos(vfoo2.yy);
	float3 vcos_swiz_3 = cos(vfoo3.rrg);
	float4 vcos_swiz_4 = cos(vfoo4.rrbg);

	float3 vcross3			= cross(vfoo3, vbar3);
	float3 vcross_swiz_3_a	= cross(vfoo3, vbar3.yyx);
	float3 vcross_swiz_3_b	= cross(vfoo3.xyz, vbar3);
	float3 vcross_swiz_3_c	= cross(vfoo3.yzx, vbar3.yyx);

	float1 vdot2	= dot(vfoo2, vbar2);
	float1 vdot2_a	= dot(vfoo2, vbar2.yx);
	float1 vdot2_b	= dot(vfoo2.rg, vbar2);
	float1 vdot2_c	= dot(vfoo2.gr, vbar2.yx);

	float1 vdot3	= dot(vfoo3, vbar3);
	float1 vdot3_a	= dot(vfoo3, vbar3.bgr);
	float1 vdot3_b	= dot(vfoo3.rrg, vbar3);
	float1 vdot3_c	= dot(vfoo3.rrg, vbar3);

	float1 vdot4	= dot(vfoo4, vbar4);
	float1 vdot4_a	= dot(vfoo4, vbar4.bgra);
	float1 vdot4_b	= dot(vfoo4.rrgb, vbar4);
	float1 vdot4_c	= dot(vfoo4.rrgg, vbar4);

	float1 vfloor1 = floor(vfoo1);
	float2 vfloor2 = floor(vfoo2);
	float3 vfloor3 = floor(vfoo3);
	float4 vfloor4 = floor(vfoo4);

	float1 vfloor_swiz_1 = floor(vfoo1.r);
	float2 vfloor_swiz_2 = floor(vfoo2.yx);
	float3 vfloor_swiz_3 = floor(vfoo3.xxy);
	float4 vfloor_swiz_4 = floor(vfoo4.wwxy);

	float1 vfrac1 = frac(vfoo1);
	float2 vfrac2 = frac(vfoo2);
	float3 vfrac3 = frac(vfoo3);
	float4 vfrac4 = frac(vfoo4);

	float1 vfrac_swiz_1 = frac(vfoo1.r);
	float2 vfrac_swiz_2 = frac(vfoo2.xy);
	float3 vfrac_swiz_3 = frac(vfoo3.bgr);
	float4 vfrac_swiz_4 = frac(vfoo4.wzzy);

	float1 vexp1 = exp(vfoo1);
	float2 vexp2 = exp(vfoo2);
	float3 vexp3 = exp(vfoo3);
	float4 vexp4 = exp(vfoo4);

	float1 vexp_swiz_1 = exp(vfoo1.r);
	float2 vexp_swiz_2 = exp(vfoo2.yx);
	float3 vexp_swiz_3 = exp(vfoo3.brr);
	float4 vexp_swiz_4 = exp(vfoo4.wxzy);

	float1 vexp2_1 = exp2(vfoo1);
	float2 vexp2_2 = exp2(vfoo2);
	float3 vexp2_3 = exp2(vfoo3);
	float4 vexp2_4 = exp2(vfoo4);

	float1 vexp2_swiz_1 = exp2(vfoo1.r);
	float2 vexp2_swiz_2 = exp2(vfoo2.xy);
	float3 vexp2_swiz_3 = exp2(vfoo3.bgr);
	float4 vexp2_swiz_4 = exp2(vfoo4.wxxy);

	float1 visfinite_1 = isfinite(vfoo1);
	float2 visfinite_2 = isfinite(vfoo2);
	float3 visfinite_3 = isfinite(vfoo3);
	float4 visfinite_4 = isfinite(vfoo4);

	float1 visfinite_swiz_1 = isfinite(vfoo1.r);
	float2 visfinite_swiz_2 = isfinite(vfoo2.xy);
	float3 visfinite_swiz_3 = isfinite(vfoo3.bgr);
	float4 visfinite_swiz_4 = isfinite(vfoo4.wxxy);

	float1 visinf_1 = isinf(vfoo1);
	float2 visinf_2 = isinf(vfoo2);
	float3 visinf_3 = isinf(vfoo3);
	float4 visinf_4 = isinf(vfoo4);

	float1 visinf_swiz_1 = isinf(vfoo1.r);
	float2 visinf_swiz_2 = isinf(vfoo2.xy);
	float3 visinf_swiz_3 = isinf(vfoo3.bgr);
	float4 visinf_swiz_4 = isinf(vfoo4.wxxy);

	float1 visnan_1 = isnan(vfoo1);
	float2 visnan_2 = isnan(vfoo2);
	float3 visnan_3 = isnan(vfoo3);
	float4 visnan_4 = isnan(vfoo4);

	float1 visnan_swiz_1 = isnan(vfoo1.r);
	float2 visnan_swiz_2 = isnan(vfoo2.xy);
	float3 visnan_swiz_3 = isnan(vfoo3.bgr);
	float4 visnan_swiz_4 = isnan(vfoo4.wxxy);

	float1 vlength_1 = length(vfoo1);
	float1 vlength_2 = length(vfoo2);
	float1 vlength_3 = length(vfoo3);
	float1 vlength_4 = length(vfoo4);

	float1 vlength_swiz_1 = length(vfoo1.r);
	float1 vlength_swiz_2 = length(vfoo2.xy);
	float1 vlength_swiz_3 = length(vfoo3.rgb);
	float1 vlength_swiz_4 = length(vfoo4.wwxy);

	// Linear Interpolation

	float1 vlerp1 = lerp(vfoo1, vbar1, vbaz1);
	float2 vlerp2 = lerp(vfoo2, vbar2, vbaz2);
	float3 vlerp3 = lerp(vfoo3, vbar3, vbaz3);
	float4 vlerp4 = lerp(vfoo4, vbar4, vbaz4);

	float1 vlerpf_1 = lerp(vfoo1, vbar1, 0.3f);
	float2 vlerpf_2 = lerp(vfoo2, vbar2, 0.3f);
	float3 vlerpf_3 = lerp(vfoo3, vbar3, 0.5f);
	float4 vlerpf_4 = lerp(vfoo4, vbar4, 0.7f);

	float1 vlerp_swiz_1 = lerp(vfoo1, vbar1, vbaz1.r);
	float2 vlerp_swiz_2 = lerp(vfoo2, vbar2, vbaz2.rg);
	float3 vlerp_swiz_3 = lerp(vfoo3, vbar3, vbaz3.bgr);
	float4 vlerp_swiz_4 = lerp(vfoo4, vbar4, vbaz4.rgba);

	float1 vlog1 = log(vfoo1);
	float2 vlog2 = log(vfoo2);
	float3 vlog3 = log(vfoo3);
	float4 vlog4 = log(vfoo4);

	float1 vlog_swiz_1 = log(vfoo1.r);
	float2 vlog_swiz_2 = log(vfoo2.yx);
	float3 vlog_swiz_3 = log(vfoo3.rrg);
	float4 vlog_swiz_4 = log(vfoo4.wwxy);

	float1 vlog2_1 = log2(vfoo1);
	float2 vlog2_2 = log2(vfoo2);
	float3 vlog2_3 = log2(vfoo3);
	float4 vlog2_4 = log2(vfoo4);

	float1 vlog2_swiz_1 = log2(vfoo1.r);
	float2 vlog2_swiz_2 = log2(vfoo2.yx);
	float3 vlog2_swiz_3 = log2(vfoo3.gbr);
	float4 vlog2_swiz_4 = log2(vfoo4.yyxw);

	float1 vlog10_1 = log10(vfoo1);
	float2 vlog10_2 = log10(vfoo2);
	float3 vlog10_3 = log10(vfoo3);
	float4 vlog10_4 = log10(vfoo4);

	float1 vlog10_swiz_1 = log10(vfoo1.r);
	float2 vlog10_swiz_2 = log10(vfoo2.rg);
	float3 vlog10_swiz_3 = log10(vfoo3.yxy);
	float4 vlog10_swiz_4 = log10(vfoo4.yyzw);

	float1 vmin_1 = min(vfoo1, vbar1);
	float2 vmin_2 = min(vfoo2, vbar2);
	float3 vmin_3 = min(vfoo3, vbar3);
	float4 vmin_4 = min(vfoo4, vbar4);

	float1 vmin_swiz_1 = min(vfoo1.r, vbar1.r);
	float2 vmin_swiz_2 = min(vfoo2.gr, vbar2.rg);
	float3 vmin_swiz_3 = min(vfoo3.ggb, vbar3.bgr);
	float4 vmin_swiz_4 = min(vfoo4.gggg, vbar4.brgr);

	float1 vmax_1 = max(vfoo1, vbar1);
	float2 vmax_2 = max(vfoo2, vbar2);
	float3 vmax_3 = max(vfoo3, vbar3);
	float4 vmax_4 = max(vfoo4, vbar4);

	float1 vmax_swiz_1 = max(vfoo1.r, vbar1.x);
	float2 vmax_swiz_2 = max(vfoo2.rg, vbar2.yx);
	float3 vmax_swiz_3 = max(vfoo3.gbr, vbar3.xyy);
	float4 vmax_swiz_4 = max(vfoo4.brga, vbar4.yxzw);

	float1 vnormalize_1 = normalize(vfoo1);
	float2 vnormalize_2 = normalize(vfoo2);
	float3 vnormalize_3 = normalize(vfoo3);
	float4 vnormalize_4 = normalize(vfoo4);

	float1 vnormalize_swiz_1 = normalize(vfoo1.r);
	float2 vnormalize_swiz_2 = normalize(vfoo2.rg);
	float3 vnormalize_swiz_3 = normalize(vfoo3.gbr);
	float4 vnormalize_swiz_4 = normalize(vfoo4.brga);

	float1 vpow_1 = pow(vfoo1, vbar1);
	float2 vpow_2 = pow(vfoo2, vbar2);
	float3 vpow_3 = pow(vfoo3, vbar3);
	float4 vpow_4 = pow(vfoo4, vbar4);

	float1 vpow_swiz_1 = pow(vfoo1.r, vbar1.r);
	float2 vpow_swiz_2 = pow(vfoo2.rg, vbar2.xy);
	float3 vpow_swiz_3 = pow(vfoo3.bgr, vbar3.yyx);
	float4 vpow_swiz_4 = pow(vfoo4.yyxw, vbar4.xxyw);

	float1 vpow_swiz_1_a = pow(vfoo1, vbar1.r);
	float2 vpow_swiz_2_a = pow(vfoo2, vbar2.xy);
	float3 vpow_swiz_3_a = pow(vfoo3, vbar3.yyx);
	float4 vpow_swiz_4_a = pow(vfoo4, vbar4.xxyw);

	float1 vpow_swiz_1_b = pow(vfoo1.r, vbar1);
	float2 vpow_swiz_2_b = pow(vfoo2.rg, vbar2);
	float3 vpow_swiz_3_b = pow(vfoo3.bgr, vbar3);
	float4 vpow_swiz_4_b = pow(vfoo4.yyxw, vbar4);

	float1 vradians1 = radians(vfoo1);
	float2 vradians2 = radians(vfoo2);
	float3 vradians3 = radians(vfoo3);
	float4 vradians4 = radians(vfoo4);

	float1 vradians_swiz_1 = radians(vfoo1.r);
	float2 vradians_swiz_2 = radians(vfoo2.rg);
	float3 vradians_swiz_3 = radians(vfoo3.bgr);
	float4 vradians_swiz_4 = radians(vfoo4.yyxw);

	float1 vreflect1 = reflect(vfoo1, vbar1);
	float2 vreflect2 = reflect(vfoo2, vbar2);
	float3 vreflect3 = reflect(vfoo3, vbar3);
	float4 vreflect4 = reflect(vfoo4, vbar4);

	float1 vreflect_swiz_1 = reflect(vfoo1.r, vbar1);
	float2 vreflect_swiz_2 = reflect(vfoo2.xy, vbar2);
	float3 vreflect_swiz_3 = reflect(vfoo3.bgr, vbar3);
	float4 vreflect_swiz_4 = reflect(vfoo4.xxzy, vbar4);

	float1 vreflect_swiz_1_a = reflect(vfoo1, vbar1.r);
	float2 vreflect_swiz_2_a = reflect(vfoo2, vbar2.yx);
	float3 vreflect_swiz_3_a = reflect(vfoo3, vbar3.ggr);
	float4 vreflect_swiz_4_a = reflect(vfoo4, vbar4.wxyy);

	float1 vreflect_swiz_1_b = reflect(vfoo1.r, vbar1.r);
	float2 vreflect_swiz_2_b = reflect(vfoo2.xy, vbar2.yx);
	float3 vreflect_swiz_3_b = reflect(vfoo3.bgr, vbar3.ggr);
	float4 vreflect_swiz_4_b = reflect(vfoo4.xxzy, vbar4.wxyy);

	float1 vrsqrt1 = rsqrt(vfoo1);
	float2 vrsqrt2 = rsqrt(vfoo2);
	float3 vrsqrt3 = rsqrt(vfoo3);
	float4 vrsqrt4 = rsqrt(vfoo4);

	float1 vrsqrt_swiz_1 = rsqrt(vfoo1.r);
	float2 vrsqrt_swiz_2 = rsqrt(vfoo2.rg);
	float3 vrsqrt_swiz_3 = rsqrt(vfoo3.bgr);
	float4 vrsqrt_swiz_4 = rsqrt(vfoo4.yyxw);	

	float1 vround1 = round(vfoo1);
	float2 vround2 = round(vfoo2);
	float3 vround3 = round(vfoo3);
	float4 vround4 = round(vfoo4);

	float1 vround_swiz_1 = round(vfoo1.r);
	float2 vround_swiz_2 = round(vfoo2.gr);
	float3 vround_swiz_3 = round(vfoo3.yyx);
	float4 vround_swiz_4 = round(vfoo4.wwyx);

	float1 vsaturate1 = saturate(vfoo1);
	float2 vsaturate2 = saturate(vfoo2);
	float3 vsaturate3 = saturate(vfoo3);
	float4 vsaturate4 = saturate(vfoo4);

	float1 vsaturate_swiz_1 = saturate(vfoo1.r);
	float2 vsaturate_swiz_2 = saturate(vfoo2.xy);
	float3 vsaturate_swiz_3 = saturate(vfoo3.ggr);
	float4 vsaturate_swiz_4 = saturate(vfoo4.wyyx);

	float1 vsign1 = sign(vfoo1);
	float2 vsign2 = sign(vfoo2);
	float3 vsign3 = sign(vfoo3);
	float4 vsign4 = sign(vfoo4);

	float1 vsign_swiz_1 = sign(vfoo1.x);
	float2 vsign_swiz_2 = sign(vfoo2.gg);
	float3 vsign_swiz_3 = sign(vfoo3.bbb);
	float4 vsign_swiz_4 = sign(vfoo4.xxyz);

	float1 vsin1 = sin(vfoo1);
	float2 vsin2 = sin(vfoo2);
	float3 vsin3 = sin(vfoo3);
	float4 vsin4 = sin(vfoo4);

	float1 vsin_swiz_1 = sin(vfoo1.x);
	float2 vsin_swiz_2 = sin(vfoo2.yy);
	float3 vsin_swiz_3 = sin(vfoo3.rrg);
	float4 vsin_swiz_4 = sin(vfoo4.rrbg);

	float1 vsqrt1 = sqrt(vfoo1);
	float2 vsqrt2 = sqrt(vfoo2);
	float3 vsqrt3 = sqrt(vfoo3);
	float4 vsqrt4 = sqrt(vfoo4);

	float1 vsqrt_swiz_1 = sqrt(vfoo1.r);
	float2 vsqrt_swiz_2 = sqrt(vfoo2.rr);
	float3 vsqrt_swiz_3 = sqrt(vfoo3.yyy);
	float4 vsqrt_swiz_4 = sqrt(vfoo4.wwwx);

	float1 vstep1 = step(vfoo1, vbar1);
	float2 vstep2 = step(vfoo2, vbar2);
	float3 vstep3 = step(vfoo3, vbar3);
	float4 vstep4 = step(vfoo4, vbar4);

	float1 vstep_swiz_1 = step(vfoo1, vbar1.x);
	float2 vstep_swiz_2 = step(vfoo2, vbar2.yx);
	float3 vstep_swiz_3 = step(vfoo3, vbar3.xxy);
	float4 vstep_swiz_4 = step(vfoo4, vbar4.zzzw);

	float1 vstep_swiz_1_a = step(vfoo1.x, vbar1);
	float2 vstep_swiz_2_a = step(vfoo2.yx, vbar2);
	float3 vstep_swiz_3_a = step(vfoo3.xxy, vbar3);
	float4 vstep_swiz_4_a = step(vfoo4.zzwx, vbar4);

	float1 vstep_swiz_1_b = step(vfoo1.x, vbar1.x);
	float2 vstep_swiz_2_b = step(vfoo2.yx, vbar2.yx);
	float3 vstep_swiz_3_b = step(vfoo3.xxz, vbar3.xxy);
	float4 vstep_swiz_4_b = step(vfoo4.zwyx, vbar4.zzzw);

	float1 vtan1 = tan(vfoo1);
	float2 vtan2 = tan(vfoo2);
	float3 vtan3 = tan(vfoo3);
	float4 vtan4 = tan(vfoo4);

	float1 vtan_swiz_1 = tan(vfoo1.r);
	float2 vtan_swiz_2 = tan(vfoo2.yy);
	float3 vtan_swiz_3 = tan(vfoo3.zzz);
	float4 vtan_swiz_4 = tan(vfoo4.wwzw);

	float1 vtrunc1 = trunc(vfoo1);
	float2 vtrunc2 = trunc(vfoo2);
	float3 vtrunc3 = trunc(vfoo3);
	float4 vtrunc4 = trunc(vfoo4);

	float1 vtrunc_swiz_1 = trunc(vfoo1.r);
	float2 vtrunc_swiz_2 = trunc(vfoo2.yy);
	float3 vtrunc_swiz_3 = trunc(vfoo3.zzz);
	float4 vtrunc_swiz_4 = trunc(vfoo4.wwzw);

	// Integer

	int32_t i1 = (rand() % 1000); int32_t i5 = (rand() % 1000); int32_t i9 = (rand() % 1000); int32_t i13 = (rand() % 1000); int32_t i17 = (rand() % 1000);
	int32_t i2 = (rand() % 1000); int32_t i6 = (rand() % 1000); int32_t i10 = (rand() % 1000); int32_t i14 = (rand() % 1000); int32_t i18 = (rand() % 1000);
	int32_t i3 = (rand() % 1000); int32_t i7 = (rand() % 1000); int32_t i11 = (rand() % 1000); int32_t i15 = (rand() % 1000); int32_t i19 = (rand() % 1000);
	int32_t i4 = (rand() % 1000); int32_t i8 = (rand() % 1000); int32_t i12 = (rand() % 1000); int32_t i16 = (rand() % 1000); int32_t i20 = (rand() % 1000);

	int1 ivfoo1 = int1(i1);										assert(eq(ivfoo1, i1));
	int2 ivfoo2 = int2(i2, i3);									assert(eq(ivfoo2, i2, i3));
	int3 ivfoo3 = int3(i4, i5, i6);								assert(eq(ivfoo3, i4, i5, i6));
	int4 ivfoo4 = int4(i7, i8, i9, i10);						assert(eq(ivfoo4, i7, i8, i9, i10));

	ivfoo1 = int1(i1);											assert(eq(ivfoo1, i1));
	ivfoo2 = int2(i2, i3);										assert(eq(ivfoo2, i2, i3));
	ivfoo3 = int3(i4, i5, i6);									assert(eq(ivfoo3, i4, i5, i6));
	ivfoo4 = int4(i7, i8, i9, i10);								assert(eq(ivfoo4, i7, i8, i9, i10));

	int1 ivbar1 = ivfoo1.x;										assert(eq(ivbar1, i1));
	int2 ivbar2 = ivfoo2.gr;									assert(eq(ivbar2, i3, i2));
	int3 ivbar3 = ivfoo3.zyx;									assert(eq(ivbar3, i6, i5, i4));
	int4 ivbar4 = ivfoo4.bgra;									assert(eq(ivbar4, i9, i8, i7, i10));

	ivbar1 = i11;												assert(eq(ivbar1, i11));
	ivbar2 = int2(i12, i13);									assert(eq(ivbar2, i12, i13));
	ivbar3 = int3(i14, i15, i16);								assert(eq(ivbar3, i14, i15, i16));
	ivbar4 = int4(i17, i18, i19, i20);							assert(eq(ivbar4, i17, i18, i19, i20));

	int1 ivbaz1 = int1(2);										assert(eq(ivbaz1, 2));
	int2 ivbaz2 = int2(3, 7);									assert(eq(ivbaz2, 3, 7));
	int3 ivbaz3 = int3(1, 4, 8);								assert(eq(ivbaz3, 1, 4, 8));
	int4 ivbaz4 = int4(0, 2, 6, 10);							assert(eq(ivbaz4, 0, 2, 6, 10));

	int2 ivfoo_mix_2_a = int2(ivfoo1, ivbar1);					assert(eq(ivfoo_mix_2_a, ivfoo1, ivbar1));
	int2 ivfoo_mix_2_b = int2(ivfoo2.y, ivbar1);				assert(eq(ivfoo_mix_2_b, ivfoo2.y, ivbar1));
	int2 ivfoo_mix_2_c = int2(ivfoo1, ivbar1.x);				assert(eq(ivfoo_mix_2_c, ivfoo1, ivbar1.x));
	int2 ivfoo_mix_2_d = int2(ivfoo1.x, ivbar2.y);				assert(eq(ivfoo_mix_2_d, ivfoo1.x, ivbar2.y));

	int2 ivfoo_mix_2_f_a = int2(ivfoo1, i1);					assert(eq(ivfoo_mix_2_f_a, ivfoo1.x, i1));
	int2 ivfoo_mix_2_f_b = int2(i2, ivbar1);					assert(eq(ivfoo_mix_2_f_b, i2, ivbar1));
	int2 ivfoo_mix_2_f_c = int2(ivfoo2.y, i1);					assert(eq(ivfoo_mix_2_f_c, ivfoo2.y, i1));
	int2 ivfoo_mix_2_f_d = int2(i2, ivbar3.z);					assert(eq(ivfoo_mix_2_f_d, i2, ivbar3.z));
	int2 ivfoo_mix_2_f_e = int2(i3, i4);						assert(eq(ivfoo_mix_2_f_e, i3, i4));

	int3 ivfoo_mix_3_a = int3(ivfoo1, ivbar1, ivbaz1);			assert(eq(ivfoo_mix_3_a, ivfoo1.x, ivbar1.x, ivbaz1.x));
	int3 ivfoo_mix_3_b = int3(ivfoo2, ivbar1);					assert(eq(ivfoo_mix_3_b, ivfoo2.x, ivfoo2.y, ivbar1.x));
	int3 ivfoo_mix_3_c = int3(ivbar1, ivbar2);					assert(eq(ivfoo_mix_3_c, ivbar1.x, ivbar2.x, ivbar2.y));

	int3 ivfoo_mix_3_d = int3(ivfoo1, ivbar1, ivbaz1.x);		assert(eq(ivfoo_mix_3_d, ivfoo1.x, ivbar1.x, ivbaz1.x));
	int3 ivfoo_mix_3_e = int3(ivfoo1, ivbar1.x, ivbaz1);		assert(eq(ivfoo_mix_3_e, ivfoo1.x, ivbar1.x, ivbaz1.x));
	int3 ivfoo_mix_3_f = int3(ivfoo1.x, ivbar1, ivbaz1);		assert(eq(ivfoo_mix_3_f, ivfoo1.x, ivbar1.x, ivbaz1.x));

	int3 ivfoo_mix_3_g = int3(ivfoo1, ivbar1.x, ivbaz1.x);		assert(eq(ivfoo_mix_3_g, ivfoo1.x, ivbar1.x, ivbaz1.x));
	int3 ivfoo_mix_3_h = int3(ivfoo1.x, ivbar1, ivbaz1.x);		assert(eq(ivfoo_mix_3_h, ivfoo1.x, ivbar1.x, ivbaz1.x));
	int3 ivfoo_mix_3_i = int3(ivfoo1.x, ivbar1.x, ivbaz1);		assert(eq(ivfoo_mix_3_i, ivfoo1.x, ivbar1.x, ivbaz1.x));
	int3 ivfoo_mix_3_j = int3(ivfoo1.x, ivbar1.x, ivbaz1.x);	assert(eq(ivfoo_mix_3_j, ivfoo1.x, ivbar1.x, ivbaz1.x));

	int3 ivfoo_mix_3_f_a = int3(ivfoo1, ivbar1, i1);			assert(eq(ivfoo_mix_3_f_a, ivfoo1.x, ivbar1.x, i1));
	int3 ivfoo_mix_3_f_b = int3(ivfoo1, i1, ivbaz1);			assert(eq(ivfoo_mix_3_f_b, ivfoo1.x, i1, ivbaz1.x));
	int3 ivfoo_mix_3_f_c = int3(i1, ivbar1, ivbaz1);			assert(eq(ivfoo_mix_3_f_c, i1, ivbar1.x, ivbaz1.x));

	int3 ivfoo_mix_3_f_d = int3(ivfoo1, i1, i2);				assert(eq(ivfoo_mix_3_f_d, ivfoo1.x, i1, i2));
	int3 ivfoo_mix_3_f_e = int3(i1, ivbar1, i2);				assert(eq(ivfoo_mix_3_f_e, i1, ivbar1.x, i2));
	int3 ivfoo_mix_3_f_f = int3(i1, i2, ivbaz1);				assert(eq(ivfoo_mix_3_f_f, i1, i2, ivbaz1));

	int3 ivfoo_mix_3_f_g = int3(ivfoo1.x, i1, i2);				assert(eq(ivfoo_mix_3_f_g, ivfoo1.x, i1, i2));
	int3 ivfoo_mix_3_f_h = int3(i1, ivbar2.y, i2);				assert(eq(ivfoo_mix_3_f_h, i1, ivbar2.y, i2));
	int3 ivfoo_mix_3_f_i = int3(i1, i2, ivbaz3.z);				assert(eq(ivfoo_mix_3_f_i, i1, i2, ivbaz3.z));

	int3 ivfoo_mix_3_f_j = int3(ivfoo1.x, ivbar2.y, i2);		assert(eq(ivfoo_mix_3_f_j, ivfoo1.x, ivbar2.y, i2));
	int3 ivfoo_mix_3_f_k = int3(i1, ivbar2.y, ivbaz3.x);		assert(eq(ivfoo_mix_3_f_k, i1, ivbar2.y, ivbaz3.x));
	int3 ivfoo_mix_3_f_l = int3(ivfoo1.x, i2, ivbaz3.z);		assert(eq(ivfoo_mix_3_f_l, ivfoo1.x, i2, ivbaz3.z));

	int3 ivfoo_mix_3_f_m = int3(ivfoo2, i1);					assert(eq(ivfoo_mix_3_f_m, ivfoo2.x, ivfoo2.y, i1));
	int3 ivfoo_mix_3_f_n = int3(i2, ivbar2);					assert(eq(ivfoo_mix_3_f_n, i2, ivbar2.x, ivbar2.y));

	int3 ivfoo_mix_3_f_o = int3(ivfoo2.xy, i1);					assert(eq(ivfoo_mix_3_f_o, ivfoo2.x, ivfoo2.y, i1));
	int3 ivfoo_mix_3_f_p = int3(i2, ivbar2.xy);					assert(eq(ivfoo_mix_3_f_p, i2, ivbar2.x, ivbar2.y));

	int4 ivfoo_mix_4_a = int4(ivbaz1, ivbaz2.x, ivbaz3.x, 5);		assert(eq(ivfoo_mix_4_a, ivbaz1.x, ivbaz2.x, ivbaz3.x, 5));
	int4 ivfoo_mix_4_b = int4(ivbaz1, ivbaz3);						assert(eq(ivfoo_mix_4_b, ivbaz1.x, ivbaz3.x, ivbaz3.y, ivbaz3.z));
	int4 ivfoo_mix_4_c = int4(ivbaz3, ivbaz1);						assert(eq(ivfoo_mix_4_c, ivbaz3.x, ivbaz3.y, ivbaz3.z, ivbaz1.x));
	int4 ivfoo_mix_4_d = int4(ivbaz2, ivbar2);						assert(eq(ivfoo_mix_4_d, ivbaz2.x, ivbaz2.y, ivbar2.x, ivbar2.y));
	int4 ivfoo_mix_4_e = int4(ivbaz2, ivbar1, ivbaz1);				assert(eq(ivfoo_mix_4_e, ivbaz2.x, ivbaz2.y, ivbar1.x, ivbaz1.x));
	int4 ivfoo_mix_4_f = int4(ivbar1, ivbaz2, ivbaz1);				assert(eq(ivfoo_mix_4_f, ivbar1.x, ivbaz2.x, ivbaz2.y, ivbaz1.x));
	int4 ivfoo_mix_4_g = int4(ivbar1, ivbaz1, ivbaz2);				assert(eq(ivfoo_mix_4_g, ivbar1.x, ivbaz1.x, ivbaz2.x, ivbaz2.y));

	int4 ivfoo_mix_4_f_a = int4(i1, ivfoo1, ivbar1, ivbaz1);		assert(eq(ivfoo_mix_4_f_a, i1, ivfoo1, ivbar1, ivbaz1));
	int4 ivfoo_mix_4_f_b = int4(i2, i3, ivbar1, ivbaz1);			assert(eq(ivfoo_mix_4_f_b, i2, i3, ivbar1, ivbaz1));
	int4 ivfoo_mix_4_f_c = int4(i4, i5, i6, ivbaz1);				assert(eq(ivfoo_mix_4_f_c, i4, i5, i6, ivbaz1));

	int4 ivfoo_mix_4_f_d = int4(i1, ivfoo1.x, ivbar2.y, ivbaz3.z);	assert(eq(ivfoo_mix_4_f_d, i1, ivfoo1, ivbar2.y, ivbaz3.z));
	int4 ivfoo_mix_4_f_e = int4(i2, i3, ivbar2.y, ivbaz3.z);		assert(eq(ivfoo_mix_4_f_e, i2, i3, ivbar2.y, ivbaz3.z));
	int4 ivfoo_mix_4_f_f = int4(i4, i5, i6, ivbaz3.z);				assert(eq(ivfoo_mix_4_f_f, i4, i5, i6, ivbaz3.z));

	int4 ivfoo_mix_4_f_g = int4(i1, ivfoo1, ivbar2.y, ivbaz3.z);	assert(eq(ivfoo_mix_4_f_g, i1, ivfoo1, ivbar2.y, ivbaz3.z));
	int4 ivfoo_mix_4_f_h = int4(i2, ivfoo1, ivbar1, ivbaz3.z);		assert(eq(ivfoo_mix_4_f_h, i2, ivfoo1, ivbar1, ivbaz3.z));
	int4 ivfoo_mix_4_f_i = int4(i3, ivfoo1.x, ivbar1, ivbaz3.z);	assert(eq(ivfoo_mix_4_f_i, i3, ivfoo1.x, ivbar1, ivbaz3.z));
	int4 ivfoo_mix_4_f_j = int4(i4, ivfoo1.x, ivbar2.y, ivbaz1);	assert(eq(ivfoo_mix_4_f_j, i4, ivfoo1.x, ivbar2.y, ivbaz1));

	int4 ivfoo_mix_4_f_k = int4(i1, i2, ivbar1, ivbaz3.z);			assert(eq(ivfoo_mix_4_f_k, i1, i2, ivbar1, ivbaz3.z));
	int4 ivfoo_mix_4_f_l = int4(i3, i4, ivbar2.y, ivbaz1);			assert(eq(ivfoo_mix_4_f_l, i3, i4, ivbar2.y, ivbaz1));

	// Assignment and swizzle

	int1 ivassign1 = ivfoo1.x;										assert(eq(ivassign1.x, ivfoo1.x));
	ivassign1 = ivfoo1.r;											assert(eq(ivassign1.x, ivfoo1.x));
	ivassign1.r = ivfoo1;											assert(eq(ivassign1.x, ivfoo1.x));
	ivassign1.r = ivfoo1.r;											assert(eq(ivassign1.x, ivfoo1.x));

	int2 ivassign2 = ivfoo2.yx;										assert(eq(ivassign2, ivfoo2.y, ivfoo2.x));
	ivassign2 = ivfoo2.yy;											assert(eq(ivassign2, ivfoo2.y, ivfoo2.y));
	ivassign2.rg = ivfoo2;											assert(eq(ivassign2, ivfoo2.x, ivfoo2.y));
	ivassign2.rg = ivfoo2.gr;										assert(eq(ivassign2, ivfoo2.y, ivfoo2.x));

	int3 ivassign3 = ivfoo3.yxz;									assert(eq(ivassign3, ivfoo3.y, ivfoo3.x, ivfoo3.z));
	ivassign3 = ivfoo3.yyx;											assert(eq(ivassign3, ivfoo3.y, ivfoo3.y, ivfoo3.x));
	ivassign3.rbg = ivfoo3;											assert(eq(ivassign3, ivfoo3.x, ivfoo3.z, ivfoo3.y));
	ivassign3.rgb = ivfoo3.grr;										assert(eq(ivassign3, ivfoo3.y, ivfoo3.x, ivfoo3.x));

	int4 ivassign4 = ivfoo4.yxzw;									assert(eq(ivassign4, ivfoo4.y, ivfoo4.x, ivfoo4.z, ivfoo4.w));
	ivassign4 = ivfoo4.yyxx;										assert(eq(ivassign4, ivfoo4.y, ivfoo4.y, ivfoo4.x, ivfoo4.x));
	ivassign4.bgra = ivfoo4;										assert(eq(ivassign4, ivfoo4.b, ivfoo4.g, ivfoo4.r, ivfoo4.a));
	ivassign4.rgba = ivfoo4.grba;									assert(eq(ivassign4, ivfoo4.g, ivfoo4.r, ivfoo4.b, ivfoo4.a));

	int2 ivneg_swiz_2 = -ivfoo2.yx;									//assert(ivassign2.x == (int32_t)ivfoo2.y && ivassign2.y == (int32_t)ivfoo2.x);

	// Addition

	int1 ivadd1 = ivfoo1 + ivbar1;									assert(eq(ivadd1, (int32_t)ivfoo1.x + (int32_t)ivbar1.x));
	int2 ivadd2 = ivfoo2 + ivbar2;									assert(eq(ivadd2, (int32_t)ivfoo2.x + (int32_t)ivbar2.x, (int32_t)ivfoo2.y + (int32_t)ivbar2.y));
	int3 ivadd3 = ivfoo3 + ivbar3;									assert(eq(ivadd3, (int32_t)ivfoo3.x + (int32_t)ivbar3.x, (int32_t)ivfoo3.y + (int32_t)ivbar3.y, (int32_t)ivfoo3.z + (int32_t)ivbar3.z));
	int4 ivadd4 = ivfoo4 + ivbar4;									assert(eq(ivadd4, (int32_t)ivfoo4.x + (int32_t)ivbar4.x, (int32_t)ivfoo4.y + (int32_t)ivbar4.y, (int32_t)ivfoo4.z + (int32_t)ivbar4.z, (int32_t)ivfoo4.w + (int32_t)ivbar4.w));

	int1 ivadd_f_1 = ivfoo1 + 1;									assert(eq(ivadd_f_1, (int32_t)ivfoo1.x + 1));
	int2 ivadd_f_2 = ivfoo2 + 2;									assert(eq(ivadd_f_2, (int32_t)ivfoo2.x + 2, (int32_t)ivfoo2.y + 2));
	int3 ivadd_f_3 = ivfoo3 + 3;									assert(eq(ivadd_f_3, (int32_t)ivfoo3.x + 3, (int32_t)ivfoo3.y + 3, (int32_t)ivfoo3.z + 3));
	int4 ivadd_f_4 = ivfoo4 + 4;									assert(eq(ivadd_f_4, (int32_t)ivfoo4.x + 4, (int32_t)ivfoo4.y + 4, (int32_t)ivfoo4.z + 4, (int32_t)ivfoo4.w + 4));

	ivadd_f_1 += 1;													assert(eq(ivadd_f_1, (int32_t)ivfoo1.x + 1 + 1));
	ivadd_f_2 += 2;													assert(eq(ivadd_f_2, (int32_t)ivfoo2.x + 2 + 2, (int32_t)ivfoo2.y + 2 + 2));
	ivadd_f_3 += 3;													assert(eq(ivadd_f_3, (int32_t)ivfoo3.x + 3 + 3, (int32_t)ivfoo3.y + 3 + 3, (int32_t)ivfoo3.z + 3 + 3));
	ivadd_f_4 += 4;													assert(eq(ivadd_f_4, (int32_t)ivfoo4.x + 4 + 4, (int32_t)ivfoo4.y + 4 + 4, (int32_t)ivfoo4.z + 4 + 4, (int32_t)ivfoo4.w + 4 + 4));

	int1 ivadd_swiz_a_1 = ivfoo1 + ivbar1.x;						assert(eq(ivadd_swiz_a_1, (int32_t)ivfoo1 + (int32_t)ivbar1.x));
	int1 ivadd_swiz_b_1 = ivfoo1.r + ivbar1.x;						assert(eq(ivadd_swiz_b_1, (int32_t)ivfoo1.r + (int32_t)ivbar1.x));
	int1 ivadd_swiz_c_1 = ivfoo1.r + ivbar1;						assert(eq(ivadd_swiz_c_1, (int32_t)ivfoo1.r + (int32_t)ivbar1));

	int2 ivadd_swiz_a_2 = ivfoo2 + ivbar2.yx;						assert(eq(ivadd_swiz_a_2, (int32_t)ivfoo2.x + (int32_t)ivbar2.y, (int32_t)ivfoo2.y + (int32_t)ivbar2.x));
	int2 ivadd_swiz_b_2 = ivfoo2.gr + ivbar2.yx;					assert(eq(ivadd_swiz_b_2, (int32_t)ivfoo2.g + (int32_t)ivbar2.y, (int32_t)ivfoo2.r + (int32_t)ivbar2.x));
	int2 ivadd_swiz_c_2 = ivfoo2.rg + ivbar2;						assert(eq(ivadd_swiz_c_2, (int32_t)ivfoo2.r + (int32_t)ivbar2.x, (int32_t)ivfoo2.g + (int32_t)ivbar2.y));

	int3 ivadd_swiz_a_3 = ivfoo3 + ivbar3.yxz;						assert(eq(ivadd_swiz_a_3, (int32_t)ivfoo3.x + (int32_t)ivbar3.y, (int32_t)ivfoo3.y + (int32_t)ivbar3.x, (int32_t)ivfoo3.z + (int32_t)ivbar3.z));
	int3 ivadd_swiz_b_3 = ivfoo3.bgr + ivbar3.xyz;					assert(eq(ivadd_swiz_b_3, (int32_t)ivfoo3.b + (int32_t)ivbar3.x, (int32_t)ivfoo3.g + (int32_t)ivbar3.y, (int32_t)ivfoo3.r + (int32_t)ivbar3.z));
	int3 ivadd_swiz_c_3 = ivfoo3.bgr + ivbar3;						assert(eq(ivadd_swiz_c_3, (int32_t)ivfoo3.b + (int32_t)ivbar3.x, (int32_t)ivfoo3.g + (int32_t)ivbar3.y, (int32_t)ivfoo3.r + (int32_t)ivbar3.z));

	int4 ivadd_swiz_a_4 = ivfoo4 + ivbar4.yxzw;						assert(eq(ivadd_swiz_a_4, (int32_t)ivfoo4.x + (int32_t)ivbar4.y, (int32_t)ivfoo4.y + (int32_t)ivbar4.x, (int32_t)ivfoo4.z + (int32_t)ivbar4.z, (int32_t)ivfoo4.w + (int32_t)ivbar4.w));
	int4 ivadd_swiz_b_4 = ivfoo4.bgra + ivbar4.yxzw;				assert(eq(ivadd_swiz_b_4, (int32_t)ivfoo4.b + (int32_t)ivbar4.y, (int32_t)ivfoo4.g + (int32_t)ivbar4.x, (int32_t)ivfoo4.r + (int32_t)ivbar4.z, (int32_t)ivfoo4.a + (int32_t)ivbar4.w));
	int4 ivadd_swiz_c_4 = ivfoo4.bgra + ivbar4;						assert(eq(ivadd_swiz_c_4, (int32_t)ivfoo4.b + (int32_t)ivbar4.x, (int32_t)ivfoo4.g + (int32_t)ivbar4.y, (int32_t)ivfoo4.r + (int32_t)ivbar4.z, (int32_t)ivfoo4.a + (int32_t)ivbar4.w));

	ivadd_swiz_a_1 += ivfoo1;
	ivadd_swiz_b_1 += ivfoo1.x;
	ivadd_swiz_c_1.x += ivfoo1;
	ivadd_swiz_c_1.r += ivfoo1.r;

	ivadd_swiz_a_2 += ivfoo2;
	ivadd_swiz_b_2 += ivfoo2.xy;
	ivadd_swiz_c_2.xy += ivfoo2;
	ivadd_swiz_c_2.gr += ivfoo2.rg;

	// Subtraction

	int1 ivsub1 = ivfoo1 - ivbar1;									assert(eq(ivsub1, (int32_t)ivfoo1.x - (int32_t)ivbar1.x));
	int2 ivsub2 = ivfoo2 - ivbar2;									assert(eq(ivsub2, (int32_t)ivfoo2.x - (int32_t)ivbar2.x, (int32_t)ivfoo2.y - (int32_t)ivbar2.y));
	int3 ivsub3 = ivfoo3 - ivbar3;									assert(eq(ivsub3, (int32_t)ivfoo3.x - (int32_t)ivbar3.x, (int32_t)ivfoo3.y - (int32_t)ivbar3.y, (int32_t)ivfoo3.z - (int32_t)ivbar3.z));
	int4 ivsub4 = ivfoo4 - ivbar4;									assert(eq(ivsub4, (int32_t)ivfoo4.x - (int32_t)ivbar4.x, (int32_t)ivfoo4.y - (int32_t)ivbar4.y, (int32_t)ivfoo4.z - (int32_t)ivbar4.z, (int32_t)ivfoo4.w - (int32_t)ivbar4.w));

	int1 ivsub_f_1 = ivfoo1 - 1;									assert(eq(ivsub_f_1, (int32_t)ivfoo1.x - 1));
	int2 ivsub_f_2 = ivfoo2 - 2;									assert(eq(ivsub_f_2, (int32_t)ivfoo2.x - 2, (int32_t)ivfoo2.y - 2));
	int3 ivsub_f_3 = ivfoo3 - 3;									assert(eq(ivsub_f_3, (int32_t)ivfoo3.x - 3, (int32_t)ivfoo3.y - 3, (int32_t)ivfoo3.z - 3));
	int4 ivsub_f_4 = ivfoo4 - 4;									assert(eq(ivsub_f_4, (int32_t)ivfoo4.x - 4, (int32_t)ivfoo4.y - 4, (int32_t)ivfoo4.z - 4, (int32_t)ivfoo4.w - 4));

	ivsub_f_1 -= 1;													assert(eq(ivsub_f_1, (int32_t)ivfoo1.x - 1 - 1));
	ivsub_f_2 -= 2;													assert(eq(ivsub_f_2, (int32_t)ivfoo2.x - 2 - 2, (int32_t)ivfoo2.y - 2 - 2));
	ivsub_f_3 -= 3;													assert(eq(ivsub_f_3, (int32_t)ivfoo3.x - 3 - 3, (int32_t)ivfoo3.y - 3 - 3, (int32_t)ivfoo3.z - 3 - 3));
	ivsub_f_4 -= 4;													assert(eq(ivsub_f_4, (int32_t)ivfoo4.x - 4 - 4, (int32_t)ivfoo4.y - 4 - 4, (int32_t)ivfoo4.z - 4 - 4, (int32_t)ivfoo4.w - 4 - 4));

	int1 ivsub_swiz_a_1 = ivfoo1 - ivbar1.x;						assert(eq(ivsub_swiz_a_1, (int32_t)ivfoo1 - (int32_t)ivbar1.x));
	int1 ivsub_swiz_b_1 = ivfoo1.r - ivbar1.x;						assert(eq(ivsub_swiz_b_1, (int32_t)ivfoo1.r - (int32_t)ivbar1.x));
	int1 ivsub_swiz_c_1 = ivfoo1.r - ivbar1;						assert(eq(ivsub_swiz_c_1, (int32_t)ivfoo1.r - (int32_t)ivbar1));
	ivsub_swiz_c_1.r = ivfoo4.r - ivbar4.r;

	int2 ivsub_swiz_a_2 = ivfoo2 - ivbar2.yx;						assert(eq(ivsub_swiz_a_2, (int32_t)ivfoo2.x - (int32_t)ivbar2.y, (int32_t)ivfoo2.y - (int32_t)ivbar2.x));
	int2 ivsub_swiz_b_2 = ivfoo2.gr - ivbar2.yx;					assert(eq(ivsub_swiz_b_2, (int32_t)ivfoo2.g - (int32_t)ivbar2.y, (int32_t)ivfoo2.r - (int32_t)ivbar2.x));
	int2 ivsub_swiz_c_2 = ivfoo2.rg - ivbar2;						assert(eq(ivsub_swiz_c_2, (int32_t)ivfoo2.r - (int32_t)ivbar2.x, (int32_t)ivfoo2.g - (int32_t)ivbar2.y));
	ivsub_swiz_c_2.gr = ivfoo4.rg - ivbar4.gr;

	int3 ivsub_swiz_a_3 = ivfoo3 - ivbar3.yxz;						assert(eq(ivsub_swiz_a_3, (int32_t)ivfoo3.x - (int32_t)ivbar3.y, (int32_t)ivfoo3.y - (int32_t)ivbar3.x, (int32_t)ivfoo3.z - (int32_t)ivbar3.z));
	int3 ivsub_swiz_b_3 = ivfoo3.bgr - ivbar3.xyz;					assert(eq(ivsub_swiz_b_3, (int32_t)ivfoo3.b - (int32_t)ivbar3.x, (int32_t)ivfoo3.g - (int32_t)ivbar3.y, (int32_t)ivfoo3.r - (int32_t)ivbar3.z));
	int3 ivsub_swiz_c_3 = ivfoo3.bgr - ivbar3;						assert(eq(ivsub_swiz_c_3, (int32_t)ivfoo3.b - (int32_t)ivbar3.x, (int32_t)ivfoo3.g - (int32_t)ivbar3.y, (int32_t)ivfoo3.r - (int32_t)ivbar3.z));
	ivsub_swiz_c_3.bgr = ivfoo4.grb - ivbar4.gbr;

	int4 ivsub_swiz_a_4 = ivfoo4 - ivbar4.yxzw;						assert(eq(ivsub_swiz_a_4, (int32_t)ivfoo4.x - (int32_t)ivbar4.y, (int32_t)ivfoo4.y - (int32_t)ivbar4.x, (int32_t)ivfoo4.z - (int32_t)ivbar4.z, (int32_t)ivfoo4.w - (int32_t)ivbar4.w));
	int4 ivsub_swiz_b_4 = ivfoo4.bgra - ivbar4.yxzw;				assert(eq(ivsub_swiz_b_4, (int32_t)ivfoo4.b - (int32_t)ivbar4.y, (int32_t)ivfoo4.g - (int32_t)ivbar4.x, (int32_t)ivfoo4.r - (int32_t)ivbar4.z, (int32_t)ivfoo4.a - (int32_t)ivbar4.w));
	int4 ivsub_swiz_c_4 = ivfoo4.bgra - ivbar4;						assert(eq(ivsub_swiz_c_4, (int32_t)ivfoo4.b - (int32_t)ivbar4.x, (int32_t)ivfoo4.g - (int32_t)ivbar4.y, (int32_t)ivfoo4.r - (int32_t)ivbar4.z, (int32_t)ivfoo4.a - (int32_t)ivbar4.w));
	ivsub_swiz_c_4.bgra = ivfoo4.argb - ivbar4.ggbr;

	ivadd_swiz_a_1 -= ivfoo1;
	ivadd_swiz_b_1 -= ivfoo1.x;
	ivadd_swiz_c_1.x -= ivfoo1;
	ivadd_swiz_c_1.r -= ivfoo1.r;

	ivsub_swiz_a_2 -= ivfoo2;
	ivsub_swiz_b_2 -= ivfoo2.xy;
	ivsub_swiz_c_2.xy -= ivfoo2;
	ivsub_swiz_c_2.gr -= ivfoo2.rg;

	// Multiplication

	int1 ivmul1 = ivfoo1 * ivbar1;									assert(eq(ivmul1, (int32_t)ivfoo1.x * (int32_t)ivbar1.x));
	int2 ivmul2 = ivfoo2 * ivbar2;									assert(eq(ivmul2, (int32_t)ivfoo2.x * (int32_t)ivbar2.x, (int32_t)ivfoo2.y * (int32_t)ivbar2.y));
	int3 ivmul3 = ivfoo3 * ivbar3;									assert(eq(ivmul3, (int32_t)ivfoo3.x * (int32_t)ivbar3.x, (int32_t)ivfoo3.y * (int32_t)ivbar3.y, (int32_t)ivfoo3.z * (int32_t)ivbar3.z));
	int4 ivmul4 = ivfoo4 * ivbar4;									assert(eq(ivmul4, (int32_t)ivfoo4.x * (int32_t)ivbar4.x, (int32_t)ivfoo4.y * (int32_t)ivbar4.y, (int32_t)ivfoo4.z * (int32_t)ivbar4.z, (int32_t)ivfoo4.w * (int32_t)ivbar4.w));

	int1 ivmul_f_1 = ivfoo1 * 1;									assert(eq(ivmul_f_1, (int32_t)ivfoo1.x * 1));
	int2 ivmul_f_2 = ivfoo2 * 2;									assert(eq(ivmul_f_2, (int32_t)ivfoo2.x * 2, (int32_t)ivfoo2.y * 2));
	int3 ivmul_f_3 = ivfoo3 * 3;									assert(eq(ivmul_f_3, (int32_t)ivfoo3.x * 3, (int32_t)ivfoo3.y * 3, (int32_t)ivfoo3.z * 3));
	int4 ivmul_f_4 = ivfoo4 * 4;									assert(eq(ivmul_f_4, (int32_t)ivfoo4.x * 4, (int32_t)ivfoo4.y * 4, (int32_t)ivfoo4.z * 4, (int32_t)ivfoo4.w * 4));

	ivmul_f_1 *= 1;													assert(eq(ivmul_f_1, (int32_t)ivfoo1.x * 1 * 1));
	ivmul_f_2 *= 2;													assert(eq(ivmul_f_2, (int32_t)ivfoo2.x * 2 * 2, (int32_t)ivfoo2.y * 2 * 2));
	ivmul_f_3 *= 3;													assert(eq(ivmul_f_3, (int32_t)ivfoo3.x * 3 * 3, (int32_t)ivfoo3.y * 3 * 3, (int32_t)ivfoo3.z * 3 * 3));
	ivmul_f_4 *= 4;													assert(eq(ivmul_f_4, (int32_t)ivfoo4.x * 4 * 4, (int32_t)ivfoo4.y * 4 * 4, (int32_t)ivfoo4.z * 4 * 4, (int32_t)ivfoo4.w * 4 * 4));

	int1 ivmul_swiz_a_1 = ivfoo1 * ivbar1.x;
	int1 ivmul_swiz_b_1 = ivfoo1.r * ivbar1.x;
	int1 ivmul_swiz_c_1 = ivfoo1.r * ivbar1;

	int2 ivmul_swiz_a_2 = ivfoo2 * ivbar2.yx;
	int2 ivmul_swiz_b_2 = ivfoo2.gr * ivbar2.yx;
	int2 ivmul_swiz_c_2 = ivfoo2.rg * ivbar2;

	int3 ivmul_swiz_a_3 = ivfoo3 * ivbar3.yxz;
	int3 ivmul_swiz_b_3 = ivfoo3.rgb * ivbar3.xyz;
	int3 ivmul_swiz_c_3 = ivfoo3.bgr * ivbar3;

	int4 ivmul_swiz_a_4 = ivfoo4 * ivbar4.yxzw;
	int4 ivmul_swiz_b_4 = ivfoo4.bgra * ivbar4.yxzw;
	int4 ivmul_swiz_c_4 = ivfoo4.bgra * ivbar4;

	ivmul_swiz_a_2 *= ivfoo2;
	ivmul_swiz_b_2 *= ivfoo2.xy;
	ivmul_swiz_c_2.xy *= ivfoo2;
	ivmul_swiz_c_2.gr *= ivfoo2.rg;

	int1 vint = int1(1);
	int1 vint2 = int1(2);
	int1 vint3 = vint.r + vint2;
	vint.r = vint2.x;

	int2 perryint2 = int2(1, 2);

	float1 flala(vint);
	float1 flala2 = vint;

	flala2 = vint;

	int3 a = int3(1, 2, 3);
	int4 b = int4(0, 1, 2, 3);

	float4 bf = b;

	int4 sat4i = saturate(b);

	int a1 = 1;
	float af1 = a1;
	int a2 = af1;

	int3 c = a + b.zzw;
	int2 d = int2(1, 3);
	int2 e = d.yx + b.zz;
	int2 f = d.yx - b.zz;
	int2 g = d.yx * b.zz;

	int2 roro = abs(g);

	// Infinities and NaNs

	//float4 inf = -float4::one() / float4::zero(); //assert(all(inf != inf).x != 0.0f);
	//float4 nan = sqrt(-float4::one());

	//*********
	// Matrices
	//*********

	float1x1 mat_foo_1x1 = float1x1(1);
	float1x2 mat_foo_1x2 = float1x2(1, 2);
	float1x3 mat_foo_1x3 = float1x3(1, 2, 3);
	float1x4 mat_foo_1x4 = float1x4(1, 2, 3, 4);

	float2x1 mat_foo_2x1 = float2x1(1, 2);
	float3x1 mat_foo_3x1 = float3x1(1, 2, 3);
	float4x1 mat_foo_4x1 = float4x1(1, 2, 3, 4);

	float2x2 mat_foo_2x2 = float2x2(1, 2, 3, 4);

	float2x3 mat_foo_2x3 = float2x3(1, 2, 3, 4, 5, 6);
	float2x4 mat_foo_2x4 = float2x4(1, 2, 3, 4, 5, 6, 7, 8);

	float3x2 mat_foo_3x2 = float3x2(1, 2, 3, 4, 5, 6);
	float4x2 mat_foo_4x2 = float4x2(1, 2, 3, 4, 5, 6, 7, 8);

	float3x3 mat_foo_3x3 = float3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);

	float3x4 mat_foo_3x4 = float3x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
	float4x3 mat_foo_4x3 = float4x3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);

	float4x4 mat_foo_4x4 = float4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	float1x1 mat_bar_1x1 = float1x1(0.4f);
	float1x2 mat_bar_1x2 = float1x2(0.1f, 0.2f);
	float1x3 mat_bar_1x3 = float1x3(0.1f, 0.2f, 0.3f);
	float1x4 mat_bar_1x4 = float1x4(0.1f, 0.2f, 0.3f, 0.4f);
	
	float2x1 mat_bar_2x1 = float2x1(0.1f, 0.2f);
	float3x1 mat_bar_3x1 = float3x1(0.1f, 0.2f, 0.3f);
	float4x1 mat_bar_4x1 = float4x1(0.1f, 0.2f, 0.3f, 0.4f);
	
	float2x2 mat_bar_2x2 = float2x2(0.1f, 0.2f, 0.3f, 0.4f);
	
	float2x3 mat_bar_2x3 = float2x3(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f);
	float2x4 mat_bar_2x4 = float2x4(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f);
	
	float3x2 mat_bar_3x2 = float3x2(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f);
	float4x2 mat_bar_4x2 = float4x2(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f);
	
	float3x3 mat_bar_3x3 = float3x3(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f);
	
	float3x4 mat_bar_3x4 = float3x4(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f);
	float4x3 mat_bar_4x3 = float4x3(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f);
	
	float4x4 mat_bar_4x4 = float4x4(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f);
	
	// Addition

	float1x1 mat_add_1x1 = mat_foo_1x1 + mat_bar_1x1;
	float1x2 mat_add_1x2 = mat_foo_1x2 + mat_bar_1x2;
	float1x3 mat_add_1x3 = mat_foo_1x3 + mat_bar_1x3;
	float1x4 mat_add_1x4 = mat_foo_1x4 + mat_bar_1x4;
	float2x1 mat_add_2x1 = mat_foo_2x1 + mat_bar_2x1;
	float3x1 mat_add_3x1 = mat_foo_3x1 + mat_bar_3x1;
	float4x1 mat_add_4x1 = mat_foo_4x1 + mat_bar_4x1;
	float2x2 mat_add_2x2 = mat_foo_2x2 + mat_bar_2x2;
	float2x3 mat_add_2x3 = mat_foo_2x3 + mat_bar_2x3;
	float2x4 mat_add_2x4 = mat_foo_2x4 + mat_bar_2x4;
	float3x2 mat_add_3x2 = mat_foo_3x2 + mat_bar_3x2;
	float4x2 mat_add_4x2 = mat_foo_4x2 + mat_bar_4x2;
	float3x3 mat_add_3x3 = mat_foo_3x3 + mat_bar_3x3;
	float3x4 mat_add_3x4 = mat_foo_3x4 + mat_bar_3x4;
	float4x3 mat_add_4x3 = mat_foo_4x3 + mat_bar_4x3;
	float4x4 mat_add_4x4 = mat_foo_4x4 + mat_bar_4x4;

	float1x1 mat_add_v_1x1 = mat_foo_1x1 + vfoo1;
	float1x2 mat_add_v_1x2 = mat_foo_1x2 + vfoo1;
	float1x3 mat_add_v_1x3 = mat_foo_1x3 + vfoo1;
	float1x4 mat_add_v_1x4 = mat_foo_1x4 + vfoo1;
	float2x1 mat_add_v_2x1 = mat_foo_2x1 + vfoo1;
	float3x1 mat_add_v_3x1 = mat_foo_3x1 + vfoo1;
	float4x1 mat_add_v_4x1 = mat_foo_4x1 + vfoo1;
	float2x2 mat_add_v_2x2 = mat_foo_2x2 + vfoo1;
	float2x3 mat_add_v_2x3 = mat_foo_2x3 + vfoo1;
	float2x4 mat_add_v_2x4 = mat_foo_2x4 + vfoo1;
	float3x2 mat_add_v_3x2 = mat_foo_3x2 + vfoo1;
	float4x2 mat_add_v_4x2 = mat_foo_4x2 + vfoo1;
	float3x3 mat_add_v_3x3 = mat_foo_3x3 + vfoo1;
	float3x4 mat_add_v_3x4 = mat_foo_3x4 + vfoo1;
	float4x3 mat_add_v_4x3 = mat_foo_4x3 + vfoo1;
	float4x4 mat_add_v_4x4 = mat_foo_4x4 + vfoo1;

	float1x1 mat_add_f_1x1 = mat_foo_1x1 + 1.0f;
	float1x2 mat_add_f_1x2 = mat_foo_1x2 + 1.0f;
	float1x3 mat_add_f_1x3 = mat_foo_1x3 + 1.0f;
	float1x4 mat_add_f_1x4 = mat_foo_1x4 + 1.0f;
	float2x1 mat_add_f_2x1 = mat_foo_2x1 + 1.0f;
	float3x1 mat_add_f_3x1 = mat_foo_3x1 + 1.0f;
	float4x1 mat_add_f_4x1 = mat_foo_4x1 + 1.0f;
	float2x2 mat_add_f_2x2 = mat_foo_2x2 + 1.0f;
	float2x3 mat_add_f_2x3 = mat_foo_2x3 + 1.0f;
	float2x4 mat_add_f_2x4 = mat_foo_2x4 + 1.0f;
	float3x2 mat_add_f_3x2 = mat_foo_3x2 + 1.0f;
	float4x2 mat_add_f_4x2 = mat_foo_4x2 + 1.0f;
	float3x3 mat_add_f_3x3 = mat_foo_3x3 + 1.0f;
	float3x4 mat_add_f_3x4 = mat_foo_3x4 + 1.0f;
	float4x3 mat_add_f_4x3 = mat_foo_4x3 + 1.0f;
	float4x4 mat_add_f_4x4 = mat_foo_4x4 + 1.0f;

	// Subtraction

	float1x1 mat_sub_1x1 = mat_foo_1x1 - mat_bar_1x1;
	float1x2 mat_sub_1x2 = mat_foo_1x2 - mat_bar_1x2;
	float1x3 mat_sub_1x3 = mat_foo_1x3 - mat_bar_1x3;
	float1x4 mat_sub_1x4 = mat_foo_1x4 - mat_bar_1x4;
	float2x1 mat_sub_2x1 = mat_foo_2x1 - mat_bar_2x1;
	float3x1 mat_sub_3x1 = mat_foo_3x1 - mat_bar_3x1;
	float4x1 mat_sub_4x1 = mat_foo_4x1 - mat_bar_4x1;
	float2x2 mat_sub_2x2 = mat_foo_2x2 - mat_bar_2x2;
	float2x3 mat_sub_2x3 = mat_foo_2x3 - mat_bar_2x3;
	float2x4 mat_sub_2x4 = mat_foo_2x4 - mat_bar_2x4;
	float3x2 mat_sub_3x2 = mat_foo_3x2 - mat_bar_3x2;
	float4x2 mat_sub_4x2 = mat_foo_4x2 - mat_bar_4x2;
	float3x3 mat_sub_3x3 = mat_foo_3x3 - mat_bar_3x3;
	float3x4 mat_sub_3x4 = mat_foo_3x4 - mat_bar_3x4;
	float4x3 mat_sub_4x3 = mat_foo_4x3 - mat_bar_4x3;
	float4x4 mat_sub_4x4 = mat_foo_4x4 - mat_bar_4x4;

	float1x1 mat_sub_v_1x1 = mat_foo_1x1 - vfoo1;
	float1x2 mat_sub_v_1x2 = mat_foo_1x2 - vfoo1;
	float1x3 mat_sub_v_1x3 = mat_foo_1x3 - vfoo1;
	float1x4 mat_sub_v_1x4 = mat_foo_1x4 - vfoo1;
	float2x1 mat_sub_v_2x1 = mat_foo_2x1 - vfoo1;
	float3x1 mat_sub_v_3x1 = mat_foo_3x1 - vfoo1;
	float4x1 mat_sub_v_4x1 = mat_foo_4x1 - vfoo1;
	float2x2 mat_sub_v_2x2 = mat_foo_2x2 - vfoo1;
	float2x3 mat_sub_v_2x3 = mat_foo_2x3 - vfoo1;
	float2x4 mat_sub_v_2x4 = mat_foo_2x4 - vfoo1;
	float3x2 mat_sub_v_3x2 = mat_foo_3x2 - vfoo1;
	float4x2 mat_sub_v_4x2 = mat_foo_4x2 - vfoo1;
	float3x3 mat_sub_v_3x3 = mat_foo_3x3 - vfoo1;
	float3x4 mat_sub_v_3x4 = mat_foo_3x4 - vfoo1;
	float4x3 mat_sub_v_4x3 = mat_foo_4x3 - vfoo1;
	float4x4 mat_sub_v_4x4 = mat_foo_4x4 - vfoo1;

	float1x1 mat_sub_f_1x1 = mat_foo_1x1 - 1.0f;
	float1x2 mat_sub_f_1x2 = mat_foo_1x2 - 1.0f;
	float1x3 mat_sub_f_1x3 = mat_foo_1x3 - 1.0f;
	float1x4 mat_sub_f_1x4 = mat_foo_1x4 - 1.0f;
	float2x1 mat_sub_f_2x1 = mat_foo_2x1 - 1.0f;
	float3x1 mat_sub_f_3x1 = mat_foo_3x1 - 1.0f;
	float4x1 mat_sub_f_4x1 = mat_foo_4x1 - 1.0f;
	float2x2 mat_sub_f_2x2 = mat_foo_2x2 - 1.0f;
	float2x3 mat_sub_f_2x3 = mat_foo_2x3 - 1.0f;
	float2x4 mat_sub_f_2x4 = mat_foo_2x4 - 1.0f;
	float3x2 mat_sub_f_3x2 = mat_foo_3x2 - 1.0f;
	float4x2 mat_sub_f_4x2 = mat_foo_4x2 - 1.0f;
	float3x3 mat_sub_f_3x3 = mat_foo_3x3 - 1.0f;
	float3x4 mat_sub_f_3x4 = mat_foo_3x4 - 1.0f;
	float4x3 mat_sub_f_4x3 = mat_foo_4x3 - 1.0f;
	float4x4 mat_sub_f_4x4 = mat_foo_4x4 - 1.0f;

	// Multiplication

	float1x1 mat_mul_1x1 = mat_foo_1x1 * mat_bar_1x1;
	float1x2 mat_mul_1x2 = mat_foo_1x2 * mat_bar_1x2;
	float1x3 mat_mul_1x3 = mat_foo_1x3 * mat_bar_1x3;
	float1x4 mat_mul_1x4 = mat_foo_1x4 * mat_bar_1x4;
	float2x1 mat_mul_2x1 = mat_foo_2x1 * mat_bar_2x1;
	float3x1 mat_mul_3x1 = mat_foo_3x1 * mat_bar_3x1;
	float4x1 mat_mul_4x1 = mat_foo_4x1 * mat_bar_4x1;
	float2x2 mat_mul_2x2 = mat_foo_2x2 * mat_bar_2x2;
	float2x3 mat_mul_2x3 = mat_foo_2x3 * mat_bar_2x3;
	float2x4 mat_mul_2x4 = mat_foo_2x4 * mat_bar_2x4;
	float3x2 mat_mul_3x2 = mat_foo_3x2 * mat_bar_3x2;
	float4x2 mat_mul_4x2 = mat_foo_4x2 * mat_bar_4x2;
	float3x3 mat_mul_3x3 = mat_foo_3x3 * mat_bar_3x3;
	float3x4 mat_mul_3x4 = mat_foo_3x4 * mat_bar_3x4;
	float4x3 mat_mul_4x3 = mat_foo_4x3 * mat_bar_4x3;
	float4x4 mat_mul_4x4 = mat_foo_4x4 * mat_bar_4x4;

	float1x1 mat_mul_v_1x1 = mat_foo_1x1 * vfoo1;
	float1x2 mat_mul_v_1x2 = mat_foo_1x2 * vfoo1;
	float1x3 mat_mul_v_1x3 = mat_foo_1x3 * vfoo1;
	float1x4 mat_mul_v_1x4 = mat_foo_1x4 * vfoo1;
	float2x1 mat_mul_v_2x1 = mat_foo_2x1 * vfoo1;
	float3x1 mat_mul_v_3x1 = mat_foo_3x1 * vfoo1;
	float4x1 mat_mul_v_4x1 = mat_foo_4x1 * vfoo1;
	float2x2 mat_mul_v_2x2 = mat_foo_2x2 * vfoo1;
	float2x3 mat_mul_v_2x3 = mat_foo_2x3 * vfoo1;
	float2x4 mat_mul_v_2x4 = mat_foo_2x4 * vfoo1;
	float3x2 mat_mul_v_3x2 = mat_foo_3x2 * vfoo1;
	float4x2 mat_mul_v_4x2 = mat_foo_4x2 * vfoo1;
	float3x3 mat_mul_v_3x3 = mat_foo_3x3 * vfoo1;
	float3x4 mat_mul_v_3x4 = mat_foo_3x4 * vfoo1;
	float4x3 mat_mul_v_4x3 = mat_foo_4x3 * vfoo1;
	float4x4 mat_mul_v_4x4 = mat_foo_4x4 * vfoo1;

	float1x1 mat_mul_f_1x1 = mat_foo_1x1 * 2.0f;
	float1x2 mat_mul_f_1x2 = mat_foo_1x2 * 2.0f;
	float1x3 mat_mul_f_1x3 = mat_foo_1x3 * 2.0f;
	float1x4 mat_mul_f_1x4 = mat_foo_1x4 * 2.0f;
	float2x1 mat_mul_f_2x1 = mat_foo_2x1 * 2.0f;
	float3x1 mat_mul_f_3x1 = mat_foo_3x1 * 2.0f;
	float4x1 mat_mul_f_4x1 = mat_foo_4x1 * 2.0f;
	float2x2 mat_mul_f_2x2 = mat_foo_2x2 * 2.0f;
	float2x3 mat_mul_f_2x3 = mat_foo_2x3 * 2.0f;
	float2x4 mat_mul_f_2x4 = mat_foo_2x4 * 2.0f;
	float3x2 mat_mul_f_3x2 = mat_foo_3x2 * 2.0f;
	float4x2 mat_mul_f_4x2 = mat_foo_4x2 * 2.0f;
	float3x3 mat_mul_f_3x3 = mat_foo_3x3 * 2.0f;
	float3x4 mat_mul_f_3x4 = mat_foo_3x4 * 2.0f;
	float4x3 mat_mul_f_4x3 = mat_foo_4x3 * 2.0f;
	float4x4 mat_mul_f_4x4 = mat_foo_4x4 * 2.0f;

	// Division

	float1x1 mat_div_1x1 = mat_foo_1x1 / mat_bar_1x1;
	float1x2 mat_div_1x2 = mat_foo_1x2 / mat_bar_1x2;
	float1x3 mat_div_1x3 = mat_foo_1x3 / mat_bar_1x3;
	float1x4 mat_div_1x4 = mat_foo_1x4 / mat_bar_1x4;
	float2x1 mat_div_2x1 = mat_foo_2x1 / mat_bar_2x1;
	float3x1 mat_div_3x1 = mat_foo_3x1 / mat_bar_3x1;
	float4x1 mat_div_4x1 = mat_foo_4x1 / mat_bar_4x1;
	float2x2 mat_div_2x2 = mat_foo_2x2 / mat_bar_2x2;
	float2x3 mat_div_2x3 = mat_foo_2x3 / mat_bar_2x3;
	float2x4 mat_div_2x4 = mat_foo_2x4 / mat_bar_2x4;
	float3x2 mat_div_3x2 = mat_foo_3x2 / mat_bar_3x2;
	float4x2 mat_div_4x2 = mat_foo_4x2 / mat_bar_4x2;
	float3x3 mat_div_3x3 = mat_foo_3x3 / mat_bar_3x3;
	float3x4 mat_div_3x4 = mat_foo_3x4 / mat_bar_3x4;
	float4x3 mat_div_4x3 = mat_foo_4x3 / mat_bar_4x3;
	float4x4 mat_div_4x4 = mat_foo_4x4 / mat_bar_4x4;

	float1x1 mat_div_v_1x1 = mat_foo_1x1 / vfoo1;
	float1x2 mat_div_v_1x2 = mat_foo_1x2 / vfoo1;
	float1x3 mat_div_v_1x3 = mat_foo_1x3 / vfoo1;
	float1x4 mat_div_v_1x4 = mat_foo_1x4 / vfoo1;
	float2x1 mat_div_v_2x1 = mat_foo_2x1 / vfoo1;
	float3x1 mat_div_v_3x1 = mat_foo_3x1 / vfoo1;
	float4x1 mat_div_v_4x1 = mat_foo_4x1 / vfoo1;
	float2x2 mat_div_v_2x2 = mat_foo_2x2 / vfoo1;
	float2x3 mat_div_v_2x3 = mat_foo_2x3 / vfoo1;
	float2x4 mat_div_v_2x4 = mat_foo_2x4 / vfoo1;
	float3x2 mat_div_v_3x2 = mat_foo_3x2 / vfoo1;
	float4x2 mat_div_v_4x2 = mat_foo_4x2 / vfoo1;
	float3x3 mat_div_v_3x3 = mat_foo_3x3 / vfoo1;
	float3x4 mat_div_v_3x4 = mat_foo_3x4 / vfoo1;
	float4x3 mat_div_v_4x3 = mat_foo_4x3 / vfoo1;
	float4x4 mat_div_v_4x4 = mat_foo_4x4 / vfoo1;

	float1x1 mat_div_f_1x1 = mat_foo_1x1 / 2.0f;
	float1x2 mat_div_f_1x2 = mat_foo_1x2 / 2.0f;
	float1x3 mat_div_f_1x3 = mat_foo_1x3 / 2.0f;
	float1x4 mat_div_f_1x4 = mat_foo_1x4 / 2.0f;
	float2x1 mat_div_f_2x1 = mat_foo_2x1 / 2.0f;
	float3x1 mat_div_f_3x1 = mat_foo_3x1 / 2.0f;
	float4x1 mat_div_f_4x1 = mat_foo_4x1 / 2.0f;
	float2x2 mat_div_f_2x2 = mat_foo_2x2 / 2.0f;
	float2x3 mat_div_f_2x3 = mat_foo_2x3 / 2.0f;
	float2x4 mat_div_f_2x4 = mat_foo_2x4 / 2.0f;
	float3x2 mat_div_f_3x2 = mat_foo_3x2 / 2.0f;
	float4x2 mat_div_f_4x2 = mat_foo_4x2 / 2.0f;
	float3x3 mat_div_f_3x3 = mat_foo_3x3 / 2.0f;
	float3x4 mat_div_f_3x4 = mat_foo_3x4 / 2.0f;
	float4x3 mat_div_f_4x3 = mat_foo_4x3 / 2.0f;
	float4x4 mat_div_f_4x4 = mat_foo_4x4 / 2.0f;

	// Matrix - matrix multiplication

	float1x1 mat_mmul_1x1_1x1 = mul(mat_foo_1x1, mat_bar_1x1);
	float1x2 mat_mmul_1x1_1x2 = mul(mat_foo_1x1, mat_bar_1x2);
	float1x3 mat_mmul_1x1_1x3 = mul(mat_foo_1x1, mat_bar_1x3);
	float1x4 mat_mmul_1x1_1x4 = mul(mat_foo_1x1, mat_bar_1x4);

	float2x1 mat_mmul_2x1_1x1 = mul(mat_bar_2x1, mat_foo_1x1);
	float2x2 mat_mmul_2x1_1x2 = mul(mat_bar_2x1, mat_foo_1x2);
	float2x3 mat_mmul_2x1_1x3 = mul(mat_bar_2x1, mat_foo_1x3);
	float2x4 mat_mmul_2x1_1x4 = mul(mat_bar_2x1, mat_foo_1x4);
	
	float3x1 mat_mmul_3x1_1x1 = mul(mat_bar_3x1, mat_foo_1x1);
	float3x2 mat_mmul_3x1_1x2 = mul(mat_bar_3x1, mat_foo_1x2);
	float3x3 mat_mmul_3x1_1x3 = mul(mat_bar_3x1, mat_foo_1x3);
	float3x4 mat_mmul_3x1_1x4 = mul(mat_bar_3x1, mat_foo_1x4);

	float4x1 mat_mmul_4x1_1x1 = mul(mat_bar_4x1, mat_foo_1x1);
	float4x2 mat_mmul_4x1_1x2 = mul(mat_bar_4x1, mat_foo_1x2);
	float4x3 mat_mmul_4x1_1x3 = mul(mat_bar_4x1, mat_foo_1x3);
	float4x4 mat_mmul_4x1_1x4 = mul(mat_bar_4x1, mat_foo_1x4);
	
	float1x1 mat_mmul_1x2_2x1 = mul(mat_bar_1x2, mat_foo_2x1);
	float1x2 mat_mmul_1x2_2x2 = mul(mat_bar_1x2, mat_foo_2x2);
	float1x3 mat_mmul_1x2_2x3 = mul(mat_bar_1x2, mat_foo_2x3);
	float1x4 mat_mmul_1x2_2x4 = mul(mat_bar_1x2, mat_foo_2x4);

	float1x1 mat_mmul_1x3_3x1 = mul(mat_bar_1x3, mat_foo_3x1);
	float1x2 mat_mmul_1x3_3x2 = mul(mat_bar_1x3, mat_foo_3x2);
	float1x3 mat_mmul_1x3_3x3 = mul(mat_bar_1x3, mat_foo_3x3);
	float1x4 mat_mmul_1x3_3x4 = mul(mat_bar_1x3, mat_foo_3x4);

	float1x1 mat_mmul_1x4_4x1 = mul(mat_bar_1x4, mat_foo_4x1);
	float1x2 mat_mmul_1x4_4x2 = mul(mat_bar_1x4, mat_foo_4x2);
	float1x3 mat_mmul_1x4_4x3 = mul(mat_bar_1x4, mat_foo_4x3);
	float1x4 mat_mmul_1x4_4x4 = mul(mat_bar_1x4, mat_foo_4x4);

	float2x1 mat_mmul_2x2_2x1 = mul(mat_bar_2x2, mat_foo_2x1);
	float2x2 mat_mmul_2x2_2x2 = mul(mat_bar_2x2, mat_foo_2x2);
	float2x3 mat_mmul_2x2_2x3 = mul(mat_bar_2x2, mat_foo_2x3);
	float2x4 mat_mmul_2x2_2x4 = mul(mat_bar_2x2, mat_foo_2x4);

	float3x1 mat_mmul_3x2_2x1 = mul(mat_bar_3x2, mat_foo_2x1);
	float3x2 mat_mmul_3x2_2x2 = mul(mat_bar_3x2, mat_foo_2x2);
	float3x3 mat_mmul_3x2_2x3 = mul(mat_bar_3x2, mat_foo_2x3);
	float3x4 mat_mmul_3x2_2x4 = mul(mat_bar_3x2, mat_foo_2x4);

	float4x1 mat_mmul_4x2_2x1 = mul(mat_bar_4x2, mat_foo_2x1);
	float4x2 mat_mmul_4x2_2x2 = mul(mat_bar_4x2, mat_foo_2x2);
	float4x3 mat_mmul_4x2_2x3 = mul(mat_bar_4x2, mat_foo_2x3);
	float4x4 mat_mmul_4x2_2x4 = mul(mat_bar_4x2, mat_foo_2x4);

	float2x1 mat_mmul_2x3_3x1 = mul(mat_bar_2x3, mat_foo_3x1);
	float2x2 mat_mmul_2x3_3x2 = mul(mat_bar_2x3, mat_foo_3x2);
	float2x3 mat_mmul_2x3_3x3 = mul(mat_bar_2x3, mat_foo_3x3);
	float2x4 mat_mmul_2x3_3x4 = mul(mat_bar_2x3, mat_foo_3x4);

	float2x1 mat_mmul_2x4_4x1 = mul(mat_bar_2x4, mat_foo_4x1);
	float2x2 mat_mmul_2x4_4x2 = mul(mat_bar_2x4, mat_foo_4x2);
	float2x3 mat_mmul_2x4_4x3 = mul(mat_bar_2x4, mat_foo_4x3);
	float2x4 mat_mmul_2x4_4x4 = mul(mat_bar_2x4, mat_foo_4x4);

	float3x1 mat_mmul_3x3_3x1 = mul(mat_bar_3x3, mat_foo_3x1);
	float3x2 mat_mmul_3x3_3x2 = mul(mat_bar_3x3, mat_foo_3x2);
	float3x3 mat_mmul_3x3_3x3 = mul(mat_bar_3x3, mat_foo_3x3);
	float3x4 mat_mmul_3x3_3x4 = mul(mat_bar_3x3, mat_foo_3x4);

	float3x1 mat_mmul_3x4_4x1 = mul(mat_bar_3x4, mat_foo_4x1);
	float3x2 mat_mmul_3x4_4x2 = mul(mat_bar_3x4, mat_foo_4x2);	
	float3x3 mat_mmul_3x4_4x3 = mul(mat_bar_3x4, mat_foo_4x3);
	float3x4 mat_mmul_3x4_4x4 = mul(mat_bar_3x4, mat_foo_4x4);

	float4x1 mat_mmul_4x3_3x1 = mul(mat_bar_4x3, mat_foo_3x1);
	float4x2 mat_mmul_4x3_3x2 = mul(mat_bar_4x3, mat_foo_3x2);
	float4x3 mat_mmul_4x3_3x3 = mul(mat_bar_4x3, mat_foo_3x3);
	float4x4 mat_mmul_4x3_3x4 = mul(mat_bar_4x3, mat_foo_3x4);

	float4x1 mat_mmul_4x4_4x1 = mul(mat_bar_4x4, mat_foo_4x1);
	float4x2 mat_mmul_4x4_4x2 = mul(mat_bar_4x4, mat_foo_4x2);
	float4x3 mat_mmul_4x4_4x3 = mul(mat_bar_4x4, mat_foo_4x3);
	float4x4 mat_mmul_4x4_4x4 = mul(mat_bar_4x4, mat_foo_4x4);

	// Matrix-vector multiplication

	float1 vec_vmul_1x1_v1 = mul(mat_foo_1x1, vfoo1);
	float1 vec_vmul_1x2_v2 = mul(mat_foo_1x2, vfoo2);
	float1 vec_vmul_1x3_v3 = mul(mat_foo_1x3, vfoo3);
	float1 vec_vmul_1x4_v4 = mul(mat_foo_1x4, vfoo4);

	float2 vec_vmul_2x1_v1 = mul(mat_foo_2x1, vfoo1);
	float2 vec_vmul_2x2_v2 = mul(mat_foo_2x2, vfoo2);
	float2 vec_vmul_2x3_v3 = mul(mat_foo_2x3, vfoo3);
	float2 vec_vmul_2x4_v4 = mul(mat_foo_2x4, vfoo4);

	float3 vec_vmul_3x1_v1 = mul(mat_foo_3x1, vfoo1);
	float3 vec_vmul_3x2_v2 = mul(mat_foo_3x2, vfoo2);
	float3 vec_vmul_3x3_v3 = mul(mat_foo_3x3, vfoo3);
	float3 vec_vmul_3x4_v4 = mul(mat_foo_3x4, vfoo4);

	float4 vec_vmul_4x1_v1 = mul(mat_foo_4x1, vfoo1);
	float4 vec_vmul_4x2_v2 = mul(mat_foo_4x2, vfoo2);
	float4 vec_vmul_4x3_v3 = mul(mat_foo_4x3, vfoo3);
 	float4 vec_vmul_4x4_v4 = mul(mat_foo_4x4, vfoo4);

	// Matrix transposition

	float1x1 mat_transp_1x1 = transpose(mat_foo_1x1);

	float1x2 mat_transp_1x2 = transpose(mat_foo_2x1);
	float2x2 mat_transp_2x2 = transpose(mat_foo_2x2);
	float3x2 mat_transp_3x2 = transpose(mat_foo_2x3);
	float4x2 mat_transp_4x2 = transpose(mat_foo_2x4);

	float1x3 mat_transp_1x3 = transpose(mat_foo_3x1);
	float2x3 mat_transp_2x3 = transpose(mat_foo_3x2);
	float3x3 mat_transp_3x3 = transpose(mat_foo_3x3);
	float4x3 mat_transp_4x3 = transpose(mat_foo_3x4);

	float1x4 mat_transp_1x4 = transpose(mat_foo_4x1);
	float2x4 mat_transp_2x4 = transpose(mat_foo_4x2);
	float3x4 mat_transp_3x4 = transpose(mat_foo_4x3);
	float4x4 mat_transp_4x4 = transpose(mat_foo_4x4);

	// Determinants

	float1 mat_det_2x2 = determinant(mat_foo_2x2);
	float1 mat_det_3x3 = determinant(mat_foo_3x3);
	float1 mat_det_4x4 = determinant(mat_foo_4x4);

	// Inverses

	float2x2 mat_inv_2x2 = inverse(mat_foo_2x2);
	float3x3 mat_inv_3x3 = inverse(mat_foo_3x3);
	float4x4 mat_inv_4x4 = inverse(mat_foo_4x4);
}

void RunExperiments()
{
	float4 test;
	float4 testResult;
	test = float4(52730508.0f);
	testResult = sin(test);

	test = float4(-5.80792141f);
	testResult = sin(test);
	test = float4(-0.0f);
	testResult = sin(test);
	test = float4(1.0f);
	testResult = sin(test);
	test = float4(-1.0f);
	testResult = sin(test);
	test = float4(2.0f);
	testResult = sin(test);
	test = float4(-2.0f);
	testResult = sin(test);
	test = float4(3.0f);
	testResult = sin(test);
	test = float4(-3.0f);
	testResult = sin(test);
	test = float4(4.0f);
	testResult = sin(test);
	test = float4(-4.0f);
	testResult = sin(test);
	test = float4(5.0f);
	testResult = sin(test);
	test = float4(-5.0f);
	testResult = sin(test);
	test = float4(6.1f);
	testResult = sin(test);
	test = float4(-7.0f);
	testResult = sin(test);

	float4 nan = float4(1.0f) / float4(0.0f);
	float4 subtractNan = float4(1.0f) - nan;

	Float_t f(52730508.0f);

	Float_t maxfloatasint(1.0e5f);
	Float_t minfloatasint(0.0f);
	//Float_t maxfloatasint(1.0f);
	const uint32_t signBit = 0x80000000;

	// Max error vs. std::atan = 2.62260437e-6

	//ExhaustiveTest(0, (uint32_t) maxfloatasint.i, _mm_asin_ps, std::asin, "asin");
	//ExhaustiveTest(signBit, signBit | (uint32_t) maxfloatasint.i, _mm_asin_ps, std::asin, "asin");

	//ExhaustiveTest(0, (uint32_t)maxfloatasint.i, _mm_acos_ps, std::acos, "acos");
	//ExhaustiveTest(signBit, signBit | (uint32_t)maxfloatasint.i, _mm_acos_ps, std::acos, "acos");

	//ExhaustiveTest(0, (uint32_t)maxfloatasint.i, _mm_atan_ps, std::atan, "atan");
	//ExhaustiveTest(signBit, signBit | (uint32_t)maxfloatasint.i, _mm_atan_ps, std::atan, "atan");


// 	ExhaustiveTest((uint32_t)minfloatasint.i, (uint32_t)maxfloatasint.i, _hlslpp_sin_ps, std::sin, "sin");
// 	ExhaustiveTest(signBit | minfloatasint.i, signBit | (uint32_t)maxfloatasint.i, _hlslpp_sin_ps, std::sin, "sin");
// 
// 	ExhaustiveTest((uint32_t)minfloatasint.i, (uint32_t)maxfloatasint.i, _hlslpp_cos_ps, std::cos, "cos");
// 	ExhaustiveTest(signBit | minfloatasint.i, signBit | (uint32_t)maxfloatasint.i, _hlslpp_cos_ps, std::cos, "cos");
// 	
// 	ExhaustiveTest((uint32_t)minfloatasint.i, (uint32_t)maxfloatasint.i, _hlslpp_tan_ps, std::tan, "tan");
// 	ExhaustiveTest(signBit | minfloatasint.i, signBit | (uint32_t)maxfloatasint.i, _hlslpp_tan_ps, std::tan, "tan");

// 	ExhaustiveTest((uint32_t)minfloatasint.i, (uint32_t)maxfloatasint.i, _hlslpp_exp_ps, std::exp2, "exp2");
// 	ExhaustiveTest(signBit | minfloatasint.i, signBit | (uint32_t)maxfloatasint.i, _hlslpp_exp2_ps, std::exp2, "exp2");

	const float deg2rad = 3.14159265f / 180.0f;
	
	quaternion q1 = quaternion::euler(float3(0.0f * deg2rad, 0.0f * deg2rad, 0.0f * deg2rad));
	quaternion q2 = quaternion::euler(float3(180.0f * deg2rad, 0.0f * deg2rad, 0.0f * deg2rad));
	quaternion fax = quaternion::axisangle(float3(0.0f, 1.0f, 0.0f), 1.57f);
	
	quaternion slerp1 = slerp(q1, q2, 0.0f);
	quaternion slerp2 = slerp(q1, q2, 1.0f);

	quaternion slerp3 = slerp(q1, q2, 0.5f);

	//float2 p = (float2) q1.xyzw;
}

void RunSpeedTests()
{
	float f1 = (rand() % 1000) / 100.0f;
	float f2 = (rand() % 1000) / 100.0f;
	float f3 = (rand() % 1000) / 100.0f;
	float f4 = (rand() % 1000) / 100.0f;

	const int iter = 100;
	Timer timer;

	//// DirectX XMVECTOR
	//{
	//	using namespace DirectX;
//
	//	XMVECTOR v1 = XMVectorSet(f1, f1, f1, f1);
	//	XMVECTOR v2 = XMVectorSet(f2, f2, f2, f2);
	//	XMVECTOR v3 = XMVectorSet(f3, f3, f3, f3);
	//	XMVECTOR v4 = XMVectorSet(f4, f4, f4, f4);
//
	//	timer.Start();
	//	for (int i = 0; i < iter; ++i)
	//	{
	//		//v2 = XMVectorSqrt((v1 * v2 + v2 * v3));
	//		//v2 = XMVector4NormalizeEst(v2);
	//	}
	//	float time = timer.Get();
	//	float result[4];
	//	_mm_storeu_ps(result, v2);
	//	printf("DirectX XMVECTOR: %f, %f, %f, %f = %f\n", result[0], result[1], result[2], result[3], time);
	//}

	// Plain old struct vector
	{
// 		Vector4 v1(f1);
// 		Vector4 v2(f2);
// 		Vector4 v3(f3);
// 		Vector4 v4(f4);
// 
// 		timer.Start();
// 		for (int i = 0; i < iter; ++i)
// 		{
// 			v2 = sqrt((v1 * v2 + v2 * v3));
// 			//v2 = normalize(v2);
// 		}
// 		double time = timer.Get();
// 		printf("STRUCT: %f, %f, %f, %f = %f\n", v2.x, v2.y, v2.z, v2.w, time);
	}

	float4 v1(f1);
	float4 v2(2.1f);
	float4 v3(f3);
	float4 v4(f4);

	float4x4 mat_foo_4x4 = float4x4(10, 20, 1, 1,
									78, 5, 2, 8,
									14, 5, 5, 6,
									8, 4, 5, 6);

	timer.Start();
	for (int i = 0; i < iter; ++i)
	{
		v4 = v4.xxxx + v3.yyzw;
		//Vector4 yyzw = Vector4(v3f.y, v3f.y, v3f.z, v3f.w);
		//Vector4 xxxx = Vector4(v4f.x, v4f.x, v4f.x, v4f.x);
		//v4f = xxxx + yyzw;
	}
	double time = timer.Get();
	printf("float4: %f, %f, %f, %f = %f\n", (float)v4.x, (float)v4.y, (float)v4.z, (float)v4.w, time);
	//printf("Vector4: %f, %f, %f, %f\n\n", (float)v4f.x, (float)v4f.y, (float)v4f.z, (float)v4f.w);
	printf("Elapsed = %f\n", time);
}

int main()
{
	RunUnitTests();
	RunSpeedTests();
	RunExperiments();

	getchar();
}