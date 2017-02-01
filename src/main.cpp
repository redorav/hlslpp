
#if defined(_WIN32)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <cstdio>
#include <iostream>

#include "hlsl++.h"
#include "hlsl++_unit_tests.h"

using std::cout;

int main()
{
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

	float a = 3.0f;

	float4 perry1(1, 2, 3, 4);
	float4 perry2(5, 6, 7, 8);

	float2x2 m2x2_1 = float2x2(1, 2, 3, 4);
	float2x2 m2x2_2 = float2x2(5, 6, 7, 8);

	float2x2 m2x2_3 = mul(m2x2_1, m2x2_2);

	float4x4 mat0 = float4x4(	1, 2, 3, 4,
								5, 6, 7, 8,
								9, 10, 11, 12,
								13, 14, 15, 16);
	
	float4 vec0(1, 2, 3, 4);
	float4 vec1(1, 2, 3, 4);
	float4 vec2(1, 2, 3, 4);

	//float1 alpha = float1(0);

	float4 lrp = lerp(vec0.bgra, vec1.rrgb, vec2.rrrr);
	//float4 lrp2 = lerp(vec0.bgra, vec1.rrgb, alpha);

	float4 cmVec = mul(mat0, vec0);
	float4 rmVec = mul(vec0, mat0);

	float2 vec20 = float2(1, 2);
	float2 vec21 = float2(1, 2);

	float1 dot2_0 = dot(vec20.yx, vec21);

	RunSpeedTests();
	RunUnitTests();
	RunExperiments();

	getchar();
}