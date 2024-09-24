#pragma once

#include "hlsl++/common.h"

#if defined(HLSLPP_DOUBLE)

HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_BEGIN

hlslpp_module_export namespace hlslpp
{
	template<int X>
	struct hlslpp_nodiscard dswizzle1
	{
		template<int A> friend struct dswizzle1;

		hlslpp_inline operator double() const { return f64[X]; }

		// Return the address of this double in the same way we return the value
		hlslpp_inline double* operator&() { return &f64[X]; }

		template<int E, int A>
		static hlslpp_inline n128d swizzle(n128d v)
		{
			return _hlslpp_perm_pd(v, (((IdentityMask2 >> E) & 1) << A) | (IdentityMask2 & ~((1 << A))));
		}

		template<int E, int A>
		hlslpp_inline n128d swizzle() const
		{
			return swizzle<E % 2, A % 2>(vec[X / 2]);
		}

		// Assignment

		hlslpp_inline dswizzle1& operator = (double f);

		template<int A>
		hlslpp_inline dswizzle1& operator = (const dswizzle1<A>& s);

		hlslpp_inline dswizzle1& operator = (const dswizzle1<X>& s);

		hlslpp_inline dswizzle1& operator = (const double1& f);

	private:

		union
		{
			n128d vec[X < 2 ? 1 : 2];
			double f64[X < 2 ? 2 : 4];
		};
	};

	template<int X, int Y>
	struct hlslpp_nodiscard dswizzle2
	{
		template<int SrcA, int SrcB, int DstA, int DstB>
		static hlslpp_inline n128d swizzle(n128d vec0, n128d vec1)
		{
			// Select which vector to read from and how to build the mask based on the output
			#define HLSLPP_SELECT(Dst) ((Dst % 2) == 0 ? (SrcA < 2 ? vec0 : vec1) : (SrcB < 2 ? vec0 : vec1))
			n128d result = _hlslpp_shuffle_pd(HLSLPP_SELECT(DstA), HLSLPP_SELECT(DstB), HLSLPP_SHUFFLE_MASK_PD((DstA % 2) == 0 ? (SrcA % 2) : (SrcB % 2), (DstB % 2) == 0 ? (SrcA % 2) : (SrcB % 2)));
			#undef HLSLPP_SELECT
			return result;
		}

		template<int SrcA, int SrcB, int DstA, int DstB>
		hlslpp_inline n128d swizzle() const
		{
			// Select which vector to read from and how to build the mask based on the output
			#define HLSLPP_SELECT(Dst) (Dst % 2) == 0 ? vec[(SrcA < 2) ? 0 : 1] : vec[(SrcB < 2) ? 0 : 1]
			n128d result = _hlslpp_shuffle_pd(HLSLPP_SELECT(DstA), HLSLPP_SELECT(DstB), HLSLPP_SHUFFLE_MASK_PD((DstA % 2) == 0 ? (SrcA % 2) : (SrcB % 2), (DstB % 2) == 0 ? (SrcA % 2) : (SrcB % 2)));
			#undef HLSLPP_SELECT
			return result;
		}
	
		template<int E, int F>
		hlslpp_inline void swizzle_all(const dswizzle2<E, F>& s)
		{
			hlslpp_constexpr_if((X < 2 && Y < 2) || (X >= 2 && Y >= 2))
			{
				vec[(X < 2 && Y < 2) ? 0 : 1] = s.template swizzle<E, F, X, Y>();
			}
			else
			{
				// Swizzle E and F into both 0 and 1
				n128d swizzledE = s.template swizzle<E, E, 0, 1>();
				n128d swizzledF = s.template swizzle<F, F, 0, 1>();

				// Blend with original vectors to preserve contents in remaining entries
				vec[X / 2] = _hlslpp_blend_pd(vec[X / 2], swizzledE, HLSLPP_BLEND_MASK_PD((X % 2) == 1, (X % 2) == 0));
				vec[Y / 2] = _hlslpp_blend_pd(vec[Y / 2], swizzledF, HLSLPP_BLEND_MASK_PD((Y % 2) == 1, (Y % 2) == 0));
			}
		}

		// Assignment
	
		template<int E, int F>
		hlslpp_inline dswizzle2& operator = (const dswizzle2<E, F>& s);

		hlslpp_inline dswizzle2& operator = (const dswizzle2<X, Y>& s);
	
		hlslpp_inline dswizzle2& operator = (const double2& f);
	
		union
		{
			n128d vec[(X < 2 && Y < 2) ? 1 : 2];
			double f64[(X < 2 && Y < 2) ? 2 : 4];
		};
	};

	template<int X, int Y, int Z>
	struct hlslpp_nodiscard dswizzle3
	{
		template<int A, int B, int C>
		hlslpp_inline void swizzle_all(const dswizzle3<A, B, C>& s)
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			swizzleblend<A, B, C, X, Y, Z>(s.vec, vec);
#else
			swizzleblend<A, B, C, X, Y, Z>(s.vec[0], s.vec[1], vec[0], vec[1]);
#endif
		}

		// Assignment

		template<int A, int B, int C>
		hlslpp_inline dswizzle3& operator = (const dswizzle3<A, B, C>& s);

		hlslpp_inline dswizzle3& operator = (const dswizzle3<X, Y, Z>& s);

		hlslpp_inline dswizzle3& operator = (const double3& f);

#if defined(HLSLPP_SIMD_REGISTER_256)

		// Swizzles SrcA into 0, SrcB into 1 and SrcC into 2
		// This version doesn't blend so only works for dswizzle3 -> double3 conversions
		template<int SrcA, int SrcB, int SrcC>
		static hlslpp_inline void swizzle(n256d vec, n256d& ovec)
		{
			ovec = _hlslpp256_perm_pd(vec, SrcA, SrcB, SrcC, SrcC);
		}

		// Swizzles SrcA, SrcB, SrcC into DstA, DstB, DstC
		template<int SrcA, int SrcB, int SrcC, int DstA, int DstB, int DstC>
		static hlslpp_inline void swizzleblend(n256d vec, n256d& ovec)
		{
			#define HLSLPP_SELECT(x) (DstA == x ? SrcA : (DstB == x ? SrcB : SrcC))
			#define HLSLPP_BLEND(x) ((DstA == x || DstB == x || DstC == x) ? 1 : 0)
			n256d perm = _hlslpp256_perm_pd(vec, HLSLPP_SELECT(0), HLSLPP_SELECT(1), HLSLPP_SELECT(2), HLSLPP_SELECT(3));
			ovec = _hlslpp256_blend_pd(perm, ovec, HLSLPP_BLEND_MASK(HLSLPP_BLEND(0), HLSLPP_BLEND(1), HLSLPP_BLEND(2), HLSLPP_BLEND(3)));
			#undef HLSLPP_SELECT
			#undef HLSLPP_BLEND
		}

#else

		// Swizzles SrcA into position 0 and SrcB into position 1
		template<int SrcA, int SrcB>
		static hlslpp_inline n128d swizzle(n128d vec0, n128d vec1)
		{
			return _hlslpp_shuffle_pd(SrcA < 2 ? vec0 : vec1, SrcB < 2 ? vec0 : vec1, HLSLPP_SHUFFLE_MASK_PD(SrcA % 2, SrcB % 2));
		}

		// Swizzles SrcA into 0, SrcB into 1 and SrcC into 2
		// This version doesn't blend so only works for dswizzle3 -> double3 conversions
		template<int SrcA, int SrcB, int SrcC>
		static hlslpp_inline void swizzle(n128d vec0, n128d vec1, n128d& ovec0, n128d& ovec1)
		{
			ovec0 = swizzle<SrcA, SrcB>(vec0, vec1);
			ovec1 = swizzle<SrcC, 0   >(vec0, vec1);
		}

		// Swizzles SrcA into DstA, SrcB into DstB and SrcC into DstC
		// Needs to blend to be able to preserve the remaining component
		template<int SrcA, int SrcB, int SrcC, int DstA, int DstB, int DstC>
		static hlslpp_inline void swizzleblend(n128d vec0, n128d vec1, n128d& ovec0, n128d& ovec1)
		{
			#define HLSLPP_SELECT(x) (DstA == x ? SrcA : (DstB == x ? SrcB : SrcC))
			#define HLSLPP_BLEND(x) ((DstA == x || DstB == x || DstC == x) ? 1 : 0)

			n128d swizzle0 = swizzle<HLSLPP_SELECT(0), HLSLPP_SELECT(1)>(vec0, vec1);
			n128d swizzle1 = swizzle<HLSLPP_SELECT(2), HLSLPP_SELECT(3)>(vec0, vec1);

			ovec0 = _hlslpp_blend_pd(swizzle0, ovec0, HLSLPP_BLEND_MASK_PD(HLSLPP_BLEND(0), HLSLPP_BLEND(1)));
			ovec1 = _hlslpp_blend_pd(swizzle1, ovec1, HLSLPP_BLEND_MASK_PD(HLSLPP_BLEND(2), HLSLPP_BLEND(3)));

			#undef HLSLPP_SELECT
			#undef HLSLPP_BLEND
		}

#endif

		union
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			n256d vec;
#else
			n128d vec[2];
#endif
			double f64[4];
		};
	};

	template<int X, int Y, int Z, int W>
	struct hlslpp_nodiscard dswizzle4
	{
		template<int A, int B, int C, int D>
		hlslpp_inline dswizzle4& operator = (const dswizzle4<A, B, C, D>& s);
		
		hlslpp_inline dswizzle4& operator = (const double4& f);

#if defined(HLSLPP_SIMD_REGISTER_256)

		// Swizzles SrcA, SrcB, SrcC into DstA, DstB, DstC
		template<int SrcA, int SrcB, int SrcC, int SrcD, int DstA, int DstB, int DstC, int DstD>
		static hlslpp_inline void swizzle(n256d vec, n256d& ovec)
		{
			#define HLSLPP_SELECT(x) DstA == x ? SrcA : (DstB == x ? SrcB : (DstC == x ? SrcC : SrcD))
			ovec = _hlslpp256_perm_pd(vec, HLSLPP_SELECT(0), HLSLPP_SELECT(1), HLSLPP_SELECT(2), HLSLPP_SELECT(3));
			#undef HLSLPP_SELECT
		}

#else

		template<int SrcA, int SrcB, int SrcC, int SrcD, int DstA, int DstB, int DstC, int DstD>
		static hlslpp_inline void swizzle(n128d vec0, n128d vec1, n128d& ovec0, n128d& ovec1)
		{
			#define HLSLPP_SELECT(x) (DstA == x ? SrcA : (DstB == x ? SrcB : (DstC == x ? SrcC : SrcD)))

			#define hlslpp_dswizzle4_swizzle2(SrcA, SrcB, vec0, vec1) \
				_hlslpp_shuffle_pd((SrcA) < 2 ? vec0 : vec1, (SrcB) < 2 ? vec0 : vec1, HLSLPP_SHUFFLE_MASK_PD((SrcA) % 2, (SrcB) % 2))

			ovec0 = hlslpp_dswizzle4_swizzle2(HLSLPP_SELECT(0), HLSLPP_SELECT(1), vec0, vec1);
			ovec1 = hlslpp_dswizzle4_swizzle2(HLSLPP_SELECT(2), HLSLPP_SELECT(3), vec0, vec1);

			#undef HLSLPP_SELECT
		}

#endif

		union
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			n256d vec;
#else
			n128d vec[2];
#endif
			double f64[4];
		};
	};

	//-------------//
	// Double type //
	//-------------//

	struct hlslpp_nodiscard double1
	{
		hlslpp_inline double1() : vec(_hlslpp_setzero_pd()) {}
		hlslpp_inline double1(const double1& f) : vec(f.vec) {}
		explicit hlslpp_inline double1(n128d vec) : vec(vec) {}

		template<typename T>
		hlslpp_inline double1(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set_pd(double(f), 0.0)) {}

		template<int X> hlslpp_inline double1(const dswizzle1<X>& s) : vec(s.template swizzle<X, 0>()) {}

		//double1(const int1& i);

		hlslpp_inline double1& operator = (const double1& f) { vec = f.vec; return *this; }

		operator double() const { return f64[0]; }

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128d vec;
			double f64[2];
			#include "swizzle/vector_double_x.h"
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct hlslpp_nodiscard double2
	{
		// Constructors

		hlslpp_inline double2() : vec(_hlslpp_setzero_pd()) {}
		hlslpp_inline double2(const double2& f) : vec(f.vec) {}
		explicit hlslpp_inline double2(n128d vec) : vec(vec) {}
		explicit hlslpp_inline double2(const double1& f) : vec(_hlslpp_perm_xx_pd(f.vec)) {}

		template<typename T>
		hlslpp_inline double2(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set_pd(double(f), double(f))) {}

		template<typename T1, typename T2>
		hlslpp_inline double2(T1 f1, T2 f2, hlslpp_enable_if_number_2(T1, T2)) : vec(_hlslpp_set_pd(double(f1), double(f2))) {}

		hlslpp_inline double2(const double1& f1, const double1& f2) { vec = _hlslpp_blend_pd(f1.vec, _hlslpp_perm_xx_pd(f2.vec), HLSLPP_BLEND_MASK_PD(1, 0)); }
		
		template<int X, int Y> hlslpp_inline double2(const dswizzle2<X, Y>& s) : vec(s.template swizzle<X, Y, 0, 1>()) {}

		//double2(const int2& i);

		hlslpp_inline double2& operator = (const double2& f) { vec = f.vec; return *this; }

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128d vec;
			double f64[2];
			#include "swizzle/vector_double_x.h"
			#include "swizzle/vector_double_y.h"
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct hlslpp_nodiscard double3
	{
		// Constructors

#if defined(HLSLPP_SIMD_REGISTER_256)

		hlslpp_inline double3() : vec(_hlslpp256_setzero_pd()) {}
		hlslpp_inline double3(const double3& f) : vec(f.vec) {}
		explicit hlslpp_inline double3(n256d vec) : vec(vec) {}
		explicit hlslpp_inline double3(const double1& f) : vec(_hlslpp256_set128_pd(_hlslpp_perm_xx_pd(f.vec), _hlslpp_perm_xx_pd(f.vec))) {}

		template<typename T>
		hlslpp_inline double3(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp256_set_pd(double(f), double(f), double(f), 0.0)) {}

		template<typename T1, typename T2, typename T3>
		hlslpp_inline double3(T1 f1, T2 f2, T3 f3, hlslpp_enable_if_number_3(T1, T2, T3)) : vec(_hlslpp256_set_pd(double(f1), double(f2), double(f3), 0.0)) {}

		hlslpp_inline double3& operator = (const double3& f) { vec = f.vec; return *this; }

#else

		hlslpp_inline double3() : vec0(_hlslpp_setzero_pd()), vec1(_hlslpp_setzero_pd()) {}
		hlslpp_inline double3(const double3& f) : vec0(f.vec0), vec1(f.vec1) {}
		explicit hlslpp_inline double3(n128d vec0, n128d vec1) : vec0(vec0), vec1(vec1) {}
		explicit hlslpp_inline double3(const double1& f) : vec0(_hlslpp_perm_xx_pd(f.vec)), vec1(_hlslpp_perm_xx_pd(f.vec)) {}

		template<typename T>
		hlslpp_inline double3(T f, hlslpp_enable_if_number(T)) : vec0(_hlslpp_set_pd(double(f), double(f))), vec1(_hlslpp_set_pd(double(f), 0.0)) {}

		template<typename T1, typename T2, typename T3>
		hlslpp_inline double3(T1 f1, T2 f2, T3 f3, hlslpp_enable_if_number_3(T1, T2, T3)) : vec0(_hlslpp_set_pd(double(f1), double(f2))), vec1(_hlslpp_set_pd(double(f3), 0.0)) {}

		hlslpp_inline double3& operator = (const double3& f) { vec0 = f.vec0; vec1 = f.vec1; return *this; }

#endif

		hlslpp_inline double3(const double1& f1, const double1& f2, const double1& f3)
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			n128d f1f2 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec);
			vec = _hlslpp256_set128_pd(f1f2, f3.vec);
#else
			vec0 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = f3.vec;
#endif
		}

		hlslpp_inline double3(const double2& f1, const double1& f2)
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			vec = _hlslpp256_set128_pd(f1.vec, f2.vec);
#else
			vec0 = f1.vec;
			vec1 = f2.vec;
#endif
		}

		hlslpp_inline double3(const double1& f1, const double2& f2)
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			n128d f1f2x = _hlslpp_shuf_xx_pd(f1.vec, f2.vec);
			n128d f2y = _hlslpp_perm_yx_pd(f2.vec);
			vec = _hlslpp256_set128_pd(f1f2x, f2y);
#else
			vec0 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = _hlslpp_perm_yx_pd(f2.vec);
#endif
		}

		template<int X, int Y, int Z>
		hlslpp_inline double3(const dswizzle3<X, Y, Z>& s)
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			dswizzle3<X, Y, Z>::template swizzle<X, Y, Z>(s.vec, vec);
#else
			dswizzle3<X, Y, Z>::template swizzle<X, Y, Z>(s.vec[0], s.vec[1], vec0, vec1);
#endif
		}
		
		//float3(const int3& i);

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
#if defined(HLSLPP_SIMD_REGISTER_256)

			n256d vec;

#else

			HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
			struct
			{
				n128d vec0;
				n128d vec1;
			};
			HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END

#endif

			double f64[4];
			#include "swizzle/vector_double_x.h"
			#include "swizzle/vector_double_y.h"
			#include "swizzle/vector_double_z.h"
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct hlslpp_nodiscard double4
	{
#if defined(HLSLPP_SIMD_REGISTER_256)

		hlslpp_inline double4() : vec(_hlslpp256_setzero_pd()) {}
		hlslpp_inline double4(const double4& f) : vec(f.vec) {}
		explicit hlslpp_inline double4(n256d vec) : vec(vec) {}
		explicit hlslpp_inline double4(const double1& f) : vec(_hlslpp256_set128_pd(_hlslpp_perm_xx_pd(f.vec), _hlslpp_perm_xx_pd(f.vec))) {}

		template<typename T>
		hlslpp_inline double4(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp256_set1_pd(double(f))) {}

		template<typename T1, typename T2, typename T3, typename T4>
		hlslpp_inline double4(T1 f1, T2 f2, T3 f3, T4 f4, hlslpp_enable_if_number_4(T1, T2, T3, T4)) : vec(_hlslpp256_set_pd(double(f1), double(f2), double(f3), double(f4))) {}

		hlslpp_inline double4& operator = (const double4& f) { vec = f.vec; return *this; }

#else

		hlslpp_inline double4() : vec0(_hlslpp_setzero_pd()), vec1(_hlslpp_setzero_pd()) {}
		hlslpp_inline double4(const double4& f) : vec0(f.vec0), vec1(f.vec1) {}
		explicit hlslpp_inline double4(n128d vec0, n128d vec1) : vec0(vec0), vec1(vec1) {}
		explicit hlslpp_inline double4(const double1& f) : vec0(_hlslpp_perm_xx_pd(f.vec)), vec1(_hlslpp_perm_xx_pd(f.vec)) {}

		template<typename T>
		hlslpp_inline double4(T f, hlslpp_enable_if_number(T)) : vec0(_hlslpp_set1_pd(double(f))), vec1(_hlslpp_set1_pd(double(f))) {}

		template<typename T1, typename T2, typename T3, typename T4>
		hlslpp_inline double4(T1 f1, T2 f2, T3 f3, T4 f4, hlslpp_enable_if_number_4(T1, T2, T3, T4)) : vec0(_hlslpp_set_pd(double(f1), double(f2))), vec1(_hlslpp_set_pd(double(f3), double(f4))) {}

		hlslpp_inline double4& operator = (const double4& f) { vec0 = f.vec0; vec1 = f.vec1; return *this; }

#endif

		hlslpp_inline double4(const double1& f1, const double1& f2, const double1& f3, const double1& f4)
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			n128d f1f2 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec);
			n128d f3f4 = _hlslpp_shuf_xx_pd(f3.vec, f4.vec);
			vec = _hlslpp256_set128_pd(f1f2, f3f4);
#else
			vec0 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = _hlslpp_shuf_xx_pd(f3.vec, f4.vec);
#endif
		}

		hlslpp_inline double4(const double2& f1, const double1& f2, const double1& f3)
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			vec = _hlslpp256_set128_pd(f1.vec, _hlslpp_shuf_xx_pd(f2.vec, f3.vec));
#else
			vec0 = f1.vec;
			vec1 = _hlslpp_shuf_xx_pd(f2.vec, f3.vec);
#endif
		}

		hlslpp_inline double4(const double1& f1, const double2& f2, const double1& f3)
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			vec = _hlslpp256_set128_pd(_hlslpp_shuf_xx_pd(f1.vec, f2.vec), _hlslpp_shuf_yx_pd(f2.vec, f3.vec));
#else
			vec0 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = _hlslpp_shuf_yx_pd(f2.vec, f3.vec);
#endif
		}

		hlslpp_inline double4(const double1& f1, const double1& f2, const double2& f3)
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			vec = _hlslpp256_set128_pd(_hlslpp_shuf_xx_pd(f1.vec, f2.vec), f3.vec);
#else
			vec0 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = f3.vec;
#endif
		}

		hlslpp_inline double4(const double2& f1, const double2& f2)
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			vec = _hlslpp256_set128_pd(f1.vec, f2.vec);
#else
			vec0 = f1.vec;
			vec1 = f2.vec;
#endif
		}

		hlslpp_inline double4(const double1& f1, const double3& f2)
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			vec = _hlslpp256_set128_pd(_hlslpp_shuf_xx_pd(f1.vec, _hlslpp256_low_pd(f2.vec)), _hlslpp_shuf_yx_pd(_hlslpp256_low_pd(f2.vec), _hlslpp256_high_pd(f2.vec)));
#else
			vec0 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec0);
			vec1 = _hlslpp_shuf_yx_pd(f2.vec0, f2.vec1);
#endif
		}

		hlslpp_inline double4(const double3& f1, const double1& f2)
		{
#if defined(HLSLPP_SIMD_REGISTER_256)

			vec = _hlslpp256_set128_pd(_hlslpp256_low_pd(f1.vec), _hlslpp_shuf_xx_pd(_hlslpp256_high_pd(f1.vec), f2.vec));
#else
			vec0 = f1.vec0;
			vec1 = _hlslpp_shuf_xx_pd(f1.vec1, f2.vec);
#endif
		}
		
		template<int X, int Y, int Z, int W>
		hlslpp_inline double4(const dswizzle4<X, Y, Z, W>& s)
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			dswizzle4<X, Y, Z, W>::template swizzle<X, Y, Z, W, 0, 1, 2, 3>(s.vec, vec);
#else
			dswizzle4<X, Y, Z, W>::template swizzle<X, Y, Z, W, 0, 1, 2, 3>(s.vec[0], s.vec[1], vec[0], vec[1]);
#endif
		}

		//double4(const int4& i);

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
#if defined(HLSLPP_SIMD_REGISTER_256)
			n256d vec;
#else
			HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
			struct
			{
				n128d vec0;
				n128d vec1;
			};
			HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END

			n128d vec[2];
#endif
			double f64[4];
			#include "swizzle/vector_double_x.h"
			#include "swizzle/vector_double_y.h"
			#include "swizzle/vector_double_z.h"
			#include "swizzle/vector_double_w.h"
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};
};

HLSLPP_WARNINGS_IMPLICIT_CONSTRUCTOR_BEGIN

#endif