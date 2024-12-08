#pragma once

#include "hlsl++/common.h"

HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_BEGIN

namespace hlslpp
{
	template<int X>
	struct hlslpp_nodiscard uswizzle1
	{
		template<int A> friend struct uswizzle1;
	
		// Cast
	
		hlslpp_inline operator uint32_t() const { return u32[X]; }

		// Return the address of this uint32 in the same way we return the value
		hlslpp_inline uint32_t* operator&() { return &u32[X]; }
	
		#define hlslpp_uswizzle1_swizzle(E, A, v) (_hlslpp_perm_epi32(v, A == 0 ? E : 0, A == 1 ? E : 1, A == 2 ? E : 2, A == 3 ? E : 3))

		hlslpp_inline uswizzle1& operator = (uint32_t i);

		template<int A>
		hlslpp_inline uswizzle1& operator = (const uswizzle1<A>& s);

		hlslpp_inline uswizzle1& operator = (const uswizzle1<X>& s);

		hlslpp_inline uswizzle1& operator = (const uint1& i);

		union
		{
			n128u vec;
			uint32_t u32[4];
		};
	};
	
	template<int X, int Y>
	struct hlslpp_nodiscard uswizzle2
	{
		#define hlslpp_uswizzle2_swizzle(E, F, A, B, v) \
		    (_hlslpp_perm_epi32(v, A == 0 ? E : B == 0 ? F : 0, \
		                           A == 1 ? E : B == 1 ? F : 1, \
		                           A == 2 ? E : B == 2 ? F : 2, \
		                           A == 3 ? E : B == 3 ? F : 3))

		// Select based on property mask
		#define hlslpp_uswizzle2_blend(x, y) _hlslpp_blend_epi32(x, y, HLSLPP_COMPONENT_XY(X, Y))

		template<int A, int B>
		hlslpp_inline uswizzle2& operator = (const uswizzle2<A, B>& s);

		hlslpp_inline uswizzle2& operator = (const uswizzle2<X, Y>& s);

		hlslpp_inline uswizzle2& operator = (const uint2& i);

		n128u vec;
	};
	
	template<int X, int Y, int Z>
	struct hlslpp_nodiscard uswizzle3
	{
		#define hlslpp_uswizzle3_swizzle(E, F, G, A, B, C, v) \
		    (_hlslpp_perm_epi32(v, A == 0 ? E : B == 0 ? F : C == 0 ? G : 0, \
		                           A == 1 ? E : B == 1 ? F : C == 1 ? G : 1, \
		                           A == 2 ? E : B == 2 ? F : C == 2 ? G : 2, \
		                           A == 3 ? E : B == 3 ? F : C == 3 ? G : 3))

		// Select based on property mask
		#define hlslpp_uswizzle3_blend(x, y) _hlslpp_blend_epi32(x, y, HLSLPP_COMPONENT_XYZ(X, Y, Z))

		template<int A, int B, int C>
		hlslpp_inline uswizzle3& operator = (const uswizzle3<A, B, C>& s);

		hlslpp_inline uswizzle3& operator = (const uswizzle3<X, Y, Z>& s);

		hlslpp_inline uswizzle3& operator = (const uint3& i);

		n128u vec;
	};

	template<int X, int Y, int Z, int W>
	struct hlslpp_nodiscard uswizzle4
	{
		#define hlslpp_uswizzle4_swizzle(E, F, G, H, A, B, C, D, v) \
		    (_hlslpp_perm_epi32(v, A == 0 ? E : B == 0 ? F : C == 0 ? G : D == 0 ? H : 0, \
		                           A == 1 ? E : B == 1 ? F : C == 1 ? G : D == 1 ? H : 1, \
		                           A == 2 ? E : B == 2 ? F : C == 2 ? G : D == 2 ? H : 2, \
		                           A == 3 ? E : B == 3 ? F : C == 3 ? G : D == 3 ? H : 3))

		template<int A, int B, int C, int D>
		hlslpp_inline uswizzle4& operator = (const uswizzle4<A, B, C, D>& s);

		hlslpp_inline uswizzle4& operator = (const uint4& i);

		n128u vec;
	};
	
	struct hlslpp_nodiscard hlslpp_alignas(16) uint1
	{
		hlslpp_inline uint1() hlslpp_noexcept : vec(_hlslpp_setzero_epu32()) {}
		hlslpp_inline uint1(const uint1& i) hlslpp_noexcept : vec(i.vec) {}
		explicit hlslpp_inline uint1(n128u vec) hlslpp_noexcept : vec(vec) {}

		template<typename T>
		hlslpp_inline uint1(T i, hlslpp_enable_if_number(T)) hlslpp_noexcept : vec(_hlslpp_set_epu32((unsigned int)i, 0, 0, 0)) {}

		template<int X> hlslpp_inline uint1(const uswizzle1<X>& s) hlslpp_noexcept
			: vec(hlslpp_uswizzle1_swizzle(X, 0, s.vec)) {}

		hlslpp_inline uint1(const float1& f) hlslpp_noexcept;

		hlslpp_inline uint1& operator = (const uint1& i) hlslpp_noexcept { vec = i.vec; return *this; }

		hlslpp_inline uint1(uint1&& i) hlslpp_noexcept : vec(i.vec) {}
		hlslpp_inline uint1& operator = (uint1&& i) hlslpp_noexcept { vec = i.vec; return *this; }

		hlslpp_inline operator uint32_t() const { return u32[0]; }

		uint32_t& operator[](int N)
		{
			hlslpp_assert(N == 0);
			return u32[N];
		}

		const uint32_t& operator[](int N) const
		{
			hlslpp_assert(N == 0);
			return u32[N];
		}

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128u vec;
			uint32_t u32[1];
			#include "swizzle/vector_uint_x.h"
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct hlslpp_nodiscard hlslpp_alignas(16) uint2
	{
		// Constructors

		hlslpp_inline uint2() hlslpp_noexcept : vec(_hlslpp_setzero_epu32()) {}
		hlslpp_inline uint2(const uint2& i) hlslpp_noexcept : vec(i.vec) {}
		explicit hlslpp_inline uint2(n128u vec) hlslpp_noexcept : vec(vec) {}
		explicit hlslpp_inline uint2(const uint1& i) hlslpp_noexcept : vec(_hlslpp_perm_xxxx_epi32(i.vec)) {}

		hlslpp_inline uint2(uint32_t i) hlslpp_noexcept : vec(_hlslpp_set_epu32(i, i, 0, 0)) {}

		template<typename T1, typename T2>
		hlslpp_inline uint2(T1 i1, T2 i2, hlslpp_enable_if_number_2(T1, T2)) hlslpp_noexcept : vec(_hlslpp_set_epu32((unsigned int)i1, (unsigned int)i2, 0, 0)) {}

		hlslpp_inline uint2(const uint1& i1, const uint1& i2) hlslpp_noexcept { vec = _hlslpp_blend_epi32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }
		
		template<int X, int Y> hlslpp_inline uint2(const uswizzle2<X, Y>& s) hlslpp_noexcept
			: vec(hlslpp_uswizzle2_swizzle(X, Y, 0, 1, s.vec)) {}

		hlslpp_inline uint2(const float2& f) hlslpp_noexcept;

		hlslpp_inline uint2& operator = (const uint2& i) hlslpp_noexcept { vec = i.vec; return *this; }

		hlslpp_inline uint2(uint2&& i) hlslpp_noexcept : vec(i.vec) {}
		hlslpp_inline uint2& operator = (uint2&& i) hlslpp_noexcept { vec = i.vec; return *this; }

		uint32_t& operator[](int N)
		{
			hlslpp_assert(N >= 0 && N <= 1);
			return u32[N];
		}

		const uint32_t& operator[](int N) const
		{
			hlslpp_assert(N >= 0 && N <= 1);
			return u32[N];
		}

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128u vec;
			uint32_t u32[2];
			#include "swizzle/vector_uint_x.h"
			#include "swizzle/vector_uint_y.h"
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};
	
	struct hlslpp_nodiscard hlslpp_alignas(16) uint3
	{
		// Constructors

		hlslpp_inline uint3() hlslpp_noexcept : vec(_hlslpp_setzero_epu32()) {}
		hlslpp_inline uint3(const uint3& i) hlslpp_noexcept : vec(i.vec) {}
		explicit hlslpp_inline uint3(n128u vec) hlslpp_noexcept : vec(vec) {}

		explicit hlslpp_inline uint3(const uint1& i) hlslpp_noexcept : vec(_hlslpp_perm_xxxx_epi32(i.vec)) {}

		hlslpp_inline uint3(uint32_t i) hlslpp_noexcept : vec(_hlslpp_set_epu32(i, i, i, 0)) {}

		template<typename T1, typename T2, typename T3>
		hlslpp_inline uint3(T1 i1, T2 i2, T3 i3, hlslpp_enable_if_number_3(T1, T2, T3)) hlslpp_noexcept : vec(_hlslpp_set_epu32((unsigned int)i1, (unsigned int)i2, (unsigned int)i3, 0)) {}

		hlslpp_inline uint3(const uint1& i1, const uint1& i2, const uint1& i3) hlslpp_noexcept 
		{ vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxx_epi32(i1.vec, i3.vec), _hlslpp_perm_xxxx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }

		hlslpp_inline uint3(const uint2& i1, const uint1& i2) hlslpp_noexcept { vec = _hlslpp_shuf_xyxx_epi32(i1.vec, i2.vec); }
		hlslpp_inline uint3(const uint1& i1, const uint2& i2) hlslpp_noexcept { vec = _hlslpp_blend_epi32(i1.vec, _hlslpp_perm_xxyx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }

		template<int X, int Y, int Z>
		hlslpp_inline uint3(const uswizzle3<X, Y, Z>& s) hlslpp_noexcept
			: vec(hlslpp_uswizzle3_swizzle(X, Y, Z, 0, 1, 2, s.vec)) {}

		hlslpp_inline uint3(const float3& f) hlslpp_noexcept;

		hlslpp_inline uint3& operator = (const uint3& i) hlslpp_noexcept { vec = i.vec; return *this; }

		hlslpp_inline uint3(uint3&& i) hlslpp_noexcept : vec(i.vec) {}
		hlslpp_inline uint3& operator = (uint3&& i) hlslpp_noexcept { vec = i.vec; return *this; }

		uint32_t& operator[](int N)
		{
			hlslpp_assert(N >= 0 && N <= 2);
			return u32[N];
		}

		const uint32_t& operator[](int N) const
		{
			hlslpp_assert(N >= 0 && N <= 2);
			return u32[N];
		}

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128u vec;
			uint32_t u32[3];
			#include "swizzle/vector_uint_x.h"
			#include "swizzle/vector_uint_y.h"
			#include "swizzle/vector_uint_z.h"
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct hlslpp_nodiscard hlslpp_alignas(16) uint4
	{
		hlslpp_inline uint4() hlslpp_noexcept : vec(_hlslpp_setzero_epu32()) {}
		hlslpp_inline uint4(const uint4& i) hlslpp_noexcept : vec(i.vec) {}
		explicit hlslpp_inline uint4(n128u vec) hlslpp_noexcept : vec(vec) {}

		explicit hlslpp_inline uint4(const uint1& i) hlslpp_noexcept : vec(_hlslpp_perm_xxxx_epi32(i.vec)) {}

		hlslpp_inline uint4(uint32_t i) hlslpp_noexcept : vec(_hlslpp_set1_epu32(i)) {}

		template<typename T1, typename T2, typename T3, typename T4>
		hlslpp_inline uint4(T1 i1, T2 i2, T3 i3, T4 i4, hlslpp_enable_if_number_4(T1, T2, T3, T4)) hlslpp_noexcept : vec(_hlslpp_set_epu32((unsigned int)i1, (unsigned int)i2, (unsigned int)i3, (unsigned int)i4)) {}

		hlslpp_inline uint4(const uint1& i1, const uint1& i2, const uint1& i3, const uint1& i4) hlslpp_noexcept 
		{ vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxx_epi32(i1.vec, i3.vec), _hlslpp_shuf_xxxx_epi32(i2.vec, i4.vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }
		
		hlslpp_inline uint4(const uint2& i1, const uint1& i2, const uint1& i3) hlslpp_noexcept 
		{ vec = _hlslpp_blend_epi32(_hlslpp_shuf_xyxx_epi32(i1.vec, i2.vec), _hlslpp_perm_xxxx_epi32(i3.vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }

		hlslpp_inline uint4(const uint1& i1, const uint2& i2, const uint1& i3) hlslpp_noexcept 
		{ vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxx_epi32(i1.vec, i3.vec), _hlslpp_perm_xxyx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }

		hlslpp_inline uint4(const uint1& i1, const uint1& i2, const uint2& i3) hlslpp_noexcept 
		{ vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxy_epi32(i1.vec, i3.vec), _hlslpp_perm_xxxx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }

		hlslpp_inline uint4(const uint2& i1, const uint2& f2) hlslpp_noexcept { vec = _hlslpp_shuf_xyxy_epi32(i1.vec, f2.vec); }

		hlslpp_inline uint4(const uint1& i1, const uint3& i2) hlslpp_noexcept { vec = _hlslpp_blend_epi32(i1.vec, _hlslpp_perm_xxyz_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 0)); }
		hlslpp_inline uint4(const uint3& i1, const uint1& i2) hlslpp_noexcept { vec = _hlslpp_blend_epi32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }

		template<int X, int Y, int Z, int W>
		hlslpp_inline uint4(const uswizzle4<X, Y, Z, W>& s) hlslpp_noexcept
			: vec(hlslpp_uswizzle4_swizzle(X, Y, Z, W, 0, 1, 2, 3, s.vec)) {}

		hlslpp_inline uint4(const float4& f) hlslpp_noexcept;

		hlslpp_inline uint4& operator = (const uint4& i) hlslpp_noexcept { vec = i.vec; return *this; }

		hlslpp_inline uint4(uint4&& i) hlslpp_noexcept : vec(i.vec) {}
		hlslpp_inline uint4& operator = (uint4&& i) hlslpp_noexcept { vec = i.vec; return *this; }

		uint32_t& operator[](int N)
		{
			hlslpp_assert(N >= 0 && N <= 3);
			return u32[N];
		}

		const uint32_t& operator[](int N) const
		{
			hlslpp_assert(N >= 0 && N <= 3);
			return u32[N];
		}

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128u vec;
			uint32_t u32[4];
			#include "swizzle/vector_uint_x.h"
			#include "swizzle/vector_uint_y.h"
			#include "swizzle/vector_uint_z.h"
			#include "swizzle/vector_uint_w.h"
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	static_assert(hlslpp_alignof(uint4) == 16, "Mismatched alignment");
};

HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_END