#pragma once

#include "hlsl++/common.h"

#include "hlsl++/matrix_float_type.h"

//--------------//
// Float Matrix //
//--------------//

hlslpp_module_export namespace hlslpp
{
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

	inline n128 _hlslpp_adjoint_2x2_ps(n128 m)
	{
		return _hlslpp_xor_ps(_hlslpp_perm_wyzx_ps(m), _hlslpp_set_ps(0.0f, -0.0f, -0.0f, 0.0f));
	}

	// | a b c |
	// | d e f |
	// | g h i |
	inline void _hlslpp_adjoint_3x3_ps(const n128& vec0, const n128& vec1, const n128& vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 bca = _hlslpp_perm_yzxw_ps(vec0);
		n128 cab = _hlslpp_perm_zxyw_ps(vec0);
		n128 efd = _hlslpp_perm_yzxw_ps(vec1);
		n128 fde = _hlslpp_perm_zxyw_ps(vec1);
		n128 hig = _hlslpp_perm_yzxw_ps(vec2);
		n128 igh = _hlslpp_perm_zxyw_ps(vec2);

		// Compute the adjoint matrix directly with 2x2 determinants
		n128 row_0 = _hlslpp_msub_ps(efd, igh, _hlslpp_mul_ps(fde, hig));
		n128 row_1 = _hlslpp_msub_ps(cab, hig, _hlslpp_mul_ps(bca, igh));
		n128 row_2 = _hlslpp_msub_ps(bca, fde, _hlslpp_mul_ps(cab, efd));

		// Transpose the matrix
		n128 shuf_0 = _hlslpp_shuf_xyxy_ps(row_0, row_1);
		n128 shuf_1 = _hlslpp_shuf_yzyz_ps(row_0, row_1);

		o_vec0 = _hlslpp_shuf_xzxw_ps(shuf_0, row_2);
		o_vec1 = _hlslpp_shuf_ywyw_ps(shuf_0, row_2);
		o_vec2 = _hlslpp_shuf_ywzw_ps(shuf_1, row_2);
	}

	// https://gist.github.com/runestubbe/466ffdde670e6a697affe4a899bcf3a3
	// | a b c d |
	// | e f g h |
	// | i j k l |
	// | m n o p |
	inline void _hlslpp_adjoint_4x4_ps(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
	{
		n128 efab = _hlslpp_movelh_ps(vec1, vec0);
		n128 ijmn = _hlslpp_movelh_ps(vec2, vec3);
		n128 ghcd = _hlslpp_movehl_ps(vec0, vec1);
		n128 klop = _hlslpp_movehl_ps(vec3, vec2);

		n128 fgbc = _hlslpp_shuf_yzyz_ps(vec1, vec0);
		n128 jkno = _hlslpp_shuf_yzyz_ps(vec2, vec3);
		n128 heda = _hlslpp_shuf_wxwx_ps(vec1, vec0);
		n128 lipm = _hlslpp_shuf_wxwx_ps(vec2, vec3);

		n128 miea = _hlslpp_shuf_zxxz_ps(ijmn, efab);
		n128 njfb = _hlslpp_shuf_wyyw_ps(ijmn, efab);
		n128 okgc = _hlslpp_shuf_zxxz_ps(klop, ghcd);
		n128 plhd = _hlslpp_shuf_wyyw_ps(klop, ghcd);

		n128 inner12_23 = _hlslpp_sub_ps(_hlslpp_mul_ps(fgbc, klop), _hlslpp_mul_ps(jkno, ghcd));
		n128 inner02_13 = _hlslpp_sub_ps(_hlslpp_mul_ps(efab, klop), _hlslpp_mul_ps(ijmn, ghcd));
		n128 inner30_01 = _hlslpp_sub_ps(_hlslpp_mul_ps(lipm, efab), _hlslpp_mul_ps(heda, ijmn));

		n128 inner12 = _hlslpp_shuf_xzzx_ps(inner12_23, inner12_23);
		n128 inner23 = _hlslpp_shuf_ywwy_ps(inner12_23, inner12_23);

		n128 inner02 = _hlslpp_shuf_xzzx_ps(inner02_13, inner02_13);
		n128 inner13 = _hlslpp_shuf_ywwy_ps(inner02_13, inner02_13);
		n128 inner30 = _hlslpp_shuf_xzzx_ps(inner30_01, inner30_01);
		n128 inner01 = _hlslpp_shuf_ywwy_ps(inner30_01, inner30_01);

		n128 minors0 = _hlslpp_add_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(plhd, inner12), _hlslpp_mul_ps(okgc, inner13)), _hlslpp_mul_ps(njfb, inner23));
		n128 minors1 = _hlslpp_sub_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(okgc, inner30), _hlslpp_mul_ps(miea, inner23)), _hlslpp_mul_ps(plhd, inner02));
		n128 minors2 = _hlslpp_sub_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(miea, inner13), _hlslpp_mul_ps(njfb, inner30)), _hlslpp_mul_ps(plhd, inner01));
		n128 minors3 = _hlslpp_add_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(njfb, inner02), _hlslpp_mul_ps(miea, inner12)), _hlslpp_mul_ps(okgc, inner01));

		o_vec0 = _hlslpp_xor_ps(minors0, _hlslpp_set_ps(0.0f, 0.0f, -0.0f, -0.0f));
		o_vec1 = _hlslpp_xor_ps(minors1, _hlslpp_set_ps(0.0f, 0.0f, -0.0f, -0.0f));
		o_vec2 = _hlslpp_xor_ps(minors2, _hlslpp_set_ps(0.0f, 0.0f, -0.0f, -0.0f));
		o_vec3 = _hlslpp_xor_ps(minors3, _hlslpp_set_ps(0.0f, 0.0f, -0.0f, -0.0f));
	}

	inline n128 _hlslpp_inv_2x2_ps(n128 m)
	{
		n128 det = _hlslpp_perm_xxxx_ps(_hlslpp_det_2x2_ps(m));
		n128 shuf = _hlslpp_mul_ps(_hlslpp_perm_wyzx_ps(m), _hlslpp_set_ps(1.0f, -1.0f, -1.0f, 1.0f));
		return _hlslpp_div_ps(shuf, det);
	}

	inline void _hlslpp_inv_3x3_ps(const n128& vec0, const n128& vec1, const n128& vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 bca = _hlslpp_perm_yzxw_ps(vec0);
		n128 cab = _hlslpp_perm_zxyw_ps(vec0);
		n128 efd = _hlslpp_perm_yzxw_ps(vec1);
		n128 fde = _hlslpp_perm_zxyw_ps(vec1);
		n128 hig = _hlslpp_perm_yzxw_ps(vec2);
		n128 igh = _hlslpp_perm_zxyw_ps(vec2);

		// Compute the adjoint matrix directly with 2x2 determinants
		n128 row_0 = _hlslpp_msub_ps(efd, igh, _hlslpp_mul_ps(fde, hig));
		n128 row_1 = _hlslpp_msub_ps(cab, hig, _hlslpp_mul_ps(bca, igh));
		n128 row_2 = _hlslpp_msub_ps(bca, fde, _hlslpp_mul_ps(cab, efd));

		// Transpose the matrix
		n128 shuf_0 = _hlslpp_shuf_xyxy_ps(row_0, row_1);
		n128 shuf_1 = _hlslpp_shuf_yzyz_ps(row_0, row_1);

		n128 transp_row_0 = _hlslpp_shuf_xzxw_ps(shuf_0, row_2);
		n128 transp_row_1 = _hlslpp_shuf_ywyw_ps(shuf_0, row_2);
		n128 transp_row_2 = _hlslpp_shuf_ywzw_ps(shuf_1, row_2);

		// Compute the determinant and divide all results by it
		n128 prod = _hlslpp_mul_ps(efd, vec2);
		n128 sub = _hlslpp_msub_ps(vec1, hig, prod);

		n128 det = _hlslpp_perm_xxxx_ps(_hlslpp_dot3_ps(vec0, _hlslpp_perm_yzxw_ps(sub)));
		n128 invDet = _hlslpp_div_ps(f4_1, det);

		o_vec0 = _hlslpp_mul_ps(transp_row_0, invDet);
		o_vec1 = _hlslpp_mul_ps(transp_row_1, invDet);
		o_vec2 = _hlslpp_mul_ps(transp_row_2, invDet);
	}

	// https://gist.github.com/runestubbe/466ffdde670e6a697affe4a899bcf3a3
	inline void _hlslpp_inv_4x4_ps(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3, n128& o_vec0, n128& o_vec1, n128& o_vec2, n128& o_vec3)
	{
		n128 efab = _hlslpp_movelh_ps(vec1, vec0);
		n128 ijmn = _hlslpp_movelh_ps(vec2, vec3);
		n128 ghcd = _hlslpp_movehl_ps(vec0, vec1);
		n128 klop = _hlslpp_movehl_ps(vec3, vec2);

		n128 fgbc = _hlslpp_shuf_yzyz_ps(vec1, vec0);
		n128 jkno = _hlslpp_shuf_yzyz_ps(vec2, vec3);
		n128 heda = _hlslpp_shuf_wxwx_ps(vec1, vec0);
		n128 lipm = _hlslpp_shuf_wxwx_ps(vec2, vec3);

		n128 miea = _hlslpp_shuf_zxxz_ps(ijmn, efab);
		n128 njfb = _hlslpp_shuf_wyyw_ps(ijmn, efab);
		n128 okgc = _hlslpp_shuf_zxxz_ps(klop, ghcd);
		n128 plhd = _hlslpp_shuf_wyyw_ps(klop, ghcd);
		n128 aeim = _hlslpp_shuf_zxxz_ps(efab, ijmn);

		n128 inner12_23 = _hlslpp_sub_ps(_hlslpp_mul_ps(fgbc, klop), _hlslpp_mul_ps(jkno, ghcd));
		n128 inner02_13 = _hlslpp_sub_ps(_hlslpp_mul_ps(efab, klop), _hlslpp_mul_ps(ijmn, ghcd));
		n128 inner30_01 = _hlslpp_sub_ps(_hlslpp_mul_ps(lipm, efab), _hlslpp_mul_ps(heda, ijmn));

		n128 inner12 = _hlslpp_shuf_xzzx_ps(inner12_23, inner12_23);
		n128 inner23 = _hlslpp_shuf_ywwy_ps(inner12_23, inner12_23);

		n128 inner02 = _hlslpp_shuf_xzzx_ps(inner02_13, inner02_13);
		n128 inner13 = _hlslpp_shuf_ywwy_ps(inner02_13, inner02_13);
		n128 inner30 = _hlslpp_shuf_xzzx_ps(inner30_01, inner30_01);
		n128 inner01 = _hlslpp_shuf_ywwy_ps(inner30_01, inner30_01);

		n128 minors0 = _hlslpp_add_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(plhd, inner12), _hlslpp_mul_ps(okgc, inner13)), _hlslpp_mul_ps(njfb, inner23));
		n128 minors1 = _hlslpp_sub_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(okgc, inner30), _hlslpp_mul_ps(miea, inner23)), _hlslpp_mul_ps(plhd, inner02));
		n128 minors2 = _hlslpp_sub_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(miea, inner13), _hlslpp_mul_ps(njfb, inner30)), _hlslpp_mul_ps(plhd, inner01));
		n128 minors3 = _hlslpp_add_ps(_hlslpp_sub_ps(_hlslpp_mul_ps(njfb, inner02), _hlslpp_mul_ps(miea, inner12)), _hlslpp_mul_ps(okgc, inner01));

		n128 denom = _hlslpp_mul_ps(aeim, minors0);
		denom = _hlslpp_add_ps(denom, _hlslpp_shuf_yxwz_ps(denom, denom));	// x+y		x+y			z+w			z+w
		denom = _hlslpp_sub_ps(denom, _hlslpp_shuf_zzxx_ps(denom, denom));	// x+y-z-w  x+y-z-w		z+w-x-y		z+w-x-y
		n128 rcp_denom_ppnn = _hlslpp_div_ps(f4_1, denom);

		o_vec0 = _hlslpp_mul_ps(minors0, rcp_denom_ppnn);
		o_vec1 = _hlslpp_mul_ps(minors1, rcp_denom_ppnn);
		o_vec2 = _hlslpp_mul_ps(minors2, rcp_denom_ppnn);
		o_vec3 = _hlslpp_mul_ps(minors3, rcp_denom_ppnn);
	}

	// Puts trace in first element
	hlslpp_inline n128 _hlslpp_trace_2x2_ps(const n128 m)
	{
		return _hlslpp_add_ps(m, _hlslpp_perm_wwww_ps(m));
	}

	// Puts trace in first element
	hlslpp_inline n128 _hlslpp_trace_3x3_ps(const n128 vec0, const n128 vec1, const n128 vec2)
	{
		return _hlslpp_add_ps(_hlslpp_add_ps(vec0, _hlslpp_perm_yyyy_ps(vec1)), _hlslpp_perm_zzzz_ps(vec2));
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
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_shuf_xxxx_ps(dpy, dpz), HLSLPP_BLEND_MASK(1, 0, 0, 0));
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
		o_vec0 = _hlslpp_blend_ps(dpx0, _hlslpp_shuf_xxxx_ps(dpy0, dpz0), HLSLPP_BLEND_MASK(1, 0, 0, 0));

		n128 dpx1 = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpy1 = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1_vec1, m2_vec2);
		o_vec1 = _hlslpp_blend_ps(dpx1, _hlslpp_shuf_xxxx_ps(dpy1, dpz1), HLSLPP_BLEND_MASK(1, 0, 0, 0));
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

	inline void _hlslpp_mul_3x3_3x4_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		// First row
		n128 mul1x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec0), m2_vec0);
		n128 mad1y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec0), m2_vec1, mul1x);
		o_vec0     = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec0), m2_vec2, mad1y);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec1), m2_vec0);
		n128 mad2y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec1), m2_vec1, mul2x);
		o_vec1     = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec1), m2_vec2, mad2y);

		// Third row
		n128 mul3x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1_vec2), m2_vec0);
		n128 mad3y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1_vec2), m2_vec1, mul3x);
		o_vec2     = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1_vec2), m2_vec2, mad3y);
	}

	inline n128 _hlslpp_mul_3x4_4x1_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec)
	{
		n128 dpx = _hlslpp_dot4_ps(m1_vec0, m2_vec);
		n128 dpy = _hlslpp_dot4_ps(m1_vec1, m2_vec);
		n128 dpz = _hlslpp_dot4_ps(m1_vec2, m2_vec);
		n128 result = _hlslpp_blend_ps(dpx, _hlslpp_shuf_xxxx_ps(dpy, dpz), HLSLPP_BLEND_MASK(1, 0, 0, 0));
		return result;
	}

	inline void _hlslpp_mul_3x4_4x2_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, n128& o_vec0, n128& o_vec1)
	{
		n128 dpx0 = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpz0 = _hlslpp_dot4_ps(m1_vec2, m2_vec0);
		o_vec0 = _hlslpp_blend_ps(dpx0, _hlslpp_shuf_xxxx_ps(dpy0, dpz0), HLSLPP_BLEND_MASK(1, 0, 0, 0));

		n128 dpx1 = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpy1 = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1_vec2, m2_vec1);
		o_vec1 = _hlslpp_blend_ps(dpx1, _hlslpp_shuf_xxxx_ps(dpy1, dpz1), HLSLPP_BLEND_MASK(1, 0, 0, 0));
	}

	inline void _hlslpp_mul_3x4_4x3_ps(const n128& m1_vec0, const n128& m1_vec1, const n128& m1_vec2, const n128& m2_vec0, const n128& m2_vec1, const n128& m2_vec2, n128& o_vec0, n128& o_vec1, n128& o_vec2)
	{
		n128 dpx0 = _hlslpp_dot4_ps(m1_vec0, m2_vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1_vec0, m2_vec1);
		n128 dpz0 = _hlslpp_dot4_ps(m1_vec0, m2_vec2);
		o_vec0 = _hlslpp_blend_ps(dpx0, _hlslpp_shuf_xxxx_ps(dpy0, dpz0), HLSLPP_BLEND_MASK(1, 0, 0, 0));

		n128 dpx1 = _hlslpp_dot4_ps(m1_vec1, m2_vec0);
		n128 dpy1 = _hlslpp_dot4_ps(m1_vec1, m2_vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1_vec1, m2_vec2);
		o_vec1 = _hlslpp_blend_ps(dpx1, _hlslpp_shuf_xxxx_ps(dpy1, dpz1), HLSLPP_BLEND_MASK(1, 0, 0, 0));

		n128 dpx2 = _hlslpp_dot4_ps(m1_vec2, m2_vec0);
		n128 dpy2 = _hlslpp_dot4_ps(m1_vec2, m2_vec1);
		n128 dpz2 = _hlslpp_dot4_ps(m1_vec2, m2_vec2);
		o_vec2 = _hlslpp_blend_ps(dpx2, _hlslpp_shuf_xxxx_ps(dpy2, dpz2), HLSLPP_BLEND_MASK(1, 0, 0, 0));
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
#if defined(HLSLPP_SIMD_REGISTER_512)

		n512 m1_m1_m1_m1 = _hlslpp512_set128_ps(m1.vec, m1.vec, m1.vec, m1.vec);
		n512 m2_m2_m2_m2 = _hlslpp512_set128_ps(m2.vec, m2.vec, m2.vec, m2.vec);

		return float4x4(_hlslpp512_mul_ps(_hlslpp512_perm_ps(m1_m1_m1_m1, 0, 0, 0, 0, 5, 5, 5, 5, 10, 10, 10, 10, 15, 15, 15, 15), m2_m2_m2_m2));

#elif defined(HLSLPP_SIMD_REGISTER_256)

		n256 m1_m1 = _hlslpp256_set128_ps(m1.vec, m1.vec);
		n256 m2_m2 = _hlslpp256_set128_ps(m2.vec, m2.vec);

		return float4x4
		(
			_hlslpp256_mul_ps(_hlslpp256_perm_xxxx_bbbb_ps(m1_m1), m2_m2),
			_hlslpp256_mul_ps(_hlslpp256_perm_zzzz_dddd_ps(m1_m1), m2_m2)
		);

#else

		return float4x4
		(
			_hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec), m2.vec), 
			_hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1.vec), m2.vec), 
			_hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1.vec), m2.vec), 
			_hlslpp_mul_ps(_hlslpp_perm_wwww_ps(m1.vec), m2.vec)
		);
		
#endif
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

	hlslpp_inline float1x4 mul(const float1x4& m1, const float4x4& m2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)

		n512 m1_m1_m1_m1 = _hlslpp512_set128_ps(m1.vec, m1.vec, m1.vec, m1.vec);
		n512 mul0 = _hlslpp512_mul_ps(m2.vec, _hlslpp512_perm_ps(m1_m1_m1_m1, 0, 0, 0, 0, 5, 5, 5, 5, 10, 10, 10, 10, 15, 15, 15, 15));
		n256 add0 = _hlslpp256_add_ps(_hlslpp512_low_ps(mul0), _hlslpp512_high_ps(mul0));
		return float1x4(_hlslpp_add_ps(_hlslpp256_low_ps(add0), _hlslpp256_high_ps(add0)));

#elif defined(HLSLPP_SIMD_REGISTER_256)

		n256 m1_m1 = _hlslpp256_set128_ps(m1.vec, m1.vec);
		n256 mul0 = _hlslpp256_mul_ps(m2.vec0, _hlslpp256_perm_xxxx_bbbb_ps(m1_m1));
		n256 mul1 = _hlslpp256_madd_ps(m2.vec1, _hlslpp256_perm_zzzz_dddd_ps(m1_m1), mul0);
		return float1x4(_hlslpp_add_ps(_hlslpp256_low_ps(mul1), _hlslpp256_high_ps(mul1)));

#else

		n128 mul0 = _hlslpp_mul_ps(m2.vec0, _hlslpp_perm_xxxx_ps(m1.vec));
		n128 mul1 = _hlslpp_madd_ps(m2.vec1, _hlslpp_perm_yyyy_ps(m1.vec), mul0);
		n128 mul2 = _hlslpp_madd_ps(m2.vec2, _hlslpp_perm_zzzz_ps(m1.vec), mul1);
		return float1x4(_hlslpp_madd_ps(m2.vec3, _hlslpp_perm_wwww_ps(m1.vec), mul2));

#endif
	}

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
#if defined(HLSLPP_SIMD_REGISTER_512)

		n512 m1_vec0 = _hlslpp512_set128_ps(m1.vec0, m1.vec0, m1.vec0, m1.vec0);
		n512 m2_vec0 = _hlslpp512_set128_ps(m2.vec0, m2.vec0, m2.vec0, m2.vec0);
		n512 m1_vec1 = _hlslpp512_set128_ps(m1.vec1, m1.vec1, m1.vec1, m1.vec1);
		n512 m2_vec1 = _hlslpp512_set128_ps(m2.vec1, m2.vec1, m2.vec1, m2.vec1);

		n512 mul0 = _hlslpp512_mul_ps(_hlslpp512_perm_ps(m1_vec0, 0, 0, 0, 0, 5, 5, 5, 5, 10, 10, 10, 10, 15, 15, 15, 15), m2_vec0);
		n512 mad0 = _hlslpp512_madd_ps(_hlslpp512_perm_ps(m1_vec1, 0, 0, 0, 0, 5, 5, 5, 5, 10, 10, 10, 10, 15, 15, 15, 15), m2_vec1, mul0);

		return float4x4(mad0);

#elif defined(HLSLPP_SIMD_REGISTER_256)

		n256 m2_vec0 = _hlslpp256_set128_ps(m2.vec0, m2.vec0);
		n256 m2_vec1 = _hlslpp256_set128_ps(m2.vec1, m2.vec1);
		n256 m1_vec0 = _hlslpp256_set128_ps(m1.vec0, m1.vec0);
		n256 m1_vec1 = _hlslpp256_set128_ps(m1.vec1, m1.vec1);

		n256 mul0 = _hlslpp256_mul_ps(_hlslpp256_perm_xxxx_bbbb_ps(m1_vec0), m2_vec0);
		n256 mul1 = _hlslpp256_mul_ps(_hlslpp256_perm_zzzz_dddd_ps(m1_vec0), m2_vec0);

		return float4x4
		(
			_hlslpp256_madd_ps(_hlslpp256_perm_xxxx_bbbb_ps(m1_vec1), m2_vec1, mul0),
			_hlslpp256_madd_ps(_hlslpp256_perm_zzzz_dddd_ps(m1_vec1), m2_vec1, mul1)
		);

#else
		n128 mul0 = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec0), m2.vec0);
		n128 mul1 = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1.vec0), m2.vec0);
		n128 mul2 = _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1.vec0), m2.vec0);
		n128 mul3 = _hlslpp_mul_ps(_hlslpp_perm_wwww_ps(m1.vec0), m2.vec0);

		return float4x4
		(
			_hlslpp_madd_ps(_hlslpp_perm_xxxx_ps(m1.vec1), m2.vec1, mul0), 
			_hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1.vec1), m2.vec1, mul1),
			_hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1.vec1), m2.vec1, mul2),
			_hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1.vec1), m2.vec1, mul3)
		);
#endif
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
#if defined(HLSLPP_SIMD_REGISTER_512)

		n512 m1_vec0 = _hlslpp512_set128_ps(m1.vec0, m1.vec0, m1.vec0, m1.vec0);
		n512 m1_vec1 = _hlslpp512_set128_ps(m1.vec1, m1.vec1, m1.vec1, m1.vec1);

		// Transpose
		n512 m2_vec_t = _hlslpp512_perm_ps(m2.vec, 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15);

		// Multiply
		n512 mul0 = _hlslpp512_mul_ps(m1_vec0, m2_vec_t);
		n512 mul1 = _hlslpp512_mul_ps(m1_vec1, m2_vec_t);

		// Transpose back to efficiently add
		n512 mul0_t = _hlslpp512_perm_ps(mul0, 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15);
		n512 mul1_t = _hlslpp512_perm_ps(mul1, 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15);

		n256 mul0_t_low = _hlslpp512_low_ps(mul0_t);
		n256 mul0_t_high = _hlslpp512_high_ps(mul0_t);

		n256 hadd0_0 = _hlslpp256_add_ps(mul0_t_low, mul0_t_high);
		n128 hadd0_1 = _hlslpp_add_ps(_hlslpp256_low_ps(hadd0_0), _hlslpp256_high_ps(hadd0_0));

		n256 mul1_t_low = _hlslpp512_low_ps(mul1_t);
		n256 mul1_t_high = _hlslpp512_high_ps(mul1_t);

		n256 hadd1_0 = _hlslpp256_add_ps(mul1_t_low, mul1_t_high);
		n128 hadd1_1 = _hlslpp_add_ps(_hlslpp256_low_ps(hadd1_0), _hlslpp256_high_ps(hadd1_0));

		return float2x4(hadd0_1, hadd1_1);

#elif defined(HLSLPP_SIMD_REGISTER_256)

		n256 m1_vec0 = _hlslpp256_set128_ps(m1.vec0, m1.vec0);
		n256 m1_vec1 = _hlslpp256_set128_ps(m1.vec1, m1.vec1);

		// First row
		n256 m1_vec0_xxxx_yyyy = _hlslpp256_perm_xxxx_bbbb_ps(m1_vec0);
		n256 m1_vec0_zzzz_wwww = _hlslpp256_perm_zzzz_dddd_ps(m1_vec0);
		n256 mul0 = _hlslpp256_mul_ps(m1_vec0_xxxx_yyyy, m2.vec0);
		n256 mul1 = _hlslpp256_madd_ps(m1_vec0_zzzz_wwww, m2.vec1, mul0);

		// Second row
		n256 m1_vec1_xxxx_yyyy = _hlslpp256_perm_xxxx_bbbb_ps(m1_vec1);
		n256 m1_vec1_zzzz_wwww = _hlslpp256_perm_zzzz_dddd_ps(m1_vec1);
		n256 mul2 = _hlslpp256_mul_ps(m1_vec1_xxxx_yyyy, m2.vec0);
		n256 mul3 = _hlslpp256_madd_ps(m1_vec1_zzzz_wwww, m2.vec1, mul2);

		return float2x4
		(
			_hlslpp_add_ps(_hlslpp256_low_ps(mul1), _hlslpp256_high_ps(mul1)),
			_hlslpp_add_ps(_hlslpp256_low_ps(mul3), _hlslpp256_high_ps(mul3))
		);

#else

		// First row
		n128 mul0x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec0), m2.vec0);
		n128 mad0y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1.vec0), m2.vec1, mul0x);
		n128 mad0z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1.vec0), m2.vec2, mad0y);
		n128 mad0w = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1.vec0), m2.vec3, mad0z);

		// Second row
		n128 mul1x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec1), m2.vec0);
		n128 mad1y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1.vec1), m2.vec1, mul1x);
		n128 mad1z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1.vec1), m2.vec2, mad1y);
		n128 mad1w = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1.vec1), m2.vec3, mad1z);

		return float2x4(mad0w, mad1w);

#endif
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
		_hlslpp_mul_3x3_3x4_ps(m1.vec0, m1.vec1, m1.vec2, m2.vec0, m2.vec1, m2.vec2, vec0, vec1, vec2);
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

	inline float3x4 mul(const float3x4& m1, const float4x4& m2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)

		n128 m2_vec0 = _hlslpp512_vec0_ps(m2.vec);
		n128 m2_vec1 = _hlslpp512_vec1_ps(m2.vec);
		n128 m2_vec2 = _hlslpp512_vec2_ps(m2.vec);
		n128 m2_vec3 = _hlslpp512_vec3_ps(m2.vec);

#elif defined(HLSLPP_SIMD_REGISTER_256)

		n128 m2_vec0 = _hlslpp256_low_ps(m2.vec0);
		n128 m2_vec1 = _hlslpp256_high_ps(m2.vec0);
		n128 m2_vec2 = _hlslpp256_low_ps(m2.vec1);
		n128 m2_vec3 = _hlslpp256_high_ps(m2.vec1);

#else

		n128 m2_vec0 = m2.vec0;
		n128 m2_vec1 = m2.vec1;
		n128 m2_vec2 = m2.vec2;
		n128 m2_vec3 = m2.vec3;

#endif

		// First row
		n128 mul1x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec0), m2_vec0);
		n128 mad1y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1.vec0), m2_vec1, mul1x);
		n128 mad1z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1.vec0), m2_vec2, mad1y);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec1), m2_vec0);
		n128 mad2y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1.vec1), m2_vec1, mul2x);
		n128 mad2z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1.vec1), m2_vec2, mad2y);

		// Third row
		n128 mul3x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec2), m2_vec0);
		n128 mad3y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1.vec2), m2_vec1, mul3x);
		n128 mad3z = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1.vec2), m2_vec2, mad3y);

		return float3x4
		(
			_hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1.vec0), m2_vec3, mad1z),
			_hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1.vec1), m2_vec3, mad2z),
			_hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1.vec2), m2_vec3, mad3z)
		);
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

	inline float4x4 mul(const float4x3& m1, const float3x4& m2)
	{
		// First row
		n128 mul0x = _hlslpp_mul_ps(_hlslpp_perm_xxxx_ps(m1.vec0), m2.vec0);
		n128 mad0y = _hlslpp_madd_ps(_hlslpp_perm_xxxx_ps(m1.vec1), m2.vec1, mul0x);

		// Second row
		n128 mul1x = _hlslpp_mul_ps(_hlslpp_perm_yyyy_ps(m1.vec0), m2.vec0);
		n128 mad1y = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1.vec1), m2.vec1, mul1x);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(_hlslpp_perm_zzzz_ps(m1.vec0), m2.vec0);
		n128 mad2y = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1.vec1), m2.vec1, mul2x);

		// Second row
		n128 mul3x = _hlslpp_mul_ps(_hlslpp_perm_wwww_ps(m1.vec0), m2.vec0);
		n128 mad3y = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1.vec1), m2.vec1, mul3x);

		n128 row0 = _hlslpp_madd_ps(_hlslpp_perm_xxxx_ps(m1.vec2), m2.vec2, mad0y);
		n128 row1 = _hlslpp_madd_ps(_hlslpp_perm_yyyy_ps(m1.vec2), m2.vec2, mad1y);
		n128 row2 = _hlslpp_madd_ps(_hlslpp_perm_zzzz_ps(m1.vec2), m2.vec2, mad2y);
		n128 row3 = _hlslpp_madd_ps(_hlslpp_perm_wwww_ps(m1.vec2), m2.vec2, mad3y);

#if defined(HLSLPP_SIMD_REGISTER_512)

		return float4x4(_hlslpp512_set128_ps(row0, row1, row2, row3));

#elif defined(HLSLPP_SIMD_REGISTER_256)

		return float4x4(_hlslpp256_set128_ps(row0, row1), _hlslpp256_set128_ps(row2, row3));

#else

		return float4x4(row0, row1, row2, row3);

#endif
	}

	inline float4x1 mul(const float4x4& m1, const float4x1& m2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)

		n256 m2_vec = _hlslpp256_set128_ps(m2.vec, m2.vec);

		n256 dot_row12 = _hlslpp256_dot4_ps(_hlslpp512_low_ps(m1.vec), m2_vec);
		n256 dot_row23 = _hlslpp256_dot4_ps(_hlslpp512_high_ps(m1.vec), m2_vec);

		n128 dpx = _hlslpp256_low_ps(dot_row12);
		n128 dpy = _hlslpp256_high_ps(dot_row12);
		n128 dpz = _hlslpp256_low_ps(dot_row23);
		n128 dpw = _hlslpp256_high_ps(dot_row23);

#elif defined(HLSLPP_SIMD_REGISTER_256)

		n256 m2_vec = _hlslpp256_set128_ps(m2.vec, m2.vec);

		n256 dot_row12 = _hlslpp256_dot4_ps(m1.vec0, m2_vec);
		n256 dot_row23 = _hlslpp256_dot4_ps(m1.vec1, m2_vec);

		n128 dpx = _hlslpp256_low_ps(dot_row12);
		n128 dpy = _hlslpp256_high_ps(dot_row12);
		n128 dpz = _hlslpp256_low_ps(dot_row23);
		n128 dpw = _hlslpp256_high_ps(dot_row23);

#else

		n128 dpx = _hlslpp_dot4_ps(m1.vec0, m2.vec);
		n128 dpy = _hlslpp_dot4_ps(m1.vec1, m2.vec);
		n128 dpz = _hlslpp_dot4_ps(m1.vec2, m2.vec);
		n128 dpw = _hlslpp_dot4_ps(m1.vec3, m2.vec);

#endif

		return float4x1(_hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx, dpz), _hlslpp_shuf_xxxx_ps(dpy, dpw), HLSLPP_BLEND_MASK(1, 0, 1, 0)));
	}

	inline float4x2 mul(const float4x4& m1, const float4x2& m2)
	{
#if defined(HLSLPP_SIMD_REGISTER_256)

		#if defined(HLSLPP_SIMD_REGISTER_512)
		n256 m1_vec0 = _hlslpp512_low_ps(m1.vec);
		n256 m1_vec1 = _hlslpp512_high_ps(m1.vec);
		#else
		n256 m1_vec0 = m1.vec0;
		n256 m1_vec1 = m1.vec1;
		#endif

		n256 m2_vec0 = _hlslpp256_set128_ps(m2.vec0, m2.vec0);
		n256 dot_row0_12 = _hlslpp256_dot4_ps(m1_vec0, m2_vec0);
		n256 dot_row0_23 = _hlslpp256_dot4_ps(m1_vec1, m2_vec0);

		n256 m2_vec1 = _hlslpp256_set128_ps(m2.vec1, m2.vec1);
		n256 dot_row1_12 = _hlslpp256_dot4_ps(m1_vec0, m2_vec1);
		n256 dot_row1_23 = _hlslpp256_dot4_ps(m1_vec1, m2_vec1);

		n128 dpx0 = _hlslpp256_low_ps(dot_row0_12);
		n128 dpy0 = _hlslpp256_high_ps(dot_row0_12);
		n128 dpz0 = _hlslpp256_low_ps(dot_row0_23);
		n128 dpw0 = _hlslpp256_high_ps(dot_row0_23);

		n128 dpx1 = _hlslpp256_low_ps(dot_row1_12);
		n128 dpy1 = _hlslpp256_high_ps(dot_row1_12);
		n128 dpz1 = _hlslpp256_low_ps(dot_row1_23);
		n128 dpw1 = _hlslpp256_high_ps(dot_row1_23);

#else

		n128 dpx0 = _hlslpp_dot4_ps(m1.vec0, m2.vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1.vec1, m2.vec0);
		n128 dpz0 = _hlslpp_dot4_ps(m1.vec2, m2.vec0);
		n128 dpw0 = _hlslpp_dot4_ps(m1.vec3, m2.vec0);

		n128 dpx1 = _hlslpp_dot4_ps(m1.vec0, m2.vec1);
		n128 dpy1 = _hlslpp_dot4_ps(m1.vec1, m2.vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1.vec2, m2.vec1);
		n128 dpw1 = _hlslpp_dot4_ps(m1.vec3, m2.vec1);

#endif

		return float4x2
		(
			_hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx0, dpz0), _hlslpp_shuf_xxxx_ps(dpy0, dpw0), HLSLPP_BLEND_MASK(1, 0, 1, 0)),
			_hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx1, dpz1), _hlslpp_shuf_xxxx_ps(dpy1, dpw1), HLSLPP_BLEND_MASK(1, 0, 1, 0))
		);
	}

	inline float4x3 mul(const float4x4& m1, const float4x3& m2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		
		n512 m1_xxxx = _hlslpp512_perm_ps(m1.vec, 0, 4,  8, 12, 0, 4,  8, 12, 0, 4,  8, 12, 0, 0, 0, 0);
		n512 m1_yyyy = _hlslpp512_perm_ps(m1.vec, 1, 5,  9, 13, 1, 5,  9, 13, 1, 5,  9, 13, 0, 0, 0, 0);
		n512 m1_zzzz = _hlslpp512_perm_ps(m1.vec, 2, 6, 10, 14, 2, 6, 10, 14, 2, 6, 10, 14, 0, 0, 0, 0);
		n512 m1_wwww = _hlslpp512_perm_ps(m1.vec, 3, 7, 11, 15, 3, 7, 11, 15, 3, 7, 11, 15, 0, 0, 0, 0);

		n512 m2_vec0123 = _hlslpp512_set128_ps(m2.vec0, m2.vec1, m2.vec2, m2.vec0);

		n512 m2_vec0_vec0_vec0_vec0 = _hlslpp512_perm_ps(m2_vec0123, 0, 0, 0, 0, 4, 4, 4, 4, 8, 8, 8, 8, 0, 0, 0, 0);
		n512 m2_vec1_vec1_vec1_vec1 = _hlslpp512_perm_ps(m2_vec0123, 1, 1, 1, 1, 5, 5, 5, 5, 9, 9, 9, 9, 0, 0, 0, 0);
		n512 m2_vec2_vec2_vec2_vec2 = _hlslpp512_perm_ps(m2_vec0123, 2, 2, 2, 2, 6, 6, 6, 6, 10, 10, 10, 10, 0, 0, 0, 0);
		n512 m2_vec3_vec3_vec3_vec3 = _hlslpp512_perm_ps(m2_vec0123, 3, 3, 3, 3, 7, 7, 7, 7, 11, 11, 11, 11, 0, 0, 0, 0);

		n512 mul1 = _hlslpp512_mul_ps (m1_xxxx, m2_vec0_vec0_vec0_vec0);
		n512 mad1 = _hlslpp512_madd_ps(m1_yyyy, m2_vec1_vec1_vec1_vec1, mul1);
		n512 mad2 = _hlslpp512_madd_ps(m1_zzzz, m2_vec2_vec2_vec2_vec2, mad1);
		n512 mad3 = _hlslpp512_madd_ps(m1_wwww, m2_vec3_vec3_vec3_vec3, mad2);

		return float4x3(_hlslpp512_vec0_ps(mad3), _hlslpp512_vec1_ps(mad3), _hlslpp512_vec2_ps(mad3));

#elif defined(HLSLPP_SIMD_REGISTER_256)

		n256 m2_vec0 = _hlslpp256_set128_ps(m2.vec0, m2.vec0);

		n256 dot_row0_12 = _hlslpp256_dot4_ps(m1.vec0, m2_vec0);
		n256 dot_row0_23 = _hlslpp256_dot4_ps(m1.vec1, m2_vec0);

		n128 row0 = _hlslpp_blend_ps(
			_hlslpp_shuf_xxxx_ps(_hlslpp256_low_ps(dot_row0_12), _hlslpp256_low_ps(dot_row0_23)),
			_hlslpp_shuf_xxxx_ps(_hlslpp256_high_ps(dot_row0_12), _hlslpp256_high_ps(dot_row0_23)),
			HLSLPP_BLEND_MASK(1, 0, 1, 0));

		n256 m2_vec1 = _hlslpp256_set128_ps(m2.vec1, m2.vec1);

		n256 dot_row1_12 = _hlslpp256_dot4_ps(m1.vec0, m2_vec1);
		n256 dot_row1_23 = _hlslpp256_dot4_ps(m1.vec1, m2_vec1);

		n128 row1 = _hlslpp_blend_ps(
			_hlslpp_shuf_xxxx_ps(_hlslpp256_low_ps(dot_row1_12), _hlslpp256_low_ps(dot_row1_23)),
			_hlslpp_shuf_xxxx_ps(_hlslpp256_high_ps(dot_row1_12), _hlslpp256_high_ps(dot_row1_23)),
			HLSLPP_BLEND_MASK(1, 0, 1, 0));

		n256 m2_vec2 = _hlslpp256_set128_ps(m2.vec2, m2.vec2);

		n256 dot_row2_12 = _hlslpp256_dot4_ps(m1.vec0, m2_vec2);
		n256 dot_row2_23 = _hlslpp256_dot4_ps(m1.vec1, m2_vec2);

		n128 row2 = _hlslpp_blend_ps(
			_hlslpp_shuf_xxxx_ps(_hlslpp256_low_ps(dot_row2_12), _hlslpp256_low_ps(dot_row2_23)),
			_hlslpp_shuf_xxxx_ps(_hlslpp256_high_ps(dot_row2_12), _hlslpp256_high_ps(dot_row2_23)),
			HLSLPP_BLEND_MASK(1, 0, 1, 0));

		return float4x3(row0, row1, row2);

#else

		n128 dpx0 = _hlslpp_dot4_ps(m1.vec0, m2.vec0);
		n128 dpy0 = _hlslpp_dot4_ps(m1.vec1, m2.vec0);
		n128 dpz0 = _hlslpp_dot4_ps(m1.vec2, m2.vec0);
		n128 dpw0 = _hlslpp_dot4_ps(m1.vec3, m2.vec0);

		n128 dpx1 = _hlslpp_dot4_ps(m1.vec0, m2.vec1);
		n128 dpy1 = _hlslpp_dot4_ps(m1.vec1, m2.vec1);
		n128 dpz1 = _hlslpp_dot4_ps(m1.vec2, m2.vec1);
		n128 dpw1 = _hlslpp_dot4_ps(m1.vec3, m2.vec1);

		n128 dpx2 = _hlslpp_dot4_ps(m1.vec0, m2.vec2);
		n128 dpy2 = _hlslpp_dot4_ps(m1.vec1, m2.vec2);
		n128 dpz2 = _hlslpp_dot4_ps(m1.vec2, m2.vec2);
		n128 dpw2 = _hlslpp_dot4_ps(m1.vec3, m2.vec2);

		return float4x3
		(
			_hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx0, dpz0), _hlslpp_shuf_xxxx_ps(dpy0, dpw0), HLSLPP_BLEND_MASK(1, 0, 1, 0)),
			_hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx1, dpz1), _hlslpp_shuf_xxxx_ps(dpy1, dpw1), HLSLPP_BLEND_MASK(1, 0, 1, 0)),
			_hlslpp_blend_ps(_hlslpp_shuf_xxxx_ps(dpx2, dpz2), _hlslpp_shuf_xxxx_ps(dpy2, dpw2), HLSLPP_BLEND_MASK(1, 0, 1, 0))
		);

#endif
	}

	inline float4x4 mul(const float4x4& m1, const float4x4& m2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)

		n512 m2_vec0_vec0_vec0_vec0 = _mm512_shuffle_f32x4(m2.vec, m2.vec, 0x00);
		n512 m2_vec1_vec1_vec1_vec1 = _mm512_shuffle_f32x4(m2.vec, m2.vec, 0x55); // 0b01010101
		n512 m2_vec2_vec2_vec2_vec2 = _mm512_shuffle_f32x4(m2.vec, m2.vec, 0xaa); // 0b10101010
		n512 m2_vec3_vec3_vec3_vec3 = _mm512_shuffle_f32x4(m2.vec, m2.vec, 0xff); // 0b11111111

		n512 m1_xxxx = _hlslpp512_perm_ps(m1.vec, 0, 0, 0, 0, 4, 4, 4, 4,  8,  8,  8,  8, 12, 12, 12, 12);
		n512 m1_yyyy = _hlslpp512_perm_ps(m1.vec, 1, 1, 1, 1, 5, 5, 5, 5,  9,  9,  9,  9, 13, 13, 13, 13);
		n512 m1_zzzz = _hlslpp512_perm_ps(m1.vec, 2, 2, 2, 2, 6, 6, 6, 6, 10, 10, 10, 10, 14, 14, 14, 14);
		n512 m1_wwww = _hlslpp512_perm_ps(m1.vec, 3, 3, 3, 3, 7, 7, 7, 7, 11, 11, 11, 11, 15, 15, 15, 15);

		n512 mul1 = _hlslpp512_mul_ps(m2_vec0_vec0_vec0_vec0, m1_xxxx);
		n512 mad1 = _hlslpp512_madd_ps(m2_vec1_vec1_vec1_vec1, m1_yyyy, mul1);
		n512 mad2 = _hlslpp512_madd_ps(m2_vec2_vec2_vec2_vec2, m1_zzzz, mad1);
		n512 mad3 = _hlslpp512_madd_ps(m2_vec3_vec3_vec3_vec3, m1_wwww, mad2);

		return float4x4(mad3);

#elif defined(HLSLPP_SIMD_REGISTER_256)

		n256 m2_vec0_high_low = _hlslpp256_high_low_ps(m2.vec0, m2.vec0);
		n256 m2_vec1_high_low = _hlslpp256_high_low_ps(m2.vec1, m2.vec1);

		// First/Second rows
		n256 mul1xa = _hlslpp256_mul_ps(m2.vec0,           _hlslpp256_perm_xxxx_bbbb_ps(m1.vec0));
		n256 mad1yb = _hlslpp256_madd_ps(m2_vec0_high_low, _hlslpp256_perm_yyyy_aaaa_ps(m1.vec0), mul1xa);
		n256 mad1zc = _hlslpp256_madd_ps(m2.vec1,          _hlslpp256_perm_zzzz_dddd_ps(m1.vec0), mad1yb);
		n256 row12  = _hlslpp256_madd_ps(m2_vec1_high_low, _hlslpp256_perm_wwww_cccc_ps(m1.vec0), mad1zc);

		// Third/Fourth rows
		n256 mul2xa = _hlslpp256_mul_ps(m2.vec0,           _hlslpp256_perm_xxxx_bbbb_ps(m1.vec1));
		n256 mad2yb = _hlslpp256_madd_ps(m2_vec0_high_low, _hlslpp256_perm_yyyy_aaaa_ps(m1.vec1), mul2xa);
		n256 mad2zc = _hlslpp256_madd_ps(m2.vec1,          _hlslpp256_perm_zzzz_dddd_ps(m1.vec1), mad2yb);
		n256 row34  = _hlslpp256_madd_ps(m2_vec1_high_low, _hlslpp256_perm_wwww_cccc_ps(m1.vec1), mad2zc);

		return float4x4(row12, row34);

#else

		// First row
		n128 mul1x = _hlslpp_mul_ps(m2.vec0, _hlslpp_perm_xxxx_ps(m1.vec0));
		n128 mad1y = _hlslpp_madd_ps(m2.vec1, _hlslpp_perm_yyyy_ps(m1.vec0), mul1x);
		n128 mad1z = _hlslpp_madd_ps(m2.vec2, _hlslpp_perm_zzzz_ps(m1.vec0), mad1y);
		n128 row1 = _hlslpp_madd_ps(m2.vec3, _hlslpp_perm_wwww_ps(m1.vec0), mad1z);

		// Second row
		n128 mul2x = _hlslpp_mul_ps(m2.vec0, _hlslpp_perm_xxxx_ps(m1.vec1));
		n128 mad2y = _hlslpp_madd_ps(m2.vec1, _hlslpp_perm_yyyy_ps(m1.vec1), mul2x);
		n128 mad2z = _hlslpp_madd_ps(m2.vec2, _hlslpp_perm_zzzz_ps(m1.vec1), mad2y);
		n128 row2 = _hlslpp_madd_ps(m2.vec3, _hlslpp_perm_wwww_ps(m1.vec1), mad2z);

		// Third row
		n128 mul3x = _hlslpp_mul_ps(m2.vec0, _hlslpp_perm_xxxx_ps(m1.vec2));
		n128 mad3y = _hlslpp_madd_ps(m2.vec1, _hlslpp_perm_yyyy_ps(m1.vec2), mul3x);
		n128 mad3z = _hlslpp_madd_ps(m2.vec2, _hlslpp_perm_zzzz_ps(m1.vec2), mad3y);
		n128 row3 = _hlslpp_madd_ps(m2.vec3, _hlslpp_perm_wwww_ps(m1.vec2), mad3z);

		// Fourth row
		n128 mul4x = _hlslpp_mul_ps(m2.vec0, _hlslpp_perm_xxxx_ps(m1.vec3));
		n128 mad4y = _hlslpp_madd_ps(m2.vec1, _hlslpp_perm_yyyy_ps(m1.vec3), mul4x);
		n128 mad4z = _hlslpp_madd_ps(m2.vec2, _hlslpp_perm_zzzz_ps(m1.vec3), mad4y);
		n128 row4 = _hlslpp_madd_ps(m2.vec3, _hlslpp_perm_wwww_ps(m1.vec3), mad4z);

		return float4x4(row1, row2, row3, row4);

#endif
	}

	hlslpp_inline float1 mul(const float1x1& m1, const float1& m2) { return float1(_hlslpp_mul_ps(m1.vec, m2.vec)); }

	hlslpp_inline float1 mul(const float1x2& m1, const float2& v1) { return float1(mul(m1, float2x1(v1.vec)).vec); }
	hlslpp_inline float2 mul(const float2x2& m1, const float2& v1) { return float2(mul(m1, float2x1(v1.vec)).vec); }
	hlslpp_inline float3 mul(const float3x2& m1, const float2& v1) { return float3(mul(m1, float2x1(v1.vec)).vec); }
	hlslpp_inline float4 mul(const float4x2& m1, const float2& v1) { return float4(mul(m1, float2x1(v1.vec)).vec); }

	hlslpp_inline float1 mul(const float2& v1, const float2x1& m2) { return float1(mul(float1x2(v1.vec), m2).vec); }
	hlslpp_inline float2 mul(const float2& v1, const float2x2& m2) { return float2(mul(float1x2(v1.vec), m2).vec); }
	hlslpp_inline float3 mul(const float2& v1, const float2x3& m2) { return float3(mul(float1x2(v1.vec), m2).vec); }
	hlslpp_inline float4 mul(const float2& v1, const float2x4& m2) { return float4(mul(float1x2(v1.vec), m2).vec); }

	hlslpp_inline float1 mul(const float1x3& m1, const float3& v1) { return float1(mul(m1, float3x1(v1.vec)).vec); }
	hlslpp_inline float2 mul(const float2x3& m1, const float3& v1) { return float2(mul(m1, float3x1(v1.vec)).vec); }
	hlslpp_inline float3 mul(const float3x3& m1, const float3& v1) { return float3(mul(m1, float3x1(v1.vec)).vec); }
	hlslpp_inline float4 mul(const float4x3& m1, const float3& v1) { return float4(mul(m1, float3x1(v1.vec)).vec); }

	hlslpp_inline float1 mul(const float3& v1, const float3x1& m2) { return float1(mul(float1x3(v1.vec), m2).vec); }
	hlslpp_inline float2 mul(const float3& v1, const float3x2& m2) { return float2(mul(float1x3(v1.vec), m2).vec); }
	hlslpp_inline float3 mul(const float3& v1, const float3x3& m2) { return float3(mul(float1x3(v1.vec), m2).vec); }
	hlslpp_inline float4 mul(const float3& v1, const float3x4& m2) { return float4(mul(float1x3(v1.vec), m2).vec); }

	hlslpp_inline float1 mul(const float1x4& m1, const float4& v1) { return float1(mul(m1, float4x1(v1.vec)).vec); }
	hlslpp_inline float2 mul(const float2x4& m1, const float4& v1) { return float2(mul(m1, float4x1(v1.vec)).vec); }
	hlslpp_inline float3 mul(const float3x4& m1, const float4& v1) { return float3(mul(m1, float4x1(v1.vec)).vec); }
	hlslpp_inline float4 mul(const float4x4& m1, const float4& v1) { return float4(mul(m1, float4x1(v1.vec)).vec); }

	hlslpp_inline float1 mul(const float4& v1, const float4x1& m2) { return float1(mul(float1x4(v1.vec), m2).vec); }
	hlslpp_inline float2 mul(const float4& v1, const float4x2& m2) { return float2(mul(float1x4(v1.vec), m2).vec); }
	hlslpp_inline float3 mul(const float4& v1, const float4x3& m2) { return float3(mul(float1x4(v1.vec), m2).vec); }
	hlslpp_inline float4 mul(const float4& v1, const float4x4& m2) { return float4(mul(float1x4(v1.vec), m2).vec); }

	hlslpp_inline float1x1 operator + (const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_add_ps(m1.vec, m2.vec)); }
	hlslpp_inline float1x2 operator + (const float1x2& m1, const float1x2& m2) { return float1x2(_hlslpp_add_ps(m1.vec, m2.vec)); }
	hlslpp_inline float1x3 operator + (const float1x3& m1, const float1x3& m2) { return float1x3(_hlslpp_add_ps(m1.vec, m2.vec)); }
	hlslpp_inline float1x4 operator + (const float1x4& m1, const float1x4& m2) { return float1x4(_hlslpp_add_ps(m1.vec, m2.vec)); }
	hlslpp_inline float2x1 operator + (const float2x1& m1, const float2x1& m2) { return float2x1(_hlslpp_add_ps(m1.vec, m2.vec)); }
	hlslpp_inline float3x1 operator + (const float3x1& m1, const float3x1& m2) { return float3x1(_hlslpp_add_ps(m1.vec, m2.vec)); }
	hlslpp_inline float4x1 operator + (const float4x1& m1, const float4x1& m2) { return float4x1(_hlslpp_add_ps(m1.vec, m2.vec)); }
	hlslpp_inline float2x2 operator + (const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_add_ps(m1.vec, m2.vec)); }
	hlslpp_inline float2x3 operator + (const float2x3& m1, const float2x3& m2) { return float2x3(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float3x2 operator + (const float3x2& m1, const float3x2& m2) { return float3x2(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float2x4 operator + (const float2x4& m1, const float2x4& m2) { return float2x4(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float4x2 operator + (const float4x2& m1, const float4x2& m2) { return float4x2(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float3x3 operator + (const float3x3& m1, const float3x3& m2) { return float3x3(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1), _hlslpp_add_ps(m1.vec2, m2.vec2)); }
	hlslpp_inline float3x4 operator + (const float3x4& m1, const float3x4& m2) { return float3x4(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1), _hlslpp_add_ps(m1.vec2, m2.vec2)); }
	hlslpp_inline float4x3 operator + (const float4x3& m1, const float4x3& m2) { return float4x3(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1), _hlslpp_add_ps(m1.vec2, m2.vec2)); }
	hlslpp_inline float4x4 operator + (const float4x4& m1, const float4x4& m2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		return float4x4(_hlslpp512_add_ps(m1.vec, m2.vec));
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return float4x4(_hlslpp256_add_ps(m1.vec0, m2.vec0), _hlslpp256_add_ps(m1.vec1, m2.vec1));
#else
		return float4x4(_hlslpp_add_ps(m1.vec0, m2.vec0), _hlslpp_add_ps(m1.vec1, m2.vec1), _hlslpp_add_ps(m1.vec2, m2.vec2), _hlslpp_add_ps(m1.vec3, m2.vec3));
#endif
	}

	hlslpp_inline float1x1& operator += (float1x1& m1, const float1x1& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float1x2& operator += (float1x2& m1, const float1x2& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float1x3& operator += (float1x3& m1, const float1x3& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float1x4& operator += (float1x4& m1, const float1x4& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float2x1& operator += (float2x1& m1, const float2x1& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float3x1& operator += (float3x1& m1, const float3x1& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float4x1& operator += (float4x1& m1, const float4x1& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float2x2& operator += (float2x2& m1, const float2x2& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float2x3& operator += (float2x3& m1, const float2x3& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float2x4& operator += (float2x4& m1, const float2x4& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float3x2& operator += (float3x2& m1, const float3x2& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float4x2& operator += (float4x2& m1, const float4x2& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float3x3& operator += (float3x3& m1, const float3x3& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float3x4& operator += (float3x4& m1, const float3x4& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float4x3& operator += (float4x3& m1, const float4x3& m2) { m1 = m1 + m2; return m1; }
	hlslpp_inline float4x4& operator += (float4x4& m1, const float4x4& m2) { m1 = m1 + m2; return m1; }

	hlslpp_inline float1x1 operator - (const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	hlslpp_inline float1x2 operator - (const float1x2& m1, const float1x2& m2) { return float1x2(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	hlslpp_inline float1x3 operator - (const float1x3& m1, const float1x3& m2) { return float1x3(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	hlslpp_inline float1x4 operator - (const float1x4& m1, const float1x4& m2) { return float1x4(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	hlslpp_inline float2x1 operator - (const float2x1& m1, const float2x1& m2) { return float2x1(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	hlslpp_inline float3x1 operator - (const float3x1& m1, const float3x1& m2) { return float3x1(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	hlslpp_inline float4x1 operator - (const float4x1& m1, const float4x1& m2) { return float4x1(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	hlslpp_inline float2x2 operator - (const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_sub_ps(m1.vec, m2.vec)); }
	hlslpp_inline float2x3 operator - (const float2x3& m1, const float2x3& m2) { return float2x3(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float3x2 operator - (const float3x2& m1, const float3x2& m2) { return float3x2(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float2x4 operator - (const float2x4& m1, const float2x4& m2) { return float2x4(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float4x2 operator - (const float4x2& m1, const float4x2& m2) { return float4x2(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float3x3 operator - (const float3x3& m1, const float3x3& m2) { return float3x3(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1), _hlslpp_sub_ps(m1.vec2, m2.vec2)); }
	hlslpp_inline float3x4 operator - (const float3x4& m1, const float3x4& m2) { return float3x4(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1), _hlslpp_sub_ps(m1.vec2, m2.vec2)); }
	hlslpp_inline float4x3 operator - (const float4x3& m1, const float4x3& m2) { return float4x3(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1), _hlslpp_sub_ps(m1.vec2, m2.vec2)); }
	hlslpp_inline float4x4 operator - (const float4x4& m1, const float4x4& m2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		return float4x4(_hlslpp512_sub_ps(m1.vec, m2.vec));
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return float4x4(_hlslpp256_sub_ps(m1.vec0, m2.vec0), _hlslpp256_sub_ps(m1.vec1, m2.vec1));
#else
		return float4x4(_hlslpp_sub_ps(m1.vec0, m2.vec0), _hlslpp_sub_ps(m1.vec1, m2.vec1), _hlslpp_sub_ps(m1.vec2, m2.vec2), _hlslpp_sub_ps(m1.vec3, m2.vec3));
#endif
	}

	hlslpp_inline float1x1& operator -= (float1x1& m1, const float1x1& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float1x2& operator -= (float1x2& m1, const float1x2& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float1x3& operator -= (float1x3& m1, const float1x3& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float1x4& operator -= (float1x4& m1, const float1x4& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float2x1& operator -= (float2x1& m1, const float2x1& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float3x1& operator -= (float3x1& m1, const float3x1& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float4x1& operator -= (float4x1& m1, const float4x1& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float2x2& operator -= (float2x2& m1, const float2x2& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float2x3& operator -= (float2x3& m1, const float2x3& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float2x4& operator -= (float2x4& m1, const float2x4& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float3x2& operator -= (float3x2& m1, const float3x2& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float4x2& operator -= (float4x2& m1, const float4x2& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float3x3& operator -= (float3x3& m1, const float3x3& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float3x4& operator -= (float3x4& m1, const float3x4& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float4x3& operator -= (float4x3& m1, const float4x3& m2) { m1 = m1 - m2; return m1; }
	hlslpp_inline float4x4& operator -= (float4x4& m1, const float4x4& m2) { m1 = m1 - m2; return m1; }

	hlslpp_inline float1x1 operator * (const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	hlslpp_inline float1x2 operator * (const float1x2& m1, const float1x2& m2) { return float1x2(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	hlslpp_inline float1x3 operator * (const float1x3& m1, const float1x3& m2) { return float1x3(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	hlslpp_inline float1x4 operator * (const float1x4& m1, const float1x4& m2) { return float1x4(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	hlslpp_inline float2x1 operator * (const float2x1& m1, const float2x1& m2) { return float2x1(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	hlslpp_inline float3x1 operator * (const float3x1& m1, const float3x1& m2) { return float3x1(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	hlslpp_inline float4x1 operator * (const float4x1& m1, const float4x1& m2) { return float4x1(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	hlslpp_inline float2x2 operator * (const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_mul_ps(m1.vec, m2.vec)); }
	hlslpp_inline float2x3 operator * (const float2x3& m1, const float2x3& m2) { return float2x3(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float3x2 operator * (const float3x2& m1, const float3x2& m2) { return float3x2(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float2x4 operator * (const float2x4& m1, const float2x4& m2) { return float2x4(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float4x2 operator * (const float4x2& m1, const float4x2& m2) { return float4x2(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float3x3 operator * (const float3x3& m1, const float3x3& m2) { return float3x3(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1), _hlslpp_mul_ps(m1.vec2, m2.vec2)); }
	hlslpp_inline float3x4 operator * (const float3x4& m1, const float3x4& m2) { return float3x4(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1), _hlslpp_mul_ps(m1.vec2, m2.vec2)); }
	hlslpp_inline float4x3 operator * (const float4x3& m1, const float4x3& m2) { return float4x3(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1), _hlslpp_mul_ps(m1.vec2, m2.vec2)); }
	hlslpp_inline float4x4 operator * (const float4x4& m1, const float4x4& m2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		return float4x4(_hlslpp512_mul_ps(m1.vec, m2.vec));
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return float4x4(_hlslpp256_mul_ps(m1.vec0, m2.vec0), _hlslpp256_mul_ps(m1.vec1, m2.vec1));
#else
		return float4x4(_hlslpp_mul_ps(m1.vec0, m2.vec0), _hlslpp_mul_ps(m1.vec1, m2.vec1), _hlslpp_mul_ps(m1.vec2, m2.vec2), _hlslpp_mul_ps(m1.vec3, m2.vec3));
#endif
	}

	hlslpp_inline float1x1& operator *= (float1x1& m1, const float1x1& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float1x2& operator *= (float1x2& m1, const float1x2& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float1x3& operator *= (float1x3& m1, const float1x3& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float1x4& operator *= (float1x4& m1, const float1x4& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float2x1& operator *= (float2x1& m1, const float2x1& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float3x1& operator *= (float3x1& m1, const float3x1& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float4x1& operator *= (float4x1& m1, const float4x1& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float2x2& operator *= (float2x2& m1, const float2x2& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float2x3& operator *= (float2x3& m1, const float2x3& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float2x4& operator *= (float2x4& m1, const float2x4& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float3x2& operator *= (float3x2& m1, const float3x2& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float4x2& operator *= (float4x2& m1, const float4x2& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float3x3& operator *= (float3x3& m1, const float3x3& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float3x4& operator *= (float3x4& m1, const float3x4& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float4x3& operator *= (float4x3& m1, const float4x3& m2) { m1 = m1 * m2; return m1; }
	hlslpp_inline float4x4& operator *= (float4x4& m1, const float4x4& m2) { m1 = m1 * m2; return m1; }

	hlslpp_inline float1x1 operator / (const float1x1& m1, const float1x1& m2) { return float1x1(_hlslpp_div_ps(m1.vec, m2.vec)); }
	hlslpp_inline float1x2 operator / (const float1x2& m1, const float1x2& m2) { return float1x2(_hlslpp_div_ps(m1.vec, m2.vec)); }
	hlslpp_inline float1x3 operator / (const float1x3& m1, const float1x3& m2) { return float1x3(_hlslpp_div_ps(m1.vec, m2.vec)); }
	hlslpp_inline float1x4 operator / (const float1x4& m1, const float1x4& m2) { return float1x4(_hlslpp_div_ps(m1.vec, m2.vec)); }
	hlslpp_inline float2x1 operator / (const float2x1& m1, const float2x1& m2) { return float2x1(_hlslpp_div_ps(m1.vec, m2.vec)); }
	hlslpp_inline float3x1 operator / (const float3x1& m1, const float3x1& m2) { return float3x1(_hlslpp_div_ps(m1.vec, m2.vec)); }
	hlslpp_inline float4x1 operator / (const float4x1& m1, const float4x1& m2) { return float4x1(_hlslpp_div_ps(m1.vec, m2.vec)); }
	hlslpp_inline float2x2 operator / (const float2x2& m1, const float2x2& m2) { return float2x2(_hlslpp_div_ps(m1.vec, m2.vec)); }
	hlslpp_inline float2x3 operator / (const float2x3& m1, const float2x3& m2) { return float2x3(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float3x2 operator / (const float3x2& m1, const float3x2& m2) { return float3x2(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float2x4 operator / (const float2x4& m1, const float2x4& m2) { return float2x4(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float4x2 operator / (const float4x2& m1, const float4x2& m2) { return float4x2(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1)); }
	hlslpp_inline float3x3 operator / (const float3x3& m1, const float3x3& m2) { return float3x3(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1), _hlslpp_div_ps(m1.vec2, m2.vec2)); }
	hlslpp_inline float3x4 operator / (const float3x4& m1, const float3x4& m2) { return float3x4(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1), _hlslpp_div_ps(m1.vec2, m2.vec2)); }
	hlslpp_inline float4x3 operator / (const float4x3& m1, const float4x3& m2) { return float4x3(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1), _hlslpp_div_ps(m1.vec2, m2.vec2)); }
	hlslpp_inline float4x4 operator / (const float4x4& m1, const float4x4& m2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		return float4x4(_hlslpp512_div_ps(m1.vec, m2.vec));
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return float4x4(_hlslpp256_div_ps(m1.vec0, m2.vec0), _hlslpp256_div_ps(m1.vec1, m2.vec1));
#else
		return float4x4(_hlslpp_div_ps(m1.vec0, m2.vec0), _hlslpp_div_ps(m1.vec1, m2.vec1), _hlslpp_div_ps(m1.vec2, m2.vec2), _hlslpp_div_ps(m1.vec3, m2.vec3));
#endif
	}

	hlslpp_inline float1x1& operator /= (float1x1& m1, const float1x1& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float1x2& operator /= (float1x2& m1, const float1x2& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float1x3& operator /= (float1x3& m1, const float1x3& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float1x4& operator /= (float1x4& m1, const float1x4& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float2x1& operator /= (float2x1& m1, const float2x1& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float3x1& operator /= (float3x1& m1, const float3x1& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float4x1& operator /= (float4x1& m1, const float4x1& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float2x2& operator /= (float2x2& m1, const float2x2& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float2x3& operator /= (float2x3& m1, const float2x3& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float2x4& operator /= (float2x4& m1, const float2x4& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float3x2& operator /= (float3x2& m1, const float3x2& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float4x2& operator /= (float4x2& m1, const float4x2& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float3x3& operator /= (float3x3& m1, const float3x3& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float3x4& operator /= (float3x4& m1, const float3x4& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float4x3& operator /= (float4x3& m1, const float4x3& m2) { m1 = m1 / m2; return m1; }
	hlslpp_inline float4x4& operator /= (float4x4& m1, const float4x4& m2) { m1 = m1 / m2; return m1; }

	// Scalar operators

	hlslpp_inline float1x1 operator + (const float1x1& m, const float1& f) { return float1x1(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float1x2 operator + (const float1x2& m, const float1& f) { return float1x2(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float1x3 operator + (const float1x3& m, const float1& f) { return float1x3(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float1x4 operator + (const float1x4& m, const float1& f) { return float1x4(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float2x1 operator + (const float2x1& m, const float1& f) { return float2x1(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float3x1 operator + (const float3x1& m, const float1& f) { return float3x1(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float4x1 operator + (const float4x1& m, const float1& f) { return float4x1(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float2x2 operator + (const float2x2& m, const float1& f) { return float2x2(_hlslpp_add_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float2x3 operator + (const float2x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x3(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm)); }
	hlslpp_inline float3x2 operator + (const float3x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x2(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm)); }
	hlslpp_inline float2x4 operator + (const float2x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x4(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm)); }
	hlslpp_inline float4x2 operator + (const float4x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x2(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm)); }
	hlslpp_inline float3x3 operator + (const float3x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x3(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm), _hlslpp_add_ps(m.vec2, perm)); }
	hlslpp_inline float3x4 operator + (const float3x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x4(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm), _hlslpp_add_ps(m.vec2, perm)); }
	hlslpp_inline float4x3 operator + (const float4x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x3(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm), _hlslpp_add_ps(m.vec2, perm)); }
	hlslpp_inline float4x4 operator + (const float4x4& m, const float1& f)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)

		n128 perm128 = _hlslpp_perm_xxxx_ps(f.vec);
		n512 perm = _hlslpp512_set128_ps(perm128, perm128, perm128, perm128);
		return float4x4(_hlslpp512_add_ps(m.vec, perm));

#elif defined(HLSLPP_SIMD_REGISTER_256)
		n128 perm128 = _hlslpp_perm_xxxx_ps(f.vec);
		n256 perm = _hlslpp256_set128_ps(perm128, perm128);
		return float4x4(_hlslpp256_add_ps(m.vec0, perm), _hlslpp256_add_ps(m.vec1, perm));
#else
		n128 perm = _hlslpp_perm_xxxx_ps(f.vec);
		return float4x4(_hlslpp_add_ps(m.vec0, perm), _hlslpp_add_ps(m.vec1, perm), _hlslpp_add_ps(m.vec2, perm), _hlslpp_add_ps(m.vec3, perm));
#endif
	}

	hlslpp_inline float1x1 operator - (const float1x1& m, const float1& f) { return float1x1(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float1x2 operator - (const float1x2& m, const float1& f) { return float1x2(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float1x3 operator - (const float1x3& m, const float1& f) { return float1x3(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float1x4 operator - (const float1x4& m, const float1& f) { return float1x4(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float2x1 operator - (const float2x1& m, const float1& f) { return float2x1(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float3x1 operator - (const float3x1& m, const float1& f) { return float3x1(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float4x1 operator - (const float4x1& m, const float1& f) { return float4x1(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float2x2 operator - (const float2x2& m, const float1& f) { return float2x2(_hlslpp_sub_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float2x3 operator - (const float2x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x3(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm)); }
	hlslpp_inline float3x2 operator - (const float3x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x2(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm)); }
	hlslpp_inline float2x4 operator - (const float2x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x4(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm)); }
	hlslpp_inline float4x2 operator - (const float4x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x2(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm)); }
	hlslpp_inline float3x3 operator - (const float3x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x3(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm), _hlslpp_sub_ps(m.vec2, perm)); }
	hlslpp_inline float3x4 operator - (const float3x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x4(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm), _hlslpp_sub_ps(m.vec2, perm)); }
	hlslpp_inline float4x3 operator - (const float4x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x3(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm), _hlslpp_sub_ps(m.vec2, perm)); }
	hlslpp_inline float4x4 operator - (const float4x4& m, const float1& f)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)

		n128 perm128 = _hlslpp_perm_xxxx_ps(f.vec);
		n512 perm = _hlslpp512_set128_ps(perm128, perm128, perm128, perm128);
		return float4x4(_hlslpp512_sub_ps(m.vec, perm));

#elif defined(HLSLPP_SIMD_REGISTER_256)
		n128 perm128 = _hlslpp_perm_xxxx_ps(f.vec);
		n256 perm = _hlslpp256_set128_ps(perm128, perm128);
		return float4x4(_hlslpp256_sub_ps(m.vec0, perm), _hlslpp256_sub_ps(m.vec1, perm));
#else
		n128 perm = _hlslpp_perm_xxxx_ps(f.vec);
		return float4x4(_hlslpp_sub_ps(m.vec0, perm), _hlslpp_sub_ps(m.vec1, perm), _hlslpp_sub_ps(m.vec2, perm), _hlslpp_sub_ps(m.vec3, perm));
#endif
	}

	hlslpp_inline float1x1 operator * (const float1x1& m, const float1& f) { return float1x1(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float1x2 operator * (const float1x2& m, const float1& f) { return float1x2(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float1x3 operator * (const float1x3& m, const float1& f) { return float1x3(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float1x4 operator * (const float1x4& m, const float1& f) { return float1x4(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float2x1 operator * (const float2x1& m, const float1& f) { return float2x1(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float3x1 operator * (const float3x1& m, const float1& f) { return float3x1(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float4x1 operator * (const float4x1& m, const float1& f) { return float4x1(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float2x2 operator * (const float2x2& m, const float1& f) { return float2x2(_hlslpp_mul_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }	
	hlslpp_inline float2x3 operator * (const float2x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x3(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm)); }
	hlslpp_inline float3x2 operator * (const float3x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x2(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm)); }
	hlslpp_inline float2x4 operator * (const float2x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x4(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm)); }
	hlslpp_inline float4x2 operator * (const float4x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x2(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm)); }
	hlslpp_inline float3x3 operator * (const float3x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x3(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm), _hlslpp_mul_ps(m.vec2, perm)); }
	hlslpp_inline float3x4 operator * (const float3x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x4(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm), _hlslpp_mul_ps(m.vec2, perm)); }
	hlslpp_inline float4x3 operator * (const float4x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x3(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm), _hlslpp_mul_ps(m.vec2, perm)); }
	hlslpp_inline float4x4 operator * (const float4x4& m, const float1& f)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)

		n128 perm128 = _hlslpp_perm_xxxx_ps(f.vec);
		n512 perm = _hlslpp512_set128_ps(perm128, perm128, perm128, perm128);
		return float4x4(_hlslpp512_mul_ps(m.vec, perm));

#elif defined(HLSLPP_SIMD_REGISTER_256)
		n128 perm128 = _hlslpp_perm_xxxx_ps(f.vec);
		n256 perm = _hlslpp256_set128_ps(perm128, perm128);
		return float4x4(_hlslpp256_mul_ps(m.vec0, perm), _hlslpp256_mul_ps(m.vec1, perm));
#else
		n128 perm = _hlslpp_perm_xxxx_ps(f.vec);
		return float4x4(_hlslpp_mul_ps(m.vec0, perm), _hlslpp_mul_ps(m.vec1, perm), _hlslpp_mul_ps(m.vec2, perm), _hlslpp_mul_ps(m.vec3, perm));
#endif
	}

	hlslpp_inline float1x1 operator / (const float1x1& m, const float1& f) { return float1x1(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float1x2 operator / (const float1x2& m, const float1& f) { return float1x2(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float1x3 operator / (const float1x3& m, const float1& f) { return float1x3(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float1x4 operator / (const float1x4& m, const float1& f) { return float1x4(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float2x1 operator / (const float2x1& m, const float1& f) { return float2x1(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float3x1 operator / (const float3x1& m, const float1& f) { return float3x1(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float4x1 operator / (const float4x1& m, const float1& f) { return float4x1(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float2x2 operator / (const float2x2& m, const float1& f) { return float2x2(_hlslpp_div_ps(m.vec, _hlslpp_perm_xxxx_ps(f.vec))); }
	hlslpp_inline float2x3 operator / (const float2x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x3(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm)); }
	hlslpp_inline float3x2 operator / (const float3x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x2(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm)); }
	hlslpp_inline float2x4 operator / (const float2x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float2x4(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm)); }
	hlslpp_inline float4x2 operator / (const float4x2& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x2(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm)); }
	hlslpp_inline float3x3 operator / (const float3x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x3(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm), _hlslpp_div_ps(m.vec2, perm)); }
	hlslpp_inline float3x4 operator / (const float3x4& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float3x4(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm), _hlslpp_div_ps(m.vec2, perm)); }
	hlslpp_inline float4x3 operator / (const float4x3& m, const float1& f) { n128 perm = _hlslpp_perm_xxxx_ps(f.vec); return float4x3(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm), _hlslpp_div_ps(m.vec2, perm)); }
	hlslpp_inline float4x4 operator / (const float4x4& m, const float1& f)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)

		n128 perm128 = _hlslpp_perm_xxxx_ps(f.vec);
		n512 perm = _hlslpp512_set128_ps(perm128, perm128, perm128, perm128);
		return float4x4(_hlslpp512_div_ps(m.vec, perm));

#elif defined(HLSLPP_SIMD_REGISTER_256)
		n128 perm128 = _hlslpp_perm_xxxx_ps(f.vec);
		n256 perm = _hlslpp256_set128_ps(perm128, perm128);
		return float4x4(_hlslpp256_div_ps(m.vec0, perm), _hlslpp256_div_ps(m.vec1, perm));
#else
		n128 perm = _hlslpp_perm_xxxx_ps(f.vec);
		return float4x4(_hlslpp_div_ps(m.vec0, perm), _hlslpp_div_ps(m.vec1, perm), _hlslpp_div_ps(m.vec2, perm), _hlslpp_div_ps(m.vec3, perm));
#endif
	}

	hlslpp_inline float1x1 operator - (const float1x1& m) { return float1x1(_hlslpp_neg_ps(m.vec)); }
	hlslpp_inline float1x2 operator - (const float1x2& m) { return float1x2(_hlslpp_neg_ps(m.vec)); }
	hlslpp_inline float1x3 operator - (const float1x3& m) { return float1x3(_hlslpp_neg_ps(m.vec)); }
	hlslpp_inline float1x4 operator - (const float1x4& m) { return float1x4(_hlslpp_neg_ps(m.vec)); }
	hlslpp_inline float2x1 operator - (const float2x1& m) { return float2x1(_hlslpp_neg_ps(m.vec)); }
	hlslpp_inline float3x1 operator - (const float3x1& m) { return float3x1(_hlslpp_neg_ps(m.vec)); }
	hlslpp_inline float4x1 operator - (const float4x1& m) { return float4x1(_hlslpp_neg_ps(m.vec)); }
	hlslpp_inline float2x2 operator - (const float2x2& m) { return float2x2(_hlslpp_neg_ps(m.vec)); }
	hlslpp_inline float2x3 operator - (const float2x3& m) { return float2x3(_hlslpp_neg_ps(m.vec0), _hlslpp_neg_ps(m.vec1)); }
	hlslpp_inline float3x2 operator - (const float3x2& m) { return float3x2(_hlslpp_neg_ps(m.vec0), _hlslpp_neg_ps(m.vec1)); }
	hlslpp_inline float2x4 operator - (const float2x4& m) { return float2x4(_hlslpp_neg_ps(m.vec0), _hlslpp_neg_ps(m.vec1)); }
	hlslpp_inline float4x2 operator - (const float4x2& m) { return float4x2(_hlslpp_neg_ps(m.vec0), _hlslpp_neg_ps(m.vec1)); }
	hlslpp_inline float3x3 operator - (const float3x3& m) { return float3x3(_hlslpp_neg_ps(m.vec0), _hlslpp_neg_ps(m.vec1), _hlslpp_neg_ps(m.vec2)); }
	hlslpp_inline float3x4 operator - (const float3x4& m) { return float3x4(_hlslpp_neg_ps(m.vec0), _hlslpp_neg_ps(m.vec1), _hlslpp_neg_ps(m.vec2)); }
	hlslpp_inline float4x3 operator - (const float4x3& m) { return float4x3(_hlslpp_neg_ps(m.vec0), _hlslpp_neg_ps(m.vec1), _hlslpp_neg_ps(m.vec2)); }
	hlslpp_inline float4x4 operator - (const float4x4& m)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		return float4x4(_hlslpp512_neg_ps(m.vec));
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return float4x4(_hlslpp256_neg_ps(m.vec0), _hlslpp256_neg_ps(m.vec1));
#else
		return float4x4(_hlslpp_neg_ps(m.vec0), _hlslpp_neg_ps(m.vec1), _hlslpp_neg_ps(m.vec2), _hlslpp_neg_ps(m.vec3));
#endif
	}

	// Pre-increment

	hlslpp_inline float1x1& operator ++ (float1x1& f) { f = f + float1x1(1.0f); return f; }
	hlslpp_inline float1x2& operator ++ (float1x2& f) { f = f + float1x2(1.0f); return f; }
	hlslpp_inline float1x3& operator ++ (float1x3& f) { f = f + float1x3(1.0f); return f; }
	hlslpp_inline float1x4& operator ++ (float1x4& f) { f = f + float1x4(1.0f); return f; }
	hlslpp_inline float2x1& operator ++ (float2x1& f) { f = f + float2x1(1.0f); return f; }
	hlslpp_inline float3x1& operator ++ (float3x1& f) { f = f + float3x1(1.0f); return f; }
	hlslpp_inline float4x1& operator ++ (float4x1& f) { f = f + float4x1(1.0f); return f; }
	hlslpp_inline float2x2& operator ++ (float2x2& f) { f = f + float2x2(1.0f); return f; }
	hlslpp_inline float2x3& operator ++ (float2x3& f) { f = f + float2x3(1.0f); return f; }
	hlslpp_inline float3x2& operator ++ (float3x2& f) { f = f + float3x2(1.0f); return f; }
	hlslpp_inline float2x4& operator ++ (float2x4& f) { f = f + float2x4(1.0f); return f; }
	hlslpp_inline float4x2& operator ++ (float4x2& f) { f = f + float4x2(1.0f); return f; }
	hlslpp_inline float3x3& operator ++ (float3x3& f) { f = f + float3x3(1.0f); return f; }
	hlslpp_inline float3x4& operator ++ (float3x4& f) { f = f + float3x4(1.0f); return f; }
	hlslpp_inline float4x3& operator ++ (float4x3& f) { f = f + float4x3(1.0f); return f; }
	hlslpp_inline float4x4& operator ++ (float4x4& f) { f = f + float4x4(1.0f); return f; }

	hlslpp_inline float1x1& operator -- (float1x1& f) { f = f - float1x1(1.0f); return f; }
	hlslpp_inline float1x2& operator -- (float1x2& f) { f = f - float1x2(1.0f); return f; }
	hlslpp_inline float1x3& operator -- (float1x3& f) { f = f - float1x3(1.0f); return f; }
	hlslpp_inline float1x4& operator -- (float1x4& f) { f = f - float1x4(1.0f); return f; }
	hlslpp_inline float2x1& operator -- (float2x1& f) { f = f - float2x1(1.0f); return f; }
	hlslpp_inline float3x1& operator -- (float3x1& f) { f = f - float3x1(1.0f); return f; }
	hlslpp_inline float4x1& operator -- (float4x1& f) { f = f - float4x1(1.0f); return f; }
	hlslpp_inline float2x2& operator -- (float2x2& f) { f = f - float2x2(1.0f); return f; }
	hlslpp_inline float2x3& operator -- (float2x3& f) { f = f - float2x3(1.0f); return f; }
	hlslpp_inline float3x2& operator -- (float3x2& f) { f = f - float3x2(1.0f); return f; }
	hlslpp_inline float2x4& operator -- (float2x4& f) { f = f - float2x4(1.0f); return f; }
	hlslpp_inline float4x2& operator -- (float4x2& f) { f = f - float4x2(1.0f); return f; }
	hlslpp_inline float3x3& operator -- (float3x3& f) { f = f - float3x3(1.0f); return f; }
	hlslpp_inline float3x4& operator -- (float3x4& f) { f = f - float3x4(1.0f); return f; }
	hlslpp_inline float4x3& operator -- (float4x3& f) { f = f - float4x3(1.0f); return f; }
	hlslpp_inline float4x4& operator -- (float4x4& f) { f = f - float4x4(1.0f); return f; }

	// Post-increment

	hlslpp_inline float1x1 operator ++ (float1x1& f, int) { float1x1 tmp = f; f = f + float1x1(1.0f); return tmp; }
	hlslpp_inline float1x2 operator ++ (float1x2& f, int) { float1x2 tmp = f; f = f + float1x2(1.0f); return tmp; }
	hlslpp_inline float1x3 operator ++ (float1x3& f, int) { float1x3 tmp = f; f = f + float1x3(1.0f); return tmp; }
	hlslpp_inline float1x4 operator ++ (float1x4& f, int) { float1x4 tmp = f; f = f + float1x4(1.0f); return tmp; }
	hlslpp_inline float2x1 operator ++ (float2x1& f, int) { float2x1 tmp = f; f = f + float2x1(1.0f); return tmp; }
	hlslpp_inline float3x1 operator ++ (float3x1& f, int) { float3x1 tmp = f; f = f + float3x1(1.0f); return tmp; }
	hlslpp_inline float4x1 operator ++ (float4x1& f, int) { float4x1 tmp = f; f = f + float4x1(1.0f); return tmp; }
	hlslpp_inline float2x2 operator ++ (float2x2& f, int) { float2x2 tmp = f; f = f + float2x2(1.0f); return tmp; }
	hlslpp_inline float2x3 operator ++ (float2x3& f, int) { float2x3 tmp = f; f = f + float2x3(1.0f); return tmp; }
	hlslpp_inline float3x2 operator ++ (float3x2& f, int) { float3x2 tmp = f; f = f + float3x2(1.0f); return tmp; }
	hlslpp_inline float2x4 operator ++ (float2x4& f, int) { float2x4 tmp = f; f = f + float2x4(1.0f); return tmp; }
	hlslpp_inline float4x2 operator ++ (float4x2& f, int) { float4x2 tmp = f; f = f + float4x2(1.0f); return tmp; }
	hlslpp_inline float3x3 operator ++ (float3x3& f, int) { float3x3 tmp = f; f = f + float3x3(1.0f); return tmp; }
	hlslpp_inline float3x4 operator ++ (float3x4& f, int) { float3x4 tmp = f; f = f + float3x4(1.0f); return tmp; }
	hlslpp_inline float4x3 operator ++ (float4x3& f, int) { float4x3 tmp = f; f = f + float4x3(1.0f); return tmp; }
	hlslpp_inline float4x4 operator ++ (float4x4& f, int) { float4x4 tmp = f; f = f + float4x4(1.0f); return tmp; }

	hlslpp_inline float1x1 operator -- (float1x1& f, int) { float1x1 tmp = f; f = f - float1x1(1.0f); return tmp; }
	hlslpp_inline float1x2 operator -- (float1x2& f, int) { float1x2 tmp = f; f = f - float1x2(1.0f); return tmp; }
	hlslpp_inline float1x3 operator -- (float1x3& f, int) { float1x3 tmp = f; f = f - float1x3(1.0f); return tmp; }
	hlslpp_inline float1x4 operator -- (float1x4& f, int) { float1x4 tmp = f; f = f - float1x4(1.0f); return tmp; }
	hlslpp_inline float2x1 operator -- (float2x1& f, int) { float2x1 tmp = f; f = f - float2x1(1.0f); return tmp; }
	hlslpp_inline float3x1 operator -- (float3x1& f, int) { float3x1 tmp = f; f = f - float3x1(1.0f); return tmp; }
	hlslpp_inline float4x1 operator -- (float4x1& f, int) { float4x1 tmp = f; f = f - float4x1(1.0f); return tmp; }
	hlslpp_inline float2x2 operator -- (float2x2& f, int) { float2x2 tmp = f; f = f - float2x2(1.0f); return tmp; }
	hlslpp_inline float2x3 operator -- (float2x3& f, int) { float2x3 tmp = f; f = f - float2x3(1.0f); return tmp; }
	hlslpp_inline float3x2 operator -- (float3x2& f, int) { float3x2 tmp = f; f = f - float3x2(1.0f); return tmp; }
	hlslpp_inline float2x4 operator -- (float2x4& f, int) { float2x4 tmp = f; f = f - float2x4(1.0f); return tmp; }
	hlslpp_inline float4x2 operator -- (float4x2& f, int) { float4x2 tmp = f; f = f - float4x2(1.0f); return tmp; }
	hlslpp_inline float3x3 operator -- (float3x3& f, int) { float3x3 tmp = f; f = f - float3x3(1.0f); return tmp; }
	hlslpp_inline float3x4 operator -- (float3x4& f, int) { float3x4 tmp = f; f = f - float3x4(1.0f); return tmp; }
	hlslpp_inline float4x3 operator -- (float4x3& f, int) { float4x3 tmp = f; f = f - float4x3(1.0f); return tmp; }
	hlslpp_inline float4x4 operator -- (float4x4& f, int) { float4x4 tmp = f; f = f - float4x4(1.0f); return tmp; }
	
	hlslpp_inline float2x2 operator == (const float2x2& f1, const float2x2& f2) { return float2x2(_hlslpp_cmpeq1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3x3 operator == (const float3x3& f1, const float3x3& f2) { return float3x3(_hlslpp_cmpeq1_ps(f1.vec0, f2.vec0), _hlslpp_cmpeq1_ps(f1.vec1, f2.vec1), _hlslpp_cmpeq1_ps(f1.vec2, f2.vec2)); }
	hlslpp_inline float4x4 operator == (const float4x4& f1, const float4x4& f2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		return float4x4(_hlslpp512_cmpeq1_ps(f1.vec, f2.vec));
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return float4x4(_hlslpp256_cmpeq1_ps(f1.vec0, f2.vec0), _hlslpp256_cmpeq1_ps(f1.vec1, f2.vec1));
#else
		return float4x4(_hlslpp_cmpeq1_ps(f1.vec0, f2.vec0), _hlslpp_cmpeq1_ps(f1.vec1, f2.vec1), _hlslpp_cmpeq1_ps(f1.vec2, f2.vec2), _hlslpp_cmpeq1_ps(f1.vec3, f2.vec3));
#endif
	}

	hlslpp_inline float2x2 operator != (const float2x2& f1, const float2x2& f2) { return float2x2(_hlslpp_cmpneq1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3x3 operator != (const float3x3& f1, const float3x3& f2) { return float3x3(_hlslpp_cmpneq1_ps(f1.vec0, f2.vec0), _hlslpp_cmpneq1_ps(f1.vec1, f2.vec1), _hlslpp_cmpneq1_ps(f1.vec2, f2.vec2)); }
	hlslpp_inline float4x4 operator != (const float4x4& f1, const float4x4& f2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		return float4x4(_hlslpp512_cmpneq1_ps(f1.vec, f2.vec));
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return float4x4(_hlslpp256_cmpneq1_ps(f1.vec0, f2.vec0), _hlslpp256_cmpneq1_ps(f1.vec1, f2.vec1));
#else
		return float4x4(_hlslpp_cmpneq1_ps(f1.vec0, f2.vec0), _hlslpp_cmpneq1_ps(f1.vec1, f2.vec1), _hlslpp_cmpneq1_ps(f1.vec2, f2.vec2), _hlslpp_cmpneq1_ps(f1.vec3, f2.vec3));
#endif
	}

	hlslpp_inline float2x2 operator > (const float2x2& f1, const float2x2& f2) { return float2x2(_hlslpp_cmpgt1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3x3 operator > (const float3x3& f1, const float3x3& f2) { return float3x3(_hlslpp_cmpgt1_ps(f1.vec0, f2.vec0), _hlslpp_cmpgt1_ps(f1.vec1, f2.vec1), _hlslpp_cmpgt1_ps(f1.vec2, f2.vec2)); }
	hlslpp_inline float4x4 operator > (const float4x4& f1, const float4x4& f2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		return float4x4(_hlslpp512_cmpgt1_ps(f1.vec, f2.vec));
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return float4x4(_hlslpp256_cmpgt1_ps(f1.vec0, f2.vec0), _hlslpp256_cmpgt1_ps(f1.vec1, f2.vec1));
#else
		return float4x4(_hlslpp_cmpgt1_ps(f1.vec0, f2.vec0), _hlslpp_cmpgt1_ps(f1.vec1, f2.vec1), _hlslpp_cmpgt1_ps(f1.vec2, f2.vec2), _hlslpp_cmpgt1_ps(f1.vec3, f2.vec3));
#endif
	}

	hlslpp_inline float2x2 operator >= (const float2x2& f1, const float2x2& f2) { return float2x2(_hlslpp_cmpge1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3x3 operator >= (const float3x3& f1, const float3x3& f2) { return float3x3(_hlslpp_cmpge1_ps(f1.vec0, f2.vec0), _hlslpp_cmpge1_ps(f1.vec1, f2.vec1), _hlslpp_cmpge1_ps(f1.vec2, f2.vec2)); }
	hlslpp_inline float4x4 operator >= (const float4x4& f1, const float4x4& f2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		return float4x4(_hlslpp512_cmpge1_ps(f1.vec, f2.vec));
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return float4x4(_hlslpp256_cmpge1_ps(f1.vec0, f2.vec0), _hlslpp256_cmpge1_ps(f1.vec1, f2.vec1));
#else
		return float4x4(_hlslpp_cmpge1_ps(f1.vec0, f2.vec0), _hlslpp_cmpge1_ps(f1.vec1, f2.vec1), _hlslpp_cmpge1_ps(f1.vec2, f2.vec2), _hlslpp_cmpge1_ps(f1.vec3, f2.vec3));
#endif
	}

	hlslpp_inline float2x2 operator < (const float2x2& f1, const float2x2& f2) { return float2x2(_hlslpp_cmplt1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3x3 operator < (const float3x3& f1, const float3x3& f2) { return float3x3(_hlslpp_cmplt1_ps(f1.vec0, f2.vec0), _hlslpp_cmplt1_ps(f1.vec1, f2.vec1), _hlslpp_cmplt1_ps(f1.vec2, f2.vec2)); }
	hlslpp_inline float4x4 operator < (const float4x4& f1, const float4x4& f2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		return float4x4(_hlslpp512_cmplt1_ps(f1.vec, f2.vec));
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return float4x4(_hlslpp256_cmplt1_ps(f1.vec0, f2.vec0), _hlslpp256_cmplt1_ps(f1.vec1, f2.vec1));
#else
		return float4x4(_hlslpp_cmplt1_ps(f1.vec0, f2.vec0), _hlslpp_cmplt1_ps(f1.vec1, f2.vec1), _hlslpp_cmplt1_ps(f1.vec2, f2.vec2), _hlslpp_cmplt1_ps(f1.vec3, f2.vec3));
#endif
	}

	hlslpp_inline float2x2 operator <= (const float2x2& f1, const float2x2& f2) { return float2x2(_hlslpp_cmple1_ps(f1.vec, f2.vec)); }
	hlslpp_inline float3x3 operator <= (const float3x3& f1, const float3x3& f2)	{ return float3x3(_hlslpp_cmple1_ps(f1.vec0, f2.vec0), _hlslpp_cmple1_ps(f1.vec1, f2.vec1), _hlslpp_cmple1_ps(f1.vec2, f2.vec2)); }
	hlslpp_inline float4x4 operator <= (const float4x4& f1, const float4x4& f2)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		return float4x4(_hlslpp512_cmple1_ps(f1.vec, f2.vec));
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return float4x4(_hlslpp256_cmple1_ps(f1.vec0, f2.vec0), _hlslpp256_cmple1_ps(f1.vec1, f2.vec1));
#else
		return float4x4(_hlslpp_cmple1_ps(f1.vec0, f2.vec0), _hlslpp_cmple1_ps(f1.vec1, f2.vec1), _hlslpp_cmple1_ps(f1.vec2, f2.vec2), _hlslpp_cmple1_ps(f1.vec3, f2.vec3));
#endif
	}

	hlslpp_inline float2x2 adjoint(const float2x2& m)
	{
		return float2x2(_hlslpp_adjoint_2x2_ps(m.vec));
	}

	hlslpp_inline float3x3 adjoint(const float3x3& m)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_adjoint_3x3_ps(m.vec0, m.vec1, m.vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 adjoint(const float4x4& m)
	{
		n128 vec0, vec1, vec2, vec3;

#if defined(HLSLPP_SIMD_REGISTER_512)

		n128 mvec0 = _hlslpp512_vec0_ps(m.vec);
		n128 mvec1 = _hlslpp512_vec1_ps(m.vec);
		n128 mvec2 = _hlslpp512_vec2_ps(m.vec);
		n128 mvec3 = _hlslpp512_vec3_ps(m.vec);

#elif defined(HLSLPP_SIMD_REGISTER_256)

		n128 mvec0 = _hlslpp256_low_ps(m.vec0);
		n128 mvec1 = _hlslpp256_high_ps(m.vec0);
		n128 mvec2 = _hlslpp256_low_ps(m.vec1);
		n128 mvec3 = _hlslpp256_high_ps(m.vec1);

#else

		n128 mvec0 = m.vec0;
		n128 mvec1 = m.vec1;
		n128 mvec2 = m.vec2;
		n128 mvec3 = m.vec3;

#endif

		_hlslpp_adjoint_4x4_ps(mvec0, mvec1, mvec2, mvec3, vec0, vec1, vec2, vec3);

#if defined(HLSLPP_SIMD_REGISTER_512)
		return float4x4(_hlslpp512_set128_ps(vec0, vec1, vec2, vec3));
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return float4x4(_hlslpp256_set128_ps(vec0, vec1), _hlslpp256_set128_ps(vec2, vec3));
#else
		return float4x4(vec0, vec1, vec2, vec3);
#endif
	}

	hlslpp_inline bool all(const float2x2& m) { return _hlslpp_all4_ps(m.vec); }
	hlslpp_inline bool all(const float3x3& m) { return _hlslpp_all3_ps(m.vec0) && _hlslpp_all3_ps(m.vec1) && _hlslpp_all3_ps(m.vec2); }
	hlslpp_inline bool all(const float4x4& m)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		return _hlslpp512_all16_ps(m.vec);
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return _hlslpp256_all8_ps(m.vec0) && _hlslpp256_all8_ps(m.vec1);
#else
		return _hlslpp_all4_ps(m.vec0) && _hlslpp_all4_ps(m.vec1) && _hlslpp_all4_ps(m.vec2) && _hlslpp_all4_ps(m.vec3);
#endif
	}

	hlslpp_inline bool any(const float2x2& m) { return _hlslpp_any4_ps(m.vec); }
	hlslpp_inline bool any(const float3x3& m) { return _hlslpp_any3_ps(m.vec0) || _hlslpp_any3_ps(m.vec1) || _hlslpp_any3_ps(m.vec2); }
	hlslpp_inline bool any(const float4x4& m)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)
		return _hlslpp512_any16_ps(m.vec);
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return _hlslpp256_any8_ps(m.vec0) || _hlslpp256_any8_ps(m.vec1);
#else
		return _hlslpp_any4_ps(m.vec0) || _hlslpp_any4_ps(m.vec1) || _hlslpp_any4_ps(m.vec2) || _hlslpp_any4_ps(m.vec3);
#endif
	}

	hlslpp_inline float1 trace(const float2x2& m)
	{
		return float1(_hlslpp_trace_2x2_ps(m.vec));
	}

	hlslpp_inline float1 trace(const float3x3& m)
	{
		return float1(_hlslpp_trace_3x3_ps(m.vec0, m.vec1, m.vec2));
	}

	inline float1 trace(const float4x4& m)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)

		n128 mvec0 = _hlslpp512_vec0_ps(m.vec);
		n128 mvec1 = _hlslpp512_vec1_ps(m.vec);
		n128 mvec2 = _hlslpp512_vec2_ps(m.vec);
		n128 mvec3 = _hlslpp512_vec3_ps(m.vec);

#elif defined(HLSLPP_SIMD_REGISTER_256)

		n128 mvec0 = _hlslpp256_low_ps(m.vec0);
		n128 mvec1 = _hlslpp256_high_ps(m.vec0);
		n128 mvec2 = _hlslpp256_low_ps(m.vec1);
		n128 mvec3 = _hlslpp256_high_ps(m.vec1);

#else

		n128 mvec0 = m.vec0;
		n128 mvec1 = m.vec1;
		n128 mvec2 = m.vec2;
		n128 mvec3 = m.vec3;

#endif

		n128 shuf1 = _hlslpp_shuf_xyxx_ps(mvec0, mvec1); // x, y
		n128 shuf2 = _hlslpp_shuf_zwxx_ps(mvec2, mvec3); // 
		n128 sum1 = _hlslpp_add_ps(shuf1, shuf2); // x + z, y + w, _, _
		n128 t = _hlslpp_add_ps(sum1, _hlslpp_perm_yyyy_ps(sum1)); // x + y + z + w, _, _, _
		return float1(t);
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

	inline float4x4 transpose(const float4x4& m)
	{
#if defined(HLSLPP_SIMD_REGISTER_512)

		return float4x4(_hlslpp512_transpose4x4_ps(m.vec));

#elif defined(HLSLPP_SIMD_REGISTER_256)

		n256 o_vec0, o_vec1;
		_hlslpp256_transpose4x4_ps(m.vec0, m.vec1, o_vec0, o_vec1);
		return float4x4(o_vec0, o_vec1);

#else

		// From the Intel Intrinsics Guide _MM_TRANSPOSE4_PS
		n128 shuf_tmp_0 = _hlslpp_unpacklo_ps(m.vec0, m.vec1);
		n128 shuf_tmp_1 = _hlslpp_unpackhi_ps(m.vec0, m.vec1);
		n128 shuf_tmp_2 = _hlslpp_unpacklo_ps(m.vec2, m.vec3);
		n128 shuf_tmp_3 = _hlslpp_unpackhi_ps(m.vec2, m.vec3);

		n128 vec0 = _hlslpp_movelh_ps(shuf_tmp_0, shuf_tmp_2);
		n128 vec1 = _hlslpp_movehl_ps(shuf_tmp_2, shuf_tmp_0);
		n128 vec2 = _hlslpp_movelh_ps(shuf_tmp_1, shuf_tmp_3);
		n128 vec3 = _hlslpp_movehl_ps(shuf_tmp_3, shuf_tmp_1);

		return float4x4(vec0, vec1, vec2, vec3);

#endif
	}

	// These transpose functions just copy the data because the 1xM, Nx1, 2xM, Nx2, 3xM and Nx3 matrices are always laid out as rows
	// even if they're meant to represent columns.

	hlslpp_inline float1x1 transpose(const float1x1& m) { return float1x1(m.vec); }

	hlslpp_inline float1x2 transpose(const float2x1& m) { return float1x2(m.vec); }
	hlslpp_inline float2x1 transpose(const float1x2& m) { return float2x1(m.vec); }

	hlslpp_inline float1x3 transpose(const float3x1& m) { return float1x3(m.vec); }
	hlslpp_inline float3x1 transpose(const float1x3& m) { return float3x1(m.vec); }

	hlslpp_inline float1x4 transpose(const float4x1& m) { return float1x4(m.vec); }
	hlslpp_inline float4x1 transpose(const float1x4& m) { return float4x1(m.vec); }

	hlslpp_inline float2x3 transpose(const float3x2& m) { return float2x3(m.vec0, m.vec1); }
	hlslpp_inline float3x2 transpose(const float2x3& m) { return float3x2(m.vec0, m.vec1); }

	hlslpp_inline float2x4 transpose(const float4x2& m) { return float2x4(m.vec0, m.vec1); }
	hlslpp_inline float4x2 transpose(const float2x4& m) { return float4x2(m.vec0, m.vec1); }

	hlslpp_inline float3x4 transpose(const float4x3& m) { return float3x4(m.vec0, m.vec1, m.vec2); }
	hlslpp_inline float4x3 transpose(const float3x4& m) { return float4x3(m.vec0, m.vec1, m.vec2); }

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
		// Use the Laplace expansion to calculate the determinant in terms of 2x2 determinant multiplies instead of calculating
		// 3x3 determinants and then doing a dot product. https://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf

#if defined(HLSLPP_SIMD_REGISTER_512)

		n512 mul_a0_12 = _hlslpp512_perm_ps(m.vec,  0,  0,  0,  1,  1,  2, 10,  9,  9,  8,  8,  8, 0, 0, 0, 0);
		n512 mul_a1_12 = _hlslpp512_perm_ps(m.vec,  5,  6,  7,  6,  7,  7, 15, 15, 14, 15, 14, 13, 0, 0, 0, 0);
		n512 mul_a2_12 = _hlslpp512_perm_ps(m.vec,  1,  2,  3,  2,  3,  3, 11, 11, 10, 11, 10,  9, 0, 0, 0, 0);
		n512 mul_a3_12 = _hlslpp512_perm_ps(m.vec,  4,  4,  4,  5,  5,  6, 14, 13, 13, 12, 12, 12, 0, 0, 0, 0);

		n512 det_mul_0 = _hlslpp512_mul_ps(mul_a0_12, mul_a1_12);
		n512 det_mul_1 = _hlslpp512_mul_ps(mul_a2_12, mul_a3_12);
		n512 det_sub_0 = _hlslpp512_sub_ps(det_mul_0, det_mul_1);

		n512 det_mul_3 = _hlslpp512_mul_ps(det_sub_0, _hlslpp512_perm_ps(det_sub_0, 6, 7, 8, 9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));

		static const uint32_t neg = 0x80000000u;
		n512 det_mul_3_s  = _hlslpp512_xor_ps(det_mul_3, _hlslpp512_castsi512_ps(_hlslpp512_set_epi32(0, neg, 0, 0, neg, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)));
		n512 det_mul_3_s1 = _hlslpp512_perm_ps(det_mul_3_s, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

		n128 det_add0 = _hlslpp_add_ps(_hlslpp512_vec0_ps(det_mul_3_s), _hlslpp512_vec0_ps(det_mul_3_s1));

		n128 det_add1 = _hlslpp_add_ps(det_add0, _hlslpp_perm_yyyy_ps(det_add0));
		n128 det_add_final = _hlslpp_add_ps(det_add1, _hlslpp_perm_zzzz_ps(det_add0));
 
		return float1(det_add_final);

#elif defined(HLSLPP_SIMD_REGISTER_256)

		// Extract low and high parts into n256 vectors
		n256 vec0_low  = _hlslpp256_low_low_ps(m.vec0, m.vec0);
		n256 vec0_high = _hlslpp256_high_high_ps(m.vec0, m.vec0);
		n256 vec1_low  = _hlslpp256_low_low_ps(m.vec1, m.vec1);
		n256 vec1_high = _hlslpp256_high_high_ps(m.vec1, m.vec1);

		n256 tmp_shuf_0_2 = _hlslpp256_perm_xzxy_badc_ps(vec0_low);
		n256 tmp_shuf_1_3 = _hlslpp256_perm_yxwz_acab_ps(vec0_high);
		n256 tmp_shuf_4_6 = _hlslpp256_perm_zyyx_ddcd_ps(vec1_low);
		n256 tmp_shuf_5_7 = _hlslpp256_perm_wwzw_cbba_ps(vec1_high);

		n256 tmp_mul_01_23 = _hlslpp256_mul_ps(tmp_shuf_0_2, tmp_shuf_1_3);
		n256 tmp_mul_45_67 = _hlslpp256_mul_ps(tmp_shuf_4_6, tmp_shuf_5_7);

		n256 tmp_shuf_sub0 = _hlslpp256_low_low_ps(tmp_mul_01_23, tmp_mul_45_67);
		n256 tmp_shuf_sub1 = _hlslpp256_high_high_ps(tmp_mul_01_23, tmp_mul_45_67);

		n256 tmp_sub0 = _hlslpp256_sub_ps(tmp_shuf_sub0, tmp_shuf_sub1);
		 
		n256 vec0_vec1_low  = _hlslpp256_low_low_ps(m.vec0, m.vec1);
		n256 vec0_vec1_high  = _hlslpp256_high_high_ps(m.vec0, m.vec1);

		n256 tmp_shuf_8_10 = _hlslpp256_perm_wzyw_aacb_ps(vec0_vec1_low);
 		n256 tmp_shuf_9_11 = _hlslpp256_perm_ywwz_cbaa_ps(vec0_vec1_high);

		n256 tmp_mul_89_1011 = _hlslpp256_mul_ps(tmp_shuf_8_10, tmp_shuf_9_11);
		n256 tmp_perm_89_1011 = _hlslpp256_perm_zwxx_cdaa_ps(tmp_mul_89_1011);
		n256 tmp_sub1 = _hlslpp256_sub_ps(tmp_mul_89_1011, tmp_perm_89_1011);

		n256 tmp_sub0_sub1_low = _hlslpp256_low_low_ps(tmp_sub0, tmp_sub1);
		n256 tmp_sub0_sub1_high = _hlslpp256_high_high_ps(tmp_sub0, tmp_sub1);

		n256 tmp_mul_final = _hlslpp256_mul_ps(tmp_sub0_sub1_low, tmp_sub0_sub1_high);

		// The sum of the first 6 values is the determinant
		n256 tmp_add_6_0 = _hlslpp256_hadd_ps(tmp_mul_final, tmp_mul_final);

		n128 tmp_add_6_0_low = _hlslpp256_low_ps(tmp_add_6_0);
		n128 tmp_add_6_0_high = _hlslpp256_high_ps(tmp_add_6_0);

		n128 tmp_final_add_1 = _hlslpp_add_ps(tmp_add_6_0_low, _hlslpp_perm_yyyy_ps(tmp_add_6_0_low));
		n128 tmp_final_add_2 = _hlslpp_add_ps(tmp_final_add_1, tmp_add_6_0_high);

		return float1(tmp_final_add_2);

#else

		n128 tmp_shuf_0 = _hlslpp_perm_xzxy_ps(m.vec0);
		n128 tmp_shuf_1 = _hlslpp_perm_yxwz_ps(m.vec1);
		n128 tmp_shuf_2 = _hlslpp_perm_yxwz_ps(m.vec0);
		n128 tmp_shuf_3 = _hlslpp_perm_xzxy_ps(m.vec1);

		n128 tmp_shuf_4 = _hlslpp_perm_zyyx_ps(m.vec2);
		n128 tmp_shuf_5 = _hlslpp_perm_wwzw_ps(m.vec3);
		n128 tmp_shuf_6 = _hlslpp_perm_wwzw_ps(m.vec2);
		n128 tmp_shuf_7 = _hlslpp_perm_zyyx_ps(m.vec3);

		n128 tmp_4_terms = _hlslpp_mul_ps
		(
			_hlslpp_sub_ps(_hlslpp_mul_ps(tmp_shuf_0, tmp_shuf_1), _hlslpp_mul_ps(tmp_shuf_2, tmp_shuf_3)),
			_hlslpp_sub_ps(_hlslpp_mul_ps(tmp_shuf_4, tmp_shuf_5), _hlslpp_mul_ps(tmp_shuf_6, tmp_shuf_7))
		);

		n128 tmp_shuf_8  = _hlslpp_shuf_wzxx_ps(m.vec0, m.vec2);
		n128 tmp_shuf_9  = _hlslpp_shuf_ywzy_ps(m.vec1, m.vec3);
		n128 tmp_shuf_10 = _hlslpp_shuf_ywzy_ps(m.vec0, m.vec2);
		n128 tmp_shuf_11 = _hlslpp_shuf_wzxx_ps(m.vec1, m.vec3);

		n128 tmp_mul_0 = _hlslpp_sub_ps
		(
			_hlslpp_mul_ps(tmp_shuf_8, tmp_shuf_9), 
			_hlslpp_mul_ps(tmp_shuf_10, tmp_shuf_11)
		);

		n128 tmp_2_terms = _hlslpp_mul_ps
		(
			_hlslpp_perm_xyxy_ps(tmp_mul_0), 
			_hlslpp_perm_zwzw_ps(tmp_mul_0)
		);

		// Add all the results now (terms that subtract have already been inverted)
		n128 tmp_add_0 = _hlslpp_add_ps(_hlslpp_shuf_xzxx_ps(tmp_4_terms, tmp_2_terms), _hlslpp_shuf_ywyy_ps(tmp_4_terms, tmp_2_terms));
		n128 tmp_add_1 = _hlslpp_add_ps(_hlslpp_perm_xxxx_ps(tmp_add_0), _hlslpp_perm_yyyy_ps(tmp_add_0));
		n128 tmp_add_2 = _hlslpp_add_ps(_hlslpp_perm_xxxx_ps(tmp_add_1), _hlslpp_perm_zzzz_ps(tmp_add_0));

		return float1(tmp_add_2);

#endif
	}

	hlslpp_inline float2x2 inverse(const float2x2& m)
	{
		return float2x2(_hlslpp_inv_2x2_ps(m.vec));
	}

	hlslpp_inline  float3x3 inverse(const float3x3& m)
	{
		n128 vec0, vec1, vec2;
		_hlslpp_inv_3x3_ps(m.vec0, m.vec1, m.vec2, vec0, vec1, vec2);
		return float3x3(vec0, vec1, vec2);
	}

	hlslpp_inline float4x4 inverse(const float4x4& m)
	{
		// For AVX, trying to convert the SSE implementation results in many wide shuffles and combinations
		// that result in a slower algorithm. In fact, this straightforward approach is actually faster than
		// SSE if AVX is enabled.

#if defined(HLSLPP_SIMD_REGISTER_512)

		n128 mvec0 = _hlslpp512_vec0_ps(m.vec);
		n128 mvec1 = _hlslpp512_vec1_ps(m.vec);
		n128 mvec2 = _hlslpp512_vec2_ps(m.vec);
		n128 mvec3 = _hlslpp512_vec3_ps(m.vec);

#elif defined(HLSLPP_SIMD_REGISTER_256)

		n128 mvec0 = _hlslpp256_low_ps(m.vec0);
		n128 mvec1 = _hlslpp256_high_ps(m.vec0);
		n128 mvec2 = _hlslpp256_low_ps(m.vec1);
		n128 mvec3 = _hlslpp256_high_ps(m.vec1);

#else

		n128 mvec0 = m.vec0;
		n128 mvec1 = m.vec1;
		n128 mvec2 = m.vec2;
		n128 mvec3 = m.vec3;

#endif

		n128 vec0, vec1, vec2, vec3;
		_hlslpp_inv_4x4_ps(mvec0, mvec1, mvec2, mvec3, vec0, vec1, vec2, vec3);

#if defined(HLSLPP_SIMD_REGISTER_512)
		return float4x4(_hlslpp512_set128_ps(vec0, vec1, vec2, vec3));
#elif defined(HLSLPP_SIMD_REGISTER_256)
		return float4x4(_hlslpp256_set128_ps(vec0, vec1), _hlslpp256_set128_ps(vec2, vec3));
#else
		return float4x4(vec0, vec1, vec2, vec3);
#endif
	}
}