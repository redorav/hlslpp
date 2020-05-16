//--------------//
// Float Vector //
//--------------//

namespace hlslpp
{
	// Cross product for 3-component vectors
	// http://threadlocalmutex.com/?p=8
	// Measured to be marginally faster than the 4-shuffle
	hlslpp_inline n128 _hlslpp_cross_ps(n128 x, n128 y)
	{
		n128 yzx_0 = _hlslpp_perm_yzxx_ps(x);
		n128 yzx_1 = _hlslpp_perm_yzxx_ps(y);
		return _hlslpp_perm_yzxx_ps(_hlslpp_msub_ps(x, yzx_1, _hlslpp_mul_ps(yzx_0, y)));
	}
	
	hlslpp_inline n128 _hlslpp_dot2_ps(n128 x, n128 y)
	{
		n128 multi = _hlslpp_mul_ps(x, y);         // Multiply components together
		n128 shuf1 = _hlslpp_perm_yyyy_ps(multi);  // Move y into x
		n128 result = _hlslpp_add_ss(shuf1, multi); // Contains x+y, _, _, _
		return result;
	}

#if !defined(HLSLPP_DOT3_IMPLEMENTATION)

	hlslpp_inline n128 _hlslpp_dot3_ps(n128 x, n128 y)
	{
		// SSE4 slower
		// n128 result = _hlslpp_dp_ps(v1.xyzw, v2.xyzw, 0x7f);

		// SSE2
		n128 multi  = _hlslpp_mul_ps(x, y);         // Multiply components together
		n128 shuf1  = _hlslpp_perm_yyyy_ps(multi);  // Move y into x
		n128 add1   = _hlslpp_add_ps(shuf1, multi); // Contains x+y, _, _, _
		n128 shuf2  = _hlslpp_perm_zzzz_ps(multi);  // Move z into x
		n128 result = _hlslpp_add_ss(add1, shuf2);  // Contains x+y+z, _, _, _
		return result;
	}

#endif

	// See http://http.developer.nvidia.com/Cg/fmod.html for reference
	// This implementation does not follow the reference
	// float2 c = frac(abs(a/b))*abs(b);
	// return (a < 0) ? -c : c;    // if ( a < 0 ) c = 0-c
	hlslpp_inline n128 _hlslpp_fmod_ps(n128 x, n128 y)
	{
		n128 div = _hlslpp_div_ps(x, y);
		n128 trnc = _hlslpp_sub_ps(div, _hlslpp_trunc_ps(div));
		return _hlslpp_mul_ps(trnc, y);
	}

	hlslpp_inline void _hlslpp_modf_ps(n128 x, n128& intPart, n128& fracPart)
	{
		intPart = _hlslpp_trunc_ps(x);
		fracPart = _hlslpp_sub_ps(x, intPart);
	}

	// Returns true if x is not +infinity or -infinity
	hlslpp_inline n128 _hlslpp_isfinite_ps(n128 x)
	{
		return _hlslpp_and_ps(_hlslpp_and_ps(_hlslpp_cmpneq_ps(x, f4_inf), _hlslpp_cmpneq_ps(x, f4_minusinf)), _hlslpp_cmpeq_ps(x, x));
	}

	// Returns true if x is +infinity or -infinity
	hlslpp_inline n128 _hlslpp_isinf_ps(n128 x)
	{
		return _hlslpp_or_ps(_hlslpp_cmpeq_ps(x, f4_inf), _hlslpp_cmpeq_ps(x, f4_minusinf));
	}

	// Returns true if x is nan
	hlslpp_inline n128 _hlslpp_isnan_ps(n128 x)
	{
		return _hlslpp_cmpneq_ps(x, x);
	}

	// Follows fxc in order of operations (a * (y - x) + x)
	hlslpp_inline n128 _hlslpp_lerp_ps(n128 x, n128 y, n128 a)
	{
		n128 y_minus_x = _hlslpp_sub_ps(y, x);
		n128 result = _hlslpp_madd_ps(a, y_minus_x, x);
		return result;
	}

	// See http://jrfonseca.blogspot.co.uk/2008/09/fast-sse2-pow-tables-or-polynomials.html for derivation
	// Fonseca derives from here: http://forum.devmaster.net/t/approximate-math-library/11679
	inline n128 _hlslpp_log2_ps(n128 x)
	{
		static const n128 log2_c0 = _hlslpp_set1_ps(3.1157899f);
		static const n128 log2_c1 = _hlslpp_set1_ps(-3.3241990f);
		static const n128 log2_c2 = _hlslpp_set1_ps(2.5988452f);
		static const n128 log2_c3 = _hlslpp_set1_ps(-1.2315303f);
		static const n128 log2_c4 = _hlslpp_set1_ps(3.1821337e-1f);
		static const n128 log2_c5 = _hlslpp_set1_ps(-3.4436006e-2f);

		static const n128i exp = _hlslpp_set1_epi32(0x7F800000);
		static const n128i mant = _hlslpp_set1_epi32(0x007FFFFF);

		static const n128 minus127 = _hlslpp_set1_ps(-127.0f);

		n128i i = _hlslpp_castps_si128(x);

		n128 e = _hlslpp_cvtepi32_ps(_hlslpp_sub_epi32(_hlslpp_srli_epi32(_hlslpp_and_si128(i, exp), 23), _hlslpp_set1_epi32(127)));

		n128 m = _hlslpp_or_ps(_hlslpp_castsi128_ps(_hlslpp_and_si128(i, mant)), f4_1);

		n128 p;
		// Minimax polynomial fit of log2(x)/(x - 1), for x in range [1, 2[
		p = _hlslpp_madd_ps(m, log2_c5, log2_c4);
		p = _hlslpp_madd_ps(m, p, log2_c3);
		p = _hlslpp_madd_ps(m, p, log2_c2);
		p = _hlslpp_madd_ps(m, p, log2_c1);
		p = _hlslpp_madd_ps(m, p, log2_c0);

		// This effectively increases the polynomial degree by one, but ensures that log2(1) == 0
		p = _hlslpp_mul_ps(p, _hlslpp_sub_ps(m, f4_1));

		n128 result = _hlslpp_add_ps(p, e);

		// We can't compute a logarithm beyond this value, so we'll mark it as -infinity to indicate close to 0
		n128 ltminus127 = _hlslpp_cmple_ps(result, minus127);
		result = _hlslpp_sel_ps(result, f4_minusinf, ltminus127);

		// Check for negative values and return NaN
		n128 lt0 = _hlslpp_cmplt_ps(x, f4_0);
		result = _hlslpp_sel_ps(result, f4_NaN, lt0);

		return result;
	}

	hlslpp_inline n128 _hlslpp_log10_ps(n128 x)
	{
		static const n128 invlog_2_10 = _hlslpp_div_ps(f4_1, _hlslpp_log2_ps(f4_10));
		return _hlslpp_mul_ps(_hlslpp_log2_ps(x), invlog_2_10);
	}

	hlslpp_inline n128 _hlslpp_log_ps(n128 x)
	{
		static const n128 invlog_2_e = _hlslpp_div_ps(f4_1, _hlslpp_log2_ps(f4_e));
		return _hlslpp_mul_ps(_hlslpp_log2_ps(x), invlog_2_e);
	}

	// See http://jrfonseca.blogspot.co.uk/2008/09/fast-sse2-pow-tables-or-polynomials.html for derivation
	inline n128 _hlslpp_exp2_ps(n128 x)
	{
		static const n128 exp2_c0 = _hlslpp_set1_ps(1.0f);
		static const n128 exp2_c1 = _hlslpp_set1_ps(6.9315308e-1f);
		static const n128 exp2_c2 = _hlslpp_set1_ps(2.4015361e-1f);
		static const n128 exp2_c3 = _hlslpp_set1_ps(5.5826318e-2f);
		static const n128 exp2_c4 = _hlslpp_set1_ps(8.9893397e-3f);
		static const n128 exp2_c5 = _hlslpp_set1_ps(1.8775767e-3f);

		static const n128 exp2_129 = _hlslpp_set1_ps(129.00000f);
		static const n128 exp2_minus127 = _hlslpp_set1_ps(-126.99999f);
		static const n128i exp2_127i = _hlslpp_set1_epi32(127);

		n128i ipart;
		n128 fpart, expipart, expfpart;

		// Clamp values
		x = _hlslpp_min_ps(x, exp2_129);
		x = _hlslpp_max_ps(x, exp2_minus127);

		// ipart = int(x - 0.5)
		ipart = _hlslpp_cvtps_epi32(_hlslpp_sub_ps(x, f4_05));

		// fpart = x - ipart
		fpart = _hlslpp_sub_ps(x, _hlslpp_cvtepi32_ps(ipart));

		// expipart = (float) (1 << ipart)
		expipart = _hlslpp_castsi128_ps(_hlslpp_slli_epi32(_hlslpp_add_epi32(ipart, exp2_127i), 23));

		// Minimax polynomial fit of 2^x, in range [-0.5, 0.5[
		expfpart = _hlslpp_madd_ps(fpart, exp2_c5, exp2_c4);
		expfpart = _hlslpp_madd_ps(fpart, expfpart, exp2_c3);
		expfpart = _hlslpp_madd_ps(fpart, expfpart, exp2_c2);
		expfpart = _hlslpp_madd_ps(fpart, expfpart, exp2_c1);
		expfpart = _hlslpp_madd_ps(fpart, expfpart, exp2_c0);

		return _hlslpp_mul_ps(expipart, expfpart);
	}

	hlslpp_inline n128 _hlslpp_exp_ps(n128 x)
	{
		static const n128 log_2_e = _hlslpp_log2_ps(f4_e);
		return _hlslpp_exp2_ps(_hlslpp_mul_ps(x, log_2_e));
	}

	// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/smoothstep.xhtml
	// x = (x - edge0) / (edge1 - edge0);
	// 0,           x <= 0
	// 3x^2 - 2x^3, 0 < x < 1
	// 1,           x >= 1
	hlslpp_inline n128 _hlslpp_smoothstep_ps(n128 edge0, n128 edge1, n128 x)
	{
		x = _hlslpp_sat_ps(_hlslpp_div_ps(_hlslpp_sub_ps(x, edge0), _hlslpp_sub_ps(edge1, edge0))); // x = saturate((x - edge0) / (edge1 - edge0))
		n128 result = _hlslpp_mul_ps(_hlslpp_mul_ps(x, x), _hlslpp_sub_ps(f4_3, _hlslpp_add_ps(x, x))); // result = x^2(3 - 2x)
		return result;
	}

	// Hlsl, glsl and Cg behavior is to swap the operands.
	// http://http.developer.nvidia.com/Cg/step.html
	// https://www.opengl.org/sdk/docs/man/html/step.xhtml
	hlslpp_inline n128 _hlslpp_step_ps(n128 x, n128 y)
	{
		return _hlslpp_cmpge1_ps(x, y);
	}

#if !defined(HLSLPP_SIN_IMPLEMENTATION)

	// Uses a minimax polynomial fitted to the [-pi/2, pi/2] range
	inline n128 _hlslpp_sin_ps(n128 x)
	{
		static const n128 sin_c1 = f4_1;
		static const n128 sin_c3 = _hlslpp_set1_ps(-1.6665578e-1f);
		static const n128 sin_c5 = _hlslpp_set1_ps(8.3109378e-3f);
		static const n128 sin_c7 = _hlslpp_set1_ps(-1.84477486e-4f);

		// Range reduction (into [-pi, pi] range)
		// Formula is x = x - round(x / 2pi) * 2pi

		x = _hlslpp_subm_ps(x, _hlslpp_round_ps(_hlslpp_mul_ps(x, f4_inv2pi)), f4_2pi);

		n128 gtpi2 = _hlslpp_cmpgt_ps(x, f4_pi2);
		n128 ltminusPi2 = _hlslpp_cmplt_ps(x, f4_minusPi2);

		n128 ox = x;

		// Use identities/mirroring to remap into the range of the minimax polynomial
		x = _hlslpp_sel_ps(x, _hlslpp_sub_ps(f4_pi, ox), gtpi2);
		x = _hlslpp_sel_ps(x, _hlslpp_sub_ps(f4_minusPi, ox), ltminusPi2);

		n128 x2 = _hlslpp_mul_ps(x, x);
		n128 result;
		result = _hlslpp_madd_ps(x2, sin_c7, sin_c5);
		result = _hlslpp_madd_ps(x2, result, sin_c3);
		result = _hlslpp_madd_ps(x2, result, sin_c1);
		result = _hlslpp_mul_ps(result, x);
		return result;
	}

#endif

#if !defined(HLSLPP_COS_IMPLEMENTATION)

	hlslpp_inline n128 _hlslpp_cos_ps(n128 x)
	{
		return _hlslpp_sin_ps(_hlslpp_sub_ps(f4_pi2, x));
	}

#endif

#if !defined(HLSLPP_TAN_IMPLEMENTATION)

	// Uses a minimax polynomial fitted to the [-pi/4, pi/4] range
	inline n128 _hlslpp_tan_ps(n128 x)
	{
		static const n128 tan_c1 = f4_1;
		static const n128 tan_c3 = _hlslpp_set1_ps(3.329923284e-1f);
		static const n128 tan_c5 = _hlslpp_set1_ps(1.374784343e-1f);
		static const n128 tan_c7 = _hlslpp_set1_ps(3.769634481e-2f);
		static const n128 tan_c9 = _hlslpp_set1_ps(4.609737727e-2f);

		// Range reduction (into [-pi/2, pi/2] range)
		// Formula is x = x - round(x / pi) * pi

		x = _hlslpp_subm_ps(x, _hlslpp_round_ps(_hlslpp_mul_ps(x, f4_invPi)), f4_pi);

		n128 gtPi4 = _hlslpp_cmpgt_ps(x, f4_pi4);
		n128 ltMinusPi4 = _hlslpp_cmplt_ps(x, f4_minusPi4);
		n128 gtltPi4 = _hlslpp_or_ps(gtPi4, ltMinusPi4);

		x = _hlslpp_sel_ps(x, _hlslpp_sub_ps(f4_pi2, x), gtPi4);
		x = _hlslpp_sel_ps(x, _hlslpp_sub_ps(f4_minusPi2, x), ltMinusPi4);

		n128 x2 = _hlslpp_mul_ps(x, x);
		n128 centerResult;
		centerResult = _hlslpp_madd_ps(x2, tan_c9, tan_c7);
		centerResult = _hlslpp_madd_ps(x2, centerResult, tan_c5);
		centerResult = _hlslpp_madd_ps(x2, centerResult, tan_c3);
		centerResult = _hlslpp_madd_ps(x2, centerResult, tan_c1);
		centerResult = _hlslpp_mul_ps(centerResult, x);				// Valid within [-pi/4, pi/4]

		n128 lateralResult = _hlslpp_div_ps(f4_1, centerResult); // Valid in [-pi/2, -pi/4) U (pi/4, pi/2]

		n128 result = _hlslpp_sel_ps(centerResult, lateralResult, gtltPi4);

		return result;
	}

#endif

#if !defined(HLSLPP_ACOS_IMPLEMENTATION)

	// Max error vs. std::acos
	// SSE : 1.54972076e-6
	inline n128 _hlslpp_acos_ps(n128 x)
	{
		static const n128 asinacos_c0 = f4_pi2;
		static const n128 asinacos_c1 = _hlslpp_set1_ps(-2.145329213e-1f);
		static const n128 asinacos_c2 = _hlslpp_set1_ps(8.797308928e-2f);
		static const n128 asinacos_c3 = _hlslpp_set1_ps(-4.513026638e-2f);
		static const n128 asinacos_c4 = _hlslpp_set1_ps(1.946746668e-2f);
		static const n128 asinacos_c5 = _hlslpp_set1_ps(-4.360132611e-3f);

		// We use the trigonometric identity acos(x) = pi - acos(-x) to mirror [0, 1]
		// into the [-1, 0] range
		n128 ltZero = _hlslpp_cmplt_ps(x, f4_0);
		x = _hlslpp_sel_ps(x, _hlslpp_neg_ps(x), ltZero);

		n128 sqrt1minusx = _hlslpp_sqrt_ps(_hlslpp_sub_ps(f4_1, x));

		n128 result;
		result = _hlslpp_madd_ps(x, asinacos_c5, asinacos_c4);
		result = _hlslpp_madd_ps(x, result, asinacos_c3);
		result = _hlslpp_madd_ps(x, result, asinacos_c2);
		result = _hlslpp_madd_ps(x, result, asinacos_c1);
		result = _hlslpp_madd_ps(x, result, asinacos_c0);
		result = _hlslpp_mul_ps(result, sqrt1minusx);

		result = _hlslpp_sel_ps(result, _hlslpp_sub_ps(f4_pi, result), ltZero); // Select the [0, 1] or [-1, 0] result

		n128 gtltOne = _hlslpp_cmpgt_ps(_hlslpp_abs_ps(x), f4_1);	// > 1 || < -1
		result = _hlslpp_sel_ps(result, f4_NaN, gtltOne);			// Select NaN if input out of range

		return result;
	}

#endif

#if !defined(HLSLPP_ASIN_IMPLEMENTATION)

	// Max error vs. std::asin
	// SSE : 1.5348196e-6
	inline n128 _hlslpp_asin_ps(n128 x)
	{
		static const n128 asinacos_c0 = f4_pi2;
		static const n128 asinacos_c1 = _hlslpp_set1_ps(-2.145329213e-1f);
		static const n128 asinacos_c2 = _hlslpp_set1_ps(8.797308928e-2f);
		static const n128 asinacos_c3 = _hlslpp_set1_ps(-4.513026638e-2f);
		static const n128 asinacos_c4 = _hlslpp_set1_ps(1.946746668e-2f);
		static const n128 asinacos_c5 = _hlslpp_set1_ps(-4.360132611e-3f);

		// We use the trigonometric identity asin(x) = -asin(-x) to mirror [0, 1] into the [-1, 0] range
		n128 ltZero = _hlslpp_cmplt_ps(x, f4_0);
		x = _hlslpp_sel_ps(x, _hlslpp_neg_ps(x), ltZero);

		n128 sqrt1minusx = _hlslpp_sqrt_ps(_hlslpp_sub_ps(f4_1, x));

		n128 result;
		result = _hlslpp_madd_ps(x, asinacos_c5, asinacos_c4);
		result = _hlslpp_madd_ps(x, result, asinacos_c3);
		result = _hlslpp_madd_ps(x, result, asinacos_c2);
		result = _hlslpp_madd_ps(x, result, asinacos_c1);
		result = _hlslpp_madd_ps(x, result, asinacos_c0);
		result = _hlslpp_subm_ps(f4_pi2, result, sqrt1minusx); // pi/2 - result * sqrt(1 - x)

		result = _hlslpp_sel_ps(result, _hlslpp_neg_ps(result), ltZero);	// Select the [0, 1] or [-1, 0] result

		n128 gtltOne = _hlslpp_cmpgt_ps(_hlslpp_abs_ps(x), f4_1);		// > 1 || < -1
		result = _hlslpp_sel_ps(result, f4_NaN, gtltOne);				// Select NaN if input out of range

		return result;
	}

#endif

#if !defined(HLSLPP_ATAN_IMPLEMENTATION)

	// Max error vs. std::atan
	// SSE : 2.74181366e-6
	inline n128 _hlslpp_atan_ps(n128 x)
	{
		static const n128 atan_c1 = f4_1;
		static const n128 atan_c3 = _hlslpp_set1_ps(-3.329452768e-1f);
		static const n128 atan_c5 = _hlslpp_set1_ps(1.949865716e-1f);
		static const n128 atan_c7 = _hlslpp_set1_ps(-1.192157627e-1f);
		static const n128 atan_c9 = _hlslpp_set1_ps(5.506335136e-2f);
		static const n128 atan_c11 = _hlslpp_set1_ps(-1.249072006e-2f);

		n128 ltgtOne = _hlslpp_cmpgt_ps(_hlslpp_abs_ps(x), f4_1); // Check if outside the [-1, 1] range
		n128 gtOne = _hlslpp_cmpgt_ps(x, f4_1);				 // Check if input > 1 (as we need to select the constant later)

		x = _hlslpp_sel_ps(x, _hlslpp_div_ps(f4_1, x), ltgtOne);

		n128 x2 = _hlslpp_mul_ps(x, x);
		n128 result;
		result = _hlslpp_madd_ps(x2, atan_c11, atan_c9);
		result = _hlslpp_madd_ps(x2, result, atan_c7);
		result = _hlslpp_madd_ps(x2, result, atan_c5);
		result = _hlslpp_madd_ps(x2, result, atan_c3);
		result = _hlslpp_madd_ps(x2, result, atan_c1);
		result = _hlslpp_mul_ps(x, result);

		// if(abs(x) < 1)	return result
		// if(x >  1)		return pi/2 - result
		// if(x < -1)		return -pi/2 - result

		n128 outRangeK = _hlslpp_sel_ps(f4_minusPi2, f4_pi2, gtOne);
		n128 outRangeResult = _hlslpp_sub_ps(outRangeK, result);

		result = _hlslpp_sel_ps(result, outRangeResult, ltgtOne);
		return result;
	}

#endif

#if !defined(HLSLPP_SINH_IMPLEMENTATION)

	// sinh(x) = (exp(x) - exp(-x)) / 2.0
	hlslpp_inline n128 _hlslpp_sinh_ps(n128 x)
	{
		n128 expx = _hlslpp_exp_ps(x);
		n128 exp_minusx = _hlslpp_rcp_ps(expx);
		return _hlslpp_mul_ps(_hlslpp_sub_ps(expx, exp_minusx), f4_05);
	}

#endif

#if !defined(HLSLPP_COSH_IMPLEMENTATION)

	// cosh(x) = (exp(x) + exp(-x)) / 2.0
	hlslpp_inline n128 _hlslpp_cosh_ps(n128 x)
	{
		n128 expx = _hlslpp_exp_ps(x);
		n128 exp_minusx = _hlslpp_rcp_ps(expx);
		return _hlslpp_mul_ps(_hlslpp_add_ps(expx, exp_minusx), f4_05);
	}

#endif

#if !defined(HLSLPP_TANH_IMPLEMENTATION)

	// tanh(x) = (exp(x) - exp(-x)) / (exp(x) + exp(-x))
	hlslpp_inline n128 _hlslpp_tanh_ps(n128 x)
	{
		n128 expx = _hlslpp_exp_ps(x);
		n128 exp_minusx = _hlslpp_rcp_ps(expx);
		return _hlslpp_div_ps(_hlslpp_sub_ps(expx, exp_minusx), _hlslpp_add_ps(expx, exp_minusx));
	}

#endif

	// https://docs.microsoft.com/en-us/windows/desktop/direct3dhlsl/dx-graphics-hlsl-reflect
	// v = i - 2 * n * dot(i, n)

	hlslpp_inline n128 _hlslpp_reflect1_ps(n128 i, n128 n)
	{
		return _hlslpp_sub_ps(i, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n, _hlslpp_mul_ps(i, n))));
	}

	hlslpp_inline n128 _hlslpp_reflect2_ps(n128 i, n128 n)
	{
		return _hlslpp_sub_ps(i, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n, _hlslpp_perm_xxxx_ps(_hlslpp_dot2_ps(i, n)))));
	}

	hlslpp_inline n128 _hlslpp_reflect3_ps(n128 i, n128 n)
	{
		return _hlslpp_sub_ps(i, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n, _hlslpp_perm_xxxx_ps(_hlslpp_dot3_ps(i, n)))));
	}

	hlslpp_inline n128 _hlslpp_reflect4_ps(n128 i, n128 n)
	{
		return _hlslpp_sub_ps(i, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n, _hlslpp_perm_xxxx_ps(_hlslpp_dot4_ps(i, n)))));
	}

	// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/refract.xhtml
	//
	// k = 1.0 - ior * ior * (1.0 - dot(n, i) * dot(n, i));
	// if (k < 0.0)
	//     return 0.0;
	// else
	//     return ior * i - (ior * dot(n, i) + sqrt(k)) * n;

	hlslpp_inline n128 _hlslpp_refract_ps(const n128& i, const n128& n, const n128& ior, const n128& NdotI)
	{
		n128 NdotI4 = _hlslpp_perm_xxxx_ps(NdotI); // Propagate to all components (dot lives in x)

		n128 ior2 = _hlslpp_mul_ps(ior, ior);                // ior^2
		n128 invNdotI2 = _hlslpp_subm_ps(f4_1, NdotI4, NdotI4);   // 1.0 - dot(n, i)^2
		n128 k = _hlslpp_subm_ps(f4_1, ior2, invNdotI2);  // k = 1.0 - ior^2 * (1.0 - dot(n, i)^2)

		n128 sqrtK = _hlslpp_sqrt_ps(k);                      // sqrt(k)
		n128 iorNdotISqrtk = _hlslpp_madd_ps(ior, NdotI4, sqrtK);     // ior * dot(n, i) + sqrt(k)
		n128 iorNdotISqrtkn = _hlslpp_mul_ps(iorNdotISqrtk, n);        // (ior * dot(n, i) + sqrt(k)) * n
		n128 result = _hlslpp_msub_ps(ior, i, iorNdotISqrtkn); // ior * i - (ior * dot(n, i) + sqrt(k)) * n

		n128 klt0 = _hlslpp_cmplt_ps(k, _hlslpp_setzero_ps()); // Whether k was less than 0

		return _hlslpp_sel_ps(result, _hlslpp_setzero_ps(), klt0); // Select between 0 and the result 
	}

	hlslpp_inline n128 _hlslpp_refract1_ps(n128 i, n128 n, n128 ior)
	{
		return _hlslpp_refract_ps(i, n, ior, _hlslpp_mul_ps(i, n));
	}

	hlslpp_inline n128 _hlslpp_refract2_ps(n128 i, n128 n, n128 ior)
	{
		return _hlslpp_refract_ps(i, n, _hlslpp_perm_xxxx_ps(ior), _hlslpp_dot2_ps(i, n));
	}

	hlslpp_inline n128 _hlslpp_refract3_ps(n128 i, n128 n, n128 ior)
	{
		return _hlslpp_refract_ps(i, n, _hlslpp_perm_xxxx_ps(ior), _hlslpp_dot3_ps(i, n));
	}

	hlslpp_inline n128 _hlslpp_refract4_ps(n128 i, n128 n, n128 ior)
	{
		return _hlslpp_refract_ps(i, n, _hlslpp_perm_xxxx_ps(ior), _hlslpp_dot4_ps(i, n));
	}

	template<int X>
	struct hlslpp_nodiscard	swizzle1
	{
		template<int A> friend struct swizzle1;

		// Cast

		hlslpp_inline operator float() const { return f32[X]; }

		// Helper

		template<int E, int A>
		static hlslpp_inline n128 swizzle(n128 v)
		{
			const int finalMask = (((IdentityMask >> 2 * E) & 3) << 2 * A) | (IdentityMask & ~((3 << 2 * A)));
			return _hlslpp_perm_ps(v, finalMask);
		}

		template<int E, int A>
		hlslpp_inline n128 swizzle() const
		{
			return swizzle<E, A>(vec);
		}

		// Assignment

		hlslpp_inline swizzle1& operator = (float f)
		{
			vec = _hlslpp_blend_ps(vec, _hlslpp_set1_ps(f), HLSLPP_COMPONENT_X(X));
			return *this;
		}

		template<int A>
		hlslpp_inline swizzle1& operator = (const swizzle1<A>& s) // Revise this function. Can I not do with swizzle?
		{
			n128 t = _hlslpp_shuffle_ps(s.vec, s.vec, HLSLPP_SHUFFLE_MASK(A, A, A, A));
			vec = _hlslpp_blend_ps(vec, t, HLSLPP_COMPONENT_X(X));
			return *this;
		}

		hlslpp_inline swizzle1& operator = (const float1& f);

	private:
		union
		{
			n128 vec;
			float f32[4];
		};
	};

	template<int X, int Y>
	struct hlslpp_nodiscard	swizzle2
	{
		// Helper

		void staticAsserts()
		{
			static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		template<int E, int F, int A, int B>
		static hlslpp_inline n128 swizzle(n128 v)
		{
			const int finalMask =
				(((IdentityMask >> 2 * E) & 3) << 2 * A) |
				(((IdentityMask >> 2 * F) & 3) << 2 * B) |
				(IdentityMask & ~((3 << 2 * A) | (3 << 2 * B)));
			return _hlslpp_perm_ps(v, finalMask);
		}

		template<int E, int F, int A, int B>
		hlslpp_inline n128 swizzle() const
		{
			return swizzle<E, F, A, B>(vec);
		}

		// Assignment

		template<int A, int B>
		hlslpp_inline swizzle2& operator = (const swizzle2<A, B>& s)
		{
			staticAsserts();
			vec = blend(vec, s.template swizzle<A, B, X, Y>());
			return *this;
		}

		hlslpp_inline swizzle2& operator = (const float2& f);

	private:

		static hlslpp_inline n128 blend(n128 x, n128 y)
		{
			return _hlslpp_blend_ps(x, y, HLSLPP_COMPONENT_XY(X, Y)); // Select based on property mask
		}

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	template<int X, int Y, int Z>
	struct hlslpp_nodiscard	swizzle3
	{
		void staticAsserts()
		{
			static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		template<int E, int F, int G, int A, int B, int C>
		static hlslpp_inline n128 swizzle(n128 v)
		{
			const int finalMask =
				(((IdentityMask >> 2 * E) & 3) << 2 * A) |
				(((IdentityMask >> 2 * F) & 3) << 2 * B) |
				(((IdentityMask >> 2 * G) & 3) << 2 * C) |
				(IdentityMask & ~((3 << 2 * A) | (3 << 2 * B) | (3 << 2 * C)));
			return _hlslpp_perm_ps(v, finalMask);
		}

		template<int E, int F, int G, int A, int B, int C>
		hlslpp_inline n128 swizzle() const
		{
			return swizzle<E, F, G, A, B, C>(vec);
		}

		// Assignment

		template<int A, int B, int C>
		hlslpp_inline swizzle3& operator = (const swizzle3<A, B, C>& s)
		{
			staticAsserts();
			vec = blend(vec, s.template swizzle<A, B, C, X, Y, Z>());
			return *this;
		}

		hlslpp_inline swizzle3& operator = (const float3& f);

	private:

		static hlslpp_inline n128 blend(n128 x, n128 y)
		{
			return _hlslpp_blend_ps(x, y, HLSLPP_COMPONENT_XYZ(X, Y, Z)); // Select based on property mask
		}

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	template<int X, int Y, int Z, int W>
	struct hlslpp_nodiscard swizzle4
	{
		void staticAsserts()
		{
			static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		template<int E, int F, int G, int H, int A, int B, int C, int D>
		static hlslpp_inline n128 swizzle(n128 v)
		{
			const int finalMask =
				(((IdentityMask >> 2 * E) & 3) << (2 * A)) |
				(((IdentityMask >> 2 * F) & 3) << (2 * B)) |
				(((IdentityMask >> 2 * G) & 3) << (2 * C)) |
				(((IdentityMask >> 2 * H) & 3) << (2 * D));

			return _hlslpp_perm_ps(v, finalMask);
		}

		template<int E, int F, int G, int H, int A, int B, int C, int D>
		hlslpp_inline n128 swizzle() const
		{
			return swizzle<E, F, G, H, A, B, C, D>(vec);
		}

		// Assignment

		template<int A, int B, int C, int D>
		hlslpp_inline swizzle4& operator = (const swizzle4<A, B, C, D>& s)
		{
			staticAsserts();
			vec = s.template swizzle<A, B, C, D, X, Y, Z, W>();
			return *this;
		}

		hlslpp_inline swizzle4& operator = (const float4& f);

	private:
		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct hlslpp_nodiscard float1
	{
		hlslpp_inline float1() {}
		hlslpp_inline float1(const float1& f) : vec(f.vec) {}
		explicit hlslpp_inline float1(n128 vec) : vec(vec) {}

		template<typename T>
		hlslpp_inline float1(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set_ps(float(f), 0.0f, 0.0f, 0.0f)) {}

		template<int X> hlslpp_inline float1(const swizzle1<X>& s) : vec(s.template swizzle<X, 0>()) {}

		hlslpp_inline float1(const int1& i);

		hlslpp_inline float1(const uint1& i);

		hlslpp_inline operator float() const { return f32[0]; }

		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/hlsl++_vector_float_x.h"
		};
	};

	struct hlslpp_nodiscard	float2
	{
		// Constructors

		hlslpp_inline float2() {}
		hlslpp_inline float2(const float2& f) : vec(f.vec) {}
		explicit hlslpp_inline float2(n128 vec) : vec(vec) {}
		explicit hlslpp_inline float2(const float1& f) : vec(_hlslpp_perm_xxxx_ps(f.vec)) {}

		template<typename T>
		hlslpp_inline float2(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set_ps(float(f), float(f), 0.0f, 0.0f)) {}

		template<typename T1, typename T2>
		hlslpp_inline float2(T1 f1, T2 f2, hlslpp_enable_if_number_2(T1, T2)) : vec(_hlslpp_set_ps(float(f1), float(f2), 0.0f, 0.0f)) {}

		hlslpp_inline float2(const float1& f1, const float1& f2) { vec = _hlslpp_blend_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }

		template<int X, int Y> hlslpp_inline float2(const swizzle2<X, Y>& s) : vec(s.template swizzle<X, Y, 0, 1>()) {}

		hlslpp_inline float2(const int2& i);

		hlslpp_inline float2(const uint2& i);

		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/hlsl++_vector_float_x.h"
			#include "swizzle/hlsl++_vector_float_y.h"
		};
	};

	struct hlslpp_nodiscard	float3
	{
		// Constructors

		hlslpp_inline float3() {}
		hlslpp_inline float3(const float3& f) : vec(f.vec) {}
		explicit hlslpp_inline float3(n128 vec) : vec(vec) {}
		explicit hlslpp_inline float3(const float1& f) : vec(_hlslpp_perm_xxxx_ps(f.vec)) {}

		template<typename T>
		hlslpp_inline float3(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set_ps(float(f), float(f), float(f), 0.0f)) {}

		template<typename T1, typename T2, typename T3>
		hlslpp_inline float3(T1 f1, T2 f2, T3 f3, hlslpp_enable_if_number_3(T1, T2, T3)) : vec(_hlslpp_set_ps(float(f1), float(f2), float(f3), 0.0f)) {}

		hlslpp_inline float3(const float1& f1, const float1& f2, const float1& f3) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(f1.vec, f3.vec), _hlslpp_perm_xxxx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }

		hlslpp_inline float3(const float2& f1, const float1& f2) { vec = _hlslpp_shuf_xyxx_ps(f1.vec, f2.vec); }
		hlslpp_inline float3(const float1& f1, const float2& f2) { vec = _hlslpp_blend_ps(f1.vec, _hlslpp_perm_xxyx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }

		template<int X, int Y, int Z>
		hlslpp_inline float3(const swizzle3<X, Y, Z>& s) : vec(s.template swizzle<X, Y, Z, 0, 1, 2>()) {}

		hlslpp_inline float3(const int3& i);

		hlslpp_inline float3(const uint3& i);

		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/hlsl++_vector_float_x.h"
			#include "swizzle/hlsl++_vector_float_y.h"
			#include "swizzle/hlsl++_vector_float_z.h"
		};
	};

	struct hlslpp_nodiscard	float4
	{
		hlslpp_inline float4() {}
		hlslpp_inline float4(const float4& f) : vec(f.vec) {}
		explicit hlslpp_inline float4(n128 vec) : vec(vec) {}
		explicit hlslpp_inline float4(const float1& f) : vec(_hlslpp_perm_xxxx_ps(f.vec)) {}

		template<typename T>
		float4(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set1_ps(float(f))) {}

		template<typename T1, typename T2, typename T3, typename T4>
		hlslpp_inline float4(T1 f1, T2 f2, T3 f3, T4 f4, hlslpp_enable_if_number_4(T1, T2, T3, T4)) : vec(_hlslpp_set_ps(float(f1), float(f2), float(f3), float(f4))) {}

		hlslpp_inline float4(const float1& f1, const float1& f2, const float1& f3, const float1& f4) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(f1.vec, f3.vec), _hlslpp_shuf_xxxx_ps(f2.vec, f4.vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }

		hlslpp_inline float4(const float2& f1, const float1& f2, const float1& f3) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xyxx_ps(f1.vec, f2.vec), _hlslpp_perm_xxxx_ps(f3.vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }
		hlslpp_inline float4(const float1& f1, const float2& f2, const float1& f3) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(f1.vec, f3.vec), _hlslpp_perm_xxyx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }
		hlslpp_inline float4(const float1& f1, const float1& f2, const float2& f3) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxy_ps(f1.vec, f3.vec), _hlslpp_perm_xxxx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }

		hlslpp_inline float4(const float2& f1, const float2& f2) { vec = _hlslpp_shuf_xyxy_ps(f1.vec, f2.vec); }

		hlslpp_inline float4(const float1& f1, const float3& f2) { vec = _hlslpp_blend_ps(f1.vec, _hlslpp_perm_xxyz_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 0)); }
		hlslpp_inline float4(const float3& f1, const float1& f2) { vec = _hlslpp_blend_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }

		template<int X, int Y, int Z, int W>
		hlslpp_inline float4(const swizzle4<X, Y, Z, W>& s) : vec(s.template swizzle<X, Y, Z, W, 0, 1, 2, 3>()) {}

		hlslpp_inline float4(const int4& i);

		hlslpp_inline float4(const uint4& i);

		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/hlsl++_vector_float_x.h"
			#include "swizzle/hlsl++_vector_float_y.h"
			#include "swizzle/hlsl++_vector_float_z.h"
			#include "swizzle/hlsl++_vector_float_w.h"
		};
	};

	// Operators

	hlslpp_inline float1 operator + (const float1& f1, const float1& f2) { return float1(_hlslpp_add_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 operator + (const float2& f1, const float2& f2) { return float2(_hlslpp_add_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 operator + (const float3& f1, const float3& f2) { return float3(_hlslpp_add_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 operator + (const float4& f1, const float4& f2) { return float4(_hlslpp_add_ps(f1.vec, f2.vec)); }

	hlslpp_inline float2 operator + (const float2& f1, const float1& f2) { return float2(_hlslpp_add_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec))); }
	hlslpp_inline float3 operator + (const float3& f1, const float1& f2) { return float3(_hlslpp_add_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec))); }
	hlslpp_inline float4 operator + (const float4& f1, const float1& f2) { return float4(_hlslpp_add_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec))); }

	hlslpp_inline float2 operator + (const float1& f1, const float2& f2) { return float2(_hlslpp_add_ps(f2.vec, _hlslpp_perm_xxxx_ps(f1.vec))); }
	hlslpp_inline float3 operator + (const float1& f1, const float3& f2) { return float3(_hlslpp_add_ps(f2.vec, _hlslpp_perm_xxxx_ps(f1.vec))); }
	hlslpp_inline float4 operator + (const float1& f1, const float4& f2) { return float4(_hlslpp_add_ps(f2.vec, _hlslpp_perm_xxxx_ps(f1.vec))); }

	hlslpp_inline float1 operator - (const float1& f1, const float1& f2) { return float1(_hlslpp_sub_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 operator - (const float2& f1, const float2& f2) { return float2(_hlslpp_sub_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 operator - (const float3& f1, const float3& f2) { return float3(_hlslpp_sub_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 operator - (const float4& f1, const float4& f2) { return float4(_hlslpp_sub_ps(f1.vec, f2.vec)); }

	hlslpp_inline float2 operator - (const float2& f1, const float1& f2) { return float2(_hlslpp_sub_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec))); }
	hlslpp_inline float3 operator - (const float3& f1, const float1& f2) { return float3(_hlslpp_sub_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec))); }
	hlslpp_inline float4 operator - (const float4& f1, const float1& f2) { return float4(_hlslpp_sub_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec))); }

	hlslpp_inline float2 operator - (const float1& f1, const float2& f2) { return float2(_hlslpp_sub_ps(f2.vec, _hlslpp_perm_xxxx_ps(f1.vec))); }
	hlslpp_inline float3 operator - (const float1& f1, const float3& f2) { return float3(_hlslpp_sub_ps(f2.vec, _hlslpp_perm_xxxx_ps(f1.vec))); }
	hlslpp_inline float4 operator - (const float1& f1, const float4& f2) { return float4(_hlslpp_sub_ps(f2.vec, _hlslpp_perm_xxxx_ps(f1.vec))); }

	hlslpp_inline float1 operator * (const float1& f1, const float1& f2) { return float1(_hlslpp_mul_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 operator * (const float2& f1, const float2& f2) { return float2(_hlslpp_mul_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 operator * (const float3& f1, const float3& f2) { return float3(_hlslpp_mul_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 operator * (const float4& f1, const float4& f2) { return float4(_hlslpp_mul_ps(f1.vec, f2.vec)); }

	hlslpp_inline float2 operator * (const float2& f1, const float1& f2) { return float2(_hlslpp_mul_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec))); }
	hlslpp_inline float3 operator * (const float3& f1, const float1& f2) { return float3(_hlslpp_mul_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec))); }
	hlslpp_inline float4 operator * (const float4& f1, const float1& f2) { return float4(_hlslpp_mul_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec))); }

	hlslpp_inline float2 operator * (const float1& f1, const float2& f2) { return float2(_hlslpp_mul_ps(f2.vec, _hlslpp_perm_xxxx_ps(f1.vec))); }
	hlslpp_inline float3 operator * (const float1& f1, const float3& f2) { return float3(_hlslpp_mul_ps(f2.vec, _hlslpp_perm_xxxx_ps(f1.vec))); }
	hlslpp_inline float4 operator * (const float1& f1, const float4& f2) { return float4(_hlslpp_mul_ps(f2.vec, _hlslpp_perm_xxxx_ps(f1.vec))); }

	hlslpp_inline float1 operator / (const float1& f1, const float1& f2) { return float1(_hlslpp_div_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 operator / (const float2& f1, const float2& f2) { return float2(_hlslpp_div_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 operator / (const float3& f1, const float3& f2) { return float3(_hlslpp_div_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 operator / (const float4& f1, const float4& f2) { return float4(_hlslpp_div_ps(f1.vec, f2.vec)); }

	hlslpp_inline float2 operator / (const float2& f1, const float1& f2) { return float2(_hlslpp_div_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec))); }
	hlslpp_inline float3 operator / (const float3& f1, const float1& f2) { return float3(_hlslpp_div_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec))); }
	hlslpp_inline float4 operator / (const float4& f1, const float1& f2) { return float4(_hlslpp_div_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec))); }

	hlslpp_inline float2 operator / (const float1& f1, const float2& f2) { return float2(_hlslpp_div_ps(f2.vec, _hlslpp_perm_xxxx_ps(f1.vec))); }
	hlslpp_inline float3 operator / (const float1& f1, const float3& f2) { return float3(_hlslpp_div_ps(f2.vec, _hlslpp_perm_xxxx_ps(f1.vec))); }
	hlslpp_inline float4 operator / (const float1& f1, const float4& f2) { return float4(_hlslpp_div_ps(f2.vec, _hlslpp_perm_xxxx_ps(f1.vec))); }

	hlslpp_inline float1 operator - (const float1& f) { return float1(_hlslpp_neg_ps(f.vec)); }
	hlslpp_inline float2 operator - (const float2& f) { return float2(_hlslpp_neg_ps(f.vec)); }
	hlslpp_inline float3 operator - (const float3& f) { return float3(_hlslpp_neg_ps(f.vec)); }
	hlslpp_inline float4 operator - (const float4& f) { return float4(_hlslpp_neg_ps(f.vec)); }

	hlslpp_inline float1 operator % (const float1& f1, const float1& f2) { return float1(_hlslpp_fmod_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 operator % (const float2& f1, const float2& f2) { return float2(_hlslpp_fmod_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 operator % (const float3& f1, const float3& f2) { return float3(_hlslpp_fmod_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 operator % (const float4& f1, const float4& f2) { return float4(_hlslpp_fmod_ps(f1.vec, f2.vec)); }

	hlslpp_inline float1& operator += (float1& f1, const float1& f2) { f1 = f1 + f2; return f1; }
	hlslpp_inline float2& operator += (float2& f1, const float2& f2) { f1 = f1 + f2; return f1; }
	hlslpp_inline float3& operator += (float3& f1, const float3& f2) { f1 = f1 + f2; return f1; }
	hlslpp_inline float4& operator += (float4& f1, const float4& f2) { f1 = f1 + f2; return f1; }

	hlslpp_inline float1& operator -= (float1& f1, const float1& f2) { f1 = f1 - f2; return f1; }
	hlslpp_inline float2& operator -= (float2& f1, const float2& f2) { f1 = f1 - f2; return f1; }
	hlslpp_inline float3& operator -= (float3& f1, const float3& f2) { f1 = f1 - f2; return f1; }
	hlslpp_inline float4& operator -= (float4& f1, const float4& f2) { f1 = f1 - f2; return f1; }

	hlslpp_inline float1& operator *= (float1& f1, const float1& f2) { f1 = f1 * f2; return f1; }
	hlslpp_inline float2& operator *= (float2& f1, const float2& f2) { f1 = f1 * f2; return f1; }
	hlslpp_inline float3& operator *= (float3& f1, const float3& f2) { f1 = f1 * f2; return f1; }
	hlslpp_inline float4& operator *= (float4& f1, const float4& f2) { f1 = f1 * f2; return f1; }

	hlslpp_inline float1& operator /= (float1& f1, const float1& f2) { f1 = f1 / f2; return f1; }
	hlslpp_inline float2& operator /= (float2& f1, const float2& f2) { f1 = f1 / f2; return f1; }
	hlslpp_inline float3& operator /= (float3& f1, const float3& f2) { f1 = f1 / f2; return f1; }
	hlslpp_inline float4& operator /= (float4& f1, const float4& f2) { f1 = f1 / f2; return f1; }

	hlslpp_inline float1& operator %= (float1& f1, const float1& f2) { f1 = f1 % f2; return f1; }
	hlslpp_inline float2& operator %= (float2& f1, const float2& f2) { f1 = f1 % f2; return f1; }
	hlslpp_inline float3& operator %= (float3& f1, const float3& f2) { f1 = f1 % f2; return f1; }
	hlslpp_inline float4& operator %= (float4& f1, const float4& f2) { f1 = f1 % f2; return f1; }

	// Pre-increment

	hlslpp_inline float1& operator ++ (float1& f) { f = f + float1(f4_1); return f; }
	hlslpp_inline float2& operator ++ (float2& f) { f = f + float2(f4_1); return f; }
	hlslpp_inline float3& operator ++ (float3& f) { f = f + float3(f4_1); return f; }
	hlslpp_inline float4& operator ++ (float4& f) { f = f + float4(f4_1); return f; }

	template<int X> hlslpp_inline swizzle1<X>& operator ++ (swizzle1<X>& f) { f = f + float1(f4_1); return f; }
	template<int X, int Y> hlslpp_inline swizzle2<X, Y>& operator ++ (swizzle2<X, Y>& f) { f = f + float2(f4_1); return f; }
	template<int X, int Y, int Z> hlslpp_inline swizzle3<X, Y, Z>& operator ++ (swizzle3<X, Y, Z>& f) { f = f + float3(f4_1); return f; }
	template<int X, int Y, int Z, int W> hlslpp_inline swizzle4<X, Y, Z, W>& operator ++ (swizzle4<X, Y, Z, W>& f) { f = f + float4(f4_1); return f; }

	hlslpp_inline float1& operator -- (float1& f) { f = f - float1(f4_1); return f; }
	hlslpp_inline float2& operator -- (float2& f) { f = f - float2(f4_1); return f; }
	hlslpp_inline float3& operator -- (float3& f) { f = f - float3(f4_1); return f; }
	hlslpp_inline float4& operator -- (float4& f) { f = f - float4(f4_1); return f; }

	template<int X> hlslpp_inline swizzle1<X>& operator -- (swizzle1<X>& f) { f = f - float1(f4_1); return f; }
	template<int X, int Y> hlslpp_inline swizzle2<X, Y>& operator -- (swizzle2<X, Y>& f) { f = f - float2(f4_1); return f; }
	template<int X, int Y, int Z> hlslpp_inline swizzle3<X, Y, Z>& operator -- (swizzle3<X, Y, Z>& f) { f = f - float3(f4_1); return f; }
	template<int X, int Y, int Z, int W> hlslpp_inline swizzle4<X, Y, Z, W>& operator -- (swizzle4<X, Y, Z, W>& f) { f = f - float4(f4_1); return f; }

	// Post-increment

	hlslpp_inline float1 operator ++ (float1& f, int) { float1 tmp = f; f = f + float1(f4_1); return tmp; }
	hlslpp_inline float2 operator ++ (float2& f, int) { float2 tmp = f; f = f + float2(f4_1); return tmp; }
	hlslpp_inline float3 operator ++ (float3& f, int) { float3 tmp = f; f = f + float3(f4_1); return tmp; }
	hlslpp_inline float4 operator ++ (float4& f, int) { float4 tmp = f; f = f + float4(f4_1); return tmp; }

	template<int X>
	hlslpp_inline swizzle1<X> operator ++ (swizzle1<X>& f, int) { swizzle1<X> tmp = f; f = f + float1(f4_1); return tmp; }
	template<int X, int Y>
	hlslpp_inline swizzle2<X, Y> operator ++ (swizzle2<X, Y>& f, int) { swizzle2<X, Y> tmp = f; f = f + float2(f4_1); return tmp; }
	template<int X, int Y, int Z>
	hlslpp_inline swizzle3<X, Y, Z> operator ++ (swizzle3<X, Y, Z>& f, int) { swizzle3<X, Y, Z> tmp = f; f = f + float3(f4_1); return tmp; }
	template<int X, int Y, int Z, int W>
	hlslpp_inline swizzle4<X, Y, Z, W> operator ++ (swizzle4<X, Y, Z, W>& f, int) { swizzle4<X, Y, Z, W> tmp = f; f = f + float4(f4_1); return tmp; }

	hlslpp_inline float1 operator -- (float1& f, int) { float1 tmp = f; f = f - float1(f4_1); return tmp; }
	hlslpp_inline float2 operator -- (float2& f, int) { float2 tmp = f; f = f - float2(f4_1); return tmp; }
	hlslpp_inline float3 operator -- (float3& f, int) { float3 tmp = f; f = f - float3(f4_1); return tmp; }
	hlslpp_inline float4 operator -- (float4& f, int) { float4 tmp = f; f = f - float4(f4_1); return tmp; }

	template<int X>
	hlslpp_inline swizzle1<X> operator -- (swizzle1<X>& f, int) { swizzle1<X> tmp = f; f = f - float1(f4_1); return tmp; }
	template<int X, int Y>
	hlslpp_inline swizzle2<X, Y> operator -- (swizzle2<X, Y>& f, int) { swizzle2<X, Y> tmp = f; f = f - float2(f4_1); return tmp; }
	template<int X, int Y, int Z>
	hlslpp_inline swizzle3<X, Y, Z> operator -- (swizzle3<X, Y, Z>& f, int) { swizzle3<X, Y, Z> tmp = f; f = f - float3(f4_1); return tmp; }
	template<int X, int Y, int Z, int W>
	hlslpp_inline swizzle4<X, Y, Z, W> operator -- (swizzle4<X, Y, Z, W>& f, int) { swizzle4<X, Y, Z, W> tmp = f; f = f - float4(f4_1); return tmp; }

	//------------------------------------------------------------------------------------------------------------------------
	// float1 and swizzle1 need special overloads to disambiguate between our operators/functions and built-in float operators
	// and functions that are part of common headers such as cmath, math.h, algorithm, etc
	//------------------------------------------------------------------------------------------------------------------------

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator + (const float1& f1, T f2) { return f1 + float1(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float2) operator + (const float2& f1, T f2) { return f1 + float2(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float3) operator + (const float3& f1, T f2) { return f1 + float3(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float4) operator + (const float4& f1, T f2) { return f1 + float4(f2); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator + (T f1, const float1& f2) { return float1(f1) + f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float2) operator + (T f1, const float2& f2) { return float2(f1) + f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float3) operator + (T f1, const float3& f2) { return float3(f1) + f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float4) operator + (T f1, const float4& f2) { return float4(f1) + f2; }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator - (const float1& f1, T f2) { return f1 - float1(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float2) operator - (const float2& f1, T f2) { return f1 - float2(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float3) operator - (const float3& f1, T f2) { return f1 - float3(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float4) operator - (const float4& f1, T f2) { return f1 - float4(f2); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator - (T f1, const float1& f2) { return float1(f1) - f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float2) operator - (T f1, const float2& f2) { return float2(f1) - f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float3) operator - (T f1, const float3& f2) { return float3(f1) - f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float4) operator - (T f1, const float4& f2) { return float4(f1) - f2; }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator * (const float1& f1, T f2) { return f1 * float1(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float2) operator * (const float2& f1, T f2) { return f1 * float2(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float3) operator * (const float3& f1, T f2) { return f1 * float3(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float4) operator * (const float4& f1, T f2) { return f1 * float4(f2); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator * (T f1, const float1& f2) { return float1(f1) * f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float2) operator * (T f1, const float2& f2) { return float2(f1) * f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float3) operator * (T f1, const float3& f2) { return float3(f1) * f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float4) operator * (T f1, const float4& f2) { return float4(f1) * f2; }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator / (const float1& f1, T f2) { return f1 / float1(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float2) operator / (const float2& f1, T f2) { return f1 / float2(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float3) operator / (const float3& f1, T f2) { return f1 / float3(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float4) operator / (const float4& f1, T f2) { return f1 / float4(f2); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator / (T f1, const float1& f2) { return float1(f1) / f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float2) operator / (T f1, const float2& f2) { return float2(f1) / f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float3) operator / (T f1, const float3& f2) { return float3(f1) / f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float4) operator / (T f1, const float4& f2) { return float4(f1) / f2; }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator % (const float1& f1, T f2) { return f1 % float1(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float2) operator % (const float2& f1, T f2) { return f1 % float2(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float3) operator % (const float3& f1, T f2) { return f1 % float3(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float4) operator % (const float4& f1, T f2) { return f1 % float4(f2); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator % (T f1, const float1& f2) { return float1(f1) % f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float2) operator % (T f1, const float2& f2) { return float2(f1) % f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float3) operator % (T f1, const float3& f2) { return float3(f1) % f2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float4) operator % (T f1, const float4& f2) { return float4(f1) % f2; }

	template<int X, typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator + (const swizzle1<X>& f1, T f2) { return float1(f1) + float1(f2); }
	template<int X, typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator + (T f1, const swizzle1<X>& f2) { return float1(f1) + float1(f2); }

	template<int X, typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator - (const swizzle1<X>& f1, T f2) { return float1(f1) - float1(f2); }
	template<int X, typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator - (T f1, const swizzle1<X>& f2) { return float1(f1) - float1(f2); }

	template<int X, typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator * (const swizzle1<X>& f1, T f2) { return float1(f1) * float1(f2); }
	template<int X, typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator * (T f1, const swizzle1<X>& f2) { return float1(f1) * float1(f2); }

	template<int X, typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator / (const swizzle1<X>& f1, T f2) { return float1(f1) / float1(f2); }
	template<int X, typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator / (T f1, const swizzle1<X>& f2) { return float1(f1) / float1(f2); }

	template<int X, typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator % (const swizzle1<X>& f1, T f2) { return float1(f1) % float1(f2); }
	template<int X, typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) operator % (T f1, const swizzle1<X>& f2) { return float1(f1) % float1(f2); }

	template<int X> hlslpp_inline float1 operator + (const swizzle1<X>& s, const float1& f) { return float1(s) + f; }
	template<int X> hlslpp_inline float1 operator - (const swizzle1<X>& s, const float1& f) { return float1(s) - f; }
	template<int X> hlslpp_inline float1 operator * (const swizzle1<X>& s, const float1& f) { return float1(s) * f; }
	template<int X> hlslpp_inline float1 operator / (const swizzle1<X>& s, const float1& f) { return float1(s) / f; }
	template<int X> hlslpp_inline float1 operator % (const swizzle1<X>& s, const float1& f) { return float1(s) % f; }

	template<int X> hlslpp_inline float1 operator - (const swizzle1<X>& s) { return -float1(s); }

	template<int X>	hlslpp_inline swizzle1<X>& operator += (swizzle1<X>& s, const float1& f) { s = float1(s) + f; return s; }
	template<int X>	hlslpp_inline swizzle1<X>& operator -= (swizzle1<X>& s, const float1& f) { s = float1(s) - f; return s; }
	template<int X>	hlslpp_inline swizzle1<X>& operator *= (swizzle1<X>& s, const float1& f) { s = float1(s) * f; return s; }
	template<int X>	hlslpp_inline swizzle1<X>& operator /= (swizzle1<X>& s, const float1& f) { s = float1(s) / f; return s; }
	template<int X>	hlslpp_inline swizzle1<X>& operator %= (swizzle1<X>& s, const float1& f) { s = float1(s) % f; return s; }

	template<int X, int Y> hlslpp_inline swizzle2<X, Y>& operator += (swizzle2<X, Y>& s, const float2& f) { s = float2(s) + f; return s; }
	template<int X, int Y> hlslpp_inline swizzle2<X, Y>& operator -= (swizzle2<X, Y>& s, const float2& f) { s = float2(s) - f; return s; }
	template<int X, int Y> hlslpp_inline swizzle2<X, Y>& operator *= (swizzle2<X, Y>& s, const float2& f) { s = float2(s) * f; return s; }
	template<int X, int Y> hlslpp_inline swizzle2<X, Y>& operator /= (swizzle2<X, Y>& s, const float2& f) { s = float2(s) / f; return s; }
	template<int X, int Y> hlslpp_inline swizzle2<X, Y>& operator %= (swizzle2<X, Y>& s, const float2& f) { s = float2(s) % f; return s; }

	template<int X, int Y, int Z> hlslpp_inline swizzle3<X, Y, Z>& operator += (swizzle3<X, Y, Z>& s, const float3& f) { s = float3(s) + f; return s; }
	template<int X, int Y, int Z> hlslpp_inline swizzle3<X, Y, Z>& operator -= (swizzle3<X, Y, Z>& s, const float3& f) { s = float3(s) - f; return s; }
	template<int X, int Y, int Z> hlslpp_inline swizzle3<X, Y, Z>& operator *= (swizzle3<X, Y, Z>& s, const float3& f) { s = float3(s) * f; return s; }
	template<int X, int Y, int Z> hlslpp_inline swizzle3<X, Y, Z>& operator /= (swizzle3<X, Y, Z>& s, const float3& f) { s = float3(s) / f; return s; }
	template<int X, int Y, int Z> hlslpp_inline swizzle3<X, Y, Z>& operator %= (swizzle3<X, Y, Z>& s, const float3& f) { s = float3(s) % f; return s; }

	template<int X, int Y, int Z, int W> hlslpp_inline swizzle4<X, Y, Z, W>& operator += (swizzle4<X, Y, Z, W>& s, const float4& f) { s = float4(s) + f; return s; }
	template<int X, int Y, int Z, int W> hlslpp_inline swizzle4<X, Y, Z, W>& operator -= (swizzle4<X, Y, Z, W>& s, const float4& f) { s = float4(s) - f; return s; }
	template<int X, int Y, int Z, int W> hlslpp_inline swizzle4<X, Y, Z, W>& operator *= (swizzle4<X, Y, Z, W>& s, const float4& f) { s = float4(s) * f; return s; }
	template<int X, int Y, int Z, int W> hlslpp_inline swizzle4<X, Y, Z, W>& operator /= (swizzle4<X, Y, Z, W>& s, const float4& f) { s = float4(s) / f; return s; }
	template<int X, int Y, int Z, int W> hlslpp_inline swizzle4<X, Y, Z, W>& operator %= (swizzle4<X, Y, Z, W>& s, const float4& f) { s = float4(s) % f; return s; }

	hlslpp_inline float1 operator == (const float1& f1, const float1& f2) { return float1(_hlslpp_cmpeq1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 operator == (const float2& f1, const float2& f2) { return float2(_hlslpp_cmpeq1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 operator == (const float3& f1, const float3& f2) { return float3(_hlslpp_cmpeq1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 operator == (const float4& f1, const float4& f2) { return float4(_hlslpp_cmpeq1_ps(f1.vec, f2.vec)); }

	hlslpp_inline float1 operator != (const float1& f1, const float1& f2) { return float1(_hlslpp_cmpneq1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 operator != (const float2& f1, const float2& f2) { return float2(_hlslpp_cmpneq1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 operator != (const float3& f1, const float3& f2) { return float3(_hlslpp_cmpneq1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 operator != (const float4& f1, const float4& f2) { return float4(_hlslpp_cmpneq1_ps(f1.vec, f2.vec)); }

	hlslpp_inline float1 operator > (const float1& f1, const float1& f2) { return float1(_hlslpp_cmpgt1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 operator > (const float2& f1, const float2& f2) { return float2(_hlslpp_cmpgt1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 operator > (const float3& f1, const float3& f2) { return float3(_hlslpp_cmpgt1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 operator > (const float4& f1, const float4& f2) { return float4(_hlslpp_cmpgt1_ps(f1.vec, f2.vec)); }

	hlslpp_inline float1 operator >= (const float1& f1, const float1& f2) { return float1(_hlslpp_cmpge1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 operator >= (const float2& f1, const float2& f2) { return float2(_hlslpp_cmpge1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 operator >= (const float3& f1, const float3& f2) { return float3(_hlslpp_cmpge1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 operator >= (const float4& f1, const float4& f2) { return float4(_hlslpp_cmpge1_ps(f1.vec, f2.vec)); }

	hlslpp_inline float1 operator < (const float1& f1, const float1& f2) { return float1(_hlslpp_cmplt1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 operator < (const float2& f1, const float2& f2) { return float2(_hlslpp_cmplt1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 operator < (const float3& f1, const float3& f2) { return float3(_hlslpp_cmplt1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 operator < (const float4& f1, const float4& f2) { return float4(_hlslpp_cmplt1_ps(f1.vec, f2.vec)); }

	hlslpp_inline float1 operator <= (const float1& f1, const float1& f2) { return float1(_hlslpp_cmple1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 operator <= (const float2& f1, const float2& f2) { return float2(_hlslpp_cmple1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 operator <= (const float3& f1, const float3& f2) { return float3(_hlslpp_cmple1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 operator <= (const float4& f1, const float4& f2) { return float4(_hlslpp_cmple1_ps(f1.vec, f2.vec)); }

	hlslpp_inline float1 abs(const float1& f) { return float1(_hlslpp_abs_ps(f.vec)); }
	hlslpp_inline float2 abs(const float2& f) { return float2(_hlslpp_abs_ps(f.vec)); }
	hlslpp_inline float3 abs(const float3& f) { return float3(_hlslpp_abs_ps(f.vec)); }
	hlslpp_inline float4 abs(const float4& f) { return float4(_hlslpp_abs_ps(f.vec)); }

	hlslpp_inline float1 acos(const float1& f) { return float1(_hlslpp_acos_ps(f.vec)); }
	hlslpp_inline float2 acos(const float2& f) { return float2(_hlslpp_acos_ps(f.vec)); }
	hlslpp_inline float3 acos(const float3& f) { return float3(_hlslpp_acos_ps(f.vec)); }
	hlslpp_inline float4 acos(const float4& f) { return float4(_hlslpp_acos_ps(f.vec)); }

	hlslpp_inline bool all(const float1& f) { return _hlslpp_all1_ps(f.vec); }
	hlslpp_inline bool all(const float2& f) { return _hlslpp_all2_ps(f.vec); }
	hlslpp_inline bool all(const float3& f) { return _hlslpp_all3_ps(f.vec); }
	hlslpp_inline bool all(const float4& f) { return _hlslpp_all4_ps(f.vec); }

	hlslpp_inline bool any(const float1& f) { return _hlslpp_any1_ps(f.vec); }
	hlslpp_inline bool any(const float2& f) { return _hlslpp_any2_ps(f.vec); }
	hlslpp_inline bool any(const float3& f) { return _hlslpp_any3_ps(f.vec); }
	hlslpp_inline bool any(const float4& f) { return _hlslpp_any4_ps(f.vec); }

	hlslpp_inline float1 asin(const float1& f) { return float1(_hlslpp_asin_ps(f.vec)); }
	hlslpp_inline float2 asin(const float2& f) { return float2(_hlslpp_asin_ps(f.vec)); }
	hlslpp_inline float3 asin(const float3& f) { return float3(_hlslpp_asin_ps(f.vec)); }
	hlslpp_inline float4 asin(const float4& f) { return float4(_hlslpp_asin_ps(f.vec)); }

	hlslpp_inline float1 atan(const float1& f) { return float1(_hlslpp_atan_ps(f.vec)); }
	hlslpp_inline float2 atan(const float2& f) { return float2(_hlslpp_atan_ps(f.vec)); }
	hlslpp_inline float3 atan(const float3& f) { return float3(_hlslpp_atan_ps(f.vec)); }
	hlslpp_inline float4 atan(const float4& f) { return float4(_hlslpp_atan_ps(f.vec)); }

	hlslpp_inline float1 ceil(const float1& f) { return float1(_hlslpp_ceil_ps(f.vec)); }
	hlslpp_inline float2 ceil(const float2& f) { return float2(_hlslpp_ceil_ps(f.vec)); }
	hlslpp_inline float3 ceil(const float3& f) { return float3(_hlslpp_ceil_ps(f.vec)); }
	hlslpp_inline float4 ceil(const float4& f) { return float4(_hlslpp_ceil_ps(f.vec)); }

	hlslpp_inline float1 clamp(const float1& f, const float1& minf, const float1& maxf) { return float1(_hlslpp_clamp_ps(f.vec, minf.vec, maxf.vec)); }
	hlslpp_inline float2 clamp(const float2& f, const float2& minf, const float2& maxf) { return float2(_hlslpp_clamp_ps(f.vec, minf.vec, maxf.vec)); }
	hlslpp_inline float3 clamp(const float3& f, const float3& minf, const float3& maxf) { return float3(_hlslpp_clamp_ps(f.vec, minf.vec, maxf.vec)); }
	hlslpp_inline float4 clamp(const float4& f, const float4& minf, const float4& maxf) { return float4(_hlslpp_clamp_ps(f.vec, minf.vec, maxf.vec)); }

	hlslpp_inline float1 cos(const float1& f) { return float1(_hlslpp_cos_ps(f.vec)); }
	hlslpp_inline float2 cos(const float2& f) { return float2(_hlslpp_cos_ps(f.vec)); }
	hlslpp_inline float3 cos(const float3& f) { return float3(_hlslpp_cos_ps(f.vec)); }
	hlslpp_inline float4 cos(const float4& f) { return float4(_hlslpp_cos_ps(f.vec)); }

	hlslpp_inline float1 cosh(const float1& f) { return float1(_hlslpp_cosh_ps(f.vec)); }
	hlslpp_inline float2 cosh(const float2& f) { return float2(_hlslpp_cosh_ps(f.vec)); }
	hlslpp_inline float3 cosh(const float3& f) { return float3(_hlslpp_cosh_ps(f.vec)); }
	hlslpp_inline float4 cosh(const float4& f) { return float4(_hlslpp_cosh_ps(f.vec)); }

	hlslpp_inline float3 cross(const float3& f1, const float3& f2) { return float3(_hlslpp_cross_ps(f1.vec, f2.vec)); }

	hlslpp_inline float1 degrees(const float1& f) { return float1(_hlslpp_mul_ps(f.vec, f4_rad2deg)); }
	hlslpp_inline float2 degrees(const float2& f) { return float2(_hlslpp_mul_ps(f.vec, f4_rad2deg)); }
	hlslpp_inline float3 degrees(const float3& f) { return float3(_hlslpp_mul_ps(f.vec, f4_rad2deg)); }
	hlslpp_inline float4 degrees(const float4& f) { return float4(_hlslpp_mul_ps(f.vec, f4_rad2deg)); }

	hlslpp_inline float1 dot(const float1& f1, const float1& f2) { return f1 * f2; }
	hlslpp_inline float1 dot(const float2& f1, const float2& f2) { return float1(_hlslpp_dot2_ps(f1.vec, f2.vec)); }
	hlslpp_inline float1 dot(const float3& f1, const float3& f2) { return float1(_hlslpp_dot3_ps(f1.vec, f2.vec)); }
	hlslpp_inline float1 dot(const float4& f1, const float4& f2) { return float1(_hlslpp_dot4_ps(f1.vec, f2.vec)); }

	hlslpp_inline float1 exp(const float1& f) { return float1(_hlslpp_exp_ps(f.vec)); }
	hlslpp_inline float2 exp(const float2& f) { return float2(_hlslpp_exp_ps(f.vec)); }
	hlslpp_inline float3 exp(const float3& f) { return float3(_hlslpp_exp_ps(f.vec)); }
	hlslpp_inline float4 exp(const float4& f) { return float4(_hlslpp_exp_ps(f.vec)); }

	hlslpp_inline float1 exp2(const float1& f) { return float1(_hlslpp_exp2_ps(f.vec)); }
	hlslpp_inline float2 exp2(const float2& f) { return float2(_hlslpp_exp2_ps(f.vec)); }
	hlslpp_inline float3 exp2(const float3& f) { return float3(_hlslpp_exp2_ps(f.vec)); }
	hlslpp_inline float4 exp2(const float4& f) { return float4(_hlslpp_exp2_ps(f.vec)); }

	hlslpp_inline float1 floor(const float1& f) { return float1(_hlslpp_floor_ps(f.vec)); }
	hlslpp_inline float2 floor(const float2& f) { return float2(_hlslpp_floor_ps(f.vec)); }
	hlslpp_inline float3 floor(const float3& f) { return float3(_hlslpp_floor_ps(f.vec)); }
	hlslpp_inline float4 floor(const float4& f) { return float4(_hlslpp_floor_ps(f.vec)); }

	hlslpp_inline float1 fmod(const float1& f1, const float1& f2) { return float1(_hlslpp_fmod_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 fmod(const float2& f1, const float2& f2) { return float2(_hlslpp_fmod_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 fmod(const float3& f1, const float3& f2) { return float3(_hlslpp_fmod_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 fmod(const float4& f1, const float4& f2) { return float4(_hlslpp_fmod_ps(f1.vec, f2.vec)); }

	// A note on negative numbers. Contrary to intuition, frac(-0.75) != 0.75,
	// but is actually frac(-0.75) == 0.25 This is because hlsl defines frac
	// as frac(x) = x - floor(x)
	hlslpp_inline float1 frac(const float1& f) { return float1(_hlslpp_frac_ps(f.vec)); }
	hlslpp_inline float2 frac(const float2& f) { return float2(_hlslpp_frac_ps(f.vec)); }
	hlslpp_inline float3 frac(const float3& f) { return float3(_hlslpp_frac_ps(f.vec)); }
	hlslpp_inline float4 frac(const float4& f) { return float4(_hlslpp_frac_ps(f.vec)); }

	hlslpp_inline float1 isfinite(const float1& f) { return float1(_hlslpp_andnot_ps(_hlslpp_isfinite_ps(f.vec), f4_1)); }
	hlslpp_inline float2 isfinite(const float2& f) { return float2(_hlslpp_andnot_ps(_hlslpp_isfinite_ps(f.vec), f4_1)); }
	hlslpp_inline float3 isfinite(const float3& f) { return float3(_hlslpp_andnot_ps(_hlslpp_isfinite_ps(f.vec), f4_1)); }
	hlslpp_inline float4 isfinite(const float4& f) { return float4(_hlslpp_andnot_ps(_hlslpp_isfinite_ps(f.vec), f4_1)); }

	hlslpp_inline float1 isinf(const float1& f) { return float1(_hlslpp_and_ps(_hlslpp_isinf_ps(f.vec), f4_1)); }
	hlslpp_inline float2 isinf(const float2& f) { return float2(_hlslpp_and_ps(_hlslpp_isinf_ps(f.vec), f4_1)); }
	hlslpp_inline float3 isinf(const float3& f) { return float3(_hlslpp_and_ps(_hlslpp_isinf_ps(f.vec), f4_1)); }
	hlslpp_inline float4 isinf(const float4& f) { return float4(_hlslpp_and_ps(_hlslpp_isinf_ps(f.vec), f4_1)); }

	hlslpp_inline float1 isnan(const float1& f) { return float1(_hlslpp_and_ps(_hlslpp_isnan_ps(f.vec), f4_1)); }
	hlslpp_inline float2 isnan(const float2& f) { return float2(_hlslpp_and_ps(_hlslpp_isnan_ps(f.vec), f4_1)); }
	hlslpp_inline float3 isnan(const float3& f) { return float3(_hlslpp_and_ps(_hlslpp_isnan_ps(f.vec), f4_1)); }
	hlslpp_inline float4 isnan(const float4& f) { return float4(_hlslpp_and_ps(_hlslpp_isnan_ps(f.vec), f4_1)); }

	hlslpp_inline float1 length(const float1& f) { return f; }
	hlslpp_inline float1 length(const float2& f) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot2_ps(f.vec, f.vec))); }
	hlslpp_inline float1 length(const float3& f) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot3_ps(f.vec, f.vec))); }
	hlslpp_inline float1 length(const float4& f) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(f.vec, f.vec))); }

	hlslpp_inline float1 lerp(const float1& f1, const float1& f2, const float1& a) { return float1(_hlslpp_lerp_ps(f1.vec, f2.vec, a.vec)); }
	hlslpp_inline float2 lerp(const float2& f1, const float2& f2, const float2& a) { return float2(_hlslpp_lerp_ps(f1.vec, f2.vec, a.vec)); }
	hlslpp_inline float3 lerp(const float3& f1, const float3& f2, const float3& a) { return float3(_hlslpp_lerp_ps(f1.vec, f2.vec, a.vec)); }
	hlslpp_inline float4 lerp(const float4& f1, const float4& f2, const float4& a) { return float4(_hlslpp_lerp_ps(f1.vec, f2.vec, a.vec)); }

	hlslpp_inline float1 log(const float1& f) { return float1(_hlslpp_log_ps(f.vec)); }
	hlslpp_inline float2 log(const float2& f) { return float2(_hlslpp_log_ps(f.vec)); }
	hlslpp_inline float3 log(const float3& f) { return float3(_hlslpp_log_ps(f.vec)); }
	hlslpp_inline float4 log(const float4& f) { return float4(_hlslpp_log_ps(f.vec)); }

	hlslpp_inline float1 log2(const float1& f) { return float1(_hlslpp_log2_ps(f.vec)); }
	hlslpp_inline float2 log2(const float2& f) { return float2(_hlslpp_log2_ps(f.vec)); }
	hlslpp_inline float3 log2(const float3& f) { return float3(_hlslpp_log2_ps(f.vec)); }
	hlslpp_inline float4 log2(const float4& f) { return float4(_hlslpp_log2_ps(f.vec)); }

	hlslpp_inline float1 log10(const float1& f) { return float1(_hlslpp_log10_ps(f.vec)); }
	hlslpp_inline float2 log10(const float2& f) { return float2(_hlslpp_log10_ps(f.vec)); }
	hlslpp_inline float3 log10(const float3& f) { return float3(_hlslpp_log10_ps(f.vec)); }
	hlslpp_inline float4 log10(const float4& f) { return float4(_hlslpp_log10_ps(f.vec)); }

	hlslpp_inline float1 min(const float1& f1, const float1& f2) { return float1(_hlslpp_min_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 min(const float2& f1, const float2& f2) { return float2(_hlslpp_min_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 min(const float3& f1, const float3& f2) { return float3(_hlslpp_min_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 min(const float4& f1, const float4& f2) { return float4(_hlslpp_min_ps(f1.vec, f2.vec)); }

	hlslpp_inline float1 mad(const float1& f1, const float1& f2, const float1& f3) { return float1(_hlslpp_madd_ps(f1.vec, f2.vec, f3.vec)); }
	hlslpp_inline float2 mad(const float2& f1, const float2& f2, const float2& f3) { return float2(_hlslpp_madd_ps(f1.vec, f2.vec, f3.vec)); }
	hlslpp_inline float3 mad(const float3& f1, const float3& f2, const float3& f3) { return float3(_hlslpp_madd_ps(f1.vec, f2.vec, f3.vec)); }
	hlslpp_inline float4 mad(const float4& f1, const float4& f2, const float4& f3) { return float4(_hlslpp_madd_ps(f1.vec, f2.vec, f3.vec)); }

	hlslpp_inline float1 max(const float1& f1, const float1& f2) { return float1(_hlslpp_max_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 max(const float2& f1, const float2& f2) { return float2(_hlslpp_max_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 max(const float3& f1, const float3& f2) { return float3(_hlslpp_max_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 max(const float4& f1, const float4& f2) { return float4(_hlslpp_max_ps(f1.vec, f2.vec)); }

	hlslpp_inline float1 modf(const float1& f1, float1& integerPart)
	{
		n128 signedFrac, signedInteger;
		_hlslpp_modf_ps(f1.vec, signedInteger, signedFrac);
		integerPart = float1(signedInteger);
		return float1(signedFrac);
	}

	hlslpp_inline float2 modf(const float2& f1, float2& integerPart)
	{
		n128 signedFrac, signedInteger;
		_hlslpp_modf_ps(f1.vec, signedInteger, signedFrac);
		integerPart = float2(signedInteger);
		return float2(signedFrac);
	}

	hlslpp_inline float3 modf(const float3& f1, float3& integerPart)
	{ 
		n128 signedFrac, signedInteger;
		_hlslpp_modf_ps(f1.vec, signedInteger, signedFrac);
		integerPart = float3(signedInteger);
		return float3(signedFrac);
	}

	hlslpp_inline float4 modf(const float4& f1, float4& integerPart)
	{
		n128 signedFrac, signedInteger;
		_hlslpp_modf_ps(f1.vec, signedInteger, signedFrac);
		integerPart = float4(signedInteger);
		return float4(signedFrac);
	}

	hlslpp_inline float1 normalize(const float1&/* f*/) { return float1(1.0f); }
	hlslpp_inline float2 normalize(const float2& f) { return float2(_hlslpp_div_ps(f.vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot2_ps(f.vec, f.vec))))); }
	hlslpp_inline float3 normalize(const float3& f) { return float3(_hlslpp_div_ps(f.vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot3_ps(f.vec, f.vec))))); }
	hlslpp_inline float4 normalize(const float4& f) { return float4(_hlslpp_div_ps(f.vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(f.vec, f.vec))))); }

	hlslpp_inline float1 pow(const float1& f1, const float1& f2) { return float1(_hlslpp_exp2_ps(_hlslpp_mul_ps(f2.vec, _hlslpp_log2_ps(f1.vec)))); }
	hlslpp_inline float2 pow(const float2& f1, const float2& f2) { return float2(_hlslpp_exp2_ps(_hlslpp_mul_ps(f2.vec, _hlslpp_log2_ps(f1.vec)))); }
	hlslpp_inline float3 pow(const float3& f1, const float3& f2) { return float3(_hlslpp_exp2_ps(_hlslpp_mul_ps(f2.vec, _hlslpp_log2_ps(f1.vec)))); }
	hlslpp_inline float4 pow(const float4& f1, const float4& f2) { return float4(_hlslpp_exp2_ps(_hlslpp_mul_ps(f2.vec, _hlslpp_log2_ps(f1.vec)))); }

	hlslpp_inline float1 radians(const float1& f) { return float1(_hlslpp_mul_ps(f.vec, f4_deg2rad)); }
	hlslpp_inline float2 radians(const float2& f) { return float2(_hlslpp_mul_ps(f.vec, f4_deg2rad)); }
	hlslpp_inline float3 radians(const float3& f) { return float3(_hlslpp_mul_ps(f.vec, f4_deg2rad)); }
	hlslpp_inline float4 radians(const float4& f) { return float4(_hlslpp_mul_ps(f.vec, f4_deg2rad)); }

	hlslpp_inline float1 rcp(const float1& f) { return float1(_hlslpp_rcp_ps(f.vec)); }
	hlslpp_inline float2 rcp(const float2& f) { return float2(_hlslpp_rcp_ps(f.vec)); }
	hlslpp_inline float3 rcp(const float3& f) { return float3(_hlslpp_rcp_ps(f.vec)); }
	hlslpp_inline float4 rcp(const float4& f) { return float4(_hlslpp_rcp_ps(f.vec)); }

	hlslpp_inline float1 reflect(const float1& i, const float1& n) { return float1(_hlslpp_reflect1_ps(i.vec, n.vec)); }
	hlslpp_inline float2 reflect(const float2& i, const float2& n) { return float2(_hlslpp_reflect2_ps(i.vec, n.vec)); }
	hlslpp_inline float3 reflect(const float3& i, const float3& n) { return float3(_hlslpp_reflect3_ps(i.vec, n.vec)); }
	hlslpp_inline float4 reflect(const float4& i, const float4& n) { return float4(_hlslpp_reflect4_ps(i.vec, n.vec)); }

	hlslpp_inline float1 refract(const float1& i, const float1& n, const float1& ior) { return float1(_hlslpp_refract1_ps(i.vec, n.vec, ior.vec)); }
	hlslpp_inline float2 refract(const float2& i, const float2& n, const float1& ior) { return float2(_hlslpp_refract2_ps(i.vec, n.vec, ior.vec)); }
	hlslpp_inline float3 refract(const float3& i, const float3& n, const float1& ior) { return float3(_hlslpp_refract3_ps(i.vec, n.vec, ior.vec)); }
	hlslpp_inline float4 refract(const float4& i, const float4& n, const float1& ior) { return float4(_hlslpp_refract4_ps(i.vec, n.vec, ior.vec)); }

	hlslpp_inline float1 rsqrt(const float1& f) { return float1(_hlslpp_rsqrt_ps(f.vec)); }
	hlslpp_inline float2 rsqrt(const float2& f) { return float2(_hlslpp_rsqrt_ps(f.vec)); }
	hlslpp_inline float3 rsqrt(const float3& f) { return float3(_hlslpp_rsqrt_ps(f.vec)); }
	hlslpp_inline float4 rsqrt(const float4& f) { return float4(_hlslpp_rsqrt_ps(f.vec)); }

	hlslpp_inline float1 round(const float1& f) { return float1(_hlslpp_round_ps(f.vec)); }
	hlslpp_inline float2 round(const float2& f) { return float2(_hlslpp_round_ps(f.vec)); }
	hlslpp_inline float3 round(const float3& f) { return float3(_hlslpp_round_ps(f.vec)); }
	hlslpp_inline float4 round(const float4& f) { return float4(_hlslpp_round_ps(f.vec)); }

	hlslpp_inline float1 saturate(const float1& f) { return float1(_hlslpp_sat_ps(f.vec)); }
	hlslpp_inline float2 saturate(const float2& f) { return float2(_hlslpp_sat_ps(f.vec)); }
	hlslpp_inline float3 saturate(const float3& f) { return float3(_hlslpp_sat_ps(f.vec)); }
	hlslpp_inline float4 saturate(const float4& f) { return float4(_hlslpp_sat_ps(f.vec)); }

	hlslpp_inline float1 sign(const float1& f) { return float1(_hlslpp_sign_ps(f.vec)); }
	hlslpp_inline float2 sign(const float2& f) { return float2(_hlslpp_sign_ps(f.vec)); }
	hlslpp_inline float3 sign(const float3& f) { return float3(_hlslpp_sign_ps(f.vec)); }
	hlslpp_inline float4 sign(const float4& f) { return float4(_hlslpp_sign_ps(f.vec)); }

	hlslpp_inline float1 sin(const float1& f) { return float1(_hlslpp_sin_ps(f.vec)); }
	hlslpp_inline float2 sin(const float2& f) { return float2(_hlslpp_sin_ps(f.vec)); }
	hlslpp_inline float3 sin(const float3& f) { return float3(_hlslpp_sin_ps(f.vec)); }
	hlslpp_inline float4 sin(const float4& f) { return float4(_hlslpp_sin_ps(f.vec)); }

	hlslpp_inline void sincos(const float1& f, float1& s, float1& c) { s = float1(_hlslpp_sin_ps(f.vec)); c = float1(_hlslpp_cos_ps(f.vec)); }
	hlslpp_inline void sincos(const float2& f, float2& s, float2& c) { s = float2(_hlslpp_sin_ps(f.vec)); c = float2(_hlslpp_cos_ps(f.vec)); }
	hlslpp_inline void sincos(const float3& f, float3& s, float3& c) { s = float3(_hlslpp_sin_ps(f.vec)); c = float3(_hlslpp_cos_ps(f.vec)); }
	hlslpp_inline void sincos(const float4& f, float4& s, float4& c) { s = float4(_hlslpp_sin_ps(f.vec)); c = float4(_hlslpp_cos_ps(f.vec)); }

	hlslpp_inline float1 sinh(const float1& f) { return float1(_hlslpp_sinh_ps(f.vec)); }
	hlslpp_inline float2 sinh(const float2& f) { return float2(_hlslpp_sinh_ps(f.vec)); }
	hlslpp_inline float3 sinh(const float3& f) { return float3(_hlslpp_sinh_ps(f.vec)); }
	hlslpp_inline float4 sinh(const float4& f) { return float4(_hlslpp_sinh_ps(f.vec)); }

	hlslpp_inline float1 smoothstep(const float1& f1, const float1& f2, const float1& a) { return float1(_hlslpp_smoothstep_ps(f1.vec, f2.vec, a.vec)); }
	hlslpp_inline float2 smoothstep(const float2& f1, const float2& f2, const float2& a) { return float2(_hlslpp_smoothstep_ps(f1.vec, f2.vec, a.vec)); }
	hlslpp_inline float3 smoothstep(const float3& f1, const float3& f2, const float3& a) { return float3(_hlslpp_smoothstep_ps(f1.vec, f2.vec, a.vec)); }
	hlslpp_inline float4 smoothstep(const float4& f1, const float4& f2, const float4& a) { return float4(_hlslpp_smoothstep_ps(f1.vec, f2.vec, a.vec)); }

	hlslpp_inline float1 sqrt(const float1& f) { return float1(_hlslpp_sqrt_ps(f.vec)); }
	hlslpp_inline float2 sqrt(const float2& f) { return float2(_hlslpp_sqrt_ps(f.vec)); }
	hlslpp_inline float3 sqrt(const float3& f) { return float3(_hlslpp_sqrt_ps(f.vec)); }
	hlslpp_inline float4 sqrt(const float4& f) { return float4(_hlslpp_sqrt_ps(f.vec)); }

	hlslpp_inline float1 step(const float1& f1, const float1& f2) { return float1(_hlslpp_step_ps(f1.vec, f2.vec)); }
	hlslpp_inline float2 step(const float2& f1, const float2& f2) { return float2(_hlslpp_step_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3 step(const float3& f1, const float3& f2) { return float3(_hlslpp_step_ps(f1.vec, f2.vec)); }
	hlslpp_inline float4 step(const float4& f1, const float4& f2) { return float4(_hlslpp_step_ps(f1.vec, f2.vec)); }

	hlslpp_inline float1 tan(const float1& f) { return float1(_hlslpp_tan_ps(f.vec)); }
	hlslpp_inline float2 tan(const float2& f) { return float2(_hlslpp_tan_ps(f.vec)); }
	hlslpp_inline float3 tan(const float3& f) { return float3(_hlslpp_tan_ps(f.vec)); }
	hlslpp_inline float4 tan(const float4& f) { return float4(_hlslpp_tan_ps(f.vec)); }

	hlslpp_inline float1 tanh(const float1& f) { return float1(_hlslpp_tanh_ps(f.vec)); }
	hlslpp_inline float2 tanh(const float2& f) { return float2(_hlslpp_tanh_ps(f.vec)); }
	hlslpp_inline float3 tanh(const float3& f) { return float3(_hlslpp_tanh_ps(f.vec)); }
	hlslpp_inline float4 tanh(const float4& f) { return float4(_hlslpp_tanh_ps(f.vec)); }

	hlslpp_inline float1 trunc(const float1& f) { return float1(_hlslpp_trunc_ps(f.vec)); }
	hlslpp_inline float2 trunc(const float2& f) { return float2(_hlslpp_trunc_ps(f.vec)); }
	hlslpp_inline float3 trunc(const float3& f) { return float3(_hlslpp_trunc_ps(f.vec)); }
	hlslpp_inline float4 trunc(const float4& f) { return float4(_hlslpp_trunc_ps(f.vec)); }

	//--------------------------------------------------------------------------------------------------------------------------
	// Function disambiguation. This typically happens when pulling in math.h, <cmath> or <algorithm>, where functions now live
	// in the global namespace. Due to implicit conversions, we need to clarify to the compiler which functions it needs to use.
	//--------------------------------------------------------------------------------------------------------------------------

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) fmod(const float1& f1, T f2) { return fmod(f1, float1(f2)); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) fmod(T f1, const float1& f2) { return fmod(float1(f1), f2); }

	template<int X, int Y> hlslpp_inline float1 max(const swizzle1<X>& s, const swizzle1<Y>& f) { return max(float1(s), float1(f)); }
	template<int X> hlslpp_inline float1 max(const swizzle1<X>& s, const swizzle1<X>& f) { return max(float1(s), float1(f)); }

	template<int X, int Y> hlslpp_inline float1 min(const swizzle1<X>& s, const swizzle1<Y>& f) { return min(float1(s), float1(f)); }
	template<int X> hlslpp_inline float1 min(const swizzle1<X>& s, const swizzle1<X>& f) { return min(float1(s), float1(f)); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) pow(const float1& f1, T f2) { return pow(f1, float1(f2)); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, float1) pow(T f1, const float1& f2) { return pow(float1(f1), f2); }
	template<int X, int Y> hlslpp_inline float1 pow(const swizzle1<X>& s, const swizzle1<Y>& f) { return pow(float1(s), float1(f)); }

	template<int X> hlslpp_inline float1 abs(const swizzle1<X>& s) { return abs(float1(s)); }
	template<int X> hlslpp_inline float1 acos(const swizzle1<X>& s) { return acos(float1(s)); }
	template<int X> hlslpp_inline float1 asin(const swizzle1<X>& s) { return asin(float1(s)); }
	template<int X> hlslpp_inline float1 atan(const swizzle1<X>& s) { return atan(float1(s)); }
	template<int X> hlslpp_inline float1 ceil(const swizzle1<X>& s) { return ceil(float1(s)); }
	template<int X> hlslpp_inline float1 cos(const swizzle1<X>& s) { return cos(float1(s)); }
	template<int X> hlslpp_inline float1 cosh(const swizzle1<X>& s) { return cosh(float1(s)); }
	template<int X> hlslpp_inline float1 floor(const swizzle1<X>& s) { return floor(float1(s)); }
	template<int X> hlslpp_inline float1 frac(const swizzle1<X>& s) { return frac(float1(s)); }
	template<int X> hlslpp_inline float1 exp(const swizzle1<X>& s) { return exp(float1(s)); }
	template<int X> hlslpp_inline float1 exp2(const swizzle1<X>& s) { return exp2(float1(s)); }
	template<int X> hlslpp_inline float1 log(const swizzle1<X>& s) { return log(float1(s)); }
	template<int X> hlslpp_inline float1 log2(const swizzle1<X>& s) { return log2(float1(s)); }
	template<int X> hlslpp_inline float1 log10(const swizzle1<X>& s) { return log10(float1(s)); }
	template<int X> hlslpp_inline float1 round(const swizzle1<X>& s) { return round(float1(s)); }
	template<int X> hlslpp_inline float1 sin(const swizzle1<X>& s) { return sin(float1(s)); }
	template<int X> hlslpp_inline float1 sinh(const swizzle1<X>& s) { return sinh(float1(s)); }
	template<int X> hlslpp_inline float1 sqrt(const swizzle1<X>& s) { return sqrt(float1(s)); }
	template<int X> hlslpp_inline float1 tan(const swizzle1<X>& s) { return tan(float1(s)); }
	template<int X> hlslpp_inline float1 tanh(const swizzle1<X>& s) { return tanh(float1(s)); }
	template<int X> hlslpp_inline float1 trunc(const swizzle1<X>& s) { return trunc(float1(s)); }

	template<int X> hlslpp_inline float1 isfinite(const swizzle1<X>& s) { return isfinite(float1(s)); }
	template<int X> hlslpp_inline float1 isnan(const swizzle1<X>& s) { return isnan(float1(s)); }
	template<int X> hlslpp_inline float1 isinf(const swizzle1<X>& s) { return isinf(float1(s)); }

	template<int X, int Y> hlslpp_inline float2 isfinite(const swizzle2<X, Y>& s) { return isfinite(float2(s)); }
	template<int X, int Y> hlslpp_inline float2 isinf(const swizzle2<X, Y>& s) { return isinf(float2(s)); }
	template<int X, int Y> hlslpp_inline float2 isnan(const swizzle2<X, Y>& s) { return isnan(float2(s)); }

	template<int X, int Y, int Z> hlslpp_inline float3 isfinite(const swizzle3<X, Y, Z>& s) { return isfinite(float3(s)); }
	template<int X, int Y, int Z> hlslpp_inline float3 isinf(const swizzle3<X, Y, Z>& s) { return isinf(float3(s)); }
	template<int X, int Y, int Z> hlslpp_inline float3 isnan(const swizzle3<X, Y, Z>& s) { return isnan(float3(s)); }

	template<int X, int Y, int Z, int W> hlslpp_inline float4 isfinite(const swizzle4<X, Y, Z, W>& s) { return isfinite(float4(s)); }
	template<int X, int Y, int Z, int W> hlslpp_inline float4 isinf(const swizzle4<X, Y, Z, W>& s) { return isinf(float4(s)); }
	template<int X, int Y, int Z, int W> hlslpp_inline float4 isnan(const swizzle4<X, Y, Z, W>& s) { return isnan(float4(s)); }

	template<int X>
	swizzle1<X>& swizzle1<X>::operator = (const float1& f)
	{
		vec = _hlslpp_blend_ps(vec, (swizzle<0, X>(f.vec)), HLSLPP_COMPONENT_X(X)); return *this;
	}

	template<int X, int Y>
	swizzle2<X, Y>& swizzle2<X, Y>::operator = (const float2& f)
	{
		staticAsserts();
		vec = blend(vec, swizzle<0, 1, X, Y>(f.vec));
		return *this;
	}

	template<int X, int Y, int Z>
	swizzle3<X, Y, Z>& swizzle3<X, Y, Z>::operator = (const float3& f)
	{
		staticAsserts();
		vec = blend(vec, swizzle<0, 1, 2, X, Y, Z>(f.vec));
		return *this;
	}

	template<int X, int Y, int Z, int W>
	swizzle4<X, Y, Z, W>& swizzle4<X, Y, Z, W>::operator = (const float4& f)
	{
		staticAsserts();
		vec = swizzle<0, 1, 2, 3, X, Y, Z, W>(f.vec);
		return *this;
	}

	hlslpp_inline void store(const float1& v, float* f)
	{
		_hlslpp_store1_ps(f, v.vec);
	}

	hlslpp_inline void store(const float2& v, float* f)
	{
		_hlslpp_store2_ps(f, v.vec);
	}

	hlslpp_inline void store(const float3& v, float* f)
	{
		_hlslpp_store3_ps(f, v.vec);
	}

	hlslpp_inline void store(const float4& v, float* f)
	{
		_hlslpp_store4_ps(f, v.vec);
	}

	hlslpp_inline void load(float1& v, float* f)
	{
		_hlslpp_load1_ps(f, v.vec);
	}

	hlslpp_inline void load(float2& v, float* f)
	{
		_hlslpp_load2_ps(f, v.vec);
	}

	hlslpp_inline void load(float3& v, float* f)
	{
		_hlslpp_load3_ps(f, v.vec);
	}

	hlslpp_inline void load(float4& v, float* f)
	{
		_hlslpp_load4_ps(f, v.vec);
	}
}