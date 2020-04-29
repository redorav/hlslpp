namespace hlslpp
{
	float1::float1(const int1& i) : vec(_hlslpp_cvtepi32_ps(i.vec)) {}

	float2::float2(const int2& i) : vec(_hlslpp_cvtepi32_ps(i.vec)) {}

	float3::float3(const int3& i) : vec(_hlslpp_cvtepi32_ps(i.vec)) {}

	float4::float4(const int4& i) : vec(_hlslpp_cvtepi32_ps(i.vec)) {}

	float1::float1(const uint1& i) : vec(_hlslpp_cvtepu32_ps(i.vec)) {}

	float2::float2(const uint2& i) : vec(_hlslpp_cvtepu32_ps(i.vec)) {}

	float3::float3(const uint3& i) : vec(_hlslpp_cvtepu32_ps(i.vec)) {}

	float4::float4(const uint4& i) : vec(_hlslpp_cvtepu32_ps(i.vec)) {}

	hlslpp_inline float3x3::float3x3(const quaternion& q)
	{
		_hlslpp_quat_to_3x3_ps(q.vec, vec0, vec1, vec2);
	}

	hlslpp_inline float4x4::float4x4(const quaternion& q)
	{
#if defined(HLSLPP_SIMD_REGISTER_FLOAT8)

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
}