//----------------//
// Integer Vector //
//----------------//

namespace hlslpp
{
	const n128u u4_0x55555555 = _hlslpp_set1_epu32(0x55555555);
	const n128u u4_0x33333333 = _hlslpp_set1_epu32(0x33333333);
	const n128u u4_0x0f0f0f0f = _hlslpp_set1_epu32(0x0f0f0f0f);
	const n128u u4_0x01010101 = _hlslpp_set1_epu32(0x01010101);
	const n128u u4_0x0000003f = _hlslpp_set1_epu32(0x0000003f);
	const n128u u4_0xaaaaaaaa = _hlslpp_set1_epu32(0xaaaaaaaa);
	const n128u u4_0xcccccccc = _hlslpp_set1_epu32(0xcccccccc);
	const n128u u4_0xf0f0f0f0 = _hlslpp_set1_epu32(0xf0f0f0f0);
	const n128u u4_0x00ff00ff = _hlslpp_set1_epu32(0x00ff00ff);
	const n128u u4_0xff00ff00 = _hlslpp_set1_epu32(0xff00ff00);
	const n128u u4_0x0000ffff = _hlslpp_set1_epu32(0x0000ffff);
	const n128u u4_0xffff0000 = _hlslpp_set1_epu32(0xffff0000);

	// https://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer
	hlslpp_inline n128u _hlslpp_countbits_epu32(n128u u)
	{
		u = _hlslpp_sub_epu32(u, _hlslpp_and_si128(_hlslpp_srli_epu32(u, 1), u4_0x55555555));
		u = _hlslpp_add_epu32(_hlslpp_and_si128(u, u4_0x33333333), _hlslpp_and_si128(_hlslpp_srli_epu32(u, 2), u4_0x33333333));
		u = _hlslpp_srli_epu32(_hlslpp_mul_epu32(_hlslpp_and_si128(_hlslpp_add_epu32(u, _hlslpp_srli_epu32(u, 4)), u4_0x0f0f0f0f), u4_0x01010101), 24);
		return u;
	}

	// https://stackoverflow.com/questions/10439242/count-leading-zeroes-in-an-int32
	hlslpp_inline n128u _hlslpp_firstbithigh_epu32(const n128u u)
	{
		n128u r = u;

		// Populate right side with 1s
		r = _hlslpp_or_si128(r, _hlslpp_srli_epu32(r, 1)); // x |= x >> 1
		r = _hlslpp_or_si128(r, _hlslpp_srli_epu32(r, 2)); // x |= x >> 2
		r = _hlslpp_or_si128(r, _hlslpp_srli_epu32(r, 4)); // x |= x >> 4
		r = _hlslpp_or_si128(r, _hlslpp_srli_epu32(r, 8)); // x |= x >> 8
		r = _hlslpp_or_si128(r, _hlslpp_srli_epu32(r, 16)); // x |= x >> 16

		// Count 1s
		r = _hlslpp_countbits_epu32(r);

		// Subtract number of 1s from 32 (maximum number of 1s)
		r = _hlslpp_sub_epu32(_hlslpp_set1_epu32(32), _hlslpp_and_si128(r, u4_0x0000003f));

		// Set a -1 (which is incidentally all 1s) if the input is 0. This matches hlsl behavior
		return _hlslpp_or_si128(r, _hlslpp_cmpeq_epu32(u, _hlslpp_setzero_epu32()));
	}

	// Apply the inverse logic as with the leading zeroes, to count trailing zeroes
	hlslpp_inline n128u _hlslpp_firstbitlow_epu32(n128u u)
	{
		n128u r = u;

		// Populate left side with 1s
		r = _hlslpp_or_si128(r, _hlslpp_slli_epu32(r, 1)); // x |= x << 1
		r = _hlslpp_or_si128(r, _hlslpp_slli_epu32(r, 2)); // x |= x << 2
		r = _hlslpp_or_si128(r, _hlslpp_slli_epu32(r, 4)); // x |= x << 4
		r = _hlslpp_or_si128(r, _hlslpp_slli_epu32(r, 8)); // x |= x << 8
		r = _hlslpp_or_si128(r, _hlslpp_slli_epu32(r, 16)); // x |= x << 16

		// Count 1s (using same method as countbits)
		r = _hlslpp_countbits_epu32(r);

		// Subtract number of 1s from 32 (maximum number of 1s)
		r = _hlslpp_sub_epu32(_hlslpp_set1_epu32(32), _hlslpp_and_si128(r, u4_0x0000003f));

		// Set a -1 (which is incidentally all 1s) if the input is 0. This matches hlsl behavior
		return _hlslpp_or_si128(r, _hlslpp_cmpeq_epu32(u, _hlslpp_setzero_epu32()));
	}

	// https://stackoverflow.com/questions/21619397/reverse-all-bits-in-an-int-and-return-the-int
	hlslpp_inline n128u _hlslpp_reversebits_epu32(n128u u)
	{
		u = _hlslpp_or_si128(_hlslpp_slli_epu32(_hlslpp_and_si128(u, u4_0x55555555), 1), _hlslpp_srli_epu32(_hlslpp_and_si128(u, u4_0xaaaaaaaa), 1));
		u = _hlslpp_or_si128(_hlslpp_slli_epu32(_hlslpp_and_si128(u, u4_0x33333333), 2), _hlslpp_srli_epu32(_hlslpp_and_si128(u, u4_0xcccccccc), 2));
		u = _hlslpp_or_si128(_hlslpp_slli_epu32(_hlslpp_and_si128(u, u4_0x0f0f0f0f), 4), _hlslpp_srli_epu32(_hlslpp_and_si128(u, u4_0xf0f0f0f0), 4));
		u = _hlslpp_or_si128(_hlslpp_slli_epu32(_hlslpp_and_si128(u, u4_0x00ff00ff), 8), _hlslpp_srli_epu32(_hlslpp_and_si128(u, u4_0xff00ff00), 8));
		u = _hlslpp_or_si128(_hlslpp_slli_epu32(_hlslpp_and_si128(u, u4_0x0000ffff), 16), _hlslpp_srli_epu32(_hlslpp_and_si128(u, u4_0xffff0000), 16));
		return u;
	}

	hlslpp_inline n128u _hlslpp_imod_epu32(n128u x, n128u y)
	{
		n128u div = _hlslpp_div_epu32(x, y);
		n128u result = _hlslpp_sub_epu32(x, _hlslpp_mul_epu32(div, y));
		return result;
	}

	template<int X>
	struct hlslpp_nodiscard uswizzle1
	{
		template<int A> friend struct uswizzle1;
	
		// Cast
	
		hlslpp_inline operator uint32_t() const { return u32[X]; }
	
		// Helper
	
		template<int E, int A>
		static hlslpp_inline n128u swizzle(n128u v)
		{
			const int finalMask = (((IdentityMask >> 2 * E) & 3) << 2 * A) | (IdentityMask & ~((3 << 2 * A)));
			return _hlslpp_perm_epi32(v, finalMask);
		}
	
		template<int E, int A>
		hlslpp_inline n128u swizzle() const
		{
			return swizzle<E, A>(vec);
		}
	
		hlslpp_inline uswizzle1& operator = (uint32_t i)
		{
			vec = _hlslpp_blend_epi32(vec, _hlslpp_set1_epu32(i), HLSLPP_COMPONENT_X(X));
			return *this;
		}
	
		// Assignment
	
		template<int A>
		hlslpp_inline uswizzle1& operator = (const uswizzle1<A>& s) // Revise this function. Can I not do with swizzle?
		{
			n128u t = _hlslpp_shuffle_epi32(s.vec, s.vec, HLSLPP_SHUFFLE_MASK(A, A, A, A));
			vec = _hlslpp_blend_epi32(vec, t, HLSLPP_COMPONENT_X(X));
			return *this;
		}
	
		hlslpp_inline uswizzle1& operator = (const uint1& i);
	
	private:
		union
		{
			n128u vec;
			uint32_t u32[4];
		};
	};
	
	template<int X, int Y>
	struct hlslpp_nodiscard uswizzle2
	{
		// Helper

		void staticAsserts()
		{
			static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		static hlslpp_inline n128u blend(n128u x, n128u y)
		{
			return _hlslpp_blend_epi32(x, y, HLSLPP_COMPONENT_XY(X, Y)); // Select based on property mask
		}

		template<int E, int F, int A, int B>
		static hlslpp_inline n128u swizzle(n128u v)
		{
			const int finalMask =
				(((IdentityMask >> 2 * E) & 3) << 2 * A) |
				(((IdentityMask >> 2 * F) & 3) << 2 * B) |
				(IdentityMask & ~((3 << 2 * A) | (3 << 2 * B)));
			return _hlslpp_perm_epi32(v, finalMask);
		}

		template<int E, int F, int A, int B>
		hlslpp_inline n128u swizzle() const
		{
			return swizzle<E, F, A, B>(vec);
		}

		// Assignment

		template<int A, int B>
		hlslpp_inline uswizzle2& operator = (const uswizzle2<A, B>& s)
		{
			staticAsserts();
			vec = blend(vec, s.template swizzle<A, B, X, Y>());
			return *this;
		}

		hlslpp_inline uswizzle2& operator = (const uint2& i);

	private:
		union
		{
			n128u vec;
			uint32_t u32[4];
		};
	};
	
	template<int X, int Y, int Z>
	struct hlslpp_nodiscard uswizzle3
	{
		// Helper

		void staticAsserts()
		{
			static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		static hlslpp_inline n128u blend(n128u x, n128u y)
		{
			return _hlslpp_blend_epi32(x, y, HLSLPP_COMPONENT_XYZ(X, Y, Z)); // Select based on property mask
		}

		template<int E, int F, int G, int A, int B, int C>
		static hlslpp_inline n128u swizzle(n128u v)
		{
			const int finalMask =
				(((IdentityMask >> 2 * E) & 3) << 2 * A) |
				(((IdentityMask >> 2 * F) & 3) << 2 * B) |
				(((IdentityMask >> 2 * G) & 3) << 2 * C) |
				(IdentityMask & ~((3 << 2 * A) | (3 << 2 * B) | (3 << 2 * C)));
			return _hlslpp_perm_epi32(v, finalMask);
		}

		template<int E, int F, int G, int A, int B, int C>
		hlslpp_inline n128u swizzle() const
		{
			return swizzle<E, F, G, A, B, C>(vec);
		}

		// Assignment

		template<int A, int B, int C>
		hlslpp_inline uswizzle3& operator = (const uswizzle3<A, B, C>& s)
		{
			staticAsserts();
			vec = blend(vec, s.template swizzle<A, B, C, X, Y, Z>());
			return *this;
		}

		hlslpp_inline uswizzle3& operator = (const uint3& i);

	private:
		union
		{
			n128u vec;
			uint32_t u32[4];
		};
	};

	template<int X, int Y, int Z, int W>
	struct hlslpp_nodiscard uswizzle4
	{
		// Helper

		void staticAsserts()
		{
			static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		template<int E, int F, int G, int H, int A, int B, int C, int D>
		static hlslpp_inline n128u swizzle(n128u v)
		{
			const int finalMask =
				(((IdentityMask >> 2 * E) & 3) << (2 * A)) |
				(((IdentityMask >> 2 * F) & 3) << (2 * B)) |
				(((IdentityMask >> 2 * G) & 3) << (2 * C)) |
				(((IdentityMask >> 2 * H) & 3) << (2 * D));

			return _hlslpp_perm_epi32(v, finalMask);
		}

		template<int E, int F, int G, int H, int A, int B, int C, int D>
		hlslpp_inline n128u swizzle() const
		{
			return swizzle<E, F, G, H, A, B, C, D>(vec);
		}

		// Assignment

		template<int A, int B, int C, int D>
		hlslpp_inline uswizzle4& operator = (const uswizzle4<A, B, C, D>& s)
		{
			staticAsserts();
			vec = s.template swizzle<A, B, C, D, X, Y, Z, W>();
			return *this;
		}

		hlslpp_inline uswizzle4& operator = (const uint4& i);

	private:
		union
		{
			n128u vec;
			uint32_t u32[4];
		};
	};
	
	struct hlslpp_nodiscard uint1
	{
		hlslpp_inline uint1() {}
		hlslpp_inline uint1(const uint1& i) : vec(i.vec) {}
		explicit hlslpp_inline uint1(n128u vec) : vec(vec) {}

		template<typename T>
		hlslpp_inline uint1(T i, hlslpp_enable_if_number(T)) : vec(_hlslpp_set_epu32((unsigned int)i, 0, 0, 0)) {}

		template<int X> hlslpp_inline uint1(const uswizzle1<X>& s) : vec(s.template swizzle<X, 0>()) {}

		hlslpp_inline operator uint32_t() const { return u32[0]; }

		union
		{
			n128u vec;
			uint32_t u32[4];
			#include "swizzle/hlsl++_vector_uint_x.h"
		};
	};

	struct hlslpp_nodiscard uint2
	{
		// Constructors

		hlslpp_inline uint2() {}
		hlslpp_inline uint2(const uint2& i) : vec(i.vec) {}
		explicit hlslpp_inline uint2(n128u vec) : vec(vec) {}
		explicit hlslpp_inline uint2(const uint1& i) : vec(_hlslpp_perm_xxxx_epi32(i.vec)) {}

		hlslpp_inline uint2(uint32_t i) : vec(_hlslpp_set_epu32(i, i, 0, 0)) {}

		template<typename T1, typename T2>
		hlslpp_inline uint2(T1 i1, T2 i2, hlslpp_enable_if_number_2(T1, T2)) : vec(_hlslpp_set_epi32((unsigned int)i1, (unsigned int)i2, 0, 0)) {}

		hlslpp_inline uint2(const uint1& i1, const uint1& i2) { vec = _hlslpp_blend_epi32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }
		
		template<int X, int Y> hlslpp_inline uint2(const uswizzle2<X, Y>& s) : vec(s.template swizzle<X, Y, 0, 1>()) {}

		union
		{
			n128u vec;
			uint32_t u32[4];
			#include "swizzle/hlsl++_vector_uint_x.h"
			#include "swizzle/hlsl++_vector_uint_y.h"
		};
	};
	
	struct hlslpp_nodiscard uint3
	{
		// Constructors

		hlslpp_inline uint3() {}
		hlslpp_inline uint3(const uint3& i) : vec(i.vec) {}
		explicit hlslpp_inline uint3(n128u vec) : vec(vec) {}

		explicit hlslpp_inline uint3(const uint1& i) : vec(_hlslpp_perm_xxxx_epi32(i.vec)) {}

		hlslpp_inline uint3(uint32_t i) : vec(_hlslpp_set_epu32(i, i, i, 0)) {}

		template<typename T1, typename T2, typename T3>
		hlslpp_inline uint3(T1 i1, T2 i2, T3 i3, hlslpp_enable_if_number_3(T1, T2, T3)) : vec(_hlslpp_set_epi32((unsigned int)i1, (unsigned int)i2, (unsigned int)i3, 0)) {}

		hlslpp_inline uint3(const uint1& i1, const uint1& i2, const uint1& i3) { vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxx_epi32(i1.vec, i3.vec), _hlslpp_perm_xxxx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }

		hlslpp_inline uint3(const uint2& i1, const uint1& i2) { vec = _hlslpp_shuf_xyxx_epi32(i1.vec, i2.vec); }
		hlslpp_inline uint3(const uint1& i1, const uint2& i2) { vec = _hlslpp_blend_epi32(i1.vec, _hlslpp_perm_xxyx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }

		template<int X, int Y, int Z>
		hlslpp_inline uint3(const uswizzle3<X, Y, Z>& s) : vec(s.template swizzle<X, Y, Z, 0, 1, 2>()) {}

		union
		{
			n128u vec;
			uint32_t u32[4];
			#include "swizzle/hlsl++_vector_uint_x.h"
			#include "swizzle/hlsl++_vector_uint_y.h"
			#include "swizzle/hlsl++_vector_uint_z.h"
		};
	};

	struct hlslpp_nodiscard uint4
	{
		hlslpp_inline uint4() {}
		hlslpp_inline uint4(const uint4& i) : vec(i.vec) {}
		explicit hlslpp_inline uint4(n128u vec) : vec(vec) {}

		explicit hlslpp_inline uint4(const uint1& i) : vec(_hlslpp_perm_xxxx_epi32(i.vec)) {}

		hlslpp_inline uint4(uint32_t i) : vec(_hlslpp_set1_epu32(i)) {}

		template<typename T1, typename T2, typename T3, typename T4>
		hlslpp_inline uint4(T1 i1, T2 i2, T3 i3, T4 i4, hlslpp_enable_if_number_4(T1, T2, T3, T4)) : vec(_hlslpp_set_epu32((unsigned int)i1, (unsigned int)i2, (unsigned int)i3, (unsigned int)i4)) {}

		hlslpp_inline uint4(const uint1& i1, const uint1& i2, const uint1& i3, const uint1& i4) { vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxx_epi32(i1.vec, i3.vec), _hlslpp_shuf_xxxx_epi32(i2.vec, i4.vec), HLSLPP_BLEND_MASK(1, 0, 1, 0)); }
		
		hlslpp_inline uint4(const uint2& i1, const uint1& i2, const uint1& i3) { vec = _hlslpp_blend_epi32(_hlslpp_shuf_xyxx_epi32(i1.vec, i2.vec), _hlslpp_perm_xxxx_epi32(i3.vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }
		hlslpp_inline uint4(const uint1& i1, const uint2& i2, const uint1& i3) { vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxx_epi32(i1.vec, i3.vec), _hlslpp_perm_xxyx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 1)); }
		hlslpp_inline uint4(const uint1& i1, const uint1& i2, const uint2& i3) { vec = _hlslpp_blend_epi32(_hlslpp_shuf_xxxy_epi32(i1.vec, i3.vec), _hlslpp_perm_xxxx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }

		hlslpp_inline uint4(const uint2& i1, const uint2& f2) { vec = _hlslpp_shuf_xyxy_epi32(i1.vec, f2.vec); }

		hlslpp_inline uint4(const uint1& i1, const uint3& i2) { vec = _hlslpp_blend_epi32(i1.vec, _hlslpp_perm_xxyz_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 0, 0, 0)); }
		hlslpp_inline uint4(const uint3& i1, const uint1& i2) { vec = _hlslpp_blend_epi32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec), HLSLPP_BLEND_MASK(1, 1, 1, 0)); }

		template<int X, int Y, int Z, int W>
		hlslpp_inline uint4(const uswizzle4<X, Y, Z, W>& s) : vec(s.template swizzle<X, Y, Z, W, 0, 1, 2, 3>()) {}

		hlslpp_inline uint4& operator = (const uint4& i) { vec = i.vec; return *this; }

		union
		{
			n128u vec;
			uint32_t u32[4];
			#include "swizzle/hlsl++_vector_uint_x.h"
			#include "swizzle/hlsl++_vector_uint_y.h"
			#include "swizzle/hlsl++_vector_uint_z.h"
			#include "swizzle/hlsl++_vector_uint_w.h"
		};
	};
	
	// Operators

	hlslpp_inline uint1 operator + (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_add_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator + (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_add_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator + (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_add_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator + (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_add_epu32(i1.vec, i2.vec)); }

	hlslpp_inline uint1 operator - (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_sub_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator - (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_sub_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator - (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_sub_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator - (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_sub_epu32(i1.vec, i2.vec)); }

	hlslpp_inline uint1 operator * (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_mul_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator * (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_mul_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator * (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_mul_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator * (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_mul_epu32(i1.vec, i2.vec)); }

	hlslpp_inline uint1 operator / (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_div_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator / (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_div_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator / (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_div_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator / (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_div_epu32(i1.vec, i2.vec)); }

	//hlslpp_inline uint1 operator % (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_imod_epi32(i1.vec, i2.vec)); }
	//hlslpp_inline uint2 operator % (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_imod_epi32(i1.vec, i2.vec)); }
	//hlslpp_inline uint3 operator % (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_imod_epi32(i1.vec, i2.vec)); }
	//hlslpp_inline uint4 operator % (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_imod_epi32(i1.vec, i2.vec)); }

	// Pre-increment

	hlslpp_inline uint1& operator ++ (uint1& i) { i = i + uint1(1); return i; }
	hlslpp_inline uint2& operator ++ (uint2& i) { i = i + uint2(1); return i; }
	hlslpp_inline uint3& operator ++ (uint3& i) { i = i + uint3(1); return i; }
	hlslpp_inline uint4& operator ++ (uint4& i) { i = i + uint4(1); return i; }

	template<int X> hlslpp_inline uswizzle1<X>& operator ++ (uswizzle1<X>& i) { i = i + uint1(i4_1); return i; }
	template<int X, int Y> hlslpp_inline uswizzle2<X, Y>& operator ++ (uswizzle2<X, Y>& i) { i = i + uint2(i4_1); return i; }
	template<int X, int Y, int Z> hlslpp_inline uswizzle3<X, Y, Z>& operator ++ (uswizzle3<X, Y, Z>& i) { i = i + uint3(i4_1); return i; }
	template<int X, int Y, int Z, int W> hlslpp_inline uswizzle4<X, Y, Z, W>& operator ++ (uswizzle4<X, Y, Z, W>& i) { i = i + uint4(i4_1); return i; }

	hlslpp_inline uint1& operator -- (uint1& i) { i = i - uint1(1); return i; }
	hlslpp_inline uint2& operator -- (uint2& i) { i = i - uint2(1); return i; }
	hlslpp_inline uint3& operator -- (uint3& i) { i = i - uint3(1); return i; }
	hlslpp_inline uint4& operator -- (uint4& i) { i = i - uint4(1); return i; }

	template<int X> hlslpp_inline uswizzle1<X>& operator -- (uswizzle1<X>& i) { i = i - uint1(i4_1); return i; }
	template<int X, int Y> hlslpp_inline uswizzle2<X, Y>& operator -- (uswizzle2<X, Y>& i) { i = i - uint2(i4_1); return i; }
	template<int X, int Y, int Z> hlslpp_inline uswizzle3<X, Y, Z>& operator -- (uswizzle3<X, Y, Z>& i) { i = i - uint3(i4_1); return i; }
	template<int X, int Y, int Z, int W> hlslpp_inline uswizzle4<X, Y, Z, W>& operator -- (uswizzle4<X, Y, Z, W>& i) { i = i - uint4(i4_1); return i; }

	// Post-increment

	hlslpp_inline uint1 operator ++ (uint1& i, int) { uint1 tmp = i; i = i + uint1(1); return tmp; }
	hlslpp_inline uint2 operator ++ (uint2& i, int) { uint2 tmp = i; i = i + uint2(1); return tmp; }
	hlslpp_inline uint3 operator ++ (uint3& i, int) { uint3 tmp = i; i = i + uint3(1); return tmp; }
	hlslpp_inline uint4 operator ++ (uint4& i, int) { uint4 tmp = i; i = i + uint4(1); return tmp; }

	template<int X>
	hlslpp_inline uswizzle1<X> operator ++ (uswizzle1<X>& i, int) { uswizzle1<X> tmp = i; i = i + uint1(i4_1); return tmp; }
	template<int X, int Y>
	hlslpp_inline uswizzle2<X, Y> operator ++ (uswizzle2<X, Y>& i, int) { uswizzle2<X, Y> tmp = i; i = i + uint2(i4_1); return tmp; }
	template<int X, int Y, int Z>
	hlslpp_inline uswizzle3<X, Y, Z> operator ++ (uswizzle3<X, Y, Z>& i, int) { uswizzle3<X, Y, Z> tmp = i; i = i + uint3(i4_1); return tmp; }
	template<int X, int Y, int Z, int W>
	hlslpp_inline uswizzle4<X, Y, Z, W> operator ++ (uswizzle4<X, Y, Z, W>& i, int) { uswizzle4<X, Y, Z, W> tmp = i; i = i + uint4(i4_1); return tmp; }

	hlslpp_inline uint1 operator -- (uint1& i, int) { uint1 tmp = i; i = i - uint1(1); return tmp; }
	hlslpp_inline uint2 operator -- (uint2& i, int) { uint2 tmp = i; i = i - uint2(1); return tmp; }
	hlslpp_inline uint3 operator -- (uint3& i, int) { uint3 tmp = i; i = i - uint3(1); return tmp; }
	hlslpp_inline uint4 operator -- (uint4& i, int) { uint4 tmp = i; i = i - uint4(1); return tmp; }

	template<int X>
	hlslpp_inline uswizzle1<X> operator -- (uswizzle1<X>& i, int) { uswizzle1<X> tmp = i; i = i - uint1(i4_1); return tmp; }
	template<int X, int Y>
	hlslpp_inline uswizzle2<X, Y> operator -- (uswizzle2<X, Y>& i, int) { uswizzle2<X, Y> tmp = i; i = i - uint2(i4_1); return tmp; }
	template<int X, int Y, int Z>
	hlslpp_inline uswizzle3<X, Y, Z> operator -- (uswizzle3<X, Y, Z>& i, int) { uswizzle3<X, Y, Z> tmp = i; i = i - uint3(i4_1); return tmp; }
	template<int X, int Y, int Z, int W>
	hlslpp_inline uswizzle4<X, Y, Z, W> operator -- (uswizzle4<X, Y, Z, W>& i, int) { uswizzle4<X, Y, Z, W> tmp = i; i = i - uint4(i4_1); return tmp; }

	//------------------------------------------------------------------------------------------------------------------------//
	// uint1 and uswizzle1 need special overloads to disambiguate between our operators/functions and built-in float operators //
	// and functions that are part of common headers such as cmath, math.h, algorithm, etc                                    //
	//------------------------------------------------------------------------------------------------------------------------//

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint1) operator + (const uint1& i1, T i2) { return i1 + uint1(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint2) operator + (const uint2& i1, T i2) { return i1 + uint2(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint3) operator + (const uint3& i1, T i2) { return i1 + uint3(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint4) operator + (const uint4& i1, T i2) { return i1 + uint4(i2); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint1) operator + (T i1, const uint1& i2) { return uint1(i1) + i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint2) operator + (T i1, const uint2& i2) { return uint2(i1) + i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint3) operator + (T i1, const uint3& i2) { return uint3(i1) + i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint4) operator + (T i1, const uint4& i2) { return uint4(i1) + i2; }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint1) operator - (const uint1& i1, T i2) { return i1 - uint1(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint2) operator - (const uint2& i1, T i2) { return i1 - uint2(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint3) operator - (const uint3& i1, T i2) { return i1 - uint3(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint4) operator - (const uint4& i1, T i2) { return i1 - uint4(i2); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint1) operator - (T i1, const uint1& i2) { return uint1(i1) - i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint2) operator - (T i1, const uint2& i2) { return uint2(i1) - i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint3) operator - (T i1, const uint3& i2) { return uint3(i1) - i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint4) operator - (T i1, const uint4& i2) { return uint4(i1) - i2; }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint1) operator * (const uint1& i1, T i2) { return i1 * uint1(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint2) operator * (const uint2& i1, T i2) { return i1 * uint2(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint3) operator * (const uint3& i1, T i2) { return i1 * uint3(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint4) operator * (const uint4& i1, T i2) { return i1 * uint4(i2); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint1) operator * (T i1, const uint1& i2) { return uint1(i1) * i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint2) operator * (T i1, const uint2& i2) { return uint2(i1) * i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint3) operator * (T i1, const uint3& i2) { return uint3(i1) * i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint4) operator * (T i1, const uint4& i2) { return uint4(i1) * i2; }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint1) operator / (const uint1& i1, T i2) { return i1 / uint1(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint2) operator / (const uint2& i1, T i2) { return i1 / uint2(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint3) operator / (const uint3& i1, T i2) { return i1 / uint3(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint4) operator / (const uint4& i1, T i2) { return i1 / uint4(i2); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint1) operator / (T i1, const uint1& i2) { return uint1(i1) / i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint2) operator / (T i1, const uint2& i2) { return uint2(i1) / i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint3) operator / (T i1, const uint3& i2) { return uint3(i1) / i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint4) operator / (T i1, const uint4& i2) { return uint4(i1) / i2; }

	template<int X> hlslpp_inline uint1 operator + (const uswizzle1<X>& s, const uint1& i) { return uint1(s) + i; }
	template<int X> hlslpp_inline uint1 operator - (const uswizzle1<X>& s, const uint1& i) { return uint1(s) - i; }
	template<int X> hlslpp_inline uint1 operator * (const uswizzle1<X>& s, const uint1& i) { return uint1(s) * i; }
	template<int X> hlslpp_inline uint1 operator / (const uswizzle1<X>& s, const uint1& i) { return uint1(s) / i; }

	hlslpp_inline uint1& operator += (uint1& i1, const uint1& i2) { i1 = i1 + i2; return i1; }
	hlslpp_inline uint2& operator += (uint2& i1, const uint2& i2) { i1 = i1 + i2; return i1; }
	hlslpp_inline uint3& operator += (uint3& i1, const uint3& i2) { i1 = i1 + i2; return i1; }
	hlslpp_inline uint4& operator += (uint4& i1, const uint4& i2) { i1 = i1 + i2; return i1; }

	template<int X>	hlslpp_inline uswizzle1<X>& operator += (uswizzle1<X>& s, const uint1& i) { s = uint1(s) + i; return s; }
	template<int X>	hlslpp_inline uswizzle1<X>& operator -= (uswizzle1<X>& s, const uint1& i) { s = uint1(s) - i; return s; }
	template<int X>	hlslpp_inline uswizzle1<X>& operator *= (uswizzle1<X>& s, const uint1& i) { s = uint1(s) * i; return s; }
	template<int X>	hlslpp_inline uswizzle1<X>& operator /= (uswizzle1<X>& s, const uint1& i) { s = uint1(s) / i; return s; }

	template<int X, int Y> hlslpp_inline uswizzle2<X, Y>& operator += (uswizzle2<X, Y>& s, const uint2& i) { s = uint2(s) + i; return s; }
	template<int X, int Y> hlslpp_inline uswizzle2<X, Y>& operator -= (uswizzle2<X, Y>& s, const uint2& i) { s = uint2(s) - i; return s; }
	template<int X, int Y> hlslpp_inline uswizzle2<X, Y>& operator *= (uswizzle2<X, Y>& s, const uint2& i) { s = uint2(s) * i; return s; }
	template<int X, int Y> hlslpp_inline uswizzle2<X, Y>& operator /= (uswizzle2<X, Y>& s, const uint2& i) { s = uint2(s) / i; return s; }

	template<int X, int Y, int Z> hlslpp_inline uswizzle3<X, Y, Z>& operator += (uswizzle3<X, Y, Z>& s, const uint3& i) { s = uint3(s) + i; return s; }
	template<int X, int Y, int Z> hlslpp_inline uswizzle3<X, Y, Z>& operator -= (uswizzle3<X, Y, Z>& s, const uint3& i) { s = uint3(s) - i; return s; }
	template<int X, int Y, int Z> hlslpp_inline uswizzle3<X, Y, Z>& operator *= (uswizzle3<X, Y, Z>& s, const uint3& i) { s = uint3(s) * i; return s; }
	template<int X, int Y, int Z> hlslpp_inline uswizzle3<X, Y, Z>& operator /= (uswizzle3<X, Y, Z>& s, const uint3& i) { s = uint3(s) / i; return s; }

	template<int X, int Y, int Z, int W> hlslpp_inline uswizzle4<X, Y, Z, W>& operator += (uswizzle4<X, Y, Z, W>& s, const uint4& i) { s = uint4(s) + i; return s; }
	template<int X, int Y, int Z, int W> hlslpp_inline uswizzle4<X, Y, Z, W>& operator -= (uswizzle4<X, Y, Z, W>& s, const uint4& i) { s = uint4(s) - i; return s; }
	template<int X, int Y, int Z, int W> hlslpp_inline uswizzle4<X, Y, Z, W>& operator *= (uswizzle4<X, Y, Z, W>& s, const uint4& i) { s = uint4(s) * i; return s; }
	template<int X, int Y, int Z, int W> hlslpp_inline uswizzle4<X, Y, Z, W>& operator /= (uswizzle4<X, Y, Z, W>& s, const uint4& i) { s = uint4(s) / i; return s; }

	hlslpp_inline uint1& operator -= (uint1& i1, const uint1& i2) { i1 = i1 - i2; return i1; }
	hlslpp_inline uint2& operator -= (uint2& i1, const uint2& i2) { i1 = i1 - i2; return i1; }
	hlslpp_inline uint3& operator -= (uint3& i1, const uint3& i2) { i1 = i1 - i2; return i1; }
	hlslpp_inline uint4& operator -= (uint4& i1, const uint4& i2) { i1 = i1 - i2; return i1; }

	hlslpp_inline uint1& operator *= (uint1& i1, const uint1& i2) { i1 = i1 * i2; return i1; }
	hlslpp_inline uint2& operator *= (uint2& i1, const uint2& i2) { i1 = i1 * i2; return i1; }
	hlslpp_inline uint3& operator *= (uint3& i1, const uint3& i2) { i1 = i1 * i2; return i1; }
	hlslpp_inline uint4& operator *= (uint4& i1, const uint4& i2) { i1 = i1 * i2; return i1; }

	//hlslpp_inline uint1 operator == (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_cmpeq1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint2 operator == (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_cmpeq1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint3 operator == (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_cmpeq1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint4 operator == (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_cmpeq1_epu32(i1.vec, i2.vec)); }
	//
	//hlslpp_inline uint1 operator != (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_cmpneq1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint2 operator != (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_cmpneq1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint3 operator != (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_cmpneq1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint4 operator != (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_cmpneq1_epu32(i1.vec, i2.vec)); }
	//
	//hlslpp_inline uint1 operator > (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_cmpgt1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint2 operator > (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_cmpgt1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint3 operator > (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_cmpgt1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint4 operator > (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_cmpgt1_epu32(i1.vec, i2.vec)); }

	//hlslpp_inline uint1 operator >= (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_cmpge1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint2 operator >= (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_cmpge1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint3 operator >= (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_cmpge1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint4 operator >= (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_cmpge1_epu32(i1.vec, i2.vec)); }
	//
	//hlslpp_inline uint1 operator < (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_cmplt1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint2 operator < (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_cmplt1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint3 operator < (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_cmplt1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint4 operator < (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_cmplt1_epu32(i1.vec, i2.vec)); }
	//
	//hlslpp_inline uint1 operator <= (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_cmple1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint2 operator <= (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_cmple1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint3 operator <= (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_cmple1_epu32(i1.vec, i2.vec)); }
	//hlslpp_inline uint4 operator <= (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_cmple1_epu32(i1.vec, i2.vec)); }

	// Bitwise

	hlslpp_inline uint1 operator >> (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_srlv_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator >> (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_srlv_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator >> (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_srlv_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator >> (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_srlv_epu32(i1.vec, i2.vec)); }

	hlslpp_inline uint2 operator >> (const uint2& i1, const uint1& i2) { return uint2(_hlslpp_srlv_epu32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline uint3 operator >> (const uint3& i1, const uint1& i2) { return uint3(_hlslpp_srlv_epu32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline uint4 operator >> (const uint4& i1, const uint1& i2) { return uint4(_hlslpp_srlv_epu32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }

	hlslpp_inline uint1 operator << (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_sllv_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator << (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_sllv_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator << (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_sllv_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator << (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_sllv_epu32(i1.vec, i2.vec)); }

	hlslpp_inline uint2 operator << (const uint2& i1, const uint1& i2) { return uint2(_hlslpp_sllv_epu32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline uint3 operator << (const uint3& i1, const uint1& i2) { return uint3(_hlslpp_sllv_epu32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline uint4 operator << (const uint4& i1, const uint1& i2) { return uint4(_hlslpp_sllv_epu32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }

	hlslpp_inline uint1 operator & (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_and_si128(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator & (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_and_si128(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator & (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_and_si128(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator & (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_and_si128(i1.vec, i2.vec)); }

	hlslpp_inline uint2 operator & (const uint2& i1, const uint1& i2) { return uint2(_hlslpp_and_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline uint3 operator & (const uint3& i1, const uint1& i2) { return uint3(_hlslpp_and_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline uint4 operator & (const uint4& i1, const uint1& i2) { return uint4(_hlslpp_and_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }

	hlslpp_inline uint1 operator | (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_or_si128(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator | (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_or_si128(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator | (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_or_si128(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator | (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_or_si128(i1.vec, i2.vec)); }

	hlslpp_inline uint2 operator | (const uint2& i1, const uint1& i2) { return uint2(_hlslpp_or_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline uint3 operator | (const uint3& i1, const uint1& i2) { return uint3(_hlslpp_or_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline uint4 operator | (const uint4& i1, const uint1& i2) { return uint4(_hlslpp_or_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }

	hlslpp_inline uint1 operator ^ (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_xor_si128(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator ^ (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_xor_si128(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator ^ (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_xor_si128(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator ^ (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_xor_si128(i1.vec, i2.vec)); }

	hlslpp_inline uint2 operator ^ (const uint2& i1, const uint1& i2) { return uint2(_hlslpp_xor_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline uint3 operator ^ (const uint3& i1, const uint1& i2) { return uint3(_hlslpp_xor_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline uint4 operator ^ (const uint4& i1, const uint1& i2) { return uint4(_hlslpp_xor_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }

	hlslpp_inline uint1 operator ~ (const uint1& i1) { return uint1(_hlslpp_not_si128(i1.vec)); }
	hlslpp_inline uint2 operator ~ (const uint2& i1) { return uint2(_hlslpp_not_si128(i1.vec)); }
	hlslpp_inline uint3 operator ~ (const uint3& i1) { return uint3(_hlslpp_not_si128(i1.vec)); }
	hlslpp_inline uint4 operator ~ (const uint4& i1) { return uint4(_hlslpp_not_si128(i1.vec)); }

	hlslpp_inline uint1& operator >>= (uint1& i1, const uint1& i2) { i1 = i1 >> i2; return i1; }
	hlslpp_inline uint2& operator >>= (uint2& i1, const uint2& i2) { i1 = i1 >> i2; return i1; }
	hlslpp_inline uint3& operator >>= (uint3& i1, const uint3& i2) { i1 = i1 >> i2; return i1; }
	hlslpp_inline uint4& operator >>= (uint4& i1, const uint4& i2) { i1 = i1 >> i2; return i1; }

	hlslpp_inline uint1& operator <<= (uint1& i1, const uint1& i2) { i1 = i1 << i2; return i1; }
	hlslpp_inline uint2& operator <<= (uint2& i1, const uint2& i2) { i1 = i1 << i2; return i1; }
	hlslpp_inline uint3& operator <<= (uint3& i1, const uint3& i2) { i1 = i1 << i2; return i1; }
	hlslpp_inline uint4& operator <<= (uint4& i1, const uint4& i2) { i1 = i1 << i2; return i1; }

	hlslpp_inline uint1& operator &= (uint1& i1, const uint1& i2) { i1 = i1 & i2; return i1; }
	hlslpp_inline uint2& operator &= (uint2& i1, const uint2& i2) { i1 = i1 & i2; return i1; }
	hlslpp_inline uint3& operator &= (uint3& i1, const uint3& i2) { i1 = i1 & i2; return i1; }
	hlslpp_inline uint4& operator &= (uint4& i1, const uint4& i2) { i1 = i1 & i2; return i1; }

	hlslpp_inline uint1& operator |= (uint1& i1, const uint1& i2) { i1 = i1 | i2; return i1; }
	hlslpp_inline uint2& operator |= (uint2& i1, const uint2& i2) { i1 = i1 | i2; return i1; }
	hlslpp_inline uint3& operator |= (uint3& i1, const uint3& i2) { i1 = i1 | i2; return i1; }
	hlslpp_inline uint4& operator |= (uint4& i1, const uint4& i2) { i1 = i1 | i2; return i1; }

	hlslpp_inline uint1& operator ^= (uint1& i1, const uint1& i2) { i1 = i1 ^ i2; return i1; }
	hlslpp_inline uint2& operator ^= (uint2& i1, const uint2& i2) { i1 = i1 ^ i2; return i1; }
	hlslpp_inline uint3& operator ^= (uint3& i1, const uint3& i2) { i1 = i1 ^ i2; return i1; }
	hlslpp_inline uint4& operator ^= (uint4& i1, const uint4& i2) { i1 = i1 ^ i2; return i1; }

	hlslpp_inline uint1 countbits(const uint1& i) { return uint1(_hlslpp_countbits_epu32(i.vec)); }
	hlslpp_inline uint2 countbits(const uint2& i) { return uint2(_hlslpp_countbits_epu32(i.vec)); }
	hlslpp_inline uint3 countbits(const uint3& i) { return uint3(_hlslpp_countbits_epu32(i.vec)); }
	hlslpp_inline uint4 countbits(const uint4& i) { return uint4(_hlslpp_countbits_epu32(i.vec)); }
	
	hlslpp_inline uint1 firstbithigh(const uint1& i) { return uint1(_hlslpp_firstbithigh_epu32(i.vec)); }
	hlslpp_inline uint2 firstbithigh(const uint2& i) { return uint2(_hlslpp_firstbithigh_epu32(i.vec)); }
	hlslpp_inline uint3 firstbithigh(const uint3& i) { return uint3(_hlslpp_firstbithigh_epu32(i.vec)); }
	hlslpp_inline uint4 firstbithigh(const uint4& i) { return uint4(_hlslpp_firstbithigh_epu32(i.vec)); }
	
	hlslpp_inline uint1 firstbitlow(const uint1& i) { return uint1(_hlslpp_firstbitlow_epu32(i.vec)); }
	hlslpp_inline uint2 firstbitlow(const uint2& i) { return uint2(_hlslpp_firstbitlow_epu32(i.vec)); }
	hlslpp_inline uint3 firstbitlow(const uint3& i) { return uint3(_hlslpp_firstbitlow_epu32(i.vec)); }
	hlslpp_inline uint4 firstbitlow(const uint4& i) { return uint4(_hlslpp_firstbitlow_epu32(i.vec)); }

	hlslpp_inline uint1 min(const uint1& i1, const uint1& i2) { return uint1(_hlslpp_min_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 min(const uint2& i1, const uint2& i2) { return uint2(_hlslpp_min_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 min(const uint3& i1, const uint3& i2) { return uint3(_hlslpp_min_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 min(const uint4& i1, const uint4& i2) { return uint4(_hlslpp_min_epu32(i1.vec, i2.vec)); }

	hlslpp_inline uint1 mad(const uint1& i1, const uint1& i2, const uint1& i3) { return uint1(_hlslpp_madd_epu32(i1.vec, i2.vec, i3.vec)); }
	hlslpp_inline uint2 mad(const uint2& i1, const uint2& i2, const uint2& i3) { return uint2(_hlslpp_madd_epu32(i1.vec, i2.vec, i3.vec)); }
	hlslpp_inline uint3 mad(const uint3& i1, const uint3& i2, const uint3& i3) { return uint3(_hlslpp_madd_epu32(i1.vec, i2.vec, i3.vec)); }
	hlslpp_inline uint4 mad(const uint4& i1, const uint4& i2, const uint4& i3) { return uint4(_hlslpp_madd_epu32(i1.vec, i2.vec, i3.vec)); }

	hlslpp_inline uint1 max(const uint1& i1, const uint1& i2) { return uint1(_hlslpp_max_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 max(const uint2& i1, const uint2& i2) { return uint2(_hlslpp_max_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 max(const uint3& i1, const uint3& i2) { return uint3(_hlslpp_max_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 max(const uint4& i1, const uint4& i2) { return uint4(_hlslpp_max_epu32(i1.vec, i2.vec)); }

	hlslpp_inline uint1 reversebits(const uint1& i) { return uint1(_hlslpp_reversebits_epu32(i.vec)); }
	hlslpp_inline uint2 reversebits(const uint2& i) { return uint2(_hlslpp_reversebits_epu32(i.vec)); }
	hlslpp_inline uint3 reversebits(const uint3& i) { return uint3(_hlslpp_reversebits_epu32(i.vec)); }
	hlslpp_inline uint4 reversebits(const uint4& i) { return uint4(_hlslpp_reversebits_epu32(i.vec)); }

	template<int X>
	uswizzle1<X>& uswizzle1<X>::operator = (const uint1& i)
	{
		vec = _hlslpp_blend_epi32(vec, i.vec, HLSLPP_COMPONENT_X(X)); return *this;
	}

	template<int X, int Y>
	uswizzle2<X, Y>& uswizzle2<X, Y>::operator = (const uint2& i)
	{
		staticAsserts();
		vec = blend(vec, swizzle<0, 1, X, Y>(i.vec));
		return *this;
	}

	template<int X, int Y, int Z>
	uswizzle3<X, Y, Z>& uswizzle3<X, Y, Z>::operator = (const uint3& i)
	{
		staticAsserts();
		vec = blend(vec, swizzle<0, 1, 2, X, Y, Z>(i.vec));
		return *this;
	}

	template<int X, int Y, int Z, int W>
	uswizzle4<X, Y, Z, W>& uswizzle4<X, Y, Z, W>::operator = (const uint4& i)
	{
		staticAsserts();
		vec = swizzle<0, 1, 2, 3, X, Y, Z, W>(i.vec);
		return *this;
	}
}