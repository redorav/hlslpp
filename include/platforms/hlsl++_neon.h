#pragma once

#if defined(_M_ARM64) || defined(__aarch64__)

	#define HLSLPP_ARM64
	#define HLSLPP_DOUBLE

#endif

#if defined(_M_ARM64)

	// The Microsoft ARM64 header is named differently
	#include <arm64_neon.h>

	// The Microsoft ARM64 headers don't define these
#if !defined(vmaxvq_u32)
	#define vmaxvq_u32(x) neon_umaxvq32(x)
#endif

#if !defined(vminvq_u32)
	#define vminvq_u32(x) neon_uminvq32(x)
#endif

#if !defined(vmovq_n_f64)
	#define vmovq_n_f64(x) neon_dupqrf64(x)
#endif

#if !defined(vld1q_f64)
	#define vld1q_f64(x) neon_ld1m_q64((__int64*)x)
#endif

#if !defined(vrecpeq_f64)
	#define vrecpeq_f64(x) neon_frecpeq64(x)
#endif

#if !defined(vmlaq_f64)
	#define vmlaq_f64(x, y, z) neon_fmlaq64(x, y, z)
#endif

#if !defined(vsubq_f64)
	#define vsubq_f64(x, y) neon_fsubq64(x, y)
#endif

#if !defined(vmulq_f64)
	#define vmulq_f64(x, y) neon_fmulq64(x, y)
#endif

#if !defined(vcvtq_f64_s64)
	#define vcvtq_f64_s64(x) neon_scvtfq64(x)
#endif

#if !defined(vmlsq_f64)
	#define vmlsq_f64(x, y, z) neon_fmlsq64(x, y, z)
#endif

#if !defined(vcgeq_f64)
	#define vcgeq_f64(x, y) neon_fcmgeq64(x, y)
#endif

#if !defined(vabsq_f64)
	#define vabsq_f64(x) neon_fabsq64(x)
#endif
	
#if !defined(vrndpq_f64)
	#define vrndpq_f64(x) neon_frintp_q64(x)
#endif
	
#if !defined(vminq_f64)
	#define vminq_f64(x, y) neon_fminq64(x, y)
#endif
	
#if !defined(vmaxq_f64)
	#define vmaxq_f64(x, y) neon_fmaxq64(x, y)
#endif
	
#if !defined(vrndmq_f64)
	#define vrndmq_f64(x) neon_frintm_q64(x)
#endif

#if !defined(vsqrtq_f64)
	#define vsqrtq_f64(x) neon_fsqrtq64(x)
#endif

#if !defined(vrecpsq_f64)
	#define vrecpsq_f64(x, y) neon_frecpsq64(x, y)
#endif

#if !defined(vrsqrteq_f64)
	#define vrsqrteq_f64(x) neon_frsqrteq64(x)
#endif

#if !defined(vrsqrtsq_f64)
	#define vrsqrtsq_f64(x, y) neon_frsqrtsq64(x, y)
#endif

#if !defined(vst1q_lane_f64)
	#define vst1q_lane_f64(x, y, z) neon_st1s_q32((__int32*)x, y, z)
#endif

#if !defined(vst1q_f64)
	#define vst1q_f64(x, y) neon_st1m_q32((__int32*)x, y)
#endif

#if !defined(vld1q_lane_f64)
	#define vld1q_lane_f64(x, y, z) neon_ld1s_q32((__int32*)x, y, z)
#endif

#if !defined(vmaxvq_f64)
	#define vmaxvq_f64 neon_fmaxps64
#endif

#if !defined(vminvq_f64)
	#define vminvq_f64 neon_fminps64
#endif

#else

	#include <arm_neon.h>

#endif

// For NEON version check flags, see https://github.com/magnumripper/JohnTheRipper/issues/1998

typedef float32x4_t n128;
typedef int32x4_t n128i;
typedef uint32x4_t n128u;

#if defined(HLSLPP_ARM64)

typedef float64x2_t n128d;

#endif

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
hlslpp_inline int32x4_t vpermq_s32(const int32x4_t x, const uint32_t X, const uint32_t Y, const uint32_t Z, const uint32_t W)
{
	static const uint32_t ControlMask[4] = { 0x03020100, 0x07060504, 0x0B0A0908, 0x0F0E0D0C }; // Swizzle x, swizzle y, swizzle z, swizzle w

	uint8x8x2_t tbl = { { vget_low_s32(x), vget_high_s32(x) } }; // Get ints

	const uint8x8_t idxL = vcreate_u8(((uint64_t)ControlMask[X]) | (((uint64_t)ControlMask[Y]) << 32));
	const uint8x8_t rL = vtbl2_u8(tbl, idxL);

	const uint8x8_t idxH = vcreate_u8(((uint64_t)ControlMask[Z]) | (((uint64_t)ControlMask[W]) << 32));
	const uint8x8_t rH = vtbl2_u8(tbl, idxH);

	return vcombine_s32(rL, rH);
}

hlslpp_inline int32x4_t vshufq_s32(const int32x4_t x, const int32x4_t y, const uint32_t X0, const uint32_t Y0, const uint32_t X1, const uint32_t Y1)
{
	static const uint32_t ControlMaskX[4] = { 0x03020100, 0x07060504, 0x0B0A0908, 0x0F0E0D0C }; // Swizzle X0, swizzle Y0, swizzle Z0, swizzle W0,
	static const uint32_t ControlMaskY[4] = { 0x13121110, 0x17161514, 0x1B1A1918, 0x1F1E1D1C }; // Swizzle X1, swizzle Y1, swizzle Z1, swizzle W1

	uint8x8x4_t tbl = { { vget_low_s32(x), vget_high_s32(x), vget_low_s32(y), vget_high_s32(y) } };

	const uint8x8_t idxL = vcreate_u8(((uint64_t)ControlMaskX[X0]) | (((uint64_t)ControlMaskX[Y0]) << 32));
	const uint8x8_t rL = vtbl4_u8(tbl, idxL);

	const uint8x8_t idxH = vcreate_u8(((uint64_t)ControlMaskY[X1]) | (((uint64_t)ControlMaskY[Y1]) << 32));
	const uint8x8_t rH = vtbl4_u8(tbl, idxH);

	return vcombine_s32(rL, rH);
}

hlslpp_inline float32x4_t vrsqrtq_f32(float32x4_t x)
{
	float32x4_t e = vrsqrteq_f32(x);								// Calculate a first estimate of the rsqrt
	e = vmulq_f32(e, vrsqrtsq_f32(vmulq_f32(e, x), e));				// First Newton-Raphson iteration
	e = vmulq_f32(e, vrsqrtsq_f32(vmulq_f32(e, x), e));				// Second Newton-Raphson iteration
	return e;
}

#if (__ARM_ARCH <= 7)

#if !defined(vrndmq_f32)
// Source https://github.com/andrepuschmann/math-neon/blob/master/src/math_floorf.c
hlslpp_inline float32x4_t vrndmq_f32(float32x4_t x)
{
	float32x4_t trnc = vcvtq_f32_s32(vcvtq_s32_f32(x));				// Truncate
	float32x4_t gt = vcgtq_f32(trnc, x);							// Check if truncation was greater or smaller (i.e. was negative or positive number)
	uint32x4_t shr = vshrq_n_u32(vreinterpretq_u32_f32(gt), 31);	// Shift to leave a 1 or a 0
	float32x4_t result = vsubq_f32(trnc, vcvtq_f32_u32(shr));		// Subtract from truncated value
	return result;
}
#endif

#if !defined(vrndpq_f32)
// Source https://github.com/andrepuschmann/math-neon/blob/master/src/math_ceilf.c
hlslpp_inline float32x4_t vrndpq_f32(float32x4_t x)
{
	float32x4_t trnc = vcvtq_f32_s32(vcvtq_s32_f32(x));				// Truncate
	float32x4_t gt = vcgtq_f32(x, trnc);							// Check if truncation was greater or smaller (i.e. was negative or positive number)
	uint32x4_t shr = vshrq_n_u32(vreinterpretq_u32_f32(gt), 31);	// Shift to leave a 1 or a 0
	float32x4_t result = vaddq_f32(trnc, vcvtq_f32_u32(shr));		// Add to truncated value
	return result;
}
#endif

#if !defined(vrndq_f32)
hlslpp_inline float32x4_t vrndq_f32(float32x4_t x)
{
	float32x4_t add = vaddq_f32(x, vmovq_n_f32(0.5f));				// Add 0.5
	float32x4_t frc_add = vsubq_f32(add, vrndmq_f32(add));			// Get the fractional part
	float32x4_t result = vsubq_f32(add, frc_add);					// Subtract from result
	return result;
}
#endif

hlslpp_inline float32x4_t vsqrtq_f32(float32x4_t x)
{
	uint32x4_t cmpZero = vceqq_f32(x, vmovq_n_f32(0.0f));							// Sqrt of 0 is NaN (since we use rsqrt to compute it) which is incorrect but we still want it to go NaN on negatives
	float32x4_t sqrt = vmulq_f32(x, vrsqrtq_f32(x));								// Multiply by x to get x * rqsrt(x)
	return vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(sqrt), cmpZero));	// Select 0 if input is 0
}

#endif

// ARMv8 has these functions natively but we need to emulate them for ARMv7
#if !defined(_M_ARM64) && (__ARM_ARCH <= 7)

hlslpp_inline float32x4_t vdivq_f32(float32x4_t x, float32x4_t y)
{
	float32x4_t rcpy_e = vrecpeq_f32(y);					// Calculate a first estimate of the rcp
	rcpy_e = vmulq_f32(rcpy_e, vrecpsq_f32(y, rcpy_e));		// Refine
	rcpy_e = vmulq_f32(rcpy_e, vrecpsq_f32(y, rcpy_e));		// Refine
	return vmulq_f32(x, rcpy_e);							// Multiply by x
}

#endif

hlslpp_inline int32x4_t vdivq_s32(int32x4_t x, int32x4_t y)
{
	return (int32x4_t)vdivq_f32((float32x4_t)x, (float32x4_t)y);
}

hlslpp_inline uint32x4_t vdivq_u32(uint32x4_t x, uint32x4_t y)
{
	return (uint32x4_t)vdivq_f32((float32x4_t)x, (float32x4_t)y);
}

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
#define _hlslpp_setzero_ps()					vmovq_n_f32(0.0f)

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
#define _hlslpp_msub_ps(x, y, z)				_hlslpp_neg_ps(vmlsq_f32((z), (x), (y))) // Negate because vmlsq_f32 does -(x * y - z) and we want x * y - z
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

#define _hlslpp_sel_ps(x, y, mask)				vbslq_f32((mask), (y), (x))

// We decompose the mask and turn it into 4 floats
// The input mask follows the format for SSE
#define _hlslpp_blend_ps(x, y, mask)			vbslq_f32(vmov4q_n_u32((mask & 1) * 0xffffffff, ((mask >> 1) & 1) * 0xffffffff, ((mask >> 2) & 1) * 0xffffffff, ((mask >> 3) & 1) * 0xffffffff), (y), (x))

#define _hlslpp_trunc_ps(x)						vcvtq_f32_s32(vcvtq_s32_f32(x))
#define _hlslpp_floor_ps(x)						vrndmq_f32((x))
#define _hlslpp_ceil_ps(x)						vrndpq_f32((x))
#define _hlslpp_round_ps(x)						vrndq_f32((x))

#define _hlslpp_frac_ps(x)						vsubq_f32((x), vrndmq_f32(x))

#define _hlslpp_clamp_ps(x, minx, maxx)			vmaxq_f32(vminq_f32((x), (maxx)), (minx))
#define _hlslpp_sat_ps(x)						vmaxq_f32(vminq_f32((x), f4_1), f4_0)

// http://codesuppository.blogspot.co.uk/2015/02/sse2neonh-porting-guide-and-header-file.html
#define _hlslpp_and_ps(x, y)					vreinterpretq_f32_u32(vandq_u32(vreinterpretq_u32_f32((x)), vreinterpretq_u32_f32((y))))
#define _hlslpp_andnot_ps(x, y)					vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32((y)), vreinterpretq_u32_f32((x))))
#define _hlslpp_not_ps(x)						vreinterpretq_f32_u32(vmvnq_u32(vreinterpretq_u32_f32((x))))
#define _hlslpp_or_ps(x, y)						vreinterpretq_f32_u32(vorrq_u32(vreinterpretq_u32_f32((x)), vreinterpretq_u32_f32((y))))
#define _hlslpp_xor_ps(x, y)					vreinterpretq_f32_u32(veorq_u32(vreinterpretq_u32_f32((x)), vreinterpretq_u32_f32((y))))

// SSE: Move the lower 2 single-precision (32-bit) floating-point elements from b to the upper 2 elements of dst, and copy the lower 2 elements from a to the lower 2 elements of dst.
#define _hlslpp_movelh_ps(x, y)					vcombine_f32(vget_low_f32(x), vget_low_f32(y))

// SSE: Move the upper 2 single-precision (32-bit) floating-point elements from b to the lower 2 elements of dst, and copy the upper 2 elements from a to the upper 2 elements of dst.
#define _hlslpp_movehl_ps(x, y)					vcombine_f32(vget_high_f32(y), vget_high_f32(x))

// SSE: Duplicate odd-indexed single-precision (32-bit) floating-point elements from a, and store the results in dst.
#define _hlslpp_movehdup_ps(x)					vcombine_f32(vdup_lane_f32(vget_low_f32(x), 1), vdup_lane_f32(vget_high_f32(x), 1))

#define _hlslpp_perm_ps(x, mask)				vpermq_f32((x), mask & 3, (mask >> 2) & 3, (mask >> 4) & 3, (mask >> 6) & 3)
#define _hlslpp_shuffle_ps(x, y, mask)			vshufq_f32((x), (y), mask & 3, (mask >> 2) & 3, (mask >> 4) & 3, (mask >> 6) & 3)

#define _hlslpp_unpacklo_ps(x, y)				vzipq_f32(x, y).val[0]
#define _hlslpp_unpackhi_ps(x, y)				vzipq_f32(x, y).val[1]

// https://gist.github.com/rikusalminen/3040241
hlslpp_inline n128 _hlslpp_dot4_ps(n128 x, n128 y)
{
	n128 prod = vmulq_f32(x, y);
	n128 sum1 = vaddq_f32(prod, vrev64q_f32(prod));
	n128 result = vaddq_f32(sum1, vcombine_f32(vget_high_f32(sum1), vget_low_f32(sum1)));
	return result;
}

//https://stackoverflow.com/questions/15389539/fastest-way-to-test-a-128-bit-neon-register-for-a-value-of-0-using-intrinsics

hlslpp_inline bool _hlslpp_any1_ps(n128 x)
{
	return vget_lane_u32(vget_low_u32(vreinterpretq_u32_f32(x)), 0) != 0;
}

hlslpp_inline bool _hlslpp_any2_ps(n128 x)
{
	uint32x2_t low = vget_low_u32(vreinterpretq_u32_f32(x));
	return vget_lane_u32(vpmax_u32(low, low), 0) != 0;
}

hlslpp_inline bool _hlslpp_any3_ps(n128 x)
{
	uint32x4_t maskw = vsetq_lane_u32(0, vreinterpretq_u32_f32(x), 3); // set w to minimum value
#if defined(HLSLPP_ARM64)
	return vmaxvq_u32(maskw) != 0;
#else
	uint32x2_t maxlohi = vorr_u32(vget_low_u32(maskw), vget_high_u32(maskw));
	return vget_lane_u32(vpmax_u32(maxlohi, maxlohi), 0) != 0;
#endif
}

hlslpp_inline bool _hlslpp_any4_ps(n128 x)
{
#if defined(HLSLPP_ARM64)
	return vmaxvq_u32(vreinterpretq_u32_f32(x)) != 0;
#else
	uint32x2_t tmp = vorr_u32(vget_low_u32(vreinterpretq_u32_f32(x)), vget_high_u32(vreinterpretq_u32_f32(x)));
	return vget_lane_u32(vpmax_u32(tmp, tmp), 0) != 0;
#endif
}

hlslpp_inline bool _hlslpp_all1_ps(n128 x)
{
	return vget_lane_u32(vget_low_u32(vreinterpretq_u32_f32(x)), 0) != 0;
}

hlslpp_inline bool _hlslpp_all2_ps(n128 x)
{
	uint32x2_t low = vget_low_u32(vreinterpretq_u32_f32(x));
	return vget_lane_u32(vpmin_u32(low, low), 0) != 0;
}

hlslpp_inline bool _hlslpp_all3_ps(n128 x)
{
	uint32x4_t maskw = vsetq_lane_u32(0xffffffff, vreinterpretq_u32_f32(x), 3); // set w to maximum value
#if defined(HLSLPP_ARM64)
	return vminvq_u32(maskw) != 0;
#else
	uint32x2_t minlohi = vpmin_u32(vget_low_u32(maskw), vget_high_u32(maskw));
	return vget_lane_u32(vpmin_u32(minlohi, minlohi), 0) != 0;
#endif
}

hlslpp_inline bool _hlslpp_all4_ps(n128 x)
{
#if defined(HLSLPP_ARM64)
	return vminvq_u32(vreinterpretq_u32_f32(x)) != 0;
#else
	uint32x2_t minlohi = vpmin_u32(vget_low_u32(vreinterpretq_u32_f32(x)), vget_high_u32(vreinterpretq_u32_f32(x)));
	return vget_lane_u32(vpmin_u32(minlohi, minlohi), 0) != 0;
#endif
}

//--------
// Storing
//--------

hlslpp_inline void _hlslpp_store1_ps(float* p, n128 x)
{
	vst1q_lane_f32(p, x, 0);
}

hlslpp_inline void _hlslpp_store2_ps(float* p, n128 x)
{
	vst1_f32(p, vget_low_f32(x));
}

hlslpp_inline void _hlslpp_store3_ps(float* p, n128 x)
{
	vst1_f32(p, vget_low_f32(x));
	vst1q_lane_f32(p + 2, x, 2);
}

hlslpp_inline void _hlslpp_store4_ps(float* p, n128 x)
{
	vst1q_f32(p, x);
}

hlslpp_inline void _hlslpp_store3x3_ps(float* p, n128 x0, n128 x1, n128 x2)
{
	vst1q_f32(p, x0);
	vst1q_f32(p + 3, x1);
	vst1_f32(p + 6, vget_low_f32(x2));
	vst1q_lane_f32(p + 8, x2, 2);
}

hlslpp_inline void _hlslpp_store4x4_ps(float* p, n128 x0, n128 x1, n128 x2, n128 x3)
{
	vst1q_f32(p, x0);
	vst1q_f32(p + 4, x1);
	vst1q_f32(p + 8, x2);
	vst1q_f32(p + 12, x3);
}

hlslpp_inline void _hlslpp_load1_ps(float* p, n128& x)
{
	x = vld1q_lane_f32(p, x, 0);
}

hlslpp_inline void _hlslpp_load2_ps(float* p, n128& x)
{
	float32x2_t t = vld1_f32(p); // Load the two values
	x = vcombine_f32(t, t); // Replicate in the other two to create a float32x4_t
}

hlslpp_inline void _hlslpp_load3_ps(float* p, n128& x)
{
	float32x2_t t = vld1_f32(p); // Load the two values
	x = vcombine_f32(t, t); // Replicate in the other two to create a float32x4_t
	x = vld1q_lane_f32(p + 2, x, 2);
}

hlslpp_inline void _hlslpp_load4_ps(float* p, n128& x)
{
	x = vld1q_f32(p);
}

hlslpp_inline void _hlslpp_load3x3_ps(float* p, n128& x0, n128& x1, n128& x2)
{
	x0 = vld1q_f32(p);
	x1 = vld1q_f32(p + 3);
	x2 = vld1q_f32(p + 6);
}

hlslpp_inline void _hlslpp_load4x4_ps(float* p, n128& x0, n128& x1, n128& x2, n128& x3)
{
	x0 = vld1q_f32(p);
	x1 = vld1q_f32(p + 4);
	x2 = vld1q_f32(p + 8);
	x3 = vld1q_f32(p + 12);
}

//--------
// Integer
//--------

#define _hlslpp_set1_epi32(x)					vmovq_n_s32((x))
#define _hlslpp_set_epi32(x, y, z, w)			vmov4q_n_s32((x), (y), (z), (w))
#define _hlslpp_setzero_epi32()					vmovq_n_s32(0)

#define _hlslpp_add_epi32(x, y)					vaddq_s32((x), (y))
#define _hlslpp_sub_epi32(x, y)					vsubq_s32((x), (y))
#define _hlslpp_mul_epi32(x, y)					vmulq_s32((x), (y))
#define _hlslpp_div_epi32(x, y)					vdivq_s32((x), (y))

#define _hlslpp_neg_epi32(x)					vaddq_s32(veorq_u32(vreinterpretq_u32_s32(x), vmovq_n_u32(0xffffffffu)), vmovq_n_u32(1))

#define _hlslpp_madd_epi32(x, y, z)				vmlaq_s32((z), (x), (y))
#define _hlslpp_msub_epi32(x, y, z)				_hlslpp_neg_epi32(vmlsq_s32((z), (x), (y))) // Negate because vmlsq_u32 does z - x * y and we want x * y - z
#define _hlslpp_subm_epi32(x, y, z)				vmlsq_s32((z), (x), (y))

#define _hlslpp_abs_epi32(x)					vabsq_s32((x))

#define _hlslpp_cmpeq_epi32(x, y)				vceqq_s32((x), (y))
#define _hlslpp_cmpneq_epi32(x, y)				veorq_s32(vceqq_s32((x), (y)), vmovq_n_u32(0xffffffffu))

#define _hlslpp_cmpgt_epi32(x, y)				vcgtq_s32((x), (y))
#define _hlslpp_cmpge_epi32(x, y)				vcgeq_s32((x), (y))

#define _hlslpp_cmplt_epi32(x, y)				vcltq_s32((x), (y))
#define _hlslpp_cmple_epi32(x, y)				vcleq_s32((x), (y))

#define _hlslpp_max_epi32(x, y)					vmaxq_s32((x), (y))
#define _hlslpp_min_epi32(x, y)					vminq_s32((x), (y))

#define _hlslpp_clamp_epi32(x, minx, maxx)		vmaxq_s32(vminq_s32((x), (maxx)), (minx))
#define _hlslpp_sat_epi32(x)					vmaxq_s32(vminq_s32((x), i4_1), i4_0)

#define _hlslpp_and_si128(x, y)					vandq_s32((x), (y))
#define _hlslpp_andnot_si128(x, y)				vandq_s32((y), (x))
#define _hlslpp_not_si128(x)					vmvnq_s32((x))
#define _hlslpp_or_si128(x, y)					vorrq_s32((x), (y))
#define _hlslpp_xor_si128(x, y)					veorq_s32((x), (y))

#define _hlslpp_perm_epi32(x, mask)				vpermq_s32((x), mask & 3, (mask >> 2) & 3, (mask >> 4) & 3, (mask >> 6) & 3)
#define _hlslpp_shuffle_epi32(x, y, mask)		vshufq_s32((x), (y), mask & 3, (mask >> 2) & 3, (mask >> 4) & 3, (mask >> 6) & 3)

#define _hlslpp_blend_epi32(x, y, mask)			vbslq_s32(vmov4q_n_u32(~((mask & 1) * 0xffffffff), ~(((mask >> 1) & 1) * 0xffffffff), ~(((mask >> 2) & 1) * 0xffffffff), ~(((mask >> 3) & 1) * 0xffffffff)), (x), (y))

#define _hlslpp_castps_si128(x)					vreinterpretq_s32_f32((x))
#define _hlslpp_castsi128_ps(x)					vreinterpretq_f32_s32((x))

#define _hlslpp_cvtps_epi32(x)					vcvtq_s32_f32((x))
#define _hlslpp_cvtepi32_ps(x)					vcvtq_f32_s32((x))

#define _hlslpp_slli_epi32(x, y)				vshlq_n_s32((x), (y))
#define _hlslpp_srli_epi32(x, y)				vshrq_n_s32((x), (y))

// From the documentation of vshlq_s32: Vector shift left: Vr[i] := Va[i] << Vb[i] (negative values shift right)
#define _hlslpp_sllv_epi32(x, y)				vshlq_s32((x), (y))
#define _hlslpp_srlv_epi32(x, y)				vshlq_s32((x), _hlslpp_neg_epi32(y))

//-----------------
// Unsigned Integer
//-----------------

#define _hlslpp_set1_epu32(x)					vmovq_n_u32((x))
#define _hlslpp_set_epu32(x, y, z, w)			vmov4q_n_u32((x), (y), (z), (w))
#define _hlslpp_setzero_epu32()					vmovq_n_u32(0)

#define _hlslpp_add_epu32(x, y)					vaddq_u32((x), (y))
#define _hlslpp_sub_epu32(x, y)					vsubq_u32((x), (y))
#define _hlslpp_mul_epu32(x, y)					vmulq_u32((x), (y))
#define _hlslpp_div_epu32(x, y)					vdivq_u32((x), (y))

#define _hlslpp_madd_epu32(x, y, z)				vmlaq_u32((z), (x), (y))
#define _hlslpp_msub_epu32(x, y, z)				_hlslpp_neg_epi32(vmlsq_u32((z), (x), (y))) // Negate because vmlsq_u32 does z - x * y and we want x * y - z
#define _hlslpp_subm_epu32(x, y, z)				vmlsq_u32((z), (x), (y))

#define _hlslpp_cmpeq_epu32(x, y)				vceqq_u32((x), (y))
#define _hlslpp_cmpneq_epu32(x, y)				veorq_u32(vceqq_u32((x), (y)), vmovq_n_u32(0xffffffffu))

#define _hlslpp_cmpgt_epu32(x, y)				vcgtq_u32((x), (y))
#define _hlslpp_cmpge_epu32(x, y)				vcgeq_u32((x), (y))

#define _hlslpp_cmplt_epu32(x, y)				vcltq_u32((x), (y))
#define _hlslpp_cmple_epu32(x, y)				vcleq_u32((x), (y))

#define _hlslpp_max_epu32(x, y)					vmaxq_u32((x), (y))
#define _hlslpp_min_epu32(x, y)					vminq_u32((x), (y))

#define _hlslpp_clamp_epu32(x, minx, maxx)		vmaxq_u32(vminq_u32((x), (maxx)), (minx))
#define _hlslpp_sat_epu32(x)					vmaxq_u32(vminq_u32((x), i4_1), i4_0)

#define _hlslpp_cvtps_epu32(x)					vcvtq_u32_f32((x))
#define _hlslpp_cvtepu32_ps(x)					vcvtq_f32_u32((x))

#define _hlslpp_slli_epu32(x, y)				vshlq_n_u32((x), (y))
#define _hlslpp_srli_epu32(x, y)				vshrq_n_u32((x), (y))

// From the documentation of vshlq_s32: Vector shift left: Vr[i] := Va[i] << Vb[i] (negative values shift right)
#define _hlslpp_sllv_epu32(x, y)				vshlq_u32((x), (y))
#define _hlslpp_srlv_epu32(x, y)				vshlq_u32((x), _hlslpp_neg_epi32(y))

#if defined(HLSLPP_DOUBLE)

//-------
// Double
//-------

hlslpp_inline float64x2_t vmov2q_n_f64(const double x, const double y)
{
	const double values[2] = { x, y };
	return vld1q_f64(values);
}

hlslpp_inline int64x2_t vmov2q_n_s64(const int64_t x, const int64_t y)
{
	const int64_t values[2] = { x, y };
	return vld1q_s64(values);
}

hlslpp_inline uint64x2_t vmov2q_n_u64(const uint64_t x, const uint64_t y)
{
	const uint64_t values[2] = { x, y };
	return vld1q_u64(values);
}

template<int X, int Y>
hlslpp_inline float64x2_t permute(const float64x2_t x);

template<> hlslpp_inline float64x2_t permute<0, 0>(const float64x2_t x) { return vcombine_f64(vget_low_f64(x), vget_low_f64(x)); }

template<> hlslpp_inline float64x2_t permute<0, 1>(const float64x2_t x) { return x; }

template<> hlslpp_inline float64x2_t permute<1, 0>(const float64x2_t x) { return vcombine_f64(vget_high_f64(x), vget_low_f64(x)); }

template<> hlslpp_inline float64x2_t permute<1, 1>(const float64x2_t x) { return vcombine_f64(vget_high_f64(x), vget_high_f64(x)); }

#define vpermq_f64(x, X, Y) permute<X, Y>(x)

template<int X, int Y>
hlslpp_inline float64x2_t shuffle(const float64x2_t x, const float64x2_t y);

template<> hlslpp_inline float64x2_t shuffle<0, 0>(const float64x2_t x, const float64x2_t y) { return vcombine_f64(vget_low_f64(x), vget_low_f64(y)); }

template<> hlslpp_inline float64x2_t shuffle<0, 1>(const float64x2_t x, const float64x2_t y) { return vcombine_f64(vget_low_f64(x), vget_high_f64(y)); }

template<> hlslpp_inline float64x2_t shuffle<1, 0>(const float64x2_t x, const float64x2_t y) { return vcombine_f64(vget_high_f64(x), vget_low_f64(y)); }

template<> hlslpp_inline float64x2_t shuffle<1, 1>(const float64x2_t x, const float64x2_t y) { return vcombine_f64(vget_high_f64(x), vget_high_f64(y)); }

#define vshufq_f64(x, y, X, Y) shuffle<X, Y>(x, y)

hlslpp_inline float64x2_t vrcpq_f64(float64x2_t x)
{
	float64x2_t rcpx_e = vrecpeq_f64(x);					// Calculate a first estimate of the rcp
	rcpx_e = vmulq_f64(rcpx_e, vrecpsq_f64(x, rcpx_e));		// Refine
	return vmulq_f64(rcpx_e, vrecpsq_f64(x, rcpx_e));		// Refine
}

hlslpp_inline float64x2_t vrsqrtq_f64(float64x2_t x)
{
	float64x2_t e = vrsqrteq_f64(x);								// Calculate a first estimate of the rsqrt
	e = vmulq_f64(e, vrsqrtsq_f64(vmulq_f64(e, x), e));				// First Newton-Raphson iteration
	e = vmulq_f64(e, vrsqrtsq_f64(vmulq_f64(e, x), e));				// Second Newton-Raphson iteration
	return e;
}


#define _hlslpp_set1_pd(x)						vmovq_n_f64(x)
#define _hlslpp_set_pd(x, y)					vmov2q_n_f64((x), (y))
#define _hlslpp_setzero_pd()					vmovq_n_f64(0.0)

#define _hlslpp_add_pd(x, y)					vaddq_f64((x), (y))
#define _hlslpp_sub_pd(x, y)					vsubq_f64((x), (y))
#define _hlslpp_mul_pd(x, y)					vmulq_f64((x), (y))
#define _hlslpp_div_pd(x, y)					vdivq_f64(x, y)

#define _hlslpp_rcp_pd(x)						vrcpq_f64(x)

#define _hlslpp_neg_pd(x)						veorq_u64(vreinterpretq_u32_f32(x), d2negativeMask)

#define _hlslpp_madd_pd(x, y, z)				vmlaq_f64((z), (x), (y))
#define _hlslpp_msub_pd(x, y, z)				_hlslpp_neg_pd(vmlsq_f64((z), (x), (y))) // Negate because vmlsq_f32 does z - x * y and we want x * y - z
#define _hlslpp_subm_pd(x, y, z)				vmlsq_f64((z), (x), (y))

#define _hlslpp_abs_pd(x)						vabsq_f64(x)

#define _hlslpp_sqrt_pd(x)						vsqrtq_f64(x)
#define _hlslpp_rsqrt_pd(x)						vrsqrtq_f64(x)

#define _hlslpp_cmpeq_pd(x, y)					vceqq_f64((x), (y))
#define _hlslpp_cmpneq_pd(x, y)					veorq_u64(vreinterpretq_u64_f64(vceqq_f64((x), (y))), vmovq_n_u64(0xffffffffffffffffu))

#define _hlslpp_cmpgt_pd(x, y)					vcgtq_f64((x), (y))
#define _hlslpp_cmpge_pd(x, y)					vcgeq_f64((x), (y))

#define _hlslpp_cmplt_pd(x, y)					vcltq_f64((x), (y))
#define _hlslpp_cmple_pd(x, y)					vcleq_f64((x), (y))

#define _hlslpp_max_pd(x, y)					vmaxq_f64((x), (y))
#define _hlslpp_min_pd(x, y)					vminq_f64((x), (y))

#define _hlslpp_trunc_pd(x)						vcvtq_f64_s64(vcvtq_s64_f64(x))
#define _hlslpp_floor_pd(x)						vrndmq_f64((x))
#define _hlslpp_ceil_pd(x)						vrndpq_f64((x))
#define _hlslpp_round_pd(x)						vrndq_f64((x))

#define _hlslpp_frac_pd(x)						vsubq_f64((x), vrndmq_f64(x))

#define _hlslpp_clamp_pd(x, minx, maxx)			vmaxq_f64(vminq_f64((x), (maxx)), (minx))
#define _hlslpp_sat_pd(x)						vmaxq_f64(vminq_f64((x), f4_1), f4_0)

#define _hlslpp_and_pd(x, y)					vreinterpretq_f64_u64(vandq_u64(vreinterpretq_u64_f64((x)), vreinterpretq_u64_f64((y))))
#define _hlslpp_andnot_pd(x, y)					vreinterpretq_f64_u64(vbicq_u64(vreinterpretq_u64_f64((y)), vreinterpretq_u64_f64((x))))
#define _hlslpp_not_pd(x, y)					vreinterpretq_f64_u64(vmvnq_u64(vreinterpretq_u64_f64((y)), vreinterpretq_u64_f64((x))))
#define _hlslpp_or_pd(x, y)						vreinterpretq_f64_u64(vorrq_u64(vreinterpretq_u64_f64((x)), vreinterpretq_u64_f64((y))))
#define _hlslpp_xor_pd(x, y)					vreinterpretq_f64_u64(veorq_u64(vreinterpretq_u64_f64((x)), vreinterpretq_u64_f64((y))))

#define _hlslpp_perm_pd(x, mask)				vpermq_f64((x), mask & 1, (mask >> 1) & 1)
#define _hlslpp_shuffle_pd(x, y, mask)			vshufq_f64((x), (y), mask & 1, (mask >> 1) & 1)

// Bit-select x and y based on the contents of the mask
#define _hlslpp_sel_pd(x, y, mask)				vbslq_f64((mask), (y), (x))

#define _hlslpp_blend_pd(x, y, mask)			vbslq_f64(vmov2q_n_u64((mask & 1) * 0xffffffffffffffff, ((mask >> 1) & 1) * 0xffffffffffffffff), (y), (x))

hlslpp_inline bool _hlslpp_any1_pd(n128d x)
{
	return vget_lane_u64(vget_low_u64(vreinterpretq_u64_f64(x)), 0) != 0;
}

hlslpp_inline bool _hlslpp_any2_pd(n128d x)
{
	return vmaxvq_f64(vabsq_f64(x)) != 0;
}

hlslpp_inline bool _hlslpp_any3_pd(n128d x0, n128d x1)
{
	return vmaxvq_f64(vabsq_f64(x0)) != 0 || vget_lane_u64(vget_low_u64(vreinterpretq_u64_f64(x1)), 0) != 0;
}

hlslpp_inline bool _hlslpp_any4_pd(n128d x0, n128d x1)
{
	return vmaxvq_f64(vabsq_f64(x0)) != 0 || vmaxvq_f64(vabsq_f64(x1)) != 0;;
}

hlslpp_inline bool _hlslpp_all1_pd(n128d x)
{
	return vget_lane_u64(vget_low_u64(vreinterpretq_u64_f64(x)), 0) != 0;
}

hlslpp_inline bool _hlslpp_all2_pd(n128d x)
{
	return vminvq_f64(vabsq_f64(x)) != 0;
}

hlslpp_inline bool _hlslpp_all3_pd(n128d x0, n128d x1)
{
	return vminvq_f64(vabsq_f64(x0)) != 0 && vget_lane_u64(vget_low_u64(vreinterpretq_u64_f64(x1)), 0) != 0;
}

hlslpp_inline bool _hlslpp_all4_pd(n128d x0, n128d x1)
{
	return vminvq_f64(vabsq_f64(x0)) != 0 && vminvq_f64(vabsq_f64(x1)) != 0;
}

//------------------
// Double Store/Load
//------------------

hlslpp_inline void _hlslpp_store1_pd(double* p, n128d x)
{
	vst1q_lane_f64(p, x, 0);
}

hlslpp_inline void _hlslpp_store2_pd(double* p, n128d x)
{
	vst1q_f64(p, x);
}

hlslpp_inline void _hlslpp_store3_pd(double* p, n128d x0, n128d x1)
{
	vst1q_f64(p, x0);
	vst1q_lane_f64(p + 2, x1, 0);
}

hlslpp_inline void _hlslpp_store4_pd(double* p, n128d x0, n128d x1)
{
	vst1q_f64(p, x0);
	vst1q_f64(p + 2, x1);
}

hlslpp_inline void _hlslpp_load1_pd(double* p, n128d& x)
{
	x = vld1q_lane_f64(p, x, 0);
}

hlslpp_inline void _hlslpp_load2_pd(double* p, n128d& x)
{
	x = vld1q_f64(p);
}

hlslpp_inline void _hlslpp_load3_pd(double* p, n128d& x0, n128d& x1)
{
	x0 = vld1q_f64(p);
	x1 = vld1q_lane_f64(p + 2, x1, 0);
}

hlslpp_inline void _hlslpp_load4_pd(double* p, n128d& x0, n128d& x1)
{
	x0 = vld1q_f64(p);
	x1 = vld1q_f64(p + 2);
}

#endif