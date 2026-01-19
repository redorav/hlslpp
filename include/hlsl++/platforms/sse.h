#pragma once

#if defined(__clang__) || defined(__GNUG__)

	#include <x86intrin.h>

#elif defined(_MSC_VER)

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

	#endif

	#if defined(__SSE4_1__)

		#if !defined(__SSSE3__)
		#define __SSSE3__ 1
		#endif

	#endif

	// https://github.com/p12tic/libsimdpp/issues/33
	#if defined(HLSLPP_MODULE_DECLARATION)
	import <intrin.h>;
	#else	
	#include <intrin.h>
	#endif

	//#include "hlsl++_sse_intrin.h"

#endif

#define _HLSLPP_ROUND_MASK        0x6000
#define _HLSLPP_ROUND_NEAREST     0x0000
#define _HLSLPP_ROUND_DOWN        0x2000
#define _HLSLPP_ROUND_UP          0x4000
#define _HLSLPP_ROUND_TOWARD_ZERO 0x6000

#define _HLSLPP_FLUSH_ZERO_MASK   0x8000
#define _HLSLPP_FLUSH_ZERO_ON     0x8000
#define _HLSLPP_FLUSH_ZERO_OFF    0x0000

#define HLSLPP_DOUBLE

// All available in SSE/SSE2
typedef __m128  n128;
typedef __m128i n128i;
typedef __m128i n128u;
typedef __m128d n128d;

#if defined(__AVX__)

// Whether the float8 type is available
#define HLSLPP_FLOAT8

// Whether this configuration has a 256-wide register
#define HLSLPP_SIMD_REGISTER_256

typedef __m256  n256;
typedef __m256d n256d;
typedef __m256i n256i;

#endif

#if defined(__AVX512F__)

#define HLSLPP_SIMD_REGISTER_512

typedef __m512  n512;
typedef __m512d n512d;
typedef __m512i n512i;

#endif

//------
// Float
//------

#define _hlslpp_set1_ps(x)						_mm_set_ps1((x))
#define _hlslpp_set_ps(x, y, z, w)				_mm_set_ps((w), (z), (y), (x))
#define _hlslpp_setzero_ps()					_mm_setzero_ps()

#define _hlslpp_add_ps(x, y)					_mm_add_ps((x), (y))
#define _hlslpp_sub_ps(x, y)					_mm_sub_ps((x), (y))
#define _hlslpp_mul_ps(x, y)					_mm_mul_ps((x), (y))
#define _hlslpp_div_ps(x, y)					_mm_div_ps((x), (y))

#define _hlslpp_rcp_ps(x)						_mm_rcp_ps((x))

// The following are alternatives but have been measured to be slower
// _mm_sub_ps(f4_0, x);			// Slowest
// _mm_mul_ps(f4_minus1, x);	// Slower
#define _hlslpp_neg_ps(x)						_mm_xor_ps((x), _mm_castsi128_ps(_mm_set1_epi32(0x80000000u)))

// https://wunkolo.github.io/post/2022/10/vfixupimm-signum/
#if defined(__AVX512F__) && defined(__AVX512VL__)
#define _hlslpp_sign_ps(x)						_mm_fixupimm_ps((x), (x), _mm_set1_epi32(0xa9a90a00), 0)
#endif

#if defined(__FMA__)

#define _hlslpp_madd_ps(x, y, z)				_mm_fmadd_ps((x), (y), (z)) // x * y + z
#define _hlslpp_msub_ps(x, y, z)				_mm_fmsub_ps((x), (y), (z)) // x * y - z
#define _hlslpp_subm_ps(x, y, z)				_mm_fnmadd_ps((y), (z), (x)) // x - y * z

#else

#define _hlslpp_madd_ps(x, y, z)				_mm_add_ps(_mm_mul_ps((x), (y)), (z)) // x * y + z
#define _hlslpp_msub_ps(x, y, z)				_mm_sub_ps(_mm_mul_ps((x), (y)), (z)) // x * y - z
#define _hlslpp_subm_ps(x, y, z)				_mm_sub_ps((x), _mm_mul_ps((y), (z))) // x - y * z

#endif

// Reference http://www.liranuna.com/sse-intrinsics-optimizations-in-popular-compilers/
#define _hlslpp_abs_ps(x)						_mm_and_ps(_mm_castsi128_ps(_mm_set1_epi32(0x7fffffff)), (x))

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

// SSE2 alternative https://markplusplus.wordpress.com/2007/03/14/fast-sse-select-operation/
// Bit-select val1 and val2 based on the contents of the mask
#if defined(__SSE4_1__)

#define _hlslpp_sel_ps(x, y, mask)				_mm_blendv_ps((x), (y), (mask))

#define _hlslpp_blend_ps(x, y, mask)			_mm_blend_ps((x), (y), (mask))

#else

#define _hlslpp_sel_ps(x, y, mask)				_mm_xor_ps((x), _mm_and_ps((mask), _mm_xor_ps((y), (x))))

hlslpp_inline n128 _hlslpp_blend_ps(n128 x, n128 y, int mask)
{
	n128 mask128 = _mm_castsi128_ps(_mm_set_epi32(int(((mask >> 3) & 1) * 0xffffffff), int(((mask >> 2) & 1) * 0xffffffff), int(((mask >> 1) & 1) * 0xffffffff), int((mask & 1) * 0xffffffff)));
	return _hlslpp_sel_ps(x, y, mask128);
}

#endif

#if defined(__SSE4_1__)

#define _hlslpp_trunc_ps(x)						_mm_round_ps((x), _MM_FROUND_TRUNC)
#define _hlslpp_floor_ps(x)						_mm_round_ps((x), _MM_FROUND_FLOOR)
#define _hlslpp_ceil_ps(x)						_mm_round_ps((x), _MM_FROUND_CEIL)

// _MM_FROUND_TO_NEAREST_INT to match fxc behavior
#define _hlslpp_round_ps(x)						_mm_round_ps((x), _MM_FROUND_TO_NEAREST_INT)

#else

#define _hlslpp_trunc_ps(x)						_mm_cvtepi32_ps(_mm_cvttps_epi32(x))

// http://dss.stephanierct.com/DevBlog/?p=8

hlslpp_inline __m128 _hlslpp_floor_ps(__m128 x)
{
	__m128 ones = _mm_set_ps1(1.0f);
	__m128 trnc = _mm_cvtepi32_ps(_mm_cvttps_epi32(x)); // Truncate 
	__m128 tgtx = _mm_cmpgt_ps(trnc, x);
	return _mm_sub_ps(trnc, _mm_and_ps(tgtx, ones)); // Subtract one if trnc greater than x
}

hlslpp_inline __m128 _hlslpp_ceil_ps(__m128 x)
{
	__m128 ones = _mm_set_ps1(1.0f);
	__m128 trnc = _mm_cvtepi32_ps(_mm_cvttps_epi32(x)); // Truncate 
	__m128 tgtx = _mm_cmplt_ps(trnc, x);
	return _mm_add_ps(trnc, _mm_and_ps(tgtx, ones)); // Add one if trnc greater than x
}

hlslpp_inline __m128 _hlslpp_round_ps(__m128 x)
{
	__m128 near_2    = _mm_set_ps1(1.99999988f);
	__m128 trnc      = _mm_cvtepi32_ps(_mm_cvttps_epi32(x)); // Truncate 
	__m128 frac      = _mm_sub_ps(x, trnc);                  // Get fractional part
	__m128 frac2     = _mm_mul_ps(frac, near_2);             // Fractional part by near 2
	__m128 frac2trnc = _mm_cvtepi32_ps(_mm_cvttps_epi32(frac2));
	__m128 result    = _mm_add_ps(trnc, frac2trnc);
	return result;
}

#endif

#define _hlslpp_frac_ps(x)						_mm_sub_ps((x), _hlslpp_floor_ps(x))

#define _hlslpp_clamp_ps(x, minx, maxx)			_mm_max_ps(_mm_min_ps((x), (maxx)), (minx))
#define _hlslpp_sat_ps(x)						_mm_max_ps(_mm_min_ps((x), _mm_set1_ps(1.0f)), _mm_setzero_ps())

#define _hlslpp_and_ps(x, y)					_mm_and_ps((x), (y))
#define _hlslpp_andnot_ps(x, y)					_mm_andnot_ps((x), (y))
#define _hlslpp_not_ps(x)						_mm_andnot_ps((x), f4_fff)
#define _hlslpp_or_ps(x, y)						_mm_or_ps((x), (y))
#define _hlslpp_xor_ps(x, y)					_mm_xor_ps((x), (y))

// Equivalent to shuffle(x, y, X, Y, X, Y)
#define _hlslpp_movelh_ps(x, y)					_mm_movelh_ps((x), (y))

// Equivalent to shuffle(y, x, Z, W, Z, W)
#define _hlslpp_movehl_ps(x, y)					_mm_movehl_ps((x), (y))

// Equivalent to shuffle(x, x, Y, Y, W, W)
#define _hlslpp_movehdup_ps(x)					_mm_movehdup_ps((x))

namespace hlslpp
{
	template<int X, int Y, int Z, int W>
	hlslpp_inline __m128 permute(__m128 x)
	{
#if defined(__AVX__)
		return _mm_permute_ps((x), HLSLPP_SHUFFLE_MASK(X, Y, Z, W));
		
#else
		return _mm_shuffle_ps(x, x, HLSLPP_SHUFFLE_MASK(X, Y, Z, W));
#endif
	}

	template<>
	hlslpp_inline __m128 permute<0, 1, 2, 3>(__m128 x)
	{
		return x;
	}
};

#define _hlslpp_perm_ps(x, X, Y, Z, W) (hlslpp::permute<X, Y, Z, W>(x))

// Follows the semantics of _mm_shuffle_ps, in that it selects two components from x and two from y
#define _hlslpp_shuffle_ps(x, y, X, Y, A, B)	_mm_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(X, Y, A, B))

// Equivalent to shuffle(x, y, X, X, Y, Y)
#define _hlslpp_unpacklo_ps(x, y)				_mm_unpacklo_ps((x), (y))

// Equivalent to shuffle(x, y, Z, Z, W, W)
#define _hlslpp_unpackhi_ps(x, y)				_mm_unpackhi_ps((x), (y))

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
	
		n128 mul    = _mm_mul_ps(x, y);                  // Multiply components
		n128 shuf   = _hlslpp_perm_ps(mul, 1, 0, 3, 0);  // Move y into x, and w into z (ignore the rest)
		n128 add    = _mm_add_ps(shuf, mul);             // Contains x+y, _, z+w, _
		shuf        = _mm_movehl_ps(shuf, add);          // Move (z + w) into x
		n128 result = _mm_add_ss(add, shuf);             // Contains x+y+z+w, _, _, _
	
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

hlslpp_inline void _hlslpp_store1_ps(float* dst, n128 src)
{
	_mm_store_ss(dst, src);
}

hlslpp_inline void _hlslpp_store2_ps(float* dst, n128 src)
{
	_mm_storel_epi64((__m128i*)dst, *(n128i*)&src);
}

hlslpp_inline void _hlslpp_store3_ps(float* dst, n128 src)
{
	_mm_storel_epi64((__m128i*)dst, *(n128i*)&src);
	_mm_store_ss(dst + 2, _hlslpp_perm_ps(src, 2, 2, 2, 2));
}

hlslpp_inline void _hlslpp_store4_ps(float* dst, n128 src)
{
	_mm_storeu_ps(dst, src);
}

// Store first 3, store second 3, store last 2 and then the last one
// We need to do it this way to avoid stomping memory outside the provided buffer
hlslpp_inline void _hlslpp_store3x3_ps(float* dst, n128 src0, n128 src1, n128 src2)
{
	_mm_storeu_ps(dst, src0);
	_mm_storeu_ps(dst + 3, src1);
	_mm_storel_epi64((__m128i*)(dst + 6), *(n128i*)&src2);
	_mm_store_ss(dst + 8, _hlslpp_perm_ps(src2, 2, 2, 2, 2));
}

hlslpp_inline void _hlslpp_store4x4_ps(float* dst, const n128& src0, const n128& src1, const n128& src2, const n128& src3)
{
	_mm_storeu_ps(dst, src0);
	_mm_storeu_ps(dst + 4, src1);
	_mm_storeu_ps(dst + 8, src2);
	_mm_storeu_ps(dst + 12, src3);
}

hlslpp_inline void _hlslpp_load1_ps(n128& dst, const float* src)
{
	dst = _mm_load_ss(src);
}

// http://fastcpp.blogspot.com/2011/03/loading-3d-vector-into-sse-register.html
hlslpp_inline void _hlslpp_load2_ps(n128& dst, const float* src)
{
	dst = _mm_castsi128_ps(_mm_loadl_epi64((__m128i*)src));
}

hlslpp_inline void _hlslpp_load3_ps(n128& dst, const float* src)
{
	dst = _mm_movelh_ps(_mm_castsi128_ps(_mm_loadl_epi64((__m128i*)src)), _mm_load_ss(src + 2));
}

hlslpp_inline void _hlslpp_load4_ps(n128& dst, const float* src)
{
	dst = _mm_loadu_ps(src);
}

hlslpp_inline void _hlslpp_load3x3_ps(n128& dst0, n128& dst1, n128& dst2, const float* src)
{
	dst0 = _mm_loadu_ps(src);
	dst1 = _mm_loadu_ps(src + 3);
	dst2 = _mm_loadu_ps(src + 6);
}

hlslpp_inline void _hlslpp_load4x4_ps(n128& dst0, n128& dst1, n128& dst2, n128& dst3, const float* src)
{
	dst0 = _mm_loadu_ps(src);
	dst1 = _mm_loadu_ps(src + 4);
	dst2 = _mm_loadu_ps(src + 8);
	dst3 = _mm_loadu_ps(src + 12);
}

//----------
// Float 256
//----------

#if defined(HLSLPP_SIMD_REGISTER_256)

#define _hlslpp256_set1_ps(x)						_mm256_set1_ps((x))

#define _hlslpp256_set_ps(x, y, z, w, a, b, c, d)	_mm256_set_ps((d), (c), (b), (a), (w), (z), (y), (x))
#define _hlslpp256_setzero_ps()						_mm256_setzero_ps()

#define _hlslpp256_set128_ps(lo, hi)				_mm256_insertf128_ps(_mm256_castps128_ps256(lo), (hi), 0x1)

#define _hlslpp256_add_ps(x, y)						_mm256_add_ps((x), (y))
#define _hlslpp256_sub_ps(x, y)						_mm256_sub_ps((x), (y))
#define _hlslpp256_mul_ps(x, y)						_mm256_mul_ps((x), (y))
#define _hlslpp256_div_ps(x, y)						_mm256_div_ps((x), (y))

#define _hlslpp256_rcp_ps(x)						_mm256_rcp_ps((x))

// The following are alternatives but have been measured to be slower
// _mm_sub_ps(f4zero, x);			// Slowest
// _mm_mul_ps(f4minusOne, x);		// Slower
#define _hlslpp256_neg_ps(x)						_mm256_xor_ps((x), f8negativeMask)

// https://wunkolo.github.io/post/2022/10/vfixupimm-signum/
#if defined(__AVX512F__) && defined(__AVX512VL__)
#define _hlslpp256_sign_ps(x)						_mm256_fixupimm_ps((x), (x), _mm256_set1_epi32(0xa9a90a00), 0)
#endif

#if defined(__FMA__)

#define _hlslpp256_madd_ps(x, y, z)					_mm256_fmadd_ps((x), (y), (z)) // x * y + z
#define _hlslpp256_msub_ps(x, y, z)					_mm256_fmsub_ps((x), (y), (z)) // x * y - z
#define _hlslpp256_subm_ps(x, y, z)					_mm256_fnmadd_ps((y), (z), (x)) // x - y * z

#else

#define _hlslpp256_madd_ps(x, y, z)					_mm256_add_ps(_mm256_mul_ps((x), (y)), (z)) // x * y + z
#define _hlslpp256_msub_ps(x, y, z)					_mm256_sub_ps(_mm256_mul_ps((x), (y)), (z)) // x * y - z
#define _hlslpp256_subm_ps(x, y, z)					_mm256_sub_ps((x), _mm256_mul_ps((y), (z))) // x - y * z

#endif

// Reference http://www.liranuna.com/sse-intrinsics-optimizations-in-popular-compilers/
#define _hlslpp256_abs_ps(x)						_mm256_and_ps(f8absMask, (x))

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
#define _hlslpp256_floor_ps(x)						_mm256_round_ps((x), _MM_FROUND_FLOOR)
#define _hlslpp256_ceil_ps(x)						_mm256_round_ps((x), _MM_FROUND_CEIL)


// _MM_FROUND_TO_NEAREST_INT to match fxc behavior
#define _hlslpp256_round_ps(x)						_mm256_round_ps((x), _MM_FROUND_TO_NEAREST_INT)

#define _hlslpp256_frac_ps(x)						_mm256_sub_ps((x), _hlslpp256_floor_ps(x))

#define _hlslpp256_clamp_ps(x, minx, maxx)			_mm256_max_ps(_mm256_min_ps((x), (maxx)), (minx))
#define _hlslpp256_sat_ps(x)						_mm256_max_ps(_mm256_min_ps((x), f8_1), f8_0)

#define _hlslpp256_and_ps(x, y)						_mm256_and_ps((x), (y))
#define _hlslpp256_andnot_ps(x, y)					_mm256_andnot_ps((x), (y))
#define _hlslpp256_not_ps(x, y)						_mm256_andnot_ps((x), f8_fff)
#define _hlslpp256_or_ps(x, y)						_mm256_or_ps((x), (y))
#define _hlslpp256_xor_ps(x, y)						_mm256_xor_ps((x), (y))

#define _hlslpp256_movehdup_ps(x)					_mm256_movehdup_ps((x))

// We could make these functions use SFINAE and other template magic to select the appropriate implementation, but it makes it really hard to read
// and debug. On older platforms without if constexpr the debug versions will incur in some overhead, on release it optimizes properly since these
// are all compile time constants
template<int X, int Y, int Z, int W, int A, int B, int C, int D>
hlslpp_inline n256 permute_float(n256 x)
{
	static_assert
	(
		X >= 0 && X < 8 && Y >= 0 && Y < 8 && Z >= 0 && Z < 8 && W >= 0 && W < 8 &&
		A >= 0 && A < 8 && B >= 0 && B < 8 && C >= 0 && C < 8 && D >= 0 && D < 8,
		"Invalid value for permute indices"
	);

	static_assert
	(
		(X < 4 && Y < 4 && Z < 4 && W < 4 && A >= 4 && B >= 4 && C >= 4 && D >= 4) ||
		(A < 4 && B < 4 && C < 4 && D < 4 && X >= 4 && Y >= 4 && Z >= 4 && W >= 4),
		"Permute combination not supported"
	);

	// Covers cases where XYZW belong to the first vector, and ABCD cover the second vector
	hlslpp_constexpr_if(X < 4 && Y < 4 && Z < 4 && W < 4 && A >= 4 && B >= 4 && C >= 4 && D >= 4)
	{
		hlslpp_constexpr_if(X == (A - 4) && Y == (B - 4) && Z == (C - 4) && W == (D - 4))
		{
			HLSLPP_WARNING_INVALID_SHUFFLE_BEGIN
			return _mm256_permute_ps(x, HLSLPP_SHUFFLE_MASK(X, Y, Z, W));
			HLSLPP_WARNING_INVALID_SHUFFLE_END
		}
		else
		{
			return _mm256_permutevar_ps(x, _mm256_setr_epi32(X, Y, Z, W, A, B, C, D));
		}
	}
	// Covers cases where ABCD belong to the first vector, and XYZW cover the second vector
	else hlslpp_constexpr_if(A < 4 && B < 4 && C < 4 && D < 4 && X >= 4 && Y >= 4 && Z >= 4 && W >= 4)
	{
		n256 swap = _mm256_permute2f128_ps(x, x, 0x3); // 0b00110000
	
		hlslpp_constexpr_if(A == (X - 4) && B == (Y - 4) && C == (Z - 4) && D == (W - 4))
		{
			HLSLPP_WARNING_INVALID_SHUFFLE_BEGIN
			return _mm256_permute_ps(x, HLSLPP_SHUFFLE_MASK(A, B, C, D));
			HLSLPP_WARNING_INVALID_SHUFFLE_END
		}
		else
		{
			return _mm256_permutevar_ps(swap, _mm256_setr_epi32(X, Y, Z, W, A, B, C, D));
		}
	}
	else
	{
		return _mm256_setzero_ps();
	}
}

template<>
hlslpp_inline n256 permute_float<0, 0, 0, 0, 0, 0, 0, 0>(n256 x)
{
	n256 t = _mm256_permute2f128_ps(x, x, 0);
	return _mm256_permute_ps(t, HLSLPP_SHUFFLE_MASK(0, 0, 0, 0));
}

template<>
hlslpp_inline n256 permute_float<0, 1, 2, 3, 4, 5, 6, 7>(n256 x)
{
	return x;
}

#define _hlslpp256_perm_ps(x, X, Y, Z, W, A, B, C, D)	permute_float<X, Y, Z, W, A, B, C, D>(x)

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

hlslpp_inline n256 _hlslpp256_reduce_add_ps(n256 x)
{
	n128 add1 = _mm_add_ps(_hlslpp256_low_ps(x), _hlslpp256_high_ps(x));
	n128 shuf = _hlslpp_perm_ps(add1, 1, 0, 3, 0);
	n128 add2 = _mm_add_ps(shuf, add1);
	shuf = _mm_movehl_ps(shuf, add2);
	return _mm256_castps128_ps256(_mm_add_ps(add2, shuf));
}

hlslpp_inline n256 _hlslpp256_dot8_ps(n256 x, n256 y)
{
	n256 dot4 = _mm256_dp_ps(x, y, 0xff);
	n256 reversedot4 = _mm256_permute2f128_ps(dot4, dot4, 0x3);
	return _mm256_add_ps(dot4, reversedot4);
}

hlslpp_inline bool _hlslpp256_any8_ps(n256 x)
{
	return _mm256_movemask_ps(_mm256_cmp_ps(x, _mm256_setzero_ps(), _CMP_EQ_OQ)) != 0xff;
}

hlslpp_inline bool _hlslpp256_all8_ps(n256 x)
{
	return _mm256_movemask_ps(_mm256_cmp_ps(x, _mm256_setzero_ps(), _CMP_EQ_OQ)) == 0;
}

hlslpp_inline void _hlslpp256_store8_ps(float* dst, const n256& src)
{
	_mm256_storeu_ps(dst, src);
}

hlslpp_inline void _hlslpp256_load8_ps(n256& x, const float* src)
{
	x = _mm256_loadu_ps(src);
}

hlslpp_inline void _hlslpp256_store4x4_ps(float* dst, const n256& src0, const n256& src1)
{
	_mm256_storeu_ps(dst, src0);
	_mm256_storeu_ps(dst + 8, src1);
}

hlslpp_inline void _hlslpp256_load4x4_ps(n256& dst0, n256& dst1, const float* src)
{
	dst0 = _mm256_loadu_ps(src);
	dst1 = _mm256_loadu_ps(src + 8);
}

hlslpp_inline void _hlslpp256_transpose4x4_ps(n256& o0, n256& o1, const n256& x0, const n256& x1)
{
	n256 unpacklo = _mm256_unpacklo_ps(x0, x1);
	n256 unpackhi = _mm256_unpackhi_ps(x0, x1);

#if defined(__AVX2__)
	o0 = _mm256_permutevar8x32_ps(unpacklo, _mm256_setr_epi32(0, 4, 1, 5, 2, 6, 3, 7));
	o1 = _mm256_permutevar8x32_ps(unpackhi, _mm256_setr_epi32(0, 4, 1, 5, 2, 6, 3, 7));
#else
	n256 unpacklo_rev = _mm256_permute2f128_ps(unpacklo, unpacklo, 0x1);
	n256 unpackhi_rev = _mm256_permute2f128_ps(unpackhi, unpackhi, 0x1);

	n256 unpacklo_perm0 = _mm256_unpacklo_ps(unpacklo, unpacklo_rev);
	n256 unpacklo_perm1 = _mm256_unpackhi_ps(unpacklo_rev, unpacklo);
	o0 = _mm256_blend_ps(unpacklo_perm0, unpacklo_perm1, 0xf0);

	n256 unpackhi_perm0 = _mm256_unpacklo_ps(unpackhi, unpackhi_rev);
	n256 unpackhi_perm1 = _mm256_unpackhi_ps(unpackhi_rev, unpackhi);
	o1 = _mm256_blend_ps(unpackhi_perm0, unpackhi_perm1, 0xf0);
#endif
}

#endif

//----------
// Float 512
//----------

#if defined(HLSLPP_SIMD_REGISTER_512)

#define _hlslpp512_set1_ps(x)						_mm512_set1_ps((x))

#define _hlslpp512_set_ps(x0, y0, z0, w0, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3) \
	_mm512_set_ps((w3), (z3), (y3), (x3), (w2), (z2), (y2), (x2), (w1), (z1), (y1), (x1), (w0), (z0), (y0), (x0))
#define _hlslpp512_setzero_ps()						_mm512_setzero_ps()

#define _hlslpp512_set128_ps(a, b, c, d)			_mm512_insertf32x8(_mm512_castps256_ps512(_mm256_insertf128_ps(_mm256_castps128_ps256(a), b, 0x1)), _mm256_insertf128_ps(_mm256_castps128_ps256(c), d, 0x1), 0x1)

#define _hlslpp512_add_ps(x, y)						_mm512_add_ps((x), (y))
#define _hlslpp512_sub_ps(x, y)						_mm512_sub_ps((x), (y))
#define _hlslpp512_mul_ps(x, y)						_mm512_mul_ps((x), (y))
#define _hlslpp512_div_ps(x, y)						_mm512_div_ps((x), (y))

#define _hlslpp512_rcp_ps(x)						_mm512_rcp14_ps((x))

#define _hlslpp512_neg_ps(x)						_mm512_xor_ps((x), _mm512_castsi512_ps(_mm512_set1_epi32(0x80000000)))

// http://www.liranuna.com/sse-intrinsics-optimizations-in-popular-compilers/
//#define _hlslpp512_sign_ps(x)						_hlslpp512_and_ps(_hlslpp512_or_ps(_hlslpp512_and_ps((x), f4_minus1), f4_1), _hlslpp512_cmpneq_ps((x), _hlslpp512_setzero_ps()))

#define _hlslpp512_madd_ps(x, y, z)					_mm512_fmadd_ps((x), (y), (z)) // x * y + z
#define _hlslpp512_msub_ps(x, y, z)					_mm512_fmsub_ps((x), (y), (z)) // x * y - z
#define _hlslpp512_subm_ps(x, y, z)					_mm512_fnmadd_ps((y), (z), (x)) // x - y * z

// Reference http://www.liranuna.com/sse-intrinsics-optimizations-in-popular-compilers/
#define _hlslpp512_abs_ps(x)						_mm512_and_ps(_mm512_castsi512_ps(_mm512_set1_epi32(0x7fffffff)), (x))

#define _hlslpp512_sqrt_ps(x)						_mm512_sqrt_ps((x))
#define _hlslpp512_rsqrt_ps(x)						_mm512_rsqrt14_ps((x))

#define _hlslpp512_cmpeq_ps(x, y)					_mm512_maskz_expand_ps(_mm512_cmpeq_ps_mask((x), (y)), _mm512_castsi512_ps(_mm512_set1_epi32(0xffffffff)))
#define _hlslpp512_cmpneq_ps(x, y)					_mm512_maskz_expand_ps(_mm512_cmpneq_ps_mask((x), (y)), _mm512_castsi512_ps(_mm512_set1_epi32(0xffffffff)))

#define _hlslpp512_cmpgt_ps(x, y)					_mm512_maskz_expand_ps(_mm512_cmp_ps_mask((x), (y), _CMP_GT_OS), _mm512_castsi512_ps(_mm512_set1_epi32(0xffffffff)))
#define _hlslpp512_cmpge_ps(x, y)					_mm512_maskz_expand_ps(_mm512_cmp_ps_mask((x), (y), _CMP_GE_OS), _mm512_castsi512_ps(_mm512_set1_epi32(0xffffffff)))

#define _hlslpp512_cmplt_ps(x, y)					_mm512_maskz_expand_ps(_mm512_cmp_ps_mask((x), (y), _CMP_LT_OS), _mm512_castsi512_ps(_mm512_set1_epi32(0xffffffff)))
#define _hlslpp512_cmple_ps(x, y)					_mm512_maskz_expand_ps(_mm512_cmp_ps_mask((x), (y), _CMP_LE_OS), _mm512_castsi512_ps(_mm512_set1_epi32(0xffffffff)))

#define _hlslpp512_max_ps(x, y)						_mm512_max_ps((x), (y))
#define _hlslpp512_min_ps(x, y)						_mm512_min_ps((x), (y))

//#define _hlslpp512_sel_ps(x, y, mask)				_mm512_blendv_ps((x), (y), (mask))

//#define _hlslpp512_blend_ps(x, y, mask)			_mm512_blend_ps((x), (y), (mask))

#define _hlslpp512_trunc_ps(x)						_mm512_roundscale_ps((x), _MM_FROUND_TRUNC)
#define _hlslpp512_floor_ps(x)						_mm512_roundscale_ps((x), _MM_FROUND_FLOOR)
#define _hlslpp512_ceil_ps(x)						_mm512_roundscale_ps((x), _MM_FROUND_CEIL)

// _MM_FROUND_TO_NEAREST_INT to match fxc behavior
#define _hlslpp512_round_ps(x)						_mm512_roundscale_ps((x), _MM_FROUND_TO_NEAREST_INT)

#define _hlslpp512_frac_ps(x)						_mm512_sub_ps((x), _hlslpp512_floor_ps(x))

#define _hlslpp512_clamp_ps(x, minx, maxx)			_mm512_max_ps(_mm512_min_ps((x), (maxx)), (minx))
#define _hlslpp512_sat_ps(x)						_mm512_max_ps(_mm512_min_ps((x), _mm512_set1_ps(1.0f)), _mm512_setzero_ps())

#define _hlslpp512_and_ps(x, y)						_mm512_and_ps((x), (y))
#define _hlslpp512_andnot_ps(x, y)					_mm512_andnot_ps((x), (y))
#define _hlslpp512_not_ps(x)						_mm512_andnot_ps((x), f4_fff)
#define _hlslpp512_or_ps(x, y)						_mm512_or_ps((x), (y))
#define _hlslpp512_xor_ps(x, y)						_mm512_xor_ps((x), (y))

#define HLSLPP_PERM_MASK_512(X, Y, Z, W, A, B, C, D, E, F, G, H, I, J, K, L) \
	((L << 30) | (K << 28) | (J << 26) | (I << 24) | (H << 22) | (G << 20) | (F << 18) | (E << 16) | (D << 14) | (C << 12) | (B << 10) | (A << 8) | (W << 6) | (Z << 4) | (Y << 2) | (X))

template
<
	int X, int Y, int Z, int W, 
	int A, int B, int C, int D,
	int E, int F, int G, int H,
	int I, int J, int K, int L
>
hlslpp_inline n512 permute_float(n512 x)
{
	hlslpp_constexpr_if
	(
		X < 4   && Y < 4  && Z < 4   && W < 4  && 
		A >= 4  && A < 8  && B >= 4  && B < 8  && C >= 4  && C < 8  && D >= 4  && D < 8 &&
		E >= 8  && E < 12 && F >= 8  && F < 12 && G >= 8  && G < 12 && H >= 8  && H < 12 &&
		I >= 12 && I < 16 && J >= 12 && J < 16 && K >= 12 && K < 16 && L >= 12 && L < 16
	)
	{
		hlslpp_constexpr_if
		(
			X == (A - 4) && X == (E - 8) && X == (I - 12) &&
			Y == (B - 4) && Y == (F - 8) && Y == (J - 12) &&
			Z == (C - 4) && Z == (G - 8) && Z == (K - 12) &&
			W == (D - 4) && W == (H - 8) && W == (L - 12)
		)
		{
			HLSLPP_WARNING_INVALID_SHUFFLE_BEGIN
			return _mm512_permute_ps(x, HLSLPP_SHUFFLE_MASK(X, Y, Z, W));
			HLSLPP_WARNING_INVALID_SHUFFLE_END
		}
		else
		{
			return _mm512_permutevar_ps(x, _mm512_setr_epi32(X, Y, Z, W, A, B, C, D, E, F, G, H, I, J, K, L));
		}
	}
	else
	{
		return _mm512_permutexvar_ps(_mm512_setr_epi32(X, Y, Z, W, A, B, C, D, E, F, G, H, I, J, K, L), x);
	}
}

#define _hlslpp512_perm_ps(x, X, Y, Z, W, A, B, C, D, E, F, G, H, I, J, K, L) permute_float<X, Y, Z, W, A, B, C, D, E, F, G, H, I, J, K, L>(x)

#define _hlslpp512_vec0_ps(x)						_mm512_castps512_ps128((x))
#define _hlslpp512_vec1_ps(x)						_mm512_extractf32x4_ps((x), 1)
#define _hlslpp512_vec2_ps(x)						_mm512_extractf32x4_ps((x), 2)
#define _hlslpp512_vec3_ps(x)						_mm512_extractf32x4_ps((x), 3)

#define _hlslpp512_low_ps(x)						_mm512_castps512_ps256((x))
#define _hlslpp512_high_ps(x)						_mm512_extractf32x8_ps((x), 1)

#define _hlslpp512_vec1230(x)						_mm512_extractf32x4_ps((x), 1)

#define _hlslpp512_castps_si512(x)					_mm512_castps_si512((x))
#define _hlslpp512_castsi512_ps(x)					_mm512_castsi512_ps((x))

#define _hlslpp512_cvtepi32_ps(x)					_mm512_cvtepi32_ps((x))
#define _hlslpp512_cvtps_epi32(x)					_mm512_cvttps_epi32((x))

hlslpp_inline n512 _hlslpp512_reduce_add_ps(n512 x)
{
	n256 add0  = _mm256_add_ps(_hlslpp512_low_ps(x), _hlslpp512_high_ps(x));
	n128 add1  = _mm_add_ps(_hlslpp256_low_ps(add0), _hlslpp256_high_ps(add0));
	n128 shuf = _hlslpp_perm_ps(add1, 1, 0, 3, 0);
	n128 add2 = _mm_add_ps(shuf, add1);
	shuf = _mm_movehl_ps(shuf, add2);
	return _mm512_castps128_ps512(_mm_add_ps(add2, shuf));
}

hlslpp_inline n512 _hlslpp512_dot16_ps(n512 x, n512 y)
{
	return _hlslpp512_reduce_add_ps(_hlslpp512_mul_ps(x, y));
}

hlslpp_inline bool _hlslpp512_any16_ps(n512 x)
{
	return _mm512_cmpeq_ps_mask(x, _mm512_setzero_ps()) != 0xffff;
}

hlslpp_inline bool _hlslpp512_all16_ps(n512 x)
{
	return _mm512_cmpeq_ps_mask(x, _mm512_setzero_ps()) == 0;
}

hlslpp_inline void _hlslpp512_store16_ps(float* dst, const n512& src)
{
	_mm512_storeu_ps(dst, src);
}

hlslpp_inline void _hlslpp512_load16_ps(n512& dst, float* src)
{
	dst = _mm512_loadu_ps(src);
}

hlslpp_inline void _hlslpp512_store4x4_ps(float* dst, const n512& src)
{
	_mm512_storeu_ps(dst, src);
}

hlslpp_inline void _hlslpp512_load4x4_ps(n512& dst, const float* src)
{
	dst = _mm512_loadu_ps(src);
}

hlslpp_inline n512 _hlslpp512_transpose4x4_ps(const n512& x)
{
	return _hlslpp512_perm_ps(x, 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15);
}

#define _hlslpp512_set_epi32(x0, y0, z0, w0, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3) \
	_mm512_set_epi32((w3), (z3), (y3), (x3), (w2), (z2), (y2), (x2), (w1), (z1), (y1), (x1), (w0), (z0), (y0), (x0))

#endif

//--------
// Integer
//--------

#define _hlslpp_set1_epi32(x)					_mm_set1_epi32((x))
#define _hlslpp_set_epi32(x, y, z, w)			_mm_set_epi32((w), (z), (y), (x))
#define _hlslpp_setzero_epi32()					_mm_setzero_si128()

#define _hlslpp_add_epi32(x, y)					_mm_add_epi32((x), (y))
#define _hlslpp_sub_epi32(x, y)					_mm_sub_epi32((x), (y))

// https://stackoverflow.com/questions/10500766/sse-multiplication-of-4-32-bit-integers
#if defined(__SSE4_1__)

#define _hlslpp_mul_epi32(x, y)					_mm_mullo_epi32((x), (y))

#else

hlslpp_inline n128i _hlslpp_mul_epi32(n128i x, n128i y)
{
	n128i tmp1 = _mm_mul_epu32(x, y);
	n128i tmp2 = _mm_mul_epu32(_mm_srli_si128(x, 4), _mm_srli_si128(y, 4));
	return _mm_unpacklo_epi32(_mm_shuffle_epi32(tmp1, _MM_SHUFFLE(0, 0, 2, 0)), _mm_shuffle_epi32(tmp2, _MM_SHUFFLE(0, 0, 2, 0)));
}

#endif

#define _hlslpp_div_epi32(x, y)					_mm_cvttps_epi32(_mm_div_ps(_mm_cvtepi32_ps(x), _mm_cvtepi32_ps(y)))

#if defined(__SSSE3__)
#define _hlslpp_neg_epi32(x)					_mm_sign_epi32((x), _mm_set1_epi32(-1))
#else
#define _hlslpp_neg_epi32(x)					_mm_sub_epi32(_mm_setzero_si128(), (x))
#endif

#define _hlslpp_madd_epi32(x, y, z)				_mm_add_epi32(_hlslpp_mul_epi32((x), (y)), (z))
#define _hlslpp_msub_epi32(x, y, z)				_mm_sub_epi32(_hlslpp_mul_epi32((x), (y)), (z))
#define _hlslpp_subm_epi32(x, y, z)				_mm_sub_epi32((x), _hlslpp_mul_epi32((y), (z)))

#if defined(__SSSE3__)
	#define _hlslpp_abs_epi32(x)				_mm_abs_epi32((x))
#else

	// https://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
	hlslpp_inline n128i _hlslpp_abs_epi32(n128i x)
	{
		n128i mask = _mm_srai_epi32(x, 31);
		n128i sum = _mm_add_epi32(x, mask);
		return _mm_xor_si128(sum, mask);
	}

#endif

#define _hlslpp_cmpeq_epi32(x, y)				_mm_cmpeq_epi32((x), (y))
#define _hlslpp_cmpneq_epi32(x, y)				_mm_andnot_si128(_mm_cmpeq_epi32((x), (y)), i4fffMask)

#define _hlslpp_cmpgt_epi32(x, y)				_mm_cmpgt_epi32((x), (y))
#define _hlslpp_cmpge_epi32(x, y)				_mm_or_si128(_mm_cmpgt_epi32((x), (y)), _mm_cmpeq_epi32((x), (y)))

#define _hlslpp_cmplt_epi32(x, y)				_mm_cmplt_epi32((x), (y))
#define _hlslpp_cmple_epi32(x, y)				_mm_or_si128(_mm_cmplt_epi32((x), (y)), _mm_cmpeq_epi32((x), (y)))

#if defined(__SSE4_1__)

#define _hlslpp_max_epi32(x, y)					_mm_max_epi32((x), (y))
#define _hlslpp_min_epi32(x, y)					_mm_min_epi32((x), (y))

#else

hlslpp_inline n128i _hlslpp_max_epi32(n128i x, n128i y)
{
	n128i gt        = _mm_cmpgt_epi32(x, y);   // Compare both values
	n128i x_greater = _mm_and_si128(x, gt);    // if y is greater,  gt is 0xffffffff
	n128i y_greater = _mm_andnot_si128(gt, y); // if x is greater, !gt is 0xffffffff
	return _mm_or_si128(x_greater, y_greater); // Or them together as one is guaranteed to be 0
}

hlslpp_inline n128i _hlslpp_min_epi32(n128i x, n128i y)
{
	n128i gt        = _mm_cmpgt_epi32(x, y);   // Compare both values
	n128i x_smaller = _mm_andnot_si128(gt, x); // if x is smaller, !gt is 0xffffffff
	n128i y_smaller = _mm_and_si128(y, gt);    // if y is smaller,  gt is 0xffffffff
	return _mm_or_si128(x_smaller, y_smaller); // Or them together as one is guaranteed to be 0
}

#endif

// SSE2 alternative https://markplusplus.wordpress.com/2007/03/14/fast-sse-select-operation/
// Bit-select val1 and val2 based on the contents of the mask
#if defined(__SSE4_1__)

#define _hlslpp_sel_epi32(x, y, mask)			_mm_blendv_epi8((x), (y), (mask))

#else

#define _hlslpp_sel_epi32(x, y, mask)			_mm_xor_si128((x), _mm_and_si128(mask, _mm_xor_si128((y), (x))))

#endif

#if defined(__AVX2__)

#define _hlslpp_blend_epi32(x, y, mask)			_mm_blend_epi32((x), (y), mask)

#elif defined(__SSE4_1__)

// Reshuffle the mask because we use _mm_blend_epi16 as that's what's available in SSE4.1 
#define _hlslpp_blend_epi32(x, y, mask)			_mm_blend_epi16((x), (y), ((mask & 1) * 3) | ((((mask >> 1) & 1) * 3) << 2) | ((((mask >> 2) & 1) * 3) << 4) | ((((mask >> 3) & 1) * 3) << 6))

#else

hlslpp_inline n128i _hlslpp_blend_epi32(n128i x, n128i y, int mask)
{
	n128i mask128 = _mm_set_epi32(int(((mask >> 3) & 1) * 0xffffffff), int(((mask >> 2) & 1) * 0xffffffff), int(((mask >> 1) & 1) * 0xffffffff), int((mask & 1) * 0xffffffff));
	return _mm_xor_si128((x), _mm_and_si128(mask128, _mm_xor_si128((y), (x))));
}

#endif

namespace hlslpp
{
	template<unsigned int X, unsigned int Y, unsigned int Z, unsigned int W>
	hlslpp_inline __m128i permute(__m128i x)
	{
		return _mm_shuffle_epi32((x), HLSLPP_SHUFFLE_MASK(X, Y, Z, W));
	}

	template<>
	hlslpp_inline __m128i permute<0, 1, 2, 3>(__m128i x)
	{
		return x;
	}
}

#define _hlslpp_clamp_epi32(x, minx, maxx)		_hlslpp_max_epi32(_hlslpp_min_epi32((x), (maxx)), (minx))
#define _hlslpp_sat_epi32(x)					_hlslpp_max_epi32(_hlslpp_min_epi32((x), i4_1), i4_0)

#define _hlslpp_and_si128(x, y)					_mm_and_si128((x), (y))
#define _hlslpp_andnot_si128(x, y)				_mm_andnot_si128((x), (y))
#define _hlslpp_not_si128(x)					_mm_andnot_si128((x), i4fffMask)
#define _hlslpp_or_si128(x, y)					_mm_or_si128((x), (y))
#define _hlslpp_xor_si128(x, y)					_mm_xor_si128((x), (y))

// https://stackoverflow.com/questions/13153584/mm-shuffle-ps-equivalent-for-integer-vectors-m128i
#define _hlslpp_perm_epi32(x, X, Y, Z, W)		hlslpp::permute<X, Y, Z, W>((x))
#define _hlslpp_shuffle_epi32(x, y, X, Y, A, B)	_mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(x), _mm_castsi128_ps(y), HLSLPP_SHUFFLE_MASK(X, Y, A, B)))

#define _hlslpp_castps_si128(x)					_mm_castps_si128((x))
#define _hlslpp_castsi128_ps(x)					_mm_castsi128_ps((x))

// Converts packed signed 32-bit integers in x to floating point
#define _hlslpp_cvtepi32_ps(x)					_mm_cvtepi32_ps((x))

// Converts floating point in x to packed 32-bit integers with truncation
#define _hlslpp_cvttps_epi32(x)					_mm_cvttps_epi32((x))

#if defined(__SSE4_1__)

#define _hlslpp_cvtepi8_epi32(x)				_mm_cvtepi8_epi32(x)
#define _hlslpp_cvtepu8_epi32(x)				_mm_cvtepu8_epi32(x)

#else

// https://sseplus.sourceforge.net/group__emulated___s_s_e2.html
hlslpp_inline __m128i _hlslpp_cvtepi8_epi32(__m128i v)
{
	const __m128i minus_one = _mm_set1_epi32(-1);

	__m128i unpacked8  = _mm_unpacklo_epi8(v, minus_one);
	__m128i unpacked16 = _mm_unpacklo_epi16(unpacked8, minus_one);
	__m128i andnot     = _mm_andnot_si128(unpacked16, _mm_set1_epi32(128));
	__m128i shift_1    = _mm_slli_epi32(andnot, 1);
	__m128i result     = _mm_add_epi32(unpacked16, shift_1);
	return result;
}

hlslpp_inline __m128i _hlslpp_cvtepu8_epi32(__m128i v)
{
	__m128i zero = _mm_setzero_si128();
	__m128i unpacked8 = _mm_unpacklo_epi8(v, zero);
	return _mm_unpacklo_epi16(unpacked8, zero);
}

#endif

// Shift left/right by an immediate while shifting in zeroes
#define _hlslpp_slli_epi32(x, y)				_mm_slli_epi32((x), (y))
#define _hlslpp_srli_epi32(x, y)				_mm_srli_epi32((x), (y))

#if defined(__AVX2__)

#define _hlslpp_sllv_epi32(x, y)				_mm_sllv_epi32((x), (y))
#define _hlslpp_srlv_epi32(x, y)				_mm_srlv_epi32((x), (y))

#else

hlslpp_inline n128i _hlslpp_sllv_epi32(n128i x, n128i count)
{
	int32_t x4[4];
	int32_t count4[4];

	_mm_storeu_si128((__m128i*)x4, x);
	_mm_storeu_si128((__m128i*)count4, count);

	int32_t result4[4];
	result4[0] = x4[0] << count4[0];
	result4[1] = x4[1] << count4[1];
	result4[2] = x4[2] << count4[2];
	result4[3] = x4[3] << count4[3];

	return _mm_loadu_si128((__m128i*)result4);
}

hlslpp_inline n128i _hlslpp_srlv_epi32(n128i x, n128i count)
{
	int32_t x4[4];
	int32_t count4[4];

	_mm_storeu_si128((__m128i*)x4, x);
	_mm_storeu_si128((__m128i*)count4, count);

	int32_t result4[4];
	result4[0] = x4[0] >> count4[0];
	result4[1] = x4[1] >> count4[1];
	result4[2] = x4[2] >> count4[2];
	result4[3] = x4[3] >> count4[3];

	return _mm_loadu_si128((__m128i*)result4);
}

#endif

hlslpp_inline bool _hlslpp_any1_epi32(n128i x)
{
	return (_mm_movemask_epi8(_mm_cmpeq_epi32(x, _mm_setzero_si128())) & 0xf) != 0xf;
}

hlslpp_inline bool _hlslpp_any2_epi32(n128i x)
{
	return (_mm_movemask_epi8(_mm_cmpeq_epi32(x, _mm_setzero_si128())) & 0xff) != 0xff;
}

hlslpp_inline bool _hlslpp_any3_epi32(n128i x)
{
	return (_mm_movemask_epi8(_mm_cmpeq_epi32(x, _mm_setzero_si128())) & 0xfff) != 0xfff;
}

hlslpp_inline bool _hlslpp_any4_epi32(n128i x)
{
	return (_mm_movemask_epi8(_mm_cmpeq_epi32(x, _mm_setzero_si128())) & 0xffff) != 0xffff;
}

hlslpp_inline bool _hlslpp_all1_epi32(n128i x)
{
	return (_mm_movemask_epi8(_mm_cmpeq_epi32(x, _mm_setzero_si128())) & 0xf) == 0;
}

hlslpp_inline bool _hlslpp_all2_epi32(n128i x)
{
	return (_mm_movemask_epi8(_mm_cmpeq_epi32(x, _mm_setzero_si128())) & 0xff) == 0;
}

hlslpp_inline bool _hlslpp_all3_epi32(n128i x)
{
	return (_mm_movemask_epi8(_mm_cmpeq_epi32(x, _mm_setzero_si128())) & 0xfff) == 0;
}

hlslpp_inline bool _hlslpp_all4_epi32(n128i x)
{
	return (_mm_movemask_epi8(_mm_cmpeq_epi32(x, _mm_setzero_si128())) & 0xffff) == 0;
}

//-------------------
// Integer Store/Load
//-------------------

hlslpp_inline void _hlslpp_store1_epi32(int32_t* dst, n128i src)
{
	_mm_store_ss((float*)dst, *(n128*)&src);
}

hlslpp_inline void _hlslpp_store2_epi32(int32_t* dst, n128i src)
{
	_mm_storel_epi64((__m128i*)dst, src);
}

hlslpp_inline void _hlslpp_store3_epi32(int32_t* dst, n128i src)
{
	_mm_storel_epi64((__m128i*)dst, src);
	_mm_store_ss((float*)dst + 2, _mm_castsi128_ps(_hlslpp_perm_epi32(src, 2, 2, 2, 2)));
}

hlslpp_inline void _hlslpp_store4_epi32(int32_t* dst, n128i src)
{
	_mm_storeu_si128((__m128i*)dst, src);
}

hlslpp_inline void _hlslpp_load1_epi32(n128i& dst, const int32_t* src)
{
	dst = _mm_castps_si128(_mm_load_ss((float*)src));
}

// http://fastcpp.blogspot.com/2011/03/loading-3d-vector-into-sse-register.html
hlslpp_inline void _hlslpp_load2_epi32(n128i& dst, const int32_t* src)
{
	dst = _mm_loadl_epi64((__m128i*)src);
}

hlslpp_inline void _hlslpp_load3_epi32(n128i& dst, const int32_t* src)
{
	dst = _mm_castps_si128(_mm_movelh_ps(_mm_castsi128_ps(_mm_loadl_epi64((__m128i*)src)), _mm_load_ss((float*) + 2)));
}

hlslpp_inline void _hlslpp_load4_epi32(n128i& dst, const int32_t* src)
{
	dst = _mm_loadu_si128((__m128i*)src);
}

//------------
// Integer 256
//------------

#if defined(__AVX__)

#define _hlslpp256_set1_epi32(x)						_mm256_set1_epi32((x))
#define _hlslpp256_set_epi32(x, y, z, w, a, b, c, d)	_mm256_set_epi32(d, c, b, a, w, z, y, x)
#define _hlslpp256_setzero_si256()						_mm256_setzero_si256()
#define _hlslpp256_set128_epi32(lo, hi)					_mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 0x1)

#define _hlslpp256_low_epi32(x)							_mm256_castsi256_si128((x))
#define _hlslpp256_high_epi32(x)						_mm256_extractf128_si256((x), 1)

#if defined(__AVX2__)

#define _hlslpp256_add_epi32(x, y)						_mm256_add_epi32((x), (y))
#define _hlslpp256_sub_epi32(x, y)						_mm256_sub_epi32((x), (y))
#define _hlslpp256_mul_epi32(x, y)						_mm256_mullo_epi32((x), (y))

#else

hlslpp_inline n256i _hlslpp256_add_epi32(n256i x, n256i y)
{
	return _hlslpp256_set128_epi32
	(
		_mm_add_epi32(_hlslpp256_low_epi32(x), _hlslpp256_low_epi32(y)),
		_mm_add_epi32(_hlslpp256_high_epi32(x), _hlslpp256_high_epi32(y))
	);
}

hlslpp_inline n256i _hlslpp256_sub_epi32(n256i x, n256i y)
{
	return _hlslpp256_set128_epi32
	(
		_mm_sub_epi32(_hlslpp256_low_epi32(x), _hlslpp256_low_epi32(y)),
		_mm_sub_epi32(_hlslpp256_high_epi32(x), _hlslpp256_high_epi32(y))
	);
}

hlslpp_inline n256i _hlslpp256_mul_epi32(n256i x, n256i y)
{
	return _hlslpp256_set128_epi32
	(
		_mm_mul_epi32(_hlslpp256_low_epi32(x), _hlslpp256_low_epi32(y)),
		_mm_mul_epi32(_hlslpp256_high_epi32(x), _hlslpp256_high_epi32(y))
	);
}

#endif

#define _hlslpp256_div_epi32(x, y)						_mm256_castps_si256(_mm256_div_ps(_mm256_castsi256_ps(x), _mm256_castsi256_ps(y)))

#define _hlslpp256_neg_epi32(x)							_mm256_sign_epi32((x), _mm256_set1_epi32(-1))

#define _hlslpp256_madd_epi32(x, y, z)					_mm256_add_epi32(_mm256_mullo_epi32((x), (y)), (z))
#define _hlslpp256_msub_epi32(x, y, z)					_mm256_sub_epi32(_mm256_mullo_epi32((x), (y)), (z))
#define _hlslpp256_subm_epi32(x, y, z)					_mm256_sub_epi32((x), _mm256_mullo_epi32((y), (z)))

#define _hlslpp256_abs_epi32(x)							_mm256_and_si256(i8absMask, (x))

#define _hlslpp256_cmpeq_epi32(x, y)					_mm256_cmpeq_epi32((x), (y))
#define _hlslpp256_cmpneq_epi32(x, y)					_mm256_andnot_si256(_mm256_cmpeq_epi32((x), (y)), i8fffMask)

#define _hlslpp256_cmpgt_epi32(x, y)					_mm256_cmpgt_epi32((x), (y))
#define _hlslpp256_cmpge_epi32(x, y)					_mm256_or_si256(_mm256_cmpgt_epi32((x), (y)), _mm256_cmpeq_epi32((x), (y)))

#define _hlslpp256_cmplt_epi32(x, y)					_mm256_cmplt_epi32((x), (y))
#define _hlslpp256_cmple_epi32(x, y)					_mm256_or_si256(_mm256_cmplt_epi32((x), (y)), _mm256_cmpeq_epi32((x), (y)))

#define _hlslpp256_max_epi32(x, y)						_mm256_max_epi32((x), (y))
#define _hlslpp256_min_epi32(x, y)						_mm256_min_epi32((x), (y))

#define _hlslpp256_clamp_epi32(x, minx, maxx)			_mm256_max_epi32(_mm256_min_epi32((x), (maxx)), (minx))
#define _hlslpp256_sat_epi32(x)							_mm256_max_epi32(_mm256_min_epi32((x), i4_1), i4_0)

#if defined(__AVX2__)

#define _hlslpp256_and_si128(x, y)						_mm256_and_si256((x), (y))
#define _hlslpp256_or_si128(x, y)						_mm256_or_si256((x), (y))

#else

hlslpp_inline n256i _hlslpp256_and_si128(n256i x, n256i y)
{
	return _hlslpp256_set128_epi32
	(
		_mm_and_si128(_hlslpp256_low_epi32(x), _hlslpp256_low_epi32(y)),
		_mm_and_si128(_hlslpp256_high_epi32(x), _hlslpp256_high_epi32(y))
	);
}

hlslpp_inline n256i _hlslpp256_or_si128(n256i x, n256i y)
{
	return _hlslpp256_set128_epi32
	(
		_mm_or_si128(_hlslpp256_low_epi32(x), _hlslpp256_low_epi32(y)),
		_mm_or_si128(_hlslpp256_high_epi32(x), _hlslpp256_high_epi32(y))
	);
}

#endif

// https://stackoverflow.com/questions/13153584/mm-shuffle-ps-equivalent-for-integer-vectors-m128i
//#define _hlslpp256_perm_epi32(x, mask)				_mm_shuffle_epi32((x), (mask))
//#define _hlslpp256_shuffle_epi32(x, y, mask)		_mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(x), _mm_castsi128_ps(y), (mask)))

#define _hlslpp256_blend_epi32(x, y, mask)				_mm256_blend_epi32((x), (y), (mask))

#define _hlslpp256_castps_si256(x)						_mm256_castps_si256((x))
#define _hlslpp256_castsi256_ps(x)						_mm256_castsi256_ps((x))

#define _hlslpp256_cvtepi32_ps(x)						_mm256_cvtepi32_ps((x))
#define _hlslpp256_cvtps_epi32(x)						_mm256_cvttps_epi32((x))

#if defined(__AVX2__)

#define _hlslpp256_slli_epi32(x, y)						_mm256_slli_epi32((x), (y))
#define _hlslpp256_srli_epi32(x, y)						_mm256_srli_epi32((x), (y))

#else

#define _hlslpp256_slli_epi32(x, y)						_hlslpp256_set128_epi32(_mm_slli_si128(_hlslpp256_low_epi32(x), y),	_mm_slli_si128(_hlslpp256_high_epi32(x), y))
#define _hlslpp256_srli_epi32(x, y)						_hlslpp256_set128_epi32(_mm_srli_si128(_hlslpp256_low_epi32(x), y),	_mm_srli_si128(_hlslpp256_high_epi32(x), y))

#endif

#endif

//-----------------
// Unsigned Integer
//-----------------

#define _hlslpp_set1_epu32(x)					_hlslpp_set1_epi32(int(x))
#define _hlslpp_set_epu32(x, y, z, w)			_hlslpp_set_epi32(int(x), int(y), int(z), int(w))
#define _hlslpp_setzero_epu32()					_hlslpp_setzero_epi32()

#define _hlslpp_add_epu32(x, y)					_hlslpp_add_epi32((x), (y))
#define _hlslpp_sub_epu32(x, y)					_hlslpp_sub_epi32((x), (y))

#define _hlslpp_mul_epu32(x, y)					_hlslpp_mul_epi32((x), (y))

#define _hlslpp_div_epu32(x, y)					_hlslpp_div_epi32((x), (y))

#define _hlslpp_madd_epu32(x, y, z)				_hlslpp_madd_epi32(x, y, z)
#define _hlslpp_msub_epu32(x, y, z)				_hlslpp_msub_epi32(x, y, z)
#define _hlslpp_subm_epu32(x, y, z)				_hlslpp_subm_epi32(x, y, z)

#define _hlslpp_cmpeq_epu32(x, y)				_hlslpp_cmpeq_epi32((x), (y))
#define _hlslpp_cmpneq_epu32(x, y)				_hlslpp_cmpneq_epi32((x), (y))

hlslpp_inline n128u _hlslpp_cmpgt_epu32(n128u x, n128u y)
{
	return _mm_xor_si128(_mm_cmpgt_epi32(_mm_xor_si128(x, _mm_set1_epi32((int)0xf0000000)), _mm_xor_si128(y, _mm_set1_epi32((int)0xf0000000))), _mm_set1_epi32((int)0xf0000000));
}

hlslpp_inline n128i _hlslpp_cmpge_epu32(n128i x, n128i y)
{
	n128i xor_x = _mm_xor_si128(x, _mm_set1_epi32((int)0xf0000000));
	n128i xor_y = _mm_xor_si128(y, _mm_set1_epi32((int)0xf0000000));

	return _mm_xor_si128(_mm_or_si128(_mm_cmpgt_epi32(xor_x, xor_y), _mm_cmpeq_epi32(xor_x, xor_y)), _mm_set1_epi32((int)0xf0000000));
}

hlslpp_inline n128u _hlslpp_cmplt_epu32(n128u x, n128u y)
{
	return _mm_xor_si128(_mm_cmplt_epi32(_mm_xor_si128(x, _mm_set1_epi32((int)0xf0000000)), _mm_xor_si128(y, _mm_set1_epi32((int)0xf0000000))), _mm_set1_epi32((int)0xf0000000));
}

hlslpp_inline n128i _hlslpp_cmple_epu32(n128i x, n128i y)
{
	n128i xor_x = _mm_xor_si128(x, _mm_set1_epi32((int)0xf0000000));
	n128i xor_y = _mm_xor_si128(y, _mm_set1_epi32((int)0xf0000000));

	return _mm_xor_si128(_mm_or_si128(_mm_cmplt_epi32(xor_x, xor_y), _mm_cmpeq_epi32(xor_x, xor_y)), _mm_set1_epi32((int)0xf0000000));
}

#if defined(__SSE4_1__)

#define _hlslpp_max_epu32(x, y)					_mm_max_epu32((x), (y))
#define _hlslpp_min_epu32(x, y)					_mm_min_epu32((x), (y))

#else

// https://stackoverflow.com/questions/41610655/sse2-intrinsics-find-max-of-two-unsigned-short-vectors

hlslpp_inline n128i _hlslpp_max_epu32(n128u x, n128u y)
{
	return _mm_xor_si128(_hlslpp_max_epi32(_mm_xor_si128(x, _mm_set1_epi32((int)0xf0000000)), _mm_xor_si128(y, _mm_set1_epi32((int)0xf0000000))), _mm_set1_epi32((int)0xf0000000));
}

hlslpp_inline n128i _hlslpp_min_epu32(n128u x, n128u y)
{
	return _mm_xor_si128(_hlslpp_min_epi32(_mm_xor_si128(x, _mm_set1_epi32((int)0xf0000000)), _mm_xor_si128(y, _mm_set1_epi32((int)0xf0000000))), _mm_set1_epi32((int)0xf0000000));
}

#endif

#define _hlslpp_sel_epu32(x, y, mask)			_hlslpp_sel_epi32((x), (y), (mask))
#define _hlslpp_blend_epu32(x, y, mask)			_hlslpp_blend_epi32((x), (y), (mask))

#define _hlslpp_clamp_epu32(x, minx, maxx)		_hlslpp_max_epu32(_hlslpp_min_epu32((x), (maxx)), (minx))
#define _hlslpp_sat_epu32(x)					_hlslpp_max_epu32(_hlslpp_min_epu32((x), i4_1), i4_0)

// https://stackoverflow.com/questions/13153584/mm-shuffle-ps-equivalent-for-integer-vectors-m128i
#define _hlslpp_perm_epu32(x, X, Y, Z, W)		hlslpp::permute<X, Y, Z, W>((x))
#define _hlslpp_shuffle_epu32(x, y, X, Y, A, B)	_mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(x), _mm_castsi128_ps(y), HLSLPP_SHUFFLE_MASK(X, Y, A, B)))

#define _hlslpp_cvttps_epu32(x)					_hlslpp_cvttps_epi32((x))
#define _hlslpp_cvtepu32_ps(x)					_hlslpp_cvtepi32_ps((x))

#define _hlslpp_slli_epu32(x, y)				_hlslpp_slli_epi32((x), (y))
#define _hlslpp_srli_epu32(x, y)				_hlslpp_srli_epi32((x), (y))

#define _hlslpp_sllv_epu32(x, y)				_hlslpp_sllv_epi32((x), (y))
#define _hlslpp_srlv_epu32(x, y)				_hlslpp_srlv_epi32((x), (y))

#define _hlslpp_any1_epu32(x)					_hlslpp_any1_epi32(x)
#define _hlslpp_any2_epu32(x)					_hlslpp_any2_epi32(x)
#define _hlslpp_any3_epu32(x)					_hlslpp_any3_epi32(x)
#define _hlslpp_any4_epu32(x)					_hlslpp_any4_epi32(x)

#define _hlslpp_all1_epu32(x)					_hlslpp_all1_epi32(x)
#define _hlslpp_all2_epu32(x)					_hlslpp_all2_epi32(x)
#define _hlslpp_all3_epu32(x)					_hlslpp_all3_epi32(x)
#define _hlslpp_all4_epu32(x)					_hlslpp_all4_epi32(x)

//----------------------------
// Unsigned Integer Store/Load
//----------------------------

hlslpp_inline void _hlslpp_store1_epu32(uint32_t* p, n128u x) { _hlslpp_store1_epi32((int32_t*)p, x); }
hlslpp_inline void _hlslpp_store2_epu32(uint32_t* p, n128u x) { _hlslpp_store2_epi32((int32_t*)p, x); }
hlslpp_inline void _hlslpp_store3_epu32(uint32_t* p, n128u x) { _hlslpp_store3_epi32((int32_t*)p, x); }
hlslpp_inline void _hlslpp_store4_epu32(uint32_t* p, n128u x) { _hlslpp_store4_epi32((int32_t*)p, x); }
hlslpp_inline void _hlslpp_load1_epu32(n128u& x, const uint32_t* p) { _hlslpp_load1_epi32(x, (const int32_t*)p); }
hlslpp_inline void _hlslpp_load2_epu32(n128u& x, const uint32_t* p) { _hlslpp_load2_epi32(x, (const int32_t*)p); }
hlslpp_inline void _hlslpp_load3_epu32(n128u& x, const uint32_t* p) { _hlslpp_load3_epi32(x, (const int32_t*)p); }
hlslpp_inline void _hlslpp_load4_epu32(n128u& x, const uint32_t* p) { _hlslpp_load4_epi32(x, (const int32_t*)p); }

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

#define _hlslpp_madd_pd(x, y, z)				_mm_fmadd_pd((x), (y), (z)) // x * y + z
#define _hlslpp_msub_pd(x, y, z)				_mm_fmsub_pd((x), (y), (z)) // x * y - z
#define _hlslpp_subm_pd(x, y, z)				_mm_fnmadd_pd((y), (z), (x))) // x - y * z

#else

#define _hlslpp_madd_pd(x, y, z)				_mm_add_pd(_mm_mul_pd((x), (y)), (z)) // x * y + z
#define _hlslpp_msub_pd(x, y, z)				_mm_sub_pd(_mm_mul_pd((x), (y)), (z)) // x * y - z
#define _hlslpp_subm_pd(x, y, z)				_mm_sub_pd((x), _mm_mul_pd((y), (z))) // x - y * z

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

#if defined(__SSE4_1__)

// SSE2 alternative https://markplusplus.wordpress.com/2007/03/14/fast-sse-select-operation/
// _mm_xor_ps((x), _mm_and_ps(mask, _mm_xor_ps((y), (x))))
// Bit-select val1 and val2 based on the contents of the mask
#define _hlslpp_sel_pd(x, y, mask)				_mm_blendv_pd((x), (y), (mask))

#define _hlslpp_blend_pd(x, y, mask)			_mm_blend_pd((x), (y), (mask))

#else

#define _hlslpp_sel_pd(x, y, mask)				_mm_xor_pd((x), _mm_and_pd(mask, _mm_xor_pd((y), (x))))

hlslpp_inline n128d _hlslpp_blend_pd(n128d x, n128d y, int mask)
{
	n128d mask128 = _mm_castsi128_pd(_mm_set_epi64x(int64_t((((mask) >> 1) & 1) * 0xffffffffffffffff), int64_t(((mask) & 1) * 0xffffffffffffffff)));
	return _hlslpp_sel_pd(x, y, mask128);
}

#endif

#if defined(__SSE4_1__)

#define _hlslpp_trunc_pd(x)						_mm_round_pd((x), _MM_FROUND_TRUNC)
#define _hlslpp_floor_pd(x)						_mm_floor_pd((x))
#define _hlslpp_ceil_pd(x)						_mm_ceil_pd((x))

// _MM_FROUND_TO_NEAREST_INT to match fxc behavior
#define _hlslpp_round_pd(x)						_mm_round_pd((x), _MM_FROUND_TO_NEAREST_INT)

#else

// The original version of this used to add and subtract a large double number that would remove the decimals but depends
// on the rounding mode and to avoid getting and setting it we instead use integer operations
hlslpp_inline n128d _hlslpp_trunc_pd(n128d x)
{
	n128i xi = _mm_castpd_si128(x);

	// Extract the exponent
	n128i exponent;
	exponent = _mm_and_si128(xi, _mm_set1_epi64x(0x7ff0000000000000));
	exponent = _mm_srli_epi64(exponent, 52);
	exponent = _mm_sub_epi64(exponent, _mm_set1_epi64x(1023));

	// Extract the sign
	n128i sign = _mm_and_si128(xi, _mm_set1_epi64x((int64_t)0x8000000000000000));

	// Subtract the mantissa size of a double from the exponent and extract it to the lower part
	// as the shift right and left instructions only take the lower integers into account
	n128i trim_size0 = _mm_sub_epi64(_mm_set1_epi64x(52), exponent);
	n128i trim_size1 = _mm_unpackhi_epi64(trim_size0, trim_size0);

	// Shift left and right to remove the decimals
	n128i result_u64_0 = _mm_sll_epi64(_mm_srl_epi64(xi, trim_size0), trim_size0);
	n128i result_u64_1 = _mm_sll_epi64(_mm_srl_epi64(xi, trim_size1), trim_size1);

	// Merge the result back
	n128d result = _mm_shuffle_pd(_mm_castsi128_pd(result_u64_0), _mm_castsi128_pd(result_u64_1), HLSLPP_SHUFFLE_MASK_PD(HLSLPP_MASK_X, HLSLPP_MASK_Y));

	n128i exponent_lt_zero = _mm_cmplt_epi32(exponent, _mm_setzero_si128());
	n128i exponent_ge_52   = _mm_cmpgt_epi32(exponent, _mm_set1_epi64x(51));

	// Put the sign back in the zero
	result = _hlslpp_sel_pd(result, _mm_or_pd(_mm_castsi128_pd(sign), _mm_setzero_pd()), _mm_castsi128_pd(exponent_lt_zero));
	result = _hlslpp_sel_pd(result, x, _mm_castsi128_pd(exponent_ge_52));

	return result;
}

hlslpp_inline n128d _hlslpp_floor_pd(n128d x)
{
	n128d trnc      = _hlslpp_trunc_pd(x);											// Truncate
	n128d gt        = _mm_cmpgt_pd(trnc, x);										// Check if truncation was greater or smaller (i.e. was negative or positive number)
	n128i shr       = _mm_srl_epi64(_mm_castpd_si128(gt), _mm_set_epi64x(0, 63));	// Shift to leave a 1 or a 0
	n128i shrAdjust = _mm_shuffle_epi32(shr, HLSLPP_SHUFFLE_MASK(0, 2, 3, 3));		// Shuffle to be able to convert shifted 1 to double
	n128d result    = _mm_sub_pd(trnc, _mm_cvtepi32_pd(shrAdjust));					// Subtract from truncated value
	return result;
}

hlslpp_inline n128d _hlslpp_ceil_pd(n128d x)
{
	n128d trnc      = _hlslpp_trunc_pd(x);											// Truncate
	n128d gt        = _mm_cmpgt_pd(x, trnc);										// Check if truncation was greater or smaller (i.e. was negative or positive number)
	n128i shr       = _mm_srl_epi64(_mm_castpd_si128(gt), _mm_set_epi64x(0, 63));	// Shift to leave a 1 or a 0
	n128i shrAdjust = _mm_shuffle_epi32(shr, HLSLPP_SHUFFLE_MASK(0, 2, 3, 3));		// Shuffle to be able to convert shifted 1 to double
	n128d result    = _mm_add_pd(trnc, _mm_cvtepi32_pd(shrAdjust));					// Add to truncated value
	return result;
}

hlslpp_inline n128d _hlslpp_round_pd(n128d x)
{
	n128d add     = _mm_add_pd(x, _mm_set1_pd(0.5));		// Add 0.5
	n128d frc_add = _mm_sub_pd(add, _hlslpp_floor_pd(add));	// Get the fractional part
	n128d result  = _mm_sub_pd(add, frc_add);				// Subtract from result
	return result;
}

#endif

#define _hlslpp_frac_pd(x)						_mm_sub_pd((x), _hlslpp_floor_pd(x))

#define _hlslpp_clamp_pd(x, minx, maxx)			_mm_max_pd(_mm_min_pd((x), (maxx)), (minx))
#define _hlslpp_sat_pd(x)						_mm_max_pd(_mm_min_pd((x), d2_1), _mm_setzero_pd())

#define _hlslpp_and_pd(x, y)					_mm_and_pd((x), (y))
#define _hlslpp_andnot_pd(x, y)					_mm_andnot_pd((x), (y))
#define _hlslpp_not_pd(x)						_mm_andnot_pd((x), d2_fff)
#define _hlslpp_or_pd(x, y)						_mm_or_pd((x), (y))
#define _hlslpp_xor_pd(x, y)					_mm_xor_pd((x), (y))

#define _hlslpp_perm_pd(x, X, Y)				_mm_shuffle_pd((x), (x), HLSLPP_SHUFFLE_MASK_PD(X, Y))
#define _hlslpp_shuffle_pd(x, y, X, Y)			_mm_shuffle_pd((x), (y), HLSLPP_SHUFFLE_MASK_PD(X, Y))

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

hlslpp_inline void _hlslpp_store1_pd(double* dst, n128d src)
{
	_mm_storel_pd(dst, src);
}

hlslpp_inline void _hlslpp_store2_pd(double* dst, n128d src)
{
	_mm_storeu_pd(dst, src);
}

hlslpp_inline void _hlslpp_store3_pd(double* dst, n128d src0, n128d src1)
{
	_mm_storeu_pd(dst, src0);
	_mm_storel_pd(dst + 2, src1);
}

hlslpp_inline void _hlslpp_store4_pd(double* dst, n128d src0, n128d src1)
{
	_mm_storeu_pd(dst, src0);
	_mm_storeu_pd(dst + 2, src1);
}

hlslpp_inline void _hlslpp_load1_pd(n128d& dst, const double* src)
{
	dst = _mm_load1_pd(src);
}

// http://fastcpp.blogspot.com/2011/03/loading-3d-vector-into-sse-register.html
hlslpp_inline void _hlslpp_load2_pd(n128d& dst, const double* src)
{
	dst = _mm_loadu_pd(src);
}

hlslpp_inline void _hlslpp_load3_pd(n128d& dst0, n128d& dst1, const double* src)
{
	dst0 = _mm_loadu_pd(src);
	dst1 = _mm_load1_pd(src + 2);
}

hlslpp_inline void _hlslpp_load4_pd(n128d& dst0, n128d& dst1, const double* src)
{
	dst0 = _mm_loadu_pd(src);
	dst1 = _mm_loadu_pd(src + 2);
}

//-----------
// Double 256
//-----------

#if defined(__AVX__)

#define _hlslpp256_set1_pd(x)					_mm256_set1_pd((x))
#define _hlslpp256_set_pd(x, y, z, w)			_mm256_set_pd((w), (z), (y), (x))
#define _hlslpp256_setzero_pd()					_mm256_setzero_pd()
#define _hlslpp256_set128_pd(lo, hi)			_mm256_insertf128_pd(_mm256_castpd128_pd256(lo), (hi), 0x1)

#define _hlslpp256_add_pd(x, y)					_mm256_add_pd((x), (y))
#define _hlslpp256_sub_pd(x, y)					_mm256_sub_pd((x), (y))
#define _hlslpp256_mul_pd(x, y)					_mm256_mul_pd((x), (y))
#define _hlslpp256_div_pd(x, y)					_mm256_div_pd((x), (y))

#define _hlslpp256_rcp_pd(x)					_mm256_div_pd(d4_1, (x))

#define _hlslpp256_neg_pd(x)					_mm256_xor_pd((x), d4negativeMask)

#if defined(__FMA__)

#define _hlslpp256_madd_pd(x, y, z)				_mm256_fmadd_pd((x), (y), (z)) // x * y + z
#define _hlslpp256_msub_pd(x, y, z)				_mm256_fmsub_pd((x), (y), (z)) // x * y - z
#define _hlslpp256_subm_pd(x, y, z)				_mm256_fnmadd_pd((y), (z), (x))) // x - y * z

#else

#define _hlslpp256_madd_pd(x, y, z)				_mm256_add_pd(_mm256_mul_pd((x), (y)), (z)) // x * y + z
#define _hlslpp256_msub_pd(x, y, z)				_mm256_sub_pd(_mm256_mul_pd((x), (y)), (z)) // x * y - z
#define _hlslpp256_subm_pd(x, y, z)				_mm256_sub_pd((x), _mm256_mul_pd((y), (z))) // x - y * z

#endif

// Reference http://www.liranuna.com/sse-intrinsics-optimizations-in-popular-compilers/
#define _hlslpp256_abs_pd(x)					_mm256_and_pd(d4absMask, (x))

#define _hlslpp256_sqrt_pd(x)					_mm256_sqrt_pd((x))
#define _hlslpp256_rsqrt_pd(x)					_mm256_div_pd(d4_1, _mm256_sqrt_pd((x)))

#define _hlslpp256_cmpeq_pd(x, y)				_mm256_cmp_pd((x), (y), _CMP_EQ_OQ)
#define _hlslpp256_cmpneq_pd(x, y)				_mm256_cmp_pd((x), (y), _CMP_NEQ_OQ)

#define _hlslpp256_cmpgt_pd(x, y)				_mm256_cmp_pd((x), (y), _CMP_GT_OQ)
#define _hlslpp256_cmpge_pd(x, y)				_mm256_cmp_pd((x), (y), _CMP_GE_OQ)

#define _hlslpp256_cmplt_pd(x, y)				_mm256_cmp_pd((x), (y), _CMP_LT_OQ)
#define _hlslpp256_cmple_pd(x, y)				_mm256_cmp_pd((x), (y), _CMP_LE_OQ)

#define _hlslpp256_max_pd(x, y)					_mm256_max_pd((x), (y))
#define _hlslpp256_min_pd(x, y)					_mm256_min_pd((x), (y))

#define _hlslpp256_low_pd(x)					_mm256_castpd256_pd128((x))
#define _hlslpp256_high_pd(x)					_mm256_extractf128_pd((x), 1)

// Bit-select val1 and val2 based on the contents of the mask
#define _hlslpp256_sel_pd(x, y, mask)			_mm256_blendv_pd((x), (y), (mask))

#define _hlslpp256_blend_pd(x, y, mask)			_mm256_blend_pd((x), (y), (mask))

#define _hlslpp256_trunc_pd(x)					_mm256_round_pd((x), _MM_FROUND_TRUNC)
#define _hlslpp256_floor_pd(x)					_mm256_floor_pd((x))
#define _hlslpp256_ceil_pd(x)					_mm256_ceil_pd((x))

// _MM_FROUND_TO_NEAREST_INT to match fxc behavior
#define _hlslpp256_round_pd(x)					_mm256_round_pd((x), _MM_FROUND_TO_NEAREST_INT)

#define _hlslpp256_frac_pd(x)					_mm256_sub_pd((x), _hlslpp256_floor_pd(x))

#define _hlslpp256_clamp_pd(x, minx, maxx)		_mm256_max_pd(_mm256_min_pd((x), (maxx)), (minx))
#define _hlslpp256_sat_pd(x)					_mm256_max_pd(_mm256_min_pd((x), d4_1), _mm256_setzero_pd())

#define _hlslpp256_and_pd(x, y)					_mm256_and_pd((x), (y))
#define _hlslpp256_andnot_pd(x, y)				_mm256_andnot_pd((x), (y))
#define _hlslpp256_not_pd(x)					_mm256_andnot_pd((x), d4_fff)
#define _hlslpp256_or_pd(x, y)					_mm256_or_pd((x), (y))
#define _hlslpp256_xor_pd(x, y)					_mm256_xor_pd((x), (y))

// Uses constant indices to decide the most efficient implementation. Unfortunately for non-AVX2 code,
// it's the best we can do with the tools provided. It means some shuffles are more expensive than others.
template<int X, int Y, int Z, int W>
hlslpp_inline n256d permute_double(n256d x)
{	
	// Covers cases like XYZZ, XXZW, YXWZ, etc
	hlslpp_constexpr_if(X < 2 && Y < 2 && Z >= 2 && W >= 2)
	{
		return _mm256_permute_pd(x, (X == 0 ? 0 : 1) | ((Y == 0 ? 0 : 1) << 1) | ((Z == 2 ? 0 : 1) << 2) | ((W == 2 ? 0 : 1) << 3));
	}
#if defined(__AVX2__)
	else
	{
		// This one is faster in all cases except for the simple permute that doesn't do cross-lane
		return _mm256_permute4x64_pd((x), HLSLPP_SHUFFLE_MASK(X, Y, Z, W));
	}
#else

	// Covers cases like ZWYY, WZXY, WWYX
	else hlslpp_constexpr_if(X >= 2 && Y >= 2 && Z < 2 && W < 2)
	{
		n256d swap = _mm256_permute2f128_pd(x, x, 0x3); // Reverse components 0b00110000
		return _mm256_permute_pd(swap, (X == 2 ? 0 : 1) | ((Y == 2 ? 0 : 1) << 1) | ((Z == 0 ? 0 : 1) << 2) | ((W == 0 ? 0 : 1) << 3));
	}
	// Covers XXXX, YYYY, ZZZZ, WWWW
	else hlslpp_constexpr_if(X == Y && X == Z && X == W)
	{
		n256d shuf = _mm256_permute2f128_pd(x, x, (X == 0 || X == 1) ? 0x0 : 0x11); // Select the same component for both
		return _mm256_permute_pd(shuf, ((X % 2) << 3) | ((X % 2) << 2) | ((X % 2) << 1) | (X % 2));
	}
	// Covers the generic case, but is more inefficient
	else
	{
		n256d shuf0 = _mm256_permute2f128_pd(x, x, (X >= 2 ? 0x01 : 0x0) | (Z >= 2 ? 0x10 : 0x0));
		n256d splat0 = _mm256_permute_pd(shuf0, ((Z % 2) << 3) | ((Z % 2) << 2) | ((X % 2) << 1) | (X % 2));

		n256d shuf1 = _mm256_permute2f128_pd(x, x, (Y >= 2 ? 0x01 : 0x0) | (W >= 2 ? 0x10 : 0x0));
		n256d splat1 = _mm256_permute_pd(shuf1, ((W % 2) << 3) | ((W % 2) << 2) | ((Y % 2) << 1) | (Y % 2));

		return _mm256_blend_pd(splat0, splat1, HLSLPP_BLEND_MASK(1, 0, 1, 0));
	}

#endif
}

template<>
hlslpp_inline n256d permute_double<0, 1, 2, 3>(n256d x)
{
	return x;
}

#define _hlslpp256_perm_pd(x, X, Y, Z, W)	permute_double<X, Y, Z, W>(x)
//#define _hlslpp256_shuffle_pd(x, y, mask)		_mm256_shuffle_pd((x), (y), (mask))

hlslpp_inline bool _hlslpp256_any3_pd(n256d x)
{
	return ((_mm256_movemask_pd(_hlslpp256_cmpeq_pd(x, _mm256_setzero_pd())) & 0x7) != 0x7);
}

hlslpp_inline bool _hlslpp256_any4_pd(n256d x)
{
	return (_mm256_movemask_pd(_hlslpp256_cmpeq_pd(x, _mm256_setzero_pd())) != 0xf);
}

hlslpp_inline bool _hlslpp256_all3_pd(n256d x)
{
	return ((_mm256_movemask_pd(_hlslpp256_cmpeq_pd(x, _mm256_setzero_pd())) & 0x7) == 0);
}

hlslpp_inline bool _hlslpp256_all4_pd(n256d x)
{
	return (_mm256_movemask_pd(_hlslpp256_cmpeq_pd(x, _mm256_setzero_pd())) == 0);
}

hlslpp_inline void _hlslpp256_store3_pd(double* dst, n256d src)
{
	_mm_storeu_pd(dst, _hlslpp256_low_pd(src)); // Store bottom two
	_mm_store_sd(dst + 2, _hlslpp256_high_pd(src));
}

hlslpp_inline void _hlslpp256_store4_pd(double* dst, n256d src)
{
	_mm256_storeu_pd(dst, src);
}

hlslpp_inline void _hlslpp256_load3_pd(n256d& dst, const double* src)
{
	dst = _mm256_loadu_pd(src);
}

hlslpp_inline void _hlslpp256_load4_pd(n256d& dst, const double* src)
{
	dst = _mm256_loadu_pd(src);
}

#endif

//-------------
// Data Packing
//-------------

hlslpp_inline uint32_t _hlslpp_pack_epu32_rgba8_unorm(__m128 v)
{
	__m128 v255f = _hlslpp_madd_ps(v, _mm_set1_ps(255.0f), _mm_set1_ps(0.5f));
	__m128i v255i = _mm_cvttps_epi32(v255f);

#if defined(__SSSE3__)
	__m128i packed8 = _mm_shuffle_epi8(v255i, _mm_set1_epi32(0x0C080400));
#else
	__m128i packed16 = _mm_packus_epi16(v255i, v255i);
	__m128i packed8 = _mm_packus_epi16(packed16, packed16);
#endif

	return (uint32_t)_mm_cvtsi128_si32(packed8);
}

hlslpp_inline __m128 _hlslpp_unpack_rgba8_unorm_epu32(uint32_t p)
{
	__m128i i = _mm_set1_epi32((int)p);
	__m128 t = _mm_cvtepi32_ps(_hlslpp_cvtepu8_epi32(i));
	return _mm_mul_ps(t, _hlslpp_set1_ps(1.0f / 255.0f));
}

hlslpp_inline uint32_t _hlslpp_pack_epu32_rgba8_snorm(__m128 v)
{
	// Copy sign from x to 0.5
	__m128 vbias = _mm_or_ps(_mm_set1_ps(0.5f), _mm_and_ps(v, _mm_castsi128_ps(_mm_set1_epi32((int)0x80000000u))));
	__m128 v127f = _hlslpp_madd_ps(v, _mm_set1_ps(127.0f), vbias);
	__m128i v127i = _mm_cvttps_epi32(v127f);
#if defined(__SSSE3__)
	__m128i packed8 = _mm_shuffle_epi8(v127i, _mm_set1_epi32(0x0C080400));
#else
	__m128i packed16 = _mm_packs_epi16(v127i, v127i);
	__m128i packed8 = _mm_packs_epi16(packed16, packed16);
#endif
	return (uint32_t)_mm_cvtsi128_si32(packed8);
}

hlslpp_inline __m128 _hlslpp_unpack_rgba8_snorm_epu32(uint32_t p)
{
	__m128i i = _mm_set1_epi32((int)p);
	__m128 t = _mm_cvtepi32_ps(_hlslpp_cvtepi8_epi32(i));
	return _mm_mul_ps(t, _hlslpp_set1_ps(1.0f / 127.0f));
}