#pragma once

#define HLSLPP_MATRIX_PACK_ROW_MAJOR

#if defined(__ANDROID__)

	#define HLSLPP_NEON

#elif __APPLE

	#include "TargetConditionals.h"
    #if TARGET_OS_IPHONE
		#define HLSLPP_NEON
    #elif TARGET_OS_MAC
		#define HLSLPP_SSE
    #endif

#elif defined(_WIN32) || defined(__linux__)

	#define HLSLPP_SSE

#else
	#error Platform not supported!
#endif

#if defined(HLSLPP_SSE)

	#include "hlsl++_sse.h"

#elif defined(HLSLPP_NEON)

	#include "hlsl++_neon.h"

#endif

#include <type_traits>
#include <cstdint>

// Helper constants

namespace hlslpp
{
	union BitMask
	{
		uint32_t i;
		float f;
		explicit BitMask(uint32_t i) : i(i) {}
		explicit BitMask(float f) : f(f) {}
	};
}

static const hlslpp::BitMask fffMask		(0xffffffffu); // Negative NaN
static const hlslpp::BitMask nanMask		(0x7fffffffu); // Positive NaN
static const hlslpp::BitMask infMask		(0x7f800000u);
static const hlslpp::BitMask minusinfMask	(0xff800000u);
static const hlslpp::BitMask absMask		(0x7fffffffu);
static const hlslpp::BitMask negMask		(0x80000000u);

// Constants
static const n128 f4_0				= _hlslpp_set1_ps( 0.0f);
static const n128 f4_1				= _hlslpp_set1_ps( 1.0f);
static const n128 f4minusOne		= _hlslpp_set1_ps(-1.0f);
static const n128 f4_05				= _hlslpp_set1_ps( 0.5f);
static const n128 f4_minus05		= _hlslpp_set1_ps(-0.5f);
static const n128 f4_2				= _hlslpp_set1_ps( 2.0f);
static const n128 f4_minus2			= _hlslpp_set1_ps(-2.0f);
static const n128 f4_10				= _hlslpp_set1_ps(10.0f);
static const n128 f4_e				= _hlslpp_set1_ps(2.718281828f);

static const n128 f4_pi				= _hlslpp_set1_ps( 3.14159265f);
static const n128 f4_minusPi		= _hlslpp_set1_ps(-3.14159265f);
static const n128 f4_invPi			= _hlslpp_set1_ps( 0.31830988f);

static const n128 f4_2pi			= _hlslpp_set1_ps( 6.28318530f); //  2 * pi
static const n128 f4_minus2pi		= _hlslpp_set1_ps(-6.28318530f); // -2 * pi
static const n128 f4_inv2pi			= _hlslpp_set1_ps( 0.15915494f); // 1.0 / 2 * pi

static const n128 f4_pi2			= _hlslpp_set1_ps( 1.57079632f); //  pi / 2
static const n128 f4_minusPi2		= _hlslpp_set1_ps(-1.57079632f); // -pi / 2

static const n128 f4_3pi2			= _hlslpp_set1_ps( 4.71238898f); //  3 * pi / 2
static const n128 f4_minus3pi2		= _hlslpp_set1_ps(-4.71238898f); // -3 * pi / 2

static const n128 f4_pi4			= _hlslpp_set1_ps( 0.78539816f); //  pi / 4
static const n128 f4_minusPi4		= _hlslpp_set1_ps(-0.78539816f); // -pi / 4

static const n128 f4_NaN			= _hlslpp_set1_ps(nanMask.f);		// Quiet NaN
static const n128 f4_inf			= _hlslpp_set1_ps(infMask.f);		// Infinity
static const n128 f4_minusinf		= _hlslpp_set1_ps(minusinfMask.f);	// -Infinity

static const n128 f4_rad2deg		= _hlslpp_set1_ps(180.0f / 3.14159265f);
static const n128 f4_deg2rad		= _hlslpp_set1_ps(3.14159265f / 180.f);

// Masks
static const n128 f4negativeMask	= _hlslpp_set1_ps(negMask.f);
static const n128 f4absMask			= _hlslpp_set1_ps(absMask.f);

static const uint32_t _MM_X = 0;
static const uint32_t _MM_Y = 1;
static const uint32_t _MM_Z = 2;
static const uint32_t _MM_W = 3;

// Create a mask where 1 selects from x, 0 selects from y
#define HLSLPP_BLEND_MASK(X, Y, Z, W)			(~(X | (Y << 1) | (Z << 2) | (W << 3)) & 0xf)

#define HLSLPP_COMPONENT_X(X)					(1 << X)
#define HLSLPP_COMPONENT_XY(X, Y)				((1 << X) | (1 << Y))
#define HLSLPP_COMPONENT_XYZ(X, Y, Z)			((1 << X) | (1 << Y) | (1 << Z))
#define HLSLPP_COMPONENT_XYZW(X, Y, Z, W)		((1 << X) | (1 << Y) | (1 << Z) | (1 << W))

#define HLSLPP_SHUFFLE_MASK(X, Y, Z, W)			(((W) << 6) | ((Z) << 4) | ((Y) << 2) | (X))

// Helper compound "intrinsics"

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

// See http://http.developer.nvidia.com/Cg/fmod.html for reference
// This implementation does not follow the reference
// float2 c = frac(abs(a/b))*abs(b);
// return (a < 0) ? -c : c;    // if ( a < 0 ) c = 0-c
inline n128 _hlslpp_fmod_ps(n128 x, n128 y)
{
	n128 div = _hlslpp_div_ps(x, y);
	n128 trnc = _hlslpp_sub_ps(div, _hlslpp_trunc_ps(div));
	return _hlslpp_mul_ps(trnc, y);
}

// Cross product for 3-component vectors
// TODO Can apparently be done with one less shuffle http://fastcpp.blogspot.co.uk/2011/04/vector-cross-product-using-sse-code.html
inline n128 _hlslpp_cross_ps(n128 x, n128 y)
{
	n128 yzx_0 = _hlslpp_perm_yzxx_ps(x);
	n128 zxy_1 = _hlslpp_perm_zxyx_ps(y);

	n128 zxy_0 = _hlslpp_perm_zxyx_ps(x);
	n128 yzx_1 = _hlslpp_perm_yzxx_ps(y);

	return _hlslpp_msub_ps(yzx_0, zxy_1, _hlslpp_mul_ps(zxy_0, yzx_1));
}

static const n128 log2_c0 = _hlslpp_set1_ps( 3.1157899f);
static const n128 log2_c1 = _hlslpp_set1_ps(-3.3241990f);
static const n128 log2_c2 = _hlslpp_set1_ps( 2.5988452f);
static const n128 log2_c3 = _hlslpp_set1_ps(-1.2315303f);
static const n128 log2_c4 = _hlslpp_set1_ps( 3.1821337e-1f);
static const n128 log2_c5 = _hlslpp_set1_ps(-3.4436006e-2f);

// See http://jrfonseca.blogspot.co.uk/2008/09/fast-sse2-pow-tables-or-polynomials.html for derivation
// Fonseca derives from here: http://forum.devmaster.net/t/approximate-math-library/11679
inline n128 _hlslpp_log2_ps(n128 x)
{
	n128i exp = _hlslpp_set1_epi32(0x7F800000);
	n128i mant = _hlslpp_set1_epi32(0x007FFFFF);

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

	return _hlslpp_add_ps(p, e);
}

static const n128 invlog_2_10 = _hlslpp_div_ps(f4_1, _hlslpp_log2_ps(f4_10));

inline n128 _hlslpp_log10_ps(n128 x)
{
	return _hlslpp_mul_ps(_hlslpp_log2_ps(x), invlog_2_10);
}

static const n128 invlog_2_e = _hlslpp_div_ps(f4_1, _hlslpp_log2_ps(f4_e));

inline n128 _hlslpp_log_ps(n128 x)
{
	return _hlslpp_mul_ps(_hlslpp_log2_ps(x), invlog_2_e);
}

inline n128 _hlslpp_lrp_ps(n128 x, n128 y, n128 a)
{
	// Slower
	// n128 y_minus_x = _mm_sub_ps(y, x);
	// n128 result = _hlslpp_madd_ps(y_minus_x, a, x);

	n128 one_minus_a = _hlslpp_sub_ps(f4_1, a);
	n128 x_one_minus_a = _hlslpp_mul_ps(x, one_minus_a);
	n128 result = _hlslpp_madd_ps(y, a, x_one_minus_a);
	return result;
}

static const n128 exp2_c0 = _hlslpp_set1_ps(1.0f);
static const n128 exp2_c1 = _hlslpp_set1_ps(6.9315308e-1f);
static const n128 exp2_c2 = _hlslpp_set1_ps(2.4015361e-1f);
static const n128 exp2_c3 = _hlslpp_set1_ps(5.5826318e-2f);
static const n128 exp2_c4 = _hlslpp_set1_ps(8.9893397e-3f);
static const n128 exp2_c5 = _hlslpp_set1_ps(1.8775767e-3f);

static const n128 exp2_129 = _hlslpp_set1_ps(129.00000f);
static const n128 exp2_m127 = _hlslpp_set1_ps(-126.99999f);
static const n128i exp2_127 = _hlslpp_set1_epi32(127);

// See http://jrfonseca.blogspot.co.uk/2008/09/fast-sse2-pow-tables-or-polynomials.html for derivation

inline n128 _hlslpp_exp2_ps(n128 x)
{
	n128i ipart;
	n128 fpart, expipart, expfpart;

	// Clamp values
	x = _hlslpp_min_ps(x, exp2_129);
	x = _hlslpp_max_ps(x, exp2_m127);

	// ipart = int(x - 0.5)
	ipart = _hlslpp_cvtps_epi32(_hlslpp_sub_ps(x, f4_05));

	// fpart = x - ipart
	fpart = _hlslpp_sub_ps(x, _hlslpp_cvtepi32_ps(ipart));

	// expipart = (float) (1 << ipart)
	expipart = _hlslpp_castsi128_ps(_hlslpp_slli_epi32(_hlslpp_add_epi32(ipart, exp2_127), 23));

	// Minimax polynomial fit of 2^x, in range [-0.5, 0.5[
	expfpart = _hlslpp_madd_ps(fpart, exp2_c5, exp2_c4);
	expfpart = _hlslpp_madd_ps(fpart, expfpart, exp2_c3);
	expfpart = _hlslpp_madd_ps(fpart, expfpart, exp2_c2);
	expfpart = _hlslpp_madd_ps(fpart, expfpart, exp2_c1);
	expfpart = _hlslpp_madd_ps(fpart, expfpart, exp2_c0);

	return _hlslpp_mul_ps(expipart, expfpart);
}

static const n128 log_2_e = _hlslpp_log2_ps(f4_e);

inline n128 _hlslpp_exp_ps(n128 x)
{
	return _hlslpp_exp2_ps(_hlslpp_mul_ps(x, log_2_e));
}

static const n128 sin_c1 = f4_1;
static const n128 sin_c3 = _hlslpp_set1_ps(-1.6665578e-1f);
static const n128 sin_c5 = _hlslpp_set1_ps( 8.3109378e-3f);
static const n128 sin_c7 = _hlslpp_set1_ps(-1.84477486e-4f);

// Uses a minimax polynomial fitted to the [-pi/2, pi/2] range
inline n128 _hlslpp_sin_ps(n128 x)
{	
	// Range reduction (into [-2pi, 2pi] range)
	n128 reduced;
	reduced = _hlslpp_mul_ps(x, f4_inv2pi);
	x = _hlslpp_sub_ps(x, _hlslpp_mul_ps(_hlslpp_trunc_ps(reduced), f4_2pi));

	n128 gtpi2			= _hlslpp_cmpgt_ps(x, f4_pi2);
	n128 ltminusPi2		= _hlslpp_cmplt_ps(x, f4_minusPi2);
	n128 gt3pi2			= _hlslpp_cmpgt_ps(x, f4_3pi2);
	n128 lt3minus3pi2	= _hlslpp_cmplt_ps(x, f4_minus3pi2);

	n128 ox = x;

	// Use identities/mirroring to remap into the range of the minimax polynomial
	x = _hlslpp_sel_ps(x, _hlslpp_sub_ps(f4_pi, ox),		gtpi2);
	x = _hlslpp_sel_ps(x, _hlslpp_sub_ps(f4_minusPi, ox),	ltminusPi2);
	x = _hlslpp_sel_ps(x, _hlslpp_add_ps(ox, f4_minus2pi),	gt3pi2);
	x = _hlslpp_sel_ps(x, _hlslpp_add_ps(ox, f4_2pi),		lt3minus3pi2);

	n128 x2 = _hlslpp_mul_ps(x, x);
	n128 result;
	result = _hlslpp_madd_ps(x2, sin_c7, sin_c5);
	result = _hlslpp_madd_ps(x2, result, sin_c3);
	result = _hlslpp_madd_ps(x2, result, sin_c1);
	result = _hlslpp_mul_ps(result, x);
	return result;
}

static const n128 cos_c0 = f4_1;
static const n128 cos_c2 = _hlslpp_set1_ps(-4.999274621e-1f);
static const n128 cos_c4 = _hlslpp_set1_ps( 4.149392034e-2f);
static const n128 cos_c6 = _hlslpp_set1_ps(-1.271243501e-3f);

// Uses a minimax polynomial fitted to the [-pi/2, pi/2] range
inline n128 _hlslpp_cos_ps(n128 x)
{	
	// Range reduction (into [-pi, pi] range)
	n128 reduced;
	reduced = _hlslpp_div_ps(x, f4_2pi);
	n128 reduceTrunc = _hlslpp_mul_ps(_hlslpp_trunc_ps(reduced), f4_2pi);
	x = _hlslpp_sub_ps(x, reduceTrunc);

	n128 gtPi2		= _hlslpp_cmpgt_ps(x, f4_pi2);			// x >  pi/2 ?
	n128 ltMinusPi2	= _hlslpp_cmplt_ps(x, f4_minusPi2);		// x < -pi/2 ?

	x = _hlslpp_sel_ps(x, _hlslpp_add_ps(f4_minusPi, x), gtPi2);
	x = _hlslpp_sel_ps(x, _hlslpp_add_ps(f4_pi, x), ltMinusPi2);

	n128 x2 = _hlslpp_mul_ps(x, x);
	n128 result;
	result = _hlslpp_madd_ps(x2, cos_c6, cos_c4);
	result = _hlslpp_madd_ps(x2, result, cos_c2);
	result = _hlslpp_madd_ps(x2, result, cos_c0);

	// if(abs(x) < pi/2) return cos(x)
	// if(x >  pi/2) return -cos(-pi + x)
	// if(x < -pi/2) return -cos( pi + x)

	//result = _hlslpp_sel_ps(result, _hlslpp_neg_ps(result), _mm_or_ps(gtPi2, ltMinusPi2));

	return result;
}

static const n128 tan_c1 = f4_1;
static const n128 tan_c3 = _hlslpp_set1_ps(3.329923284e-1f);
static const n128 tan_c5 = _hlslpp_set1_ps(1.374784343e-1f);
static const n128 tan_c7 = _hlslpp_set1_ps(3.769634481e-2f);
static const n128 tan_c9 = _hlslpp_set1_ps(4.609737727e-2f);

// Uses a minimax polynomial fitted to the [-pi/4, pi/4] range
inline n128 _hlslpp_tan_ps(n128 x)
{
	// Range reduction (into [-pi/2, pi/2] range)
	x = _hlslpp_fmod_ps(x, f4_pi2);

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

	n128 lateralResult = _hlslpp_div_ps(f4_1, centerResult); // Valid from [-pi/2, -pi/4) U (pi/4, pi/2]

	n128 result = _hlslpp_sel_ps(centerResult, lateralResult, gtltPi4);

	return result;
}

static const n128 asinacos_c0 = f4_pi2;
static const n128 asinacos_c1 = _hlslpp_set1_ps(-2.145329213e-1f);
static const n128 asinacos_c2 = _hlslpp_set1_ps( 8.797308928e-2f);
static const n128 asinacos_c3 = _hlslpp_set1_ps(-4.513026638e-2f);
static const n128 asinacos_c4 = _hlslpp_set1_ps( 1.946746668e-2f);
static const n128 asinacos_c5 = _hlslpp_set1_ps(-4.360132611e-3f);

// Max error vs. std::acos = 1.54972076e-6
inline n128 _hlslpp_acos_ps(n128 x)
{
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

// Max error vs. std::asin = 1.5348196e-6
inline n128 _hlslpp_asin_ps(n128 x)
{
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

static const n128 atan_c1  = f4_1;
static const n128 atan_c3  = _hlslpp_set1_ps(-3.329452768e-1f);
static const n128 atan_c5  = _hlslpp_set1_ps( 1.949865716e-1f);
static const n128 atan_c7  = _hlslpp_set1_ps(-1.192157627e-1f);
static const n128 atan_c9  = _hlslpp_set1_ps( 5.506335136e-2f);
static const n128 atan_c11 = _hlslpp_set1_ps(-1.249072006e-2f);

// Max error vs. std::atan = 2.74181366e-6
inline n128 _hlslpp_atan_ps(n128 x)
{
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

inline n128 _hlslpp_dot4_ps(n128 x, n128 y)
{
	// SSE3 slower
	// __m128 m			= _mm_mul_ps(x, y);				// Multiply components together
	// __m128 h1		= _mm_hadd_ps(m, m);			// Add once
	// __m128 result	= _mm_hadd_ps(h1, h1);		// Add twice

	// SSE4 slower
	// __m128 result	= _mm_dp_ps(x, y, 0xff);

	// SSE2
	n128 multi	= _hlslpp_mul_ps(x, y);				// Multiply components together
	n128 shuf1	= _hlslpp_perm_yxwx_ps(multi);		// Move y into x, and w into z (ignore the rest)
	n128 add1	= _hlslpp_add_ps(shuf1, multi);		// Contains x+y, _, z+w, _
	n128 shuf2	= _hlslpp_perm_zzzz_ps(add1);		// Move (z + w) into x
	n128 result	= _hlslpp_add_ps(add1, shuf2);		// Contains x+y+z+w, _, _, _

	return result;
}

inline n128 _hlslpp_dot3_ps(n128 x, n128 y)
{
	// SSE4 slower
	// __m128 result = _mm_dp_ps(v1.xyzw, v2.xyzw, 0x7f);

	// SSE2
	n128 multi	= _hlslpp_mul_ps(x, y);			// Multiply components together
	n128 shuf1	= _hlslpp_perm_yyyy_ps(multi);	// Move y into x
	n128 add1	= _hlslpp_add_ps(shuf1, multi);	// Contains x+y, _, _, _
	n128 shuf2	= _hlslpp_perm_zzzz_ps(multi);	// Move z into x
	n128 result	= _hlslpp_add_ps(add1, shuf2);	// Contains x+y+z, _, _, _

	return result;
}

inline n128 _hlslpp_dot2_ps(n128 x, n128 y)
{
	n128 multi	= _hlslpp_mul_ps(x, y);			// Multiply components together
	n128 shuf1	= _hlslpp_perm_yyyy_ps(multi);	// Move y into x
	n128 result = _hlslpp_add_ps(shuf1, multi);	// Contains x+y, _, _, _

	return result;
}

// Auxiliary dot3 that adds, subtracts, adds instead of adding all
inline n128 _hlslpp_dot3_asa_ps(n128 x, n128 y)
{
	n128 multi	= _hlslpp_mul_ps(x, y);			// Multiply components together
	n128 shuf1	= _hlslpp_perm_yyyy_ps(multi);	// Move y into x
	n128 add1	= _hlslpp_sub_ps(multi, shuf1);	// Contains x-y, _, _, _
	n128 shuf2	= _hlslpp_perm_zzzz_ps(multi);	// Move z into x
	n128 result	= _hlslpp_add_ps(add1, shuf2);	// Contains x-y+z, _, _, _
	return result;
}

inline n128 _hlslpp_any_ps(n128 x)
{
	n128 shuf1	= _hlslpp_perm_yxwx_ps(x);					// Move y into x, and w into z (ignore the rest)
	n128 add1	= _hlslpp_add_ps(shuf1, x);					// Contains x+y, _, z+w, _
	n128 shuf2	= _hlslpp_perm_zxxx_ps(add1);				// Move (z + w) into x
	n128 add2	= _hlslpp_add_ps(add1, shuf2);				// Contains x+y+z+w, _, _, _
	n128 neZero	= _hlslpp_cmpneq_ps(add2, f4_0);
	n128 result	= _hlslpp_perm_xxxx_ps(neZero);				// Replicate in all components

	return result;
}

inline n128 _hlslpp_all_ps(n128 x)
{
	n128 shuf1	= _hlslpp_perm_yxwx_ps(x);					// Move y into x, and w into z (ignore the rest)
	n128 mul1	= _hlslpp_mul_ps(shuf1, x);					// Contains x*y, _, z*w, _
	n128 shuf2	= _hlslpp_perm_zxxx_ps(mul1);				// Move (z * w) into x
	n128 mul2	= _hlslpp_mul_ps(mul1, shuf2);				// Contains x*y*z*w, _, _, _
	n128 neZero	= _hlslpp_cmpneq_ps(mul2, f4_0);
	n128 result	= _hlslpp_perm_xxxx_ps(neZero);				// Replicate in all components

	return result;
}

// Returns true if x is nan
inline n128 _hlslpp_isnan_ps(n128 x)
{
	return _hlslpp_cmpneq_ps(x, x);
}

// Returns true if x is +infinity or -infinity
inline n128 _hlslpp_isinf_ps(n128 x)
{
	return _hlslpp_or_ps(_hlslpp_cmpeq_ps(x, f4_inf), _hlslpp_cmpeq_ps(x, f4_minusinf));
}

// Returns true if x is not +infinity or -infinity
inline n128 _hlslpp_isfinite_ps(n128 x)
{
	return _hlslpp_and_ps(_hlslpp_and_ps(_hlslpp_cmpneq_ps(x, f4_inf), _hlslpp_cmpneq_ps(x, f4_minusinf)), _hlslpp_cmpeq_ps(x, x));
}

inline n128 _hlslpp_transpose_2x2_ps(n128 m)
{
	return _hlslpp_perm_xzyw_ps(m);
}

inline void _hlslpp_transpose_3x3_ps(const n128& vec0, const n128& vec1, const n128& vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
{
	n128 shuf_tmp_0 = _hlslpp_shuf_xyxy_ps(vec0, vec1);
	n128 shuf_tmp_1 = _hlslpp_shuf_yzyz_ps(vec0, vec1);

	o_vec0 = _hlslpp_shuf_xzxw_ps(shuf_tmp_0, vec2);
	o_vec1 = _hlslpp_shuf_ywyw_ps(shuf_tmp_0, vec2);
	o_vec2 = _hlslpp_shuf_ywzw_ps(shuf_tmp_1, vec2);
}

inline void _hlslpp_transpose_4x4_ps(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
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

inline n128 _hlslpp_det_2x2_ps(n128 m)
{
	// The determinant for a 2x2 matrix is m00 * m11 - m01 * m10
	n128 shuf_1 = _hlslpp_perm_wzxx_ps(m);	// Shuffle w and z into x and y to multiply them together
	n128 prod = _hlslpp_mul_ps(m, shuf_1);		// Now this vector contains wx, zy, _, _
	n128 shuf_2 = _hlslpp_perm_yxxx_ps(prod);	// Shuffle yz into where xw is to subtract them
	n128 result = _hlslpp_sub_ps(prod, shuf_2);	// Determinant is now in the x component
	return result;
}

inline n128 _hlslpp_det_3x3_ps(n128 vec0, n128 vec1, n128 vec2)
{
	// The determinant for a 3x3 matrix can be expressed as dot[ (m00, m01, m02), (m11 * m22 - m12 * m21, m12 * m20 - m10 * m22, m10 * m21 - m11 * m20) ]
	n128 shuf_1 = _hlslpp_perm_yzxw_ps(vec2);
	n128 prod_1 = _hlslpp_mul_ps(vec1, shuf_1);
	
	n128 shuf_2 = _hlslpp_perm_yzxw_ps(vec1);
	n128 prod_2 = _hlslpp_mul_ps(shuf_2, vec2);
	
	n128 sub	= _hlslpp_sub_ps(prod_1, prod_2);

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

template<int N> class floatN {};

using float1 = floatN<1>;
using float2 = floatN<2>;
using float3 = floatN<3>;
using float4 = floatN<4>;

template<int N, int M> class floatNxM {};

// These need to be explicitly declared, otherwise floatN types cannot reference any float1xM or floatNx1 types, as the compiler looks for specialization
template<> class floatNxM<1, 1>;
template<> class floatNxM<1, 2>;
template<> class floatNxM<1, 3>;
template<> class floatNxM<1, 4>;
template<> class floatNxM<2, 1>;
template<> class floatNxM<3, 1>;
template<> class floatNxM<4, 1>;

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

template<int A>
class component1
{
public:
	n128 _vec;

	component1<A>() {}

	template<int E>
	component1<A>& operator = (const component1<E>& p);
	component1<A>& operator = (float f);
	component1<A>& operator = (const float1& v);
	component1<A>& operator = (const float1x1& m);

	operator float() const
	{
#if defined(__clang__) || defined(__GNUG__) // Either clang++ or g++
		return _vec[A];
#else
		return _vec.m128_f32[A];
#endif
	}
};

template<int X, int Y>
class component2
{
public:
	n128 _vec;

	void staticAsserts()
	{
		// Assert that no component is equal to each other for assignment
		static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
	}

	static n128 blend(n128 x, n128 y)
	{
		return _hlslpp_blend_ps(x, y, HLSLPP_COMPONENT_XY(X, Y));									// Select based on property mask
	}

	template<int E, int F, int A, int B>
	static n128 swizzle(n128 x)
	{
		const int mask = HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_W);
		const uint32_t reshuffledMask = (((mask >> (2 * E)) & 3) << (2 * A)) | (((mask >> (2 * F)) & 3) << (2 * B)) | (mask & ~((3 << 2 * A) | (3 << 2 * B)));
		const n128 inputShuffle = _hlslpp_shuffle_ps(x, x, reshuffledMask);	// Swizzle input mask with property mask
		return inputShuffle;
	}
	
	component2<X, Y>() {}
	explicit component2<X, Y>(n128 vec) : _vec(vec) {}

	template<int E, int F>
	component2<X, Y>& operator = (const component2<E, F>& c);
	component2<X, Y>& operator = (const component2<X, Y>& c);
	component2<X, Y>& operator = (const float2& v);
};

template<int X, int Y, int Z>
class component3
{
public:
	n128 _vec;

	void staticAsserts()
	{
		// Assert that no component is equal to each other for assignment
		static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
	}

	static n128 blend(n128 x, n128 y)
	{
		return _hlslpp_blend_ps(x, y, HLSLPP_COMPONENT_XYZ(X, Y, Z));							// Select based on property mask
	}

	template<int E, int F, int G, int A, int B, int C>
	static n128 swizzle(n128 x)
	{
		static const int mask = HLSLPP_SHUFFLE_MASK(_MM_X, _MM_Y, _MM_Z, _MM_W);
		const uint32_t reshuffledMask = (((mask >> (2 * E)) & 0x3) << (2 * A)) | (((mask >> (2 * F)) & 0x3) << (2 * B)) | (((mask >> (2 * G)) & 0x3) << (2 * C)) | (mask & ~((3 << 2 * A) | (3 << 2 * B) | (3 << 2 * C)));
		n128 inputShuffle = _hlslpp_shuffle_ps(x, x, reshuffledMask);	// Swizzle input mask with property mask
		return inputShuffle;
	}

	component3<X, Y, Z>() {}
	explicit component3<X, Y, Z>(n128 vec) : _vec(vec) {}

	template<int E, int F, int G>
	component3<X, Y, Z>& operator = (const component3<E, F, G>& c);
	component3<X, Y, Z>& operator = (const component3<X, Y, Z>& c);
	component3<X, Y, Z>& operator = (const float3& v);
};

template<int X, int Y, int Z, int W>
class component4
{
public:
	n128 _vec;

	void staticAsserts()
	{
		// Assert that no component is equal to each other for assignment
		static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
	}

	component4<X, Y, Z, W>() {}
	explicit component4<X, Y, Z, W>(n128 vec) : _vec(vec) {}

	template<int E, int F, int G, int H>
	inline component4<X, Y, Z, W>& operator = (const component4<E, F, G, H>& c);
	inline component4<X, Y, Z, W>& operator = (const component4<X, Y, Z, W>& c);
	inline component4<X, Y, Z, W>& operator = (const float4& v);
};

template<>
class floatN<1>
{
public:
	union
	{
		n128 _vec;
		#include "swizzle/hlsl++_vector_x.h"
	};

	explicit floatN<1>(n128 vec) : _vec(vec) {}
	floatN<1>() {}
	/*explicit*/ floatN<1>(float f) : _vec(_hlslpp_set_ps(f, 0.0f, 0.0f, 0.0f)) {}
	floatN<1>(const floatN<1>& v) : _vec(v._vec) {}
	template<int A>
	floatN<1>(const component1<A>& c);
	explicit floatN<1>(const floatNxM<1, 1>& v);

	floatN<1>& operator = (float f);
	floatN<1>& operator = (const floatN<1>& c);
	template<int A>
	floatN<1>& operator = (const component1<A>& c);
	floatN<1>& operator = (const float1x1& m);

	operator float() const
	{
#if defined(__clang__) || defined(__GNUG__) // Either clang++ or g++
		return _vec[0];
#else
		return _vec.m128_f32[0];
#endif
	}
};

template<>
class floatN<2>
{
public:
	union
	{
		n128 _vec;
		#include "swizzle/hlsl++_vector_x.h"
		#include "swizzle/hlsl++_vector_y.h"
	};

	explicit floatN<2>(n128 vec) : _vec(vec) {}
	floatN<2>() {}
	explicit floatN<2>(float f) : _vec(_hlslpp_set_ps(f, f, 0.0f, 0.0f)) {}
	floatN<2>(float x, float y) : _vec(_hlslpp_set_ps(x, y, 0.0f, 0.0f)) {}
	floatN<2>(const floatN<2>& v) : _vec(v._vec) {}
	floatN<2>(const floatN<1>& v1,	const floatN<1>& v2);
	
	explicit floatN<2>(const float2x1& v);
	explicit floatN<2>(const float1x2& v);

	floatN<2>(const float1& v1,		const float v2)		: floatN<2>(v1, float1(v2)) {}
	floatN<2>(const float v1,		const float1& v2)	: floatN<2>(float1(v1), v2) {}
	template<int A> floatN<2>(const component1<A>& v1,	const float1& v2)				: floatN<2>(float1(v1), v2) {}
	template<int A> floatN<2>(const float1& v1,			const component1<A>& v2)		: floatN<2>(v1, float1(v2)) {}
	template<int A> floatN<2>(const component1<A>& v1,	const float v2)					: floatN<2>(float1(v1), float1(v2)) {}
	template<int A> floatN<2>(const float v1,			const component1<A>& v2)		: floatN<2>(float1(v1), float1(v2)) {}
	template<int A, int B> floatN<2>(const component1<A>& v1, const component1<B>& v2)	: floatN<2>(float1(v1), float1(v2)) {}

	template<int A, int B> floatN<2>(const component2<A, B>& c);

	floatN<2>& operator = (const floatN<2>& c);

	template<int A, int B> floatN<2>& operator = (const component2<A, B>& c);
};

template<>
class floatN<3>
{
public:
	union
	{
		n128 _vec;
		#include "swizzle/hlsl++_vector_x.h"
		#include "swizzle/hlsl++_vector_y.h"
		#include "swizzle/hlsl++_vector_z.h"
	};

	explicit floatN<3>(n128 vec) : _vec(vec) {}
	floatN<3>() {}
	explicit floatN<3>(float f) : _vec(_hlslpp_set_ps(f, f, f, 0.0f)) {}
	floatN<3>(const floatN<3>& v) : _vec(v._vec) {}
	floatN<3>(const float x,		const float y,			const float z) : _vec(_hlslpp_set_ps(x, y, z, 0.0f)) {}

	// floatN constructors
	floatN<3>(const float1& v1,	const float1& v2,	const floatN<1>& v3);
	floatN<3>(const float2& v1,	const float1& v2);
	floatN<3>(const float1& v1,	const float2& v2);

	// componentN constructors
	template<int A, int B, int C> floatN<3>(const component1<A>& v1,	const component1<B>& v2,	const component1<C>& v3)			: floatN<3>(float1(v1), float1(v2), float1(v3)) {}
	template<int A, int B, int C> floatN<3>(const component2<A, B>& v1,	const component1<C>& v2)	: floatN<3>(float2(v1), float1(v2)) {}
	template<int A, int B, int C> floatN<3>(const component1<A>& v1,	const component2<B, C>& v2)	: floatN<3>(float1(v1), float2(v2)) {}
	template<int A, int B, int C> floatN<3>(const component3<A, B, C>& c);

	// floatN + float constructors
	floatN<3>(const float v1,	const float1& v2,	const float1& v3);
	floatN<3>(const float1& v1,	const float v2,		const float1& v3);
	floatN<3>(const float1& v1,	const float1& v2,	const float v3);
	floatN<3>(const float v1,	const float v2,		const float1& v3);
	floatN<3>(const float1& v1,	const float v2,		const float v3);
	floatN<3>(const float v1,	const float1& v2,	const float v3);

	// floatN + componentN constructors
	template<int A> floatN<3>(const float1& v1,	const float1& v2,			const component1<A>& v3)	: floatN<3>(v1, v2, float1(v3)) {}
	template<int A> floatN<3>(const float1& v1,	const component1<A>& v2,	const float1& v3)			: floatN<3>(v1, float1(v2), v3) {}
	template<int A> floatN<3>(const component1<A>& v1,	const float1& v2,	const float1& v3)			: floatN<3>(float1(v1), v2, v3) {}

	template<int A, int B> floatN<3>(const float1& v1,			const component1<A>& v2,	const component1<B>& v3)	: floatN<3>(v1, float1(v2), float1(v3)) {}
	template<int A, int B> floatN<3>(const component1<A>& v1,	const float1& v2,			const component1<B>& v3)	: floatN<3>(float1(v1), v2, float1(v3)) {}
	template<int A, int B> floatN<3>(const component1<A>& v1,	const component1<B>& v2,	const float1& v3)			: floatN<3>(float1(v1), float1(v2), v3) {}

	template<int A, int B> floatN<3>(const float1& v1,	const component2<A, B>& v2)	: floatN<3>(v1, float2(v2)) {}
	template<int A, int B> floatN<3>(const component2<A, B>& v1, const float1& v2)	: floatN<3>(float2(v1), v2) {}

	// float + componentN constructors
	template<int A> floatN<3>(const float& v1, const float& v2, const component1<A>& v3) : floatN<3>(float2(v1, v2), float1(v3)) {}
	template<int A> floatN<3>(const float& v1, const component1<A>& v2, const float& v3) : floatN<3>(float1(v1), float1(v2), float1(v3)) {}
	template<int A> floatN<3>(const component1<A>& v1, const float& v2, const float& v3) : floatN<3>(float1(v1), float2(v2, v3)) {}

	template<int A, int B> floatN<3>(const float& v1, const component1<A>& v2, const component1<B>& v3) : floatN<3>(float1(v1), float1(v2), float1(v3)) {}
	template<int A, int B> floatN<3>(const component1<A>& v1, const float& v2, const component1<B>& v3) : floatN<3>(float1(v1), float1(v2), float1(v3)) {}
	template<int A, int B> floatN<3>(const component1<A>& v1, const component1<B>& v2, const float& v3) : floatN<3>(float1(v1), float1(v2), float1(v3)) {}

	template<int A, int B> floatN<3>(const float& v1, const component2<A, B>& v2) : floatN<3>(float1(v1), float2(v2)) {}
	template<int A, int B> floatN<3>(const component2<A, B>& v1, const float& v2) : floatN<3>(float2(v1), float1(v2)) {}

	// floatN + componentN + float constructors
	template<int A> floatN<3>(const float1& v1,	const component1<A>& v2,	const float v3)				: floatN<3>(v1, float1(v2), float1(v3)) {}
	template<int A> floatN<3>(const float1& v1,	const float v2,				const component1<A>& v3)	: floatN<3>(v1, float1(v2), float1(v3)) {}

	template<int A> floatN<3>(const float v1,	const float1& v2,			const component1<A>& v3)	: floatN<3>(float1(v1), v2, float1(v3)) {}
	template<int A> floatN<3>(const float v1,	const component1<A>& v2,	const float1& v3)			: floatN<3>(float1(v1), float1(v2), v3) {}

	template<int A> floatN<3>(const component1<A>& v1,	const float1& v2,	const float v3)			: floatN<3>(float1(v1), v2, float1(v3)) {}
	template<int A> floatN<3>(const component1<A>& v1,	const float v2,		const float1& v3)		: floatN<3>(float1(v1), float1(v2), v3) {}

	explicit floatN<3>(const float3x1& v);
	explicit floatN<3>(const float1x3& v);

	floatN<3>& operator = (const floatN<3>& c);
	template<int A, int B, int C>
	floatN<3>& operator = (const component3<A, B, C>& c);
};

template<>
class floatN<4>
{
public:
	union
	{
		n128 _vec;
		#include "swizzle/hlsl++_vector_x.h"
		#include "swizzle/hlsl++_vector_y.h"
		#include "swizzle/hlsl++_vector_z.h"
		#include "swizzle/hlsl++_vector_w.h"
	};

	explicit floatN<4>(n128 vec) : _vec(vec) {}
	floatN<4>() {}
	explicit floatN<4>(float f) : _vec(_hlslpp_set1_ps(f)) {}
	floatN<4>(float x, float y, float z, float w) : _vec(_hlslpp_set_ps(x, y, z, w)) {}
	
	// floatN constructors
	floatN<4>(const floatN<4>& v) : _vec(v._vec) {}
	floatN<4>(const floatN<1>& v1,	const floatN<1>& v2,	const floatN<1>& v3,	const floatN<1>& v4);
	floatN<4>(const floatN<2>& v1,	const floatN<1>& v2,	const floatN<1>& v3);
	floatN<4>(const floatN<1>& v1,	const floatN<2>& v2,	const floatN<1>& v3);
	floatN<4>(const floatN<1>& v1,	const floatN<1>& v2,	const floatN<2>& v3);
	floatN<4>(const floatN<2>& v1,	const floatN<2>& v2);
	floatN<4>(const floatN<1>& v1,	const floatN<3>& v2);
	floatN<4>(const floatN<3>& v1,	const floatN<1>& v2);

	// componentN constructors
	template<int A, int B, int C, int D> floatN<4>(const component1<A>& v1,	const component1<B>& v2,	const component1<C>& v3,	const component1<D>& v4) : floatN<4>(float1(v1), float1(v2), float1(v2), float1(v2)) {}
	template<int A, int B, int C, int D> floatN<4>(const component4<A, B, C, D>& c);

	// floatN + float constructors
	floatN<4>(const float v1,		const float1& v2,	const float1& v3,	const float1& v4)	: float4(float1(v1), v2, v3, v4) {}
	floatN<4>(const float1& v1,		const float v2,		const float1& v3,	const float1& v4)	: float4(v1, float1(v2), v3, v4) {}
	floatN<4>(const float1& v1,		const float1& v2,	const float v3,		const float1& v4)	: float4(v1, v2, float1(v3), v4) {}
	floatN<4>(const float1& v1,		const float1& v2,	const float1& v3,	const float v4)		: float4(v1, v2, v3, float1(v4)) {}

	floatN<4>(const float1& v1,		const float v2,		const float v3,		const float v4);
	floatN<4>(const float v1,		const float1& v2,	const float v3,		const float v4);
	floatN<4>(const float v1,		const float v2,		const float1& v3,	const float v4);
	floatN<4>(const float v1,		const float v2,		const float v3,		const float1& v4);
	
	floatN<4>(const float v1,		const float1& v2,	const float1& v3,	const float v4);
	floatN<4>(const float v1,		const float v2,		const float1& v3,	const float1& v4);
	floatN<4>(const float v1,		const float1& v2,	const float v3,		const float1& v4);

	floatN<4>(const float1& v1,		const float v2,		const float v3,		const float1& v4);
	floatN<4>(const float1& v1,		const float1& v2,	const float v3,		const float v4);
	floatN<4>(const float1& v1,		const float v2,		const float1& v3,	const float v4);

	floatN<4>(const float2& v1,		const float v2,		const float1& v3)	: float4(v1, float1(v2), v3) {}
	floatN<4>(const float2& v1,		const float1& v2,	const float v3)		: float4(v1, v2, float1(v3)) {}
	floatN<4>(const float2& v1,		const float v2,		const float v3)		: float4(v1, v2, float1(v3)) {}

	floatN<4>(const float v1,		const float2& v2,	const float1& v3)	: float4(float1(v1), v2, v3) {}
	floatN<4>(const float1& v1,		const float2& v2,	const float v3)		: float4(v1, v2, float1(v3)) {}

	floatN<4>(const float v1,		const float1& v2,	const float2& v3)	: float4(float1(v1), v2, v3) {}
	floatN<4>(const float1& v1,		const float v2,		const float2& v3)	: float4(v1, float1(v2), v3) {}
	floatN<4>(const float v1,		const float v2,		const float2& v3)	: float4(float2(v1, v2), v3) {}

	floatN<4>(const float v1,		const float3& v2)	: float4(float1(v1), v2) {}
	floatN<4>(const float3& v1,		const float v2)		: float4(v1, float1(v2)) {}

	// floatN + componentN constructors
	template<int A> floatN<4>(const component1<A>& v1,	const float1& v2,			const float1& v3,			const float1& v4)			: floatN<4>(float1(v1), v2, v3, v4) {}
	template<int A> floatN<4>(const float1& v1,			const component1<A>& v2,	const float1& v3,			const float1& v4)			: floatN<4>(v1, float1(v2), v3, v4) {}
	template<int A> floatN<4>(const float1& v1,			const float1& v2,			const component1<A>& v3,	const float1& v4)			: floatN<4>(v1, v2, float1(v3), v4) {}
	template<int A> floatN<4>(const float1& v1,			const float1& v2,			const float1& v3,			const component1<A>& v4)	: floatN<4>(v1, v2, v3, float1(v4)) {}

	template<int A, int B, int C> floatN<4>(const float1& v1,			const component1<A>& v2,	const component1<B>& v3,	const component1<C>& v4)	: floatN<4>(v1, float1(v2), float1(v3), float1(v4)) {}
	template<int A, int B, int C> floatN<4>(const component1<A>& v1,	const float1& v2,			const component1<B>& v3,	const component1<C>& v4)	: floatN<4>(float1(v1), v2, float1(v3), float1(v4)) {}
	template<int A, int B, int C> floatN<4>(const component1<A>& v1,	const component1<B>& v2,	const float1& v3,			const component1<C>& v4)	: floatN<4>(float1(v1), float1(v2), v3, float1(v4)) {}
	template<int A, int B, int C> floatN<4>(const component1<A>& v1,	const component1<B>& v2,	const component1<C>& v3,	const float1& v4)			: floatN<4>(float1(v1), float1(v2), float1(v3), v4) {}

	template<int A, int B> floatN<4>(const component1<A>& v1,	const float1& v2,			const float1& v3,			const component1<B>& v4)	: floatN<4>(float1(v1), v2, v3, float1(v4)) {}
	template<int A, int B> floatN<4>(const component1<A>& v1,	const component1<B>& v2,	const float1& v3,			const float1& v4)			: floatN<4>(float1(v1), float1(v2), v3, v4) {}
	template<int A, int B> floatN<4>(const component1<A>& v1,	const float1& v2,			const component1<B>& v3,	const float1& v4)			: floatN<4>(float1(v1), v2, float1(v3), v4) {}

	template<int A, int B> floatN<4>(const float1& v1,			const component1<A>& v2,	const component1<B>& v3,	const float1& v4)			: floatN<4>(v1, float1(v2), float1(v3), v4) {}
	template<int A, int B> floatN<4>(const float1& v1,			const float1& v2,			const component1<A>& v3,	const component1<B>& v4)	: floatN<4>(v1, v2, float1(v3), float1(v4)) {}
	template<int A, int B> floatN<4>(const float1& v1,			const component1<A>& v2,	const float1& v3,			const component1<B>& v4)	: floatN<4>(v1, float1(v2), v3, float1(v4)) {}

	template<int A>			floatN<4>(const float2& v1,		const component1<A>& v2,	const float1& v3)			: floatN<4>(v1, float1(v2), v3) {}
	template<int A>			floatN<4>(const float2& v1,		const float1& v2,			const component1<A>& v3)	: floatN<4>(v1, v2, float1(v3)) {}
	template<int A, int B>	floatN<4>(const float2& v1,		const component1<A>& v2,	const component1<B>& v3)	: float4(v1, v2, float1(v3)) {}

	template<int A> floatN<4>(const component1<A>& v1,	const float2& v2,	const float1& v3)			: floatN<4>(float1(v1), v2, v3) {}
	template<int A> floatN<4>(const float1& v1,			const float2& v2,	const component1<A>& v3)	: floatN<4>(v1, v2, float1(v3)) {}

	template<int A>			floatN<4>(const float1& v1,			const component1<A>& v2,	const float2& v3)	: floatN<4>(v1, float1(v2), v3) {}
	template<int A>			floatN<4>(const component1<A>& v1,	const float1& v2,			const float2& v3)	: floatN<4>(float1(v1), v2, v3) {}
	template<int A, int B>	floatN<4>(const component1<A>& v1,	const component1<B>& v2,	const float2& v3)	: floatN<4>(float1(v1), float1(v2), v3) {}

	template<int A> floatN<4>(const component1<A>& v1,	const float3& v2)			: floatN<4>(float1(v1), v2) {}
	template<int A> floatN<4>(const float3& v1,			const component1<A>& v2)	: float4(v1, float1(v2)) {}

	// componentN + float constructors
	template<int A> floatN<4>(const component1<A>& v1,	const float v2,				const float v3,				const float v4)				: floatN<4>(float1(v1), float3(v2, v3, v4)) {}
	template<int A> floatN<4>(const float v1,			const component1<A>& v2,	const float v3,				const float v4)				: floatN<4>(float1(v1), float1(v2), float2(v3, v4)) {}
	template<int A> floatN<4>(const float v1,			const float v2,				const component1<A>& v3,	const float v4)				: floatN<4>(float2(v1, v2), float1(v3), float1(v4)) {}
	template<int A> floatN<4>(const float v1,			const float v2,				const float v3,				const component1<A>& v4)	: floatN<4>(float3(v1, v2, v3), float1(v4)) {}

	template<int A, int B, int C> floatN<4>(const float v1,				const component1<A>& v2,	const component1<B>& v3,	const component1<C>& v4)	: floatN<4>(float1(v1), float1(v2), float1(v3), float1(v4)) {}
	template<int A, int B, int C> floatN<4>(const component1<A>& v1,	const float v2,				const component1<B>& v3,	const component1<C>& v4)	: floatN<4>(float1(v1), float1(v2), float1(v3), float1(v4)) {}
	template<int A, int B, int C> floatN<4>(const component1<A>& v1,	const component1<B>& v2,	const float v3,				const component1<C>& v4)	: floatN<4>(float1(v1), float1(v2), float1(v3), float1(v4)) {}
	template<int A, int B, int C> floatN<4>(const component1<A>& v1,	const component1<B>& v2,	const component1<C>& v3,	const float v4)				: floatN<4>(float1(v1), float1(v2), float1(v3), float1(v4)) {}

	template<int A, int B> floatN<4>(const component1<A>& v1,		const float v2,				const float v3,				const component1<B>& v4)	: floatN<4>(float1(v1), float2(v2, v3), float1(v4)) {}
	template<int A, int B> floatN<4>(const component1<A>& v1,		const component1<B>& v2,	const float v3,				const float v4)				: floatN<4>(float1(v1), float1(v2), float2(v3, v4)) {}
	template<int A, int B> floatN<4>(const component1<A>& v1,		const float v2,				const component1<B>& v3,	const float v4)				: floatN<4>(float1(v1), float1(v2), float1(v3), float1(v4)) {}

	template<int A, int B> floatN<4>(const float v1,				const component1<A>& v2,	const component1<B>& v3,	const float v4)				: floatN<4>(float1(v1), float1(v2), float1(v3), float1(v4)) {}
	template<int A, int B> floatN<4>(const float v1,				const float v2,				const component1<A>& v3,	const component1<B>& v4)	: floatN<4>(float2(v1, v2), float1(v3), float1(v4)) {}
	template<int A, int B> floatN<4>(const float v1,				const component1<A>& v2,	const float v3,				const component1<B>& v4)	: floatN<4>(float1(v1), float1(v2), float1(v3), float1(v4)) {}


	template<int A, int B> floatN<4>(const component2<A, B>& v1,	const float v2,				const float v3)				: floatN<4>(float2(v1), float1(v2), float1(v3)) {}
	template<int A, int B> floatN<4>(const float v1,				const component2<A, B>& v2,	const float v3)				: floatN<4>(float1(v1), float2(v2), float1(v3)) {}
	template<int A, int B> floatN<4>(const float v1,				const float v2,				const component2<A, B>& v3)	: floatN<4>(float1(v1), float1(v2), float2(v3)) {}

	template<int A, int B, int C> floatN<4>(const float v1,				const component2<A, B>& v2,	const component1<C>& v3)	: floatN<4>(float1(v1), float2(v2), float1(v3)) {}
	template<int A, int B, int C> floatN<4>(const float v1,				const component1<A>& v2,	const component2<B, C>& v3)	: floatN<4>(float1(v1), float1(v2), float2(v3)) {}

	template<int A, int B, int C> floatN<4>(const component1<A>& v1,	const component2<B, C>& v2,	const float v3)				: floatN<4>(float1(v1), float2(v2), float1(v3)) {}
	template<int A, int B, int C> floatN<4>(const component1<A>& v1,	const float v2,				const component2<B, C>& v3)	: floatN<4>(float1(v1), float1(v2), float2(v3)) {}

	template<int A, int B, int C> floatN<4>(const component2<A, B>& v1,	const float v2,				const component1<C>& v3)	: floatN<4>(float2(v1), float1(v2), float1(v3)) {}
	template<int A, int B, int C> floatN<4>(const component2<A, B>& v1,	const component1<C>& v2,	const float v3)				: floatN<4>(float2(v1), float1(v2), float1(v3)) {}

	template<int A, int B, int C> floatN<4>(const float v1,				const component3<A, B, C>& v2)	: floatN<4>(float1(v1), float3(v2)) {}
	template<int A, int B, int C> floatN<4>(const component3<A, B, C>& v1,	const float v2)				: floatN<4>(float3(v1), float1(v2)) {}

	// floatN + componentN + float constructors
	template<int A>			floatN<4>(const float v1,	const component1<A>& v2,	const float1& v3,		const float v4)				: floatN<4>(float1(v1), float1(v2), v3, float1(v4)) {}
	template<int A>			floatN<4>(const float v1,	const component1<A>& v2,	const float1& v3,		const float1& v4)			: floatN<4>(float1(v1), float1(v2), v3, v4) {}
	template<int A, int B>	floatN<4>(const float v1,	const component1<A>& v2,	const float1& v3,		const component1<B>& v4)	: floatN<4>(float1(v1), float1(v2), v3, float1(v4)) {}

	template<int A>			floatN<4>(const float v1,	const float1& v2,		const component1<A>& v3,	const float v4)				: floatN<4>(float1(v1), v2, float1(v3), float1(v4)) {}
	template<int A>			floatN<4>(const float v1,	const float1& v2,		const component1<A>& v3,	const float1& v4)			: floatN<4>(float1(v1), v2, float1(v3), v4) {}
	template<int A, int B>	floatN<4>(const float v1,	const float1& v2,		const component1<A>& v3,	const component1<B>& v4)	: floatN<4>(float1(v1), v2, float1(v3), float1(v4)) {}

	template<int A>			floatN<4>(const float v1,	const float v2,			const component1<A>& v3,	const float1& v4)			: floatN<4>(float2(v1, v2), float1(v3), v4) {}
	template<int A>			floatN<4>(const float v1,	const float v2,			const float1& v3,			const component1<A>& v4)	: floatN<4>(float2(v1, v2), v3, float1(v4)) {}

	template<int A, int B>	floatN<4>(const float v1,	const component1<A>& v2,	const float v3,				const float1& v4)		: floatN<4>(float1(v1), float1(v2), float1(v3), v4) {}
	template<int A, int B>	floatN<4>(const float v1,	const component1<A>& v2,	const component1<B>& v3,	const float1& v4)		: floatN<4>(float1(v1), float1(v2), float1(v3), v4) {}

	template<int A>			floatN<4>(const float v1,	const float1& v2,			const float1& v3,			const component1<A>& v4)	: floatN<4>(float1(v1), v2, v3, float1(v4)) {}

	template<int A>			floatN<4>(const component1<A>& v1,	const float v2,	const float1& v3,	const float v4)				: floatN<4>(float1(v1), v2, v3, float1(v4)) {}
	template<int A>			floatN<4>(const component1<A>& v1,	const float v2,	const float1& v3,	const float1& v4)			: floatN<4>(float1(v1), float1(v2), v3, v4) {}
	template<int A, int B>	floatN<4>(const component1<A>& v1,	const float v2,	const float1& v3,	const component1<B>& v4)	: floatN<4>(float1(v1), float1(v2), v3, float1(v4)) {}
	
	template<int A, int B>	floatN<4>(const component1<A>& v1,	const float1& v2,		const float v3,			const float v4)				: floatN<4>(float1(v1), v2, float1(v3), float1(v4)) {}
	template<int A, int B>	floatN<4>(const component1<A>& v1,	const float1& v2,		const float v3,			const float1& v4)			: floatN<4>(float1(v1), v2, float1(v3), v4) {}
	template<int A, int B>	floatN<4>(const component1<A>& v1,	const float1& v2,		const float v3,			const component1<B>& v4)	: floatN<4>(float1(v1), v2, float1(v3), float1(v4)) {}

	template<int A, int B>	floatN<4>(const component1<A>& v1,	const component1<B>& v2,	const float1& v3,	const float v4)			: floatN<4>(float1(v1), float1(v2), v3, float1(v4)) {}
	template<int A, int B>	floatN<4>(const component1<A>& v1,	const component1<B>& v2,	const float v3,		const float1& v4)		: floatN<4>(float1(v1), float1(v2), float1(v3), v4) {}

	template<int A, int B>	floatN<4>(const component1<A>& v1,	const float1& v2,	const component1<B>& v3,	const float v4)		: floatN<4>(float1(v1), v2, float1(v3), float1(v4)) {}
	template<int A>			floatN<4>(const component1<A>& v1,	const float1& v2,	const float v3,				const float1& v4)	: floatN<4>(float1(v1), v2, float1(v3), v4) {}

	template<int A, int B>	floatN<4>(const component1<A>& v1,	const float v2,		const component1<B>& v3,	const float1& v4)	: floatN<4>(float1(v1), float1(v2), float1(v3), v4) {}

	template<int A>			floatN<4>(const float1& v1,	const component1<A>& v2,	const float  v3,			const float v4)				: floatN<4>(v1, float1(v2), float1(v3), float1(v4)) {}
	template<int A>			floatN<4>(const float1& v1,	const component1<A>& v2,	const float v3,				const float1& v4)			: floatN<4>(v1, float1(v2), float1(v3), v4) {}
	template<int A, int B>	floatN<4>(const float1& v1,	const component1<A>& v2,	const float  v3,			const component1<B>& v4)	: floatN<4>(v1, float1(v2), float1(v3), float1(v4)) {}

	template<int A>			floatN<4>(const float1& v1, const float v2,			const component1<A>&  v3,	const float v4)				: floatN<4>(v1, float1(v2), float1(v3), float1(v4)) {}
	template<int A>			floatN<4>(const float1& v1, const float v2,			const component1<A>& v3,	const float1& v4)			: floatN<4>(v1, float1(v2), float1(v3), v4) {}
	template<int A, int B>	floatN<4>(const float1& v1, const float v2,			const component1<A>&  v3,	const component1<B>& v4)	: floatN<4>(v1, float1(v2), float1(v3), float1(v4)) {}

	template<int A>			floatN<4>(const float1& v1, const float1& v2,		const float v3,				const component1<A>& v4)	: floatN<4>(v1, v2, float1(v3), float1(v4)) {}
	template<int A>			floatN<4>(const float1& v1, const float1& v2,		const component1<A>& v3,	const float v4)				: floatN<4>(v1, v2, float1(v3), float1(v4)) {}

	template<int A>			floatN<4>(const float1& v1, const float v2,			const float1& v3,		const component1<A>& v4)	: floatN<4>(v1, float1(v2), v3, float1(v4)) {}
	template<int A>			floatN<4>(const float1& v1, const float v2,			const float  v3,		const component1<A>& v4)	: floatN<4>(v1, float1(v2), float1(v3), float1(v4)) {}

	template<int A>			floatN<4>(const float1& v1, const component1<A>& v2,	const float1& v3,			const float v4)		: floatN<4>(v1, float1(v2), v3, float1(v4)) {}
	template<int A, int B>	floatN<4>(const float1& v1, const component1<A>& v2,	const component1<B>&  v3,	const float v4)		: floatN<4>(v1, float1(v2), float1(v3), float1(v4)) {}

	explicit floatN<4>(const float4x1& v);
	explicit floatN<4>(const float1x4& v);

	floatN<4>& operator = (const float4& c);
	template<int A, int B, int C, int D> floatN<4>& operator = (const component4<A, B, C, D>& c);
};

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
		#include "swizzle/hlsl++_matrix_row0_1.h"
	};

	floatNxM() {}
	explicit floatNxM(n128 vec) : _vec(vec) {}
	explicit floatNxM(float f) : _vec(_hlslpp_set_ps(f, 0.0f, 0.0f, 0.0f)) {}
	floatNxM(const float1& v) : _vec(v._vec) {}
	floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
};

template<>
class floatNxM<1, 2>
{
public:
	union
	{
		n128 _vec;
		#include "swizzle/hlsl++_matrix_row0_2.h"
	};

	floatNxM() {}
	explicit floatNxM(n128 vec) : _vec(vec) {}
	floatNxM(float f0, float f1) : _vec(_hlslpp_set_ps(f0, f1, 0.0f, 0.0f)) {}
	explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
	floatNxM(const float2& v) : _vec(v._vec) {}
	floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
};

template<>
class floatNxM<2, 1>
{
public:
	union
	{
		n128 _vec;
	};

	floatNxM() {}
	explicit floatNxM(n128 vec) : _vec(vec) {}
	floatNxM(float f0, float f1) : _vec(_hlslpp_set_ps(f0, f1, 0.0f, 0.0f)) {}
	explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
	floatNxM(const float2& v) : _vec(v._vec) {}
	floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
};

template<>
class floatNxM<1, 3>
{
public:
	union
	{
		n128 _vec;
	};

	floatNxM() {}
	explicit floatNxM(n128 vec) : _vec(vec) {}
	floatNxM(float f0, float f1, float f2) : _vec(_hlslpp_set_ps(f0, f1, f2, 0.0f)) {}
	explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
	floatNxM(const float3& v) : _vec(v._vec) {}
	floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
};

template<>
class floatNxM<3, 1>
{
public:
	union
	{
		n128 _vec;
	};

	floatNxM() {}
	explicit floatNxM(n128 vec) : _vec(vec) {}
	floatNxM(float f0, float f1, float f2) : _vec(_hlslpp_set_ps(f0, f1, f2, 0.0f)) {}
	explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
	floatNxM(const float3& v) : _vec(v._vec) {}
	floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
};

template<>
class floatNxM<1, 4>
{
public:
	union
	{
		n128 _vec;
	};

	floatNxM() {}
	explicit floatNxM(n128 vec) : _vec(vec) {}
	floatNxM(float f0, float f1, float f2, float f3) : _vec(_hlslpp_set_ps(f0, f1, f2, f3)) {}
	explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
	floatNxM(const float4& v) : _vec(v._vec) {}
	floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
};

template<>
class floatNxM<4, 1>
{
public:
	union
	{
		n128 _vec;
	};

	floatNxM() {}
	explicit floatNxM(n128 vec) : _vec(vec) {}
	floatNxM(float f0, float f1, float f2, float f3) : _vec(_hlslpp_set_ps(f0, f1, f2, f3)) {}
	explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
	floatNxM(const float4& v) : _vec(v._vec) {}
	floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
};

template<>
class floatNxM<2, 2>
{
public:	
	union
	{
		n128 _vec; // We can store it in a single vector to save memory
	};

	floatNxM() {}
	explicit floatNxM(n128 vec) : _vec(vec) {}

	floatNxM(float f00, float f01,
			 float f10, float f11) : _vec(_hlslpp_set_ps(f00, f01, f10, f11)) {}

	explicit floatNxM(float f) : _vec(_hlslpp_set1_ps(f)) {}
	floatNxM(const floatNxM& m) : _vec(m._vec) {}
	floatNxM& operator = (const floatNxM& m) { _vec = m._vec; return *this; }
};

template<>
class floatNxM<2, 3>
{
public:
	union
	{
		n128 _vec0;
	};

	union
	{
		n128 _vec1;
	};

	floatNxM() {}
	explicit floatNxM(n128 vec0, n128 vec1) : _vec0(vec0), _vec1(vec1) {}

	floatNxM(float f00, float f01, float f02,
			 float f10, float f11, float f12) : _vec0(_hlslpp_set_ps(f00, f01, f02, 0.0f)), _vec1(_hlslpp_set_ps(f10, f11, f12, 0.0f)) {}

	explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)) {}
	floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1) {}
	floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; return *this; }
};

template<>
class floatNxM<3, 2>
{
public:
	union
	{
		n128 _vec0;
	};

	union
	{
		n128 _vec1;
	};

	floatNxM() {}
	explicit floatNxM(n128 vec0, n128 vec1) : _vec0(vec0), _vec1(vec1) {}

	floatNxM(float f00, float f01, 
			 float f10, float f11,
			 float f20, float f21) : _vec0(_hlslpp_set_ps(f00, f10, f20, 0.0f)), _vec1(_hlslpp_set_ps(f01, f11, f21, 0.0f)) {}

	explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)) {}
	floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1) {}
	floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; return *this; }
};

template<>
class floatNxM<2, 4>
{
public:
	union
	{
		n128 _vec0;
	};

	union
	{
		n128 _vec1;
	};

	floatNxM() {}
	explicit floatNxM(n128 vec0, n128 vec1) : _vec0(vec0), _vec1(vec1) {}

	floatNxM(float f00, float f01, float f02, float f03,
			 float f10, float f11, float f12, float f13) : _vec0(_hlslpp_set_ps(f00, f01, f02, f03)), _vec1(_hlslpp_set_ps(f10, f11, f12, f13)) {}

	explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)) {}
	floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1) {}
	floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; return *this; }
};

template<>
class floatNxM<4, 2>
{
public:
	union
	{
		n128 _vec0;
	};

	union
	{
		n128 _vec1;
	};

	floatNxM() {}
	explicit floatNxM(n128 vec0, n128 vec1) : _vec0(vec0), _vec1(vec1) {}

	floatNxM(float f00, float f01,
			 float f10, float f11,
			 float f20, float f21, 
			 float f30, float f31) : _vec0(_hlslpp_set_ps(f00, f10, f20, f30)), _vec1(_hlslpp_set_ps(f01, f11, f21, f31)) {}

	explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)) {}
	floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1) {}
	floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; return *this; }
};

template<>
class floatNxM<3, 3>
{
public:
	union
	{
		n128 _vec0;
		#include "swizzle/hlsl++_matrix_row0_1.h"
		#include "swizzle/hlsl++_matrix_row0_2.h"
		#include "swizzle/hlsl++_matrix_row0_3.h"
	};

	union
	{
		n128 _vec1;
		#include "swizzle/hlsl++_matrix_row1_1.h"
		#include "swizzle/hlsl++_matrix_row1_2.h"
		#include "swizzle/hlsl++_matrix_row1_3.h"
	};

	union
	{
		n128 _vec2;
		#include "swizzle/hlsl++_matrix_row2_1.h"
		#include "swizzle/hlsl++_matrix_row2_2.h"
		#include "swizzle/hlsl++_matrix_row2_3.h"
	};

	floatNxM() {}
	explicit floatNxM(const n128 vec0, const n128 vec1, const n128 vec2) : _vec0(vec0), _vec1(vec1), _vec2(vec2) {}

	floatNxM(float f00, float f01, float f02,
			 float f10, float f11, float f12,
			 float f20, float f21, float f22) : _vec0(_hlslpp_set_ps(f00, f01, f02, 0.0f)), _vec1(_hlslpp_set_ps(f10, f11, f12, 0.0f)), _vec2(_hlslpp_set_ps(f20, f21, f22, 0.0f)) {}

	explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)), _vec2(_hlslpp_set1_ps(f)) {}
	floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1), _vec2(m._vec2) {}
	floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; _vec2 = m._vec2; return *this; }

	static const float3x3& identity() { static const float3x3 iden = float3x3(1, 0, 0, 0, 1, 0, 0, 0, 1); return iden; };
};

template<>
class floatNxM<3, 4>
{
public:
	union
	{
		n128 _vec0;
	};

	union
	{
		n128 _vec1;
	};

	union
	{
		n128 _vec2;
	};

	floatNxM() {}
	explicit floatNxM(n128 vec0, n128 vec1, n128 vec2) : _vec0(vec0), _vec1(vec1), _vec2(vec2) {}

	floatNxM(float f00, float f01, float f02, float f03,
			 float f10, float f11, float f12, float f13,
			 float f20, float f21, float f22, float f23) : _vec0(_hlslpp_set_ps(f00, f01, f02, f03)), _vec1(_hlslpp_set_ps(f10, f11, f12, f13)), _vec2(_hlslpp_set_ps(f20, f21, f22, f23)) {}

	explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)), _vec2(_hlslpp_set1_ps(f)) {}
	floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1), _vec2(m._vec2) {}
	floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; _vec2 = m._vec2; return *this; }
};

template<>
class floatNxM<4, 3>
{
public:
	union
	{
		n128 _vec0;
	};

	union
	{
		n128 _vec1;
	};

	union
	{
		n128 _vec2;
	};

	floatNxM() {}
	explicit floatNxM(n128 vec0, n128 vec1, n128 vec2) : _vec0(vec0), _vec1(vec1), _vec2(vec2) {}

	floatNxM(float f00, float f01, float f02,
			 float f10, float f11, float f12,
			 float f20, float f21, float f22,
			 float f30, float f31, float f32): _vec0(_hlslpp_set_ps(f00, f10, f20, f30)), _vec1(_hlslpp_set_ps(f01, f11, f21, f31)), _vec2(_hlslpp_set_ps(f02, f12, f22, f32)) {}

	explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)), _vec2(_hlslpp_set1_ps(f)) {}
	floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1), _vec2(m._vec2) {}
	floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; _vec2 = m._vec2; return *this; }
};

template<>
class floatNxM<4, 4>
{
public:
	union
	{
		n128 _vec0;
		#include "swizzle/hlsl++_matrix_row0_1.h"
		#include "swizzle/hlsl++_matrix_row0_2.h"
		#include "swizzle/hlsl++_matrix_row0_3.h"
		#include "swizzle/hlsl++_matrix_row0_4.h"
	};

	union
	{
		n128 _vec1;
		#include "swizzle/hlsl++_matrix_row1_1.h"
		#include "swizzle/hlsl++_matrix_row1_2.h"
		#include "swizzle/hlsl++_matrix_row1_3.h"
		#include "swizzle/hlsl++_matrix_row1_4.h"
	};

	union
	{
		n128 _vec2;
		#include "swizzle/hlsl++_matrix_row2_1.h"
		#include "swizzle/hlsl++_matrix_row2_2.h"
		#include "swizzle/hlsl++_matrix_row2_3.h"
		#include "swizzle/hlsl++_matrix_row2_4.h"
	};

	union
	{
		n128 _vec3;
		#include "swizzle/hlsl++_matrix_row3_1.h"
		#include "swizzle/hlsl++_matrix_row3_2.h"
		#include "swizzle/hlsl++_matrix_row3_3.h"
		#include "swizzle/hlsl++_matrix_row3_4.h"
	};

	floatNxM() {}
	explicit floatNxM(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3) : _vec0(vec0), _vec1(vec1), _vec2(vec2), _vec3(vec3) {}


	floatNxM(float f00, float f01, float f02, float f03,
			 float f10, float f11, float f12, float f13,
			 float f20, float f21, float f22, float f23,
			 float f30, float f31, float f32, float f33)
		: _vec0(_hlslpp_set_ps(f03, f02, f01, f00)), _vec1(_hlslpp_set_ps(f10, f11, f12, f13)), _vec2(_hlslpp_set_ps(f20, f21, f22, f23)), _vec3(_hlslpp_set_ps(f30, f31, f32, f33)) {}

	explicit floatNxM(float f) : _vec0(_hlslpp_set1_ps(f)), _vec1(_hlslpp_set1_ps(f)), _vec2(_hlslpp_set1_ps(f)), _vec3(_hlslpp_set1_ps(f)) {}
	floatNxM(const floatNxM& m) : _vec0(m._vec0), _vec1(m._vec1), _vec2(m._vec2), _vec3(m._vec3) {}
	floatNxM& operator = (const floatNxM& m) { _vec0 = m._vec0; _vec1 = m._vec1; _vec2 = m._vec2; _vec3 = m._vec3; return *this; }
	static const float4x4& identity() { static const float4x4 iden = float4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); return iden; };
};

//--------------------
// Component functions
//--------------------

template<int A>
template<int E>
inline component1<A>& component1<A>::operator = (const component1<E>& p)
{
	n128 s = _hlslpp_shuffle_ps(p._vec, p._vec, HLSLPP_SHUFFLE_MASK(E, E, E, E));
	_vec = _hlslpp_blend_ps(_vec, s, HLSLPP_COMPONENT_X(A));
	return *this;
}

template<int A>
inline component1<A>& component1<A>::operator = (float f)
{
	const n128 s = _hlslpp_set1_ps(f);
	_vec = _hlslpp_blend_ps(_vec, s, HLSLPP_COMPONENT_X(A));
	return *this;
}

template<int A>
inline component1<A>& component1<A>::operator = (const float1& v)
{
	_vec = _hlslpp_blend_ps(_vec, v._vec, HLSLPP_COMPONENT_X(A));
	return *this;
}

template<int A>
inline component1<A>& component1<A>::operator = (const float1x1& m)
{
	_vec = _hlslpp_blend_ps(_vec, m._vec, HLSLPP_COMPONENT_X(A));
	return *this;
}

template<int A, int B>
template<int E, int F>
inline component2<A, B>& component2<A, B>::operator = (const component2<E, F>& c)
{
	staticAsserts();
	_vec = blend(_vec, swizzle<E, F, A, B>(c._vec));
	return *this;
}

template<int A, int B>
inline component2<A, B>& component2<A, B>::operator = (const component2<A, B>& c)
{
	_vec = _hlslpp_blend_ps(_vec, c._vec, HLSLPP_BLEND_MASK(0, 0, 1, 1));
	return *this;
}

template<int A, int B>
inline component2<A, B>& component2<A, B>::operator = (const float2& v)
{
	staticAsserts();
	_vec = blend(_vec, swizzle<0, 1, A, B>(v._vec));
	return *this;
}

template<int A, int B, int C>
template<int E, int F, int G>
inline component3<A, B, C>& component3<A, B, C>::operator = (const component3<E, F, G>& c)
{
	staticAsserts();
	_vec = blend(_vec, swizzle<E, F, G, A, B, C>(c._vec));
	return *this;
}

template<int A, int B, int C>
inline component3<A, B, C>& component3<A, B, C>::operator = (const component3<A, B, C>& c)
{
	_vec = _hlslpp_blend_ps(_vec, c._vec, HLSLPP_BLEND_MASK(0, 0, 0, 1));
	return *this;
}

template<int A, int B, int C>
inline component3<A, B, C>& component3<A, B, C>::operator = (const float3& v)
{
	staticAsserts();
	_vec = blend(_vec, swizzle<0, 1, 2, A, B, C>(v._vec));
	return *this;
}

template<int A, int B, int C, int D>
template<int E, int F, int G, int H>
inline component4<A, B, C, D>& component4<A, B, C, D>::operator = (const component4<E, F, G, H>& c)
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
inline component4<A, B, C, D>& component4<A, B, C, D>::operator = (const component4<A, B, C, D>& c)
{
	_vec = c._vec;
	return *this;
}

template<int A, int B, int C, int D>
inline component4<A, B, C, D>& component4<A, B, C, D>::operator = (const float4& v)
{
	staticAsserts();
	_vec = _hlslpp_shuffle_ps(v._vec, v._vec, HLSLPP_SHUFFLE_MASK(A, B, C, D));
	return *this;
}

// Optimize a straight copy via explicit instantiation (doesn't produce/need the shuffle)
template<>
inline component4<0, 1, 2, 3>& component4<0, 1, 2, 3>::operator = (const float4& v)
{
	_vec = v._vec;
	return *this;
}

//-----------------
// Vector functions
//-----------------

template<int A>
inline float1::floatN(const component1<A>& c)
{
	_vec = _hlslpp_shuffle_ps(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(A, A, A, A));
}

template<>
inline float1::floatN(const component1<0>& c)
{
	_vec = c._vec;
}

inline float1::floatN(const float1x1& v)
{
	_vec = v._vec;
}

inline float1& float1::operator = (const float1& v)
{
	_vec = v._vec;
	return *this;
}

inline float1& float1::operator = (float f)
{
	_vec = _hlslpp_set_ps(f, 0.0f, 0.0f, 0.0f);
	return *this;
}

template<int A>
inline float1& float1::operator = (const component1<A>& c)
{
	_vec = _hlslpp_shuffle_ps(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(A, A, A, A));
	return *this;
}

template<>
inline float1& float1::operator = (const component1<0>& c)
{
	_vec = c._vec; return *this;
}

inline float1& float1::operator = (const float1x1& m)
{
	_vec = m._vec; return *this;
}

inline float2::floatN(const float1& v1, const float1& v2)
{
	_vec = _hlslpp_blend_ps(v1._vec, _hlslpp_perm_xxxx_ps(v2._vec), HLSLPP_BLEND_MASK(1, 0, 1, 1));
}

template<int A, int B>
inline float2::floatN(const component2<A, B>& c)
{
	_vec = component2<A, B>::template swizzle<A, B, 0, 1>(c._vec);
}

template<>
inline float2::floatN(const component2<0, 1>& c)
{
	_vec = c._vec;
}

inline float2::floatN(const float2x1& v)
{
	_vec = v._vec;
}

inline float2::floatN(const float1x2& v)
{
	_vec = v._vec;
}

inline float2& float2::operator = (const float2& v)
{
	_vec = v._vec; return *this;
}

template<int A, int B>
inline float2& float2::operator = (const component2<A, B>& c)
{
	_vec = component2<A, B>::template swizzle<A, B, 0, 1>(c._vec);
	return *this;
}

template<>
inline float2& float2::operator = (const component2<0, 1>& c)
{
	_vec = c._vec; return *this;
}

template<int A, int B, int C>
inline float3::floatN(const component3<A, B, C>& c)
{
	_vec = component3<A, B, C>::template swizzle<A, B, C, 0, 1, 2>(c._vec);
}

template<>
inline float3::floatN(const component3<0, 1, 2>& c)
{
	_vec = c._vec;
}

inline float3::floatN(const floatN<1>& v1, const floatN<1>& v2, const floatN<1>& v3)
{
	_vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(v1._vec, v3._vec), _hlslpp_perm_xxxx_ps(v2._vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); // 0010
}

inline float3::floatN(const float v1,		const floatN<1>& v2,	const floatN<1>& v3)	: float3(float1(v1), v2, v3) {}
inline float3::floatN(const floatN<1>& v1,	const float v2,			const floatN<1>& v3)	: float3(v1, float1(v2), v3) {}
inline float3::floatN(const floatN<1>& v1,	const floatN<1>& v2,	const float v3)			: float3(v1, v2, float1(v3)) {}
inline float3::floatN(const float v1,		const float v2,			const floatN<1>& v3)	: float3(float2(v1, v2), v3) {}
inline float3::floatN(const floatN<1>& v1,	const float v2,			const float v3)			: float3(v1, float2(v2, v3)) {}
inline float3::floatN(const float v1,		const floatN<1>& v2,	const float v3)			: float3(float1(v1), v2, float1(v3)) {}

inline float3::floatN(const floatN<2>& v1, const floatN<1>& v2)
{
	_vec = _hlslpp_shuf_xyxx_ps(v1._vec, v2._vec);
}

inline float3::floatN(const floatN<1>& v1, const floatN<2>& v2)
{
	_vec = _hlslpp_blend_ps(v1._vec, _hlslpp_perm_xxyx_ps(v2._vec), HLSLPP_BLEND_MASK(1, 0, 0, 1));
}

inline float3::floatN(const float3x1& v)
{
	_vec = v._vec;
}

inline float3::floatN(const float1x3& v)
{
	_vec = v._vec;
}

inline float3& float3::operator = (const float3& v)
{
	_vec = v._vec; return *this;
}

template<int A, int B, int C>
inline float3& float3::operator = (const component3<A, B, C>& c)
{
	_vec = component3<A, B, C>::template swizzle<A, B, C, 0, 1, 2>(c._vec);
	return *this;
}

template<>
inline float3& float3::operator = (const component3<0, 1, 1>& c)
{
	_vec = c._vec; return *this;
}

inline float4::floatN(const float1& v1, const float1& v2, const float1& v3, const float1& v4)
{
	_vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(v1._vec, v3._vec), _hlslpp_shuf_xxxx_ps(v2._vec, v4._vec), HLSLPP_BLEND_MASK(1, 0, 1, 0));
}

inline float4::floatN(const float1& v1, const float3& v2)
{
	_vec = _hlslpp_blend_ps(v1._vec, _hlslpp_perm_xxyz_ps(v2._vec), HLSLPP_BLEND_MASK(1, 0, 0, 0));
}

inline float4::floatN(const float3& v1, const float1& v2)
{
	_vec = _hlslpp_blend_ps(v1._vec, _hlslpp_perm_xxxx_ps(v2._vec), HLSLPP_BLEND_MASK(1, 1, 1, 0));
}

inline float4::floatN(const float2& v1, const float2& v2)
{
	_vec = _hlslpp_shuf_xyxy_ps(v1._vec, v2._vec);
}

inline float4::floatN(const float2& v1, const float1& v2, const float1& v3)
{
	_vec = _hlslpp_blend_ps(_hlslpp_shuf_xyxx_ps(v1._vec, v2._vec), _hlslpp_perm_xxxx_ps(v3._vec), HLSLPP_BLEND_MASK(1, 1, 1, 0));
}

inline float4::floatN(const float1& v1, const float2& v2, const float1& v3)
{
	_vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(v1._vec, v3._vec), _hlslpp_perm_xxyx_ps(v2._vec), HLSLPP_BLEND_MASK(1, 0, 0, 1));
}

inline float4::floatN(const float1& v1, const float1& v2, const float2& v3)
{
	_vec = _hlslpp_blend_ps(_hlslpp_shuf_xxxy_ps(v1._vec, v3._vec), _hlslpp_perm_xxxx_ps(v2._vec), HLSLPP_BLEND_MASK(1, 0, 1, 1));
}

inline float4::floatN(const float v1, const float v2, const float1& v3, const float1& v4)
{
	_vec = _hlslpp_blend_ps(_hlslpp_set_ps(v1, v2, 0.0f, 0.0f), _hlslpp_shuf_xxxx_ps(v3._vec, v4._vec), HLSLPP_BLEND_MASK(1, 1, 0, 0));
}

inline float4::floatN(const float v1, const float1& v2, const float v3, const float1& v4)
{
	_vec = _hlslpp_blend_ps(_hlslpp_set_ps(v1, 0.0f, v3, 0.0f), _hlslpp_shuf_xxxx_ps(v2._vec, v4._vec), HLSLPP_BLEND_MASK(1, 0, 1, 0));
}

inline float4::floatN(const float v1, const float1& v2, const float1& v3, const float v4)
{
	_vec = _hlslpp_blend_ps(_hlslpp_set_ps(v1, 0.0f, 0.0f, v4), _hlslpp_shuf_xxxx_ps(v2._vec, v3._vec), HLSLPP_BLEND_MASK(1, 0, 0, 1));
}

inline float4::floatN(const float1& v1, const float v2, const float v3, const float1& v4)
{
	_vec = _hlslpp_blend_ps(_hlslpp_set_ps(0.0f, v2, v3, 0.0f), _hlslpp_shuf_xxxx_ps(v1._vec, v4._vec), HLSLPP_BLEND_MASK(0, 1, 1, 0));
}

inline float4::floatN(const float1& v1, const float v2, const float1& v3, const float v4)
{
	_vec = _hlslpp_blend_ps(_hlslpp_set_ps(0.0f, v2, 0.0, v4), _hlslpp_shuf_xxxx_ps(v1._vec, v3._vec), HLSLPP_BLEND_MASK(0, 1, 0, 1));
}

inline float4::floatN(const float1& v1, const float1& v2, const float v3, const float v4)
{
	_vec = _hlslpp_blend_ps(_hlslpp_set_ps(0.0f, 0.0f, v3, v4), _hlslpp_shuf_xxxx_ps(v1._vec, v2._vec), HLSLPP_BLEND_MASK(0, 0, 1, 1));
}

inline float4::floatN(const float v1, const float v2, const float v3, const float1& v4)
{
	_vec = _hlslpp_blend_ps(_hlslpp_set_ps(v1, v2, v3, 0.0f), _hlslpp_shuf_xxxx_ps(v4._vec, v4._vec), HLSLPP_BLEND_MASK(1, 1, 1, 0));
}

inline float4::floatN(const float v1, const float v2, const float1& v3, const float v4)
{
	_vec = _hlslpp_blend_ps(_hlslpp_set_ps(v1, v2, 0.0f, v4), _hlslpp_shuf_xxxx_ps(v3._vec, v3._vec), HLSLPP_BLEND_MASK(1, 1, 0, 1));
}

inline float4::floatN(const float v1, const float1& v2, const float v3, const float v4)
{
	_vec = _hlslpp_blend_ps(_hlslpp_set_ps(v1, 0.0f, v3, v4), _hlslpp_shuf_xxxx_ps(v2._vec, v2._vec), HLSLPP_BLEND_MASK(1, 0, 1, 1));
}

inline float4::floatN(const float1& v1, const float v2, const float v3, const float v4)
{
	_vec = _hlslpp_blend_ps(_hlslpp_set_ps(0.0f, v2, v3, v4), v1._vec, HLSLPP_BLEND_MASK(0, 1, 1, 1));
}

template<int A, int B, int C, int D>
inline float4::floatN(const component4<A, B, C, D>& c) { *this = c; }

template<> inline float4::floatN(const component4<0, 1, 2, 3>& c) { _vec = c._vec; } // Optimize a straight copy if the indices match 0, 1, 2, 3 (doesn't produce/need the shuffle)

inline float4::floatN(const float4x1& v) { _vec = v._vec; }

inline float4::floatN(const float1x4& v) { _vec = v._vec; }

inline float4& float4::operator = (const float4& v) { _vec = v._vec; return *this; }

template<int A, int B, int C, int D>
inline float4& float4::operator = (const component4<A, B, C, D>& c)
{
	_vec = _hlslpp_shuffle_ps(c._vec, c._vec, HLSLPP_SHUFFLE_MASK(A, B, C, D));
	return *this;
}

template<> inline float4& float4::operator = (const component4<0, 1, 2, 3>& c) { _vec = c._vec; return *this; } // Optimize a straight copy if the indices match 0, 1, 2, 3 (doesn't produce/need the shuffle)

// Addition
template<int N> inline floatN<N> operator + (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_add_ps(v1._vec, v2._vec)); }

template<int N> inline floatN<N> operator + (const floatN<N>& v1, const float v2) { return v1 + floatN<N>(v2); }
template<int N> inline floatN<N> operator + (const float v1, const floatN<N>& v2) { return floatN<N>(v1) + v2; }

template<int N,	template<int...Dim> class components, int...Dim>
inline floatN<N> operator + (const floatN<N>& v1, const components<Dim...>& v2) { return v1 + floatN<N>(v2); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator + (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) + v2; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> operator + (const components<Dim1...>& v1, const components<Dim2...>& v2) 
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return floatN<sizeof...(Dim1)>(v1) + floatN<sizeof...(Dim1)>(v2);
}

template<int N> inline floatN<N> operator + (const floatN<N>& v1, const float1& v2) { return v1 + floatN<N>(_hlslpp_perm_xxxx_ps(v2._vec)); }
inline float1 operator + (const float1& v1, const float1& v2) { return float1(_hlslpp_add_ps(v1._vec, v2._vec)); } // A bit more optimal as it avoids the shuffle

// Plus equals
template<int N> inline floatN<N>& operator += (floatN<N>& v1, const floatN<N>& v2) { v1 = v1 + v2; return v1; }

template<int N> inline floatN<N>& operator += (floatN<N>& v1, const float v2) { v1 = v1 + floatN<N>(v2); return v1; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N>& operator += (floatN<N>& v1, const components<Dim...>& v2) { v1 = v1 + floatN<N>(v2); return v1; }

template<int N, template<int...Dim> class components, int...Dim>
inline components<Dim...>& operator += (components<Dim...>& v1, const floatN<N>& v2) { v1 = floatN<N>(v1) + v2; return v1; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline components<Dim1...>& operator += (components<Dim1...>& v1, const components<Dim2...>& v2) 
{ 
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	v1 = floatN<sizeof...(Dim1)>(v1) + floatN<sizeof...(Dim1)>(v2); return v1;
}

template<int N> inline floatN<N>& operator += (floatN<N>& v1, const float1& v2) { v1 = v1 + v2; return v1; }
inline float1& operator += (float1& v1, const float1& v2) { v1 = v1 + v2; return v1; }

// Subtraction
template<int N> inline floatN<N> operator - (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_sub_ps(v1._vec, v2._vec)); }

template<int N> inline floatN<N> operator - (const floatN<N>& v1, const float v2) { return v1 - floatN<N>(v2); }
template<int N> inline floatN<N> operator - (const float v1, const floatN<N>& v2) { return floatN<N>(v1) - v2; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator - (const floatN<N>& v1, const components<Dim...>& v2) { return v1 - floatN<N>(v2); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator - (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) - v2; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> operator - (const components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return floatN<sizeof...(Dim1)>(v1) - floatN<sizeof...(Dim1)>(v2);
}

template<int N>
inline floatN<N> operator - (const floatN<N>& v1, const float1& v2) { return v1 - floatN<N>(_hlslpp_perm_xxxx_ps(v2._vec)); }
inline float1 operator - (const float1& v1, const float1& v2) { return float1(_hlslpp_sub_ps(v1._vec, v2._vec)); } // A bit more optimal as it avoids the shuffle

// Minus equals
template<int N> inline floatN<N>& operator -= (floatN<N>& v1, const floatN<N>& v2) { v1 = v1 - v2; return v1; }

template<int N> inline floatN<N>& operator -= (floatN<N>& v1, const float v2) { v1 = v1 - floatN<N>(v2); return v1; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N>& operator -= (floatN<N>& v1, const components<Dim...>& v2) { v1 = v1 - floatN<N>(v2); return v1; }

template<int N, template<int...Dim> class components, int...Dim>
inline components<Dim...>& operator -= (components<Dim...>& v1, const floatN<N>& v2) { v1 = floatN<N>(v1) - v2; return v1; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline components<Dim1...>& operator -= (components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	v1 = floatN<sizeof...(Dim1)>(v1) - floatN<sizeof...(Dim1)>(v2); return v1;
}

template<int N> inline floatN<N>& operator -= (floatN<N>& v1, const float1& v2) { v1 = v1 - v2; return v1; }
inline float1& operator -= (float1& v1, const float1& v2) { v1 = v1 - v2; return v1; }

// Multiplication
template<int N> inline floatN<N> operator * (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_mul_ps(v1._vec, v2._vec)); }

template<int N> inline floatN<N> operator * (const floatN<N>& v1, const float v2) { return v1 * floatN<N>(v2); }
template<int N> inline floatN<N> operator * (const float v1, const floatN<N>& v2) { return floatN<N>(v1) * v2; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator * (const floatN<N>& v1, const components<Dim...>& v2) { return v1 * floatN<N>(v2); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator * (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) * v2; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> operator * (const components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return floatN<sizeof...(Dim1)>(v1) * floatN<sizeof...(Dim1)>(v2);
}

template<int N> inline floatN<N> operator * (const floatN<N>& v1, const float1& v2) { return v1 * floatN<N>(_hlslpp_perm_xxxx_ps(v2._vec)); }
inline float1 operator * (const float1& v1, const float1& v2) { return float1(_hlslpp_mul_ps(v1._vec, v2._vec)); } // A bit more optimal as it avoids the shuffle

// Times equals
template<int N> inline floatN<N>& operator *= (floatN<N>& v1, const floatN<N>& v2) { v1 = v1 * v2; return v1; }

template<int N> inline floatN<N>& operator *= (floatN<N>& v1, const float v2) { v1 = v1 * floatN<N>(v2); return v1; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N>& operator *= (floatN<N>& v1, const components<Dim...>& v2) { v1 = v1 * floatN<N>(v2); return v1; }

template<int N, template<int...Dim> class components, int...Dim>
inline components<Dim...>& operator *= (components<Dim...>& v1, const floatN<N>& v2) { v1 = floatN<N>(v1) * v2; return v1; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline components<Dim1...>& operator *= (components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	v1 = floatN<sizeof...(Dim1)>(v1) * floatN<sizeof...(Dim1)>(v2); return v1;
}

template<int N>
inline floatN<N>& operator *= (floatN<N>& v1, const float1& v2) { v1 = v1 * v2; return v1; }
inline float1& operator *= (float1& v1, const float1& v2) { v1 = v1 * v2; return v1; }

// Division
template<int N> inline floatN<N> operator / (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_div_ps(v1._vec, v2._vec)); }

template<int N> inline floatN<N> operator / (const floatN<N>& v1, const float v2) { return v1 / floatN<N>(v2); }
template<int N> inline floatN<N> operator / (const float v1, const floatN<N>& v2) { return floatN<N>(v1) / v2; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator / (const floatN<N>& v1, const components<Dim...>& v2) { return v1 / floatN<N>(v2); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator / (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) / v2; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> operator / (const components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return floatN<sizeof...(Dim1)>(v1) / floatN<sizeof...(Dim1)>(v2);
}

template<int N> inline floatN<N> operator / (const floatN<N>& v1, const float1& v2) { return v1 / floatN<N>(_hlslpp_perm_xxxx_ps(v2._vec)); }
inline float1 operator / (const float1& v1, const float1& v2) { return float1(_hlslpp_div_ps(v1._vec, v2._vec)); } // A bit more optimal as it avoids the shuffle

// Divide equals
template<int N> inline floatN<N>& operator /= (floatN<N>& v1, const floatN<N>& v2) { v1 = v1 / v2; return v1; }

template<int N> inline floatN<N>& operator /= (floatN<N>& v1, const float v2) { v1 = v1 / floatN<N>(v2); return v1; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N>& operator /= (floatN<N>& v1, const components<Dim...>& v2) { v1 = v1 / floatN<N>(v2); return v1; }

template<int N, template<int...Dim> class components, int...Dim>
inline components<Dim...>& operator /= (components<Dim...>& v1, const floatN<N>& v2) { v1 = floatN<N>(v1) / v2; return v1; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline components<Dim1...>& operator /= (components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	v1 = floatN<sizeof...(Dim1)>(v1) / floatN<sizeof...(Dim1)>(v2); return v1;
}

template<int N> inline floatN<N>& operator /= (floatN<N>& v1, const float1& v2) { v1 = v1 / v2; return v1; }
inline float1& operator /= (float1& v1, const float1& v2) { v1 = v1 / v2; return v1; }

// Negation
template<int N> inline floatN<N> operator - (const floatN<N>& v) { return floatN<N>(_hlslpp_neg_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim1>
inline floatN<sizeof...(Dim1)> operator - (const components<Dim1...>& v) { return -floatN<sizeof...(Dim1)>(v); }

// Equals
template<int N> inline floatN<N> operator == (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_cmpeq1_ps(v1._vec, v2._vec)); }

template<int N> inline floatN<N> operator == (const floatN<N>& v1, const float v2) { return v1 == floatN<N>(v2); }
template<int N> inline floatN<N> operator == (const float v1, const floatN<N>& v2) { return floatN<N>(v1) == v2; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator == (const floatN<N>& v1, const components<Dim...>& v2) { return v1 == floatN<N>(v2); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator == (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) == v2; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> operator == (const components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return floatN<sizeof...(Dim1)>(v1) == floatN<sizeof...(Dim1)>(v2);
}

// Not equals
template<int N> inline floatN<N> operator != (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_cmpneq1_ps(v1._vec, v2._vec)); }

template<int N> inline floatN<N> operator != (const floatN<N>& v1, const float v2) { return v1 != floatN<N>(v2); }
template<int N> inline floatN<N> operator != (const float v1, const floatN<N>& v2) { return floatN<N>(v1) != v2; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator != (const floatN<N>& v1, const components<Dim...>& v2) { return v1 != floatN<N>(v2); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator != (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) != v2; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> operator != (const components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return floatN<sizeof...(Dim1)>(v1) != floatN<sizeof...(Dim1)>(v2);
}

// Greater than
template<int N> inline floatN<N> operator > (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_cmpgt1_ps(v1._vec, v2._vec)); }

template<int N> inline floatN<N> operator > (const floatN<N>& v1, const float v2) { return v1 > floatN<N>(v2); }
template<int N> inline floatN<N> operator > (const float v1, const floatN<N>& v2) { return floatN<N>(v1) > v2; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator > (const floatN<N>& v1, const components<Dim...>& v2) { return v1 > floatN<N>(v2); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator > (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) > v2; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> operator > (const components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return floatN<sizeof...(Dim1)>(v1) > floatN<sizeof...(Dim1)>(v2);
}

// Greater equals
template<int N> inline floatN<N> operator >= (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_cmpge1_ps(v1._vec, v2._vec)); }

template<int N> inline floatN<N> operator >= (const floatN<N>& v1, const float v2) { return v1 >= floatN<N>(v2); }
template<int N> inline floatN<N> operator >= (const float v1, const floatN<N>& v2) { return floatN<N>(v1) >= v2; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator >= (const floatN<N>& v1, const components<Dim...>& v2) { return v1 >= floatN<N>(v2); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator >= (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) >= v2; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> operator >= (const components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return floatN<sizeof...(Dim1)>(v1) >= floatN<sizeof...(Dim1)>(v2);
}

// Less than
template<int N> inline floatN<N> operator < (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_cmplt1_ps(v1._vec, v2._vec)); }

template<int N> inline floatN<N> operator < (const floatN<N>& v1, const float v2) { return v1 < floatN<N>(v2); }
template<int N> inline floatN<N> operator < (const float v1, const floatN<N>& v2) { return floatN<N>(v1) < v2; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator < (const floatN<N>& v1, const components<Dim...>& v2) { return v1 < floatN<N>(v2); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator < (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) < v2; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> operator < (const components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return floatN<sizeof...(Dim1)>(v1) < floatN<sizeof...(Dim1)>(v2);
}

// Less equals
template<int N> inline floatN<N> operator <= (const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_cmple1_ps(v1._vec, v2._vec)); }

template<int N> inline floatN<N> operator <= (const floatN<N>& v1, const float v2) { return v1 <= floatN<N>(v2); }
template<int N> inline floatN<N> operator <= (const float v1, const floatN<N>& v2) { return floatN<N>(v1) <= v2; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator <= (const floatN<N>& v1, const components<Dim...>& v2) { return v1 <= floatN<N>(v2); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> operator <= (const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) <= v2; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> operator <= (const components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return floatN<sizeof...(Dim1)>(v1) <= floatN<sizeof...(Dim1)>(v2);
}

template<int N> inline floatN<N> abs(const floatN<N>& v) { return floatN<N>(_hlslpp_abs_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> abs(const components<Dim...>& v) { return abs(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> acos(const floatN<N>& v) { return floatN<N>(_hlslpp_acos_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> acos(const components<Dim...>& v) { return acos(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> all(const floatN<N>& v) { return floatN<N>(_hlslpp_all1_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> all(const components<Dim...>& v) { return all(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> any(const floatN<N>& v) { return floatN<N>(_hlslpp_any1_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> any(const components<Dim...>& v) { return any(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> asin(const floatN<N>& v) { return floatN<N>(_hlslpp_asin_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> asin(const components<Dim...>& v) { return asin(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> atan(const floatN<N>& v) { return floatN<N>(_hlslpp_atan_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> atan(const components<Dim...>& v) { return atan(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> ceil(const floatN<N>& v) { return floatN<N>(_hlslpp_ceil_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> ceil(const components<Dim...>& v) { return ceil(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> clamp(const floatN<N>& v, const floatN<N>& minv, const floatN<N>& maxv) { return floatN<N>(_hlslpp_clamp_ps(v._vec, minv._vec, maxv._vec)); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> clamp(const floatN<N>& v1, const floatN<N>& v2, const components<Dim...>& a) { return clamp(v1, v2, floatN<N>(a)); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> clamp(const floatN<N>& v1, const components<Dim...>& v2, const floatN<N>& a) { return clamp(v1, floatN<N>(v2), a); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> clamp(const components<Dim...>& v1, const floatN<N>& v2, const floatN<N>& a) { return clamp(floatN<N>(v1), v2, a); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> clamp(const floatN<N>& v1, const components<Dim...>& v2, const components<Dim...>& a) { return clamp(v1, floatN<N>(v2), floatN<N>(a)); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> clamp(const components<Dim...>& v1, const floatN<N>& v2, const components<Dim...>& a) { return clamp(floatN<N>(v1), v2, floatN<N>(a)); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> clamp(const components<Dim...>& v1, const components<Dim...>& v2, const floatN<N>& a) { return clamp(floatN<N>(v1), floatN<N>(v2), a); }

template<template<int...Dim> class components, int...Dim1, int...Dim2, int...Dim3>
inline floatN<sizeof...(Dim1)> clamp(const components<Dim1...>& v1, const components<Dim2...>& v2, const components<Dim3...>& a)
{
	static_assert((sizeof...(Dim1) == sizeof...(Dim2)) && (sizeof...(Dim2) == sizeof...(Dim3)), "Vectors must be the same dimension!");
	return clamp(floatN<sizeof...(Dim1)>(v1), floatN<sizeof...(Dim1)>(v2), floatN<sizeof...(Dim1)>(a));
}

template<int N> inline floatN<N> cos(const floatN<N>& v) { return floatN<N>(_hlslpp_cos_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> cos(const components<Dim...>& v) { return cos(floatN<sizeof...(Dim)>(v)); }

inline float3 cross(const float3& v1, const float3& v2) { return float3(_hlslpp_cross_ps(v1._vec, v2._vec)); }

template<int N> inline floatN<N> degrees(const floatN<N>& v) { return floatN<N>(_hlslpp_mul_ps(v._vec, f4_rad2deg)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> degrees(const components<Dim...>& v) { return degrees(floatN<sizeof...(Dim)>(v)); }

inline float1 dot(const float4& v1, const float4& v2) { return float1(_hlslpp_dot4_ps(v1._vec, v2._vec)); }

inline float1 dot(const float3& v1, const float3& v2) { return float1(_hlslpp_dot3_ps(v1._vec, v2._vec)); }

inline float1 dot(const float2& v1, const float2& v2) { return float1(_hlslpp_dot2_ps(v1._vec, v2._vec)); }

template<int N> inline floatN<N> exp(const floatN<N>& v) { return floatN<N>(_hlslpp_exp_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> exp(const components<Dim...>& v) { return exp(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> exp2(const floatN<N>& v) { return floatN<N>(_hlslpp_exp2_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> exp2(const components<Dim...>& v) { return exp2(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> floor(const floatN<N>& v) { return floatN<N>(_hlslpp_floor_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> floor(const components<Dim...>& v) { return floor(floatN<sizeof...(Dim)>(v)); }

// A note on negative numbers. Contrary to intuition, frac(-0.75) != 0.75,
// but is actually frac(-0.75) == 0.25 This is because hlsl defines frac
// as frac(x) = x - floor(x)
template<int N> inline floatN<N> frac(const floatN<N>& v) { return floatN<N>(_hlslpp_frac_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> frac(const components<Dim...>& v) { return frac(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> isfinite(const floatN<N>& v) { return floatN<N>(_hlslpp_andnot_ps(_hlslpp_isfinite_ps(v._vec), f4_1)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> isfinite(const components<Dim...>& v) { return isfinite(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> isinf(const floatN<N>& v) { return floatN<N>(_hlslpp_and_ps(_hlslpp_isinf_ps(v._vec), f4_1)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> isinf(const components<Dim...>& v) { return isinf(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> isnan(const floatN<N>& v) { return floatN<N>(_hlslpp_and_ps(_hlslpp_isnan_ps(v._vec), f4_1)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> isnan(const components<Dim...>& v) { return isnan(floatN<sizeof...(Dim)>(v)); }

inline float1 length(const float1& v) { return v; }
inline float1 length(const float2& v) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot2_ps(v._vec, v._vec))); }
inline float1 length(const float3& v) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot3_ps(v._vec, v._vec))); }
inline float1 length(const float4& v) { return float1(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(v._vec, v._vec))); }

template<int N> inline floatN<N> lerp(const floatN<N>& v1, const floatN<N>& v2, const floatN<N>& a) { return floatN<N>(_hlslpp_lrp_ps(v1._vec, v2._vec, a._vec)); }

template<int N> inline floatN<N> lerp(const floatN<N>& v1, const floatN<N>& v2, float a) { return lerp(v1, v2, floatN<N>(a)); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> lerp(const floatN<N>& v1, const floatN<N>& v2, const components<Dim...>& a) { return lerp(v1, v2, floatN<N>(a)); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> lerp(const floatN<N>& v1, const components<Dim...>& v2, const floatN<N>& a) { return lerp(v1, floatN<N>(v2), a); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> lerp(const components<Dim...>& v1, const floatN<N>& v2, const floatN<N>& a) { return lerp(floatN<N>(v1), v2, a); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> lerp(const floatN<N>& v1, const components<Dim...>& v2, const components<Dim...>& a) { return lerp(v1, floatN<N>(v2), floatN<N>(a)); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> lerp(const components<Dim...>& v1, const floatN<N>& v2, const components<Dim...>& a) { return lerp(floatN<N>(v1), v2, floatN<N>(a)); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> lerp(const components<Dim...>& v1, const components<Dim...>& v2, const floatN<N>& a) { return lerp(floatN<N>(v1), floatN<N>(v2), a); }

template<template<int...Dim> class components, int...Dim1, int...Dim2, int...Dim3>
inline floatN<sizeof...(Dim1)> lerp(const components<Dim1...>& v1, const components<Dim2...>& v2, const components<Dim3...>& a) 
{ 
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return lerp(floatN<sizeof...(Dim1)>(v1), floatN<sizeof...(Dim1)>(v2), floatN<sizeof...(Dim1)>(a)); 
}

template<int N> inline floatN<N> log(const floatN<N>& v) { return floatN<N>(_hlslpp_log_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> log(const components<Dim...>& v) { return log(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> log2(const floatN<N>& v) { return floatN<N>(_hlslpp_log2_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> log2(const components<Dim...>& v) { return log2(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> log10(const floatN<N>& v) { return floatN<N>(_hlslpp_log10_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> log10(const components<Dim...>& v) { return log10(floatN<sizeof...(Dim)>(v)); }

// Minimum
template<int N> inline floatN<N> min(const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_min_ps(v1._vec, v2._vec)); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> min(const floatN<N>& v1, const components<Dim...>& v2) { return min(v1, floatN<N>(v2)); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> min(const components<Dim...>& v1, const floatN<N>& v2) { return min(floatN<N>(v1), v2); }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> min(const components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return min(floatN<sizeof...(Dim1)>(v1), floatN<sizeof...(Dim1)>(v2));
}

// Maximum
template<int N> inline floatN<N> max(const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_max_ps(v1._vec, v2._vec)); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> max(const floatN<N>& v1, const components<Dim...>& v2) { return max(v1, floatN<N>(v2)); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> max(const components<Dim...>& v1, const floatN<N>& v2) { return max(floatN<N>(v1), v2); }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> max(const components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return max(floatN<sizeof...(Dim1)>(v1), floatN<sizeof...(Dim1)>(v2));
}

// Normalize

inline float4 normalize(const float4& v) { return float4(_hlslpp_div_ps(v._vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot4_ps(v._vec, v._vec))))); }
inline float3 normalize(const float3& v) { return float3(_hlslpp_div_ps(v._vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot3_ps(v._vec, v._vec))))); }
inline float2 normalize(const float2& v) { return float2(_hlslpp_div_ps(v._vec, _hlslpp_perm_xxxx_ps(_hlslpp_sqrt_ps(_hlslpp_dot2_ps(v._vec, v._vec))))); }
inline float1 normalize(const float1&) { return float1(1.0f); }

// Pow
template<int N> inline floatN<N> pow(const floatN<N>& v1, const floatN<N>& v2) { return floatN<N>(_hlslpp_exp2_ps(_hlslpp_mul_ps(v1._vec, _hlslpp_log2_ps(v2._vec)))); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> pow(const floatN<N>& v1, const components<Dim...>& v2) { return pow(v1, floatN<N>(v2)); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> pow(const components<Dim...>& v1, const floatN<N>& v2) { return pow(floatN<N>(v1), v2); }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> pow(const components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return pow(floatN<sizeof...(Dim1)>(v1), floatN<sizeof...(Dim1)>(v2));
}

template<int N> inline floatN<N> radians(const floatN<N>& v) { return floatN<N>(_hlslpp_mul_ps(v._vec, f4_deg2rad)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> radians(const components<Dim...>& v) { return radians(floatN<sizeof...(Dim)>(v)); }


inline float1 reflect(const float1& i, const float1& n) { return float1(_hlslpp_sub_ps(i._vec, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n._vec, _hlslpp_perm_xxxx_ps(_hlslpp_mul_ps(i._vec, n._vec)))))); }
inline float2 reflect(const float2& i, const float2& n) { return float2(_hlslpp_sub_ps(i._vec, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n._vec, _hlslpp_perm_xxxx_ps(_hlslpp_dot2_ps(i._vec, n._vec)))))); }
inline float3 reflect(const float3& i, const float3& n) { return float3(_hlslpp_sub_ps(i._vec, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n._vec, _hlslpp_perm_xxxx_ps(_hlslpp_dot3_ps(i._vec, n._vec)))))); }
inline float4 reflect(const float4& i, const float4& n) { return float4(_hlslpp_sub_ps(i._vec, _hlslpp_mul_ps(f4_2, _hlslpp_mul_ps(n._vec, _hlslpp_perm_xxxx_ps(_hlslpp_dot4_ps(i._vec, n._vec)))))); }

template<int N> inline floatN<N> rsqrt(const floatN<N>& v) { return floatN<N>(_hlslpp_rsqrt_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> rsqrt(const components<Dim...>& v) { return rsqrt(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> round(const floatN<N>& v) { return floatN<N>(_hlslpp_round_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> round(const components<Dim...>& v) { return round(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> saturate(const floatN<N>& v) { return floatN<N>(_hlslpp_sat_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> saturate(const components<Dim...>& v) { return saturate(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> sign(const floatN<N>& v) {	return floatN<N>(_hlslpp_sign_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> sign(const components<Dim...>& v) { return sign(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> sin(const floatN<N>& v) { return floatN<N>(_hlslpp_sin_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> sin(const components<Dim...>& v) { return sin(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> sqrt(const floatN<N>& v) { return floatN<N>(_hlslpp_sqrt_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> sqrt(const components<Dim...>& v) { return sqrt(floatN<sizeof...(Dim)>(v)); }

// Step
// Hlsl, glsl and Cg behavior is to swap the operands.
// http://http.developer.nvidia.com/Cg/step.html
// https://www.opengl.org/sdk/docs/man/html/step.xhtml
template<int N> inline floatN<N> step(const floatN<N>& v1, const floatN<N>& v2) { return v1 >= v2; }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> step(const floatN<N>& v1, const components<Dim...>& v2) { return v1 >= floatN<N>(v2); }

template<int N, template<int...Dim> class components, int...Dim>
inline floatN<N> step(const components<Dim...>& v1, const floatN<N>& v2) { return floatN<N>(v1) >= v2; }

template<template<int...Dim> class components, int...Dim1, int...Dim2>
inline floatN<sizeof...(Dim1)> step(const components<Dim1...>& v1, const components<Dim2...>& v2)
{
	static_assert(sizeof...(Dim1) == sizeof...(Dim2), "Vectors must be the same dimension!");
	return floatN<sizeof...(Dim1)>(v1) >= floatN<sizeof...(Dim1)>(v2);
}

template<int N> inline floatN<N> tan(const floatN<N>& v) { return floatN<N>(_hlslpp_tan_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> tan(const components<Dim...>& v) { return tan(floatN<sizeof...(Dim)>(v)); }

template<int N> inline floatN<N> trunc(const floatN<N>& v) { return floatN<N>(_hlslpp_trunc_ps(v._vec)); }

template<template<int...Dim> class components, int...Dim>
inline floatN<sizeof...(Dim)> trunc(const components<Dim...>& v) { return trunc(floatN<sizeof...(Dim)>(v)); }

// inline float4 normalize_fast(const float4& v)
// {
// 	return float4(_hlslpp_mul_ps(v._vec, _hlslpp_perm_xxxx_ps(_mm_rsqrt_ps(_hlslpp_dot4_ps(v._vec, v._vec)))));
// }

// inline float4 smoothstep

// https://books.google.co.uk/books?id=yphBBAAAQBAJ&pg=PA99&lpg=PA99&dq=_mm_cmpnltps&source=bl&ots=zLVjV__tgU&sig=8uNKfkS_-hIbiLRSFODgG5EWMzw&hl=en&sa=X&ved=0ahUKEwjlkY3126nRAhUHI8AKHSqUCJ4Q6AEIGjAA#v=onepage&q&f=false
//inline float4 atan2
//inline float4 cosh
//inline float4 sinh
//inline float4 tanh

//-----------------
// Matrix functions
//-----------------

// For matrices, use SFINAE with dummy template parameters to reduce code repetition and enforce conditions to make sure templates aren't ambiguous
// (e.g. a template for <1, N> and a template for <M, 2>)

// Matrix - Matrix multiplication

// Note that matrix-vector multiplication assumes the matrix data is laid out as row major.

template<int M>
inline floatNxM<1, M> mul(const float1x1& m1, const floatNxM<1, M>& m2)
{
	return floatNxM<1, M>(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1._vec), m2._vec));
}

template<int N, typename std::enable_if<(N > 1)>::type* = nullptr>
inline floatNxM<N, 1> mul(const floatNxM<N, 1>& m1, const float1x1& m2)
{
	return floatNxM<N, 1>(_hlslpp_mul_ps(m1._vec, _hlslpp_perm_xxxx_ps(m2._vec)));
}

inline float2x2 mul(const float2x1& m1, const float1x2& m2)
{
	return float2x2(_hlslpp_mul_ps(_hlslpp_perm_xxyy_ps(m1._vec), _hlslpp_perm_xyxy_ps(m2._vec)));
}

template<int M, typename std::enable_if<(M > 2)>::type* = nullptr>
inline floatNxM<2, M> mul(const float2x1& m1, const floatNxM<1, M>& m2)
{
	return floatNxM<2, M>(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1._vec), m2._vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1._vec), m2._vec));
}

template<int N, typename std::enable_if<(N > 2)>::type* = nullptr>
inline floatNxM<N, 2> mul(const floatNxM<N, 1>& m1, const float1x2& m2)
{
	return floatNxM<N, 2>(_hlslpp_mul_ps(m1._vec, _hlslpp_perm_xxxx_ps(m2._vec)), _hlslpp_mul_ps(m1._vec, _hlslpp_perm_yyyy_ps(m2._vec)));
}

template<int N, typename std::enable_if<(N > 2)>::type* = nullptr>
inline floatNxM<N, 3> mul(const floatNxM<N, 1>& m1, const float1x3& m2)
{
	return floatNxM<N, 3>(_hlslpp_mul_ps(m1._vec, _hlslpp_perm_xxxx_ps(m2._vec)), _hlslpp_mul_ps(m1._vec, _hlslpp_perm_yyyy_ps(m2._vec)), _hlslpp_mul_ps(m1._vec, _hlslpp_perm_zzzz_ps(m2._vec)));
}

inline float3x4 mul(const float3x1& m1, const float1x4& m2)
{
	return float3x4(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1._vec), m2._vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1._vec), m2._vec), _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1._vec), m2._vec));
}

inline float4x4 mul(const float4x1& m1, const float1x4& m2)
{
	return float4x4(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1._vec), m2._vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1._vec), m2._vec), _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1._vec), m2._vec), _hlslpp_mul_ps(_hlslpp_perm_wwww_ps(m1._vec), m2._vec));
}

inline float1x1 mul(const float1x2& m1, const float2x1& m2)
{
	return float1x1(_hlslpp_dot2_ps(m1._vec, m2._vec));
}

inline n128 _hlslpp_mul_1x2_2x1_ps(n128 m1_vec, n128 m2_vec)
{
	n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec), m2_vec);
	n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1_vec), _hlslpp_perm_zwxx_ps(m2_vec));
	n128 result = _hlslpp_add_ps(mul1, mul2);
	return result;
}

inline n128 _hlslpp_mul_1x2_2xM_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1)
{
	n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec), m2_vec0);
	n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1_vec), m2_vec1);
	n128 result = _hlslpp_add_ps(mul1, mul2);
	return result;
}

inline n128 _hlslpp_mul_1x3_3x2_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1)
{
	n128 dpx = _hlslpp_dot3_ps(m1_vec, m2_vec0);
	n128 dpy = _hlslpp_dot3_ps(m1_vec, m2_vec1);
	n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
	return result;
}

inline n128 _hlslpp_mul_1x3_3xM_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2)
{
	n128 mul0 = _hlslpp_mul_ps(m2_vec0, _hlslpp_perm_xxxx_ps(m1_vec));
	n128 mul1 = _hlslpp_madd_ps(m2_vec1, _hlslpp_perm_yyyy_ps(m1_vec), mul0);
	n128 result = _hlslpp_madd_ps(m2_vec2, _hlslpp_perm_zzzz_ps(m1_vec), mul1);
	return result;
}

inline n128 _hlslpp_mul_1x4_4x2_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1)
{
	n128 dpx = _hlslpp_dot4_ps(m1_vec, m2_vec0);
	n128 dpy = _hlslpp_dot4_ps(m1_vec, m2_vec1);
	n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
	return result;
}

inline n128 _hlslpp_mul_1x4_4x3_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2)
{
	n128 dpx = _hlslpp_dot4_ps(m1_vec, m2_vec0);
	n128 dpy = _hlslpp_dot4_ps(m1_vec, m2_vec1);
	n128 dpz = _hlslpp_dot4_ps(m1_vec, m2_vec2);
	n128 result = _hlslpp_blend_ps(dpy, _hlslpp_shuf_xxxx_ps(dpx, dpz), HLSLPP_BLEND_MASK(0, 1, 0, 1));
	return result;
}

inline n128 _hlslpp_mul_1x4_4x4_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, const n128& m2_vec3)
{
	n128 mul0 = _hlslpp_mul_ps(m2_vec0, _hlslpp_perm_xxxx_ps(m1_vec));
	n128 mul1 = _hlslpp_madd_ps(m2_vec1, _hlslpp_perm_yyyy_ps(m1_vec), mul0);
	n128 mul2 = _hlslpp_madd_ps(m2_vec2, _hlslpp_perm_zzzz_ps(m1_vec), mul1);
	n128 result = _hlslpp_madd_ps(m2_vec3, _hlslpp_perm_wwww_ps(m1_vec), mul2);
	return result;
}

inline n128 _hlslpp_mul_2x2_2x1_ps(const n128& m1_vec, const n128& m2_vec)
{
	n128 dpx = _hlslpp_dot2_ps(m1_vec, m2_vec);
	n128 dpy = _hlslpp_dot2_ps(_hlslpp_perm_zwxx_ps(m1_vec), m2_vec);
	n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
	return result;
}

inline n128 _hlslpp_mul_2x2_2x2_ps(const n128& m1_vec, const n128& m2_vec)
{
	// First and last elements in the matrix
	n128 diag1shuf1 = _hlslpp_perm_xzyw_ps(m2_vec);			// Shuffle m2 to align components with m1
	n128 diag1mul1 = _hlslpp_mul_ps(m1_vec, diag1shuf1);		// Multiply. Now contains m00 * n00, m01 * n10, m10 * n01, m11 * n11
	n128 diag1shuf2 = _hlslpp_perm_yxxz_ps(diag1mul1);		// Shuffle to align to be able to add
	n128 diag1result = _hlslpp_add_ps(diag1mul1, diag1shuf2);	// Now contains m00*n00 + m01*n10, _, _, m10*n01 + m11*n11

	// Second and third elements in the matrix
	n128 diag2shuf1 = _hlslpp_perm_ywxz_ps(m2_vec);			// Shuffle matrix to align components with m1
	n128 diag2mul1 = _hlslpp_mul_ps(m1_vec, diag2shuf1);		// Multiply. Now contains m00 * n00, m01 * n10, m10 * n01, m11 * n11
	n128 diag2shuf2 = _hlslpp_perm_xxwx_ps(diag2mul1);		// Shuffle to align to be able to add
	n128 diag2result = _hlslpp_add_ps(diag2mul1, diag2shuf2);	// Now contains m00*n00 + m01*n10, _, _, m10*n01 + m11*n11

	n128 result = _hlslpp_blend_ps(diag1result, diag2result, HLSLPP_BLEND_MASK(1, 0, 0, 1));
	return result;
}

inline void _hlslpp_mul_2x2_2xM_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
{
	n128 mul0 = _hlslpp_mul_ps(m2_vec0, _hlslpp_perm_xxxx_ps(m1_vec));
	o_vec0 = _hlslpp_madd_ps(m2_vec1, _hlslpp_perm_yyyy_ps(m1_vec), mul0);

	n128 mul1 = _hlslpp_mul_ps(m2_vec0, _hlslpp_perm_zzzz_ps(m1_vec));
	o_vec1 = _hlslpp_madd_ps(m2_vec1, _hlslpp_perm_wwww_ps(m1_vec), mul1);
}

inline n128 _hlslpp_mul_Nx2_2x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec)
{
	n128 mul0 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec));
	n128 result = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec), mul0);
	return result;
}

inline void _hlslpp_mul_Nx2_2x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec, n128& o_vec0, n128& o_vec1)
{
	n128 mul0 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec));
	o_vec0 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_zzzz_ps(m2_vec), mul0);

	n128 mul1 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_yyyy_ps(m2_vec));
	o_vec1 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_wwww_ps(m2_vec), mul1);
}

inline void _hlslpp_mul_3x2_2xM_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1, n128& o_vec2)
{
	n128 mul0 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
	o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec1, mul0);

	n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec0);
	o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul1);

	n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec0);
	o_vec2 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec1, mul2);
}

inline void _hlslpp_mul_4x2_2x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1, n128& o_vec2)
{
	n128 mul0 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec0));
	o_vec0 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_xxxx_ps(m2_vec1), mul0);

	n128 mul1 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_yyyy_ps(m2_vec0));
	o_vec1 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec1), mul1);

	n128 mul2 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_zzzz_ps(m2_vec0));
	o_vec2 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_zzzz_ps(m2_vec1), mul2);
}

inline void _hlslpp_mul_4x2_2x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
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

inline n128 _hlslpp_mul_2x3_3x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec)
{
	n128 dpx = _hlslpp_dot3_ps(m1_vec0, m2_vec);
	n128 dpy = _hlslpp_dot3_ps(m1_vec1, m2_vec);
	n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
	return result;
}

inline n128 _hlslpp_mul_2x3_3x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1)
{
	n128 dpx = _hlslpp_dot3_ps(m1_vec0, m2_vec0);
	n128 dpy = _hlslpp_dot3_ps(m1_vec0, m2_vec1);
	n128 dpz = _hlslpp_dot3_ps(m1_vec1, m2_vec0);
	n128 dpw = _hlslpp_dot3_ps(m1_vec1, m2_vec1);
	n128 result = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx, dpz), _hlslpp_shuf_xxxx_ps(dpy, dpw), HLSLPP_BLEND_MASK(1, 0, 1, 0));
	return result;
}

inline void _hlslpp_mul_4x2_2x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1)
{
	n128 mul0 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
	n128 mul1 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec1, mul0);
	o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec2, mul1);

	n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec0);
	n128 mul3 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul2);
	o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec2, mul3);
}

inline n128 _hlslpp_mul_2x3_3x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec)
{
	n128 dpx = _hlslpp_dot4_ps(m1_vec0, m2_vec);
	n128 dpy = _hlslpp_dot4_ps(m1_vec1, m2_vec);
	n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
	return result;
}

inline n128 _hlslpp_mul_2x4_4x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1)
{
	n128 dpx = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
	n128 dpy = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
	n128 dpz = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
	n128 dpw = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
	n128 result = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx, dpz), _hlslpp_shuf_xxxx_ps(dpy, dpw), HLSLPP_BLEND_MASK(1, 0, 1, 0));
	return result;
}

inline void _hlslpp_mul_2x4_4x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1)
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

inline void _hlslpp_mul_2x4_4x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, const n128& m2_vec3, n128& o_vec0, n128& o_vec1)
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

inline n128 _hlslpp_mul_3x3_3x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec)
{
	n128 dpx = _hlslpp_dot3_ps(m1_vec0, m2_vec);
	n128 dpy = _hlslpp_dot3_ps(m1_vec1, m2_vec);
	n128 dpz = _hlslpp_dot3_ps(m1_vec2, m2_vec);
	n128 result = _hlslpp_blend_ps(dpx, _hlslpp_shuf_xxxx_ps(dpy, dpz), HLSLPP_BLEND_MASK(1, 0, 0, 1));
	return result;
}

inline void _hlslpp_mul_3x3_3x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
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

inline void _hlslpp_mul_3x3_3x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
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

inline void _hlslpp_mul_3x3_3x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
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

inline n128 _hlslpp_mul_3x4_4x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec)
{
	n128 dpx = _hlslpp_dot4_ps(m1_vec0, m2_vec);
	n128 dpy = _hlslpp_dot4_ps(m1_vec1, m2_vec);
	n128 dpz = _hlslpp_dot4_ps(m1_vec2, m2_vec);
	n128 result = _hlslpp_blend_ps(dpy, _hlslpp_shuf_xxxx_ps(dpx, dpz), HLSLPP_BLEND_MASK(0, 1, 0, 1));
	return result;
}

inline void _hlslpp_mul_3x4_4x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
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

inline void _hlslpp_mul_3x4_4x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
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

inline void _hlslpp_mul_3x4_4x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, const n128& m2_vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2)
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

inline n128 _hlslpp_mul_4x3_3x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec)
{
	n128 mul1x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec));
	n128 mad1y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec), mul1x);
	n128 result = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec), mad1y);
	return result;
}

inline void _hlslpp_mul_4x3_3x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
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

inline void _hlslpp_mul_4x3_3x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
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

inline void _hlslpp_mul_4x3_3x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
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

inline n128 _hlslpp_mul_4x4_4x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m1_vec3, const n128& m2_vec)
{
	n128 dpx = _hlslpp_dot4_ps(m1_vec0, m2_vec);
	n128 dpy = _hlslpp_dot4_ps(m1_vec1, m2_vec);
	n128 dpz = _hlslpp_dot4_ps(m1_vec2, m2_vec);
	n128 dpw = _hlslpp_dot4_ps(m1_vec3, m2_vec);

	n128 result = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx, dpz), _hlslpp_shuf_xxxx_ps(dpy, dpw), HLSLPP_BLEND_MASK(1, 0, 1, 0));
	return result;
}

inline void _hlslpp_mul_4x4_4x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m1_vec3, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
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

inline void _hlslpp_mul_4x4_4x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m1_vec3, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
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

inline void _hlslpp_mul_4x4_4x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m1_vec3, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, const n128& m2_vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
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

inline float1x2 mul(const float1x2& m1, const float2x2& m2)
{	
	return float1x2(_hlslpp_mul_1x2_2x1_ps(m1._vec, m2._vec));
}

template<int M, typename std::enable_if<(M > 2)>::type* = nullptr>
inline floatNxM<1, M> mul(const float1x2& m1, const floatNxM<2, M>& m2)
{
	return floatNxM<1, M>(_hlslpp_mul_1x2_2xM_ps(m1._vec, m2._vec0, m2._vec1));
}

inline float1x1 mul(const float1x3& m1, const float3x1& m2)
{
	return float1x1(_hlslpp_dot3_ps(m1._vec, m2._vec));
}

inline float1x2 mul(const float1x3& m1, const float3x2& m2)
{
	return float1x2(_hlslpp_mul_1x3_3x2_ps(m1._vec, m2._vec0, m2._vec1));
}

template<int M, typename std::enable_if<(M > 2)>::type* = nullptr>
inline floatNxM<1, M> mul(const float1x3& m1, const floatNxM<3, M>& m2)
{
	return floatNxM<1, M>(_hlslpp_mul_1x3_3xM_ps(m1._vec, m2._vec0, m2._vec1, m2._vec2));
}

inline float1x1 mul(const float1x4& m1, const float4x1& m2)
{
	return float1x1(_hlslpp_dot4_ps(m1._vec, m2._vec));
}

inline float1x2 mul(const float1x4& m1, const float4x2& m2)
{
	return float1x2(_hlslpp_mul_1x4_4x2_ps(m1._vec, m2._vec0, m2._vec1));
}

inline float1x3 mul(const float1x4& m1, const float4x3& m2)
{
	return float1x3(_hlslpp_mul_1x4_4x3_ps(m1._vec, m2._vec0, m2._vec1, m2._vec2));
}

inline float1x4 mul(const float1x4& m1, const float4x4& m2)
{
	return float1x4(_hlslpp_mul_1x4_4x4_ps(m1._vec, m2._vec0, m2._vec1, m2._vec2, m2._vec3));
}

inline float2x1 mul(const float2x2& m1, const float2x1& m2)
{
	return float2x1(_hlslpp_mul_2x2_2x1_ps(m1._vec, m2._vec));
}

inline float2x2 mul(const float2x2& m1, const float2x2& m2)
{
	return float2x2(_hlslpp_mul_2x2_2x2_ps(m1._vec, m2._vec));
}

template<int M, typename std::enable_if<(M > 2)>::type* = nullptr>
inline floatNxM<2, M> mul(const float2x2& m1, const floatNxM<2, M>& m2)
{
	n128 vec0, vec1;
	_hlslpp_mul_2x2_2xM_ps(m1._vec, m2._vec0, m2._vec1, vec0, vec1);
	return floatNxM<2, M>(vec0, vec1);
}

template<int N, typename std::enable_if<(N > 2)>::type* = nullptr>
inline floatNxM<N, 1> mul(const floatNxM<N, 2>& m1, const float2x1& m2)
{
	return floatNxM<N, 1>(_hlslpp_mul_Nx2_2x1_ps(m1._vec0, m1._vec1, m2._vec));
}

template<int N, typename std::enable_if<(N > 2)>::type* = nullptr>
inline floatNxM<N, 2> mul(const floatNxM<N, 2>& m1, const float2x2& m2)
{
	n128 vec0, vec1;
	_hlslpp_mul_Nx2_2x2_ps(m1._vec0, m1._vec1, m2._vec, vec0, vec1);
	return floatNxM<N, 2>(vec0, vec1);
}

template<int M, typename std::enable_if<(M > 2)>::type* = nullptr>
inline floatNxM<3, M> mul(const float3x2& m1, const floatNxM<2, M>& m2)
{
	n128 vec0, vec1, vec2;
	_hlslpp_mul_3x2_2xM_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1, vec0, vec1, vec2);
	return floatNxM<3, M>(vec0, vec1, vec2);
}

inline float4x3 mul(const float4x2& m1, const float2x3& m2)
{
	n128 vec0, vec1, vec2;
	_hlslpp_mul_4x2_2x3_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1, vec0, vec1, vec2);
	return float4x3(vec0, vec1, vec2);
}

inline float4x4 mul(const float4x2& m1, const float2x4& m2)
{
	n128 vec0, vec1, vec2, vec3;
	_hlslpp_mul_4x2_2x4_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1, vec0, vec1, vec2, vec3);
	return float4x4(vec0, vec1, vec2, vec3);
}

inline float2x1 mul(const float2x3& m1, const float3x1& m2)
{
	return float2x1(_hlslpp_mul_2x3_3x1_ps(m1._vec0, m1._vec1, m2._vec));
}

inline float2x2 mul(const float2x3& m1, const float3x2& m2)
{
	return float2x2(_hlslpp_mul_2x3_3x2_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1));
}

template<int M, typename std::enable_if<(M > 2)>::type* = nullptr>
inline floatNxM<2, M> mul(const float2x3& m1, const floatNxM<3, M>& m2)
{
	n128 vec0, vec1;
	_hlslpp_mul_4x2_2x4_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1, m2._vec2, vec0, vec1);
	return floatNxM<2, M>(vec0, vec1);
}

inline float2x1 mul(const float2x4& m1, const float4x1& m2)
{
	return float2x1(_hlslpp_mul_2x3_3x2_ps(m1._vec0, m1._vec1, m2._vec));
}

inline float2x2 mul(const float2x4& m1, const float4x2& m2)
{
	return float2x2(_hlslpp_mul_2x4_4x2_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1));
}

inline float2x3 mul(const float2x4& m1, const float4x3& m2)
{
	n128 vec0, vec1;
	_hlslpp_mul_2x4_4x3_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1, m2._vec2, vec0, vec1);
	return float2x3(vec0, vec1);
}

inline float2x4 mul(const float2x4& m1, const float4x4& m2)
{
	n128 vec0, vec1;
	_hlslpp_mul_2x4_4x4_ps(m1._vec0, m1._vec1, m2._vec0, m2._vec1, m2._vec2, m2._vec3, vec0, vec1);
	return float2x4(vec0, vec1);
}

inline float3x1 mul(const float3x3& m1, const float3x1& m2)
{
	return float3x1(_hlslpp_mul_3x3_3x1_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec));
}

inline float3x2 mul(const float3x3& m1, const float3x2& m2)
{
	n128 vec0, vec1;
	_hlslpp_mul_3x3_3x2_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, vec0, vec1);
	return float3x2(vec0, vec1);
}

inline float3x3 mul(const float3x3& m1, const float3x3& m2)
{
	n128 vec0, vec1, vec2;
	_hlslpp_mul_3x3_3x3_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, m2._vec2, vec0, vec1, vec2);
	return float3x3(vec0, vec1, vec2);
}

inline float3x4 mul(const float3x3& m1, const float3x4& m2)
{
	n128 vec0, vec1, vec2;
	_hlslpp_mul_3x3_3x4_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, m2._vec2, vec0, vec1, vec2);
	return float3x4(vec0, vec1, vec2);
}

inline float3x1 mul(const float3x4& m1, const float4x1& m2)
{
	
	return float3x1(_hlslpp_mul_3x4_4x1_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec));
}

inline float3x2 mul(const float3x4& m1, const float4x2& m2)
{
	n128 vec0, vec1;
	_hlslpp_mul_3x4_4x2_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, vec0, vec1);
	return float3x2(vec0, vec1);
}

inline float3x3 mul(const float3x4& m1, const float4x3& m2)
{
	n128 vec0, vec1, vec2;
	_hlslpp_mul_3x4_4x3_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, m2._vec2, vec0, vec1, vec2);
	return float3x3(vec0, vec1, vec2);
}

inline float3x4 mul(const float3x4& m1, const float4x4& m2)
{
	n128 vec0, vec1, vec2;
	_hlslpp_mul_3x4_4x4_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, m2._vec2, m2._vec3, vec0, vec1, vec2);
	return float3x4(vec0, vec1, vec2);
}

inline float4x1 mul(const float4x3& m1, const float3x1& m2)
{
	return float4x1(_hlslpp_mul_4x3_3x1_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec));
}

inline float4x2 mul(const float4x3& m1, const float3x2& m2)
{
	n128 vec0, vec1;
	_hlslpp_mul_4x3_3x2_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, vec0, vec1);
	return float4x2(vec0, vec1);
}

inline float4x3 mul(const float4x3& m1, const float3x3& m2)
{
	n128 vec0, vec1, vec2;
	_hlslpp_mul_4x3_3x3_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, m2._vec2, vec0, vec1, vec2);
	return float4x3(vec0, vec1, vec2);
}

inline float4x4 mul(const float4x3& m1, const float3x4& m2)
{
	n128 vec0, vec1, vec2, vec3;
	_hlslpp_mul_4x3_3x4_ps(m1._vec0, m1._vec1, m1._vec2, m2._vec0, m2._vec1, m2._vec2, vec0, vec1, vec2, vec3);
	return float4x4(vec0, vec1, vec2, vec3);
}

inline float4x1 mul(const float4x4& m1, const float4x1& m2)
{
	return float4x1(_hlslpp_mul_4x4_4x1_ps(m1._vec0, m1._vec1, m1._vec2, m1._vec3, m2._vec));
}

inline float4x2 mul(const float4x4& m1, const float4x2& m2)
{
	n128 vec0, vec1;
	_hlslpp_mul_4x4_4x2_ps(m1._vec0, m1._vec1, m1._vec2, m1._vec3, m2._vec0, m2._vec1, vec0, vec1);
	return float4x2(vec0, vec1);
}

inline float4x3 mul(const float4x4& m1, const float4x3& m2)
{
	n128 vec0, vec1, vec2;
	_hlslpp_mul_4x4_4x3_ps(m1._vec0, m1._vec1, m1._vec2, m1._vec3, m2._vec0, m2._vec1, m2._vec2, vec0, vec1, vec2);
	return float4x3(vec0, vec1, vec2);
}

inline float4x4 mul(const float4x4& m1, const float4x4& m2)
{
#if defined(HLSLPP_MATRIX_PACK_COLUMN_MAJOR)

#else

#endif
	
	n128 vec0, vec1, vec2, vec3;
	_hlslpp_mul_4x4_4x4_ps(m1._vec0, m1._vec1, m1._vec2, m1._vec3, m2._vec0, m2._vec1, m2._vec2, m2._vec3, vec0, vec1, vec2, vec3);
	return float4x4(vec0, vec1, vec2, vec3);
}

// Matrix-matrix multiplication with floatN<N> vectors and components as operands

template<int N> inline floatN<N> mul(const floatNxM<N, 4>& m1, const float4& v) { return floatN<N>(mul(m1, float4x1(v))); }

template<int N> inline floatN<N> mul(const floatNxM<N, 3>& m1, const float3& v) { return floatN<N>(mul(m1, float3x1(v))); }

template<int N> inline floatN<N> mul(const floatNxM<N, 2>& m1, const float2& v) { return floatN<N>(mul(m1, float2x1(v))); }

template<int N> inline floatN<N> mul(const floatNxM<N, 1>& m1, const float1& v) { return floatN<N>(mul(m1, float1x1(v))); }

template<int N> inline floatN<N> mul(const float4& v, const floatNxM<N, 4>& m1) { return floatN<N>(mul(float1x4(v), m1)); }

template<int N> inline floatN<N> mul(const float3& v, const floatNxM<N, 3>& m1) { return floatN<N>(mul(float1x3(v), m1)); }

template<int N> inline floatN<N> mul(const float2& v, const floatNxM<N, 2>& m1) { return floatN<N>(mul(float1x2(v), m1)); }

template<int N> inline floatN<N> mul(const float1& v, const floatNxM<N, 1>& m1) { return floatN<N>(mul(float1x1(v), m1)); }

// Matrix-Matrix Addition

template<int N, int M, typename std::enable_if<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))>::type* = nullptr>
inline floatNxM<N, M> operator + (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	return floatNxM<N, M>(_hlslpp_add_ps(m1._vec, m2._vec));
}

template<int N, int M, typename std::enable_if<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))>::type* = nullptr>
inline floatNxM<N, M> operator + (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	return floatNxM<N, M>(_hlslpp_add_ps(m1._vec0, m2._vec0), _hlslpp_add_ps(m1._vec1, m2._vec1));
}

template<int N, int M, typename std::enable_if<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))>::type* = nullptr>
inline floatNxM<N, M> operator + (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	return floatNxM<N, M>(_hlslpp_add_ps(m1._vec0, m2._vec0), _hlslpp_add_ps(m1._vec1, m2._vec1), _hlslpp_add_ps(m1._vec2, m2._vec2));
}

inline float4x4 operator + (const float4x4& m1, const float4x4& m2)
{
	return float4x4(_hlslpp_add_ps(m1._vec0, m2._vec0), _hlslpp_add_ps(m1._vec1, m2._vec1), _hlslpp_add_ps(m1._vec2, m2._vec2), _hlslpp_add_ps(m1._vec3, m2._vec3));
}

template<int N, int M>
inline floatNxM<N, M>& operator += (floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	m1 = m1 + m2;
	return m1;
}

// Matrix-Scalar Addition

template<int N, int M, typename std::enable_if<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))>::type* = nullptr>
inline floatNxM<N, M> operator + (const floatNxM<N, M>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<N, M>(_hlslpp_add_ps(m._vec, v_perm));
}

template<int N, int M, typename std::enable_if<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))>::type* = nullptr>
inline floatNxM<N, M> operator + (const floatNxM<N, M>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<N, M>(_hlslpp_add_ps(m._vec0, v_perm), _hlslpp_add_ps(m._vec1, v_perm));
}

template<int N, int M, typename std::enable_if<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))>::type* = nullptr>
inline floatNxM<N, M> operator + (const floatNxM<N, M>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<N, M>(_hlslpp_add_ps(m._vec0, v_perm), _hlslpp_add_ps(m._vec1, v_perm), _hlslpp_add_ps(m._vec2, v_perm));
}

inline float4x4 operator + (const float4x4& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return float4x4(_hlslpp_add_ps(m._vec0, v_perm), _hlslpp_add_ps(m._vec1, v_perm), _hlslpp_add_ps(m._vec2, v_perm), _hlslpp_add_ps(m._vec3, v_perm));
}

template<int N, int M>
inline floatNxM<N, M>& operator += (floatNxM<N, M>& m, const float1& v)
{
	m = m + v;
	return m;
}

// Matrix-Matrix Subtraction

template<int N, int M, typename std::enable_if<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))>::type* = nullptr>
inline floatNxM<N, M> operator - (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	return floatNxM<N, M>(_hlslpp_sub_ps(m1._vec, m2._vec));
}

template<int N, int M, typename std::enable_if<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))>::type* = nullptr>
inline floatNxM<N, M> operator - (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	return floatNxM<N, M>(_hlslpp_sub_ps(m1._vec0, m2._vec0), _hlslpp_sub_ps(m1._vec1, m2._vec1));
}

template<int N, int M, typename std::enable_if<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))>::type* = nullptr>
inline floatNxM<N, M> operator - (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	return floatNxM<N, M>(_hlslpp_sub_ps(m1._vec0, m2._vec0), _hlslpp_sub_ps(m1._vec1, m2._vec1), _hlslpp_sub_ps(m1._vec2, m2._vec2));
}

inline floatNxM<4, 4> operator - (const floatNxM<4, 4>& m1, const floatNxM<4, 4>& m2)
{
	return floatNxM<4, 4>(_hlslpp_sub_ps(m1._vec0, m2._vec0), _hlslpp_sub_ps(m1._vec1, m2._vec1), _hlslpp_sub_ps(m1._vec2, m2._vec2), _hlslpp_sub_ps(m1._vec3, m2._vec3));
}

template<int N, int M>
inline floatNxM<N, M>& operator -= (floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	m1 = m1 - m2;
	return m1;
}

// Matrix-Scalar Subtraction

template<int N, int M, typename std::enable_if<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))>::type* = nullptr>
inline floatNxM<N, M> operator - (const floatNxM<N, M>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<N, M>(_hlslpp_sub_ps(m._vec, v_perm));
}

template<int N, int M, typename std::enable_if<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))>::type* = nullptr>
inline floatNxM<N, M> operator - (const floatNxM<N, M>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<N, M>(_hlslpp_sub_ps(m._vec0, v_perm), _hlslpp_sub_ps(m._vec1, v_perm));
}

template<int N, int M, typename std::enable_if<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))>::type* = nullptr>
inline floatNxM<N, M> operator - (const floatNxM<N, M>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<N, M>(_hlslpp_sub_ps(m._vec0, v_perm), _hlslpp_sub_ps(m._vec1, v_perm), _hlslpp_sub_ps(m._vec2, v_perm));
}

inline floatNxM<4, 4> operator - (const floatNxM<4, 4>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<4, 4>(_hlslpp_sub_ps(m._vec0, v_perm), _hlslpp_sub_ps(m._vec1, v_perm), _hlslpp_sub_ps(m._vec2, v_perm), _hlslpp_sub_ps(m._vec3, v_perm));
}

template<int N, int M>
inline floatNxM<N, M>& operator -= (floatNxM<N, M>& m, const float1& v)
{
	m = m - v;
	return m;
}

// Multiplication

template<int N, int M, typename std::enable_if<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))>::type* = nullptr>
inline floatNxM<N, M> operator * (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	return floatNxM<N, M>(_hlslpp_mul_ps(m1._vec, m2._vec));
}

template<int N, int M, typename std::enable_if<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))>::type* = nullptr>
inline floatNxM<N, M> operator * (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	return floatNxM<N, M>(_hlslpp_mul_ps(m1._vec0, m2._vec0), _hlslpp_mul_ps(m1._vec1, m2._vec1));
}

template<int N, int M, typename std::enable_if<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))>::type* = nullptr>
inline floatNxM<N, M> operator * (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	return floatNxM<N, M>(_hlslpp_mul_ps(m1._vec0, m2._vec0), _hlslpp_mul_ps(m1._vec1, m2._vec1), _hlslpp_mul_ps(m1._vec2, m2._vec2));
}

inline floatNxM<4, 4> operator * (const floatNxM<4, 4>& m1, const floatNxM<4, 4>& m2)
{
	return floatNxM<4, 4>(_hlslpp_mul_ps(m1._vec0, m2._vec0), _hlslpp_mul_ps(m1._vec1, m2._vec1), _hlslpp_mul_ps(m1._vec2, m2._vec2), _hlslpp_mul_ps(m1._vec3, m2._vec3));
}

template<int N, int M>
inline floatNxM<N, M>& operator *= (floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	m1 = m1 * m2;
	return m1;
}

// Matrix-Scalar Multiplication

template<int N, int M, typename std::enable_if<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))>::type* = nullptr>
inline floatNxM<N, M> operator * (const floatNxM<N, M>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<N, M>(_hlslpp_mul_ps(m._vec, v_perm));
}

template<int N, int M, typename std::enable_if<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))>::type* = nullptr>
inline floatNxM<N, M> operator * (const floatNxM<N, M>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<N, M>(_hlslpp_mul_ps(m._vec0, v_perm), _hlslpp_mul_ps(m._vec1, v_perm));
}

template<int N, int M, typename std::enable_if<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))>::type* = nullptr>
inline floatNxM<N, M> operator * (const floatNxM<N, M>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<N, M>(_hlslpp_mul_ps(m._vec0, v_perm), _hlslpp_mul_ps(m._vec1, v_perm), _hlslpp_mul_ps(m._vec2, v_perm));
}

inline floatNxM<4, 4> operator * (const floatNxM<4, 4>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<4, 4>(_hlslpp_mul_ps(m._vec0, v_perm), _hlslpp_mul_ps(m._vec1, v_perm), _hlslpp_mul_ps(m._vec2, v_perm), _hlslpp_mul_ps(m._vec3, v_perm));
}

template<int N, int M>
inline floatNxM<N, M>& operator *= (floatNxM<N, M>& m, const float1& v)
{
	m = m * v;
	return m;
}

// Division

template<int N, int M, typename std::enable_if<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))>::type* = nullptr>
inline floatNxM<N, M> operator / (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	return floatNxM<N, M>(_hlslpp_div_ps(m1._vec, m2._vec));
}

template<int N, int M, typename std::enable_if<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))>::type* = nullptr>
inline floatNxM<N, M> operator / (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	return floatNxM<N, M>(_hlslpp_div_ps(m1._vec0, m2._vec0), _hlslpp_div_ps(m1._vec1, m2._vec1));
}

template<int N, int M, typename std::enable_if<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))>::type* = nullptr>
inline floatNxM<N, M> operator / (const floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	return floatNxM<N, M>(_hlslpp_div_ps(m1._vec0, m2._vec0), _hlslpp_div_ps(m1._vec1, m2._vec1), _hlslpp_div_ps(m1._vec2, m2._vec2));
}

inline floatNxM<4, 4> operator / (const floatNxM<4, 4>& m1, const floatNxM<4, 4>& m2)
{
	return floatNxM<4, 4>(_hlslpp_div_ps(m1._vec0, m2._vec0), _hlslpp_div_ps(m1._vec1, m2._vec1), _hlslpp_div_ps(m1._vec2, m2._vec2), _hlslpp_div_ps(m1._vec3, m2._vec3));
}

template<int N, int M>
inline floatNxM<N, M>& operator /= (floatNxM<N, M>& m1, const floatNxM<N, M>& m2)
{
	m1 = m1 / m2;
	return m1;
}

// Matrix-Scalar Division

template<int N, int M, typename std::enable_if<((N == 1) || (M == 1) || ((N == 2) && (M == 2)))>::type* = nullptr>
inline floatNxM<N, M> operator / (const floatNxM<N, M>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<N, M>(_hlslpp_div_ps(m._vec, v_perm));
}

template<int N, int M, typename std::enable_if<((N == 2) && (M > 2)) || ((N > 2) && (M == 2))>::type* = nullptr>
inline floatNxM<N, M> operator / (const floatNxM<N, M>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<N, M>(_hlslpp_div_ps(m._vec0, v_perm), _hlslpp_div_ps(m._vec1, v_perm));
}

template<int N, int M, typename std::enable_if<((N == 3) && (M >= 3)) || ((N >= 3) && (M == 3))>::type* = nullptr>
inline floatNxM<N, M> operator / (const floatNxM<N, M>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<N, M>(_hlslpp_div_ps(m._vec0, v_perm), _hlslpp_div_ps(m._vec1, v_perm), _hlslpp_div_ps(m._vec2, v_perm));
}

inline floatNxM<4, 4> operator / (const floatNxM<4, 4>& m, const float1& v)
{
	n128 v_perm = _hlslpp_perm_xxxx_ps(v._vec);
	return floatNxM<4, 4>(_hlslpp_div_ps(m._vec0, v_perm), _hlslpp_div_ps(m._vec1, v_perm), _hlslpp_div_ps(m._vec2, v_perm), _hlslpp_div_ps(m._vec3, v_perm));
}

template<int N, int M>
inline floatNxM<N, M>& operator /= (floatNxM<N, M>& m, const float1& v)
{
	m = m / v;
	return m;
}

inline float2x2 transpose(const float2x2& m)
{
	return float2x2(_hlslpp_transpose_2x2_ps(m._vec));
}

inline float3x3 transpose(const float3x3& m)
{
	n128 vec0, vec1, vec2;
	_hlslpp_transpose_3x3_ps(m._vec0, m._vec1, m._vec2, vec0, vec1, vec2);
	return float3x3(vec0, vec1, vec2);
}

inline float4x4 transpose(const float4x4& m)
{
	n128 vec0, vec1, vec2, vec3;
	_hlslpp_transpose_4x4_ps(m._vec0, m._vec1, m._vec2, m._vec3, vec0, vec1, vec2, vec3);
	return float4x4(vec0, vec1, vec2, vec3);
}

// These transpose functions just copy the data because the 1xM, Nx1, 2xM, Nx2, 3xM and Nx3 matrices are always laid out as rows
// even if they're meant to represent columns.

template<int N, int M, typename std::enable_if<(N == 1) || (M == 1)>::type* = nullptr>
floatNxM<M, N> transpose(const floatNxM<N, M>& m) { return floatNxM<M, N>(m._vec); }

template<int N, int M, typename std::enable_if<(N == 2 && M > 2) || (M == 2 && N > 2)>::type* = nullptr>
floatNxM<M, N> transpose(const floatNxM<N, M>& m) {	return floatNxM<M, N>(m._vec0, m._vec1); }

template<int N, int M, typename std::enable_if<(N == 3 && M > 3) || (M == 3 && N > 3)>::type* = nullptr>
floatNxM<M, N> transpose(const floatNxM<N, M>& m) { return floatNxM<M, N>(m._vec0, m._vec1, m._vec2); }

inline float1 determinant(const float2x2& m)
{
	return float1(_hlslpp_det_2x2_ps(m._vec));
}

inline float1 determinant(const float3x3& m)
{
	return float1(_hlslpp_det_3x3_ps(m._vec0, m._vec1, m._vec2));
}

inline float1 determinant(const float4x4& m)
{
	return float1(_hlslpp_det_4x4_ps(m._vec0, m._vec1, m._vec2, m._vec3));
}

inline float2x2 inverse(const float2x2& m)
{
	return float2x2(_hlslpp_inv_2x2_ps(m._vec));
}

inline float3x3 inverse(const float3x3& m)
{
	n128 vec0, vec1, vec2;
	_hlslpp_inv_3x3_ps(m._vec0, m._vec1, m._vec2, vec0, vec1, vec2);
	return float3x3(vec0, vec1, vec2);
}

inline float4x4 inverse(const float4x4& m)
{
	n128 vec0, vec1, vec2, vec3;
	_hlslpp_inv_4x4_ps(m._vec0, m._vec1, m._vec2, m._vec3, vec0, vec1, vec2, vec3);
	return float4x4(vec0, vec1, vec2, vec3);
}

inline void store(const float1& v, float* f)
{
	_hlslpp_store1_ps(f + 0, v._vec);
}

inline void store(const float2& v, float* f)
{
	_hlslpp_store2_ps(f, v._vec);
}

inline void store(const float3& v, float* f)
{
	_hlslpp_store3_ps(f, v._vec);
}

inline void store(const float4& v, float* f)
{
	_hlslpp_store4_ps(f, v._vec);
}

inline void store(const float3x3& m, float* f)
{
	_hlslpp_store3x3_ps(f, m._vec0, m._vec1, m._vec2);
}

inline void store(const float4x4& m, float* f)
{
	_hlslpp_store4x4_ps(f, m._vec0, m._vec1, m._vec2, m._vec3);
}