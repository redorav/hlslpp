#include <hlsl++_matrix_transform_ext.h>

#include "hlsl++_unit_tests.h"

void RunUnitTestsMatrixTransform()
{
	using namespace hlslpp_unit;

	const float pi = std::acos(-1.0f);
	const float sq2 = std::sqrt(2.0f) / 2.0f;
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

	// Scaling

	eq(mul(vec2d_a1, float2x2_scale(2.0f)), 2.0f, 2.0f, tolerance);
	eq(mul(vec3d_a1, float3x3_scale(2.0f)), 2.0f, 2.0f, 2.0f, tolerance);

	eq(mul(vec2d_a1, float2x2_scale(2.0f, 3.0f)), 2.0f, 3.0f, tolerance);
	eq(mul(vec3d_a1, float3x3_scale(2.0f, 3.0f)), 2.0f, 3.0f, 1.0f, tolerance);

	eq(mul(vec2d_a1, float2x2_scale(float2(4.0f, 5.0f))), 4.0f, 5.0f, tolerance);
	eq(mul(vec3d_a1, float3x3_scale(float2(4.0f, 5.0f))), 4.0f, 5.0f, 1.0f, tolerance);

	eq(mul(vec3d_a1, float3x3_scale(2.0f)), 2.0f, 2.0f, 2.0f, tolerance);
	eq(mul(vec4d_a1, float4x4_scale(2.0f)), 2.0f, 2.0f, 2.0f, 1.0f, tolerance);

	eq(mul(vec3d_a1, float3x3_scale(2.0f, 3.0f, 4.0f)), 2.0f, 3.0f, 4.0f, tolerance);
	eq(mul(vec4d_a1, float4x4_scale(2.0f, 3.0f, 4.0f)), 2.0f, 3.0f, 4.0f, 1.0f, tolerance);

	eq(mul(vec3d_a1, float3x3_scale(float3(4.0f, 5.0f, 6.0f))), 4.0f, 5.0f, 6.0f, tolerance);
	eq(mul(vec4d_a1, float4x4_scale(float3(4.0f, 5.0f, 6.0f))), 4.0f, 5.0f, 6.0f, 1.0f, tolerance);

	// Rotation

	eq(mul(vec2d_x1, float2x2_rotate(pi / 2.0f)), 0.0f, 1.0f, tolerance);
	eq(mul(vec3d_x1, float3x3_rotate_z(pi / 2.0f)), 0.0f, 1.0f, 0.0f, tolerance);

	eq(mul(vec2d_y1, float2x2_rotate(pi / 2.0f)), -1.0f, 0.0f, tolerance);
	eq(mul(vec3d_y1, float3x3_rotate_z(pi / 2.0f)), -1.0f, 0.0f, 0.0f, tolerance);

	eq(mul(vec2d_x1, float2x2_rotate(pi / 4.0f)), sq2, sq2, tolerance);
	eq(mul(vec3d_x1, float3x3_rotate_z(pi / 4.0f)), sq2, sq2, 0.0f, tolerance);

	eq(mul(vec2d_y1, float2x2_rotate(pi / 4.0f)), -sq2, sq2, tolerance);
	eq(mul(vec3d_y1, float3x3_rotate_z(pi / 4.0f)), -sq2, sq2, 0.0f, tolerance);

	eq(mul(vec2d_x1, float2x2_rotate(pi * 3.0f / 4.0f)), -sq2, sq2, tolerance);
	eq(mul(vec3d_x1, float3x3_rotate_z(pi * 3.0f / 4.0f)), -sq2, sq2, 0.0f, tolerance);

	eq(mul(vec2d_y1, float2x2_rotate(pi * 3.0f / 4.0f)), -sq2, -sq2, tolerance);
	eq(mul(vec3d_y1, float3x3_rotate_z(pi * 3.0f / 4.0f)), -sq2, -sq2, 0.0f, tolerance);

	eq(mul(vec3d_y1, float3x3_rotate_x(pi / 2.0f)), 0.0f, 0.0f, 1.0f, tolerance);
	eq(mul(vec4d_y1, float4x4_rotate_x(pi / 2.0f)), 0.0f, 0.0f, 1.0f, 1.0f, tolerance);
	eq(mul(vec3d_y1, float3x3_rotate_axis(vec3d_x1, pi / 2.0f)), 0.0f, 0.0f, 1.0f, tolerance);
	eq(mul(vec4d_y1, float4x4_rotate_axis(vec3d_x1, pi / 2.0f)), 0.0f, 0.0f, 1.0f, 1.0f, tolerance);

	eq(mul(vec3d_z1, float3x3_rotate_y(pi / 2.0f)), 1.0f, 0.0f, 0.0f, tolerance);
	eq(mul(vec4d_z1, float4x4_rotate_y(pi / 2.0f)), 1.0f, 0.0f, 0.0f, 1.0f, tolerance);
	eq(mul(vec3d_z1, float3x3_rotate_axis(vec3d_y1, pi / 2.0f)), 1.0f, 0.0f, 0.0f, tolerance);
	eq(mul(vec4d_z1, float4x4_rotate_axis(vec3d_y1, pi / 2.0f)), 1.0f, 0.0f, 0.0f, 1.0f, tolerance);

	eq(mul(vec3d_x1, float3x3_rotate_z(pi / 2.0f)), 0.0f, 1.0f, 0.0f, tolerance);
	eq(mul(vec4d_x1, float4x4_rotate_z(pi / 2.0f)), 0.0f, 1.0f, 0.0f, 1.0f, tolerance);
	eq(mul(vec3d_x1, float3x3_rotate_axis(vec3d_z1, pi / 2.0f)), 0.0f, 1.0f, 0.0f, tolerance);
	eq(mul(vec4d_x1, float4x4_rotate_axis(vec3d_z1, pi / 2.0f)), 0.0f, 1.0f, 0.0f, 1.0f, tolerance);

	eq(mul(vec3d_y1, float3x3_rotate_x(pi / 4.0f)), 0.0f, sq2, sq2, tolerance);
	eq(mul(vec4d_y1, float4x4_rotate_x(pi / 4.0f)), 0.0f, sq2, sq2, 1.0f, tolerance);
	eq(mul(vec3d_y1, float3x3_rotate_axis(vec3d_x1, pi / 4.0f)), 0.0f, sq2, sq2, tolerance);
	eq(mul(vec4d_y1, float4x4_rotate_axis(vec3d_x1, pi / 4.0f)), 0.0f, sq2, sq2, 1.0f, tolerance);

	eq(mul(vec3d_z1, float3x3_rotate_y(pi / 4.0f)), sq2, 0.0f, sq2, tolerance);
	eq(mul(vec4d_z1, float4x4_rotate_y(pi / 4.0f)), sq2, 0.0f, sq2, 1.0f, tolerance);
	eq(mul(vec3d_z1, float3x3_rotate_axis(vec3d_y1, pi / 4.0f)), sq2, 0.0f, sq2, tolerance);
	eq(mul(vec4d_z1, float4x4_rotate_axis(vec3d_y1, pi / 4.0f)), sq2, 0.0f, sq2, 1.0f, tolerance);

	eq(mul(vec3d_x1, float3x3_rotate_z(pi / 4.0f)), sq2, sq2, 0.0f, tolerance);
	eq(mul(vec4d_x1, float4x4_rotate_z(pi / 4.0f)), sq2, sq2, 0.0f, 1.0f, tolerance);
	eq(mul(vec3d_x1, float3x3_rotate_axis(vec3d_z1, pi / 4.0f)), sq2, sq2, 0.0f, tolerance);
	eq(mul(vec4d_x1, float4x4_rotate_axis(vec3d_z1, pi / 4.0f)), sq2, sq2, 0.0f, 1.0f, tolerance);

	eq(mul(vec3d_y1, float3x3_rotate_x(pi * 3.0f / 4.0f)), 0.0f, -sq2, sq2, tolerance);
	eq(mul(vec4d_y1, float4x4_rotate_x(pi * 3.0f / 4.0f)), 0.0f, -sq2, sq2, 1.0f, tolerance);
	eq(mul(vec3d_y1, float3x3_rotate_axis(vec3d_x1, pi * 3.0f / 4.0f)), 0.0f, -sq2, sq2, tolerance);
	eq(mul(vec4d_y1, float4x4_rotate_axis(vec3d_x1, pi * 3.0f / 4.0f)), 0.0f, -sq2, sq2, 1.0f, tolerance);

	eq(mul(vec3d_z1, float3x3_rotate_y(pi * 3.0f / 4.0f)), sq2, 0.0f, -sq2, tolerance);
	eq(mul(vec4d_z1, float4x4_rotate_y(pi * 3.0f / 4.0f)), sq2, 0.0f, -sq2, 1.0f, tolerance);
	eq(mul(vec3d_z1, float3x3_rotate_axis(vec3d_y1, pi * 3.0f / 4.0f)), sq2, 0.0f, -sq2, tolerance);
	eq(mul(vec4d_z1, float4x4_rotate_axis(vec3d_y1, pi * 3.0f / 4.0f)), sq2, 0.0f, -sq2, 1.0f, tolerance);

	eq(mul(vec3d_x1, float3x3_rotate_z(pi * 3.0f / 4.0f)), -sq2, sq2, 0.0f, tolerance);
	eq(mul(vec4d_x1, float4x4_rotate_z(pi * 3.0f / 4.0f)), -sq2, sq2, 0.0f, 1.0f, tolerance);
	eq(mul(vec3d_x1, float3x3_rotate_axis(vec3d_z1, pi * 3.0f / 4.0f)), -sq2, sq2, 0.0f, tolerance);
	eq(mul(vec4d_x1, float4x4_rotate_axis(vec3d_z1, pi * 3.0f / 4.0f)), -sq2, sq2, 0.0f, 1.0f, tolerance);

	// Translation

	eq(mul(vec3d_a1, float3x3_translate(2.0f, 3.0f)), 3.0f, 4.0f, 1.0f, tolerance);
	eq(mul(vec3d_a1, float3x3_translate(float2(2.0f, 3.0f))), 3.0f, 4.0f, 1.0f, tolerance);

	eq(mul(vec4d_a1, float4x4_translate(2.0f, 3.0f, 4.0f)), 3.0f, 4.0f, 5.0f, 1.0f, tolerance);
	eq(mul(vec4d_a1, float4x4_translate(float3(2.0f, 3.0f, 4.0f))), 3.0f, 4.0f, 5.0f, 1.0f, tolerance);

	// World to View coordinates transformation

	const float3 view_position(1.0f, 0.0f, 0.0f);
	const float3 view_target(0.0f, 0.0f, 0.0f);
	const float3 view_up(0.0f, 0.0f, 1.0f);

	eq(mul(vec4d_a1, float4x4_look_at(view_position, view_target, view_up)), -1.0f, 1.0f, 0.0f, 1.0f, tolerance);

	// View to Orthographic Projection coordinates transformation

	const float4 vec4d_view1(0.5f, 0.5f, 0.0f, 1.0f);
	Frustrum ortho_frustrum(-0.5f, 0.5f, -0.5f, 0.5f, -1.0f, 1.0f);

	eq(mul(vec4d_view1, float4x4_projection(ProjectionSettings(ortho_frustrum, ProjectionType::Orthographic, ZClip::Zero))), 1.0f, 1.0f, 0.5f, 1.0f, tolerance);
	eq(mul(vec4d_view1, float4x4_projection(ProjectionSettings(ortho_frustrum, ProjectionType::Orthographic, ZClip::NegativeOne))), 1.0f, 1.0f, 0.0f, 1.0f, tolerance);

	// View to Perspective Projection coordinates transformation

	const float4 vec4d_view2(0.5f, 0.5f, 1.0f, 1.0f);
	Frustrum persp_frustrum(-0.5f, 0.5f, -0.5f, 0.5f, 0.001f, 1.0f);

	eq(mul(vec4d_view2, float4x4_projection(ProjectionSettings(persp_frustrum, ProjectionType::Perspective, ZClip::Zero))), 0.001f, 0.001f, 1.0f, 1.0f, tolerance);
	eq(mul(vec4d_view2, float4x4_projection(ProjectionSettings(persp_frustrum, ProjectionType::Perspective, ZClip::NegativeOne))), 0.001f, 0.001f, 1.0f, 1.0f, tolerance);
}
