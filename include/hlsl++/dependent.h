#pragma once

#include "hlsl++/vector_float.h"
#include "hlsl++/vector_int.h"
#include "hlsl++/vector_uint.h"
#include "hlsl++/quaternion.h"
#include "hlsl++/matrix_float.h"

hlslpp_module_export namespace hlslpp
{
	float1::float1(const int1& i) hlslpp_noexcept : vec(_hlslpp_cvtepi32_ps(i.vec)) {}
	float2::float2(const int2& i) hlslpp_noexcept : vec(_hlslpp_cvtepi32_ps(i.vec)) {}
	float3::float3(const int3& i) hlslpp_noexcept : vec(_hlslpp_cvtepi32_ps(i.vec)) {}
	float4::float4(const int4& i) hlslpp_noexcept : vec(_hlslpp_cvtepi32_ps(i.vec)) {}

	float1::float1(const uint1& i) hlslpp_noexcept : vec(_hlslpp_cvtepu32_ps(i.vec)) {}
	float2::float2(const uint2& i) hlslpp_noexcept : vec(_hlslpp_cvtepu32_ps(i.vec)) {}
	float3::float3(const uint3& i) hlslpp_noexcept : vec(_hlslpp_cvtepu32_ps(i.vec)) {}
	float4::float4(const uint4& i) hlslpp_noexcept : vec(_hlslpp_cvtepu32_ps(i.vec)) {}

	int1::int1(const float1& f) hlslpp_noexcept : vec(_hlslpp_cvttps_epi32(f.vec)) {}
	int2::int2(const float2& f) hlslpp_noexcept : vec(_hlslpp_cvttps_epi32(f.vec)) {}
	int3::int3(const float3& f) hlslpp_noexcept : vec(_hlslpp_cvttps_epi32(f.vec)) {}
	int4::int4(const float4& f) hlslpp_noexcept : vec(_hlslpp_cvttps_epi32(f.vec)) {}

	uint1::uint1(const float1& f) hlslpp_noexcept : vec(_hlslpp_cvttps_epu32(f.vec)) {}
	uint2::uint2(const float2& f) hlslpp_noexcept : vec(_hlslpp_cvttps_epu32(f.vec)) {}
	uint3::uint3(const float3& f) hlslpp_noexcept : vec(_hlslpp_cvttps_epu32(f.vec)) {}
	uint4::uint4(const float4& f) hlslpp_noexcept : vec(_hlslpp_cvttps_epu32(f.vec)) {}

	hlslpp_inline float1x1::float1x1(const float2x2& m) hlslpp_noexcept
	{
		vec = m.vec;
	}

	hlslpp_inline float2x2::float2x2(const float3x3& m) hlslpp_noexcept
	{
		vec = _hlslpp_shuf_xyxy_ps(m.vec0, m.vec1);
	}

	hlslpp_inline float3x3::float3x3(const quaternion& q) hlslpp_noexcept
	{
		_hlslpp_quat_to_3x3_ps(q.vec, vec0, vec1, vec2);
	}

	hlslpp_inline float3x3::float3x3(const float4x4& m) hlslpp_noexcept
	{
#if defined(HLSLPP_SIMD_REGISTER_256)
		vec0 = _hlslpp256_low_ps(m.vec0);
		vec1 = _hlslpp256_high_ps(m.vec0);
		vec2 = _hlslpp256_low_ps(m.vec1);
#else
		vec0 = m.vec0;
		vec1 = m.vec1;
		vec2 = m.vec2;
#endif
	}

	hlslpp_inline float4x4::float4x4(const quaternion& q) hlslpp_noexcept
	{
#if defined(HLSLPP_SIMD_REGISTER_256)

		n128 temp_vec0, temp_vec1, temp_vec2;

		_hlslpp_quat_to_3x3_ps(q.vec, temp_vec0, temp_vec1, temp_vec2);
		const n256 row01Mask = _hlslpp256_castsi256_ps(_hlslpp256_set_epi32(0xffffffff, 0xffffffff, 0xffffffff, 0, 0xffffffff, 0xffffffff, 0xffffffff, 0));
		const n256 row23Mask = _hlslpp256_castsi256_ps(_hlslpp256_set_epi32(0xffffffff, 0xffffffff, 0xffffffff, 0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff));

		const n256 row01 = _hlslpp256_set128_ps(temp_vec0, temp_vec1);
		const n256 row23 = _hlslpp256_set128_ps(temp_vec2, _hlslpp_set_ps(0.0f, 0.0f, 0.0f, 1.0f));

		vec0 = _hlslpp256_and_ps(row01, row01Mask);
		vec1 = _hlslpp256_and_ps(row23, row23Mask);

#else

		_hlslpp_quat_to_3x3_ps(q.vec, vec0, vec1, vec2);
		const n128 zeroLast = _hlslpp_castsi128_ps(_hlslpp_set_epi32(0xffffffff, 0xffffffff, 0xffffffff, 0));
		vec0 = _hlslpp_and_ps(vec0, zeroLast);
		vec1 = _hlslpp_and_ps(vec1, zeroLast);
		vec2 = _hlslpp_and_ps(vec2, zeroLast);
		vec3 = _hlslpp_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

#endif
	}

	hlslpp_inline quaternion::quaternion(const float3x3& m) hlslpp_noexcept
	{
		_hlslpp_3x3_to_quat_ps(m.vec0, m.vec1, m.vec2, vec);
	}

	hlslpp_inline float1 ldexp(const float1& f, const int1& e) { return float1(_hlslpp_ldexp_ps(f.vec, e.vec)); }
	hlslpp_inline float2 ldexp(const float2& f, const int2& e) { return float2(_hlslpp_ldexp_ps(f.vec, e.vec)); }
	hlslpp_inline float3 ldexp(const float3& f, const int3& e) { return float3(_hlslpp_ldexp_ps(f.vec, e.vec)); }
	hlslpp_inline float4 ldexp(const float4& f, const int4& e) { return float4(_hlslpp_ldexp_ps(f.vec, e.vec)); }

	//-----------------------
	// asfloat, asuint, asint
	//-----------------------

	hlslpp_inline float asfloat(const uint v) { return detail::packed_union(v)._f32; }
	hlslpp_inline float1 asfloat(const uint1& v) { return (float1&)v; }
	hlslpp_inline float2 asfloat(const uint2& v) { return (float2&)v; }
	hlslpp_inline float3 asfloat(const uint3& v) { return (float3&)v; }
	hlslpp_inline float4 asfloat(const uint4& v) { return (float4&)v; }

	hlslpp_inline float asfloat(const int v) { return detail::packed_union(v)._f32; }
	hlslpp_inline float1 asfloat(const int1& v) { return (float1&)v; }
	hlslpp_inline float2 asfloat(const int2& v) { return (float2&)v; }
	hlslpp_inline float3 asfloat(const int3& v) { return (float3&)v; }
	hlslpp_inline float4 asfloat(const int4& v) { return (float4&)v; }

	hlslpp_inline uint asuint(const int v) { return detail::packed_union(v)._u32; }
	hlslpp_inline uint1 asuint(const int1& v) { return (uint1&)v; }
	hlslpp_inline uint2 asuint(const int2& v) { return (uint2&)v; }
	hlslpp_inline uint3 asuint(const int3& v) { return (uint3&)v; }
	hlslpp_inline uint4 asuint(const int4& v) { return (uint4&)v; }

	hlslpp_inline uint asuint(const float v) { return detail::packed_union(v)._u32; }
	hlslpp_inline uint1 asuint(const float1& v) { return (uint1&)v; }
	hlslpp_inline uint2 asuint(const float2& v) { return (uint2&)v; }
	hlslpp_inline uint3 asuint(const float3& v) { return (uint3&)v; }
	hlslpp_inline uint4 asuint(const float4& v) { return (uint4&)v; }

	hlslpp_inline int asint(const uint v) { return detail::packed_union(v)._i32; }
	hlslpp_inline int1 asint(const uint1& v) { return (int1&)v; }
	hlslpp_inline int2 asint(const uint2& v) { return (int2&)v; }
	hlslpp_inline int3 asint(const uint3& v) { return (int3&)v; }
	hlslpp_inline int4 asint(const uint4& v) { return (int4&)v; }

	hlslpp_inline int asint(const float v) { return detail::packed_union(v)._i32; }
	hlslpp_inline int1 asint(const float1& v) { return (int1&)v; }
	hlslpp_inline int2 asint(const float2& v) { return (int2&)v; }
	hlslpp_inline int3 asint(const float3& v) { return (int3&)v; }
	hlslpp_inline int4 asint(const float4& v) { return (int4&)v; }
}