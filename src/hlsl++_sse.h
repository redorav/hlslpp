#pragma once

#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

using n128 = __m128;
using n128i = __m128i;

#define _hlslpp_set1_ps(x)						_mm_set1_ps((x))
#define _hlslpp_set_ps(x, y, z, w)				_mm_set_ps((w), (z), (y), (x))

#define _hlslpp_set1_epi32(x)					_mm_set1_epi32((x))
#define _hlslpp_set_epi32(x, y, z, w)			_mm_set_epi32((w), (z), (y), (x))

#define _hlslpp_add_ps(x, y)					_mm_add_ps((x), (y))
#define _hlslpp_sub_ps(x, y)					_mm_sub_ps((x), (y))
#define _hlslpp_mul_ps(x, y)					_mm_mul_ps((x), (y))
#define _hlslpp_div_ps(x, y)					_mm_div_ps((x), (y))

// The following are alternatives but have been measured to be slower
// _mm_sub_ps(f4zero, v.xyzw);			// Slowest
// _mm_mul_ps(f4minusOne, v.xyzw);		// Slower
#define _hlslpp_neg_ps(x)						_mm_xor_ps((x), f4negativeMask)

#define _hlslpp_madd_ps(x, y, z)				_mm_add_ps(_mm_mul_ps((x), (y)), (z))
#define _hlslpp_msub_ps(x, y, z)				_mm_sub_ps(_mm_mul_ps((x), (y)), (z))

// Reference http://www.liranuna.com/sse-intrinsics-optimizations-in-popular-compilers/
#define _hlslpp_abs_ps(x)						_mm_and_ps(f4absMask, (x))

#define _hlslpp_sqrt_ps(x)						_mm_sqrt_ps((x))

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

#define _hlslpp_frac_ps(x)						_mm_sub_ps((x), _mm_floor_ps(x))

#define _hlslpp_clamp_ps(x, minx, maxx)			_mm_max_ps(_mm_min_ps((x), (maxx)), (minx))
#define _hlslpp_sat_ps(x)						_mm_max_ps(_mm_min_ps((x), f4_1), f4_0)

#define _hlslpp_and_ps(x, y)					_mm_and_ps((x), (y))
#define _hlslpp_andnot_ps(x, y)					_mm_andnot_ps((x), (y))
#define _hlslpp_or_ps(x, y)						_mm_or_ps((x), (y))

#define _hlslpp_perm_ps(x, X, Y, Z, W)			_mm_shuffle_ps((x), (x), _MM_SHUFFLE(W, Z, Y, X))

// SSE2 alternative https://markplusplus.wordpress.com/2007/03/14/fast-sse-select-operation/
// _mm_xor_ps((x), _mm_and_ps(msk, _mm_xor_ps((y), (x))))
// Bit-select val1 and val2 based on the contents of the mask
#define _hlslpp_sel_ps(x, y, msk)				_mm_blendv_ps((x), (y), (msk))

#define _hlslpp_blend_ps(x, y, msk)				_mm_blend_ps((x), (y), (msk))

// Integer

#define _hlslpp_add_epi32(x, y)					_mm_add_epi32((x), (y))
#define _hlslpp_sub_epi32(x, y)					_mm_sub_epi32((x), (y))
#define _hlslpp_mul_epi32(x, y)					_mm_mul_epi32((x), (y))

#define _hlslpp_and_si128(x, y)					_mm_and_si128((x), (y))
#define _hlslpp_or_si128(x, y)					_mm_or_si128((x), (y))

#define _hlslpp_castps_si128(x)					_mm_castps_si128((x))
#define _hlslpp_castsi128_ps(x)					_mm_castsi128_ps((x))

#define _hlslpp_cvtepi32_ps(x)					_mm_cvtepi32_ps((x))
#define _hlslpp_cvtps_epi32(x)					_mm_cvtps_epi32((x))

#define _hlslpp_slli_epi32(x, y)				_mm_slli_epi32((x), (y))
#define _hlslpp_srli_epi32(x, y)				_mm_srli_epi32((x), (y))

#define _hlslpp_shuffle_ps(x, y, X, Y, Z, W)	_mm_shuffle_ps(x, y, _MM_SHUFFLE(W, Z, Y, X))