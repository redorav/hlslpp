#include "hlsl++.h"

#include "hlsl++_unit_tests.h"

void RunUnitTestsMatrixFloat()
{
	using namespace hlslpp_unit;

	//---------
	// Matrices
	//---------

	float f1 = (rand() % 1000) / 100.0f; float f5 = (rand() % 1000) / 100.0f; float f9 = (rand() % 1000) / 100.0f; float f13 = (rand() % 1000) / 100.0f; float f17 = (rand() % 1000) / 100.0f;
	float f2 = (rand() % 1000) / 100.0f; float f6 = (rand() % 1000) / 100.0f; float f10 = (rand() % 1000) / 100.0f; float f14 = (rand() % 1000) / 100.0f; float f18 = (rand() % 1000) / 100.0f;
	float f3 = (rand() % 1000) / 100.0f; float f7 = (rand() % 1000) / 100.0f; float f11 = (rand() % 1000) / 100.0f; float f15 = (rand() % 1000) / 100.0f; float f19 = (rand() % 1000) / 100.0f;
	float f4 = (rand() % 1000) / 100.0f; float f8 = (rand() % 1000) / 100.0f; float f12 = (rand() % 1000) / 100.0f; float f16 = (rand() % 1000) / 100.0f; float f20 = (rand() % 1000) / 100.0f;

	// Initialization

	float1 vfoo1 = float1(f1);												eq(vfoo1, f1);
	float2 vfoo2 = float2(f2, f3);											eq(vfoo2, f2, f3);
	float3 vfoo3 = float3(f4, f5, f6);										eq(vfoo3, f4, f5, f6);
	float4 vfoo4 = float4(f7, f8, f9, f10);									eq(vfoo4, f7, f8, f9, f10);

	float1x1 mat_foo_1x1 = float1x1(42.0f);
	float1x2 mat_foo_1x2 = float1x2(32.6f, 12.1f);
	float1x3 mat_foo_1x3 = float1x3(11.1f, 21.5f, 14.3f);
	float1x4 mat_foo_1x4 = float1x4(74.1f, 3.25f, 0.75f, 1.88f);
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
	eq(mat_mmul_1x1_1x1, 16.8000011f);

	float1x2 mat_mmul_1x1_1x2 = mul(mat_foo_1x1, mat_bar_1x2);
	eq(mat_mmul_1x1_1x2, 4.20000029f, 8.40000057f);

	float1x3 mat_mmul_1x1_1x3 = mul(mat_foo_1x1, mat_bar_1x3);
	eq(mat_mmul_1x1_1x3, 4.20000029f, 8.40000057f, 12.6000004f);

	float1x4 mat_mmul_1x1_1x4 = mul(mat_foo_1x1, mat_bar_1x4);
	eq(mat_mmul_1x1_1x4, 4.20000029f, 8.40000057f, 12.6000004f, 16.8000011f);

	float2x1 mat_mmul_2x1_1x1 = mul(mat_bar_2x1, mat_foo_1x1);
	eq(mat_mmul_2x1_1x1, 4.20000029f, 8.40000057f);
	
	float2x2 mat_mmul_2x1_1x2 = mul(mat_bar_2x1, mat_foo_1x2);
	eq(mat_mmul_2x1_1x2, 3.25999999f, 1.21000004f, 6.5199998f, 2.42000008f);
	
	float2x3 mat_mmul_2x1_1x3 = mul(mat_bar_2x1, mat_foo_1x3);
	eq(mat_mmul_2x1_1x3, 1.11000001f, 2.15000010f, 1.43000007f, 2.22000003f, 4.30000019f, 2.86000013f);
	
	float2x4 mat_mmul_2x1_1x4 = mul(mat_bar_2x1, mat_foo_1x4);
	eq(mat_mmul_2x1_1x4, 
		7.40999985f, 0.325000018f, 0.075000003f, 0.188000008f,
		14.8199997f, 0.650000036f, 0.150000006f, 0.376000017f);

	float3x1 mat_mmul_3x1_1x1 = mul(mat_bar_3x1, mat_foo_1x1); 
	eq(mat_mmul_3x1_1x1, 4.20000029f, 8.40000057f, 12.6000004f);

	float3x2 mat_mmul_3x1_1x2 = mul(mat_bar_3x1, mat_foo_1x2);
	eq(mat_mmul_3x1_1x2, 
		3.25999999f, 1.21000004f, 
		6.51999998f, 2.42000008f, 
		9.77999973f, 3.63000035f);
	
	float3x3 mat_mmul_3x1_1x3 = mul(mat_bar_3x1, mat_foo_1x3);
	eq(mat_mmul_3x1_1x3, 
		1.11000004f, 2.22000003f, 3.33000016f, 
		2.15000010f, 4.30000019f, 6.45000029f, 
		1.43000007f, 2.86000013f, 4.29000044f);
	
	float3x4 mat_mmul_3x1_1x4 = mul(mat_bar_3x1, mat_foo_1x4);
	eq(mat_mmul_3x1_1x4, 
		7.40999985f, 0.325000018f, 0.075000003f, 0.188000008f,
		14.8199997f, 0.650000036f, 0.150000006f, 0.376000017f,
		22.2299995f, 0.975000024f, 0.225000009f, 0.564000010f);

	float4x1 mat_mmul_4x1_1x1 = mul(mat_bar_4x1, mat_foo_1x1);
	eq(mat_mmul_4x1_1x1, 4.20000029f, 8.40000057f, 12.6000004f, 16.8000011f);
	
	float4x2 mat_mmul_4x1_1x2 = mul(mat_bar_4x1, mat_foo_1x2);
	eq(mat_mmul_4x1_1x2, 
		3.25999999f, 1.21000004f,
		6.51999998f, 2.42000008f,
		9.77999973f, 3.63000035f,
		13.0400000f, 4.84000015f
	);
	
	float4x3 mat_mmul_4x1_1x3 = mul(mat_bar_4x1, mat_foo_1x3);
	eq(mat_mmul_4x1_1x3, 
		1.11000001f, 2.15000010f, 1.43000007f,
		2.22000003f, 4.30000019f, 2.86000013f,
		3.33000016f, 6.45000029f, 4.29000044f,
		4.44000006f, 8.60000038f, 5.72000027f
	);
	
	float4x4 mat_mmul_4x1_1x4 = mul(mat_bar_4x1, mat_foo_1x4);
	eq(mat_mmul_4x1_1x4, 
		7.40999985f, 0.325000018f, 0.075000003f, 0.188000008f,
		14.8199997f, 0.650000036f, 0.150000006f, 0.376000017f,
		22.2299995f, 0.975000024f, 0.225000009f, 0.564000010f,
		29.6399994f, 1.300000070f, 0.300000012f, 0.752000034f
	);

	float1x1 mat_mmul_1x2_2x1 = mul(mat_bar_1x2, mat_foo_2x1);
	eq(mat_mmul_1x2_2x1, 0.5f);
	
	float1x2 mat_mmul_1x2_2x2 = mul(mat_bar_1x2, mat_foo_2x2);
	eq(mat_mmul_1x2_2x2, 0.700000048f, 1.00000000f);
	
	float1x3 mat_mmul_1x2_2x3 = mul(mat_bar_1x2, mat_foo_2x3);
	eq(mat_mmul_1x2_2x3, 0.900000036f, 1.20000005f, 1.50000000f);
	
	float1x4 mat_mmul_1x2_2x4 = mul(mat_bar_1x2, mat_foo_2x4);
	eq(mat_mmul_1x2_2x4, 1.10000002f, 1.40000010f, 1.70000005f, 2.0f);
	
	float1x1 mat_mmul_1x3_3x1 = mul(mat_bar_1x3, mat_foo_3x1);
	eq(mat_mmul_1x3_3x1, 1.40000010f);
	
	float1x2 mat_mmul_1x3_3x2 = mul(mat_bar_1x3, mat_foo_3x2);
	eq(mat_mmul_1x3_3x2, 2.20000005f, 2.80000019f);
	
	float1x3 mat_mmul_1x3_3x3 = mul(mat_bar_1x3, mat_foo_3x3);
	eq(mat_mmul_1x3_3x3, 3.00000024f, 3.60000014f, 4.19999981f);
	
	float1x4 mat_mmul_1x3_3x4 = mul(mat_bar_1x3, mat_foo_3x4);
	eq(mat_mmul_1x3_3x4, 3.80000019f, 4.40000010f, 5.0f, 5.60000038f);
	
	float1x1 mat_mmul_1x4_4x1 = mul(mat_bar_1x4, mat_foo_4x1);
	eq(mat_mmul_1x4_4x1, 3.0f);
	
	float1x2 mat_mmul_1x4_4x2 = mul(mat_bar_1x4, mat_foo_4x2);
	eq(mat_mmul_1x4_4x2, 5.0f, 6.0f);
	
	float1x3 mat_mmul_1x4_4x3 = mul(mat_bar_1x4, mat_foo_4x3);
	eq(mat_mmul_1x4_4x3, 7.00000048f, 8.00000000f, 9.00000000f);
	
	float1x4 mat_mmul_1x4_4x4 = mul(mat_bar_1x4, mat_foo_4x4);
	eq(mat_mmul_1x4_4x4, 9.00000000f, 10.0000000f, 11.0000000f, 12.0000000f);
	
	float2x1 mat_mmul_2x2_2x1 = mul(mat_bar_2x2, mat_foo_2x1);
	eq(mat_mmul_2x2_2x1, 0.5f, 1.10000002f);
	
	float2x2 mat_mmul_2x2_2x2 = mul(mat_bar_2x2, mat_foo_2x2);
	eq(mat_mmul_2x2_2x2, 0.700000048f, 1.0f, 1.50000000f, 2.20000005f);
	
	float2x3 mat_mmul_2x2_2x3 = mul(mat_bar_2x2, mat_foo_2x3);
	eq(mat_mmul_2x2_2x3, 
		0.900000036f, 1.20000005f, 1.50000000f,
		1.90000010f, 2.59999990f, 3.30000019f
	);
	
	float2x4 mat_mmul_2x2_2x4 = mul(mat_bar_2x2, mat_foo_2x4);
	eq(mat_mmul_2x2_2x4, 
		1.10000002f, 1.40000010f, 1.70000005f, 2.00000000f,
		2.29999995f, 3.00000000f, 3.70000005f, 4.40000010f
	);
	
	float3x1 mat_mmul_3x2_2x1 = mul(mat_bar_3x2, mat_foo_2x1);
	eq(mat_mmul_3x2_2x1, 0.5f, 1.10000002f, 1.70000005f);
	
	float3x2 mat_mmul_3x2_2x2 = mul(mat_bar_3x2, mat_foo_2x2);
	eq(mat_mmul_3x2_2x2, 
		0.700000048f, 1.00000000f,
		1.50000000f, 2.20000005f,
		2.30000019f, 3.40000010f
	);
	
	float3x3 mat_mmul_3x2_2x3 = mul(mat_bar_3x2, mat_foo_2x3);
	eq(mat_mmul_3x2_2x3, 
		0.900000036f, 1.20000005f, 1.50000000f,
		1.90000010f, 2.59999990f, 3.30000019f,
		2.90000010f, 4.00000000f, 5.10000038f
	);
	
	float3x4 mat_mmul_3x2_2x4 = mul(mat_bar_3x2, mat_foo_2x4);
	eq(mat_mmul_3x2_2x4, 
		1.10000002f, 1.40000010f, 1.70000005f, 2.00000000f,
		2.29999995f, 3.00000000f, 3.70000005f, 4.40000010f,
		3.50000000f, 4.60000038f, 5.70000029f, 6.80000019f
	);
	
	float4x1 mat_mmul_4x2_2x1 = mul(mat_bar_4x2, mat_foo_2x1);
	eq(mat_mmul_4x2_2x1, 0.500000000f, 1.10000002f, 1.70000005f, 2.29999995f);
	
	float4x2 mat_mmul_4x2_2x2 = mul(mat_bar_4x2, mat_foo_2x2);
	eq(mat_mmul_4x2_2x2, 
		0.700000048f, 1.00000000f,
		1.50000000f, 2.20000005f,
		2.30000019f, 3.40000010f,
		3.10000014f, 4.59999990f
	);
	
	float4x3 mat_mmul_4x2_2x3 = mul(mat_bar_4x2, mat_foo_2x3);
	eq(mat_mmul_4x2_2x3, 
		0.900000036f, 1.20000005f, 1.50000000f,
		1.90000010f, 2.59999990f, 3.30000019f,
		2.90000010f, 4.00000000f, 5.10000038f,
		3.90000010f, 5.40000010f, 6.90000010f
	);
	
	float4x4 mat_mmul_4x2_2x4 = mul(mat_bar_4x2, mat_foo_2x4);
	eq(mat_mmul_4x2_2x4, 
		1.10000002f, 1.40000010f, 1.70000005f, 2.00000000f,
		2.29999995f, 3.00000000f, 3.70000005f, 4.40000010f,
		3.50000000f, 4.60000038f, 5.70000029f, 6.80000019f,
		4.69999981f, 6.20000029f, 7.69999981f, 9.19999981f
	);
	
	float2x1 mat_mmul_2x3_3x1 = mul(mat_bar_2x3, mat_foo_3x1);
	eq(mat_mmul_2x3_3x1, 1.40000010f, 3.20000005f);
	
	float2x2 mat_mmul_2x3_3x2 = mul(mat_bar_2x3, mat_foo_3x2);
	eq(mat_mmul_2x3_3x2, 2.20000005f, 2.80000019f, 4.90000010f, 6.40000010f);
	
	float2x3 mat_mmul_2x3_3x3 = mul(mat_bar_2x3, mat_foo_3x3);
	eq(mat_mmul_2x3_3x3, 
		3.00000024f, 3.60000014f, 4.19999981f,
		6.60000038f, 8.10000038f, 9.60000038f
	);
	
	float2x4 mat_mmul_2x3_3x4 = mul(mat_bar_2x3, mat_foo_3x4);
	eq(mat_mmul_2x3_3x4, 
		3.80000019f, 4.40000010f, 5.00000000f, 5.60000038f,
		8.30000019f, 9.80000019f, 11.3000002f, 12.8000002f
	);
	
	float2x1 mat_mmul_2x4_4x1 = mul(mat_bar_2x4, mat_foo_4x1);
	eq(mat_mmul_2x4_4x1, 3.00000000f, 7.00000000f);
	
	float2x2 mat_mmul_2x4_4x2 = mul(mat_bar_2x4, mat_foo_4x2);
	eq(mat_mmul_2x4_4x2, 5.00000000f, 6.00000000f, 11.4000006f, 14.0000000f);
	
	float2x3 mat_mmul_2x4_4x3 = mul(mat_bar_2x4, mat_foo_4x3);
	eq(mat_mmul_2x4_4x3, 
		7.00000048f, 8.00000000f, 9.00000000f,
		15.7999992f, 18.3999996f, 21.0000000f
	);
	
	// TODO Revisit this unit test. Using AVX vs SSE gives very slightly different results.
	// We would like them to be identical if possible
	float2x4 mat_mmul_2x4_4x4 = mul(mat_bar_2x4, mat_foo_4x4);
	eq(mat_mmul_2x4_4x4, 
		9.00000000f, 10.0000000f, 11.0000000f, 12.0000000f,
		20.2000008f, 22.7999992f, 25.3999996f, 28.0000000f,
		0.00001f
	);
	
	float3x1 mat_mmul_3x3_3x1 = mul(mat_bar_3x3, mat_foo_3x1);
	eq(mat_mmul_3x3_3x1, 1.40000010f, 3.20000005f, 5.00000000f);
	
	float3x2 mat_mmul_3x3_3x2 = mul(mat_bar_3x3, mat_foo_3x2);
	eq(mat_mmul_3x3_3x2, 
		2.20000005f, 2.80000019f,
		4.90000010f, 6.40000010f,
		7.60000038f, 10.0000000f
	);
	
	float3x3 mat_mmul_3x3_3x3 = mul(mat_bar_3x3, mat_foo_3x3);
	eq(mat_mmul_3x3_3x3, 
		3.00000000f, 3.60000014f, 4.19999981f,
		6.59999990f, 8.10000038f, 9.59999943f,
		10.1999998f, 12.6000004f, 15.0000000f
	);

	float3x4 mat_mmul_3x3_3x4 = mul(mat_bar_3x3, mat_foo_3x4);
	eq(mat_mmul_3x3_3x4, 
		3.80000019f, 4.40000010f, 5.00000000f, 5.60000038f,
		8.30000019f, 9.80000019f, 11.3000002f, 12.8000002f,
		12.7999992f, 15.2000008f, 17.5999985f, 20.0000000f
	);
	
	float3x1 mat_mmul_3x4_4x1 = mul(mat_bar_3x4, mat_foo_4x1);
	eq(mat_mmul_3x4_4x1, 3.00000000f, 7.00000000f, 11.0000000f);
	
	float3x2 mat_mmul_3x4_4x2 = mul(mat_bar_3x4, mat_foo_4x2);
	eq(mat_mmul_3x4_4x2, 
		5.00000000f, 6.00000000f,
		11.4000006f, 14.0000000f,
		17.8000011f, 22.0000000f
	);
	
	float3x3 mat_mmul_3x4_4x3 = mul(mat_bar_3x4, mat_foo_4x3);
	eq(mat_mmul_3x4_4x3, 
		7.00000048f, 8.00000000f, 9.00000000f,
		15.7999992f, 18.3999996f, 21.0000000f,
		24.6000004f, 28.7999992f, 33.0000000f
	);
	
	float3x4 mat_mmul_3x4_4x4 = mul(mat_bar_3x4, mat_foo_4x4);
	eq(mat_mmul_3x4_4x4, 
		9.00000000f, 10.0000000f, 11.0000000f, 12.0000000f,
		20.2000008f, 22.7999992f, 25.3999996f, 28.0000000f,
		31.4000015f, 35.5999985f, 39.7999992f, 44.0000000f
	);
	
	float4x1 mat_mmul_4x3_3x1 = mul(mat_bar_4x3, mat_foo_3x1);
	eq(mat_mmul_4x3_3x1, 1.40000010f, 3.20000005f, 5.00000000f, 6.80000019f);
	
	float4x2 mat_mmul_4x3_3x2 = mul(mat_bar_4x3, mat_foo_3x2);
	eq(mat_mmul_4x3_3x2, 
		2.20000005f, 2.80000019f,
		4.90000010f, 6.40000010f,
		7.60000038f, 10.0000000f,
		10.3000002f, 13.6000004f
	);
	
	float4x3 mat_mmul_4x3_3x3 = mul(mat_bar_4x3, mat_foo_3x3);
	eq(mat_mmul_4x3_3x3, 
		3.00000024f, 3.60000014f, 4.19999981f,
		6.60000038f, 8.10000038f, 9.60000038f,
		10.1999998f, 12.6000004f, 15.0000000f,
		13.8000011f, 17.1000004f, 20.4000015f
	);
	
	float4x4 mat_mmul_4x3_3x4 = mul(mat_bar_4x3, mat_foo_3x4);
	eq(mat_mmul_4x3_3x4, 
		3.80000019f, 4.40000010f, 5.00000000f, 5.60000038f,
		8.30000019f, 9.80000019f, 11.3000002f, 12.8000002f,
		12.7999992f, 15.2000008f, 17.5999985f, 20.0000000f,
		17.2999992f, 20.6000004f, 23.9000015f, 27.2000008f
	);
	
	float4x1 mat_mmul_4x4_4x1 = mul(mat_bar_4x4, mat_foo_4x1);
	eq(mat_mmul_4x4_4x1, 3.00000000f, 7.00000000f, 11.0000000f, 15.0000000f);
	
	float4x2 mat_mmul_4x4_4x2 = mul(mat_bar_4x4, mat_foo_4x2);
	eq(mat_mmul_4x4_4x2, 
		5.00000000f, 6.00000000f,
		11.4000006f, 14.0000000f,
		17.8000011f, 22.0000000f,
		24.2000008f, 30.0000000f
	);
	
	float4x3 mat_mmul_4x4_4x3 = mul(mat_bar_4x4, mat_foo_4x3);
	eq(mat_mmul_4x4_4x3, 
		7.00000048f, 8.00000000f, 9.00000000f,
		15.7999992f, 18.3999996f, 21.0000000f,
		24.6000004f, 28.7999992f, 33.0000000f,
		33.4000015f, 39.2000008f, 45.0000000f
	);

	// TODO Revisit this unit test. Using AVX vs SSE gives very slightly different results.
	// We would like them to be identical if possible
	float4x4 mat_mmul_4x4_4x4 = mul(mat_bar_4x4, mat_foo_4x4);
	eq(mat_mmul_4x4_4x4, 
		9.00000000f, 10.0000000f, 11.0000000f, 12.0000000f,
		20.2000008f, 22.7999992f, 25.3999996f, 28.0000000f,
		31.4000015f, 35.5999985f, 39.7999992f, 44.0000000f,
		42.5999985f, 48.4000015f, 54.2000008f, 60.0000000f,
		0.00001f
	);

	// Matrix-vector multiplication

	//float1 vec_vmul_1x1_v1 = mul(mat_foo_1x1, vfoo1);
	//float1 vec_vmul_1x2_v2 = mul(mat_foo_1x2, vfoo2);
	//float1 vec_vmul_1x3_v3 = mul(mat_foo_1x3, vfoo3);
	//float1 vec_vmul_1x4_v4 = mul(mat_foo_1x4, vfoo4);
	//
	//float2 vec_vmul_2x1_v1 = mul(mat_foo_2x1, vfoo1);
	//float2 vec_vmul_2x2_v2 = mul(mat_foo_2x2, vfoo2);
	//float2 vec_vmul_2x3_v3 = mul(mat_foo_2x3, vfoo3);
	//float2 vec_vmul_2x4_v4 = mul(mat_foo_2x4, vfoo4);
	//
	//float3 vec_vmul_3x1_v1 = mul(mat_foo_3x1, vfoo1);
	//float3 vec_vmul_3x2_v2 = mul(mat_foo_3x2, vfoo2);
	//float3 vec_vmul_3x3_v3 = mul(mat_foo_3x3, vfoo3);
	//float3 vec_vmul_3x4_v4 = mul(mat_foo_3x4, vfoo4);
	//
	//float4 vec_vmul_4x1_v1 = mul(mat_foo_4x1, vfoo1);
	//float4 vec_vmul_4x2_v2 = mul(mat_foo_4x2, vfoo2);
	//float4 vec_vmul_4x3_v3 = mul(mat_foo_4x3, vfoo3);
	//float4 vec_vmul_4x4_v4 = mul(mat_foo_4x4, vfoo4);

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
	eq(mat_transp_4x4,
		mat_foo_4x4._m00, mat_foo_4x4._m10, mat_foo_4x4._m20, mat_foo_4x4._m30,
		mat_foo_4x4._m01, mat_foo_4x4._m11, mat_foo_4x4._m21, mat_foo_4x4._m31,
		mat_foo_4x4._m02, mat_foo_4x4._m12, mat_foo_4x4._m22, mat_foo_4x4._m32,
		mat_foo_4x4._m03, mat_foo_4x4._m13, mat_foo_4x4._m23, mat_foo_4x4._m33);

	// Determinants

	float1 mat_det_2x2 = determinant
	(
		float2x2(
			0.1f, 0.7f, 
			-2.4f, 30.9f)
	); eq(mat_det_2x2, 4.77f);

	float1 mat_det_3x3 = determinant
	(
		float3x3(
			9.8f,  0.8f,  1.3f,
			2.1f, -5.6f, -4.2f,
			3.4f, 40.3f,  9.2f)
	);

	eq(mat_det_3x3, 1261.743f);

	float1 mat_det_4x4 = determinant
	(
		float4x4(
			1.85301f, 1.33804f, 4.93541f, 0.89339f,
			7.80464f, 1.23109f, 4.57515f, 5.18840f,
			6.14745f, 6.81015f, 6.94445f, 5.96989f,
			8.70953f, 8.39168f, 0.36891f, 2.90656f
		)
	);

	eq(mat_det_4x4, -1032.1171482186170986f, 0.001f);

	// Inverses

	float2x2 mat_invertible_2x2 = float2x2(1, 2, 3, 4);

	float2x2 mat_inv_2x2 = inverse(mat_invertible_2x2);

	eq(mat_inv_2x2, -2.0f, 1.0f, 1.5f, -0.5f);

	float3x3 mat_invertible_3x3 = float3x3(
		1, 2, 3,
		3, 4, 5,
		6, 1, 2);

	float3x3 mat_inv_3x3 = inverse(mat_invertible_3x3);

	eq(mat_inv_3x3,
		-0.25f, 0.083333333f, 0.166666666f,
		-2.00f, 1.333333333f, -0.333333333f,
		1.75f, -0.916666666f, 0.166666666f);

	float4x4 mat_invertible_4x4 = float4x4(
		5, 6, 6, 8,
		2, 2, 2, 8,
		6, 6, 2, 8,
		2, 3, 6, 7);

	float4x4 mat_inv_4x4 = inverse(mat_invertible_4x4);

	eq(mat_inv_4x4,
		-17.0f, -9.00f, 12.00f, 16.0f,
		17.0f, 8.75f, -11.75f, -16.0f,
		-4.0f, -2.25f, 2.75f, 4.0f,
		1.0f, 0.75f, -0.75f, -1.0f);

	// Storage

	float mat_store_3x3[9];
	float mat_store_4x4[16];

	store(mat_foo_3x3, mat_store_3x3);
	eq(mat_foo_3x3,
		mat_store_3x3[0], mat_store_3x3[1], mat_store_3x3[2],
		mat_store_3x3[3], mat_store_3x3[4], mat_store_3x3[5],
		mat_store_3x3[6], mat_store_3x3[7], mat_store_3x3[8]);

	store(mat_foo_4x4, mat_store_4x4);
	eq(mat_foo_4x4,
		mat_store_4x4[0], mat_store_4x4[1], mat_store_4x4[2], mat_store_4x4[3],
		mat_store_4x4[4], mat_store_4x4[5], mat_store_4x4[6], mat_store_4x4[7],
		mat_store_4x4[8], mat_store_4x4[9], mat_store_4x4[10], mat_store_4x4[11],
		mat_store_4x4[12], mat_store_4x4[13], mat_store_4x4[14], mat_store_4x4[15]);
}