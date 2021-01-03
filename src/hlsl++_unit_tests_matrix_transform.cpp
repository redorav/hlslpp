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
	const float4 vec4d_x1(1.f, 0.f, 0.f, 1.f);
	const float4 vec4d_y1(0.f, 1.f, 0.f, 1.f);
	const float4 vec4d_z1(0.f, 0.f, 1.f, 1.f);

	// Scaling

	eq(mul(vec2d_a1, float2x2_scale(2.f)), 2.f, 2.f, tolerance);
	eq(mul(vec3d_a1, float3x3_scale(2.f)), 2.f, 2.f, 2.f, tolerance);

	eq(mul(vec2d_a1, float2x2_scale(2.f, 3.f)), 2.f, 3.f, tolerance);
	eq(mul(vec3d_a1, float3x3_scale(2.f, 3.f)), 2.f, 3.f, 1.f, tolerance);

	eq(mul(vec2d_a1, float2x2_scale(float2(4.f, 5.f))), 4.f, 5.f, tolerance);
	eq(mul(vec3d_a1, float3x3_scale(float2(4.f, 5.f))), 4.f, 5.f, 1.f, tolerance);

	eq(mul(vec3d_a1, float3x3_scale(2.f)), 2.f, 2.f, 2.f, tolerance);
	eq(mul(vec4d_a1, float4x4_scale(2.f)), 2.f, 2.f, 2.f, 1.f, tolerance);

	eq(mul(vec3d_a1, float3x3_scale(2.f, 3.f, 4.f)), 2.f, 3.f, 4.f, tolerance);
	eq(mul(vec4d_a1, float4x4_scale(2.f, 3.f, 4.f)), 2.f, 3.f, 4.f, 1.f, tolerance);

	eq(mul(vec3d_a1, float3x3_scale(float3(4.f, 5.f, 6.f))), 4.f, 5.f, 6.f, tolerance);
	eq(mul(vec4d_a1, float4x4_scale(float3(4.f, 5.f, 6.f))), 4.f, 5.f, 6.f, 1.f, tolerance);

	// Rotation

	eq(mul(vec2d_x1, float2x2_rotate(pi / 2.f)), 0.f, 1.f, tolerance);
	eq(mul(vec3d_x1, float3x3_rotate(pi / 2.f)), 0.f, 1.f, 0.f, tolerance);

	eq(mul(vec2d_y1, float2x2_rotate(pi / 2.f)), -1.f, 0.f, tolerance);
	eq(mul(vec3d_y1, float3x3_rotate(pi / 2.f)), -1.f, 0.f, 0.f, tolerance);

	eq(mul(vec2d_x1, float2x2_rotate(pi / 4.f)), sq2, sq2, tolerance);
	eq(mul(vec3d_x1, float3x3_rotate(pi / 4.f)), sq2, sq2, 0.f, tolerance);

	eq(mul(vec2d_y1, float2x2_rotate(pi / 4.f)), -sq2, sq2, tolerance);
	eq(mul(vec3d_y1, float3x3_rotate(pi / 4.f)), -sq2, sq2, 0.f, tolerance);

	eq(mul(vec2d_x1, float2x2_rotate(pi * 3.f / 4.f)), -sq2, sq2, tolerance);
	eq(mul(vec3d_x1, float3x3_rotate(pi * 3.f / 4.f)), -sq2, sq2, 0.f, tolerance);

	eq(mul(vec2d_y1, float2x2_rotate(pi * 3.f / 4.f)), -sq2, -sq2, tolerance);
	eq(mul(vec3d_y1, float3x3_rotate(pi * 3.f / 4.f)), -sq2, -sq2, 0.f, tolerance);

	eq(mul(vec2d_y1, float2x2_rotate(pi * 3.f / 4.f)), -sq2, -sq2, tolerance);
	eq(mul(vec3d_y1, float3x3_rotate(pi * 3.f / 4.f)), -sq2, -sq2, 0.f, tolerance);

	eq(mul(vec3d_y1, float3x3_rotate(vec3d_x1, -pi / 2.f)), 0.f, 0.f, 1.f, tolerance);
	eq(mul(vec4d_y1, float4x4_rotate(vec3d_x1, -pi / 2.f)), 0.f, 0.f, 1.f, 1.f, tolerance);

	eq(mul(vec3d_z1, float3x3_rotate(vec3d_y1, -pi / 2.f)), 1.f, 0.f, 0.f, tolerance);
	eq(mul(vec4d_z1, float4x4_rotate(vec3d_y1, -pi / 2.f)), 1.f, 0.f, 0.f, 1.f, tolerance);

	eq(mul(vec3d_x1, float3x3_rotate(vec3d_z1, -pi / 2.f)), 0.f, 1.f, 0.f, tolerance);
	eq(mul(vec4d_x1, float4x4_rotate(vec3d_z1, -pi / 2.f)), 0.f, 1.f, 0.f, 1.f, tolerance);

	eq(mul(vec3d_y1, float3x3_rotate(vec3d_x1, -pi / 4.f)), 0.f, sq2, sq2, tolerance);
	eq(mul(vec4d_y1, float4x4_rotate(vec3d_x1, -pi / 4.f)), 0.f, sq2, sq2, 1.f, tolerance);

	eq(mul(vec3d_z1, float3x3_rotate(vec3d_y1, -pi / 4.f)), sq2, 0.f, sq2, tolerance);
	eq(mul(vec4d_z1, float4x4_rotate(vec3d_y1, -pi / 4.f)), sq2, 0.f, sq2, 1.f, tolerance);

	eq(mul(vec3d_x1, float3x3_rotate(vec3d_z1, -pi / 4.f)), sq2, sq2, 0.f, tolerance);
	eq(mul(vec4d_x1, float4x4_rotate(vec3d_z1, -pi / 4.f)), sq2, sq2, 0.f, 1.f, tolerance);

	eq(mul(vec3d_y1, float3x3_rotate(vec3d_x1, -pi * 3.f / 4.f)), 0.f, -sq2, sq2, tolerance);
	eq(mul(vec4d_y1, float4x4_rotate(vec3d_x1, -pi * 3.f / 4.f)), 0.f, -sq2, sq2, 1.f, tolerance);

	eq(mul(vec3d_z1, float3x3_rotate(vec3d_y1, -pi * 3.f / 4.f)), sq2, 0.f, -sq2, tolerance);
	eq(mul(vec4d_z1, float4x4_rotate(vec3d_y1, -pi * 3.f / 4.f)), sq2, 0.f, -sq2, 1.f, tolerance);

	eq(mul(vec3d_x1, float3x3_rotate(vec3d_z1, -pi * 3.f / 4.f)), -sq2, sq2, 0.f, tolerance);
	eq(mul(vec4d_x1, float4x4_rotate(vec3d_z1, -pi * 3.f / 4.f)), -sq2, sq2, 0.f, 1.f, tolerance);

	// Translation

	eq(mul(vec3d_a1, float3x3_translate(2.f, 3.f)), 3.f, 4.f, 1.f, tolerance);
	eq(mul(vec3d_a1, float3x3_translate(float2(2.f, 3.f))), 3.f, 4.f, 1.f, tolerance);

	eq(mul(vec4d_a1, float4x4_translate(2.f, 3.f, 4.f)), 3.f, 4.f, 5.f, 1.f, tolerance);
	eq(mul(vec4d_a1, float4x4_translate(float3(2.f, 3.f, 4.f))), 3.f, 4.f, 5.f, 1.f, tolerance);

	// World to View coordinates transformation

	const float3 view_position(1.f, 0.f, 0.f);
	const float3 view_target(0.f, 0.f, 0.f);
	const float3 view_up(0.f, 0.f, 1.f);

	eq(mul(vec4d_a1, float4x4_look_at(view_position, view_target, view_up, true)), -1.f, 1.f, 0.f, 1.f, tolerance);
	eq(mul(vec4d_a1, float4x4_look_at(view_position, view_target, view_up, false)), 1.f, 1.f, 0.f, 1.f, tolerance);

	// View to Orthographic Projection coordinates transformation

	const float4 vec4d_view1(0.5f, 0.5f, 0.f, 1.f);
	const float l = -0.5f, r = 0.5f, b = -0.5f, t = 0.5f, n = -1.f, f = 1.f;
	const float w = r - l, h = t - b;

	eq(mul(vec4d_view1, float4x4_orthographic(l, r, b, t, n, f, true, true)), 1.f, 1.f, 0.5f, 1.f, tolerance);
	eq(mul(vec4d_view1, float4x4_orthographic(w, h, n, f, true, true)), 1.f, 1.f, 0.5f, 1.f, tolerance);

	eq(mul(vec4d_view1, float4x4_orthographic(l, r, b, t, n, f, false, false)), 1.f, 1.f, 0.f, 1.f, tolerance);
	eq(mul(vec4d_view1, float4x4_orthographic(w, h, n, f, false, false)), 1.f, 1.f, 0.f, 1.f, tolerance);

	// View to Perspective Projection coordinates transformation

	const float4 vec4d_view2(0.5f, 0.5f, 1.f, 1.f);
	const float np = 0.001f;
	const float aspect = w / h;
	const float fov_x = 2.f * std::atan(w / (2.f * np));
	const float fov_y = 2.f * std::atan(h / (2.f * np));

	eq(mul(vec4d_view2, float4x4_perspective(l, r, b, t, np, f, true, true)), 0.001f, 0.001f, 1.f, 1.f, tolerance);
	eq(mul(vec4d_view2, float4x4_perspective(w, h, np, f, true, true)), 0.001f, 0.001f, 1.f, 1.f, tolerance);
	eq(mul(vec4d_view2, float4x4_perspective_fovx(fov_x, aspect, np, f, true, true)), 0.001f, 0.001f, 1.f, 1.f, tolerance);
	eq(mul(vec4d_view2, float4x4_perspective_fovy(fov_y, aspect, np, f, true, true)), 0.001f, 0.001f, 1.f, 1.f, tolerance);

	eq(mul(vec4d_view2, float4x4_perspective(l, r, b, t, np, f, false, false)), 0.001f, 0.001f, -1.004004f, -1.f, tolerance);
	eq(mul(vec4d_view2, float4x4_perspective(w, h, np, f, false, false)), 0.001f, 0.001f, -1.004004f, -1.f, tolerance);
	eq(mul(vec4d_view2, float4x4_perspective_fovx(fov_x, aspect, np, f, false, false)), 0.001f, 0.001f, -1.004004f, -1.f, tolerance);
	eq(mul(vec4d_view2, float4x4_perspective_fovy(fov_y, aspect, np, f, false, false)), 0.001f, 0.001f, -1.004004f, -1.f, tolerance);
}
