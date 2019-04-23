//---------------//
// Double Vector //
//---------------//

#if defined(HLSLPP_FLOAT64)

namespace hlslpp
{
	union BitMaskDouble
	{
		uint64_t i;
		double d;
		explicit BitMaskDouble(uint64_t i) : i(i) {}
		explicit BitMaskDouble(double d) : d(d) {}
	};

	const BitMaskDouble dfffMask(0xffffffffffffffffu); // Negative NaN
	const BitMaskDouble dAbsMask(0x7fffffffffffffffu);
	const BitMaskDouble dNegMask(0x8000000000000000u);

	//----------
	// Constants
	//----------

	const n128d d4_1 = _hlslpp_set1_pd(1.0);

	const n128d d4negativeMask = _hlslpp_set1_pd(dNegMask.d);
	const n128d d4absMask      = _hlslpp_set1_pd(dAbsMask.d);

	#define _hlslpp_perm_xx_pd(x)				_hlslpp_perm_pd((x), HLSLPP_SHUFFLE_MASK_PD(MaskX, MaskX))
	#define _hlslpp_perm_xy_pd(x)				_hlslpp_perm_pd((x), HLSLPP_SHUFFLE_MASK_PD(MaskX, MaskY))
	#define _hlslpp_perm_yx_pd(x)				_hlslpp_perm_pd((x), HLSLPP_SHUFFLE_MASK_PD(MaskY, MaskX))
	#define _hlslpp_perm_yy_pd(x)				_hlslpp_perm_pd((x), HLSLPP_SHUFFLE_MASK_PD(MaskY, MaskY))

	#define _hlslpp_shuf_xx_pd(x, y)			_hlslpp_shuffle_pd((x), (y), HLSLPP_SHUFFLE_MASK_PD(MaskX, MaskX))
	#define _hlslpp_shuf_xy_pd(x, y)			_hlslpp_shuffle_pd((x), (y), HLSLPP_SHUFFLE_MASK_PD(MaskX, MaskY))
	#define _hlslpp_shuf_yx_pd(x, y)			_hlslpp_shuffle_pd((x), (y), HLSLPP_SHUFFLE_MASK_PD(MaskY, MaskX))
	#define _hlslpp_shuf_yy_pd(x, y)			_hlslpp_shuffle_pd((x), (y), HLSLPP_SHUFFLE_MASK_PD(MaskY, MaskY))

	hlslpp_inline n128d _hlslpp_dot4_pd(const n128d& x0, const n128d& x1, const n128d& y0, const n128d& y1)
	{
		n128d multi0 = _hlslpp_mul_pd(x0, y0); // Multiply components
		n128d multi1 = _hlslpp_mul_pd(x1, y1);

		n128d shuf0 = _hlslpp_perm_yy_pd(multi0); // Shuffle y and w
		n128d shuf1 = _hlslpp_perm_yy_pd(multi1);

		n128d add0 = _hlslpp_add_pd(shuf0, multi0);  // Contains x+y, _
		n128d add1 = _hlslpp_add_pd(shuf1, multi1);  // Contains z+w, _

		return _hlslpp_add_pd(add0, add1);
	}

	hlslpp_inline n128d _hlslpp_dot3_pd(const n128d& x0, const n128d& x1, const n128d& y0, const n128d& y1)
	{
		n128d multi0 = _hlslpp_mul_pd(x0, y0); // Multiply components
		n128d multi1 = _hlslpp_mul_pd(x1, y1);
		n128d shuf0 = _hlslpp_perm_yy_pd(multi0); // Shuffle y and w
		n128d add0 = _hlslpp_add_pd(shuf0, multi0);  // Contains x+y, _
		return _hlslpp_add_pd(add0, multi1);
	}

	hlslpp_inline n128d _hlslpp_dot2_pd(n128d x, n128d y)
	{
		n128d multi = _hlslpp_mul_pd(x, y); // Multiply components
		n128d shuf = _hlslpp_perm_yy_pd(multi); // Shuffle y
		return _hlslpp_add_pd(multi, shuf);
	}

	template<int X>
	struct dswizzle1
	{
		template<int A> friend struct dswizzle1;

		operator double() const { return f64[X]; }

		template<int E, int A>
		static n128d swizzle(n128d v)
		{
			return _hlslpp_perm_pd(v, (((IdentityMask2 >> E) & 1) << A) | (IdentityMask2 & ~((1 << A))));
		}

		template<int E, int A>
		n128d swizzle() const
		{
			return swizzle<E % 2, A % 2>(vec[X / 2]);
		}

		// Assignment

		dswizzle1& operator = (double f)
		{
			vec[X / 2] = _hlslpp_blend_pd(vec[X / 2], _hlslpp_set1_pd(f), HLSLPP_COMPONENT_X(X % 2));
			return *this;
		}

		template<int A>
		dswizzle1& operator = (const dswizzle1<A>& s) // Revise this function. Can I not do with swizzle?
		{
			n128d t = _hlslpp_shuffle_pd(s.vec[A / 2], s.vec[A / 2], HLSLPP_SHUFFLE_MASK_PD(A, A));
			vec[X / 2] = _hlslpp_blend_pd(vec[X / 2], t, HLSLPP_COMPONENT_X(X % 2));
			return *this;
		}

		dswizzle1& operator = (const double1& f);

	private:

		union
		{
			n128d vec[X < 2 ? 1 : 2];
			double f64[X < 2 ? 2 : 4];
		};
	};

	template<int X, int Y>
	struct dswizzle2
	{
		void staticAsserts()
		{
			static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		template<int SrcA, int SrcB, int DstA, int DstB>
		static n128d swizzle(n128d vec0, n128d vec1)
		{
			// Select which vector to read from and how to build the mask based on the output
			#define HLSLPP_SELECT(Dst) ((Dst % 2) == 0 ? (SrcA < 2 ? vec0 : vec1) : (SrcB < 2 ? vec0 : vec1))
			n128d result = _hlslpp_shuffle_pd(HLSLPP_SELECT(DstA), HLSLPP_SELECT(DstB), HLSLPP_SHUFFLE_MASK_PD((DstA % 2) == 0 ? (SrcA % 2) : (SrcB % 2), (DstB % 2) == 0 ? (SrcA % 2) : (SrcB % 2)));
			#undef HLSLPP_SELECT
			return result;
		}

		template<int SrcA, int SrcB, int DstA, int DstB>
		n128d swizzle() const
		{
			// Select which vector to read from and how to build the mask based on the output
			#define HLSLPP_SELECT(Dst) ((Dst % 2) == 0 ? (SrcA < 2 ? vec[0] : vec[1]) : (SrcB < 2 ? vec[0] : vec[1]))
			n128d result = _hlslpp_shuffle_pd(HLSLPP_SELECT(DstA), HLSLPP_SELECT(DstB), HLSLPP_SHUFFLE_MASK_PD((DstA % 2) == 0 ? (SrcA % 2) : (SrcB % 2), (DstB % 2) == 0 ? (SrcA % 2) : (SrcB % 2)));
			#undef HLSLPP_SELECT
			return result;
		}
	
		// Assignment
	
		template<int E, int F>
		dswizzle2& operator = (const dswizzle2<E, F>& s)
		{
			staticAsserts();

			HLSLPP_CONSTEXPR_IF((X < 2 && Y < 2) || (X >= 2 && Y >= 2))
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

			return *this;
		}
	
		dswizzle2& operator = (const double2& f);
	
	private:
		union
		{
			n128d vec[(X < 2 && Y < 2) ? 1 : 2];
			double f64[(X < 2 && Y < 2) ? 2 : 4];
		};
	};

	template<int X, int Y, int Z>
	struct dswizzle3
	{
		void staticAsserts()
		{
			static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		}

		// Swizzles SrcA into position 0 and SrcB into position 1
		template<int SrcA, int SrcB>
		static n128d swizzle(n128d vec0, n128d vec1)
		{
			return _hlslpp_shuffle_pd(SrcA < 2 ? vec0 : vec1, SrcB < 2 ? vec0 : vec1, HLSLPP_SHUFFLE_MASK_PD(SrcA % 2, SrcB % 2));
		}

		// Swizzles SrcA into 0, SrcB into 1 and SrcC into 2
		// This version doesn't blend so only works for dswizzle3 -> double3 conversions
		template<int SrcA, int SrcB, int SrcC>
		static void swizzle(n128d vec0, n128d vec1, n128d& ovec0, n128d& ovec1)
		{
			ovec0 = swizzle<SrcA, SrcB>(vec0, vec1);
			ovec1 = swizzle<SrcC, 0   >(vec0, vec1);
		}

		// Swizzles SrcA into DstA, SrcB into DstB and SrcC into DstC
		// Needs to blend to be able to preserve the remaining component
		template<int SrcA, int SrcB, int SrcC, int DstA, int DstB, int DstC>
		static void swizzleblend(n128d vec0, n128d vec1, n128d& ovec0, n128d& ovec1)
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

		template<int SrcA, int SrcB>
		n128d swizzle() const
		{
			return swizzle<SrcA, SrcB>(vec[0], vec[1]);
		}
		
		template<int SrcA, int SrcB, int SrcC>
		void swizzle(n128d& ovec0, n128d& ovec1) const
		{
			ovec0 = swizzle<SrcA, SrcB>();
			ovec1 = swizzle<SrcC, 0   >();
		}

		template<int SrcA, int SrcB, int SrcC, int DstA, int DstB, int DstC>
		void swizzleblend(n128d& ovec0, n128d& ovec1) const
		{
			swizzleblend<SrcA, SrcB, SrcC, DstA, DstB, DstC>(vec[0], vec[1], ovec0, ovec1);
		}

		// Assignment

		template<int A, int B, int C>
		dswizzle3& operator = (const dswizzle3<A, B, C>& s)
		{
			staticAsserts();
			s.template swizzleblend<A, B, C, X, Y, Z>(vec[0], vec[1]);
			return *this;
		}

		dswizzle3& operator = (const double3& f);

	private:
		union
		{
			n128d vec[2];
			double f64[4];
		};
	};

	template<int X, int Y, int Z, int W>
	struct dswizzle4
	{
		void staticAsserts()
		{
			static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
		}
		
		template<int SrcA, int SrcB>
		static n128d swizzle(n128d vec0, n128d vec1)
		{
			return _hlslpp_shuffle_pd(SrcA < 2 ? vec0 : vec1, SrcB < 2 ? vec0 : vec1, HLSLPP_SHUFFLE_MASK_PD(SrcA % 2, SrcB % 2));
		}

		template<int SrcA, int SrcB>
		n128d swizzle() const
		{
			return swizzle<SrcA, SrcB>(vec[0], vec[1]);
		}

		template<int SrcA, int SrcB, int SrcC, int SrcD, int DstA, int DstB, int DstC, int DstD>
		static void swizzle(n128d vec0, n128d vec1, n128d& ovec0, n128d& ovec1)
		{
			#define HLSLPP_SELECT(x) DstA == x ? SrcA : (DstB == x ? SrcB : (DstC == x ? SrcC : SrcD))

			ovec0 = swizzle<HLSLPP_SELECT(0), HLSLPP_SELECT(1)>(vec0, vec1);
			ovec1 = swizzle<HLSLPP_SELECT(2), HLSLPP_SELECT(3)>(vec0, vec1);

			#undef HLSLPP_SELECT
		}

		template<int SrcA, int SrcB, int SrcC, int SrcD, int DstA, int DstB, int DstC, int DstD>
		void swizzle(n128d& ovec0, n128d& ovec1) const
		{
			swizzle< SrcA, SrcB, SrcC, SrcD, DstA, DstB, DstC, DstD>(vec[0], vec[1], ovec0, ovec1);
		}
		
		// Assignment
		
		template<int A, int B, int C, int D>
		dswizzle4& operator = (const dswizzle4<A, B, C, D>& s)
		{
			staticAsserts();
			s. template swizzle<A, B, C, D, X, Y, Z, W>(vec[0], vec[1]);
			return *this;
		}
		
		dswizzle4& operator = (const double4& f);

	private:
		union
		{
			n128d vec[2];
			double f64[4];
		};
	};

	//-------------//
	// Double type //
	//-------------//

	struct double1
	{
		double1() {}
		double1(const double1& f) : vec(f.vec) {}
		explicit double1(n128d vec) : vec(vec) {}

		template<typename T>
		double1(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set_pd(double(f), 0.0)) {}

		template<int X> double1(const dswizzle1<X>& s) : vec(s.template swizzle<X, 0>()) {}

		//double1(const int1& i);

		operator double() const { return f64[0]; }

		union
		{
			n128d vec;
			double f64[2];
			#include "swizzle/hlsl++_vector_double_x.h"
		};
	};

	struct double2
	{
		// Constructors

		double2() {}
		double2(const double2& f) : vec(f.vec) {}
		explicit double2(n128d vec) : vec(vec) {}
		explicit double2(const double1& f) : vec(_hlslpp_perm_xx_pd(f.vec)) {}

		template<typename T>
		double2(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set_pd(double(f), double(f))) {}

		template<typename T1, typename T2>
		double2(T1 f1, T2 f2, hlslpp_enable_if_number_2(T1, T2)) : vec(_hlslpp_set_pd(double(f1), double(f2))) {}

		double2(const double1& f1, const double1& f2) { vec = _hlslpp_blend_pd(f1.vec, _hlslpp_perm_xx_pd(f2.vec), HLSLPP_BLEND_MASK(1, 0, 1, 1)); }
		
		template<int X, int Y> double2(const dswizzle2<X, Y>& s) : vec(s.template swizzle<X, Y, 0, 1>()) {}

		//double2(const int2& i);

		union
		{
			n128d vec;
			double f64[2];
			#include "swizzle/hlsl++_vector_double_x.h"
			#include "swizzle/hlsl++_vector_double_y.h"
		};
	};

	struct double3
	{
		// Constructors

		double3() {}
		double3(const double3& f) : vec0(f.vec0), vec1(f.vec1) {}
		explicit double3(n128d vec0, n128d vec1) : vec0(vec0), vec1(vec1) {}
		explicit double3(const double1& f) : vec0(_hlslpp_perm_xx_pd(f.vec)), vec1(_hlslpp_perm_xx_pd(f.vec)) {}

		template<typename T>
		double3(T f, hlslpp_enable_if_number(T)) : vec0(_hlslpp_set_pd(double(f), double(f))), vec1(_hlslpp_set_pd(double(f), 0.0)) {}
		
		template<typename T1, typename T2, typename T3>
		double3(T1 f1, T2 f2, T3 f3, hlslpp_enable_if_number_3(T1, T2, T3)) : vec0(_hlslpp_set_pd(double(f1), double(f2))), vec1(_hlslpp_set_pd(double(f3), 0.0)) {}

		double3(const double1& f1, const double1& f2, const double1& f3)
		{
			vec0 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = f3.vec;
		}

		double3(const double2& f1, const double1& f2)
		{
			vec0 = f1.vec;
			vec1 = f2.vec;
		}

		double3(const double1& f1, const double2& f2)
		{
			vec0 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = _hlslpp_perm_yx_pd(f2.vec);
		}
		
		template<int X, int Y, int Z>
		double3(const dswizzle3<X, Y, Z>& s)
		{
			s.template swizzle<X, Y, Z>(vec0, vec1);
		}
		
		//float3(const int3& i);

		union
		{
			struct
			{
				n128d vec0;
				n128d vec1;
			};

			double f64[4];
			#include "swizzle/hlsl++_vector_double_x.h"
			#include "swizzle/hlsl++_vector_double_y.h"
			#include "swizzle/hlsl++_vector_double_z.h"
		};
	};

	struct double4
	{
		double4() {}
		double4(const double4& f) : vec0(f.vec0), vec1(f.vec1) {}
		explicit double4(n128d vec0, n128d vec1) : vec0(vec0), vec1(vec1) {}
		explicit double4(const double1& f) : vec0(_hlslpp_perm_xx_pd(f.vec)), vec1(_hlslpp_perm_xx_pd(f.vec)) {}

		template<typename T>
		double4(T f, hlslpp_enable_if_number(T)) : vec0(_hlslpp_set1_pd(double(f))), vec1(_hlslpp_set1_pd(double(f))) {}

		template<typename T1, typename T2, typename T3, typename T4>
		double4(T1 f1, T2 f2, T3 f3, T4 f4, hlslpp_enable_if_number_4(T1, T2, T3, T4)) : vec0(_hlslpp_set_pd(double(f1), double(f2))), vec1(_hlslpp_set_pd(double(f3), double(f4))) {}

		double4(const double1& f1, const double1& f2, const double1& f3, const double1& f4)
		{
			vec0 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = _hlslpp_shuf_xx_pd(f3.vec, f4.vec);
		}
		
		double4(const double2& f1, const double1& f2, const double1& f3)
		{
			vec0 = f1.vec;
			vec1 = _hlslpp_shuf_xx_pd(f2.vec, f3.vec);
		}

		double4(const double1& f1, const double2& f2, const double1& f3)
		{
			vec0 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = _hlslpp_shuf_yx_pd(f2.vec, f3.vec);
		}

		double4(const double1& f1, const double1& f2, const double2& f3)
		{
			vec0 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = f3.vec;
		}
		
		double4(const double2& f1, const double2& f2)
		{
			vec0 = f1.vec;
			vec1 = f2.vec;
		}
		
		double4(const double1& f1, const double3& f2)
		{
			vec0 = _hlslpp_shuf_xx_pd(f1.vec, f2.vec0);
			vec1 = _hlslpp_shuf_yx_pd(f2.vec0, f2.vec1);
		}

		double4(const double3& f1, const double1& f2)
		{
			vec0 = f1.vec0;
			vec1 = _hlslpp_shuf_xx_pd(f1.vec1, f2.vec);
		}
		
		template<int X, int Y, int Z, int W>
		double4(const dswizzle4<X, Y, Z, W>& s)
		{
			s.template swizzle<X, Y, Z, W, 0, 1, 2, 3>(vec0, vec1);
		}

		//double4(const int4& i);

		union
		{
			struct
			{
				n128d vec0;
				n128d vec1;
			};

			n128d vec[2];
			double f64[4];
			#include "swizzle/hlsl++_vector_double_x.h"
			#include "swizzle/hlsl++_vector_double_y.h"
			#include "swizzle/hlsl++_vector_double_z.h"
			#include "swizzle/hlsl++_vector_double_w.h"
		};
	};

	// Addition

	double1 operator + (const double1& f1, const double1& f2) { return double1(_hlslpp_add_pd(f1.vec, f2.vec)); }
	double2 operator + (const double2& f1, const double2& f2) { return double2(_hlslpp_add_pd(f1.vec, f2.vec)); }
	double3 operator + (const double3& f1, const double3& f2) { return double3(_hlslpp_add_pd(f1.vec0, f2.vec0), _hlslpp_add_pd(f1.vec1, f2.vec1)); }
	double4 operator + (const double4& f1, const double4& f2) { return double4(_hlslpp_add_pd(f1.vec0, f2.vec0), _hlslpp_add_pd(f1.vec1, f2.vec1)); }

	double2 operator + (const double2& f1, const double1& f2) { return double2(_hlslpp_add_pd(f1.vec, _hlslpp_perm_xx_pd(f2.vec))); }
	double3 operator + (const double3& f1, const double1& f2)
	{
		return double3(_hlslpp_add_pd(f1.vec0, _hlslpp_perm_xx_pd(f2.vec)), _hlslpp_add_pd(f1.vec1, _hlslpp_perm_xx_pd(f2.vec)));
	}

	double4 operator + (const double4& f1, const double1& f2)
	{
		return double4(_hlslpp_add_pd(f1.vec0, _hlslpp_perm_xx_pd(f2.vec)), _hlslpp_add_pd(f1.vec1, _hlslpp_perm_xx_pd(f2.vec)));
	}

	// Subtraction

	double1 operator - (const double1& f1, const double1& f2) { return double1(_hlslpp_sub_pd(f1.vec, f2.vec)); }
	double2 operator - (const double2& f1, const double2& f2) { return double2(_hlslpp_sub_pd(f1.vec, f2.vec)); }
	double3 operator - (const double3& f1, const double3& f2) { return double3(_hlslpp_sub_pd(f1.vec0, f2.vec0), _hlslpp_sub_pd(f1.vec1, f2.vec1)); }
	double4 operator - (const double4& f1, const double4& f2) { return double4(_hlslpp_sub_pd(f1.vec0, f2.vec0), _hlslpp_sub_pd(f1.vec1, f2.vec1)); }

	double2 operator - (const double2& f1, const double1& f2) { return double2(_hlslpp_sub_pd(f1.vec, _hlslpp_perm_xx_pd(f2.vec))); }
	double3 operator - (const double3& f1, const double1& f2)
	{
		return double3(_hlslpp_sub_pd(f1.vec0, _hlslpp_perm_xx_pd(f2.vec)), _hlslpp_sub_pd(f1.vec1, _hlslpp_perm_xx_pd(f2.vec)));
	}

	double4 operator - (const double4& f1, const double1& f2)
	{
		return double4(_hlslpp_sub_pd(f1.vec0, _hlslpp_perm_xx_pd(f2.vec)), _hlslpp_sub_pd(f1.vec1, _hlslpp_perm_xx_pd(f2.vec)));
	}

	// Multiplication

	double1 operator * (const double1& f1, const double1& f2) { return double1(_hlslpp_mul_pd(f1.vec, f2.vec)); }
	double2 operator * (const double2& f1, const double2& f2) { return double2(_hlslpp_mul_pd(f1.vec, f2.vec)); }
	double3 operator * (const double3& f1, const double3& f2) { return double3(_hlslpp_mul_pd(f1.vec0, f2.vec0), _hlslpp_mul_pd(f1.vec1, f2.vec1)); }
	double4 operator * (const double4& f1, const double4& f2) { return double4(_hlslpp_mul_pd(f1.vec0, f2.vec0), _hlslpp_mul_pd(f1.vec1, f2.vec1)); }

	double2 operator * (const double2& f1, const double1& f2) { return double2(_hlslpp_mul_pd(f1.vec, _hlslpp_perm_xx_pd(f2.vec))); }
	double3 operator * (const double3& f1, const double1& f2)
	{
		return double3(_hlslpp_mul_pd(f1.vec0, _hlslpp_perm_xx_pd(f2.vec)), _hlslpp_mul_pd(f1.vec1, _hlslpp_perm_xx_pd(f2.vec)));
	}

	double4 operator * (const double4& f1, const double1& f2)
	{
		return double4(_hlslpp_mul_pd(f1.vec0, _hlslpp_perm_xx_pd(f2.vec)), _hlslpp_mul_pd(f1.vec1, _hlslpp_perm_xx_pd(f2.vec)));
	}

	// Division

	double1 operator / (const double1& f1, const double1& f2) { return double1(_hlslpp_div_pd(f1.vec, f2.vec)); }
	double2 operator / (const double2& f1, const double2& f2) { return double2(_hlslpp_div_pd(f1.vec, f2.vec)); }
	double3 operator / (const double3& f1, const double3& f2) { return double3(_hlslpp_div_pd(f1.vec0, f2.vec0), _hlslpp_div_pd(f1.vec1, f2.vec1)); }
	double4 operator / (const double4& f1, const double4& f2) { return double4(_hlslpp_div_pd(f1.vec0, f2.vec0), _hlslpp_div_pd(f1.vec1, f2.vec1)); }

	double2 operator / (const double2& f1, const double1& f2) { return double2(_hlslpp_div_pd(f1.vec, _hlslpp_perm_xx_pd(f2.vec))); }
	double3 operator / (const double3& f1, const double1& f2)
	{
		return double3(_hlslpp_div_pd(f1.vec0, _hlslpp_perm_xx_pd(f2.vec)), _hlslpp_div_pd(f1.vec1, _hlslpp_perm_xx_pd(f2.vec)));
	}

	double4 operator / (const double4& f1, const double1& f2)
	{
		return double4(_hlslpp_div_pd(f1.vec0, _hlslpp_perm_xx_pd(f2.vec)), _hlslpp_div_pd(f1.vec1, _hlslpp_perm_xx_pd(f2.vec)));
	}

	double1 operator - (const double1& f) { return double1(_hlslpp_neg_pd(f.vec)); }
	double2 operator - (const double2& f) { return double2(_hlslpp_neg_pd(f.vec)); }
	double3 operator - (const double3& f) { return double3(_hlslpp_neg_pd(f.vec0), _hlslpp_neg_pd(f.vec1)); }
	double4 operator - (const double4& f) { return double4(_hlslpp_neg_pd(f.vec0), _hlslpp_neg_pd(f.vec1)); }

	double1& operator += (double1& f1, const double1& f2) { f1 = f1 + f2; return f1; }
	double2& operator += (double2& f1, const double2& f2) { f1 = f1 + f2; return f1; }
	double3& operator += (double3& f1, const double3& f2) { f1 = f1 + f2; return f1; }
	double4& operator += (double4& f1, const double4& f2) { f1 = f1 + f2; return f1; }

	double1& operator -= (double1& f1, const double1& f2) { f1 = f1 - f2; return f1; }
	double2& operator -= (double2& f1, const double2& f2) { f1 = f1 - f2; return f1; }
	double3& operator -= (double3& f1, const double3& f2) { f1 = f1 - f2; return f1; }
	double4& operator -= (double4& f1, const double4& f2) { f1 = f1 - f2; return f1; }

	double1& operator *= (double1& f1, const double1& f2) { f1 = f1 * f2; return f1; }
	double2& operator *= (double2& f1, const double2& f2) { f1 = f1 * f2; return f1; }
	double3& operator *= (double3& f1, const double3& f2) { f1 = f1 * f2; return f1; }
	double4& operator *= (double4& f1, const double4& f2) { f1 = f1 * f2; return f1; }

	double1& operator /= (double1& f1, const double1& f2) { f1 = f1 / f2; return f1; }
	double2& operator /= (double2& f1, const double2& f2) { f1 = f1 / f2; return f1; }
	double3& operator /= (double3& f1, const double3& f2) { f1 = f1 / f2; return f1; }
	double4& operator /= (double4& f1, const double4& f2) { f1 = f1 / f2; return f1; }

	//--------------------------------------------------------------------------------------------------------------------
	// double1 and dswizzle1 need special overloads to disambiguate between our operators/functions and built-in operators
	// and functions that are part of common headers such as cmath, math.h, algorithm, etc
	//--------------------------------------------------------------------------------------------------------------------

	template<typename T> hlslpp_enable_if_return(T, double1) operator + (const double1& f1, T f2) { return f1 + double1(f2); }
	template<typename T> hlslpp_enable_if_return(T, double2) operator + (const double2& f1, T f2) { return f1 + double2(f2); }
	template<typename T> hlslpp_enable_if_return(T, double3) operator + (const double3& f1, T f2) { return f1 + double3(f2); }
	template<typename T> hlslpp_enable_if_return(T, double4) operator + (const double4& f1, T f2) { return f1 + double4(f2); }

	template<typename T> hlslpp_enable_if_return(T, double1) operator + (T f1, const double1& f2) { return double1(f1) + f2; }
	template<typename T> hlslpp_enable_if_return(T, double2) operator + (T f1, const double2& f2) { return double2(f1) + f2; }
	template<typename T> hlslpp_enable_if_return(T, double3) operator + (T f1, const double3& f2) { return double3(f1) + f2; }
	template<typename T> hlslpp_enable_if_return(T, double4) operator + (T f1, const double4& f2) { return double4(f1) + f2; }

	template<typename T> hlslpp_enable_if_return(T, double1) operator - (const double1& f1, T f2) { return f1 - double1(f2); }
	template<typename T> hlslpp_enable_if_return(T, double2) operator - (const double2& f1, T f2) { return f1 - double2(f2); }
	template<typename T> hlslpp_enable_if_return(T, double3) operator - (const double3& f1, T f2) { return f1 - double3(f2); }
	template<typename T> hlslpp_enable_if_return(T, double4) operator - (const double4& f1, T f2) { return f1 - double4(f2); }

	template<typename T> hlslpp_enable_if_return(T, double1) operator - (T f1, const double1& f2) { return double1(f1) - f2; }
	template<typename T> hlslpp_enable_if_return(T, double2) operator - (T f1, const double2& f2) { return double2(f1) - f2; }
	template<typename T> hlslpp_enable_if_return(T, double3) operator - (T f1, const double3& f2) { return double3(f1) - f2; }
	template<typename T> hlslpp_enable_if_return(T, double4) operator - (T f1, const double4& f2) { return double4(f1) - f2; }

	template<typename T> hlslpp_enable_if_return(T, double1) operator * (const double1& f1, T f2) { return f1 * double1(f2); }
	template<typename T> hlslpp_enable_if_return(T, double2) operator * (const double2& f1, T f2) { return f1 * double2(f2); }
	template<typename T> hlslpp_enable_if_return(T, double3) operator * (const double3& f1, T f2) { return f1 * double3(f2); }
	template<typename T> hlslpp_enable_if_return(T, double4) operator * (const double4& f1, T f2) { return f1 * double4(f2); }

	template<typename T> hlslpp_enable_if_return(T, double1) operator * (T f1, const double1& f2) { return double1(f1) * f2; }
	template<typename T> hlslpp_enable_if_return(T, double2) operator * (T f1, const double2& f2) { return double2(f1) * f2; }
	template<typename T> hlslpp_enable_if_return(T, double3) operator * (T f1, const double3& f2) { return double3(f1) * f2; }
	template<typename T> hlslpp_enable_if_return(T, double4) operator * (T f1, const double4& f2) { return double4(f1) * f2; }

	template<typename T> hlslpp_enable_if_return(T, double1) operator / (const double1& f1, T f2) { return f1 / double1(f2); }
	template<typename T> hlslpp_enable_if_return(T, double2) operator / (const double2& f1, T f2) { return f1 / double2(f2); }
	template<typename T> hlslpp_enable_if_return(T, double3) operator / (const double3& f1, T f2) { return f1 / double3(f2); }
	template<typename T> hlslpp_enable_if_return(T, double4) operator / (const double4& f1, T f2) { return f1 / double4(f2); }

	template<typename T> hlslpp_enable_if_return(T, double1) operator / (T f1, const double1& f2) { return double1(f1) / f2; }
	template<typename T> hlslpp_enable_if_return(T, double2) operator / (T f1, const double2& f2) { return double2(f1) / f2; }
	template<typename T> hlslpp_enable_if_return(T, double3) operator / (T f1, const double3& f2) { return double3(f1) / f2; }
	template<typename T> hlslpp_enable_if_return(T, double4) operator / (T f1, const double4& f2) { return double4(f1) / f2; }

	template<int X> double1 operator + (const dswizzle1<X>& s, const double1& f) { return double1(s) + f; }
	template<int X> double1 operator - (const dswizzle1<X>& s, const double1& f) { return double1(s) - f; }
	template<int X> double1 operator * (const dswizzle1<X>& s, const double1& f) { return double1(s) * f; }
	template<int X> double1 operator / (const dswizzle1<X>& s, const double1& f) { return double1(s) / f; }

	template<int X> double1 operator - (const dswizzle1<X>& s) { return -double1(s); }

	template<int X>	dswizzle1<X>& operator += (dswizzle1<X>& s, const double1& f) { s = double1(s) + f; return s; }
	template<int X>	dswizzle1<X>& operator -= (dswizzle1<X>& s, const double1& f) { s = double1(s) - f; return s; }
	template<int X>	dswizzle1<X>& operator *= (dswizzle1<X>& s, const double1& f) { s = double1(s) * f; return s; }
	template<int X>	dswizzle1<X>& operator /= (dswizzle1<X>& s, const double1& f) { s = double1(s) / f; return s; }

	template<int X, int Y> dswizzle2<X, Y>& operator += (dswizzle2<X, Y>& s, const double2& f) { s = double2(s) + f; return s; }
	template<int X, int Y> dswizzle2<X, Y>& operator -= (dswizzle2<X, Y>& s, const double2& f) { s = double2(s) - f; return s; }
	template<int X, int Y> dswizzle2<X, Y>& operator *= (dswizzle2<X, Y>& s, const double2& f) { s = double2(s) * f; return s; }
	template<int X, int Y> dswizzle2<X, Y>& operator /= (dswizzle2<X, Y>& s, const double2& f) { s = double2(s) / f; return s; }

	template<int X, int Y, int Z> dswizzle3<X, Y, Z>& operator += (dswizzle3<X, Y, Z>& s, const double3& f) { s = double3(s) + f; return s; }
	template<int X, int Y, int Z> dswizzle3<X, Y, Z>& operator -= (dswizzle3<X, Y, Z>& s, const double3& f) { s = double3(s) - f; return s; }
	template<int X, int Y, int Z> dswizzle3<X, Y, Z>& operator *= (dswizzle3<X, Y, Z>& s, const double3& f) { s = double3(s) * f; return s; }
	template<int X, int Y, int Z> dswizzle3<X, Y, Z>& operator /= (dswizzle3<X, Y, Z>& s, const double3& f) { s = double3(s) / f; return s; }

	template<int X, int Y, int Z, int W> dswizzle4<X, Y, Z, W>& operator += (dswizzle4<X, Y, Z, W>& s, const double4& f) { s = double4(s) + f; return s; }
	template<int X, int Y, int Z, int W> dswizzle4<X, Y, Z, W>& operator -= (dswizzle4<X, Y, Z, W>& s, const double4& f) { s = double4(s) - f; return s; }
	template<int X, int Y, int Z, int W> dswizzle4<X, Y, Z, W>& operator *= (dswizzle4<X, Y, Z, W>& s, const double4& f) { s = double4(s) * f; return s; }
	template<int X, int Y, int Z, int W> dswizzle4<X, Y, Z, W>& operator /= (dswizzle4<X, Y, Z, W>& s, const double4& f) { s = double4(s) / f; return s; }

	hlslpp_inline double1 abs(const double1& f) { return double1(_hlslpp_abs_pd(f.vec)); }
	hlslpp_inline double2 abs(const double2& f) { return double2(_hlslpp_abs_pd(f.vec)); }
	hlslpp_inline double3 abs(const double3& f) { return double3(_hlslpp_abs_pd(f.vec0), _hlslpp_abs_pd(f.vec1)); }
	hlslpp_inline double4 abs(const double4& f) { return double4(_hlslpp_abs_pd(f.vec0), _hlslpp_abs_pd(f.vec1)); }

	hlslpp_inline bool all(const double1& f) { return _hlslpp_all1_pd(f.vec); }
	hlslpp_inline bool all(const double2& f) { return _hlslpp_all2_pd(f.vec); }
	hlslpp_inline bool all(const double3& f) { return _hlslpp_all3_pd(f.vec0, f.vec1); }
	hlslpp_inline bool all(const double4& f) { return _hlslpp_all4_pd(f.vec0, f.vec1); }
	
	hlslpp_inline bool any(const double1& f) { return _hlslpp_any1_pd(f.vec); }
	hlslpp_inline bool any(const double2& f) { return _hlslpp_any2_pd(f.vec); }
	hlslpp_inline bool any(const double3& f) { return _hlslpp_any3_pd(f.vec0, f.vec1); }
	hlslpp_inline bool any(const double4& f) { return _hlslpp_any4_pd(f.vec0, f.vec1); }

	double1 dot(const double1& f1, const double1& f2) { return f1 * f2; }
	double1 dot(const double2& f1, const double2& f2) { return double1(_hlslpp_dot2_pd(f1.vec, f2.vec)); }
	double1 dot(const double3& f1, const double3& f2) { return double1(_hlslpp_dot3_pd(f1.vec0, f1.vec1, f2.vec0, f2.vec1)); }
	double1 dot(const double4& f1, const double4& f2) { return double1(_hlslpp_dot4_pd(f1.vec0, f1.vec1, f2.vec0, f2.vec1)); }

	template<int X> hlslpp_inline double1 abs(const dswizzle1<X>& s) { return abs(double1(s)); }

	template<int X>
	dswizzle1<X>& dswizzle1<X>::operator = (const double1& f)
	{
		vec[X / 2] = _hlslpp_blend_pd(vec[X / 2], _hlslpp_perm_xx_pd(f.vec), HLSLPP_COMPONENT_X(X));
		return *this;
	}

	template<int X, int Y>
	dswizzle2<X, Y>& dswizzle2<X, Y>::operator = (const double2& f)
	{
		staticAsserts();
		
		HLSLPP_CONSTEXPR_IF((X < 2 && Y < 2) || (X >= 2 && Y >= 2))
		{
			vec[(X < 2 && Y < 2) ? 0 : 1] = _hlslpp_perm_pd(f.vec, HLSLPP_SHUFFLE_MASK_PD((X % 2) == 0 ? 0 : 1, (Y % 2) == 0 ? 0 : 1));
			//vec[(X < 2 && Y < 2) ? 0 : 1] = swizzle<0, 1, X, Y>(f.vec);
		}
		else
		{
			// Swizzle E and F into both 0 and 1
			n128d swizzledE = _hlslpp_perm_xx_pd(f.vec);
			n128d swizzledF = _hlslpp_perm_yy_pd(f.vec);

			// Blend with original vectors to preserve contents in remaining entries
			vec[X / 2] = _hlslpp_blend_pd(vec[X / 2], swizzledE, HLSLPP_BLEND_MASK_PD((X % 2) == 1, (X % 2) == 0));
			vec[Y / 2] = _hlslpp_blend_pd(vec[Y / 2], swizzledF, HLSLPP_BLEND_MASK_PD((Y % 2) == 1, (Y % 2) == 0));
		}

		return *this;
	}

	template<int X, int Y, int Z>
	dswizzle3<X, Y, Z>& dswizzle3<X, Y, Z>::operator = (const double3& f)
	{
		staticAsserts();
		swizzleblend<0, 1, 2, X, Y, Z>(f.vec0, f.vec1, vec[0], vec[1]);
		return *this;
	}

	template<int X, int Y, int Z, int W>
	dswizzle4<X, Y, Z, W>& dswizzle4<X, Y, Z, W>::operator = (const double4& f)
	{
		staticAsserts();
		swizzle<0, 1, 2, 3, X, Y, Z, W>(f.vec0, f.vec1, vec[0], vec[1]);
		return *this;
	}
}

#endif