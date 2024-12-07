#pragma once

// Note: The HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_BEGIN warning behaves differently
// between GCC and Clang. In GCC, we need to apply the warning to the call site, i.e.
// wherever we call the copy constructor. In Clang, we need to apply it to the class
// itself. This means we seem to add the same warning suppression to multiple places,
// where in reality it only applies once per compiler

#if defined(__clang__)

	#define hlslpp_inline inline __attribute__((always_inline))

	#define HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
	#define HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END

	#define HLSLPP_WARNING_POTENTIAL_DIVIDE_BY_0_BEGIN
	#define HLSLPP_WARNING_POTENTIAL_DIVIDE_BY_0_END

	#define HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_BEGIN \
		_Pragma("clang diagnostic push") \
		_Pragma("clang diagnostic ignored \"-Wdeprecated\"")

	#define HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_END \
		_Pragma("clang diagnostic pop")

#elif defined(__GNUG__)

	#define hlslpp_inline inline __attribute__((always_inline))

	#define HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
	#define HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END

	#define HLSLPP_WARNING_POTENTIAL_DIVIDE_BY_0_BEGIN
	#define HLSLPP_WARNING_POTENTIAL_DIVIDE_BY_0_END

	#define HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_BEGIN \
	    _Pragma("GCC diagnostic push") \
		_Pragma("GCC diagnostic ignored \"-Wdeprecated-copy\"")

	#define HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_END \
		_Pragma("GCC diagnostic pop")

#elif defined(_MSC_VER)

	#define hlslpp_inline __forceinline

	#define HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN \
	__pragma(warning(push)) \
	__pragma(warning(disable : 4201))

	#define HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END __pragma(warning(pop))

	#define HLSLPP_WARNING_POTENTIAL_DIVIDE_BY_0_BEGIN \
	__pragma(warning(push)) \
	__pragma(warning(disable : 4723))

	#define HLSLPP_WARNING_POTENTIAL_DIVIDE_BY_0_END __pragma(warning(pop))

	#define HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_BEGIN
	#define HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_END

#else

	#error Unrecognized compiler

#endif

#if (__cplusplus >= 201702L) || (_MSVC_LANG >= 201702L)
	#define hlslpp_nodiscard [[nodiscard]]
#else
	#define hlslpp_nodiscard
#endif

// Versions previous to VS2015 need special attention
#if defined(_MSC_VER) && _MSC_VER < 1900
	#define hlslpp_noexcept
	#define hlslpp_swizzle_start struct {
	#define hlslpp_swizzle_end };

	#define hlslpp_alignas(x) __declspec(align(x))
	#define hlslpp_alignof(T) __alignof(T)

#else
	#define hlslpp_noexcept noexcept
	#define hlslpp_swizzle_start
	#define hlslpp_swizzle_end

	#define hlslpp_alignas(x) alignas(x)
	#define hlslpp_alignof(T) alignof(T)
	
#endif

#if defined(__cpp_user_defined_literals)

	#define HLSLPP_USER_DEFINED_LITERALS

#endif

#if defined(HLSLPP_ASSERT)
#include <assert.h>
#define hlslpp_assert(x) assert(x)
#else
#define hlslpp_assert(x)
#endif

#if defined(HLSLPP_MODULE_DECLARATION)

#define hlslpp_module_export export

#else

#define hlslpp_module_export

#endif

#define HLSLPP_MASK_X 0
#define HLSLPP_MASK_Y 1
#define HLSLPP_MASK_Z 2
#define HLSLPP_MASK_W 3

#define HLSLPP_MASK_A 4
#define HLSLPP_MASK_B 5
#define HLSLPP_MASK_C 6
#define HLSLPP_MASK_D 7

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

	#define hlslpp_constexpr_if(x) if constexpr(x)

#else

	#if defined(_MSC_VER)
		
		// warning C4127: conditional expression is constant
		// Disable because we always use these in a template context
		// Builds that don't support constexpr optimize them away
		#define hlslpp_constexpr_if(x) \
		__pragma(warning(push)) \
		__pragma(warning(disable : 4127)) \
		if(x) \
		__pragma(warning(pop))

	#else

		#define hlslpp_constexpr_if(x) if(x)

	#endif

#endif

// We try to auto detect any vector libraries available to the system.
// If we don't find any, fall back to scalar.

#if !defined(HLSLPP_ARM) && (defined(_M_ARM) || defined(__arm__) || defined(_M_ARM64) || defined(__aarch64__) || defined(_M_ARM64EC))

	#define HLSLPP_ARM

#elif !defined(HLSLPP_360) && defined(_XBOX)

	#define HLSLPP_360

#elif !defined(HLSLPP_SSE) && (defined(__SSE__) || (defined(_M_IX86_FP) && _M_IX86_FP > 0) || defined(_M_AMD64) || defined(_M_X64))

	#define HLSLPP_SSE

#elif !defined(HLSLPP_WASM) && defined(__wasm_simd128__)

	#define HLSLPP_WASM

#elif !defined(HLSLPP_SCALAR)

	#define HLSLPP_SCALAR

#endif

#if defined(HLSLPP_MODULE_DECLARATION)
import "stdint.h";
#else
#include <stdint.h>
#endif

#include "hlsl++/type_traits.h"

#include "hlsl++/bitmask.h"

// Despite the process above, we can still force the library to behave as scalar by defining the
// implementation we want.

#if defined(HLSLPP_SCALAR)

	#include "platforms/scalar.h"

#elif defined(HLSLPP_WASM)

	#include "platforms/wasm.h"

#elif defined(HLSLPP_SSE)

	#include "platforms/sse.h"

#elif defined(HLSLPP_ARM)

	#include "platforms/neon.h"

#elif defined(HLSLPP_360)

	#include "platforms/xbox360.h"

#endif

// There are two main matrix swizzle formats one where upper left is _m00 and the other where it's indicated as _11
// We enable _m00 by default and the other one is left as an option

#if !defined(HLSLPP_ENABLE_MATRIX_SWIZZLE_M00)

	#define HLSLPP_ENABLE_MATRIX_SWIZZLE_M00 1

#endif

#if !defined(HLSLPP_ENABLE_MATRIX_SWIZZLE_11)

	#define HLSLPP_ENABLE_MATRIX_SWIZZLE_11 0

#endif