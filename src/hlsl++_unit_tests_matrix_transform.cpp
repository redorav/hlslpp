#include "hlsl++.h"

#include "hlsl++_unit_tests.h"

void RunUnitTestsMatrixTransform()
{
	using namespace hlslpp_unit;

	const float pi = std::acos(-1.f);
	const float sq2 = std::sqrt(2.f) / 2.f;
	const float tolerance = 1e-7f;

	const float2 vec2d_a1(1.f, 1.f);
	const float2 vec2d_x1(1.f, 0.f);
	const float2 vec2d_y1(0.f, 1.f);

	const float3 vec3d_a1(1.f, 1.f, 1.f);
	const float3 vec3d_x1(1.f, 0.f, 0.f);
	const float3 vec3d_y1(0.f, 1.f, 0.f);
	const float3 vec3d_z1(0.f, 0.f, 1.f);

	const float4 vec4d_a1(1.f, 1.f, 1.f, 1.f);

	// 2D Scale

	eq(mul(float2x2_scale(2.f), vec2d_a1), 2.f, 2.f, tolerance);
	eq(mul(float2x2_scale(2.f, 3.f), vec2d_a1), 2.f, 3.f, tolerance);
	eq(mul(float2x2_scale(float2(4.f, 5.f)), vec2d_a1), 4.f, 5.f, tolerance);

	// 3D Scale

	eq(mul(float3x3_scale(2.f), vec3d_a1), 2.f, 2.f, 2.f, tolerance);
	eq(mul(float3x3_scale(2.f, 3.f, 4.f), vec3d_a1), 2.f, 3.f, 4.f, tolerance);
	eq(mul(float3x3_scale(float3(4.f, 5.f, 6.f)), vec3d_a1), 4.f, 5.f, 6.f, tolerance);

	// 2D Rotation

	eq(mul(float2x2_rotation(pi / 2.f), vec2d_x1), 0.f, 1.f, tolerance);
	eq(mul(float2x2_rotation(pi / 2.f), vec2d_y1), -1.f, 0.f, tolerance);

	eq(mul(float2x2_rotation(pi / 4.f), vec2d_x1), sq2, sq2, tolerance);
	eq(mul(float2x2_rotation(pi / 4.f), vec2d_y1), -sq2, sq2, tolerance);

	eq(mul(float2x2_rotation(pi * 3.f / 4.f), vec2d_x1), -sq2, sq2, tolerance);
	eq(mul(float2x2_rotation(pi * 3.f / 4.f), vec2d_y1), -sq2, -sq2, tolerance);

	// 3D Rotation

	eq(mul(float3x3_rotation(vec3d_x1, -pi / 2.f), vec3d_y1), 0.f, 0.f, 1.f, tolerance);
	eq(mul(float3x3_rotation(vec3d_y1, -pi / 2.f), vec3d_z1), 1.f, 0.f, 0.f, tolerance);
	eq(mul(float3x3_rotation(vec3d_z1, -pi / 2.f), vec3d_x1), 0.f, 1.f, 0.f, tolerance);

	eq(mul(float3x3_rotation(vec3d_x1, -pi / 4.f), vec3d_y1), 0.f, sq2, sq2, tolerance);
	eq(mul(float3x3_rotation(vec3d_y1, -pi / 4.f), vec3d_z1), sq2, 0.f, sq2, tolerance);
	eq(mul(float3x3_rotation(vec3d_z1, -pi / 4.f), vec3d_x1), sq2, sq2, 0.f, tolerance);

	eq(mul(float3x3_rotation(vec3d_x1, -pi * 3.f / 4.f), vec3d_y1), 0.f, -sq2, sq2, tolerance);
	eq(mul(float3x3_rotation(vec3d_y1, -pi * 3.f / 4.f), vec3d_z1), sq2, 0.f, -sq2, tolerance);
	eq(mul(float3x3_rotation(vec3d_z1, -pi * 3.f / 4.f), vec3d_x1), -sq2, sq2, 0.f, tolerance);

	// 2D Translation

	eq(mul(float3x3_translation(2.f, 3.f), vec3d_a1), 3.f, 4.f, 1.f, tolerance);
	eq(mul(float3x3_translation(float2(2.f, 3.f)), vec3d_a1), 3.f, 4.f, 1.f, tolerance);

	// 3D Translation

	eq(mul(float4x4_translation(2.f, 3.f, 4.f), vec4d_a1), 3.f, 4.f, 5.f, 1.f, tolerance);
	eq(mul(float4x4_translation(float3(2.f, 3.f, 4.f)), vec4d_a1), 3.f, 4.f, 5.f, 1.f, tolerance);
}
