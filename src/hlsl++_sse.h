#pragma once

#if defined(_MSC_VER)

#include <immintrin.h>
#include <ammintrin.h>

#else
#include <x86intrin.h>
#endif

using n128 = __m128;
using n128i = __m128i;

//------
// Float
//------

#define _hlslpp_set1_ps(x)						_mm_set1_ps((x))
#define _hlslpp_set_ps(x, y, z, w)				_mm_set_ps((w), (z), (y), (x))

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
// _mm_sub_ps(f4zero, v.xyzw);			// Slowest
// _mm_mul_ps(f4minusOne, v.xyzw);		// Slower
#define _hlslpp_neg_ps(x)						_mm_xor_ps((x), f4negativeMask)

#define _hlslpp_madd_ps(x, y, z)				_mm_add_ps(_mm_mul_ps((x), (y)), (z))
#define _hlslpp_msub_ps(x, y, z)				_mm_sub_ps(_mm_mul_ps((x), (y)), (z))
#define _hlslpp_subm_ps(x, y, z)				_mm_sub_ps((x), _mm_mul_ps((y), (z)))

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

#define _hlslpp_movehl_ps(x, y)					_mm_movehl_ps((x), (y))
#define _hlslpp_movehdup_ps(x)					_mm_movehdup_ps((x))

#define _hlslpp_perm_ps(x, msk)					_mm_shuffle_ps((x), (x), msk)
#define _hlslpp_shuffle_ps(x, y, msk)			_mm_shuffle_ps((x), (y), msk)

// SSE2 alternative https://markplusplus.wordpress.com/2007/03/14/fast-sse-select-operation/
// _mm_xor_ps((x), _mm_and_ps(msk, _mm_xor_ps((y), (x))))
// Bit-select val1 and val2 based on the contents of the mask
#define _hlslpp_sel_ps(x, y, msk)				_mm_blendv_ps((x), (y), (msk))

#define _hlslpp_blend_ps(x, y, msk)				_mm_blend_ps((x), (y), (msk))

//--------
// Integer
//--------

#define _hlslpp_set1_epi32(x)					_mm_set1_epi32((x))
#define _hlslpp_set_epi32(x, y, z, w)			_mm_set_epi32((w), (z), (y), (x))

#define _hlslpp_add_epi32(x, y)					_mm_add_epi32((x), (y))
#define _hlslpp_sub_epi32(x, y)					_mm_sub_epi32((x), (y))

// https://stackoverflow.com/questions/10500766/sse-multiplication-of-4-32-bit-integers
#define _hlslpp_mul_epi32(x, y)					_mm_mullo_epi32((x), (y))

#define _hlslpp_neg_epi32(x)					_mm_xor_si128((x), i4negativeMask)

#define _hlslpp_madd_epi32(x, y, z)				_mm_add_epi32(_mm_mullo_epi32((x), (y)), (z))
#define _hlslpp_msub_epi32(x, y, z)				_mm_sub_epi32(_mm_mullo_epi32((x), (y)), (z))
#define _hlslpp_subm_epi32(x, y, z)				_mm_sub_epi32((x), _mm_mullo_epi32((y), (z)))

#define _hlslpp_abs_epi32(x)					_mm_and_si128(i4absMask, (x))

#define _hlslpp_max_epi32(x, y)					_mm_max_epi32((x), (y))
#define _hlslpp_min_epi32(x, y)					_mm_min_epi32((x), (y))

#define _hlslpp_clamp_epi32(x, minx, maxx)		_mm_max_epi32(_mm_min_epi32((x), (maxx)), (minx))
#define _hlslpp_sat_epi32(x)					_mm_max_epi32(_mm_min_epi32((x), i4_1), i4_0)

#define _hlslpp_and_si128(x, y)					_mm_and_si128((x), (y))
#define _hlslpp_or_si128(x, y)					_mm_or_si128((x), (y))

// https://stackoverflow.com/questions/13153584/mm-shuffle-ps-equivalent-for-integer-vectors-m128i
#define _hlslpp_perm_epi32(x, msk)				_mm_shuffle_epi32((x), (msk))
#define _hlslpp_shuffle_epi32(x, y, msk)		_mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(x), _mm_castsi128_ps(y), (msk)))

// Reshuffle the mask because we use _mm_blend_epi16 as that's what's available in SSE4.1 
// _mm_blend_epi32 was added later in AVX2
#define _hlslpp_blend_epi32(x, y, msk)			_mm_blend_epi16((x), (y), ((msk & 1) * 3) | ((((msk >> 1) & 1) * 3) << 2) | ((((msk >> 2) & 1) * 3) << 4) | ((((msk >> 3) & 1) * 3) << 6))

#define _hlslpp_castps_si128(x)					_mm_castps_si128((x))
#define _hlslpp_castsi128_ps(x)					_mm_castsi128_ps((x))

#define _hlslpp_cvtepi32_ps(x)					_mm_cvtepi32_ps((x))
#define _hlslpp_cvtps_epi32(x)					_mm_cvtps_epi32((x))

#define _hlslpp_slli_epi32(x, y)				_mm_slli_epi32((x), (y))
#define _hlslpp_srli_epi32(x, y)				_mm_srli_epi32((x), (y))

#define HLSLPP_SHUFFLE_MASK(X, Y, Z, W)			(((W) << 6) | ((Z) << 4) | ((Y) << 2) | (X))

// Create a mask where 1 selects from x, 0 selects from y
#define HLSLPP_BLEND_MASK(X, Y, Z, W)			(~(X | (Y << 1) | (Z << 2) | (W << 3)) & 0xf)

hlslpp_inline n128i _hlslpp_sllv_epi32(n128i x, n128i count)
{
	n128i sb = _hlslpp_perm_epi32((count), HLSLPP_SHUFFLE_MASK(1, 0, 0, 0));
	n128i sc = _hlslpp_perm_epi32((count), HLSLPP_SHUFFLE_MASK(2, 0, 0, 0));

	n128i im0 = _hlslpp_set_epi32(0xffffffff, 0, 0, 0);

	n128i imask0 = _hlslpp_and_si128(count, im0);
	n128i imask1 = _hlslpp_and_si128(sb, im0);
	n128i imask2 = _hlslpp_and_si128(sc, im0);
	n128i imask3 = _mm_srli_epi32(count, 96);

	n128i ic0 = _mm_sll_epi32(x, imask0);
	n128i ic1 = _mm_sll_epi32(x, imask1);
	n128i ic2 = _mm_sll_epi32(x, imask2);
	n128i ic3 = _mm_sll_epi32(x, imask3);

	n128i blend0 = _hlslpp_blend_epi32(ic0, ic1, HLSLPP_BLEND_MASK(1, 0, 0, 0));
	n128i blend1 = _hlslpp_blend_epi32(ic2, ic3, HLSLPP_BLEND_MASK(0, 0, 1, 0));

	n128i result = _hlslpp_blend_epi32(blend0, blend1, HLSLPP_BLEND_MASK(1, 1, 0, 0));

	return result;
}

hlslpp_inline n128i _hlslpp_srlv_epi32(n128i x, n128i count)
{
	n128i sb = _hlslpp_perm_epi32((count), HLSLPP_SHUFFLE_MASK(1, 0, 0, 0));
	n128i sc = _hlslpp_perm_epi32((count), HLSLPP_SHUFFLE_MASK(2, 0, 0, 0));

	n128i im0 = _hlslpp_set_epi32(0xffffffff, 0, 0, 0);

	n128i imask0 = _hlslpp_and_si128(count, im0);
	n128i imask1 = _hlslpp_and_si128(sb, im0);
	n128i imask2 = _hlslpp_and_si128(sc, im0);
	n128i imask3 = _hlslpp_srli_epi32(count, 96);

	n128i ic0 = _mm_srl_epi32(x, imask0);
	n128i ic1 = _mm_srl_epi32(x, imask1);
	n128i ic2 = _mm_srl_epi32(x, imask2);
	n128i ic3 = _mm_srl_epi32(x, imask3);

	n128i blend0 = _hlslpp_blend_epi32(ic0, ic1, HLSLPP_BLEND_MASK(1, 0, 0, 0));
	n128i blend1 = _hlslpp_blend_epi32(ic2, ic3, HLSLPP_BLEND_MASK(0, 0, 1, 0));

	n128i result = _hlslpp_blend_epi32(blend0, blend1, HLSLPP_BLEND_MASK(1, 1, 0, 0));

	return result;
}

//--------
// Storing
//--------

#define _hlslpp_store1_ps(p, x)					_mm_store_ss((p), (x))
#define _hlslpp_store2_ps(p, x)					_mm_store_ss((p), x); _mm_store_ss((p) + 1, _hlslpp_perm_yyyy_ps(x))
#define _hlslpp_store3_ps(p, x)					_mm_store_ss((p), x); _mm_store_ss((p) + 1, _hlslpp_perm_yyyy_ps(x)); _mm_store_ss((p) + 2, _hlslpp_perm_zzzz_ps(x))
#define _hlslpp_store4_ps(p, x)					_mm_storeu_ps((p), x);

// Store first 3, store second 3, store last 3, stomping one of the previous values but making sure it's the same
#define _hlslpp_store3x3_ps(p, x0, x1, x2)		_mm_storeu_ps((p), x0); _mm_storeu_ps((p) + 3, x1); _mm_storeu_ps((p) + 5, _hlslpp_blend_ps(_hlslpp_perm_zzzz_ps(x1), _hlslpp_perm_wxyz_ps(x2), HLSLPP_BLEND_MASK(1, 0, 0, 0)))
#define _hlslpp_store4x4_ps(p, x0, x1, x2, x3)	_mm_storeu_ps((p), x0); _mm_storeu_ps((p) + 4, x1); _mm_storeu_ps((p) + 8, x2); _mm_storeu_ps((p) + 12, x3)