//---------------------------------//
// Special Transformation Matrices //
//---------------------------------//

#include <cmath>

namespace hlslpp
{
	// Scale

	hlslpp_inline float2x2 float2x2_scale(float sx, float sy)
	{
		return float2x2(
			sx,  0.f,
			0.f, sy
		);
	}

	hlslpp_inline float2x2 float2x2_scale(float2 s)
	{
		return float2x2_scale(s.x, s.y);
	}

	hlslpp_inline float2x2 float2x2_scale(float su)
	{
		return float2x2_scale(su, su);
	}

	hlslpp_inline float3x3 float3x3_scale(float sx, float sy, float sz)
	{
		return float3x3(
			sx,  0.f, 0.f,
			0.f, sy,  0.f,
			0.f, 0.f, sz
		);
	}

	hlslpp_inline float3x3 float3x3_scale(float3 s)
	{
		return float3x3_scale(s.x, s.y, s.z);
	}

	hlslpp_inline float3x3 float3x3_scale(float su)
	{
		return float3x3_scale(su, su, su);
	}

	// Rotation

	hlslpp_inline float2x2 float2x2_rotation(float angle_rad)
	{
		const float s = std::sin(angle_rad);
		const float c = std::cos(angle_rad);

		return float2x2(
			c, -s,
			s,  c
		);
	}

	hlslpp_inline float3x3 float3x3_rotation(const float3& axis, float angle_rad)
	{
		const float s  = std::sin(angle_rad);
		const float c  = std::cos(angle_rad);

		const float3 as = axis * s;
		const float3 ac = axis * (1.f - c);
		const float3 v1 = axis * ac;
		const float3 v2 = axis * ac.yzx;

		return float3x3(
			v1.x + c,    v2.x + as.z, v2.z - as.y,
			v2.x - as.z, v1.y + c,    v2.y + as.x,
			v2.z + as.y, v2.y - as.x, v1.z + c
		);
	}

	// Translation

	hlslpp_inline float3x3 float3x3_translation(float tx, float ty)
	{
		return float3x3(
			1.f, 0.f, tx,
			0.f, 1.f, ty,
			0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float3x3 float3x3_translation(const float2& t)
	{
		return float3x3_translation(t.x, t.y);
	}

	hlslpp_inline float4x4 float4x4_translation(float tx, float ty, float tz)
	{
		return float4x4(
			1.f, 0.f, 0.f, tx,
			0.f, 1.f, 0.f, ty,
			0.f, 0.f, 1.f, tz,
			0.f, 0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float4x4 float4x4_translation(const float3& t)
	{
		return float4x4_translation(t.x, t.y, t.z);
	}

} // namespace hlslpp
