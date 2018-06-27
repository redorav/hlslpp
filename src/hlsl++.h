#pragma once

#define HLSLPP_MATRIX_PACK_ROW_MAJOR

#define hlslpp_str2(x) #x
#define hlslpp_str(x) hlslpp_str2(x)

#if defined(__clang__) || defined(__GNUG__)

#define hlslpp_inline inline __attribute__((always_inline))

// Add \t to the word warning to avoid some compilers issuing extra warnings
//#define hlslpp_pragma(x) _Pragma (#x)
//#define hlslpp_warning(msg) hlslpp_pragma(message(__FILE__"(" hlslpp_str(__LINE__) "):\twarning: "#msg))

#elif defined(_MSC_VER)

#define hlslpp_inline __forceinline

//#define hlslpp_warning(msg) __pragma(message(__FILE__"(" hlslpp_str(__LINE__) "): warning: "##msg))

#endif

#define hlslpp_warning(msg)

#include <type_traits>
#include <cstdint>

namespace hlslpp
{
	union BitMask
	{
		uint32_t i;
		float f;
		explicit BitMask(uint32_t i) : i(i) {}
		explicit BitMask(float f) : f(f) {}
	};

	const hlslpp::BitMask fffMask		(0xffffffffu); // Negative NaN
	const hlslpp::BitMask nanMask		(0x7fffffffu); // Positive NaN
	const hlslpp::BitMask infMask		(0x7f800000u);
	const hlslpp::BitMask minusinfMask	(0xff800000u);
	const hlslpp::BitMask absMask		(0x7fffffffu);
	const hlslpp::BitMask negMask		(0x80000000u);
}

#if defined(_M_ARM) || defined(__arm__)
	#include "hlsl++_neon.h"
#else
	#include "hlsl++_sse.h"
#endif

// Helper constants

namespace hlslpp
{	
	//----- Constants
	const n128 f4_0				= _hlslpp_set1_ps( 0.0f);
	const n128 f4_1				= _hlslpp_set1_ps( 1.0f);
	const n128 f4minusOne		= _hlslpp_set1_ps(-1.0f);
	const n128 f4_05			= _hlslpp_set1_ps( 0.5f);
	const n128 f4_minus05		= _hlslpp_set1_ps(-0.5f);
	const n128 f4_2				= _hlslpp_set1_ps( 2.0f);
	const n128 f4_minus2		= _hlslpp_set1_ps(-2.0f);
	const n128 f4_3				= _hlslpp_set1_ps( 3.0f);
	const n128 f4_10			= _hlslpp_set1_ps(10.0f);
	const n128 f4_e				= _hlslpp_set1_ps(2.718281828f);
	
	const n128 f4_pi			= _hlslpp_set1_ps( 3.14159265f); // pi
	const n128 f4_minusPi		= _hlslpp_set1_ps(-3.14159265f); // -pi
	const n128 f4_invPi			= _hlslpp_set1_ps( 0.31830988f); // 1 / pi
	
	const n128 f4_2pi			= _hlslpp_set1_ps( 6.28318530f); //  2 * pi
	const n128 f4_minus2pi		= _hlslpp_set1_ps(-6.28318530f); // -2 * pi
	const n128 f4_inv2pi		= _hlslpp_set1_ps( 0.15915494f); // 1 / (2 * pi)
	
	const n128 f4_pi2			= _hlslpp_set1_ps( 1.57079632f); //  pi / 2
	const n128 f4_minusPi2		= _hlslpp_set1_ps(-1.57079632f); // -pi / 2
	const n128 f4_invPi2		= _hlslpp_set1_ps( 0.63661977f); // 2 / pi
	
	const n128 f4_3pi2			= _hlslpp_set1_ps( 4.71238898f); //  3 * pi / 2
	const n128 f4_minus3pi2		= _hlslpp_set1_ps(-4.71238898f); // -3 * pi / 2
	
	const n128 f4_pi4			= _hlslpp_set1_ps( 0.78539816f); //  pi / 4
	const n128 f4_minusPi4		= _hlslpp_set1_ps(-0.78539816f); // -pi / 4
	
	const n128 f4_NaN			= _hlslpp_set1_ps(nanMask.f);		// Quiet NaN
	const n128 f4_inf			= _hlslpp_set1_ps(infMask.f);		// Infinity
	const n128 f4_minusinf		= _hlslpp_set1_ps(minusinfMask.f);	// -Infinity
	
	const n128 f4_rad2deg		= _hlslpp_set1_ps(180.0f / 3.14159265f);
	const n128 f4_deg2rad		= _hlslpp_set1_ps(3.14159265f / 180.f);
	
	const n128i i4_0			= _hlslpp_set1_epi32( 0);
	const n128i i4_1			= _hlslpp_set1_epi32( 1);
	
	//----- Masks
	const n128 f4negativeMask	= _hlslpp_set1_ps(negMask.f);
	const n128 f4absMask		= _hlslpp_set1_ps(absMask.f);
	
	const n128i i4negativeMask	= _hlslpp_set1_epi32(negMask.i);
	const n128i i4absMask		= _hlslpp_set1_epi32(absMask.i);
	
	const uint32_t _MM_X		= 0;
	const uint32_t _MM_Y		= 1;
	const uint32_t _MM_Z		= 2;
	const uint32_t _MM_W		= 3;
}

#define HLSLPP_SHUFFLE_MASK(X, Y, Z, W)			(((W) << 6) | ((Z) << 4) | ((Y) << 2) | (X))

// Create a mask where 1 selects from x, 0 selects from y
#define HLSLPP_BLEND_MASK(X, Y, Z, W)			(~(X | (Y << 1) | (Z << 2) | (W << 3)) & 0xf)

#define HLSLPP_COMPONENT_X(X)					(1 << X)
#define HLSLPP_COMPONENT_XY(X, Y)				((1 << X) | (1 << Y))
#define HLSLPP_COMPONENT_XYZ(X, Y, Z)			((1 << X) | (1 << Y) | (1 << Z))
#define HLSLPP_COMPONENT_XYZW(X, Y, Z, W)		((1 << X) | (1 << Y) | (1 << Z) | (1 << W))

//----- Helper compound "intrinsics"

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

namespace hlslpp
{
	// Returns true if x is +infinity or -infinity
	hlslpp_inline n128 _hlslpp_isinf_ps(n128 x)
	{
		return _hlslpp_or_ps(_hlslpp_cmpeq_ps(x, f4_inf), _hlslpp_cmpeq_ps(x, f4_minusinf));
	}

	// Returns true if x is not +infinity or -infinity
	hlslpp_inline n128 _hlslpp_isfinite_ps(n128 x)
	{
		return _hlslpp_and_ps(_hlslpp_and_ps(_hlslpp_cmpneq_ps(x, f4_inf), _hlslpp_cmpneq_ps(x, f4_minusinf)), _hlslpp_cmpeq_ps(x, x));
	}
};

#define _hlslpp_perm_xxxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_X))
#define _hlslpp_perm_xxxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_perm_xxxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_perm_xxxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_W))
#define _hlslpp_perm_xxyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_perm_xxyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_perm_xxyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_perm_xxyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_perm_xxzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_perm_xxzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_perm_xxzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_perm_xxzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_perm_xxwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_X))
#define _hlslpp_perm_xxwy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_perm_xxwz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_perm_xxww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_W))
#define _hlslpp_perm_xyxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_perm_xyxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_perm_xyxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_perm_xyxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_perm_xyyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_perm_xyyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_perm_xyyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_perm_xyyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_perm_xyzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_perm_xyzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_perm_xyzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_perm_xyzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_perm_xywx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_perm_xywy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_perm_xywz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_perm_xyww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_perm_xzxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_perm_xzxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_perm_xzxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_perm_xzxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_perm_xzyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_perm_xzyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_perm_xzyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_perm_xzyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_perm_xzzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_perm_xzzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_perm_xzzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_perm_xzzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_perm_xzwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_perm_xzwy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_perm_xzwz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_perm_xzww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_perm_xwxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_X))
#define _hlslpp_perm_xwxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_perm_xwxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_perm_xwxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_W))
#define _hlslpp_perm_xwyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_perm_xwyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_perm_xwyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_perm_xwyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_perm_xwzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_perm_xwzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_perm_xwzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_perm_xwzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_perm_xwwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_X))
#define _hlslpp_perm_xwwy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_perm_xwwz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_perm_xwww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_W))
#define _hlslpp_perm_yxxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_X))
#define _hlslpp_perm_yxxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_perm_yxxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_perm_yxxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_W))
#define _hlslpp_perm_yxyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_perm_yxyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_perm_yxyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_perm_yxyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_perm_yxzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_perm_yxzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_perm_yxzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_perm_yxzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_perm_yxwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_X))
#define _hlslpp_perm_yxwy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_perm_yxwz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_perm_yxww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_W))
#define _hlslpp_perm_yyxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_perm_yyxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_perm_yyxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_perm_yyxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_perm_yyyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_perm_yyyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_perm_yyyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_perm_yyyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_perm_yyzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_perm_yyzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_perm_yyzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_perm_yyzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_perm_yywx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_perm_yywy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_perm_yywz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_perm_yyww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_perm_yzxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_perm_yzxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_perm_yzxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_perm_yzxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_perm_yzyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_perm_yzyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_perm_yzyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_perm_yzyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_perm_yzzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_perm_yzzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_perm_yzzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_perm_yzzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_perm_yzwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_perm_yzwy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_perm_yzwz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_perm_yzww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_perm_ywxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_X))
#define _hlslpp_perm_ywxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_perm_ywxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_perm_ywxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_W))
#define _hlslpp_perm_ywyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_perm_ywyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_perm_ywyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_perm_ywyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_perm_ywzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_perm_ywzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_perm_ywzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_perm_ywzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_perm_ywwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_X))
#define _hlslpp_perm_ywwy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_perm_ywwz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_perm_ywww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_W))
#define _hlslpp_perm_zxxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_X))
#define _hlslpp_perm_zxxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_perm_zxxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_perm_zxxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_W))
#define _hlslpp_perm_zxyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_perm_zxyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_perm_zxyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_perm_zxyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_perm_zxzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_perm_zxzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_perm_zxzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_perm_zxzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_perm_zxwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_X))
#define _hlslpp_perm_zxwy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_perm_zxwz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_perm_zxww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_W))
#define _hlslpp_perm_zyxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_perm_zyxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_perm_zyxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_perm_zyxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_perm_zyyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_perm_zyyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_perm_zyyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_perm_zyyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_perm_zyzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_perm_zyzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_perm_zyzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_perm_zyzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_perm_zywx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_perm_zywy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_perm_zywz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_perm_zyww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_perm_zzxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_perm_zzxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_perm_zzxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_perm_zzxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_perm_zzyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_perm_zzyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_perm_zzyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_perm_zzyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_perm_zzzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_perm_zzzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_perm_zzzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_perm_zzzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_perm_zzwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_perm_zzwy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_perm_zzwz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_perm_zzww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_perm_zwxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_X))
#define _hlslpp_perm_zwxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_perm_zwxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_perm_zwxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_W))
#define _hlslpp_perm_zwyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_perm_zwyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_perm_zwyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_perm_zwyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_perm_zwzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_perm_zwzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_perm_zwzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_perm_zwzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_perm_zwwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_X))
#define _hlslpp_perm_zwwy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_perm_zwwz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_perm_zwww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_W))
#define _hlslpp_perm_wxxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_X))
#define _hlslpp_perm_wxxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_perm_wxxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_perm_wxxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_W))
#define _hlslpp_perm_wxyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_perm_wxyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_perm_wxyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_perm_wxyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_perm_wxzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_perm_wxzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_perm_wxzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_perm_wxzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_perm_wxwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_X))
#define _hlslpp_perm_wxwy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_perm_wxwz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_perm_wxww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_W))
#define _hlslpp_perm_wyxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_perm_wyxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_perm_wyxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_perm_wyxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_perm_wyyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_perm_wyyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_perm_wyyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_perm_wyyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_perm_wyzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_perm_wyzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_perm_wyzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_perm_wyzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_perm_wywx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_perm_wywy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_perm_wywz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_perm_wyww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_perm_wzxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_perm_wzxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_perm_wzxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_perm_wzxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_perm_wzyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_perm_wzyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_perm_wzyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_perm_wzyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_perm_wzzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_perm_wzzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_perm_wzzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_perm_wzzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_perm_wzwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_perm_wzwy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_perm_wzwz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_perm_wzww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_perm_wwxx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_X))
#define _hlslpp_perm_wwxy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_perm_wwxz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_perm_wwxw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_W))
#define _hlslpp_perm_wwyx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_perm_wwyy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_perm_wwyz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_perm_wwyw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_perm_wwzx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_perm_wwzy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_perm_wwzz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_perm_wwzw_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_perm_wwwx_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_X))
#define _hlslpp_perm_wwwy_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_perm_wwwz_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_perm_wwww_ps(x)				_hlslpp_perm_ps((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_W))

#define _hlslpp_shuf_xxxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_X))
#define _hlslpp_shuf_xxxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_shuf_xxxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_shuf_xxxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_W))
#define _hlslpp_shuf_xxyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_shuf_xxyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_shuf_xxyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_shuf_xxyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_shuf_xxzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_shuf_xxzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_shuf_xxzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_shuf_xxzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_shuf_xxwx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_X))
#define _hlslpp_shuf_xxwy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_shuf_xxwz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_shuf_xxww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_W))
#define _hlslpp_shuf_xyxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_shuf_xyxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_shuf_xyxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_shuf_xyxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_shuf_xyyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_shuf_xyyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_shuf_xyyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_shuf_xyyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_shuf_xyzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_shuf_xyzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_shuf_xyzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_shuf_xyzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_shuf_xywx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_shuf_xywy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_shuf_xywz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_shuf_xyww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_shuf_xzxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_shuf_xzxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_shuf_xzxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_shuf_xzxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_shuf_xzyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_shuf_xzyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_shuf_xzyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_shuf_xzyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_shuf_xzzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_shuf_xzzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_shuf_xzzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_shuf_xzzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_shuf_xzwx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_shuf_xzwy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_shuf_xzwz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_shuf_xzww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_shuf_xwxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_X))
#define _hlslpp_shuf_xwxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_shuf_xwxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_shuf_xwxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_W))
#define _hlslpp_shuf_xwyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_shuf_xwyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_shuf_xwyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_shuf_xwyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_shuf_xwzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_shuf_xwzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_shuf_xwzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_shuf_xwzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_shuf_xwwx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_X))
#define _hlslpp_shuf_xwwy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_shuf_xwwz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_shuf_xwww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_W))
#define _hlslpp_shuf_yxxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_X))
#define _hlslpp_shuf_yxxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_shuf_yxxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_shuf_yxxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_W))
#define _hlslpp_shuf_yxyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_shuf_yxyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_shuf_yxyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_shuf_yxyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_shuf_yxzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_shuf_yxzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_shuf_yxzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_shuf_yxzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_shuf_yxwx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_X))
#define _hlslpp_shuf_yxwy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_shuf_yxwz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_shuf_yxww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_W))
#define _hlslpp_shuf_yyxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_shuf_yyxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_shuf_yyxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_shuf_yyxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_shuf_yyyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_shuf_yyyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_shuf_yyyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_shuf_yyyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_shuf_yyzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_shuf_yyzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_shuf_yyzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_shuf_yyzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_shuf_yywx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_shuf_yywy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_shuf_yywz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_shuf_yyww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_shuf_yzxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_shuf_yzxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_shuf_yzxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_shuf_yzxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_shuf_yzyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_shuf_yzyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_shuf_yzyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_shuf_yzyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_shuf_yzzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_shuf_yzzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_shuf_yzzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_shuf_yzzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_shuf_yzwx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_shuf_yzwy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_shuf_yzwz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_shuf_yzww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_shuf_ywxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_X))
#define _hlslpp_shuf_ywxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_shuf_ywxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_shuf_ywxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_W))
#define _hlslpp_shuf_ywyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_shuf_ywyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_shuf_ywyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_shuf_ywyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_shuf_ywzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_shuf_ywzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_shuf_ywzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_shuf_ywzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_shuf_ywwx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_X))
#define _hlslpp_shuf_ywwy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_shuf_ywwz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_shuf_ywww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_W))
#define _hlslpp_shuf_zxxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_X))
#define _hlslpp_shuf_zxxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_shuf_zxxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_shuf_zxxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_W))
#define _hlslpp_shuf_zxyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_shuf_zxyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_shuf_zxyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_shuf_zxyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_shuf_zxzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_shuf_zxzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_shuf_zxzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_shuf_zxzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_shuf_zxwx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_X))
#define _hlslpp_shuf_zxwy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_shuf_zxwz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_shuf_zxww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_W))
#define _hlslpp_shuf_zyxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_shuf_zyxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_shuf_zyxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_shuf_zyxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_shuf_zyyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_shuf_zyyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_shuf_zyyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_shuf_zyyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_shuf_zyzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_shuf_zyzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_shuf_zyzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_shuf_zyzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_shuf_zywx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_shuf_zywy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_shuf_zywz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_shuf_zyww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_shuf_zzxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_shuf_zzxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_shuf_zzxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_shuf_zzxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_shuf_zzyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_shuf_zzyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_shuf_zzyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_shuf_zzyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_shuf_zzzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_shuf_zzzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_shuf_zzzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_shuf_zzzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_shuf_zzwx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_shuf_zzwy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_shuf_zzwz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_shuf_zzww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_shuf_zwxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_X))
#define _hlslpp_shuf_zwxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_shuf_zwxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_shuf_zwxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_W))
#define _hlslpp_shuf_zwyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_shuf_zwyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_shuf_zwyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_shuf_zwyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_shuf_zwzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_shuf_zwzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_shuf_zwzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_shuf_zwzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_shuf_zwwx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_X))
#define _hlslpp_shuf_zwwy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_shuf_zwwz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_shuf_zwww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_W))
#define _hlslpp_shuf_wxxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_X))
#define _hlslpp_shuf_wxxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_shuf_wxxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_shuf_wxxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_W))
#define _hlslpp_shuf_wxyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_shuf_wxyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_shuf_wxyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_shuf_wxyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_shuf_wxzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_shuf_wxzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_shuf_wxzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_shuf_wxzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_shuf_wxwx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_X))
#define _hlslpp_shuf_wxwy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_shuf_wxwz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_shuf_wxww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_W))
#define _hlslpp_shuf_wyxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_shuf_wyxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_shuf_wyxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_shuf_wyxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_shuf_wyyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_shuf_wyyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_shuf_wyyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_shuf_wyyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_shuf_wyzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_shuf_wyzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_shuf_wyzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_shuf_wyzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_shuf_wywx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_shuf_wywy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_shuf_wywz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_shuf_wyww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_shuf_wzxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_shuf_wzxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_shuf_wzxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_shuf_wzxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_shuf_wzyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_shuf_wzyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_shuf_wzyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_shuf_wzyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_shuf_wzzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_shuf_wzzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_shuf_wzzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_shuf_wzzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_shuf_wzwx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_shuf_wzwy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_shuf_wzwz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_shuf_wzww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_shuf_wwxx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_X))
#define _hlslpp_shuf_wwxy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_shuf_wwxz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_shuf_wwxw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_W))
#define _hlslpp_shuf_wwyx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_shuf_wwyy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_shuf_wwyz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_shuf_wwyw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_shuf_wwzx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_shuf_wwzy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_shuf_wwzz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_shuf_wwzw_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_shuf_wwwx_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_X))
#define _hlslpp_shuf_wwwy_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_shuf_wwwz_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_shuf_wwww_ps(x, y)			_hlslpp_shuffle_ps((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_W))

#define _hlslpp_perm_xxxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_X))
#define _hlslpp_perm_xxxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_perm_xxxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_perm_xxxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_W))
#define _hlslpp_perm_xxyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_perm_xxyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_perm_xxyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_perm_xxyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_perm_xxzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_perm_xxzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_perm_xxzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_perm_xxzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_perm_xxwx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_X))
#define _hlslpp_perm_xxwy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_perm_xxwz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_perm_xxww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_W))
#define _hlslpp_perm_xyxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_perm_xyxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_perm_xyxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_perm_xyxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_perm_xyyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_perm_xyyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_perm_xyyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_perm_xyyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_perm_xyzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_perm_xyzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_perm_xyzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_perm_xyzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_perm_xywx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_perm_xywy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_perm_xywz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_perm_xyww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_perm_xzxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_perm_xzxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_perm_xzxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_perm_xzxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_perm_xzyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_perm_xzyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_perm_xzyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_perm_xzyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_perm_xzzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_perm_xzzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_perm_xzzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_perm_xzzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_perm_xzwx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_perm_xzwy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_perm_xzwz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_perm_xzww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_perm_xwxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_X))
#define _hlslpp_perm_xwxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_perm_xwxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_perm_xwxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_W))
#define _hlslpp_perm_xwyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_perm_xwyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_perm_xwyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_perm_xwyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_perm_xwzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_perm_xwzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_perm_xwzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_perm_xwzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_perm_xwwx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_X))
#define _hlslpp_perm_xwwy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_perm_xwwz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_perm_xwww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_W))
#define _hlslpp_perm_yxxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_X))
#define _hlslpp_perm_yxxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_perm_yxxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_perm_yxxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_W))
#define _hlslpp_perm_yxyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_perm_yxyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_perm_yxyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_perm_yxyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_perm_yxzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_perm_yxzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_perm_yxzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_perm_yxzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_perm_yxwx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_X))
#define _hlslpp_perm_yxwy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_perm_yxwz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_perm_yxww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_W))
#define _hlslpp_perm_yyxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_perm_yyxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_perm_yyxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_perm_yyxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_perm_yyyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_perm_yyyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_perm_yyyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_perm_yyyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_perm_yyzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_perm_yyzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_perm_yyzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_perm_yyzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_perm_yywx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_perm_yywy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_perm_yywz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_perm_yyww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_perm_yzxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_perm_yzxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_perm_yzxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_perm_yzxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_perm_yzyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_perm_yzyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_perm_yzyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_perm_yzyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_perm_yzzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_perm_yzzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_perm_yzzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_perm_yzzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_perm_yzwx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_perm_yzwy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_perm_yzwz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_perm_yzww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_perm_ywxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_X))
#define _hlslpp_perm_ywxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_perm_ywxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_perm_ywxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_W))
#define _hlslpp_perm_ywyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_perm_ywyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_perm_ywyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_perm_ywyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_perm_ywzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_perm_ywzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_perm_ywzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_perm_ywzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_perm_ywwx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_X))
#define _hlslpp_perm_ywwy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_perm_ywwz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_perm_ywww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_W))
#define _hlslpp_perm_zxxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_X))
#define _hlslpp_perm_zxxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_perm_zxxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_perm_zxxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_W))
#define _hlslpp_perm_zxyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_perm_zxyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_perm_zxyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_perm_zxyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_perm_zxzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_perm_zxzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_perm_zxzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_perm_zxzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_perm_zxwx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_X))
#define _hlslpp_perm_zxwy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_perm_zxwz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_perm_zxww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_W))
#define _hlslpp_perm_zyxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_perm_zyxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_perm_zyxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_perm_zyxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_perm_zyyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_perm_zyyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_perm_zyyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_perm_zyyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_perm_zyzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_perm_zyzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_perm_zyzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_perm_zyzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_perm_zywx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_perm_zywy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_perm_zywz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_perm_zyww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_perm_zzxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_perm_zzxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_perm_zzxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_perm_zzxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_perm_zzyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_perm_zzyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_perm_zzyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_perm_zzyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_perm_zzzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_perm_zzzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_perm_zzzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_perm_zzzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_perm_zzwx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_perm_zzwy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_perm_zzwz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_perm_zzww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_perm_zwxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_X))
#define _hlslpp_perm_zwxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_perm_zwxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_perm_zwxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_W))
#define _hlslpp_perm_zwyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_perm_zwyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_perm_zwyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_perm_zwyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_perm_zwzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_perm_zwzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_perm_zwzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_perm_zwzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_perm_zwwx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_X))
#define _hlslpp_perm_zwwy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_perm_zwwz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_perm_zwww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_W))
#define _hlslpp_perm_wxxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_X))
#define _hlslpp_perm_wxxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_perm_wxxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_perm_wxxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_W))
#define _hlslpp_perm_wxyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_perm_wxyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_perm_wxyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_perm_wxyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_perm_wxzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_perm_wxzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_perm_wxzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_perm_wxzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_perm_wxwx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_X))
#define _hlslpp_perm_wxwy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_perm_wxwz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_perm_wxww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_W))
#define _hlslpp_perm_wyxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_perm_wyxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_perm_wyxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_perm_wyxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_perm_wyyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_perm_wyyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_perm_wyyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_perm_wyyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_perm_wyzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_perm_wyzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_perm_wyzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_perm_wyzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_perm_wywx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_perm_wywy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_perm_wywz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_perm_wyww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_perm_wzxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_perm_wzxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_perm_wzxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_perm_wzxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_perm_wzyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_perm_wzyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_perm_wzyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_perm_wzyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_perm_wzzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_perm_wzzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_perm_wzzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_perm_wzzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_perm_wzwx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_perm_wzwy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_perm_wzwz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_perm_wzww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_perm_wwxx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_X))
#define _hlslpp_perm_wwxy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_perm_wwxz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_perm_wwxw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_W))
#define _hlslpp_perm_wwyx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_perm_wwyy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_perm_wwyz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_perm_wwyw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_perm_wwzx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_perm_wwzy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_perm_wwzz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_perm_wwzw_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_perm_wwwx_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_X))
#define _hlslpp_perm_wwwy_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_perm_wwwz_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_perm_wwww_epi32(x)				_hlslpp_perm_epi32((x), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_W))

#define _hlslpp_shuf_xxxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_X))
#define _hlslpp_shuf_xxxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_shuf_xxxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_shuf_xxxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_X, _MM_W))
#define _hlslpp_shuf_xxyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_shuf_xxyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_shuf_xxyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_shuf_xxyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_shuf_xxzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_shuf_xxzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_shuf_xxzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_shuf_xxzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_shuf_xxwx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_X))
#define _hlslpp_shuf_xxwy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_shuf_xxwz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_shuf_xxww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_X, _MM_W, _MM_W))
#define _hlslpp_shuf_xyxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_shuf_xyxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_shuf_xyxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_shuf_xyxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_shuf_xyyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_shuf_xyyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_shuf_xyyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_shuf_xyyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_shuf_xyzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_shuf_xyzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_shuf_xyzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_shuf_xyzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_shuf_xywx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_shuf_xywy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_shuf_xywz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_shuf_xyww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_shuf_xzxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_shuf_xzxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_shuf_xzxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_shuf_xzxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_shuf_xzyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_shuf_xzyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_shuf_xzyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_shuf_xzyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_shuf_xzzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_shuf_xzzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_shuf_xzzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_shuf_xzzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_shuf_xzwx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_shuf_xzwy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_shuf_xzwz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_shuf_xzww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_shuf_xwxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_X))
#define _hlslpp_shuf_xwxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_shuf_xwxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_shuf_xwxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_X, _MM_W))
#define _hlslpp_shuf_xwyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_shuf_xwyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_shuf_xwyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_shuf_xwyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_shuf_xwzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_shuf_xwzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_shuf_xwzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_shuf_xwzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_shuf_xwwx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_X))
#define _hlslpp_shuf_xwwy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_shuf_xwwz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_shuf_xwww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_X, _MM_W, _MM_W, _MM_W))
#define _hlslpp_shuf_yxxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_X))
#define _hlslpp_shuf_yxxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_shuf_yxxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_shuf_yxxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_X, _MM_W))
#define _hlslpp_shuf_yxyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_shuf_yxyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_shuf_yxyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_shuf_yxyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_shuf_yxzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_shuf_yxzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_shuf_yxzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_shuf_yxzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_shuf_yxwx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_X))
#define _hlslpp_shuf_yxwy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_shuf_yxwz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_shuf_yxww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_X, _MM_W, _MM_W))
#define _hlslpp_shuf_yyxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_shuf_yyxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_shuf_yyxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_shuf_yyxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_shuf_yyyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_shuf_yyyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_shuf_yyyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_shuf_yyyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_shuf_yyzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_shuf_yyzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_shuf_yyzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_shuf_yyzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_shuf_yywx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_shuf_yywy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_shuf_yywz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_shuf_yyww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_shuf_yzxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_shuf_yzxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_shuf_yzxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_shuf_yzxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_shuf_yzyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_shuf_yzyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_shuf_yzyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_shuf_yzyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_shuf_yzzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_shuf_yzzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_shuf_yzzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_shuf_yzzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_shuf_yzwx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_shuf_yzwy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_shuf_yzwz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_shuf_yzww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_shuf_ywxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_X))
#define _hlslpp_shuf_ywxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_shuf_ywxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_shuf_ywxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_X, _MM_W))
#define _hlslpp_shuf_ywyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_shuf_ywyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_shuf_ywyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_shuf_ywyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_shuf_ywzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_shuf_ywzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_shuf_ywzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_shuf_ywzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_shuf_ywwx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_X))
#define _hlslpp_shuf_ywwy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_shuf_ywwz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_shuf_ywww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Y, _MM_W, _MM_W, _MM_W))
#define _hlslpp_shuf_zxxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_X))
#define _hlslpp_shuf_zxxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_shuf_zxxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_shuf_zxxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_X, _MM_W))
#define _hlslpp_shuf_zxyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_shuf_zxyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_shuf_zxyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_shuf_zxyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_shuf_zxzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_shuf_zxzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_shuf_zxzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_shuf_zxzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_shuf_zxwx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_X))
#define _hlslpp_shuf_zxwy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_shuf_zxwz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_shuf_zxww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_X, _MM_W, _MM_W))
#define _hlslpp_shuf_zyxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_shuf_zyxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_shuf_zyxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_shuf_zyxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_shuf_zyyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_shuf_zyyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_shuf_zyyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_shuf_zyyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_shuf_zyzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_shuf_zyzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_shuf_zyzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_shuf_zyzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_shuf_zywx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_shuf_zywy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_shuf_zywz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_shuf_zyww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_shuf_zzxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_shuf_zzxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_shuf_zzxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_shuf_zzxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_shuf_zzyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_shuf_zzyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_shuf_zzyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_shuf_zzyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_shuf_zzzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_shuf_zzzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_shuf_zzzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_shuf_zzzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_shuf_zzwx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_shuf_zzwy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_shuf_zzwz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_shuf_zzww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_shuf_zwxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_X))
#define _hlslpp_shuf_zwxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_shuf_zwxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_shuf_zwxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_X, _MM_W))
#define _hlslpp_shuf_zwyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_shuf_zwyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_shuf_zwyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_shuf_zwyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_shuf_zwzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_shuf_zwzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_shuf_zwzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_shuf_zwzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_shuf_zwwx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_X))
#define _hlslpp_shuf_zwwy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_shuf_zwwz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_shuf_zwww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_Z, _MM_W, _MM_W, _MM_W))
#define _hlslpp_shuf_wxxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_X))
#define _hlslpp_shuf_wxxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_Y))
#define _hlslpp_shuf_wxxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_Z))
#define _hlslpp_shuf_wxxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_X, _MM_W))
#define _hlslpp_shuf_wxyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_X))
#define _hlslpp_shuf_wxyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_Y))
#define _hlslpp_shuf_wxyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_Z))
#define _hlslpp_shuf_wxyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Y, _MM_W))
#define _hlslpp_shuf_wxzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_X))
#define _hlslpp_shuf_wxzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_Y))
#define _hlslpp_shuf_wxzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_Z))
#define _hlslpp_shuf_wxzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_Z, _MM_W))
#define _hlslpp_shuf_wxwx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_X))
#define _hlslpp_shuf_wxwy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_Y))
#define _hlslpp_shuf_wxwz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_Z))
#define _hlslpp_shuf_wxww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_X, _MM_W, _MM_W))
#define _hlslpp_shuf_wyxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_X))
#define _hlslpp_shuf_wyxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_Y))
#define _hlslpp_shuf_wyxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_Z))
#define _hlslpp_shuf_wyxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_X, _MM_W))
#define _hlslpp_shuf_wyyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_X))
#define _hlslpp_shuf_wyyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_Y))
#define _hlslpp_shuf_wyyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_Z))
#define _hlslpp_shuf_wyyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Y, _MM_W))
#define _hlslpp_shuf_wyzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_X))
#define _hlslpp_shuf_wyzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_Y))
#define _hlslpp_shuf_wyzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_Z))
#define _hlslpp_shuf_wyzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_Z, _MM_W))
#define _hlslpp_shuf_wywx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_X))
#define _hlslpp_shuf_wywy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_Y))
#define _hlslpp_shuf_wywz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_Z))
#define _hlslpp_shuf_wyww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Y, _MM_W, _MM_W))
#define _hlslpp_shuf_wzxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_X))
#define _hlslpp_shuf_wzxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_Y))
#define _hlslpp_shuf_wzxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_Z))
#define _hlslpp_shuf_wzxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_X, _MM_W))
#define _hlslpp_shuf_wzyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_X))
#define _hlslpp_shuf_wzyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_Y))
#define _hlslpp_shuf_wzyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_Z))
#define _hlslpp_shuf_wzyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Y, _MM_W))
#define _hlslpp_shuf_wzzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_X))
#define _hlslpp_shuf_wzzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_Y))
#define _hlslpp_shuf_wzzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_Z))
#define _hlslpp_shuf_wzzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_Z, _MM_W))
#define _hlslpp_shuf_wzwx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_X))
#define _hlslpp_shuf_wzwy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_Y))
#define _hlslpp_shuf_wzwz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_Z))
#define _hlslpp_shuf_wzww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_Z, _MM_W, _MM_W))
#define _hlslpp_shuf_wwxx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_X))
#define _hlslpp_shuf_wwxy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_Y))
#define _hlslpp_shuf_wwxz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_Z))
#define _hlslpp_shuf_wwxw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_X, _MM_W))
#define _hlslpp_shuf_wwyx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_X))
#define _hlslpp_shuf_wwyy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_Y))
#define _hlslpp_shuf_wwyz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_Z))
#define _hlslpp_shuf_wwyw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Y, _MM_W))
#define _hlslpp_shuf_wwzx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_X))
#define _hlslpp_shuf_wwzy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_Y))
#define _hlslpp_shuf_wwzz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_Z))
#define _hlslpp_shuf_wwzw_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_Z, _MM_W))
#define _hlslpp_shuf_wwwx_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_X))
#define _hlslpp_shuf_wwwy_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_Y))
#define _hlslpp_shuf_wwwz_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_Z))
#define _hlslpp_shuf_wwww_epi32(x, y)			_hlslpp_shuffle_epi32((x), (y), HLSLPP_SHUFFLE_MASK(_MM_W, _MM_W, _MM_W, _MM_W))

namespace hlslpp
{
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
	hlslpp_inline n128 _hlslpp_log2_ps(n128 x)
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
		// n128 y_minus_x = _mm_sub_ps(y, x);
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
	hlslpp_inline n128 _hlslpp_exp2_ps(n128 x)
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
	hlslpp_inline n128 _hlslpp_sin_ps(n128 x)
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
	hlslpp_inline n128 _hlslpp_tan_ps(n128 x)
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
	hlslpp_inline n128 _hlslpp_acos_ps(n128 x)
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
	hlslpp_inline n128 _hlslpp_asin_ps(n128 x)
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
	hlslpp_inline n128 _hlslpp_atan_ps(n128 x)
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
	// Can optimize further in SSE3 via _mm_movehdup_ps instead of _hlslpp_perm_yxwx_ps, but is slower in MSVC and
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

	// Returns true if x is nan
	hlslpp_inline n128 _hlslpp_isnan_ps(n128 x)
	{
		return _hlslpp_cmpneq_ps(x, x);
	}

	//----- Float type -----//

	template<int N> class floatN {};
	template<int N, int M> class floatNxM {};

	// These need to be explicitly declared, otherwise floatN types cannot reference any float1xM or floatNx1 types, as the compiler looks for specialization
	template<> class floatNxM<1, 1>;
	template<> class floatNxM<1, 2>;
	template<> class floatNxM<1, 3>;
	template<> class floatNxM<1, 4>;
	template<> class floatNxM<2, 1>;
	template<> class floatNxM<3, 1>;
	template<> class floatNxM<4, 1>;

	// Auxiliary types to help template functions that take and return component types
	template<int...C> class components {};
	template<int X> using component1 = components<X>;
	template<int X, int Y> using component2 = components<X, Y>;
	template<int X, int Y, int Z> using component3 = components<X, Y, Z>;
	template<int X, int Y, int Z, int W> using component4 = components<X, Y, Z, W>;

	template<int N> struct componenttype {};
	template<> struct componenttype<1> { using type = components<0>; };
	template<> struct componenttype<2> { using type = components<0, 1>; };
	template<> struct componenttype<3> { using type = components<0, 1, 2>; };
	template<> struct componenttype<4> { using type = components<0, 1, 2, 3>; };

	template<int N> using componentbase = typename componenttype<N>::type;

	//----- Integer type -----//

	template<int N> class intN {};
	template<int N, int M> class intNxM {};

	// These need to be explicitly declared, otherwise floatN types cannot reference any float1xM or floatNx1 types, as the compiler looks for specialization
	template<> class intNxM<1, 1>;
	template<> class intNxM<1, 2>;
	template<> class intNxM<1, 3>;
	template<> class intNxM<1, 4>;
	template<> class intNxM<2, 1>;
	template<> class intNxM<3, 1>;
	template<> class intNxM<4, 1>;

	template<int...C> class icomponents {};
	template<int X> using icomponent1 = icomponents<X>;
	template<int X, int Y> using icomponent2 = icomponents<X, Y>;
	template<int X, int Y, int Z> using icomponent3 = icomponents<X, Y, Z>;
	template<int X, int Y, int Z, int W> using icomponent4 = icomponents<X, Y, Z, W>;

	template<int N> struct icomponenttype {};
	template<> struct icomponenttype<1> { using type = icomponents<0>; };
	template<> struct icomponenttype<2> { using type = icomponents<0, 1>; };
	template<> struct icomponenttype<3> { using type = icomponents<0, 1, 2>; };
	template<> struct icomponenttype<4> { using type = icomponents<0, 1, 2, 3>; };

	template<int N> using icomponentbase = typename icomponenttype<N>::type;

	template< bool B, class T = void >
	using enable_if_dim = typename std::enable_if<B, T>::type*;

	template<int X>
	class components<X>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
		};

		components<X>() {}
		hlslpp_inline explicit components<X>(n128 vec) : _vec(vec) {}
		hlslpp_inline explicit components<X>(float f) : _vec(_hlslpp_set_ps(f, 0.0f, 0.0f, 0.0f)) {}

		template<int E>
		explicit components<X>(const component1<E>& v);

		template<int E>
		components<X>& operator = (const component1<E>& v);
		components<X>& operator = (float f);
		components<X>& operator = (const floatN<1>& v);
		components<X>& operator = (const floatNxM<1, 1>& m);

		hlslpp_inline operator float() const
		{
			return _f32[X];
		}
	};

	template<int X, int Y>
	class components<X, Y>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
		};

		hlslpp_inline void staticAsserts()
		{
			// Assert that no component is equal to each other for assignment
			static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		hlslpp_inline static n128 blend(n128 x, n128 y)
		{
			return _hlslpp_blend_ps(x, y, HLSLPP_COMPONENT_XY(X, Y)); // Select based on property mask
		}

		template<int E, int F, int A, int B>
		hlslpp_inline static n128 swizzle(n128 x)
		{
			const int mask = HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_W);
			const uint32_t reshuffledMask = (((mask >> (2 * E)) & 3) << (2 * A)) | (((mask >> (2 * F)) & 3) << (2 * B)) | (mask & ~((3 << 2 * A) | (3 << 2 * B)));
			const n128 inputShuffle = _hlslpp_perm_ps(x, reshuffledMask); // Swizzle input mask with property mask
			return inputShuffle;
		}
	
		components<X, Y>() {}
		hlslpp_inline explicit components<X, Y>(n128 vec) : _vec(vec) {}
		template<int E, int F>
		explicit components<X, Y>(const component2<E, F>& c);

		template<int E, int F>
		components<X, Y>& operator = (const component2<E, F>& c);
		components<X, Y>& operator = (const component2<X, Y>& c);
		components<X, Y>& operator = (const floatN<2>& v);
	};

	template<int X, int Y, int Z>
	class components<X, Y, Z>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
		};

		hlslpp_inline void staticAsserts()
		{
			// Assert that no component is equal to each other for assignment
			static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		hlslpp_inline static n128 blend(n128 x, n128 y)
		{
			return _hlslpp_blend_ps(x, y, HLSLPP_COMPONENT_XYZ(X, Y, Z));							// Select based on property mask
		}

		template<int E, int F, int G, int A, int B, int C>
		hlslpp_inline static n128 swizzle(n128 x)
		{
			static const int mask = HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_W);
			const uint32_t reshuffledMask = (((mask >> (2 * E)) & 0x3) << (2 * A)) | (((mask >> (2 * F)) & 0x3) << (2 * B)) | (((mask >> (2 * G)) & 0x3) << (2 * C)) | (mask & ~((3 << 2 * A) | (3 << 2 * B) | (3 << 2 * C)));
			n128 inputShuffle = _hlslpp_perm_ps(x, reshuffledMask);	// Swizzle input mask with property mask
			return inputShuffle;
		}

		components<X, Y, Z>() {}
		hlslpp_inline explicit components<X, Y, Z>(n128 vec) : _vec(vec) {}
		template<int E, int F, int G>
		explicit components<X, Y, Z>(const component3<E, F, G>& c);

		template<int E, int F, int G>
		components<X, Y, Z>& operator = (const component3<E, F, G>& c);
		components<X, Y, Z>& operator = (const component3<X, Y, Z>& c);
		components<X, Y, Z>& operator = (const floatN<3>& v);
	};

	template<int X, int Y, int Z, int W>
	class components<X, Y, Z, W>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
		};

		hlslpp_inline void staticAsserts()
		{
			// Assert that no component is equal to each other for assignment
			static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		components<X, Y, Z, W>() {}
		hlslpp_inline explicit components<X, Y, Z, W>(n128 vec) : _vec(vec) {}
		template<int E, int F, int G, int H>
		explicit inline components<X, Y, Z, W>(const component4<E, F, G, H>& c);

		template<int E, int F, int G, int H>
		inline components<X, Y, Z, W>& operator = (const component4<E, F, G, H>& c);
		inline components<X, Y, Z, W>& operator = (const component4<X, Y, Z, W>& c);
		inline components<X, Y, Z, W>& operator = (const floatN<4>& v);
	};

	//----- float1

	template<>
	class floatN<1>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
			#include "swizzle/hlsl++_vector_float_x.h"
			#include "swizzle/hlsl++_vector_float_r.h"
		};

		hlslpp_inline explicit floatN<1>(n128 vec) : _vec(vec) {}
		hlslpp_inline floatN<1>() {}
		hlslpp_inline floatN<1>(float f) : _vec(_hlslpp_set_ps(f, 0.0f, 0.0f, 0.0f)) {}
		hlslpp_inline floatN<1>(const floatN<1>& v) : _vec(v._vec) {}

		// intN/icomponentN constructors

		template<int N, enable_if_dim<(N == 1)> = nullptr> hlslpp_inline floatN<1>(const intN<N>& v) { _vec = _hlslpp_cvtepi32_ps(v._vec); }

		template<int A> hlslpp_inline floatN<1>(const icomponent1<A>& c) { _vec = _hlslpp_cvtepi32_ps(_hlslpp_shuffle_epi32(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(A, A, A, A))); }

		template<int A> hlslpp_inline floatN<1>(const component1<A>& c) { _vec = _hlslpp_shuffle_ps(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(A, A, A, A)); }

		template<int N, enable_if_dim<(N == 1)> = nullptr> hlslpp_inline explicit floatN<1>(const floatNxM<N, N>& v) { _vec = v._vec; }

		// Assignment operators

		hlslpp_inline floatN<1>& operator = (float f) { _vec = _hlslpp_set_ps(f, 0.0f, 0.0f, 0.0f); return *this; }

		hlslpp_inline floatN<1>& operator = (const floatN<1>& v) { _vec = v._vec; return *this; }

		template<int A> hlslpp_inline floatN<1>& operator = (const component1<A>& c) { _vec = _hlslpp_shuffle_ps(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(A, A, A, A)); return *this; }

		template<int A> hlslpp_inline floatN<1>& operator = (const icomponent1<A>& c) { _vec = _hlslpp_cvtepi32_ps(_hlslpp_shuffle_epi32(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(A, A, A, A))); return *this; }

		template<int N, enable_if_dim<(N == 1)> = nullptr> hlslpp_inline floatN<1>& operator = (const floatNxM<N, N>& m) { _vec = m._vec; return *this; }

		template<int N, enable_if_dim<(N == 1)> = nullptr> hlslpp_inline floatN<1>& operator = (const intN<N>& i) { _vec = _hlslpp_cvtepi32_ps(i._vec); return *this; }

		hlslpp_inline operator float() const { return _f32[0]; }
	};

	// Explicit specialization when A == 0 to avoid swizzle
	template<> hlslpp_inline floatN<1>::floatN(const component1<0>& c) { _vec = c._vec; }
	template<> hlslpp_inline floatN<1>& floatN<1>::operator = (const component1<0>& c) { _vec = c._vec; return *this; }

	//----- float2

	template<>
	class floatN<2>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
			#include "swizzle/hlsl++_vector_float_x.h"
			#include "swizzle/hlsl++_vector_float_r.h"
			#include "swizzle/hlsl++_vector_float_y.h"
			#include "swizzle/hlsl++_vector_float_g.h"
		};

		hlslpp_inline explicit floatN<2>(n128 vec) : _vec(vec) {}
		hlslpp_inline floatN<2>() {}
		hlslpp_inline floatN<2>(float f) : _vec(_hlslpp_set_ps(f, f, 0.0f, 0.0f)) {}
		hlslpp_inline floatN<2>(float x, float y) : _vec(_hlslpp_set_ps(x, y, 0.0f, 0.0f)) {}
		hlslpp_inline floatN<2>(const floatN<2>& v) : _vec(v._vec) {}
		hlslpp_inline floatN<2>(const floatN<1>& v1, const floatN<1>& v2) { _vec = _hlslpp_blend_ps(v1._vec, _hlslpp_perm_xxxx_ps(v2._vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }
	
		template<int N, int M, enable_if_dim<((N == 2) && (M == 1)) || ((N == 1) && (M == 2))> = nullptr> hlslpp_inline explicit floatN<2>(const floatNxM<N, M>& v) { _vec = v._vec; }

		// intN/icomponentN constructors
		template<int N, enable_if_dim<(N == 2)> = nullptr> hlslpp_inline floatN<2>(const intN<N>& v) { _vec = _hlslpp_cvtepi32_ps(v._vec); }
		template<int A, int B> hlslpp_inline floatN<2>(const icomponent2<A, B>& c) { _vec = _hlslpp_cvtepi32_ps((icomponent2<A, B>::template swizzle<A, B, 0, 1>(c._vec))); }

		// floatN constructors
		hlslpp_inline floatN<2>(const floatN<1>& v1, const float v2)                                     : floatN<2>(v1, floatN<1>(v2)) {}
		hlslpp_inline floatN<2>(const float v1,      const floatN<1>& v2)                                : floatN<2>(floatN<1>(v1), v2) {}
		template<int A> hlslpp_inline floatN<2>(const component1<A>& v1,        const floatN<1>& v2)     : floatN<2>(floatN<1>(v1), v2) {}
		template<int A> hlslpp_inline floatN<2>(const floatN<1>& v1,            const component1<A>& v2) : floatN<2>(v1, floatN<1>(v2)) {}
		template<int A> hlslpp_inline floatN<2>(const component1<A>& v1,        const float v2)          : floatN<2>(floatN<1>(v1), floatN<1>(v2)) {}
		template<int A> hlslpp_inline floatN<2>(const float v1,                 const component1<A>& v2) : floatN<2>(floatN<1>(v1), floatN<1>(v2)) {}
		template<int A, int B> hlslpp_inline floatN<2>(const component1<A>& v1, const component1<B>& v2) : floatN<2>(floatN<1>(v1), floatN<1>(v2)) {}

		template<int A, int B> hlslpp_inline floatN<2>(const component2<A, B>& c) { _vec = component2<A, B>::template swizzle<A, B, 0, 1>(c._vec); }

		hlslpp_inline floatN<2>& operator = (const floatN<2>& v) { _vec = v._vec; return *this; }
		hlslpp_inline floatN<2>& operator = (const float f);

		template<int A, int B> hlslpp_inline floatN<2>& operator = (const component2<A, B>& c) { _vec = component2<A, B>::template swizzle<A, B, 0, 1>(c._vec); return *this; }
		template<int A, int B> hlslpp_inline floatN<2>& operator = (const icomponent2<A, B>& c) { _vec = _hlslpp_cvtepi32_ps((icomponent2<A, B>::template swizzle<A, B, 0, 1>(c._vec))); return *this; }

		hlslpp_inline static const floatN<2>& one() { static const floatN<2> one = floatN<2>(1.0f, 1.0f); return one; };
		hlslpp_inline static const floatN<2>& zero() { static const floatN<2> zero = floatN<2>(0.0f, 0.0f); return zero; };
	};

	template<> hlslpp_inline floatN<2>::floatN(const component2<0, 1>& c) { _vec = c._vec; }

	template<> hlslpp_inline floatN<2>& floatN<2>::operator = (const component2<0, 1>& c) { _vec = c._vec; return *this; }

	//----- float3

	template<>
	class floatN<3>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
			#include "swizzle/hlsl++_vector_float_x.h"
			#include "swizzle/hlsl++_vector_float_y.h"
			#include "swizzle/hlsl++_vector_float_z.h"
			#include "swizzle/hlsl++_vector_float_r.h"
			#include "swizzle/hlsl++_vector_float_g.h"
			#include "swizzle/hlsl++_vector_float_b.h"
		};

		hlslpp_inline explicit floatN<3>(n128 vec) : _vec(vec) {}
		hlslpp_inline floatN<3>() {}
		hlslpp_inline floatN<3>(float f) : _vec(_hlslpp_set_ps(f, f, f, 0.0f)) {}
		hlslpp_inline floatN<3>(const floatN<3>& v) : _vec(v._vec) {}
		hlslpp_inline floatN<3>(const float x, const float y, const float z) : _vec(_hlslpp_set_ps(x, y, z, 0.0f)) {}

		template<int N, enable_if_dim<(N == 3)> = nullptr> hlslpp_inline floatN<3>(const intN<N>& v) { _vec = _hlslpp_cvtepi32_ps(v._vec); }
		template<int A, int B, int C> hlslpp_inline floatN<3>(const icomponent3<A, B, C>& c) { _vec = _hlslpp_cvtepi32_ps((icomponent3<A, B, C>::template swizzle<A, B, C, 0, 1, 2>(c._vec))); }

		// floatN constructors
		hlslpp_inline floatN<3>(const floatN<1>& v1, const floatN<1>& v2, const floatN<1>& v3) { _vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(v1._vec, v3._vec), _hlslpp_perm_xxxx_ps(v2._vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }
		hlslpp_inline floatN<3>(const floatN<2>& v1, const floatN<1>& v2)                      { _vec = _hlslpp_shuf_xyxx_ps(v1._vec, v2._vec); }
		hlslpp_inline floatN<3>(const floatN<1>& v1, const floatN<2>& v2)                      { _vec = _hlslpp_blend_ps(v1._vec, _hlslpp_perm_xxyx_ps(v2._vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }

		// componentN constructors
		template<int A, int B, int C> hlslpp_inline floatN<3>(const component1<A>& v1,    const component1<B>& v2, const component1<C>& v3) : floatN<3>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3)) {}
		template<int A, int B, int C> hlslpp_inline floatN<3>(const component2<A, B>& v1, const component1<C>& v2)    : floatN<3>(floatN<2>(v1), floatN<1>(v2)) {}
		template<int A, int B, int C> hlslpp_inline floatN<3>(const component1<A>& v1,    const component2<B, C>& v2) : floatN<3>(floatN<1>(v1), floatN<2>(v2)) {}
		template<int A, int B, int C> hlslpp_inline floatN<3>(const component3<A, B, C>& c) { _vec = component3<A, B, C>::template swizzle<A, B, C, 0, 1, 2>(c._vec); }

		// floatN + float constructors
		hlslpp_inline floatN<3>(const float v1,      const floatN<1>& v2, const floatN<1>& v3) : floatN<3>(floatN<1>(v1), v2, v3) {}
		hlslpp_inline floatN<3>(const floatN<1>& v1, const float v2,      const floatN<1>& v3) : floatN<3>(v1, floatN<1>(v2), v3) {}
		hlslpp_inline floatN<3>(const floatN<1>& v1, const floatN<1>& v2, const float v3)      : floatN<3>(v1, v2, floatN<1>(v3)) {}
		hlslpp_inline floatN<3>(const float v1,      const float v2,      const floatN<1>& v3) : floatN<3>(floatN<2>(v1, v2), v3) {}
		hlslpp_inline floatN<3>(const floatN<1>& v1, const float v2,      const float v3)      : floatN<3>(v1, floatN<2>(v2, v3)) {}
		hlslpp_inline floatN<3>(const float v1,      const floatN<1>& v2, const float v3)      : floatN<3>(floatN<1>(v1), v2, floatN<1>(v3)) {}
		hlslpp_inline floatN<3>(const float v1,      const floatN<2>& v2)                      : floatN<3>(floatN<1>(v1), v2) {}
		hlslpp_inline floatN<3>(const floatN<2>& v1, const float v2)                           : floatN<3>(v1, floatN<1>(v2)) {}

		// floatN + componentN constructors
		template<int A> hlslpp_inline floatN<3>(const floatN<1>& v1,     const floatN<1>& v2,     const component1<A>& v3) : floatN<3>(v1, v2, floatN<1>(v3)) {}
		template<int A> hlslpp_inline floatN<3>(const floatN<1>& v1,     const component1<A>& v2, const floatN<1>& v3)     : floatN<3>(v1, floatN<1>(v2), v3) {}
		template<int A> hlslpp_inline floatN<3>(const component1<A>& v1, const floatN<1>& v2,     const floatN<1>& v3)     : floatN<3>(floatN<1>(v1), v2, v3) {}

		template<int A, int B> hlslpp_inline floatN<3>(const floatN<1>& v1,     const component1<A>& v2, const component1<B>& v3) : floatN<3>(v1, floatN<1>(v2), floatN<1>(v3)) {}
		template<int A, int B> hlslpp_inline floatN<3>(const component1<A>& v1, const floatN<1>& v2,     const component1<B>& v3) : floatN<3>(floatN<1>(v1), v2, floatN<1>(v3)) {}
		template<int A, int B> hlslpp_inline floatN<3>(const component1<A>& v1, const component1<B>& v2, const floatN<1>& v3)     : floatN<3>(floatN<1>(v1), floatN<1>(v2), v3) {}

		template<int A, int B> hlslpp_inline floatN<3>(const floatN<1>& v1, const component2<A, B>& v2) : floatN<3>(v1, floatN<2>(v2)) {}
		template<int A, int B> hlslpp_inline floatN<3>(const component2<A, B>& v1, const floatN<1>& v2) : floatN<3>(floatN<2>(v1), v2) {}

		// float + componentN constructors
		template<int A> hlslpp_inline floatN<3>(const float v1, const float v2, const component1<A>& v3) : floatN<3>(floatN<2>(v1, v2), floatN<1>(v3)) {}
		template<int A> hlslpp_inline floatN<3>(const float v1, const component1<A>& v2, const float v3) : floatN<3>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3)) {}
		template<int A> hlslpp_inline floatN<3>(const component1<A>& v1, const float v2, const float v3) : floatN<3>(floatN<1>(v1), floatN<2>(v2, v3)) {}

		template<int A, int B> hlslpp_inline floatN<3>(const float v1, const component1<A>& v2, const component1<B>& v3) : floatN<3>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3)) {}
		template<int A, int B> hlslpp_inline floatN<3>(const component1<A>& v1, const float v2, const component1<B>& v3) : floatN<3>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3)) {}
		template<int A, int B> hlslpp_inline floatN<3>(const component1<A>& v1, const component1<B>& v2, const float v3) : floatN<3>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3)) {}

		template<int A, int B> hlslpp_inline floatN<3>(const float v1, const component2<A, B>& v2) : floatN<3>(floatN<1>(v1), floatN<2>(v2)) {}
		template<int A, int B> hlslpp_inline floatN<3>(const component2<A, B>& v1, const float v2) : floatN<3>(floatN<2>(v1), floatN<1>(v2)) {}

		// floatN + componentN + float constructors
		template<int A> hlslpp_inline floatN<3>(const floatN<1>& v1, const component1<A>& v2, const float v3)          : floatN<3>(v1, floatN<1>(v2), floatN<1>(v3)) {}
		template<int A> hlslpp_inline floatN<3>(const floatN<1>& v1, const float v2,          const component1<A>& v3) : floatN<3>(v1, floatN<1>(v2), floatN<1>(v3)) {}

		template<int A> hlslpp_inline floatN<3>(const float v1, const floatN<1>& v2,     const component1<A>& v3) : floatN<3>(floatN<1>(v1), v2, floatN<1>(v3)) {}
		template<int A> hlslpp_inline floatN<3>(const float v1, const component1<A>& v2, const floatN<1>& v3)     : floatN<3>(floatN<1>(v1), floatN<1>(v2), v3) {}

		template<int A> hlslpp_inline floatN<3>(const component1<A>& v1, const floatN<1>& v2, const float v3)      : floatN<3>(floatN<1>(v1), v2, floatN<1>(v3)) {}
		template<int A> hlslpp_inline floatN<3>(const component1<A>& v1, const float v2,      const floatN<1>& v3) : floatN<3>(floatN<1>(v1), floatN<1>(v2), v3) {}

		// floatNxM constructors
		template<int N, int M, enable_if_dim<((N == 3) && (M == 1)) || ((N == 1) && (M == 3))> = nullptr> hlslpp_inline explicit floatN<3>(const floatNxM<N, M>& v) { _vec = v._vec; }

		hlslpp_inline floatN<3>& operator = (const floatN<3>& v) { _vec = v._vec; return *this; }
		hlslpp_inline floatN<3>& operator = (const float f);
		template<int A, int B, int C> hlslpp_inline floatN<3>& operator = (const component3<A, B, C>& c) { _vec = component3<A, B, C>::template swizzle<A, B, C, 0, 1, 2>(c._vec); return *this; }
		template<int A, int B, int C> hlslpp_inline floatN<3>& operator = (const icomponent3<A, B, C>& c) { _vec = _hlslpp_cvtepi32_ps((icomponent3<A, B, C>::template swizzle<A, B, C, 0, 1, 2>(c._vec))); return *this; }

		hlslpp_inline static const floatN<3>& one() { static const floatN<3> one = floatN<3>(1.0f, 1.0f, 1.0f); return one; };
		hlslpp_inline static const floatN<3>& zero() { static const floatN<3> zero = floatN<3>(0.0f, 0.0f, 0.0f); return zero; };

		// Disallow these constructors, as implicit construction rules could allow them to be valid
		floatN<3>(float v1, float v2) = delete;
	};

	template<> hlslpp_inline floatN<3>::floatN(const component3<0, 1, 2>& c) { _vec = c._vec; }
	template<> hlslpp_inline floatN<3>& floatN<3>::operator = (const component3<0, 1, 2>& c) { _vec = c._vec; return *this; }

	template<>
	class floatN<4>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
			#include "swizzle/hlsl++_vector_float_x.h"
			#include "swizzle/hlsl++_vector_float_y.h"
			#include "swizzle/hlsl++_vector_float_z.h"
			#include "swizzle/hlsl++_vector_float_w.h"
			#include "swizzle/hlsl++_vector_float_r.h"
			#include "swizzle/hlsl++_vector_float_g.h"
			#include "swizzle/hlsl++_vector_float_b.h"
			#include "swizzle/hlsl++_vector_float_a.h"
		};

		hlslpp_inline explicit floatN<4>(n128 vec) : _vec(vec) {}
		hlslpp_inline floatN<4>() {}
		hlslpp_inline floatN<4>(float f) : _vec(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatN<4>(float x, float y, float z, float w) : _vec(_hlslpp_set_ps(x, y, z, w)) {}
	
		// intN/icomponent constructors
		template<int N, enable_if_dim<(N == 4)> = nullptr> floatN<4>(const intN<N>& v) { _vec = _hlslpp_cvtepi32_ps(v._vec); }
		template<int A, int B, int C, int D> floatN<4>(const icomponent4<A, B, C, D>& c) { _vec = _hlslpp_cvtepi32_ps(_hlslpp_shuffle_epi32(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(A, B, C, D))); }

		// floatN constructors
		hlslpp_inline floatN<4>(const floatN<4>& v) : _vec(v._vec) {}
		floatN<4>(const floatN<1>& v1, const floatN<1>& v2, const floatN<1>& v3, const floatN<1>& v4) { _vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(v1._vec, v3._vec), _hlslpp_shuf_xxxx_ps(v2._vec, v4._vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }
		floatN<4>(const floatN<2>& v1, const floatN<1>& v2, const floatN<1>& v3) { _vec = _hlslpp_blend_ps(_hlslpp_shuf_xyxx_ps(v1._vec, v2._vec), _hlslpp_perm_xxxx_ps(v3._vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }
		floatN<4>(const floatN<1>& v1, const floatN<2>& v2, const floatN<1>& v3) { _vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(v1._vec, v3._vec), _hlslpp_perm_xxyx_ps(v2._vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }
		floatN<4>(const floatN<1>& v1, const floatN<1>& v2, const floatN<2>& v3) { _vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxy_ps(v1._vec, v3._vec), _hlslpp_perm_xxxx_ps(v2._vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }
		floatN<4>(const floatN<2>& v1, const floatN<2>& v2) { _vec = _hlslpp_shuf_xyxy_ps(v1._vec, v2._vec); }
		floatN<4>(const floatN<1>& v1, const floatN<3>& v2) { _vec = _hlslpp_blend_ps(v1._vec, _hlslpp_perm_xxyz_ps(v2._vec), HLSLPP_BLEND_MASK(1, 0, 0, 0)); }
		floatN<4>(const floatN<3>& v1, const floatN<1>& v2) { _vec = _hlslpp_blend_ps(v1._vec, _hlslpp_perm_xxxx_ps(v2._vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }

		// componentN constructors
		template<int A, int B, int C, int D> hlslpp_inline floatN<4>(const component1<A>& v1, const component1<B>& v2, const component1<C>& v3, const component1<D>& v4) : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v2), floatN<1>(v2)) {}
		template<int A, int B, int C, int D> floatN<4>(const component4<A, B, C, D>& c) { *this = c; }

		// floatN + float constructors
		hlslpp_inline floatN<4>(const float v1,      const floatN<1>& v2, const floatN<1>& v3, const floatN<1>& v4) : floatN<4>(floatN<1>(v1), v2, v3, v4) {}
		hlslpp_inline floatN<4>(const floatN<1>& v1, const float v2,      const floatN<1>& v3, const floatN<1>& v4) : floatN<4>(v1, floatN<1>(v2), v3, v4) {}
		hlslpp_inline floatN<4>(const floatN<1>& v1, const floatN<1>& v2, const float v3,      const floatN<1>& v4) : floatN<4>(v1, v2, floatN<1>(v3), v4) {}
		hlslpp_inline floatN<4>(const floatN<1>& v1, const floatN<1>& v2, const floatN<1>& v3, const float v4)      : floatN<4>(v1, v2, v3, floatN<1>(v4)) {}

		hlslpp_inline floatN<4>(const floatN<1>& v1, const float v2,      const float v3,      const float v4)      { _vec = _hlslpp_blend_ps(_hlslpp_set_ps(0.0f, v2, v3, v4), v1._vec, HLSLPP_BLEND_MASK(0, 1, 1, 1)); }
		hlslpp_inline floatN<4>(const float v1,      const floatN<1>& v2, const float v3,      const float v4)      { _vec = _hlslpp_blend_ps(_hlslpp_set_ps(v1, 0.0f, v3, v4), _hlslpp_perm_xxxx_ps(v2._vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }
		hlslpp_inline floatN<4>(const float v1,      const float v2,      const floatN<1>& v3, const float v4)      { _vec = _hlslpp_blend_ps(_hlslpp_set_ps(v1, v2, 0.0f, v4), _hlslpp_perm_xxxx_ps(v3._vec), HLSLPP_BLEND_MASK(1, 1, 0, 1)); }
		hlslpp_inline floatN<4>(const float v1,      const float v2,      const float v3,      const floatN<1>& v4) { _vec = _hlslpp_blend_ps(_hlslpp_set_ps(v1, v2, v3, 0.0f), _hlslpp_perm_xxxx_ps(v4._vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }
	
		hlslpp_inline floatN<4>(const float v1,      const floatN<1>& v2, const floatN<1>& v3, const float v4)      { _vec = _hlslpp_blend_ps(_hlslpp_set_ps(v1, 0.0f, 0.0f, v4), _hlslpp_shuf_xxxx_ps(v2._vec, v3._vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }
		hlslpp_inline floatN<4>(const float v1,      const float v2,      const floatN<1>& v3, const floatN<1>& v4) { _vec = _hlslpp_blend_ps(_hlslpp_set_ps(v1, v2, 0.0f, 0.0f), _hlslpp_perm_xzxz_ps(_hlslpp_shuf_xxxx_ps(v3._vec, v4._vec)), HLSLPP_BLEND_MASK(1, 1, 0, 0)); }
		hlslpp_inline floatN<4>(const float v1,      const floatN<1>& v2, const float v3,      const floatN<1>& v4) { _vec = _hlslpp_blend_ps(_hlslpp_set_ps(v1, 0.0f, v3, 0.0f), _hlslpp_shuf_xxxx_ps(v2._vec, v4._vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }

		hlslpp_inline floatN<4>(const floatN<1>& v1, const float v2,      const float v3,      const floatN<1>& v4) { _vec = _hlslpp_blend_ps(_hlslpp_set_ps(0.0f, v2, v3, 0.0f), _hlslpp_shuf_xxxx_ps(v1._vec, v4._vec), HLSLPP_BLEND_MASK(0, 1, 1, 0)); }
		hlslpp_inline floatN<4>(const floatN<1>& v1, const floatN<1>& v2, const float v3,      const float v4)      { _vec = _hlslpp_blend_ps(_hlslpp_set_ps(0.0f, 0.0f, v3, v4), _hlslpp_perm_xzxz_ps(_hlslpp_shuf_xxxx_ps(v1._vec, v2._vec)), HLSLPP_BLEND_MASK(0, 0, 1, 1)); }
		hlslpp_inline floatN<4>(const floatN<1>& v1, const float v2,      const floatN<1>& v3, const float v4)      { _vec = _hlslpp_blend_ps(_hlslpp_set_ps(0.0f, v2, 0.0f, v4), _hlslpp_shuf_xxxx_ps(v1._vec, v3._vec), HLSLPP_BLEND_MASK(0, 1, 0, 1)); }

		hlslpp_inline floatN<4>(const floatN<2>& v1, const float v2,      const floatN<1>& v3) : floatN<4>(v1, floatN<1>(v2), v3) {}
		hlslpp_inline floatN<4>(const floatN<2>& v1, const floatN<1>& v2, const float v3)      : floatN<4>(v1, v2, floatN<1>(v3)) {}
		hlslpp_inline floatN<4>(const floatN<2>& v1, const float v2,      const float v3)      : floatN<4>(v1, v2, floatN<1>(v3)) {}

		hlslpp_inline floatN<4>(const float v1,      const floatN<2>& v2, const floatN<1>& v3) : floatN<4>(floatN<1>(v1), v2, v3) {}
		hlslpp_inline floatN<4>(const floatN<1>& v1, const floatN<2>& v2, const float v3)      : floatN<4>(v1, v2, floatN<1>(v3)) {}

		hlslpp_inline floatN<4>(const float v1,      const floatN<1>& v2, const floatN<2>& v3) : floatN<4>(floatN<1>(v1), v2, v3) {}
		hlslpp_inline floatN<4>(const floatN<1>& v1, const float v2,      const floatN<2>& v3) : floatN<4>(v1, floatN<1>(v2), v3) {}
		hlslpp_inline floatN<4>(const float v1,      const float v2,      const floatN<2>& v3) : floatN<4>(floatN<2>(v1, v2), v3) {}

		hlslpp_inline floatN<4>(const float v1,      const floatN<3>& v2) : floatN<4>(floatN<1>(v1), v2) {}
		hlslpp_inline floatN<4>(const floatN<3>& v1, const float v2)      : floatN<4>(v1, floatN<1>(v2)) {}

		// floatN + componentN constructors
		template<int A> hlslpp_inline floatN<4>(const component1<A>& v1, const floatN<1>& v2,     const floatN<1>& v3,     const floatN<1>& v4)     : floatN<4>(floatN<1>(v1), v2, v3, v4) {}
		template<int A> hlslpp_inline floatN<4>(const floatN<1>& v1,     const component1<A>& v2, const floatN<1>& v3,     const floatN<1>& v4)     : floatN<4>(v1, floatN<1>(v2), v3, v4) {}
		template<int A> hlslpp_inline floatN<4>(const floatN<1>& v1,     const floatN<1>& v2,     const component1<A>& v3, const floatN<1>& v4)     : floatN<4>(v1, v2, floatN<1>(v3), v4) {}
		template<int A> hlslpp_inline floatN<4>(const floatN<1>& v1,     const floatN<1>& v2,     const floatN<1>& v3,     const component1<A>& v4) : floatN<4>(v1, v2, v3, floatN<1>(v4)) {}

		template<int A, int B, int C> hlslpp_inline floatN<4>(const floatN<1>& v1,     const component1<A>& v2, const component1<B>& v3, const component1<C>& v4) : floatN<4>(v1, floatN<1>(v2), floatN<1>(v3), floatN<1>(v4)) {}
		template<int A, int B, int C> hlslpp_inline floatN<4>(const component1<A>& v1, const floatN<1>& v2,     const component1<B>& v3, const component1<C>& v4) : floatN<4>(floatN<1>(v1), v2, floatN<1>(v3), floatN<1>(v4)) {}
		template<int A, int B, int C> hlslpp_inline floatN<4>(const component1<A>& v1, const component1<B>& v2, const floatN<1>& v3,     const component1<C>& v4) : floatN<4>(floatN<1>(v1), floatN<1>(v2), v3, floatN<1>(v4)) {}
		template<int A, int B, int C> hlslpp_inline floatN<4>(const component1<A>& v1, const component1<B>& v2, const component1<C>& v3, const floatN<1>& v4)     : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3), v4) {}

		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const floatN<1>& v2,     const floatN<1>& v3,     const component1<B>& v4) : floatN<4>(floatN<1>(v1), v2, v3, floatN<1>(v4)) {}
		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const component1<B>& v2, const floatN<1>& v3,     const floatN<1>& v4)     : floatN<4>(floatN<1>(v1), floatN<1>(v2), v3, v4) {}
		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const floatN<1>& v2,     const component1<B>& v3, const floatN<1>& v4)     : floatN<4>(floatN<1>(v1), v2, floatN<1>(v3), v4) {}

		template<int A, int B> hlslpp_inline floatN<4>(const floatN<1>& v1, const component1<A>& v2, const component1<B>& v3, const floatN<1>& v4)     : floatN<4>(v1, floatN<1>(v2), floatN<1>(v3), v4) {}
		template<int A, int B> hlslpp_inline floatN<4>(const floatN<1>& v1, const floatN<1>& v2,     const component1<A>& v3, const component1<B>& v4) : floatN<4>(v1, v2, floatN<1>(v3), floatN<1>(v4)) {}
		template<int A, int B> hlslpp_inline floatN<4>(const floatN<1>& v1, const component1<A>& v2, const floatN<1>& v3,     const component1<B>& v4) : floatN<4>(v1, floatN<1>(v2), v3, floatN<1>(v4)) {}

		template<int A>        hlslpp_inline floatN<4>(const floatN<2>& v1, const component1<A>& v2, const floatN<1>& v3)     : floatN<4>(v1, floatN<1>(v2), v3) {}
		template<int A>        hlslpp_inline floatN<4>(const floatN<2>& v1, const floatN<1>& v2,     const component1<A>& v3) : floatN<4>(v1, v2, floatN<1>(v3)) {}
		template<int A, int B> hlslpp_inline floatN<4>(const floatN<2>& v1, const component1<A>& v2, const component1<B>& v3) : floatN<4>(v1, v2, floatN<1>(v3)) {}

		template<int A> hlslpp_inline floatN<4>(const component1<A>& v1, const floatN<2>& v2, const floatN<1>& v3)     : floatN<4>(floatN<1>(v1), v2, v3) {}
		template<int A> hlslpp_inline floatN<4>(const floatN<1>& v1,     const floatN<2>& v2, const component1<A>& v3) : floatN<4>(v1, v2, floatN<1>(v3)) {}

		template<int A>        hlslpp_inline floatN<4>(const floatN<1>& v1,     const component1<A>& v2, const floatN<2>& v3) : floatN<4>(v1, floatN<1>(v2), v3) {}
		template<int A>        hlslpp_inline floatN<4>(const component1<A>& v1, const floatN<1>& v2,     const floatN<2>& v3) : floatN<4>(floatN<1>(v1), v2, v3) {}
		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const component1<B>& v2, const floatN<2>& v3) : floatN<4>(floatN<1>(v1), floatN<1>(v2), v3) {}

		template<int A> hlslpp_inline floatN<4>(const component1<A>& v1, const floatN<3>& v2)     : floatN<4>(floatN<1>(v1), v2) {}
		template<int A> hlslpp_inline floatN<4>(const floatN<3>& v1,     const component1<A>& v2) : floatN<4>(v1, floatN<1>(v2)) {}

		// componentN + float constructors
		template<int A> hlslpp_inline floatN<4>(const component1<A>& v1, const float v2,          const float v3,          const float v4)          : floatN<4>(floatN<1>(v1), floatN<3>(v2, v3, v4)) {}
		template<int A> hlslpp_inline floatN<4>(const float v1,          const component1<A>& v2, const float v3,          const float v4)          : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<2>(v3, v4)) {}
		template<int A> hlslpp_inline floatN<4>(const float v1,          const float v2,          const component1<A>& v3, const float v4)          : floatN<4>(floatN<2>(v1, v2), floatN<1>(v3), floatN<1>(v4)) {}
		template<int A> hlslpp_inline floatN<4>(const float v1,          const float v2,          const float v3,          const component1<A>& v4) : floatN<4>(floatN<3>(v1, v2, v3), floatN<1>(v4)) {}

		template<int A, int B, int C> hlslpp_inline floatN<4>(const float v1,          const component1<A>& v2, const component1<B>& v3, const component1<C>& v4) : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3), floatN<1>(v4)) {}
		template<int A, int B, int C> hlslpp_inline floatN<4>(const component1<A>& v1, const float v2,          const component1<B>& v3, const component1<C>& v4) : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3), floatN<1>(v4)) {}
		template<int A, int B, int C> hlslpp_inline floatN<4>(const component1<A>& v1, const component1<B>& v2, const float v3,          const component1<C>& v4) : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3), floatN<1>(v4)) {}
		template<int A, int B, int C> hlslpp_inline floatN<4>(const component1<A>& v1, const component1<B>& v2, const component1<C>& v3, const float v4)          : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3), floatN<1>(v4)) {}

		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const float v2, const float v3, const component1<B>& v4) : floatN<4> (floatN<1> (v1), floatN<2> (v2, v3), floatN<1> (v4)) {}
		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const component1<B>& v2, const float v3, const float v4) : floatN<4> (floatN<1> (v1), floatN<1> (v2), floatN<2> (v3, v4)) {}
		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const float v2, const component1<B>& v3, const float v4) : floatN<4> (floatN<1> (v1), floatN<1> (v2), floatN<1> (v3), floatN<1> (v4)) {}

		template<int A, int B> hlslpp_inline floatN<4>(const float v1, const component1<A>& v2, const component1<B>& v3, const float v4)          : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3), floatN<1>(v4)) {}
		template<int A, int B> hlslpp_inline floatN<4>(const float v1, const float v2,          const component1<A>& v3, const component1<B>& v4) : floatN<4>(floatN<2>(v1, v2), floatN<1>(v3), floatN<1>(v4)) {}
		template<int A, int B> hlslpp_inline floatN<4>(const float v1, const component1<A>& v2, const float v3,          const component1<B>& v4) : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3), floatN<1>(v4)) {}


		template<int A, int B> hlslpp_inline floatN<4>(const component2<A, B>& v1, const float v2,             const float v3)             : floatN<4>(floatN<2>(v1), floatN<1>(v2), floatN<1>(v3)) {}
		template<int A, int B> hlslpp_inline floatN<4>(const float v1,             const component2<A, B>& v2, const float v3)             : floatN<4>(floatN<1>(v1), floatN<2>(v2), floatN<1>(v3)) {}
		template<int A, int B> hlslpp_inline floatN<4>(const float v1,             const float v2,             const component2<A, B>& v3) : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<2>(v3)) {}

		template<int A, int B, int C> hlslpp_inline floatN<4>(const float v1, const component2<A, B>& v2, const component1<C>& v3)    : floatN<4>(floatN<1>(v1), floatN<2>(v2), floatN<1>(v3)) {}
		template<int A, int B, int C> hlslpp_inline floatN<4>(const float v1, const component1<A>& v2,    const component2<B, C>& v3) : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<2>(v3)) {}

		template<int A, int B, int C> hlslpp_inline floatN<4>(const component1<A>& v1, const component2<B, C>& v2, const float v3)             : floatN<4>(floatN<1>(v1), floatN<2>(v2), floatN<1>(v3)) {}
		template<int A, int B, int C> hlslpp_inline floatN<4>(const component1<A>& v1, const float v2,             const component2<B, C>& v3) : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<2>(v3)) {}

		template<int A, int B, int C> hlslpp_inline floatN<4>(const component2<A, B>& v1, const float v2,          const component1<C>& v3) : floatN<4>(floatN<2>(v1), floatN<1>(v2), floatN<1>(v3)) {}
		template<int A, int B, int C> hlslpp_inline floatN<4>(const component2<A, B>& v1, const component1<C>& v2, const float v3)          : floatN<4>(floatN<2>(v1), floatN<1>(v2), floatN<1>(v3)) {}

		template<int A, int B, int C> hlslpp_inline floatN<4>(const float v1,                const component3<A, B, C>& v2) : floatN<4>(floatN<1>(v1), floatN<3>(v2)) {}
		template<int A, int B, int C> hlslpp_inline floatN<4>(const component3<A, B, C>& v1, const float v2)                : floatN<4>(floatN<3>(v1), floatN<1>(v2)) {}

		// floatN + componentN + float constructors
		template<int A>        hlslpp_inline floatN<4>(const float v1, const component1<A>& v2, const floatN<1>& v3, const float v4)          : floatN<4>(floatN<1>(v1), floatN<1>(v2), v3, floatN<1>(v4)) {}
		template<int A>        hlslpp_inline floatN<4>(const float v1, const component1<A>& v2, const floatN<1>& v3, const floatN<1>& v4)     : floatN<4>(floatN<1>(v1), floatN<1>(v2), v3, v4) {}
		template<int A, int B> hlslpp_inline floatN<4>(const float v1, const component1<A>& v2, const floatN<1>& v3, const component1<B>& v4) : floatN<4>(floatN<1>(v1), floatN<1>(v2), v3, floatN<1>(v4)) {}

		template<int A>        hlslpp_inline floatN<4>(const float v1, const floatN<1>& v2, const component1<A>& v3, const float v4) : floatN<4>(floatN<1>(v1), v2, floatN<1>(v3), floatN<1>(v4)) {}
		template<int A>        hlslpp_inline floatN<4>(const float v1, const floatN<1>& v2, const component1<A>& v3, const floatN<1>& v4) : floatN<4>(floatN<1>(v1), v2, floatN<1>(v3), v4) {}
		template<int A, int B> hlslpp_inline floatN<4>(const float v1, const floatN<1>& v2, const component1<A>& v3, const component1<B>& v4) : floatN<4>(floatN<1>(v1), v2, floatN<1>(v3), floatN<1>(v4)) {}

		template<int A>        hlslpp_inline floatN<4>(const float v1, const float v2, const component1<A>& v3, const floatN<1>& v4) : floatN<4>(floatN<2>(v1, v2), floatN<1>(v3), v4) {}
		template<int A>        hlslpp_inline floatN<4>(const float v1, const float v2, const floatN<1>& v3, const component1<A>& v4) : floatN<4>(floatN<2>(v1, v2), v3, floatN<1>(v4)) {}

		template<int A, int B> hlslpp_inline floatN<4>(const float v1, const component1<A>& v2, const float v3,          const floatN<1>& v4) : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3), v4) {}
		template<int A, int B> hlslpp_inline floatN<4>(const float v1, const component1<A>& v2, const component1<B>& v3, const floatN<1>& v4) : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3), v4) {}

		template<int A>        hlslpp_inline floatN<4>(const float v1, const floatN<1>& v2, const floatN<1>& v3, const component1<A>& v4) : floatN<4>(floatN<1>(v1), v2, v3, floatN<1>(v4)) {}

		template<int A>        hlslpp_inline floatN<4>(const component1<A>& v1, const float v2, const floatN<1>& v3, const float v4)          : floatN<4>(floatN<1>(v1), v2, v3, floatN<1>(v4)) {}
		template<int A>        hlslpp_inline floatN<4>(const component1<A>& v1, const float v2, const floatN<1>& v3, const floatN<1>& v4)     : floatN<4>(floatN<1>(v1), floatN<1>(v2), v3, v4) {}
		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const float v2, const floatN<1>& v3, const component1<B>& v4) : floatN<4>(floatN<1>(v1), floatN<1>(v2), v3, floatN<1>(v4)) {}

		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const floatN<1>& v2, const float v3, const float v4)          : floatN<4>(floatN<1>(v1), v2, floatN<1>(v3), floatN<1>(v4)) {}
		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const floatN<1>& v2, const float v3, const floatN<1>& v4)     : floatN<4>(floatN<1>(v1), v2, floatN<1>(v3), v4) {}
		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const floatN<1>& v2, const float v3, const component1<B>& v4) : floatN<4>(floatN<1>(v1), v2, floatN<1>(v3), floatN<1>(v4)) {}

		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const component1<B>& v2, const floatN<1>& v3, const float v4) : floatN<4>(floatN<1>(v1), floatN<1>(v2), v3, floatN<1>(v4)) {}
		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const component1<B>& v2, const float v3, const floatN<1>& v4) : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3), v4) {}

		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const floatN<1>& v2, const component1<B>& v3, const float v4) : floatN<4>(floatN<1>(v1), v2, floatN<1>(v3), floatN<1>(v4)) {}
		template<int A>        hlslpp_inline floatN<4>(const component1<A>& v1, const floatN<1>& v2, const float v3, const floatN<1>& v4)     : floatN<4>(floatN<1>(v1), v2, floatN<1>(v3), v4) {}

		template<int A, int B> hlslpp_inline floatN<4>(const component1<A>& v1, const float v2, const component1<B>& v3, const floatN<1>& v4) : floatN<4>(floatN<1>(v1), floatN<1>(v2), floatN<1>(v3), v4) {}

		template<int A>        hlslpp_inline floatN<4>(const floatN<1>& v1, const component1<A>& v2, const float v3, const float v4)          : floatN<4>(v1, floatN<1>(v2), floatN<1>(v3), floatN<1>(v4)) {}
		template<int A>        hlslpp_inline floatN<4>(const floatN<1>& v1, const component1<A>& v2, const float v3, const floatN<1>& v4)     : floatN<4>(v1, floatN<1>(v2), floatN<1>(v3), v4) {}
		template<int A, int B> hlslpp_inline floatN<4>(const floatN<1>& v1, const component1<A>& v2, const float v3, const component1<B>& v4) : floatN<4>(v1, floatN<1>(v2), floatN<1>(v3), floatN<1>(v4)) {}

		template<int A>        hlslpp_inline floatN<4>(const floatN<1>& v1, const float v2, const component1<A>& v3, const float v4)          : floatN<4>(v1, floatN<1>(v2), floatN<1>(v3), floatN<1>(v4)) {}
		template<int A>        hlslpp_inline floatN<4>(const floatN<1>& v1, const float v2, const component1<A>& v3, const floatN<1>& v4)     : floatN<4>(v1, floatN<1>(v2), floatN<1>(v3), v4) {}
		template<int A, int B> hlslpp_inline floatN<4>(const floatN<1>& v1, const float v2, const component1<A>& v3, const component1<B>& v4) : floatN<4>(v1, floatN<1>(v2), floatN<1>(v3), floatN<1>(v4)) {}

		template<int A>        hlslpp_inline floatN<4>(const floatN<1>& v1, const floatN<1>& v2, const float v3, const component1<A>& v4) : floatN<4>(v1, v2, floatN<1>(v3), floatN<1>(v4)) {}
		template<int A>        hlslpp_inline floatN<4>(const floatN<1>& v1, const floatN<1>& v2, const component1<A>& v3, const float v4) : floatN<4>(v1, v2, floatN<1>(v3), floatN<1>(v4)) {}

		template<int A>        hlslpp_inline floatN<4>(const floatN<1>& v1, const float v2, const floatN<1>& v3, const component1<A>& v4) : floatN<4>(v1, floatN<1>(v2), v3, floatN<1>(v4)) {}
		template<int A>        hlslpp_inline floatN<4>(const floatN<1>& v1, const float v2, const float v3, const component1<A>& v4)      : floatN<4>(v1, floatN<1>(v2), floatN<1>(v3), floatN<1>(v4)) {}

		template<int A>        hlslpp_inline floatN<4>(const floatN<1>& v1, const component1<A>& v2, const floatN<1>& v3, const float v4)     : floatN<4>(v1, floatN<1>(v2), v3, floatN<1>(v4)) {}
		template<int A, int B> hlslpp_inline floatN<4>(const floatN<1>& v1, const component1<A>& v2, const component1<B>& v3, const float v4) : floatN<4>(v1, floatN<1>(v2), floatN<1>(v3), floatN<1>(v4)) {}

		template<int N, int M, enable_if_dim<(N == 4 && M == 1) || (N == 1 && M == 4)> = nullptr> hlslpp_inline explicit floatN<4>(const floatNxM<N, M>& v) { _vec = v._vec; }

		hlslpp_inline floatN<4>& operator = (const floatN<4>& v) { _vec = v._vec; return *this; }
		hlslpp_inline floatN<4>& operator = (const float f);
		template<int A, int B, int C, int D> hlslpp_inline floatN<4>& operator = (const component4<A, B, C, D>& c) { _vec = _hlslpp_shuffle_ps(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(A, B, C, D)); return *this; }
		template<int A, int B, int C, int D> floatN<4>& operator = (const icomponent4<A, B, C, D>& c) { _vec = _hlslpp_cvtepi32_ps(_hlslpp_shuffle_epi32(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(A, B, C, D))); return *this; }

		hlslpp_inline static const floatN<4>& one() { static const floatN<4> one = floatN<4>(1.0f, 1.0f, 1.0f, 1.0f); return one; };
		hlslpp_inline static const floatN<4>& zero() { static const floatN<4> zero = floatN<4>(0.0f, 0.0f, 0.0f, 0.0f); return zero; };

		// Disallow these constructors, as implicit construction rules could allow them to be valid
		floatN<4>(float v1, float v2) = delete;
		floatN<4>(float v1, float v2, float v3) = delete;
	};

	// Optimize straight copies if the indices match 0, 1, 2, 3 (doesn't produce/need the shuffle)
	template<> hlslpp_inline floatN<4>::floatN(const component4<0, 1, 2, 3>& c) { _vec = c._vec; }
	template<> hlslpp_inline floatN<4>& floatN<4>::operator = (const component4<0, 1, 2, 3>& c) { _vec = c._vec; return *this; }

	using float1 = floatN<1>;
	using float2 = floatN<2>;
	using float3 = floatN<3>;
	using float4 = floatN<4>;

	//--------------------
	// Integer class types
	//--------------------

	template<int X>
	class icomponents<X>
	{
	public:
		union
		{
			n128i _vec;
			int32_t _i32[4];
		};

		icomponents<X>() {}
		hlslpp_inline explicit icomponents<X>(n128i vec) : _vec(vec) {}
		hlslpp_inline explicit icomponents<X>(int32_t i) : _vec(_hlslpp_set_epi32(i, 0, 0, 0)) {}

		template<int E>
		explicit icomponents<X>(const icomponent1<E>& v);

		template<int E>
		icomponents<X>& operator = (const icomponent1<E>& v);
		icomponents<X>& operator = (int32_t i);
		icomponents<X>& operator = (const intN<1>& v);
		icomponents<X>& operator = (const intNxM<1, 1>& m);

		hlslpp_inline operator int32_t() const
		{
			return _i32[X];
		}
	};

	template<int X, int Y>
	class icomponents<X, Y>
	{
	public:
		union
		{
			n128i _vec;
			int32_t _i32[4];
		};

		hlslpp_inline void staticAsserts()
		{
			// Assert that no component is equal to each other for assignment
			static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		hlslpp_inline static n128i blend(n128i x, n128i y)
		{
			return _hlslpp_blend_epi32(x, y, HLSLPP_COMPONENT_XY(X, Y));									// Select based on property mask
		}

		template<int E, int F, int A, int B>
		hlslpp_inline static n128i swizzle(n128i x)
		{
			const int mask = HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_W);
			const uint32_t reshuffledMask = (((mask >> (2 * E)) & 3) << (2 * A)) | (((mask >> (2 * F)) & 3) << (2 * B)) | (mask & ~((3 << 2 * A) | (3 << 2 * B)));
			const n128i inputShuffle = _hlslpp_perm_epi32(x, reshuffledMask);	// Swizzle input mask with property mask
			return inputShuffle;
		}
	
		icomponents<X, Y>() {}
		hlslpp_inline explicit icomponents<X, Y>(n128i vec) : _vec(vec) {}
		template<int E, int F>
		explicit icomponents<X, Y>(const icomponent2<E, F>& c);

		template<int E, int F>
		icomponents<X, Y>& operator = (const icomponent2<E, F>& c);
		icomponents<X, Y>& operator = (const icomponent2<X, Y>& c);
		icomponents<X, Y>& operator = (const intN<2>& v);
	};

	template<int X, int Y, int Z>
	class icomponents<X, Y, Z>
	{
	public:
		union
		{
			n128i _vec;
			int32_t _i32[4];
		};

		hlslpp_inline void staticAsserts()
		{
			// Assert that no component is equal to each other for assignment
			static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		hlslpp_inline static n128i blend(n128i x, n128i y)
		{
			return _hlslpp_blend_epi32(x, y, HLSLPP_COMPONENT_XYZ(X, Y, Z));							// Select based on property mask
		}

		template<int E, int F, int G, int A, int B, int C>
		hlslpp_inline static n128i swizzle(n128i x)
		{
			static const int mask = HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_W);
			const uint32_t reshuffledMask = (((mask >> (2 * E)) & 0x3) << (2 * A)) | (((mask >> (2 * F)) & 0x3) << (2 * B)) | (((mask >> (2 * G)) & 0x3) << (2 * C)) | (mask & ~((3 << 2 * A) | (3 << 2 * B) | (3 << 2 * C)));
			n128i inputShuffle = _hlslpp_perm_epi32(x, reshuffledMask);	// Swizzle input mask with property mask
			return inputShuffle;
		}

		icomponents<X, Y, Z>() {}
		hlslpp_inline explicit icomponents<X, Y, Z>(n128i vec) : _vec(vec) {}
		template<int E, int F, int G>
		explicit icomponents<X, Y, Z>(const icomponent3<E, F, G>& c);

		template<int E, int F, int G>
		icomponents<X, Y, Z>& operator = (const icomponent3<E, F, G>& c);
		icomponents<X, Y, Z>& operator = (const icomponent3<X, Y, Z>& c);
		icomponents<X, Y, Z>& operator = (const intN<3>& v);
	};

	template<int X, int Y, int Z, int W>
	class icomponents<X, Y, Z, W>
	{
	public:
		union
		{
			n128i _vec;
			int32_t _i32[4];
		};

		hlslpp_inline void staticAsserts()
		{
			// Assert that no component is equal to each other for assignment
			static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		icomponents<X, Y, Z, W>() {}
		hlslpp_inline explicit icomponents<X, Y, Z, W>(n128i vec) : _vec(vec) {}
		template<int E, int F, int G, int H>
		explicit inline icomponents<X, Y, Z, W>(const icomponent4<E, F, G, H>& c);

		template<int E, int F, int G, int H>
		inline icomponents<X, Y, Z, W>& operator = (const icomponent4<E, F, G, H>& c);
		inline icomponents<X, Y, Z, W>& operator = (const icomponent4<X, Y, Z, W>& c);
		inline icomponents<X, Y, Z, W>& operator = (const intN<4>& v);
	};

	template<>
	class intN<1>
	{
	public:
		union
		{
			n128i _vec;
			#include "swizzle/hlsl++_vector_int_x.h"
			#include "swizzle/hlsl++_vector_int_r.h"
			int32_t _i32[4];
		};

		hlslpp_inline explicit intN<1>(n128i vec) : _vec(vec) {}
		intN<1>() {}
		hlslpp_inline intN<1>(int32_t i) : _vec(_hlslpp_set_epi32(i, 0, 0, 0)) {}
		hlslpp_inline intN<1>(const intN<1>& v) : _vec(v._vec) {}
		template<int A>
		intN<1>(const icomponent1<A>& c);
		explicit intN<1>(const intNxM<1, 1>& v);

		// Force compiler to instantiate this later as the template specialization hasn't yet taken place, while restricting the dimension
		template<int N, enable_if_dim<(N == 1)> = nullptr> intN<1>(const floatN<N>& v);

		intN<1>& operator = (int f);
		intN<1>& operator = (const intN<1>& c);
		template<int A>
		intN<1>& operator = (const icomponent1<A>& c);
		intN<1>& operator = (const intNxM<1, 1>& m);

		operator int32_t() const
		{
			return _i32[0];
		}
	};

	template<>
	class intN<2>
	{
	public:
		union
		{
			n128i _vec;
			#include "swizzle/hlsl++_vector_int_x.h"
			#include "swizzle/hlsl++_vector_int_r.h"
			#include "swizzle/hlsl++_vector_int_y.h"
			#include "swizzle/hlsl++_vector_int_g.h"
			int32_t _i32[4];
		};

		hlslpp_inline explicit intN<2>(n128i vec) : _vec(vec) {}
		intN<2>() {}
		hlslpp_inline intN<2>(int32_t i) : _vec(_hlslpp_set_epi32(i, i, 0, 0)) {}
		hlslpp_inline intN<2>(int32_t x, int32_t y) : _vec(_hlslpp_set_epi32(x, y, 0, 0)) {}
		hlslpp_inline intN<2>(const intN<2>& v) : _vec(v._vec) {}
		intN<2>(const intN<1>& v1,	const intN<1>& v2);
	
		explicit intN<2>(const intNxM<2, 1>& v);
		explicit intN<2>(const intNxM<1, 2>& v);

		// Force compiler to instantiate this later as the template specialization hasn't yet taken place, while restricting the dimension
		template<int N, enable_if_dim<(N == 2)> = nullptr> intN<2>(const floatN<N>& v);

		hlslpp_inline intN<2>(const intN<1>& v1,	const int32_t v2)	: intN<2>(v1, intN<1>(v2)) {}
		hlslpp_inline intN<2>(const int32_t v1,	const intN<1>& v2)		: intN<2>(intN<1>(v1), v2) {}
		template<int A> hlslpp_inline intN<2>(const icomponent1<A>& v1,	const intN<1>& v2)						: intN<2>(intN<1>(v1), v2) {}
		template<int A> hlslpp_inline intN<2>(const intN<1>& v1,			const icomponent1<A>& v2)			: intN<2>(v1, intN<1>(v2)) {}
		template<int A> hlslpp_inline intN<2>(const icomponent1<A>& v1,	const int32_t v2)					: intN<2>(intN<1>(v1), intN<1>(v2)) {}
		template<int A> hlslpp_inline intN<2>(const int32_t v1,			const icomponent1<A>& v2)			: intN<2>(intN<1>(v1), intN<1>(v2)) {}
		template<int A, int B> hlslpp_inline intN<2>(const icomponent1<A>& v1, const icomponent1<B>& v2)	: intN<2>(intN<1>(v1), intN<1>(v2)) {}

		template<int A, int B> intN<2>(const icomponent2<A, B>& c);

		intN<2>& operator = (const intN<2>& c);
		intN<2>& operator = (const int32_t i);

		template<int A, int B> intN<2>& operator = (const icomponent2<A, B>& c);
	};

	template<>
	class intN<3>
	{
	public:
		union
		{
			n128i _vec;
			#include "swizzle/hlsl++_vector_int_x.h"
			#include "swizzle/hlsl++_vector_int_y.h"
			#include "swizzle/hlsl++_vector_int_z.h"
			#include "swizzle/hlsl++_vector_int_r.h"
			#include "swizzle/hlsl++_vector_int_g.h"
			#include "swizzle/hlsl++_vector_int_b.h"
			int32_t _i32[4];
		};

		hlslpp_inline explicit intN<3>(n128i vec) : _vec(vec) {}
		hlslpp_inline intN<3>() {}
		hlslpp_inline intN<3>(int32_t i) : _vec(_hlslpp_set_epi32(i, i, i, 0)) {}
		hlslpp_inline intN<3>(const int32_t x, const int32_t y, const int32_t z) : _vec(_hlslpp_set_epi32(x, y, z, 0)) {}
		hlslpp_inline intN<3>(const intN<3>& v) : _vec(v._vec) {}

		// Force compiler to instantiate this later as the template specialization hasn't yet taken place, while restricting the dimension
		template<int N, enable_if_dim<(N == 3)> = nullptr> intN<3>(const floatN<N>& v);

		// intN constructors
		intN<3>(const intN<1>& v1,	const intN<1>& v2,	const intN<1>& v3);
		intN<3>(const intN<2>& v1,	const intN<1>& v2);
		intN<3>(const intN<1>& v1,	const intN<2>& v2);

		// icomponentN constructors
		template<int A, int B, int C> hlslpp_inline intN<3>(const icomponent1<A>& v1,		const icomponent1<B>& v2,	const icomponent1<C>& v3)	: intN<3>(intN<1>(v1), intN<1>(v2), intN<1>(v3)) {}
		template<int A, int B, int C> hlslpp_inline intN<3>(const icomponent2<A, B>& v1,	const icomponent1<C>& v2)								: intN<3>(intN<2>(v1), intN<1>(v2)) {}
		template<int A, int B, int C> hlslpp_inline intN<3>(const icomponent1<A>& v1,		const icomponent2<B, C>& v2)								: intN<3>(intN<1>(v1), intN<2>(v2)) {}
		template<int A, int B, int C> intN<3>(const icomponent3<A, B, C>& c);

		// intN + int32_t constructors
		intN<3>(const int32_t v1,	const intN<1>& v2,	const intN<1>& v3);
		intN<3>(const intN<1>& v1,	const int32_t v2,		const intN<1>& v3);
		intN<3>(const intN<1>& v1,	const intN<1>& v2,	const int32_t v3);
		intN<3>(const int32_t v1,	const int32_t v2,		const intN<1>& v3);
		intN<3>(const intN<1>& v1,	const int32_t v2,		const int32_t v3);
		intN<3>(const int32_t v1,	const intN<1>& v2,	const int32_t v3);
		intN<3>(const int32_t v1,	const intN<2>& v2)	: intN<3>(intN<1>(v1), v2) {}
		intN<3>(const intN<2>& v1, const int32_t v2)		: intN<3>(v1, intN<1>(v2)) {}

		// intN + icomponentN constructors
		template<int A> hlslpp_inline intN<3>(const intN<1>& v1,	const intN<1>& v2,			const icomponent1<A>& v3)	: intN<3>(v1, v2, intN<1>(v3)) {}
		template<int A> hlslpp_inline intN<3>(const intN<1>& v1,	const icomponent1<A>& v2,	const intN<1>& v3)			: intN<3>(v1, intN<1>(v2), v3) {}
		template<int A> hlslpp_inline intN<3>(const icomponent1<A>& v1,	const intN<1>& v2,	const intN<1>& v3)			: intN<3>(intN<1>(v1), v2, v3) {}

		template<int A, int B> hlslpp_inline intN<3>(const intN<1>& v1,			const icomponent1<A>& v2,	const icomponent1<B>& v3)	: intN<3>(v1, intN<1>(v2), intN<1>(v3)) {}
		template<int A, int B> hlslpp_inline intN<3>(const icomponent1<A>& v1,	const intN<1>& v2,			const icomponent1<B>& v3)	: intN<3>(intN<1>(v1), v2, intN<1>(v3)) {}
		template<int A, int B> hlslpp_inline intN<3>(const icomponent1<A>& v1,	const icomponent1<B>& v2,	const intN<1>& v3)			: intN<3>(intN<1>(v1), intN<1>(v2), v3) {}

		template<int A, int B> hlslpp_inline intN<3>(const intN<1>& v1,	const icomponent2<A, B>& v2)	: intN<3>(v1, intN<2>(v2)) {}
		template<int A, int B> hlslpp_inline intN<3>(const icomponent2<A, B>& v1, const intN<1>& v2)	: intN<3>(intN<2>(v1), v2) {}

		// int32_t + icomponentN constructors
		template<int A> hlslpp_inline intN<3>(const int32_t v1, const int32_t v2, const icomponent1<A>& v3) : intN<3>(intN<2>(v1, v2), intN<1>(v3)) {}
		template<int A> hlslpp_inline intN<3>(const int32_t v1, const icomponent1<A>& v2, const int32_t v3) : intN<3>(intN<1>(v1), intN<1>(v2), intN<1>(v3)) {}
		template<int A> hlslpp_inline intN<3>(const icomponent1<A>& v1, const int32_t v2, const int32_t v3) : intN<3>(intN<1>(v1), intN<2>(v2, v3)) {}

		template<int A, int B> hlslpp_inline intN<3>(const int32_t v1, const icomponent1<A>& v2, const icomponent1<B>& v3) : intN<3>(intN<1>(v1), intN<1>(v2), intN<1>(v3)) {}
		template<int A, int B> hlslpp_inline intN<3>(const icomponent1<A>& v1, const int32_t v2, const icomponent1<B>& v3) : intN<3>(intN<1>(v1), intN<1>(v2), intN<1>(v3)) {}
		template<int A, int B> hlslpp_inline intN<3>(const icomponent1<A>& v1, const icomponent1<B>& v2, const int32_t v3) : intN<3>(intN<1>(v1), intN<1>(v2), intN<1>(v3)) {}

		template<int A, int B> hlslpp_inline intN<3>(const int32_t v1, const icomponent2<A, B>& v2) : intN<3>(intN<1>(v1), intN<2>(v2)) {}
		template<int A, int B> hlslpp_inline intN<3>(const icomponent2<A, B>& v1, const int32_t v2) : intN<3>(intN<2>(v1), intN<1>(v2)) {}

		// intN + icomponentN + int32_t constructors
		template<int A> hlslpp_inline intN<3>(const intN<1>& v1,	const icomponent1<A>& v2,	const int32_t v3)				: intN<3>(v1, intN<1>(v2), intN<1>(v3)) {}
		template<int A> hlslpp_inline intN<3>(const intN<1>& v1,	const int32_t v2,				const icomponent1<A>& v3)	: intN<3>(v1, intN<1>(v2), intN<1>(v3)) {}

		template<int A> hlslpp_inline intN<3>(const int32_t v1,	const intN<1>& v2,			const icomponent1<A>& v3)	: intN<3>(intN<1>(v1), v2, intN<1>(v3)) {}
		template<int A> hlslpp_inline intN<3>(const int32_t v1,	const icomponent1<A>& v2,	const intN<1>& v3)			: intN<3>(intN<1>(v1), intN<1>(v2), v3) {}

		template<int A> hlslpp_inline intN<3>(const icomponent1<A>& v1,	const intN<1>& v2,	const int32_t v3)			: intN<3>(intN<1>(v1), v2, intN<1>(v3)) {}
		template<int A> hlslpp_inline intN<3>(const icomponent1<A>& v1,	const int32_t v2,		const intN<1>& v3)		: intN<3>(intN<1>(v1), intN<1>(v2), v3) {}

		explicit intN<3>(const intNxM<3, 1>& v);
		explicit intN<3>(const intNxM<1, 3>& v);

		intN<3>& operator = (const intN<3>& c);
		intN<3>& operator = (const int32_t f);
		template<int A, int B, int C>
		intN<3>& operator = (const icomponent3<A, B, C>& c);

		// Disallow these constructors, as implicit construction rules could allow them to be valid
		intN<3>(int32_t v1, int32_t v2) = delete;
	};

	template<>
	class intN<4>
	{
	public:
		union
		{
			n128i _vec;
			#include "swizzle/hlsl++_vector_int_x.h"
			#include "swizzle/hlsl++_vector_int_y.h"
			#include "swizzle/hlsl++_vector_int_z.h"
			#include "swizzle/hlsl++_vector_int_w.h"
			#include "swizzle/hlsl++_vector_int_r.h"
			#include "swizzle/hlsl++_vector_int_g.h"
			#include "swizzle/hlsl++_vector_int_b.h"
			#include "swizzle/hlsl++_vector_int_a.h"
			int32_t _i32[4];
		};

		hlslpp_inline explicit intN<4>(n128i vec) : _vec(vec) {}
		hlslpp_inline intN<4>() {}
		hlslpp_inline intN<4>(int32_t i) : _vec(_hlslpp_set1_epi32(i)) {}
		hlslpp_inline intN<4>(int32_t x, int32_t y, int32_t z, int32_t w) : _vec(_hlslpp_set_epi32(x, y, z, w)) {}

		// Force compiler to instantiate this later as the template specialization hasn't yet taken place, while restricting the dimension
		template<int N, enable_if_dim<(N == 4)> = nullptr> intN<4>(const floatN<N>& v);
	
		// intN constructors
		hlslpp_inline intN<4>(const intN<4>& v) : _vec(v._vec) {}
		intN<4>(const intN<1>& v1,	const intN<1>& v2,	const intN<1>& v3,	const intN<1>& v4);
		intN<4>(const intN<2>& v1,	const intN<1>& v2,	const intN<1>& v3);
		intN<4>(const intN<1>& v1,	const intN<2>& v2,	const intN<1>& v3);
		intN<4>(const intN<1>& v1,	const intN<1>& v2,	const intN<2>& v3);
		intN<4>(const intN<2>& v1,	const intN<2>& v2);
		intN<4>(const intN<1>& v1,	const intN<3>& v2);
		intN<4>(const intN<3>& v1,	const intN<1>& v2);

		// icomponentN constructors
		template<int A, int B, int C, int D> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const icomponent1<B>& v2,	const icomponent1<C>& v3,	const icomponent1<D>& v4) : intN<4>(intN<1>(v1), intN<1>(v2), intN<1>(v2), intN<1>(v2)) {}
		template<int A, int B, int C, int D> intN<4>(const icomponent4<A, B, C, D>& c);

		// intN + int32_t constructors
		hlslpp_inline intN<4>(const int32_t v1,		const intN<1>& v2,	const intN<1>& v3,	const intN<1>& v4)	: intN<4>(intN<1>(v1), v2, v3, v4) {}
		hlslpp_inline intN<4>(const intN<1>& v1,	const int32_t v2,		const intN<1>& v3,	const intN<1>& v4)	: intN<4>(v1, intN<1>(v2), v3, v4) {}
		hlslpp_inline intN<4>(const intN<1>& v1,	const intN<1>& v2,	const int32_t v3,		const intN<1>& v4)	: intN<4>(v1, v2, intN<1>(v3), v4) {}
		hlslpp_inline intN<4>(const intN<1>& v1,	const intN<1>& v2,	const intN<1>& v3,	const int32_t v4)		: intN<4>(v1, v2, v3, intN<1>(v4)) {}

		intN<4>(const intN<1>& v1,		const int32_t v2,		const int32_t v3,		const int32_t v4);
		intN<4>(const int32_t v1,		const intN<1>& v2,	const int32_t v3,		const int32_t v4);
		intN<4>(const int32_t v1,		const int32_t v2,		const intN<1>& v3,	const int32_t v4);
		intN<4>(const int32_t v1,		const int32_t v2,		const int32_t v3,		const intN<1>& v4);
	
		intN<4>(const int32_t v1,		const intN<1>& v2,	const intN<1>& v3,	const int32_t v4);
		intN<4>(const int32_t v1,		const int32_t v2,		const intN<1>& v3,	const intN<1>& v4);
		intN<4>(const int32_t v1,		const intN<1>& v2,	const int32_t v3,		const intN<1>& v4);

		intN<4>(const intN<1>& v1,		const int32_t v2,		const int32_t v3,		const intN<1>& v4);
		intN<4>(const intN<1>& v1,		const intN<1>& v2,	const int32_t v3,		const int32_t v4);
		intN<4>(const intN<1>& v1,		const int32_t v2,		const intN<1>& v3,	const int32_t v4);

		hlslpp_inline intN<4>(const intN<2>& v1,	const int32_t v2,		const intN<1>& v3)	: intN<4>(v1, intN<1>(v2), v3) {}
		hlslpp_inline intN<4>(const intN<2>& v1,	const intN<1>& v2,	const int32_t v3)		: intN<4>(v1, v2, intN<1>(v3)) {}
		hlslpp_inline intN<4>(const intN<2>& v1,	const int32_t v2,		const int32_t v3)		: intN<4>(v1, v2, intN<1>(v3)) {}

		hlslpp_inline intN<4>(const int32_t v1,		const intN<2>& v2,	const intN<1>& v3)	: intN<4>(intN<1>(v1), v2, v3) {}
		hlslpp_inline intN<4>(const intN<1>& v1,	const intN<2>& v2,	const int32_t v3)		: intN<4>(v1, v2, intN<1>(v3)) {}

		hlslpp_inline intN<4>(const int32_t v1,		const intN<1>& v2,	const intN<2>& v3)	: intN<4>(intN<1>(v1), v2, v3) {}
		hlslpp_inline intN<4>(const intN<1>& v1,	const int32_t v2,		const intN<2>& v3)	: intN<4>(v1, intN<1>(v2), v3) {}
		hlslpp_inline intN<4>(const int32_t v1,		const int32_t v2,		const intN<2>& v3)	: intN<4>(intN<2>(v1, v2), v3) {}

		hlslpp_inline intN<4>(const int32_t v1,		const intN<3>& v2)	: intN<4>(intN<1>(v1), v2) {}
		hlslpp_inline intN<4>(const intN<3>& v1,	const int32_t v2)		: intN<4>(v1, intN<1>(v2)) {}

		// intN + icomponentN constructors
		template<int A> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const intN<1>& v2,			const intN<1>& v3,			const intN<1>& v4)			: intN<4>(intN<1>(v1), v2, v3, v4) {}
		template<int A> hlslpp_inline intN<4>(const intN<1>& v1,			const icomponent1<A>& v2,	const intN<1>& v3,			const intN<1>& v4)			: intN<4>(v1, intN<1>(v2), v3, v4) {}
		template<int A> hlslpp_inline intN<4>(const intN<1>& v1,			const intN<1>& v2,			const icomponent1<A>& v3,	const intN<1>& v4)			: intN<4>(v1, v2, intN<1>(v3), v4) {}
		template<int A> hlslpp_inline intN<4>(const intN<1>& v1,			const intN<1>& v2,			const intN<1>& v3,			const icomponent1<A>& v4)	: intN<4>(v1, v2, v3, intN<1>(v4)) {}

		template<int A, int B, int C> hlslpp_inline intN<4>(const intN<1>& v1,			const icomponent1<A>& v2,	const icomponent1<B>& v3,	const icomponent1<C>& v4)	: intN<4>(v1, intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}
		template<int A, int B, int C> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const intN<1>& v2,			const icomponent1<B>& v3,	const icomponent1<C>& v4)	: intN<4>(intN<1>(v1), v2, intN<1>(v3), intN<1>(v4)) {}
		template<int A, int B, int C> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const icomponent1<B>& v2,	const intN<1>& v3,			const icomponent1<C>& v4)	: intN<4>(intN<1>(v1), intN<1>(v2), v3, intN<1>(v4)) {}
		template<int A, int B, int C> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const icomponent1<B>& v2,	const icomponent1<C>& v3,	const intN<1>& v4)			: intN<4>(intN<1>(v1), intN<1>(v2), intN<1>(v3), v4) {}

		template<int A, int B> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const intN<1>& v2,			const intN<1>& v3,			const icomponent1<B>& v4)	: intN<4>(intN<1>(v1), v2, v3, intN<1>(v4)) {}
		template<int A, int B> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const icomponent1<B>& v2,	const intN<1>& v3,			const intN<1>& v4)			: intN<4>(intN<1>(v1), intN<1>(v2), v3, v4) {}
		template<int A, int B> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const intN<1>& v2,			const icomponent1<B>& v3,	const intN<1>& v4)			: intN<4>(intN<1>(v1), v2, intN<1>(v3), v4) {}

		template<int A, int B> hlslpp_inline intN<4>(const intN<1>& v1,			const icomponent1<A>& v2,	const icomponent1<B>& v3,	const intN<1>& v4)			: intN<4>(v1, intN<1>(v2), intN<1>(v3), v4) {}
		template<int A, int B> hlslpp_inline intN<4>(const intN<1>& v1,			const intN<1>& v2,			const icomponent1<A>& v3,	const icomponent1<B>& v4)	: intN<4>(v1, v2, intN<1>(v3), intN<1>(v4)) {}
		template<int A, int B> hlslpp_inline intN<4>(const intN<1>& v1,			const icomponent1<A>& v2,	const intN<1>& v3,			const icomponent1<B>& v4)	: intN<4>(v1, intN<1>(v2), v3, intN<1>(v4)) {}

		template<int A>			hlslpp_inline intN<4>(const intN<2>& v1,		const icomponent1<A>& v2,	const intN<1>& v3)			: intN<4>(v1, intN<1>(v2), v3) {}
		template<int A>			hlslpp_inline intN<4>(const intN<2>& v1,		const intN<1>& v2,			const icomponent1<A>& v3)	: intN<4>(v1, v2, intN<1>(v3)) {}
		template<int A, int B>	hlslpp_inline intN<4>(const intN<2>& v1,		const icomponent1<A>& v2,	const icomponent1<B>& v3)	: intN<4>(v1, v2, intN<1>(v3)) {}

		template<int A> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const intN<2>& v2,	const intN<1>& v3)			: intN<4>(intN<1>(v1), v2, v3) {}
		template<int A> hlslpp_inline intN<4>(const intN<1>& v1,			const intN<2>& v2,	const icomponent1<A>& v3)	: intN<4>(v1, v2, intN<1>(v3)) {}

		template<int A>			hlslpp_inline intN<4>(const intN<1>& v1,			const icomponent1<A>& v2,	const intN<2>& v3)	: intN<4>(v1, intN<1>(v2), v3) {}
		template<int A>			hlslpp_inline intN<4>(const icomponent1<A>& v1,	const intN<1>& v2,			const intN<2>& v3)	: intN<4>(intN<1>(v1), v2, v3) {}
		template<int A, int B>	hlslpp_inline intN<4>(const icomponent1<A>& v1,	const icomponent1<B>& v2,	const intN<2>& v3)	: intN<4>(intN<1>(v1), intN<1>(v2), v3) {}

		template<int A> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const intN<3>& v2)			: intN<4>(intN<1>(v1), v2) {}
		template<int A> hlslpp_inline intN<4>(const intN<3>& v1,			const icomponent1<A>& v2)	: intN<4>(v1, intN<1>(v2)) {}

		// icomponentN + int32_t constructors
		template<int A> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const int32_t v2,				const int32_t v3,				const int32_t v4)				: intN<4>(intN<1>(v1), intN<3>(v2, v3, v4)) {}
		template<int A> hlslpp_inline intN<4>(const int32_t v1,			const icomponent1<A>& v2,	const int32_t v3,				const int32_t v4)				: intN<4>(intN<1>(v1), intN<1>(v2), intN<2>(v3, v4)) {}
		template<int A> hlslpp_inline intN<4>(const int32_t v1,			const int32_t v2,				const icomponent1<A>& v3,	const int32_t v4)				: intN<4>(intN<2>(v1, v2), intN<1>(v3), intN<1>(v4)) {}
		template<int A> hlslpp_inline intN<4>(const int32_t v1,			const int32_t v2,				const int32_t v3,				const icomponent1<A>& v4)	: intN<4>(intN<3>(v1, v2, v3), intN<1>(v4)) {}

		template<int A, int B, int C> hlslpp_inline intN<4>(const int32_t v1,				const icomponent1<A>& v2,	const icomponent1<B>& v3,	const icomponent1<C>& v4)	: intN<4>(intN<1>(v1), intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}
		template<int A, int B, int C> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const int32_t v2,				const icomponent1<B>& v3,	const icomponent1<C>& v4)	: intN<4>(intN<1>(v1), intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}
		template<int A, int B, int C> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const icomponent1<B>& v2,	const int32_t v3,				const icomponent1<C>& v4)	: intN<4>(intN<1>(v1), intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}
		template<int A, int B, int C> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const icomponent1<B>& v2,	const icomponent1<C>& v3,	const int32_t v4)				: intN<4>(intN<1>(v1), intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}

		template<int A, int B> hlslpp_inline intN<4>(const icomponent1<A>& v1,		const int32_t v2,				const int32_t v3,				const icomponent1<B>& v4)	: intN<4>(intN<1>(v1), intN<2>(v2, v3), intN<1>(v4)) {}
		template<int A, int B> hlslpp_inline intN<4>(const icomponent1<A>& v1,		const icomponent1<B>& v2,	const int32_t v3,				const int32_t v4)				: intN<4>(intN<1>(v1), intN<1>(v2), intN<2>(v3, v4)) {}
		template<int A, int B> hlslpp_inline intN<4>(const icomponent1<A>& v1,		const int32_t v2,				const icomponent1<B>& v3,	const int32_t v4)				: intN<4>(intN<1>(v1), intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}

		template<int A, int B> hlslpp_inline intN<4>(const int32_t v1,				const icomponent1<A>& v2,	const icomponent1<B>& v3,	const int32_t v4)				: intN<4>(intN<1>(v1), intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}
		template<int A, int B> hlslpp_inline intN<4>(const int32_t v1,				const int32_t v2,				const icomponent1<A>& v3,	const icomponent1<B>& v4)	: intN<4>(intN<2>(v1, v2), intN<1>(v3), intN<1>(v4)) {}
		template<int A, int B> hlslpp_inline intN<4>(const int32_t v1,				const icomponent1<A>& v2,	const int32_t v3,				const icomponent1<B>& v4)	: intN<4>(intN<1>(v1), intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}


		template<int A, int B> hlslpp_inline intN<4>(const icomponent2<A, B>& v1,	const int32_t v2,				const int32_t v3)				: intN<4>(intN<2>(v1), intN<1>(v2), intN<1>(v3)) {}
		template<int A, int B> hlslpp_inline intN<4>(const int32_t v1,				const icomponent2<A, B>& v2,	const int32_t v3)				: intN<4>(intN<1>(v1), intN<2>(v2), intN<1>(v3)) {}
		template<int A, int B> hlslpp_inline intN<4>(const int32_t v1,				const int32_t v2,				const icomponent2<A, B>& v3)	: intN<4>(intN<1>(v1), intN<1>(v2), intN<2>(v3)) {}

		template<int A, int B, int C> hlslpp_inline intN<4>(const int32_t v1, const icomponent2<A, B>& v2, const icomponent1<C>& v3) : intN<4>(intN<1>(v1), intN<2>(v2), intN<1>(v3)) {}
		template<int A, int B, int C> hlslpp_inline intN<4>(const int32_t v1, const icomponent1<A>& v2, const icomponent2<B, C>& v3) : intN<4>(intN<1>(v1), intN<1>(v2), intN<2>(v3)) {}

		template<int A, int B, int C> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const icomponent2<B, C>& v2,	const int32_t v3)				: intN<4>(intN<1>(v1), intN<2>(v2), intN<1>(v3)) {}
		template<int A, int B, int C> hlslpp_inline intN<4>(const icomponent1<A>& v1,	const int32_t v2,				const icomponent2<B, C>& v3)	: intN<4>(intN<1>(v1), intN<1>(v2), intN<2>(v3)) {}

		template<int A, int B, int C> hlslpp_inline intN<4>(const icomponent2<A, B>& v1,	const int32_t v2,				const icomponent1<C>& v3)	: intN<4>(intN<2>(v1), intN<1>(v2), intN<1>(v3)) {}
		template<int A, int B, int C> hlslpp_inline intN<4>(const icomponent2<A, B>& v1,	const icomponent1<C>& v2,	const int32_t v3)				: intN<4>(intN<2>(v1), intN<1>(v2), intN<1>(v3)) {}

		template<int A, int B, int C> hlslpp_inline intN<4>(const int32_t v1,				const icomponent3<A, B, C>& v2)	: intN<4>(intN<1>(v1), intN<3>(v2)) {}
		template<int A, int B, int C> hlslpp_inline intN<4>(const icomponent3<A, B, C>& v1,	const int32_t v2)				: intN<4>(intN<3>(v1), intN<1>(v2)) {}

		// intN + icomponentN + int32_t constructors
		template<int A>			hlslpp_inline intN<4>(const int32_t v1, const icomponent1<A>& v2, const intN<1>& v3, const int32_t v4) : intN<4>(intN<1>(v1), intN<1>(v2), v3, intN<1>(v4)) {}
		template<int A>			hlslpp_inline intN<4>(const int32_t v1, const icomponent1<A>& v2, const intN<1>& v3, const intN<1>& v4) : intN<4>(intN<1>(v1), intN<1>(v2), v3, v4) {}
		template<int A, int B>	hlslpp_inline intN<4>(const int32_t v1, const icomponent1<A>& v2, const intN<1>& v3, const icomponent1<B>& v4) : intN<4>(intN<1>(v1), intN<1>(v2), v3, intN<1>(v4)) {}

		template<int A>			hlslpp_inline intN<4>(const int32_t v1,	const intN<1>& v2,		const icomponent1<A>& v3,	const int32_t v4)				: intN<4>(intN<1>(v1), v2, intN<1>(v3), intN<1>(v4)) {}
		template<int A>			hlslpp_inline intN<4>(const int32_t v1,	const intN<1>& v2,		const icomponent1<A>& v3,	const intN<1>& v4)			: intN<4>(intN<1>(v1), v2, intN<1>(v3), v4) {}
		template<int A, int B>	hlslpp_inline intN<4>(const int32_t v1,	const intN<1>& v2,		const icomponent1<A>& v3,	const icomponent1<B>& v4)	: intN<4>(intN<1>(v1), v2, intN<1>(v3), intN<1>(v4)) {}

		template<int A>			hlslpp_inline intN<4>(const int32_t v1,	const int32_t v2,			const icomponent1<A>& v3,	const intN<1>& v4)			: intN<4>(intN<2>(v1, v2), intN<1>(v3), v4) {}
		template<int A>			hlslpp_inline intN<4>(const int32_t v1,	const int32_t v2,			const intN<1>& v3,			const icomponent1<A>& v4)	: intN<4>(intN<2>(v1, v2), v3, intN<1>(v4)) {}

		template<int A, int B>	hlslpp_inline intN<4>(const int32_t v1,	const icomponent1<A>& v2,	const int32_t v3,				const intN<1>& v4)		: intN<4>(intN<1>(v1), intN<1>(v2), intN<1>(v3), v4) {}
		template<int A, int B>	hlslpp_inline intN<4>(const int32_t v1,	const icomponent1<A>& v2,	const icomponent1<B>& v3,	const intN<1>& v4)		: intN<4>(intN<1>(v1), intN<1>(v2), intN<1>(v3), v4) {}

		template<int A>			hlslpp_inline intN<4>(const int32_t v1,	const intN<1>& v2,			const intN<1>& v3,			const icomponent1<A>& v4)	: intN<4>(intN<1>(v1), v2, v3, intN<1>(v4)) {}

		template<int A>			hlslpp_inline intN<4>(const icomponent1<A>& v1,	const int32_t v2,	const intN<1>& v3,	const int32_t v4)				: intN<4>(intN<1>(v1), v2, v3, intN<1>(v4)) {}
		template<int A>			hlslpp_inline intN<4>(const icomponent1<A>& v1,	const int32_t v2,	const intN<1>& v3,	const intN<1>& v4)			: intN<4>(intN<1>(v1), intN<1>(v2), v3, v4) {}
		template<int A, int B>	hlslpp_inline intN<4>(const icomponent1<A>& v1,	const int32_t v2,	const intN<1>& v3,	const icomponent1<B>& v4)	: intN<4>(intN<1>(v1), intN<1>(v2), v3, intN<1>(v4)) {}

		template<int A, int B>	hlslpp_inline intN<4>(const icomponent1<A>& v1,	const intN<1>& v2,		const int32_t v3,			const int32_t v4)				: intN<4>(intN<1>(v1), v2, intN<1>(v3), intN<1>(v4)) {}
		template<int A, int B>	hlslpp_inline intN<4>(const icomponent1<A>& v1,	const intN<1>& v2,		const int32_t v3,			const intN<1>& v4)			: intN<4>(intN<1>(v1), v2, intN<1>(v3), v4) {}
		template<int A, int B>	hlslpp_inline intN<4>(const icomponent1<A>& v1,	const intN<1>& v2,		const int32_t v3,			const icomponent1<B>& v4)	: intN<4>(intN<1>(v1), v2, intN<1>(v3), intN<1>(v4)) {}

		template<int A, int B>	hlslpp_inline intN<4>(const icomponent1<A>& v1,	const icomponent1<B>& v2,	const intN<1>& v3,	const int32_t v4)			: intN<4>(intN<1>(v1), intN<1>(v2), v3, intN<1>(v4)) {}
		template<int A, int B>	hlslpp_inline intN<4>(const icomponent1<A>& v1,	const icomponent1<B>& v2,	const int32_t v3,		const intN<1>& v4)		: intN<4>(intN<1>(v1), intN<1>(v2), intN<1>(v3), v4) {}

		template<int A, int B>	hlslpp_inline intN<4>(const icomponent1<A>& v1,	const intN<1>& v2,	const icomponent1<B>& v3,	const int32_t v4)		: intN<4>(intN<1>(v1), v2, intN<1>(v3), intN<1>(v4)) {}
		template<int A>			hlslpp_inline intN<4>(const icomponent1<A>& v1,	const intN<1>& v2,	const int32_t v3,				const intN<1>& v4)	: intN<4>(intN<1>(v1), v2, intN<1>(v3), v4) {}

		template<int A, int B>	hlslpp_inline intN<4>(const icomponent1<A>& v1,	const int32_t v2,		const icomponent1<B>& v3,	const intN<1>& v4)	: intN<4>(intN<1>(v1), intN<1>(v2), intN<1>(v3), v4) {}

		template<int A>			hlslpp_inline intN<4>(const intN<1>& v1,	const icomponent1<A>& v2,	const int32_t  v3,			const int32_t v4)				: intN<4>(v1, intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}
		template<int A>			hlslpp_inline intN<4>(const intN<1>& v1,	const icomponent1<A>& v2,	const int32_t v3,				const intN<1>& v4)			: intN<4>(v1, intN<1>(v2), intN<1>(v3), v4) {}
		template<int A, int B>	hlslpp_inline intN<4>(const intN<1>& v1,	const icomponent1<A>& v2,	const int32_t  v3,			const icomponent1<B>& v4)	: intN<4>(v1, intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}

		template<int A>			hlslpp_inline intN<4>(const intN<1>& v1, const int32_t v2,			const icomponent1<A>&  v3,	const int32_t v4)				: intN<4>(v1, intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}
		template<int A>			hlslpp_inline intN<4>(const intN<1>& v1, const int32_t v2,			const icomponent1<A>& v3,	const intN<1>& v4)			: intN<4>(v1, intN<1>(v2), intN<1>(v3), v4) {}
		template<int A, int B>	hlslpp_inline intN<4>(const intN<1>& v1, const int32_t v2,			const icomponent1<A>&  v3,	const icomponent1<B>& v4)	: intN<4>(v1, intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}

		template<int A>			hlslpp_inline intN<4>(const intN<1>& v1, const intN<1>& v2,		const int32_t v3,				const icomponent1<A>& v4)	: intN<4>(v1, v2, intN<1>(v3), intN<1>(v4)) {}
		template<int A>			hlslpp_inline intN<4>(const intN<1>& v1, const intN<1>& v2,		const icomponent1<A>& v3,	const int32_t v4)				: intN<4>(v1, v2, intN<1>(v3), intN<1>(v4)) {}

		template<int A>			hlslpp_inline intN<4>(const intN<1>& v1, const int32_t v2,			const intN<1>& v3,		const icomponent1<A>& v4)	: intN<4>(v1, intN<1>(v2), v3, intN<1>(v4)) {}
		template<int A>			hlslpp_inline intN<4>(const intN<1>& v1, const int32_t v2,			const int32_t  v3,		const icomponent1<A>& v4)	: intN<4>(v1, intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}

		template<int A>			hlslpp_inline intN<4>(const intN<1>& v1, const icomponent1<A>& v2,	const intN<1>& v3,			const int32_t v4)		: intN<4>(v1, intN<1>(v2), v3, intN<1>(v4)) {}
		template<int A, int B>	hlslpp_inline intN<4>(const intN<1>& v1, const icomponent1<A>& v2,	const icomponent1<B>&  v3,	const int32_t v4)		: intN<4>(v1, intN<1>(v2), intN<1>(v3), intN<1>(v4)) {}

		explicit intN<4>(const intNxM<4, 1>& v);
		explicit intN<4>(const intNxM<1, 4>& v);

		intN<4>& operator = (const intN<4>& c);
		intN<4>& operator = (const int32_t f);
		template<int A, int B, int C, int D> intN<4>& operator = (const icomponent4<A, B, C, D>& c);

		// Disallow these constructors, as implicit construction rules could allow them to be valid
		intN<4>(int32_t v1, int32_t v2) = delete;
		intN<4>(int32_t v1, int32_t v2, int32_t v3) = delete;
	};

	using int1 = intN<1>;
	using int2 = intN<2>;
	using int3 = intN<3>;
	using int4 = intN<4>;

	//-------------------
	// Matrix class types
	//-------------------

	template<>
	class floatNxM<1, 1>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
			#include "swizzle/hlsl++_matrix_row0_1.h"
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec) : _vec(vec) {}
		hlslpp_inline explicit floatNxM(float f) : _vec(_hlslpp_set_ps(f, 0.0f, 0.0f, 0.0f)) {}
		hlslpp_inline floatNxM(const float1& v) : _vec(v._vec) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
	};

	template<>
	class floatNxM<1, 2>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
			#include "swizzle/hlsl++_matrix_row0_2.h"
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec) : _vec(vec) {}
		hlslpp_inline floatNxM(float f0, float f1) : _vec(_hlslpp_set_ps(f0, f1, 0.0f, 0.0f)) {}
		hlslpp_inline explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const float2& v) : _vec(v._vec) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
	};

	template<>
	class floatNxM<2, 1>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec) : _vec(vec) {}
		hlslpp_inline floatNxM(float f0, float f1) : _vec(_hlslpp_set_ps(f0, f1, 0.0f, 0.0f)) {}
		hlslpp_inline explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const float2& v) : _vec(v._vec) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
	};

	template<>
	class floatNxM<1, 3>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec) : _vec(vec) {}
		hlslpp_inline floatNxM(float f0, float f1, float f2) : _vec(_hlslpp_set_ps(f0, f1, f2, 0.0f)) {}
		hlslpp_inline explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const float3& v) : _vec(v._vec) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
	};

	template<>
	class floatNxM<3, 1>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec) : _vec(vec) {}
		hlslpp_inline floatNxM(float f0, float f1, float f2) : _vec(_hlslpp_set_ps(f0, f1, f2, 0.0f)) {}
		hlslpp_inline explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const float3& v) : _vec(v._vec) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
	};

	template<>
	class floatNxM<1, 4>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec) : _vec(vec) {}
		hlslpp_inline floatNxM(float f0, float f1, float f2, float f3) : _vec(_hlslpp_set_ps(f0, f1, f2, f3)) {}
		hlslpp_inline explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const float4& v) : _vec(v._vec) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
	};

	template<>
	class floatNxM<4, 1>
	{
	public:
		union
		{
			n128 _vec;
			float _f32[4];
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec) : _vec(vec) {}
		hlslpp_inline floatNxM(float f0, float f1, float f2, float f3) : _vec(_hlslpp_set_ps(f0, f1, f2, f3)) {}
		hlslpp_inline explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const float4& v) : _vec(v._vec) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
	};

	template<>
	class floatNxM<2, 2>
	{
	public:	
		union
		{
			n128 _vec; // We can store it in a single vector to save memory
			float _f32[4];
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec) : _vec(vec) {}

		hlslpp_inline floatNxM(float f00, float f01,
				 float f10, float f11) : _vec(_hlslpp_set_ps(f00, f01, f10, f11)) {}

		hlslpp_inline explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const floatNxM& m) : _vec(m._vec) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
	};

	template<>
	class floatNxM<2, 3>
	{
	public:
		union
		{
			n128 _vec0;
			float _f32_0[4];
		};

		union
		{
			n128 _vec1;
			float _f32_1[4];
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec0, n128 vec1) : _vec0(vec0), _vec1(vec1) {}

		hlslpp_inline floatNxM(float f00, float f01, float f02,
				 float f10, float f11, float f12) : _vec0(_hlslpp_set_ps(f00, f01, f02, 0.0f)), _vec1(_hlslpp_set_ps(f10, f11, f12, 0.0f)) {}

		hlslpp_inline explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; return *this; }
	};

	template<>
	class floatNxM<3, 2>
	{
	public:
		union
		{
			n128 _vec0;
			float _f32_0[4];
		};

		union
		{
			n128 _vec1;
			float _f32_1[4];
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec0, n128 vec1) : _vec0(vec0), _vec1(vec1) {}

		hlslpp_inline floatNxM(float f00, float f01,
				 float f10, float f11,
				 float f20, float f21) : _vec0(_hlslpp_set_ps(f00, f10, f20, 0.0f)), _vec1(_hlslpp_set_ps(f01, f11, f21, 0.0f)) {}

		hlslpp_inline explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; return *this; }
	};

	template<>
	class floatNxM<2, 4>
	{
	public:
		union
		{
			n128 _vec0;
			float _f32_0[4];
		};

		union
		{
			n128 _vec1;
			float _f32_1[4];
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec0, n128 vec1) : _vec0(vec0), _vec1(vec1) {}

		hlslpp_inline floatNxM(float f00, float f01, float f02, float f03,
				 float f10, float f11, float f12, float f13) : _vec0(_hlslpp_set_ps(f00, f01, f02, f03)), _vec1(_hlslpp_set_ps(f10, f11, f12, f13)) {}

		hlslpp_inline explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; return *this; }
	};

	template<>
	class floatNxM<4, 2>
	{
	public:
		union
		{
			n128 _vec0;
			float _f32_0[4];
		};

		union
		{
			n128 _vec1;
			float _f32_1[4];
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec0, n128 vec1) : _vec0(vec0), _vec1(vec1) {}

		hlslpp_inline floatNxM(float f00, float f01,
				 float f10, float f11,
				 float f20, float f21, 
				 float f30, float f31) : _vec0(_hlslpp_set_ps(f00, f10, f20, f30)), _vec1(_hlslpp_set_ps(f01, f11, f21, f31)) {}

		hlslpp_inline explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; return *this; }
	};

	class quaternion; // Forward declare for float3x3 and float4x4

	template<>
	class floatNxM<3, 3>
	{
	public:
		union
		{
			n128 _vec0;
			float _f32_0[4];
			#include "swizzle/hlsl++_matrix_row0_1.h"
			#include "swizzle/hlsl++_matrix_row0_2.h"
			#include "swizzle/hlsl++_matrix_row0_3.h"
		};

		union
		{
			n128 _vec1;
			float _f32_1[4];
			#include "swizzle/hlsl++_matrix_row1_1.h"
			#include "swizzle/hlsl++_matrix_row1_2.h"
			#include "swizzle/hlsl++_matrix_row1_3.h"
		};

		union
		{
			n128 _vec2;
			float _f32_2[4];
			#include "swizzle/hlsl++_matrix_row2_1.h"
			#include "swizzle/hlsl++_matrix_row2_2.h"
			#include "swizzle/hlsl++_matrix_row2_3.h"
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(const n128 vec0, const n128 vec1, const n128 vec2) : _vec0(vec0), _vec1(vec1), _vec2(vec2) {}

		hlslpp_inline floatNxM(float f00, float f01, float f02,
				 float f10, float f11, float f12,
				 float f20, float f21, float f22) : _vec0(_hlslpp_set_ps(f00, f01, f02, 0.0f)), _vec1(_hlslpp_set_ps(f10, f11, f12, 0.0f)), _vec2(_hlslpp_set_ps(f20, f21, f22, 0.0f)) {}

		hlslpp_inline floatNxM(const quaternion& q);

		hlslpp_inline explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)), _vec2(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1), _vec2(m._vec2) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; _vec2 = m._vec2; return *this; }

		static const floatNxM<3, 3>& identity() { static const floatNxM<3, 3> iden = floatNxM<3, 3>(1, 0, 0, 0, 1, 0, 0, 0, 1); return iden; };
	};

	template<>
	class floatNxM<3, 4>
	{
	public:
		union
		{
			n128 _vec0;
			float _f32_0[4];
		};

		union
		{
			n128 _vec1;
			float _f32_1[4];
		};

		union
		{
			n128 _vec2;
			float _f32_2[4];
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec0, n128 vec1, n128 vec2) : _vec0(vec0), _vec1(vec1), _vec2(vec2) {}

		hlslpp_inline floatNxM(float f00, float f01, float f02, float f03,
				 float f10, float f11, float f12, float f13,
				 float f20, float f21, float f22, float f23) : _vec0(_hlslpp_set_ps(f00, f01, f02, f03)), _vec1(_hlslpp_set_ps(f10, f11, f12, f13)), _vec2(_hlslpp_set_ps(f20, f21, f22, f23)) {}

		hlslpp_inline explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)), _vec2(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1), _vec2(m._vec2) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; _vec2 = m._vec2; return *this; }
	};

	template<>
	class floatNxM<4, 3>
	{
	public:
		union
		{
			n128 _vec0;
			float _f32_0[4];
		};

		union
		{
			n128 _vec1;
			float _f32_1[4];
		};

		union
		{
			n128 _vec2;
			float _f32_2[4];
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(n128 vec0, n128 vec1, n128 vec2) : _vec0(vec0), _vec1(vec1), _vec2(vec2) {}

		hlslpp_inline floatNxM(float f00, float f01, float f02,
				 float f10, float f11, float f12,
				 float f20, float f21, float f22,
				 float f30, float f31, float f32): _vec0(_hlslpp_set_ps(f00, f10, f20, f30)), _vec1(_hlslpp_set_ps(f01, f11, f21, f31)), _vec2(_hlslpp_set_ps(f02, f12, f22, f32)) {}

		hlslpp_inline explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)), _vec2(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1), _vec2(m._vec2) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; _vec2 = m._vec2; return *this; }
	};

	template<>
	class floatNxM<4, 4>
	{
	public:
		union
		{
			n128 _vec0;
			float _f32_0[4];
			#include "swizzle/hlsl++_matrix_row0_1.h"
			#include "swizzle/hlsl++_matrix_row0_2.h"
			#include "swizzle/hlsl++_matrix_row0_3.h"
			#include "swizzle/hlsl++_matrix_row0_4.h"
		};

		union
		{
			n128 _vec1;
			float _f32_1[4];
			#include "swizzle/hlsl++_matrix_row1_1.h"
			#include "swizzle/hlsl++_matrix_row1_2.h"
			#include "swizzle/hlsl++_matrix_row1_3.h"
			#include "swizzle/hlsl++_matrix_row1_4.h"
		};

		union
		{
			n128 _vec2;
			float _f32_2[4];
			#include "swizzle/hlsl++_matrix_row2_1.h"
			#include "swizzle/hlsl++_matrix_row2_2.h"
			#include "swizzle/hlsl++_matrix_row2_3.h"
			#include "swizzle/hlsl++_matrix_row2_4.h"
		};

		union
		{
			n128 _vec3;
			float _f32_3[4];
			#include "swizzle/hlsl++_matrix_row3_1.h"
			#include "swizzle/hlsl++_matrix_row3_2.h"
			#include "swizzle/hlsl++_matrix_row3_3.h"
			#include "swizzle/hlsl++_matrix_row3_4.h"
		};

		hlslpp_inline floatNxM() {}
		hlslpp_inline explicit floatNxM(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3) : _vec0(vec0), _vec1(vec1), _vec2(vec2), _vec3(vec3) {}


		hlslpp_inline floatNxM(float f00, float f01, float f02, float f03,
				 float f10, float f11, float f12, float f13,
				 float f20, float f21, float f22, float f23,
				 float f30, float f31, float f32, float f33)
			: _vec0(_hlslpp_set_ps(f00, f01, f02, f03)), _vec1(_hlslpp_set_ps(f10, f11, f12, f13)), _vec2(_hlslpp_set_ps(f20, f21, f22, f23)), _vec3(_hlslpp_set_ps(f30, f31, f32, f33)) {}

		hlslpp_inline floatNxM(const quaternion& q);

		hlslpp_inline explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)), _vec2(_hlslpp_set1_ps(f)), _vec3(_hlslpp_set1_ps(f)) {}
		hlslpp_inline floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1), _vec2(m._vec2), _vec3(m._vec3) {}
		hlslpp_inline floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; _vec2 = m._vec2; _vec3 = m._vec3; return *this; }
		static const floatNxM<4, 4>& identity() { static const floatNxM<4, 4> iden = floatNxM<4, 4>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); return iden; };
	};

	using float1x1 = floatNxM<1, 1>;
	using float1x2 = floatNxM<1, 2>;
	using float2x1 = floatNxM<2, 1>;
	using float1x3 = floatNxM<1, 3>;
	using float3x1 = floatNxM<3, 1>;
	using float1x4 = floatNxM<1, 4>;
	using float4x1 = floatNxM<4, 1>;

	using float2x2 = floatNxM<2, 2>;
	using float2x3 = floatNxM<2, 3>;
	using float3x2 = floatNxM<3, 2>;
	using float2x4 = floatNxM<2, 4>;
	using float4x2 = floatNxM<4, 2>;

	using float3x3 = floatNxM<3, 3>;
	using float3x4 = floatNxM<3, 4>;
	using float4x3 = floatNxM<4, 3>;

	using float4x4 = floatNxM<4, 4>;

	using int1x1 = intNxM<1, 1>;
	using int1x2 = intNxM<1, 2>;
	using int2x1 = intNxM<2, 1>;
	using int1x3 = intNxM<1, 3>;
	using int3x1 = intNxM<3, 1>;
	using int1x4 = intNxM<1, 4>;
	using int4x1 = intNxM<4, 1>;

	using int2x2 = intNxM<2, 2>;
	using int2x3 = intNxM<2, 3>;
	using int3x2 = intNxM<3, 2>;
	using int2x4 = intNxM<2, 4>;
	using int4x2 = intNxM<4, 2>;

	using int3x3 = intNxM<3, 3>;
	using int3x4 = intNxM<3, 4>;
	using int4x3 = intNxM<4, 3>;

	using int4x4 = intNxM<4, 4>;

	//--------------------------
	// Component float functions
	//--------------------------

	template<int A>
	template<int E>
	hlslpp_inline components<A>::components(const component1<E>& c) { *this = c; }

	template<int A>
	template<int E>
	hlslpp_inline components<A>& components<A>::operator = (const component1<E>& c)
	{
		n128 s = _hlslpp_shuffle_ps(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(E, E, E, E));
		_vec = _hlslpp_blend_ps(_vec, s, HLSLPP_COMPONENT_X(A));
		return *this;
	}

	template<int A>
	hlslpp_inline components<A>& components<A>::operator = (float f)
	{
		const n128 s = _hlslpp_set1_ps(f);
		_vec = _hlslpp_blend_ps(_vec, s, HLSLPP_COMPONENT_X(A));
		return *this;
	}

	template<int A>
	hlslpp_inline components<A>& components<A>::operator = (const float1& v) { _vec = _hlslpp_blend_ps(_vec, v._vec, HLSLPP_COMPONENT_X(A)); return *this; }

	template<int A>
	hlslpp_inline components<A>& components<A>::operator = (const float1x1& m) { _vec = _hlslpp_blend_ps(_vec, m._vec, HLSLPP_COMPONENT_X(A)); return *this; }

	template<int A, int B>
	template<int E, int F>
	hlslpp_inline components<A, B>::components(const component2<E, F>& c) { *this = c; }

	template<int A, int B>
	template<int E, int F>
	hlslpp_inline components<A, B>& components<A, B>::operator = (const component2<E, F>& c)
	{
		staticAsserts();
		_vec = blend(_vec, swizzle<E, F, A, B>(c._vec));
		return *this;
	}

	template<int A, int B>
	hlslpp_inline components<A, B>& components<A, B>::operator = (const component2<A, B>& c) { _vec = _hlslpp_blend_ps(_vec, c._vec, HLSLPP_BLEND_MASK(0, 0, 1, 1)); return *this; }

	template<int A, int B>
	hlslpp_inline components<A, B>& components<A, B>::operator = (const float2& v)
	{
		staticAsserts();
		_vec = blend(_vec, swizzle<0, 1, A, B>(v._vec));
		return *this;
	}

	template<int A, int B, int C>
	template<int E, int F, int G>
	hlslpp_inline components<A, B, C>::components(const component3<E, F, G>& c) { *this = c; }

	template<int A, int B, int C>
	template<int E, int F, int G>
	hlslpp_inline components<A, B, C>& components<A, B, C>::operator = (const component3<E, F, G>& c)
	{
		staticAsserts();
		_vec = blend(_vec, swizzle<E, F, G, A, B, C>(c._vec));
		return *this;
	}

	template<int A, int B, int C>
	hlslpp_inline components<A, B, C>& components<A, B, C>::operator = (const component3<A, B, C>& c) { _vec = _hlslpp_blend_ps(_vec, c._vec, HLSLPP_BLEND_MASK(0, 0, 0, 1)); return *this; }

	template<int A, int B, int C>
	hlslpp_inline components<A, B, C>& components<A, B, C>::operator = (const float3& v)
	{
		staticAsserts();
		_vec = blend(_vec, swizzle<0, 1, 2, A, B, C>(v._vec));
		return *this;
	}

	template<int A, int B, int C, int D>
	template<int E, int F, int G, int H>
	hlslpp_inline components<A, B, C, D>::components(const component4<E, F, G, H>& c) { *this = c; }

	template<int A, int B, int C, int D>
	template<int E, int F, int G, int H>
	hlslpp_inline components<A, B, C, D>& components<A, B, C, D>::operator = (const component4<E, F, G, H>& c)
	{
		staticAsserts();	
		const uint32_t mask = HLSLPP_SHUFFLE_MASK(E, F, G, H);
		const uint32_t reshuffleMask = ((mask & 3) << (2 * A)) | (((mask >> 2) & 3) << (2 * B)) | (((mask >> 4) & 3) << (2 * C)) | (((mask >> 6) & 3) << (2 * D));	// Re-swizzle with property mask
		_vec = _hlslpp_shuffle_ps(c._vec, c._vec, reshuffleMask);

		// Reference for correctness
		//p = _mm_shuffle_ps(f.p, f.p, _MM_SHUFFLE(H, G, F, E));
		//p = _mm_shuffle_ps(p, p, _MM_SHUFFLE(D, C, B, A));
	
		return *this;
	}

	template<int A, int B, int C, int D>
	hlslpp_inline components<A, B, C, D>& components<A, B, C, D>::operator = (const component4<A, B, C, D>& c) { _vec = c._vec; return *this; }

	template<int A, int B, int C, int D>
	hlslpp_inline components<A, B, C, D>& components<A, B, C, D>::operator = (const float4& v)
	{
		staticAsserts();
		_vec = _hlslpp_shuffle_ps(v._vec, v._vec, HLSLPP_SHUFFLE_MASK(A, B, C, D));
		return *this;
	}

	template<> // Optimize a straight copy via explicit instantiation (doesn't produce/need the shuffle)
	hlslpp_inline components<0, 1, 2, 3>& components<0, 1, 2, 3>::operator = (const float4& v) { _vec = v._vec; return *this; }

	//-----------------------
	// Vector float functions
	//-----------------------

	//----- Addition

	template<int N> hlslpp_inline floatN<N> operator + (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_add_ps(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline floatN<N> operator + (const floatN<N>& v1, const float v2) { return v1 + floatN<N>(v2); }
	template<int N> hlslpp_inline floatN<N> operator + (const float v1, const floatN<N>& v2) { return floatN<N>(v1) + v2; }

	template<int N,	int...Dim>
	hlslpp_inline floatN<N> operator + (const floatN<N>& v1, const components<Dim...>& v2) { return v1 + floatN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator + (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) + v2; }

	template<int...D1, int...D2>
	hlslpp_inline floatN<sizeof...(D1)> operator + (const components<D1...>& v1, const components<D2...>& v2)
	{
		return floatN<sizeof...(D1)>(_hlslpp_add_ps(floatN<sizeof...(D1)>(v1)._vec, floatN<sizeof...(D1)>(v2)._vec));
	}

	template<int N> hlslpp_inline floatN<N> operator + (const floatN<N>& v1, const float1& v2) { return v1 + floatN<N>(_hlslpp_perm_xxxx_ps(v2._vec)); }
	hlslpp_inline float1 operator + (const float1& v1, const float1& v2) { return float1(_hlslpp_add_ps(v1._vec, v2._vec)); } // A bit more optimal as it avoids the shuffle

	//----- Plus equals

	template<int N> hlslpp_inline floatN<N>& operator += (floatN<N>& v1, const floatN<N>& v2) { v1 = v1 + v2; return v1; }

	template<int N> hlslpp_inline floatN<N>& operator += (floatN<N>& v1, const float v2) { v1 = v1 + floatN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N>& operator += (floatN<N>& v1, const components<Dim...>& v2) { v1 = v1 + floatN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline components<Dim...>& operator += (components<Dim...>& v1, const floatN<N>& v2) { v1 = floatN<N>(v1) + v2; return v1; }

	template<int...Dim1, int...Dim2>
	hlslpp_inline components<Dim1...>& operator += (components<Dim1...>& v1, const components<Dim2...>& v2)
	{ 
		static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension");
		v1 = floatN<sizeof...(Dim1)>(v1) + floatN<sizeof...(Dim1)>(v2); return v1;
	}

	template<int N> hlslpp_inline floatN<N>& operator += (floatN<N>& v1, const float1& v2) { v1 = v1 + v2; return v1; }
	hlslpp_inline float1& operator += (float1& v1, const float1& v2) { v1 = v1 + v2; return v1; }

	//----- Subtraction
	template<int N> hlslpp_inline floatN<N> operator - (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_sub_ps(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline floatN<N> operator - (const floatN<N>& v1, const float v2) { return v1 - floatN<N>(v2); }
	template<int N> hlslpp_inline floatN<N> operator - (const float v1, const floatN<N>& v2) { return floatN<N>(v1) - v2; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator - (const floatN<N>& v1, const components<Dim...>& v2) { return v1 - floatN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator - (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) - v2; }

	template<int...D1, int...D2>
	hlslpp_inline componentbase<sizeof...(D1)> operator - (const components<D1...>& v1, const components<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return componentbase<sizeof...(D1)>(_hlslpp_sub_ps(componentbase<sizeof...(D1)>(v1)._vec, componentbase<sizeof...(D1)>(v2)._vec));
	}

	template<int N>
	hlslpp_inline floatN<N> operator - (const floatN<N>& v1, const float1& v2) { return v1 - floatN<N>(_hlslpp_perm_xxxx_ps(v2._vec)); }
	hlslpp_inline float1 operator - (const float1& v1, const float1& v2) { return float1(_hlslpp_sub_ps(v1._vec, v2._vec)); } // A bit more optimal as it avoids the shuffle

	//----- Minus equals
	template<int N> hlslpp_inline floatN<N>& operator -= (floatN<N>& v1, const floatN<N>& v2) { v1 = v1 - v2; return v1; }

	template<int N> hlslpp_inline floatN<N>& operator -= (floatN<N>& v1, const float v2) { v1 = v1 - floatN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N>& operator -= (floatN<N>& v1, const components<Dim...>& v2) { v1 = v1 - floatN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline components<Dim...>& operator -= (components<Dim...>& v1, const floatN<N>& v2) { v1 = floatN<N>(v1) - v2; return v1; }

	template<int...Dim1, int...Dim2>
	hlslpp_inline components<Dim1...>& operator -= (components<Dim1...>& v1, const components<Dim2...>& v2)
	{
		static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
		v1 = floatN<sizeof...(Dim1)>(v1) - floatN<sizeof...(Dim1)>(v2); return v1;
	}

	template<int N> hlslpp_inline floatN<N>& operator -= (floatN<N>& v1, const float1& v2) { v1 = v1 - v2; return v1; }
	hlslpp_inline float1& operator -= (float1& v1, const float1& v2) { v1 = v1 - v2; return v1; }

	//----- Multiplication
	template<int N> hlslpp_inline floatN<N> operator * (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_mul_ps(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline floatN<N> operator * (const floatN<N>& v1, const float v2) { return v1 * floatN<N>(v2); }
	template<int N> hlslpp_inline floatN<N> operator * (const float v1, const floatN<N>& v2) { return floatN<N>(v1) * v2; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator * (const floatN<N>& v1, const components<Dim...>& v2) { return v1 * floatN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator * (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) * v2; }

	template<int...D1, int...D2>
	hlslpp_inline floatN<sizeof...(D1)> operator * (const components<D1...>& v1, const components<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return floatN<sizeof...(D1)>(_hlslpp_mul_ps(floatN<sizeof...(D1)>(v1)._vec, floatN<sizeof...(D1)>(v2)._vec));
	}

	template<int N> hlslpp_inline floatN<N> operator * (const floatN<N>& v1, const float1& v2) { return v1 * floatN<N>(_hlslpp_perm_xxxx_ps(v2._vec)); }
	hlslpp_inline float1 operator * (const float1& v1, const float1& v2) { return float1(_hlslpp_mul_ps(v1._vec, v2._vec)); } // A bit more optimal as it avoids the shuffle

	//----- Times equals
	template<int N> hlslpp_inline floatN<N>& operator *= (floatN<N>& v1, const floatN<N>& v2) { v1 = v1 * v2; return v1; }

	template<int N> hlslpp_inline floatN<N>& operator *= (floatN<N>& v1, const float v2) { v1 = v1 * floatN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N>& operator *= (floatN<N>& v1, const components<Dim...>& v2) { v1 = v1 * floatN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline components<Dim...>& operator *= (components<Dim...>& v1, const floatN<N>& v2) { v1 = floatN<N>(v1) * v2; return v1; }

	template<int...Dim1, int...Dim2>
	hlslpp_inline components<Dim1...>& operator *= (components<Dim1...>& v1, const components<Dim2...>& v2)
	{
		static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
		v1 = floatN<sizeof...(Dim1)>(v1) * floatN<sizeof...(Dim1)>(v2); return v1;
	}

	template<int N>
	hlslpp_inline floatN<N>& operator *= (floatN<N>& v1, const float1& v2) { v1 = v1 * v2; return v1; }
	hlslpp_inline float1& operator *= (float1& v1, const float1& v2) { v1 = v1 * v2; return v1; }

	//----- Division
	template<int N> hlslpp_inline floatN<N> operator / (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_div_ps(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline floatN<N> operator / (const floatN<N>& v1, const float v2) { return v1 / floatN<N>(v2); }
	template<int N> hlslpp_inline floatN<N> operator / (const float v1, const floatN<N>& v2) { return floatN<N>(v1) / v2; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator / (const floatN<N>& v1, const components<Dim...>& v2) { return v1 / floatN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator / (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) / v2; }

	template<int...D1, int...D2>
	hlslpp_inline floatN<sizeof...(D1)> operator / (const components<D1...>& v1, const components<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return floatN<sizeof...(D1)>(_hlslpp_div_ps(floatN<sizeof...(D1)>(v1)._vec, floatN<sizeof...(D1)>(v2)._vec));
	}

	template<int N> inline floatN<N> operator / (const floatN<N>& v1, const float1& v2) { return v1 / floatN<N>(_hlslpp_perm_xxxx_ps(v2._vec)); }
	hlslpp_inline float1 operator / (const float1& v1, const float1& v2) { return float1(_hlslpp_div_ps(v1._vec, v2._vec)); } // A bit more optimal as it avoids the shuffle

	//----- Divide equals
	template<int N> hlslpp_inline floatN<N>& operator /= (floatN<N>& v1, const floatN<N>& v2) { v1 = v1 / v2; return v1; }

	template<int N> hlslpp_inline floatN<N>& operator /= (floatN<N>& v1, const float v2) { v1 = v1 / floatN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N>& operator /= (floatN<N>& v1, const components<Dim...>& v2) { v1 = v1 / floatN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline components<Dim...>& operator /= (components<Dim...>& v1, const floatN<N>& v2) { v1 = floatN<N>(v1) / v2; return v1; }

	template<int...Dim1, int...Dim2>
	hlslpp_inline components<Dim1...>& operator /= (components<Dim1...>& v1, const components<Dim2...>& v2)
	{
		static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
		v1 = floatN<sizeof...(Dim1)>(v1) / floatN<sizeof...(Dim1)>(v2); return v1;
	}

	template<int N> hlslpp_inline floatN<N>& operator /= (floatN<N>& v1, const float1& v2) { v1 = v1 / v2; return v1; }
	hlslpp_inline float1& operator /= (float1& v1, const float1& v2) { v1 = v1 / v2; return v1; }

	//----- Negation
	template<int N> hlslpp_inline floatN<N> operator - (const floatN<N>& v) { return floatN<N>(_hlslpp_neg_ps(v._vec)); }

	template<int...D>
	hlslpp_inline components<D...> operator - (const components<D...>& v) { return components<D...>(_hlslpp_neg_ps(v._vec)); }

	//----- Equals
	template<int N> hlslpp_inline floatN<N> operator == (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_cmpeq1_ps(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline floatN<N> operator == (const floatN<N>& v1, const float v2) { return v1 == floatN<N>(v2); }
	template<int N> hlslpp_inline floatN<N> operator == (const float v1, const floatN<N>& v2) { return floatN<N>(v1) == v2; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator == (const floatN<N>& v1, const components<Dim...>& v2) { return v1 == floatN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator == (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) == v2; }

	template<int...D1, int...D2>
	hlslpp_inline componentbase<sizeof...(D1)> operator == (const components<D1...>& v1, const components<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return componentbase<sizeof...(D1)>(_hlslpp_cmpeq1_ps(componentbase<sizeof...(D1)>(v1)._vec, componentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Not equals
	template<int N> hlslpp_inline floatN<N> operator != (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_cmpneq1_ps(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline floatN<N> operator != (const floatN<N>& v1, const float v2) { return v1 != floatN<N>(v2); }
	template<int N> hlslpp_inline floatN<N> operator != (const float v1, const floatN<N>& v2) { return floatN<N>(v1) != v2; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator != (const floatN<N>& v1, const components<Dim...>& v2) { return v1 != floatN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator != (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) != v2; }

	template<int...D1, int...D2>
	hlslpp_inline componentbase<sizeof...(D1)> operator != (const components<D1...>& v1, const components<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return componentbase<sizeof...(D1)>(_hlslpp_cmpneq1_ps(componentbase<sizeof...(D1)>(v1)._vec, componentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Greater than
	template<int N> hlslpp_inline floatN<N> operator > (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_cmpgt1_ps(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline floatN<N> operator > (const floatN<N>& v1, const float v2) { return v1 > floatN<N>(v2); }
	template<int N> hlslpp_inline floatN<N> operator > (const float v1, const floatN<N>& v2) { return floatN<N>(v1) > v2; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator > (const floatN<N>& v1, const components<Dim...>& v2) { return v1 > floatN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator > (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) > v2; }

	template<int...D1, int...D2>
	hlslpp_inline componentbase<sizeof...(D1)> operator > (const components<D1...>& v1, const components<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return componentbase<sizeof...(D1)>(_hlslpp_cmpgt1_ps(componentbase<sizeof...(D1)>(v1)._vec, componentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Greater equals
	template<int N> hlslpp_inline floatN<N> operator >= (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_cmpge1_ps(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline floatN<N> operator >= (const floatN<N>& v1, const float v2) { return v1 >= floatN<N>(v2); }
	template<int N> hlslpp_inline floatN<N> operator >= (const float v1, const floatN<N>& v2) { return floatN<N>(v1) >= v2; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator >= (const floatN<N>& v1, const components<Dim...>& v2) { return v1 >= floatN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator >= (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) >= v2; }

	template<int...D1, int...D2>
	hlslpp_inline componentbase<sizeof...(D1)> operator >= (const components<D1...>& v1, const components<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return componentbase<sizeof...(D1)>(_hlslpp_cmpge1_ps(componentbase<sizeof...(D1)>(v1)._vec, componentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Less than
	template<int N> hlslpp_inline floatN<N> operator < (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_cmplt1_ps(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline floatN<N> operator < (const floatN<N>& v1, const float v2) { return v1 < floatN<N>(v2); }
	template<int N> hlslpp_inline floatN<N> operator < (const float v1, const floatN<N>& v2) { return floatN<N>(v1) < v2; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator < (const floatN<N>& v1, const components<Dim...>& v2) { return v1 < floatN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator < (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) < v2; }

	template<int...D1, int...D2>
	hlslpp_inline componentbase<sizeof...(D1)> operator < (const components<D1...>& v1, const components<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return componentbase<sizeof...(D1)>(_hlslpp_cmplt1_ps(componentbase<sizeof...(D1)>(v1)._vec, componentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Less equals
	template<int N> hlslpp_inline floatN<N> operator <= (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_cmple1_ps(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline floatN<N> operator <= (const floatN<N>& v1, const float v2) { return v1 <= floatN<N>(v2); }
	template<int N> hlslpp_inline floatN<N> operator <= (const float v1, const floatN<N>& v2) { return floatN<N>(v1) <= v2; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator <= (const floatN<N>& v1, const components<Dim...>& v2) { return v1 <= floatN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> operator <= (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) <= v2; }

	template<int...D1, int...D2>
	hlslpp_inline componentbase<sizeof...(D1)> operator <= (const components<D1...>& v1, const components<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return componentbase<sizeof...(D1)>(_hlslpp_cmple1_ps(componentbase<sizeof...(D1)>(v1)._vec, componentbase<sizeof...(D1)>(v2)._vec));
	}

	template<int N>		hlslpp_inline floatN<N>				abs(const floatN<N>& v) { return floatN<N>(_hlslpp_abs_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	abs(const components<Dim...>& v) { return components<Dim...>(_hlslpp_abs_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				acos(const floatN<N>& v) { return floatN<N>(_hlslpp_acos_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	acos(const components<Dim...>& v) { return components<Dim...>(_hlslpp_acos_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				all(const floatN<N>& v) { return floatN<N>(_hlslpp_all1_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	all(const components<Dim...>& v) { return components<Dim...>(_hlslpp_all1_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				any(const floatN<N>& v) { return floatN<N>(_hlslpp_any1_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	any(const components<Dim...>& v) { return components<Dim...>(_hlslpp_any1_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				asin(const floatN<N>& v) { return floatN<N>(_hlslpp_asin_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	asin(const components<Dim...>& v) { return components<Dim...>(_hlslpp_asin_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				atan(const floatN<N>& v) { return floatN<N>(_hlslpp_atan_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	atan(const components<Dim...>& v) { return components<Dim...>(_hlslpp_atan_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				ceil(const floatN<N>& v) { return floatN<N>(_hlslpp_ceil_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	ceil(const components<Dim...>& v) { return components<Dim...>(_hlslpp_ceil_ps(v._vec)); }

	template<int N> hlslpp_inline floatN<N> clamp(const floatN<N>& v, const floatN<N>& minv, const floatN<N>& maxv) { return floatN<N>(_hlslpp_clamp_ps(v._vec, minv._vec, maxv._vec)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> clamp(const floatN<N>& v1, const floatN<N>& v2, const components<Dim...>& a) { return clamp(v1, v2, floatN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> clamp(const floatN<N>& v1, const components<Dim...>& v2, const floatN<N>& a) { return clamp(v1, floatN<N>(v2), a); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> clamp(const components<Dim...>& v1, const floatN<N>& v2, const floatN<N>& a) { return clamp(floatN<N>(v1), v2, a); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> clamp(const floatN<N>& v1, const components<Dim...>& v2, const components<Dim...>& a) { return clamp(v1, floatN<N>(v2), floatN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> clamp(const components<Dim...>& v1, const floatN<N>& v2, const components<Dim...>& a) { return clamp(floatN<N>(v1), v2, floatN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> clamp(const components<Dim...>& v1, const components<Dim...>& v2, const floatN<N>& a) { return clamp(floatN<N>(v1), floatN<N>(v2), a); }

	template<int...D1, int...D2, int...D3>
	hlslpp_inline floatN<sizeof...(D1)> clamp(const components<D1...>& v1, const components<D2...>& v2, const components<D3...>& a)
	{
		static_assert((sizeof...(D1) == sizeof...(D2)) && (sizeof...(D2) == sizeof...(D3)), "Vectors must be the same dimension");
		return floatN<sizeof...(D1)>(_hlslpp_clamp_ps((floatN<sizeof...(D1)>(v1)._vec), (floatN<sizeof...(D1)>(v2)._vec), (floatN<sizeof...(D3)>(a)._vec)));
	}

	template<int N>		hlslpp_inline floatN<N>					cos(const floatN<N>& v) { return floatN<N>(_hlslpp_cos_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>		cos(const components<Dim...>& v) { return components<Dim...>(_hlslpp_cos_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>					cosh(const floatN<N>& v) { return floatN<N>(_hlslpp_cosh_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>		cosh(const components<Dim...>& v) { return components<Dim...>(_hlslpp_cosh_ps(v._vec)); }

	hlslpp_inline float3 cross(const float3& v1, const float3& v2) { return float3(_hlslpp_cross_ps(v1._vec, v2._vec)); }

	template<int N>		hlslpp_inline floatN<N>					degrees(const floatN<N>& v) { return floatN<N>(_hlslpp_mul_ps(v._vec, f4_rad2deg)); }
	template<int...Dim>	hlslpp_inline components<Dim...>		degrees(const components<Dim...>& v) { return components<Dim...>(_hlslpp_mul_ps(v._vec, f4_rad2deg)); }

	hlslpp_inline float1 dot(const float2& v1, const float2& v2) { return float1(_hlslpp_dot2_ps(v1._vec, v2._vec)); }
	hlslpp_inline float1 dot(const float3& v1, const float3& v2) { return float1(_hlslpp_dot3_ps(v1._vec, v2._vec)); }
	hlslpp_inline float1 dot(const float4& v1, const float4& v2) { return float1(_hlslpp_dot4_ps(v1._vec, v2._vec)); }

	template<int N>		hlslpp_inline floatN<N>					exp(const floatN<N>& v) { return floatN<N>(_hlslpp_exp_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>		exp(const components<Dim...>& v) { return components<Dim...>(_hlslpp_exp_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>					exp2(const floatN<N>& v) { return floatN<N>(_hlslpp_exp2_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>		exp2(const components<Dim...>& v) { return components<Dim...>(_hlslpp_exp2_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>					floor(const floatN<N>& v) { return floatN<N>(_hlslpp_floor_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>		floor(const components<Dim...>& v) { return components<Dim...>(_hlslpp_floor_ps(v._vec)); }

	// A note on negative numbers. Contrary to intuition, frac(-0.75) != 0.75,
	// but is actually frac(-0.75) == 0.25 This is because hlsl defines frac
	// as frac(x) = x - floor(x)
	template<int N>		hlslpp_inline floatN<N>				frac(const floatN<N>& v) { return floatN<N>(_hlslpp_frac_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	frac(const components<Dim...>& v) { return components<Dim...>(_hlslpp_frac_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				isfinite(const floatN<N>& v) { return floatN<N>(_hlslpp_andnot_ps(_hlslpp_isfinite_ps(v._vec), f4_1)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	isfinite(const components<Dim...>& v) { return components<Dim...>(_hlslpp_andnot_ps(_hlslpp_isfinite_ps(v._vec), f4_1)); }

	template<int N>		hlslpp_inline floatN<N>				isinf(const floatN<N>& v) { return floatN<N>(_hlslpp_and_ps(_hlslpp_isinf_ps(v._vec), f4_1)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	isinf(const components<Dim...>& v) { return components<Dim...>(_hlslpp_and_ps(_hlslpp_isinf_ps(v._vec), f4_1)); }

	template<int N>		hlslpp_inline floatN<N>				isnan(const floatN<N>& v) { return floatN<N>(_hlslpp_and_ps(_hlslpp_isnan_ps(v._vec), f4_1)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	isnan(const components<Dim...>& v) { return components<Dim...>(_hlslpp_and_ps(_hlslpp_isnan_ps(v._vec), f4_1)); }

	//----- Length

	hlslpp_inline float1 length(const float1& v) { return v; }
	hlslpp_inline float1 length(const float2& v) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot2_ps(v._vec, v._vec))); }
	hlslpp_inline float1 length(const float3& v) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot3_ps(v._vec, v._vec))); }
	hlslpp_inline float1 length(const float4& v) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(v._vec, v._vec))); }

	template<int X, int Y, int Z, int W>
	hlslpp_inline float1 length(const component4<X, Y, Z, W>& v) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(v._vec, v._vec))); }

	//----- Lerp

	template<int N> hlslpp_inline floatN<N> lerp(const floatN<N>& v1, const floatN<N>& v2, const floatN<N>& a) { return floatN<N>(_hlslpp_lrp_ps(v1._vec, v2._vec, a._vec)); }

	template<int N> hlslpp_inline floatN<N> lerp(const floatN<N>& v1, const floatN<N>& v2, float a) { return lerp(v1, v2, floatN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> lerp(const floatN<N>& v1, const floatN<N>& v2, const components<Dim...>& a) { return lerp(v1, v2, floatN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> lerp(const floatN<N>& v1, const components<Dim...>& v2, const floatN<N>& a) { return lerp(v1, floatN<N>(v2), a); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> lerp(const components<Dim...>& v1, const floatN<N>& v2, const floatN<N>& a) { return lerp(floatN<N>(v1), v2, a); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> lerp(const floatN<N>& v1, const components<Dim...>& v2, const components<Dim...>& a) { return lerp(v1, floatN<N>(v2), floatN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> lerp(const components<Dim...>& v1, const floatN<N>& v2, const components<Dim...>& a) { return lerp(floatN<N>(v1), v2, floatN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> lerp(const components<Dim...>& v1, const components<Dim...>& v2, const floatN<N>& a) { return lerp(floatN<N>(v1), floatN<N>(v2), a); }

	template<int...D1, int...D2, int...D3>
	hlslpp_inline componentbase<sizeof...(D1)> lerp(const components<D1...>& v1, const components<D2...>& v2, const components<D3...>& a)
	{
		static_assert((sizeof...(D1) == sizeof...(D2)) && (sizeof...(D2) == sizeof...(D3)), "Vectors must be the same dimension");
		return componentbase<sizeof...(D1)>(_hlslpp_lrp_ps((componentbase<sizeof...(D1)>(v1)._vec), (componentbase<sizeof...(D1)>(v2)._vec), (componentbase<sizeof...(D3)>(a)._vec)));
	}

	//----- Log

	template<int N>		hlslpp_inline floatN<N>				log(const floatN<N>& v) { return floatN<N>(_hlslpp_log_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	log(const components<Dim...>& v) { return components<Dim...>(_hlslpp_log_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				log2(const floatN<N>& v) { return floatN<N>(_hlslpp_log2_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	log2(const components<Dim...>& v) { return components<Dim...>(_hlslpp_log2_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				log10(const floatN<N>& v) { return floatN<N>(_hlslpp_log10_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	log10(const components<Dim...>& v) { return components<Dim...>(_hlslpp_log10_ps(v._vec)); }

	//----- Minimum
	template<int N> hlslpp_inline floatN<N> min(const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_min_ps(v1._vec, v2._vec)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> min(const floatN<N>& v1, const components<Dim...>& v2) { return min(v1, floatN<N>(v2)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> min(const components<Dim...>& v1, const floatN<N>& v2) { return min(floatN<N>(v1), v2); }

	template<int...D1, int...D2>
	hlslpp_inline componentbase<sizeof...(D1)> min(const components<D1...>& v1, const components<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return componentbase<sizeof...(D1)>(_hlslpp_min_ps(componentbase<sizeof...(D1)>(v1)._vec, componentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Maximum
	template<int N> hlslpp_inline floatN<N> max(const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_max_ps(v1._vec, v2._vec)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> max(const floatN<N>& v1, const components<Dim...>& v2) { return max(v1, floatN<N>(v2)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> max(const components<Dim...>& v1, const floatN<N>& v2) { return max(floatN<N>(v1), v2); }

	template<int...D1, int...D2>
	hlslpp_inline componentbase<sizeof...(D1)> max(const components<D1...>& v1, const components<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return componentbase<sizeof...(D1)>(_hlslpp_max_ps(componentbase<sizeof...(D1)>(v1)._vec, componentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Normalize

	template<int X, int Y, int Z, int W>
	hlslpp_inline component4<0, 1, 2, 3>	normalize(const component4<X, Y, Z, W>& v) { return component4<0, 1, 2, 3>(_hlslpp_div_ps(v._vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(v._vec, v._vec))))); }

	hlslpp_inline float4					normalize(const float4& v) { return float4(_hlslpp_div_ps(v._vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(v._vec, v._vec))))); }
	hlslpp_inline float3					normalize(const float3& v) { return float3(_hlslpp_div_ps(v._vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot3_ps(v._vec, v._vec))))); }
	hlslpp_inline float2					normalize(const float2& v) { return float2(_hlslpp_div_ps(v._vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot2_ps(v._vec, v._vec))))); }
	hlslpp_inline float1					normalize(const float1&) { return float1(1.0f); }

	//----- Pow
	template<int N> hlslpp_inline floatN<N> pow(const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_exp2_ps(_hlslpp_mul_ps(v1._vec, _hlslpp_log2_ps(v2._vec)))); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> pow(const floatN<N>& v1, const components<Dim...>& v2) { return pow(v1, floatN<N>(v2)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> pow(const components<Dim...>& v1, const floatN<N>& v2) { return pow(floatN<N>(v1), v2); }

	template<int...D1, int...D2>
	hlslpp_inline floatN<sizeof...(D1)> pow(const components<D1...>& v1, const components<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return floatN<sizeof...(D1)>(_hlslpp_exp2_ps(_hlslpp_mul_ps(floatN<sizeof...(D1)>(v1)._vec, _hlslpp_log2_ps(floatN<sizeof...(D1)>(v2)._vec))));
	}

	template<int N>		hlslpp_inline floatN<N>				radians(const floatN<N>& v) { return floatN<N>(_hlslpp_mul_ps(v._vec, f4_deg2rad)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	radians(const components<Dim...>& v) { return components<Dim...>(_hlslpp_mul_ps(v._vec, f4_deg2rad)); }

	template<int N>		hlslpp_inline floatN<N>				rcp(const floatN<N>& v) { return floatN<N>(_hlslpp_rcp_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	rcp(const components<Dim...>& v) { return components<Dim...>(_hlslpp_rcp_ps(v._vec)); }

	hlslpp_inline float1 reflect(const float1& i, const float1& n) { return float1(_hlslpp_sub_ps(i._vec, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n._vec, _hlslpp_perm_xxxx_ps(_hlslpp_mul_ps(i._vec, n._vec)))))); }
	hlslpp_inline float2 reflect(const float2& i, const float2& n) { return float2(_hlslpp_sub_ps(i._vec, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n._vec, _hlslpp_perm_xxxx_ps(_hlslpp_dot2_ps(i._vec, n._vec)))))); }
	hlslpp_inline float3 reflect(const float3& i, const float3& n) { return float3(_hlslpp_sub_ps(i._vec, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n._vec, _hlslpp_perm_xxxx_ps(_hlslpp_dot3_ps(i._vec, n._vec)))))); }
	hlslpp_inline float4 reflect(const float4& i, const float4& n) { return float4(_hlslpp_sub_ps(i._vec, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n._vec, _hlslpp_perm_xxxx_ps(_hlslpp_dot4_ps(i._vec, n._vec)))))); }

	template<int N>		hlslpp_inline floatN<N>				rsqrt(const floatN<N>& v) { return floatN<N>(_hlslpp_rsqrt_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	rsqrt(const components<Dim...>& v) { return components<Dim...>(_hlslpp_rsqrt_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				round(const floatN<N>& v) { return floatN<N>(_hlslpp_round_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	round(const components<Dim...>& v) { return components<Dim...>(_hlslpp_round_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				saturate(const floatN<N>& v) { return floatN<N>(_hlslpp_sat_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	saturate(const components<Dim...>& v) { return components<Dim...>(_hlslpp_sat_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				sign(const floatN<N>& v) {	return floatN<N>(_hlslpp_sign_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	sign(const components<Dim...>& v) { return components<Dim...>(_hlslpp_sign_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				sin(const floatN<N>& v) { return floatN<N>(_hlslpp_sin_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	sin(const components<Dim...>& v) { return components<Dim...>(_hlslpp_sin_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				sinh(const floatN<N>& v) { return floatN<N>(_hlslpp_sinh_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	sinh(const components<Dim...>& v) { return components<Dim...>(_hlslpp_sinh_ps(v._vec)); }

	//----- smoothstep

	template<int N> hlslpp_inline floatN<N> smoothstep(const floatN<N>& v1, const floatN<N>& v2, const floatN<N>& a) { return floatN<N>(_hlslpp_smoothstep_ps(v1._vec, v2._vec, a._vec)); }

	template<int N> hlslpp_inline floatN<N> smoothstep(const floatN<N>& v1, const floatN<N>& v2, float a) { return smoothstep(v1, v2, floatN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> smoothstep(const floatN<N>& v1, const floatN<N>& v2, const components<Dim...>& a) { return smoothstep(v1, v2, floatN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> smoothstep(const floatN<N>& v1, const components<Dim...>& v2, const floatN<N>& a) { return smoothstep(v1, floatN<N>(v2), a); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> smoothstep(const components<Dim...>& v1, const floatN<N>& v2, const floatN<N>& a) { return smoothstep(floatN<N>(v1), v2, a); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> smoothstep(const floatN<N>& v1, const components<Dim...>& v2, const components<Dim...>& a) { return smoothstep(v1, floatN<N>(v2), floatN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> smoothstep(const components<Dim...>& v1, const floatN<N>& v2, const components<Dim...>& a) { return smoothstep(floatN<N>(v1), v2, floatN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> smoothstep(const components<Dim...>& v1, const components<Dim...>& v2, const floatN<N>& a) { return smoothstep(floatN<N>(v1), floatN<N>(v2), a); }

	template<int...D1, int...D2, int...D3>
	hlslpp_inline componentbase<sizeof...(D1)> smoothstep(const components<D1...>& v1, const components<D2...>& v2, const components<D3...>& a)
	{
		static_assert((sizeof...(D1) == sizeof...(D2)) && (sizeof...(D2) == sizeof...(D3)), "Vectors must be the same dimension");
		return componentbase<sizeof...(D1)>(_hlslpp_smoothstep_ps((componentbase<sizeof...(D1)>(v1)._vec), (componentbase<sizeof...(D1)>(v2)._vec), (componentbase<sizeof...(D3)>(a)._vec)));
	}

	template<int N>		hlslpp_inline floatN<N>				sqrt(const floatN<N>& v) { return floatN<N>(_hlslpp_sqrt_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	sqrt(const components<Dim...>& v) { return components<Dim...>(_hlslpp_sqrt_ps(v._vec)); }

	//----- Step
	// Hlsl, glsl and Cg behavior is to swap the operands.
	// http://http.developer.nvidia.com/Cg/step.html
	// https://www.opengl.org/sdk/docs/man/html/step.xhtml
	template<int N> hlslpp_inline floatN<N> step(const floatN<N>& v1, const floatN<N>& v2) { return v1 >= v2; }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> step(const floatN<N>& v1, const components<Dim...>& v2) { return v1 >= floatN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline floatN<N> step(const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) >= v2; }

	template<int...Dim1, int...Dim2>
	hlslpp_inline floatN<sizeof...(Dim1)> step(const components<Dim1...>& v1, const components<Dim2...>& v2)
	{
		static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
		return floatN<sizeof...(Dim1)>(v1) >= floatN<sizeof...(Dim1)>(v2);
	}

	template<int N>		hlslpp_inline floatN<N>				tan(const floatN<N>& v) { return floatN<N>(_hlslpp_tan_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	tan(const components<Dim...>& v) { return components<Dim...>(_hlslpp_tan_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				tanh(const floatN<N>& v) { return floatN<N>(_hlslpp_tanh_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	tanh(const components<Dim...>& v) { return components<Dim...>(_hlslpp_tanh_ps(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				trunc(const floatN<N>& v) { return floatN<N>(_hlslpp_trunc_ps(v._vec)); }
	template<int...Dim>	hlslpp_inline components<Dim...>	trunc(const components<Dim...>& v) { return components<Dim...>(_hlslpp_trunc_ps(v._vec)); }

	// hlslpp_forceinline float4 normalize_fast(const float4& v)
	// {
	// 	return float4(_hlslpp_mul_ps(v._vec, _hlslpp_perm_xxxx_ps(_mm_rsqrt_ps(_hlslpp_dot4_ps(v._vec, v._vec)))));
	// }

	// https://books.google.co.uk/books?id=yphBBAAAQBAJ&pg=PA99&lpg=PA99&dq=_mm_cmpnltps&source=bl&ots=zLVjV__tgU&sig=8uNKfkS_-hIbiLRSFODgG5EWMzw&hl=en&sa=X&ved=0ahUKEwjlkY3126nRAhUHI8AKHSqUCJ4Q6AEIGjAA#v=onepage&q&f=false
	//hlslpp_forceinline float4 atan2
	//hlslpp_forceinline float4 modf

	//----------------------------
	// Component integer functions
	//----------------------------

	template<int A>
	template<int E>
	hlslpp_inline icomponents<A>::icomponents(const icomponent1<E>& c) { *this = c; }

	template<int A>
	template<int E>
	hlslpp_inline icomponents<A>& icomponents<A>::operator = (const icomponent1<E>& c)
	{
		n128i s = _hlslpp_shuffle_epi32(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(E, E, E, E));
		_vec = _hlslpp_blend_epi32(_vec, s, HLSLPP_COMPONENT_X(A));
		return *this;
	}

	template<int A>
	hlslpp_inline icomponents<A>& icomponents<A>::operator = (int32_t i)
	{
		_vec = _hlslpp_blend_epi32(_vec, _hlslpp_set1_epi32(i), HLSLPP_COMPONENT_X(A));
		return *this;
	}

	template<int A>
	hlslpp_inline icomponents<A>& icomponents<A>::operator = (const int1& v) { _vec = _hlslpp_blend_epi32(_vec, v._vec, HLSLPP_COMPONENT_X(A)); return *this; }

	//template<int A>
	//hlslpp_inline icomponents<A>& icomponents<A>::operator = (const int1x1& m) { _vec = _hlslpp_blend_epi32(_vec, m._vec, HLSLPP_COMPONENT_X(A)); return *this; }

	template<int A, int B>
	template<int E, int F>
	hlslpp_inline icomponents<A, B>::icomponents(const icomponent2<E, F>& c) { *this = c; }

	template<int A, int B>
	template<int E, int F>
	hlslpp_inline icomponents<A, B>& icomponents<A, B>::operator = (const icomponent2<E, F>& c)
	{
		staticAsserts();
		_vec = blend(_vec, swizzle<E, F, A, B>(c._vec));
		return *this;
	}

	template<int A, int B>
	hlslpp_inline icomponents<A, B>& icomponents<A, B>::operator = (const icomponent2<A, B>& c) { _vec = _hlslpp_blend_epi32(_vec, c._vec, HLSLPP_BLEND_MASK(0, 0, 1, 1)); return *this; }

	template<int A, int B>
	hlslpp_inline icomponents<A, B>& icomponents<A, B>::operator = (const int2& v)
	{
		staticAsserts();
		_vec = blend(_vec, swizzle<0, 1, A, B>(v._vec));
		return *this;
	}

	template<int A, int B, int C>
	template<int E, int F, int G>
	hlslpp_inline icomponents<A, B, C>::icomponents(const icomponent3<E, F, G>& c) { *this = c; }

	template<int A, int B, int C>
	template<int E, int F, int G>
	hlslpp_inline icomponents<A, B, C>& icomponents<A, B, C>::operator = (const icomponent3<E, F, G>& c)
	{
		staticAsserts();
		_vec = blend(_vec, swizzle<E, F, G, A, B, C>(c._vec));
		return *this;
	}

	template<int A, int B, int C>
	hlslpp_inline icomponents<A, B, C>& icomponents<A, B, C>::operator = (const icomponent3<A, B, C>& c) { _vec = _hlslpp_blend_epi32(_vec, c._vec, HLSLPP_BLEND_MASK(0, 0, 0, 1)); return *this; }

	template<int A, int B, int C>
	hlslpp_inline icomponents<A, B, C>& icomponents<A, B, C>::operator = (const int3& v)
	{
		staticAsserts();
		_vec = blend(_vec, swizzle<0, 1, 2, A, B, C>(v._vec));
		return *this;
	}

	template<int A, int B, int C, int D>
	template<int E, int F, int G, int H>
	hlslpp_inline icomponents<A, B, C, D>::icomponents(const icomponent4<E, F, G, H>& c) { *this = c; }

	template<int A, int B, int C, int D>
	template<int E, int F, int G, int H>
	hlslpp_inline icomponents<A, B, C, D>& icomponents<A, B, C, D>::operator = (const icomponent4<E, F, G, H>& c)
	{
		staticAsserts();
		const uint32_t mask = HLSLPP_SHUFFLE_MASK(E, F, G, H);
		const uint32_t reshuffleMask = ((mask & 3) << (2 * A)) | (((mask >> 2) & 3) << (2 * B)) | (((mask >> 4) & 3) << (2 * C)) | (((mask >> 6) & 3) << (2 * D));	// Re-swizzle with property mask
		_vec = _hlslpp_shuffle_epi32(c._vec, c._vec, reshuffleMask);

		// Reference for correctness
		//p = _mm_shuffle_epi32(f.p, f.p, _MM_SHUFFLE(H, G, F, E));
		//p = _mm_shuffle_epi32(p, p, _MM_SHUFFLE(D, C, B, A));

		return *this;
	}

	template<int A, int B, int C, int D>
	hlslpp_inline icomponents<A, B, C, D>& icomponents<A, B, C, D>::operator = (const icomponent4<A, B, C, D>& c) { _vec = c._vec; return *this; }

	template<int A, int B, int C, int D>
	hlslpp_inline icomponents<A, B, C, D>& icomponents<A, B, C, D>::operator = (const int4& v)
	{
		staticAsserts();
		_vec = _hlslpp_shuffle_epi32(v._vec, v._vec, HLSLPP_SHUFFLE_MASK(A, B, C, D));
		return *this;
	}

	template<> // Optimize a straight copy via explicit instantiation (doesn't produce/need the shuffle)
	hlslpp_inline icomponents<0, 1, 2, 3>& icomponents<0, 1, 2, 3>::operator = (const int4& v) { _vec = v._vec; return *this; }

	//----------------------------
	// Vector integer constructors
	//----------------------------

	//----- int1

	template<int A> hlslpp_inline int1::intN(const icomponent1<A>& c) { _vec = _hlslpp_shuffle_epi32(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(A, A, A, A)); }

	template<> hlslpp_inline int1::intN(const icomponent1<0>& c) { _vec = c._vec; }

	//hlslpp_inline int1::intN(const int1x1& v) { _vec = v._vec; }

	hlslpp_inline int1& int1::operator = (const int1& v) { _vec = v._vec; return *this; }

	hlslpp_inline int1& int1::operator = (int32_t i) { _vec = _hlslpp_set_epi32(i, 0, 0, 0); return *this; }

	template<int A> hlslpp_inline int1& int1::operator = (const icomponent1<A>& c) { _vec = _hlslpp_shuffle_epi32(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(A, A, A, A)); return *this; }

	template<> hlslpp_inline int1& int1::operator = (const icomponent1<0>& c) { _vec = c._vec; return *this; }

	//hlslpp_inline int1& int1::operator = (const int1x1& m) { _vec = m._vec; return *this; }

	template<int N, enable_if_dim<(N == 1)> > hlslpp_inline int1::intN(const floatN<N>& v) { _vec = _hlslpp_cvtps_epi32(v._vec); }

	//----- int2

	hlslpp_inline int2::intN(const int1& v1, const int1& v2) { _vec = _hlslpp_blend_epi32(v1._vec, _hlslpp_perm_xxxx_epi32(v2._vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }

	template<int A, int B>
	hlslpp_inline int2::intN(const icomponent2<A, B>& c) { _vec = icomponent2<A, B>::template swizzle<A, B, 0, 1>(c._vec); }

	template<> hlslpp_inline int2::intN(const icomponent2<0, 1>& c) { _vec = c._vec; }

	//hlslpp_inline int2::intN(const int2x1& v) { _vec = v._vec; }

	//hlslpp_inline int2::intN(const int1x2& v) { _vec = v._vec; }

	template<int N, enable_if_dim<(N == 2)> > hlslpp_inline int2::intN(const floatN<N>& v) { _vec = _hlslpp_cvtps_epi32(v._vec); }

	hlslpp_inline int2& int2::operator = (const int2& v) { _vec = v._vec; return *this; }

	template<int A, int B>
	hlslpp_inline int2& int2::operator = (const icomponent2<A, B>& c) { _vec = icomponent2<A, B>::template swizzle<A, B, 0, 1>(c._vec); return *this; }

	template<>
	hlslpp_inline int2& int2::operator = (const icomponent2<0, 1>& c) { _vec = c._vec; return *this; }

	//----- int3

	template<int A, int B, int C>
	hlslpp_inline int3::intN(const icomponent3<A, B, C>& c) { _vec = icomponent3<A, B, C>::template swizzle<A, B, C, 0, 1, 2>(c._vec); }

	template<>
	hlslpp_inline int3::intN(const icomponent3<0, 1, 2>& c) { _vec = c._vec; }

	hlslpp_inline int3::intN(const intN<1>& v1, const intN<1>& v2, const intN<1>& v3) { _vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxx_epi32(v1._vec, v3._vec), _hlslpp_perm_xxxx_epi32(v2._vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }

	hlslpp_inline int3::intN(const int32_t v1, const intN<1>& v2, const intN<1>& v3) : int3(int1(v1), v2, v3) {}
	hlslpp_inline int3::intN(const intN<1>& v1, const int32_t v2, const intN<1>& v3) : int3(v1, int1(v2), v3) {}
	hlslpp_inline int3::intN(const intN<1>& v1, const intN<1>& v2, const int32_t v3) : int3(v1, v2, int1(v3)) {}
	hlslpp_inline int3::intN(const int32_t v1, const int32_t v2, const intN<1>& v3) : int3(int2(v1, v2), v3) {}
	hlslpp_inline int3::intN(const intN<1>& v1, const int32_t v2, const int32_t v3) : int3(v1, int2(v2, v3)) {}
	hlslpp_inline int3::intN(const int32_t v1, const intN<1>& v2, const int32_t v3) : int3(int1(v1), v2, int1(v3)) {}

	hlslpp_inline int3::intN(const intN<2>& v1, const intN<1>& v2) { _vec = _hlslpp_shuf_xyxx_epi32(v1._vec, v2._vec); }

	hlslpp_inline int3::intN(const intN<1>& v1, const intN<2>& v2) { _vec = _hlslpp_blend_epi32(v1._vec, _hlslpp_perm_xxyx_epi32(v2._vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }

	//hlslpp_inline int3::intN(const int3x1& v) { _vec = v._vec; }

	//hlslpp_inline int3::intN(const int1x3& v) { _vec = v._vec; }

	template<int N, enable_if_dim<(N == 3)> > hlslpp_inline int3::intN(const floatN<N>& v) { _vec = _hlslpp_cvtps_epi32(v._vec); }

	hlslpp_inline int3& int3::operator = (const int3& v) { _vec = v._vec; return *this; }

	template<int A, int B, int C>
	hlslpp_inline int3& int3::operator = (const icomponent3<A, B, C>& c) { _vec = icomponent3<A, B, C>::template swizzle<A, B, C, 0, 1, 2>(c._vec); return *this; }

	template<>
	hlslpp_inline int3& int3::operator = (const icomponent3<0, 1, 1>& c) { _vec = c._vec; return *this; }

	//----- int4

	hlslpp_inline int4::intN(const int1& v1, const int1& v2, const int1& v3, const int1& v4)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxx_epi32(v1._vec, v3._vec), _hlslpp_shuf_xxxx_epi32(v2._vec, v4._vec), HLSLPP_BLEND_MASK(1, 0, 1, 0));
	}

	hlslpp_inline int4::intN(const int1& v1, const int3& v2)
	{
		_vec = _hlslpp_blend_epi32(v1._vec, _hlslpp_perm_xxyz_epi32(v2._vec), HLSLPP_BLEND_MASK(1, 0, 0, 0));
	}

	hlslpp_inline int4::intN(const int3& v1, const int1& v2)
	{
		_vec = _hlslpp_blend_epi32(v1._vec, _hlslpp_perm_xxxx_epi32(v2._vec), HLSLPP_BLEND_MASK(1, 1, 1, 0));
	}

	hlslpp_inline int4::intN(const int2& v1, const int2& v2)
	{
		_vec = _hlslpp_shuf_xyxy_epi32(v1._vec, v2._vec);
	}

	hlslpp_inline int4::intN(const int2& v1, const int1& v2, const int1& v3)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_shuf_xyxx_epi32(v1._vec, v2._vec), _hlslpp_perm_xxxx_epi32(v3._vec), HLSLPP_BLEND_MASK(1, 1, 1, 0));
	}

	hlslpp_inline int4::intN(const int1& v1, const int2& v2, const int1& v3)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxx_epi32(v1._vec, v3._vec), _hlslpp_perm_xxyx_epi32(v2._vec), HLSLPP_BLEND_MASK(1, 0, 0, 1));
	}

	hlslpp_inline int4::intN(const int1& v1, const int1& v2, const int2& v3)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxy_epi32(v1._vec, v3._vec), _hlslpp_perm_xxxx_epi32(v2._vec), HLSLPP_BLEND_MASK(1, 0, 1, 1));
	}

	hlslpp_inline int4::intN(const int32_t v1, const int32_t v2, const int1& v3, const int1& v4)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_set_epi32(v1, v2, 0, 0), _hlslpp_perm_xzxz_epi32(_hlslpp_shuf_xxxx_epi32(v3._vec, v4._vec)), HLSLPP_BLEND_MASK(1, 1, 0, 0));
	}

	hlslpp_inline int4::intN(const int32_t v1, const int1& v2, const int32_t v3, const int1& v4)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_set_epi32(v1, 0, v3, 0), _hlslpp_shuf_xxxx_epi32(v2._vec, v4._vec), HLSLPP_BLEND_MASK(1, 0, 1, 0));
	}

	hlslpp_inline int4::intN(const int32_t v1, const int1& v2, const int1& v3, const int32_t v4)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_set_epi32(v1, 0, 0, v4), _hlslpp_shuf_xxxx_epi32(v2._vec, v3._vec), HLSLPP_BLEND_MASK(1, 0, 0, 1));
	}

	hlslpp_inline int4::intN(const int1& v1, const int32_t v2, const int32_t v3, const int1& v4)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_set_epi32(0, v2, v3, 0), _hlslpp_shuf_xxxx_epi32(v1._vec, v4._vec), HLSLPP_BLEND_MASK(0, 1, 1, 0));
	}

	hlslpp_inline int4::intN(const int1& v1, const int32_t v2, const int1& v3, const int32_t v4)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_set_epi32(0, v2, 0, v4), _hlslpp_shuf_xxxx_epi32(v1._vec, v3._vec), HLSLPP_BLEND_MASK(0, 1, 0, 1));
	}

	hlslpp_inline int4::intN(const int1& v1, const int1& v2, const int32_t v3, const int32_t v4)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_set_epi32(0, 0, v3, v4), _hlslpp_perm_xzxz_epi32(_hlslpp_shuf_xxxx_epi32(v1._vec, v2._vec)), HLSLPP_BLEND_MASK(0, 0, 1, 1));
	}

	hlslpp_inline int4::intN(const int32_t v1, const int32_t v2, const int32_t v3, const int1& v4)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_set_epi32(v1, v2, v3, 0), _hlslpp_perm_xxxx_epi32(v4._vec), HLSLPP_BLEND_MASK(1, 1, 1, 0));
	}

	hlslpp_inline int4::intN(const int32_t v1, const int32_t v2, const int1& v3, const int32_t v4)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_set_epi32(v1, v2, 0, v4), _hlslpp_perm_xxxx_epi32(v3._vec), HLSLPP_BLEND_MASK(1, 1, 0, 1));
	}

	hlslpp_inline int4::intN(const int32_t v1, const int1& v2, const int32_t v3, const int32_t v4)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_set_epi32(v1, 0, v3, v4), _hlslpp_perm_xxxx_epi32(v2._vec), HLSLPP_BLEND_MASK(1, 0, 1, 1));
	}

	hlslpp_inline int4::intN(const int1& v1, const int32_t v2, const int32_t v3, const int32_t v4)
	{
		_vec = _hlslpp_blend_epi32(_hlslpp_set_epi32(0, v2, v3, v4), v1._vec, HLSLPP_BLEND_MASK(0, 1, 1, 1));
	}

	template<int A, int B, int C, int D>
	hlslpp_inline int4::intN(const icomponent4<A, B, C, D>& c) { *this = c; }

	template<> hlslpp_inline int4::intN(const icomponent4<0, 1, 2, 3>& c) { _vec = c._vec; } // Optimize a straight copy if the indices match 0, 1, 2, 3 (doesn't produce/need the shuffle)

	//hlslpp_inline int4::intN(const int4x1& v) { _vec = v._vec; }

	//hlslpp_inline int4::intN(const int1x4& v) { _vec = v._vec; }

	template<int N, enable_if_dim<(N == 4)> > hlslpp_inline int4::intN(const floatN<N>& v) { _vec = _hlslpp_cvtps_epi32(v._vec); }

	hlslpp_inline int4& int4::operator = (const int4& v) { _vec = v._vec; return *this; }

	template<int A, int B, int C, int D>
	hlslpp_inline int4& int4::operator = (const icomponent4<A, B, C, D>& c)
	{
		_vec = _hlslpp_shuffle_epi32(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(A, B, C, D));
		return *this;
	}

	template<> hlslpp_inline int4& int4::operator = (const icomponent4<0, 1, 2, 3>& c) { _vec = c._vec; return *this; } // Optimize a straight copy if the indices match 0, 1, 2, 3 (doesn't produce/need the shuffle)


	//-------------------------
	// Vector integer functions
	//-------------------------

	//----- Addition

	template<int N> hlslpp_inline intN<N> operator + (const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_add_epi32(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline intN<N> operator + (const intN<N>& v1, const int32_t v2) { return v1 + intN<N>(v2); }
	template<int N> hlslpp_inline intN<N> operator + (const int32_t v1, const intN<N>& v2) { return intN<N>(v1) + v2; }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator + (const intN<N>& v1, const icomponents<Dim...>& v2) { return v1 + intN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator + (const icomponents<Dim...>& v1, const intN<N>& v2) { return intN<N>(v1) + v2; }

	template<int...Dim1, int...Dim2>
	hlslpp_inline intN<sizeof...(Dim1)> operator + (const icomponents<Dim1...>& v1, const icomponents<Dim2...>& v2)
	{
		static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension");
		return intN<sizeof...(Dim1)>(_hlslpp_add_epi32(intN<sizeof...(Dim1)>(v1)._vec, intN<sizeof...(Dim1)>(v2)._vec));
	}

	template<int N> hlslpp_inline intN<N> operator + (const intN<N>& v1, const int1& v2) { return v1 + intN<N>(_hlslpp_perm_xxxx_epi32(v2._vec)); }
	template<int N> hlslpp_inline intN<N> operator + (const int1& v1, const intN<N>& v2) { return intN<N>(_hlslpp_perm_xxxx_epi32(v1._vec) + v2); }
	hlslpp_inline int1 operator + (const int1& v1, const int1& v2) { return int1(_hlslpp_add_epi32(v1._vec, v2._vec)); } // A bit more optimal as it avoids the shuffle

	//----- Plus equals

	template<int N> hlslpp_inline intN<N>& operator += (intN<N>& v1, const intN<N>& v2) { v1 = v1 + v2; return v1; }

	template<int N> hlslpp_inline intN<N>& operator += (intN<N>& v1, const int32_t v2) { v1 = v1 + intN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline intN<N>& operator += (intN<N>& v1, const icomponents<Dim...>& v2) { v1 = v1 + intN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline icomponents<Dim...>& operator += (icomponents<Dim...>& v1, const intN<N>& v2) { v1 = intN<N>(v1) + v2; return v1; }

	template<int...Dim1, int...Dim2>
	hlslpp_inline icomponents<Dim1...>& operator += (icomponents<Dim1...>& v1, const icomponents<Dim2...>& v2)
	{ 
		static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension");
		v1 = intN<sizeof...(Dim1)>(v1) + intN<sizeof...(Dim1)>(v2); return v1;
	}

	template<int N> hlslpp_inline intN<N>& operator += (intN<N>& v1, const int1& v2) { v1 = v1 + v2; return v1; }
	hlslpp_inline int1& operator += (int1& v1, const int1& v2) { v1 = v1 + v2; return v1; }

	//----- Subtraction

	template<int N> hlslpp_inline intN<N> operator - (const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_sub_epi32(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline intN<N> operator - (const intN<N>& v1, const int32_t v2) { return v1 - intN<N>(v2); }
	template<int N> hlslpp_inline intN<N> operator - (const int32_t v1, const intN<N>& v2) { return intN<N>(v1) - v2; }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator - (const intN<N>& v1, const icomponents<Dim...>& v2) { return v1 - intN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator - (const icomponents<Dim...>& v1, const intN<N>& v2) { return intN<N>(v1) - v2; }

	template<int...D1, int...D2>
	hlslpp_inline icomponentbase<sizeof...(D1)> operator - (const icomponents<D1...>& v1, const icomponents<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return icomponentbase<sizeof...(D1)>(_hlslpp_sub_epi32(icomponentbase<sizeof...(D1)>(v1)._vec, icomponentbase<sizeof...(D1)>(v2)._vec));
	}

	template<int N>
	hlslpp_inline intN<N> operator - (const intN<N>& v1, const int1& v2) { return v1 - intN<N>(_hlslpp_perm_xxxx_epi32(v2._vec)); }
	hlslpp_inline int1 operator - (const int1& v1, const int1& v2) { return int1(_hlslpp_sub_epi32(v1._vec, v2._vec)); } // A bit more optimal as it avoids the shuffle

	//----- Minus equals

	template<int N> hlslpp_inline intN<N>& operator -= (intN<N>& v1, const intN<N>& v2) { v1 = v1 - v2; return v1; }

	template<int N> hlslpp_inline intN<N>& operator -= (intN<N>& v1, const int32_t v2) { v1 = v1 - intN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline intN<N>& operator -= (intN<N>& v1, const icomponents<Dim...>& v2) { v1 = v1 - intN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline icomponents<Dim...>& operator -= (icomponents<Dim...>& v1, const intN<N>& v2) { v1 = intN<N>(v1) - v2; return v1; }

	template<int...Dim1, int...Dim2>
	hlslpp_inline icomponents<Dim1...>& operator -= (icomponents<Dim1...>& v1, const icomponents<Dim2...>& v2)
	{
		static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
		v1 = intN<sizeof...(Dim1)>(v1) - intN<sizeof...(Dim1)>(v2); return v1;
	}

	template<int N> hlslpp_inline intN<N>& operator -= (intN<N>& v1, const int1& v2) { v1 = v1 - v2; return v1; }
	hlslpp_inline int1& operator -= (int1& v1, const int1& v2) { v1 = v1 - v2; return v1; }

	//----- Multiplication

	template<int N> hlslpp_inline intN<N> operator * (const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_mul_epi32(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline intN<N> operator * (const intN<N>& v1, const int32_t v2) { return v1 * intN<N>(v2); }
	template<int N> hlslpp_inline intN<N> operator * (const int32_t v1, const intN<N>& v2) { return intN<N>(v1) * v2; }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator * (const intN<N>& v1, const icomponents<Dim...>& v2) { return v1 * intN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator * (const icomponents<Dim...>& v1, const intN<N>& v2) { return intN<N>(v1) * v2; }

	template<int...Dim1, int...Dim2>
	hlslpp_inline intN<sizeof...(Dim1)> operator * (const icomponents<Dim1...>& v1, const icomponents<Dim2...>& v2)
	{
		static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension");
		return intN<sizeof...(Dim1)>(_hlslpp_mul_epi32(intN<sizeof...(Dim1)>(v1)._vec, intN<sizeof...(Dim1)>(v2)._vec));
	}

	template<int N> hlslpp_inline intN<N> operator * (const intN<N>& v1, const int1& v2) { return v1 * intN<N>(_hlslpp_perm_xxxx_epi32(v2._vec)); }
	hlslpp_inline int1 operator * (const int1& v1, const int1& v2) { return int1(_hlslpp_mul_epi32(v1._vec, v2._vec)); } // A bit more optimal as it avoids the shuffle

	//----- Times equals

	template<int N> hlslpp_inline intN<N>& operator *= (intN<N>& v1, const intN<N>& v2) { v1 = v1 * v2; return v1; }

	template<int N> hlslpp_inline intN<N>& operator *= (intN<N>& v1, const int32_t v2) { v1 = v1 * intN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline intN<N>& operator *= (intN<N>& v1, const icomponents<Dim...>& v2) { v1 = v1 * intN<N>(v2); return v1; }

	template<int N, int...Dim>
	hlslpp_inline icomponents<Dim...>& operator *= (icomponents<Dim...>& v1, const intN<N>& v2) { v1 = intN<N>(v1) * v2; return v1; }

	template<int...Dim1, int...Dim2>
	hlslpp_inline icomponents<Dim1...>& operator *= (icomponents<Dim1...>& v1, const icomponents<Dim2...>& v2)
	{
		static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
		v1 = intN<sizeof...(Dim1)>(v1) * intN<sizeof...(Dim1)>(v2); return v1;
	}

	template<int N>
	hlslpp_inline intN<N>& operator *= (intN<N>& v1, const int1& v2) { v1 = v1 * v2; return v1; }
	hlslpp_inline int1& operator *= (int1& v1, const int1& v2) { v1 = v1 * v2; return v1; }

//	//----- Division

// 	template<int N> hlslpp_inline intN<N> operator / (const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_div_epi32(v1._vec, v2._vec)); }
// 
// 	template<int N> hlslpp_inline intN<N> operator / (const intN<N>& v1, const int32_t v2) { return v1 / intN<N>(v2); }
// 	template<int N> hlslpp_inline intN<N> operator / (const int32_t v1, const intN<N>& v2) { return intN<N>(v1) / v2; }
// 
// 	template<int N, int...Dim>
// 	hlslpp_inline intN<N> operator / (const intN<N>& v1, const icomponents<Dim...>& v2) { return v1 / intN<N>(v2); }
// 
// 	template<int N, int...Dim>
// 	hlslpp_inline intN<N> operator / (const icomponents<Dim...>& v1, const intN<N>& v2) { return intN<N>(v1) / v2; }
// 
// 	template<int...D1, int...D2>
// 	hlslpp_inline intN<sizeof...(D1)> operator / (const icomponents<D1...>& v1, const icomponents<D2...>& v2)
// 	{
// 		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
// 		return intN<sizeof...(D1)>(_hlslpp_div_epi32(intN<sizeof...(D1)>(v1)._vec, intN<sizeof...(D1)>(v2)._vec));
// 	}
// 
// 	template<int N> inline intN<N> operator / (const intN<N>& v1, const int1& v2) { return v1 / intN<N>(_hlslpp_perm_xxxx_epi32(v2._vec)); }
// 	hlslpp_inline int1 operator / (const int1& v1, const int1& v2) { return int1(0); }// int1(_hlslpp_div_epi32(v1._vec, v2._vec)); } // A bit more optimal as it avoids the shuffle
// 
// 	//----- Divide equals
// 
// 	template<int N> hlslpp_inline intN<N>& operator /= (intN<N>& v1, const intN<N>& v2) { v1 = v1 / v2; return v1; }
// 
// 	template<int N> hlslpp_inline intN<N>& operator /= (intN<N>& v1, const int32_t v2) { v1 = v1 / intN<N>(v2); return v1; }
// 
// 	template<int N, int...Dim>
// 	hlslpp_inline intN<N>& operator /= (intN<N>& v1, const icomponents<Dim...>& v2) { v1 = v1 / intN<N>(v2); return v1; }
// 
// 	template<int N, int...Dim>
// 	hlslpp_inline icomponents<Dim...>& operator /= (icomponents<Dim...>& v1, const intN<N>& v2) { v1 = intN<N>(v1) / v2; return v1; }
// 
// 	template<int...Dim1, int...Dim2>
// 	hlslpp_inline icomponents<Dim1...>& operator /= (icomponents<Dim1...>& v1, const icomponents<Dim2...>& v2)
// 	{
// 		static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
// 		v1 = intN<sizeof...(Dim1)>(v1) / intN<sizeof...(Dim1)>(v2); return v1;
// 	}
// 
// 	template<int N> hlslpp_inline intN<N>& operator /= (intN<N>& v1, const int1& v2) { v1 = v1 / v2; return v1; }
// 	hlslpp_inline int1& operator /= (int1& v1, const int1& v2) { v1 = v1 / v2; return v1; }

	//----- Negation

	template<int N> hlslpp_inline intN<N> operator - (const intN<N>& v) { return intN<N>(_hlslpp_neg_epi32(v._vec)); }

	template<int...D>
	hlslpp_inline icomponents<D...> operator - (const icomponents<D...>& v) { return icomponents<D...>(_hlslpp_neg_epi32(v._vec)); }

	//----- Equals

	template<int N> hlslpp_inline intN<N> operator == (const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_cmpeq1_epi32(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline intN<N> operator == (const intN<N>& v1, const int32_t v2) { return v1 == intN<N>(v2); }
	template<int N> hlslpp_inline intN<N> operator == (const int32_t v1, const intN<N>& v2) { return intN<N>(v1) == v2; }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator == (const intN<N>& v1, const icomponents<Dim...>& v2) { return v1 == intN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator == (const icomponents<Dim...>& v1, const intN<N>& v2) { return intN<N>(v1) == v2; }

	template<int...D1, int...D2>
	hlslpp_inline icomponentbase<sizeof...(D1)> operator == (const icomponents<D1...>& v1, const icomponents<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return icomponentbase<sizeof...(D1)>(_hlslpp_cmpeq1_epi32(icomponentbase<sizeof...(D1)>(v1)._vec, icomponentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Not equals

	template<int N> hlslpp_inline intN<N> operator != (const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_cmpneq1_epi32(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline intN<N> operator != (const intN<N>& v1, const int32_t v2) { return v1 != intN<N>(v2); }
	template<int N> hlslpp_inline intN<N> operator != (const int32_t v1, const intN<N>& v2) { return intN<N>(v1) != v2; }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator != (const intN<N>& v1, const icomponents<Dim...>& v2) { return v1 != intN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator != (const icomponents<Dim...>& v1, const intN<N>& v2) { return intN<N>(v1) != v2; }

	template<int...D1, int...D2>
	hlslpp_inline icomponentbase<sizeof...(D1)> operator != (const icomponents<D1...>& v1, const icomponents<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return icomponentbase<sizeof...(D1)>(_hlslpp_cmpneq1_epi32(icomponentbase<sizeof...(D1)>(v1)._vec, icomponentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Greater than

	template<int N> hlslpp_inline intN<N> operator > (const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_cmpgt1_epi32(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline intN<N> operator > (const intN<N>& v1, const int32_t v2) { return v1 > intN<N>(v2); }
	template<int N> hlslpp_inline intN<N> operator > (const int32_t v1, const intN<N>& v2) { return intN<N>(v1) > v2; }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator > (const intN<N>& v1, const icomponents<Dim...>& v2) { return v1 > intN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator > (const icomponents<Dim...>& v1, const intN<N>& v2) { return intN<N>(v1) > v2; }

	template<int...D1, int...D2>
	hlslpp_inline icomponentbase<sizeof...(D1)> operator > (const icomponents<D1...>& v1, const icomponents<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return icomponentbase<sizeof...(D1)>(_hlslpp_cmpgt1_epi32(icomponentbase<sizeof...(D1)>(v1)._vec, icomponentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Greater equals

	template<int N> hlslpp_inline intN<N> operator >= (const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_cmpge1_epi32(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline intN<N> operator >= (const intN<N>& v1, const int32_t v2) { return v1 >= intN<N>(v2); }
	template<int N> hlslpp_inline intN<N> operator >= (const int32_t v1, const intN<N>& v2) { return intN<N>(v1) >= v2; }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator >= (const intN<N>& v1, const icomponents<Dim...>& v2) { return v1 >= intN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator >= (const icomponents<Dim...>& v1, const intN<N>& v2) { return intN<N>(v1) >= v2; }

	template<int...D1, int...D2>
	hlslpp_inline icomponentbase<sizeof...(D1)> operator >= (const icomponents<D1...>& v1, const icomponents<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return icomponentbase<sizeof...(D1)>(_hlslpp_cmpge1_epi32(icomponentbase<sizeof...(D1)>(v1)._vec, icomponentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Less than

	template<int N> hlslpp_inline intN<N> operator < (const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_cmplt1_epi32(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline intN<N> operator < (const intN<N>& v1, const int32_t v2) { return v1 < intN<N>(v2); }
	template<int N> hlslpp_inline intN<N> operator < (const int32_t v1, const intN<N>& v2) { return intN<N>(v1) < v2; }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator < (const intN<N>& v1, const icomponents<Dim...>& v2) { return v1 < intN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator < (const icomponents<Dim...>& v1, const intN<N>& v2) { return intN<N>(v1) < v2; }

	template<int...D1, int...D2>
	hlslpp_inline icomponentbase<sizeof...(D1)> operator < (const icomponents<D1...>& v1, const icomponents<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return icomponentbase<sizeof...(D1)>(_hlslpp_cmplt1_epi32(icomponentbase<sizeof...(D1)>(v1)._vec, icomponentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Less equals

	template<int N> hlslpp_inline intN<N> operator <= (const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_cmple1_epi32(v1._vec, v2._vec)); }

	template<int N> hlslpp_inline intN<N> operator <= (const intN<N>& v1, const int32_t v2) { return v1 <= intN<N>(v2); }
	template<int N> hlslpp_inline intN<N> operator <= (const int32_t v1, const intN<N>& v2) { return intN<N>(v1) <= v2; }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator <= (const intN<N>& v1, const icomponents<Dim...>& v2) { return v1 <= intN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator <= (const icomponents<Dim...>& v1, const intN<N>& v2) { return intN<N>(v1) <= v2; }

	template<int...D1, int...D2>
	hlslpp_inline icomponentbase<sizeof...(D1)> operator <= (const icomponents<D1...>& v1, const icomponents<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return icomponentbase<sizeof...(D1)>(_hlslpp_cmple1_epi32(icomponentbase<sizeof...(D1)>(v1)._vec, icomponentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Shift left

	template<int N> hlslpp_inline intN<N> operator << (const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_sllv_epi32(v1._vec, v2._vec)); }

	// If we pass in an int use the version taking a constant instead of a vector, as it's faster in SSE
	template<int N> hlslpp_inline intN<N> operator << (const intN<N>& v1, const int32_t v2) { return intN<N>(_hlslpp_slli(v1._vec, v2)); }
	template<int N> hlslpp_inline intN<N> operator << (const int32_t v1, const intN<N>& v2) { return intN<N>(v1) << v2; }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator << (const intN<N>& v1, const icomponents<Dim...>& v2) { return v1 << intN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator << (const icomponents<Dim...>& v1, const intN<N>& v2) { return intN<N>(v1) << v2; }

	template<int...D1, int...D2>
	hlslpp_inline icomponentbase<sizeof...(D1)> operator << (const icomponents<D1...>& v1, const icomponents<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return icomponentbase<sizeof...(D1)>(_hlslpp_sllv_epi32(icomponentbase<sizeof...(D1)>(v1)._vec, icomponentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Shift right

	template<int N> hlslpp_inline intN<N> operator >> (const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_srlv_epi32(v1._vec, v2._vec)); }

	// If we pass in an int use the version taking a constant instead of a vector, as it's faster in SSE
	template<int N> hlslpp_inline intN<N> operator >> (const intN<N>& v1, const int32_t v2) { return intN<N>(_hlslpp_srli(v1._vec, v2)); }
	template<int N> hlslpp_inline intN<N> operator >> (const int32_t v1, const intN<N>& v2) { return intN<N>(v1) >> v2; }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator >> (const intN<N>& v1, const icomponents<Dim...>& v2) { return v1 >> intN<N>(v2); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> operator >> (const icomponents<Dim...>& v1, const intN<N>& v2) { return intN<N>(v1) >> v2; }

	template<int...D1, int...D2>
	hlslpp_inline icomponentbase<sizeof...(D1)> operator >> (const icomponents<D1...>& v1, const icomponents<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return icomponentbase<sizeof...(D1)>(_hlslpp_srlv_epi32(icomponentbase<sizeof...(D1)>(v1)._vec, icomponentbase<sizeof...(D1)>(v2)._vec));
	}

	template<int N>		hlslpp_inline intN<N>					abs(const intN<N>& v) { return intN<N>(_hlslpp_abs_epi32(v._vec)); }
	template<int...Dim>	hlslpp_inline icomponents<Dim...>		abs(const icomponents<Dim...>& v) { return icomponents<Dim...>(_hlslpp_abs_epi32(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>					acos(const intN<N>& v) { return floatN<N>(_hlslpp_acos_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>		acos(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_acos_ps(_hlslpp_cvtepi32_ps(v._vec))); }

	template<int N>		hlslpp_inline intN<N>					all(const intN<N>& v) { return intN<N>(_hlslpp_all1_epi32(v._vec)); }
	template<int...Dim>	hlslpp_inline icomponents<Dim...>		all(const icomponents<Dim...>& v) { return icomponents<Dim...>(_hlslpp_all1_epi32(v._vec)); }

	template<int N>		hlslpp_inline intN<N>					any(const intN<N>& v) { return intN<N>(_hlslpp_any1_epi32(v._vec)); }
	template<int...Dim>	hlslpp_inline icomponents<Dim...>		any(const icomponents<Dim...>& v) { return icomponents<Dim...>(_hlslpp_any1_epi32(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>					asin(const intN<N>& v) { return floatN<N>(_hlslpp_asin_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>		asin(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_asin_ps(_hlslpp_cvtepi32_ps(v._vec))); }

	template<int N>		hlslpp_inline floatN<N>					atan(const intN<N>& v) { return floatN<N>(_hlslpp_atan_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>		atan(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_atan_ps(_hlslpp_cvtepi32_ps(v._vec))); }

	template<int N>		hlslpp_inline intN<N>					ceil(const intN<N>& v) { hlslpp_warning("Noop. Consider removing this code."); return v; }
	template<int...Dim>	hlslpp_inline intN<sizeof...(Dim)>		ceil(const icomponents<Dim...>& v) { hlslpp_warning("Noop. Consider removing this code."); return intN<sizeof...(Dim)>(v._vec); }

	template<int N> hlslpp_inline intN<N> clamp(const intN<N>& v, const intN<N>& minv, const intN<N>& maxv) { return intN<N>(_hlslpp_clamp_epi32(v._vec, minv._vec, maxv._vec)); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> clamp(const intN<N>& v1, const intN<N>& v2, const icomponents<Dim...>& a) { return clamp(v1, v2, intN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> clamp(const intN<N>& v1, const icomponents<Dim...>& v2, const intN<N>& a) { return clamp(v1, intN<N>(v2), a); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> clamp(const icomponents<Dim...>& v1, const intN<N>& v2, const intN<N>& a) { return clamp(intN<N>(v1), v2, a); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> clamp(const intN<N>& v1, const icomponents<Dim...>& v2, const icomponents<Dim...>& a) { return clamp(v1, intN<N>(v2), intN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> clamp(const icomponents<Dim...>& v1, const intN<N>& v2, const icomponents<Dim...>& a) { return clamp(intN<N>(v1), v2, intN<N>(a)); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> clamp(const icomponents<Dim...>& v1, const icomponents<Dim...>& v2, const intN<N>& a) { return clamp(intN<N>(v1), intN<N>(v2), a); }

	template<int...D1, int...D2, int...D3>
	hlslpp_inline intN<sizeof...(D1)> clamp(const icomponents<D1...>& v1, const icomponents<D2...>& v2, const icomponents<D3...>& a)
	{
		static_assert((sizeof...(D1) == sizeof...(D2)) && (sizeof...(D2) == sizeof...(D3)), "Vectors must be the same dimension");
		return intN<sizeof...(D1)>(_hlslpp_clamp_epi32((intN<sizeof...(D1)>(v1)._vec), (intN<sizeof...(D1)>(v2)._vec), (intN<sizeof...(D3)>(a)._vec)));
	}

	template<int N>		hlslpp_inline floatN<N>					cos(const intN<N>& v) { return floatN<N>(_hlslpp_cos_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>		cos(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_cos_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	
	template<int N>		hlslpp_inline floatN<N>					cosh(const intN<N>& v) { return floatN<N>(_hlslpp_cosh_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>		cosh(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_cosh_ps(_hlslpp_cvtepi32_ps(v._vec))); }

	hlslpp_inline float3 cross(const int3& v1, const int3& v2) { return float3(_hlslpp_cross_ps(_hlslpp_cvtepi32_ps(v1._vec), _hlslpp_cvtepi32_ps(v2._vec))); }

	template<int N>		hlslpp_inline floatN<N>					degrees(const intN<N>& v) { return floatN<N>(_hlslpp_mul_ps(_hlslpp_cvtepi32_ps(v._vec), f4_rad2deg)); }
	template<int...Dim>	hlslpp_inline components<Dim...>		degrees(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_mul_ps(_hlslpp_cvtepi32_ps(v._vec), f4_rad2deg)); }

	hlslpp_inline float1 dot(const int2& v1, const int2& v2) { return float1(_hlslpp_dot2_ps(_hlslpp_cvtepi32_ps(v1._vec), _hlslpp_cvtepi32_ps(v2._vec))); }
	hlslpp_inline float1 dot(const int3& v1, const int3& v2) { return float1(_hlslpp_dot3_ps(_hlslpp_cvtepi32_ps(v1._vec), _hlslpp_cvtepi32_ps(v2._vec))); }
	hlslpp_inline float1 dot(const int4& v1, const int4& v2) { return float1(_hlslpp_dot4_ps(_hlslpp_cvtepi32_ps(v1._vec), _hlslpp_cvtepi32_ps(v2._vec))); }

	template<int N>		hlslpp_inline floatN<N>				exp(const intN<N>& v) { return floatN<N>(_hlslpp_exp_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>	exp(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_exp_ps(_hlslpp_cvtepi32_ps(v._vec))); }

	template<int N>		hlslpp_inline floatN<N>				exp2(const intN<N>& v) { return floatN<N>(_hlslpp_exp2_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>	exp2(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_exp2_ps(_hlslpp_cvtepi32_ps(v._vec))); }

	template<int N>		hlslpp_inline floatN<N>				floor(const intN<N>& v) { hlslpp_warning("Noop. Consider removing this code."); return v._vec; }
	template<int...Dim>	hlslpp_inline components<Dim...>	floor(const icomponents<Dim...>& v) { hlslpp_warning("Noop. Consider removing this code."); return components<Dim...>(v._vec); }

	template<int N>		hlslpp_inline intN<N>				frac(const intN<N>& v) { hlslpp_warning("Always returns 0. Consider removing this code."); return intN<N>(i4_0); }
	template<int...Dim>	hlslpp_inline icomponents<Dim...>	frac(const icomponents<Dim...>& v) { hlslpp_warning("Always returns 0. Consider removing this code."); return icomponents<Dim...>(i4_0); }

	template<int N>		hlslpp_inline floatN<N>				isfinite(const intN<N>& v) { hlslpp_warning("Always returns true. Consider removing this code."); return floatN<N>(f4_1); }
	template<int...Dim>	hlslpp_inline components<Dim...>	isfinite(const icomponents<Dim...>& v) { hlslpp_warning("Always returns true. Consider removing this code."); return components<Dim...>(f4_1); }

	template<int N>		hlslpp_inline floatN<N>				isinf(const intN<N>& v) { hlslpp_warning("Always returns false. Consider removing this code."); return floatN<N>(f4_0); }
	template<int...Dim>	hlslpp_inline components<Dim...>	isinf(const icomponents<Dim...>& v) { hlslpp_warning("Always returns false. Consider removing this code."); return components<Dim...>(f4_0); }

	template<int N>		hlslpp_inline floatN<N>				isnan(const intN<N>& v) { hlslpp_warning("Always returns false. Consider removing this code."); return floatN<N>(f4_0); }
	template<int...Dim>	hlslpp_inline components<Dim...>	isnan(const icomponents<Dim...>& v) { hlslpp_warning("Always returns false. Consider removing this code."); return components<Dim...>(f4_0); }

	//----- Length

	hlslpp_inline float1 length(const int1& v) { return float1(v); }
	hlslpp_inline float1 length(const int2& v) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot2_ps(_hlslpp_cvtepi32_ps(v._vec), _hlslpp_cvtepi32_ps(v._vec)))); }
	hlslpp_inline float1 length(const int3& v) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot3_ps(_hlslpp_cvtepi32_ps(v._vec), _hlslpp_cvtepi32_ps(v._vec)))); }
	hlslpp_inline float1 length(const int4& v) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(_hlslpp_cvtepi32_ps(v._vec), _hlslpp_cvtepi32_ps(v._vec)))); }

	template<int X, int Y, int Z, int W>
	hlslpp_inline float1 length(const icomponent4<X, Y, Z, W>& v) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(_hlslpp_cvtepi32_ps(v._vec), _hlslpp_cvtepi32_ps(v._vec)))); }

	//----- Log

	template<int N>		hlslpp_inline floatN<N>					log(const intN<N>& v) { return floatN<N>(_hlslpp_log_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>		log(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_log_ps(_hlslpp_cvtepi32_ps(v._vec))); }

	template<int N>		hlslpp_inline floatN<N>					log2(const intN<N>& v) { return floatN<N>(_hlslpp_log2_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>		log2(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_log2_ps(_hlslpp_cvtepi32_ps(v._vec))); }

	template<int N>		hlslpp_inline floatN<N>					log10(const intN<N>& v) { return floatN<N>(_hlslpp_log10_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>		log10(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_log10_ps(_hlslpp_cvtepi32_ps(v._vec))); }

	//----- Minimum

	template<int N> hlslpp_inline intN<N> min(const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_min_epi32(v1._vec, v2._vec)); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> min(const intN<N>& v1, const icomponents<Dim...>& v2) { return min(v1, intN<N>(v2)); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> min(const icomponents<Dim...>& v1, const intN<N>& v2) { return min(intN<N>(v1), v2); }

	template<int...D1, int...D2>
	hlslpp_inline icomponentbase<sizeof...(D1)> min(const icomponents<D1...>& v1, const icomponents<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return icomponentbase<sizeof...(D1)>(_hlslpp_min_epi32(icomponentbase<sizeof...(D1)>(v1)._vec, icomponentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Maximum

	template<int N> hlslpp_inline intN<N> max(const intN<N>& v1, const intN<N>& v2) { return intN<N>(_hlslpp_max_epi32(v1._vec, v2._vec)); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> max(const intN<N>& v1, const icomponents<Dim...>& v2) { return max(v1, intN<N>(v2)); }

	template<int N, int...Dim>
	hlslpp_inline intN<N> max(const icomponents<Dim...>& v1, const intN<N>& v2) { return max(intN<N>(v1), v2); }

	template<int...D1, int...D2>
	hlslpp_inline icomponentbase<sizeof...(D1)> max(const icomponents<D1...>& v1, const icomponents<D2...>& v2)
	{
		static_assert(sizeof...(D1) == sizeof...(D2), "Vectors must be the same dimension");
		return icomponentbase<sizeof...(D1)>(_hlslpp_max_epi32(icomponentbase<sizeof...(D1)>(v1)._vec, icomponentbase<sizeof...(D1)>(v2)._vec));
	}

	//----- Normalize

	template<int X, int Y, int Z, int W>
	hlslpp_inline component4<0, 1, 2, 3>	normalize(const icomponent4<X, Y, Z, W>& v)
	{
		n128 fvec = _hlslpp_cvtepi32_ps(v._vec);
		return component4<0, 1, 2, 3>(_hlslpp_div_ps(fvec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(fvec, fvec)))));
	}

	hlslpp_inline float4					normalize(const int4& v)
	{
		n128 fvec = _hlslpp_cvtepi32_ps(v._vec);
		return float4(_hlslpp_div_ps(fvec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(fvec, fvec)))));
	}

	hlslpp_inline float3					normalize(const int3& v)
	{
		n128 fvec = _hlslpp_cvtepi32_ps(v._vec);
		return float3(_hlslpp_div_ps(fvec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot3_ps(fvec, fvec)))));
	}

	hlslpp_inline float2					normalize(const int2& v)
	{
		n128 fvec = _hlslpp_cvtepi32_ps(v._vec);
		return float2(_hlslpp_div_ps(fvec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot2_ps(fvec, fvec)))));
	}

	hlslpp_inline float1					normalize(const int1&) { return float1(1.0f); }

	template<int N>		hlslpp_inline intN<N>				round(const intN<N>& v) { hlslpp_warning("Noop. Consider removing this code."); return v; }
	template<int...Dim>	hlslpp_inline icomponents<Dim...>	round(const icomponents<Dim...>& v) { hlslpp_warning("Noop. Consider removing this code."); return icomponents<Dim...>(v._vec); }

	template<int N>		hlslpp_inline intN<N>				saturate(const intN<N>& v) { return intN<N>(_hlslpp_sat_epi32(v._vec)); }
	template<int...Dim>	hlslpp_inline icomponents<Dim...>	saturate(const icomponents<Dim...>& v) { return icomponents<Dim...>(_hlslpp_sat_epi32(v._vec)); }

	template<int N>		hlslpp_inline intN<N>				sign(const intN<N>& v) { return intN<N>(_hlslpp_sign_epi32(v._vec)); }
	template<int...Dim>	hlslpp_inline icomponents<Dim...>	sign(const icomponents<Dim...>& v) { return icomponents<Dim...>(_hlslpp_sign_epi32(v._vec)); }

	template<int N>		hlslpp_inline floatN<N>				sin(const intN<N>& v) { return floatN<N>(_hlslpp_sin_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>	sin(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_sin_ps(_hlslpp_cvtepi32_ps(v._vec))); }

	template<int N>		hlslpp_inline floatN<N>				sinh(const intN<N>& v) { return floatN<N>(_hlslpp_sinh_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>	sinh(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_sinh_ps(_hlslpp_cvtepi32_ps(v._vec))); }

	template<int N>		hlslpp_inline floatN<N>				tan(const intN<N>& v) { return floatN<N>(_hlslpp_tan_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>	tan(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_tan_ps(_hlslpp_cvtepi32_ps(v._vec))); }

	template<int N>		hlslpp_inline floatN<N>				tanh(const intN<N>& v) { return floatN<N>(_hlslpp_tanh_ps(_hlslpp_cvtepi32_ps(v._vec))); }
	template<int...Dim>	hlslpp_inline components<Dim...>	tanh(const icomponents<Dim...>& v) { return components<Dim...>(_hlslpp_tanh_ps(_hlslpp_cvtepi32_ps(v._vec))); }

	template<int N>		hlslpp_inline intN<N>				trunc(const intN<N>& v) { hlslpp_warning("Noop. Consider removing this code."); return v; }
	template<int...Dim>	hlslpp_inline icomponents<Dim...>	trunc(const icomponents<Dim...>& v) { hlslpp_warning("Noop. Consider removing this code."); return icomponents<Dim...>(v._vec); }

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

	hlslpp_inline n128 _hlslpp_det_4x4_ps(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3)
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

	hlslpp_inline n128 _hlslpp_inv_2x2_ps(n128 m)
	{
		n128 det = _hlslpp_perm_xxxx_ps(_hlslpp_det_2x2_ps(m));
		n128 shuf = _hlslpp_mul_ps(_hlslpp_perm_wyzx_ps(m), _hlslpp_set_ps(1.0f, -1.0f, -1.0f, 1.0f));
		return _hlslpp_div_ps(shuf, det);
	}

	hlslpp_inline void _hlslpp_inv_3x3_ps(const n128& vec0, const n128& vec1, const n128& vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
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

	hlslpp_inline void _hlslpp_inv_4x4_ps(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
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

	// Matrix - Matrix multiplication

	// Note that matrix-vector multiplication assumes the matrix data is laid out as row major.

	template<int M>
	hlslpp_inline floatNxM<1, M> mul(const float1x1& m1, const floatNxM<1, M>& m2)
	{
		return floatNxM<1, M>(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1._vec), m2._vec));
	}

	template<int N, enable_if_dim<(N > 1)> = nullptr>
	hlslpp_inline floatNxM<N, 1> mul(const floatNxM<N, 1>& m1, const float1x1& m2)
	{
		return floatNxM<N, 1>(_hlslpp_mul_ps(m1._vec, _hlslpp_perm_xxxx_ps(m2._vec)));
	}

	hlslpp_inline float2x2 mul(const float2x1& m1, const float1x2& m2)
	{
		return float2x2(_hlslpp_mul_ps(_hlslpp_perm_xxyy_ps(m1._vec), _hlslpp_perm_xyxy_ps(m2._vec)));
	}

	template<int M, enable_if_dim<(M > 2)> = nullptr>
	hlslpp_inline floatNxM<2, M> mul(const float2x1& m1, const floatNxM<1, M>& m2)
	{
		return floatNxM<2, M>(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1._vec), m2._vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1._vec), m2._vec));
	}

	template<int N, enable_if_dim<(N > 2)> = nullptr>
	hlslpp_inline floatNxM<N, 2> mul(const floatNxM<N, 1>& m1, const float1x2& m2)
	{
		return floatNxM<N, 2>(_hlslpp_mul_ps(m1._vec, _hlslpp_perm_xxxx_ps(m2._vec)), _hlslpp_mul_ps(m1._vec, _hlslpp_perm_yyyy_ps(m2._vec)));
	}

	template<int N, enable_if_dim<(N > 2)> = nullptr>
	hlslpp_inline floatNxM<N, 3> mul(const floatNxM<N, 1>& m1, const float1x3& m2)
	{
		return floatNxM<N, 3>(_hlslpp_mul_ps(m1._vec, _hlslpp_perm_xxxx_ps(m2._vec)), _hlslpp_mul_ps(m1._vec, _hlslpp_perm_yyyy_ps(m2._vec)), _hlslpp_mul_ps(m1._vec, _hlslpp_perm_zzzz_ps(m2._vec)));
	}

	hlslpp_inline float3x4 mul(const float3x1& m1, const float1x4& m2)
	{
		return float3x4(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1._vec), m2._vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1._vec), m2._vec), _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1._vec), m2._vec));
	}

	hlslpp_inline float4x4 mul(const float4x1& m1, const float1x4& m2)
	{
		return float4x4(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1._vec), m2._vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1._vec), m2._vec), _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1._vec), m2._vec), _hlslpp_mul_ps(_hlslpp_perm_wwww_ps(m1._vec), m2._vec));
	}

	hlslpp_inline float1x1 mul(const float1x2& m1, const float2x1& m2)
	{
		return float1x1(_hlslpp_dot2_ps(m1._vec, m2._vec));
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

	// https://lxjk.github.io/2017/09/03/Fast-4x4-Matrix-Inverse-with-SSE-SIMD-Explained.html
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

	hlslpp_inline void _hlslpp_mul_4x2_2x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1)
	{
		n128 mul0 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		n128 mul1 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec1, mul0);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec2, mul1);

		n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec0);
		n128 mul3 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul2);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec2, mul3);
	}

	hlslpp_inline n128 _hlslpp_mul_2x3_3x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec)
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

	hlslpp_inline float1x2 mul(const float1x2& m1, const float2x2& m2)
	{	
		return float1x2(_hlslpp_mul_1x2_2x1_ps(m1._vec, m2._vec));
	}

	template<int M, enable_if_dim<(M > 2)> = nullptr>
	hlslpp_inline floatNxM<1, M> mul(const float1x2& m1, const floatNxM<2, M>& m2)
	{
		return floatNxM<1, M>(_hlslpp_mul_1x2_2xM_ps(m1._vec, m2._vec0, m2._vec1));
	}

	hlslpp_inline float1x1 mul(const float1x3& m1, const float3x1& m2)
	{
		return float1x1(_hlslpp_dot3_ps(m1._vec, m2._vec));
	}

	hlslpp_inline float1x2 mul(const float1x3& m1, const float3x2& m2)
	{
		return float1x2(_hlslpp_mul_1x3_3x2_ps(m1._vec, m2._vec0, m2._vec1));
	}

	template<int M, enable_if_dim<(M > 2)> = nullptr>
	hlslpp_inline floatNxM<1, M> mul(const float1x3& m1, const floatNxM<3, M>& m2)
	{
		return floatNxM<1, M>(_hlslpp_mul_1x3_3xM_ps(m1._vec, m2._vec0, m2._vec1, m2._vec2));
	}

	hlslpp_inline float1x1 mul(const float1x4& m1, const float4x1& m2)
	{
		return float1x1(_hlslpp_dot4_ps(m1._vec, m2._vec));
	}

	hlslpp_inline float1x2 mul(const float1x4& m1, const float4x2& m2)
	{
		return float1x2(_hlslpp_mul_1x4_4x2_ps(m1._vec, m2._vec0, m2._vec1));
	}

	hlslpp_inline float1x3 mul(const float1x4& m1, const float4x3& m2)
	{
		return float1x3(_hlslpp_mul_1x4_4x3_ps(m1._vec, m2._vec0, m2._vec1, m2._vec2));
	}

	hlslpp_inline float1x4 mul(const float1x4& m1, const float4x4& m2)
	{
		return float1x4(_hlslpp_mul_1x4_4x4_ps(m1._vec, m2._vec0, m2._vec1, m2._vec2, m2._vec3));
	}

	hlslpp_inline float2x1 mul(const float2x2& m1, const float2x1& m2)
	{
		return float2x1(_hlslpp_mul_2x2_2x1_ps(m1._vec, m2._vec));
	}

	hlslpp_inline float2x2 mul(const float2x2& m1, const float2x2& m2)
	{
		return float2x2(_hlslpp_mul_2x2_2x2_ps(m1._vec, m2._vec));
	}

	template<int M, enable_if_dim<(M > 2)> = nullptr>
	hlslpp_inline floatNxM<2, M> mul(const float2x2& m1, const floatNxM<2, M>& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x2_2xM_ps(m1._vec, m2._vec0, m2._vec1, vec0, vec1);
		return floatNxM<2, M>(vec0, vec1);
	}

	template<int N, enable_if_dim<(N > 2)> = nullptr>
	hlslpp_inline floatNxM<N, 1> mul(const floatNxM<N, 2>& m1, const float2x1& m2)
	{
		return floatNxM<N, 1>(_hlslpp_mul_Nx2_2x1_ps(m1._vec0, m1._vec1, m2._vec));
	}

	template<int N, enable_if_dim<(N > 2)> = nullptr>
	hlslpp_inline floatNxM<N, 2> mul(const floatNxM<N, 2>& m1, const float2x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_Nx2_2x2_ps(m1._vec0, m1._vec1, m2._vec, vec0, vec1);
		return floatNxM<N, 2>(vec0, vec1);
	}

	template<int M, enable_if_dim<(M > 2)> = nullptr>
	hlslpp_inline floatNxM<3, M> mul(const float3x2& m1, const floatNxM<2, M>& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x2_2xM_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1, vec0, vec1, vec2);
		return floatNxM<3, M>(vec0, vec1, vec2);
	}

	hlslpp_inline float4x3 mul(const float4x2& m1, const float2x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_4x2_2x3_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1, vec0, vec1, vec2);
		return float4x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 mul(const float4x2& m1, const float2x4& m2)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_mul_4x2_2x4_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	hlslpp_inline float2x1 mul(const float2x3& m1, const float3x1& m2)
	{
		return float2x1(_hlslpp_mul_2x3_3x1_ps(m1._vec0, m1._vec1, m2._vec));
	}

	hlslpp_inline float2x2 mul(const float2x3& m1, const float3x2& m2)
	{
		return float2x2(_hlslpp_mul_2x3_3x2_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1));
	}

	template<int M, enable_if_dim<(M > 2)> = nullptr>
	hlslpp_inline floatNxM<2, M> mul(const float2x3& m1, const floatNxM<3, M>& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_4x2_2x4_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1, m2._vec2, vec0, vec1);
		return floatNxM<2, M>(vec0, vec1);
	}

	hlslpp_inline float2x1 mul(const float2x4& m1, const float4x1& m2)
	{
		return float2x1(_hlslpp_mul_2x3_3x2_ps(m1._vec0, m1._vec1, m2._vec));
	}

	hlslpp_inline float2x2 mul(const float2x4& m1, const float4x2& m2)
	{
		return float2x2(_hlslpp_mul_2x4_4x2_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1));
	}

	hlslpp_inline float2x3 mul(const float2x4& m1, const float4x3& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x4_4x3_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1, m2._vec2, vec0, vec1);
		return float2x3(vec0, vec1);
	}

	hlslpp_inline float2x4 mul(const float2x4& m1, const float4x4& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x4_4x4_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1, m2._vec2, m2._vec3, vec0, vec1);
		return float2x4(vec0, vec1);
	}

	hlslpp_inline float3x1 mul(const float3x3& m1, const float3x1& m2)
	{
		return float3x1(_hlslpp_mul_3x3_3x1_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec));
	}

	hlslpp_inline float3x2 mul(const float3x3& m1, const float3x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_3x3_3x2_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, vec0, vec1);
		return float3x2(vec0, vec1);
	}

	hlslpp_inline float3x3 mul(const float3x3& m1, const float3x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x3_3x3_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, m2._vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float3x4 mul(const float3x3& m1, const float3x4& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x3_3x4_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, m2._vec2, vec0, vec1, vec2);
		return float3x4(vec0, vec1, vec2);
	}

	hlslpp_inline float3x1 mul(const float3x4& m1, const float4x1& m2)
	{
	
		return float3x1(_hlslpp_mul_3x4_4x1_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec));
	}

	hlslpp_inline float3x2 mul(const float3x4& m1, const float4x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_3x4_4x2_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, vec0, vec1);
		return float3x2(vec0, vec1);
	}

	hlslpp_inline float3x3 mul(const float3x4& m1, const float4x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x4_4x3_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, m2._vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float3x4 mul(const float3x4& m1, const float4x4& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x4_4x4_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, m2._vec2, m2._vec3, vec0, vec1, vec2);
		return float3x4(vec0, vec1, vec2);
	}

	hlslpp_inline float4x1 mul(const float4x3& m1, const float3x1& m2)
	{
		return float4x1(_hlslpp_mul_4x3_3x1_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec));
	}

	hlslpp_inline float4x2 mul(const float4x3& m1, const float3x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_4x3_3x2_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, vec0, vec1);
		return float4x2(vec0, vec1);
	}

	hlslpp_inline float4x3 mul(const float4x3& m1, const float3x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_4x3_3x3_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, m2._vec2, vec0, vec1, vec2);
		return float4x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 mul(const float4x3& m1, const float3x4& m2)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_mul_4x3_3x4_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, m2._vec2, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	hlslpp_inline float4x1 mul(const float4x4& m1, const float4x1& m2)
	{
		return float4x1(_hlslpp_mul_4x4_4x1_ps(m1._vec0, m1._vec1, m1._vec2, m1._vec3, m2._vec));
	}

	hlslpp_inline float4x2 mul(const float4x4& m1, const float4x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_4x4_4x2_ps(m1._vec0, m1._vec1, m1._vec2, m1._vec3, m2._vec0, m2._vec1, vec0, vec1);
		return float4x2(vec0, vec1);
	}

	hlslpp_inline float4x3 mul(const float4x4& m1, const float4x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_4x4_4x3_ps(m1._vec0, m1._vec1, m1._vec2, m1._vec3, m2._vec0, m2._vec1, m2._vec2, vec0, vec1, vec2);
		return float4x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 mul(const float4x4& m1, const float4x4& m2)
	{
	#if defined(HLSLPP_MATRIX_PACK_COLUMN_MAJOR)

	#else

	#endif
	
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_mul_4x4_4x4_ps(m1._vec0, m1._vec1, m1._vec2, m1._vec3, m2._vec0, m2._vec1, m2._vec2, m2._vec3, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	// Matrix-matrix multiplication with floatN<N> vectors and components as operands

	template<int N> hlslpp_inline floatN<N> mul(const floatNxM<N, 4>& m1, const float4& v) { return floatN<N>(mul(m1, float4x1(v))); }

	template<int N> hlslpp_inline floatN<N> mul(const floatNxM<N, 3>& m1, const float3& v) { return floatN<N>(mul(m1, float3x1(v))); }

	template<int N> hlslpp_inline floatN<N> mul(const floatNxM<N, 2>& m1, const float2& v) { return floatN<N>(mul(m1, float2x1(v))); }

	template<int N> hlslpp_inline floatN<N> mul(const floatNxM<N, 1>& m1, const float1& v) { return floatN<N>(mul(m1, float1x1(v))); }

	template<int N> hlslpp_inline floatN<N> mul(const float4& v, const floatNxM<N, 4>& m1) { return floatN<N>(mul(float1x4(v), m1)); }

	template<int N> hlslpp_inline floatN<N> mul(const float3& v, const floatNxM<N, 3>& m1) { return floatN<N>(mul(float1x3(v), m1)); }

	template<int N> hlslpp_inline floatN<N> mul(const float2& v, const floatNxM<N, 2>& m1) { return floatN<N>(mul(float1x2(v), m1)); }

	template<int N> hlslpp_inline floatN<N> mul(const float1& v, const floatNxM<N, 1>& m1) { return floatN<N>(mul(float1x1(v), m1)); }

	//----- Matrix-Matrix Addition

	template<int N, int M, enable_if_dim<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator + (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		return floatNxM<N, M>(_hlslpp_add_ps(m1._vec, m2._vec));
	}

	template<int N, int M, enable_if_dim<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator + (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		return floatNxM<N, M>(_hlslpp_add_ps(m1._vec0, m2._vec0), _hlslpp_add_ps(m1._vec1, m2._vec1));
	}

	template<int N, int M, enable_if_dim<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator + (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		return floatNxM<N, M>(_hlslpp_add_ps(m1._vec0, m2._vec0), _hlslpp_add_ps(m1._vec1, m2._vec1), _hlslpp_add_ps(m1._vec2, m2._vec2));
	}

	hlslpp_inline float4x4 operator + (const float4x4& m1, const float4x4& m2)
	{
		return float4x4(_hlslpp_add_ps(m1._vec0, m2._vec0), _hlslpp_add_ps(m1._vec1, m2._vec1), _hlslpp_add_ps(m1._vec2, m2._vec2), _hlslpp_add_ps(m1._vec3, m2._vec3));
	}

	template<int N, int M>
	hlslpp_inline floatNxM<N, M>& operator += (floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		m1 = m1 + m2;
		return m1;
	}

	//----- Matrix-Scalar Addition

	template<int N, int M, enable_if_dim<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator + (const floatNxM<N, M>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<N, M>(_hlslpp_add_ps(m._vec, v_perm));
	}

	template<int N, int M, enable_if_dim<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator + (const floatNxM<N, M>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<N, M>(_hlslpp_add_ps(m._vec0, v_perm), _hlslpp_add_ps(m._vec1, v_perm));
	}

	template<int N, int M, enable_if_dim<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator + (const floatNxM<N, M>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<N, M>(_hlslpp_add_ps(m._vec0, v_perm), _hlslpp_add_ps(m._vec1, v_perm), _hlslpp_add_ps(m._vec2, v_perm));
	}

	hlslpp_inline float4x4 operator + (const float4x4& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return float4x4(_hlslpp_add_ps(m._vec0, v_perm), _hlslpp_add_ps(m._vec1, v_perm), _hlslpp_add_ps(m._vec2, v_perm), _hlslpp_add_ps(m._vec3, v_perm));
	}

	template<int N, int M>
	hlslpp_inline floatNxM<N, M>& operator += (floatNxM<N, M>& m, const float1& v)
	{
		m = m + v;
		return m;
	}

	//----- Matrix-Matrix Subtraction

	template<int N, int M, enable_if_dim<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator - (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		return floatNxM<N, M>(_hlslpp_sub_ps(m1._vec, m2._vec));
	}

	template<int N, int M, enable_if_dim<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator - (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		return floatNxM<N, M>(_hlslpp_sub_ps(m1._vec0, m2._vec0), _hlslpp_sub_ps(m1._vec1, m2._vec1));
	}

	template<int N, int M, enable_if_dim<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator - (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		return floatNxM<N, M>(_hlslpp_sub_ps(m1._vec0, m2._vec0), _hlslpp_sub_ps(m1._vec1, m2._vec1), _hlslpp_sub_ps(m1._vec2, m2._vec2));
	}

	hlslpp_inline floatNxM<4, 4> operator - (const floatNxM<4, 4>& m1, const floatNxM<4, 4>& m2)
	{
		return floatNxM<4, 4>(_hlslpp_sub_ps(m1._vec0, m2._vec0), _hlslpp_sub_ps(m1._vec1, m2._vec1), _hlslpp_sub_ps(m1._vec2, m2._vec2), _hlslpp_sub_ps(m1._vec3, m2._vec3));
	}

	template<int N, int M>
	hlslpp_inline floatNxM<N, M>& operator -= (floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		m1 = m1 - m2;
		return m1;
	}

	//----- Matrix-Scalar Subtraction

	template<int N, int M, enable_if_dim<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator - (const floatNxM<N, M>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<N, M>(_hlslpp_sub_ps(m._vec, v_perm));
	}

	template<int N, int M, enable_if_dim<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator - (const floatNxM<N, M>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<N, M>(_hlslpp_sub_ps(m._vec0, v_perm), _hlslpp_sub_ps(m._vec1, v_perm));
	}

	template<int N, int M, enable_if_dim<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator - (const floatNxM<N, M>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<N, M>(_hlslpp_sub_ps(m._vec0, v_perm), _hlslpp_sub_ps(m._vec1, v_perm), _hlslpp_sub_ps(m._vec2, v_perm));
	}

	hlslpp_inline floatNxM<4, 4> operator - (const floatNxM<4, 4>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<4, 4>(_hlslpp_sub_ps(m._vec0, v_perm), _hlslpp_sub_ps(m._vec1, v_perm), _hlslpp_sub_ps(m._vec2, v_perm), _hlslpp_sub_ps(m._vec3, v_perm));
	}

	template<int N, int M>
	hlslpp_inline floatNxM<N, M>& operator -= (floatNxM<N, M>& m, const float1& v)
	{
		m = m - v;
		return m;
	}

	//----- Multiplication

	template<int N, int M, enable_if_dim<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator * (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		return floatNxM<N, M>(_hlslpp_mul_ps(m1._vec, m2._vec));
	}

	template<int N, int M, enable_if_dim<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator * (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		return floatNxM<N, M>(_hlslpp_mul_ps(m1._vec0, m2._vec0), _hlslpp_mul_ps(m1._vec1, m2._vec1));
	}

	template<int N, int M, enable_if_dim<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator * (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		return floatNxM<N, M>(_hlslpp_mul_ps(m1._vec0, m2._vec0), _hlslpp_mul_ps(m1._vec1, m2._vec1), _hlslpp_mul_ps(m1._vec2, m2._vec2));
	}

	hlslpp_inline floatNxM<4, 4> operator * (const floatNxM<4, 4>& m1, const floatNxM<4, 4>& m2)
	{
		return floatNxM<4, 4>(_hlslpp_mul_ps(m1._vec0, m2._vec0), _hlslpp_mul_ps(m1._vec1, m2._vec1), _hlslpp_mul_ps(m1._vec2, m2._vec2), _hlslpp_mul_ps(m1._vec3, m2._vec3));
	}

	template<int N, int M>
	hlslpp_inline floatNxM<N, M>& operator *= (floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		m1 = m1 * m2;
		return m1;
	}

	//----- Matrix-Scalar Multiplication

	template<int N, int M, enable_if_dim<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator * (const floatNxM<N, M>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<N, M>(_hlslpp_mul_ps(m._vec, v_perm));
	}

	template<int N, int M, enable_if_dim<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator * (const floatNxM<N, M>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<N, M>(_hlslpp_mul_ps(m._vec0, v_perm), _hlslpp_mul_ps(m._vec1, v_perm));
	}

	template<int N, int M, enable_if_dim<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator * (const floatNxM<N, M>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<N, M>(_hlslpp_mul_ps(m._vec0, v_perm), _hlslpp_mul_ps(m._vec1, v_perm), _hlslpp_mul_ps(m._vec2, v_perm));
	}

	hlslpp_inline floatNxM<4, 4> operator * (const floatNxM<4, 4>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<4, 4>(_hlslpp_mul_ps(m._vec0, v_perm), _hlslpp_mul_ps(m._vec1, v_perm), _hlslpp_mul_ps(m._vec2, v_perm), _hlslpp_mul_ps(m._vec3, v_perm));
	}

	template<int N, int M>
	hlslpp_inline floatNxM<N, M>& operator *= (floatNxM<N, M>& m, const float1& v)
	{
		m = m * v;
		return m;
	}

	//----- Division

	template<int N, int M, enable_if_dim<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator / (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		return floatNxM<N, M>(_hlslpp_div_ps(m1._vec, m2._vec));
	}

	template<int N, int M, enable_if_dim<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator / (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		return floatNxM<N, M>(_hlslpp_div_ps(m1._vec0, m2._vec0), _hlslpp_div_ps(m1._vec1, m2._vec1));
	}

	template<int N, int M, enable_if_dim<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator / (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		return floatNxM<N, M>(_hlslpp_div_ps(m1._vec0, m2._vec0), _hlslpp_div_ps(m1._vec1, m2._vec1), _hlslpp_div_ps(m1._vec2, m2._vec2));
	}

	hlslpp_inline floatNxM<4, 4> operator / (const floatNxM<4, 4>& m1, const floatNxM<4, 4>& m2)
	{
		return floatNxM<4, 4>(_hlslpp_div_ps(m1._vec0, m2._vec0), _hlslpp_div_ps(m1._vec1, m2._vec1), _hlslpp_div_ps(m1._vec2, m2._vec2), _hlslpp_div_ps(m1._vec3, m2._vec3));
	}

	template<int N, int M>
	hlslpp_inline floatNxM<N, M>& operator /= (floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
	{
		m1 = m1 / m2;
		return m1;
	}

	//----- Matrix-Scalar Division

	template<int N, int M, enable_if_dim<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator / (const floatNxM<N, M>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<N, M>(_hlslpp_div_ps(m._vec, v_perm));
	}

	template<int N, int M, enable_if_dim<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator / (const floatNxM<N, M>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<N, M>(_hlslpp_div_ps(m._vec0, v_perm), _hlslpp_div_ps(m._vec1, v_perm));
	}

	template<int N, int M, enable_if_dim<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))> = nullptr>
	hlslpp_inline floatNxM<N, M> operator / (const floatNxM<N, M>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<N, M>(_hlslpp_div_ps(m._vec0, v_perm), _hlslpp_div_ps(m._vec1, v_perm), _hlslpp_div_ps(m._vec2, v_perm));
	}

	hlslpp_inline floatNxM<4, 4> operator / (const floatNxM<4, 4>& m, const float1& v)
	{
		n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
		return floatNxM<4, 4>(_hlslpp_div_ps(m._vec0, v_perm), _hlslpp_div_ps(m._vec1, v_perm), _hlslpp_div_ps(m._vec2, v_perm), _hlslpp_div_ps(m._vec3, v_perm));
	}

	template<int N, int M>
	hlslpp_inline floatNxM<N, M>& operator /= (floatNxM<N, M>& m, const float1& v)
	{
		m = m / v;
		return m;
	}

	hlslpp_inline float1 trace(const float2x2& m)
	{
		return float1(_hlslpp_trace_2x2_ps(m._vec));
	}

	hlslpp_inline float1 trace(const float3x3& m)
	{
		return float1(_hlslpp_trace_3x3_ps(m._vec0, m._vec1, m._vec2));
	}

	hlslpp_inline float1 trace(const float4x4& m)
	{
		return float1(_hlslpp_trace_4x4_ps(m._vec0, m._vec1, m._vec2, m._vec3));
	}

	hlslpp_inline float2x2 transpose(const float2x2& m)
	{
		return float2x2(_hlslpp_transpose_2x2_ps(m._vec));
	}

	hlslpp_inline float3x3 transpose(const float3x3& m)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_transpose_3x3_ps(m._vec0, m._vec1, m._vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 transpose(const float4x4& m)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_transpose_4x4_ps(m._vec0, m._vec1, m._vec2, m._vec3, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	// These transpose functions just copy the data because the 1xM, Nx1, 2xM, Nx2, 3xM and Nx3 matrices are always laid out as rows
	// even if they're meant to represent columns.

	template<int N, int M, enable_if_dim<(N == 1) || (M == 1)> = nullptr>
	floatNxM<M, N> transpose(const floatNxM<N, M>& m) { return floatNxM<M, N>(m._vec); }

	template<int N, int M, enable_if_dim<(N == 2 && M > 2) || (M == 2 && N > 2)> = nullptr>
	floatNxM<M, N> transpose(const floatNxM<N, M>& m) {	return floatNxM<M, N>(m._vec0, m._vec1); }

	template<int N, int M, enable_if_dim<(N == 3 && M > 3) || (M == 3 && N > 3)> = nullptr>
	floatNxM<M, N> transpose(const floatNxM<N, M>& m) { return floatNxM<M, N>(m._vec0, m._vec1, m._vec2); }

	hlslpp_inline float1 determinant(const float2x2& m)
	{
		return float1(_hlslpp_det_2x2_ps(m._vec));
	}

	hlslpp_inline float1 determinant(const float3x3& m)
	{
		return float1(_hlslpp_det_3x3_ps(m._vec0, m._vec1, m._vec2));
	}

	hlslpp_inline float1 determinant(const float4x4& m)
	{
		return float1(_hlslpp_det_4x4_ps(m._vec0, m._vec1, m._vec2, m._vec3));
	}

	hlslpp_inline float2x2 inverse(const float2x2& m)
	{
		return float2x2(_hlslpp_inv_2x2_ps(m._vec));
	}

	hlslpp_inline float3x3 inverse(const float3x3& m)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_inv_3x3_ps(m._vec0, m._vec1, m._vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 inverse(const float4x4& m)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_inv_4x4_ps(m._vec0, m._vec1, m._vec2, m._vec3, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	hlslpp_inline void store(const float1& v, float* f)
	{
		_hlslpp_store1_ps(f + 0, v._vec);
	}

	hlslpp_inline void store(const float2& v, float* f)
	{
		_hlslpp_store2_ps(f, v._vec);
	}

	hlslpp_inline void store(const float3& v, float* f)
	{
		_hlslpp_store3_ps(f, v._vec);
	}

	hlslpp_inline void store(const float4& v, float* f)
	{
		_hlslpp_store4_ps(f, v._vec);
	}

	hlslpp_inline void store(const float3x3& m, float* f)
	{
		_hlslpp_store3x3_ps(f, m._vec0, m._vec1, m._vec2);
	}

	hlslpp_inline void store(const float4x4& m, float* f)
	{
		_hlslpp_store4x4_ps(f, m._vec0, m._vec1, m._vec2, m._vec3);
	}
}

#include "hlsl++_quaternion.h"

namespace hlslpp
{
	hlslpp_inline float3x3::floatNxM(const quaternion& q)
	{
		_hlslpp_quat_to_3x3_ps(q._vec, _vec0, _vec1, _vec2);
	}

	hlslpp_inline float4x4::floatNxM(const quaternion& q)
	{
		_hlslpp_quat_to_4x4_ps(q._vec, _vec0, _vec1, _vec2, _vec3);
	}
}