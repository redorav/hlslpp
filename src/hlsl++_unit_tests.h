#include "hlsl++.h"
#include <cassert>

//#include "DirectXMath.h"

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
typedef __m128(*Transform4)(__m128);

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
#if defined(__clang__)
		Float_t testValue = TestFunc(_mm_set_ps1(input.f))[0];
#else
		Float_t testValue = TestFunc(_mm_set_ps1(input.f)).m128_f32[0];
#endif
		Float_t refValue = RefFunc(input.f);
		
		//if  (testValue.f != refValue.f && // If the results don’t match then report an error.
		//	(testValue.f == testValue.f || refValue.f == refValue.f)) // If both results are NaNs then we treat that as a match.
		//{
		float absError = std::abs(testValue.f - refValue.f);
		
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

void RunUnitTests()
{
	float f1 = rand();
	float f2 = rand();
	float f3 = rand();
	float f4 = rand();

	// Initialization

	float1 vfoo1 = float1(f1); assert((float)vfoo1.x == f1);
	float2 vfoo2 = float2(1, 2);
	float3 vfoo3 = float3(1, 2, 3);
	float4 vfoo4 = float4(1, 2, 3, 4);

	vfoo1 = float1(1);
	vfoo2 = float2(1, 2);
	vfoo3 = float3(1, 2, 3);
	vfoo4 = float4(1, 2, 3, 4);

	float1 vbar1 = vfoo1.x;
	float2 vbar2 = vfoo2.gr;
	float3 vbar3 = vfoo3.zyx;
	float4 vbar4 = vfoo4.bgra;

	float1 vbaz1 = float1(0.2f);
	float2 vbaz2 = float2(0.3f, 0.7f);
	float3 vbaz3 = float3(0.1f, 0.4f, 0.8f);
	float4 vbaz4 = float4(0.0f, 0.2f, 0.6f, 1.0f);

	// Addition

	float1 vadd1 = vfoo1 + vbar1;
	float2 vadd2 = vfoo2 + vbar2;
	float3 vadd3 = vfoo3 + vbar3;
	float4 vadd4 = vfoo4 + vbar4;

	// Subtraction

	float1 vsub1 = vfoo1 - vbar1;
	float2 vsub2 = vfoo2 - vbar2;
	float3 vsub3 = vfoo3 - vbar3;
	float4 vsub4 = vfoo4 - vbar4;

	// Multiplication

	float1 vmul1 = vfoo1 * vbar1;
	float2 vmul2 = vfoo2 * vbar2;
	float3 vmul3 = vfoo3 * vbar3;
	float4 vmul4 = vfoo4 * vbar4;

	// Division

	float1 vdiv1 = vfoo1 / vbar1;
	float2 vdiv2 = vfoo2 / vbar2;
	float3 vdiv3 = vfoo3 / vbar3;
	float4 vdiv4 = vfoo4 / vbar4;

	float1 vgt1 = vfoo1 > vbar1;
	float2 vgt2 = vfoo2 > vbar2;
	float3 vgt3 = vfoo3 > vbar3;
	float4 vgt4 = vfoo4 > vbar4;

	float1 vlt1 = vfoo1 < vbar1;
	float2 vlt2 = vfoo2 < vbar2;
	float3 vlt3 = vfoo3 < vbar3;
	float4 vlt4 = vfoo4 < vbar4;

	float2 vge2 = vfoo2 >= vbar2;
	float3 vge3 = vfoo3 >= vbar3;
	float4 vge4 = vfoo4 >= vbar4;

	float2 vle2 = vfoo2 <= vbar2;
	float3 vle3 = vfoo3 <= vbar3;
	float4 vle4 = vfoo4 <= vbar4;

	float2 veq2 = vfoo2 == vbar2;
	float3 veq3 = vfoo3 == vbar3;
	float4 veq4 = vfoo4 == vbar4;

	vfoo2 = -vbar2.gr;
	vfoo3 = -vbar3.bgg;
	vfoo4 = -vbar4.rrrr;

	float2 vabs2 = abs(vfoo2);
	float3 vabs3 = abs(vfoo3);
	float4 vabs4 = abs(vfoo4);

	float2 vceil2 = ceil(vfoo2);
	float3 vceil3 = ceil(vfoo3);
	float4 vceil4 = ceil(vfoo4);

	float3 vcross3 = cross(vfoo3, vbar3);
	float3 vcross_swiz3 = cross(vfoo3.yzx, vbar3.yyx);

	float2 vfloor2 = floor(vfoo2);
	float3 vfloor3 = floor(vfoo3);
	float4 vfloor4 = floor(vfoo4);

	float2 vfrac2 = frac(vfoo2);
	float3 vfrac3 = frac(vfoo3);
	float4 vfrac4 = frac(vfoo4);

	float2 vexp2 = exp(vfoo2);
	float3 vexp3 = exp(vfoo3);
	float4 vexp4 = exp(vfoo4);

	float2 vexp2_2 = exp2(vfoo2);
	float3 vexp2_3 = exp2(vfoo3);
	float4 vexp2_4 = exp2(vfoo4);

	// Linear Interpolation

	float2 vlerp2 = lerp(vfoo2, vbar2, vbaz2);
	float3 vlerp3 = lerp(vfoo3, vbar3, vbaz3);
	float4 vlerp4 = lerp(vfoo4, vbar4, vbaz4);

	float2 vlerpf_2 = lerp(vfoo2, vbar2, 0.3f);
	float3 vlerpf_3 = lerp(vfoo3, vbar3, 0.5f);
	float4 vlerpf_4 = lerp(vfoo4, vbar4, 0.7f);

	float2 vlerp_swiz2 = lerp(vfoo2, vbar2, vbaz2.rg);
	float3 vlerp_swiz3 = lerp(vfoo3, vbar3, vbaz3.bgr);
	float4 vlerp_swiz4 = lerp(vfoo4, vbar4, vbaz4.rgba);

	float2 vlog2 = log(vfoo2);
	float3 vlog3 = log(vfoo3);
	float4 vlog4 = log(vfoo4);

	float2 vlog2_2 = log2(vfoo2);
	float3 vlog2_3 = log2(vfoo3);
	float4 vlog2_4 = log2(vfoo4);

	float2 vlog10_2 = log10(vfoo2);
	float3 vlog10_3 = log10(vfoo3);
	float4 vlog10_4 = log10(vfoo4);

	float2 vmin2 = min(vfoo2, vbar2);
	float3 vmin3 = min(vfoo3, vbar3);
	float4 vmin4 = min(vfoo4, vbar4);

	float2 vmax2 = max(vfoo2, vbar2);
	float3 vmax3 = max(vfoo3, vbar3);
	float4 vmax4 = max(vfoo4, vbar4);

	float2 vrsqrt2 = rsqrt(vfoo2);
	float3 vrsqrt3 = rsqrt(vfoo3);
	float4 vrsqrt4 = rsqrt(vfoo4);

	float2 vround2 = round(vfoo2);
	float3 vround3 = round(vfoo3);
	float4 vround4 = round(vfoo4);

	float2 vsaturate2 = saturate(vfoo2);
	float3 vsaturate3 = saturate(vfoo3);
	float4 vsaturate4 = saturate(vfoo4);

	float2 vsign2 = sign(vfoo2);
	float3 vsign3 = sign(vfoo3);
	float4 vsign4 = sign(vfoo4);

	float2 vsin2 = sin(vfoo2);
	float3 vsin3 = sin(vfoo3);
	float4 vsin4 = sin(vfoo4);

	float2 vsqrt2 = sqrt(vfoo2);
	float3 vsqrt3 = sqrt(vfoo3);
	float4 vsqrt4 = sqrt(vfoo4);

	float2 vstep2 = step(vfoo2, vbar2);
	float3 vstep3 = step(vfoo3, vbar3);
	float4 vstep4 = step(vfoo4, vbar4);

	float2 vtrunc2 = trunc(vfoo2);
	float3 vtrunc3 = trunc(vfoo3);
	float4 vtrunc4 = trunc(vfoo4);

	float2 vassign2 = vfoo2.yx;
	vassign2 = vfoo2.yy;
	vassign2.rg = vfoo2;
	vassign2.rg = vfoo2.gr;

	float3 vassign3 = vfoo3.yxz;
	vassign3 = vfoo3.yyx;
	vassign3.rgb = vfoo3;
	vassign3.rgb = vfoo3.grr;

	float4 vassign4 = vfoo4.yxzw;
	vassign4 = vfoo4.yyxx;
	vassign4.bgra = vfoo4;
	vassign4.rgba = vfoo4.grba;

	float2 vneg_swiz_2 = -vfoo2.yx;
	float3 vexp_swiz_3 = exp(vfoo4.bgr);

	// Addition
	float4 vadd_swiz_a_4 = vfoo4 + vbar4.yxzw;
	float4 vadd_swiz_b_4 = vfoo4.bgra + vbar4.yxzw;
	float4 vadd_swiz_c_4 = vfoo4.bgra + vbar4;

	float3 vadd_swiz_a_3 = vfoo3 + vbar3.yxz;
	float3 vadd_swiz_b_3 = vfoo3.bgr + vbar3.xyz;
	float3 vadd_swiz_c_3 = vfoo3.bgr + vbar3;

	float2 vadd_swiz_a_2 = vfoo2 + vbar2.yx;
	float2 vadd_swiz_b_2 = vfoo2.gr + vbar2.yx;
	float2 vadd_swiz_c_2 = vfoo2.rg + vbar2;

	vadd_swiz_a_2 += vfoo2;
	vadd_swiz_b_2 += vfoo2.xy;
	vadd_swiz_c_2.xy += vfoo2;
	vadd_swiz_c_2.gr += vfoo2.rg;

	// Subtraction
	float4 vsub_swiz_a_4 = vfoo4 - vbar4.yxzw;
	float4 vsub_swiz_b_4 = vfoo4.bgra - vbar4.yxzw;
	float4 vsub_swiz_c_4 = vfoo4.bgra - vbar4;
	vsub_swiz_c_4.bgra = vfoo4.argb - vbar4.ggbr;

	float3 vsub_swiz_a_3 = vfoo3 - vbar3.yxz;
	float3 vsub_swiz_b_3 = vfoo3.bgr - vbar3.xyz;
	float3 vsub_swiz_c_3 = vfoo3.bgr - vbar3;
	vsub_swiz_c_3.bgr = vfoo4.grb - vbar4.gbr;

	float2 vsub_swiz_a_2 = vfoo2 - vbar2.yx;
	float2 vsub_swiz_b_2 = vfoo2.gr - vbar2.yx;
	float2 vsub_swiz_c_2 = vfoo2.rg - vbar2;
	vsub_swiz_c_2.gr = vfoo4.rg - vbar4.gr;

	vsub_swiz_a_2 -= vfoo2;
	vsub_swiz_b_2 -= vfoo2.xy;
	vsub_swiz_c_2.xy -= vfoo2;
	vsub_swiz_c_2.gr -= vfoo2.rg;

	// Multiplication
	float4 vmul_swiz_a_4 = vfoo4 * vbar4.yxzw;
	float4 vmul_swiz_b_4 = vfoo4.bgra * vbar4.yxzw;
	float4 vmul_swiz_c_4 = vfoo4.bgra * vbar4;

	float3 vmul_swiz_a_3 = vfoo3 * vbar3.yxz;
	float3 vmul_swiz_b_3 = vfoo3.rgb * vbar3.xyz;
	float3 vmul_swiz_c_3 = vfoo3.bgr * vbar3;

	float2 vmul_swiz_a_2 = vfoo2 * vbar2.yx;
	float2 vmul_swiz_b_2 = vfoo2.gr * vbar2.yx;
	float2 vmul_swiz_c_2 = vfoo2.rg * vbar2;

	vadd_swiz_a_2 *= vfoo2;
	vadd_swiz_b_2 *= vfoo2.xy;
	vadd_swiz_c_2.xy *= vfoo2;
	vadd_swiz_c_2.gr *= vfoo2.rg;

	float2 vmin_swiz_2 = min(vfoo2.gr, vbar2.rg);
	float3 vmin_swiz_3 = min(vfoo3.ggb, vbar3.bgr);
	float4 vmin_swiz_4 = min(vfoo4.gggg, vbar4.brgr);

	vfoo4 = float4(10, 2, 30, 4);
	vbar4 = float4(9, 5, 6, 7);

	float2 vmax_swiz_2 = max(vfoo2.rg, vbar2.yx);
	float3 vmax_swiz_3 = max(vfoo3.gbr, vbar3.xyy);
	float4 vmax_swiz_4 = max(vfoo4.brga, vbar4.yxzw);

	// Infinities and NaNs

	float4 inf = -float4::one() / float4::zero(); //assert(all(inf != inf).x != 0.0f);
	float4 nan = sqrt(-float4::one());

	//*********
	// Matrices
	//*********


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

	
	ExhaustiveTest((uint32_t)minfloatasint.i, (uint32_t)maxfloatasint.i, _mm_sin_ps, std::sin, "sin");
	ExhaustiveTest(signBit | minfloatasint.i, signBit | (uint32_t)maxfloatasint.i, _mm_sin_ps, std::sin, "sin");

	ExhaustiveTest((uint32_t)minfloatasint.i, (uint32_t)maxfloatasint.i, _mm_cos_ps, std::cos, "cos");
	ExhaustiveTest(signBit | minfloatasint.i, signBit | (uint32_t)maxfloatasint.i, _mm_cos_ps, std::cos, "cos");
	
	ExhaustiveTest((uint32_t)minfloatasint.i, (uint32_t)maxfloatasint.i, _mm_tan_ps, std::tan, "tan");
	ExhaustiveTest(signBit | minfloatasint.i, signBit | (uint32_t)maxfloatasint.i, _mm_tan_ps, std::tan, "tan");

	ExhaustiveTest((uint32_t)minfloatasint.i, (uint32_t)maxfloatasint.i, _mm_exp_ps, std::exp2, "exp2");
	ExhaustiveTest(signBit | minfloatasint.i, signBit | (uint32_t)maxfloatasint.i, _mm_exp2_ps, std::exp2, "exp2");
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

void RunSpeedTests()
{
	float f1 = (rand() % 1000) / 100.0f;
	float f2 = (rand() % 1000) / 100.0f;
	float f3 = (rand() % 1000) / 100.0f;
	float f4 = (rand() % 1000) / 100.0f;

	const int iter = 100000000000000;
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

	float4 v1(f1);
	float4 v2(2.1f);
	float4 v3(f3);
	float4 v4(f4);

	timer.Start();
	for (int i = 0; i < iter; ++i)
	{
		v2 = lerp(v1, v2, v2);
	}
	float time = timer.Get();
	printf("float4: %f, %f, %f, %f = %f\n", (float)v2.x, (float)v2.y, (float)v2.z, (float)v2.w, time);
}