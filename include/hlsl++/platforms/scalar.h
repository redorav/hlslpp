#pragma once

#include <math.h>
#include <stdint.h>

namespace hlslpp
{
	struct vector_float4
	{
		hlslpp_inline vector_float4() {}
		hlslpp_inline vector_float4(float f) : x(f), y(f), z(f), w(f) {}
		hlslpp_inline vector_float4(float f1, float f2, float f3, float f4) : x(f1), y(f2), z(f3), w(f4) {}

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			struct
			{
				float x, y, z, w;
			};

			struct
			{
				uint32_t ix, iy, iz, iw;
			};

			float m[4];
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct vector_int4
	{
		static const int32_t Max =  2147483647;
		static const int32_t Min = -2147483647 - 1;

		hlslpp_inline vector_int4() {}
		hlslpp_inline vector_int4(int32_t i) : x(i), y(i), z(i), w(i) {}
		hlslpp_inline vector_int4(int32_t i1, int32_t i2, int32_t i3, int32_t i4) : x(i1), y(i2), z(i3), w(i4) {}

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			struct
			{
				int32_t x, y, z, w;
			};

			int32_t m[4];
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct vector_uint4
	{
		static const uint32_t Max = 4294967295;

		hlslpp_inline vector_uint4() {}
		hlslpp_inline vector_uint4(uint32_t i) : x(i), y(i), z(i), w(i) {}
		hlslpp_inline vector_uint4(uint32_t i1, uint32_t i2, uint32_t i3, uint32_t i4) : x(i1), y(i2), z(i3), w(i4) {}

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			struct
			{
				uint32_t x, y, z, w;
			};

			uint32_t m[4];
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	typedef vector_float4 n128;
	typedef vector_int4 n128i;
	typedef vector_uint4 n128u;

	//------
	// Float
	//------

	hlslpp_inline vector_float4 _hlslpp_set1_ps(float x) { return vector_float4(x); }
	hlslpp_inline vector_float4 _hlslpp_set_ps(float x, float y, float z, float w) { return vector_float4(x, y, z, w); }
	hlslpp_inline vector_float4 _hlslpp_setzero_ps() { return vector_float4(0.0f, 0.0f, 0.0f, 0.0f); }

	hlslpp_inline vector_float4 _hlslpp_add_ps(const vector_float4& v1, const vector_float4& v2) { return vector_float4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w); }
	hlslpp_inline vector_float4 _hlslpp_sub_ps(const vector_float4& v1, const vector_float4& v2) { return vector_float4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w); }
	hlslpp_inline vector_float4 _hlslpp_mul_ps(const vector_float4& v1, const vector_float4& v2) { return vector_float4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w); }

HLSLPP_WARNING_POTENTIAL_DIVIDE_BY_0_BEGIN
	hlslpp_inline vector_float4 _hlslpp_div_ps(const vector_float4& v1, const vector_float4& v2) { return vector_float4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w); }
HLSLPP_WARNING_POTENTIAL_DIVIDE_BY_0_END

	hlslpp_inline vector_float4 _hlslpp_rcp_ps(const vector_float4& v) { return vector_float4(1.0f / v.x, 1.0f / v.y, 1.0f / v.z, 1.0f / v.w); }

	hlslpp_inline vector_float4 _hlslpp_neg_ps(const vector_float4& v) { return vector_float4(-v.x, -v.y, -v.z, -v.w); }

	hlslpp_inline vector_float4 _hlslpp_madd_ps(const vector_float4& v1, const vector_float4& v2, const vector_float4& v3)
	{
		return vector_float4(v1.x * v2.x + v3.x, v1.y * v2.y + v3.y, v1.z * v2.z + v3.z, v1.w * v2.w + v3.w);
	}

	hlslpp_inline vector_float4 _hlslpp_msub_ps(const vector_float4& v1, const vector_float4& v2, const vector_float4& v3)
	{
		return vector_float4(v1.x * v2.x - v3.x, v1.y * v2.y - v3.y, v1.z * v2.z - v3.z, v1.w * v2.w - v3.w);
	}

	hlslpp_inline vector_float4 _hlslpp_subm_ps(const vector_float4& v1, const vector_float4& v2, const vector_float4& v3)
	{
		return vector_float4(v1.x - v2.x * v3.x, v1.y - v2.y * v3.y, v1.z - v2.z * v3.z, v1.w - v2.w * v3.w);
	}

	hlslpp_inline vector_float4 _hlslpp_abs_ps(const vector_float4& v)
	{
		return vector_float4(
			v.x >= 0.0f ? v.x : -v.x,
			v.y >= 0.0f ? v.y : -v.y,
			v.z >= 0.0f ? v.z : -v.z,
			v.w >= 0.0f ? v.w : -v.w);
	}

	hlslpp_inline vector_float4 _hlslpp_sqrt_ps(const vector_float4& v) { return vector_float4(sqrtf(v.x), sqrtf(v.y), sqrtf(v.z), sqrtf(v.w)); }

	hlslpp_inline vector_float4 _hlslpp_rsqrt_ps(const vector_float4& v)
	{
		return vector_float4(1.0f / sqrtf(v.x), 1.0f / sqrtf(v.y), 1.0f / sqrtf(v.z), 1.0f / sqrtf(v.w));
	}

	hlslpp_inline vector_float4 _hlslpp_cmpeq_ps(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(v1.x == v2.x ? fffMask._f32 : 0, v1.y == v2.y ? fffMask._f32 : 0, v1.z == v2.z ? fffMask._f32 : 0, v1.w == v2.w ? fffMask._f32 : 0);
	}

	hlslpp_inline vector_float4 _hlslpp_cmpneq_ps(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(v1.x != v2.x ? fffMask._f32 : 0, v1.y != v2.y ? fffMask._f32 : 0, v1.z != v2.z ? fffMask._f32 : 0, v1.w != v2.w ? fffMask._f32 : 0);
	}

	hlslpp_inline vector_float4 _hlslpp_cmpgt_ps(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(v1.x > v2.x ? fffMask._f32 : 0, v1.y > v2.y ? fffMask._f32 : 0, v1.z > v2.z ? fffMask._f32 : 0, v1.w > v2.w ? fffMask._f32 : 0);
	}

	hlslpp_inline vector_float4 _hlslpp_cmpge_ps(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(v1.x >= v2.x ? fffMask._f32 : 0, v1.y >= v2.y ? fffMask._f32 : 0, v1.z >= v2.z ? fffMask._f32 : 0, v1.w >= v2.w ? fffMask._f32 : 0);
	}

	hlslpp_inline vector_float4 _hlslpp_cmplt_ps(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(v1.x < v2.x ? fffMask._f32 : 0, v1.y < v2.y ? fffMask._f32 : 0, v1.z < v2.z ? fffMask._f32 : 0, v1.w < v2.w ? fffMask._f32 : 0);
	}

	hlslpp_inline vector_float4 _hlslpp_cmple_ps(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(v1.x <= v2.x ? fffMask._f32 : 0, v1.y <= v2.y ? fffMask._f32 : 0, v1.z <= v2.z ? fffMask._f32 : 0, v1.w <= v2.w ? fffMask._f32 : 0);
	}

	hlslpp_inline vector_float4 _hlslpp_max_ps(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(v1.x > v2.x ? v1.x : v2.x, v1.y > v2.y ? v1.y : v2.y, v1.z > v2.z ? v1.z : v2.z, v1.w > v2.w ? v1.w : v2.w);
	}

	hlslpp_inline vector_float4 _hlslpp_min_ps(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(v1.x < v2.x ? v1.x : v2.x, v1.y < v2.y ? v1.y : v2.y, v1.z < v2.z ? v1.z : v2.z, v1.w < v2.w ? v1.w : v2.w);
	}

	hlslpp_inline vector_float4 select4(const vector_float4& v1, const vector_float4& v2, const vector_float4& msk)
	{
		return vector_float4(msk.x == 0.0f ? v1.x : v2.x,
			msk.y == 0.0f ? v1.y : v2.y,
			msk.z == 0.0f ? v1.z : v2.z,
			msk.w == 0.0f ? v1.w : v2.w);
	}

	// Bit-select val1 and val2 based on the contents of the mask
#define _hlslpp_sel_ps(x, y, msk)				select4((x), (y), (msk))

	template<int A, int B, int C, int D>
	hlslpp_inline vector_float4 blend4(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(A == 1 ? v2.m[0] : v1.m[0], B == 1 ? v2.m[1] : v1.m[1], C == 1 ? v2.m[2] : v1.m[2], D == 1 ? v2.m[3] : v1.m[3]);
	}

#define _hlslpp_blend_ps(x, y, msk)				blend4<(msk) & 1, ((msk) >> 1) & 1, ((msk) >> 2) & 1, ((msk) >> 3) & 1>((x), (y))

	namespace internal
	{
		hlslpp_inline float trunc_float(float f)
		{
			return (float)(int)f;
		}

		hlslpp_inline float floor_float(float f)
		{
			float trunc = (float)(int)f;
			return trunc > f ? trunc - 1.0f : trunc;
		}

		hlslpp_inline float ceil_float(float f)
		{
			float trunc = (float)(int)f;
			return trunc < f ? trunc + 1.0f : trunc;
		}

		hlslpp_inline float round_float(float f)
		{
			float trunc = (float)(int)f;
			float frac = f - trunc;
			float abs_frac = frac >= 0.0f ? frac : -frac;
			return abs_frac <= 0.5f ? trunc : f >= 0.0f ? trunc + 1.0f : trunc - 1.0f;
		}
	};

	hlslpp_inline vector_float4 _hlslpp_trunc_ps(const vector_float4& v)
	{
		return vector_float4(internal::trunc_float(v.x), internal::trunc_float(v.y), internal::trunc_float(v.z), internal::trunc_float(v.w));
	}

	hlslpp_inline vector_float4 _hlslpp_floor_ps(const vector_float4& v)
	{
		return vector_float4(internal::floor_float(v.x), internal::floor_float(v.y), internal::floor_float(v.z), internal::floor_float(v.w));
	}

	hlslpp_inline vector_float4 _hlslpp_ceil_ps(const vector_float4& v)
	{
		return vector_float4(internal::ceil_float(v.x), internal::ceil_float(v.y), internal::ceil_float(v.z), internal::ceil_float(v.w));
	}

	hlslpp_inline vector_float4 _hlslpp_round_ps(const vector_float4& v)
	{
		return vector_float4(internal::round_float(v.x), internal::round_float(v.y), internal::round_float(v.z), internal::round_float(v.w));
	}

	hlslpp_inline vector_float4 _hlslpp_frac_ps(const vector_float4& v)
	{
		float fracX, fracY, fracZ, fracW;
		modff(v.x, &fracX);
		modff(v.y, &fracY);
		modff(v.z, &fracZ);
		modff(v.w, &fracW);
		return vector_float4(fracX, fracY, fracZ, fracW);
	}

	hlslpp_inline vector_float4 _hlslpp_clamp_ps(const vector_float4& v1, const vector_float4& min, const vector_float4& max)
	{
		return vector_float4(v1.x > max.x ? max.x : v1.x < min.x ? min.x : v1.x,
			v1.y > max.y ? max.y : v1.y < min.y ? min.y : v1.y,
			v1.z > max.z ? max.z : v1.z < min.z ? min.z : v1.z,
			v1.w > max.w ? max.w : v1.w < min.w ? min.w : v1.w);
	}

	hlslpp_inline vector_float4 _hlslpp_sat_ps(const vector_float4& v)
	{
		return vector_float4(v.x > 1.0f ? 1.0f : v.x < 0.0f ? 0.0f : v.x,
			v.y > 1.0f ? 1.0f : v.y < 0.0f ? 0.0f : v.y,
			v.z > 1.0f ? 1.0f : v.z < 0.0f ? 0.0f : v.z,
			v.w > 1.0f ? 1.0f : v.w < 0.0f ? 0.0f : v.w);
	}

	hlslpp_inline vector_float4 _hlslpp_sign_ps(const vector_float4& v)
	{
		return vector_float4(v.x > 0.0f ? 1.0f : -1.0f, v.y > 0.0f ? 1.0f : -1.0f, v.z > 0.0f ? 1.0f : -1.0f, v.w > 0.0f ? 1.0f : -1.0f);
	}

	hlslpp_inline vector_float4 _hlslpp_and_ps(const vector_float4& v1, const vector_float4& v2)
	{
		uint32_t ix = v1.ix & v2.ix; uint32_t iy = v1.iy & v2.iy;
		uint32_t iz = v1.iz & v2.iz; uint32_t iw = v1.iw & v2.iw;

		return vector_float4(*(const float*)(&ix), *(const float*)(&iy), *(const float*)(&iz), *(const float*)(&iw));
	}

	hlslpp_inline vector_float4 _hlslpp_andnot_ps(const vector_float4& v1, const vector_float4& v2)
	{
		uint32_t ix = (~v1.ix) & v2.ix; uint32_t iy = (~v1.iy) & v2.iy;
		uint32_t iz = (~v1.iz) & v2.iz; uint32_t iw = (~v1.iw) & v2.iw;

		return vector_float4(*(const float*)(&ix), *(const float*)(&iy), *(const float*)(&iz), *(const float*)(&iw));
	}

	hlslpp_inline vector_float4 _hlslpp_not_ps(const vector_float4& v1)
	{
		uint32_t ix = ~v1.ix; uint32_t iy = ~v1.iy; uint32_t iz = ~v1.iz; uint32_t iw = ~v1.iw;
		return vector_float4(*(const float*)(&ix), *(const float*)(&iy), *(const float*)(&iz), *(const float*)(&iw));
	}

	hlslpp_inline vector_float4 _hlslpp_or_ps(const vector_float4& v1, const vector_float4& v2)
	{
		uint32_t ix = v1.ix | v2.ix; uint32_t iy = v1.iy | v2.iy;
		uint32_t iz = v1.iz | v2.iz; uint32_t iw = v1.iw | v2.iw;

		return vector_float4(*(const float*)(&ix), *(const float*)(&iy), *(const float*)(&iz), *(const float*)(&iw));
	}

	hlslpp_inline vector_float4 _hlslpp_xor_ps(const vector_float4& v1, const vector_float4& v2)
	{
		uint32_t ix = v1.ix ^ v2.ix; uint32_t iy = v1.iy ^ v2.iy;
		uint32_t iz = v1.iz ^ v2.iz; uint32_t iw = v1.iw ^ v2.iw;

		return vector_float4(*(const float*)(&ix), *(const float*)(&iy), *(const float*)(&iz), *(const float*)(&iw));
	}

	hlslpp_inline vector_float4 _hlslpp_movelh_ps(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(v1.x, v1.y, v2.x, v2.y);
	}

	hlslpp_inline vector_float4 _hlslpp_movehl_ps(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(v2.z, v2.w, v1.z, v1.w);
	}

	hlslpp_inline vector_float4 _hlslpp_movehdup_ps(const vector_float4& v)
	{
		return vector_float4(v.y, v.y, v.w, v.w);
	}

	template<int A, int B, int C, int D>
	hlslpp_inline vector_float4 perm4(const vector_float4& v)
	{
		return vector_float4(v.m[A], v.m[B], v.m[C], v.m[D]);
	}

	template<int X, int Y, int A, int B>
	hlslpp_inline vector_float4 shuf4(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(v1.m[X], v1.m[Y], v2.m[A], v2.m[B]);
	}

	#define _hlslpp_perm_ps(x, X, Y, Z, W)			perm4<X, Y, Z, W>((x))

	#define _hlslpp_shuffle_ps(x, y, X, Y, A, B)	shuf4<X, Y, A, B>((x), (y))

	hlslpp_inline vector_float4 _hlslpp_unpacklo_ps(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(v1.x, v2.x, v1.y, v2.y);
	}

	hlslpp_inline vector_float4 _hlslpp_unpackhi_ps(const vector_float4& v1, const vector_float4& v2)
	{
		return vector_float4(v1.z, v2.z, v1.w, v2.w);
	}

	hlslpp_inline vector_float4 _hlslpp_dot4_ps(const vector_float4& v1, const vector_float4& v2)
	{
		// The odd way this is written (using two floats) is faster than having a single chain of A + B + C + D
		float f1 = (v1.x * v2.x) + (v1.y * v2.y);
		float f2 = (v1.z * v2.z) + (v1.w * v2.w);
		return vector_float4(f1 + f2, 0.0f, 0.0f, 0.0f);
	}

	hlslpp_inline bool _hlslpp_any1_ps(const vector_float4& v)
	{
		return v.x != 0.0f;
	}

	hlslpp_inline bool _hlslpp_any2_ps(const vector_float4& v)
	{
		return v.x != 0.0f || v.y != 0.0f;
	}

	hlslpp_inline bool _hlslpp_any3_ps(const vector_float4& v)
	{
		return v.x != 0.0f || v.y != 0.0f || v.z != 0.0f;
	}

	hlslpp_inline bool _hlslpp_any4_ps(const vector_float4& v)
	{
		return v.x != 0.0f || v.y != 0.0f || v.z != 0.0f || v.w != 0.0f;
	}

	hlslpp_inline bool _hlslpp_all1_ps(const vector_float4& v)
	{
		return v.x != 0.0f;
	}

	hlslpp_inline bool _hlslpp_all2_ps(const vector_float4& v)
	{
		return v.x != 0.0f && v.y != 0.0f;
	}

	hlslpp_inline bool _hlslpp_all3_ps(const vector_float4& v)
	{
		return v.x != 0.0f && v.y != 0.0f && v.z != 0.0f;
	}

	hlslpp_inline bool _hlslpp_all4_ps(const vector_float4& v)
	{
		return v.x != 0.0f && v.y != 0.0f && v.z != 0.0f && v.w != 0.0f;
	}

#define HLSLPP_ACOS_IMPLEMENTATION

	hlslpp_inline vector_float4 _hlslpp_acos_ps(const vector_float4& v)
	{
		return vector_float4(acosf(v.x), acosf(v.y), acosf(v.z), acosf(v.w));
	}

#define HLSLPP_ASIN_IMPLEMENTATION

	hlslpp_inline vector_float4 _hlslpp_asin_ps(const vector_float4& v)
	{
		return vector_float4(asinf(v.x), asinf(v.y), asinf(v.z), asinf(v.w));
	}

#define HLSLPP_ATAN_IMPLEMENTATION

	hlslpp_inline vector_float4 _hlslpp_atan_ps(const vector_float4& v)
	{
		return vector_float4(atanf(v.x), atanf(v.y), atanf(v.z), atanf(v.w));
	}

#define HLSLPP_ATAN2_IMPLEMENTATION

	hlslpp_inline vector_float4 _hlslpp_atan2_ps(const vector_float4& y, const vector_float4& x)
	{
		return vector_float4(atan2f(y.x, x.x), atan2f(y.y, x.y), atan2f(y.z, x.z), atan2f(y.w, x.w));
	}

#define HLSLPP_SIN_IMPLEMENTATION

	hlslpp_inline vector_float4 _hlslpp_sin_ps(const vector_float4& v)
	{
		return vector_float4(sinf(v.x), sinf(v.y), sinf(v.z), sinf(v.w));
	}

#define HLSLPP_COS_IMPLEMENTATION

	hlslpp_inline vector_float4 _hlslpp_cos_ps(vector_float4 v)
	{
		return vector_float4(cosf(v.x), cosf(v.y), cosf(v.z), cosf(v.w));
	}

#define HLSLPP_TAN_IMPLEMENTATION

	hlslpp_inline vector_float4 _hlslpp_tan_ps(const vector_float4& v)
	{
		return vector_float4(tanf(v.x), tanf(v.y), tanf(v.z), tanf(v.w));
	}

#define HLSLPP_SINH_IMPLEMENTATION

	hlslpp_inline vector_float4 _hlslpp_sinh_ps(const vector_float4& v)
	{
		return vector_float4(sinhf(v.x), sinhf(v.y), sinhf(v.z), sinhf(v.w));
	}

#define HLSLPP_COSH_IMPLEMENTATION

	hlslpp_inline vector_float4 _hlslpp_cosh_ps(const vector_float4& v)
	{
		return vector_float4(coshf(v.x), coshf(v.y), coshf(v.z), coshf(v.w));
	}

#define HLSLPP_TANH_IMPLEMENTATION

	hlslpp_inline vector_float4 _hlslpp_tanh_ps(const vector_float4& v)
	{
		return vector_float4(tanhf(v.x), tanhf(v.y), tanhf(v.z), tanhf(v.w));
	}

	//-----------------
	// Float Store/Load
	//-----------------

	hlslpp_inline void _hlslpp_store1_ps(float* p, const vector_float4& v) { p[0] = v.x; }
	hlslpp_inline void _hlslpp_store2_ps(float* p, const vector_float4& v) { p[0] = v.x; p[1] = v.y; }
	hlslpp_inline void _hlslpp_store3_ps(float* p, const vector_float4& v) { p[0] = v.x; p[1] = v.y; p[2] = v.z; }
	hlslpp_inline void _hlslpp_store4_ps(float* p, const vector_float4& v) { p[0] = v.x; p[1] = v.y; p[2] = v.z; p[3] = v.w; }

	hlslpp_inline void _hlslpp_store3x3_ps(float* p, const vector_float4& v1, const vector_float4& v2, const vector_float4& v3)
	{
		p[0] = v1.x; p[1] = v1.y; p[2] = v1.z;
		p[3] = v2.x; p[4] = v2.y; p[5] = v2.z;
		p[6] = v3.x; p[7] = v3.y; p[8] = v3.z;
	}

	hlslpp_inline void _hlslpp_store4x4_ps(float* p, const vector_float4& v1, const vector_float4& v2, const vector_float4& v3, const vector_float4& v4)
	{
		p[0] = v1.x; p[1] = v1.y; p[2] = v1.z; p[3] = v1.w;
		p[4] = v2.x; p[5] = v2.y; p[6] = v2.z; p[7] = v2.w;
		p[8] = v3.x; p[9] = v3.y; p[10] = v3.z; p[11] = v3.w;
		p[12] = v4.x; p[13] = v4.y; p[14] = v4.z; p[15] = v4.w;
	}

	hlslpp_inline void _hlslpp_load1_ps(float* p, n128& v) { v.x = p[0]; }
	hlslpp_inline void _hlslpp_load2_ps(float* p, n128& v) { v.x = p[0]; v.y = p[1]; }
	hlslpp_inline void _hlslpp_load3_ps(float* p, n128& v) { v.x = p[0]; v.y = p[1]; v.z = p[2]; }
	hlslpp_inline void _hlslpp_load4_ps(float* p, n128& v) { v.x = p[0]; v.y = p[1]; v.z = p[2]; v.w = p[3]; }

	hlslpp_inline void _hlslpp_load3x3_ps(float* p, n128& v1, n128& v2, n128& v3)
	{
		v1.x = p[0]; v1.y = p[1]; v1.z = p[2];
		v2.x = p[3]; v2.y = p[4]; v2.z = p[5];
		v3.x = p[6]; v3.y = p[7]; v3.z = p[8];
	}

	hlslpp_inline void _hlslpp_load4x4_ps(float* p, n128& v1, n128& v2, n128& v3, n128& v4)
	{
		v1.x = p[0];  v1.y = p[1];  v1.z = p[2];  v1.w = p[3];
		v2.x = p[4];  v2.y = p[5];  v2.z = p[6];  v2.w = p[7];
		v3.x = p[8];  v3.y = p[9];  v3.z = p[10]; v3.w = p[11];
		v4.x = p[12]; v4.y = p[13]; v4.z = p[14]; v4.w = p[15];
	}

	//--------
	// Integer
	//--------

	hlslpp_inline vector_int4 _hlslpp_set1_epi32(int32_t x) { return vector_int4(x); }

	hlslpp_inline vector_int4 _hlslpp_set_epi32(int32_t x, int32_t y, int32_t z, int32_t w) { return vector_int4(x, y, z, w); }

	hlslpp_inline vector_int4 _hlslpp_setzero_epi32() { return vector_int4(0, 0, 0, 0); }

	hlslpp_inline vector_int4 _hlslpp_add_epi32(const vector_int4& v1, const vector_int4& v2) { return vector_int4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w); }

	hlslpp_inline vector_int4 _hlslpp_sub_epi32(const vector_int4& v1, const vector_int4& v2) { return vector_int4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w); }

	hlslpp_inline vector_int4 _hlslpp_mul_epi32(const vector_int4& v1, const vector_int4& v2) { return vector_int4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w); }

	hlslpp_inline vector_int4 _hlslpp_div_epi32(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4
		(
			v2.x != 0 ? v1.x / v2.x : (v1.x > 0 ? v1.Max : v1.Min),
			v2.y != 0 ? v1.y / v2.y : (v1.y > 0 ? v1.Max : v1.Min),
			v2.z != 0 ? v1.z / v2.z : (v1.z > 0 ? v1.Max : v1.Min),
			v2.w != 0 ? v1.w / v2.w : (v1.w > 0 ? v1.Max : v1.Min)
		);
	}

	hlslpp_inline vector_int4 _hlslpp_neg_epi32(const vector_int4& v) { return vector_int4(-v.x, -v.y, -v.z, -v.w); }

	hlslpp_inline vector_int4 _hlslpp_madd_epi32(const vector_int4& v1, const vector_int4& v2, const vector_int4& v3)
	{
		return vector_int4(v1.x * v2.x + v3.x, v1.y * v2.y + v3.y, v1.z * v2.z + v3.z, v1.w * v2.w + v3.w);
	}

	hlslpp_inline vector_int4 _hlslpp_msub_epi32(const vector_int4& v1, const vector_int4& v2, const vector_int4& v3)
	{
		return vector_int4(v1.x * v2.x - v3.x, v1.y * v2.y - v3.y, v1.z * v2.z - v3.z, v1.w * v2.w - v3.w);
	}

	hlslpp_inline vector_int4 _hlslpp_subm_epi32(const vector_int4& v1, const vector_int4& v2, const vector_int4& v3)
	{
		return vector_int4(v1.x - v2.x * v3.x, v1.y - v2.y * v3.y, v1.z - v2.z * v3.z, v1.w - v2.w * v3.w);
	}

	hlslpp_inline vector_int4 _hlslpp_abs_epi32(const vector_int4& v) { return vector_int4(labs(v.x), labs(v.y), labs(v.z), labs(v.w)); }

	hlslpp_inline vector_int4 _hlslpp_cmpeq_epi32(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x == v2.x ? 0xffffffff : 0, v1.y == v2.y ? 0xffffffff : 0, v1.z == v2.z ? 0xffffffff : 0, v1.w == v2.w ? 0xffffffff : 0);
	}

	hlslpp_inline vector_int4 _hlslpp_cmpneq_epi32(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x != v2.x ? 0xffffffff : 0, v1.y != v2.y ? 0xffffffff : 0, v1.z != v2.z ? 0xffffffff : 0, v1.w != v2.w ? 0xffffffff : 0);
	}

	hlslpp_inline vector_int4 _hlslpp_cmpgt_epi32(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x > v2.x ? 0xffffffff : 0, v1.y > v2.y ? 0xffffffff : 0, v1.z > v2.z ? 0xffffffff : 0, v1.w > v2.w ? 0xffffffff : 0);
	}

	hlslpp_inline vector_int4 _hlslpp_cmpge_epi32(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x >= v2.x ? 0xffffffff : 0, v1.y >= v2.y ? 0xffffffff : 0, v1.z >= v2.z ? 0xffffffff : 0, v1.w >= v2.w ? 0xffffffff : 0);
	}

	hlslpp_inline vector_int4 _hlslpp_cmplt_epi32(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x < v2.x ? 0xffffffff : 0, v1.y < v2.y ? 0xffffffff : 0, v1.z < v2.z ? 0xffffffff : 0, v1.w < v2.w ? 0xffffffff : 0);
	}

	hlslpp_inline vector_int4 _hlslpp_cmple_epi32(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x <= v2.x ? 0xffffffff : 0, v1.y <= v2.y ? 0xffffffff : 0, v1.z <= v2.z ? 0xffffffff : 0, v1.w <= v2.w ? 0xffffffff : 0);
	}

	hlslpp_inline vector_int4 _hlslpp_max_epi32(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x > v2.x ? v1.x : v2.x, v1.y > v2.y ? v1.y : v2.y, v1.z > v2.z ? v1.z : v2.z, v1.w > v2.w ? v1.w : v2.w);
	}

	hlslpp_inline vector_int4 _hlslpp_min_epi32(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x < v2.x ? v1.x : v2.x, v1.y < v2.y ? v1.y : v2.y, v1.z < v2.z ? v1.z : v2.z, v1.w < v2.w ? v1.w : v2.w);
	}

	hlslpp_inline vector_int4 _hlslpp_clamp_epi32(const vector_int4& v1, const vector_int4& min, const vector_int4& max)
	{
		return vector_int4(v1.x > max.x ? max.x : v1.x < min.x ? min.x : v1.x,
			v1.y > max.y ? max.y : v1.y < min.y ? min.y : v1.y,
			v1.z > max.z ? max.z : v1.z < min.z ? min.z : v1.z,
			v1.w > max.w ? max.w : v1.w < min.w ? min.w : v1.w);
	}

	hlslpp_inline vector_int4 _hlslpp_sat_epi32(const vector_int4& v1)
	{
		return vector_int4(v1.x > 1 ? 1 : v1.x < 0 ? 0 : v1.x,
			v1.y > 1 ? 1 : v1.y < 0 ? 0 : v1.y,
			v1.z > 1 ? 1 : v1.z < 0 ? 0 : v1.z,
			v1.w > 1 ? 1 : v1.w < 0 ? 0 : v1.w);
	}

	hlslpp_inline vector_int4 _hlslpp_and_si128(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x & v2.x, v1.y & v2.y, v1.z & v2.z, v1.w & v2.w);
	}

	hlslpp_inline vector_int4 _hlslpp_andnot_si128(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(~v1.x & v2.x, ~v1.y & v2.y, ~v1.z & v2.z, ~v1.w & v2.w);
	}

	hlslpp_inline vector_int4 _hlslpp_not_si128(const vector_int4& v1)
	{
		return vector_int4(~v1.x, ~v1.y, ~v1.z, ~v1.w);
	}

	hlslpp_inline vector_int4 _hlslpp_or_si128(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x | v2.x, v1.y | v2.y, v1.z | v2.z, v1.w | v2.w);
	}

	hlslpp_inline vector_int4 _hlslpp_xor_si128(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x ^ v2.x, v1.y ^ v2.y, v1.z ^ v2.z, v1.w ^ v2.w);
	}

	template<int A, int B, int C, int D>
	hlslpp_inline vector_int4 perm4(const vector_int4& v)
	{
		return vector_int4(v.m[A], v.m[B], v.m[C], v.m[D]);
	}

	template<int A, int B, int C, int D>
	hlslpp_inline vector_int4 shuf4(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.m[A], v1.m[B], v2.m[C], v2.m[D]);
	}

	// https://stackoverflow.com/questions/13153584/mm-shuffle-ps-equivalent-for-integer-vectors-m128i
	#define _hlslpp_perm_epi32(x, X, Y, Z, W)		perm4<X, Y, Z, W>((x))
	#define _hlslpp_shuffle_epi32(x, y, X, Y, A, B)	shuf4<X, Y, A, B>((x), (y))

	hlslpp_inline vector_int4 select4(const vector_int4& v1, const vector_int4& v2, const vector_int4& msk)
	{
		return vector_int4(msk.x == 0 ? v1.x : v2.x, msk.y == 0 ? v1.y : v2.y, msk.z == 0 ? v1.z : v2.z, msk.w == 0 ? v1.w : v2.w);
	}

	// Bit-select val1 and val2 based on the contents of the mask
	#define _hlslpp_sel_epi32(x, y, msk)				select4((x), (y), (msk))

	template<int A, int B, int C, int D>
	hlslpp_inline vector_int4 blend4(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(A == 1 ? v2.m[0] : v1.m[0], B == 1 ? v2.m[1] : v1.m[1], C == 1 ? v2.m[2] : v1.m[2], D == 1 ? v2.m[3] : v1.m[3]);
	}

	#define _hlslpp_blend_epi32(x, y, msk)			blend4<(msk) & 1, ((msk) >> 1) & 1, ((msk) >> 2) & 1, ((msk) >> 3) & 1>((x), (y))

	hlslpp_inline vector_int4 _hlslpp_castps_si128(const vector_float4& v)
	{
		return vector_int4(reinterpret_cast<const int32_t&>(v.x), reinterpret_cast<const int32_t&>(v.y), reinterpret_cast<const int32_t&>(v.z), reinterpret_cast<const int32_t&>(v.w));
	}

	hlslpp_inline vector_float4 _hlslpp_castsi128_ps(const vector_int4& v)
	{
		return vector_float4(reinterpret_cast<const float&>(v.x), reinterpret_cast<const float&>(v.y), reinterpret_cast<const float&>(v.z), reinterpret_cast<const float&>(v.w));
	}

	hlslpp_inline vector_float4 _hlslpp_cvtepi32_ps(const vector_int4& v)
	{
		return vector_float4((float)(v.x), (float)(v.y), (float)(v.z), (float)(v.w));
	}

	hlslpp_inline vector_int4 _hlslpp_cvttps_epi32(const vector_float4& v)
	{
		return vector_int4((int32_t)(v.x), (int32_t)(v.y), (int32_t)(v.z), (int32_t)(v.w));
	}

	hlslpp_inline vector_int4 _hlslpp_sll_epi32(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x << v2.x, v1.y << v2.x, v1.z << v2.x, v1.w << v2.x);
	}

	hlslpp_inline vector_int4 _hlslpp_slli_epi32(const vector_int4& v, const int32_t i)
	{
		return vector_int4(v.x << i, v.y << i, v.z << i, v.w << i);
	}

	hlslpp_inline vector_int4 _hlslpp_srl_epi32(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x >> v2.x, v1.y >> v2.x, v1.z >> v2.x, v1.w >> v2.x);
	}

	hlslpp_inline vector_int4 _hlslpp_srli_epi32(const vector_int4& v, const int32_t i)
	{
		return vector_int4(v.x >> i, v.y >> i, v.z >> i, v.w >> i);
	}

	hlslpp_inline vector_int4 _hlslpp_sllv_epi32(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x << v2.x, v1.y << v2.y, v1.z << v2.z, v1.w << v2.w);
	}

	hlslpp_inline vector_int4 _hlslpp_srlv_epi32(const vector_int4& v1, const vector_int4& v2)
	{
		return vector_int4(v1.x >> v2.x, v1.y >> v2.y, v1.z >> v2.z, v1.w >> v2.w);
	}

	hlslpp_inline bool _hlslpp_any1_epi32(const vector_int4& v) { return v.x != 0; }
	hlslpp_inline bool _hlslpp_any2_epi32(const vector_int4& v) { return v.x != 0 || v.y != 0; }
	hlslpp_inline bool _hlslpp_any3_epi32(const vector_int4& v) { return v.x != 0 || v.y != 0 || v.z != 0; }
	hlslpp_inline bool _hlslpp_any4_epi32(const vector_int4& v) { return v.x != 0 || v.y != 0 || v.z != 0 || v.w != 0; }

	hlslpp_inline bool _hlslpp_all1_epi32(const vector_int4& v) { return v.x != 0; }
	hlslpp_inline bool _hlslpp_all2_epi32(const vector_int4& v) { return v.x != 0 && v.y != 0; }
	hlslpp_inline bool _hlslpp_all3_epi32(const vector_int4& v) { return v.x != 0 && v.y != 0 && v.z != 0; }
	hlslpp_inline bool _hlslpp_all4_epi32(const vector_int4& v) { return v.x != 0 && v.y != 0 && v.z != 0 && v.w != 0; }


	//-------------------
	// Integer Store/Load
	//-------------------

	hlslpp_inline void _hlslpp_store1_epi32(int32_t* p, const vector_int4& v) { p[0] = v.x; }
	hlslpp_inline void _hlslpp_store2_epi32(int32_t* p, const vector_int4& v) { p[0] = v.x; p[1] = v.y; }
	hlslpp_inline void _hlslpp_store3_epi32(int32_t* p, const vector_int4& v) { p[0] = v.x; p[1] = v.y; p[2] = v.z; }
	hlslpp_inline void _hlslpp_store4_epi32(int32_t* p, const vector_int4& v) { p[0] = v.x; p[1] = v.y; p[2] = v.z; p[3] = v.w; }

	hlslpp_inline void _hlslpp_load1_epi32(int32_t* p, vector_int4& v) { v.x = p[0]; }
	hlslpp_inline void _hlslpp_load2_epi32(int32_t* p, vector_int4& v) { v.x = p[0]; v.y = p[1]; }
	hlslpp_inline void _hlslpp_load3_epi32(int32_t* p, vector_int4& v) { v.x = p[0]; v.y = p[1]; v.z = p[2]; }
	hlslpp_inline void _hlslpp_load4_epi32(int32_t* p, vector_int4& v) { v.x = p[0]; v.y = p[1]; v.z = p[2]; v.w = p[3]; }

	//-----------------
	// Unsigned Integer
	//-----------------

	hlslpp_inline vector_uint4 _hlslpp_set1_epu32(uint32_t x) { return vector_uint4(x); }

	hlslpp_inline vector_uint4 _hlslpp_set_epu32(uint32_t x, uint32_t y, uint32_t z, uint32_t w) { return vector_uint4(x, y, z, w); }

	hlslpp_inline vector_uint4 _hlslpp_setzero_epu32() { return vector_uint4(0, 0, 0, 0); }

	hlslpp_inline vector_uint4 _hlslpp_add_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_sub_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_mul_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_div_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4
		(
			v2.x != 0 ? v1.x / v2.x : v1.Max,
			v2.y != 0 ? v1.y / v2.y : v1.Max,
			v2.z != 0 ? v1.z / v2.z : v1.Max,
			v2.w != 0 ? v1.w / v2.w : v1.Max
		);
	}

	hlslpp_inline vector_uint4 _hlslpp_madd_epu32(const vector_uint4& v1, const vector_uint4& v2, const vector_uint4& v3)
	{
		return vector_uint4(v1.x * v2.x + v3.x, v1.y * v2.y + v3.y, v1.z * v2.z + v3.z, v1.w * v2.w + v3.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_msub_epu32(const vector_uint4& v1, const vector_uint4& v2, const vector_uint4& v3)
	{
		return vector_uint4(v1.x * v2.x - v3.x, v1.y * v2.y - v3.y, v1.z * v2.z - v3.z, v1.w * v2.w - v3.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_subm_epu32(const vector_uint4& v1, const vector_uint4& v2, const vector_uint4& v3)
	{
		return vector_uint4(v1.x - v2.x * v3.x, v1.y - v2.y * v3.y, v1.z - v2.z * v3.z, v1.w - v2.w * v3.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_cmpeq_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x == v2.x ? 0xffffffff : 0, v1.y == v2.y ? 0xffffffff : 0, v1.z == v2.z ? 0xffffffff : 0, v1.w == v2.w ? 0xffffffff : 0);
	}

	hlslpp_inline vector_uint4 _hlslpp_cmpneq_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x != v2.x ? 0xffffffff : 0, v1.y != v2.y ? 0xffffffff : 0, v1.z != v2.z ? 0xffffffff : 0, v1.w != v2.w ? 0xffffffff : 0);
	}

	hlslpp_inline vector_uint4 _hlslpp_cmpgt_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x > v2.x ? 0xffffffff : 0, v1.y > v2.y ? 0xffffffff : 0, v1.z > v2.z ? 0xffffffff : 0, v1.w > v2.w ? 0xffffffff : 0);
	}

	hlslpp_inline vector_uint4 _hlslpp_cmpge_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x >= v2.x ? 0xffffffff : 0, v1.y >= v2.y ? 0xffffffff : 0, v1.z >= v2.z ? 0xffffffff : 0, v1.w >= v2.w ? 0xffffffff : 0);
	}

	hlslpp_inline vector_uint4 _hlslpp_cmplt_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x < v2.x ? 0xffffffff : 0, v1.y < v2.y ? 0xffffffff : 0, v1.z < v2.z ? 0xffffffff : 0, v1.w < v2.w ? 0xffffffff : 0);
	}

	hlslpp_inline vector_uint4 _hlslpp_cmple_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x <= v2.x ? 0xffffffff : 0, v1.y <= v2.y ? 0xffffffff : 0, v1.z <= v2.z ? 0xffffffff : 0, v1.w <= v2.w ? 0xffffffff : 0);
	}

	hlslpp_inline vector_uint4 _hlslpp_max_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x > v2.x ? v1.x : v2.x, v1.y > v2.y ? v1.y : v2.y, v1.z > v2.z ? v1.z : v2.z, v1.w > v2.w ? v1.w : v2.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_min_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x < v2.x ? v1.x : v2.x, v1.y < v2.y ? v1.y : v2.y, v1.z < v2.z ? v1.z : v2.z, v1.w < v2.w ? v1.w : v2.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_clamp_epu32(const vector_uint4& v1, const vector_uint4& min, const vector_uint4& max)
	{
		return vector_uint4(v1.x > max.x ? max.x : v1.x < min.x ? min.x : v1.x,
			v1.y > max.y ? max.y : v1.y < min.y ? min.y : v1.y,
			v1.z > max.z ? max.z : v1.z < min.z ? min.z : v1.z,
			v1.w > max.w ? max.w : v1.w < min.w ? min.w : v1.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_sat_epu32(const vector_uint4& v1)
	{
		return vector_uint4(v1.x > 1 ? 1 : v1.x,
			v1.y > 1 ? 1 : v1.y,
			v1.z > 1 ? 1 : v1.z,
			v1.w > 1 ? 1 : v1.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_and_si128(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x & v2.x, v1.y & v2.y, v1.z & v2.z, v1.w & v2.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_andnot_si128(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(~v1.x & v2.x, ~v1.y & v2.y, ~v1.z & v2.z, ~v1.w & v2.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_not_si128(const vector_uint4& v1)
	{
		return vector_uint4(~v1.x, ~v1.y, ~v1.z, ~v1.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_or_si128(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x | v2.x, v1.y | v2.y, v1.z | v2.z, v1.w | v2.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_xor_si128(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x ^ v2.x, v1.y ^ v2.y, v1.z ^ v2.z, v1.w ^ v2.w);
	}

	template<int A, int B, int C, int D>
	hlslpp_inline vector_uint4 perm4(const vector_uint4& v)
	{
		return vector_uint4(v.m[A], v.m[B], v.m[C], v.m[D]);
	}

	template<int A, int B, int C, int D>
	hlslpp_inline vector_uint4 shuf4(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.m[A], v1.m[B], v2.m[C], v2.m[D]);
	}

#define _hlslpp_sel_epu32(x, y, msk)				select4((x), (y), (msk))

	hlslpp_inline vector_uint4 select4(const vector_uint4& v1, const vector_uint4& v2, const vector_uint4& msk)
	{
		return vector_uint4(msk.x == 0 ? v1.x : v2.x, msk.y == 0 ? v1.y : v2.y, msk.z == 0 ? v1.z : v2.z, msk.w == 0 ? v1.w : v2.w);
	}

#define _hlslpp_blend_epu32(x, y, msk)			blend4<(msk) & 1, ((msk) >> 1) & 1, ((msk) >> 2) & 1, ((msk) >> 3) & 1>((x), (y))

	template<int A, int B, int C, int D>
	hlslpp_inline vector_uint4 blend4(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(A == 1 ? v2.m[0] : v1.m[0], B == 1 ? v2.m[1] : v1.m[1], C == 1 ? v2.m[2] : v1.m[2], D == 1 ? v2.m[3] : v1.m[3]);
	}

	//hlslpp_inline vector_uint4 _hlslpp_castps_si128(const vector_float4& v)
	//{
	//	return vector_uint4(reinterpret_cast<const uint32_t&>(v.x), reinterpret_cast<const uint32_t&>(v.y), reinterpret_cast<const uint32_t&>(v.z), reinterpret_cast<const uint32_t&>(v.w));
	//}
	//
	//hlslpp_inline vector_float4 _hlslpp_castsi128_ps(const vector_uint4& v)
	//{
	//	return vector_float4(reinterpret_cast<const float&>(v.x), reinterpret_cast<const float&>(v.y), reinterpret_cast<const float&>(v.z), reinterpret_cast<const float&>(v.w));
	//}

	hlslpp_inline vector_float4 _hlslpp_cvtepu32_ps(const vector_uint4& v)
	{
		return vector_float4((float)(v.x), (float)(v.y), (float)(v.z), (float)(v.w));
	}

	hlslpp_inline vector_uint4 _hlslpp_cvttps_epu32(const vector_float4& v)
	{
		return vector_uint4((uint32_t)(v.x), (uint32_t)(v.y), (uint32_t)(v.z), (uint32_t)(v.w));
	}

	hlslpp_inline vector_uint4 _hlslpp_sll_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x << v2.x, v1.y << v2.x, v1.z << v2.x, v1.w << v2.x);
	}

	hlslpp_inline vector_uint4 _hlslpp_slli_epu32(const vector_uint4& v, const uint32_t i)
	{
		return vector_uint4(v.x << i, v.y << i, v.z << i, v.w << i);
	}

	hlslpp_inline vector_uint4 _hlslpp_srl_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x >> v2.x, v1.y >> v2.x, v1.z >> v2.x, v1.w >> v2.x);
	}

	hlslpp_inline vector_uint4 _hlslpp_srli_epu32(const vector_uint4& v, const uint32_t i)
	{
		return vector_uint4(v.x >> i, v.y >> i, v.z >> i, v.w >> i);
	}

	hlslpp_inline vector_uint4 _hlslpp_sllv_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x << v2.x, v1.y << v2.y, v1.z << v2.z, v1.w << v2.w);
	}

	hlslpp_inline vector_uint4 _hlslpp_srlv_epu32(const vector_uint4& v1, const vector_uint4& v2)
	{
		return vector_uint4(v1.x >> v2.x, v1.y >> v2.y, v1.z >> v2.z, v1.w >> v2.w);
	}

	hlslpp_inline bool _hlslpp_any1_epu32(const vector_uint4& v) { return v.x != 0; }
	hlslpp_inline bool _hlslpp_any2_epu32(const vector_uint4& v) { return v.x != 0 || v.y != 0; }
	hlslpp_inline bool _hlslpp_any3_epu32(const vector_uint4& v) { return v.x != 0 || v.y != 0 || v.z != 0; }
	hlslpp_inline bool _hlslpp_any4_epu32(const vector_uint4& v) { return v.x != 0 || v.y != 0 || v.z != 0 || v.w != 0; }

	hlslpp_inline bool _hlslpp_all1_epu32(const vector_uint4& v) { return v.x != 0; }
	hlslpp_inline bool _hlslpp_all2_epu32(const vector_uint4& v) { return v.x != 0 && v.y != 0; }
	hlslpp_inline bool _hlslpp_all3_epu32(const vector_uint4& v) { return v.x != 0 && v.y != 0 && v.z != 0; }
	hlslpp_inline bool _hlslpp_all4_epu32(const vector_uint4& v) { return v.x != 0 && v.y != 0 && v.z != 0 && v.w != 0; }

	//----------------------------
	// Unsigned Integer Store/Load
	//----------------------------

	hlslpp_inline void _hlslpp_store1_epu32(uint32_t* p, const vector_uint4& v) { p[0] = v.x; }
	hlslpp_inline void _hlslpp_store2_epu32(uint32_t* p, const vector_uint4& v) { p[0] = v.x; p[1] = v.y; }
	hlslpp_inline void _hlslpp_store3_epu32(uint32_t* p, const vector_uint4& v) { p[0] = v.x; p[1] = v.y; p[2] = v.z; }
	hlslpp_inline void _hlslpp_store4_epu32(uint32_t* p, const vector_uint4& v) { p[0] = v.x; p[1] = v.y; p[2] = v.z; p[3] = v.w; }

	hlslpp_inline void _hlslpp_load1_epu32(uint32_t* p, vector_uint4& v) { v.x = p[0]; }
	hlslpp_inline void _hlslpp_load2_epu32(uint32_t* p, vector_uint4& v) { v.x = p[0]; v.y = p[1]; }
	hlslpp_inline void _hlslpp_load3_epu32(uint32_t* p, vector_uint4& v) { v.x = p[0]; v.y = p[1]; v.z = p[2]; }
	hlslpp_inline void _hlslpp_load4_epu32(uint32_t* p, vector_uint4& v) { v.x = p[0]; v.y = p[1]; v.z = p[2]; v.w = p[3]; }

	//-------------
	// Data Packing
	//-------------

	hlslpp_inline uint32_t _hlslpp_pack_epu32_rgba8_unorm(vector_float4 v)
	{
		vector_float4 v255f = vector_float4(v.x * 255.0f + 0.5f, v.y * 255.0f + 0.5f, v.z * 255.0f + 0.5f, v.w * 255.0f + 0.5f);
		detail::packed_union packed;
		packed._u8[0] = (uint8_t)v255f.x;
		packed._u8[1] = (uint8_t)v255f.y;
		packed._u8[2] = (uint8_t)v255f.z;
		packed._u8[3] = (uint8_t)v255f.w;
		return packed._u32;
	}

	hlslpp_inline vector_float4 _hlslpp_unpack_rgba8_unorm_epu32(uint32_t p)
	{
		detail::packed_union packed(p);
		return vector_float4(packed._u8[0] / 255.0f, packed._u8[1] / 255.0f, packed._u8[2] / 255.0f, packed._u8[3] / 255.0f);
	}

	hlslpp_inline uint32_t _hlslpp_pack_epu32_rgba8_snorm(vector_float4 v)
	{
		vector_float4 v127f = vector_float4
		(
			v.x * 127.0f + (v.x > 0.0f ? 0.5f : -0.5f),
			v.y * 127.0f + (v.y > 0.0f ? 0.5f : -0.5f),
			v.z * 127.0f + (v.z > 0.0f ? 0.5f : -0.5f),
			v.w * 127.0f + (v.w > 0.0f ? 0.5f : -0.5f)
		);

		detail::packed_union packed;
		packed._c[0] = (char)v127f.x;
		packed._c[1] = (char)v127f.y;
		packed._c[2] = (char)v127f.z;
		packed._c[3] = (char)v127f.w;
		return packed._u32;
	}

	hlslpp_inline vector_float4 _hlslpp_unpack_rgba8_snorm_epu32(uint32_t p)
	{
		detail::packed_union packed(p);
		return vector_float4(packed._c[0] / 127.0f, packed._c[1] / 127.0f, packed._c[2] / 127.0f, packed._c[3] / 127.0f);
	}
}