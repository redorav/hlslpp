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

		return transpose(float4x4(
			float4(right,  -dot(position, right)),
			float4(up_dir, -dot(position, up_dir)),
			float4(look,   -dot(position, look)),
			float4(0.f, 0.f, 0.f, 1.f)
		));
	}

} // namespace hlslpp
