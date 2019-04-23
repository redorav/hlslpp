namespace hlslpp
{
	float1::float1(const int1& i) : vec(_hlslpp_castsi128_ps(i.vec)) {}

	float2::float2(const int2& i) : vec(_hlslpp_castsi128_ps(i.vec)) {}

	float3::float3(const int3& i) : vec(_hlslpp_castsi128_ps(i.vec)) {}

	float4::float4(const int4& i) : vec(_hlslpp_castsi128_ps(i.vec)) {}

	hlslpp_inline float3x3::float3x3(const quaternion& q)
	{
		_hlslpp_quat_to_3x3_ps(q.vec, vec0, vec1, vec2);
	}

	hlslpp_inline float4x4::float4x4(const quaternion& q)
	{
		_hlslpp_quat_to_4x4_ps(q.vec, vec0, vec1, vec2, vec3);
	}
}