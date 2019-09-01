//-----------
// Quaternion
//-----------

namespace hlslpp
{
	struct hlslpp_nodiscard quaternion
	{
		quaternion() {}
		explicit quaternion(n128 vec) : vec(vec) {}

		template<typename T1, typename T2, typename T3, typename T4>
		quaternion(T1 f1, T2 f2, T3 f3, T4 f4, hlslpp_enable_if_number_4(T1, T2, T3, T4)) : vec(_hlslpp_set_ps(float(f1), float(f2), float(f3), float(f4))) {}

		quaternion(const float1& f1, const float1& f2, const float1& f3, const float1& f4) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(f1.vec, f3.vec), _hlslpp_shuf_xxxx_ps(f2.vec, f4.vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }

		quaternion(const float2& f1, const float1& f2, const float1& f3) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xyxx_ps(f1.vec, f2.vec), _hlslpp_perm_xxxx_ps(f3.vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }
		quaternion(const float1& f1, const float2& f2, const float1& f3) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(f1.vec, f3.vec), _hlslpp_perm_xxyx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }
		quaternion(const float1& f1, const float1& f2, const float2& f3) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxy_ps(f1.vec, f3.vec), _hlslpp_perm_xxxx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }

		quaternion(const float2& f1, const float2& f2) { vec = _hlslpp_shuf_xyxy_ps(f1.vec, f2.vec); }

		quaternion(const float1& f1, const float3& f2) { vec = _hlslpp_blend_ps(f1.vec, _hlslpp_perm_xxyz_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 0)); }
		quaternion(const float3& f1, const float1& f2) { vec = _hlslpp_blend_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }

		quaternion(const float4& f) { vec = f.vec; }
		//quaternion(const float1x4& q) { vec = q.vec; }

		static const quaternion& identity() { static const quaternion identity = quaternion(0.0f, 0.0f, 0.0f, 1.0f); return identity; };

		union
		{
			n128 vec;
			#include "swizzle/hlsl++_vector_float_x.h"
			#include "swizzle/hlsl++_vector_float_y.h"
			#include "swizzle/hlsl++_vector_float_z.h"
			#include "swizzle/hlsl++_vector_float_w.h"
		};
	};

	hlslpp_inline n128 _hlslpp_quat_mul_ps(const n128 q0, const n128 q1)
	{
		n128 tmp_mul_0 = _hlslpp_mul_ps(_hlslpp_perm_xyxx_ps(q0), _hlslpp_perm_wwyx_ps(q1));
		n128 tmp_mad_1 = _hlslpp_madd_ps(_hlslpp_perm_yzzy_ps(q0), _hlslpp_perm_zxwy_ps(q1), tmp_mul_0);
		const n128i signMask = _hlslpp_set_epi32(0, 0, 0, 0x80000000);
		n128 tmp_sign = _hlslpp_xor_ps(tmp_mad_1, _hlslpp_castsi128_ps(signMask)); // Flip the sign from the last row (w)
		n128 tmp_mad_2 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(q0), q1, tmp_sign);
		n128 result = _hlslpp_subm_ps(tmp_mad_2, _hlslpp_perm_zxyz_ps(q0), _hlslpp_perm_yzxz_ps(q1));
		return result;
	}

	hlslpp_inline n128 _hlslpp_quat_conjugate_ps(const n128 q)
	{
		static const n128i signMask = _hlslpp_set_epi32(0x80000000, 0x80000000, 0x80000000, 0);
		return _hlslpp_xor_ps(q, _hlslpp_castsi128_ps(signMask)); // Flip the sign bits of the vector part of the quaternion
	}

	// Quaternion - vector multiplication. Faster version of q * v * q*
	// Rotates a vector using a quaternion
	// https://blog.molecular-matters.com/2013/05/24/a-faster-quaternion-vector-multiplication/
	hlslpp_inline n128 _hlslpp_quat_mul_vec_ps(const n128 q, const n128 v)
	{
		n128 t = _hlslpp_cross_ps(q, v);
		t = _hlslpp_add_ps(t, t);
		n128 qxt = _hlslpp_cross_ps(q, t);
		n128 v_qxt = _hlslpp_add_ps(v, qxt);
		n128 result = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(q), t, v_qxt);
		return result;
	}

	hlslpp_inline n128 _hlslpp_quat_inverse_ps(const n128 q)
	{
		n128 conjugate = _hlslpp_quat_conjugate_ps(q);
		n128 sqNorm = _hlslpp_dot4_ps(q, q);
		n128 result = _hlslpp_div_ps(conjugate, sqNorm);
		return result;
	}

	// Assume axis is a 3-component vector and angle is contained in the x component of angle
	// Also assume that the axis is normalized
	hlslpp_inline n128 _hlslpp_quat_axis_angle_ps(const n128 axis, const n128 angle)
	{
		n128 angle05 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(angle), f4_05);
		n128 sin	= _hlslpp_mul_ps(_hlslpp_sin_ps(angle05), axis);
		n128 cos	= _hlslpp_cos_ps(angle05);
		n128 result = _hlslpp_blend_ps(sin, cos, HLSLPP_BLEND_MASK(1, 1, 1, 0));
		return result;
	}

	// http://d.hatena.ne.jp/ohtorii/20150424/p1
	hlslpp_inline n128 _hlslpp_quat_euler_zxy_ps(const n128 angles)
	{
		n128 angles05 = _hlslpp_mul_ps(angles, f4_05);
		n128 sin = _hlslpp_sin_ps(angles05);
		n128 cos = _hlslpp_cos_ps(angles05);

		n128 CxCxCxCx	= _hlslpp_perm_xxxx_ps(cos);
		n128 SySyCyCy	= _hlslpp_shuf_yyyy_ps(sin, cos);
		n128 SzCzSzCz	= _hlslpp_blend_ps(_hlslpp_perm_zzzz_ps(sin), _hlslpp_perm_zzzz_ps(cos), HLSLPP_BLEND_MASK(1, 0, 1, 0));

		n128 term1		= _hlslpp_mul_ps(CxCxCxCx, _hlslpp_mul_ps(SySyCyCy, SzCzSzCz));

		n128 SxSxSxSx	= _hlslpp_perm_xxxx_ps(sin);
		n128 CyCySySy	= _hlslpp_shuf_yyyy_ps(cos, sin);
		n128 CzSzCzSz	= _hlslpp_blend_ps(_hlslpp_perm_zzzz_ps(sin), _hlslpp_perm_zzzz_ps(cos), HLSLPP_BLEND_MASK(0, 1, 0, 1));

		n128 term2		= _hlslpp_mul_ps(SxSxSxSx, _hlslpp_mul_ps(CyCySySy, CzSzCzSz));
		const n128i signMask = _hlslpp_set_epi32(0, 0x80000000, 0x80000000, 0);
		term2			= _hlslpp_xor_ps(term2, _hlslpp_castsi128_ps(signMask)); // Flip the sign bits

		n128 result		= _hlslpp_add_ps(term1, term2);
		return result;
	}

	// Assume input quaternions are normalized
	// Assume t is in the x component
	inline n128 _hlslpp_quat_slerp_ps(const n128 q0, const n128 q1, const n128 t)
	{
		n128 cosHalfTheta		= _hlslpp_dot4_ps(q0, q1);
		n128 halfTheta			= _hlslpp_acos_ps(cosHalfTheta);

		n128 t4					= _hlslpp_shuf_xxxx_ps(t, f4_1);	// Contains t, t, 1, unused
		n128 oneMinusT			= _hlslpp_sub_ps(f4_1, t4);			// Contains 1 - t, 1 - t, 0, unused
		n128 lerpFactors		= _hlslpp_blend_ps(oneMinusT, t4, HLSLPP_BLEND_MASK(1, 0, 0, 1));	// Contains (1 - t), t, 1, unused
		n128 tTheta				= _hlslpp_mul_ps(lerpFactors, _hlslpp_perm_xxxx_ps(halfTheta));		// Contains (1 - t) * theta, t * theta, theta
		n128 sinVec				= _hlslpp_sin_ps(tTheta);											// Contains sin((1 - t) * theta), sin(t * theta), sin(theta)
		
		n128 sinTheta4			= _hlslpp_perm_zzzz_ps(sinVec);
		n128 sinVecDiv			= _hlslpp_div_ps(sinVec, sinTheta4);

		n128 mul0				= _hlslpp_mul_ps(q0, _hlslpp_perm_xxxx_ps(sinVecDiv));
		n128 mul1				= _hlslpp_mul_ps(q1, _hlslpp_perm_yyyy_ps(sinVecDiv));

		n128 result				= _hlslpp_add_ps(mul0, mul1);

		return result;
	}

	inline void _hlslpp_quat_to_3x3_ps(const n128 q, n128& row0, n128& row1, n128& row2)
	{
		n128 q_xxy		= _hlslpp_perm_xxyx_ps(q);
		n128 q_zyz		= _hlslpp_perm_zyzx_ps(q);
		n128 q_mul0		= _hlslpp_mul_ps(q_xxy, q_zyz);

		n128 q_yzx		= _hlslpp_perm_yzxx_ps(q);
		n128 q_www		= _hlslpp_perm_wwwx_ps(q);
		n128 q_mul1		= _hlslpp_mul_ps(q_yzx, q_www);

		n128 q_add		= _hlslpp_perm_yzxx_ps(_hlslpp_add_ps(q_mul0, q_mul1)); // swizzle to get in place
		q_add			= _hlslpp_add_ps(q_add, q_add);

		n128 q_sub		= _hlslpp_sub_ps(q_mul0, q_mul1);
		q_sub			= _hlslpp_add_ps(q_sub, q_sub);

		n128 q_xyz_2	= _hlslpp_mul_ps(q, q);

		n128 q_yxx_2	= _hlslpp_perm_yxxx_ps(q_xyz_2);
		n128 q_zzy_2	= _hlslpp_perm_zzyx_ps(q_xyz_2);

		n128 oneMinus_2 = _hlslpp_sub_ps(f4_05, _hlslpp_add_ps(q_yxx_2, q_zzy_2));
		oneMinus_2		= _hlslpp_add_ps(oneMinus_2, oneMinus_2);

		row0 = _hlslpp_blend_ps(oneMinus_2, q_sub,	HLSLPP_BLEND_MASK(1, 0, 0, 0));
		row0 = _hlslpp_blend_ps(row0, q_add,		HLSLPP_BLEND_MASK(1, 1, 0, 0));

		row1 = _hlslpp_blend_ps(oneMinus_2, q_sub,	HLSLPP_BLEND_MASK(0, 1, 0, 0));
		row1 = _hlslpp_blend_ps(row1, q_add,		HLSLPP_BLEND_MASK(0, 1, 1, 0));

		row2 = _hlslpp_blend_ps(oneMinus_2, q_sub,	HLSLPP_BLEND_MASK(0, 0, 1, 0));
		row2 = _hlslpp_blend_ps(row2, q_add,		HLSLPP_BLEND_MASK(1, 0, 1, 0));
	}

	inline void _hlslpp_quat_to_4x4_ps(const n128 q, n128& row0, n128& row1, n128& row2, n128& row3)
	{
		_hlslpp_quat_to_3x3_ps(q, row0, row1, row2);
		const n128 zeroLast = _hlslpp_castsi128_ps(_hlslpp_set_epi32(0xffffffff, 0xffffffff, 0xffffffff, 0));
		row0 = _hlslpp_and_ps(row0, zeroLast);
		row1 = _hlslpp_and_ps(row1, zeroLast);
		row2 = _hlslpp_and_ps(row2, zeroLast);
		row3 = _hlslpp_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
	}

	hlslpp_inline quaternion	operator + (const quaternion& q1, const quaternion& q2) { return quaternion(_hlslpp_add_ps(q1.vec, q2.vec)); }
	hlslpp_inline quaternion&	operator += (quaternion& q1, const quaternion& q2) { q1 = q1 + q2; return q1; }

	hlslpp_inline quaternion	operator - (const quaternion& q1, const quaternion& q2) { return quaternion(_hlslpp_sub_ps(q1.vec, q2.vec)); }
	hlslpp_inline quaternion&	operator -= (quaternion& q1, const quaternion& q2) { q1 = q1 - q2; return q1; }

	hlslpp_inline quaternion	operator * (const quaternion& q1, const quaternion& q2) { return quaternion(_hlslpp_quat_mul_ps(q1.vec, q2.vec)); }
	hlslpp_inline float3		operator * (const quaternion& q, const float3& v) { return float3(_hlslpp_quat_mul_vec_ps(q.vec, v.vec)); }

	hlslpp_inline quaternion	operator * (const quaternion& q, const float1& v) { return quaternion(_hlslpp_mul_ps(q.vec, _hlslpp_perm_xxxx_ps(v.vec))); }
	hlslpp_inline quaternion	operator * (const float1& v, const quaternion& q) { return q * v; }

	hlslpp_inline quaternion&	operator *= (quaternion& q1, const quaternion& q2) { q1 = q1 * q2; return q1; }
	hlslpp_inline quaternion&	operator *= (quaternion& q, const float1& v) { q = q * v; return q; }

	//inline quaternion operator / (const quaternion& q1, const quaternion& q2) { return quaternion(_hlslpp_div_ps(q1._vec, q2._vec)); }
	//inline quaternion& operator /= (quaternion& q1, const quaternion& q2) { q1 = q1 / q2; return q1; }

	hlslpp_inline quaternion	operator / (const quaternion& q, const float1& v) { return quaternion(_hlslpp_div_ps(q.vec, _hlslpp_perm_xxxx_ps(v.vec))); }
	hlslpp_inline quaternion&	operator /= (quaternion& q, const float1& v) { q = q / v; return q; }

	hlslpp_inline quaternion	operator - (const quaternion& q) { return quaternion(_hlslpp_neg_ps(q.vec)); }
	hlslpp_inline quaternion	operator * (const quaternion& q) { return quaternion(_hlslpp_quat_conjugate_ps(q.vec)); }
	hlslpp_inline float4		operator == (const quaternion& q1, const quaternion& q2) { return float4(_hlslpp_cmpeq1_ps(q1.vec, q2.vec)); }
	hlslpp_inline float4		operator != (const quaternion& q1, const quaternion& q2) { return float4(_hlslpp_cmpneq1_ps(q1.vec, q2.vec)); }
	hlslpp_inline float4		operator >  (const quaternion& q1, const quaternion& q2) { return float4(_hlslpp_cmpgt1_ps(q1.vec, q2.vec)); }
	hlslpp_inline float4		operator >= (const quaternion& q1, const quaternion& q2) { return float4(_hlslpp_cmpge1_ps(q1.vec, q2.vec)); }
	hlslpp_inline float4		operator <  (const quaternion& q1, const quaternion& q2) { return float4(_hlslpp_cmplt1_ps(q1.vec, q2.vec)); }
	hlslpp_inline float4		operator <= (const quaternion& q1, const quaternion& q2) { return float4(_hlslpp_cmple1_ps(q1.vec, q2.vec)); }

	hlslpp_inline quaternion	abs(const quaternion& q) { return quaternion(_hlslpp_abs_ps(q.vec)); }
	//hlslpp_inline float4		all(const quaternion& q) { return float4(_hlslpp_all1_ps(q.vec)); }
	//hlslpp_inline float4		any(const quaternion& q) { return float4(_hlslpp_any1_ps(q.vec)); }
	hlslpp_inline quaternion	axisangle(const float3& axis, const float1& angle) { return quaternion(_hlslpp_quat_axis_angle_ps(axis.vec, angle.vec)); }
	hlslpp_inline quaternion	conjugate(const quaternion& q) { return quaternion(_hlslpp_quat_conjugate_ps(q.vec)); }
	//clamp TODO
	hlslpp_inline float1		dot(const quaternion& q0, const quaternion& q1) { return float1(_hlslpp_dot4_ps(q0.vec, q1.vec)); }
	hlslpp_inline quaternion	euler(const float3& angles) { return quaternion(_hlslpp_quat_euler_zxy_ps(angles.vec)); }
	//hlslpp_inline quaternion exp(quaternion& q) { return quaternion(_hlslpp_exp_ps(q._vec)); }
	hlslpp_inline quaternion	frac(const quaternion& q) { return quaternion(_hlslpp_frac_ps(q.vec)); }
	hlslpp_inline quaternion	inverse(const quaternion& q) { return quaternion(_hlslpp_quat_inverse_ps(q.vec)); }
	hlslpp_inline float4		isfinite(const quaternion& q) { return float4(_hlslpp_andnot_ps(_hlslpp_isfinite_ps(q.vec), f4_1)); }
	hlslpp_inline float4		isinf(const quaternion& q) { return float4(_hlslpp_and_ps(_hlslpp_isinf_ps(q.vec), f4_1)); }
	hlslpp_inline float4		isnan(const quaternion& q) { return float4(_hlslpp_and_ps(_hlslpp_isnan_ps(q.vec), f4_1)); }
	hlslpp_inline float1		length(const quaternion& q) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(q.vec, q.vec))); }
	hlslpp_inline quaternion	lerp(const quaternion& q1, const quaternion& q2, const float1& a) { return quaternion(_hlslpp_lerp_ps(q1.vec, q2.vec, _hlslpp_perm_xxxx_ps(a.vec))); }

	hlslpp_inline quaternion	slerp(const quaternion& q1, const quaternion& q2, const float1& a) { return quaternion(_hlslpp_quat_slerp_ps(q1.vec, q2.vec, _hlslpp_perm_xxxx_ps(a.vec))); }

	//hlslpp_inline quaternion log(const quaternion& q) { return quaternion(_hlslpp_log_ps(q._vec)); }
	hlslpp_inline quaternion	min(const quaternion& q1, const quaternion& q2) { return quaternion(_hlslpp_min_ps(q1.vec, q2.vec)); }
	hlslpp_inline quaternion	max(const quaternion& q1, const quaternion& q2) { return quaternion(_hlslpp_max_ps(q1.vec, q2.vec)); }
	hlslpp_inline float3		mul(const quaternion& q, const float3& v) { return float3(_hlslpp_quat_mul_vec_ps(q.vec, v.vec)); }
	hlslpp_inline quaternion	normalize(const quaternion& q) { return quaternion(_hlslpp_div_ps(q.vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(q.vec, q.vec))))); }
	hlslpp_inline quaternion	saturate(const quaternion& q) { return quaternion(_hlslpp_sat_ps(q.vec)); }
	hlslpp_inline quaternion	sign(const quaternion& q) { return quaternion(_hlslpp_sign_ps(q.vec)); }
}