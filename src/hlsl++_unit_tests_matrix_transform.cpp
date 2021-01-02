#include "hlsl++.h"

#include "hlsl++_unit_tests.h"

void RunUnitTestsMatrixTransform()
{
	using namespace hlslpp_unit;

	const float pi = std::acos(-1.f);
	const float tolerance(1e-7);

	// 2D Rotation

	const float2 vec2d_x1(1.f, 0.f);
	const float  sq2 = std::sqrt(2.f) / 2.f;

	eq(mul(float2x2_rotation(pi / 2.f), vec2d_x1), 0.f, 1.f, tolerance);
	eq(mul(float2x2_rotation(pi / 4.f), vec2d_x1), sq2, sq2, tolerance);
	eq(mul(float2x2_rotation(pi * 3.f / 4.f), vec2d_x1), -sq2, sq2, tolerance);

	// 3D Rotation

	const float3 vec3d_x1(1.f, 0.f, 0.f);
	const float3 vec3d_y1(0.f, 1.f, 0.f);
	const float3 vec3d_z1(0.f, 0.f, 1.f);

	eq(mul(float3x3_rotation(vec3d_x1, -pi / 2.f), vec3d_y1), 0.f, 0.f, 1.f, tolerance);
	eq(mul(float3x3_rotation(vec3d_y1, -pi / 2.f), vec3d_z1), 1.f, 0.f, 0.f, tolerance);
	eq(mul(float3x3_rotation(vec3d_z1, -pi / 2.f), vec3d_x1), 0.f, 1.f, 0.f, tolerance);

	eq(mul(float3x3_rotation(vec3d_x1, -pi / 4.f), vec3d_y1), 0.f, sq2, sq2, tolerance);
	eq(mul(float3x3_rotation(vec3d_y1, -pi / 4.f), vec3d_z1), sq2, 0.f, sq2, tolerance);
	eq(mul(float3x3_rotation(vec3d_z1, -pi / 4.f), vec3d_x1), sq2, sq2, 0.f, tolerance);

	eq(mul(float3x3_rotation(vec3d_x1, -pi * 3.f / 4.f), vec3d_y1), 0.f, -sq2, sq2, tolerance);
	eq(mul(float3x3_rotation(vec3d_y1, -pi * 3.f / 4.f), vec3d_z1), sq2, 0.f, -sq2, tolerance);
	eq(mul(float3x3_rotation(vec3d_z1, -pi * 3.f / 4.f), vec3d_x1), -sq2, sq2, 0.f, tolerance);
}
