#pragma once

#include "hlsl++/common.h"

#include "hlsl++/vector_float.h"

#include "hlsl++/transform/common.h"

//--------------//
// Float Matrix //
//--------------//

hlslpp_module_export namespace hlslpp
{
	struct hlslpp_nodiscard float1x1
	{
		hlslpp_inline float1x1() hlslpp_noexcept : vec(_hlslpp_setzero_ps()) {}
		hlslpp_inline float1x1(const float1x1& m) hlslpp_noexcept : vec(m.vec) {}

		explicit hlslpp_inline float1x1(n128 vec) hlslpp_noexcept : vec(vec) {}

		template<typename T>
		explicit hlslpp_inline float1x1(T f, hlslpp_enable_if_number(T)) hlslpp_noexcept : vec(_hlslpp_set_ps(float(f), 0.0f, 0.0f, 0.0f)) {}

		explicit hlslpp_inline float1x1(const float1& f) hlslpp_noexcept : vec(f.vec) {}

		explicit hlslpp_inline float1x1(const float2x2& m) hlslpp_noexcept;

		hlslpp_inline float1x1& operator = (const float1x1& m) hlslpp_noexcept { vec = m.vec; return *this; }

		hlslpp_inline float1x1(float1x1&& m) hlslpp_noexcept : vec(m.vec) {}
		hlslpp_inline float1x1& operator = (float1x1&& m) hlslpp_noexcept { vec = m.vec; return *this; }
    
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/matrix_row0_1.h"
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct hlslpp_nodiscard float1x2
	{
		hlslpp_inline float1x2() hlslpp_noexcept : vec(_hlslpp_setzero_ps()) {}
		hlslpp_inline float1x2(const float1x2& m) hlslpp_noexcept : vec(m.vec) {}

		explicit hlslpp_inline float1x2(n128 vec) hlslpp_noexcept : vec(vec) {}

		template<typename T>
		explicit hlslpp_inline float1x2(T f, hlslpp_enable_if_number(T)) hlslpp_noexcept : vec(_hlslpp_set_ps(float(f), float(f), 0.0f, 0.0f)) {}

		explicit hlslpp_inline float1x2(float f0, float f1) hlslpp_noexcept : vec(_hlslpp_set_ps(f0, f1, 0.0f, 0.0f)) {}

		hlslpp_inline float1x2(const float2& f) hlslpp_noexcept : vec(f.vec) {}

		hlslpp_inline float1x2& operator = (const float1x2& m) hlslpp_noexcept { vec = m.vec; return *this; }

		hlslpp_inline float1x2(float1x2&& m) hlslpp_noexcept : vec(m.vec) {}
		hlslpp_inline float1x2& operator = (float1x2&& m) hlslpp_noexcept { vec = m.vec; return *this; }

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/matrix_row0_2.h"
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct hlslpp_nodiscard float2x1
	{
		hlslpp_inline float2x1() hlslpp_noexcept : vec(_hlslpp_setzero_ps()) {}
		hlslpp_inline float2x1(const float2x1& m) hlslpp_noexcept : vec(m.vec) {}

		explicit hlslpp_inline float2x1(n128 vec) hlslpp_noexcept : vec(vec) {}

		template<typename T>
		explicit hlslpp_inline float2x1(T f, hlslpp_enable_if_number(T)) hlslpp_noexcept : vec(_hlslpp_set_ps(float(f), float(f), 0.0f, 0.0f)) {}

		explicit hlslpp_inline float2x1(float f0, float f1) hlslpp_noexcept : vec(_hlslpp_set_ps(f0, f1, 0.0f, 0.0f)) {}

		hlslpp_inline float2x1(const float2& f) hlslpp_noexcept : vec(f.vec) {}

		hlslpp_inline float2x1& operator = (const float2x1& m) hlslpp_noexcept { vec = m.vec; return *this; }

		hlslpp_inline float2x1(float2x1&& m) hlslpp_noexcept : vec(m.vec) {}
		hlslpp_inline float2x1& operator = (float2x1&& m) hlslpp_noexcept { vec = m.vec; return *this; }

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct hlslpp_nodiscard float1x3
	{
		hlslpp_inline float1x3() hlslpp_noexcept : vec(_hlslpp_setzero_ps()) {}
		hlslpp_inline float1x3(const float1x3& m) hlslpp_noexcept : vec(m.vec) {}

		explicit hlslpp_inline float1x3(n128 vec) hlslpp_noexcept : vec(vec) {}

		template<typename T>
		explicit hlslpp_inline float1x3(T f, hlslpp_enable_if_number(T)) hlslpp_noexcept : vec(_hlslpp_set_ps(float(f), float(f), float(f), 0.0f)) {}

		explicit hlslpp_inline float1x3(float f0, float f1, float f2) hlslpp_noexcept : vec(_hlslpp_set_ps(f0, f1, f2, 0.0f)) {}

		hlslpp_inline float1x3(const float3& f) hlslpp_noexcept : vec(f.vec) {}

		hlslpp_inline float1x3& operator = (const float1x3& m) hlslpp_noexcept { vec = m.vec; return *this; }

		hlslpp_inline float1x3(float1x3&& m) hlslpp_noexcept : vec(m.vec) {}
		hlslpp_inline float1x3& operator = (float1x3&& m) hlslpp_noexcept { vec = m.vec; return *this; }

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct hlslpp_nodiscard float3x1
	{
		hlslpp_inline float3x1() hlslpp_noexcept : vec(_hlslpp_setzero_ps()) {}
		hlslpp_inline float3x1(const float3x1& m) hlslpp_noexcept : vec(m.vec) {}

		explicit hlslpp_inline float3x1(n128 vec) hlslpp_noexcept : vec(vec) {}

		template<typename T>
		explicit hlslpp_inline float3x1(T f, hlslpp_enable_if_number(T)) hlslpp_noexcept : vec(_hlslpp_set_ps(float(f), float(f), float(f), 0.0f)) {}

		explicit hlslpp_inline float3x1(float f0, float f1, float f2) hlslpp_noexcept : vec(_hlslpp_set_ps(f0, f1, f2, 0.0f)) {}

		hlslpp_inline float3x1(const float3& f) hlslpp_noexcept : vec(f.vec) {}

		hlslpp_inline float3x1& operator = (const float3x1& m) hlslpp_noexcept { vec = m.vec; return *this; }

		hlslpp_inline float3x1(float3x1&& m) hlslpp_noexcept : vec(m.vec) {}
		hlslpp_inline float3x1& operator = (float3x1&& m) hlslpp_noexcept { vec = m.vec; return *this; }

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct hlslpp_nodiscard float1x4
	{
		hlslpp_inline float1x4() hlslpp_noexcept : vec(_hlslpp_setzero_ps()) {}
		hlslpp_inline float1x4(const float1x4& m) hlslpp_noexcept : vec(m.vec) {}

		explicit hlslpp_inline float1x4(n128 vec) hlslpp_noexcept : vec(vec) {}

		template<typename T>
		explicit hlslpp_inline float1x4(T f, hlslpp_enable_if_number(T)) hlslpp_noexcept : vec(_hlslpp_set1_ps(float(f))) {}

		explicit hlslpp_inline float1x4(float f0, float f1, float f2, float f3) hlslpp_noexcept : vec(_hlslpp_set_ps(f0, f1, f2, f3)) {}

		hlslpp_inline float1x4(const float4& f) hlslpp_noexcept : vec(f.vec) {}

		hlslpp_inline float1x4& operator = (const float1x4& m) hlslpp_noexcept { vec = m.vec; return *this; }

		hlslpp_inline float1x4(float1x4&& m) hlslpp_noexcept : vec(m.vec) {}
		hlslpp_inline float1x4& operator = (float1x4&& m) hlslpp_noexcept { vec = m.vec; return *this; }

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct hlslpp_nodiscard float4x1
	{
		hlslpp_inline float4x1() hlslpp_noexcept : vec(_hlslpp_setzero_ps()) {}
		hlslpp_inline float4x1(const float4x1& m) hlslpp_noexcept : vec(m.vec) {}

		explicit hlslpp_inline float4x1(n128 vec) hlslpp_noexcept : vec(vec) {}

		template<typename T>
		explicit hlslpp_inline float4x1(T f, hlslpp_enable_if_number(T)) hlslpp_noexcept : vec(_hlslpp_set1_ps(float(f))) {}

		explicit hlslpp_inline float4x1(float f0, float f1, float f2, float f3) hlslpp_noexcept : vec(_hlslpp_set_ps(f0, f1, f2, f3)) {}

		hlslpp_inline float4x1(const float4& f) hlslpp_noexcept : vec(f.vec) {}

		hlslpp_inline float4x1& operator = (const float4x1& m) hlslpp_noexcept { vec = m.vec; return *this; }

		hlslpp_inline float4x1(float4x1&& m) hlslpp_noexcept : vec(m.vec) {}
		hlslpp_inline float4x1& operator = (float4x1&& m) hlslpp_noexcept { vec = m.vec; return *this; }

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct hlslpp_nodiscard float2x2
	{
		hlslpp_inline float2x2() hlslpp_noexcept : vec(_hlslpp_setzero_ps()) {}
		hlslpp_inline float2x2(const float2x2& m) hlslpp_noexcept : vec(m.vec) {}

		explicit hlslpp_inline float2x2(n128 vec) hlslpp_noexcept : vec(vec) {}

		explicit hlslpp_inline float2x2(
		    float f00, float f01,
		    float f10, float f11) hlslpp_noexcept : vec(_hlslpp_set_ps(f00, f01, f10, f11)) {}

		explicit hlslpp_inline float2x2(float f) hlslpp_noexcept : vec(_hlslpp_set1_ps(f)) {}

		explicit hlslpp_inline float2x2(const float3x3& m) hlslpp_noexcept;

		hlslpp_inline float2x2(const float2& f1, const float2& f2) hlslpp_noexcept : vec(_hlslpp_shuf_xyxy_ps(f1.vec, f2.vec)) {}

		hlslpp_inline float2x2& operator = (const float2x2& m) hlslpp_noexcept { vec = m.vec; return *this; }

		hlslpp_inline float2x2(float2x2&& m) hlslpp_noexcept : vec(m.vec) {}
		hlslpp_inline float2x2& operator = (float2x2&& m) hlslpp_noexcept { vec = m.vec; return *this; }

		#include "hlsl++/transform/float2x2.h"

		union
		{
			n128 vec; // Store it in a single vector to save memory
			float f32[4];
		};
	};

	struct hlslpp_nodiscard float2x3
	{
		hlslpp_inline float2x3() hlslpp_noexcept : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()) {}
		hlslpp_inline float2x3(const float2x3& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1) {}

		explicit hlslpp_inline float2x3(n128 vec0, n128 vec1) hlslpp_noexcept : vec0(vec0), vec1(vec1) {}

		explicit hlslpp_inline float2x3(float f) hlslpp_noexcept : vec0(_hlslpp_set_ps(f, f, f, 0.0f)), vec1(_hlslpp_set_ps(f, f, f, 0.0f)) {}

		explicit hlslpp_inline float2x3(
		    float f00, float f01, float f02,
		    float f10, float f11, float f12)
		    hlslpp_noexcept : vec0(_hlslpp_set_ps(f00, f01, f02, 0.0f)), vec1(_hlslpp_set_ps(f10, f11, f12, 0.0f)) {}

		// Construct matrix with two float3 interpreted as rows
		hlslpp_inline float2x3(const float3& f1, const float3& f2) hlslpp_noexcept : vec0(f1.vec), vec1(f2.vec) {}

		hlslpp_inline float2x3& operator = (const float2x3& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		hlslpp_inline float2x3(float2x3&& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1) {}
		hlslpp_inline float2x3& operator = (float2x3&& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};
	};

	struct hlslpp_nodiscard float3x2
	{
		hlslpp_inline float3x2() hlslpp_noexcept : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()) {}
		hlslpp_inline float3x2(const float3x2& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1) {}

		explicit hlslpp_inline float3x2(n128 vec0, n128 vec1) hlslpp_noexcept : vec0(vec0), vec1(vec1) {}

		explicit hlslpp_inline float3x2(float f) hlslpp_noexcept : vec0(_hlslpp_set_ps(f, f, f, 0.0f)), vec1(_hlslpp_set_ps(f, f, f, 0.0f)) {}

		explicit hlslpp_inline float3x2(
		    float f00, float f01,
		    float f10, float f11,
		    float f20, float f21)
		    hlslpp_noexcept : vec0(_hlslpp_set_ps(f00, f10, f20, 0.0f)), vec1(_hlslpp_set_ps(f01, f11, f21, 0.0f)) {}

		// Construct matrix with two float3 interpreted as columns
		hlslpp_inline float3x2(const float3& f1, const float3& f2) hlslpp_noexcept : vec0(f1.vec), vec1(f2.vec) {}

		hlslpp_inline float3x2& operator = (const float3x2& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		hlslpp_inline float3x2(float3x2&& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1) {}
		hlslpp_inline float3x2& operator = (float3x2&& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};
	};

	struct hlslpp_nodiscard float2x4
	{
		hlslpp_inline float2x4() hlslpp_noexcept : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()) {}
		hlslpp_inline float2x4(const float2x4& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1) {}

		explicit hlslpp_inline float2x4(n128 vec0, n128 vec1) hlslpp_noexcept : vec0(vec0), vec1(vec1) {}

		explicit hlslpp_inline float2x4(
		    float f00, float f01, float f02, float f03,
		    float f10, float f11, float f12, float f13)
		    hlslpp_noexcept : vec0(_hlslpp_set_ps(f00, f01, f02, f03)), vec1(_hlslpp_set_ps(f10, f11, f12, f13)) {}

		explicit hlslpp_inline float2x4(float f) hlslpp_noexcept : vec0(_hlslpp_set_ps(f, f, f, f)), vec1(_hlslpp_set_ps(f, f, f, f)) {}

		// Construct matrix with two float3 interpreted as rows
		hlslpp_inline float2x4(const float4& f1, const float4& f2) hlslpp_noexcept : vec0(f1.vec), vec1(f2.vec) {}

		hlslpp_inline float2x4& operator = (const float2x4& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		hlslpp_inline float2x4(float2x4&& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1) {}
		hlslpp_inline float2x4& operator = (float2x4&& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};
	};

	struct hlslpp_nodiscard float4x2
	{
		hlslpp_inline float4x2() hlslpp_noexcept : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()) {}
		hlslpp_inline float4x2(const float4x2& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1) {}

		explicit hlslpp_inline float4x2(n128 vec0, n128 vec1) hlslpp_noexcept : vec0(vec0), vec1(vec1) {}

		explicit hlslpp_inline float4x2(
		    float f00, float f01,
		    float f10, float f11,
		    float f20, float f21,
		    float f30, float f31) 
		    hlslpp_noexcept : vec0(_hlslpp_set_ps(f00, f10, f20, f30)), vec1(_hlslpp_set_ps(f01, f11, f21, f31)) {}

		explicit hlslpp_inline float4x2(float f) hlslpp_noexcept : vec0(_hlslpp_set_ps(f, f, f, f)), vec1(_hlslpp_set_ps(f, f, f, f)) {}

		// Construct matrix with two float3 interpreted as columns
		hlslpp_inline float4x2(const float4& f1, const float4& f2) hlslpp_noexcept : vec0(f1.vec), vec1(f2.vec) {}

		hlslpp_inline float4x2& operator = (const float4x2& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		hlslpp_inline float4x2(float4x2&& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1) {}
		hlslpp_inline float4x2& operator = (float4x2&& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};
	};

	struct quaternion;

	struct hlslpp_nodiscard float3x3
	{
		hlslpp_inline float3x3() hlslpp_noexcept : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()), vec2(_hlslpp_setzero_ps()) {}
		hlslpp_inline float3x3(const float3x3& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}

		explicit hlslpp_inline float3x3(const n128 vec0, const n128 vec1, const n128 vec2) hlslpp_noexcept : vec0(vec0), vec1(vec1), vec2(vec2) {}

		explicit hlslpp_inline float3x3(
		    float f00, float f01, float f02,
		    float f10, float f11, float f12,
		    float f20, float f21, float f22)
		    hlslpp_noexcept : vec0(_hlslpp_set_ps(f00, f01, f02, 0.0f)), vec1(_hlslpp_set_ps(f10, f11, f12, 0.0f)), vec2(_hlslpp_set_ps(f20, f21, f22, 0.0f)) {}

		explicit hlslpp_inline float3x3(const quaternion& q) hlslpp_noexcept;
		explicit hlslpp_inline float3x3(const float4x4& m) hlslpp_noexcept;

		explicit hlslpp_inline float3x3(float f) hlslpp_noexcept : vec0(_hlslpp_set1_ps(f)), vec1(_hlslpp_set1_ps(f)), vec2(_hlslpp_set1_ps(f)) {}

		hlslpp_inline float3x3(const float3& f1, const float3& f2, const float3& f3) hlslpp_noexcept : vec0(f1.vec), vec1(f2.vec), vec2(f3.vec) {}

		hlslpp_inline float3x3& operator = (const float3x3& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; return *this; }

		hlslpp_inline float3x3(float3x3&& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}
		hlslpp_inline float3x3& operator = (float3x3&& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; return *this; }

		static const float3x3& identity() { static const float3x3 iden = float3x3(1, 0, 0, 0, 1, 0, 0, 0, 1); return iden; }

		#include "hlsl++/transform/float3x3.h"

		float3& operator[](int N)
		{
			hlslpp_assert(N >= 0 && N <= 2);
			return *(&reinterpret_cast<float3&>(vec0) + N);
		}

		const float3& operator[](int N) const
		{
			hlslpp_assert(N >= 0 && N <= 2);
			return *(&reinterpret_cast<const float3&>(vec0) + N);
		}

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128 vec0;
			float f32_0[3];
			#include "swizzle/matrix_row0_1.h"
			#include "swizzle/matrix_row0_2.h"
			#include "swizzle/matrix_row0_3.h"
		};

		union
		{
			n128 vec1;
			float f32_1[3];
			#include "swizzle/matrix_row1_1.h"
			#include "swizzle/matrix_row1_2.h"
			#include "swizzle/matrix_row1_3.h"
		};

		union
		{
			n128 vec2;
			float f32_2[3];
			#include "swizzle/matrix_row2_1.h"
			#include "swizzle/matrix_row2_2.h"
			#include "swizzle/matrix_row2_3.h"
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct hlslpp_nodiscard float3x4
	{
		hlslpp_inline float3x4() hlslpp_noexcept : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()), vec2(_hlslpp_setzero_ps()) {}
		hlslpp_inline float3x4(const float3x4& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}

		explicit hlslpp_inline float3x4(n128 vec0, n128 vec1, n128 vec2) hlslpp_noexcept : vec0(vec0), vec1(vec1), vec2(vec2) {}

		explicit hlslpp_inline float3x4(
		    float f00, float f01, float f02, float f03,
		    float f10, float f11, float f12, float f13,
		    float f20, float f21, float f22, float f23) 
		    hlslpp_noexcept : vec0(_hlslpp_set_ps(f00, f01, f02, f03)), vec1(_hlslpp_set_ps(f10, f11, f12, f13)), vec2(_hlslpp_set_ps(f20, f21, f22, f23)) {}

		explicit hlslpp_inline float3x4(float f) hlslpp_noexcept : vec0(_hlslpp_set1_ps(f)), vec1(_hlslpp_set1_ps(f)), vec2(_hlslpp_set1_ps(f)) {}

		// Construct matrix with two float3 interpreted as rows
		hlslpp_inline float3x4(const float4& f1, const float4& f2, const float4& f3) hlslpp_noexcept : vec0(f1.vec), vec1(f2.vec), vec2(f3.vec) {}

		hlslpp_inline float3x4& operator = (const float3x4& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; return *this; }

		hlslpp_inline float3x4(float3x4&& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}
		hlslpp_inline float3x4& operator = (float3x4&& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; return *this; }

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};

		union
		{
			n128 vec2;
			float f32_2[4];
		};
	};

	struct hlslpp_nodiscard float4x3
	{
		hlslpp_inline float4x3() hlslpp_noexcept : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()), vec2(_hlslpp_setzero_ps()) {}
		hlslpp_inline float4x3(const float4x3& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}

		explicit hlslpp_inline float4x3(n128 vec0, n128 vec1, n128 vec2) hlslpp_noexcept : vec0(vec0), vec1(vec1), vec2(vec2) {}

		explicit hlslpp_inline float4x3(
		    float f00, float f01, float f02,
		    float f10, float f11, float f12,
		    float f20, float f21, float f22,
		    float f30, float f31, float f32)
		    hlslpp_noexcept : vec0(_hlslpp_set_ps(f00, f10, f20, f30)), vec1(_hlslpp_set_ps(f01, f11, f21, f31)), vec2(_hlslpp_set_ps(f02, f12, f22, f32)) {}

		explicit hlslpp_inline float4x3(float f) hlslpp_noexcept : vec0(_hlslpp_set1_ps(f)), vec1(_hlslpp_set1_ps(f)), vec2(_hlslpp_set1_ps(f)) {}
		
		// Construct matrix with two float3 interpreted as columns
		hlslpp_inline float4x3(const float4& f1, const float4& f2, const float4& f3) hlslpp_noexcept : vec0(f1.vec), vec1(f2.vec), vec2(f3.vec) {}

		hlslpp_inline float4x3& operator = (const float4x3& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; return *this; }

		hlslpp_inline float4x3(float4x3&& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}
		hlslpp_inline float4x3& operator = (float4x3&& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; return *this; }

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};

		union
		{
			n128 vec2;
			float f32_2[4];
		};
	};

	float4x4 transpose(const float4x4& m);

	struct hlslpp_nodiscard float4x4
	{
#if defined(HLSLPP_SIMD_REGISTER_256)

		hlslpp_inline float4x4() hlslpp_noexcept : vec0(_hlslpp256_setzero_ps()), vec1(_hlslpp256_setzero_ps()) {}
		hlslpp_inline float4x4(const float4x4& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1) {}

		explicit hlslpp_inline float4x4(const n256& vec0, const n256& vec1) hlslpp_noexcept : vec0(vec0), vec1(vec1) {}

		explicit hlslpp_inline float4x4(
		    float f00, float f01, float f02, float f03,
		    float f10, float f11, float f12, float f13,
		    float f20, float f21, float f22, float f23,
		    float f30, float f31, float f32, float f33)
		    hlslpp_noexcept : vec0(_hlslpp256_set_ps(f00, f01, f02, f03, f10, f11, f12, f13)), vec1(_hlslpp256_set_ps(f20, f21, f22, f23, f30, f31, f32, f33)) {}

		explicit hlslpp_inline float4x4(float f) hlslpp_noexcept : vec0(_hlslpp256_set1_ps(f)), vec1(_hlslpp256_set1_ps(f)) {}

		hlslpp_inline float4x4(const float4& f1, const float4& f2, const float4& f3, const float4& f4) 
			hlslpp_noexcept : vec0(_hlslpp256_set128_ps(f1.vec, f2.vec)), vec1(_hlslpp256_set128_ps(f3.vec, f4.vec)) {}

		hlslpp_inline float4x4& operator = (const float4x4& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		hlslpp_inline float4x4(float4x4&& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1) {}
		hlslpp_inline float4x4& operator = (float4x4&& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		hlslpp_inline void build(const float3x3& m, const float4& v) hlslpp_noexcept
		{
			vec0 = _hlslpp256_and_ps(
				_hlslpp256_set128_ps(m.vec0, m.vec1),
				_hlslpp256_set_ps(fffMask._f32, fffMask._f32, fffMask._f32, 0.0f, fffMask._f32, fffMask._f32, fffMask._f32, 0.0f));

			vec1 = _hlslpp256_and_ps(
				_hlslpp256_set128_ps(m.vec2, v.vec),
				_hlslpp256_set_ps(fffMask._f32, fffMask._f32, fffMask._f32, 0.0f, fffMask._f32, fffMask._f32, fffMask._f32, fffMask._f32));
		}

		hlslpp_inline void build(const float3x4& m, const float4& v) hlslpp_noexcept
		{
			vec0 = _hlslpp256_set128_ps(m.vec0, m.vec1);
			vec1 = _hlslpp256_set128_ps(m.vec2, v.vec);
		}

		hlslpp_inline void build(const float4x3& m, const float4& v) hlslpp_noexcept
		{
			vec0 = _hlslpp256_set128_ps(m.vec0, m.vec1);
			vec1 = _hlslpp256_set128_ps(m.vec2, v.vec);
			*this = transpose(*this); // Copy over as rows, then transpose
		}

		float4& operator[](int N)
		{
			hlslpp_assert(N >= 0 && N <= 3);
			return *(&row0 + N);
		}

		const float4& operator[](int N) const
		{
			hlslpp_assert(N >= 0 && N <= 3);
			return *(&row0 + N);
		}

		union
		{
			n256 vec0;
			float f32_256_0[8];
			float4 row0;

			HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
			struct
			{
				union 
				{
					#include "swizzle/matrix_row0_1.h"
					#include "swizzle/matrix_row0_2.h"
					#include "swizzle/matrix_row0_3.h"
					#include "swizzle/matrix_row0_4.h"
				};
			
				union
				{
					#include "swizzle/matrix_row1_1.h"
					#include "swizzle/matrix_row1_2.h"
					#include "swizzle/matrix_row1_3.h"
					#include "swizzle/matrix_row1_4.h"
				};
			};
			HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
		};

		union
		{
			n256 vec1;
			float f32_256_1[8];

			HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
			struct
			{
				union
				{
					#include "swizzle/matrix_row2_1.h"
					#include "swizzle/matrix_row2_2.h"
					#include "swizzle/matrix_row2_3.h"
					#include "swizzle/matrix_row2_4.h"
				};

				union
				{
					#include "swizzle/matrix_row3_1.h"
					#include "swizzle/matrix_row3_2.h"
					#include "swizzle/matrix_row3_3.h"
					#include "swizzle/matrix_row3_4.h"
				};
			};
			HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
		};
#else

		hlslpp_inline float4x4() hlslpp_noexcept 
			: vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()), vec2(_hlslpp_setzero_ps()), vec3(_hlslpp_setzero_ps()) {}

		hlslpp_inline float4x4(const float4x4& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2), vec3(m.vec3) {}

		explicit hlslpp_inline float4x4(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3) hlslpp_noexcept 
			: vec0(vec0), vec1(vec1), vec2(vec2), vec3(vec3) {}

		explicit hlslpp_inline float4x4(
		    float f00, float f01, float f02, float f03,
		    float f10, float f11, float f12, float f13,
		    float f20, float f21, float f22, float f23,
		    float f30, float f31, float f32, float f33)
		    hlslpp_noexcept : vec0(_hlslpp_set_ps(f00, f01, f02, f03)), vec1(_hlslpp_set_ps(f10, f11, f12, f13)), 
			                  vec2(_hlslpp_set_ps(f20, f21, f22, f23)), vec3(_hlslpp_set_ps(f30, f31, f32, f33)) {}

		explicit hlslpp_inline float4x4(float f) hlslpp_noexcept 
			: vec0(_hlslpp_set1_ps(f)), vec1(_hlslpp_set1_ps(f)), vec2(_hlslpp_set1_ps(f)), vec3(_hlslpp_set1_ps(f)) {}

		hlslpp_inline float4x4(const float4& f1, const float4& f2, const float4& f3, const float4& f4) hlslpp_noexcept 
			: vec0(f1.vec), vec1(f2.vec), vec2(f3.vec), vec3(f4.vec) {}

		hlslpp_inline float4x4& operator = (const float4x4& m) hlslpp_noexcept 
		{ vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; vec3 = m.vec3; return *this; }

		hlslpp_inline float4x4(float4x4&& m) hlslpp_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2), vec3(m.vec3) {}
		hlslpp_inline float4x4& operator = (float4x4&& m) hlslpp_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; vec3 = m.vec3; return *this; }

		hlslpp_inline void build(const float3x3& m, const float4& v) hlslpp_noexcept
		{
			vec0 = _hlslpp_and_ps(m.vec0, _hlslpp_set_ps(fffMask._f32, fffMask._f32, fffMask._f32, 0.0f));
			vec1 = _hlslpp_and_ps(m.vec1, _hlslpp_set_ps(fffMask._f32, fffMask._f32, fffMask._f32, 0.0f));
			vec2 = _hlslpp_and_ps(m.vec2, _hlslpp_set_ps(fffMask._f32, fffMask._f32, fffMask._f32, 0.0f));
			vec3 = v.vec;
		}

		hlslpp_inline void build(const float3x4& m, const float4& v) hlslpp_noexcept
		{
			vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; vec3 = v.vec;
		}

		hlslpp_inline void build(const float4x3& m, const float4& v) hlslpp_noexcept
		{
			vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2;
			*this = transpose(*this); // Copy over as rows, then transpose
			vec3 = v.vec;
		}

		float4& operator[](int N)
		{
			hlslpp_assert(N >= 0 && N <= 3);
			return *(&reinterpret_cast<float4&>(vec0) + N);
		}

		const float4& operator[](int N) const
		{
			hlslpp_assert(N >= 0 && N <= 3);
			return *(&reinterpret_cast<const float4&>(vec0) + N);
		}

		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128 vec0;
			float f32_128_0[4];
			#include "swizzle/matrix_row0_1.h"
			#include "swizzle/matrix_row0_2.h"
			#include "swizzle/matrix_row0_3.h"
			#include "swizzle/matrix_row0_4.h"
		};

		union
		{
			n128 vec1;
			float f32_128_1[4];
			#include "swizzle/matrix_row1_1.h"
			#include "swizzle/matrix_row1_2.h"
			#include "swizzle/matrix_row1_3.h"
			#include "swizzle/matrix_row1_4.h"
		};

		union
		{
			n128 vec2;
			float f32_128_2[4];
			#include "swizzle/matrix_row2_1.h"
			#include "swizzle/matrix_row2_2.h"
			#include "swizzle/matrix_row2_3.h"
			#include "swizzle/matrix_row2_4.h"
		};

		union
		{
			n128 vec3;
			float f32_128_3[4];
			#include "swizzle/matrix_row3_1.h"
			#include "swizzle/matrix_row3_2.h"
			#include "swizzle/matrix_row3_3.h"
			#include "swizzle/matrix_row3_4.h"
		};
		HLSLPP_WARNING_ANONYMOUS_STRUCT_UNION_END
#endif

		// Conversion from lower-dimension matrices
		explicit hlslpp_inline float4x4(const float3x3& m, const float4& v) hlslpp_noexcept { build(m, v); }
		explicit hlslpp_inline float4x4(const float3x3& m) hlslpp_noexcept { build(m, float4(_hlslpp_setzero_ps())); }
		
		explicit hlslpp_inline float4x4(const float3x4& m, const float4& v) hlslpp_noexcept { build(m, v); }
		explicit hlslpp_inline float4x4(const float3x4& m) hlslpp_noexcept { build(m, float4(_hlslpp_setzero_ps())); }

		explicit hlslpp_inline float4x4(const float4x3& m) hlslpp_noexcept { build(m, float4(_hlslpp_setzero_ps())); }

		explicit hlslpp_inline float4x4(const quaternion& q) hlslpp_noexcept;

		static const float4x4& identity() { static const float4x4 iden = float4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); return iden; };

		#include "hlsl++/transform/float4x4.h"
	};
};