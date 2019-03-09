#pragma once

#if defined(__clang__) || defined(__GNUG__)

	#define hlslpp_inline inline __attribute__((always_inline))

#elif defined(_MSC_VER)

	#define hlslpp_inline __forceinline

#endif

#define HLSLPP_SHUFFLE_MASK(X, Y, Z, W)			(((W) << 6) | ((Z) << 4) | ((Y) << 2) | (X))

// Create a mask where 1 selects from x, 0 selects from y
#define HLSLPP_BLEND_MASK(X, Y, Z, W)			(~(X | (Y << 1) | (Z << 2) | (W << 3)) & 0xf)

#define HLSLPP_COMPONENT_X(X)					(1 << X)
#define HLSLPP_COMPONENT_XY(X, Y)				((1 << X) | (1 << Y))
#define HLSLPP_COMPONENT_XYZ(X, Y, Z)			((1 << X) | (1 << Y) | (1 << Z))
#define HLSLPP_COMPONENT_XYZW(X, Y, Z, W)		((1 << X) | (1 << Y) | (1 << Z) | (1 << W))

#if defined(_M_ARM) || defined(__arm__) || defined(_M_ARM64)
	#include "hlsl++_neon.h"
#else
	#include "hlsl++_sse.h"
#endif

#include <cstdint>
#include <type_traits>

namespace hlslpp
{
	union BitMask
	{
		uint32_t i;
		float f;
		explicit BitMask(uint32_t i) : i(i) {}
		explicit BitMask(float f) : f(f) {}
	};

	const hlslpp::BitMask fffMask(0xffffffffu); // Negative NaN
	const hlslpp::BitMask nanMask(0x7fffffffu); // Positive NaN
	const hlslpp::BitMask infMask(0x7f800000u);
	const hlslpp::BitMask minusinfMask(0xff800000u);
	const hlslpp::BitMask absMask(0x7fffffffu);
	const hlslpp::BitMask negMask(0x80000000u);

	//----- Constants
	const n128 f4_0         = _hlslpp_set1_ps(0.0f);
	const n128 f4_1         = _hlslpp_set1_ps(1.0f);
	const n128 f4minusOne   = _hlslpp_set1_ps(-1.0f);
	const n128 f4_05        = _hlslpp_set1_ps(0.5f);
	const n128 f4_minus05   = _hlslpp_set1_ps(-0.5f);
	const n128 f4_2         = _hlslpp_set1_ps(2.0f);
	const n128 f4_minus2    = _hlslpp_set1_ps(-2.0f);
	const n128 f4_3         = _hlslpp_set1_ps(3.0f);
	const n128 f4_10        = _hlslpp_set1_ps(10.0f);
	const n128 f4_e         = _hlslpp_set1_ps(2.718281828f);

	const n128 f4_pi        = _hlslpp_set1_ps(3.14159265f); // pi
	const n128 f4_minusPi   = _hlslpp_set1_ps(-3.14159265f); // -pi
	const n128 f4_invPi     = _hlslpp_set1_ps(0.31830988f); // 1 / pi

	const n128 f4_2pi       = _hlslpp_set1_ps(6.28318530f); //  2 * pi
	const n128 f4_minus2pi  = _hlslpp_set1_ps(-6.28318530f); // -2 * pi
	const n128 f4_inv2pi    = _hlslpp_set1_ps(0.15915494f); // 1 / (2 * pi)

	const n128 f4_pi2       = _hlslpp_set1_ps(1.57079632f); //  pi / 2
	const n128 f4_minusPi2  = _hlslpp_set1_ps(-1.57079632f); // -pi / 2
	const n128 f4_invPi2    = _hlslpp_set1_ps(0.63661977f); // 2 / pi

	const n128 f4_3pi2      = _hlslpp_set1_ps(4.71238898f); //  3 * pi / 2
	const n128 f4_minus3pi2 = _hlslpp_set1_ps(-4.71238898f); // -3 * pi / 2

	const n128 f4_pi4       = _hlslpp_set1_ps(0.78539816f); //  pi / 4
	const n128 f4_minusPi4  = _hlslpp_set1_ps(-0.78539816f); // -pi / 4

	const n128 f4_NaN       = _hlslpp_set1_ps(nanMask.f);		// Quiet NaN
	const n128 f4_inf       = _hlslpp_set1_ps(infMask.f);		// Infinity
	const n128 f4_minusinf  = _hlslpp_set1_ps(minusinfMask.f);	// -Infinity

	const n128 f4_rad2deg   = _hlslpp_set1_ps(180.0f / 3.14159265f);
	const n128 f4_deg2rad   = _hlslpp_set1_ps(3.14159265f / 180.f);

	const n128i i4_0        = _hlslpp_set1_epi32(0);
	const n128i i4_1        = _hlslpp_set1_epi32(1);

	//----- Masks
	const n128 f4negativeMask  = _hlslpp_set1_ps(negMask.f);
	const n128 f4absMask       = _hlslpp_set1_ps(absMask.f);

	const n128i i4negativeMask = _hlslpp_set1_epi32(negMask.i);
	const n128i i4absMask      = _hlslpp_set1_epi32(absMask.i);

	const n128i i4fffMask      = _hlslpp_set1_epi32(fffMask.i);

	const uint32_t MaskX = 0;
	const uint32_t MaskY = 1;
	const uint32_t MaskZ = 2;
	const uint32_t MaskW = 3;

	//----- Helper intrinsics

	// Float

	#define _hlslpp_perm_xxxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskX, MaskX, MaskX))
	#define _hlslpp_perm_xxyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskX, MaskY, MaskX))
	#define _hlslpp_perm_xxyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskX, MaskY, MaskZ))
	#define _hlslpp_perm_xyxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskY, MaskX, MaskY))
	#define _hlslpp_perm_xyww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskY, MaskW, MaskW))
	#define _hlslpp_perm_xzyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskZ, MaskY, MaskW))
	#define _hlslpp_perm_xzxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskZ, MaskX, MaskY))
	#define _hlslpp_perm_xzwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskZ, MaskW, MaskX))
	#define _hlslpp_perm_xwxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskW, MaskX, MaskW))
	#define _hlslpp_perm_yxxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskY, MaskX, MaskX, MaskX))
	#define _hlslpp_perm_yxwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskY, MaskX, MaskW, MaskX))
	#define _hlslpp_perm_yxwz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskY, MaskX, MaskW, MaskZ))
	#define _hlslpp_perm_yyyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskY, MaskY, MaskY, MaskY))
	#define _hlslpp_perm_yzxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskY, MaskZ, MaskX, MaskX))
	#define _hlslpp_perm_yzxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskY, MaskZ, MaskX, MaskW))
	#define _hlslpp_perm_yzwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskY, MaskZ, MaskW, MaskX))
	#define _hlslpp_perm_zxxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskZ, MaskX, MaskX, MaskX))
	#define _hlslpp_perm_zxyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskZ, MaskX, MaskY, MaskW))
	#define _hlslpp_perm_zyyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskZ, MaskY, MaskY, MaskX))
	#define _hlslpp_perm_zyzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskZ, MaskY, MaskZ, MaskY))
	#define _hlslpp_perm_zzyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskZ, MaskZ, MaskY, MaskX))
	#define _hlslpp_perm_zzzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskZ, MaskZ, MaskZ, MaskZ))
	#define _hlslpp_perm_zwzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskZ, MaskW, MaskZ, MaskW))
	#define _hlslpp_perm_wyzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskW, MaskY, MaskZ, MaskX))
	#define _hlslpp_perm_wzxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskW, MaskZ, MaskX, MaskX))
	#define _hlslpp_perm_wwyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskW, MaskW, MaskY, MaskX))
	#define _hlslpp_perm_wwzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskW, MaskW, MaskZ, MaskX))
	#define _hlslpp_perm_wwzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskW, MaskW, MaskZ, MaskW))
	#define _hlslpp_perm_wwww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskW, MaskW, MaskW, MaskW))
	#define _hlslpp_perm_xxyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskX, MaskY, MaskY))
	#define _hlslpp_perm_zwxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskZ, MaskW, MaskX, MaskX))
	#define _hlslpp_perm_xyxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskY, MaskX, MaskX))
	#define _hlslpp_perm_zxwy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskZ, MaskX, MaskW, MaskY))
	#define _hlslpp_perm_yzzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskY, MaskZ, MaskZ, MaskY))
	#define _hlslpp_perm_zxyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskZ, MaskX, MaskY, MaskZ))
	#define _hlslpp_perm_yzxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskY, MaskZ, MaskX, MaskZ))
	#define _hlslpp_perm_zyzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskZ, MaskY, MaskZ, MaskX))
	#define _hlslpp_perm_wwwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskW, MaskW, MaskW, MaskX))
	#define _hlslpp_perm_wxyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(MaskW, MaskX, MaskY, MaskZ))

	#define _hlslpp_shuf_xxxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskX, MaskX, MaskX, MaskX))
	#define _hlslpp_shuf_xxxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskX, MaskX, MaskX, MaskY))
	#define _hlslpp_shuf_xyxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskX, MaskY, MaskX, MaskX))
	#define _hlslpp_shuf_xyxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskX, MaskY, MaskX, MaskY))
	#define _hlslpp_shuf_yzyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskY, MaskZ, MaskY, MaskZ))
	#define _hlslpp_shuf_xzxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskX, MaskZ, MaskX, MaskW))
	#define _hlslpp_shuf_ywyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskY, MaskW, MaskY, MaskW))
	#define _hlslpp_shuf_ywzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskY, MaskW, MaskZ, MaskW))
	#define _hlslpp_shuf_zwzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskZ, MaskW, MaskZ, MaskW))
	#define _hlslpp_shuf_xzxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskX, MaskZ, MaskX, MaskZ))
	#define _hlslpp_shuf_wzxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskW, MaskZ, MaskX, MaskX))
	#define _hlslpp_shuf_ywzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskY, MaskW, MaskZ, MaskY))
	#define _hlslpp_shuf_xzxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskX, MaskZ, MaskX, MaskX))
	#define _hlslpp_shuf_ywyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskY, MaskW, MaskY, MaskY))
	#define _hlslpp_shuf_yyyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(MaskY, MaskY, MaskY, MaskY))

	// Reference http://www.liranuna.com/sse-intrinsics-optimizations-in-popular-compilers/
	#define _hlslpp_sign_ps(val)				_hlslpp_and_ps(_hlslpp_or_ps(_hlslpp_and_ps((val), f4minusOne), f4_1), _hlslpp_cmpneq_ps((val), f4_0))
	
	#define _hlslpp_cmpneq1_ps(val1, val2)		_hlslpp_and_ps(_hlslpp_cmpneq_ps((val1), (val2)), f4_1)
	#define _hlslpp_cmpeq1_ps(val1, val2)		_hlslpp_and_ps(_hlslpp_cmpeq_ps((val1), (val2)), f4_1)
	
	#define _hlslpp_cmpgt1_ps(val1, val2)		_hlslpp_and_ps(_hlslpp_cmpgt_ps((val1), (val2)), f4_1)
	#define _hlslpp_cmpge1_ps(val1, val2)		_hlslpp_and_ps(_hlslpp_cmpge_ps((val1), (val2)), f4_1)
	
	#define _hlslpp_cmplt1_ps(val1, val2)		_hlslpp_and_ps(_hlslpp_cmplt_ps((val1), (val2)), f4_1)
	#define _hlslpp_cmple1_ps(val1, val2)		_hlslpp_and_ps(_hlslpp_cmple_ps((val1), (val2)), f4_1)
	
	#define _hlslpp_any1_ps(val)				_hlslpp_and_ps(_hlslpp_any_ps((val)), f4_1)
	#define _hlslpp_all1_ps(val)				_hlslpp_and_ps(_hlslpp_all_ps((val)), f4_1)

	// Integer

	#define _hlslpp_perm_xxxx_epi32(x)			_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskX, MaskX, MaskX))
	#define _hlslpp_perm_xxyx_epi32(x)			_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskX, MaskY, MaskX))
	#define _hlslpp_perm_xxyz_epi32(x)			_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(MaskX, MaskX, MaskY, MaskZ))

	#define _hlslpp_shuf_xxxx_epi32(x, y)		_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(MaskX, MaskX, MaskX, MaskX))
	#define _hlslpp_shuf_xyxx_epi32(x, y)		_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(MaskX, MaskY, MaskX, MaskX))
	#define _hlslpp_shuf_xxxy_epi32(x, y)		_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(MaskX, MaskX, MaskX, MaskY))
	#define _hlslpp_shuf_xyxy_epi32(x, y)		_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(MaskX, MaskY, MaskX, MaskY))

	#define _hlslpp_cmpneq1_epi32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmpneq_epi32((val1), (val2)), i4_1)
	#define _hlslpp_cmpeq1_epi32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmpeq_epi32((val1), (val2)), i4_1)
	
	#define _hlslpp_cmpgt1_epi32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmpgt_epi32((val1), (val2)), i4_1)
	#define _hlslpp_cmpge1_epi32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmpge_epi32((val1), (val2)), i4_1)
	
	#define _hlslpp_cmplt1_epi32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmplt_epi32((val1), (val2)), i4_1)
	#define _hlslpp_cmple1_epi32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmple_epi32((val1), (val2)), i4_1)

	// Hlsl, glsl and Cg behavior is to swap the operands.
	// http://http.developer.nvidia.com/Cg/step.html
	// https://www.opengl.org/sdk/docs/man/html/step.xhtml
	#define _hlslpp_step_ps(val1, val2)			_hlslpp_cmpge1_ps((val1), (val2))

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

	// Cross product for 3-component vectors
	// http://threadlocalmutex.com/?p=8
	// Measured to be marginally faster than the 4-shuffle
	hlslpp_inline n128 _hlslpp_cross_ps(n128 x, n128 y)
	{
		n128 yzx_0 = _hlslpp_perm_yzxx_ps(x);
		n128 yzx_1 = _hlslpp_perm_yzxx_ps(y);
		return _hlslpp_perm_yzxx_ps(_hlslpp_msub_ps(x, yzx_1, _hlslpp_mul_ps(yzx_0, y)));
	}

	// See http://jrfonseca.blogspot.co.uk/2008/09/fast-sse2-pow-tables-or-polynomials.html for derivation
	// Fonseca derives from here: http://forum.devmaster.net/t/approximate-math-library/11679
	inline n128 _hlslpp_log2_ps(n128 x)
	{
		static const n128 log2_c0	= _hlslpp_set1_ps( 3.1157899f);
		static const n128 log2_c1	= _hlslpp_set1_ps(-3.3241990f);
		static const n128 log2_c2	= _hlslpp_set1_ps( 2.5988452f);
		static const n128 log2_c3	= _hlslpp_set1_ps(-1.2315303f);
		static const n128 log2_c4	= _hlslpp_set1_ps( 3.1821337e-1f);
		static const n128 log2_c5	= _hlslpp_set1_ps(-3.4436006e-2f);

		static const n128i exp		= _hlslpp_set1_epi32(0x7F800000);
		static const n128i mant		= _hlslpp_set1_epi32(0x007FFFFF);

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

	hlslpp_inline n128 _hlslpp_lrp_ps(n128 x, n128 y, n128 a)
	{
		// Slower
		// n128 y_minus_x = Masksub_ps(y, x);
		// n128 result = _hlslpp_madd_ps(y_minus_x, a, x);

		n128 one_minus_a = _hlslpp_sub_ps(f4_1, a);
		n128 x_one_minus_a = _hlslpp_mul_ps(x, one_minus_a);
		n128 result = _hlslpp_madd_ps(y, a, x_one_minus_a);
		return result;
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

	// See http://jrfonseca.blogspot.co.uk/2008/09/fast-sse2-pow-tables-or-polynomials.html for derivation
	inline n128 _hlslpp_exp2_ps(n128 x)
	{
		static const n128 exp2_c0 = _hlslpp_set1_ps(1.0f);
		static const n128 exp2_c1 = _hlslpp_set1_ps(6.9315308e-1f);
		static const n128 exp2_c2 = _hlslpp_set1_ps(2.4015361e-1f);
		static const n128 exp2_c3 = _hlslpp_set1_ps(5.5826318e-2f);
		static const n128 exp2_c4 = _hlslpp_set1_ps(8.9893397e-3f);
		static const n128 exp2_c5 = _hlslpp_set1_ps(1.8775767e-3f);

		static const n128 exp2_129		= _hlslpp_set1_ps(129.00000f);
		static const n128 exp2_minus127	= _hlslpp_set1_ps(-126.99999f);
		static const n128i exp2_127i	= _hlslpp_set1_epi32(127);

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

		n128 gtpi2			= _hlslpp_cmpgt_ps(x, f4_pi2);
		n128 ltminusPi2		= _hlslpp_cmplt_ps(x, f4_minusPi2);

		n128 ox = x;

		// Use identities/mirroring to remap into the range of the minimax polynomial
		x = _hlslpp_sel_ps(x, _hlslpp_sub_ps(f4_pi, ox),		gtpi2);
		x = _hlslpp_sel_ps(x, _hlslpp_sub_ps(f4_minusPi, ox),	ltminusPi2);

		n128 x2 = _hlslpp_mul_ps(x, x);
		n128 result;
		result = _hlslpp_madd_ps(x2, sin_c7, sin_c5);
		result = _hlslpp_madd_ps(x2, result, sin_c3);
		result = _hlslpp_madd_ps(x2, result, sin_c1);
		result = _hlslpp_mul_ps(result, x);
		return result;
	}

	hlslpp_inline n128 _hlslpp_cos_ps(n128 x)
	{	
		return _hlslpp_sin_ps(_hlslpp_sub_ps(f4_pi2, x));
	}

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

		n128 gtPi4		= _hlslpp_cmpgt_ps(x, f4_pi4);
		n128 ltMinusPi4	= _hlslpp_cmplt_ps(x, f4_minusPi4);
		n128 gtltPi4	= _hlslpp_or_ps(gtPi4, ltMinusPi4);

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
		result = _hlslpp_sub_ps(f4_pi2, _hlslpp_mul_ps(result, sqrt1minusx));

		result = _hlslpp_sel_ps(result, _hlslpp_neg_ps(result), ltZero);	// Select the [0, 1] or [-1, 0] result

		n128 gtltOne = _hlslpp_cmpgt_ps(_hlslpp_abs_ps(x), f4_1);		// > 1 || < -1
		result = _hlslpp_sel_ps(result, f4_NaN, gtltOne);				// Select NaN if input out of range

		return result;
	}

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

		n128 ltgtOne	= _hlslpp_cmpgt_ps(_hlslpp_abs_ps(x), f4_1); // Check if outside the [-1, 1] range
		n128 gtOne		= _hlslpp_cmpgt_ps(x, f4_1);				 // Check if input > 1 (as we need to select the constant later)

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

	// sinh(x) = (exp(x) - exp(-x)) / 2.0
	hlslpp_inline n128 _hlslpp_sinh_ps(n128 x)
	{
		n128 expx = _hlslpp_exp_ps(x);
		n128 exp_minusx = _hlslpp_rcp_ps(expx);
		return _hlslpp_mul_ps(_hlslpp_sub_ps(expx, exp_minusx), f4_05);
	}

	// cosh(x) = (exp(x) + exp(-x)) / 2.0
	hlslpp_inline n128 _hlslpp_cosh_ps(n128 x)
	{
		n128 expx = _hlslpp_exp_ps(x);
		n128 exp_minusx = _hlslpp_rcp_ps(expx);
		return _hlslpp_mul_ps(_hlslpp_add_ps(expx, exp_minusx), f4_05);
	}

	// tanh(x) = (exp(x) - exp(-x)) / (exp(x) + exp(-x))
	hlslpp_inline n128 _hlslpp_tanh_ps(n128 x)
	{
		n128 expx = _hlslpp_exp_ps(x);
		n128 exp_minusx = _hlslpp_rcp_ps(expx);
		return _hlslpp_div_ps(_hlslpp_sub_ps(expx, exp_minusx), _hlslpp_add_ps(expx, exp_minusx));
	}

	// Inspiration for some bits from https://stackoverflow.com/questions/6996764/fastest-way-to-do-horizontal-float-vector-sum-on-x86
	// Can optimize further in SSE3 via Maskmovehdup_ps instead of _hlslpp_perm_yxwx_ps, but is slower in MSVC and
	// only marginally faster on clang
	hlslpp_inline n128 _hlslpp_dot4_ps(n128 x, n128 y)
	{
		// SSE3 slower
		// n128 m      = _hlslpp_mul_ps(x, y);    // Multiply components together
		// n128 h1     = _hlslpp_hadd_ps(m, m);   // Add once
		// n128 result = _hlslpp_hadd_ps(h1, h1); // Add twice

		// SSE4 slower
		// n128 result = _hlslpp_dp_ps(x, y, 0xff);

		// SSE2
		n128 multi = _hlslpp_mul_ps(x, y);         // Multiply components
		n128 shuf  = _hlslpp_perm_yxwx_ps(multi);  // Move y into x, and w into z (ignore the rest)
		n128 add   = _hlslpp_add_ps(shuf, multi);  // Contains x+y, _, z+w, _
		shuf       = _hlslpp_movehl_ps(shuf, add); // Move (z + w) into x
		add        = _hlslpp_add_ss(add, shuf);    // Contains x+y+z+w, _, _, _
		return add;
	}

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

	hlslpp_inline n128 _hlslpp_dot2_ps(n128 x, n128 y)
	{
		n128 multi  = _hlslpp_mul_ps(x, y);         // Multiply components together
		n128 shuf1  = _hlslpp_perm_yyyy_ps(multi);  // Move y into x
		n128 result = _hlslpp_add_ss(shuf1, multi); // Contains x+y, _, _, _
		return result;
	}

	// Auxiliary dot3 that adds, subtracts, adds instead of adding all
	hlslpp_inline n128 _hlslpp_dot3_asa_ps(n128 x, n128 y)
	{
		n128 multi  = _hlslpp_mul_ps(x, y);         // Multiply components together
		n128 shuf1  = _hlslpp_perm_yyyy_ps(multi);  // Move y into x
		n128 add1   = _hlslpp_sub_ps(multi, shuf1); // Contains x-y, _, _, _
		n128 shuf2  = _hlslpp_perm_zzzz_ps(multi);  // Move z into x
		n128 result = _hlslpp_add_ss(add1, shuf2);  // Contains x-y+z, _, _, _
		return result;
	}

	hlslpp_inline n128 _hlslpp_any_ps(n128 x)
	{
		n128 shuf1  = _hlslpp_perm_yxwx_ps(x);       // Move y into x, and w into z (ignore the rest)
		n128 add1   = _hlslpp_add_ps(shuf1, x);      // Contains x+y, _, z+w, _
		n128 shuf2  = _hlslpp_perm_zxxx_ps(add1);    // Move (z + w) into x
		n128 add2   = _hlslpp_add_ps(add1, shuf2);   // Contains x+y+z+w, _, _, _
		n128 result = _hlslpp_cmpneq_ps(add2, f4_0);
		return result;
	}

	hlslpp_inline n128 _hlslpp_all_ps(n128 x)
	{
		n128 shuf1  = _hlslpp_perm_yxwx_ps(x);       // Move y into x, and w into z (ignore the rest)
		n128 mul1   = _hlslpp_mul_ps(shuf1, x);      // Contains x*y, _, z*w, _
		n128 shuf2  = _hlslpp_perm_zxxx_ps(mul1);    // Move (z * w) into x
		n128 mul2   = _hlslpp_mul_ps(mul1, shuf2);   // Contains x*y*z*w, _, _, _
		n128 result = _hlslpp_cmpneq_ps(mul2, f4_0);
		return result;
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

	// Forward declarations

	template<int X>	struct swizzle1;
	template<int X, int Y> struct swizzle2;
	template<int X, int Y, int Z> struct swizzle3;
	template<int X, int Y, int Z, int W> struct swizzle4;

	struct float1;
	struct float2;
	struct float3;
	struct float4;

	template<int X>	struct iswizzle1;
	template<int X, int Y> struct iswizzle2;
	template<int X, int Y, int Z> struct iswizzle3;
	template<int X, int Y, int Z, int W> struct iswizzle4;

	struct int1;
	struct int2;
	struct int3;
	struct int4;

	struct float1x1;

	// Auxiliary templates for disambiguation with standard header functions

	template<typename T>
	using enable_if_number = typename std::enable_if<std::is_arithmetic<T>::value, void>::type*;

	template<typename T1, typename T2>
	using enable_if_number_2 = typename std::enable_if<
		std::is_arithmetic<T1>::value *
		std::is_arithmetic<T2>::value, void>::type*;

	template<typename T1, typename T2, typename T3>
	using enable_if_number_3 = typename std::enable_if<
		std::is_arithmetic<T1>::value *
		std::is_arithmetic<T2>::value *
		std::is_arithmetic<T3>::value, void>::type*;

	template<typename T1, typename T2, typename T3, typename T4>
	using enable_if_number_4 = typename std::enable_if<
		std::is_arithmetic<T1>::value *
		std::is_arithmetic<T2>::value *
		std::is_arithmetic<T3>::value *
		std::is_arithmetic<T4>::value, void>::type*;

	//--------------------//
	// Float swizzle type //
	//--------------------//

	static const int IdentityMask = ((3 << 6) | (2 << 4) | (1 << 2) | 0);

	template<int X>
	struct swizzle1
	{
		template<int A> friend struct swizzle1;

		// Cast

		operator float() const { return f32[X]; }
		
		// Helper

		template<int E, int A>
		static n128 swizzle(n128 v)
		{
			const int finalMask = (((IdentityMask >> 2 * E) & 3) << 2 * A) | (IdentityMask & ~((3 << 2 * A)));
			return _hlslpp_perm_ps(v, finalMask);
		}

		template<int E, int A>
		n128 swizzle() const
		{
			return swizzle<E, A>(vec);
		}

		// Assignment

		swizzle1& operator = (float f)
		{
			vec = _hlslpp_blend_ps(vec, _hlslpp_set1_ps(f), HLSLPP_COMPONENT_X(X));
			return *this;
		}

		template<int A>
		swizzle1& operator = (const swizzle1<A>& s) // Revise this function. Can I not do with swizzle?
		{
			n128 t = _hlslpp_shuffle_ps(s.vec, s.vec, HLSLPP_SHUFFLE_MASK(A, A, A, A));
			vec = _hlslpp_blend_ps(vec, t, HLSLPP_COMPONENT_X(X));
			return *this;
		}

		swizzle1& operator = (const float1& f);

	private:
		union
		{
			n128 vec;
			float f32[4];
		};
	};

	template<int X, int Y>
	struct swizzle2
	{
		// Helper

		void staticAsserts()
		{
			// Assert that no component is equal to each other for assignment
			static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		static n128 blend(n128 x, n128 y)
		{
			return _hlslpp_blend_ps(x, y, HLSLPP_COMPONENT_XY(X, Y)); // Select based on property mask
		}

		template<int E, int F, int A, int B>
		static n128 swizzle(n128 v)
		{
			const int finalMask = 
				(((IdentityMask >> 2 * E) & 3) << 2 * A) | 
				(((IdentityMask >> 2 * F) & 3) << 2 * B) | 
				(IdentityMask & ~((3 << 2 * A) | (3 << 2 * B)));
			return _hlslpp_perm_ps(v, finalMask);
		}

		template<int E, int F, int A, int B>
		n128 swizzle() const
		{
			return swizzle<E, F, A, B>(vec);
		}

		// Assignment

		template<int A, int B>
		swizzle2& operator = (const swizzle2<A, B>& s)
		{
			staticAsserts();
			vec = blend(vec, s.template swizzle<A, B, X, Y>());
			return *this;
		}

		swizzle2& operator = (const float2& f);

	private:
		union
		{
			n128 vec;
			float f32[4];
		};
	};

	template<int X, int Y, int Z>
	struct swizzle3
	{
		// Helper

		void staticAsserts()
		{
			// Assert that no component is equal to each other for assignment
			static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		static n128 blend(n128 x, n128 y)
		{
			return _hlslpp_blend_ps(x, y, HLSLPP_COMPONENT_XYZ(X, Y, Z)); // Select based on property mask
		}

		template<int E, int F, int G, int A, int B, int C>
		static n128 swizzle(n128 v)
		{
			const int finalMask = 
				(((IdentityMask >> 2 * E) & 3) << 2 * A) | 
				(((IdentityMask >> 2 * F) & 3) << 2 * B) | 
				(((IdentityMask >> 2 * G) & 3) << 2 * C) | 
				(IdentityMask & ~((3 << 2 * A) | (3 << 2 * B) | (3 << 2 * C)));
			return _hlslpp_perm_ps(v, finalMask);
		}

		template<int E, int F, int G, int A, int B, int C>
		n128 swizzle() const
		{
			return swizzle<E, F, G, A, B, C>(vec);
		}

		// Assignment

		template<int A, int B, int C>
		swizzle3& operator = (const swizzle3<A, B, C>& s)
		{
			staticAsserts();
			vec = blend(vec, s.template swizzle<A, B, C, X, Y, Z>());
			return *this;
		}

		swizzle3& operator = (const float3& f);

	private:
		union
		{
			n128 vec;
			float f32[4];
		};
	};

	template<int X, int Y, int Z, int W>
	struct swizzle4
	{
		// Helper

		void staticAsserts()
		{
			// Assert that no component is equal to each other for assignment
			static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		template<int E, int F, int G, int H, int A, int B, int C, int D>
		static n128 swizzle(n128 v)
		{
			const int finalMask = 
				(((IdentityMask >> 2 * E) & 3) << (2 * A)) |
				(((IdentityMask >> 2 * F) & 3) << (2 * B)) |
				(((IdentityMask >> 2 * G) & 3) << (2 * C)) |
				(((IdentityMask >> 2 * H) & 3) << (2 * D));
			
			return _hlslpp_perm_ps(v, finalMask);
		}

		template<int E, int F, int G, int H, int A, int B, int C, int D>
		n128 swizzle() const
		{
			return swizzle<E, F, G, H, A, B, C, D>(vec);
		}

		// Assignment

		template<int A, int B, int C, int D>
		swizzle4& operator = (const swizzle4<A, B, C, D>& s)
		{
			staticAsserts();
			vec = s.template swizzle<A, B, C, D, X, Y, Z, W>();
			return *this;
		}

		swizzle4& operator = (const float4& f);

	private:
		union
		{
			n128 vec;
			float f32[4];
		};
	};

	//------------//
	// Float type //
	//------------//

	struct float1
	{
		float1() {}
		float1(const float1& f) : vec(f.vec) {}
		explicit float1(n128 vec) : vec(vec) {}

		template<typename T, enable_if_number<T> = nullptr>
		float1(T f) : vec(_hlslpp_set_ps(float(f), 0.0f, 0.0f, 0.0f)) {}

		template<int X> float1(const swizzle1<X>& s) : vec(s.template swizzle<X, 0>()) {}

		float1(const int1& i);

		operator float() const { return f32[0]; }

		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/hlsl++_vector_float_x.h"
			#include "swizzle/hlsl++_vector_float_r.h"
		};
	};

	struct float2
	{
		// Constructors

		float2() {}
		float2(const float2& f) : vec(f.vec) {}
		explicit float2(n128 vec) : vec(vec) {}
		explicit float2(const float1& f) : vec(_hlslpp_perm_xxxx_ps(f.vec)) {}

		template<typename T, enable_if_number<T> = nullptr>
		float2(T f) : vec(_hlslpp_set_ps(float(f), float(f), 0.0f, 0.0f)) {}

		template<typename T1, typename T2, enable_if_number_2<T1, T2> = nullptr>
		float2(T1 f1, T2 f2) : vec(_hlslpp_set_ps(float(f1), float(f2), 0.0f, 0.0f)) {}

		float2(const float1& f1, const float1& f2) { vec = _hlslpp_blend_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }
		
		template<int X, int Y> float2(const swizzle2<X, Y>& s) : vec(s.template swizzle<X, Y, 0, 1>()) {}

		float2(const int2& i);

		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/hlsl++_vector_float_x.h"
			#include "swizzle/hlsl++_vector_float_y.h"
			#include "swizzle/hlsl++_vector_float_r.h"
			#include "swizzle/hlsl++_vector_float_g.h"
		};
	};

	struct float3
	{
		// Constructors

		float3() {}
		float3(const float3& f) : vec(f.vec) {}
		explicit float3(n128 vec) : vec(vec) {}

		explicit float3(const float1& f) : vec(_hlslpp_perm_xxxx_ps(f.vec)) {}

		template<typename T, enable_if_number<T> = nullptr>
		float3(T f) : vec(_hlslpp_set_ps(float(f), float(f), float(f), 0.0f)) {}

		template<typename T1, typename T2, typename T3, enable_if_number_3<T1, T2, T3> = nullptr>
		float3(T1 f1, T2 f2, T3 f3) : vec(_hlslpp_set_ps(float(f1), float(f2), float(f3), 0.0f)) {}

		float3(const float1& f1, const float1& f2, const float1& f3) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(f1.vec, f3.vec), _hlslpp_perm_xxxx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }

		float3(const float2& f1, const float1& f2) { vec = _hlslpp_shuf_xyxx_ps(f1.vec, f2.vec); }
		float3(const float1& f1, const float2& f2) { vec = _hlslpp_blend_ps(f1.vec, _hlslpp_perm_xxyx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }

		template<int X, int Y, int Z>
		float3(const swizzle3<X, Y, Z>& s) : vec(s.template swizzle<X, Y, Z, 0, 1, 2>()) {}

		float3(const int3& i);

		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/hlsl++_vector_float_x.h"
			#include "swizzle/hlsl++_vector_float_y.h"
			#include "swizzle/hlsl++_vector_float_z.h"
			#include "swizzle/hlsl++_vector_float_r.h"
			#include "swizzle/hlsl++_vector_float_g.h"
			#include "swizzle/hlsl++_vector_float_b.h"
		};
	};

	struct float4
	{
		float4() {}
		float4(const float4& f) : vec(f.vec) {}
		explicit float4(n128 vec) : vec(vec) {}

		explicit float4(const float1& f) : vec(_hlslpp_perm_xxxx_ps(f.vec)) {}

		template<typename T, enable_if_number<T> = nullptr>
		float4(T f) : vec(_hlslpp_set1_ps(float(f))) {}

		template<typename T1, typename T2, typename T3, typename T4, enable_if_number_4<T1, T2, T3, T4> = nullptr>
		float4(T1 f1, T2 f2, T3 f3, T4 f4) : vec(_hlslpp_set_ps(float(f1), float(f2), float(f3), float(f4))) {}

		float4(const float1& f1, const float1& f2, const float1& f3, const float1& f4) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(f1.vec, f3.vec), _hlslpp_shuf_xxxx_ps(f2.vec, f4.vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }
		
		float4(const float2& f1, const float1& f2, const float1& f3) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xyxx_ps(f1.vec, f2.vec), _hlslpp_perm_xxxx_ps(f3.vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }
		float4(const float1& f1, const float2& f2, const float1& f3) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(f1.vec, f3.vec), _hlslpp_perm_xxyx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }
		float4(const float1& f1, const float1& f2, const float2& f3) { vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxy_ps(f1.vec, f3.vec), _hlslpp_perm_xxxx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }

		float4(const float2& f1, const float2& f2) { vec = _hlslpp_shuf_xyxy_ps(f1.vec, f2.vec); }

		float4(const float1& f1, const float3& f2) { vec = _hlslpp_blend_ps(f1.vec, _hlslpp_perm_xxyz_ps(f2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 0)); }
		float4(const float3& f1, const float1& f2) { vec = _hlslpp_blend_ps(f1.vec, _hlslpp_perm_xxxx_ps(f2.vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }

		template<int X, int Y, int Z, int W>
		float4(const swizzle4<X, Y, Z, W>& s) : vec(s.template swizzle<X, Y, Z, W, 0, 1, 2, 3>()) {}

		float4(const int4& i);

		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/hlsl++_vector_float_x.h"
			#include "swizzle/hlsl++_vector_float_y.h"
			#include "swizzle/hlsl++_vector_float_z.h"
			#include "swizzle/hlsl++_vector_float_w.h"
			#include "swizzle/hlsl++_vector_float_r.h"
			#include "swizzle/hlsl++_vector_float_g.h"
			#include "swizzle/hlsl++_vector_float_b.h"
			#include "swizzle/hlsl++_vector_float_a.h"
		};
	};

	// Operators

	float1 operator + (const float1& f1, const float1& f2) { return float1(_hlslpp_add_ps(f1.vec, f2.vec)); }
	float2 operator + (const float2& f1, const float2& f2) { return float2(_hlslpp_add_ps(f1.vec, f2.vec)); }
	float3 operator + (const float3& f1, const float3& f2) { return float3(_hlslpp_add_ps(f1.vec, f2.vec)); }
	float4 operator + (const float4& f1, const float4& f2) { return float4(_hlslpp_add_ps(f1.vec, f2.vec)); }

	float1 operator - (const float1& f1, const float1& f2) { return float1(_hlslpp_sub_ps(f1.vec, f2.vec)); }
	float2 operator - (const float2& f1, const float2& f2) { return float2(_hlslpp_sub_ps(f1.vec, f2.vec)); }
	float3 operator - (const float3& f1, const float3& f2) { return float3(_hlslpp_sub_ps(f1.vec, f2.vec)); }
	float4 operator - (const float4& f1, const float4& f2) { return float4(_hlslpp_sub_ps(f1.vec, f2.vec)); }

	float1 operator * (const float1& f1, const float1& f2) { return float1(_hlslpp_mul_ps(f1.vec, f2.vec)); }
	float2 operator * (const float2& f1, const float2& f2) { return float2(_hlslpp_mul_ps(f1.vec, f2.vec)); }
	float3 operator * (const float3& f1, const float3& f2) { return float3(_hlslpp_mul_ps(f1.vec, f2.vec)); }
	float4 operator * (const float4& f1, const float4& f2) { return float4(_hlslpp_mul_ps(f1.vec, f2.vec)); }

	float1 operator / (const float1& f1, const float1& f2) { return float1(_hlslpp_div_ps(f1.vec, f2.vec)); }
	float2 operator / (const float2& f1, const float2& f2) { return float2(_hlslpp_div_ps(f1.vec, f2.vec)); }
	float3 operator / (const float3& f1, const float3& f2) { return float3(_hlslpp_div_ps(f1.vec, f2.vec)); }
	float4 operator / (const float4& f1, const float4& f2) { return float4(_hlslpp_div_ps(f1.vec, f2.vec)); }

	float1 operator - (const float1& f) { return float1(_hlslpp_neg_ps(f.vec)); }
	float2 operator - (const float2& f) { return float2(_hlslpp_neg_ps(f.vec)); }
	float3 operator - (const float3& f) { return float3(_hlslpp_neg_ps(f.vec)); }
	float4 operator - (const float4& f) { return float4(_hlslpp_neg_ps(f.vec)); }

	float1& operator += (float1& f1, const float1& f2) { f1 = f1 + f2; return f1; }
	float2& operator += (float2& f1, const float2& f2) { f1 = f1 + f2; return f1; }
	float3& operator += (float3& f1, const float3& f2) { f1 = f1 + f2; return f1; }
	float4& operator += (float4& f1, const float4& f2) { f1 = f1 + f2; return f1; }

	template<int X>	swizzle1<X>& operator += (swizzle1<X>& s, const float1& f) { s = float1(s) + f; return s; }
	template<int X>	swizzle1<X>& operator -= (swizzle1<X>& s, const float1& f) { s = float1(s) - f; return s; }
	template<int X>	swizzle1<X>& operator *= (swizzle1<X>& s, const float1& f) { s = float1(s) * f; return s; }
	template<int X>	swizzle1<X>& operator /= (swizzle1<X>& s, const float1& f) { s = float1(s) / f; return s; }

	template<int X, int Y> swizzle2<X, Y>& operator += (swizzle2<X, Y>& s, const float2& f) { s = float2(s) + f; return s; }
	template<int X, int Y> swizzle2<X, Y>& operator -= (swizzle2<X, Y>& s, const float2& f) { s = float2(s) - f; return s; }
	template<int X, int Y> swizzle2<X, Y>& operator *= (swizzle2<X, Y>& s, const float2& f) { s = float2(s) * f; return s; }
	template<int X, int Y> swizzle2<X, Y>& operator /= (swizzle2<X, Y>& s, const float2& f) { s = float2(s) / f; return s; }

	template<int X, int Y, int Z> swizzle3<X, Y, Z>& operator += (swizzle3<X, Y, Z>& s, const float3& f) { s = float3(s) + f; return s; }
	template<int X, int Y, int Z> swizzle3<X, Y, Z>& operator -= (swizzle3<X, Y, Z>& s, const float3& f) { s = float3(s) - f; return s; }
	template<int X, int Y, int Z> swizzle3<X, Y, Z>& operator *= (swizzle3<X, Y, Z>& s, const float3& f) { s = float3(s) * f; return s; }
	template<int X, int Y, int Z> swizzle3<X, Y, Z>& operator /= (swizzle3<X, Y, Z>& s, const float3& f) { s = float3(s) / f; return s; }

	template<int X, int Y, int Z, int W> swizzle4<X, Y, Z, W>& operator += (swizzle4<X, Y, Z, W>& s, const float4& f) { s = float4(s) + f; return s; }
	template<int X, int Y, int Z, int W> swizzle4<X, Y, Z, W>& operator -= (swizzle4<X, Y, Z, W>& s, const float4& f) { s = float4(s) - f; return s; }
	template<int X, int Y, int Z, int W> swizzle4<X, Y, Z, W>& operator *= (swizzle4<X, Y, Z, W>& s, const float4& f) { s = float4(s) * f; return s; }
	template<int X, int Y, int Z, int W> swizzle4<X, Y, Z, W>& operator /= (swizzle4<X, Y, Z, W>& s, const float4& f) { s = float4(s) / f; return s; }
	
	float1& operator -= (float1& f1, const float1& f2) { f1 = f1 - f2; return f1; }
	float2& operator -= (float2& f1, const float2& f2) { f1 = f1 - f2; return f1; }
	float3& operator -= (float3& f1, const float3& f2) { f1 = f1 - f2; return f1; }
	float4& operator -= (float4& f1, const float4& f2) { f1 = f1 - f2; return f1; }

	float1& operator *= (float1& f1, const float1& f2) { f1 = f1 * f2; return f1; }
	float2& operator *= (float2& f1, const float2& f2) { f1 = f1 * f2; return f1; }
	float3& operator *= (float3& f1, const float3& f2) { f1 = f1 * f2; return f1; }
	float4& operator *= (float4& f1, const float4& f2) { f1 = f1 * f2; return f1; }

	float1& operator /= (float1& f1, const float1& f2) { f1 = f1 / f2; return f1; }
	float2& operator /= (float2& f1, const float2& f2) { f1 = f1 / f2; return f1; }
	float3& operator /= (float3& f1, const float3& f2) { f1 = f1 / f2; return f1; }
	float4& operator /= (float4& f1, const float4& f2) { f1 = f1 / f2; return f1; }

	float1 operator == (const float1& f1, const float1& f2) { return float1(_hlslpp_cmpeq1_ps(f1.vec, f2.vec)); }
	float2 operator == (const float2& f1, const float2& f2) { return float2(_hlslpp_cmpeq1_ps(f1.vec, f2.vec)); }
	float3 operator == (const float3& f1, const float3& f2) { return float3(_hlslpp_cmpeq1_ps(f1.vec, f2.vec)); }
	float4 operator == (const float4& f1, const float4& f2) { return float4(_hlslpp_cmpeq1_ps(f1.vec, f2.vec)); }

	float1 operator != (const float1& f1, const float1& f2) { return float1(_hlslpp_cmpneq1_ps(f1.vec, f2.vec)); }
	float2 operator != (const float2& f1, const float2& f2) { return float2(_hlslpp_cmpneq1_ps(f1.vec, f2.vec)); }
	float3 operator != (const float3& f1, const float3& f2) { return float3(_hlslpp_cmpneq1_ps(f1.vec, f2.vec)); }
	float4 operator != (const float4& f1, const float4& f2) { return float4(_hlslpp_cmpneq1_ps(f1.vec, f2.vec)); }

	float1 operator > (const float1& f1, const float1& f2) { return float1(_hlslpp_cmpgt1_ps(f1.vec, f2.vec)); }
	float2 operator > (const float2& f1, const float2& f2) { return float2(_hlslpp_cmpgt1_ps(f1.vec, f2.vec)); }
	float3 operator > (const float3& f1, const float3& f2) { return float3(_hlslpp_cmpgt1_ps(f1.vec, f2.vec)); }
	float4 operator > (const float4& f1, const float4& f2) { return float4(_hlslpp_cmpgt1_ps(f1.vec, f2.vec)); }

	float1 operator >= (const float1& f1, const float1& f2) { return float1(_hlslpp_cmpge1_ps(f1.vec, f2.vec)); }
	float2 operator >= (const float2& f1, const float2& f2) { return float2(_hlslpp_cmpge1_ps(f1.vec, f2.vec)); }
	float3 operator >= (const float3& f1, const float3& f2) { return float3(_hlslpp_cmpge1_ps(f1.vec, f2.vec)); }
	float4 operator >= (const float4& f1, const float4& f2) { return float4(_hlslpp_cmpge1_ps(f1.vec, f2.vec)); }

	float1 operator < (const float1& f1, const float1& f2) { return float1(_hlslpp_cmplt1_ps(f1.vec, f2.vec)); }
	float2 operator < (const float2& f1, const float2& f2) { return float2(_hlslpp_cmplt1_ps(f1.vec, f2.vec)); }
	float3 operator < (const float3& f1, const float3& f2) { return float3(_hlslpp_cmplt1_ps(f1.vec, f2.vec)); }
	float4 operator < (const float4& f1, const float4& f2) { return float4(_hlslpp_cmplt1_ps(f1.vec, f2.vec)); }

	float1 operator <= (const float1& f1, const float1& f2) { return float1(_hlslpp_cmple1_ps(f1.vec, f2.vec)); }
	float2 operator <= (const float2& f1, const float2& f2) { return float2(_hlslpp_cmple1_ps(f1.vec, f2.vec)); }
	float3 operator <= (const float3& f1, const float3& f2) { return float3(_hlslpp_cmple1_ps(f1.vec, f2.vec)); }
	float4 operator <= (const float4& f1, const float4& f2) { return float4(_hlslpp_cmple1_ps(f1.vec, f2.vec)); }

	float1 abs(const float1& f) { return float1(_hlslpp_abs_ps(f.vec)); }
	float2 abs(const float2& f) { return float2(_hlslpp_abs_ps(f.vec)); }
	float3 abs(const float3& f) { return float3(_hlslpp_abs_ps(f.vec)); }
	float4 abs(const float4& f) { return float4(_hlslpp_abs_ps(f.vec)); }

	float1 acos(const float1& f) { return float1(_hlslpp_acos_ps(f.vec)); }
	float2 acos(const float2& f) { return float2(_hlslpp_acos_ps(f.vec)); }
	float3 acos(const float3& f) { return float3(_hlslpp_acos_ps(f.vec)); }
	float4 acos(const float4& f) { return float4(_hlslpp_acos_ps(f.vec)); }

	float1 all(const float1& f) { return float1(_hlslpp_all1_ps(f.vec)); }
	float1 all(const float2& f) { return float1(_hlslpp_all1_ps(f.vec)); }
	float1 all(const float3& f) { return float1(_hlslpp_all1_ps(f.vec)); }
	float1 all(const float4& f) { return float1(_hlslpp_all1_ps(f.vec)); }

	float1 any(const float1& f) { return float1(_hlslpp_any1_ps(f.vec)); }
	float1 any(const float2& f) { return float1(_hlslpp_any1_ps(f.vec)); }
	float1 any(const float3& f) { return float1(_hlslpp_any1_ps(f.vec)); }
	float1 any(const float4& f) { return float1(_hlslpp_any1_ps(f.vec)); }

	float1 asin(const float1& f) { return float1(_hlslpp_asin_ps(f.vec)); }
	float2 asin(const float2& f) { return float2(_hlslpp_asin_ps(f.vec)); }
	float3 asin(const float3& f) { return float3(_hlslpp_asin_ps(f.vec)); }
	float4 asin(const float4& f) { return float4(_hlslpp_asin_ps(f.vec)); }

	float1 atan(const float1& f) { return float1(_hlslpp_atan_ps(f.vec)); }
	float2 atan(const float2& f) { return float2(_hlslpp_atan_ps(f.vec)); }
	float3 atan(const float3& f) { return float3(_hlslpp_atan_ps(f.vec)); }
	float4 atan(const float4& f) { return float4(_hlslpp_atan_ps(f.vec)); }

	float1 ceil(const float1& f) { return float1(_hlslpp_ceil_ps(f.vec)); }
	float2 ceil(const float2& f) { return float2(_hlslpp_ceil_ps(f.vec)); }
	float3 ceil(const float3& f) { return float3(_hlslpp_ceil_ps(f.vec)); }
	float4 ceil(const float4& f) { return float4(_hlslpp_ceil_ps(f.vec)); }

	float1 clamp(const float1& f, const float1& minf, const float1& maxf) { return float1(_hlslpp_clamp_ps(f.vec, minf.vec, maxf.vec)); }
	float2 clamp(const float2& f, const float2& minf, const float2& maxf) { return float2(_hlslpp_clamp_ps(f.vec, minf.vec, maxf.vec)); }
	float3 clamp(const float3& f, const float3& minf, const float3& maxf) { return float3(_hlslpp_clamp_ps(f.vec, minf.vec, maxf.vec)); }
	float4 clamp(const float4& f, const float4& minf, const float4& maxf) { return float4(_hlslpp_clamp_ps(f.vec, minf.vec, maxf.vec)); }

	float1 cos(const float1& f) { return float1(_hlslpp_cos_ps(f.vec)); }
	float2 cos(const float2& f) { return float2(_hlslpp_cos_ps(f.vec)); }
	float3 cos(const float3& f) { return float3(_hlslpp_cos_ps(f.vec)); }
	float4 cos(const float4& f) { return float4(_hlslpp_cos_ps(f.vec)); }

	float1 cosh(const float1& f) { return float1(_hlslpp_cosh_ps(f.vec)); }
	float2 cosh(const float2& f) { return float2(_hlslpp_cosh_ps(f.vec)); }
	float3 cosh(const float3& f) { return float3(_hlslpp_cosh_ps(f.vec)); }
	float4 cosh(const float4& f) { return float4(_hlslpp_cosh_ps(f.vec)); }

	float3 cross(const float3& f1, const float3& f2) { return float3(_hlslpp_cross_ps(f1.vec, f2.vec)); }

	float1 degrees(const float1& f) { return float1(_hlslpp_mul_ps(f.vec, f4_rad2deg)); }
	float2 degrees(const float2& f) { return float2(_hlslpp_mul_ps(f.vec, f4_rad2deg)); }
	float3 degrees(const float3& f) { return float3(_hlslpp_mul_ps(f.vec, f4_rad2deg)); }
	float4 degrees(const float4& f) { return float4(_hlslpp_mul_ps(f.vec, f4_rad2deg)); }

	float1 dot(const float1& f1, const float1& f2) { return f1 * f2; }
	float1 dot(const float2& f1, const float2& f2) { return float1(_hlslpp_dot2_ps(f1.vec, f2.vec)); }
	float1 dot(const float3& f1, const float3& f2) { return float1(_hlslpp_dot3_ps(f1.vec, f2.vec)); }
	float1 dot(const float4& f1, const float4& f2) { return float1(_hlslpp_dot4_ps(f1.vec, f2.vec)); }

	float1 exp(const float1& f) { return float1(_hlslpp_exp_ps(f.vec)); }
	float2 exp(const float2& f) { return float2(_hlslpp_exp_ps(f.vec)); }
	float3 exp(const float3& f) { return float3(_hlslpp_exp_ps(f.vec)); }
	float4 exp(const float4& f) { return float4(_hlslpp_exp_ps(f.vec)); }

	float1 exp2(const float1& f) { return float1(_hlslpp_exp2_ps(f.vec)); }
	float2 exp2(const float2& f) { return float2(_hlslpp_exp2_ps(f.vec)); }
	float3 exp2(const float3& f) { return float3(_hlslpp_exp2_ps(f.vec)); }
	float4 exp2(const float4& f) { return float4(_hlslpp_exp2_ps(f.vec)); }

	float1 floor(const float1& f) { return float1(_hlslpp_floor_ps(f.vec)); }
	float2 floor(const float2& f) { return float2(_hlslpp_floor_ps(f.vec)); }
	float3 floor(const float3& f) { return float3(_hlslpp_floor_ps(f.vec)); }
	float4 floor(const float4& f) { return float4(_hlslpp_floor_ps(f.vec)); }

	// A note on negative numbers. Contrary to intuition, frac(-0.75) != 0.75,
	// but is actually frac(-0.75) == 0.25 This is because hlsl defines frac
	// as frac(x) = x - floor(x)
	float1 frac(const float1& f) { return float1(_hlslpp_frac_ps(f.vec)); }
	float2 frac(const float2& f) { return float2(_hlslpp_frac_ps(f.vec)); }
	float3 frac(const float3& f) { return float3(_hlslpp_frac_ps(f.vec)); }
	float4 frac(const float4& f) { return float4(_hlslpp_frac_ps(f.vec)); }

	float1 isfinite(const float1& f) { return float1(_hlslpp_andnot_ps(_hlslpp_isfinite_ps(f.vec), f4_1)); }
	float2 isfinite(const float2& f) { return float2(_hlslpp_andnot_ps(_hlslpp_isfinite_ps(f.vec), f4_1)); }
	float3 isfinite(const float3& f) { return float3(_hlslpp_andnot_ps(_hlslpp_isfinite_ps(f.vec), f4_1)); }
	float4 isfinite(const float4& f) { return float4(_hlslpp_andnot_ps(_hlslpp_isfinite_ps(f.vec), f4_1)); }

	float1 isinf(const float1& f) { return float1(_hlslpp_and_ps(_hlslpp_isinf_ps(f.vec), f4_1)); }
	float2 isinf(const float2& f) { return float2(_hlslpp_and_ps(_hlslpp_isinf_ps(f.vec), f4_1)); }
	float3 isinf(const float3& f) { return float3(_hlslpp_and_ps(_hlslpp_isinf_ps(f.vec), f4_1)); }
	float4 isinf(const float4& f) { return float4(_hlslpp_and_ps(_hlslpp_isinf_ps(f.vec), f4_1)); }

	float1 isnan(const float1& f) { return float1(_hlslpp_and_ps(_hlslpp_isnan_ps(f.vec), f4_1)); }
	float2 isnan(const float2& f) { return float2(_hlslpp_and_ps(_hlslpp_isnan_ps(f.vec), f4_1)); }
	float3 isnan(const float3& f) { return float3(_hlslpp_and_ps(_hlslpp_isnan_ps(f.vec), f4_1)); }
	float4 isnan(const float4& f) { return float4(_hlslpp_and_ps(_hlslpp_isnan_ps(f.vec), f4_1)); }

	float1 length(const float1& f) { return f; }
	float1 length(const float2& f) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot2_ps(f.vec, f.vec))); }
	float1 length(const float3& f) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot3_ps(f.vec, f.vec))); }
	float1 length(const float4& f) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(f.vec, f.vec))); }

	float1 lerp(const float1& f1, const float1& f2, const float1& a) { return float1(_hlslpp_lrp_ps(f1.vec, f2.vec, a.vec)); }
	float2 lerp(const float2& f1, const float2& f2, const float2& a) { return float2(_hlslpp_lrp_ps(f1.vec, f2.vec, a.vec)); }
	float3 lerp(const float3& f1, const float3& f2, const float3& a) { return float3(_hlslpp_lrp_ps(f1.vec, f2.vec, a.vec)); }
	float4 lerp(const float4& f1, const float4& f2, const float4& a) { return float4(_hlslpp_lrp_ps(f1.vec, f2.vec, a.vec)); }

	float1 log(const float1& f) { return float1(_hlslpp_log_ps(f.vec)); }
	float2 log(const float2& f) { return float2(_hlslpp_log_ps(f.vec)); }
	float3 log(const float3& f) { return float3(_hlslpp_log_ps(f.vec)); }
	float4 log(const float4& f) { return float4(_hlslpp_log_ps(f.vec)); }

	float1 log2(const float1& f) { return float1(_hlslpp_log2_ps(f.vec)); }
	float2 log2(const float2& f) { return float2(_hlslpp_log2_ps(f.vec)); }
	float3 log2(const float3& f) { return float3(_hlslpp_log2_ps(f.vec)); }
	float4 log2(const float4& f) { return float4(_hlslpp_log2_ps(f.vec)); }

	float1 log10(const float1& f) { return float1(_hlslpp_log10_ps(f.vec)); }
	float2 log10(const float2& f) { return float2(_hlslpp_log10_ps(f.vec)); }
	float3 log10(const float3& f) { return float3(_hlslpp_log10_ps(f.vec)); }
	float4 log10(const float4& f) { return float4(_hlslpp_log10_ps(f.vec)); }

	float1 min(const float1& f1, const float1& f2) { return float1(_hlslpp_min_ps(f1.vec, f2.vec)); }
	float2 min(const float2& f1, const float2& f2) { return float2(_hlslpp_min_ps(f1.vec, f2.vec)); }
	float3 min(const float3& f1, const float3& f2) { return float3(_hlslpp_min_ps(f1.vec, f2.vec)); }
	float4 min(const float4& f1, const float4& f2) { return float4(_hlslpp_min_ps(f1.vec, f2.vec)); }

	float1 max(const float1& f1, const float1& f2) { return float1(_hlslpp_max_ps(f1.vec, f2.vec)); }
	float2 max(const float2& f1, const float2& f2) { return float2(_hlslpp_max_ps(f1.vec, f2.vec)); }
	float3 max(const float3& f1, const float3& f2) { return float3(_hlslpp_max_ps(f1.vec, f2.vec)); }
	float4 max(const float4& f1, const float4& f2) { return float4(_hlslpp_max_ps(f1.vec, f2.vec)); }

	float1 normalize(const float1&/* f*/) { return float1(1.0f); }
	float2 normalize(const float2& f) { return float2(_hlslpp_div_ps(f.vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot2_ps(f.vec, f.vec))))); }
	float3 normalize(const float3& f) { return float3(_hlslpp_div_ps(f.vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot3_ps(f.vec, f.vec))))); }
	float4 normalize(const float4& f) { return float4(_hlslpp_div_ps(f.vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(f.vec, f.vec))))); }

	float1 pow(const float1& f1, const float1& f2) { return float1(_hlslpp_exp2_ps(_hlslpp_mul_ps(f1.vec, _hlslpp_log2_ps(f2.vec)))); }
	float2 pow(const float2& f1, const float2& f2) { return float2(_hlslpp_exp2_ps(_hlslpp_mul_ps(f1.vec, _hlslpp_log2_ps(f2.vec)))); }
	float3 pow(const float3& f1, const float3& f2) { return float3(_hlslpp_exp2_ps(_hlslpp_mul_ps(f1.vec, _hlslpp_log2_ps(f2.vec)))); }
	float4 pow(const float4& f1, const float4& f2) { return float4(_hlslpp_exp2_ps(_hlslpp_mul_ps(f1.vec, _hlslpp_log2_ps(f2.vec)))); }

	float1 radians(const float1& f) { return float1(_hlslpp_mul_ps(f.vec, f4_deg2rad)); }
	float2 radians(const float2& f) { return float2(_hlslpp_mul_ps(f.vec, f4_deg2rad)); }
	float3 radians(const float3& f) { return float3(_hlslpp_mul_ps(f.vec, f4_deg2rad)); }
	float4 radians(const float4& f) { return float4(_hlslpp_mul_ps(f.vec, f4_deg2rad)); }

	float1 rcp(const float1& f) { return float1(_hlslpp_rcp_ps(f.vec)); }
	float2 rcp(const float2& f) { return float2(_hlslpp_rcp_ps(f.vec)); }
	float3 rcp(const float3& f) { return float3(_hlslpp_rcp_ps(f.vec)); }
	float4 rcp(const float4& f) { return float4(_hlslpp_rcp_ps(f.vec)); }

	float1 reflect(const float1& i, const float1& n) { return float1(_hlslpp_sub_ps(i.vec, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n.vec, _hlslpp_perm_xxxx_ps(_hlslpp_mul_ps(i.vec, n.vec)))))); }
	float2 reflect(const float2& i, const float2& n) { return float2(_hlslpp_sub_ps(i.vec, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n.vec, _hlslpp_perm_xxxx_ps(_hlslpp_mul_ps(i.vec, n.vec)))))); }
	float3 reflect(const float3& i, const float3& n) { return float3(_hlslpp_sub_ps(i.vec, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n.vec, _hlslpp_perm_xxxx_ps(_hlslpp_mul_ps(i.vec, n.vec)))))); }
	float4 reflect(const float4& i, const float4& n) { return float4(_hlslpp_sub_ps(i.vec, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n.vec, _hlslpp_perm_xxxx_ps(_hlslpp_mul_ps(i.vec, n.vec)))))); }

	float1 rsqrt(const float1& f) { return float1(_hlslpp_rsqrt_ps(f.vec)); }
	float2 rsqrt(const float2& f) { return float2(_hlslpp_rsqrt_ps(f.vec)); }
	float3 rsqrt(const float3& f) { return float3(_hlslpp_rsqrt_ps(f.vec)); }
	float4 rsqrt(const float4& f) { return float4(_hlslpp_rsqrt_ps(f.vec)); }

	float1 round(const float1& f) { return float1(_hlslpp_round_ps(f.vec)); }
	float2 round(const float2& f) { return float2(_hlslpp_round_ps(f.vec)); }
	float3 round(const float3& f) { return float3(_hlslpp_round_ps(f.vec)); }
	float4 round(const float4& f) { return float4(_hlslpp_round_ps(f.vec)); }

	float1 saturate(const float1& f) { return float1(_hlslpp_sat_ps(f.vec)); }
	float2 saturate(const float2& f) { return float2(_hlslpp_sat_ps(f.vec)); }
	float3 saturate(const float3& f) { return float3(_hlslpp_sat_ps(f.vec)); }
	float4 saturate(const float4& f) { return float4(_hlslpp_sat_ps(f.vec)); }

	float1 sign(const float1& f) { return float1(_hlslpp_sign_ps(f.vec)); }
	float2 sign(const float2& f) { return float2(_hlslpp_sign_ps(f.vec)); }
	float3 sign(const float3& f) { return float3(_hlslpp_sign_ps(f.vec)); }
	float4 sign(const float4& f) { return float4(_hlslpp_sign_ps(f.vec)); }

	float1 sin(const float1& f) { return float1(_hlslpp_sin_ps(f.vec)); }
	float2 sin(const float2& f) { return float2(_hlslpp_sin_ps(f.vec)); }
	float3 sin(const float3& f) { return float3(_hlslpp_sin_ps(f.vec)); }
	float4 sin(const float4& f) { return float4(_hlslpp_sin_ps(f.vec)); }

	float1 sinh(const float1& f) { return float1(_hlslpp_sinh_ps(f.vec)); }
	float2 sinh(const float2& f) { return float2(_hlslpp_sinh_ps(f.vec)); }
	float3 sinh(const float3& f) { return float3(_hlslpp_sinh_ps(f.vec)); }
	float4 sinh(const float4& f) { return float4(_hlslpp_sinh_ps(f.vec)); }

	float1 smoothstep(const float1& f1, const float1& f2, const float1& a) { return float1(_hlslpp_smoothstep_ps(f1.vec, f2.vec, a.vec)); }
	float2 smoothstep(const float2& f1, const float2& f2, const float2& a) { return float2(_hlslpp_smoothstep_ps(f1.vec, f2.vec, a.vec)); }
	float3 smoothstep(const float3& f1, const float3& f2, const float3& a) { return float3(_hlslpp_smoothstep_ps(f1.vec, f2.vec, a.vec)); }
	float4 smoothstep(const float4& f1, const float4& f2, const float4& a) { return float4(_hlslpp_smoothstep_ps(f1.vec, f2.vec, a.vec)); }

	float1 sqrt(const float1& f) { return float1(_hlslpp_sqrt_ps(f.vec)); }
	float2 sqrt(const float2& f) { return float2(_hlslpp_sqrt_ps(f.vec)); }
	float3 sqrt(const float3& f) { return float3(_hlslpp_sqrt_ps(f.vec)); }
	float4 sqrt(const float4& f) { return float4(_hlslpp_sqrt_ps(f.vec)); }

	float1 step(const float1& f1, const float1& f2) { return float1(_hlslpp_step_ps(f1.vec, f2.vec)); }
	float2 step(const float2& f1, const float2& f2) { return float2(_hlslpp_step_ps(f1.vec, f2.vec)); }
	float3 step(const float3& f1, const float3& f2) { return float3(_hlslpp_step_ps(f1.vec, f2.vec)); }
	float4 step(const float4& f1, const float4& f2) { return float4(_hlslpp_step_ps(f1.vec, f2.vec)); }

	float1 tan(const float1& f) { return float1(_hlslpp_tan_ps(f.vec)); }
	float2 tan(const float2& f) { return float2(_hlslpp_tan_ps(f.vec)); }
	float3 tan(const float3& f) { return float3(_hlslpp_tan_ps(f.vec)); }
	float4 tan(const float4& f) { return float4(_hlslpp_tan_ps(f.vec)); }

	float1 tanh(const float1& f) { return float1(_hlslpp_tanh_ps(f.vec)); }
	float2 tanh(const float2& f) { return float2(_hlslpp_tanh_ps(f.vec)); }
	float3 tanh(const float3& f) { return float3(_hlslpp_tanh_ps(f.vec)); }
	float4 tanh(const float4& f) { return float4(_hlslpp_tanh_ps(f.vec)); }

	float1 trunc(const float1& f) { return float1(_hlslpp_trunc_ps(f.vec)); }
	float2 trunc(const float2& f) { return float2(_hlslpp_trunc_ps(f.vec)); }
	float3 trunc(const float3& f) { return float3(_hlslpp_trunc_ps(f.vec)); }
	float4 trunc(const float4& f) { return float4(_hlslpp_trunc_ps(f.vec)); }

	//------------------------------------------------------------------------------------------------------------------------
	// float1 and swizzle1 need special overloads to disambiguate between our operators/functions and built-in float operators
	// and functions that are part of common headers such as cmath, math.h, algorithm, etc
	//------------------------------------------------------------------------------------------------------------------------

	template<typename T, enable_if_number<T> = nullptr> float1 operator + (const float1& f1, T f2) { return f1 + float1(f2); }
	template<typename T, enable_if_number<T> = nullptr> float1 operator + (T f1, const float1& f2) { return float1(f1) + f2; }

	template<typename T, enable_if_number<T> = nullptr> float1 operator - (const float1& f1, T f2) { return f1 - float1(f2); }
	template<typename T, enable_if_number<T> = nullptr> float1 operator - (T f1, const float1& f2) { return float1(f1) - f2; }

	template<typename T, enable_if_number<T> = nullptr> float1 operator * (const float1& f1, T f2) { return f1 * float1(f2); }
	template<typename T, enable_if_number<T> = nullptr> float1 operator * (T f1, const float1& f2) { return float1(f1) * f2; }

	template<typename T, enable_if_number<T> = nullptr> float1 operator / (const float1& f1, T f2) { return f1 / float1(f2); }
	template<typename T, enable_if_number<T> = nullptr> float1 operator / (T f1, const float1& f2) { return float1(f1) / f2; }

	template<int X> float1 operator + (const swizzle1<X>& s, const float1& f) { return float1(s) + f; }
	template<int X> float1 operator - (const swizzle1<X>& s, const float1& f) { return float1(s) - f; }
	template<int X> float1 operator * (const swizzle1<X>& s, const float1& f) { return float1(s) * f; }
	template<int X> float1 operator / (const swizzle1<X>& s, const float1& f) { return float1(s) / f; }
	
	template<int X> float1 operator - (const swizzle1<X>& s) { return -float1(s); }

	template<int X, int Y> float1 max(const swizzle1<X>& s, const swizzle1<Y>& f) { return max(float1(s), float1(f)); }
	template<int X> float1 max(const swizzle1<X>& s, const swizzle1<X>& f) { return max(float1(s), float1(f)); }

	template<int X, int Y> float1 min(const swizzle1<X>& s, const swizzle1<Y>& f) { return min(float1(s), float1(f)); }
	template<int X> float1 min(const swizzle1<X>& s, const swizzle1<X>& f) { return min(float1(s), float1(f)); }

	template<int X, int Y> float1 pow(const swizzle1<X>& s, const swizzle1<Y>& f) { return pow(float1(s), float1(f)); }

	template<int X> float1 abs(const swizzle1<X>& s) { return abs(float1(s)); }
	template<int X> float1 acos(const swizzle1<X>& s) { return acos(float1(s)); }
	template<int X> float1 asin(const swizzle1<X>& s) { return asin(float1(s)); }
	template<int X> float1 atan(const swizzle1<X>& s) { return atan(float1(s)); }
	template<int X> float1 ceil(const swizzle1<X>& s) { return ceil(float1(s)); }
	template<int X> float1 cos(const swizzle1<X>& s) { return cos(float1(s)); }
	template<int X> float1 cosh(const swizzle1<X>& s) { return cosh(float1(s)); }
	template<int X> float1 floor(const swizzle1<X>& s) { return floor(float1(s)); }
	template<int X> float1 frac(const swizzle1<X>& s) { return frac(float1(s)); }
	template<int X> float1 exp(const swizzle1<X>& s) { return exp(float1(s)); }
	template<int X> float1 exp2(const swizzle1<X>& s) { return exp2(float1(s)); }
	template<int X> float1 log(const swizzle1<X>& s) { return log(float1(s)); }
	template<int X> float1 log2(const swizzle1<X>& s) { return log2(float1(s)); }
	template<int X> float1 log10(const swizzle1<X>& s) { return log10(float1(s)); }
	template<int X> float1 round(const swizzle1<X>& s) { return round(float1(s)); }
	template<int X> float1 sin(const swizzle1<X>& s) { return sin(float1(s)); }
	template<int X> float1 sinh(const swizzle1<X>& s) { return sinh(float1(s)); }
	template<int X> float1 sqrt(const swizzle1<X>& s) { return sqrt(float1(s)); }
	template<int X> float1 tan(const swizzle1<X>& s) { return tan(float1(s)); }
	template<int X> float1 tanh(const swizzle1<X>& s) { return tanh(float1(s)); }
	template<int X> float1 trunc(const swizzle1<X>& s) { return trunc(float1(s)); }

	template<int X> float1 isfinite(const swizzle1<X>& s) { return isfinite(float1(s)); }
	template<int X> float1 isnan(const swizzle1<X>& s) { return isnan(float1(s)); }
	template<int X> float1 isinf(const swizzle1<X>& s) { return isinf(float1(s)); }

	template<int X, int Y> float2 isfinite(const swizzle2<X, Y>& s) { return isfinite(float2(s)); }
	template<int X, int Y> float2 isinf(const swizzle2<X, Y>& s) { return isinf(float2(s)); }
	template<int X, int Y> float2 isnan(const swizzle2<X, Y>& s) { return isnan(float2(s)); }

	template<int X, int Y, int Z> float3 isfinite(const swizzle3<X, Y, Z>& s) { return isfinite(float3(s)); }
	template<int X, int Y, int Z> float3 isinf(const swizzle3<X, Y, Z>& s) { return isinf(float3(s)); }
	template<int X, int Y, int Z> float3 isnan(const swizzle3<X, Y, Z>& s) { return isnan(float3(s)); }

	template<int X, int Y, int Z, int W> float4 isfinite(const swizzle4<X, Y, Z, W>& s) { return isfinite(float4(s)); }
	template<int X, int Y, int Z, int W> float4 isinf(const swizzle4<X, Y, Z, W>& s) { return isinf(float4(s)); }
	template<int X, int Y, int Z, int W> float4 isnan(const swizzle4<X, Y, Z, W>& s) { return isnan(float4(s)); }

	template<int X>
	swizzle1<X>& swizzle1<X>::operator = (const float1& f)
	{
		vec = _hlslpp_blend_ps(vec, f.vec, HLSLPP_COMPONENT_X(X)); return *this;
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

	//----------------------//
	// Integer swizzle type //
	//----------------------//

	template<int X>
	struct iswizzle1
	{
		template<int A> friend struct iswizzle1;
	
		// Cast
	
		operator int32_t() const { return i32[X]; }
	
		// Helper
	
		template<int E, int A>
		static n128i swizzle(n128i v)
		{
			const int finalMask = (((IdentityMask >> 2 * E) & 3) << 2 * A) | (IdentityMask & ~((3 << 2 * A)));
			return _hlslpp_perm_epi32(v, finalMask);
		}
	
		template<int E, int A>
		n128i swizzle() const
		{
			return swizzle<E, A>(vec);
		}
	
		iswizzle1& operator = (int32_t i)
		{
			vec = _hlslpp_blend_epi32(vec, _hlslpp_set1_epi32(i), HLSLPP_COMPONENT_X(X));
			return *this;
		}
	
		// Assignment
	
		template<int A>
		iswizzle1& operator = (const iswizzle1<A>& s) // Revise this function. Can I not do with swizzle?
		{
			n128i t = _hlslpp_shuffle_epi32(s.vec, s.vec, HLSLPP_SHUFFLE_MASK(A, A, A, A));
			vec = _hlslpp_blend_epi32(vec, t, HLSLPP_COMPONENT_X(X));
			return *this;
		}
	
		iswizzle1& operator = (const int1& i);
	
	private:
		union
		{
			n128i vec;
			int32_t i32[4];
		};
	};


	template<int X, int Y>
	struct iswizzle2
	{
		// Helper

		void staticAsserts()
		{
			// Assert that no component is equal to each other for assignment
			static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		static n128i blend(n128i x, n128i y)
		{
			return _hlslpp_blend_epi32(x, y, HLSLPP_COMPONENT_XY(X, Y)); // Select based on property mask
		}

		template<int E, int F, int A, int B>
		static n128i swizzle(n128i v)
		{
			const int finalMask =
				(((IdentityMask >> 2 * E) & 3) << 2 * A) |
				(((IdentityMask >> 2 * F) & 3) << 2 * B) |
				(IdentityMask & ~((3 << 2 * A) | (3 << 2 * B)));
			return _hlslpp_perm_epi32(v, finalMask);
		}

		template<int E, int F, int A, int B>
		n128i swizzle() const
		{
			return swizzle<E, F, A, B>(vec);
		}

		// Assignment

		template<int A, int B>
		iswizzle2& operator = (const iswizzle2<A, B>& s)
		{
			staticAsserts();
			vec = blend(vec, s.template swizzle<A, B, X, Y>());
			return *this;
		}

		iswizzle2& operator = (const int2& i);

	private:
		union
		{
			n128i vec;
			int32_t i32[4];
		};
	};

	template<int X, int Y, int Z>
	struct iswizzle3
	{
		// Helper

		void staticAsserts()
		{
			// Assert that no component is equal to each other for assignment
			static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		static n128i blend(n128i x, n128i y)
		{
			return _hlslpp_blend_epi32(x, y, HLSLPP_COMPONENT_XYZ(X, Y, Z)); // Select based on property mask
		}

		template<int E, int F, int G, int A, int B, int C>
		static n128i swizzle(n128i v)
		{
			const int finalMask =
				(((IdentityMask >> 2 * E) & 3) << 2 * A) |
				(((IdentityMask >> 2 * F) & 3) << 2 * B) |
				(((IdentityMask >> 2 * G) & 3) << 2 * C) |
				(IdentityMask & ~((3 << 2 * A) | (3 << 2 * B) | (3 << 2 * C)));
			return _hlslpp_perm_epi32(v, finalMask);
		}

		template<int E, int F, int G, int A, int B, int C>
		n128i swizzle() const
		{
			return swizzle<E, F, G, A, B, C>(vec);
		}

		// Assignment

		template<int A, int B, int C>
		iswizzle3& operator = (const iswizzle3<A, B, C>& s)
		{
			staticAsserts();
			vec = blend(vec, s.template swizzle<A, B, C, X, Y, Z>());
			return *this;
		}

		iswizzle3& operator = (const int3& i);

	private:
		union
		{
			n128i vec;
			int32_t i32[4];
		};
	};

	template<int X, int Y, int Z, int W>
	struct iswizzle4
	{
		// Helper

		void staticAsserts()
		{
			// Assert that no component is equal to each other for assignment
			static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		template<int E, int F, int G, int H, int A, int B, int C, int D>
		static n128i swizzle(n128i v)
		{
			const int finalMask =
				(((IdentityMask >> 2 * E) & 3) << (2 * A)) |
				(((IdentityMask >> 2 * F) & 3) << (2 * B)) |
				(((IdentityMask >> 2 * G) & 3) << (2 * C)) |
				(((IdentityMask >> 2 * H) & 3) << (2 * D));

			return _hlslpp_perm_epi32(v, finalMask);
		}

		template<int E, int F, int G, int H, int A, int B, int C, int D>
		n128i swizzle() const
		{
			return swizzle<E, F, G, H, A, B, C, D>(vec);
		}

		// Assignment

		template<int A, int B, int C, int D>
		iswizzle4& operator = (const iswizzle4<A, B, C, D>& s)
		{
			staticAsserts();
			vec = s.template swizzle<A, B, C, D, X, Y, Z, W>();
			return *this;
		}

		iswizzle4& operator = (const int4& i);

	private:
		union
		{
			n128i vec;
			float i32[4];
		};
	};

	//--------------//
	// Integer type //
	//--------------//

	struct int1
	{
		int1() {}
		int1(const int1& i) : vec(i.vec) {}
		explicit int1(n128i vec) : vec(vec) {}

		template<typename T, enable_if_number<T> = nullptr>
		int1(T i) : vec(_hlslpp_set_epi32(int(i), 0, 0, 0)) {}

		template<int X> int1(const iswizzle1<X>& s) : vec(s.template swizzle<X, 0>()) {}

		operator int32_t() const { return i32[0]; }

		union
		{
			n128i vec;
			int32_t i32[4];
			#include "swizzle/hlsl++_vector_int_x.h"
			#include "swizzle/hlsl++_vector_int_r.h"
		};
	};

	
	struct int2
	{
		// Constructors

		int2() {}
		int2(const int2& i) : vec(i.vec) {}
		explicit int2(n128i vec) : vec(vec) {}
		explicit int2(const int1& i) : vec(_hlslpp_perm_xxxx_epi32(i.vec)) {}

		int2(int32_t i) : vec(_hlslpp_set_epi32(i, i, 0, 0)) {}

		template<typename T1, typename T2, enable_if_number_2<T1, T2> = nullptr>
		int2(T1 i1, T2 i2) : vec(_hlslpp_set_epi32(int(i1), int(i2), 0, 0)) {}

		int2(const int1& i1, const int1& i2) { vec = _hlslpp_blend_epi32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }
		
		template<int X, int Y> int2(const iswizzle2<X, Y>& s) : vec(s.template swizzle<X, Y, 0, 1>()) {}

		union
		{
			n128i vec;
			int32_t i32[4];
			#include "swizzle/hlsl++_vector_int_x.h"
			#include "swizzle/hlsl++_vector_int_y.h"
			#include "swizzle/hlsl++_vector_int_r.h"
			#include "swizzle/hlsl++_vector_int_g.h"
		};
	};

	struct int3
	{
		// Constructors

		int3() {}
		int3(const int3& i) : vec(i.vec) {}
		explicit int3(n128i vec) : vec(vec) {}

		explicit int3(const int1& i) : vec(_hlslpp_perm_xxxx_epi32(i.vec)) {}

		int3(int32_t i) : vec(_hlslpp_set_epi32(i, i, i, 0)) {}

		template<typename T1, typename T2, typename T3, enable_if_number_3<T1, T2, T3> = nullptr>
		int3(T1 i1, T2 i2, T3 i3) : vec(_hlslpp_set_epi32(int(i1), int(i2), int(i3), 0)) {}

		int3(const int1& i1, const int1& i2, const int1& i3) { vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxx_epi32(i1.vec, i3.vec), _hlslpp_perm_xxxx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }

		int3(const int2& i1, const int1& i2) { vec = _hlslpp_shuf_xyxx_epi32(i1.vec, i2.vec); }
		int3(const int1& i1, const int2& i2) { vec = _hlslpp_blend_epi32(i1.vec, _hlslpp_perm_xxyx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }

		template<int X, int Y, int Z>
		int3(const iswizzle3<X, Y, Z>& s) : vec(s.template swizzle<X, Y, Z, 0, 1, 2>()) {}

		union
		{
			n128i vec;
			int32_t i32[4];
			#include "swizzle/hlsl++_vector_int_x.h"
			#include "swizzle/hlsl++_vector_int_y.h"
			#include "swizzle/hlsl++_vector_int_z.h"
			#include "swizzle/hlsl++_vector_int_r.h"
			#include "swizzle/hlsl++_vector_int_g.h"
			#include "swizzle/hlsl++_vector_int_b.h"
		};
	};

	struct int4
	{
		int4() {}
		int4(const int4& i) : vec(i.vec) {}
		explicit int4(n128i vec) : vec(vec) {}

		explicit int4(const int1& i) : vec(_hlslpp_perm_xxxx_epi32(i.vec)) {}

		int4(int32_t i) : vec(_hlslpp_set1_epi32(i)) {}

		template<typename T1, typename T2, typename T3, typename T4, enable_if_number_4<T1, T2, T3, T4> = nullptr>
		int4(T1 i1, T2 i2, T3 i3, T4 i4) : vec(_hlslpp_set_epi32(int(i1), int(i2), int(i3), int(i4))) {}

		int4(const int1& i1, const int1& i2, const int1& i3, const int1& i4) { vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxx_epi32(i1.vec, i3.vec), _hlslpp_shuf_xxxx_epi32(i2.vec, i4.vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }
		
		int4(const int2& i1, const int1& i2, const int1& i3) { vec = _hlslpp_blend_epi32(_hlslpp_shuf_xyxx_epi32(i1.vec, i2.vec), _hlslpp_perm_xxxx_epi32(i3.vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }
		int4(const int1& i1, const int2& i2, const int1& i3) { vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxx_epi32(i1.vec, i3.vec), _hlslpp_perm_xxyx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }
		int4(const int1& i1, const int1& i2, const int2& i3) { vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxy_epi32(i1.vec, i3.vec), _hlslpp_perm_xxxx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }

		int4(const int2& i1, const int2& f2) { vec = _hlslpp_shuf_xyxy_epi32(i1.vec, f2.vec); }

		int4(const int1& i1, const int3& i2) { vec = _hlslpp_blend_epi32(i1.vec, _hlslpp_perm_xxyz_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 0)); }
		int4(const int3& i1, const int1& i2) { vec = _hlslpp_blend_epi32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }

		template<int X, int Y, int Z, int W>
		int4(const iswizzle4<X, Y, Z, W>& s) : vec(s.template swizzle<X, Y, Z, W, 0, 1, 2, 3>()) {}

		int4& operator = (const int4& i) { vec = i.vec; return *this; }

		union
		{
			n128i vec;
			int32_t i32[4];
			#include "swizzle/hlsl++_vector_int_x.h"
			#include "swizzle/hlsl++_vector_int_y.h"
			#include "swizzle/hlsl++_vector_int_z.h"
			#include "swizzle/hlsl++_vector_int_w.h"
			#include "swizzle/hlsl++_vector_int_r.h"
			#include "swizzle/hlsl++_vector_int_g.h"
			#include "swizzle/hlsl++_vector_int_b.h"
			#include "swizzle/hlsl++_vector_int_a.h"
		};
	};

	// Operators

	int1 operator + (const int1& i1, const int1& i2) { return int1(_hlslpp_add_epi32(i1.vec, i2.vec)); }
	int2 operator + (const int2& i1, const int2& i2) { return int2(_hlslpp_add_epi32(i1.vec, i2.vec)); }
	int3 operator + (const int3& i1, const int3& i2) { return int3(_hlslpp_add_epi32(i1.vec, i2.vec)); }
	int4 operator + (const int4& i1, const int4& i2) { return int4(_hlslpp_add_epi32(i1.vec, i2.vec)); }

	int1 operator - (const int1& i1, const int1& i2) { return int1(_hlslpp_sub_epi32(i1.vec, i2.vec)); }
	int2 operator - (const int2& i1, const int2& i2) { return int2(_hlslpp_sub_epi32(i1.vec, i2.vec)); }
	int3 operator - (const int3& i1, const int3& i2) { return int3(_hlslpp_sub_epi32(i1.vec, i2.vec)); }
	int4 operator - (const int4& i1, const int4& i2) { return int4(_hlslpp_sub_epi32(i1.vec, i2.vec)); }

	int1 operator * (const int1& i1, const int1& i2) { return int1(_hlslpp_mul_epi32(i1.vec, i2.vec)); }
	int2 operator * (const int2& i1, const int2& i2) { return int2(_hlslpp_mul_epi32(i1.vec, i2.vec)); }
	int3 operator * (const int3& i1, const int3& i2) { return int3(_hlslpp_mul_epi32(i1.vec, i2.vec)); }
	int4 operator * (const int4& i1, const int4& i2) { return int4(_hlslpp_mul_epi32(i1.vec, i2.vec)); }

	int1 operator / (const int1& i1, const int1& i2) { return int1(_hlslpp_div_epi32(i1.vec, i2.vec)); }
	int2 operator / (const int2& i1, const int2& i2) { return int2(_hlslpp_div_epi32(i1.vec, i2.vec)); }
	int3 operator / (const int3& i1, const int3& i2) { return int3(_hlslpp_div_epi32(i1.vec, i2.vec)); }
	int4 operator / (const int4& i1, const int4& i2) { return int4(_hlslpp_div_epi32(i1.vec, i2.vec)); }

	//------------------------------------------------------------------------------------------------------------------------//
	// int1 and iswizzle1 need special overloads to disambiguate between our operators/functions and built-in float operators //
	// and functions that are part of common headers such as cmath, math.h, algorithm, etc                                    //
	//------------------------------------------------------------------------------------------------------------------------//

	template<typename T, enable_if_number<T> = nullptr> int1 operator + (const int1& i1, T i2) { return i1 + int1(i2); }
	template<typename T, enable_if_number<T> = nullptr> int1 operator + (T i1, const int1& i2) { return int1(i1) + i2; }

	template<typename T, enable_if_number<T> = nullptr> int1 operator - (const int1& i1, T i2) { return i1 - int1(i2); }
	template<typename T, enable_if_number<T> = nullptr> int1 operator - (T i1, const int1& i2) { return int1(i1) - i2; }

	template<typename T, enable_if_number<T> = nullptr> int1 operator * (const int1& i1, T i2) { return i1 * int1(i2); }
	template<typename T, enable_if_number<T> = nullptr> int1 operator * (T i1, const int1& i2) { return int1(i1) * i2; }

	template<typename T, enable_if_number<T> = nullptr> int1 operator / (const int1& i1, T i2) { return i1 / int1(i2); }
	template<typename T, enable_if_number<T> = nullptr> int1 operator / (T i1, const int1& i2) { return int1(i1) / i2; }

	template<int X> int1 operator + (const iswizzle1<X>& s, const int1& i) { return int1(s) + i; }
	template<int X> int1 operator - (const iswizzle1<X>& s, const int1& i) { return int1(s) - i; }
	template<int X> int1 operator * (const iswizzle1<X>& s, const int1& i) { return int1(s) * i; }
	template<int X> int1 operator / (const iswizzle1<X>& s, const int1& i) { return int1(s) / i; }

	int1 operator - (const int1& i) { return int1(_hlslpp_neg_epi32(i.vec)); }
	int2 operator - (const int2& i) { return int2(_hlslpp_neg_epi32(i.vec)); }
	int3 operator - (const int3& i) { return int3(_hlslpp_neg_epi32(i.vec)); }
	int4 operator - (const int4& i) { return int4(_hlslpp_neg_epi32(i.vec)); }

	int1& operator += (int1& i1, const int1& i2) { i1 = i1 + i2; return i1; }
	int2& operator += (int2& i1, const int2& i2) { i1 = i1 + i2; return i1; }
	int3& operator += (int3& i1, const int3& i2) { i1 = i1 + i2; return i1; }
	int4& operator += (int4& i1, const int4& i2) { i1 = i1 + i2; return i1; }

	template<int X>	iswizzle1<X>& operator += (iswizzle1<X>& s, const int1& i) { s = int1(s) + i; return s; }
	template<int X>	iswizzle1<X>& operator -= (iswizzle1<X>& s, const int1& i) { s = int1(s) - i; return s; }
	template<int X>	iswizzle1<X>& operator *= (iswizzle1<X>& s, const int1& i) { s = int1(s) * i; return s; }
	template<int X>	iswizzle1<X>& operator /= (iswizzle1<X>& s, const int1& i) { s = int1(s) / i; return s; }

	template<int X, int Y> iswizzle2<X, Y>& operator += (iswizzle2<X, Y>& s, const int2& i) { s = int2(s) + i; return s; }
	template<int X, int Y> iswizzle2<X, Y>& operator -= (iswizzle2<X, Y>& s, const int2& i) { s = int2(s) - i; return s; }
	template<int X, int Y> iswizzle2<X, Y>& operator *= (iswizzle2<X, Y>& s, const int2& i) { s = int2(s) * i; return s; }
	template<int X, int Y> iswizzle2<X, Y>& operator /= (iswizzle2<X, Y>& s, const int2& i) { s = int2(s) / i; return s; }

	template<int X, int Y, int Z> iswizzle3<X, Y, Z>& operator += (iswizzle3<X, Y, Z>& s, const int3& i) { s = int3(s) + i; return s; }
	template<int X, int Y, int Z> iswizzle3<X, Y, Z>& operator -= (iswizzle3<X, Y, Z>& s, const int3& i) { s = int3(s) - i; return s; }
	template<int X, int Y, int Z> iswizzle3<X, Y, Z>& operator *= (iswizzle3<X, Y, Z>& s, const int3& i) { s = int3(s) * i; return s; }
	template<int X, int Y, int Z> iswizzle3<X, Y, Z>& operator /= (iswizzle3<X, Y, Z>& s, const int3& i) { s = int3(s) / i; return s; }

	template<int X, int Y, int Z, int W> iswizzle4<X, Y, Z, W>& operator += (iswizzle4<X, Y, Z, W>& s, const int4& i) { s = int4(s) + i; return s; }
	template<int X, int Y, int Z, int W> iswizzle4<X, Y, Z, W>& operator -= (iswizzle4<X, Y, Z, W>& s, const int4& i) { s = int4(s) - i; return s; }
	template<int X, int Y, int Z, int W> iswizzle4<X, Y, Z, W>& operator *= (iswizzle4<X, Y, Z, W>& s, const int4& i) { s = int4(s) * i; return s; }
	template<int X, int Y, int Z, int W> iswizzle4<X, Y, Z, W>& operator /= (iswizzle4<X, Y, Z, W>& s, const int4& i) { s = int4(s) / i; return s; }

	int1& operator -= (int1& i1, const int1& i2) { i1 = i1 - i2; return i1; }
	int2& operator -= (int2& i1, const int2& i2) { i1 = i1 - i2; return i1; }
	int3& operator -= (int3& i1, const int3& i2) { i1 = i1 - i2; return i1; }
	int4& operator -= (int4& i1, const int4& i2) { i1 = i1 - i2; return i1; }

	int1& operator *= (int1& i1, const int1& i2) { i1 = i1 * i2; return i1; }
	int2& operator *= (int2& i1, const int2& i2) { i1 = i1 * i2; return i1; }
	int3& operator *= (int3& i1, const int3& i2) { i1 = i1 * i2; return i1; }
	int4& operator *= (int4& i1, const int4& i2) { i1 = i1 * i2; return i1; }

	int1 operator == (const int1& i1, const int1& i2) { return int1(_hlslpp_cmpeq1_epi32(i1.vec, i2.vec)); }
	int2 operator == (const int2& i1, const int2& i2) { return int2(_hlslpp_cmpeq1_epi32(i1.vec, i2.vec)); }
	int3 operator == (const int3& i1, const int3& i2) { return int3(_hlslpp_cmpeq1_epi32(i1.vec, i2.vec)); }
	int4 operator == (const int4& i1, const int4& i2) { return int4(_hlslpp_cmpeq1_epi32(i1.vec, i2.vec)); }

	int1 operator != (const int1& i1, const int1& i2) { return int1(_hlslpp_cmpneq1_epi32(i1.vec, i2.vec)); }
	int2 operator != (const int2& i1, const int2& i2) { return int2(_hlslpp_cmpneq1_epi32(i1.vec, i2.vec)); }
	int3 operator != (const int3& i1, const int3& i2) { return int3(_hlslpp_cmpneq1_epi32(i1.vec, i2.vec)); }
	int4 operator != (const int4& i1, const int4& i2) { return int4(_hlslpp_cmpneq1_epi32(i1.vec, i2.vec)); }

	int1 operator > (const int1& i1, const int1& i2) { return int1(_hlslpp_cmpgt1_epi32(i1.vec, i2.vec)); }
	int2 operator > (const int2& i1, const int2& i2) { return int2(_hlslpp_cmpgt1_epi32(i1.vec, i2.vec)); }
	int3 operator > (const int3& i1, const int3& i2) { return int3(_hlslpp_cmpgt1_epi32(i1.vec, i2.vec)); }
	int4 operator > (const int4& i1, const int4& i2) { return int4(_hlslpp_cmpgt1_epi32(i1.vec, i2.vec)); }

	int1 operator >= (const int1& i1, const int1& i2) { return int1(_hlslpp_cmpge1_epi32(i1.vec, i2.vec)); }
	int2 operator >= (const int2& i1, const int2& i2) { return int2(_hlslpp_cmpge1_epi32(i1.vec, i2.vec)); }
	int3 operator >= (const int3& i1, const int3& i2) { return int3(_hlslpp_cmpge1_epi32(i1.vec, i2.vec)); }
	int4 operator >= (const int4& i1, const int4& i2) { return int4(_hlslpp_cmpge1_epi32(i1.vec, i2.vec)); }

	int1 operator < (const int1& i1, const int1& i2) { return int1(_hlslpp_cmplt1_epi32(i1.vec, i2.vec)); }
	int2 operator < (const int2& i1, const int2& i2) { return int2(_hlslpp_cmplt1_epi32(i1.vec, i2.vec)); }
	int3 operator < (const int3& i1, const int3& i2) { return int3(_hlslpp_cmplt1_epi32(i1.vec, i2.vec)); }
	int4 operator < (const int4& i1, const int4& i2) { return int4(_hlslpp_cmplt1_epi32(i1.vec, i2.vec)); }

	int1 operator <= (const int1& i1, const int1& i2) { return int1(_hlslpp_cmple1_epi32(i1.vec, i2.vec)); }
	int2 operator <= (const int2& i1, const int2& i2) { return int2(_hlslpp_cmple1_epi32(i1.vec, i2.vec)); }
	int3 operator <= (const int3& i1, const int3& i2) { return int3(_hlslpp_cmple1_epi32(i1.vec, i2.vec)); }
	int4 operator <= (const int4& i1, const int4& i2) { return int4(_hlslpp_cmple1_epi32(i1.vec, i2.vec)); }

	int1 abs(const int1& i) { return int1(_hlslpp_abs_epi32(i.vec)); }
	int2 abs(const int2& i) { return int2(_hlslpp_abs_epi32(i.vec)); }
	int3 abs(const int3& i) { return int3(_hlslpp_abs_epi32(i.vec)); }
	int4 abs(const int4& i) { return int4(_hlslpp_abs_epi32(i.vec)); }

	template<int X>
	iswizzle1<X>& iswizzle1<X>::operator = (const int1& i)
	{
		vec = _hlslpp_blend_epi32(vec, i.vec, HLSLPP_COMPONENT_X(X)); return *this;
	}

	template<int X, int Y>
	iswizzle2<X, Y>& iswizzle2<X, Y>::operator = (const int2& i)
	{
		staticAsserts();
		vec = blend(vec, swizzle<0, 1, X, Y>(i.vec));
		return *this;
	}

	template<int X, int Y, int Z>
	iswizzle3<X, Y, Z>& iswizzle3<X, Y, Z>::operator = (const int3& i)
	{
		staticAsserts();
		vec = blend(vec, swizzle<0, 1, 2, X, Y, Z>(i.vec));
		return *this;
	}

	template<int X, int Y, int Z, int W>
	iswizzle4<X, Y, Z, W>& iswizzle4<X, Y, Z, W>::operator = (const int4& i)
	{
		staticAsserts();
		vec = swizzle<0, 1, 2, 3, X, Y, Z, W>(i.vec);
		return *this;
	}

	float1::float1(const int1& i) : vec(_hlslpp_castsi128_ps(i.vec)) {}

	float2::float2(const int2& i) : vec(_hlslpp_castsi128_ps(i.vec)) {}

	float3::float3(const int3& i) : vec(_hlslpp_castsi128_ps(i.vec)) {}

	float4::float4(const int4& i) : vec(_hlslpp_castsi128_ps(i.vec)) {}

	//-------------
	// Matrix types
	//-------------

	struct float1x1
	{
		float1x1() : vec(_hlslpp_setzero_ps()) {}

		explicit float1x1(n128 vec) : vec(vec) {}

		template<typename T, enable_if_number<T> = nullptr>
		explicit float1x1(T f) : vec(_hlslpp_set_ps(float(f), 0.0f, 0.0f, 0.0f)) {}

		float1x1(const float1& f) : vec(f.vec) {}
    
		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/hlsl++_matrix_row0_1.h"
		};
	};

	struct float1x2
	{
		float1x2() : vec(_hlslpp_setzero_ps()) {}

		explicit float1x2(n128 vec) : vec(vec) {}

		template<typename T, enable_if_number<T> = nullptr>
		explicit float1x2(T f) : vec(_hlslpp_set_ps(float(f), float(f), 0.0f, 0.0f)) {}

		explicit float1x2(float f0, float f1) : vec(_hlslpp_set_ps(f0, f1, 0.0f, 0.0f)) {}

		float1x2(const float2& f) : vec(f.vec) {}

		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/hlsl++_matrix_row0_2.h"
		};
	};

	struct float2x1
	{
		float2x1() : vec(_hlslpp_setzero_ps()) {}

		explicit float2x1(n128 vec) : vec(vec) {}

		template<typename T, enable_if_number<T> = nullptr>
		explicit float2x1(T f) : vec(_hlslpp_set_ps(float(f), float(f), 0.0f, 0.0f)) {}

		explicit float2x1(float f0, float f1) : vec(_hlslpp_set_ps(f0, f1, 0.0f, 0.0f)) {}

		float2x1(const float2& f) : vec(f.vec) {}

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct float1x3
	{
		float1x3() : vec(_hlslpp_setzero_ps()) {}

		explicit float1x3(n128 vec) : vec(vec) {}

		template<typename T, enable_if_number<T> = nullptr>
		explicit float1x3(T f) : vec(_hlslpp_set_ps(float(f), float(f), float(f), 0.0f)) {}

		explicit float1x3(float f0, float f1, float f2) : vec(_hlslpp_set_ps(f0, f1, f2, 0.0f)) {}

		float1x3(const float3& f) : vec(f.vec) {}

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct float3x1
	{
		float3x1() : vec(_hlslpp_setzero_ps()) {}

		explicit float3x1(n128 vec) : vec(vec) {}

		template<typename T, enable_if_number<T> = nullptr>
		explicit float3x1(T f) : vec(_hlslpp_set_ps(float(f), float(f), float(f), 0.0f)) {}

		explicit float3x1(float f0, float f1, float f2) : vec(_hlslpp_set_ps(f0, f1, f2, 0.0f)) {}

		float3x1(const float3& f) : vec(f.vec) {}

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct float1x4
	{
		float1x4() : vec(_hlslpp_setzero_ps()) {}

		explicit float1x4(n128 vec) : vec(vec) {}

		template<typename T, enable_if_number<T> = nullptr>
		explicit float1x4(T f) : vec(_hlslpp_set1_ps(float(f))) {}

		explicit float1x4(float f0, float f1, float f2, float f3) : vec(_hlslpp_set_ps(f0, f1, f2, f3)) {}

		float1x4(const float4& f) : vec(f.vec) {}

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct float4x1
	{
		float4x1() : vec(_hlslpp_setzero_ps()) {}

		explicit float4x1(n128 vec) : vec(vec) {}

		template<typename T, enable_if_number<T> = nullptr>
		explicit float4x1(T f) : vec(_hlslpp_set1_ps(float(f))) {}

		explicit float4x1(float f0, float f1, float f2, float f3) : vec(_hlslpp_set_ps(f0, f1, f2, f3)) {}

		float4x1(const float4& f) : vec(f.vec) {}

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct float2x2
	{
		float2x2() : vec(_hlslpp_setzero_ps()) {}

		explicit float2x2(n128 vec) : vec(vec) {}

		explicit float2x2(float f00, float f01,
		                  float f10, float f11) : vec(_hlslpp_set_ps(f00, f01, f10, f11)) {}

		explicit float2x2(float f) : vec(_hlslpp_set1_ps(f)) {}

		float2x2(const float2x2& m) : vec(m.vec) {}

		union
		{
			n128 vec; // Store it in a single vector to save memory
			float f32[4];
		};
	};

	struct float2x3
	{
		float2x3() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()) {}

		explicit float2x3(n128 vec0, n128 vec1) : vec0(vec0), vec1(vec1) {}

		explicit float2x3(float f) : vec0(_hlslpp_set_ps(f, f, f, 0.0f)), vec1(_hlslpp_set_ps(f, f, f, 0.0f)) {}

		explicit float2x3(float f00, float f01, float f02,
		                  float f10, float f11, float f12) : vec0(_hlslpp_set_ps(f00, f01, f02, 0.0f)), vec1(_hlslpp_set_ps(f10, f11, f12, 0.0f)) {}

		float2x3(const float2x3& m) : vec0(m.vec0), vec1(m.vec1) {}

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};
	};

	struct float3x2
	{
		float3x2() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()) {}

		explicit float3x2(n128 vec0, n128 vec1) : vec0(vec0), vec1(vec1) {}

		explicit float3x2(float f) : vec0(_hlslpp_set_ps(f, f, f, 0.0f)), vec1(_hlslpp_set_ps(f, f, f, 0.0f)) {}

		explicit float3x2(float f00, float f01,
		                  float f10, float f11,
		                  float f20, float f21) : vec0(_hlslpp_set_ps(f00, f10, f20, 0.0f)), vec1(_hlslpp_set_ps(f01, f11, f21, 0.0f)) {}

		float3x2(const float3x2& m) : vec0(m.vec0), vec1(m.vec1) {}

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};
	};

	struct float2x4
	{
		float2x4() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()) {}

		explicit float2x4(n128 vec0, n128 vec1) : vec0(vec0), vec1(vec1) {}

		explicit float2x4(float f00, float f01, float f02, float f03,
		                  float f10, float f11, float f12, float f13) : vec0(_hlslpp_set_ps(f00, f01, f02, f03)), vec1(_hlslpp_set_ps(f10, f11, f12, f13)) {}

		explicit float2x4(float f) : vec0(_hlslpp_set_ps(f, f, f, f)), vec1(_hlslpp_set_ps(f, f, f, f)) {}

		float2x4(const float2x4& m) : vec0(m.vec0), vec1(m.vec1) {}

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};
	};

	struct float4x2
	{
		float4x2() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()) {}

		explicit float4x2(n128 vec0, n128 vec1) : vec0(vec0), vec1(vec1) {}

		explicit float4x2(float f00, float f01,
		                  float f10, float f11,
		                  float f20, float f21,
		                  float f30, float f31) : vec0(_hlslpp_set_ps(f00, f10, f20, f30)), vec1(_hlslpp_set_ps(f01, f11, f21, f31)) {}

		explicit float4x2(float f) : vec0(_hlslpp_set_ps(f, f, f, f)), vec1(_hlslpp_set_ps(f, f, f, f)) {}

		float4x2(const float4x2& m) : vec0(m.vec0), vec1(m.vec1) {}

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};
	};

	struct quaternion;

	struct float3x3
	{
		float3x3() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()), vec2(_hlslpp_setzero_ps()) {}

		explicit float3x3(const n128 vec0, const n128 vec1, const n128 vec2) : vec0(vec0), vec1(vec1), vec2(vec2) {}

		explicit float3x3(float f00, float f01, float f02,
		                  float f10, float f11, float f12,
		                  float f20, float f21, float f22) : vec0(_hlslpp_set_ps(f00, f01, f02, 0.0f)), vec1(_hlslpp_set_ps(f10, f11, f12, 0.0f)), vec2(_hlslpp_set_ps(f20, f21, f22, 0.0f)) {}

		float3x3(const quaternion& q);

		explicit float3x3(float f) : vec0(_hlslpp_set1_ps(f)), vec1(_hlslpp_set1_ps(f)), vec2(_hlslpp_set1_ps(f)) {}

		float3x3(const float3x3& m) : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}

		static const float3x3& identity() { static const float3x3 iden = float3x3(1, 0, 0, 0, 1, 0, 0, 0, 1); return iden; }

		union
		{
			n128 vec0;
			float f32_0[4];
			#include "swizzle/hlsl++_matrix_row0_1.h"
			#include "swizzle/hlsl++_matrix_row0_2.h"
			#include "swizzle/hlsl++_matrix_row0_3.h"
		};

		union
		{
			n128 vec1;
			float f32_1[4];
			#include "swizzle/hlsl++_matrix_row1_1.h"
			#include "swizzle/hlsl++_matrix_row1_2.h"
			#include "swizzle/hlsl++_matrix_row1_3.h"
		};

		union
		{
			n128 vec2;
			float f32_2[4];
			#include "swizzle/hlsl++_matrix_row2_1.h"
			#include "swizzle/hlsl++_matrix_row2_2.h"
			#include "swizzle/hlsl++_matrix_row2_3.h"
		};
	};

	struct float3x4
	{
		float3x4() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()), vec2(_hlslpp_setzero_ps()) {}

		explicit float3x4(n128 vec0, n128 vec1, n128 vec2) : vec0(vec0), vec1(vec1), vec2(vec2) {}

		explicit float3x4(float f00, float f01, float f02, float f03,
		                  float f10, float f11, float f12, float f13,
		                  float f20, float f21, float f22, float f23) 
			: vec0(_hlslpp_set_ps(f00, f01, f02, f03)), vec1(_hlslpp_set_ps(f10, f11, f12, f13)), vec2(_hlslpp_set_ps(f20, f21, f22, f23)) {}

		explicit float3x4(float f) : vec0(_hlslpp_set1_ps(f)), vec1(_hlslpp_set1_ps(f)), vec2(_hlslpp_set1_ps(f)) {}

		float3x4(const float3x4& m) : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}
		
		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};

		union
		{
			n128 vec2;
			float f32_2[4];
		};
	};

	struct float4x3
	{
		float4x3() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()), vec2(_hlslpp_setzero_ps()) {}

		explicit float4x3(n128 vec0, n128 vec1, n128 vec2) : vec0(vec0), vec1(vec1), vec2(vec2) {}

		explicit float4x3(float f00, float f01, float f02,
		                  float f10, float f11, float f12,
		                  float f20, float f21, float f22,
		                  float f30, float f31, float f32)
			: vec0(_hlslpp_set_ps(f00, f10, f20, f30)), vec1(_hlslpp_set_ps(f01, f11, f21, f31)), vec2(_hlslpp_set_ps(f02, f12, f22, f32)) {}

		explicit float4x3(float f) : vec0(_hlslpp_set1_ps(f)), vec1(_hlslpp_set1_ps(f)), vec2(_hlslpp_set1_ps(f)) {}
		
		float4x3(const float4x3& m) : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};

		union
		{
			n128 vec2;
			float f32_2[4];
		};
	};

	struct float4x4
	{
		float4x4() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()), vec2(_hlslpp_setzero_ps()), vec3(_hlslpp_setzero_ps()) {}

		explicit float4x4(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3) : vec0(vec0), vec1(vec1), vec2(vec2), vec3(vec3) {}


		explicit float4x4(float f00, float f01, float f02, float f03,
		                  float f10, float f11, float f12, float f13,
		                  float f20, float f21, float f22, float f23,
		                  float f30, float f31, float f32, float f33)
			: vec0(_hlslpp_set_ps(f00, f01, f02, f03)), vec1(_hlslpp_set_ps(f10, f11, f12, f13)), vec2(_hlslpp_set_ps(f20, f21, f22, f23)), vec3(_hlslpp_set_ps(f30, f31, f32, f33)) {}

		float4x4(const quaternion& q);

		explicit float4x4(float f) : vec0(_hlslpp_set1_ps(f)), vec1(_hlslpp_set1_ps(f)), vec2(_hlslpp_set1_ps(f)), vec3(_hlslpp_set1_ps(f)) {}
		
		float4x4(const float4x4& m) : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2), vec3(m.vec3) {}

		static const float4x4& identity() { static const float4x4 iden = float4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); return iden; };

		union
		{
			n128 vec0;
			float f32_0[4];
			#include "swizzle/hlsl++_matrix_row0_1.h"
			#include "swizzle/hlsl++_matrix_row0_2.h"
			#include "swizzle/hlsl++_matrix_row0_3.h"
			#include "swizzle/hlsl++_matrix_row0_4.h"
		};

		union
		{
			n128 vec1;
			float f32_1[4];
			#include "swizzle/hlsl++_matrix_row1_1.h"
			#include "swizzle/hlsl++_matrix_row1_2.h"
			#include "swizzle/hlsl++_matrix_row1_3.h"
			#include "swizzle/hlsl++_matrix_row1_4.h"
		};

		union
		{
			n128 vec2;
			float f32_2[4];
			#include "swizzle/hlsl++_matrix_row2_1.h"
			#include "swizzle/hlsl++_matrix_row2_2.h"
			#include "swizzle/hlsl++_matrix_row2_3.h"
			#include "swizzle/hlsl++_matrix_row2_4.h"
		};

		union
		{
			n128 vec3;
			float f32_3[4];
			#include "swizzle/hlsl++_matrix_row3_1.h"
			#include "swizzle/hlsl++_matrix_row3_2.h"
			#include "swizzle/hlsl++_matrix_row3_3.h"
			#include "swizzle/hlsl++_matrix_row3_4.h"
		};
	};

	//-----------------
	// Matrix functions
	//-----------------

	// For matrices, use SFINAE with dummy template parameters to reduce code repetition and enforce conditions to make sure templates aren't ambiguous
	// (e.g. a template for <1, N> and a template for <M, 2>)

	hlslpp_inline n128 _hlslpp_transpose_2x2_ps(n128 m)
	{
		return _hlslpp_perm_xzyw_ps(m);
	}

	hlslpp_inline void _hlslpp_transpose_3x3_ps(const n128& vec0, const n128& vec1, const n128& vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 shuf_tmp_0 = _hlslpp_shuf_xyxy_ps(vec0, vec1);
		n128 shuf_tmp_1 = _hlslpp_shuf_yzyz_ps(vec0, vec1);

		o_vec0 = _hlslpp_shuf_xzxw_ps(shuf_tmp_0, vec2);
		o_vec1 = _hlslpp_shuf_ywyw_ps(shuf_tmp_0, vec2);
		o_vec2 = _hlslpp_shuf_ywzw_ps(shuf_tmp_1, vec2);
	}

	hlslpp_inline void _hlslpp_transpose_4x4_ps(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
	{
		n128 shuf_tmp_0 = _hlslpp_shuf_xyxy_ps(vec0, vec1);
		n128 shuf_tmp_1 = _hlslpp_shuf_zwzw_ps(vec0, vec1);
		n128 shuf_tmp_2 = _hlslpp_shuf_xyxy_ps(vec2, vec3);
		n128 shuf_tmp_3 = _hlslpp_shuf_zwzw_ps(vec2, vec3);

		o_vec0 = _hlslpp_shuf_xzxz_ps(shuf_tmp_0, shuf_tmp_2);
		o_vec1 = _hlslpp_shuf_ywyw_ps(shuf_tmp_0, shuf_tmp_2);
		o_vec2 = _hlslpp_shuf_xzxz_ps(shuf_tmp_1, shuf_tmp_3);
		o_vec3 = _hlslpp_shuf_ywyw_ps(shuf_tmp_1, shuf_tmp_3);
	}

	hlslpp_inline n128 _hlslpp_det_2x2_ps(n128 m)
	{
		// The determinant for a 2x2 matrix is m00 * m11 - m01 * m10
		n128 shuf_1 = _hlslpp_perm_wzxx_ps(m);	// Shuffle w and z into x and y to multiply them together
		n128 prod = _hlslpp_mul_ps(m, shuf_1);		// Now this vector contains wx, zy, _, _
		n128 shuf_2 = _hlslpp_perm_yxxx_ps(prod);	// Shuffle yz into where xw is to subtract them
		n128 result = _hlslpp_sub_ps(prod, shuf_2);	// Determinant is now in the x component
		return result;
	}

	hlslpp_inline n128 _hlslpp_det_3x3_ps(n128 vec0, n128 vec1, n128 vec2)
	{
		// The determinant for a 3x3 matrix can be expressed as dot[ (m00, m01, m02), (m11 * m22 - m12 * m21, m12 * m20 - m10 * m22, m10 * m21 - m11 * m20) ]
		n128 shuf_1 = _hlslpp_perm_yzxw_ps(vec2);
		n128 prod_1 = _hlslpp_mul_ps(vec1, shuf_1);

		n128 shuf_2 = _hlslpp_perm_yzxw_ps(vec1);
		n128 prod_2 = _hlslpp_mul_ps(shuf_2, vec2);

		n128 sub = _hlslpp_sub_ps(prod_1, prod_2);

		n128 result = _hlslpp_dot3_ps(vec0, _hlslpp_perm_yzxw_ps(sub));

		return result;
	}

	inline n128 _hlslpp_det_4x4_ps(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3)
	{
		// Use the Laplace expansion to calculate the determinant in terms of 2x2 determinant multiplies instead of calculating
		// 3x3 determinants and then doing a dot product. https://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf
		n128 tmp_shuf_0 = _hlslpp_perm_xzxy_ps(vec0);
		n128 tmp_shuf_1 = _hlslpp_perm_yxwz_ps(vec1);
		n128 tmp_shuf_2 = _hlslpp_perm_yxwz_ps(vec0);
		n128 tmp_shuf_3 = _hlslpp_perm_xzxy_ps(vec1);

		n128 tmp_shuf_4 = _hlslpp_perm_zyyx_ps(vec2);
		n128 tmp_shuf_5 = _hlslpp_perm_wwzw_ps(vec3);
		n128 tmp_shuf_6 = _hlslpp_perm_wwzw_ps(vec2);
		n128 tmp_shuf_7 = _hlslpp_perm_zyyx_ps(vec3);

		n128 tmp_4_terms = _hlslpp_mul_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(tmp_shuf_0, tmp_shuf_1), _hlslpp_mul_ps(tmp_shuf_2, tmp_shuf_3)), _hlslpp_sub_ps(_hlslpp_mul_ps(tmp_shuf_4, tmp_shuf_5), _hlslpp_mul_ps(tmp_shuf_6, tmp_shuf_7)));

		n128 tmp_shuf_8 = _hlslpp_shuf_wzxx_ps(vec0, vec2);
		n128 tmp_shuf_9 = _hlslpp_shuf_ywzy_ps(vec1, vec3);
		n128 tmp_shuf_10 = _hlslpp_shuf_ywzy_ps(vec0, vec2);
		n128 tmp_shuf_11 = _hlslpp_shuf_wzxx_ps(vec1, vec3);

		n128 tmp_mul_0 = _hlslpp_sub_ps(_hlslpp_mul_ps(tmp_shuf_8, tmp_shuf_9), _hlslpp_mul_ps(tmp_shuf_10, tmp_shuf_11));

		n128 tmp_2_terms = _hlslpp_mul_ps(_hlslpp_perm_xyxy_ps(tmp_mul_0), _hlslpp_perm_zwzw_ps(tmp_mul_0));

		// Add all the results now (terms that subtract have already been inverted)
		n128 tmp_add_0 = _hlslpp_add_ps(_hlslpp_shuf_xzxx_ps(tmp_4_terms, tmp_2_terms), _hlslpp_shuf_ywyy_ps(tmp_4_terms, tmp_2_terms));
		n128 tmp_add_1 = _hlslpp_add_ps(_hlslpp_perm_xxxx_ps(tmp_add_0), _hlslpp_perm_yyyy_ps(tmp_add_0));
		n128 tmp_add_2 = _hlslpp_add_ps(_hlslpp_perm_xxxx_ps(tmp_add_1), _hlslpp_perm_zzzz_ps(tmp_add_0));

		return tmp_add_2;
	}

	inline n128 _hlslpp_inv_2x2_ps(n128 m)
	{
		n128 det = _hlslpp_perm_xxxx_ps(_hlslpp_det_2x2_ps(m));
		n128 shuf = _hlslpp_mul_ps(_hlslpp_perm_wyzx_ps(m), _hlslpp_set_ps(1.0f, -1.0f, -1.0f, 1.0f));
		return _hlslpp_div_ps(shuf, det);
	}

	inline void _hlslpp_inv_3x3_ps(const n128& vec0, const n128& vec1, const n128& vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 tmp_shuf_yzx_0 = _hlslpp_perm_yzxw_ps(vec0);
		n128 tmp_shuf_zxy_0 = _hlslpp_perm_zxyw_ps(vec0);
		n128 tmp_shuf_yzx_1 = _hlslpp_perm_yzxw_ps(vec1);
		n128 tmp_shuf_zxy_1 = _hlslpp_perm_zxyw_ps(vec1);
		n128 tmp_shuf_yzx_2 = _hlslpp_perm_yzxw_ps(vec2);
		n128 tmp_shuf_zxy_2 = _hlslpp_perm_zxyw_ps(vec2);

		// Compute the adjoint matrix directly with 2x2 determinants
		n128 tmp_row_0 = _hlslpp_msub_ps(tmp_shuf_yzx_1, tmp_shuf_zxy_2, _hlslpp_mul_ps(tmp_shuf_zxy_1, tmp_shuf_yzx_2));
		n128 tmp_row_1 = _hlslpp_msub_ps(tmp_shuf_zxy_0, tmp_shuf_yzx_2, _hlslpp_mul_ps(tmp_shuf_yzx_0, tmp_shuf_zxy_2));
		n128 tmp_row_2 = _hlslpp_msub_ps(tmp_shuf_yzx_0, tmp_shuf_zxy_1, _hlslpp_mul_ps(tmp_shuf_zxy_0, tmp_shuf_yzx_1));

		// Transpose the matrix
		n128 tmp_transp_row_0, tmp_transp_row_1, tmp_transp_row_2;
		_hlslpp_transpose_3x3_ps(tmp_row_0, tmp_row_1, tmp_row_2, tmp_transp_row_0, tmp_transp_row_1, tmp_transp_row_2);

		// Compute the determinant and divide all results by it
		n128 det = _hlslpp_perm_xxxx_ps(_hlslpp_det_3x3_ps(vec0, vec1, vec2));
		n128 invDet = _hlslpp_div_ps(f4_1, det);

		o_vec0 = _hlslpp_mul_ps(tmp_transp_row_0, invDet);
		o_vec1 = _hlslpp_mul_ps(tmp_transp_row_1, invDet);
		o_vec2 = _hlslpp_mul_ps(tmp_transp_row_2, invDet);
	}

	inline void _hlslpp_inv_4x4_ps(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
	{
		// Use the Laplace expansion to calculate the adjoint in terms of 2x2 determinants and dot products.
		// Follow https://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf

		// mms means mul mul sub. Here we add the 2x2 determinants we need
		n128 tmp_mms_c5_c4_c3 = _hlslpp_msub_ps(_hlslpp_perm_zyyx_ps(vec2), _hlslpp_perm_wwzx_ps(vec3), _hlslpp_mul_ps(_hlslpp_perm_wwzx_ps(vec2), _hlslpp_perm_zyyx_ps(vec3)));
		n128 tmp_mms_c4_c2_c0 = _hlslpp_msub_ps(_hlslpp_perm_yxxx_ps(vec2), _hlslpp_perm_wwyx_ps(vec3), _hlslpp_mul_ps(_hlslpp_perm_wwyx_ps(vec2), _hlslpp_perm_yxxx_ps(vec3)));
		n128 tmp_mms_c5_c2_c1 = _hlslpp_msub_ps(_hlslpp_perm_zxxx_ps(vec2), _hlslpp_perm_wwzx_ps(vec3), _hlslpp_mul_ps(_hlslpp_perm_wwzx_ps(vec2), _hlslpp_perm_zxxx_ps(vec3)));
		n128 tmp_mms_c3_c1_c0 = _hlslpp_msub_ps(_hlslpp_perm_yxxx_ps(vec2), _hlslpp_perm_zzyx_ps(vec3), _hlslpp_mul_ps(_hlslpp_perm_zzyx_ps(vec2), _hlslpp_perm_yxxx_ps(vec3)));

		n128 tmp_mms_s5_s4_s3 = _hlslpp_msub_ps(_hlslpp_perm_zyyx_ps(vec0), _hlslpp_perm_wwzx_ps(vec1), _hlslpp_mul_ps(_hlslpp_perm_wwzx_ps(vec0), _hlslpp_perm_zyyx_ps(vec1)));
		n128 tmp_mms_s4_s2_s0 = _hlslpp_msub_ps(_hlslpp_perm_yxxx_ps(vec0), _hlslpp_perm_wwyx_ps(vec1), _hlslpp_mul_ps(_hlslpp_perm_wwyx_ps(vec0), _hlslpp_perm_yxxx_ps(vec1)));
		n128 tmp_mms_s5_s2_s1 = _hlslpp_msub_ps(_hlslpp_perm_zxxx_ps(vec0), _hlslpp_perm_wwzx_ps(vec1), _hlslpp_mul_ps(_hlslpp_perm_wwzx_ps(vec0), _hlslpp_perm_zxxx_ps(vec1)));
		n128 tmp_mms_s3_s1_s0 = _hlslpp_msub_ps(_hlslpp_perm_yxxx_ps(vec0), _hlslpp_perm_zzyx_ps(vec1), _hlslpp_mul_ps(_hlslpp_perm_zzyx_ps(vec0), _hlslpp_perm_yxxx_ps(vec1)));

		// Dot product the determinants with the required elements from the rows
		n128 c00 = _hlslpp_dot3_asa_ps(tmp_mms_c5_c4_c3, _hlslpp_perm_yzwx_ps(vec1));
		n128 c01 = _hlslpp_dot3_asa_ps(tmp_mms_c5_c4_c3, _hlslpp_neg_ps(_hlslpp_perm_yzwx_ps(vec0)));
		n128 c02 = _hlslpp_dot3_asa_ps(tmp_mms_s5_s4_s3, _hlslpp_perm_yzwx_ps(vec3));
		n128 c03 = _hlslpp_dot3_asa_ps(tmp_mms_s5_s4_s3, _hlslpp_neg_ps(_hlslpp_perm_yzwx_ps(vec2)));

		n128 c10 = _hlslpp_dot3_asa_ps(tmp_mms_c5_c2_c1, _hlslpp_neg_ps(_hlslpp_perm_xzwx_ps(vec1)));
		n128 c11 = _hlslpp_dot3_asa_ps(tmp_mms_c5_c2_c1, _hlslpp_perm_xzwx_ps(vec0));
		n128 c12 = _hlslpp_dot3_asa_ps(tmp_mms_s5_s2_s1, _hlslpp_neg_ps(_hlslpp_perm_xzwx_ps(vec3)));
		n128 c13 = _hlslpp_dot3_asa_ps(tmp_mms_s5_s2_s1, _hlslpp_perm_xzwx_ps(vec2));

		n128 c20 = _hlslpp_dot3_asa_ps(tmp_mms_c4_c2_c0, _hlslpp_perm_xyww_ps(vec1));
		n128 c21 = _hlslpp_dot3_asa_ps(tmp_mms_c4_c2_c0, _hlslpp_neg_ps(_hlslpp_perm_xyww_ps(vec0)));
		n128 c22 = _hlslpp_dot3_asa_ps(tmp_mms_s4_s2_s0, _hlslpp_perm_xyww_ps(vec3));
		n128 c23 = _hlslpp_dot3_asa_ps(tmp_mms_s4_s2_s0, _hlslpp_neg_ps(_hlslpp_perm_xyww_ps(vec2)));

		n128 c30 = _hlslpp_dot3_asa_ps(tmp_mms_c3_c1_c0, _hlslpp_neg_ps(vec1));
		n128 c31 = _hlslpp_dot3_asa_ps(tmp_mms_c3_c1_c0, vec0);
		n128 c32 = _hlslpp_dot3_asa_ps(tmp_mms_s3_s1_s0, _hlslpp_neg_ps(vec3));
		n128 c33 = _hlslpp_dot3_asa_ps(tmp_mms_s3_s1_s0, vec2);

		// Combine the results
		n128 tmp_row0 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(c00, c02), _hlslpp_shuf_xxxx_ps(c01, c03), HLSLPP_BLEND_MASK(1, 0, 1, 0));
		n128 tmp_row1 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(c10, c12), _hlslpp_shuf_xxxx_ps(c11, c13), HLSLPP_BLEND_MASK(1, 0, 1, 0));
		n128 tmp_row2 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(c20, c22), _hlslpp_shuf_xxxx_ps(c21, c23), HLSLPP_BLEND_MASK(1, 0, 1, 0));
		n128 tmp_row3 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(c30, c32), _hlslpp_shuf_xxxx_ps(c31, c33), HLSLPP_BLEND_MASK(1, 0, 1, 0));

		// Compute the determinant and divide all results by it
		n128 det = _hlslpp_perm_xxxx_ps(_hlslpp_det_4x4_ps(vec0, vec1, vec2, vec3));
		n128 invDet = _hlslpp_div_ps(f4_1, det);

		o_vec0 = _hlslpp_mul_ps(tmp_row0, invDet);
		o_vec1 = _hlslpp_mul_ps(tmp_row1, invDet);
		o_vec2 = _hlslpp_mul_ps(tmp_row2, invDet);
		o_vec3 = _hlslpp_mul_ps(tmp_row3, invDet);
	}

	hlslpp_inline n128 _hlslpp_trace_2x2_ps(const n128 m)
	{
		return _hlslpp_add_ps(_hlslpp_perm_xxxx_ps(m), _hlslpp_perm_wwww_ps(m));
	}

	hlslpp_inline n128 _hlslpp_trace_3x3_ps(const n128 vec0, const n128 vec1, const n128 vec2)
	{
		return _hlslpp_add_ps(_hlslpp_add_ps(_hlslpp_perm_xxxx_ps(vec0), _hlslpp_perm_yyyy_ps(vec1)), _hlslpp_perm_zzzz_ps(vec2));
	}

	hlslpp_inline n128 _hlslpp_trace_4x4_ps(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3)
	{
		n128 sum1 = _hlslpp_add_ps(_hlslpp_perm_xxxx_ps(vec0), _hlslpp_perm_yyyy_ps(vec1));
		n128 sum2 = _hlslpp_add_ps(_hlslpp_perm_zzzz_ps(vec2), _hlslpp_perm_wwww_ps(vec3));
		return _hlslpp_add_ps(sum1, sum2);
	}

	hlslpp_inline n128 _hlslpp_mul_1x2_2x1_ps(n128 m1_vec, n128 m2_vec)
	{
		n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec), m2_vec);
		n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1_vec), _hlslpp_perm_zwxx_ps(m2_vec));
		n128 result = _hlslpp_add_ps(mul1, mul2);
		return result;
	}

	hlslpp_inline n128 _hlslpp_mul_1x2_2xM_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1)
	{
		n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec), m2_vec0);
		n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1_vec), m2_vec1);
		n128 result = _hlslpp_add_ps(mul1, mul2);
		return result;
	}

	hlslpp_inline n128 _hlslpp_mul_1x3_3x2_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1)
	{
		n128 dpx = _hlslpp_dot3_ps(m1_vec, m2_vec0);
		n128 dpy = _hlslpp_dot3_ps(m1_vec, m2_vec1);
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
		return result;
	}

	hlslpp_inline n128 _hlslpp_mul_1x3_3xM_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2)
	{
		n128 mul0 = _hlslpp_mul_ps(m2_vec0, _hlslpp_perm_xxxx_ps(m1_vec));
		n128 mul1 = _hlslpp_madd_ps(m2_vec1, _hlslpp_perm_yyyy_ps(m1_vec), mul0);
		n128 result = _hlslpp_madd_ps(m2_vec2, _hlslpp_perm_zzzz_ps(m1_vec), mul1);
		return result;
	}

	hlslpp_inline n128 _hlslpp_mul_1x4_4x2_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1)
	{
		n128 dpx = _hlslpp_dot4_ps(m1_vec, m2_vec0);
		n128 dpy = _hlslpp_dot4_ps(m1_vec, m2_vec1);
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
		return result;
	}

	hlslpp_inline n128 _hlslpp_mul_1x4_4x3_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2)
	{
		n128 dpx = _hlslpp_dot4_ps(m1_vec, m2_vec0);
		n128 dpy = _hlslpp_dot4_ps(m1_vec, m2_vec1);
		n128 dpz = _hlslpp_dot4_ps(m1_vec, m2_vec2);
		n128 result = _hlslpp_blend_ps(dpy, _hlslpp_shuf_xxxx_ps(dpx, dpz), HLSLPP_BLEND_MASK(0, 1, 0, 1));
		return result;
	}

	hlslpp_inline n128 _hlslpp_mul_1x4_4x4_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, const n128& m2_vec3)
	{
		n128 mul0 = _hlslpp_mul_ps(m2_vec0, _hlslpp_perm_xxxx_ps(m1_vec));
		n128 mul1 = _hlslpp_madd_ps(m2_vec1, _hlslpp_perm_yyyy_ps(m1_vec), mul0);
		n128 mul2 = _hlslpp_madd_ps(m2_vec2, _hlslpp_perm_zzzz_ps(m1_vec), mul1);
		n128 result = _hlslpp_madd_ps(m2_vec3, _hlslpp_perm_wwww_ps(m1_vec), mul2);
		return result;
	}

	hlslpp_inline n128 _hlslpp_mul_2x2_2x1_ps(const n128& m1_vec, const n128& m2_vec)
	{
		n128 dpx = _hlslpp_dot2_ps(m1_vec, m2_vec);
		n128 dpy = _hlslpp_dot2_ps(_hlslpp_perm_zwxx_ps(m1_vec), m2_vec);
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
		return result;
	}

	hlslpp_inline n128 _hlslpp_mul_2x2_2x2_ps(const n128& m1_vec, const n128& m2_vec)
	{
		n128 mul0 = _hlslpp_mul_ps(m1_vec, _hlslpp_perm_xwxw_ps(m2_vec));
		n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_yxwz_ps(m1_vec), _hlslpp_perm_zyzy_ps(m2_vec));
		n128 result = _hlslpp_add_ps(mul0, mul1);
		return result;
	}

	hlslpp_inline void _hlslpp_mul_2x2_2xM_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
	{
		n128 mul0 = _hlslpp_mul_ps(m2_vec0, _hlslpp_perm_xxxx_ps(m1_vec));
		o_vec0 = _hlslpp_madd_ps(m2_vec1, _hlslpp_perm_yyyy_ps(m1_vec), mul0);

		n128 mul1 = _hlslpp_mul_ps(m2_vec0, _hlslpp_perm_zzzz_ps(m1_vec));
		o_vec1 = _hlslpp_madd_ps(m2_vec1, _hlslpp_perm_wwww_ps(m1_vec), mul1);
	}

	hlslpp_inline n128 _hlslpp_mul_Nx2_2x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec)
	{
		n128 mul0 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec));
		n128 result = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec), mul0);
		return result;
	}

	hlslpp_inline void _hlslpp_mul_Nx2_2x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec, n128& o_vec0, n128& o_vec1)
	{
		n128 mul0 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec));
		o_vec0 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_zzzz_ps(m2_vec), mul0);

		n128 mul1 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_yyyy_ps(m2_vec));
		o_vec1 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_wwww_ps(m2_vec), mul1);
	}

	hlslpp_inline void _hlslpp_mul_3x2_2xM_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 mul0 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec1, mul0);

		n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec0);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul1);

		n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec0);
		o_vec2 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec1, mul2);
	}

	hlslpp_inline void _hlslpp_mul_4x2_2x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 mul0 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec0));
		o_vec0 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_xxxx_ps(m2_vec1), mul0);

		n128 mul1 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_yyyy_ps(m2_vec0));
		o_vec1 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec1), mul1);

		n128 mul2 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_zzzz_ps(m2_vec0));
		o_vec2 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_zzzz_ps(m2_vec1), mul2);
	}

	hlslpp_inline void _hlslpp_mul_4x2_2x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
	{
		n128 mul0 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec1, mul0);

		n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec0);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul1);

		n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec0);
		o_vec2 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec1, mul2);

		n128 mul3 = _hlslpp_mul_ps(_hlslpp_perm_wwww_ps(m1_vec0), m2_vec0);
		o_vec3 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec1), m2_vec1, mul3);
	}

	hlslpp_inline n128 _hlslpp_mul_2x3_3x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec)
	{
		n128 dpx = _hlslpp_dot3_ps(m1_vec0, m2_vec);
		n128 dpy = _hlslpp_dot3_ps(m1_vec1, m2_vec);
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
		return result;
	}

	hlslpp_inline n128 _hlslpp_mul_2x3_3x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1)
	{
		n128 dpx = _hlslpp_dot3_ps(m1_vec0, m2_vec0);
		n128 dpy = _hlslpp_dot3_ps(m1_vec0, m2_vec1);
		n128 dpz = _hlslpp_dot3_ps(m1_vec1, m2_vec0);
		n128 dpw = _hlslpp_dot3_ps(m1_vec1, m2_vec1);
		n128 result = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx, dpz), _hlslpp_shuf_xxxx_ps(dpy, dpw), HLSLPP_BLEND_MASK(1, 0, 1, 0));
		return result;
	}

	hlslpp_inline void _hlslpp_mul_2x3_3xM_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1)
	{
		n128 mul0 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		n128 mul1 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec1, mul0);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec2, mul1);

		n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec0);
		n128 mul3 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul2);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec2, mul3);
	}

	hlslpp_inline n128 _hlslpp_mul_2x4_4x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec)
	{
		n128 dpx = _hlslpp_dot4_ps(m1_vec0, m2_vec);
		n128 dpy = _hlslpp_dot4_ps(m1_vec1, m2_vec);
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
		return result;
	}

	hlslpp_inline n128 _hlslpp_mul_2x4_4x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1)
	{
		n128 dpx = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpz = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpw = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 result = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx, dpz), _hlslpp_shuf_xxxx_ps(dpy, dpw), HLSLPP_BLEND_MASK(1, 0, 1, 0));
		return result;
	}

	hlslpp_inline void _hlslpp_mul_2x4_4x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1)
	{
		n128 dpx0 = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpz0 = _hlslpp_dot4_ps(m1_vec0, m2_vec2);
		o_vec0 = _hlslpp_blend_ps(dpy0, _hlslpp_shuf_xxxx_ps(dpx0, dpz0), HLSLPP_BLEND_MASK(0, 1, 0, 1));

		n128 dpx1 = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpy1 = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1_vec1, m2_vec2);
		o_vec1 = _hlslpp_blend_ps(dpy1, _hlslpp_shuf_xxxx_ps(dpx1, dpz1), HLSLPP_BLEND_MASK(0, 1, 0, 1));
	}

	hlslpp_inline void _hlslpp_mul_2x4_4x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, const n128& m2_vec3, n128& o_vec0, n128& o_vec1)
	{
		// First row
		n128 mul0x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		n128 mad0y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec1, mul0x);
		n128 mad0z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec2, mad0y);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec0), m2_vec3, mad0z);

		// Second row
		n128 mul1x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec0);
		n128 mad1y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul1x);
		n128 mad1z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec2, mad1y);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec1), m2_vec3, mad1z);
	}

	hlslpp_inline n128 _hlslpp_mul_3x3_3x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec)
	{
		n128 dpx = _hlslpp_dot3_ps(m1_vec0, m2_vec);
		n128 dpy = _hlslpp_dot3_ps(m1_vec1, m2_vec);
		n128 dpz = _hlslpp_dot3_ps(m1_vec2, m2_vec);
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_shuf_xxxx_ps(dpy, dpz), HLSLPP_BLEND_MASK(1, 0, 0, 1));
		return result;
	}

	hlslpp_inline void _hlslpp_mul_3x3_3x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
	{
		n128 dpx0 = _hlslpp_dot3_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot3_ps(m1_vec1, m2_vec0);
		n128 dpz0 = _hlslpp_dot3_ps(m1_vec2, m2_vec0);
		o_vec0 = _hlslpp_blend_ps(dpx0, _hlslpp_shuf_xxxx_ps(dpy0, dpz0), HLSLPP_BLEND_MASK(1, 0, 0, 1));

		n128 dpx1 = _hlslpp_dot3_ps(m1_vec0, m2_vec1);
		n128 dpy1 = _hlslpp_dot3_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot3_ps(m1_vec2, m2_vec1);
		o_vec1 = _hlslpp_blend_ps(dpx1, _hlslpp_shuf_xxxx_ps(dpy1, dpz1), HLSLPP_BLEND_MASK(1, 0, 0, 1));
	}

	hlslpp_inline void _hlslpp_mul_3x3_3x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		// First row
		n128 mul1x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec0));
		n128 mad1y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec0), mul1x);
		o_vec0 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec0), mad1y);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec1));
		n128 mad2y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec1), mul2x);
		o_vec1 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec1), mad2y);

		// Third row
		n128 mul3x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec2));
		n128 mad3y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec2), mul3x);
		o_vec2 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec2), mad3y);
	}

	hlslpp_inline void _hlslpp_mul_3x3_3x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		// First row
		n128 mul1x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		n128 mad1y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec1, mul1x);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec2, mad1y);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec0);
		n128 mad2y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul2x);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec2, mad2y);

		// Third row
		n128 mul3x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec2), m2_vec0);
		n128 mad3y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec2), m2_vec1, mul3x);
		o_vec2 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec2), m2_vec2, mad3y);
	}

	hlslpp_inline n128 _hlslpp_mul_3x4_4x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec)
	{
		n128 dpx = _hlslpp_dot4_ps(m1_vec0, m2_vec);
		n128 dpy = _hlslpp_dot4_ps(m1_vec1, m2_vec);
		n128 dpz = _hlslpp_dot4_ps(m1_vec2, m2_vec);
		n128 result = _hlslpp_blend_ps(dpy, _hlslpp_shuf_xxxx_ps(dpx, dpz), HLSLPP_BLEND_MASK(0, 1, 0, 1));
		return result;
	}

	hlslpp_inline void _hlslpp_mul_3x4_4x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
	{
		n128 dpx0 = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpz0 = _hlslpp_dot4_ps(m1_vec2, m2_vec0);
		o_vec0 = _hlslpp_blend_ps(dpy0, _hlslpp_shuf_xxxx_ps(dpx0, dpz0), HLSLPP_BLEND_MASK(0, 1, 0, 1));

		n128 dpx1 = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpy1 = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1_vec2, m2_vec1);
		o_vec1 = _hlslpp_blend_ps(dpy1, _hlslpp_shuf_xxxx_ps(dpx1, dpz1), HLSLPP_BLEND_MASK(0, 1, 0, 1));
	}

	hlslpp_inline void _hlslpp_mul_3x4_4x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 dpx0 = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpz0 = _hlslpp_dot4_ps(m1_vec0, m2_vec2);
		o_vec0 = _hlslpp_blend_ps(dpy0, _hlslpp_shuf_xxxx_ps(dpx0, dpz0), HLSLPP_BLEND_MASK(0, 1, 0, 1));

		n128 dpx1 = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpy1 = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1_vec1, m2_vec2);
		o_vec1 = _hlslpp_blend_ps(dpy1, _hlslpp_shuf_xxxx_ps(dpx1, dpz1), HLSLPP_BLEND_MASK(0, 1, 0, 1));

		n128 dpx2 = _hlslpp_dot4_ps(m1_vec2, m2_vec0);
		n128 dpy2 = _hlslpp_dot4_ps(m1_vec2, m2_vec1);
		n128 dpz2 = _hlslpp_dot4_ps(m1_vec2, m2_vec2);
		o_vec2 = _hlslpp_blend_ps(dpy2, _hlslpp_shuf_xxxx_ps(dpx2, dpz2), HLSLPP_BLEND_MASK(0, 1, 0, 1));
	}

	hlslpp_inline void _hlslpp_mul_3x4_4x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, const n128& m2_vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		// First row
		n128 mul1x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		n128 mad1y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec1, mul1x);
		n128 mad1z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec2, mad1y);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec0), m2_vec3, mad1z);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec0);
		n128 mad2y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul2x);
		n128 mad2z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec2, mad2y);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec1), m2_vec3, mad2z);

		// Third row
		n128 mul3x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec2), m2_vec0);
		n128 mad3y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec2), m2_vec1, mul3x);
		n128 mad3z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec2), m2_vec2, mad3y);
		o_vec2 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec2), m2_vec3, mad3z);
	}

	hlslpp_inline n128 _hlslpp_mul_4x3_3x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec)
	{
		n128 mul1x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec));
		n128 mad1y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec), mul1x);
		n128 result = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec), mad1y);
		return result;
	}

	hlslpp_inline void _hlslpp_mul_4x3_3x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
	{
		// First row
		n128 mul0x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec0));
		n128 mad0y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec0), mul0x);
		o_vec0 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec0), mad0y);

		// Second row
		n128 mul1x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec1));
		n128 mad1y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec1), mul1x);
		o_vec1 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec1), mad1y);
	}

	hlslpp_inline void _hlslpp_mul_4x3_3x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		// First row
		n128 mul0x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec0));
		n128 mad0y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_xxxx_ps(m2_vec1), mul0x);
		o_vec0 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_xxxx_ps(m2_vec2), mad0y);

		// Second row
		n128 mul1x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_yyyy_ps(m2_vec0));
		n128 mad1y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec1), mul1x);
		o_vec1 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_yyyy_ps(m2_vec2), mad1y);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_zzzz_ps(m2_vec0));
		n128 mad2y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_zzzz_ps(m2_vec1), mul2x);
		o_vec2 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec2), mad2y);
	}

	hlslpp_inline void _hlslpp_mul_4x3_3x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
	{
		// First row
		n128 mul0x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		n128 mad0y = _hlslpp_madd_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec1, mul0x);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_xxxx_ps(m1_vec2), m2_vec2, mad0y);

		// Second row
		n128 mul1x = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec0);
		n128 mad1y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul1x);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec2), m2_vec2, mad1y);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec0);
		n128 mad2y = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec1, mul2x);
		o_vec2 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec2), m2_vec2, mad2y);

		// Second row
		n128 mul3x = _hlslpp_mul_ps(_hlslpp_perm_wwww_ps(m1_vec0), m2_vec0);
		n128 mad3y = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec1), m2_vec1, mul3x);
		o_vec3 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec2), m2_vec2, mad3y);
	}

	hlslpp_inline n128 _hlslpp_mul_4x4_4x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m1_vec3, const n128& m2_vec)
	{
		n128 dpx = _hlslpp_dot4_ps(m1_vec0, m2_vec);
		n128 dpy = _hlslpp_dot4_ps(m1_vec1, m2_vec);
		n128 dpz = _hlslpp_dot4_ps(m1_vec2, m2_vec);
		n128 dpw = _hlslpp_dot4_ps(m1_vec3, m2_vec);

		n128 result = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx, dpz), _hlslpp_shuf_xxxx_ps(dpy, dpw), HLSLPP_BLEND_MASK(1, 0, 1, 0));
		return result;
	}

	hlslpp_inline void _hlslpp_mul_4x4_4x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m1_vec3, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
	{
		n128 dpx0 = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpz0 = _hlslpp_dot4_ps(m1_vec2, m2_vec0);
		n128 dpw0 = _hlslpp_dot4_ps(m1_vec3, m2_vec0);

		o_vec0 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx0, dpz0), _hlslpp_shuf_xxxx_ps(dpy0, dpw0), HLSLPP_BLEND_MASK(1, 0, 1, 0));

		n128 dpx1 = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpy1 = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1_vec2, m2_vec1);
		n128 dpw1 = _hlslpp_dot4_ps(m1_vec3, m2_vec1);

		o_vec1 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx1, dpz1), _hlslpp_shuf_xxxx_ps(dpy1, dpw1), HLSLPP_BLEND_MASK(1, 0, 1, 0));
	}

	hlslpp_inline void _hlslpp_mul_4x4_4x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m1_vec3, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 dpx0 = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpz0 = _hlslpp_dot4_ps(m1_vec2, m2_vec0);
		n128 dpw0 = _hlslpp_dot4_ps(m1_vec3, m2_vec0);

		o_vec0 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx0, dpz0), _hlslpp_shuf_xxxx_ps(dpy0, dpw0), HLSLPP_BLEND_MASK(1, 0, 1, 0));

		n128 dpx1 = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpy1 = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1_vec2, m2_vec1);
		n128 dpw1 = _hlslpp_dot4_ps(m1_vec3, m2_vec1);

		o_vec1 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx1, dpz1), _hlslpp_shuf_xxxx_ps(dpy1, dpw1), HLSLPP_BLEND_MASK(1, 0, 1, 0));

		n128 dpx2 = _hlslpp_dot4_ps(m1_vec0, m2_vec2);
		n128 dpy2 = _hlslpp_dot4_ps(m1_vec1, m2_vec2);
		n128 dpz2 = _hlslpp_dot4_ps(m1_vec2, m2_vec2);
		n128 dpw2 = _hlslpp_dot4_ps(m1_vec3, m2_vec2);

		o_vec2 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx2, dpz2), _hlslpp_shuf_xxxx_ps(dpy2, dpw2), HLSLPP_BLEND_MASK(1, 0, 1, 0));
	}

	hlslpp_inline void _hlslpp_mul_4x4_4x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m1_vec3, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, const n128& m2_vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
	{
		// First row
		n128 mul1x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec0));
		n128 mad1y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec0), mul1x);
		n128 mad1z = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec0), mad1y);
		o_vec0 = _hlslpp_madd_ps(m1_vec3, _hlslpp_perm_wwww_ps(m2_vec0), mad1z);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec1));
		n128 mad2y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec1), mul2x);
		n128 mad2z = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec1), mad2y);
		o_vec1 = _hlslpp_madd_ps(m1_vec3, _hlslpp_perm_wwww_ps(m2_vec1), mad2z);

		// Third row
		n128 mul3x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec2));
		n128 mad3y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec2), mul3x);
		n128 mad3z = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec2), mad3y);
		o_vec2 = _hlslpp_madd_ps(m1_vec3, _hlslpp_perm_wwww_ps(m2_vec2), mad3z);

		// Fourth row
		n128 mul4x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec3));
		n128 mad4y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec3), mul4x);
		n128 mad4z = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec3), mad4y);
		o_vec3 = _hlslpp_madd_ps(m1_vec3, _hlslpp_perm_wwww_ps(m2_vec3), mad4z);
	}

	hlslpp_inline float1x1 mul(const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec)); }

	hlslpp_inline float1x2 mul(const float1x1& m1, const float1x2& m2) { return float1x2(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec)); }

	hlslpp_inline float1x3 mul(const float1x1& m1, const float1x3& m2) { return float1x3(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec)); }

	hlslpp_inline float1x4 mul(const float1x1& m1, const float1x4& m2) { return float1x4(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec)); }

	hlslpp_inline float2x1 mul(const float2x1& m1, const float1x1& m2) { return float2x1(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec))); }

	hlslpp_inline float3x1 mul(const float3x1& m1, const float1x1& m2) { return float3x1(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec))); }

	hlslpp_inline float4x1 mul(const float4x1& m1, const float1x1& m2) { return float4x1(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec))); }

	hlslpp_inline float2x2 mul(const float2x1& m1, const float1x2& m2) { return float2x2(_hlslpp_mul_ps(_hlslpp_perm_xxyy_ps(m1.vec), _hlslpp_perm_xyxy_ps(m2.vec))); }

	hlslpp_inline float2x3 mul(const float2x1& m1, const float1x3& m2) { return float2x3(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1.vec), m2.vec)); }

	hlslpp_inline float2x4 mul(const float2x1& m1, const float1x4& m2) { return float2x4(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1.vec), m2.vec)); }

	hlslpp_inline float3x2 mul(const float3x1& m1, const float1x2& m2) { return float3x2(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec)), _hlslpp_mul_ps(m1.vec, _hlslpp_perm_yyyy_ps(m2.vec))); }

	hlslpp_inline float4x2 mul(const float4x1& m1, const float1x2& m2) { return float4x2(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec)), _hlslpp_mul_ps(m1.vec, _hlslpp_perm_yyyy_ps(m2.vec))); }

	hlslpp_inline float3x3 mul(const float3x1& m1, const float1x3& m2)
	{
		return float3x3(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec)), _hlslpp_mul_ps(m1.vec, _hlslpp_perm_yyyy_ps(m2.vec)), _hlslpp_mul_ps(m1.vec, _hlslpp_perm_zzzz_ps(m2.vec)));
	}

	hlslpp_inline float4x3 mul(const float4x1& m1, const float1x3& m2)
	{
		return float4x3(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec)), _hlslpp_mul_ps(m1.vec, _hlslpp_perm_yyyy_ps(m2.vec)), _hlslpp_mul_ps(m1.vec, _hlslpp_perm_zzzz_ps(m2.vec)));
	}

	hlslpp_inline float3x4 mul(const float3x1& m1, const float1x4& m2)
	{
		return float3x4(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1.vec), m2.vec));
	}

	hlslpp_inline float4x4 mul(const float4x1& m1, const float1x4& m2)
	{
		return float4x4(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_wwww_ps(m1.vec), m2.vec));
	}

	hlslpp_inline float1x1 mul(const float1x2& m1, const float2x1& m2) { return float1x1(_hlslpp_dot2_ps(m1.vec, m2.vec)); }

	hlslpp_inline float1x2 mul(const float1x2& m1, const float2x2& m2) { return float1x2(_hlslpp_mul_1x2_2x1_ps(m1.vec, m2.vec)); }

	hlslpp_inline float1x3 mul(const float1x2& m1, const float2x3& m2) { return float1x3(_hlslpp_mul_1x2_2xM_ps(m1.vec, m2.vec0, m2.vec1)); }

	hlslpp_inline float1x4 mul(const float1x2& m1, const float2x4& m2) { return float1x4(_hlslpp_mul_1x2_2xM_ps(m1.vec, m2.vec0, m2.vec1)); }

	hlslpp_inline float1x1 mul(const float1x3& m1, const float3x1& m2) { return float1x1(_hlslpp_dot3_ps(m1.vec, m2.vec)); }

	hlslpp_inline float1x2 mul(const float1x3& m1, const float3x2& m2) { return float1x2(_hlslpp_mul_1x3_3x2_ps(m1.vec, m2.vec0, m2.vec1)); }

	hlslpp_inline float1x3 mul(const float1x3& m1, const float3x3& m2) { return float1x3(_hlslpp_mul_1x3_3xM_ps(m1.vec, m2.vec0, m2.vec1, m2.vec2)); }

	hlslpp_inline float1x4 mul(const float1x3& m1, const float3x4& m2) { return float1x4(_hlslpp_mul_1x3_3xM_ps(m1.vec, m2.vec0, m2.vec1, m2.vec2)); }

	hlslpp_inline float1x1 mul(const float1x4& m1, const float4x1& m2) { return float1x1(_hlslpp_dot4_ps(m1.vec, m2.vec)); }

	hlslpp_inline float1x2 mul(const float1x4& m1, const float4x2& m2) { return float1x2(_hlslpp_mul_1x4_4x2_ps(m1.vec, m2.vec0, m2.vec1)); }

	hlslpp_inline float1x3 mul(const float1x4& m1, const float4x3& m2) { return float1x3(_hlslpp_mul_1x4_4x3_ps(m1.vec, m2.vec0, m2.vec1, m2.vec2)); }

	hlslpp_inline float1x4 mul(const float1x4& m1, const float4x4& m2) { return float1x4(_hlslpp_mul_1x4_4x4_ps(m1.vec, m2.vec0, m2.vec1, m2.vec2, m2.vec3)); }

	hlslpp_inline float2x1 mul(const float2x2& m1, const float2x1& m2) { return float2x1(_hlslpp_mul_2x2_2x1_ps(m1.vec, m2.vec)); }

	hlslpp_inline float2x2 mul(const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_mul_2x2_2x2_ps(m1.vec, m2.vec)); }

	hlslpp_inline float2x3 mul(const float2x2& m1, const float2x3& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x2_2xM_ps(m1.vec, m2.vec0, m2.vec1, vec0, vec1);
		return float2x3(vec0, vec1);
	}

	hlslpp_inline float2x4 mul(const float2x2& m1, const float2x4& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x2_2xM_ps(m1.vec, m2.vec0, m2.vec1, vec0, vec1);
		return float2x4(vec0, vec1);
	}

	hlslpp_inline float3x1 mul(const float3x2& m1, const float2x1& m2) { return float3x1(_hlslpp_mul_Nx2_2x1_ps(m1.vec0, m1.vec1, m2.vec)); }

	hlslpp_inline float4x1 mul(const float4x2& m1, const float2x1& m2) { return float4x1(_hlslpp_mul_Nx2_2x1_ps(m1.vec0, m1.vec1, m2.vec)); }

	hlslpp_inline float3x2 mul(const float3x2& m1, const float2x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_Nx2_2x2_ps(m1.vec0, m1.vec1, m2.vec, vec0, vec1);
		return float3x2(vec0, vec1);
	}

	hlslpp_inline float4x2 mul(const float4x2& m1, const float2x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_Nx2_2x2_ps(m1.vec0, m1.vec1, m2.vec, vec0, vec1);
		return float4x2(vec0, vec1);
	}

	hlslpp_inline float3x3 mul(const float3x2& m1, const float2x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x2_2xM_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float3x4 mul(const float3x2& m1, const float2x4& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x2_2xM_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, vec0, vec1, vec2);
		return float3x4(vec0, vec1, vec2);
	}


	hlslpp_inline float4x3 mul(const float4x2& m1, const float2x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_4x2_2x3_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, vec0, vec1, vec2);
		return float4x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 mul(const float4x2& m1, const float2x4& m2)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_mul_4x2_2x4_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	hlslpp_inline float2x1 mul(const float2x3& m1, const float3x1& m2)
	{
		return float2x1(_hlslpp_mul_2x3_3x1_ps(m1.vec0, m1.vec1, m2.vec));
	}

	hlslpp_inline float2x2 mul(const float2x3& m1, const float3x2& m2)
	{
		return float2x2(_hlslpp_mul_2x3_3x2_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1));
	}

	hlslpp_inline float2x3 mul(const float2x3& m1, const float3x3& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x3_3xM_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, m2.vec2, vec0, vec1);
		return float2x3(vec0, vec1);
	}

	hlslpp_inline float2x4 mul(const float2x3& m1, const float3x4& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x3_3xM_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, m2.vec2, vec0, vec1);
		return float2x4(vec0, vec1);
	}

	hlslpp_inline float2x1 mul(const float2x4& m1, const float4x1& m2)
	{
		return float2x1(_hlslpp_mul_2x4_4x1_ps(m1.vec0, m1.vec1, m2.vec));
	}

	hlslpp_inline float2x2 mul(const float2x4& m1, const float4x2& m2)
	{
		return float2x2(_hlslpp_mul_2x4_4x2_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1));
	}

	hlslpp_inline float2x3 mul(const float2x4& m1, const float4x3& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x4_4x3_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, m2.vec2, vec0, vec1);
		return float2x3(vec0, vec1);
	}

	hlslpp_inline float2x4 mul(const float2x4& m1, const float4x4& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x4_4x4_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, m2.vec2, m2.vec3, vec0, vec1);
		return float2x4(vec0, vec1);
	}

	hlslpp_inline float3x1 mul(const float3x3& m1, const float3x1& m2)
	{
		return float3x1(_hlslpp_mul_3x3_3x1_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec));
	}

	hlslpp_inline float3x2 mul(const float3x3& m1, const float3x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_3x3_3x2_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, vec0, vec1);
		return float3x2(vec0, vec1);
	}

	hlslpp_inline float3x3 mul(const float3x3& m1, const float3x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x3_3x3_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, m2.vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float3x4 mul(const float3x3& m1, const float3x4& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x3_3x4_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, m2.vec2, vec0, vec1, vec2);
		return float3x4(vec0, vec1, vec2);
	}

	hlslpp_inline float3x1 mul(const float3x4& m1, const float4x1& m2)
	{

		return float3x1(_hlslpp_mul_3x4_4x1_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec));
	}

	hlslpp_inline float3x2 mul(const float3x4& m1, const float4x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_3x4_4x2_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, vec0, vec1);
		return float3x2(vec0, vec1);
	}

	hlslpp_inline float3x3 mul(const float3x4& m1, const float4x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x4_4x3_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, m2.vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float3x4 mul(const float3x4& m1, const float4x4& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x4_4x4_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, m2.vec2, m2.vec3, vec0, vec1, vec2);
		return float3x4(vec0, vec1, vec2);
	}

	hlslpp_inline float4x1 mul(const float4x3& m1, const float3x1& m2)
	{
		return float4x1(_hlslpp_mul_4x3_3x1_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec));
	}

	hlslpp_inline float4x2 mul(const float4x3& m1, const float3x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_4x3_3x2_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, vec0, vec1);
		return float4x2(vec0, vec1);
	}

	hlslpp_inline float4x3 mul(const float4x3& m1, const float3x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_4x3_3x3_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, m2.vec2, vec0, vec1, vec2);
		return float4x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 mul(const float4x3& m1, const float3x4& m2)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_mul_4x3_3x4_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, m2.vec2, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	hlslpp_inline float4x1 mul(const float4x4& m1, const float4x1& m2)
	{
		return float4x1(_hlslpp_mul_4x4_4x1_ps(m1.vec0, m1.vec1, m1.vec2, m1.vec3, m2.vec));
	}

	hlslpp_inline float4x2 mul(const float4x4& m1, const float4x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_4x4_4x2_ps(m1.vec0, m1.vec1, m1.vec2, m1.vec3, m2.vec0, m2.vec1, vec0, vec1);
		return float4x2(vec0, vec1);
	}

	hlslpp_inline float4x3 mul(const float4x4& m1, const float4x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_4x4_4x3_ps(m1.vec0, m1.vec1, m1.vec2, m1.vec3, m2.vec0, m2.vec1, m2.vec2, vec0, vec1, vec2);
		return float4x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 mul(const float4x4& m1, const float4x4& m2)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_mul_4x4_4x4_ps(m1.vec0, m1.vec1, m1.vec2, m1.vec3, m2.vec0, m2.vec1, m2.vec2, m2.vec3, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	float1x1 operator + (const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float1x2 operator + (const float1x2& m1, const float1x2& m2) { return float1x2(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float1x3 operator + (const float1x3& m1, const float1x3& m2) { return float1x3(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float1x4 operator + (const float1x4& m1, const float1x4& m2) { return float1x4(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float2x1 operator + (const float2x1& m1, const float2x1& m2) { return float2x1(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float3x1 operator + (const float3x1& m1, const float3x1& m2) { return float3x1(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float4x1 operator + (const float4x1& m1, const float4x1& m2) { return float4x1(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float2x2 operator + (const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float2x3 operator + (const float2x3& m1, const float2x3& m2) { return float2x3(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1)); }
	float3x2 operator + (const float3x2& m1, const float3x2& m2) { return float3x2(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1)); }
	float2x4 operator + (const float2x4& m1, const float2x4& m2) { return float2x4(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1)); }
	float4x2 operator + (const float4x2& m1, const float4x2& m2) { return float4x2(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1)); }
	float3x3 operator + (const float3x3& m1, const float3x3& m2) { return float3x3(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1), _hlslpp_add_ps(m1.vec2, m2.vec2)); }
	float3x4 operator + (const float3x4& m1, const float3x4& m2) { return float3x4(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1), _hlslpp_add_ps(m1.vec2, m2.vec2)); }
	float4x3 operator + (const float4x3& m1, const float4x3& m2) { return float4x3(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1), _hlslpp_add_ps(m1.vec2, m2.vec2)); }
	float4x4 operator + (const float4x4& m1, const float4x4& m2) { return float4x4(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1), _hlslpp_add_ps(m1.vec2, m2.vec2), _hlslpp_add_ps(m1.vec3, m2.vec3)); }

	float1x1 operator += (float1x1& m1, const float1x1& m2) { m1 = m1 + m2; return m1; }
	float1x2 operator += (float1x2& m1, const float1x2& m2) { m1 = m1 + m2; return m1; }
	float1x3 operator += (float1x3& m1, const float1x3& m2) { m1 = m1 + m2; return m1; }
	float1x4 operator += (float1x4& m1, const float1x4& m2) { m1 = m1 + m2; return m1; }
	float2x1 operator += (float2x1& m1, const float2x1& m2) { m1 = m1 + m2; return m1; }
	float3x1 operator += (float3x1& m1, const float3x1& m2) { m1 = m1 + m2; return m1; }
	float4x1 operator += (float4x1& m1, const float4x1& m2) { m1 = m1 + m2; return m1; }
	float2x2 operator += (float2x2& m1, const float2x2& m2) { m1 = m1 + m2; return m1; }
	float2x3 operator += (float2x3& m1, const float2x3& m2) { m1 = m1 + m2; return m1; }
	float2x4 operator += (float2x4& m1, const float2x4& m2) { m1 = m1 + m2; return m1; }
	float3x2 operator += (float3x2& m1, const float3x2& m2) { m1 = m1 + m2; return m1; }
	float4x2 operator += (float4x2& m1, const float4x2& m2) { m1 = m1 + m2; return m1; }
	float3x3 operator += (float3x3& m1, const float3x3& m2) { m1 = m1 + m2; return m1; }
	float3x4 operator += (float3x4& m1, const float3x4& m2) { m1 = m1 + m2; return m1; }
	float4x3 operator += (float4x3& m1, const float4x3& m2) { m1 = m1 + m2; return m1; }
	float4x4 operator += (float4x4& m1, const float4x4& m2) { m1 = m1 + m2; return m1; }

	float1x1 operator - (const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float1x2 operator - (const float1x2& m1, const float1x2& m2) { return float1x2(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float1x3 operator - (const float1x3& m1, const float1x3& m2) { return float1x3(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float1x4 operator - (const float1x4& m1, const float1x4& m2) { return float1x4(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float2x1 operator - (const float2x1& m1, const float2x1& m2) { return float2x1(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float3x1 operator - (const float3x1& m1, const float3x1& m2) { return float3x1(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float4x1 operator - (const float4x1& m1, const float4x1& m2) { return float4x1(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float2x2 operator - (const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float2x3 operator - (const float2x3& m1, const float2x3& m2) { return float2x3(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1)); }
	float3x2 operator - (const float3x2& m1, const float3x2& m2) { return float3x2(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1)); }
	float2x4 operator - (const float2x4& m1, const float2x4& m2) { return float2x4(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1)); }
	float4x2 operator - (const float4x2& m1, const float4x2& m2) { return float4x2(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1)); }
	float3x3 operator - (const float3x3& m1, const float3x3& m2) { return float3x3(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1), _hlslpp_sub_ps(m1.vec2, m2.vec2)); }
	float3x4 operator - (const float3x4& m1, const float3x4& m2) { return float3x4(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1), _hlslpp_sub_ps(m1.vec2, m2.vec2)); }
	float4x3 operator - (const float4x3& m1, const float4x3& m2) { return float4x3(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1), _hlslpp_sub_ps(m1.vec2, m2.vec2)); }
	float4x4 operator - (const float4x4& m1, const float4x4& m2) { return float4x4(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1), _hlslpp_sub_ps(m1.vec2, m2.vec2), _hlslpp_sub_ps(m1.vec3, m2.vec3)); }

	float1x1 operator -= (float1x1& m1, const float1x1& m2) { m1 = m1 - m2; return m1; }
	float1x2 operator -= (float1x2& m1, const float1x2& m2) { m1 = m1 - m2; return m1; }
	float1x3 operator -= (float1x3& m1, const float1x3& m2) { m1 = m1 - m2; return m1; }
	float1x4 operator -= (float1x4& m1, const float1x4& m2) { m1 = m1 - m2; return m1; }
	float2x1 operator -= (float2x1& m1, const float2x1& m2) { m1 = m1 - m2; return m1; }
	float3x1 operator -= (float3x1& m1, const float3x1& m2) { m1 = m1 - m2; return m1; }
	float4x1 operator -= (float4x1& m1, const float4x1& m2) { m1 = m1 - m2; return m1; }
	float2x2 operator -= (float2x2& m1, const float2x2& m2) { m1 = m1 - m2; return m1; }
	float2x3 operator -= (float2x3& m1, const float2x3& m2) { m1 = m1 - m2; return m1; }
	float2x4 operator -= (float2x4& m1, const float2x4& m2) { m1 = m1 - m2; return m1; }
	float3x2 operator -= (float3x2& m1, const float3x2& m2) { m1 = m1 - m2; return m1; }
	float4x2 operator -= (float4x2& m1, const float4x2& m2) { m1 = m1 - m2; return m1; }
	float3x3 operator -= (float3x3& m1, const float3x3& m2) { m1 = m1 - m2; return m1; }
	float3x4 operator -= (float3x4& m1, const float3x4& m2) { m1 = m1 - m2; return m1; }
	float4x3 operator -= (float4x3& m1, const float4x3& m2) { m1 = m1 - m2; return m1; }
	float4x4 operator -= (float4x4& m1, const float4x4& m2) { m1 = m1 - m2; return m1; }

	float1x1 operator * (const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float1x2 operator * (const float1x2& m1, const float1x2& m2) { return float1x2(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float1x3 operator * (const float1x3& m1, const float1x3& m2) { return float1x3(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float1x4 operator * (const float1x4& m1, const float1x4& m2) { return float1x4(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float2x1 operator * (const float2x1& m1, const float2x1& m2) { return float2x1(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float3x1 operator * (const float3x1& m1, const float3x1& m2) { return float3x1(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float4x1 operator * (const float4x1& m1, const float4x1& m2) { return float4x1(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float2x2 operator * (const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float2x3 operator * (const float2x3& m1, const float2x3& m2) { return float2x3(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1)); }
	float3x2 operator * (const float3x2& m1, const float3x2& m2) { return float3x2(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1)); }
	float2x4 operator * (const float2x4& m1, const float2x4& m2) { return float2x4(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1)); }
	float4x2 operator * (const float4x2& m1, const float4x2& m2) { return float4x2(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1)); }
	float3x3 operator * (const float3x3& m1, const float3x3& m2) { return float3x3(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1), _hlslpp_mul_ps(m1.vec2, m2.vec2)); }
	float3x4 operator * (const float3x4& m1, const float3x4& m2) { return float3x4(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1), _hlslpp_mul_ps(m1.vec2, m2.vec2)); }
	float4x3 operator * (const float4x3& m1, const float4x3& m2) { return float4x3(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1), _hlslpp_mul_ps(m1.vec2, m2.vec2)); }
	float4x4 operator * (const float4x4& m1, const float4x4& m2) { return float4x4(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1), _hlslpp_mul_ps(m1.vec2, m2.vec2), _hlslpp_mul_ps(m1.vec3, m2.vec3)); }

	float1x1 operator *= (float1x1& m1, const float1x1& m2) { m1 = m1 * m2; return m1; }
	float1x2 operator *= (float1x2& m1, const float1x2& m2) { m1 = m1 * m2; return m1; }
	float1x3 operator *= (float1x3& m1, const float1x3& m2) { m1 = m1 * m2; return m1; }
	float1x4 operator *= (float1x4& m1, const float1x4& m2) { m1 = m1 * m2; return m1; }
	float2x1 operator *= (float2x1& m1, const float2x1& m2) { m1 = m1 * m2; return m1; }
	float3x1 operator *= (float3x1& m1, const float3x1& m2) { m1 = m1 * m2; return m1; }
	float4x1 operator *= (float4x1& m1, const float4x1& m2) { m1 = m1 * m2; return m1; }
	float2x2 operator *= (float2x2& m1, const float2x2& m2) { m1 = m1 * m2; return m1; }
	float2x3 operator *= (float2x3& m1, const float2x3& m2) { m1 = m1 * m2; return m1; }
	float2x4 operator *= (float2x4& m1, const float2x4& m2) { m1 = m1 * m2; return m1; }
	float3x2 operator *= (float3x2& m1, const float3x2& m2) { m1 = m1 * m2; return m1; }
	float4x2 operator *= (float4x2& m1, const float4x2& m2) { m1 = m1 * m2; return m1; }
	float3x3 operator *= (float3x3& m1, const float3x3& m2) { m1 = m1 * m2; return m1; }
	float3x4 operator *= (float3x4& m1, const float3x4& m2) { m1 = m1 * m2; return m1; }
	float4x3 operator *= (float4x3& m1, const float4x3& m2) { m1 = m1 * m2; return m1; }
	float4x4 operator *= (float4x4& m1, const float4x4& m2) { m1 = m1 * m2; return m1; }

	float1x1 operator / (const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float1x2 operator / (const float1x2& m1, const float1x2& m2) { return float1x2(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float1x3 operator / (const float1x3& m1, const float1x3& m2) { return float1x3(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float1x4 operator / (const float1x4& m1, const float1x4& m2) { return float1x4(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float2x1 operator / (const float2x1& m1, const float2x1& m2) { return float2x1(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float3x1 operator / (const float3x1& m1, const float3x1& m2) { return float3x1(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float4x1 operator / (const float4x1& m1, const float4x1& m2) { return float4x1(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float2x2 operator / (const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float2x3 operator / (const float2x3& m1, const float2x3& m2) { return float2x3(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1)); }
	float3x2 operator / (const float3x2& m1, const float3x2& m2) { return float3x2(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1)); }
	float2x4 operator / (const float2x4& m1, const float2x4& m2) { return float2x4(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1)); }
	float4x2 operator / (const float4x2& m1, const float4x2& m2) { return float4x2(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1)); }
	float3x3 operator / (const float3x3& m1, const float3x3& m2) { return float3x3(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1), _hlslpp_div_ps(m1.vec2, m2.vec2)); }
	float3x4 operator / (const float3x4& m1, const float3x4& m2) { return float3x4(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1), _hlslpp_div_ps(m1.vec2, m2.vec2)); }
	float4x3 operator / (const float4x3& m1, const float4x3& m2) { return float4x3(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1), _hlslpp_div_ps(m1.vec2, m2.vec2)); }
	float4x4 operator / (const float4x4& m1, const float4x4& m2) { return float4x4(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1), _hlslpp_div_ps(m1.vec2, m2.vec2), _hlslpp_div_ps(m1.vec3, m2.vec3)); }

	float1x1 operator /= (float1x1& m1, const float1x1& m2) { m1 = m1 / m2; return m1; }
	float1x2 operator /= (float1x2& m1, const float1x2& m2) { m1 = m1 / m2; return m1; }
	float1x3 operator /= (float1x3& m1, const float1x3& m2) { m1 = m1 / m2; return m1; }
	float1x4 operator /= (float1x4& m1, const float1x4& m2) { m1 = m1 / m2; return m1; }
	float2x1 operator /= (float2x1& m1, const float2x1& m2) { m1 = m1 / m2; return m1; }
	float3x1 operator /= (float3x1& m1, const float3x1& m2) { m1 = m1 / m2; return m1; }
	float4x1 operator /= (float4x1& m1, const float4x1& m2) { m1 = m1 / m2; return m1; }
	float2x2 operator /= (float2x2& m1, const float2x2& m2) { m1 = m1 / m2; return m1; }
	float2x3 operator /= (float2x3& m1, const float2x3& m2) { m1 = m1 / m2; return m1; }
	float2x4 operator /= (float2x4& m1, const float2x4& m2) { m1 = m1 / m2; return m1; }
	float3x2 operator /= (float3x2& m1, const float3x2& m2) { m1 = m1 / m2; return m1; }
	float4x2 operator /= (float4x2& m1, const float4x2& m2) { m1 = m1 / m2; return m1; }
	float3x3 operator /= (float3x3& m1, const float3x3& m2) { m1 = m1 / m2; return m1; }
	float3x4 operator /= (float3x4& m1, const float3x4& m2) { m1 = m1 / m2; return m1; }
	float4x3 operator /= (float4x3& m1, const float4x3& m2) { m1 = m1 / m2; return m1; }
	float4x4 operator /= (float4x4& m1, const float4x4& m2) { m1 = m1 / m2; return m1; }

	// Scalar operators

	float1x1 operator + (const float1x1& m, const float1& f) { return float1x1(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x2 operator + (const float1x2& m, const float1& f) { return float1x2(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x3 operator + (const float1x3& m, const float1& f) { return float1x3(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x4 operator + (const float1x4& m, const float1& f) { return float1x4(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x1 operator + (const float2x1& m, const float1& f) { return float2x1(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float3x1 operator + (const float3x1& m, const float1& f) { return float3x1(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float4x1 operator + (const float4x1& m, const float1& f) { return float4x1(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x2 operator + (const float2x2& m, const float1& f) { return float2x2(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x3 operator + (const float2x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x3(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm)); }
	float3x2 operator + (const float3x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x2(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm)); }
	float2x4 operator + (const float2x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x4(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm)); }
	float4x2 operator + (const float4x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x2(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm)); }
	float3x3 operator + (const float3x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x3(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm), _hlslpp_add_ps(m.vec2, perm)); }
	float3x4 operator + (const float3x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x4(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm), _hlslpp_add_ps(m.vec2, perm)); }
	float4x3 operator + (const float4x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x3(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm), _hlslpp_add_ps(m.vec2, perm)); }
	float4x4 operator + (const float4x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x4(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm), _hlslpp_add_ps(m.vec2, perm), _hlslpp_add_ps(m.vec3, perm)); }

	float1x1 operator - (const float1x1& m, const float1& f) { return float1x1(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x2 operator - (const float1x2& m, const float1& f) { return float1x2(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x3 operator - (const float1x3& m, const float1& f) { return float1x3(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x4 operator - (const float1x4& m, const float1& f) { return float1x4(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x1 operator - (const float2x1& m, const float1& f) { return float2x1(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float3x1 operator - (const float3x1& m, const float1& f) { return float3x1(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float4x1 operator - (const float4x1& m, const float1& f) { return float4x1(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x2 operator - (const float2x2& m, const float1& f) { return float2x2(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x3 operator - (const float2x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x3(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm)); }
	float3x2 operator - (const float3x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x2(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm)); }
	float2x4 operator - (const float2x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x4(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm)); }
	float4x2 operator - (const float4x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x2(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm)); }
	float3x3 operator - (const float3x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x3(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm), _hlslpp_sub_ps(m.vec2, perm)); }
	float3x4 operator - (const float3x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x4(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm), _hlslpp_sub_ps(m.vec2, perm)); }
	float4x3 operator - (const float4x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x3(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm), _hlslpp_sub_ps(m.vec2, perm)); }
	float4x4 operator - (const float4x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x4(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm), _hlslpp_sub_ps(m.vec2, perm), _hlslpp_sub_ps(m.vec3, perm)); }

	float1x1 operator * (const float1x1& m, const float1& f) { return float1x1(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x2 operator * (const float1x2& m, const float1& f) { return float1x2(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x3 operator * (const float1x3& m, const float1& f) { return float1x3(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x4 operator * (const float1x4& m, const float1& f) { return float1x4(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x1 operator * (const float2x1& m, const float1& f) { return float2x1(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float3x1 operator * (const float3x1& m, const float1& f) { return float3x1(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float4x1 operator * (const float4x1& m, const float1& f) { return float4x1(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x2 operator * (const float2x2& m, const float1& f) { return float2x2(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }	
	float2x3 operator * (const float2x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x3(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm)); }
	float3x2 operator * (const float3x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x2(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm)); }
	float2x4 operator * (const float2x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x4(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm)); }
	float4x2 operator * (const float4x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x2(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm)); }
	float3x3 operator * (const float3x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x3(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm), _hlslpp_mul_ps(m.vec2, perm)); }
	float3x4 operator * (const float3x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x4(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm), _hlslpp_mul_ps(m.vec2, perm)); }
	float4x3 operator * (const float4x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x3(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm), _hlslpp_mul_ps(m.vec2, perm)); }
	float4x4 operator * (const float4x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x4(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm), _hlslpp_mul_ps(m.vec2, perm), _hlslpp_mul_ps(m.vec3, perm)); }

	float1x1 operator / (const float1x1& m, const float1& f) { return float1x1(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x2 operator / (const float1x2& m, const float1& f) { return float1x2(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x3 operator / (const float1x3& m, const float1& f) { return float1x3(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x4 operator / (const float1x4& m, const float1& f) { return float1x4(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x1 operator / (const float2x1& m, const float1& f) { return float2x1(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float3x1 operator / (const float3x1& m, const float1& f) { return float3x1(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float4x1 operator / (const float4x1& m, const float1& f) { return float4x1(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x2 operator / (const float2x2& m, const float1& f) { return float2x2(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x3 operator / (const float2x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x3(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm)); }
	float3x2 operator / (const float3x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x2(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm)); }
	float2x4 operator / (const float2x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x4(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm)); }
	float4x2 operator / (const float4x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x2(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm)); }
	float3x3 operator / (const float3x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x3(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm), _hlslpp_div_ps(m.vec2, perm)); }
	float3x4 operator / (const float3x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x4(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm), _hlslpp_div_ps(m.vec2, perm)); }
	float4x3 operator / (const float4x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x3(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm), _hlslpp_div_ps(m.vec2, perm)); }
	float4x4 operator / (const float4x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x4(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm), _hlslpp_div_ps(m.vec2, perm), _hlslpp_div_ps(m.vec3, perm)); }

	hlslpp_inline float1 trace(const float2x2& m)
	{
		return float1(_hlslpp_trace_2x2_ps(m.vec));
	}

	hlslpp_inline float1 trace(const float3x3& m)
	{
		return float1(_hlslpp_trace_3x3_ps(m.vec0, m.vec1, m.vec2));
	}

	hlslpp_inline float1 trace(const float4x4& m)
	{
		return float1(_hlslpp_trace_4x4_ps(m.vec0, m.vec1, m.vec2, m.vec3));
	}

	hlslpp_inline float2x2 transpose(const float2x2& m)
	{
		return float2x2(_hlslpp_transpose_2x2_ps(m.vec));
	}

	hlslpp_inline float3x3 transpose(const float3x3& m)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_transpose_3x3_ps(m.vec0, m.vec1, m.vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 transpose(const float4x4& m)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_transpose_4x4_ps(m.vec0, m.vec1, m.vec2, m.vec3, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	// These transpose functions just copy the data because the 1xM, Nx1, 2xM, Nx2, 3xM and Nx3 matrices are always laid out as rows
	// even if they're meant to represent columns.

	float1x1 transpose(const float1x1& m) { return float1x1(m.vec); }

	float1x2 transpose(const float2x1& m) { return float1x2(m.vec); }
	float2x1 transpose(const float1x2& m) { return float2x1(m.vec); }

	float1x3 transpose(const float3x1& m) { return float1x3(m.vec); }
	float3x1 transpose(const float1x3& m) { return float3x1(m.vec); }

	float1x4 transpose(const float4x1& m) { return float1x4(m.vec); }
	float4x1 transpose(const float1x4& m) { return float4x1(m.vec); }

	float2x3 transpose(const float3x2& m) { return float2x3(m.vec0, m.vec1); }
	float3x2 transpose(const float2x3& m) { return float3x2(m.vec0, m.vec1); }

	float2x4 transpose(const float4x2& m) { return float2x4(m.vec0, m.vec1); }
	float4x2 transpose(const float2x4& m) { return float4x2(m.vec0, m.vec1); }

	float3x4 transpose(const float4x3& m) { return float3x4(m.vec0, m.vec1, m.vec2); }
	float4x3 transpose(const float3x4& m) { return float4x3(m.vec0, m.vec1, m.vec2); }

	hlslpp_inline float1 determinant(const float2x2& m)
	{
		return float1(_hlslpp_det_2x2_ps(m.vec));
	}

	hlslpp_inline float1 determinant(const float3x3& m)
	{
		return float1(_hlslpp_det_3x3_ps(m.vec0, m.vec1, m.vec2));
	}

	hlslpp_inline float1 determinant(const float4x4& m)
	{
		return float1(_hlslpp_det_4x4_ps(m.vec0, m.vec1, m.vec2, m.vec3));
	}

	hlslpp_inline float2x2 inverse(const float2x2& m)
	{
		return float2x2(_hlslpp_inv_2x2_ps(m.vec));
	}

	inline float3x3 inverse(const float3x3& m)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_inv_3x3_ps(m.vec0, m.vec1, m.vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	inline float4x4 inverse(const float4x4& m)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_inv_4x4_ps(m.vec0, m.vec1, m.vec2, m.vec3, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	//--------
	// Storing
	//--------

	hlslpp_inline void store(const float1& v, float* f)
	{
		_hlslpp_store1_ps(f + 0, v.vec);
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

	hlslpp_inline void store(const float3x3& m, float* f)
	{
		_hlslpp_store3x3_ps(f, m.vec0, m.vec1, m.vec2);
	}

	hlslpp_inline void store(const float4x4& m, float* f)
	{
		_hlslpp_store4x4_ps(f, m.vec0, m.vec1, m.vec2, m.vec3);
	}

	//-----------
	// Quaternion
	//-----------

	struct quaternion
	{
		quaternion() {}
		explicit quaternion(n128 vec) : vec(vec) {}

		template<typename T1, typename T2, typename T3, typename T4, enable_if_number_4<T1, T2, T3, T4> = nullptr>
		quaternion(T1 f1, T2 f2, T3 f3, T4 f4) : vec(_hlslpp_set_ps(float(f1), float(f2), float(f3), float(f4))) {}

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
	hlslpp_inline float4		all(const quaternion& q) { return float4(_hlslpp_all1_ps(q.vec)); }
	hlslpp_inline float4		any(const quaternion& q) { return float4(_hlslpp_any1_ps(q.vec)); }
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
	hlslpp_inline quaternion	lerp(const quaternion& q1, const quaternion& q2, const float1& a) { return quaternion(_hlslpp_lrp_ps(q1.vec, q2.vec, _hlslpp_perm_xxxx_ps(a.vec))); }

	hlslpp_inline quaternion	slerp(const quaternion& q1, const quaternion& q2, const float1& a) { return quaternion(_hlslpp_quat_slerp_ps(q1.vec, q2.vec, _hlslpp_perm_xxxx_ps(a.vec))); }

	//hlslpp_inline quaternion log(const quaternion& q) { return quaternion(_hlslpp_log_ps(q._vec)); }
	hlslpp_inline quaternion	min(const quaternion& q1, const quaternion& q2) { return quaternion(_hlslpp_min_ps(q1.vec, q2.vec)); }
	hlslpp_inline quaternion	max(const quaternion& q1, const quaternion& q2) { return quaternion(_hlslpp_max_ps(q1.vec, q2.vec)); }
	hlslpp_inline float3		mul(const quaternion& q, const float3& v) { return float3(_hlslpp_quat_mul_vec_ps(q.vec, v.vec)); }
	hlslpp_inline quaternion	normalize(const quaternion& q) { return quaternion(_hlslpp_div_ps(q.vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(q.vec, q.vec))))); }
	hlslpp_inline quaternion	saturate(const quaternion& q) { return quaternion(_hlslpp_sat_ps(q.vec)); }
	hlslpp_inline quaternion	sign(const quaternion& q) { return quaternion(_hlslpp_sign_ps(q.vec)); }

	hlslpp_inline float3x3::float3x3(const quaternion& q)
	{
		_hlslpp_quat_to_3x3_ps(q.vec, vec0, vec1, vec2);
	}

	hlslpp_inline float4x4::float4x4(const quaternion& q)
	{
		_hlslpp_quat_to_4x4_ps(q.vec, vec0, vec1, vec2, vec3);
	}
}