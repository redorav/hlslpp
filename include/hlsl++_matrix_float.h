//--------------//
// Float Matrix //
//--------------//

namespace hlslpp
{
	struct float1x1
	{
		float1x1() : vec(_hlslpp_setzero_ps()) {}

		explicit float1x1(n128 vec) : vec(vec) {}

		template<typename T>
		explicit float1x1(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set_ps(float(f), 0.0f, 0.0f, 0.0f)) {}

		float1x1(const float1& f) : vec(f.vec) {}
    
		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/hlsl++_matrix_row0_1.h"
		};
	};

	struct float1x2
	{
		float1x2() : vec(_hlslpp_setzero_ps()) {}

		explicit float1x2(n128 vec) : vec(vec) {}

		template<typename T>
		explicit float1x2(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set_ps(float(f), float(f), 0.0f, 0.0f)) {}

		explicit float1x2(float f0, float f1) : vec(_hlslpp_set_ps(f0, f1, 0.0f, 0.0f)) {}

		float1x2(const float2& f) : vec(f.vec) {}

		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/hlsl++_matrix_row0_2.h"
		};
	};

	struct float2x1
	{
		float2x1() : vec(_hlslpp_setzero_ps()) {}

		explicit float2x1(n128 vec) : vec(vec) {}

		template<typename T>
		explicit float2x1(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set_ps(float(f), float(f), 0.0f, 0.0f)) {}

		explicit float2x1(float f0, float f1) : vec(_hlslpp_set_ps(f0, f1, 0.0f, 0.0f)) {}

		float2x1(const float2& f) : vec(f.vec) {}

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct float1x3
	{
		float1x3() : vec(_hlslpp_setzero_ps()) {}

		explicit float1x3(n128 vec) : vec(vec) {}

		template<typename T>
		explicit float1x3(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set_ps(float(f), float(f), float(f), 0.0f)) {}

		explicit float1x3(float f0, float f1, float f2) : vec(_hlslpp_set_ps(f0, f1, f2, 0.0f)) {}

		float1x3(const float3& f) : vec(f.vec) {}

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct float3x1
	{
		float3x1() : vec(_hlslpp_setzero_ps()) {}

		explicit float3x1(n128 vec) : vec(vec) {}

		template<typename T>
		explicit float3x1(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set_ps(float(f), float(f), float(f), 0.0f)) {}

		explicit float3x1(float f0, float f1, float f2) : vec(_hlslpp_set_ps(f0, f1, f2, 0.0f)) {}

		float3x1(const float3& f) : vec(f.vec) {}

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct float1x4
	{
		float1x4() : vec(_hlslpp_setzero_ps()) {}

		explicit float1x4(n128 vec) : vec(vec) {}

		template<typename T>
		explicit float1x4(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set1_ps(float(f))) {}

		explicit float1x4(float f0, float f1, float f2, float f3) : vec(_hlslpp_set_ps(f0, f1, f2, f3)) {}

		float1x4(const float4& f) : vec(f.vec) {}

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct float4x1
	{
		float4x1() : vec(_hlslpp_setzero_ps()) {}

		explicit float4x1(n128 vec) : vec(vec) {}

		template<typename T>
		explicit float4x1(T f, hlslpp_enable_if_number(T)) : vec(_hlslpp_set1_ps(float(f))) {}

		explicit float4x1(float f0, float f1, float f2, float f3) : vec(_hlslpp_set_ps(f0, f1, f2, f3)) {}

		float4x1(const float4& f) : vec(f.vec) {}

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct float2x2
	{
		float2x2() : vec(_hlslpp_setzero_ps()) {}

		explicit float2x2(n128 vec) : vec(vec) {}

		explicit float2x2(float f00, float f01,
		                  float f10, float f11) : vec(_hlslpp_set_ps(f00, f01, f10, f11)) {}

		explicit float2x2(float f) : vec(_hlslpp_set1_ps(f)) {}

		float2x2(const float2x2& m) : vec(m.vec) {}

		union
		{
			n128 vec; // Store it in a single vector to save memory
			float f32[4];
		};
	};

	struct float2x3
	{
		float2x3() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()) {}

		explicit float2x3(n128 vec0, n128 vec1) : vec0(vec0), vec1(vec1) {}

		explicit float2x3(float f) : vec0(_hlslpp_set_ps(f, f, f, 0.0f)), vec1(_hlslpp_set_ps(f, f, f, 0.0f)) {}

		explicit float2x3(float f00, float f01, float f02,
		                  float f10, float f11, float f12) : vec0(_hlslpp_set_ps(f00, f01, f02, 0.0f)), vec1(_hlslpp_set_ps(f10, f11, f12, 0.0f)) {}

		float2x3(const float2x3& m) : vec0(m.vec0), vec1(m.vec1) {}

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

	struct float3x2
	{
		float3x2() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()) {}

		explicit float3x2(n128 vec0, n128 vec1) : vec0(vec0), vec1(vec1) {}

		explicit float3x2(float f) : vec0(_hlslpp_set_ps(f, f, f, 0.0f)), vec1(_hlslpp_set_ps(f, f, f, 0.0f)) {}

		explicit float3x2(float f00, float f01,
		                  float f10, float f11,
		                  float f20, float f21) : vec0(_hlslpp_set_ps(f00, f10, f20, 0.0f)), vec1(_hlslpp_set_ps(f01, f11, f21, 0.0f)) {}

		float3x2(const float3x2& m) : vec0(m.vec0), vec1(m.vec1) {}

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

	struct float2x4
	{
		float2x4() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()) {}

		explicit float2x4(n128 vec0, n128 vec1) : vec0(vec0), vec1(vec1) {}

		explicit float2x4(float f00, float f01, float f02, float f03,
		                  float f10, float f11, float f12, float f13) : vec0(_hlslpp_set_ps(f00, f01, f02, f03)), vec1(_hlslpp_set_ps(f10, f11, f12, f13)) {}

		explicit float2x4(float f) : vec0(_hlslpp_set_ps(f, f, f, f)), vec1(_hlslpp_set_ps(f, f, f, f)) {}

		float2x4(const float2x4& m) : vec0(m.vec0), vec1(m.vec1) {}

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

	struct float4x2
	{
		float4x2() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()) {}

		explicit float4x2(n128 vec0, n128 vec1) : vec0(vec0), vec1(vec1) {}

		explicit float4x2(float f00, float f01,
		                  float f10, float f11,
		                  float f20, float f21,
		                  float f30, float f31) : vec0(_hlslpp_set_ps(f00, f10, f20, f30)), vec1(_hlslpp_set_ps(f01, f11, f21, f31)) {}

		explicit float4x2(float f) : vec0(_hlslpp_set_ps(f, f, f, f)), vec1(_hlslpp_set_ps(f, f, f, f)) {}

		float4x2(const float4x2& m) : vec0(m.vec0), vec1(m.vec1) {}

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

	struct float3x3
	{
		float3x3() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()), vec2(_hlslpp_setzero_ps()) {}

		explicit float3x3(const n128 vec0, const n128 vec1, const n128 vec2) : vec0(vec0), vec1(vec1), vec2(vec2) {}

		explicit float3x3(float f00, float f01, float f02,
		                  float f10, float f11, float f12,
		                  float f20, float f21, float f22) : vec0(_hlslpp_set_ps(f00, f01, f02, 0.0f)), vec1(_hlslpp_set_ps(f10, f11, f12, 0.0f)), vec2(_hlslpp_set_ps(f20, f21, f22, 0.0f)) {}

		float3x3(const quaternion& q);

		explicit float3x3(float f) : vec0(_hlslpp_set1_ps(f)), vec1(_hlslpp_set1_ps(f)), vec2(_hlslpp_set1_ps(f)) {}

		float3x3(const float3x3& m) : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}

		static const float3x3& identity() { static const float3x3 iden = float3x3(1, 0, 0, 0, 1, 0, 0, 0, 1); return iden; }

		union
		{
			n128 vec0;
			float f32_0[4];
			#include "swizzle/hlsl++_matrix_row0_1.h"
			#include "swizzle/hlsl++_matrix_row0_2.h"
			#include "swizzle/hlsl++_matrix_row0_3.h"
		};

		union
		{
			n128 vec1;
			float f32_1[4];
			#include "swizzle/hlsl++_matrix_row1_1.h"
			#include "swizzle/hlsl++_matrix_row1_2.h"
			#include "swizzle/hlsl++_matrix_row1_3.h"
		};

		union
		{
			n128 vec2;
			float f32_2[4];
			#include "swizzle/hlsl++_matrix_row2_1.h"
			#include "swizzle/hlsl++_matrix_row2_2.h"
			#include "swizzle/hlsl++_matrix_row2_3.h"
		};
	};

	struct float3x4
	{
		float3x4() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()), vec2(_hlslpp_setzero_ps()) {}

		explicit float3x4(n128 vec0, n128 vec1, n128 vec2) : vec0(vec0), vec1(vec1), vec2(vec2) {}

		explicit float3x4(float f00, float f01, float f02, float f03,
		                  float f10, float f11, float f12, float f13,
		                  float f20, float f21, float f22, float f23) 
			: vec0(_hlslpp_set_ps(f00, f01, f02, f03)), vec1(_hlslpp_set_ps(f10, f11, f12, f13)), vec2(_hlslpp_set_ps(f20, f21, f22, f23)) {}

		explicit float3x4(float f) : vec0(_hlslpp_set1_ps(f)), vec1(_hlslpp_set1_ps(f)), vec2(_hlslpp_set1_ps(f)) {}

		float3x4(const float3x4& m) : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}
		
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

	struct float4x3
	{
		float4x3() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()), vec2(_hlslpp_setzero_ps()) {}

		explicit float4x3(n128 vec0, n128 vec1, n128 vec2) : vec0(vec0), vec1(vec1), vec2(vec2) {}

		explicit float4x3(float f00, float f01, float f02,
		                  float f10, float f11, float f12,
		                  float f20, float f21, float f22,
		                  float f30, float f31, float f32)
			: vec0(_hlslpp_set_ps(f00, f10, f20, f30)), vec1(_hlslpp_set_ps(f01, f11, f21, f31)), vec2(_hlslpp_set_ps(f02, f12, f22, f32)) {}

		explicit float4x3(float f) : vec0(_hlslpp_set1_ps(f)), vec1(_hlslpp_set1_ps(f)), vec2(_hlslpp_set1_ps(f)) {}
		
		float4x3(const float4x3& m) : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}

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

	struct float4x4
	{
		float4x4() : vec0(_hlslpp_setzero_ps()), vec1(_hlslpp_setzero_ps()), vec2(_hlslpp_setzero_ps()), vec3(_hlslpp_setzero_ps()) {}

		explicit float4x4(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3) : vec0(vec0), vec1(vec1), vec2(vec2), vec3(vec3) {}


		explicit float4x4(float f00, float f01, float f02, float f03,
		                  float f10, float f11, float f12, float f13,
		                  float f20, float f21, float f22, float f23,
		                  float f30, float f31, float f32, float f33)
			: vec0(_hlslpp_set_ps(f00, f01, f02, f03)), vec1(_hlslpp_set_ps(f10, f11, f12, f13)), vec2(_hlslpp_set_ps(f20, f21, f22, f23)), vec3(_hlslpp_set_ps(f30, f31, f32, f33)) {}

		float4x4(const quaternion& q);

		explicit float4x4(float f) : vec0(_hlslpp_set1_ps(f)), vec1(_hlslpp_set1_ps(f)), vec2(_hlslpp_set1_ps(f)), vec3(_hlslpp_set1_ps(f)) {}
		
		float4x4(const float4x4& m) : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2), vec3(m.vec3) {}

		static const float4x4& identity() { static const float4x4 iden = float4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); return iden; };

		union
		{
			n128 vec0;
			float f32_0[4];
			#include "swizzle/hlsl++_matrix_row0_1.h"
			#include "swizzle/hlsl++_matrix_row0_2.h"
			#include "swizzle/hlsl++_matrix_row0_3.h"
			#include "swizzle/hlsl++_matrix_row0_4.h"
		};

		union
		{
			n128 vec1;
			float f32_1[4];
			#include "swizzle/hlsl++_matrix_row1_1.h"
			#include "swizzle/hlsl++_matrix_row1_2.h"
			#include "swizzle/hlsl++_matrix_row1_3.h"
			#include "swizzle/hlsl++_matrix_row1_4.h"
		};

		union
		{
			n128 vec2;
			float f32_2[4];
			#include "swizzle/hlsl++_matrix_row2_1.h"
			#include "swizzle/hlsl++_matrix_row2_2.h"
			#include "swizzle/hlsl++_matrix_row2_3.h"
			#include "swizzle/hlsl++_matrix_row2_4.h"
		};

		union
		{
			n128 vec3;
			float f32_3[4];
			#include "swizzle/hlsl++_matrix_row3_1.h"
			#include "swizzle/hlsl++_matrix_row3_2.h"
			#include "swizzle/hlsl++_matrix_row3_3.h"
			#include "swizzle/hlsl++_matrix_row3_4.h"
		};
	};

	//-----------------
	// Matrix functions
	//-----------------

	hlslpp_inline n128 _hlslpp_transpose_2x2_ps(n128 m)
	{
		return _hlslpp_perm_xzyw_ps(m);
	}

	hlslpp_inline void _hlslpp_transpose_3x3_ps(const n128& vec0, const n128& vec1, const n128& vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 shuf_tmp_0 = _hlslpp_shuf_xyxy_ps(vec0, vec1);
		n128 shuf_tmp_1 = _hlslpp_shuf_yzyz_ps(vec0, vec1);

		o_vec0 = _hlslpp_shuf_xzxw_ps(shuf_tmp_0, vec2);
		o_vec1 = _hlslpp_shuf_ywyw_ps(shuf_tmp_0, vec2);
		o_vec2 = _hlslpp_shuf_ywzw_ps(shuf_tmp_1, vec2);
	}

	hlslpp_inline void _hlslpp_transpose_4x4_ps(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
	{
		n128 shuf_tmp_0 = _hlslpp_shuf_xyxy_ps(vec0, vec1);
		n128 shuf_tmp_1 = _hlslpp_shuf_zwzw_ps(vec0, vec1);
		n128 shuf_tmp_2 = _hlslpp_shuf_xyxy_ps(vec2, vec3);
		n128 shuf_tmp_3 = _hlslpp_shuf_zwzw_ps(vec2, vec3);

		o_vec0 = _hlslpp_shuf_xzxz_ps(shuf_tmp_0, shuf_tmp_2);
		o_vec1 = _hlslpp_shuf_ywyw_ps(shuf_tmp_0, shuf_tmp_2);
		o_vec2 = _hlslpp_shuf_xzxz_ps(shuf_tmp_1, shuf_tmp_3);
		o_vec3 = _hlslpp_shuf_ywyw_ps(shuf_tmp_1, shuf_tmp_3);
	}

	hlslpp_inline n128 _hlslpp_det_2x2_ps(n128 m)
	{
		// The determinant for a 2x2 matrix is m00 * m11 - m01 * m10
		n128 shuf_1 = _hlslpp_perm_wzxx_ps(m);	// Shuffle w and z into x and y to multiply them together
		n128 prod = _hlslpp_mul_ps(m, shuf_1);		// Now this vector contains wx, zy, _, _
		n128 shuf_2 = _hlslpp_perm_yxxx_ps(prod);	// Shuffle yz into where xw is to subtract them
		n128 result = _hlslpp_sub_ps(prod, shuf_2);	// Determinant is now in the x component
		return result;
	}

	hlslpp_inline n128 _hlslpp_det_3x3_ps(n128 vec0, n128 vec1, n128 vec2)
	{
		// The determinant for a 3x3 matrix can be expressed as dot[ (m00, m01, m02), (m11 * m22 - m12 * m21, m12 * m20 - m10 * m22, m10 * m21 - m11 * m20) ]
		n128 shuf_1 = _hlslpp_perm_yzxw_ps(vec2);
		n128 prod_1 = _hlslpp_mul_ps(vec1, shuf_1);

		n128 shuf_2 = _hlslpp_perm_yzxw_ps(vec1);
		n128 prod_2 = _hlslpp_mul_ps(shuf_2, vec2);

		n128 sub = _hlslpp_sub_ps(prod_1, prod_2);

		n128 result = _hlslpp_dot3_ps(vec0, _hlslpp_perm_yzxw_ps(sub));

		return result;
	}

	inline n128 _hlslpp_det_4x4_ps(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3)
	{
		// Use the Laplace expansion to calculate the determinant in terms of 2x2 determinant multiplies instead of calculating
		// 3x3 determinants and then doing a dot product. https://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf
		n128 tmp_shuf_0 = _hlslpp_perm_xzxy_ps(vec0);
		n128 tmp_shuf_1 = _hlslpp_perm_yxwz_ps(vec1);
		n128 tmp_shuf_2 = _hlslpp_perm_yxwz_ps(vec0);
		n128 tmp_shuf_3 = _hlslpp_perm_xzxy_ps(vec1);

		n128 tmp_shuf_4 = _hlslpp_perm_zyyx_ps(vec2);
		n128 tmp_shuf_5 = _hlslpp_perm_wwzw_ps(vec3);
		n128 tmp_shuf_6 = _hlslpp_perm_wwzw_ps(vec2);
		n128 tmp_shuf_7 = _hlslpp_perm_zyyx_ps(vec3);

		n128 tmp_4_terms = _hlslpp_mul_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(tmp_shuf_0, tmp_shuf_1), _hlslpp_mul_ps(tmp_shuf_2, tmp_shuf_3)), _hlslpp_sub_ps(_hlslpp_mul_ps(tmp_shuf_4, tmp_shuf_5), _hlslpp_mul_ps(tmp_shuf_6, tmp_shuf_7)));

		n128 tmp_shuf_8 = _hlslpp_shuf_wzxx_ps(vec0, vec2);
		n128 tmp_shuf_9 = _hlslpp_shuf_ywzy_ps(vec1, vec3);
		n128 tmp_shuf_10 = _hlslpp_shuf_ywzy_ps(vec0, vec2);
		n128 tmp_shuf_11 = _hlslpp_shuf_wzxx_ps(vec1, vec3);

		n128 tmp_mul_0 = _hlslpp_sub_ps(_hlslpp_mul_ps(tmp_shuf_8, tmp_shuf_9), _hlslpp_mul_ps(tmp_shuf_10, tmp_shuf_11));

		n128 tmp_2_terms = _hlslpp_mul_ps(_hlslpp_perm_xyxy_ps(tmp_mul_0), _hlslpp_perm_zwzw_ps(tmp_mul_0));

		// Add all the results now (terms that subtract have already been inverted)
		n128 tmp_add_0 = _hlslpp_add_ps(_hlslpp_shuf_xzxx_ps(tmp_4_terms, tmp_2_terms), _hlslpp_shuf_ywyy_ps(tmp_4_terms, tmp_2_terms));
		n128 tmp_add_1 = _hlslpp_add_ps(_hlslpp_perm_xxxx_ps(tmp_add_0), _hlslpp_perm_yyyy_ps(tmp_add_0));
		n128 tmp_add_2 = _hlslpp_add_ps(_hlslpp_perm_xxxx_ps(tmp_add_1), _hlslpp_perm_zzzz_ps(tmp_add_0));

		return tmp_add_2;
	}

	inline n128 _hlslpp_inv_2x2_ps(n128 m)
	{
		n128 det = _hlslpp_perm_xxxx_ps(_hlslpp_det_2x2_ps(m));
		n128 shuf = _hlslpp_mul_ps(_hlslpp_perm_wyzx_ps(m), _hlslpp_set_ps(1.0f, -1.0f, -1.0f, 1.0f));
		return _hlslpp_div_ps(shuf, det);
	}

	inline void _hlslpp_inv_3x3_ps(const n128& vec0, const n128& vec1, const n128& vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 tmp_shuf_yzx_0 = _hlslpp_perm_yzxw_ps(vec0);
		n128 tmp_shuf_zxy_0 = _hlslpp_perm_zxyw_ps(vec0);
		n128 tmp_shuf_yzx_1 = _hlslpp_perm_yzxw_ps(vec1);
		n128 tmp_shuf_zxy_1 = _hlslpp_perm_zxyw_ps(vec1);
		n128 tmp_shuf_yzx_2 = _hlslpp_perm_yzxw_ps(vec2);
		n128 tmp_shuf_zxy_2 = _hlslpp_perm_zxyw_ps(vec2);

		// Compute the adjoint matrix directly with 2x2 determinants
		n128 tmp_row_0 = _hlslpp_msub_ps(tmp_shuf_yzx_1, tmp_shuf_zxy_2, _hlslpp_mul_ps(tmp_shuf_zxy_1, tmp_shuf_yzx_2));
		n128 tmp_row_1 = _hlslpp_msub_ps(tmp_shuf_zxy_0, tmp_shuf_yzx_2, _hlslpp_mul_ps(tmp_shuf_yzx_0, tmp_shuf_zxy_2));
		n128 tmp_row_2 = _hlslpp_msub_ps(tmp_shuf_yzx_0, tmp_shuf_zxy_1, _hlslpp_mul_ps(tmp_shuf_zxy_0, tmp_shuf_yzx_1));

		// Transpose the matrix
		n128 tmp_transp_row_0, tmp_transp_row_1, tmp_transp_row_2;
		_hlslpp_transpose_3x3_ps(tmp_row_0, tmp_row_1, tmp_row_2, tmp_transp_row_0, tmp_transp_row_1, tmp_transp_row_2);

		// Compute the determinant and divide all results by it
		n128 det = _hlslpp_perm_xxxx_ps(_hlslpp_det_3x3_ps(vec0, vec1, vec2));
		n128 invDet = _hlslpp_div_ps(f4_1, det);

		o_vec0 = _hlslpp_mul_ps(tmp_transp_row_0, invDet);
		o_vec1 = _hlslpp_mul_ps(tmp_transp_row_1, invDet);
		o_vec2 = _hlslpp_mul_ps(tmp_transp_row_2, invDet);
	}

	// https://gist.github.com/runestubbe/466ffdde670e6a697affe4a899bcf3a3
	inline void _hlslpp_inv_4x4_ps(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
	{
		n128 r0y_r1y_r0x_r1x = _hlslpp_movelh_ps(vec1, vec0);
		n128 r0z_r1z_r0w_r1w = _hlslpp_movelh_ps(vec2, vec3);
		n128 r2y_r3y_r2x_r3x = _hlslpp_movehl_ps(vec0, vec1);
		n128 r2z_r3z_r2w_r3w = _hlslpp_movehl_ps(vec3, vec2);

		n128 r1y_r2y_r1x_r2x = _hlslpp_shuf_yzyz_ps(vec1, vec0);
		n128 r1z_r2z_r1w_r2w = _hlslpp_shuf_yzyz_ps(vec2, vec3);
		n128 r3y_r0y_r3x_r0x = _hlslpp_shuf_wxwx_ps(vec1, vec0);
		n128 r3z_r0z_r3w_r0w = _hlslpp_shuf_wxwx_ps(vec2, vec3);

		n128 r0_wzyx = _hlslpp_shuf_zxxz_ps(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x);
		n128 r1_wzyx = _hlslpp_shuf_wyyw_ps(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x);
		n128 r2_wzyx = _hlslpp_shuf_zxxz_ps(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x);
		n128 r3_wzyx = _hlslpp_shuf_wyyw_ps(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x);
		n128 r0_xyzw = _hlslpp_shuf_zxxz_ps(r0y_r1y_r0x_r1x, r0z_r1z_r0w_r1w);

		n128 inner12_23 = _hlslpp_sub_ps(_hlslpp_mul_ps(r1y_r2y_r1x_r2x, r2z_r3z_r2w_r3w), _hlslpp_mul_ps(r1z_r2z_r1w_r2w, r2y_r3y_r2x_r3x));
		n128 inner02_13 = _hlslpp_sub_ps(_hlslpp_mul_ps(r0y_r1y_r0x_r1x, r2z_r3z_r2w_r3w), _hlslpp_mul_ps(r0z_r1z_r0w_r1w, r2y_r3y_r2x_r3x));
		n128 inner30_01 = _hlslpp_sub_ps(_hlslpp_mul_ps(r3z_r0z_r3w_r0w, r0y_r1y_r0x_r1x), _hlslpp_mul_ps(r3y_r0y_r3x_r0x, r0z_r1z_r0w_r1w));

		n128 inner12 = _hlslpp_shuf_xzzx_ps(inner12_23, inner12_23);
		n128 inner23 = _hlslpp_shuf_ywwy_ps(inner12_23, inner12_23);

		n128 inner02 = _hlslpp_shuf_xzzx_ps(inner02_13, inner02_13);
		n128 inner13 = _hlslpp_shuf_ywwy_ps(inner02_13, inner02_13);

		n128 minors0 = _hlslpp_add_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(r3_wzyx, inner12), _hlslpp_mul_ps(r2_wzyx, inner13)), _hlslpp_mul_ps(r1_wzyx, inner23));

		n128 denom = _hlslpp_mul_ps(r0_xyzw, minors0);

		denom = _hlslpp_add_ps(denom, _hlslpp_shuf_yxwz_ps(denom, denom));	// x+y		x+y			z+w			z+w
		denom = _hlslpp_sub_ps(denom, _hlslpp_shuf_zzxx_ps(denom, denom));	// x+y-z-w  x+y-z-w		z+w-x-y		z+w-x-y

		n128 rcp_denom_ppnn = _hlslpp_div_ps(f4_1, denom);
		o_vec0 = _hlslpp_mul_ps(minors0, rcp_denom_ppnn);

		n128 inner30 = _hlslpp_shuf_xzzx_ps(inner30_01, inner30_01);
		n128 inner01 = _hlslpp_shuf_ywwy_ps(inner30_01, inner30_01);

		n128 minors1 = _hlslpp_sub_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(r2_wzyx, inner30), _hlslpp_mul_ps(r0_wzyx, inner23)), _hlslpp_mul_ps(r3_wzyx, inner02));
		o_vec1 = _hlslpp_mul_ps(minors1, rcp_denom_ppnn);

		n128 minors2 = _hlslpp_sub_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(r0_wzyx, inner13), _hlslpp_mul_ps(r1_wzyx, inner30)), _hlslpp_mul_ps(r3_wzyx, inner01));
		o_vec2 = _hlslpp_mul_ps(minors2, rcp_denom_ppnn);

		n128 minors3 = _hlslpp_add_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(r1_wzyx, inner02), _hlslpp_mul_ps(r0_wzyx, inner12)), _hlslpp_mul_ps(r2_wzyx, inner01));
		o_vec3 = _hlslpp_mul_ps(minors3, rcp_denom_ppnn);
	}

	hlslpp_inline n128 _hlslpp_trace_2x2_ps(const n128 m)
	{
		return _hlslpp_add_ps(_hlslpp_perm_xxxx_ps(m), _hlslpp_perm_wwww_ps(m));
	}

	hlslpp_inline n128 _hlslpp_trace_3x3_ps(const n128 vec0, const n128 vec1, const n128 vec2)
	{
		return _hlslpp_add_ps(_hlslpp_add_ps(_hlslpp_perm_xxxx_ps(vec0), _hlslpp_perm_yyyy_ps(vec1)), _hlslpp_perm_zzzz_ps(vec2));
	}

	hlslpp_inline n128 _hlslpp_trace_4x4_ps(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3)
	{
		n128 sum1 = _hlslpp_add_ps(_hlslpp_perm_xxxx_ps(vec0), _hlslpp_perm_yyyy_ps(vec1));
		n128 sum2 = _hlslpp_add_ps(_hlslpp_perm_zzzz_ps(vec2), _hlslpp_perm_wwww_ps(vec3));
		return _hlslpp_add_ps(sum1, sum2);
	}

	inline n128 _hlslpp_mul_1x2_2x1_ps(n128 m1_vec, n128 m2_vec)
	{
		n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec), m2_vec);
		n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1_vec), _hlslpp_perm_zwxx_ps(m2_vec));
		n128 result = _hlslpp_add_ps(mul1, mul2);
		return result;
	}

	inline n128 _hlslpp_mul_1x2_2xM_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1)
	{
		n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec), m2_vec0);
		n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1_vec), m2_vec1);
		n128 result = _hlslpp_add_ps(mul1, mul2);
		return result;
	}

	inline n128 _hlslpp_mul_1x3_3x2_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1)
	{
		n128 dpx = _hlslpp_dot3_ps(m1_vec, m2_vec0);
		n128 dpy = _hlslpp_dot3_ps(m1_vec, m2_vec1);
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
		return result;
	}

	inline n128 _hlslpp_mul_1x3_3xM_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2)
	{
		n128 mul0 = _hlslpp_mul_ps(m2_vec0, _hlslpp_perm_xxxx_ps(m1_vec));
		n128 mul1 = _hlslpp_madd_ps(m2_vec1, _hlslpp_perm_yyyy_ps(m1_vec), mul0);
		n128 result = _hlslpp_madd_ps(m2_vec2, _hlslpp_perm_zzzz_ps(m1_vec), mul1);
		return result;
	}

	inline n128 _hlslpp_mul_1x4_4x2_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1)
	{
		n128 dpx = _hlslpp_dot4_ps(m1_vec, m2_vec0);
		n128 dpy = _hlslpp_dot4_ps(m1_vec, m2_vec1);
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
		return result;
	}

	inline n128 _hlslpp_mul_1x4_4x3_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2)
	{
		n128 dpx = _hlslpp_dot4_ps(m1_vec, m2_vec0);
		n128 dpy = _hlslpp_dot4_ps(m1_vec, m2_vec1);
		n128 dpz = _hlslpp_dot4_ps(m1_vec, m2_vec2);
		n128 result = _hlslpp_blend_ps(dpy, _hlslpp_shuf_xxxx_ps(dpx, dpz), HLSLPP_BLEND_MASK(0, 1, 0, 1));
		return result;
	}

	inline n128 _hlslpp_mul_1x4_4x4_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, const n128& m2_vec3)
	{
		n128 mul0 = _hlslpp_mul_ps(m2_vec0, _hlslpp_perm_xxxx_ps(m1_vec));
		n128 mul1 = _hlslpp_madd_ps(m2_vec1, _hlslpp_perm_yyyy_ps(m1_vec), mul0);
		n128 mul2 = _hlslpp_madd_ps(m2_vec2, _hlslpp_perm_zzzz_ps(m1_vec), mul1);
		n128 result = _hlslpp_madd_ps(m2_vec3, _hlslpp_perm_wwww_ps(m1_vec), mul2);
		return result;
	}

	inline n128 _hlslpp_mul_2x2_2x1_ps(const n128& m1_vec, const n128& m2_vec)
	{
		n128 dpx = _hlslpp_dot2_ps(m1_vec, m2_vec);
		n128 dpy = _hlslpp_dot2_ps(_hlslpp_perm_zwxx_ps(m1_vec), m2_vec);
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
		return result;
	}

	inline n128 _hlslpp_mul_2x2_2x2_ps(const n128& m1_vec, const n128& m2_vec)
	{
		n128 mul0 = _hlslpp_mul_ps(m1_vec, _hlslpp_perm_xwxw_ps(m2_vec));
		n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_yxwz_ps(m1_vec), _hlslpp_perm_zyzy_ps(m2_vec));
		n128 result = _hlslpp_add_ps(mul0, mul1);
		return result;
	}

	inline void _hlslpp_mul_2x2_2xM_ps(const n128& m1_vec, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
	{
		n128 mul0 = _hlslpp_mul_ps(m2_vec0, _hlslpp_perm_xxxx_ps(m1_vec));
		o_vec0 = _hlslpp_madd_ps(m2_vec1, _hlslpp_perm_yyyy_ps(m1_vec), mul0);

		n128 mul1 = _hlslpp_mul_ps(m2_vec0, _hlslpp_perm_zzzz_ps(m1_vec));
		o_vec1 = _hlslpp_madd_ps(m2_vec1, _hlslpp_perm_wwww_ps(m1_vec), mul1);
	}

	inline n128 _hlslpp_mul_Nx2_2x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec)
	{
		n128 mul0 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec));
		n128 result = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec), mul0);
		return result;
	}

	inline void _hlslpp_mul_Nx2_2x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec, n128& o_vec0, n128& o_vec1)
	{
		n128 mul0 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec));
		o_vec0 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_zzzz_ps(m2_vec), mul0);

		n128 mul1 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_yyyy_ps(m2_vec));
		o_vec1 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_wwww_ps(m2_vec), mul1);
	}

	inline void _hlslpp_mul_3x2_2xM_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 mul0 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec1, mul0);

		n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec0);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul1);

		n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec0);
		o_vec2 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec1, mul2);
	}

	inline void _hlslpp_mul_4x2_2x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 mul0 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec0));
		o_vec0 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_xxxx_ps(m2_vec1), mul0);

		n128 mul1 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_yyyy_ps(m2_vec0));
		o_vec1 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec1), mul1);

		n128 mul2 = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_zzzz_ps(m2_vec0));
		o_vec2 = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_zzzz_ps(m2_vec1), mul2);
	}

	inline void _hlslpp_mul_4x2_2x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
	{
		n128 mul0 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec1, mul0);

		n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec0);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul1);

		n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec0);
		o_vec2 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec1, mul2);

		n128 mul3 = _hlslpp_mul_ps(_hlslpp_perm_wwww_ps(m1_vec0), m2_vec0);
		o_vec3 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec1), m2_vec1, mul3);
	}

	inline n128 _hlslpp_mul_2x3_3x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec)
	{
		n128 dpx = _hlslpp_dot3_ps(m1_vec0, m2_vec);
		n128 dpy = _hlslpp_dot3_ps(m1_vec1, m2_vec);
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
		return result;
	}

	inline n128 _hlslpp_mul_2x3_3x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1)
	{
		n128 dpx = _hlslpp_dot3_ps(m1_vec0, m2_vec0);
		n128 dpy = _hlslpp_dot3_ps(m1_vec0, m2_vec1);
		n128 dpz = _hlslpp_dot3_ps(m1_vec1, m2_vec0);
		n128 dpw = _hlslpp_dot3_ps(m1_vec1, m2_vec1);
		n128 result = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx, dpz), _hlslpp_shuf_xxxx_ps(dpy, dpw), HLSLPP_BLEND_MASK(1, 0, 1, 0));
		return result;
	}

	inline void _hlslpp_mul_2x3_3xM_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1)
	{
		n128 mul0 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		n128 mul1 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec1, mul0);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec2, mul1);

		n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec0);
		n128 mul3 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul2);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec2, mul3);
	}

	inline n128 _hlslpp_mul_2x4_4x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec)
	{
		n128 dpx = _hlslpp_dot4_ps(m1_vec0, m2_vec);
		n128 dpy = _hlslpp_dot4_ps(m1_vec1, m2_vec);
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_perm_xxxx_ps(dpy), HLSLPP_BLEND_MASK(1, 0, 1, 1));
		return result;
	}

	inline n128 _hlslpp_mul_2x4_4x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1)
	{
		n128 dpx = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpz = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpw = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 result = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx, dpz), _hlslpp_shuf_xxxx_ps(dpy, dpw), HLSLPP_BLEND_MASK(1, 0, 1, 0));
		return result;
	}

	inline void _hlslpp_mul_2x4_4x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1)
	{
		n128 dpx0 = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpz0 = _hlslpp_dot4_ps(m1_vec0, m2_vec2);
		o_vec0 = _hlslpp_blend_ps(dpy0, _hlslpp_shuf_xxxx_ps(dpx0, dpz0), HLSLPP_BLEND_MASK(0, 1, 0, 1));

		n128 dpx1 = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpy1 = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1_vec1, m2_vec2);
		o_vec1 = _hlslpp_blend_ps(dpy1, _hlslpp_shuf_xxxx_ps(dpx1, dpz1), HLSLPP_BLEND_MASK(0, 1, 0, 1));
	}

	inline void _hlslpp_mul_2x4_4x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, const n128& m2_vec3, n128& o_vec0, n128& o_vec1)
	{
		// First row
		n128 mul0x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		n128 mad0y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec1, mul0x);
		n128 mad0z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec2, mad0y);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec0), m2_vec3, mad0z);

		// Second row
		n128 mul1x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec0);
		n128 mad1y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul1x);
		n128 mad1z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec2, mad1y);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec1), m2_vec3, mad1z);
	}

	inline n128 _hlslpp_mul_3x3_3x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec)
	{
		n128 dpx = _hlslpp_dot3_ps(m1_vec0, m2_vec);
		n128 dpy = _hlslpp_dot3_ps(m1_vec1, m2_vec);
		n128 dpz = _hlslpp_dot3_ps(m1_vec2, m2_vec);
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_shuf_xxxx_ps(dpy, dpz), HLSLPP_BLEND_MASK(1, 0, 0, 1));
		return result;
	}

	inline void _hlslpp_mul_3x3_3x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
	{
		n128 dpx0 = _hlslpp_dot3_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot3_ps(m1_vec1, m2_vec0);
		n128 dpz0 = _hlslpp_dot3_ps(m1_vec2, m2_vec0);
		o_vec0 = _hlslpp_blend_ps(dpx0, _hlslpp_shuf_xxxx_ps(dpy0, dpz0), HLSLPP_BLEND_MASK(1, 0, 0, 1));

		n128 dpx1 = _hlslpp_dot3_ps(m1_vec0, m2_vec1);
		n128 dpy1 = _hlslpp_dot3_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot3_ps(m1_vec2, m2_vec1);
		o_vec1 = _hlslpp_blend_ps(dpx1, _hlslpp_shuf_xxxx_ps(dpy1, dpz1), HLSLPP_BLEND_MASK(1, 0, 0, 1));
	}

	inline void _hlslpp_mul_3x3_3x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		// First row
		n128 mul1x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec0));
		n128 mad1y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec0), mul1x);
		o_vec0 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec0), mad1y);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec1));
		n128 mad2y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec1), mul2x);
		o_vec1 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec1), mad2y);

		// Third row
		n128 mul3x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec2));
		n128 mad3y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec2), mul3x);
		o_vec2 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec2), mad3y);
	}

	inline void _hlslpp_mul_3x3_3x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		// First row
		n128 mul1x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		n128 mad1y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec1, mul1x);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec2, mad1y);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec0);
		n128 mad2y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul2x);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec2, mad2y);

		// Third row
		n128 mul3x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec2), m2_vec0);
		n128 mad3y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec2), m2_vec1, mul3x);
		o_vec2 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec2), m2_vec2, mad3y);
	}

	inline n128 _hlslpp_mul_3x4_4x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec)
	{
		n128 dpx = _hlslpp_dot4_ps(m1_vec0, m2_vec);
		n128 dpy = _hlslpp_dot4_ps(m1_vec1, m2_vec);
		n128 dpz = _hlslpp_dot4_ps(m1_vec2, m2_vec);
		n128 result = _hlslpp_blend_ps(dpy, _hlslpp_shuf_xxxx_ps(dpx, dpz), HLSLPP_BLEND_MASK(0, 1, 0, 1));
		return result;
	}

	inline void _hlslpp_mul_3x4_4x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
	{
		n128 dpx0 = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpz0 = _hlslpp_dot4_ps(m1_vec2, m2_vec0);
		o_vec0 = _hlslpp_blend_ps(dpy0, _hlslpp_shuf_xxxx_ps(dpx0, dpz0), HLSLPP_BLEND_MASK(0, 1, 0, 1));

		n128 dpx1 = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpy1 = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1_vec2, m2_vec1);
		o_vec1 = _hlslpp_blend_ps(dpy1, _hlslpp_shuf_xxxx_ps(dpx1, dpz1), HLSLPP_BLEND_MASK(0, 1, 0, 1));
	}

	inline void _hlslpp_mul_3x4_4x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 dpx0 = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpz0 = _hlslpp_dot4_ps(m1_vec0, m2_vec2);
		o_vec0 = _hlslpp_blend_ps(dpy0, _hlslpp_shuf_xxxx_ps(dpx0, dpz0), HLSLPP_BLEND_MASK(0, 1, 0, 1));

		n128 dpx1 = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpy1 = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1_vec1, m2_vec2);
		o_vec1 = _hlslpp_blend_ps(dpy1, _hlslpp_shuf_xxxx_ps(dpx1, dpz1), HLSLPP_BLEND_MASK(0, 1, 0, 1));

		n128 dpx2 = _hlslpp_dot4_ps(m1_vec2, m2_vec0);
		n128 dpy2 = _hlslpp_dot4_ps(m1_vec2, m2_vec1);
		n128 dpz2 = _hlslpp_dot4_ps(m1_vec2, m2_vec2);
		o_vec2 = _hlslpp_blend_ps(dpy2, _hlslpp_shuf_xxxx_ps(dpx2, dpz2), HLSLPP_BLEND_MASK(0, 1, 0, 1));
	}

	inline void _hlslpp_mul_3x4_4x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, const n128& m2_vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		// First row
		n128 mul1x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		n128 mad1y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec1, mul1x);
		n128 mad1z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec2, mad1y);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec0), m2_vec3, mad1z);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec0);
		n128 mad2y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul2x);
		n128 mad2z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec2, mad2y);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec1), m2_vec3, mad2z);

		// Third row
		n128 mul3x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec2), m2_vec0);
		n128 mad3y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec2), m2_vec1, mul3x);
		n128 mad3z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec2), m2_vec2, mad3y);
		o_vec2 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec2), m2_vec3, mad3z);
	}

	inline n128 _hlslpp_mul_4x3_3x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec)
	{
		n128 mul1x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec));
		n128 mad1y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec), mul1x);
		n128 result = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec), mad1y);
		return result;
	}

	inline void _hlslpp_mul_4x3_3x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
	{
		// First row
		n128 mul0x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec0));
		n128 mad0y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec0), mul0x);
		o_vec0 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec0), mad0y);

		// Second row
		n128 mul1x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec1));
		n128 mad1y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec1), mul1x);
		o_vec1 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec1), mad1y);
	}

	inline void _hlslpp_mul_4x3_3x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		// First row
		n128 mul0x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec0));
		n128 mad0y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_xxxx_ps(m2_vec1), mul0x);
		o_vec0 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_xxxx_ps(m2_vec2), mad0y);

		// Second row
		n128 mul1x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_yyyy_ps(m2_vec0));
		n128 mad1y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec1), mul1x);
		o_vec1 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_yyyy_ps(m2_vec2), mad1y);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_zzzz_ps(m2_vec0));
		n128 mad2y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_zzzz_ps(m2_vec1), mul2x);
		o_vec2 = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec2), mad2y);
	}

	inline void _hlslpp_mul_4x3_3x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
	{
		// First row
		n128 mul0x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		n128 mad0y = _hlslpp_madd_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec1, mul0x);
		o_vec0 = _hlslpp_madd_ps(_hlslpp_perm_xxxx_ps(m1_vec2), m2_vec2, mad0y);

		// Second row
		n128 mul1x = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec0);
		n128 mad1y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul1x);
		o_vec1 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec2), m2_vec2, mad1y);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec0);
		n128 mad2y = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec1, mul2x);
		o_vec2 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec2), m2_vec2, mad2y);

		// Second row
		n128 mul3x = _hlslpp_mul_ps(_hlslpp_perm_wwww_ps(m1_vec0), m2_vec0);
		n128 mad3y = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec1), m2_vec1, mul3x);
		o_vec3 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1_vec2), m2_vec2, mad3y);
	}

	inline n128 _hlslpp_mul_4x4_4x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m1_vec3, const n128& m2_vec)
	{
		n128 dpx = _hlslpp_dot4_ps(m1_vec0, m2_vec);
		n128 dpy = _hlslpp_dot4_ps(m1_vec1, m2_vec);
		n128 dpz = _hlslpp_dot4_ps(m1_vec2, m2_vec);
		n128 dpw = _hlslpp_dot4_ps(m1_vec3, m2_vec);

		n128 result = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx, dpz), _hlslpp_shuf_xxxx_ps(dpy, dpw), HLSLPP_BLEND_MASK(1, 0, 1, 0));
		return result;
	}

	inline void _hlslpp_mul_4x4_4x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m1_vec3, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
	{
		n128 dpx0 = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpz0 = _hlslpp_dot4_ps(m1_vec2, m2_vec0);
		n128 dpw0 = _hlslpp_dot4_ps(m1_vec3, m2_vec0);

		o_vec0 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx0, dpz0), _hlslpp_shuf_xxxx_ps(dpy0, dpw0), HLSLPP_BLEND_MASK(1, 0, 1, 0));

		n128 dpx1 = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpy1 = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1_vec2, m2_vec1);
		n128 dpw1 = _hlslpp_dot4_ps(m1_vec3, m2_vec1);

		o_vec1 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx1, dpz1), _hlslpp_shuf_xxxx_ps(dpy1, dpw1), HLSLPP_BLEND_MASK(1, 0, 1, 0));
	}

	inline void _hlslpp_mul_4x4_4x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m1_vec3, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 dpx0 = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpz0 = _hlslpp_dot4_ps(m1_vec2, m2_vec0);
		n128 dpw0 = _hlslpp_dot4_ps(m1_vec3, m2_vec0);

		o_vec0 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx0, dpz0), _hlslpp_shuf_xxxx_ps(dpy0, dpw0), HLSLPP_BLEND_MASK(1, 0, 1, 0));

		n128 dpx1 = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpy1 = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1_vec2, m2_vec1);
		n128 dpw1 = _hlslpp_dot4_ps(m1_vec3, m2_vec1);

		o_vec1 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx1, dpz1), _hlslpp_shuf_xxxx_ps(dpy1, dpw1), HLSLPP_BLEND_MASK(1, 0, 1, 0));

		n128 dpx2 = _hlslpp_dot4_ps(m1_vec0, m2_vec2);
		n128 dpy2 = _hlslpp_dot4_ps(m1_vec1, m2_vec2);
		n128 dpz2 = _hlslpp_dot4_ps(m1_vec2, m2_vec2);
		n128 dpw2 = _hlslpp_dot4_ps(m1_vec3, m2_vec2);

		o_vec2 = _hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx2, dpz2), _hlslpp_shuf_xxxx_ps(dpy2, dpw2), HLSLPP_BLEND_MASK(1, 0, 1, 0));
	}

	inline void _hlslpp_mul_4x4_4x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m1_vec3, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, const n128& m2_vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
	{
		// First row
		n128 mul1x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec0));
		n128 mad1y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec0), mul1x);
		n128 mad1z = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec0), mad1y);
		o_vec0 = _hlslpp_madd_ps(m1_vec3, _hlslpp_perm_wwww_ps(m2_vec0), mad1z);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec1));
		n128 mad2y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec1), mul2x);
		n128 mad2z = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec1), mad2y);
		o_vec1 = _hlslpp_madd_ps(m1_vec3, _hlslpp_perm_wwww_ps(m2_vec1), mad2z);

		// Third row
		n128 mul3x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec2));
		n128 mad3y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec2), mul3x);
		n128 mad3z = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec2), mad3y);
		o_vec2 = _hlslpp_madd_ps(m1_vec3, _hlslpp_perm_wwww_ps(m2_vec2), mad3z);

		// Fourth row
		n128 mul4x = _hlslpp_mul_ps(m1_vec0, _hlslpp_perm_xxxx_ps(m2_vec3));
		n128 mad4y = _hlslpp_madd_ps(m1_vec1, _hlslpp_perm_yyyy_ps(m2_vec3), mul4x);
		n128 mad4z = _hlslpp_madd_ps(m1_vec2, _hlslpp_perm_zzzz_ps(m2_vec3), mad4y);
		o_vec3 = _hlslpp_madd_ps(m1_vec3, _hlslpp_perm_wwww_ps(m2_vec3), mad4z);
	}

	hlslpp_inline float1x1 mul(const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec)); }

	hlslpp_inline float1x2 mul(const float1x1& m1, const float1x2& m2) { return float1x2(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec)); }

	hlslpp_inline float1x3 mul(const float1x1& m1, const float1x3& m2) { return float1x3(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec)); }

	hlslpp_inline float1x4 mul(const float1x1& m1, const float1x4& m2) { return float1x4(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec)); }

	hlslpp_inline float2x1 mul(const float2x1& m1, const float1x1& m2) { return float2x1(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec))); }

	hlslpp_inline float3x1 mul(const float3x1& m1, const float1x1& m2) { return float3x1(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec))); }

	hlslpp_inline float4x1 mul(const float4x1& m1, const float1x1& m2) { return float4x1(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec))); }

	hlslpp_inline float2x2 mul(const float2x1& m1, const float1x2& m2) { return float2x2(_hlslpp_mul_ps(_hlslpp_perm_xxyy_ps(m1.vec), _hlslpp_perm_xyxy_ps(m2.vec))); }

	hlslpp_inline float2x3 mul(const float2x1& m1, const float1x3& m2) { return float2x3(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1.vec), m2.vec)); }

	hlslpp_inline float2x4 mul(const float2x1& m1, const float1x4& m2) { return float2x4(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1.vec), m2.vec)); }

	hlslpp_inline float3x2 mul(const float3x1& m1, const float1x2& m2) { return float3x2(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec)), _hlslpp_mul_ps(m1.vec, _hlslpp_perm_yyyy_ps(m2.vec))); }

	hlslpp_inline float4x2 mul(const float4x1& m1, const float1x2& m2) { return float4x2(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec)), _hlslpp_mul_ps(m1.vec, _hlslpp_perm_yyyy_ps(m2.vec))); }

	hlslpp_inline float3x3 mul(const float3x1& m1, const float1x3& m2)
	{
		return float3x3(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec)), _hlslpp_mul_ps(m1.vec, _hlslpp_perm_yyyy_ps(m2.vec)), _hlslpp_mul_ps(m1.vec, _hlslpp_perm_zzzz_ps(m2.vec)));
	}

	hlslpp_inline float4x3 mul(const float4x1& m1, const float1x3& m2)
	{
		return float4x3(_hlslpp_mul_ps(m1.vec, _hlslpp_perm_xxxx_ps(m2.vec)), _hlslpp_mul_ps(m1.vec, _hlslpp_perm_yyyy_ps(m2.vec)), _hlslpp_mul_ps(m1.vec, _hlslpp_perm_zzzz_ps(m2.vec)));
	}

	hlslpp_inline float3x4 mul(const float3x1& m1, const float1x4& m2)
	{
		return float3x4(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1.vec), m2.vec));
	}

	hlslpp_inline float4x4 mul(const float4x1& m1, const float1x4& m2)
	{
		return float4x4(_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1.vec), m2.vec), _hlslpp_mul_ps(_hlslpp_perm_wwww_ps(m1.vec), m2.vec));
	}

	hlslpp_inline float1x1 mul(const float1x2& m1, const float2x1& m2) { return float1x1(_hlslpp_dot2_ps(m1.vec, m2.vec)); }

	hlslpp_inline float1x2 mul(const float1x2& m1, const float2x2& m2) { return float1x2(_hlslpp_mul_1x2_2x1_ps(m1.vec, m2.vec)); }

	hlslpp_inline float1x3 mul(const float1x2& m1, const float2x3& m2) { return float1x3(_hlslpp_mul_1x2_2xM_ps(m1.vec, m2.vec0, m2.vec1)); }

	hlslpp_inline float1x4 mul(const float1x2& m1, const float2x4& m2) { return float1x4(_hlslpp_mul_1x2_2xM_ps(m1.vec, m2.vec0, m2.vec1)); }

	hlslpp_inline float1x1 mul(const float1x3& m1, const float3x1& m2) { return float1x1(_hlslpp_dot3_ps(m1.vec, m2.vec)); }

	hlslpp_inline float1x2 mul(const float1x3& m1, const float3x2& m2) { return float1x2(_hlslpp_mul_1x3_3x2_ps(m1.vec, m2.vec0, m2.vec1)); }

	hlslpp_inline float1x3 mul(const float1x3& m1, const float3x3& m2) { return float1x3(_hlslpp_mul_1x3_3xM_ps(m1.vec, m2.vec0, m2.vec1, m2.vec2)); }

	hlslpp_inline float1x4 mul(const float1x3& m1, const float3x4& m2) { return float1x4(_hlslpp_mul_1x3_3xM_ps(m1.vec, m2.vec0, m2.vec1, m2.vec2)); }

	hlslpp_inline float1x1 mul(const float1x4& m1, const float4x1& m2) { return float1x1(_hlslpp_dot4_ps(m1.vec, m2.vec)); }

	hlslpp_inline float1x2 mul(const float1x4& m1, const float4x2& m2) { return float1x2(_hlslpp_mul_1x4_4x2_ps(m1.vec, m2.vec0, m2.vec1)); }

	hlslpp_inline float1x3 mul(const float1x4& m1, const float4x3& m2) { return float1x3(_hlslpp_mul_1x4_4x3_ps(m1.vec, m2.vec0, m2.vec1, m2.vec2)); }

	hlslpp_inline float1x4 mul(const float1x4& m1, const float4x4& m2) { return float1x4(_hlslpp_mul_1x4_4x4_ps(m1.vec, m2.vec0, m2.vec1, m2.vec2, m2.vec3)); }

	hlslpp_inline float2x1 mul(const float2x2& m1, const float2x1& m2) { return float2x1(_hlslpp_mul_2x2_2x1_ps(m1.vec, m2.vec)); }

	hlslpp_inline float2x2 mul(const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_mul_2x2_2x2_ps(m1.vec, m2.vec)); }

	hlslpp_inline float2x3 mul(const float2x2& m1, const float2x3& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x2_2xM_ps(m1.vec, m2.vec0, m2.vec1, vec0, vec1);
		return float2x3(vec0, vec1);
	}

	hlslpp_inline float2x4 mul(const float2x2& m1, const float2x4& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x2_2xM_ps(m1.vec, m2.vec0, m2.vec1, vec0, vec1);
		return float2x4(vec0, vec1);
	}

	hlslpp_inline float3x1 mul(const float3x2& m1, const float2x1& m2) { return float3x1(_hlslpp_mul_Nx2_2x1_ps(m1.vec0, m1.vec1, m2.vec)); }

	hlslpp_inline float4x1 mul(const float4x2& m1, const float2x1& m2) { return float4x1(_hlslpp_mul_Nx2_2x1_ps(m1.vec0, m1.vec1, m2.vec)); }

	hlslpp_inline float3x2 mul(const float3x2& m1, const float2x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_Nx2_2x2_ps(m1.vec0, m1.vec1, m2.vec, vec0, vec1);
		return float3x2(vec0, vec1);
	}

	hlslpp_inline float4x2 mul(const float4x2& m1, const float2x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_Nx2_2x2_ps(m1.vec0, m1.vec1, m2.vec, vec0, vec1);
		return float4x2(vec0, vec1);
	}

	hlslpp_inline float3x3 mul(const float3x2& m1, const float2x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x2_2xM_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float3x4 mul(const float3x2& m1, const float2x4& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x2_2xM_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, vec0, vec1, vec2);
		return float3x4(vec0, vec1, vec2);
	}


	hlslpp_inline float4x3 mul(const float4x2& m1, const float2x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_4x2_2x3_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, vec0, vec1, vec2);
		return float4x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 mul(const float4x2& m1, const float2x4& m2)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_mul_4x2_2x4_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	hlslpp_inline float2x1 mul(const float2x3& m1, const float3x1& m2)
	{
		return float2x1(_hlslpp_mul_2x3_3x1_ps(m1.vec0, m1.vec1, m2.vec));
	}

	hlslpp_inline float2x2 mul(const float2x3& m1, const float3x2& m2)
	{
		return float2x2(_hlslpp_mul_2x3_3x2_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1));
	}

	hlslpp_inline float2x3 mul(const float2x3& m1, const float3x3& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x3_3xM_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, m2.vec2, vec0, vec1);
		return float2x3(vec0, vec1);
	}

	hlslpp_inline float2x4 mul(const float2x3& m1, const float3x4& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x3_3xM_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, m2.vec2, vec0, vec1);
		return float2x4(vec0, vec1);
	}

	hlslpp_inline float2x1 mul(const float2x4& m1, const float4x1& m2)
	{
		return float2x1(_hlslpp_mul_2x4_4x1_ps(m1.vec0, m1.vec1, m2.vec));
	}

	hlslpp_inline float2x2 mul(const float2x4& m1, const float4x2& m2)
	{
		return float2x2(_hlslpp_mul_2x4_4x2_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1));
	}

	hlslpp_inline float2x3 mul(const float2x4& m1, const float4x3& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x4_4x3_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, m2.vec2, vec0, vec1);
		return float2x3(vec0, vec1);
	}

	hlslpp_inline float2x4 mul(const float2x4& m1, const float4x4& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_2x4_4x4_ps(m1.vec0, m1.vec1, m2.vec0, m2.vec1, m2.vec2, m2.vec3, vec0, vec1);
		return float2x4(vec0, vec1);
	}

	hlslpp_inline float3x1 mul(const float3x3& m1, const float3x1& m2)
	{
		return float3x1(_hlslpp_mul_3x3_3x1_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec));
	}

	hlslpp_inline float3x2 mul(const float3x3& m1, const float3x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_3x3_3x2_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, vec0, vec1);
		return float3x2(vec0, vec1);
	}

	hlslpp_inline float3x3 mul(const float3x3& m1, const float3x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x3_3x3_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, m2.vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float3x4 mul(const float3x3& m1, const float3x4& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x3_3x4_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, m2.vec2, vec0, vec1, vec2);
		return float3x4(vec0, vec1, vec2);
	}

	hlslpp_inline float3x1 mul(const float3x4& m1, const float4x1& m2)
	{

		return float3x1(_hlslpp_mul_3x4_4x1_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec));
	}

	hlslpp_inline float3x2 mul(const float3x4& m1, const float4x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_3x4_4x2_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, vec0, vec1);
		return float3x2(vec0, vec1);
	}

	hlslpp_inline float3x3 mul(const float3x4& m1, const float4x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x4_4x3_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, m2.vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float3x4 mul(const float3x4& m1, const float4x4& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_3x4_4x4_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, m2.vec2, m2.vec3, vec0, vec1, vec2);
		return float3x4(vec0, vec1, vec2);
	}

	hlslpp_inline float4x1 mul(const float4x3& m1, const float3x1& m2)
	{
		return float4x1(_hlslpp_mul_4x3_3x1_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec));
	}

	hlslpp_inline float4x2 mul(const float4x3& m1, const float3x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_4x3_3x2_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, vec0, vec1);
		return float4x2(vec0, vec1);
	}

	hlslpp_inline float4x3 mul(const float4x3& m1, const float3x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_4x3_3x3_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, m2.vec2, vec0, vec1, vec2);
		return float4x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 mul(const float4x3& m1, const float3x4& m2)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_mul_4x3_3x4_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, m2.vec2, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	hlslpp_inline float4x1 mul(const float4x4& m1, const float4x1& m2)
	{
		return float4x1(_hlslpp_mul_4x4_4x1_ps(m1.vec0, m1.vec1, m1.vec2, m1.vec3, m2.vec));
	}

	hlslpp_inline float4x2 mul(const float4x4& m1, const float4x2& m2)
	{
		n128 vec0, vec1;
		_hlslpp_mul_4x4_4x2_ps(m1.vec0, m1.vec1, m1.vec2, m1.vec3, m2.vec0, m2.vec1, vec0, vec1);
		return float4x2(vec0, vec1);
	}

	hlslpp_inline float4x3 mul(const float4x4& m1, const float4x3& m2)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_mul_4x4_4x3_ps(m1.vec0, m1.vec1, m1.vec2, m1.vec3, m2.vec0, m2.vec1, m2.vec2, vec0, vec1, vec2);
		return float4x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 mul(const float4x4& m1, const float4x4& m2)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_mul_4x4_4x4_ps(m1.vec0, m1.vec1, m1.vec2, m1.vec3, m2.vec0, m2.vec1, m2.vec2, m2.vec3, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	float1x1 operator + (const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float1x2 operator + (const float1x2& m1, const float1x2& m2) { return float1x2(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float1x3 operator + (const float1x3& m1, const float1x3& m2) { return float1x3(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float1x4 operator + (const float1x4& m1, const float1x4& m2) { return float1x4(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float2x1 operator + (const float2x1& m1, const float2x1& m2) { return float2x1(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float3x1 operator + (const float3x1& m1, const float3x1& m2) { return float3x1(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float4x1 operator + (const float4x1& m1, const float4x1& m2) { return float4x1(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float2x2 operator + (const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_add_ps(m1.vec, m2.vec)); }
	float2x3 operator + (const float2x3& m1, const float2x3& m2) { return float2x3(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1)); }
	float3x2 operator + (const float3x2& m1, const float3x2& m2) { return float3x2(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1)); }
	float2x4 operator + (const float2x4& m1, const float2x4& m2) { return float2x4(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1)); }
	float4x2 operator + (const float4x2& m1, const float4x2& m2) { return float4x2(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1)); }
	float3x3 operator + (const float3x3& m1, const float3x3& m2) { return float3x3(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1), _hlslpp_add_ps(m1.vec2, m2.vec2)); }
	float3x4 operator + (const float3x4& m1, const float3x4& m2) { return float3x4(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1), _hlslpp_add_ps(m1.vec2, m2.vec2)); }
	float4x3 operator + (const float4x3& m1, const float4x3& m2) { return float4x3(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1), _hlslpp_add_ps(m1.vec2, m2.vec2)); }
	float4x4 operator + (const float4x4& m1, const float4x4& m2) { return float4x4(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1), _hlslpp_add_ps(m1.vec2, m2.vec2), _hlslpp_add_ps(m1.vec3, m2.vec3)); }

	float1x1 operator += (float1x1& m1, const float1x1& m2) { m1 = m1 + m2; return m1; }
	float1x2 operator += (float1x2& m1, const float1x2& m2) { m1 = m1 + m2; return m1; }
	float1x3 operator += (float1x3& m1, const float1x3& m2) { m1 = m1 + m2; return m1; }
	float1x4 operator += (float1x4& m1, const float1x4& m2) { m1 = m1 + m2; return m1; }
	float2x1 operator += (float2x1& m1, const float2x1& m2) { m1 = m1 + m2; return m1; }
	float3x1 operator += (float3x1& m1, const float3x1& m2) { m1 = m1 + m2; return m1; }
	float4x1 operator += (float4x1& m1, const float4x1& m2) { m1 = m1 + m2; return m1; }
	float2x2 operator += (float2x2& m1, const float2x2& m2) { m1 = m1 + m2; return m1; }
	float2x3 operator += (float2x3& m1, const float2x3& m2) { m1 = m1 + m2; return m1; }
	float2x4 operator += (float2x4& m1, const float2x4& m2) { m1 = m1 + m2; return m1; }
	float3x2 operator += (float3x2& m1, const float3x2& m2) { m1 = m1 + m2; return m1; }
	float4x2 operator += (float4x2& m1, const float4x2& m2) { m1 = m1 + m2; return m1; }
	float3x3 operator += (float3x3& m1, const float3x3& m2) { m1 = m1 + m2; return m1; }
	float3x4 operator += (float3x4& m1, const float3x4& m2) { m1 = m1 + m2; return m1; }
	float4x3 operator += (float4x3& m1, const float4x3& m2) { m1 = m1 + m2; return m1; }
	float4x4 operator += (float4x4& m1, const float4x4& m2) { m1 = m1 + m2; return m1; }

	float1x1 operator - (const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float1x2 operator - (const float1x2& m1, const float1x2& m2) { return float1x2(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float1x3 operator - (const float1x3& m1, const float1x3& m2) { return float1x3(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float1x4 operator - (const float1x4& m1, const float1x4& m2) { return float1x4(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float2x1 operator - (const float2x1& m1, const float2x1& m2) { return float2x1(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float3x1 operator - (const float3x1& m1, const float3x1& m2) { return float3x1(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float4x1 operator - (const float4x1& m1, const float4x1& m2) { return float4x1(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float2x2 operator - (const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	float2x3 operator - (const float2x3& m1, const float2x3& m2) { return float2x3(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1)); }
	float3x2 operator - (const float3x2& m1, const float3x2& m2) { return float3x2(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1)); }
	float2x4 operator - (const float2x4& m1, const float2x4& m2) { return float2x4(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1)); }
	float4x2 operator - (const float4x2& m1, const float4x2& m2) { return float4x2(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1)); }
	float3x3 operator - (const float3x3& m1, const float3x3& m2) { return float3x3(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1), _hlslpp_sub_ps(m1.vec2, m2.vec2)); }
	float3x4 operator - (const float3x4& m1, const float3x4& m2) { return float3x4(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1), _hlslpp_sub_ps(m1.vec2, m2.vec2)); }
	float4x3 operator - (const float4x3& m1, const float4x3& m2) { return float4x3(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1), _hlslpp_sub_ps(m1.vec2, m2.vec2)); }
	float4x4 operator - (const float4x4& m1, const float4x4& m2) { return float4x4(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1), _hlslpp_sub_ps(m1.vec2, m2.vec2), _hlslpp_sub_ps(m1.vec3, m2.vec3)); }

	float1x1 operator -= (float1x1& m1, const float1x1& m2) { m1 = m1 - m2; return m1; }
	float1x2 operator -= (float1x2& m1, const float1x2& m2) { m1 = m1 - m2; return m1; }
	float1x3 operator -= (float1x3& m1, const float1x3& m2) { m1 = m1 - m2; return m1; }
	float1x4 operator -= (float1x4& m1, const float1x4& m2) { m1 = m1 - m2; return m1; }
	float2x1 operator -= (float2x1& m1, const float2x1& m2) { m1 = m1 - m2; return m1; }
	float3x1 operator -= (float3x1& m1, const float3x1& m2) { m1 = m1 - m2; return m1; }
	float4x1 operator -= (float4x1& m1, const float4x1& m2) { m1 = m1 - m2; return m1; }
	float2x2 operator -= (float2x2& m1, const float2x2& m2) { m1 = m1 - m2; return m1; }
	float2x3 operator -= (float2x3& m1, const float2x3& m2) { m1 = m1 - m2; return m1; }
	float2x4 operator -= (float2x4& m1, const float2x4& m2) { m1 = m1 - m2; return m1; }
	float3x2 operator -= (float3x2& m1, const float3x2& m2) { m1 = m1 - m2; return m1; }
	float4x2 operator -= (float4x2& m1, const float4x2& m2) { m1 = m1 - m2; return m1; }
	float3x3 operator -= (float3x3& m1, const float3x3& m2) { m1 = m1 - m2; return m1; }
	float3x4 operator -= (float3x4& m1, const float3x4& m2) { m1 = m1 - m2; return m1; }
	float4x3 operator -= (float4x3& m1, const float4x3& m2) { m1 = m1 - m2; return m1; }
	float4x4 operator -= (float4x4& m1, const float4x4& m2) { m1 = m1 - m2; return m1; }

	float1x1 operator * (const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float1x2 operator * (const float1x2& m1, const float1x2& m2) { return float1x2(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float1x3 operator * (const float1x3& m1, const float1x3& m2) { return float1x3(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float1x4 operator * (const float1x4& m1, const float1x4& m2) { return float1x4(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float2x1 operator * (const float2x1& m1, const float2x1& m2) { return float2x1(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float3x1 operator * (const float3x1& m1, const float3x1& m2) { return float3x1(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float4x1 operator * (const float4x1& m1, const float4x1& m2) { return float4x1(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float2x2 operator * (const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	float2x3 operator * (const float2x3& m1, const float2x3& m2) { return float2x3(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1)); }
	float3x2 operator * (const float3x2& m1, const float3x2& m2) { return float3x2(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1)); }
	float2x4 operator * (const float2x4& m1, const float2x4& m2) { return float2x4(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1)); }
	float4x2 operator * (const float4x2& m1, const float4x2& m2) { return float4x2(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1)); }
	float3x3 operator * (const float3x3& m1, const float3x3& m2) { return float3x3(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1), _hlslpp_mul_ps(m1.vec2, m2.vec2)); }
	float3x4 operator * (const float3x4& m1, const float3x4& m2) { return float3x4(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1), _hlslpp_mul_ps(m1.vec2, m2.vec2)); }
	float4x3 operator * (const float4x3& m1, const float4x3& m2) { return float4x3(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1), _hlslpp_mul_ps(m1.vec2, m2.vec2)); }
	float4x4 operator * (const float4x4& m1, const float4x4& m2) { return float4x4(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1), _hlslpp_mul_ps(m1.vec2, m2.vec2), _hlslpp_mul_ps(m1.vec3, m2.vec3)); }

	float1x1 operator *= (float1x1& m1, const float1x1& m2) { m1 = m1 * m2; return m1; }
	float1x2 operator *= (float1x2& m1, const float1x2& m2) { m1 = m1 * m2; return m1; }
	float1x3 operator *= (float1x3& m1, const float1x3& m2) { m1 = m1 * m2; return m1; }
	float1x4 operator *= (float1x4& m1, const float1x4& m2) { m1 = m1 * m2; return m1; }
	float2x1 operator *= (float2x1& m1, const float2x1& m2) { m1 = m1 * m2; return m1; }
	float3x1 operator *= (float3x1& m1, const float3x1& m2) { m1 = m1 * m2; return m1; }
	float4x1 operator *= (float4x1& m1, const float4x1& m2) { m1 = m1 * m2; return m1; }
	float2x2 operator *= (float2x2& m1, const float2x2& m2) { m1 = m1 * m2; return m1; }
	float2x3 operator *= (float2x3& m1, const float2x3& m2) { m1 = m1 * m2; return m1; }
	float2x4 operator *= (float2x4& m1, const float2x4& m2) { m1 = m1 * m2; return m1; }
	float3x2 operator *= (float3x2& m1, const float3x2& m2) { m1 = m1 * m2; return m1; }
	float4x2 operator *= (float4x2& m1, const float4x2& m2) { m1 = m1 * m2; return m1; }
	float3x3 operator *= (float3x3& m1, const float3x3& m2) { m1 = m1 * m2; return m1; }
	float3x4 operator *= (float3x4& m1, const float3x4& m2) { m1 = m1 * m2; return m1; }
	float4x3 operator *= (float4x3& m1, const float4x3& m2) { m1 = m1 * m2; return m1; }
	float4x4 operator *= (float4x4& m1, const float4x4& m2) { m1 = m1 * m2; return m1; }

	float1x1 operator / (const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float1x2 operator / (const float1x2& m1, const float1x2& m2) { return float1x2(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float1x3 operator / (const float1x3& m1, const float1x3& m2) { return float1x3(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float1x4 operator / (const float1x4& m1, const float1x4& m2) { return float1x4(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float2x1 operator / (const float2x1& m1, const float2x1& m2) { return float2x1(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float3x1 operator / (const float3x1& m1, const float3x1& m2) { return float3x1(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float4x1 operator / (const float4x1& m1, const float4x1& m2) { return float4x1(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float2x2 operator / (const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_div_ps(m1.vec, m2.vec)); }
	float2x3 operator / (const float2x3& m1, const float2x3& m2) { return float2x3(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1)); }
	float3x2 operator / (const float3x2& m1, const float3x2& m2) { return float3x2(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1)); }
	float2x4 operator / (const float2x4& m1, const float2x4& m2) { return float2x4(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1)); }
	float4x2 operator / (const float4x2& m1, const float4x2& m2) { return float4x2(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1)); }
	float3x3 operator / (const float3x3& m1, const float3x3& m2) { return float3x3(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1), _hlslpp_div_ps(m1.vec2, m2.vec2)); }
	float3x4 operator / (const float3x4& m1, const float3x4& m2) { return float3x4(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1), _hlslpp_div_ps(m1.vec2, m2.vec2)); }
	float4x3 operator / (const float4x3& m1, const float4x3& m2) { return float4x3(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1), _hlslpp_div_ps(m1.vec2, m2.vec2)); }
	float4x4 operator / (const float4x4& m1, const float4x4& m2) { return float4x4(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1), _hlslpp_div_ps(m1.vec2, m2.vec2), _hlslpp_div_ps(m1.vec3, m2.vec3)); }

	float1x1 operator /= (float1x1& m1, const float1x1& m2) { m1 = m1 / m2; return m1; }
	float1x2 operator /= (float1x2& m1, const float1x2& m2) { m1 = m1 / m2; return m1; }
	float1x3 operator /= (float1x3& m1, const float1x3& m2) { m1 = m1 / m2; return m1; }
	float1x4 operator /= (float1x4& m1, const float1x4& m2) { m1 = m1 / m2; return m1; }
	float2x1 operator /= (float2x1& m1, const float2x1& m2) { m1 = m1 / m2; return m1; }
	float3x1 operator /= (float3x1& m1, const float3x1& m2) { m1 = m1 / m2; return m1; }
	float4x1 operator /= (float4x1& m1, const float4x1& m2) { m1 = m1 / m2; return m1; }
	float2x2 operator /= (float2x2& m1, const float2x2& m2) { m1 = m1 / m2; return m1; }
	float2x3 operator /= (float2x3& m1, const float2x3& m2) { m1 = m1 / m2; return m1; }
	float2x4 operator /= (float2x4& m1, const float2x4& m2) { m1 = m1 / m2; return m1; }
	float3x2 operator /= (float3x2& m1, const float3x2& m2) { m1 = m1 / m2; return m1; }
	float4x2 operator /= (float4x2& m1, const float4x2& m2) { m1 = m1 / m2; return m1; }
	float3x3 operator /= (float3x3& m1, const float3x3& m2) { m1 = m1 / m2; return m1; }
	float3x4 operator /= (float3x4& m1, const float3x4& m2) { m1 = m1 / m2; return m1; }
	float4x3 operator /= (float4x3& m1, const float4x3& m2) { m1 = m1 / m2; return m1; }
	float4x4 operator /= (float4x4& m1, const float4x4& m2) { m1 = m1 / m2; return m1; }

	// Scalar operators

	float1x1 operator + (const float1x1& m, const float1& f) { return float1x1(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x2 operator + (const float1x2& m, const float1& f) { return float1x2(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x3 operator + (const float1x3& m, const float1& f) { return float1x3(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x4 operator + (const float1x4& m, const float1& f) { return float1x4(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x1 operator + (const float2x1& m, const float1& f) { return float2x1(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float3x1 operator + (const float3x1& m, const float1& f) { return float3x1(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float4x1 operator + (const float4x1& m, const float1& f) { return float4x1(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x2 operator + (const float2x2& m, const float1& f) { return float2x2(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x3 operator + (const float2x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x3(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm)); }
	float3x2 operator + (const float3x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x2(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm)); }
	float2x4 operator + (const float2x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x4(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm)); }
	float4x2 operator + (const float4x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x2(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm)); }
	float3x3 operator + (const float3x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x3(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm), _hlslpp_add_ps(m.vec2, perm)); }
	float3x4 operator + (const float3x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x4(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm), _hlslpp_add_ps(m.vec2, perm)); }
	float4x3 operator + (const float4x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x3(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm), _hlslpp_add_ps(m.vec2, perm)); }
	float4x4 operator + (const float4x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x4(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm), _hlslpp_add_ps(m.vec2, perm), _hlslpp_add_ps(m.vec3, perm)); }

	float1x1 operator - (const float1x1& m, const float1& f) { return float1x1(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x2 operator - (const float1x2& m, const float1& f) { return float1x2(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x3 operator - (const float1x3& m, const float1& f) { return float1x3(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x4 operator - (const float1x4& m, const float1& f) { return float1x4(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x1 operator - (const float2x1& m, const float1& f) { return float2x1(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float3x1 operator - (const float3x1& m, const float1& f) { return float3x1(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float4x1 operator - (const float4x1& m, const float1& f) { return float4x1(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x2 operator - (const float2x2& m, const float1& f) { return float2x2(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x3 operator - (const float2x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x3(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm)); }
	float3x2 operator - (const float3x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x2(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm)); }
	float2x4 operator - (const float2x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x4(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm)); }
	float4x2 operator - (const float4x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x2(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm)); }
	float3x3 operator - (const float3x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x3(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm), _hlslpp_sub_ps(m.vec2, perm)); }
	float3x4 operator - (const float3x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x4(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm), _hlslpp_sub_ps(m.vec2, perm)); }
	float4x3 operator - (const float4x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x3(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm), _hlslpp_sub_ps(m.vec2, perm)); }
	float4x4 operator - (const float4x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x4(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm), _hlslpp_sub_ps(m.vec2, perm), _hlslpp_sub_ps(m.vec3, perm)); }

	float1x1 operator * (const float1x1& m, const float1& f) { return float1x1(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x2 operator * (const float1x2& m, const float1& f) { return float1x2(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x3 operator * (const float1x3& m, const float1& f) { return float1x3(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x4 operator * (const float1x4& m, const float1& f) { return float1x4(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x1 operator * (const float2x1& m, const float1& f) { return float2x1(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float3x1 operator * (const float3x1& m, const float1& f) { return float3x1(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float4x1 operator * (const float4x1& m, const float1& f) { return float4x1(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x2 operator * (const float2x2& m, const float1& f) { return float2x2(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }	
	float2x3 operator * (const float2x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x3(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm)); }
	float3x2 operator * (const float3x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x2(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm)); }
	float2x4 operator * (const float2x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x4(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm)); }
	float4x2 operator * (const float4x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x2(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm)); }
	float3x3 operator * (const float3x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x3(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm), _hlslpp_mul_ps(m.vec2, perm)); }
	float3x4 operator * (const float3x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x4(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm), _hlslpp_mul_ps(m.vec2, perm)); }
	float4x3 operator * (const float4x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x3(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm), _hlslpp_mul_ps(m.vec2, perm)); }
	float4x4 operator * (const float4x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x4(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm), _hlslpp_mul_ps(m.vec2, perm), _hlslpp_mul_ps(m.vec3, perm)); }

	float1x1 operator / (const float1x1& m, const float1& f) { return float1x1(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x2 operator / (const float1x2& m, const float1& f) { return float1x2(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x3 operator / (const float1x3& m, const float1& f) { return float1x3(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float1x4 operator / (const float1x4& m, const float1& f) { return float1x4(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x1 operator / (const float2x1& m, const float1& f) { return float2x1(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float3x1 operator / (const float3x1& m, const float1& f) { return float3x1(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float4x1 operator / (const float4x1& m, const float1& f) { return float4x1(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x2 operator / (const float2x2& m, const float1& f) { return float2x2(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	float2x3 operator / (const float2x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x3(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm)); }
	float3x2 operator / (const float3x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x2(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm)); }
	float2x4 operator / (const float2x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x4(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm)); }
	float4x2 operator / (const float4x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x2(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm)); }
	float3x3 operator / (const float3x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x3(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm), _hlslpp_div_ps(m.vec2, perm)); }
	float3x4 operator / (const float3x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x4(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm), _hlslpp_div_ps(m.vec2, perm)); }
	float4x3 operator / (const float4x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x3(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm), _hlslpp_div_ps(m.vec2, perm)); }
	float4x4 operator / (const float4x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x4(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm), _hlslpp_div_ps(m.vec2, perm), _hlslpp_div_ps(m.vec3, perm)); }

	hlslpp_inline float1 trace(const float2x2& m)
	{
		return float1(_hlslpp_trace_2x2_ps(m.vec));
	}

	hlslpp_inline float1 trace(const float3x3& m)
	{
		return float1(_hlslpp_trace_3x3_ps(m.vec0, m.vec1, m.vec2));
	}

	hlslpp_inline float1 trace(const float4x4& m)
	{
		return float1(_hlslpp_trace_4x4_ps(m.vec0, m.vec1, m.vec2, m.vec3));
	}

	hlslpp_inline float2x2 transpose(const float2x2& m)
	{
		return float2x2(_hlslpp_transpose_2x2_ps(m.vec));
	}

	hlslpp_inline float3x3 transpose(const float3x3& m)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_transpose_3x3_ps(m.vec0, m.vec1, m.vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 transpose(const float4x4& m)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_transpose_4x4_ps(m.vec0, m.vec1, m.vec2, m.vec3, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	// These transpose functions just copy the data because the 1xM, Nx1, 2xM, Nx2, 3xM and Nx3 matrices are always laid out as rows
	// even if they're meant to represent columns.

	float1x1 transpose(const float1x1& m) { return float1x1(m.vec); }

	float1x2 transpose(const float2x1& m) { return float1x2(m.vec); }
	float2x1 transpose(const float1x2& m) { return float2x1(m.vec); }

	float1x3 transpose(const float3x1& m) { return float1x3(m.vec); }
	float3x1 transpose(const float1x3& m) { return float3x1(m.vec); }

	float1x4 transpose(const float4x1& m) { return float1x4(m.vec); }
	float4x1 transpose(const float1x4& m) { return float4x1(m.vec); }

	float2x3 transpose(const float3x2& m) { return float2x3(m.vec0, m.vec1); }
	float3x2 transpose(const float2x3& m) { return float3x2(m.vec0, m.vec1); }

	float2x4 transpose(const float4x2& m) { return float2x4(m.vec0, m.vec1); }
	float4x2 transpose(const float2x4& m) { return float4x2(m.vec0, m.vec1); }

	float3x4 transpose(const float4x3& m) { return float3x4(m.vec0, m.vec1, m.vec2); }
	float4x3 transpose(const float3x4& m) { return float4x3(m.vec0, m.vec1, m.vec2); }

	hlslpp_inline float1 determinant(const float2x2& m)
	{
		return float1(_hlslpp_det_2x2_ps(m.vec));
	}

	hlslpp_inline float1 determinant(const float3x3& m)
	{
		return float1(_hlslpp_det_3x3_ps(m.vec0, m.vec1, m.vec2));
	}

	hlslpp_inline float1 determinant(const float4x4& m)
	{
		return float1(_hlslpp_det_4x4_ps(m.vec0, m.vec1, m.vec2, m.vec3));
	}

	hlslpp_inline float2x2 inverse(const float2x2& m)
	{
		return float2x2(_hlslpp_inv_2x2_ps(m.vec));
	}

	inline float3x3 inverse(const float3x3& m)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_inv_3x3_ps(m.vec0, m.vec1, m.vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	inline float4x4 inverse(const float4x4& m)
	{
		n128 vec0, vec1, vec2, vec3;
		_hlslpp_inv_4x4_ps(m.vec0, m.vec1, m.vec2, m.vec3, vec0, vec1, vec2, vec3);
		return float4x4(vec0, vec1, vec2, vec3);
	}

	hlslpp_inline void store(const float3x3& m, float* f)
	{
		_hlslpp_store3x3_ps(f, m.vec0, m.vec1, m.vec2);
	}

	hlslpp_inline void store(const float4x4& m, float* f)
	{
		_hlslpp_store4x4_ps(f, m.vec0, m.vec1, m.vec2, m.vec3);
	}
}