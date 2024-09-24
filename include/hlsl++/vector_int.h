#pragma once

#include "hlsl++/common.h"

//----------------//
// Integer Vector //
//----------------//

hlslpp_module_export namespace hlslpp
{
	const n128i i4_0x55555555 = _hlslpp_set1_epi32(0x55555555);
	const n128i i4_0x33333333 = _hlslpp_set1_epi32(0x33333333);
	const n128i i4_0x0f0f0f0f = _hlslpp_set1_epi32(0x0f0f0f0f);
	const n128i i4_0x01010101 = _hlslpp_set1_epi32(0x01010101);
	const n128i i4_0x0000003f = _hlslpp_set1_epi32(0x0000003f);
	const n128i i4_0xaaaaaaaa = _hlslpp_set1_epi32(0xaaaaaaaa);
	const n128i i4_0xcccccccc = _hlslpp_set1_epi32(0xcccccccc);
	const n128i i4_0xf0f0f0f0 = _hlslpp_set1_epi32(0xf0f0f0f0);
	const n128i i4_0x00ff00ff = _hlslpp_set1_epi32(0x00ff00ff);
	const n128i i4_0xff00ff00 = _hlslpp_set1_epi32(0xff00ff00);
	const n128i i4_0x0000ffff = _hlslpp_set1_epi32(0x0000ffff);
	const n128i i4_0xffff0000 = _hlslpp_set1_epi32(0xffff0000);

	// https://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer
	hlslpp_inline n128i _hlslpp_countbits_epi32(n128i i)
	{
		i = _hlslpp_sub_epi32(i, _hlslpp_and_si128(_hlslpp_srli_epi32(i, 1), i4_0x55555555));
		i = _hlslpp_add_epi32(_hlslpp_and_si128(i, i4_0x33333333), _hlslpp_and_si128(_hlslpp_srli_epi32(i, 2), i4_0x33333333));
		i = _hlslpp_srli_epi32(_hlslpp_mul_epi32(_hlslpp_and_si128(_hlslpp_add_epi32(i, _hlslpp_srli_epi32(i, 4)), i4_0x0f0f0f0f), i4_0x01010101), 24);
		return i;
	}

	// https://stackoverflow.com/questions/10439242/count-leading-zeroes-in-an-int32
	hlslpp_inline n128i _hlslpp_firstbithigh_epi32(const n128i i)
	{
		n128i r = i;

		// Populate right side with 1s
		r = _hlslpp_or_si128(r, _hlslpp_srli_epi32(r,  1)); // x |= x >> 1
		r = _hlslpp_or_si128(r, _hlslpp_srli_epi32(r,  2)); // x |= x >> 2
		r = _hlslpp_or_si128(r, _hlslpp_srli_epi32(r,  4)); // x |= x >> 4
		r = _hlslpp_or_si128(r, _hlslpp_srli_epi32(r,  8)); // x |= x >> 8
		r = _hlslpp_or_si128(r, _hlslpp_srli_epi32(r, 16)); // x |= x >> 16
		
		// Count 1s
		r = _hlslpp_countbits_epi32(r);

		// Subtract number of 1s from 32 (maximum number of 1s)
		r = _hlslpp_sub_epi32(_hlslpp_set1_epi32(32), _hlslpp_and_si128(r, i4_0x0000003f));

		// Set a -1 (which is incidentally all 1s) if the input is 0. This matches hlsl behavior
		return _hlslpp_or_si128(r, _hlslpp_cmpeq_epi32(i, _hlslpp_setzero_epi32()));
	}

	// Apply the inverse logic as with the leading zeroes, to count trailing zeroes
	hlslpp_inline n128i _hlslpp_firstbitlow_epi32(n128i i)
	{
		n128i r = i;
		
		// Populate left side with 1s
		r = _hlslpp_or_si128(r, _hlslpp_slli_epi32(r,  1)); // x |= x << 1
		r = _hlslpp_or_si128(r, _hlslpp_slli_epi32(r,  2)); // x |= x << 2
		r = _hlslpp_or_si128(r, _hlslpp_slli_epi32(r,  4)); // x |= x << 4
		r = _hlslpp_or_si128(r, _hlslpp_slli_epi32(r,  8)); // x |= x << 8
		r = _hlslpp_or_si128(r, _hlslpp_slli_epi32(r, 16)); // x |= x << 16

		// Count 1s (using same method as countbits)
		r = _hlslpp_countbits_epi32(r);

		// Subtract number of 1s from 32 (maximum number of 1s)
		r = _hlslpp_sub_epi32(_hlslpp_set1_epi32(32), _hlslpp_and_si128(r, i4_0x0000003f));

		// Set a -1 (which is incidentally all 1s) if the input is 0. This matches hlsl behavior
		return _hlslpp_or_si128(r, _hlslpp_cmpeq_epi32(i, _hlslpp_setzero_epi32()));
	}

	// https://stackoverflow.com/questions/21619397/reverse-all-bits-in-an-int-and-return-the-int
	hlslpp_inline n128i _hlslpp_reversebits_epi32(n128i i)
	{
		i = _hlslpp_or_si128(_hlslpp_slli_epi32(_hlslpp_and_si128(i, i4_0x55555555), 1), _hlslpp_srli_epi32(_hlslpp_and_si128(i, i4_0xaaaaaaaa), 1));
		i = _hlslpp_or_si128(_hlslpp_slli_epi32(_hlslpp_and_si128(i, i4_0x33333333), 2), _hlslpp_srli_epi32(_hlslpp_and_si128(i, i4_0xcccccccc), 2));
		i = _hlslpp_or_si128(_hlslpp_slli_epi32(_hlslpp_and_si128(i, i4_0x0f0f0f0f), 4), _hlslpp_srli_epi32(_hlslpp_and_si128(i, i4_0xf0f0f0f0), 4));
		i = _hlslpp_or_si128(_hlslpp_slli_epi32(_hlslpp_and_si128(i, i4_0x00ff00ff), 8), _hlslpp_srli_epi32(_hlslpp_and_si128(i, i4_0xff00ff00), 8));
		i = _hlslpp_or_si128(_hlslpp_slli_epi32(_hlslpp_and_si128(i, i4_0x0000ffff), 16), _hlslpp_srli_epi32(_hlslpp_and_si128(i, i4_0xffff0000), 16));
		return i;
	}
}

#include "hlsl++/vector_int_type.h"

hlslpp_module_export namespace hlslpp
{
	// Operators

	hlslpp_inline int1 operator + (const int1& i1, const int1& i2) { return int1(_hlslpp_add_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator + (const int2& i1, const int2& i2) { return int2(_hlslpp_add_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator + (const int3& i1, const int3& i2) { return int3(_hlslpp_add_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator + (const int4& i1, const int4& i2) { return int4(_hlslpp_add_epi32(i1.vec, i2.vec)); }

	hlslpp_inline int1 operator - (const int1& i1, const int1& i2) { return int1(_hlslpp_sub_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator - (const int2& i1, const int2& i2) { return int2(_hlslpp_sub_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator - (const int3& i1, const int3& i2) { return int3(_hlslpp_sub_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator - (const int4& i1, const int4& i2) { return int4(_hlslpp_sub_epi32(i1.vec, i2.vec)); }

	hlslpp_inline int1 operator * (const int1& i1, const int1& i2) { return int1(_hlslpp_mul_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator * (const int2& i1, const int2& i2) { return int2(_hlslpp_mul_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator * (const int3& i1, const int3& i2) { return int3(_hlslpp_mul_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator * (const int4& i1, const int4& i2) { return int4(_hlslpp_mul_epi32(i1.vec, i2.vec)); }

	hlslpp_inline int1 operator / (const int1& i1, const int1& i2) { return int1(_hlslpp_div_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator / (const int2& i1, const int2& i2) { return int2(_hlslpp_div_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator / (const int3& i1, const int3& i2) { return int3(_hlslpp_div_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator / (const int4& i1, const int4& i2) { return int4(_hlslpp_div_epi32(i1.vec, i2.vec)); }

HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_BEGIN

	// Pre-increment

	hlslpp_inline int1& operator ++ (int1& i) { i = i + int1(i4_1); return i; }
	hlslpp_inline int2& operator ++ (int2& i) { i = i + int2(i4_1); return i; }
	hlslpp_inline int3& operator ++ (int3& i) { i = i + int3(i4_1); return i; }
	hlslpp_inline int4& operator ++ (int4& i) { i = i + int4(i4_1); return i; }

	template<int X> hlslpp_inline iswizzle1<X>& operator ++ (iswizzle1<X>& i) { i = i + int1(i4_1); return i; }
	template<int X, int Y> hlslpp_inline iswizzle2<X, Y>& operator ++ (iswizzle2<X, Y>& i) { i = i + int2(i4_1); return i; }
	template<int X, int Y, int Z> hlslpp_inline iswizzle3<X, Y, Z>& operator ++ (iswizzle3<X, Y, Z>& i) { i = i + int3(i4_1); return i; }
	template<int X, int Y, int Z, int W> hlslpp_inline iswizzle4<X, Y, Z, W>& operator ++ (iswizzle4<X, Y, Z, W>& i) { i = i + int4(i4_1); return i; }

	hlslpp_inline int1& operator -- (int1& i) { i = i - int1(i4_1); return i; }
	hlslpp_inline int2& operator -- (int2& i) { i = i - int2(i4_1); return i; }
	hlslpp_inline int3& operator -- (int3& i) { i = i - int3(i4_1); return i; }
	hlslpp_inline int4& operator -- (int4& i) { i = i - int4(i4_1); return i; }

	template<int X> hlslpp_inline iswizzle1<X>& operator -- (iswizzle1<X>& i) { i = i - int1(i4_1); return i; }
	template<int X, int Y> hlslpp_inline iswizzle2<X, Y>& operator -- (iswizzle2<X, Y>& i) { i = i - int2(i4_1); return i; }
	template<int X, int Y, int Z> hlslpp_inline iswizzle3<X, Y, Z>& operator -- (iswizzle3<X, Y, Z>& i) { i = i - int3(i4_1); return i; }
	template<int X, int Y, int Z, int W> hlslpp_inline iswizzle4<X, Y, Z, W>& operator -- (iswizzle4<X, Y, Z, W>& i) { i = i - int4(i4_1); return i; }

	// Post-increment

	hlslpp_inline int1 operator ++ (int1& i, int) { int1 tmp = i; i = i + int1(i4_1); return tmp; }
	hlslpp_inline int2 operator ++ (int2& i, int) { int2 tmp = i; i = i + int2(i4_1); return tmp; }
	hlslpp_inline int3 operator ++ (int3& i, int) { int3 tmp = i; i = i + int3(i4_1); return tmp; }
	hlslpp_inline int4 operator ++ (int4& i, int) { int4 tmp = i; i = i + int4(i4_1); return tmp; }

	template<int X>
	hlslpp_inline iswizzle1<X> operator ++ (iswizzle1<X>& i, int) { iswizzle1<X> tmp = i; i = i + int1(i4_1); return tmp; }
	template<int X, int Y>
	hlslpp_inline iswizzle2<X, Y> operator ++ (iswizzle2<X, Y>& i, int) { iswizzle2<X, Y> tmp = i; i = i + int2(i4_1); return tmp; }
	template<int X, int Y, int Z>
	hlslpp_inline iswizzle3<X, Y, Z> operator ++ (iswizzle3<X, Y, Z>& i, int) { iswizzle3<X, Y, Z> tmp = i; i = i + int3(i4_1); return tmp; }
	template<int X, int Y, int Z, int W>
	hlslpp_inline iswizzle4<X, Y, Z, W> operator ++ (iswizzle4<X, Y, Z, W>& i, int) { iswizzle4<X, Y, Z, W> tmp = i; i = i + int4(i4_1); return tmp; }

	hlslpp_inline int1 operator -- (int1& i, int) { int1 tmp = i; i = i - int1(i4_1); return tmp; }
	hlslpp_inline int2 operator -- (int2& i, int) { int2 tmp = i; i = i - int2(i4_1); return tmp; }
	hlslpp_inline int3 operator -- (int3& i, int) { int3 tmp = i; i = i - int3(i4_1); return tmp; }
	hlslpp_inline int4 operator -- (int4& i, int) { int4 tmp = i; i = i - int4(i4_1); return tmp; }

	template<int X>
	hlslpp_inline iswizzle1<X> operator -- (iswizzle1<X>& i, int) { iswizzle1<X> tmp = i; i = i - int1(i4_1); return tmp; }
	template<int X, int Y>
	hlslpp_inline iswizzle2<X, Y> operator -- (iswizzle2<X, Y>& i, int) { iswizzle2<X, Y> tmp = i; i = i - int2(i4_1); return tmp; }
	template<int X, int Y, int Z>
	hlslpp_inline iswizzle3<X, Y, Z> operator -- (iswizzle3<X, Y, Z>& i, int) { iswizzle3<X, Y, Z> tmp = i; i = i - int3(i4_1); return tmp; }
	template<int X, int Y, int Z, int W>
	hlslpp_inline iswizzle4<X, Y, Z, W> operator -- (iswizzle4<X, Y, Z, W>& i, int) { iswizzle4<X, Y, Z, W> tmp = i; i = i - int4(i4_1); return tmp; }

HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_END

	//------------------------------------------------------------------------------------------------------------------------//
	// int1 and iswizzle1 need special overloads to disambiguate between our operators/functions and built-in float operators //
	// and functions that are part of common headers such as cmath, math.h, algorithm, etc                                    //
	//------------------------------------------------------------------------------------------------------------------------//

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int1) operator + (const int1& i1, T i2) { return i1 + int1(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int2) operator + (const int2& i1, T i2) { return i1 + int2(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int3) operator + (const int3& i1, T i2) { return i1 + int3(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int4) operator + (const int4& i1, T i2) { return i1 + int4(i2); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int1) operator + (T i1, const int1& i2) { return int1(i1) + i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int2) operator + (T i1, const int2& i2) { return int2(i1) + i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int3) operator + (T i1, const int3& i2) { return int3(i1) + i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int4) operator + (T i1, const int4& i2) { return int4(i1) + i2; }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int1) operator - (const int1& i1, T i2) { return i1 - int1(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int2) operator - (const int2& i1, T i2) { return i1 - int2(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int3) operator - (const int3& i1, T i2) { return i1 - int3(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int4) operator - (const int4& i1, T i2) { return i1 - int4(i2); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int1) operator - (T i1, const int1& i2) { return int1(i1) - i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int2) operator - (T i1, const int2& i2) { return int2(i1) - i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int3) operator - (T i1, const int3& i2) { return int3(i1) - i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int4) operator - (T i1, const int4& i2) { return int4(i1) - i2; }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int1) operator * (const int1& i1, T i2) { return i1 * int1(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int2) operator * (const int2& i1, T i2) { return i1 * int2(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int3) operator * (const int3& i1, T i2) { return i1 * int3(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int4) operator * (const int4& i1, T i2) { return i1 * int4(i2); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int1) operator * (T i1, const int1& i2) { return int1(i1) * i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int2) operator * (T i1, const int2& i2) { return int2(i1) * i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int3) operator * (T i1, const int3& i2) { return int3(i1) * i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int4) operator * (T i1, const int4& i2) { return int4(i1) * i2; }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int1) operator / (const int1& i1, T i2) { return i1 / int1(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int2) operator / (const int2& i1, T i2) { return i1 / int2(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int3) operator / (const int3& i1, T i2) { return i1 / int3(i2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int4) operator / (const int4& i1, T i2) { return i1 / int4(i2); }

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int1) operator / (T i1, const int1& i2) { return int1(i1) / i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int2) operator / (T i1, const int2& i2) { return int2(i1) / i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int3) operator / (T i1, const int3& i2) { return int3(i1) / i2; }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int4) operator / (T i1, const int4& i2) { return int4(i1) / i2; }

	template<int X> hlslpp_inline int1 operator + (const iswizzle1<X>& s, const int1& i) { return int1(s) + i; }
	template<int X> hlslpp_inline int1 operator - (const iswizzle1<X>& s, const int1& i) { return int1(s) - i; }
	template<int X> hlslpp_inline int1 operator * (const iswizzle1<X>& s, const int1& i) { return int1(s) * i; }
	template<int X> hlslpp_inline int1 operator / (const iswizzle1<X>& s, const int1& i) { return int1(s) / i; }

	hlslpp_inline int1 operator - (const int1& i) { return int1(_hlslpp_neg_epi32(i.vec)); }
	hlslpp_inline int2 operator - (const int2& i) { return int2(_hlslpp_neg_epi32(i.vec)); }
	hlslpp_inline int3 operator - (const int3& i) { return int3(_hlslpp_neg_epi32(i.vec)); }
	hlslpp_inline int4 operator - (const int4& i) { return int4(_hlslpp_neg_epi32(i.vec)); }

	hlslpp_inline int1& operator += (int1& i1, const int1& i2) { i1 = i1 + i2; return i1; }
	hlslpp_inline int2& operator += (int2& i1, const int2& i2) { i1 = i1 + i2; return i1; }
	hlslpp_inline int3& operator += (int3& i1, const int3& i2) { i1 = i1 + i2; return i1; }
	hlslpp_inline int4& operator += (int4& i1, const int4& i2) { i1 = i1 + i2; return i1; }

	hlslpp_inline int1& operator -= (int1& i1, const int1& i2) { i1 = i1 - i2; return i1; }
	hlslpp_inline int2& operator -= (int2& i1, const int2& i2) { i1 = i1 - i2; return i1; }
	hlslpp_inline int3& operator -= (int3& i1, const int3& i2) { i1 = i1 - i2; return i1; }
	hlslpp_inline int4& operator -= (int4& i1, const int4& i2) { i1 = i1 - i2; return i1; }

	hlslpp_inline int1& operator *= (int1& i1, const int1& i2) { i1 = i1 * i2; return i1; }
	hlslpp_inline int2& operator *= (int2& i1, const int2& i2) { i1 = i1 * i2; return i1; }
	hlslpp_inline int3& operator *= (int3& i1, const int3& i2) { i1 = i1 * i2; return i1; }
	hlslpp_inline int4& operator *= (int4& i1, const int4& i2) { i1 = i1 * i2; return i1; }

	hlslpp_inline int1& operator /= (int1& i1, const int1& i2) { i1 = i1 / i2; return i1; }
	hlslpp_inline int2& operator /= (int2& i1, const int2& i2) { i1 = i1 / i2; return i1; }
	hlslpp_inline int3& operator /= (int3& i1, const int3& i2) { i1 = i1 / i2; return i1; }
	hlslpp_inline int4& operator /= (int4& i1, const int4& i2) { i1 = i1 / i2; return i1; }

	template<int X>	hlslpp_inline iswizzle1<X>& operator += (iswizzle1<X>& s, const int1& i) { s = int1(s) + i; return s; }
	template<int X>	hlslpp_inline iswizzle1<X>& operator -= (iswizzle1<X>& s, const int1& i) { s = int1(s) - i; return s; }
	template<int X>	hlslpp_inline iswizzle1<X>& operator *= (iswizzle1<X>& s, const int1& i) { s = int1(s) * i; return s; }
	template<int X>	hlslpp_inline iswizzle1<X>& operator /= (iswizzle1<X>& s, const int1& i) { s = int1(s) / i; return s; }

	template<int X, int Y> hlslpp_inline iswizzle2<X, Y>& operator += (iswizzle2<X, Y>& s, const int2& i) { s = int2(s) + i; return s; }
	template<int X, int Y> hlslpp_inline iswizzle2<X, Y>& operator -= (iswizzle2<X, Y>& s, const int2& i) { s = int2(s) - i; return s; }
	template<int X, int Y> hlslpp_inline iswizzle2<X, Y>& operator *= (iswizzle2<X, Y>& s, const int2& i) { s = int2(s) * i; return s; }
	template<int X, int Y> hlslpp_inline iswizzle2<X, Y>& operator /= (iswizzle2<X, Y>& s, const int2& i) { s = int2(s) / i; return s; }

	template<int X, int Y, int Z> hlslpp_inline iswizzle3<X, Y, Z>& operator += (iswizzle3<X, Y, Z>& s, const int3& i) { s = int3(s) + i; return s; }
	template<int X, int Y, int Z> hlslpp_inline iswizzle3<X, Y, Z>& operator -= (iswizzle3<X, Y, Z>& s, const int3& i) { s = int3(s) - i; return s; }
	template<int X, int Y, int Z> hlslpp_inline iswizzle3<X, Y, Z>& operator *= (iswizzle3<X, Y, Z>& s, const int3& i) { s = int3(s) * i; return s; }
	template<int X, int Y, int Z> hlslpp_inline iswizzle3<X, Y, Z>& operator /= (iswizzle3<X, Y, Z>& s, const int3& i) { s = int3(s) / i; return s; }

	template<int X, int Y, int Z, int W> hlslpp_inline iswizzle4<X, Y, Z, W>& operator += (iswizzle4<X, Y, Z, W>& s, const int4& i) { s = int4(s) + i; return s; }
	template<int X, int Y, int Z, int W> hlslpp_inline iswizzle4<X, Y, Z, W>& operator -= (iswizzle4<X, Y, Z, W>& s, const int4& i) { s = int4(s) - i; return s; }
	template<int X, int Y, int Z, int W> hlslpp_inline iswizzle4<X, Y, Z, W>& operator *= (iswizzle4<X, Y, Z, W>& s, const int4& i) { s = int4(s) * i; return s; }
	template<int X, int Y, int Z, int W> hlslpp_inline iswizzle4<X, Y, Z, W>& operator /= (iswizzle4<X, Y, Z, W>& s, const int4& i) { s = int4(s) / i; return s; }

	hlslpp_inline int1 operator == (const int1& i1, const int1& i2) { return int1(_hlslpp_cmpeq1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator == (const int2& i1, const int2& i2) { return int2(_hlslpp_cmpeq1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator == (const int3& i1, const int3& i2) { return int3(_hlslpp_cmpeq1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator == (const int4& i1, const int4& i2) { return int4(_hlslpp_cmpeq1_epi32(i1.vec, i2.vec)); }

	hlslpp_inline int1 operator != (const int1& i1, const int1& i2) { return int1(_hlslpp_cmpneq1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator != (const int2& i1, const int2& i2) { return int2(_hlslpp_cmpneq1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator != (const int3& i1, const int3& i2) { return int3(_hlslpp_cmpneq1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator != (const int4& i1, const int4& i2) { return int4(_hlslpp_cmpneq1_epi32(i1.vec, i2.vec)); }

	hlslpp_inline int1 operator > (const int1& i1, const int1& i2) { return int1(_hlslpp_cmpgt1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator > (const int2& i1, const int2& i2) { return int2(_hlslpp_cmpgt1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator > (const int3& i1, const int3& i2) { return int3(_hlslpp_cmpgt1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator > (const int4& i1, const int4& i2) { return int4(_hlslpp_cmpgt1_epi32(i1.vec, i2.vec)); }

	hlslpp_inline int1 operator >= (const int1& i1, const int1& i2) { return int1(_hlslpp_cmpge1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator >= (const int2& i1, const int2& i2) { return int2(_hlslpp_cmpge1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator >= (const int3& i1, const int3& i2) { return int3(_hlslpp_cmpge1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator >= (const int4& i1, const int4& i2) { return int4(_hlslpp_cmpge1_epi32(i1.vec, i2.vec)); }

	hlslpp_inline int1 operator < (const int1& i1, const int1& i2) { return int1(_hlslpp_cmplt1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator < (const int2& i1, const int2& i2) { return int2(_hlslpp_cmplt1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator < (const int3& i1, const int3& i2) { return int3(_hlslpp_cmplt1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator < (const int4& i1, const int4& i2) { return int4(_hlslpp_cmplt1_epi32(i1.vec, i2.vec)); }

	hlslpp_inline int1 operator <= (const int1& i1, const int1& i2) { return int1(_hlslpp_cmple1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator <= (const int2& i1, const int2& i2) { return int2(_hlslpp_cmple1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator <= (const int3& i1, const int3& i2) { return int3(_hlslpp_cmple1_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator <= (const int4& i1, const int4& i2) { return int4(_hlslpp_cmple1_epi32(i1.vec, i2.vec)); }

	// Bitwise

	hlslpp_inline int1 operator >> (const int1& i1, const int1& i2) { return int1(_hlslpp_srlv_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator >> (const int2& i1, const int2& i2) { return int2(_hlslpp_srlv_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator >> (const int3& i1, const int3& i2) { return int3(_hlslpp_srlv_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator >> (const int4& i1, const int4& i2) { return int4(_hlslpp_srlv_epi32(i1.vec, i2.vec)); }

	hlslpp_inline int2 operator >> (const int2& i1, const int1& i2) { return int2(_hlslpp_srlv_epi32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline int3 operator >> (const int3& i1, const int1& i2) { return int3(_hlslpp_srlv_epi32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline int4 operator >> (const int4& i1, const int1& i2) { return int4(_hlslpp_srlv_epi32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }

	hlslpp_inline int1 operator << (const int1& i1, const int1& i2) { return int1(_hlslpp_sllv_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator << (const int2& i1, const int2& i2) { return int2(_hlslpp_sllv_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator << (const int3& i1, const int3& i2) { return int3(_hlslpp_sllv_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator << (const int4& i1, const int4& i2) { return int4(_hlslpp_sllv_epi32(i1.vec, i2.vec)); }

	hlslpp_inline int2 operator << (const int2& i1, const int1& i2) { return int2(_hlslpp_sllv_epi32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline int3 operator << (const int3& i1, const int1& i2) { return int3(_hlslpp_sllv_epi32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline int4 operator << (const int4& i1, const int1& i2) { return int4(_hlslpp_sllv_epi32(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }

	hlslpp_inline int1 operator & (const int1& i1, const int1& i2) { return int1(_hlslpp_and_si128(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator & (const int2& i1, const int2& i2) { return int2(_hlslpp_and_si128(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator & (const int3& i1, const int3& i2) { return int3(_hlslpp_and_si128(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator & (const int4& i1, const int4& i2) { return int4(_hlslpp_and_si128(i1.vec, i2.vec)); }

	hlslpp_inline int2 operator & (const int2& i1, const int1& i2) { return int2(_hlslpp_and_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline int3 operator & (const int3& i1, const int1& i2) { return int3(_hlslpp_and_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline int4 operator & (const int4& i1, const int1& i2) { return int4(_hlslpp_and_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }

	hlslpp_inline int1 operator | (const int1& i1, const int1& i2) { return int1(_hlslpp_or_si128(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator | (const int2& i1, const int2& i2) { return int2(_hlslpp_or_si128(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator | (const int3& i1, const int3& i2) { return int3(_hlslpp_or_si128(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator | (const int4& i1, const int4& i2) { return int4(_hlslpp_or_si128(i1.vec, i2.vec)); }

	hlslpp_inline int2 operator | (const int2& i1, const int1& i2) { return int2(_hlslpp_or_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline int3 operator | (const int3& i1, const int1& i2) { return int3(_hlslpp_or_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline int4 operator | (const int4& i1, const int1& i2) { return int4(_hlslpp_or_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }

	hlslpp_inline int1 operator ^ (const int1& i1, const int1& i2) { return int1(_hlslpp_xor_si128(i1.vec, i2.vec)); }
	hlslpp_inline int2 operator ^ (const int2& i1, const int2& i2) { return int2(_hlslpp_xor_si128(i1.vec, i2.vec)); }
	hlslpp_inline int3 operator ^ (const int3& i1, const int3& i2) { return int3(_hlslpp_xor_si128(i1.vec, i2.vec)); }
	hlslpp_inline int4 operator ^ (const int4& i1, const int4& i2) { return int4(_hlslpp_xor_si128(i1.vec, i2.vec)); }

	hlslpp_inline int2 operator ^ (const int2& i1, const int1& i2) { return int2(_hlslpp_xor_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline int3 operator ^ (const int3& i1, const int1& i2) { return int3(_hlslpp_xor_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }
	hlslpp_inline int4 operator ^ (const int4& i1, const int1& i2) { return int4(_hlslpp_xor_si128(i1.vec, _hlslpp_perm_xxxx_epi32(i2.vec))); }

	hlslpp_inline int1 operator ~ (const int1& i1) { return int1(_hlslpp_not_si128(i1.vec)); }
	hlslpp_inline int2 operator ~ (const int2& i1) { return int2(_hlslpp_not_si128(i1.vec)); }
	hlslpp_inline int3 operator ~ (const int3& i1) { return int3(_hlslpp_not_si128(i1.vec)); }
	hlslpp_inline int4 operator ~ (const int4& i1) { return int4(_hlslpp_not_si128(i1.vec)); }

	hlslpp_inline int1& operator >>= (int1& i1, const int1& i2) { i1 = i1 >> i2; return i1; }
	hlslpp_inline int2& operator >>= (int2& i1, const int2& i2) { i1 = i1 >> i2; return i1; }
	hlslpp_inline int3& operator >>= (int3& i1, const int3& i2) { i1 = i1 >> i2; return i1; }
	hlslpp_inline int4& operator >>= (int4& i1, const int4& i2) { i1 = i1 >> i2; return i1; }

	hlslpp_inline int1& operator <<= (int1& i1, const int1& i2) { i1 = i1 << i2; return i1; }
	hlslpp_inline int2& operator <<= (int2& i1, const int2& i2) { i1 = i1 << i2; return i1; }
	hlslpp_inline int3& operator <<= (int3& i1, const int3& i2) { i1 = i1 << i2; return i1; }
	hlslpp_inline int4& operator <<= (int4& i1, const int4& i2) { i1 = i1 << i2; return i1; }

	hlslpp_inline int1& operator &= (int1& i1, const int1& i2) { i1 = i1 & i2; return i1; }
	hlslpp_inline int2& operator &= (int2& i1, const int2& i2) { i1 = i1 & i2; return i1; }
	hlslpp_inline int3& operator &= (int3& i1, const int3& i2) { i1 = i1 & i2; return i1; }
	hlslpp_inline int4& operator &= (int4& i1, const int4& i2) { i1 = i1 & i2; return i1; }

	hlslpp_inline int1& operator |= (int1& i1, const int1& i2) { i1 = i1 | i2; return i1; }
	hlslpp_inline int2& operator |= (int2& i1, const int2& i2) { i1 = i1 | i2; return i1; }
	hlslpp_inline int3& operator |= (int3& i1, const int3& i2) { i1 = i1 | i2; return i1; }
	hlslpp_inline int4& operator |= (int4& i1, const int4& i2) { i1 = i1 | i2; return i1; }

	hlslpp_inline int1& operator ^= (int1& i1, const int1& i2) { i1 = i1 ^ i2; return i1; }
	hlslpp_inline int2& operator ^= (int2& i1, const int2& i2) { i1 = i1 ^ i2; return i1; }
	hlslpp_inline int3& operator ^= (int3& i1, const int3& i2) { i1 = i1 ^ i2; return i1; }
	hlslpp_inline int4& operator ^= (int4& i1, const int4& i2) { i1 = i1 ^ i2; return i1; }

	hlslpp_inline int1 abs(const int1& i) { return int1(_hlslpp_abs_epi32(i.vec)); }
	hlslpp_inline int2 abs(const int2& i) { return int2(_hlslpp_abs_epi32(i.vec)); }
	hlslpp_inline int3 abs(const int3& i) { return int3(_hlslpp_abs_epi32(i.vec)); }
	hlslpp_inline int4 abs(const int4& i) { return int4(_hlslpp_abs_epi32(i.vec)); }

	hlslpp_inline bool all(const int1& i) { return _hlslpp_all1_epi32(i.vec); }
	hlslpp_inline bool all(const int2& i) { return _hlslpp_all2_epi32(i.vec); }
	hlslpp_inline bool all(const int3& i) { return _hlslpp_all3_epi32(i.vec); }
	hlslpp_inline bool all(const int4& i) { return _hlslpp_all4_epi32(i.vec); }

	hlslpp_inline bool any(const int1& i) { return _hlslpp_any1_epi32(i.vec); }
	hlslpp_inline bool any(const int2& i) { return _hlslpp_any2_epi32(i.vec); }
	hlslpp_inline bool any(const int3& i) { return _hlslpp_any3_epi32(i.vec); }
	hlslpp_inline bool any(const int4& i) { return _hlslpp_any4_epi32(i.vec); }

	hlslpp_inline int1 clamp(const int1& i, const int1& mini, const int1& maxi) { return int1(_hlslpp_clamp_epi32(i.vec, mini.vec, maxi.vec)); }
	hlslpp_inline int2 clamp(const int2& i, const int2& mini, const int2& maxi) { return int2(_hlslpp_clamp_epi32(i.vec, mini.vec, maxi.vec)); }
	hlslpp_inline int3 clamp(const int3& i, const int3& mini, const int3& maxi) { return int3(_hlslpp_clamp_epi32(i.vec, mini.vec, maxi.vec)); }
	hlslpp_inline int4 clamp(const int4& i, const int4& mini, const int4& maxi) { return int4(_hlslpp_clamp_epi32(i.vec, mini.vec, maxi.vec)); }

	hlslpp_inline int1 countbits(const int1& i) { return int1(_hlslpp_countbits_epi32(i.vec)); }
	hlslpp_inline int2 countbits(const int2& i) { return int2(_hlslpp_countbits_epi32(i.vec)); }
	hlslpp_inline int3 countbits(const int3& i) { return int3(_hlslpp_countbits_epi32(i.vec)); }
	hlslpp_inline int4 countbits(const int4& i) { return int4(_hlslpp_countbits_epi32(i.vec)); }

	hlslpp_inline int1 firstbithigh(const int1& i) { return int1(_hlslpp_firstbithigh_epi32(i.vec)); }
	hlslpp_inline int2 firstbithigh(const int2& i) { return int2(_hlslpp_firstbithigh_epi32(i.vec)); }
	hlslpp_inline int3 firstbithigh(const int3& i) { return int3(_hlslpp_firstbithigh_epi32(i.vec)); }
	hlslpp_inline int4 firstbithigh(const int4& i) { return int4(_hlslpp_firstbithigh_epi32(i.vec)); }

	hlslpp_inline int1 firstbitlow(const int1& i) { return int1(_hlslpp_firstbitlow_epi32(i.vec)); }
	hlslpp_inline int2 firstbitlow(const int2& i) { return int2(_hlslpp_firstbitlow_epi32(i.vec)); }
	hlslpp_inline int3 firstbitlow(const int3& i) { return int3(_hlslpp_firstbitlow_epi32(i.vec)); }
	hlslpp_inline int4 firstbitlow(const int4& i) { return int4(_hlslpp_firstbitlow_epi32(i.vec)); }

	hlslpp_inline int1 min(const int1& i1, const int1& i2) { return int1(_hlslpp_min_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 min(const int2& i1, const int2& i2) { return int2(_hlslpp_min_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 min(const int3& i1, const int3& i2) { return int3(_hlslpp_min_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 min(const int4& i1, const int4& i2) { return int4(_hlslpp_min_epi32(i1.vec, i2.vec)); }

	hlslpp_inline int1 mad(const int1& i1, const int1& i2, const int1& i3) { return int1(_hlslpp_madd_epi32(i1.vec, i2.vec, i3.vec)); }
	hlslpp_inline int2 mad(const int2& i1, const int2& i2, const int2& i3) { return int2(_hlslpp_madd_epi32(i1.vec, i2.vec, i3.vec)); }
	hlslpp_inline int3 mad(const int3& i1, const int3& i2, const int3& i3) { return int3(_hlslpp_madd_epi32(i1.vec, i2.vec, i3.vec)); }
	hlslpp_inline int4 mad(const int4& i1, const int4& i2, const int4& i3) { return int4(_hlslpp_madd_epi32(i1.vec, i2.vec, i3.vec)); }

	hlslpp_inline int1 max(const int1& i1, const int1& i2) { return int1(_hlslpp_max_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int2 max(const int2& i1, const int2& i2) { return int2(_hlslpp_max_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int3 max(const int3& i1, const int3& i2) { return int3(_hlslpp_max_epi32(i1.vec, i2.vec)); }
	hlslpp_inline int4 max(const int4& i1, const int4& i2) { return int4(_hlslpp_max_epi32(i1.vec, i2.vec)); }

	hlslpp_inline int1 select(const int1& condition, const int1& i1, const int1& i2) { return int1(_hlslpp_sel_epi32(i1.vec, i2.vec, _hlslpp_cmpeq_epi32(condition.vec, _hlslpp_setzero_epi32()))); }
	hlslpp_inline int2 select(const int2& condition, const int2& i1, const int2& i2) { return int2(_hlslpp_sel_epi32(i1.vec, i2.vec, _hlslpp_cmpeq_epi32(condition.vec, _hlslpp_setzero_epi32()))); }
	hlslpp_inline int3 select(const int3& condition, const int3& i1, const int3& i2) { return int3(_hlslpp_sel_epi32(i1.vec, i2.vec, _hlslpp_cmpeq_epi32(condition.vec, _hlslpp_setzero_epi32()))); }
	hlslpp_inline int4 select(const int4& condition, const int4& i1, const int4& i2) { return int4(_hlslpp_sel_epi32(i1.vec, i2.vec, _hlslpp_cmpeq_epi32(condition.vec, _hlslpp_setzero_epi32()))); }

	hlslpp_inline int1 reversebits(const int1& i) { return int1(_hlslpp_reversebits_epi32(i.vec)); }
	hlslpp_inline int2 reversebits(const int2& i) { return int2(_hlslpp_reversebits_epi32(i.vec)); }
	hlslpp_inline int3 reversebits(const int3& i) { return int3(_hlslpp_reversebits_epi32(i.vec)); }
	hlslpp_inline int4 reversebits(const int4& i) { return int4(_hlslpp_reversebits_epi32(i.vec)); }

	//--------------------------------------------------------------------------------------------------------------------------
	// Function disambiguation. This typically happens when pulling in math.h, <cmath> or <algorithm>, where functions now live
	// in the global namespace. Due to implicit conversions, we need to clarify to the compiler which functions it needs to use.
	//--------------------------------------------------------------------------------------------------------------------------

	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int1) operator == (const int1& f1, T f2) { return f1 == int1(f2); }
	template<typename T> hlslpp_inline hlslpp_enable_if_return(T, int1) operator == (T f1, const int1& f2) { return int1(f1) == f2; }

	template<int X> hlslpp_inline int1 operator - (const iswizzle1<X>& s) { return -int1(s); }

	template<int X> hlslpp_inline int1 abs(const iswizzle1<X>& s) { return abs(int1(s)); }

	template<int X, int Y> hlslpp_inline int1 operator == (const iswizzle1<X>& i1, const iswizzle1<Y>& i2) { return int1(i1) == int1(i2); }
	template<int X, int Y> hlslpp_inline int1 operator != (const iswizzle1<X>& i1, const iswizzle1<Y>& i2) { return int1(i1) != int1(i2); }
	template<int X, int Y> hlslpp_inline int1 operator >  (const iswizzle1<X>& i1, const iswizzle1<Y>& i2) { return int1(i1) >  int1(i2); }
	template<int X, int Y> hlslpp_inline int1 operator >= (const iswizzle1<X>& i1, const iswizzle1<Y>& i2) { return int1(i1) >= int1(i2); }
	template<int X, int Y> hlslpp_inline int1 operator <  (const iswizzle1<X>& i1, const iswizzle1<Y>& i2) { return int1(i1) <  int1(i2); }
	template<int X, int Y> hlslpp_inline int1 operator <= (const iswizzle1<X>& i1, const iswizzle1<Y>& i2) { return int1(i1) <= int1(i2); }

	template<int X>
	hlslpp_inline iswizzle1<X>& iswizzle1<X>::operator = (int32_t i)
	{
		vec = _hlslpp_blend_epi32(vec, _hlslpp_set1_epi32(i), HLSLPP_COMPONENT_X(X));
		return *this;
	}

	// Revise these functions. Can I not do with swizzle?

	template<int X>
	template<int A>
	hlslpp_inline iswizzle1<X>& iswizzle1<X>::operator = (const iswizzle1<A>& s)
	{
		n128i t = _hlslpp_perm_epi32(s.vec, A, A, A, A);
		vec = _hlslpp_blend_epi32(vec, t, HLSLPP_COMPONENT_X(X));
		return *this;
	}

	template<int X>
	hlslpp_inline iswizzle1<X>& iswizzle1<X>::operator = (const iswizzle1<X>& s)
	{
		n128i t = _hlslpp_perm_epi32(s.vec, X, X, X, X);
		vec = _hlslpp_blend_epi32(vec, t, HLSLPP_COMPONENT_X(X));
		return *this;
	}

	template<int X>
	iswizzle1<X>& iswizzle1<X>::operator = (const int1& i)
	{
		vec = _hlslpp_blend_epi32(vec, hlslpp_iswizzle1_swizzle(0, X, i.vec), HLSLPP_COMPONENT_X(X)); return *this;
	}

	template<int X, int Y>
	template<int A, int B>
	hlslpp_inline iswizzle2<X, Y>& iswizzle2<X, Y>::operator = (const iswizzle2<A, B>& s)
	{
		static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_iswizzle2_blend(vec, hlslpp_iswizzle2_swizzle(A, B, X, Y, s.vec));
		return *this;
	}

	template<int X, int Y>
	hlslpp_inline iswizzle2<X, Y>& iswizzle2<X, Y>::operator = (const iswizzle2<X, Y>& s)
	{
		static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_iswizzle2_blend(vec, hlslpp_iswizzle2_swizzle(X, Y, X, Y, s.vec));
		return *this;
	}

	template<int X, int Y>
	iswizzle2<X, Y>& iswizzle2<X, Y>::operator = (const int2& i)
	{
		static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_iswizzle2_blend(vec, hlslpp_iswizzle2_swizzle(0, 1, X, Y, i.vec));
		return *this;
	}

	template<int X, int Y, int Z>
	template<int A, int B, int C>
	hlslpp_inline iswizzle3<X, Y, Z>& iswizzle3<X, Y, Z>::operator = (const iswizzle3<A, B, C>& s)
	{
		static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_iswizzle3_blend(vec, hlslpp_iswizzle3_swizzle(A, B, C, X, Y, Z, s.vec));
		return *this;
	}

	template<int X, int Y, int Z>
	hlslpp_inline iswizzle3<X, Y, Z>& iswizzle3<X, Y, Z>::operator = (const iswizzle3<X, Y, Z>& s)
	{
		static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_iswizzle3_blend(vec, hlslpp_iswizzle3_swizzle(X, Y, Z, X, Y, Z, s.vec));
		return *this;
	}

	template<int X, int Y, int Z>
	iswizzle3<X, Y, Z>& iswizzle3<X, Y, Z>::operator = (const int3& i)
	{
		static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_iswizzle3_blend(vec, hlslpp_iswizzle3_swizzle(0, 1, 2, X, Y, Z, i.vec));
		return *this;
	}

	template<int X, int Y, int Z, int W>
	template<int A, int B, int C, int D>
	hlslpp_inline iswizzle4<X, Y, Z, W>& iswizzle4<X, Y, Z, W>::operator = (const iswizzle4<A, B, C, D>& s)
	{
		static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_iswizzle4_swizzle(A, B, C, D, X, Y, Z, W, s.vec);
		return *this;
	}

	template<int X, int Y, int Z, int W>
	iswizzle4<X, Y, Z, W>& iswizzle4<X, Y, Z, W>::operator = (const int4& i)
	{
		static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
		vec = hlslpp_iswizzle4_swizzle(0, 1, 2, 3, X, Y, Z, W, i.vec);
		return *this;
	}

	hlslpp_inline void store(const int1& v, int32_t* i)
	{
		_hlslpp_store1_epi32(i, v.vec);
	}

	hlslpp_inline void store(const int2& v, int32_t* i)
	{
		_hlslpp_store2_epi32(i, v.vec);
	}
	
	hlslpp_inline void store(const int3& v, int32_t* i)
	{
		_hlslpp_store3_epi32(i, v.vec);
	}
	
	hlslpp_inline void store(const int4& v, int32_t* i)
	{
		_hlslpp_store4_epi32(i, v.vec);
	}
	
	hlslpp_inline void load(int1& v, int32_t* i)
	{
		_hlslpp_load1_epi32(i, v.vec);
	}
	
	hlslpp_inline void load(int2& v, int32_t* i)
	{
		_hlslpp_load2_epi32(i, v.vec);
	}
	
	hlslpp_inline void load(int3& v, int32_t* i)
	{
		_hlslpp_load3_epi32(i, v.vec);
	}
	
	hlslpp_inline void load(int4& v, int32_t* i)
	{
		_hlslpp_load4_epi32(i, v.vec);
	}
}