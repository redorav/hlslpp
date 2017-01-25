#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include <cstdio>
#include <iostream>

//#include "DirectXMath.h"

#include "hlsl++.h"
#include "hlsl++_unit_tests.h"

using std::cout;

struct Vector4
{
	float x, y, z, w;

	Vector4(float f) : x(f), y(f), z(f), w(f) {}
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	inline Vector4 operator + (const Vector4& v) { return Vector4(x + v.x, y + v.y, z + v.z, w + v.w); }
	inline Vector4& operator += (const Vector4& v)
	{ 
		x += v.x; y += v.y; z += v.z; w += v.w;
		return *this;
	}

	inline Vector4 operator * (const Vector4& v) { return Vector4(x * v.x, y * v.y, z * v.z, w * v.w); }	
	inline Vector4& operator = (const Vector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
};

inline Vector4 operator / (const Vector4& v1, const Vector4& v2)
{ 
	return Vector4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

inline float dot(const Vector4& v1, const Vector4& v2) 
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline Vector4 exp2(const Vector4& v)
{
	return Vector4(std::exp2(v.x), std::exp2(v.y), std::exp2(v.z), std::exp2(v.w));
}

inline Vector4 exp(const Vector4& v)
{
	return Vector4(std::exp(v.x), std::exp(v.y), std::exp(v.z), std::exp(v.w));
}

inline Vector4 length(const Vector4& v)
{
	return Vector4(sqrt(dot(v, v)));
}

inline Vector4 sqrt(const Vector4& v)
{
	float sqrtX = sqrtf(v.x);
	float sqrtY = sqrtf(v.y);
	float sqrtZ = sqrtf(v.z);
	float sqrtW = sqrtf(v.w);
	return Vector4(sqrtX, sqrtY, sqrtZ, sqrtW);
}

inline Vector4 normalize(const Vector4& v)
{
	return v / length(v);
}

class Timer
{
private:
	LARGE_INTEGER m_startTime, m_endTime, m_elapsedMicroseconds;
	LARGE_INTEGER m_frequency;

public:
	void Start()
	{
		QueryPerformanceFrequency(&m_frequency);
		QueryPerformanceCounter(&m_startTime);
	}

	double Get()
	{
		QueryPerformanceCounter(&m_endTime);
		m_elapsedMicroseconds.QuadPart = m_endTime.QuadPart - m_startTime.QuadPart;
		m_elapsedMicroseconds.QuadPart *= 1000000;
		m_elapsedMicroseconds.QuadPart /= m_frequency.QuadPart;

		return double(m_elapsedMicroseconds.QuadPart) / 1.0e6;
	}
};

int main()
{
	const int iter = 100000000000000;
	Timer timer;

	float f1 = (rand() % 1000) / 100.0f;
	float f2 = (rand() % 1000) / 100.0f;
	float f3 = (rand() % 1000) / 100.0f;
	float f4 = (rand() % 1000) / 100.0f;

	float4 minv = float4(2.0f);
	float4 maxv = float4(3.0f);

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
		Vector4 v1(f1);
		Vector4 v2(f2);
		Vector4 v3(f3);
		Vector4 v4(f4);

		timer.Start();
		for (int i = 0; i < iter; ++i)
		{
			//v2 = sqrt((v1 * v2 + v2 * v3));
			//v2 = normalize(v2);
		}
		float time = timer.Get();
		printf("STRUCT: %f, %f, %f, %f = %f\n", v2.x, v2.y, v2.z, v2.w, time);
	}

	// Raw SSE intrinsics
	{
		//__m128 v1 = _mm_set_ps1(f1);
		//__m128 v2 = _mm_set_ps1(f2);
		//__m128 v3 = _mm_set_ps1(f3);
		//__m128 v4 = _mm_set_ps1(f4);

		//StartCounter();
		//for (int i = 0; i < iter; ++i)
		//{
		//	//v2 = _mm_sqrt_ps(_mm_add_ps(_mm_mul_ps(v1, v2), _mm_mul_ps(v2, v3)));
		//
		//	//__m128 m = _mm_mul_ps(v1, v2);			// Multiply components together
		//	//__m128 h1 = _mm_hadd_ps(m, m);			// Add once
		//	//__m128 h2 = _mm_hadd_ps(h1, h1);		// Add twice
		//	v2 = _mm_dp_ps(v1, v2, 0xff);
		//}
		//float time = GetCounter();
		//float result[4];
		//_mm_storeu_ps(result, v2);
		//printf("Raw SSE: %f, %f, %f, %f = %f\n", result[0], result[1], result[2], result[3], time);
	}

	// float4
	{
		

		//float result[4];
		//_mm_storeu_ps(result, v2.xyzw);

		std::string s = "Hello\nWorld;";

		float4x4 m1 = {
			1, 2, 3, 4, 
			1, 2, 3, 5, 
			3, 1, 9, 7, 
			2, 4, 4, 1 };

		float4x4 m2 = {
			1, 2, 3, 4,
			1, 2, 3, 5,
			3, 1, 9, 7,
			2, 4, 4, 1 };

		//m2 += m1;

		float4x4 m3 = mul(m1, m2);

		//float4x3 = 

		//float2x2 m2x2;
		//float2x2 m2x2_2;

		//float2x2 m_lala = mul(m2x2, m2x2_2);

		float4 vec0 = { 1, 2, 3, 4 };

		float4 result = mul(m1, vec0);

		result = float4(134, 0, 71,81);
		float4 allNotZero = all(result);

		float4 one = float4(1);
		float4 zero = float4(0);

		float4 inf = -one / zero;
		float4 nan = sqrt(-one);

		float a = 3.0f;

		float4 perry1(1, 2, 3, 4);
		float4 perry2(5, 6, 7, 8);

		//float1 perry1 = float1x1(1.0f);
		//float2 perry2 = float2x1(1.0f, 2.0f);
		//float3 perry3 = float3x1(1.0f, 2.0f, 3.0f);
		//float4 perry4 = float4x1(1.0f, 2.0f, 3.0f, 4.0f);

		float lala = 0.0f;

		//inf.x = 1.0f;
		//inf.y = 1.0f / lala;
		//inf.z = -1.0f / lala;
		//inf.w = -0.0f / lala;

		float2x2 m2x2_1 = float2x2(1, 2, 3, 4);
		float2x2 m2x2_2 = float2x2(5, 6, 7, 8);

		float2x2 m2x2_3 = mul(m2x2_1, m2x2_2);

		float1x1 lalala1x1(9);
		float1 lalalala1 = lalala1x1._m00;

		//float4 isinfinite = isfinite(inf.xyzw);
		
//		RunExperiments();
		RunUnitTests();

		float4 v1(f1);
		float4 v2(2.1f);
		float4 v3(f3);
		float4 v4(f4);

		timer.Start();
		for (int i = 0; i < iter; ++i)
		{
			//v2 = sqrt((v1 * v2 + v2 * v3));
			//float4 cosv2 = cos(v2);
		//	float sinv2 = exp2(v2);
			//v1 = exp2(v1);
			v2 = lerp(v1, v2, v2);
			//v3 = exp2(v3);
			//v4 = exp2(v4);
			//v3 = sinv2; 
		}
		float time = timer.Get();
		printf("float4: %f, %f, %f, %f = %f\n", (float)v2.x, (float)v2.y, (float)v2.z, (float)v2.w, time);
	}

	getchar();
}