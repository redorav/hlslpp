#include "hlsl++.h"

#include "unit_tests.h"

void RunUnitTestsMatrixTransform()
{
	using namespace hlslpp_unit;

	const float pi  = acosf(-1.0f);
	const float sq2 = sqrtf(2.0f) / 2.0f;
	const float tolerance = 1e-7f;

	const float2 vec2d_a1(1.0f, 1.0f);
	const float2 vec2d_x1(1.0f, 0.0f);
	const float2 vec2d_y1(0.0f, 1.0f);

	const float3 vec3d_a1(1.0f, 1.0f, 1.0f);
	const float3 vec3d_x1(1.0f, 0.0f, 0.0f);
	const float3 vec3d_y1(0.0f, 1.0f, 0.0f);
	const float3 vec3d_z1(0.0f, 0.0f, 1.0f);

	const float4 vec4d_a1(1.0f, 1.0f, 1.0f, 1.0f);
	const float4 vec4d_x1(1.0f, 0.0f, 0.0f, 1.0f);
	const float4 vec4d_y1(0.0f, 1.0f, 0.0f, 1.0f);
	const float4 vec4d_z1(0.0f, 0.0f, 1.0f, 1.0f);

#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR

	hlslpp_unit::BeginTest("Transform Scaling");
	{
		hlslpp_check(eq(mul(vec2d_a1, float2x2::scale(2.0f)), 2.0f, 2.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_a1, float3x3::scale(2.0f)), 2.0f, 2.0f, 2.0f, tolerance));

		hlslpp_check(eq(mul(vec2d_a1, float2x2::scale(2.0f, 3.0f)), 2.0f, 3.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_a1, float3x3::scale(2.0f, 3.0f)), 2.0f, 3.0f, 1.0f, tolerance));

		hlslpp_check(eq(mul(vec2d_a1, float2x2::scale(float2(4.0f, 5.0f))), 4.0f, 5.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_a1, float3x3::scale(float2(4.0f, 5.0f))), 4.0f, 5.0f, 1.0f, tolerance));

		hlslpp_check(eq(mul(vec3d_a1, float3x3::scale(2.0f)), 2.0f, 2.0f, 2.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_a1, float4x4::scale(2.0f)), 2.0f, 2.0f, 2.0f, 1.0f, tolerance));

		hlslpp_check(eq(mul(vec3d_a1, float3x3::scale(2.0f, 3.0f, 4.0f)), 2.0f, 3.0f, 4.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_a1, float4x4::scale(2.0f, 3.0f, 4.0f)), 2.0f, 3.0f, 4.0f, 1.0f, tolerance));

		hlslpp_check(eq(mul(vec3d_a1, float3x3::scale(float3(4.0f, 5.0f, 6.0f))), 4.0f, 5.0f, 6.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_a1, float4x4::scale(float3(4.0f, 5.0f, 6.0f))), 4.0f, 5.0f, 6.0f, 1.0f, tolerance));
	}
	hlslpp_unit::EndTest();

	hlslpp_unit::BeginTest("Transform Translation");
	{
		hlslpp_check(eq(mul(vec3d_a1, float3x3::translation(2.0f, 3.0f)), 3.0f, 4.0f, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_a1, float3x3::translation(float2(2.0f, 3.0f))), 3.0f, 4.0f, 1.0f, tolerance));

		hlslpp_check(eq(mul(vec4d_a1, float4x4::translation(2.0f, 3.0f, 4.0f)), 3.0f, 4.0f, 5.0f, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_a1, float4x4::translation(float3(2.0f, 3.0f, 4.0f))), 3.0f, 4.0f, 5.0f, 1.0f, tolerance));
	}
	hlslpp_unit::EndTest();

#if HLSLPP_COORDINATES == HLSLPP_COORDINATES_LEFT_HANDED

	hlslpp_unit::BeginTest("Transform Rotation");
	{
		hlslpp_check(eq(mul(vec2d_x1, float2x2::rotation(pi / 2.0f)), 0.0f, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_x1, float3x3::rotation_z(pi / 2.0f)), 0.0f, 1.0f, 0.0f, tolerance));

		hlslpp_check(eq(mul(vec2d_y1, float2x2::rotation(pi / 2.0f)), -1.0f, 0.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_y1, float3x3::rotation_z(pi / 2.0f)), -1.0f, 0.0f, 0.0f, tolerance));

		hlslpp_check(eq(mul(vec2d_x1, float2x2::rotation(pi / 4.0f)), sq2, sq2, tolerance));
		hlslpp_check(eq(mul(vec3d_x1, float3x3::rotation_z(pi / 4.0f)), sq2, sq2, 0.0f, tolerance));

		hlslpp_check(eq(mul(vec2d_y1, float2x2::rotation(pi / 4.0f)), -sq2, sq2, tolerance));
		hlslpp_check(eq(mul(vec3d_y1, float3x3::rotation_z(pi / 4.0f)), -sq2, sq2, 0.0f, tolerance));

		hlslpp_check(eq(mul(vec2d_x1, float2x2::rotation(pi * 3.0f / 4.0f)), -sq2, sq2, tolerance));
		hlslpp_check(eq(mul(vec3d_x1, float3x3::rotation_z(pi * 3.0f / 4.0f)), -sq2, sq2, 0.0f, tolerance));

		hlslpp_check(eq(mul(vec2d_y1, float2x2::rotation(pi * 3.0f / 4.0f)), -sq2, -sq2, tolerance));
		hlslpp_check(eq(mul(vec3d_y1, float3x3::rotation_z(pi * 3.0f / 4.0f)), -sq2, -sq2, 0.0f, tolerance));

		hlslpp_check(eq(mul(vec3d_y1, float3x3::rotation_x(pi / 2.0f)), 0.0f, 0.0f, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_y1, float4x4::rotation_x(pi / 2.0f)), 0.0f, 0.0f, 1.0f, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_y1, float3x3::rotation_axis(vec3d_x1, pi / 2.0f)), 0.0f, 0.0f, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_y1, float4x4::rotation_axis(vec3d_x1, pi / 2.0f)), 0.0f, 0.0f, 1.0f, 1.0f, tolerance));

		hlslpp_check(eq(mul(vec3d_z1, float3x3::rotation_y(pi / 2.0f)), 1.0f, 0.0f, 0.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_z1, float4x4::rotation_y(pi / 2.0f)), 1.0f, 0.0f, 0.0f, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_z1, float3x3::rotation_axis(vec3d_y1, pi / 2.0f)), 1.0f, 0.0f, 0.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_z1, float4x4::rotation_axis(vec3d_y1, pi / 2.0f)), 1.0f, 0.0f, 0.0f, 1.0f, tolerance));

		hlslpp_check(eq(mul(vec3d_x1, float3x3::rotation_z(pi / 2.0f)), 0.0f, 1.0f, 0.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_x1, float4x4::rotation_z(pi / 2.0f)), 0.0f, 1.0f, 0.0f, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_x1, float3x3::rotation_axis(vec3d_z1, pi / 2.0f)), 0.0f, 1.0f, 0.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_x1, float4x4::rotation_axis(vec3d_z1, pi / 2.0f)), 0.0f, 1.0f, 0.0f, 1.0f, tolerance));

		hlslpp_check(eq(mul(vec3d_y1, float3x3::rotation_x(pi / 4.0f)), 0.0f, sq2, sq2, tolerance));
		hlslpp_check(eq(mul(vec4d_y1, float4x4::rotation_x(pi / 4.0f)), 0.0f, sq2, sq2, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_y1, float3x3::rotation_axis(vec3d_x1, pi / 4.0f)), 0.0f, sq2, sq2, tolerance));
		hlslpp_check(eq(mul(vec4d_y1, float4x4::rotation_axis(vec3d_x1, pi / 4.0f)), 0.0f, sq2, sq2, 1.0f, tolerance));

		hlslpp_check(eq(mul(vec3d_z1, float3x3::rotation_y(pi / 4.0f)), sq2, 0.0f, sq2, tolerance));
		hlslpp_check(eq(mul(vec4d_z1, float4x4::rotation_y(pi / 4.0f)), sq2, 0.0f, sq2, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_z1, float3x3::rotation_axis(vec3d_y1, pi / 4.0f)), sq2, 0.0f, sq2, tolerance));
		hlslpp_check(eq(mul(vec4d_z1, float4x4::rotation_axis(vec3d_y1, pi / 4.0f)), sq2, 0.0f, sq2, 1.0f, tolerance));

		hlslpp_check(eq(mul(vec3d_x1, float3x3::rotation_z(pi / 4.0f)), sq2, sq2, 0.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_x1, float4x4::rotation_z(pi / 4.0f)), sq2, sq2, 0.0f, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_x1, float3x3::rotation_axis(vec3d_z1, pi / 4.0f)), sq2, sq2, 0.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_x1, float4x4::rotation_axis(vec3d_z1, pi / 4.0f)), sq2, sq2, 0.0f, 1.0f, tolerance));

		hlslpp_check(eq(mul(vec3d_y1, float3x3::rotation_x(pi * 3.0f / 4.0f)), 0.0f, -sq2, sq2, tolerance));
		hlslpp_check(eq(mul(vec4d_y1, float4x4::rotation_x(pi * 3.0f / 4.0f)), 0.0f, -sq2, sq2, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_y1, float3x3::rotation_axis(vec3d_x1, pi * 3.0f / 4.0f)), 0.0f, -sq2, sq2, tolerance));
		hlslpp_check(eq(mul(vec4d_y1, float4x4::rotation_axis(vec3d_x1, pi * 3.0f / 4.0f)), 0.0f, -sq2, sq2, 1.0f, tolerance));

		hlslpp_check(eq(mul(vec3d_z1, float3x3::rotation_y(pi * 3.0f / 4.0f)), sq2, 0.0f, -sq2, tolerance));
		hlslpp_check(eq(mul(vec4d_z1, float4x4::rotation_y(pi * 3.0f / 4.0f)), sq2, 0.0f, -sq2, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_z1, float3x3::rotation_axis(vec3d_y1, pi * 3.0f / 4.0f)), sq2, 0.0f, -sq2, tolerance));
		hlslpp_check(eq(mul(vec4d_z1, float4x4::rotation_axis(vec3d_y1, pi * 3.0f / 4.0f)), sq2, 0.0f, -sq2, 1.0f, tolerance));

		hlslpp_check(eq(mul(vec3d_x1, float3x3::rotation_z(pi * 3.0f / 4.0f)), -sq2, sq2, 0.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_x1, float4x4::rotation_z(pi * 3.0f / 4.0f)), -sq2, sq2, 0.0f, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec3d_x1, float3x3::rotation_axis(vec3d_z1, pi * 3.0f / 4.0f)), -sq2, sq2, 0.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_x1, float4x4::rotation_axis(vec3d_z1, pi * 3.0f / 4.0f)), -sq2, sq2, 0.0f, 1.0f, tolerance));
	}
	hlslpp_unit::EndTest();

	hlslpp_unit::BeginTest("Transform Camera");
	{
		// World to View coordinates transformation

		const float3 view_position(1.0f, 0.0f, 0.0f);
		const float3 view_target(0.0f, 0.0f, 0.0f);
		const float3 view_up(0.0f, 0.0f, 1.0f);

		hlslpp_check(eq(mul(vec4d_a1, float4x4::look_at(view_position, view_target, view_up)), -1.0f, 1.0f, 0.0f, 1.0f, tolerance));

		// View to Orthographic Projection coordinates transformation

		const float4 vec4d_view1(0.5f, 0.5f, 0.0f, 1.0f);
		const frustum ortho_frustum(-0.5f, 0.5f, -0.5f, 0.5f, -1.0f, 1.0f);

		hlslpp_check(eq(mul(vec4d_view1, float4x4::orthographic(projection(ortho_frustum, zclip::zero))), 1.0f, 1.0f, 0.5f, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_view1, float4x4::orthographic(projection(ortho_frustum, zclip::minus_one))), 1.0f, 1.0f, 0.0f, 1.0f, tolerance));

		// View to Perspective Projection coordinates transformation

		const float4 vec4d_view2(0.5f, 0.5f, 1.0f, 1.0f);
		const frustum persp_frustum(-0.5f, 0.5f, -0.5f, 0.5f, 0.001f, 1.0f);

		hlslpp_check(eq(mul(vec4d_view2, float4x4::perspective(projection(persp_frustum, zclip::zero))), 0.001f, 0.001f, 1.0f, 1.0f, tolerance));
		hlslpp_check(eq(mul(vec4d_view2, float4x4::perspective(projection(persp_frustum, zclip::minus_one))), 0.001f, 0.001f, 1.0f, 1.0f, tolerance));
	}
	hlslpp_unit::EndTest();

#endif

#endif
}
