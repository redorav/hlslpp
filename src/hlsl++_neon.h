#pragma once

#include <arm_neon.h>

// For NEON version check flags, see https://github.com/magnumripper/JohnTheRipper/issues/1998

using n128 = float32x4_t;
using n128i = int32x4_t;

typedef float32x4_t vec_float4; // for iOS
typedef uint32x4_t vec_uint4;

hlslpp_inline float32x4_t vmov4q_n_f32(const float x, const float y, const float z, const float w)
{
	const float values[4] = { x, y, z, w };
	return vld1q_f32(values);
}

hlslpp_inline int32x4_t vmov4q_n_s32(const int32_t x, const int32_t y, const int32_t z, const int32_t w)
{
	const int32_t values[4] = { x, y, z, w };
	return vld1q_s32(values);
}

hlslpp_inline uint32x4_t vmov4q_n_u32(const uint32_t x, const uint32_t y, const uint32_t z, const uint32_t w)
{
	const uint32_t values[4] = { x, y, z, w };
	return vld1q_u32(values);
}

// Source http://stackoverflow.com/questions/32536265/how-to-convert-mm-shuffle-ps-sse-intrinsic-to-neon-intrinsic
hlslpp_inline float32x4_t vpermq_f32(const float32x4_t x, const uint32_t X, const uint32_t Y, const uint32_t Z, const uint32_t W)
{
	static const uint32_t ControlMask[4] = { 0x03020100, 0x07060504, 0x0B0A0908, 0x0F0E0D0C }; // Swizzle x, swizzle y, swizzle z, swizzle w

	uint8x8x2_t tbl = { { vget_low_f32(x), vget_high_f32(x) } }; // Get floats

	const uint8x8_t idxL = vcreate_u8(((uint64_t)ControlMask[X]) | (((uint64_t)ControlMask[Y]) << 32));
	const uint8x8_t rL = vtbl2_u8(tbl, idxL);

	const uint8x8_t idxH = vcreate_u8(((uint64_t)ControlMask[Z]) | (((uint64_t)ControlMask[W]) << 32));
	const uint8x8_t rH = vtbl2_u8(tbl, idxH);

	return vcombine_f32(rL, rH);
}

hlslpp_inline float32x4_t vshufq_f32(const float32x4_t x, const float32x4_t y, const uint32_t X0, const uint32_t Y0, const uint32_t X1, const uint32_t Y1)
{
	static const uint32_t ControlMaskX[4] = { 0x03020100, 0x07060504, 0x0B0A0908, 0x0F0E0D0C }; // Swizzle X0, swizzle Y0, swizzle Z0, swizzle W0,
	static const uint32_t ControlMaskY[4] = { 0x13121110, 0x17161514, 0x1B1A1918, 0x1F1E1D1C }; // Swizzle X1, swizzle Y1, swizzle Z1, swizzle W1

	uint8x8x4_t tbl = { { vget_low_f32(x), vget_high_f32(x), vget_low_f32(y), vget_high_f32(y) } };

	const uint8x8_t idxL = vcreate_u8(((uint64_t)ControlMaskX[X0]) | (((uint64_t)ControlMaskX[Y0]) << 32));
	const uint8x8_t rL = vtbl4_u8(tbl, idxL);

	const uint8x8_t idxH = vcreate_u8(((uint64_t)ControlMaskY[X1]) | (((uint64_t)ControlMaskY[Y1]) << 32));
	const uint8x8_t rH = vtbl4_u8(tbl, idxH);

	return vcombine_f32(rL, rH);
}

// Source http://stackoverflow.com/questions/32536265/how-to-convert-mm-shuffle-ps-sse-intrinsic-to-neon-intrinsic
hlslpp_inline float32x4_t vpermq_s32(const float32x4_t x, const uint32_t X, const uint32_t Y, const uint32_t Z, const uint32_t W)
{
	static const uint32_t ControlMask[4] = { 0x03020100, 0x07060504, 0x0B0A0908, 0x0F0E0D0C }; // Swizzle x, swizzle y, swizzle z, swizzle w

	uint8x8x2_t tbl = { { vget_low_s32(x), vget_high_s32(x) } }; // Get ints

	const uint8x8_t idxL = vcreate_u8(((uint64_t)ControlMask[X]) | (((uint64_t)ControlMask[Y]) << 32));
	const uint8x8_t rL = vtbl2_u8(tbl, idxL);

	const uint8x8_t idxH = vcreate_u8(((uint64_t)ControlMask[Z]) | (((uint64_t)ControlMask[W]) << 32));
	const uint8x8_t rH = vtbl2_u8(tbl, idxH);

	return vcombine_f32(rL, rH);
}

hlslpp_inline float32x4_t vshufq_s32(const float32x4_t x, const float32x4_t y, const uint32_t X0, const uint32_t Y0, const uint32_t X1, const uint32_t Y1)
{
	static const uint32_t ControlMaskX[4] = { 0x03020100, 0x07060504, 0x0B0A0908, 0x0F0E0D0C }; // Swizzle X0, swizzle Y0, swizzle Z0, swizzle W0,
	static const uint32_t ControlMaskY[4] = { 0x13121110, 0x17161514, 0x1B1A1918, 0x1F1E1D1C }; // Swizzle X1, swizzle Y1, swizzle Z1, swizzle W1

	uint8x8x4_t tbl = { { vget_low_s32(x), vget_high_s32(x), vget_low_s32(y), vget_high_s32(y) } };

	const uint8x8_t idxL = vcreate_u8(((uint64_t)ControlMaskX[X0]) | (((uint64_t)ControlMaskX[Y0]) << 32));
	const uint8x8_t rL = vtbl4_u8(tbl, idxL);

	const uint8x8_t idxH = vcreate_u8(((uint64_t)ControlMaskY[X1]) | (((uint64_t)ControlMaskY[Y1]) << 32));
	const uint8x8_t rH = vtbl4_u8(tbl, idxH);

	return vcombine_f32(rL, rH);
}

// Source https://github.com/andrepuschmann/math-neon/blob/master/src/math_floorf.c
hlslpp_inline float32x4_t vfloorq_f32(float32x4_t x)
{
	float32x4_t trnc = vcvtq_f32_s32(vcvtq_s32_f32(x));				// Truncate
	float32x4_t gt = vcgtq_f32(trnc, x);							// Check if truncation was greater or smaller (i.e. was negative or positive number)
	uint32x4_t shr = vshrq_n_u32(vreinterpretq_u32_f32(gt), 31);	// Shift to leave a 1 or a 0
	float32x4_t result = vsubq_f32(trnc, vcvtq_f32_u32(shr));		// Subtract from truncated value
	return result;
}

// Source https://github.com/andrepuschmann/math-neon/blob/master/src/math_ceilf.c
hlslpp_inline float32x4_t vceilq_f32(float32x4_t x)
{
	float32x4_t trnc = vcvtq_f32_s32(vcvtq_s32_f32(x));				// Truncate
	float32x4_t gt = vcgtq_f32(trnc, x);							// Check if truncation was greater or smaller (i.e. was negative or positive number)
	uint32x4_t shr = vshrq_n_u32(vreinterpretq_u32_f32(gt), 31);	// Shift to leave a 1 or a 0
	float32x4_t result = vaddq_f32(trnc, vcvtq_f32_u32(shr));		// Add to truncated value
	return result;
}

hlslpp_inline float32x4_t vroundq_f32(float32x4_t x)
{
	float32x4_t add = vaddq_f32(x, vmovq_n_f32(0.5f));				// Add 0.5
	float32x4_t frc_add = vsubq_f32(add, vfloorq_f32(add));			// Get the fractional part
	float32x4_t result = vsubq_f32(add, frc_add);					// Subtract from result
	return result;
}

hlslpp_inline float32x4_t vrsqrtq_f32(float32x4_t x)
{
	float32x4_t e = vrsqrteq_f32(x);								// Calculate a first estimate of the rsqrt
	e = vmulq_f32(e, vrsqrtsq_f32(vmulq_f32(e, x), e));				// First Newton-Raphson iteration
	e = vmulq_f32(e, vrsqrtsq_f32(vmulq_f32(e, x), e));				// Second Newton-Raphson iteration
	return e;
}

// ARMv8 has these functions natively but we need to emulate them for ARMv7
#if __ARM_ARCH <= 7

hlslpp_inline float32x4_t vsqrtq_f32(float32x4_t x)
{
	uint32x4_t cmpZero = vceqq_f32(x, vmovq_n_f32(0.0f));							// Sqrt of 0 is NaN (since we use rsqrt to compute it) which is incorrect but we still want it to go NaN on negatives
	float32x4_t sqrt = vmulq_f32(x, vrsqrtq_f32(x));								// Multiply by x to get x * rqsrt(x)
	return vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(sqrt), cmpZero));	// Select 0 if input is 0
}

hlslpp_inline float32x4_t vdivq_f32(float32x4_t x, float32x4_t y)
{
	float32x4_t rcpy_e = vrecpeq_f32(y);					// Calculate a first estimate of the rcp
	rcpy_e = vmulq_f32(rcpy_e, vrecpsq_f32(y, rcpy_e));		// Refine
	rcpy_e = vmulq_f32(rcpy_e, vrecpsq_f32(y, rcpy_e));		// Refine
	return vmulq_f32(x, rcpy_e);							// Multiply by x
}

#endif

hlslpp_inline float32x4_t vrcpq_f32(float32x4_t x)
{
	float32x4_t rcpx_e = vrecpeq_f32(x);					// Calculate a first estimate of the rcp
	rcpx_e = vmulq_f32(rcpx_e, vrecpsq_f32(x, rcpx_e));		// Refine
	return vmulq_f32(rcpx_e, vrecpsq_f32(x, rcpx_e));		// Refine
}

//------
// Float
//------

#define _hlslpp_set1_ps(x)						vmovq_n_f32((x))
#define _hlslpp_set_ps(x, y, z, w)				vmov4q_n_f32((x), (y), (z), (w))

#define _hlslpp_add_ps(x, y)					vaddq_f32((x), (y))
#define _hlslpp_sub_ps(x, y)					vsubq_f32((x), (y))
#define _hlslpp_mul_ps(x, y)					vmulq_f32((x), (y))
#define _hlslpp_div_ps(x, y)					vdivq_f32(x, y)

// In NEON vadd_f32 produces the exact same instruction as vaddq_f32 so just define it as the same.
// These are only here for the benefit of SSE
#define _hlslpp_add_ss(x, y)					vaddq_f32((x), (y))
#define _hlslpp_sub_ss(x, y)					vsubq_f32((x), (y))
#define _hlslpp_mul_ss(x, y)					vmulq_f32((x), (y))
#define _hlslpp_div_ss(x, y)					vdivq_f32(x, y)

#define _hlslpp_rcp_ps(x)						vrcpq_f32((x))

#define _hlslpp_neg_ps(x)						veorq_u32(vreinterpretq_u32_f32((x)), vmovq_n_u32(0x80000000u))

#define _hlslpp_madd_ps(x, y, z)				vmlaq_f32((z), (x), (y))
#define _hlslpp_msub_ps(x, y, z)				_hlslpp_neg_ps(vmlsq_f32((z), (x), (y))) // Negate because vmlsq_f32 does z - x * y and we want x * y - z
#define _hlslpp_subm_ps(x, y, z)				vmlsq_f32((z), (x), (y))

#define _hlslpp_abs_ps(x)						vabsq_f32((x))

#define _hlslpp_sqrt_ps(x)						vsqrtq_f32((x))
#define _hlslpp_rsqrt_ps(x)						vrsqrtq_f32((x))

#define _hlslpp_cmpeq_ps(x, y)					vceqq_f32((x), (y))
#define _hlslpp_cmpneq_ps(x, y)					veorq_u32(vreinterpretq_u32_f32(vceqq_f32((x), (y))), vmovq_n_u32(0xffffffffu))

#define _hlslpp_cmpgt_ps(x, y)					vcgtq_f32((x), (y))
#define _hlslpp_cmpge_ps(x, y)					vcgeq_f32((x), (y))

#define _hlslpp_cmplt_ps(x, y)					vcltq_f32((x), (y))
#define _hlslpp_cmple_ps(x, y)					vcleq_f32((x), (y))

#define _hlslpp_max_ps(x, y)					vmaxq_f32((x), (y))
#define _hlslpp_min_ps(x, y)					vminq_f32((x), (y))

#define _hlslpp_trunc_ps(x)						vcvtq_f32_s32(vcvtq_s32_f32(x))
#define _hlslpp_floor_ps(x)						vfloorq_f32((x))
#define _hlslpp_ceil_ps(x)						vceilq_f32((x))
#define _hlslpp_round_ps(x)						vroundq_f32((x))

#define _hlslpp_frac_ps(x)						vsubq_f32((x), vfloorq_f32(x))

#define _hlslpp_clamp_ps(x, minx, maxx)			vmaxq_f32(vminq_f32((x), (maxx)), (minx))
#define _hlslpp_sat_ps(x)						vmaxq_f32(vminq_f32((x), f4_1), f4_0)

// http://codesuppository.blogspot.co.uk/2015/02/sse2neonh-porting-guide-and-header-file.html
#define _hlslpp_and_ps(x, y)					vreinterpretq_f32_u32(vandq_u32(vreinterpretq_u32_f32((x)), vreinterpretq_u32_f32((y))))
#define _hlslpp_andnot_ps(x, y)					vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32((x)), vreinterpretq_u32_f32((y))))
#define _hlslpp_or_ps(x, y)						vreinterpretq_f32_u32(vorrq_u32(vreinterpretq_u32_f32((x)), vreinterpretq_u32_f32((y))))
#define _hlslpp_xor_ps(x, y)					vreinterpretq_f32_u32(veorq_u32(vreinterpretq_u32_f32((x)), vreinterpretq_u32_f32((y))))

// SSE: Move the upper 2 single-precision (32-bit) floating-point elements from b to the lower 2 elements of dst, and copy the upper 2 elements from a to the upper 2 elements of dst.
#define _hlslpp_movehl_ps(x, y)					vcombine_f32(vget_high_f32(y), vget_high_f32(x))

// SSE: Duplicate odd-indexed single-precision (32-bit) floating-point elements from a, and store the results in dst.
#define _hlslpp_movehdup_ps(x)					vcombine_f32(vdup_lane_f32(vget_low_f32(x), 1), vdup_lane_f32(vget_high_f32(x), 1))

#define _hlslpp_perm_ps(x, msk)					vpermq_f32((x), msk & 3, (msk >> 2) & 3, (msk >> 4) & 3, (msk >> 6) & 3)
#define _hlslpp_shuffle_ps(x, y, msk)			vshufq_f32((x), (y), msk & 3, (msk >> 2) & 3, (msk >> 4) & 3, (msk >> 6) & 3)

#define _hlslpp_sel_ps(x, y, msk)				vbslq_f32((msk), (x), (y))

// We decompose the mask and turn it into 4 floats
// The input mask follows the format for SSE
#define _hlslpp_blend_ps(x, y, msk)				vbslq_f32(vmov4q_n_u32(~((msk & 1) * 0xffffffff), ~(((msk >> 1) & 1) * 0xffffffff), ~(((msk >> 2) & 1) * 0xffffffff), ~(((msk >> 3) & 1) * 0xffffffff)), (x), (y))

//--------
// Integer
//--------

#define _hlslpp_set1_epi32(x)					vmovq_n_s32((x))
#define _hlslpp_set_epi32(x, y, z, w)			vmov4q_n_s32((x), (y), (z), (w))

#define _hlslpp_add_epi32(x, y)					vaddq_s32((x), (y))
#define _hlslpp_sub_epi32(x, y)					vsubq_s32((x), (y))
#define _hlslpp_mul_epi32(x, y)					vmulq_s32((x), (y))

#define _hlslpp_neg_epi32(x)					veorq_u32((x), vmovq_n_u32(0x80000000u))

#define _hlslpp_madd_epi32(x, y, z)				vmlaq_s32((z), (x), (y))
#define _hlslpp_msub_epi32(x, y, z)				_hlslpp_neg_epi32(vmlsq_s32((z), (x), (y))) // Negate because vmlsq_u32 does z - x * y and we want x * y - z
#define _hlslpp_subm_epi32(x, y, z)				vmlsq_s32((z), (x), (y))

#define _hlslpp_abs_epi32(x)					vabsq_s32((x))

#define _hlslpp_max_epi32(x, y)					vmaxq_s32((x), (y))
#define _hlslpp_min_epi32(x, y)					vminq_s32((x), (y))

#define _hlslpp_clamp_epi32(x, minx, maxx)		vmaxq_s32(vminq_s32((x), (maxx)), (minx))
#define _hlslpp_sat_epi32(x)					vmaxq_s32(vminq_s32((x), i4_1), i4_0)

#define _hlslpp_and_si128(x, y)					vandq_s32((x), (y))
#define _hlslpp_or_si128(x, y)					vorrq_s32((x), (y))

#define _hlslpp_perm_epi32(x, msk)				vpermq_s32((x), msk & 3, (msk >> 2) & 3, (msk >> 4) & 3, (msk >> 6) & 3)
#define _hlslpp_shuffle_epi32(x, y, msk)		vshufq_s32((x), (y), msk & 3, (msk >> 2) & 3, (msk >> 4) & 3, (msk >> 6) & 3)

#define _hlslpp_blend_epi32(x, y, msk)			vbslq_s32(vmov4q_n_u32(~((msk & 1) * 0xffffffff), ~(((msk >> 1) & 1) * 0xffffffff), ~(((msk >> 2) & 1) * 0xffffffff), ~(((msk >> 3) & 1) * 0xffffffff)), (x), (y))

#define _hlslpp_castps_si128(x)					vreinterpretq_s32_f32((x))
#define _hlslpp_castsi128_ps(x)					vreinterpretq_f32_s32((x))

#define _hlslpp_cvtps_epi32(x)					vcvtq_s32_f32((x))
#define _hlslpp_cvtepi32_ps(x)					vcvtq_f32_s32((x))

#define _hlslpp_slli_epi32(x, y)				vshlq_n_s32((x), (y))
#define _hlslpp_srli_epi32(x, y)				vshrq_n_s32((x), (y))

#define _hlslpp_sllv_epi32(x, y)				vshlq_s32((x), (y))
#define _hlslpp_srlv_epi32(x, y)				vshrq_s32((x), (y))

//--------
// Storing
//--------

#define _hlslpp_store1_ps(p, x)					vst1q_lane_f32(p, x, 0)
#define _hlslpp_store2_ps(p, x)					vst1_f32(p, vget_low_f32(x))
#define _hlslpp_store3_ps(p, x)					vst1_f32(p, vget_low_f32(x)); vst1q_lane_f32(p, x, 2)
#define _hlslpp_store4_ps(p, x)					vst1q_f32(p, x);

#define _hlslpp_store3x3_ps(p, x0, x1, x2)		_hlslpp_store3_ps(p, x0); _hlslpp_store3_ps(p + 3, x1); _hlslpp_store3_ps(p + 5, x2)
#define _hlslpp_store4x4_ps(p, x0, x1, x2, x3)	_hlslpp_store4_ps(p, x0); _hlslpp_store3_ps(p + 4, x1); _hlslpp_store3_ps(p + 8, x2); _hlslpp_store3_ps(p + 12, x2)