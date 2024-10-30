#pragma once

#include "hlsl++/config.h"

hlslpp_module_export namespace hlslpp
{
	//----------------
	// Float Constants
	//----------------

	const n128 f4_0           = _hlslpp_set1_ps(0.0f);
	const n128 f4_1           = _hlslpp_set1_ps(1.0f);
	const n128 f4_minus1      = _hlslpp_set1_ps(-1.0f);
	const n128 f4_05          = _hlslpp_set1_ps(0.5f);
	const n128 f4_minus05     = _hlslpp_set1_ps(-0.5f);
	const n128 f4_2           = _hlslpp_set1_ps(2.0f);
	const n128 f4_minus2      = _hlslpp_set1_ps(-2.0f);
	const n128 f4_3           = _hlslpp_set1_ps(3.0f);
	const n128 f4_10          = _hlslpp_set1_ps(10.0f);
	const n128 f4_e           = _hlslpp_set1_ps(2.718281828f);

	const n128 f4_pi          = _hlslpp_set1_ps(3.14159265f);  // pi
	const n128 f4_minusPi     = _hlslpp_set1_ps(-3.14159265f); // -pi
	const n128 f4_invPi       = _hlslpp_set1_ps(0.31830988f);  // 1 / pi

	const n128 f4_2pi         = _hlslpp_set1_ps(6.28318530f);  //  2 * pi
	const n128 f4_minus2pi    = _hlslpp_set1_ps(-6.28318530f); // -2 * pi
	const n128 f4_inv2pi      = _hlslpp_set1_ps(0.15915494f);  // 1 / (2 * pi)

	const n128 f4_pi2         = _hlslpp_set1_ps(1.57079632f);  //  pi / 2
	const n128 f4_minusPi2    = _hlslpp_set1_ps(-1.57079632f); // -pi / 2
	const n128 f4_invPi2      = _hlslpp_set1_ps(0.63661977f);  // 2 / pi

	const n128 f4_3pi2        = _hlslpp_set1_ps(4.71238898f);  //  3 * pi / 2
	const n128 f4_minus3pi2   = _hlslpp_set1_ps(-4.71238898f); // -3 * pi / 2

	const n128 f4_pi4         = _hlslpp_set1_ps(0.78539816f);  // pi / 4
	const n128 f4_minusPi4    = _hlslpp_set1_ps(-0.78539816f); // -pi / 4

	const n128 f4_NaN         = _hlslpp_set1_ps(nanMask._f32);      // Quiet NaN
	const n128 f4_inf         = _hlslpp_set1_ps(infMask._f32);      // Infinity
	const n128 f4_minusinf    = _hlslpp_set1_ps(minusinfMask._f32); // -Infinity
	const n128 f4_fff         = _hlslpp_set1_ps(fffMask._f32);      // 0xffffffff

	const n128 f4_rad2deg     = _hlslpp_set1_ps(180.0f / 3.14159265f);
	const n128 f4_deg2rad     = _hlslpp_set1_ps(3.14159265f / 180.f);

	const n128 f4negativeMask = _hlslpp_set1_ps(negMask._f32);
	const n128 f4absMask      = _hlslpp_set1_ps(absMask._f32);

	//------------------
	// Integer Constants
	//------------------

	const n128i i4_0           = _hlslpp_set1_epi32(0);
	const n128i i4_1           = _hlslpp_set1_epi32(1);

	const n128i i4negativeMask = _hlslpp_set1_epi32(negMask._i32);
	const n128i i4fffMask      = _hlslpp_set1_epi32(fffMask._i32);
	const n128i i4negMask      = _hlslpp_set1_epi32(negMask._i32);

	const n128u u4_0           = _hlslpp_set1_epu32(0);
	const n128u u4_1           = _hlslpp_set1_epu32(1);

#if defined(HLSLPP_SIMD_REGISTER_256)

	const n256 f8_0           = _hlslpp256_set1_ps(0.0f);
	const n256 f8_1           = _hlslpp256_set1_ps(1.0f);
	const n256 f8minusOne     = _hlslpp256_set1_ps(-1.0f);
	const n256 f8_05          = _hlslpp256_set1_ps(0.5f);
	const n256 f8_minus05     = _hlslpp256_set1_ps(-0.5f);
	const n256 f8_2           = _hlslpp256_set1_ps(2.0f);
	const n256 f8_minus2      = _hlslpp256_set1_ps(-2.0f);
	const n256 f8_3           = _hlslpp256_set1_ps(3.0f);
	const n256 f8_10          = _hlslpp256_set1_ps(10.0f);
	const n256 f8_e           = _hlslpp256_set1_ps(2.718281828f);

	const n256 f8_pi          = _hlslpp256_set1_ps(3.14159265f);  // pi
	const n256 f8_minusPi     = _hlslpp256_set1_ps(-3.14159265f); // -pi
	const n256 f8_invPi       = _hlslpp256_set1_ps(0.31830988f);  // 1 / pi

	const n256 f8_2pi         = _hlslpp256_set1_ps(6.28318530f);  //  2 * pi
	const n256 f8_minus2pi    = _hlslpp256_set1_ps(-6.28318530f); // -2 * pi
	const n256 f8_inv2pi      = _hlslpp256_set1_ps(0.15915494f);  // 1 / (2 * pi)

	const n256 f8_pi2         = _hlslpp256_set1_ps(1.57079632f);  //  pi / 2
	const n256 f8_minusPi2    = _hlslpp256_set1_ps(-1.57079632f); // -pi / 2
	const n256 f8_invPi2      = _hlslpp256_set1_ps(0.63661977f);  // 2 / pi

	const n256 f8_3pi2        = _hlslpp256_set1_ps(4.71238898f);  //  3 * pi / 2
	const n256 f8_minus3pi2   = _hlslpp256_set1_ps(-4.71238898f); // -3 * pi / 2

	const n256 f8_pi4         = _hlslpp256_set1_ps(0.78539816f);  // pi / 4
	const n256 f8_minusPi4    = _hlslpp256_set1_ps(-0.78539816f); // -pi / 4

	const n256 f8_NaN         = _hlslpp256_set1_ps(nanMask._f32);      // Quiet NaN
	const n256 f8_inf         = _hlslpp256_set1_ps(infMask._f32);      // Infinity
	const n256 f8_minusinf    = _hlslpp256_set1_ps(minusinfMask._f32); // -Infinity
	const n256 f8_fff         = _hlslpp256_set1_ps(fffMask._f32);      // 0xffffffff

	const n256 f8_rad2deg     = _hlslpp256_set1_ps(180.0f / 3.14159265f);
	const n256 f8_deg2rad     = _hlslpp256_set1_ps(3.14159265f / 180.f);

	const n256 f8negativeMask = _hlslpp256_set1_ps(negMask._f32);
	const n256 f8absMask      = _hlslpp256_set1_ps(absMask._f32);

#endif

	static const int IdentityMask  = ((3 << 6) | (2 << 4) | (1 << 2) | 0);
	static const int IdentityMask2 = (1 << 1) | 0;

	const uint32_t MaskX = 0;
	const uint32_t MaskY = 1;
	const uint32_t MaskZ = 2;
	const uint32_t MaskW = 3;

	const uint32_t MaskA = 4;
	const uint32_t MaskB = 5;
	const uint32_t MaskC = 6;
	const uint32_t MaskD = 7;

	// Auxiliary templates for disambiguation with standard header functions

	#define hlslpp_enable_if_return(T, R) typename hlslpp::enable_if<hlslpp::is_arithmetic<T>::value, R>::type
	
	#define hlslpp_enable_if_number(T) typename hlslpp::enable_if<hlslpp::is_arithmetic<T>::value, void*>::type = nullptr
	
	#define hlslpp_enable_if_number_2(T1, T2) \
			typename hlslpp::enable_if<hlslpp::is_arithmetic2<T1, T2>::value, void*>::type = nullptr
	
	#define hlslpp_enable_if_number_3(T1, T2, T3) \
			typename hlslpp::enable_if<hlslpp::is_arithmetic3<T1, T2, T3>::value, void*>::type = nullptr
	
	#define hlslpp_enable_if_number_4(T1, T2, T3, T4) \
			typename hlslpp::enable_if<hlslpp::is_arithmetic4<T1, T2, T3, T4>::value, void*>::type = nullptr

	#define hlslpp_enable_if_number_8(T1, T2, T3, T4, T5, T6, T7, T8) \
			typename hlslpp::enable_if<hlslpp::is_arithmetic8<T1, T2, T3, T4, T5, T6, T7, T8>::value, void*>::type = nullptr

	// Helper intrinsics

	#define _hlslpp_perm_xxxx_ps(x)		_hlslpp_perm_ps((x), MaskX, MaskX, MaskX, MaskX)
	#define _hlslpp_perm_xxyx_ps(x)		_hlslpp_perm_ps((x), MaskX, MaskX, MaskY, MaskX)
	#define _hlslpp_perm_xxyz_ps(x)		_hlslpp_perm_ps((x), MaskX, MaskX, MaskY, MaskZ)
	#define _hlslpp_perm_xyxy_ps(x)		_hlslpp_perm_ps((x), MaskX, MaskY, MaskX, MaskY)
	#define _hlslpp_perm_xyww_ps(x)		_hlslpp_perm_ps((x), MaskX, MaskY, MaskW, MaskW)
	#define _hlslpp_perm_xzyw_ps(x)		_hlslpp_perm_ps((x), MaskX, MaskZ, MaskY, MaskW)
	#define _hlslpp_perm_xzxy_ps(x)		_hlslpp_perm_ps((x), MaskX, MaskZ, MaskX, MaskY)
	#define _hlslpp_perm_xzwx_ps(x)		_hlslpp_perm_ps((x), MaskX, MaskZ, MaskW, MaskX)
	#define _hlslpp_perm_xwxw_ps(x)		_hlslpp_perm_ps((x), MaskX, MaskW, MaskX, MaskW)
	#define _hlslpp_perm_yxxx_ps(x)		_hlslpp_perm_ps((x), MaskY, MaskX, MaskX, MaskX)
	#define _hlslpp_perm_yxwx_ps(x)		_hlslpp_perm_ps((x), MaskY, MaskX, MaskW, MaskX)
	#define _hlslpp_perm_yxwz_ps(x)		_hlslpp_perm_ps((x), MaskY, MaskX, MaskW, MaskZ)
	#define _hlslpp_perm_yyyy_ps(x)		_hlslpp_perm_ps((x), MaskY, MaskY, MaskY, MaskY)
	#define _hlslpp_perm_yzxx_ps(x)		_hlslpp_perm_ps((x), MaskY, MaskZ, MaskX, MaskX)
	#define _hlslpp_perm_yzxw_ps(x)		_hlslpp_perm_ps((x), MaskY, MaskZ, MaskX, MaskW)
	#define _hlslpp_perm_yzwx_ps(x)		_hlslpp_perm_ps((x), MaskY, MaskZ, MaskW, MaskX)
	#define _hlslpp_perm_ywxz_ps(x)		_hlslpp_perm_ps((x), MaskY, MaskW, MaskX, MaskZ)
	#define _hlslpp_perm_zxxx_ps(x)		_hlslpp_perm_ps((x), MaskZ, MaskX, MaskX, MaskX)
	#define _hlslpp_perm_zxyw_ps(x)		_hlslpp_perm_ps((x), MaskZ, MaskX, MaskY, MaskW)
	#define _hlslpp_perm_zyyx_ps(x)		_hlslpp_perm_ps((x), MaskZ, MaskY, MaskY, MaskX)
	#define _hlslpp_perm_zyzy_ps(x)		_hlslpp_perm_ps((x), MaskZ, MaskY, MaskZ, MaskY)
	#define _hlslpp_perm_zzyx_ps(x)		_hlslpp_perm_ps((x), MaskZ, MaskZ, MaskY, MaskX)
	#define _hlslpp_perm_zzzz_ps(x)		_hlslpp_perm_ps((x), MaskZ, MaskZ, MaskZ, MaskZ)
	#define _hlslpp_perm_zwzw_ps(x)		_hlslpp_perm_ps((x), MaskZ, MaskW, MaskZ, MaskW)
	#define _hlslpp_perm_wyzx_ps(x)		_hlslpp_perm_ps((x), MaskW, MaskY, MaskZ, MaskX)
	#define _hlslpp_perm_wzxx_ps(x)		_hlslpp_perm_ps((x), MaskW, MaskZ, MaskX, MaskX)
	#define _hlslpp_perm_wwyx_ps(x)		_hlslpp_perm_ps((x), MaskW, MaskW, MaskY, MaskX)
	#define _hlslpp_perm_wwzx_ps(x)		_hlslpp_perm_ps((x), MaskW, MaskW, MaskZ, MaskX)
	#define _hlslpp_perm_wwzw_ps(x)		_hlslpp_perm_ps((x), MaskW, MaskW, MaskZ, MaskW)
	#define _hlslpp_perm_wwww_ps(x)		_hlslpp_perm_ps((x), MaskW, MaskW, MaskW, MaskW)
	#define _hlslpp_perm_xxyy_ps(x)		_hlslpp_perm_ps((x), MaskX, MaskX, MaskY, MaskY)
	#define _hlslpp_perm_zwxx_ps(x)		_hlslpp_perm_ps((x), MaskZ, MaskW, MaskX, MaskX)
	#define _hlslpp_perm_xyxx_ps(x)		_hlslpp_perm_ps((x), MaskX, MaskY, MaskX, MaskX)
	#define _hlslpp_perm_zxwy_ps(x)		_hlslpp_perm_ps((x), MaskZ, MaskX, MaskW, MaskY)
	#define _hlslpp_perm_yzzy_ps(x)		_hlslpp_perm_ps((x), MaskY, MaskZ, MaskZ, MaskY)
	#define _hlslpp_perm_zxyz_ps(x)		_hlslpp_perm_ps((x), MaskZ, MaskX, MaskY, MaskZ)
	#define _hlslpp_perm_yzxz_ps(x)		_hlslpp_perm_ps((x), MaskY, MaskZ, MaskX, MaskZ)
	#define _hlslpp_perm_zyzx_ps(x)		_hlslpp_perm_ps((x), MaskZ, MaskY, MaskZ, MaskX)
	#define _hlslpp_perm_wwwx_ps(x)		_hlslpp_perm_ps((x), MaskW, MaskW, MaskW, MaskX)
	#define _hlslpp_perm_wxyz_ps(x)		_hlslpp_perm_ps((x), MaskW, MaskX, MaskY, MaskZ)
	
	#define _hlslpp_shuf_xxxx_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskX, MaskX, MaskX, MaskX)
	#define _hlslpp_shuf_xxxy_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskX, MaskX, MaskX, MaskY)
	#define _hlslpp_shuf_xyxx_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskX, MaskY, MaskX, MaskX)
	#define _hlslpp_shuf_xyxy_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskX, MaskY, MaskX, MaskY)
	#define _hlslpp_shuf_yzyz_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskY, MaskZ, MaskY, MaskZ)
	#define _hlslpp_shuf_xzxw_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskX, MaskZ, MaskX, MaskW)
	#define _hlslpp_shuf_ywyw_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskY, MaskW, MaskY, MaskW)
	#define _hlslpp_shuf_ywzw_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskY, MaskW, MaskZ, MaskW)
	#define _hlslpp_shuf_zwzw_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskZ, MaskW, MaskZ, MaskW)
	#define _hlslpp_shuf_xzxz_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskX, MaskZ, MaskX, MaskZ)
	#define _hlslpp_shuf_wzxx_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskW, MaskZ, MaskX, MaskX)
	#define _hlslpp_shuf_ywzy_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskY, MaskW, MaskZ, MaskY)
	#define _hlslpp_shuf_xzxx_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskX, MaskZ, MaskX, MaskX)
	#define _hlslpp_shuf_ywyy_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskY, MaskW, MaskY, MaskY)
	#define _hlslpp_shuf_yyyy_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskY, MaskY, MaskY, MaskY)
	#define _hlslpp_shuf_zyzy_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskZ, MaskY, MaskZ, MaskY)
	#define _hlslpp_shuf_xwxw_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskX, MaskW, MaskX, MaskW)
	#define _hlslpp_shuf_wxwx_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskW, MaskX, MaskW, MaskX)
	#define _hlslpp_shuf_zxxz_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskZ, MaskX, MaskX, MaskZ)
	#define _hlslpp_shuf_wyyw_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskW, MaskY, MaskY, MaskW)
	#define _hlslpp_shuf_xzzx_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskX, MaskZ, MaskZ, MaskX)
	#define _hlslpp_shuf_ywwy_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskY, MaskW, MaskW, MaskY)
	#define _hlslpp_shuf_yxwz_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskY, MaskX, MaskW, MaskZ)
	#define _hlslpp_shuf_zzxx_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskZ, MaskZ, MaskX, MaskX)
	#define _hlslpp_shuf_zzzz_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskZ, MaskZ, MaskZ, MaskZ)
	#define _hlslpp_shuf_zwxx_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskZ, MaskW, MaskX, MaskX)
	#define _hlslpp_shuf_wwww_ps(x, y)	_hlslpp_shuffle_ps((x), (y), MaskW, MaskW, MaskW, MaskW)
	
	#define _hlslpp256_perm_xxxx_xxxx_ps(x) _hlslpp256_perm_ps(x, MaskX, MaskX, MaskX, MaskX, MaskX, MaskX, MaskX, MaskX)
	#define _hlslpp256_perm_xxxx_yyyy_ps(x) _hlslpp256_perm_ps(x, MaskX, MaskX, MaskX, MaskX, MaskY, MaskY, MaskY, MaskY)
	#define _hlslpp256_perm_xxxx_aaaa_ps(x) _hlslpp256_perm_ps(x, MaskX, MaskX, MaskX, MaskX, MaskA, MaskA, MaskA, MaskA)
	#define _hlslpp256_perm_xxxx_bbbb_ps(x) _hlslpp256_perm_ps(x, MaskX, MaskX, MaskX, MaskX, MaskB, MaskB, MaskB, MaskB)
	#define _hlslpp256_perm_xzxy_badc_ps(x) _hlslpp256_perm_ps(x, MaskX, MaskZ, MaskX, MaskY, MaskB, MaskA, MaskD, MaskC)
	#define _hlslpp256_perm_xzzx_acca_ps(x) _hlslpp256_perm_ps(x, MaskX, MaskZ, MaskZ, MaskX, MaskA, MaskC, MaskC, MaskA)
	#define _hlslpp256_perm_xzzx_bddb_ps(x) _hlslpp256_perm_ps(x, MaskX, MaskZ, MaskZ, MaskX, MaskB, MaskD, MaskD, MaskB)
	#define _hlslpp256_perm_yxwz_acab_ps(x) _hlslpp256_perm_ps(x, MaskY, MaskX, MaskW, MaskZ, MaskA, MaskC, MaskA, MaskB)
	#define _hlslpp256_perm_yyyy_bbbb_ps(x) _hlslpp256_perm_ps(x, MaskY, MaskY, MaskY, MaskY, MaskB, MaskB, MaskB, MaskB)
	#define _hlslpp256_perm_yyyy_aaaa_ps(x) _hlslpp256_perm_ps(x, MaskY, MaskY, MaskY, MaskY, MaskA, MaskA, MaskA, MaskA)
	#define _hlslpp256_perm_ywwy_bddb_ps(x) _hlslpp256_perm_ps(x, MaskY, MaskW, MaskW, MaskY, MaskB, MaskD, MaskD, MaskB)
	#define _hlslpp256_perm_ywwy_acca_ps(x) _hlslpp256_perm_ps(x, MaskY, MaskW, MaskW, MaskY, MaskA, MaskC, MaskC, MaskA)
	#define _hlslpp256_perm_ywwz_cbaa_ps(x) _hlslpp256_perm_ps(x, MaskY, MaskW, MaskW, MaskZ, MaskC, MaskB, MaskA, MaskA)
	#define _hlslpp256_perm_zyyx_ddcd_ps(x) _hlslpp256_perm_ps(x, MaskZ, MaskY, MaskY, MaskX, MaskD, MaskD, MaskC, MaskD)
	#define _hlslpp256_perm_zzzz_wwww_ps(x) _hlslpp256_perm_ps(x, MaskZ, MaskZ, MaskZ, MaskZ, MaskW, MaskW, MaskW, MaskW)
	#define _hlslpp256_perm_zzzz_cccc_ps(x) _hlslpp256_perm_ps(x, MaskZ, MaskZ, MaskZ, MaskZ, MaskC, MaskC, MaskC, MaskC)
	#define _hlslpp256_perm_zzzz_dddd_ps(x) _hlslpp256_perm_ps(x, MaskZ, MaskZ, MaskZ, MaskZ, MaskD, MaskD, MaskD, MaskD)
	#define _hlslpp256_perm_zwxx_cdaa_ps(x) _hlslpp256_perm_ps(x, MaskZ, MaskW, MaskX, MaskX, MaskC, MaskD, MaskA, MaskA)
	#define _hlslpp256_perm_wzyw_aacb_ps(x) _hlslpp256_perm_ps(x, MaskW, MaskZ, MaskY, MaskW, MaskA, MaskA, MaskC, MaskB)
	#define _hlslpp256_perm_wwzw_cbba_ps(x) _hlslpp256_perm_ps(x, MaskW, MaskW, MaskZ, MaskW, MaskC, MaskB, MaskB, MaskA)
	#define _hlslpp256_perm_wwww_cccc_ps(x) _hlslpp256_perm_ps(x, MaskW, MaskW, MaskW, MaskW, MaskC, MaskC, MaskC, MaskC)
	#define _hlslpp256_perm_wwww_dddd_ps(x) _hlslpp256_perm_ps(x, MaskW, MaskW, MaskW, MaskW, MaskD, MaskD, MaskD, MaskD)

	#define _hlslpp256_perm_aaaa_xxxx_ps(x) _hlslpp256_perm_ps(x, MaskA, MaskA, MaskA, MaskA, MaskX, MaskX, MaskX, MaskX)

#if defined(HLSLPP_DOUBLE)

	#define _hlslpp_perm_xx_pd(x)				_hlslpp_perm_pd((x), HLSLPP_SHUFFLE_MASK_PD(MaskX, MaskX))
	#define _hlslpp_perm_xy_pd(x)				_hlslpp_perm_pd((x), HLSLPP_SHUFFLE_MASK_PD(MaskX, MaskY))
	#define _hlslpp_perm_yx_pd(x)				_hlslpp_perm_pd((x), HLSLPP_SHUFFLE_MASK_PD(MaskY, MaskX))
	#define _hlslpp_perm_yy_pd(x)				_hlslpp_perm_pd((x), HLSLPP_SHUFFLE_MASK_PD(MaskY, MaskY))

	#define _hlslpp_shuf_xx_pd(x, y)			_hlslpp_shuffle_pd((x), (y), HLSLPP_SHUFFLE_MASK_PD(MaskX, MaskX))
	#define _hlslpp_shuf_xy_pd(x, y)			_hlslpp_shuffle_pd((x), (y), HLSLPP_SHUFFLE_MASK_PD(MaskX, MaskY))
	#define _hlslpp_shuf_yx_pd(x, y)			_hlslpp_shuffle_pd((x), (y), HLSLPP_SHUFFLE_MASK_PD(MaskY, MaskX))
	#define _hlslpp_shuf_yy_pd(x, y)			_hlslpp_shuffle_pd((x), (y), HLSLPP_SHUFFLE_MASK_PD(MaskY, MaskY))

#endif

#if !defined(_hlslpp_sign_ps)
	// Reference http://www.liranuna.com/sse-intrinsics-optimizations-in-popular-compilers/
	#define _hlslpp_sign_ps(val)				_hlslpp_and_ps(_hlslpp_or_ps(_hlslpp_and_ps((val), f4_minus1), f4_1), _hlslpp_cmpneq_ps((val), f4_0))
#endif
	
	#define _hlslpp_cmpneq1_ps(val1, val2)		_hlslpp_and_ps(_hlslpp_cmpneq_ps((val1), (val2)), f4_1)
	#define _hlslpp_cmpeq1_ps(val1, val2)		_hlslpp_and_ps(_hlslpp_cmpeq_ps((val1), (val2)), f4_1)
	
	#define _hlslpp_cmpgt1_ps(val1, val2)		_hlslpp_and_ps(_hlslpp_cmpgt_ps((val1), (val2)), f4_1)
	#define _hlslpp_cmpge1_ps(val1, val2)		_hlslpp_and_ps(_hlslpp_cmpge_ps((val1), (val2)), f4_1)
	
	#define _hlslpp_cmplt1_ps(val1, val2)		_hlslpp_and_ps(_hlslpp_cmplt_ps((val1), (val2)), f4_1)
	#define _hlslpp_cmple1_ps(val1, val2)		_hlslpp_and_ps(_hlslpp_cmple_ps((val1), (val2)), f4_1)

	#define _hlslpp_perm_xxxx_epi32(x)			_hlslpp_perm_epi32((x), MaskX, MaskX, MaskX, MaskX)
	#define _hlslpp_perm_xxyx_epi32(x)			_hlslpp_perm_epi32((x), MaskX, MaskX, MaskY, MaskX)
	#define _hlslpp_perm_xxyz_epi32(x)			_hlslpp_perm_epi32((x), MaskX, MaskX, MaskY, MaskZ)

	#define _hlslpp_shuf_xxxx_epi32(x, y)		_hlslpp_shuffle_epi32((x), (y), MaskX, MaskX, MaskX, MaskX)
	#define _hlslpp_shuf_xyxx_epi32(x, y)		_hlslpp_shuffle_epi32((x), (y), MaskX, MaskY, MaskX, MaskX)
	#define _hlslpp_shuf_xxxy_epi32(x, y)		_hlslpp_shuffle_epi32((x), (y), MaskX, MaskX, MaskX, MaskY)
	#define _hlslpp_shuf_xyxy_epi32(x, y)		_hlslpp_shuffle_epi32((x), (y), MaskX, MaskY, MaskX, MaskY)

	#define _hlslpp_cmpneq1_epi32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmpneq_epi32((val1), (val2)), i4_1)
	#define _hlslpp_cmpeq1_epi32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmpeq_epi32((val1), (val2)), i4_1)
	
	#define _hlslpp_cmpgt1_epi32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmpgt_epi32((val1), (val2)), i4_1)
	#define _hlslpp_cmpge1_epi32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmpge_epi32((val1), (val2)), i4_1)
	
	#define _hlslpp_cmplt1_epi32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmplt_epi32((val1), (val2)), i4_1)
	#define _hlslpp_cmple1_epi32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmple_epi32((val1), (val2)), i4_1)

	#define _hlslpp_cmpneq1_epu32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmpneq_epu32((val1), (val2)), u4_1)
	#define _hlslpp_cmpeq1_epu32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmpeq_epu32((val1), (val2)), u4_1)

	#define _hlslpp_cmpgt1_epu32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmpgt_epu32((val1), (val2)), u4_1)
	#define _hlslpp_cmpge1_epu32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmpge_epu32((val1), (val2)), u4_1)

	#define _hlslpp_cmplt1_epu32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmplt_epu32((val1), (val2)), u4_1)
	#define _hlslpp_cmple1_epu32(val1, val2)	_hlslpp_and_si128(_hlslpp_cmple_epu32((val1), (val2)), u4_1)

#if !defined(_hlslpp256_sign_ps)
	#define _hlslpp256_sign_ps(val)				_hlslpp256_and_ps(_hlslpp256_or_ps(_hlslpp256_and_ps((val), f8minusOne), f8_1), _hlslpp256_cmpneq_ps((val), f8_0))
#endif

	#define _hlslpp256_cmpneq1_ps(val1, val2)	_hlslpp256_and_ps(_hlslpp256_cmpneq_ps((val1), (val2)), f8_1)
	#define _hlslpp256_cmpeq1_ps(val1, val2)	_hlslpp256_and_ps(_hlslpp256_cmpeq_ps((val1), (val2)), f8_1)

	#define _hlslpp256_cmpgt1_ps(val1, val2)	_hlslpp256_and_ps(_hlslpp256_cmpgt_ps((val1), (val2)), f8_1)
	#define _hlslpp256_cmpge1_ps(val1, val2)	_hlslpp256_and_ps(_hlslpp256_cmpge_ps((val1), (val2)), f8_1)

	#define _hlslpp256_cmplt1_ps(val1, val2)	_hlslpp256_and_ps(_hlslpp256_cmplt_ps((val1), (val2)), f8_1)
	#define _hlslpp256_cmple1_ps(val1, val2)	_hlslpp256_and_ps(_hlslpp256_cmple_ps((val1), (val2)), f8_1)

	// Forward declarations

	struct float1;
	struct float2;
	struct float3;
	struct float4;

	struct int1;
	struct int2;
	struct int3;
	struct int4;

	struct uint1;
	struct uint2;
	struct uint3;
	struct uint4;

	struct double1;
	struct double2;
	struct double3;
	struct double4;
	
	struct float1x1;
	struct float1x2;
	struct float1x3;
	struct float1x4;
	struct float2x1;
	struct float2x2;
	struct float2x3;
	struct float2x4;
	struct float3x1;
	struct float3x2;
	struct float3x3;
	struct float3x4;
	struct float4x1;
	struct float4x2;
	struct float4x3;
	struct float4x4;

	// Aliases to conform to latest hlsl names
	// https://github.com/microsoft/DirectXShaderCompiler/wiki/16-Bit-Scalar-Types

	typedef float1 float32_t1;
	typedef float2 float32_t2;
	typedef float3 float32_t3;
	typedef float4 float32_t4;

	typedef int1 int32_t1;
	typedef int2 int32_t2;
	typedef int3 int32_t3;
	typedef int4 int32_t4;

	typedef uint1 uint32_t1;
	typedef uint2 uint32_t2;
	typedef uint3 uint32_t3;
	typedef uint4 uint32_t4;

	typedef double1 float64_t1;
	typedef double2 float64_t2;
	typedef double3 float64_t3;
	typedef double4 float64_t4;

	typedef float1x1 float32_t1x1;
	typedef float1x2 float32_t1x2;
	typedef float1x3 float32_t1x3;
	typedef float1x4 float32_t1x4;
	typedef float2x1 float32_t2x1;
	typedef float2x2 float32_t2x2;
	typedef float2x3 float32_t2x3;
	typedef float2x4 float32_t2x4;
	typedef float3x1 float32_t3x1;
	typedef float3x2 float32_t3x2;
	typedef float3x3 float32_t3x3;
	typedef float3x4 float32_t3x4;
	typedef float4x1 float32_t4x1;
	typedef float4x2 float32_t4x2;
	typedef float4x3 float32_t4x3;
	typedef float4x4 float32_t4x4;

	// Typedefs for common hlsl types

	typedef uint32_t uint;

	// HLSL assumes certain sizes of types
	static_assert(sizeof(int) == 4, "Size of integer must be 4 bytes");
}