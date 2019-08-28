#pragma once

#if defined(_MSC_VER)

	#include <immintrin.h>

	// MSVC does not define these macros so we define them via heuristics and use them below. Other compilers
	// define these macros because they have command line switches to enable them at compile time. Alternatively
	// hlsl++ users can define these themselves and get access to the features.

	#if defined(__AVX2__)

		#if !defined(__FMA__)
		#define __FMA__ 1
		#endif

	#endif

	#if defined(__AVX__)
	
		#if !defined(__SSE4_1__)
		#define __SSE4_1__ 1
		#endif

		#define HLSLPP_SIMD_REGISTER_FLOAT8

	#endif

	#if defined(__SSE4_1__)

		#if !defined(__SSSE3__)
		#define __SSSE3__ 1
		#endif

	#endif
#else

	#include <x86intrin.h>

#endif

#define HLSLPP_FLOAT64

// All available in SSE/SSE2
typedef __m128  n128;
typedef __m128i n128i;
typedef __m128d n128d;

#if defined(__AVX__)
typedef __m256  n256;
typedef __m256d n256d;
typedef __m256i n256i;
#endif

//------
// Float
//------

#define _hlslpp_set1_ps(x)						_mm_set1_ps((x))
#define _hlslpp_set_ps(x, y, z, w)				_mm_set_ps((w), (z), (y), (x))
#define _hlslpp_setzero_ps()					_mm_setzero_ps()

#define _hlslpp_add_ps(x, y)					_mm_add_ps((x), (y))
#define _hlslpp_sub_ps(x, y)					_mm_sub_ps((x), (y))
#define _hlslpp_mul_ps(x, y)					_mm_mul_ps((x), (y))
#define _hlslpp_div_ps(x, y)					_mm_div_ps((x), (y))

#define _hlslpp_add_ss(x, y)					_mm_add_ss((x), (y))
#define _hlslpp_sub_ss(x, y)					_mm_sub_ss((x), (y))
#define _hlslpp_mul_ss(x, y)					_mm_mul_ss((x), (y))
#define _hlslpp_div_ss(x, y)					_mm_div_ss((x), (y))

#define _hlslpp_rcp_ps(x)						_mm_rcp_ps((x))

// The following are alternatives but have been measured to be slower
// _mm_sub_ps(f4zero, x);			// Slowest
// _mm_mul_ps(f4minusOne, x);		// Slower
#define _hlslpp_neg_ps(x)						_mm_xor_ps((x), f4negativeMask)

#if defined(__FMA__)

#define _hlslpp_madd_ps(x, y, z)				_mm_fmadd_ps((x), (y), (z))
#define _hlslpp_msub_ps(x, y, z)				_mm_fmsub_ps((x), (y), (z))
#define _hlslpp_subm_ps(x, y, z)				_mm_fnmadd_ps((x), (y), (z))

#else

#define _hlslpp_madd_ps(x, y, z)				_mm_add_ps(_mm_mul_ps((x), (y)), (z))
#define _hlslpp_msub_ps(x, y, z)				_mm_sub_ps(_mm_mul_ps((x), (y)), (z))
#define _hlslpp_subm_ps(x, y, z)				_mm_sub_ps((x), _mm_mul_ps((y), (z)))

#endif

// Reference http://www.liranuna.com/sse-intrinsics-optimizations-in-popular-compilers/
#define _hlslpp_abs_ps(x)						_mm_and_ps(f4absMask, (x))

#define _hlslpp_sqrt_ps(x)						_mm_sqrt_ps((x))
#define _hlslpp_rsqrt_ps(x)						_mm_rsqrt_ps((x))

#define _hlslpp_cmpeq_ps(x, y)					_mm_cmpeq_ps((x), (y))
#define _hlslpp_cmpneq_ps(x, y)					_mm_cmpneq_ps((x), (y))

#define _hlslpp_cmpgt_ps(x, y)					_mm_cmpgt_ps((x), (y))
#define _hlslpp_cmpge_ps(x, y)					_mm_cmpge_ps((x), (y))

#define _hlslpp_cmplt_ps(x, y)					_mm_cmplt_ps((x), (y))
#define _hlslpp_cmple_ps(x, y)					_mm_cmple_ps((x), (y))

#define _hlslpp_max_ps(x, y)					_mm_max_ps((x), (y))
#define _hlslpp_min_ps(x, y)					_mm_min_ps((x), (y))

#define _hlslpp_trunc_ps(x)						_mm_round_ps((x), _MM_FROUND_TRUNC)
#define _hlslpp_floor_ps(x)						_mm_floor_ps((x))
#define _hlslpp_ceil_ps(x)						_mm_ceil_ps((x))

// _MM_FROUND_TO_NEAREST_INT to match fxc behavior
#define _hlslpp_round_ps(x)						_mm_round_ps((x), _MM_FROUND_TO_NEAREST_INT)

#define _hlslpp_frac_ps(x)						_mm_sub_ps((x), _mm_floor_ps(x))

#define _hlslpp_clamp_ps(x, minx, maxx)			_mm_max_ps(_mm_min_ps((x), (maxx)), (minx))
#define _hlslpp_sat_ps(x)						_mm_max_ps(_mm_min_ps((x), f4_1), f4_0)

#define _hlslpp_and_ps(x, y)					_mm_and_ps((x), (y))
#define _hlslpp_andnot_ps(x, y)					_mm_andnot_ps((x), (y))
#define _hlslpp_or_ps(x, y)						_mm_or_ps((x), (y))
#define _hlslpp_xor_ps(x, y)					_mm_xor_ps((x), (y))

#define _hlslpp_movelh_ps(x, y)					_mm_movelh_ps((x), (y))
#define _hlslpp_movehl_ps(x, y)					_mm_movehl_ps((x), (y))
#define _hlslpp_movehdup_ps(x)					_mm_movehdup_ps((x))

#if defined(__AVX__)
#define _hlslpp_perm_ps(x, mask)				_mm_permute_ps((x), (mask))
#else
#define _hlslpp_perm_ps(x, mask)				_mm_shuffle_ps((x), (x), (mask))
#endif

#define _hlslpp_shuffle_ps(x, y, mask)			_mm_shuffle_ps((x), (y), (mask))

#define _hlslpp_unpacklo_ps(x, y)				_mm_unpacklo_ps((x), (y))
#define _hlslpp_unpackhi_ps(x, y)				_mm_unpackhi_ps((x), (y))

// SSE2 alternative https://markplusplus.wordpress.com/2007/03/14/fast-sse-select-operation/
// _mm_xor_ps((x), _mm_and_ps(mask, _mm_xor_ps((y), (x))))
// Bit-select val1 and val2 based on the contents of the mask
#define _hlslpp_sel_ps(x, y, mask)				_mm_blendv_ps((x), (y), (mask))

#define _hlslpp_blend_ps(x, y, mask)			_mm_blend_ps((x), (y), (mask))

// Inspiration for some bits from https://stackoverflow.com/questions/6996764/fastest-way-to-do-horizontal-float-vector-sum-on-x86
hlslpp_inline n128 _hlslpp_dot4_ps(n128 x, n128 y)
{
	#if defined(__SSE4_1__)
	
		n128 result = _mm_dp_ps(x, y, 0xff);
	
	//#elif defined(__SSSE3__) // Slower
	
		//n128 m      = _mm_mul_ps(x, y);    // Multiply components together
		//n128 h1     = _mm_hadd_ps(m, m);   // Add once
		//n128 result = _mm_hadd_ps(h1, h1); // Add twice
	
	#else
	
		n128 multi  = _mm_mul_ps(x, y);         // Multiply components
		n128 shuf   = _hlslpp_perm_ps(multi, HLSLPP_SHUFFLE_MASK(1, 0, 3, 0));  // Move y into x, and w into z (ignore the rest)
		n128 add    = _mm_add_ps(shuf, multi);  // Contains x+y, _, z+w, _
		shuf        = _mm_movehl_ps(shuf, add); // Move (z + w) into x
		n128 result = _mm_add_ss(add, shuf);    // Contains x+y+z+w, _, _, _
	
	#endif

	return result;
}

hlslpp_inline bool _hlslpp_any1_ps(n128 x)
{
	return (_mm_movemask_ps(_mm_cmpeq_ps(x, _mm_setzero_ps())) & 0x1) != 0x1;
}

hlslpp_inline bool _hlslpp_any2_ps(n128 x)
{
	return (_mm_movemask_ps(_mm_cmpeq_ps(x, _mm_setzero_ps())) & 0x3) != 0x3;
}

hlslpp_inline bool _hlslpp_any3_ps(n128 x)
{
	return (_mm_movemask_ps(_mm_cmpeq_ps(x, _mm_setzero_ps())) & 0x7) != 0x7;
}

hlslpp_inline bool _hlslpp_any4_ps(n128 x)
{
	return _mm_movemask_ps(_mm_cmpeq_ps(x, _mm_setzero_ps())) != 0xf;
}

hlslpp_inline bool _hlslpp_all1_ps(n128 x)
{
	return (_mm_movemask_ps(_mm_cmpeq_ps(x, _mm_setzero_ps())) & 0x1) == 0;
}

hlslpp_inline bool _hlslpp_all2_ps(n128 x)
{
	return (_mm_movemask_ps(_mm_cmpeq_ps(x, _mm_setzero_ps())) & 0x3) == 0;
}

hlslpp_inline bool _hlslpp_all3_ps(n128 x)
{
	return (_mm_movemask_ps(_mm_cmpeq_ps(x, _mm_setzero_ps())) & 0x7) == 0;
}

hlslpp_inline bool _hlslpp_all4_ps(n128 x)
{
	return _mm_movemask_ps(_mm_cmpeq_ps(x, _mm_setzero_ps())) == 0;
}

//-----------------
// Float Store/Load
//-----------------

hlslpp_inline void _hlslpp_store1_ps(float* p, n128 x)
{
	_mm_store_ss(p, x);
}

hlslpp_inline void _hlslpp_store2_ps(float* p, n128 x)
{
	_mm_store_ss(p, x);
	_mm_store_ss(p + 1, _hlslpp_perm_ps(x, HLSLPP_SHUFFLE_MASK(1, 1, 1, 1)));
}

hlslpp_inline void _hlslpp_store3_ps(float* p, n128 x)
{
	_mm_store_ss(p, x);
	_mm_store_ss(p + 1, _hlslpp_perm_ps(x, HLSLPP_SHUFFLE_MASK(1, 1, 1, 1)));
	_mm_store_ss(p + 2, _hlslpp_perm_ps(x, HLSLPP_SHUFFLE_MASK(2, 2, 2, 2)));
}

hlslpp_inline void _hlslpp_store4_ps(float* p, n128 x)
{
	_mm_storeu_ps(p, x);
}

// Store first 3, store second 3, store last 3, stomping one of the previous values but making sure it's the same
hlslpp_inline void _hlslpp_store3x3_ps(float* p, n128 x0, n128 x1, n128 x2)
{
	_mm_storeu_ps(p, x0);
	_mm_storeu_ps(p + 3, x1);
	_mm_storeu_ps(p + 5, _hlslpp_blend_ps(_hlslpp_perm_ps(x1, HLSLPP_SHUFFLE_MASK(2, 2, 2, 2)), _hlslpp_perm_ps(x2, HLSLPP_SHUFFLE_MASK(3, 0, 1, 2)), HLSLPP_BLEND_MASK(1, 0, 0, 0)));
}

hlslpp_inline void _hlslpp_store4x4_ps(float* p, const n128& x0, const n128& x1, const n128& x2, const n128& x3)
{
	_mm_storeu_ps(p, x0);
	_mm_storeu_ps(p + 4, x1);
	_mm_storeu_ps(p + 8, x2);
	_mm_storeu_ps(p + 12, x3);
}

hlslpp_inline void _hlslpp_load1_ps(float* p, n128& x)
{
	x = _mm_load_ss(p);
}

// http://fastcpp.blogspot.com/2011/03/loading-3d-vector-into-sse-register.html
hlslpp_inline void _hlslpp_load2_ps(float* p, n128& x)
{
	x = _mm_castsi128_ps(_mm_loadl_epi64(reinterpret_cast<__m128i*>(p)));
}

hlslpp_inline void _hlslpp_load3_ps(float* p, n128& x)
{
	x = _mm_movelh_ps(_mm_castsi128_ps(_mm_loadl_epi64(reinterpret_cast<__m128i*>(p))), _mm_load_ss(p + 2));
}

hlslpp_inline void _hlslpp_load4_ps(float* p, n128& x)
{
	x = _mm_loadu_ps(p);
}

hlslpp_inline void _hlslpp_load3x3_ps(float* p, n128& x0, n128& x1, n128& x2)
{
	x0 = _mm_loadu_ps(p);
	x1 = _mm_loadu_ps(p + 3);
	x2 = _mm_loadu_ps(p + 6);
}

hlslpp_inline void _hlslpp_load4x4_ps(float* p, n128& x0, n128& x1, n128& x2, n128& x3)
{
	x0 = _mm_loadu_ps(p);
	x1 = _mm_loadu_ps(p + 4);
	x2 = _mm_loadu_ps(p + 8);
	x3 = _mm_loadu_ps(p + 12);
}

//----------
// Float 256
//----------

#if defined(__AVX__)

#define _hlslpp256_set1_ps(x)						_mm256_set1_ps((x))

#define _hlslpp256_set_ps(x, y, z, w, a, b, c, d)	_mm256_set_ps((d), (c), (b), (a), (w), (z), (y), (x))
#define _hlslpp256_setzero_ps()						_mm256_setzero_ps()

#define _hlslpp256_set128_ps(lo, hi)				_mm256_set_m128(hi, lo)

#define _hlslpp256_add_ps(x, y)						_mm256_add_ps((x), (y))
#define _hlslpp256_sub_ps(x, y)						_mm256_sub_ps((x), (y))
#define _hlslpp256_mul_ps(x, y)						_mm256_mul_ps((x), (y))
#define _hlslpp256_div_ps(x, y)						_mm256_div_ps((x), (y))

#define _hlslpp256_rcp_ps(x)						_mm256_rcp_ps((x))

// The following are alternatives but have been measured to be slower
// _mm_sub_ps(f4zero, x);			// Slowest
// _mm_mul_ps(f4minusOne, x);		// Slower
#define _hlslpp256_neg_ps(x)						_mm256_xor_ps((x), f4negativeMask)

#if defined(__FMA__)

#define _hlslpp256_madd_ps(x, y, z)					_mm256_fmadd_ps((x), (y), (z))
#define _hlslpp256_msub_ps(x, y, z)					_mm256_fmsub_ps((x), (y), (z))
#define _hlslpp256_subm_ps(x, y, z)					_mm256_fnmadd_ps((x), (y), (z))

#else

#define _hlslpp256_madd_ps(x, y, z)					_mm256_add_ps(_mm256_mul_ps((x), (y)), (z))
#define _hlslpp256_msub_ps(x, y, z)					_mm256_sub_ps(_mm256_mul_ps((x), (y)), (z))
#define _hlslpp256_subm_ps(x, y, z)					_mm256_sub_ps((x), _mm256_mul_ps((y), (z)))

#endif

// Reference http://www.liranuna.com/sse-intrinsics-optimizations-in-popular-compilers/
#define _hlslpp256_abs_ps(x)						_mm256_and_ps(f4absMask, (x))

#define _hlslpp256_sqrt_ps(x)						_mm256_sqrt_ps((x))
#define _hlslpp256_rsqrt_ps(x)						_mm256_rsqrt_ps((x))

#define _hlslpp256_cmpeq_ps(x, y)					_mm256_cmp_ps((x), (y), _CMP_EQ_OQ)
#define _hlslpp256_cmpneq_ps(x, y)					_mm256_cmp_ps((x), (y), _CMP_NEQ_OQ)

#define _hlslpp256_cmpgt_ps(x, y)					_mm256_cmp_ps((x), (y), _CMP_GT_OQ)
#define _hlslpp256_cmpge_ps(x, y)					_mm256_cmp_ps((x), (y), _CMP_GE_OQ)

#define _hlslpp256_cmplt_ps(x, y)					_mm256_cmp_ps((x), (y), _CMP_LT_OQ)
#define _hlslpp256_cmple_ps(x, y)					_mm256_cmp_ps((x), (y), _CMP_LE_OQ)

#define _hlslpp256_max_ps(x, y)						_mm256_max_ps((x), (y))
#define _hlslpp256_min_ps(x, y)						_mm256_min_ps((x), (y))

#define _hlslpp256_trunc_ps(x)						_mm256_round_ps((x), _MM_FROUND_TRUNC)
#define _hlslpp256_floor_ps(x)						_mm256_floor_ps((x))
#define _hlslpp256_ceil_ps(x)						_mm256_ceil_ps((x))


// _MM_FROUND_TO_NEAREST_INT to match fxc behavior
#define _hlslpp256_round_ps(x)						_mm256_round_ps((x), _MM_FROUND_TO_NEAREST_INT)

#define _hlslpp256_frac_ps(x)						_mm256_sub_ps((x), _mm256_floor_ps(x))

#define _hlslpp256_clamp_ps(x, minx, maxx)			_mm256_max_ps(_mm256_min_ps((x), (maxx)), (minx))
#define _hlslpp256_sat_ps(x)						_mm256_max_ps(_mm256_min_ps((x), f4_1), f4_0)

#define _hlslpp256_and_ps(x, y)						_mm256_and_ps((x), (y))
#define _hlslpp256_andnot_ps(x, y)					_mm256_andnot_ps((x), (y))
#define _hlslpp256_or_ps(x, y)						_mm256_or_ps((x), (y))
#define _hlslpp256_xor_ps(x, y)						_mm256_xor_ps((x), (y))

#define _hlslpp256_movehdup_ps(x)					_mm256_movehdup_ps((x))


template<int X, int Y, int Z, int W, int A, int B, int C, int D>
hlslpp_inline n256 permute(n256 x)
{
	// We need to statically assert for now until the permutes can cover more cases
	static_assert
		(
			X >= 0 && X < 8 && Y >= 0 && Y < 8 && Z >= 0 && Z < 8 && W >= 0 && W < 8 &&
			A >= 0 && A < 8 && B >= 0 && B < 8 && C >= 0 && C < 8 && D >= 0 && D < 8,
			"Invalid value for permute indices!");

	// Covers all the cases where XYZW belong to the first vector, and ABCD cover the second vector
	HLSLPP_CONSTEXPR_IF(X < 4 && Y < 4 && Z < 4 && W < 4 && A >= 4 && B >= 4 && C >= 4 && D >= 4)
	{
		return _mm256_permutevar_ps(x, _mm256_setr_epi32(X, Y, Z, W, A, B, C, D));
	}
	else HLSLPP_CONSTEXPR_IF(A < 4 && B < 4 && C < 4 && D < 4 && X >= 4 && Y >= 4 && Z >= 4 && W >= 4)
	{
	n256 swap = _mm256_permute2f128_ps(x, x, 0x3); // 0b00110000
	return _mm256_permutevar_ps(swap, _mm256_setr_epi32(X, Y, Z, W, A, B, C, D));
	}
	else
	{
	return _mm256_setzero_ps();
	}
}

template<>
hlslpp_inline n256 permute<0, 0, 0, 0, 0, 0, 0, 0>(n256 x)
{
	n256 t = _mm256_permute2f128_ps(x, x, 0);
	return _mm256_permute_ps(t, HLSLPP_SHUFFLE_MASK(0, 0, 0, 0));
}

template<>
hlslpp_inline n256 permute<0, 1, 2, 3, 4, 5, 6, 7>(n256 x)
{
	return x;
}

#define _hlslpp256_perm_ps(x, m0, m1, m2, m3, m4, m5, m6, m7)	permute<m0, m1, m2, m3, m4, m5, m6, m7>(x)
//#define _hlslpp256_shuffle_ps(x, y, mask)			_mm256_shuffle_ps((x), (y), (mask))

#define _hlslpp256_unpacklo_ps(x, y)				_mm256_unpacklo_ps(x, y)
#define _hlslpp256_unpackhi_ps(x, y)				_mm256_unpackhi_ps(x, y)

#define _hlslpp256_low_low_ps(x, y)					_mm256_permute2f128_ps((x), (y), 0x20)
#define _hlslpp256_low_high_ps(x, y)				_mm256_permute2f128_ps((x), (y), 0x30)
#define _hlslpp256_high_low_ps(x, y)				_mm256_permute2f128_ps((x), (y), 0x21)
#define _hlslpp256_high_high_ps(x, y)				_mm256_permute2f128_ps((x), (y), 0x31)

#define _hlslpp256_low_ps(x)						_mm256_castps256_ps128((x))
#define _hlslpp256_high_ps(x)						_mm256_extractf128_ps((x), 1)

// SSE2 alternative https://markplusplus.wordpress.com/2007/03/14/fast-sse-select-operation/
// _mm_xor_ps((x), _mm_and_ps(mask, _mm_xor_ps((y), (x))))
// Bit-select val1 and val2 based on the contents of the mask
#define _hlslpp256_sel_ps(x, y, mask)				_mm256_blendv_ps((x), (y), (mask))

#define _hlslpp256_blend_ps(x, y, mask)				_mm256_blend_ps((x), (y), (mask))

#define _hlslpp256_hadd_ps(x, y)					_mm256_hadd_ps((x), (y))

#define _hlslpp256_dot4_ps(x, y)					_mm256_dp_ps(x, y, 0xff)

hlslpp_inline void _hlslpp256_store4x4_ps(float* p, const n256& x0, const n256& x1)
{
	_mm256_storeu_ps(p, x0);
	_mm256_storeu_ps(p + 8, x1);
}

hlslpp_inline void _hlslpp256_load4x4_ps(float* p, n256& x0, n256& x1)
{
	x0 = _mm256_loadu_ps(p);
	x1 = _mm256_loadu_ps(p + 8);
}

#endif

//--------
// Integer
//--------

#define _hlslpp_set1_epi32(x)					_mm_set1_epi32((x))
#define _hlslpp_set_epi32(x, y, z, w)			_mm_set_epi32((w), (z), (y), (x))

#define _hlslpp_add_epi32(x, y)					_mm_add_epi32((x), (y))
#define _hlslpp_sub_epi32(x, y)					_mm_sub_epi32((x), (y))

// https://stackoverflow.com/questions/10500766/sse-multiplication-of-4-32-bit-integers
#define _hlslpp_mul_epi32(x, y)					_mm_mullo_epi32((x), (y))

#define _hlslpp_div_epi32(x, y)					_mm_castps_si128(_mm_div_ps(_mm_castsi128_ps(x), _mm_castsi128_ps(y)))

#if defined(__SSSE3__)
#define _hlslpp_neg_epi32(x)					_mm_sign_epi32((x), _mm_set1_epi32(-1))
#else
#define _hlslpp_neg_epi32(x)					_mm_add_epi32(_mm_xor_si128((x), i4fffMask), _mm_set1_epi32(1))
#endif

#define _hlslpp_madd_epi32(x, y, z)				_mm_add_epi32(_mm_mullo_epi32((x), (y)), (z))
#define _hlslpp_msub_epi32(x, y, z)				_mm_sub_epi32(_mm_mullo_epi32((x), (y)), (z))
#define _hlslpp_subm_epi32(x, y, z)				_mm_sub_epi32((x), _mm_mullo_epi32((y), (z)))

#define _hlslpp_abs_epi32(x)					_mm_and_si128(i4absMask, (x))

#define _hlslpp_cmpeq_epi32(x, y)				_mm_cmpeq_epi32((x), (y))
#define _hlslpp_cmpneq_epi32(x, y)				_mm_andnot_si128(_mm_cmpeq_epi32((x), (y)), i4fffMask)

#define _hlslpp_cmpgt_epi32(x, y)				_mm_cmpgt_epi32((x), (y))
#define _hlslpp_cmpge_epi32(x, y)				_mm_or_si128(_mm_cmpgt_epi32((x), (y)), _mm_cmpeq_epi32((x), (y)))

#define _hlslpp_cmplt_epi32(x, y)				_mm_cmplt_epi32((x), (y))
#define _hlslpp_cmple_epi32(x, y)				_mm_or_si128(_mm_cmplt_epi32((x), (y)), _mm_cmpeq_epi32((x), (y)))

#define _hlslpp_max_epi32(x, y)					_mm_max_epi32((x), (y))
#define _hlslpp_min_epi32(x, y)					_mm_min_epi32((x), (y))

#define _hlslpp_clamp_epi32(x, minx, maxx)		_mm_max_epi32(_mm_min_epi32((x), (maxx)), (minx))
#define _hlslpp_sat_epi32(x)					_mm_max_epi32(_mm_min_epi32((x), i4_1), i4_0)

#define _hlslpp_and_si128(x, y)					_mm_and_si128((x), (y))
#define _hlslpp_or_si128(x, y)					_mm_or_si128((x), (y))

// https://stackoverflow.com/questions/13153584/mm-shuffle-ps-equivalent-for-integer-vectors-m128i
#define _hlslpp_perm_epi32(x, mask)				_mm_shuffle_epi32((x), (mask))
#define _hlslpp_shuffle_epi32(x, y, mask)		_mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(x), _mm_castsi128_ps(y), (mask)))

#if defined(__AVX2__)

#define _hlslpp_blend_epi32(x, y, mask)			_mm_blend_epi32((x), (y), mask)

#else

// Reshuffle the mask because we use _mm_blend_epi16 as that's what's available in SSE4.1 
#define _hlslpp_blend_epi32(x, y, mask)			_mm_blend_epi16((x), (y), ((mask & 1) * 3) | ((((mask >> 1) & 1) * 3) << 2) | ((((mask >> 2) & 1) * 3) << 4) | ((((mask >> 3) & 1) * 3) << 6))

#endif

#define _hlslpp_castps_si128(x)					_mm_castps_si128((x))
#define _hlslpp_castsi128_ps(x)					_mm_castsi128_ps((x))

#define _hlslpp_cvtepi32_ps(x)					_mm_cvtepi32_ps((x))
#define _hlslpp_cvtps_epi32(x)					_mm_cvtps_epi32((x))

#define _hlslpp_slli_epi32(x, y)				_mm_slli_epi32((x), (y))
#define _hlslpp_srli_epi32(x, y)				_mm_srli_epi32((x), (y))

#if defined(__AVX2__)

#define _hlslpp_sllv_epi32(x, y)				_mm_sllv_epi32((x), (y))
#define _hlslpp_srlv_epi32(x, y)				_mm_srlv_epi32((x), (y))

#else

inline n128i _hlslpp_sllv_epi32(n128i x, n128i count)
{
	n128i count1 = _hlslpp_perm_epi32(count, HLSLPP_SHUFFLE_MASK(1, 0, 0, 0));
	n128i count2 = _hlslpp_perm_epi32(count, HLSLPP_SHUFFLE_MASK(2, 0, 0, 0));
	n128i count3 = _hlslpp_perm_epi32(count, HLSLPP_SHUFFLE_MASK(3, 0, 0, 0));

	n128i ffMask = _mm_setr_epi32(0xffffffff, 0, 0, 0); // The shift instruction considers 64 bits so we need to mask out everything else

	n128i imask0 = _mm_and_si128(count, ffMask);
	n128i imask1 = _mm_and_si128(count1, ffMask);
	n128i imask2 = _mm_and_si128(count2, ffMask);
	n128i imask3 = _mm_and_si128(count3, ffMask);

	n128i shift0 = _mm_sll_epi32(x, imask0);
	n128i shift1 = _mm_sll_epi32(x, imask1);
	n128i shift2 = _mm_sll_epi32(x, imask2);
	n128i shift3 = _mm_sll_epi32(x, imask3);

	n128i blend0 = _hlslpp_blend_epi32(shift0, shift1, HLSLPP_BLEND_MASK(1, 0, 0, 0));
	n128i blend1 = _hlslpp_blend_epi32(shift2, shift3, HLSLPP_BLEND_MASK(0, 0, 1, 0));

	return _hlslpp_blend_epi32(blend0, blend1, HLSLPP_BLEND_MASK(1, 1, 0, 0));
}

inline n128i _hlslpp_srlv_epi32(n128i x, n128i count)
{
	n128i count1 = _hlslpp_perm_epi32(count, HLSLPP_SHUFFLE_MASK(1, 0, 0, 0));
	n128i count2 = _hlslpp_perm_epi32(count, HLSLPP_SHUFFLE_MASK(2, 0, 0, 0));
	n128i count3 = _hlslpp_perm_epi32(count, HLSLPP_SHUFFLE_MASK(3, 0, 0, 0));

	n128i ffMask = _mm_setr_epi32(0xffffffff, 0, 0, 0); // The shift instruction considers 64 bits so we need to mask out everything else

	n128i imask0 = _mm_and_si128(count, ffMask);
	n128i imask1 = _mm_and_si128(count1, ffMask);
	n128i imask2 = _mm_and_si128(count2, ffMask);
	n128i imask3 = _mm_and_si128(count3, ffMask);

	n128i shift0 = _mm_srl_epi32(x, imask0);
	n128i shift1 = _mm_srl_epi32(x, imask1);
	n128i shift2 = _mm_srl_epi32(x, imask2);
	n128i shift3 = _mm_srl_epi32(x, imask3);

	n128i blend0 = _hlslpp_blend_epi32(shift0, shift1, HLSLPP_BLEND_MASK(1, 0, 0, 0));
	n128i blend1 = _hlslpp_blend_epi32(shift2, shift3, HLSLPP_BLEND_MASK(0, 0, 1, 0));

	return _hlslpp_blend_epi32(blend0, blend1, HLSLPP_BLEND_MASK(1, 1, 0, 0));
}

#endif

//------------
// Integer 256
//------------

#if defined(__AVX__)

#define _hlslpp256_set_epi32(x, y, z, w, a, b, c, d)	_mm256_set_epi32(d, c, b, a, w, z, y, x)

#define _hlslpp256_castps_si256(x)						_mm256_castps_si256((x))
#define _hlslpp256_castsi256_ps(x)						_mm256_castsi256_ps((x))

#endif

//-------
// Double
//-------

#define _hlslpp_set1_pd(x)						_mm_set1_pd((x))
#define _hlslpp_set_pd(x, y)					_mm_set_pd((y), (x))
#define _hlslpp_setzero_pd()					_mm_setzero_pd()

#define _hlslpp_add_pd(x, y)					_mm_add_pd((x), (y))
#define _hlslpp_sub_pd(x, y)					_mm_sub_pd((x), (y))
#define _hlslpp_mul_pd(x, y)					_mm_mul_pd((x), (y))
#define _hlslpp_div_pd(x, y)					_mm_div_pd((x), (y))

#define _hlslpp_rcp_pd(x)						_mm_div_pd(d2_1, (x))

#define _hlslpp_neg_pd(x)						_mm_xor_pd((x), d2negativeMask)

#if defined(__FMA__)

#define _hlslpp_madd_pd(x, y, z)				_mm_fmadd_pd((x), (y), (z))
#define _hlslpp_msub_pd(x, y, z)				_mm_fmsub_pd((x), (y), (z))
#define _hlslpp_subm_pd(x, y, z)				_mm_fnmadd_pd((x), (y), (z)))

#else

#define _hlslpp_madd_pd(x, y, z)				_mm_add_pd(_mm_mul_pd((x), (y)), (z))
#define _hlslpp_msub_pd(x, y, z)				_mm_sub_pd(_mm_mul_pd((x), (y)), (z))
#define _hlslpp_subm_pd(x, y, z)				_mm_sub_pd((x), _mm_mul_pd((y), (z)))

#endif

// Reference http://www.liranuna.com/sse-intrinsics-optimizations-in-popular-compilers/
#define _hlslpp_abs_pd(x)						_mm_and_pd(d2absMask, (x))

#define _hlslpp_sqrt_pd(x)						_mm_sqrt_pd((x))
#define _hlslpp_rsqrt_pd(x)						_mm_div_pd(d2_1, _mm_sqrt_pd((x)))

#define _hlslpp_cmpeq_pd(x, y)					_mm_cmpeq_pd((x), (y))
#define _hlslpp_cmpneq_pd(x, y)					_mm_cmpneq_pd((x), (y))

#define _hlslpp_cmpgt_pd(x, y)					_mm_cmpgt_pd((x), (y))
#define _hlslpp_cmpge_pd(x, y)					_mm_cmpge_pd((x), (y))

#define _hlslpp_cmplt_pd(x, y)					_mm_cmplt_pd((x), (y))
#define _hlslpp_cmple_pd(x, y)					_mm_cmple_pd((x), (y))

#define _hlslpp_max_pd(x, y)					_mm_max_pd((x), (y))
#define _hlslpp_min_pd(x, y)					_mm_min_pd((x), (y))

#define _hlslpp_trunc_pd(x)						_mm_round_pd((x), _MM_FROUND_TRUNC)
#define _hlslpp_floor_pd(x)						_mm_floor_pd((x))
#define _hlslpp_ceil_pd(x)						_mm_ceil_pd((x))

// _MM_FROUND_TO_NEAREST_INT to match fxc behavior
#define _hlslpp_round_pd(x)						_mm_round_pd((x), _MM_FROUND_TO_NEAREST_INT)

#define _hlslpp_frac_pd(x)						_mm_sub_pd((x), _mm_floor_pd(x))

#define _hlslpp_clamp_pd(x, minx, maxx)			_mm_max_pd(_mm_min_pd((x), (maxx)), (minx))
#define _hlslpp_sat_pd(x)						_mm_max_pd(_mm_min_pd((x), d2_1), _mm_setzero_pd())

#define _hlslpp_and_pd(x, y)					_mm_and_pd((x), (y))
#define _hlslpp_andnot_pd(x, y)					_mm_andnot_pd((x), (y))
#define _hlslpp_or_pd(x, y)						_mm_or_pd((x), (y))
#define _hlslpp_xor_pd(x, y)					_mm_xor_pd((x), (y))

#define _hlslpp_perm_pd(x, mask)				_mm_shuffle_pd((x), (x), (mask))
#define _hlslpp_shuffle_pd(x, y, mask)			_mm_shuffle_pd((x), (y), (mask))

// SSE2 alternative https://markplusplus.wordpress.com/2007/03/14/fast-sse-select-operation/
// _mm_xor_ps((x), _mm_and_ps(mask, _mm_xor_ps((y), (x))))
// Bit-select val1 and val2 based on the contents of the mask
#define _hlslpp_sel_pd(x, y, mask)				_mm_blendv_pd((x), (y), (mask))

#define _hlslpp_blend_pd(x, y, mask)			_mm_blend_pd((x), (y), (mask))

hlslpp_inline bool _hlslpp_any1_pd(n128d x)
{
	return (_mm_movemask_pd(_mm_cmpeq_pd(x, _mm_setzero_pd())) & 0x1) != 0x1;
}

hlslpp_inline bool _hlslpp_any2_pd(n128d x)
{
	return (_mm_movemask_pd(_mm_cmpeq_pd(x, _mm_setzero_pd())) & 0x3) != 0x3;
}

hlslpp_inline bool _hlslpp_any3_pd(n128d x0, n128d x1)
{
	return ((_mm_movemask_pd(_mm_cmpeq_pd(x0, _mm_setzero_pd())) & 0x3) != 0x3) || ((_mm_movemask_pd(_mm_cmpeq_pd(x1, _mm_setzero_pd())) & 0x1) != 0x1);
}

hlslpp_inline bool _hlslpp_any4_pd(n128d x0, n128d x1)
{
	return (_mm_movemask_pd(_mm_cmpeq_pd(x0, _mm_setzero_pd())) != 0xf) || (_mm_movemask_pd(_mm_cmpeq_pd(x1, _mm_setzero_pd())) != 0xf);
}

hlslpp_inline bool _hlslpp_all1_pd(n128d x)
{
	return (_mm_movemask_pd(_mm_cmpeq_pd(x, _mm_setzero_pd())) & 0x1) == 0;
}

hlslpp_inline bool _hlslpp_all2_pd(n128d x)
{
	return (_mm_movemask_pd(_mm_cmpeq_pd(x, _mm_setzero_pd())) & 0x3) == 0;
}

hlslpp_inline bool _hlslpp_all3_pd(n128d x0, n128d x1)
{
	return ((_mm_movemask_pd(_mm_cmpeq_pd(x0, _mm_setzero_pd())) & 0x3) == 0) && ((_mm_movemask_pd(_mm_cmpeq_pd(x1, _mm_setzero_pd())) & 0x1) == 0);
}

hlslpp_inline bool _hlslpp_all4_pd(n128d x0, n128d x1)
{
	return (_mm_movemask_pd(_mm_cmpeq_pd(x0, _mm_setzero_pd())) == 0) && (_mm_movemask_pd(_mm_cmpeq_pd(x1, _mm_setzero_pd())) == 0);
}

//------------------
// Double Store/Load
//------------------

hlslpp_inline void _hlslpp_store1_pd(double* p, n128d x)
{
	_mm_storel_pd(p, x);
}

hlslpp_inline void _hlslpp_store2_pd(double* p, n128d x)
{
	_mm_storeu_pd(p, x);
}

hlslpp_inline void _hlslpp_store3_pd(double* p, n128d x0, n128d x1)
{
	_mm_storeu_pd(p, x0);
	_mm_storel_pd(p + 2, x1);
}

hlslpp_inline void _hlslpp_store4_pd(double* p, n128d x0, n128d x1)
{
	_mm_storeu_pd(p, x0);
	_mm_storeu_pd(p + 2, x1);
}