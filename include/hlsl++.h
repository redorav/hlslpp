#pragma once

#if defined(__clang__) || defined(__GNUG__)

	#define hlslpp_inline inline __attribute__((always_inline))

	#define HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
	#define HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END

#elif defined(_MSC_VER)

	#define hlslpp_inline __forceinline

	#define HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN \
	__pragma(warning(push)) \
	__pragma(warning(disable : 4201))

	#define HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END __pragma(warning(pop))

#else

	#error Unrecognized compiler

#endif

#if (__cplusplus >= 201702L) || (_MSVC_LANG >= 201702L)

	#define hlslpp_nodiscard [[nodiscard]]

#else

	#define hlslpp_nodiscard

#endif

#define HLSLPP_SHUFFLE_MASK(X, Y, Z, W)		(((W) << 6) | ((Z) << 4) | ((Y) << 2) | (X))
#define HLSLPP_SHUFFLE_MASK_PD(X, Y)		(((Y) << 1) | (X))

// Create a mask where 1 selects from x, 0 selects from y
#define HLSLPP_BLEND_MASK(X, Y, Z, W)		(~((X) | ((Y) << 1) | ((Z) << 2) | ((W) << 3)) & 0xf)
#define HLSLPP_BLEND_MASK_PD(X, Y)			(~((X) | ((Y) << 1)) & 0x3)

#define HLSLPP_COMPONENT_X(X)				(1 << X)
#define HLSLPP_COMPONENT_XY(X, Y)			((1 << X) | (1 << Y))
#define HLSLPP_COMPONENT_XYZ(X, Y, Z)		((1 << X) | (1 << Y) | (1 << Z))
#define HLSLPP_COMPONENT_XYZW(X, Y, Z, W)	((1 << X) | (1 << Y) | (1 << Z) | (1 << W))

#if defined(__cpp_if_constexpr)

	#define HLSLPP_CONSTEXPR_IF(x) if constexpr(x)

#else

	#if defined(_MSC_VER)
		
		// warning C4127: conditional expression is constant
		// Disable because we always use these in a template context
		// Builds that don't support constexpr optimize them away
		#define HLSLPP_CONSTEXPR_IF(x) \
		__pragma(warning(push)) \
		__pragma(warning(disable : 4127)) \
		if(x) \
		__pragma(warning(pop))

	#else

		#define HLSLPP_CONSTEXPR_IF(x) if(x)

	#endif

#endif

// We try to auto detect any vector libraries available to the system.
// If we don't find any, fall back to scalar.

#if !defined(HLSLPP_ARM) && (defined(_M_ARM) || defined(__arm__) || defined(_M_ARM64) || defined(__aarch64__))

	#define HLSLPP_ARM

#elif !defined(HLSLPP_360) && defined(_XBOX)

	#define HLSLPP_360

#elif !defined(HLSLP_SSE) && (defined(__SSE__) || (_M_IX86_FP > 0) || defined(_M_AMD64) || defined(_M_X64))

	#define HLSLP_SSE

#elif !defined(HLSLPP_SCALAR)

	#define HLSLPP_SCALAR

#endif

#include <cstdint>

#include <cstdio>

#include <type_traits>

#include "hlsl++_bitmask.h"

// Despite the process above, we can still force the library to behave as scalar by defining the
// implementation we want.

#if defined(HLSLPP_SCALAR)

	#include "platforms/hlsl++_scalar.h"

#elif defined(HLSLP_SSE)

	#include "platforms/hlsl++_sse.h"

#elif defined(HLSLPP_ARM)

	#include "platforms/hlsl++_neon.h"

#elif defined(HLSLPP_360)

	#include "platforms/hlsl++_360.h"

#endif

#include "hlsl++_common.h"

#include "hlsl++_vector_float.h"

#include "hlsl++_vector_float8.h"

#include "hlsl++_matrix_float.h"

#include "hlsl++_vector_int.h"

#include "hlsl++_vector_uint.h"

#include "hlsl++_vector_double.h"

#include "hlsl++_quaternion.h"

// Some functions depend on having the knowledge of types that have been defined before.
// In order to break the header dependencies they are all defined here.
#include "hlsl++_dependent.h"