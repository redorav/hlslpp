#pragma once

#include <wasm_simd128.h>

typedef __f32x4 n128;
typedef __i32x4 n128i;
typedef __i32x4 n128u;
typedef __i64x2 n128d;

//------
// Float
//------

#define _hlslpp_set1_ps(x)						wasm_f32x4_splat((x))
#define _hlslpp_set_ps(x, y, z, w)				wasm_f32x4_make((x), (y), (z), (w))
#define _hlslpp_setzero_ps()					wasm_f32x4_const_splat(0.0f)

#define _hlslpp_add_ps(x, y)					wasm_f32x4_add((x), (y))
#define _hlslpp_sub_ps(x, y)					wasm_f32x4_sub((x), (y))
#define _hlslpp_mul_ps(x, y)					wasm_f32x4_mul((x), (y))
#define _hlslpp_div_ps(x, y)					wasm_f32x4_div((x), (y))

#define _hlslpp_rcp_ps(x)						wasm_f32x4_div(wasm_f32x4_const_splat(1.0f), (x))

#define _hlslpp_neg_ps(x)						wasm_v128_xor((x), f4negativeMask)

#define _hlslpp_madd_ps(x, y, z)				wasm_f32x4_add(wasm_f32x4_mul((x), (y)), (z)) // x * y + z
#define _hlslpp_msub_ps(x, y, z)				wasm_f32x4_sub(wasm_f32x4_mul((x), (y)), (z)) // x * y - z
#define _hlslpp_subm_ps(x, y, z)				wasm_f32x4_sub((x), wasm_f32x4_mul((y), (z))) // x - y * z

// Reference http://www.liranuna.com/sse-intrinsics-optimizations-in-popular-compilers/
#define _hlslpp_abs_ps(x)						wasm_v128_and(wasm_i32x4_splat(0x7fffffff), (x))

#define _hlslpp_sqrt_ps(x)						wasm_f32x4_sqrt((x))
#define _hlslpp_rsqrt_ps(x)						wasm_f32x4_div(wasm_f32x4_const_splat(1.0f), wasm_f32x4_sqrt(x))

#define _hlslpp_cmpeq_ps(x, y)					wasm_f32x4_eq((x), (y))
#define _hlslpp_cmpneq_ps(x, y)					wasm_f32x4_ne((x), (y))

#define _hlslpp_cmpgt_ps(x, y)					wasm_f32x4_gt((x), (y))
#define _hlslpp_cmpge_ps(x, y)					wasm_f32x4_ge((x), (y))

#define _hlslpp_cmplt_ps(x, y)					wasm_f32x4_lt((x), (y))
#define _hlslpp_cmple_ps(x, y)					wasm_f32x4_le((x), (y))

#define _hlslpp_max_ps(x, y)					wasm_f32x4_pmax((x), (y))
#define _hlslpp_min_ps(x, y)					wasm_f32x4_pmin((x), (y))

#define _hlslpp_sel_ps(x, y, mask)				wasm_v128_xor((x), wasm_v128_and(mask, wasm_v128_xor((y), (x))))

#define _hlslpp_blend_ps(x, y, mask)			wasm_i32x4_shuffle(x, y, (mask & 1) ? 4 : 0, ((mask >> 1) & 1) ? 5 : 1, ((mask >> 2) & 1) ? 6 : 2, ((mask >> 3) & 1) ? 7 : 3)

#define _hlslpp_trunc_ps(x)						wasm_f32x4_trunc((x))
#define _hlslpp_floor_ps(x)						wasm_f32x4_floor((x))
#define _hlslpp_ceil_ps(x)						wasm_f32x4_ceil((x))
#define _hlslpp_round_ps(x)						wasm_f32x4_nearest((x))

#define _hlslpp_frac_ps(x)						wasm_f32x4_sub((x), wasm_f32x4_floor(x))

#define _hlslpp_clamp_ps(x, minx, maxx)			wasm_f32x4_pmax(wasm_f32x4_pmin((x), (maxx)), (minx))
#define _hlslpp_sat_ps(x)						wasm_f32x4_pmax(wasm_f32x4_pmin((x), wasm_f32x4_const_splat(1.0f)), wasm_f32x4_const_splat(0.0f))

#define _hlslpp_and_ps(x, y)					wasm_v128_and((x), (y))
#define _hlslpp_andnot_ps(x, y)					wasm_v128_andnot((x), (y))
#define _hlslpp_not_ps(x)						wasm_v128_andnot((x), f4_fff)
#define _hlslpp_or_ps(x, y)						wasm_v128_or((x), (y))
#define _hlslpp_xor_ps(x, y)					wasm_v128_xor((x), (y))

// Equivalent to shuffle(x, y, X, Y, X, Y)
#define _hlslpp_movelh_ps(x, y)					wasm_i32x4_shuffle((x), (y), 0, 1, 4, 5)

// Equivalent to shuffle(y, x, Z, W, Z, W)
#define _hlslpp_movehl_ps(x, y)					wasm_i32x4_shuffle((x), (y), 2, 3, 6, 7)

// Equivalent to shuffle(x, x, Y, Y, W, W)
#define _hlslpp_movehdup_ps(x)					wasm_i32x4_shuffle((x), (x), 1, 1, 7, 7)

#define _hlslpp_perm_ps(x, X, Y, Z, W)			wasm_i32x4_shuffle((x), (x), X, Y, Z, W)

#define _hlslpp_shuffle_ps(x, y, X, Y, A, B)	wasm_i32x4_shuffle((x), (y), X, Y, 4 + A, 4 + B)

#define _hlslpp_unpacklo_ps(x, y)				wasm_i32x4_shuffle((x), (y), 0, 4, 1, 5)

#define _hlslpp_unpackhi_ps(x, y)				wasm_i32x4_shuffle((x), (y), 2, 6, 3, 7)

hlslpp_inline n128 _hlslpp_dot4_ps(n128 x, n128 y)
{
	n128 mul    = wasm_f32x4_mul(x, y);                      // Multiply components
	n128 shuf   = wasm_i32x4_shuffle(mul, mul, 1, 0, 3, 0);  // Move y into x, and w into z (ignore the rest)
	n128 add    = wasm_f32x4_add(shuf, mul);                 // Contains x+y, _, z+w, _
	shuf        = wasm_i32x4_shuffle(shuf, add, 2, 0, 0, 0); // Move (z + w) into x
	n128 result = wasm_f32x4_add(add, shuf);                 // Contains x+y+z+w, _, _, _
	return result;
}

hlslpp_inline bool _hlslpp_any1_ps(n128 x)
{
	return (wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) & 0x1) != 0x1;
}

hlslpp_inline bool _hlslpp_any2_ps(n128 x)
{
	return (wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) & 0x3) != 0x3;
}

hlslpp_inline bool _hlslpp_any3_ps(n128 x)
{
	return (wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) & 0x7) != 0x7;
}

hlslpp_inline bool _hlslpp_any4_ps(n128 x)
{
	return wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) != 0xf;
}

hlslpp_inline bool _hlslpp_all1_ps(n128 x)
{
	return (wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) & 0x1) == 0;
}

hlslpp_inline bool _hlslpp_all2_ps(n128 x)
{
	return (wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) & 0x3) == 0;
}

hlslpp_inline bool _hlslpp_all3_ps(n128 x)
{
	return (wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) & 0x7) == 0;
}

hlslpp_inline bool _hlslpp_all4_ps(n128 x)
{
	return wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) == 0;
}

//-----------------
// Float Store/Load
//-----------------

hlslpp_inline void _hlslpp_store1_ps(float* p, n128 x)
{
	wasm_v128_store32_lane(p, x, 0);
}

hlslpp_inline void _hlslpp_store2_ps(float* p, n128 x)
{
	wasm_v128_store64_lane(p, x, 0);
}

hlslpp_inline void _hlslpp_store3_ps(float* p, n128 x)
{
	wasm_v128_store64_lane(p, x, 0);
	wasm_v128_store32_lane(p + 2, x, 2);
}

hlslpp_inline void _hlslpp_store4_ps(float* p, n128 x)
{
	wasm_v128_store(p, x);
}

// Store first 3, store second 3, store last 2 and then the last one
// We need to do it this way to avoid stomping memory outside the provided buffer
hlslpp_inline void _hlslpp_store3x3_ps(float* p, n128 x0, n128 x1, n128 x2)
{
	wasm_v128_store(p, x0);
	wasm_v128_store(p + 3, x1);
	wasm_v128_store64_lane(p + 6, x2, 0);
	wasm_v128_store32_lane(p + 8, x2, 2);
}

hlslpp_inline void _hlslpp_store4x4_ps(float* p, const n128& x0, const n128& x1, const n128& x2, const n128& x3)
{
	wasm_v128_store(p, x0);
	wasm_v128_store(p + 4, x1);
	wasm_v128_store(p + 8, x2);
	wasm_v128_store(p + 12, x3);
}

hlslpp_inline void _hlslpp_load1_ps(float* p, n128& x)
{
	x = wasm_v128_load32_lane(p, x, 0);
}

hlslpp_inline void _hlslpp_load2_ps(float* p, n128& x)
{
	x = wasm_v128_load64_lane(p, x, 0);
}

hlslpp_inline void _hlslpp_load3_ps(float* p, n128& x)
{
	x = wasm_i32x4_shuffle(wasm_v128_load64_lane(p, x, 0), wasm_v128_load32_lane(p + 2, x, 0), 0, 1, 4, 5);
}

hlslpp_inline void _hlslpp_load4_ps(float* p, n128& x)
{
	x = wasm_v128_load(p);
}

hlslpp_inline void _hlslpp_load3x3_ps(float* p, n128& x0, n128& x1, n128& x2)
{
	x0 = wasm_v128_load(p);
	x1 = wasm_v128_load(p + 3);
	x2 = wasm_v128_load(p + 6);
}

hlslpp_inline void _hlslpp_load4x4_ps(float* p, n128& x0, n128& x1, n128& x2, n128& x3)
{
	x0 = wasm_v128_load(p);
	x1 = wasm_v128_load(p + 4);
	x2 = wasm_v128_load(p + 8);
	x3 = wasm_v128_load(p + 12);
}

//--------
// Integer
//--------

#define _hlslpp_set1_epi32(x)					wasm_i32x4_splat((x))
#define _hlslpp_set_epi32(x, y, z, w)			wasm_i32x4_make((x), (y), (z), (w))
#define _hlslpp_setzero_epi32()					wasm_i32x4_const_splat(0)

#define _hlslpp_add_epi32(x, y)					wasm_i32x4_add((x), (y))
#define _hlslpp_sub_epi32(x, y)					wasm_i32x4_sub((x), (y))
#define _hlslpp_mul_epi32(x, y)					wasm_i32x4_mul((x), (y))
#define _hlslpp_div_epi32(x, y)					wasm_i32x4_trunc_sat_f32x4(wasm_f32x4_div(wasm_f32x4_convert_i32x4(x), wasm_f32x4_convert_i32x4(y)))

#define _hlslpp_neg_epi32(x)					wasm_i32x4_add(wasm_v128_xor((x), i4fffMask), wasm_i32x4_const_splat(1))

#define _hlslpp_madd_epi32(x, y, z)				wasm_i32x4_add(wasm_i32x4_mul((x), (y)), (z))
#define _hlslpp_msub_epi32(x, y, z)				wasm_i32x4_sub(wasm_i32x4_mul((x), (y)), (z))
#define _hlslpp_subm_epi32(x, y, z)				wasm_i32x4_sub((x), wasm_i32x4_mul((y), (z)))

#define _hlslpp_abs_epi32(x)					wasm_i32x4_abs((x))

#define _hlslpp_cmpeq_epi32(x, y)				wasm_i32x4_eq((x), (y))
#define _hlslpp_cmpneq_epi32(x, y)				wasm_i32x4_ne((x), (y))

#define _hlslpp_cmpgt_epi32(x, y)				wasm_i32x4_gt((x), (y))
#define _hlslpp_cmpge_epi32(x, y)				wasm_i32x4_ge((x), (y))

#define _hlslpp_cmplt_epi32(x, y)				wasm_i32x4_lt((x), (y))
#define _hlslpp_cmple_epi32(x, y)				wasm_i32x4_le((x), (y))

#define _hlslpp_max_epi32(x, y)					wasm_i32x4_max((x), (y))
#define _hlslpp_min_epi32(x, y)					wasm_i32x4_min((x), (y))

#define _hlslpp_sel_epi32(x, y, mask)			wasm_v128_xor((x), wasm_v128_and(mask, wasm_v128_xor((y), (x))))

#define _hlslpp_blend_epi32(x, y, mask)			wasm_i32x4_shuffle(x, y, (mask & 1) ? 4 : 0, ((mask >> 1) & 1) ? 5 : 1, ((mask >> 2) & 1) ? 6 : 2, ((mask >> 3) & 1) ? 7 : 3)

#define _hlslpp_clamp_epi32(x, minx, maxx)		wasm_i32x4_max(wasm_i32x4_min((x), (maxx)), (minx))
#define _hlslpp_sat_epi32(x)					wasm_i32x4_max(wasm_i32x4_min((x), i4_1), i4_0)

#define _hlslpp_and_si128(x, y)					wasm_v128_and((x), (y))
#define _hlslpp_andnot_si128(x, y)				wasm_v128_andnot((x), (y))
#define _hlslpp_not_si128(x)					wasm_v128_andnot((x), i4fffMask)
#define _hlslpp_or_si128(x, y)					wasm_v128_or((x), (y))
#define _hlslpp_xor_si128(x, y)					wasm_v128_xor((x), (y))

#define _hlslpp_perm_epi32(x, X, Y, Z, W)		wasm_i32x4_shuffle((x), (x), X, Y, Z, W)
#define _hlslpp_shuffle_epi32(x, y, X, Y, A, B)	wasm_i32x4_shuffle((x), (y), X, Y, 4 + A, 4 + B)

#define _hlslpp_castps_si128(x)					(x)
#define _hlslpp_castsi128_ps(x)					(x)

#define _hlslpp_cvtepi32_ps(x)					wasm_f32x4_convert_i32x4((x))
#define _hlslpp_cvttps_epi32(x)					wasm_i32x4_trunc_sat_f32x4((x))

// Shift left/right while shifting in zeroes
#define _hlslpp_slli_epi32(x, y)				wasm_i32x4_shl((x), (y))
#define _hlslpp_srli_epi32(x, y)				wasm_i32x4_shr((x), (y))

#define _hlslpp_sllv_epi32(x, y)				(x) // _mm_sllv_epi32((x), (y))
#define _hlslpp_srlv_epi32(x, y)				(x) // _mm_srlv_epi32((x), (y))

hlslpp_inline bool _hlslpp_any1_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xf) != 0xf;
}

hlslpp_inline bool _hlslpp_any2_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xff) != 0xff;
}

hlslpp_inline bool _hlslpp_any3_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xfff) != 0xfff;
}

hlslpp_inline bool _hlslpp_any4_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xffff) != 0xffff;
}

hlslpp_inline bool _hlslpp_all1_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xf) == 0;
}

hlslpp_inline bool _hlslpp_all2_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xff) == 0;
}

hlslpp_inline bool _hlslpp_all3_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xfff) == 0;
}

hlslpp_inline bool _hlslpp_all4_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xffff) == 0;
}

//-------------------
// Integer Store/Load
//-------------------

hlslpp_inline void _hlslpp_store1_epi32(int32_t* p, n128i x)
{
	wasm_v128_store32_lane(p, x, 0);
}

hlslpp_inline void _hlslpp_store2_epi32(int32_t* p, n128i x)
{
	wasm_v128_store64_lane(p, x, 0);
}

hlslpp_inline void _hlslpp_store3_epi32(int32_t* p, n128i x)
{
	wasm_v128_store64_lane(p, x, 0);
	wasm_v128_store32_lane(p + 2, x, 2);
}

hlslpp_inline void _hlslpp_store4_epi32(int32_t* p, n128i x)
{
	wasm_v128_store(p, x);
}

hlslpp_inline void _hlslpp_load1_epi32(int32_t* p, n128i& x)
{
	x = wasm_v128_load32_lane(p, x, 0);
}

hlslpp_inline void _hlslpp_load2_epi32(int32_t* p, n128i& x)
{
	x = wasm_v128_load64_lane(p, x, 0);
}

hlslpp_inline void _hlslpp_load3_epi32(int32_t* p, n128i& x)
{
	x = wasm_i32x4_shuffle(wasm_v128_load64_lane(p, x, 0), wasm_v128_load32_lane(p, x, 2), 0, 1, 3, 4);
}

hlslpp_inline void _hlslpp_load4_epi32(int32_t* p, n128i& x)
{
	x = wasm_v128_load(p);
}

//-----------------
// Unsigned Integer
//-----------------

#define _hlslpp_set1_epu32(x)					wasm_u32x4_splat((x))
#define _hlslpp_set_epu32(x, y, z, w)			wasm_u32x4_make((x), (y), (z), (w))
#define _hlslpp_setzero_epu32()					wasm_u32x4_const_splat(0)

#define _hlslpp_add_epu32(x, y)					wasm_i32x4_add((x), (y))
#define _hlslpp_sub_epu32(x, y)					wasm_i32x4_sub((x), (y))
#define _hlslpp_mul_epu32(x, y)					wasm_i32x4_mul((x), (y))
#define _hlslpp_div_epu32(x, y)					_hlslpp_div_epi32((x), (y))

#define _hlslpp_madd_epu32(x, y, z)				wasm_i32x4_add(wasm_i32x4_mul((x), (y)), (z))
#define _hlslpp_msub_epu32(x, y, z)				wasm_i32x4_sub(wasm_i32x4_mul((x), (y)), (z))
#define _hlslpp_subm_epu32(x, y, z)				wasm_i32x4_sub((x), wasm_i32x4_mul((y), (z)))

#define _hlslpp_cmpeq_epu32(x, y)				wasm_i32x4_eq((x), (y))
#define _hlslpp_cmpneq_epu32(x, y)				wasm_i32x4_ne((x), (y))

#define _hlslpp_cmpgt_epu32(x, y)				wasm_u32x4_gt((x), (y))
#define _hlslpp_cmpge_epu32(x, y)				wasm_u32x4_ge((x), (y))

#define _hlslpp_cmplt_epu32(x, y)				wasm_u32x4_lt((x), (y))
#define _hlslpp_cmple_epu32(x, y)				wasm_u32x4_le((x), (y))

#define _hlslpp_max_epu32(x, y)					wasm_u32x4_max((x), (y))
#define _hlslpp_min_epu32(x, y)					wasm_u32x4_min((x), (y))

#define _hlslpp_sel_epu32(x, y, mask)			_hlslpp_sel_epi32((x), (y), (mask))
#define _hlslpp_blend_epu32(x, y, mask)			_hlslpp_blend_epi32((x), (y), (mask))

#define _hlslpp_clamp_epu32(x, minx, maxx)		_hlslpp_max_epu32(_hlslpp_min_epu32((x), (maxx)), (minx))
#define _hlslpp_sat_epu32(x)					_hlslpp_max_epu32(_hlslpp_min_epu32((x), i4_1), i4_0)

#define _hlslpp_perm_epu32(x, X, Y, Z, W)		_hlslpp_perm_epi32((x), X, Y, Z, W)
#define _hlslpp_shuffle_epu32(x, y, X, Y, A, B)	_hlslpp_shuffle_epi32((x), (y), X, Y, A, B)

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
hlslpp_inline void _hlslpp_load1_epu32(uint32_t* p, n128u& x) { _hlslpp_load1_epi32((int32_t*)p, x); }
hlslpp_inline void _hlslpp_load2_epu32(uint32_t* p, n128u& x) { _hlslpp_load2_epi32((int32_t*)p, x); }
hlslpp_inline void _hlslpp_load3_epu32(uint32_t* p, n128u& x) { _hlslpp_load3_epi32((int32_t*)p, x); }
hlslpp_inline void _hlslpp_load4_epu32(uint32_t* p, n128u& x) { _hlslpp_load4_epi32((int32_t*)p, x); }

//-------------
// Data Packing
//-------------

hlslpp_inline uint32_t _hlslpp_pack_epu32_rgba8_unorm(__f32x4 v)
{
	__f32x4 v255f = _hlslpp_madd_ps(v, wasm_f32x4_const_splat(255.0f), wasm_f32x4_const_splat(0.5f));
	__i32x4 v255i = wasm_i32x4_trunc_sat_f32x4(v255f);
	return wasm_i8x16_shuffle(v255i, v255i, 0, 4, 8, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)[0];
}

hlslpp_inline __f32x4 _hlslpp_unpack_rgba8_unorm_epu32(uint32_t p)
{
	__i32x4 i = wasm_u32x4_splat(p);
	__f32x4 t = wasm_f32x4_convert_u32x4(wasm_u32x4_extend_low_u16x8(wasm_u16x8_extend_low_u8x16(i)));
	return wasm_f32x4_mul(t, wasm_f32x4_const_splat(1.0f / 255.0f));
}

inline uint32_t _hlslpp_pack_epu32_rgba8_snorm(__f32x4 v)
{
	// Copy sign from x to 0.5
	__f32x4 vbias = wasm_v128_or(wasm_f32x4_const_splat(0.5f), wasm_v128_and(v, wasm_i32x4_const_splat(0x80000000u)));
	__f32x4 v127f = _hlslpp_madd_ps(v, wasm_f32x4_const_splat(127.0f), vbias);
	__i32x4 v127i = wasm_i32x4_trunc_sat_f32x4(v127f);
	return wasm_i8x16_shuffle(v127i, v127i, 0, 4, 8, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)[0];
}

inline __f32x4 _hlslpp_unpack_rgba8_snorm_epu32(uint32_t p)
{
	__i32x4 i = wasm_u32x4_splat(p);
	__f32x4 t = wasm_f32x4_convert_i32x4(wasm_i32x4_extend_low_i16x8(wasm_i16x8_extend_low_i8x16(i)));
	return wasm_f32x4_mul(t, wasm_f32x4_const_splat(1.0f / 127.0f));
}