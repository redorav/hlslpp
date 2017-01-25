#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

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
		
	RunExperiments();
	RunUnitTests();
	RunSpeedTests();

	getchar();
}