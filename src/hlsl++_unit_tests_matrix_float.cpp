#include "hlsl++.h"

// Hacky but needs FLOAT64
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

	float1x1 mat_foo_dc_1x1;
	float1x2 mat_foo_dc_1x2;
	float1x3 mat_foo_dc_1x3;
	float1x4 mat_foo_dc_1x4;
	float2x1 mat_foo_dc_2x1;
	float3x1 mat_foo_dc_3x1;
	float4x1 mat_foo_dc_4x1;
	float2x2 mat_foo_dc_2x2;
	float2x3 mat_foo_dc_2x3;
	float2x4 mat_foo_dc_2x4;
	float3x2 mat_foo_dc_3x2;
	float4x2 mat_foo_dc_4x2;
	float3x3 mat_foo_dc_3x3;
	float3x4 mat_foo_dc_3x4;
	float4x3 mat_foo_dc_4x3;
	float4x4 mat_foo_dc_4x4;

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

	// Determinants

	float1 mat_det_2x2 = determinant(mat_foo_2x2);
	float1 mat_det_3x3 = determinant(mat_foo_3x3);
	float1 mat_det_4x4 = determinant(mat_foo_4x4);

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