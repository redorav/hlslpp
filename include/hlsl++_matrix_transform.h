//---------------------------------//
// Special Transformation Matrices //
//---------------------------------//

#include <cmath>

namespace hlslpp
{
	// Scale 2D

	hlslpp_inline float2x2 float2x2_scale_2d(float sx, float sy)
	{
		return float2x2(
			sx,  0.f,
			0.f, sy
		);
	}

	hlslpp_inline float2x2 float2x2_scale_2d(const float2& s)
	{
		return float2x2_scale_2d(s.x, s.y);
	}

	hlslpp_inline float2x2 float2x2_scale_2d(float su)
	{
		return float2x2_scale_2d(su, su);
	}

	hlslpp_inline float3x3 float3x3_scale_2d(float sx, float sy)
	{
		return float3x3(
			sx,  0.f, 0.f,
			0.f, sy,  0.f,
			0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float3x3 float3x3_scale_2d(const float2& s)
	{
		return float3x3_scale_2d(s.x, s.y);
	}

	hlslpp_inline float3x3 float3x3_scale_2d(float su)
	{
		return float3x3_scale_2d(su, su);
	}

	// Scale 3D

	hlslpp_inline float3x3 float3x3_scale_3d(float sx, float sy, float sz)
	{
		return float3x3(
			sx,  0.f, 0.f,
			0.f, sy,  0.f,
			0.f, 0.f, sz
		);
	}

	hlslpp_inline float3x3 float3x3_scale_3d(const float3& s)
	{
		return float3x3_scale_3d(s.x, s.y, s.z);
	}

	hlslpp_inline float3x3 float3x3_scale_3d(float su)
	{
		return float3x3_scale_3d(su, su, su);
	}

	hlslpp_inline float4x4 float4x4_scale_3d(float sx, float sy, float sz)
	{
		return float4x4(
			sx,  0.f, 0.f, 0.f,
			0.f, sy,  0.f, 0.f,
			0.f, 0.f, sz,  0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float4x4 float4x4_scale_3d(const float3& s)
	{
		return float4x4_scale_3d(s.x, s.y, s.z);
	}

	hlslpp_inline float4x4 float4x4_scale_3d(float su)
	{
		return float4x4_scale_3d(su, su, su);
	}

	// Rotation 2D

	hlslpp_inline float2x2 float2x2_rotation_2d(float angle_rad)
	{
		const float s = std::sin(angle_rad);
		const float c = std::cos(angle_rad);

		return float2x2(
			c, -s,
			s,  c
		);
	}

	hlslpp_inline float3x3 float3x3_rotation_2d(float angle_rad)
	{
		const float s = std::sin(angle_rad);
		const float c = std::cos(angle_rad);

		return float3x3(
			c,  -s,   0.f,
			s,   c,   0.f,
			0.f, 0.f, 1.f
		);
	}

	// Rotation 3D

	hlslpp_inline float3x3 float3x3_rotation_3d(const float3& axis, float angle_rad)
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

	hlslpp_inline float4x4 float4x4_rotation_3d(const float3& axis, float angle_rad)
	{
		const float s  = std::sin(angle_rad);
		const float c  = std::cos(angle_rad);

		const float3 as = axis * s;
		const float3 ac = axis * (1.f - c);
		const float3 v1 = axis * ac;
		const float3 v2 = axis * ac.yzx;

		return float4x4(
			v1.x + c,    v2.x + as.z, v2.z - as.y, 0.f,
			v2.x - as.z, v1.y + c,    v2.y + as.x, 0.f,
			v2.z + as.y, v2.y - as.x, v1.z + c,    0.f,
			0.f,         0.f,         0.f,         1.f
		);
	}

	// Translation 2D

	hlslpp_inline float3x3 float3x3_translation_2d(float tx, float ty)
	{
		return float3x3(
			1.f, 0.f, tx,
			0.f, 1.f, ty,
			0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float3x3 float3x3_translation_2d(const float2& t)
	{
		return float3x3_translation_2d(t.x, t.y);
	}

	// Translation 3D

	hlslpp_inline float4x4 float4x4_translation_3d(float tx, float ty, float tz)
	{
		return float4x4(
			1.f, 0.f, 0.f, tx,
			0.f, 1.f, 0.f, ty,
			0.f, 0.f, 1.f, tz,
			0.f, 0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float4x4 float4x4_translation_3d(const float3& t)
	{
		return float4x4_translation_3d(t.x, t.y, t.z);
	}

} // namespace hlslpp
