#pragma once

#include "hlsl++/common.h"

//----------------//
// Integer Vector //
//----------------//

hlslpp_module_export namespace hlslpp
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
}

#include "hlsl++/vector_uint_type.h"

hlslpp_module_export namespace hlslpp
{
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

HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_BEGIN

	// Pre-increment

	hlslpp_inline uint1& operator ++ (uint1& i) { i = i + uint1(1); return i; }
	hlslpp_inline uint2& operator ++ (uint2& i) { i = i + uint2(1); return i; }
	hlslpp_inline uint3& operator ++ (uint3& i) { i = i + uint3(1); return i; }
	hlslpp_inline uint4& operator ++ (uint4& i) { i = i + uint4(1); return i; }

	template<int X> hlslpp_inline uswizzle1<X>& operator ++ (uswizzle1<X>& i) { i = i + uint1(u4_1); return i; }
	template<int X, int Y> hlslpp_inline uswizzle2<X, Y>& operator ++ (uswizzle2<X, Y>& i) { i = i + uint2(u4_1); return i; }
	template<int X, int Y, int Z> hlslpp_inline uswizzle3<X, Y, Z>& operator ++ (uswizzle3<X, Y, Z>& i) { i = i + uint3(u4_1); return i; }
	template<int X, int Y, int Z, int W> hlslpp_inline uswizzle4<X, Y, Z, W>& operator ++ (uswizzle4<X, Y, Z, W>& i) { i = i + uint4(u4_1); return i; }

	hlslpp_inline uint1& operator -- (uint1& i) { i = i - uint1(1); return i; }
	hlslpp_inline uint2& operator -- (uint2& i) { i = i - uint2(1); return i; }
	hlslpp_inline uint3& operator -- (uint3& i) { i = i - uint3(1); return i; }
	hlslpp_inline uint4& operator -- (uint4& i) { i = i - uint4(1); return i; }

	template<int X> hlslpp_inline uswizzle1<X>& operator -- (uswizzle1<X>& i) { i = i - uint1(u4_1); return i; }
	template<int X, int Y> hlslpp_inline uswizzle2<X, Y>& operator -- (uswizzle2<X, Y>& i) { i = i - uint2(u4_1); return i; }
	template<int X, int Y, int Z> hlslpp_inline uswizzle3<X, Y, Z>& operator -- (uswizzle3<X, Y, Z>& i) { i = i - uint3(u4_1); return i; }
	template<int X, int Y, int Z, int W> hlslpp_inline uswizzle4<X, Y, Z, W>& operator -- (uswizzle4<X, Y, Z, W>& i) { i = i - uint4(u4_1); return i; }

	// Post-increment

	hlslpp_inline uint1 operator ++ (uint1& i, int) { uint1 tmp = i; i = i + uint1(1); return tmp; }
	hlslpp_inline uint2 operator ++ (uint2& i, int) { uint2 tmp = i; i = i + uint2(1); return tmp; }
	hlslpp_inline uint3 operator ++ (uint3& i, int) { uint3 tmp = i; i = i + uint3(1); return tmp; }
	hlslpp_inline uint4 operator ++ (uint4& i, int) { uint4 tmp = i; i = i + uint4(1); return tmp; }

	template<int X>
	hlslpp_inline uswizzle1<X> operator ++ (uswizzle1<X>& i, int) { uswizzle1<X> tmp = i; i = i + uint1(u4_1); return tmp; }
	template<int X, int Y>
	hlslpp_inline uswizzle2<X, Y> operator ++ (uswizzle2<X, Y>& i, int) { uswizzle2<X, Y> tmp = i; i = i + uint2(u4_1); return tmp; }
	template<int X, int Y, int Z>
	hlslpp_inline uswizzle3<X, Y, Z> operator ++ (uswizzle3<X, Y, Z>& i, int) { uswizzle3<X, Y, Z> tmp = i; i = i + uint3(u4_1); return tmp; }
	template<int X, int Y, int Z, int W>
	hlslpp_inline uswizzle4<X, Y, Z, W> operator ++ (uswizzle4<X, Y, Z, W>& i, int) { uswizzle4<X, Y, Z, W> tmp = i; i = i + uint4(u4_1); return tmp; }

	hlslpp_inline uint1 operator -- (uint1& i, int) { uint1 tmp = i; i = i - uint1(1); return tmp; }
	hlslpp_inline uint2 operator -- (uint2& i, int) { uint2 tmp = i; i = i - uint2(1); return tmp; }
	hlslpp_inline uint3 operator -- (uint3& i, int) { uint3 tmp = i; i = i - uint3(1); return tmp; }
	hlslpp_inline uint4 operator -- (uint4& i, int) { uint4 tmp = i; i = i - uint4(1); return tmp; }

	template<int X>
	hlslpp_inline uswizzle1<X> operator -- (uswizzle1<X>& i, int) { uswizzle1<X> tmp = i; i = i - uint1(u4_1); return tmp; }
	template<int X, int Y>
	hlslpp_inline uswizzle2<X, Y> operator -- (uswizzle2<X, Y>& i, int) { uswizzle2<X, Y> tmp = i; i = i - uint2(u4_1); return tmp; }
	template<int X, int Y, int Z>
	hlslpp_inline uswizzle3<X, Y, Z> operator -- (uswizzle3<X, Y, Z>& i, int) { uswizzle3<X, Y, Z> tmp = i; i = i - uint3(u4_1); return tmp; }
	template<int X, int Y, int Z, int W>
	hlslpp_inline uswizzle4<X, Y, Z, W> operator -- (uswizzle4<X, Y, Z, W>& i, int) { uswizzle4<X, Y, Z, W> tmp = i; i = i - uint4(u4_1); return tmp; }

HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_END

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

	hlslpp_inline uint1& operator -= (uint1& i1, const uint1& i2) { i1 = i1 - i2; return i1; }
	hlslpp_inline uint2& operator -= (uint2& i1, const uint2& i2) { i1 = i1 - i2; return i1; }
	hlslpp_inline uint3& operator -= (uint3& i1, const uint3& i2) { i1 = i1 - i2; return i1; }
	hlslpp_inline uint4& operator -= (uint4& i1, const uint4& i2) { i1 = i1 - i2; return i1; }

	hlslpp_inline uint1& operator *= (uint1& i1, const uint1& i2) { i1 = i1 * i2; return i1; }
	hlslpp_inline uint2& operator *= (uint2& i1, const uint2& i2) { i1 = i1 * i2; return i1; }
	hlslpp_inline uint3& operator *= (uint3& i1, const uint3& i2) { i1 = i1 * i2; return i1; }
	hlslpp_inline uint4& operator *= (uint4& i1, const uint4& i2) { i1 = i1 * i2; return i1; }

	hlslpp_inline uint1& operator /= (uint1& i1, const uint1& i2) { i1 = i1 / i2; return i1; }
	hlslpp_inline uint2& operator /= (uint2& i1, const uint2& i2) { i1 = i1 / i2; return i1; }
	hlslpp_inline uint3& operator /= (uint3& i1, const uint3& i2) { i1 = i1 / i2; return i1; }
	hlslpp_inline uint4& operator /= (uint4& i1, const uint4& i2) { i1 = i1 / i2; return i1; }

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

	hlslpp_inline uint1 operator == (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_cmpeq1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator == (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_cmpeq1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator == (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_cmpeq1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator == (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_cmpeq1_epu32(i1.vec, i2.vec)); }
	
	hlslpp_inline uint1 operator != (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_cmpneq1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator != (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_cmpneq1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator != (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_cmpneq1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator != (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_cmpneq1_epu32(i1.vec, i2.vec)); }
	
	hlslpp_inline uint1 operator > (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_cmpgt1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator > (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_cmpgt1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator > (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_cmpgt1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator > (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_cmpgt1_epu32(i1.vec, i2.vec)); }

	hlslpp_inline uint1 operator >= (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_cmpge1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator >= (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_cmpge1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator >= (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_cmpge1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator >= (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_cmpge1_epu32(i1.vec, i2.vec)); }
	
	hlslpp_inline uint1 operator < (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_cmplt1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator < (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_cmplt1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator < (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_cmplt1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator < (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_cmplt1_epu32(i1.vec, i2.vec)); }
	
	hlslpp_inline uint1 operator <= (const uint1& i1, const uint1& i2) { return uint1(_hlslpp_cmple1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint2 operator <= (const uint2& i1, const uint2& i2) { return uint2(_hlslpp_cmple1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint3 operator <= (const uint3& i1, const uint3& i2) { return uint3(_hlslpp_cmple1_epu32(i1.vec, i2.vec)); }
	hlslpp_inline uint4 operator <= (const uint4& i1, const uint4& i2) { return uint4(_hlslpp_cmple1_epu32(i1.vec, i2.vec)); }

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

	hlslpp_inline bool all(const uint1& f) { return _hlslpp_all1_epu32(f.vec); }
	hlslpp_inline bool all(const uint2& f) { return _hlslpp_all2_epu32(f.vec); }
	hlslpp_inline bool all(const uint3& f) { return _hlslpp_all3_epu32(f.vec); }
	hlslpp_inline bool all(const uint4& f) { return _hlslpp_all4_epu32(f.vec); }

	hlslpp_inline bool any(const uint1& f) { return _hlslpp_any1_epu32(f.vec); }
	hlslpp_inline bool any(const uint2& f) { return _hlslpp_any2_epu32(f.vec); }
	hlslpp_inline bool any(const uint3& f) { return _hlslpp_any3_epu32(f.vec); }
	hlslpp_inline bool any(const uint4& f) { return _hlslpp_any4_epu32(f.vec); }

	hlslpp_inline uint1 clamp(const uint1& i, const uint1& mini, const uint1& maxi) { return uint1(_hlslpp_clamp_epu32(i.vec, mini.vec, maxi.vec)); }
	hlslpp_inline uint2 clamp(const uint2& i, const uint2& mini, const uint2& maxi) { return uint2(_hlslpp_clamp_epu32(i.vec, mini.vec, maxi.vec)); }
	hlslpp_inline uint3 clamp(const uint3& i, const uint3& mini, const uint3& maxi) { return uint3(_hlslpp_clamp_epu32(i.vec, mini.vec, maxi.vec)); }
	hlslpp_inline uint4 clamp(const uint4& i, const uint4& mini, const uint4& maxi) { return uint4(_hlslpp_clamp_epu32(i.vec, mini.vec, maxi.vec)); }

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

	hlslpp_inline uint1 select(const uint1& condition, const uint1& i1, const uint1& i2) { return uint1(_hlslpp_sel_epu32(i1.vec, i2.vec, _hlslpp_cmpeq_epu32(condition.vec, _hlslpp_setzero_epu32()))); }
	hlslpp_inline uint2 select(const uint2& condition, const uint2& i1, const uint2& i2) { return uint2(_hlslpp_sel_epu32(i1.vec, i2.vec, _hlslpp_cmpeq_epu32(condition.vec, _hlslpp_setzero_epu32()))); }
	hlslpp_inline uint3 select(const uint3& condition, const uint3& i1, const uint3& i2) { return uint3(_hlslpp_sel_epu32(i1.vec, i2.vec, _hlslpp_cmpeq_epu32(condition.vec, _hlslpp_setzero_epu32()))); }
	hlslpp_inline uint4 select(const uint4& condition, const uint4& i1, const uint4& i2) { return uint4(_hlslpp_sel_epu32(i1.vec, i2.vec, _hlslpp_cmpeq_epu32(condition.vec, _hlslpp_setzero_epu32()))); }

	hlslpp_inline uint1 reversebits(const uint1& i) { return uint1(_hlslpp_reversebits_epu32(i.vec)); }
	hlslpp_inline uint2 reversebits(const uint2& i) { return uint2(_hlslpp_reversebits_epu32(i.vec)); }
	hlslpp_inline uint3 reversebits(const uint3& i) { return uint3(_hlslpp_reversebits_epu32(i.vec)); }
	hlslpp_inline uint4 reversebits(const uint4& i) { return uint4(_hlslpp_reversebits_epu32(i.vec)); }

	//--------------------------------------------------------------------------------------------------------------------------
	// Function disambiguation. This typically happens when pulling in math.h, <cmath> or <algorithm>, where functions now live
	// in the global namespace. Due to implicit conversions, we need to clarify to the compiler which functions it needs to use.
	//--------------------------------------------------------------------------------------------------------------------------

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint1) operator == (const uint1& f1, T f2) { return f1 == uint1(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, uint1) operator == (T f1, const uint1& f2) { return uint1(f1) == f2; }

	template<int X, int Y> hlslpp_inline uint1 operator == (const uswizzle1<X>& i1, const uswizzle1<Y>& i2) { return uint1(i1) == uint1(i2); }
	template<int X, int Y> hlslpp_inline uint1 operator != (const uswizzle1<X>& i1, const uswizzle1<Y>& i2) { return uint1(i1) != uint1(i2); }
	template<int X, int Y> hlslpp_inline uint1 operator >  (const uswizzle1<X>& i1, const uswizzle1<Y>& i2) { return uint1(i1) >  uint1(i2); }
	template<int X, int Y> hlslpp_inline uint1 operator >= (const uswizzle1<X>& i1, const uswizzle1<Y>& i2) { return uint1(i1) >= uint1(i2); }
	template<int X, int Y> hlslpp_inline uint1 operator <  (const uswizzle1<X>& i1, const uswizzle1<Y>& i2) { return uint1(i1) <  uint1(i2); }
	template<int X, int Y> hlslpp_inline uint1 operator <= (const uswizzle1<X>& i1, const uswizzle1<Y>& i2) { return uint1(i1) <= uint1(i2); }

	template<int X>
	hlslpp_inline uswizzle1<X>& uswizzle1<X>::operator = (uint32_t i)
	{
		vec = _hlslpp_blend_epi32(vec, _hlslpp_set1_epu32(i), HLSLPP_COMPONENT_X(X));
		return *this;
	}

	template<int X>
	template<int A>
	hlslpp_inline uswizzle1<X>& uswizzle1<X>::operator = (const uswizzle1<A>& s)
	{
		n128u t = _hlslpp_perm_epi32(s.vec, A, A, A, A);
		vec = _hlslpp_blend_epi32(vec, t, HLSLPP_COMPONENT_X(X));
		return *this;
	}

	template<int X>
	hlslpp_inline uswizzle1<X>& uswizzle1<X>::operator = (const uswizzle1<X>& s)
	{
		n128u t = _hlslpp_perm_epi32(s.vec, X, X, X, X);
		vec = _hlslpp_blend_epi32(vec, t, HLSLPP_COMPONENT_X(X));
		return *this;
	}

	template<int X>
	uswizzle1<X>& uswizzle1<X>::operator = (const uint1& i)
	{
		vec = _hlslpp_blend_epi32(vec, hlslpp_uswizzle1_swizzle(0, X, i.vec), HLSLPP_COMPONENT_X(X)); return *this;
	}

	template<int X, int Y>
	template<int A, int B>
	hlslpp_inline uswizzle2<X, Y>& uswizzle2<X, Y>::operator = (const uswizzle2<A, B>& s)
	{
		static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_uswizzle2_blend(vec, hlslpp_uswizzle2_swizzle(A, B, X, Y, s.vec));
		return *this;
	}

	template<int X, int Y>
	hlslpp_inline uswizzle2<X, Y>& uswizzle2<X, Y>::operator = (const uswizzle2<X, Y>& s)
	{
		static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_uswizzle2_blend(vec, hlslpp_uswizzle2_swizzle(X, Y, X, Y, s.vec));
		return *this;
	}

	template<int X, int Y>
	uswizzle2<X, Y>& uswizzle2<X, Y>::operator = (const uint2& i)
	{
		static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_uswizzle2_blend(vec, hlslpp_uswizzle2_swizzle(0, 1, X, Y, i.vec));
		return *this;
	}

	template<int X, int Y, int Z>
	template<int A, int B, int C>
	hlslpp_inline uswizzle3<X, Y, Z>& uswizzle3<X, Y, Z>::operator = (const uswizzle3<A, B, C>& s)
	{
		static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_uswizzle3_blend(vec, hlslpp_uswizzle3_swizzle(A, B, C, X, Y, Z, s.vec));
		return *this;
	}

	template<int X, int Y, int Z>
	hlslpp_inline uswizzle3<X, Y, Z>& uswizzle3<X, Y, Z>::operator = (const uswizzle3<X, Y, Z>& s)
	{
		static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_uswizzle3_blend(vec, hlslpp_uswizzle3_swizzle(X, Y, Z, X, Y, Z, s.vec));
		return *this;
	}

	template<int X, int Y, int Z>
	uswizzle3<X, Y, Z>& uswizzle3<X, Y, Z>::operator = (const uint3& i)
	{
		static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_uswizzle3_blend(vec, hlslpp_uswizzle3_swizzle(0, 1, 2, X, Y, Z, i.vec));
		return *this;
	}

	template<int X, int Y, int Z, int W>
	template<int A, int B, int C, int D>
	hlslpp_inline uswizzle4<X, Y, Z, W>& uswizzle4<X, Y, Z, W>::operator = (const uswizzle4<A, B, C, D>& s)
	{
		static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_uswizzle4_swizzle(A, B, C, D, X, Y, Z, W, s.vec);
		return *this;
	}

	template<int X, int Y, int Z, int W>
	uswizzle4<X, Y, Z, W>& uswizzle4<X, Y, Z, W>::operator = (const uint4& i)
	{
		static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_uswizzle4_swizzle(0, 1, 2, 3, X, Y, Z, W, i.vec);
		return *this;
	}

	hlslpp_inline void store(const uint1& v, uint32_t* i)
	{
		_hlslpp_store1_epu32(i, v.vec);
	}

	hlslpp_inline void store(const uint2& v, uint32_t* i)
	{
		_hlslpp_store2_epu32(i, v.vec);
	}

	hlslpp_inline void store(const uint3& v, uint32_t* i)
	{
		_hlslpp_store3_epu32(i, v.vec);
	}

	hlslpp_inline void store(const uint4& v, uint32_t* i)
	{
		_hlslpp_store4_epu32(i, v.vec);
	}

	hlslpp_inline void load(uint1& v, uint32_t* i)
	{
		_hlslpp_load1_epu32(i, v.vec);
	}

	hlslpp_inline void load(uint2& v, uint32_t* i)
	{
		_hlslpp_load2_epu32(i, v.vec);
	}

	hlslpp_inline void load(uint3& v, uint32_t* i)
	{
		_hlslpp_load3_epu32(i, v.vec);
	}

	hlslpp_inline void load(uint4& v, uint32_t* i)
	{
		_hlslpp_load4_epu32(i, v.vec);
	}
}