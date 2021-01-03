//---------------------------------//
// Special Transformation Matrices //
//---------------------------------//

// NOTE:
// All transformation matrices assume "vector(N) * matrix(NxM)" multiplication order because
// HLSL math is based on row-major matrix storage and vector can be represented as 1xN matrix

#include <cmath>

namespace hlslpp
{
	// Scaling

	hlslpp_inline float2x2 float2x2_scale(float sx, float sy)
	{
		return float2x2(
			sx,  0.f,
			0.f, sy
		);
	}

	hlslpp_inline float2x2 float2x2_scale(const float2& s)
	{
		return float2x2_scale(s.x, s.y);
	}

	hlslpp_inline float2x2 float2x2_scale(float su)
	{
		return float2x2_scale(su, su);
	}

	hlslpp_inline float3x3 float3x3_scale(float sx, float sy, float sz = 1.f)
	{
		return float3x3(
			sx,  0.f, 0.f,
			0.f, sy,  0.f,
			0.f, 0.f, sz
		);
	}

	hlslpp_inline float3x3 float3x3_scale(const float3& s)
	{
		return float3x3_scale(s.x, s.y, s.z);
	}

	hlslpp_inline float3x3 float3x3_scale(const float2& s)
	{
		return float3x3_scale(s.x, s.y, 1.f);
	}

	hlslpp_inline float3x3 float3x3_scale(float su)
	{
		return float3x3_scale(su, su, su);
	}

	hlslpp_inline float4x4 float4x4_scale(float sx, float sy, float sz)
	{
		return float4x4(
			sx,  0.f, 0.f, 0.f,
			0.f, sy,  0.f, 0.f,
			0.f, 0.f, sz,  0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float4x4 float4x4_scale(const float3& s)
	{
		return float4x4_scale(s.x, s.y, s.z);
	}

	hlslpp_inline float4x4 float4x4_scale(float su)
	{
		return float4x4_scale(su, su, su);
	}

	// Rotation

	hlslpp_inline float2x2 float2x2_rotate(float angle_rad)
	{
		const float s = std::sin(angle_rad);
		const float c = std::cos(angle_rad);

		return float2x2(
			c,  s,
			-s, c
		);
	}

	hlslpp_inline float3x3 float3x3_rotate(float angle_rad)
	{
		const float s = std::sin(angle_rad);
		const float c = std::cos(angle_rad);

		return float3x3(
			c,   s,   0.f,
			-s,  c,   0.f,
			0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float3x3 float3x3_rotate(const float3& axis, float angle_rad)
	{
		const float s  = std::sin(angle_rad);
		const float c  = std::cos(angle_rad);

		const float3 as = axis * s;
		const float3 ac = axis * (1.f - c);
		const float3 v1 = axis * ac;
		const float3 v2 = axis * ac.yzx;

		return float3x3(
			v1.x + c,    v2.x - as.z, v2.z + as.y,
			v2.x + as.z, v1.y + c,    v2.y - as.x,
			v2.z - as.y, v2.y + as.x, v1.z + c
		);
	}

	hlslpp_inline float4x4 float4x4_rotate(const float3& axis, float angle_rad)
	{
		const float s  = std::sin(angle_rad);
		const float c  = std::cos(angle_rad);

		const float3 as = axis * s;
		const float3 ac = axis * (1.f - c);
		const float3 v1 = axis * ac;
		const float3 v2 = axis * ac.yzx;

		return float4x4(
			v1.x + c,    v2.x - as.z, v2.z + as.y, 0.f,
			v2.x + as.z, v1.y + c,    v2.y - as.x, 0.f,
			v2.z - as.y, v2.y + as.x, v1.z + c,    0.f,
			0.f,         0.f,         0.f,         1.f
		);
	}

	// Translation

	hlslpp_inline float3x3 float3x3_translate(float tx, float ty)
	{
		return float3x3(
			1.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			tx,  ty,  1.f
		);
	}

	hlslpp_inline float3x3 float3x3_translate(const float2& t)
	{
		return float3x3_translate(t.x, t.y);
	}

	hlslpp_inline float4x4 float4x4_translate(float tx, float ty, float tz)
	{
		return float4x4(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			tx,  ty,  tz,  1.f
		);
	}

	hlslpp_inline float4x4 float4x4_translate(const float3& t)
	{
		return float4x4_translate(t.x, t.y, t.z);
	}

	// World to View coordinates transformation

	hlslpp_inline float4x4 float4x4_look_at(const float3& position, const float3& target, const float3& up, bool left_handed = true)
	{
		const float3 look = normalize(target - position) * (left_handed ? 1.f : -1.f);
		const float3 right = normalize(cross(up, look));
		const float3 up_dir = cross(look, right);

		return float4x4(
			right.x,               up_dir.x,               look.x,               0.f,
			right.y,               up_dir.y,               look.y,               0.f,
			right.z,               up_dir.z,               look.z,               0.f,
			-dot(position, right), -dot(position, up_dir), -dot(position, look), 1.f
		);
	}

	// View to Orthographic Projection coordinates transformation

	hlslpp_inline float4x4 float4x4_orthographic(float left, float right, float bottom, float top, float near, float far, bool zclip_zero, bool left_handed = true)
	{
		const float inv_width  = 1.f / (right - left);
		const float inv_height = 1.f / (top - bottom);
		const float inv_depth  = 1.f / (far - near);
		const float s = left_handed ? 1.f : -1.f;

		return float4x4(
			2.f * inv_width,             0.f,                          0.f,                                            0.f,
			0.f,                         2.f * inv_height,             0.f,                                            0.f,
			0.f,                         0.f,                          s * (zclip_zero ? 1.f : 2.f) * inv_depth,       0.f,
			-(right + left) * inv_width, -(top + bottom) * inv_height, -(near + (zclip_zero ? 0.f : far)) * inv_depth, 1.f
		);
	}

    hlslpp_inline float4x4 float4x4_orthographic(float width, float height, float near, float far, bool zclip_zero, bool left_handed = true)
	{
		const float half_width  = width  / 2.f;
		const float half_height = height / 2.f;
		return float4x4_orthographic(-half_width, half_width, -half_height, half_height, near, far, zclip_zero, left_handed);
	}

	// View to Perspective Projection coordinates transformation

	hlslpp_inline float4x4 float4x4_perspective(float left, float right, float bottom, float top, float near, float far, bool zclip_zero, bool left_handed = true)
	{
		const float inv_width  = 1.f / (right - left);
		const float inv_height = 1.f / (top - bottom);
		const float inv_depth  = 1.f / (far - near);
		const float dbl_near   = 2.f * near;

		const float s   = left_handed ? 1.f : -1.f;
		const float m22 = s * (far + (zclip_zero ? 0.f : near)) * inv_depth;
		const float m23 = zclip_zero ? -s * near * m22 : -2.f * far * near * inv_depth;

		return float4x4(
			dbl_near * inv_width,            0.f,                               0.f, 0.f,
			0.f,                             dbl_near * inv_height,             0.f, 0.f,
			-s * (right + left) * inv_width, -s * (top + bottom) * inv_height,  m22, s,
			0.f,                             0.f,                               m23, 0.f
		);
	}

	hlslpp_inline float4x4 float4x4_perspective(float width, float height, float near, float far, bool zclip_zero, bool left_handed = true)
	{
		const float half_width  = width  / 2.f;
		const float half_height = height / 2.f;
		return float4x4_perspective(-half_width, half_width, -half_height, half_height, near, far, zclip_zero, left_handed);
	}

	hlslpp_inline float4x4 float4x4_perspective_fovx(float fov_x, float aspect, float near, float far, bool zclip_zero, bool left_handed = true)
	{
		const float width = 2.f * near * std::tan(fov_x / 2.f);
		return float4x4_perspective(width, width / aspect, near, far, zclip_zero, left_handed);
	}

	hlslpp_inline float4x4 float4x4_perspective_fovy(float fov_y, float aspect, float near, float far, bool zclip_zero, bool left_handed = true)
	{
		const float height = 2.f * near * std::tan(fov_y / 2.f);
		return float4x4_perspective(height * aspect, height, near, far, zclip_zero, left_handed);
	}

} // namespace hlslpp
