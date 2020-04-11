#include "hlsl++.h"

#include "hlsl++_unit_tests.h"

const float deg2rad = 3.14159265f / 180.0f;

void RunUnitTestsVectorInt()
{
	using namespace hlslpp_unit;

	// Integer

	int32_t i1 = (rand() % 1000); int32_t i5 = (rand() % 1000); int32_t i9 = (rand() % 1000); int32_t i13 = (rand() % 1000); int32_t i17 = (rand() % 1000);
	int32_t i2 = (rand() % 1000); int32_t i6 = (rand() % 1000); int32_t i10 = (rand() % 1000); int32_t i14 = (rand() % 1000); int32_t i18 = (rand() % 1000);
	int32_t i3 = (rand() % 1000); int32_t i7 = (rand() % 1000); int32_t i11 = (rand() % 1000); int32_t i15 = (rand() % 1000); int32_t i19 = (rand() % 1000);
	int32_t i4 = (rand() % 1000); int32_t i8 = (rand() % 1000); int32_t i12 = (rand() % 1000); int32_t i16 = (rand() % 1000); int32_t i20 = (rand() % 1000);

	int1 ivfoo1 = int1(i1);										eq(ivfoo1, i1);
	int2 ivfoo2 = int2(i2, i3);									eq(ivfoo2, i2, i3);
	int3 ivfoo3 = int3(i4, i5, i6);								eq(ivfoo3, i4, i5, i6);
	int4 ivfoo4 = int4(i7, i8, i9, i10);						eq(ivfoo4, i7, i8, i9, i10);

	int1 ivfoo_dc_1;
	int2 ivfoo_dc_2;
	int3 ivfoo_dc_3;
	int4 ivfoo_dc_4;

	ivfoo1 = int1(i1);											eq(ivfoo1, i1);
	ivfoo2 = int2(i2, i3);										eq(ivfoo2, i2, i3);
	ivfoo3 = int3(i4, i5, i6);									eq(ivfoo3, i4, i5, i6);
	ivfoo4 = int4(i7, i8, i9, i10);								eq(ivfoo4, i7, i8, i9, i10);

	int1 ivbar1 = ivfoo1.x;										eq(ivbar1, i1);
	int2 ivbar2 = ivfoo2.gr;									eq(ivbar2, i3, i2);
	int3 ivbar3 = ivfoo3.zyx;									eq(ivbar3, i6, i5, i4);
	int4 ivbar4 = ivfoo4.bgra;									eq(ivbar4, i9, i8, i7, i10);

	ivbar1 = i11;												eq(ivbar1, i11);
	ivbar2 = int2(i12, i13);									eq(ivbar2, i12, i13);
	ivbar3 = int3(i14, i15, i16);								eq(ivbar3, i14, i15, i16);
	ivbar4 = int4(i17, i18, i19, i20);							eq(ivbar4, i17, i18, i19, i20);

	int1 ivbaz1 = int1(2);										eq(ivbaz1, 2);
	int2 ivbaz2 = int2(3, 7);									eq(ivbaz2, 3, 7);
	int3 ivbaz3 = int3(1, 4, 8);								eq(ivbaz3, 1, 4, 8);
	int4 ivbaz4 = int4(0, 2, 6, 10);							eq(ivbaz4, 0, 2, 6, 10);

	int2 ivfoo_mix_2_a = int2(ivfoo1, ivbar1);					eq(ivfoo_mix_2_a, ivfoo1, ivbar1);
	int2 ivfoo_mix_2_b = int2(ivfoo2.y, ivbar1);				eq(ivfoo_mix_2_b, ivfoo2.y, ivbar1);
	int2 ivfoo_mix_2_c = int2(ivfoo1, ivbar1.x);				eq(ivfoo_mix_2_c, ivfoo1, ivbar1.x);
	int2 ivfoo_mix_2_d = int2(ivfoo1.x, ivbar2.y);				eq(ivfoo_mix_2_d, ivfoo1.x, ivbar2.y);

	int2 ivfoo_mix_2_f_a = int2(ivfoo1, i1);					eq(ivfoo_mix_2_f_a, ivfoo1.x, i1);
	int2 ivfoo_mix_2_f_b = int2(i2, ivbar1);					eq(ivfoo_mix_2_f_b, i2, ivbar1);
	int2 ivfoo_mix_2_f_c = int2(ivfoo2.y, i1);					eq(ivfoo_mix_2_f_c, ivfoo2.y, i1);
	int2 ivfoo_mix_2_f_d = int2(i2, ivbar3.z);					eq(ivfoo_mix_2_f_d, i2, ivbar3.z);
	int2 ivfoo_mix_2_f_e = int2(i3, i4);						eq(ivfoo_mix_2_f_e, i3, i4);

	int3 ivfoo_mix_3_a = int3(ivfoo1, ivbar1, ivbaz1);			eq(ivfoo_mix_3_a, ivfoo1.x, ivbar1.x, ivbaz1.x);
	int3 ivfoo_mix_3_b = int3(ivfoo2, ivbar1);					eq(ivfoo_mix_3_b, ivfoo2.x, ivfoo2.y, ivbar1.x);
	int3 ivfoo_mix_3_c = int3(ivbar1, ivbar2);					eq(ivfoo_mix_3_c, ivbar1.x, ivbar2.x, ivbar2.y);

	int3 ivfoo_mix_3_d = int3(ivfoo1, ivbar1, ivbaz1.x);		eq(ivfoo_mix_3_d, ivfoo1.x, ivbar1.x, ivbaz1.x);
	int3 ivfoo_mix_3_e = int3(ivfoo1, ivbar1.x, ivbaz1);		eq(ivfoo_mix_3_e, ivfoo1.x, ivbar1.x, ivbaz1.x);
	int3 ivfoo_mix_3_f = int3(ivfoo1.x, ivbar1, ivbaz1);		eq(ivfoo_mix_3_f, ivfoo1.x, ivbar1.x, ivbaz1.x);

	int3 ivfoo_mix_3_g = int3(ivfoo1, ivbar1.x, ivbaz1.x);		eq(ivfoo_mix_3_g, ivfoo1.x, ivbar1.x, ivbaz1.x);
	int3 ivfoo_mix_3_h = int3(ivfoo1.x, ivbar1, ivbaz1.x);		eq(ivfoo_mix_3_h, ivfoo1.x, ivbar1.x, ivbaz1.x);
	int3 ivfoo_mix_3_i = int3(ivfoo1.x, ivbar1.x, ivbaz1);		eq(ivfoo_mix_3_i, ivfoo1.x, ivbar1.x, ivbaz1.x);
	int3 ivfoo_mix_3_j = int3(ivfoo1.x, ivbar1.x, ivbaz1.x);	eq(ivfoo_mix_3_j, ivfoo1.x, ivbar1.x, ivbaz1.x);

	int3 ivfoo_mix_3_f_a = int3(ivfoo1, ivbar1, i1);			eq(ivfoo_mix_3_f_a, ivfoo1.x, ivbar1.x, i1);
	int3 ivfoo_mix_3_f_b = int3(ivfoo1, i1, ivbaz1);			eq(ivfoo_mix_3_f_b, ivfoo1.x, i1, ivbaz1.x);
	int3 ivfoo_mix_3_f_c = int3(i1, ivbar1, ivbaz1);			eq(ivfoo_mix_3_f_c, i1, ivbar1.x, ivbaz1.x);

	int3 ivfoo_mix_3_f_d = int3(ivfoo1, i1, i2);				eq(ivfoo_mix_3_f_d, ivfoo1.x, i1, i2);
	int3 ivfoo_mix_3_f_e = int3(i1, ivbar1, i2);				eq(ivfoo_mix_3_f_e, i1, ivbar1.x, i2);
	int3 ivfoo_mix_3_f_f = int3(i1, i2, ivbaz1);				eq(ivfoo_mix_3_f_f, i1, i2, ivbaz1);

	int3 ivfoo_mix_3_f_g = int3(ivfoo1.x, i1, i2);				eq(ivfoo_mix_3_f_g, ivfoo1.x, i1, i2);
	int3 ivfoo_mix_3_f_h = int3(i1, ivbar2.y, i2);				eq(ivfoo_mix_3_f_h, i1, ivbar2.y, i2);
	int3 ivfoo_mix_3_f_i = int3(i1, i2, ivbaz3.z);				eq(ivfoo_mix_3_f_i, i1, i2, ivbaz3.z);

	int3 ivfoo_mix_3_f_j = int3(ivfoo1.x, ivbar2.y, i2);		eq(ivfoo_mix_3_f_j, ivfoo1.x, ivbar2.y, i2);
	int3 ivfoo_mix_3_f_k = int3(i1, ivbar2.y, ivbaz3.x);		eq(ivfoo_mix_3_f_k, i1, ivbar2.y, ivbaz3.x);
	int3 ivfoo_mix_3_f_l = int3(ivfoo1.x, i2, ivbaz3.z);		eq(ivfoo_mix_3_f_l, ivfoo1.x, i2, ivbaz3.z);

	int3 ivfoo_mix_3_f_m = int3(ivfoo2, i1);					eq(ivfoo_mix_3_f_m, ivfoo2.x, ivfoo2.y, i1);
	int3 ivfoo_mix_3_f_n = int3(i2, ivbar2);					eq(ivfoo_mix_3_f_n, i2, ivbar2.x, ivbar2.y);

	int3 ivfoo_mix_3_f_o = int3(ivfoo2.xy, i1);					eq(ivfoo_mix_3_f_o, ivfoo2.x, ivfoo2.y, i1);
	int3 ivfoo_mix_3_f_p = int3(i2, ivbar2.xy);					eq(ivfoo_mix_3_f_p, i2, ivbar2.x, ivbar2.y);

	int4 ivfoo_mix_4_a = int4(ivbaz1, ivbaz2.x, ivbaz3.x, 5);		eq(ivfoo_mix_4_a, ivbaz1.x, ivbaz2.x, ivbaz3.x, 5);
	int4 ivfoo_mix_4_b = int4(ivbaz1, ivbaz3);						eq(ivfoo_mix_4_b, ivbaz1.x, ivbaz3.x, ivbaz3.y, ivbaz3.z);
	int4 ivfoo_mix_4_c = int4(ivbaz3, ivbaz1);						eq(ivfoo_mix_4_c, ivbaz3.x, ivbaz3.y, ivbaz3.z, ivbaz1.x);
	int4 ivfoo_mix_4_d = int4(ivbaz2, ivbar2);						eq(ivfoo_mix_4_d, ivbaz2.x, ivbaz2.y, ivbar2.x, ivbar2.y);
	int4 ivfoo_mix_4_e = int4(ivbaz2, ivbar1, ivbaz1);				eq(ivfoo_mix_4_e, ivbaz2.x, ivbaz2.y, ivbar1.x, ivbaz1.x);
	int4 ivfoo_mix_4_f = int4(ivbar1, ivbaz2, ivbaz1);				eq(ivfoo_mix_4_f, ivbar1.x, ivbaz2.x, ivbaz2.y, ivbaz1.x);
	int4 ivfoo_mix_4_g = int4(ivbar1, ivbaz1, ivbaz2);				eq(ivfoo_mix_4_g, ivbar1.x, ivbaz1.x, ivbaz2.x, ivbaz2.y);

	int4 ivfoo_mix_4_f_a = int4(i1, ivfoo1, ivbar1, ivbaz1);		eq(ivfoo_mix_4_f_a, i1, ivfoo1, ivbar1, ivbaz1);
	int4 ivfoo_mix_4_f_b = int4(i2, i3, ivbar1, ivbaz1);			eq(ivfoo_mix_4_f_b, i2, i3, ivbar1, ivbaz1);
	int4 ivfoo_mix_4_f_c = int4(i4, i5, i6, ivbaz1);				eq(ivfoo_mix_4_f_c, i4, i5, i6, ivbaz1);

	int4 ivfoo_mix_4_f_d = int4(i1, ivfoo1.x, ivbar2.y, ivbaz3.z);	eq(ivfoo_mix_4_f_d, i1, ivfoo1, ivbar2.y, ivbaz3.z);
	int4 ivfoo_mix_4_f_e = int4(i2, i3, ivbar2.y, ivbaz3.z);		eq(ivfoo_mix_4_f_e, i2, i3, ivbar2.y, ivbaz3.z);
	int4 ivfoo_mix_4_f_f = int4(i4, i5, i6, ivbaz3.z);				eq(ivfoo_mix_4_f_f, i4, i5, i6, ivbaz3.z);

	int4 ivfoo_mix_4_f_g = int4(i1, ivfoo1, ivbar2.y, ivbaz3.z);	eq(ivfoo_mix_4_f_g, i1, ivfoo1, ivbar2.y, ivbaz3.z);
	int4 ivfoo_mix_4_f_h = int4(i2, ivfoo1, ivbar1, ivbaz3.z);		eq(ivfoo_mix_4_f_h, i2, ivfoo1, ivbar1, ivbaz3.z);
	int4 ivfoo_mix_4_f_i = int4(i3, ivfoo1.x, ivbar1, ivbaz3.z);	eq(ivfoo_mix_4_f_i, i3, ivfoo1.x, ivbar1, ivbaz3.z);
	int4 ivfoo_mix_4_f_j = int4(i4, ivfoo1.x, ivbar2.y, ivbaz1);	eq(ivfoo_mix_4_f_j, i4, ivfoo1.x, ivbar2.y, ivbaz1);

	int4 ivfoo_mix_4_f_k = int4(i1, i2, ivbar1, ivbaz3.z);			eq(ivfoo_mix_4_f_k, i1, i2, ivbar1, ivbaz3.z);
	int4 ivfoo_mix_4_f_l = int4(i3, i4, ivbar2.y, ivbaz1);			eq(ivfoo_mix_4_f_l, i3, i4, ivbar2.y, ivbaz1);

	// Assignment and swizzle

	int1 ivassign1 = ivfoo1.x;										eq(ivassign1.x, ivfoo1.x);
	ivassign1 = ivfoo1.r;											eq(ivassign1.x, ivfoo1.x);
	ivassign1.r = ivfoo1;											eq(ivassign1.x, ivfoo1.x);
	ivassign1.r = ivfoo1.r;											eq(ivassign1.x, ivfoo1.x);

	int2 ivassign2 = ivfoo2.yx;										eq(ivassign2, ivfoo2.y, ivfoo2.x);
	ivassign2 = ivfoo2.yy;											eq(ivassign2, ivfoo2.y, ivfoo2.y);
	ivassign2.rg = ivfoo2;											eq(ivassign2, ivfoo2.x, ivfoo2.y);
	ivassign2.rg = ivfoo2.gr;										eq(ivassign2, ivfoo2.y, ivfoo2.x);

	int3 ivassign3 = ivfoo3.yxz;									eq(ivassign3, ivfoo3.y, ivfoo3.x, ivfoo3.z);
	ivassign3 = ivfoo3.yyx;											eq(ivassign3, ivfoo3.y, ivfoo3.y, ivfoo3.x);
	ivassign3.rbg = ivfoo3;											eq(ivassign3, ivfoo3.x, ivfoo3.z, ivfoo3.y);
	ivassign3.rgb = ivfoo3.grr;										eq(ivassign3, ivfoo3.y, ivfoo3.x, ivfoo3.x);

	int4 ivassign4 = ivfoo4.yxzw;									eq(ivassign4, ivfoo4.y, ivfoo4.x, ivfoo4.z, ivfoo4.w);
	ivassign4 = ivfoo4.yyxx;										eq(ivassign4, ivfoo4.y, ivfoo4.y, ivfoo4.x, ivfoo4.x);
	ivassign4.bgra = ivfoo4;										eq(ivassign4, ivfoo4.b, ivfoo4.g, ivfoo4.r, ivfoo4.a);
	ivassign4.rgba = ivfoo4.grba;									eq(ivassign4, ivfoo4.g, ivfoo4.r, ivfoo4.b, ivfoo4.a);

	//	int2 ivneg_swiz_2 = -ivfoo2.yx;									//assert(ivassign2.x == (int32_t)ivfoo2.y && ivassign2.y == (int32_t)ivfoo2.x);

		// Addition

	int1 ivadd1 = ivfoo1 + ivbar1;									eq(ivadd1, (int32_t)ivfoo1.x + (int32_t)ivbar1.x);
	int2 ivadd2 = ivfoo2 + ivbar2;									eq(ivadd2, (int32_t)ivfoo2.x + (int32_t)ivbar2.x, (int32_t)ivfoo2.y + (int32_t)ivbar2.y);
	int3 ivadd3 = ivfoo3 + ivbar3;									eq(ivadd3, (int32_t)ivfoo3.x + (int32_t)ivbar3.x, (int32_t)ivfoo3.y + (int32_t)ivbar3.y, (int32_t)ivfoo3.z + (int32_t)ivbar3.z);
	int4 ivadd4 = ivfoo4 + ivbar4;									eq(ivadd4, (int32_t)ivfoo4.x + (int32_t)ivbar4.x, (int32_t)ivfoo4.y + (int32_t)ivbar4.y, (int32_t)ivfoo4.z + (int32_t)ivbar4.z, (int32_t)ivfoo4.w + (int32_t)ivbar4.w);

	int1 ivadd_f_1 = ivfoo1 + 1;									eq(ivadd_f_1, (int32_t)ivfoo1.x + 1);
	int2 ivadd_f_2 = ivfoo2 + 2;									eq(ivadd_f_2, (int32_t)ivfoo2.x + 2, (int32_t)ivfoo2.y + 2);
	int3 ivadd_f_3 = ivfoo3 + 3;									eq(ivadd_f_3, (int32_t)ivfoo3.x + 3, (int32_t)ivfoo3.y + 3, (int32_t)ivfoo3.z + 3);
	int4 ivadd_f_4 = ivfoo4 + 4;									eq(ivadd_f_4, (int32_t)ivfoo4.x + 4, (int32_t)ivfoo4.y + 4, (int32_t)ivfoo4.z + 4, (int32_t)ivfoo4.w + 4);

	int1 ivadd_inv_f_1 = 1 + ivfoo1;								eq(ivadd_inv_f_1, (int32_t)ivfoo1.x + 1);
	int2 ivadd_inv_f_2 = 2 + ivfoo2;								eq(ivadd_inv_f_2, (int32_t)ivfoo2.x + 2, (int32_t)ivfoo2.y + 2);
	int3 ivadd_inv_f_3 = 3 + ivfoo3;								eq(ivadd_inv_f_3, (int32_t)ivfoo3.x + 3, (int32_t)ivfoo3.y + 3, (int32_t)ivfoo3.z + 3);
	int4 ivadd_inv_f_4 = 4 + ivfoo4;								eq(ivadd_inv_f_4, (int32_t)ivfoo4.x + 4, (int32_t)ivfoo4.y + 4, (int32_t)ivfoo4.z + 4, (int32_t)ivfoo4.w + 4);

	ivadd_f_1 += 1;													eq(ivadd_f_1, (int32_t)ivfoo1.x + 1 + 1);
	ivadd_f_2 += 2;													eq(ivadd_f_2, (int32_t)ivfoo2.x + 2 + 2, (int32_t)ivfoo2.y + 2 + 2);
	ivadd_f_3 += 3;													eq(ivadd_f_3, (int32_t)ivfoo3.x + 3 + 3, (int32_t)ivfoo3.y + 3 + 3, (int32_t)ivfoo3.z + 3 + 3);
	ivadd_f_4 += 4;													eq(ivadd_f_4, (int32_t)ivfoo4.x + 4 + 4, (int32_t)ivfoo4.y + 4 + 4, (int32_t)ivfoo4.z + 4 + 4, (int32_t)ivfoo4.w + 4 + 4);

	int1 ivadd_swiz_a_1 = ivfoo1 + ivbar1.x;						eq(ivadd_swiz_a_1, (int32_t)ivfoo1 + (int32_t)ivbar1.x);
	int1 ivadd_swiz_b_1 = ivfoo1.r + ivbar1.x;						eq(ivadd_swiz_b_1, (int32_t)ivfoo1.r + (int32_t)ivbar1.x);
	int1 ivadd_swiz_c_1 = ivfoo1.r + ivbar1;						eq(ivadd_swiz_c_1, (int32_t)ivfoo1.r + (int32_t)ivbar1);

	int2 ivadd_swiz_a_2 = ivfoo2 + ivbar2.yx;						eq(ivadd_swiz_a_2, (int32_t)ivfoo2.x + (int32_t)ivbar2.y, (int32_t)ivfoo2.y + (int32_t)ivbar2.x);
	int2 ivadd_swiz_b_2 = ivfoo2.gr + ivbar2.yx;					eq(ivadd_swiz_b_2, (int32_t)ivfoo2.g + (int32_t)ivbar2.y, (int32_t)ivfoo2.r + (int32_t)ivbar2.x);
	int2 ivadd_swiz_c_2 = ivfoo2.rg + ivbar2;						eq(ivadd_swiz_c_2, (int32_t)ivfoo2.r + (int32_t)ivbar2.x, (int32_t)ivfoo2.g + (int32_t)ivbar2.y);

	int3 ivadd_swiz_a_3 = ivfoo3 + ivbar3.yxz;						eq(ivadd_swiz_a_3, (int32_t)ivfoo3.x + (int32_t)ivbar3.y, (int32_t)ivfoo3.y + (int32_t)ivbar3.x, (int32_t)ivfoo3.z + (int32_t)ivbar3.z);
	int3 ivadd_swiz_b_3 = ivfoo3.bgr + ivbar3.xyz;					eq(ivadd_swiz_b_3, (int32_t)ivfoo3.b + (int32_t)ivbar3.x, (int32_t)ivfoo3.g + (int32_t)ivbar3.y, (int32_t)ivfoo3.r + (int32_t)ivbar3.z);
	int3 ivadd_swiz_c_3 = ivfoo3.bgr + ivbar3;						eq(ivadd_swiz_c_3, (int32_t)ivfoo3.b + (int32_t)ivbar3.x, (int32_t)ivfoo3.g + (int32_t)ivbar3.y, (int32_t)ivfoo3.r + (int32_t)ivbar3.z);

	int4 ivadd_swiz_a_4 = ivfoo4 + ivbar4.yxzw;						eq(ivadd_swiz_a_4, (int32_t)ivfoo4.x + (int32_t)ivbar4.y, (int32_t)ivfoo4.y + (int32_t)ivbar4.x, (int32_t)ivfoo4.z + (int32_t)ivbar4.z, (int32_t)ivfoo4.w + (int32_t)ivbar4.w);
	int4 ivadd_swiz_b_4 = ivfoo4.bgra + ivbar4.yxzw;				eq(ivadd_swiz_b_4, (int32_t)ivfoo4.b + (int32_t)ivbar4.y, (int32_t)ivfoo4.g + (int32_t)ivbar4.x, (int32_t)ivfoo4.r + (int32_t)ivbar4.z, (int32_t)ivfoo4.a + (int32_t)ivbar4.w);
	int4 ivadd_swiz_c_4 = ivfoo4.bgra + ivbar4;						eq(ivadd_swiz_c_4, (int32_t)ivfoo4.b + (int32_t)ivbar4.x, (int32_t)ivfoo4.g + (int32_t)ivbar4.y, (int32_t)ivfoo4.r + (int32_t)ivbar4.z, (int32_t)ivfoo4.a + (int32_t)ivbar4.w);

	ivadd_swiz_a_1 += ivfoo1;
	ivadd_swiz_b_1 += ivfoo1.x;
	ivadd_swiz_c_1.x += ivfoo1;
	ivadd_swiz_c_1.r += ivfoo1.r;

	ivadd_swiz_a_2 += ivfoo2;
	ivadd_swiz_b_2 += ivfoo2.xy;
	ivadd_swiz_c_2.xy += ivfoo2;
	ivadd_swiz_c_2.gr += ivfoo2.rg;

	// Subtraction

	int1 ivsub1 = ivfoo1 - ivbar1;									eq(ivsub1, (int32_t)ivfoo1.x - (int32_t)ivbar1.x);
	int2 ivsub2 = ivfoo2 - ivbar2;									eq(ivsub2, (int32_t)ivfoo2.x - (int32_t)ivbar2.x, (int32_t)ivfoo2.y - (int32_t)ivbar2.y);
	int3 ivsub3 = ivfoo3 - ivbar3;									eq(ivsub3, (int32_t)ivfoo3.x - (int32_t)ivbar3.x, (int32_t)ivfoo3.y - (int32_t)ivbar3.y, (int32_t)ivfoo3.z - (int32_t)ivbar3.z);
	int4 ivsub4 = ivfoo4 - ivbar4;									eq(ivsub4, (int32_t)ivfoo4.x - (int32_t)ivbar4.x, (int32_t)ivfoo4.y - (int32_t)ivbar4.y, (int32_t)ivfoo4.z - (int32_t)ivbar4.z, (int32_t)ivfoo4.w - (int32_t)ivbar4.w);

	int1 ivsub_f_1 = ivfoo1 - 1;									eq(ivsub_f_1, (int32_t)ivfoo1.x - 1);
	int2 ivsub_f_2 = ivfoo2 - 2;									eq(ivsub_f_2, (int32_t)ivfoo2.x - 2, (int32_t)ivfoo2.y - 2);
	int3 ivsub_f_3 = ivfoo3 - 3;									eq(ivsub_f_3, (int32_t)ivfoo3.x - 3, (int32_t)ivfoo3.y - 3, (int32_t)ivfoo3.z - 3);
	int4 ivsub_f_4 = ivfoo4 - 4;									eq(ivsub_f_4, (int32_t)ivfoo4.x - 4, (int32_t)ivfoo4.y - 4, (int32_t)ivfoo4.z - 4, (int32_t)ivfoo4.w - 4);

	ivsub_f_1 -= 1;													eq(ivsub_f_1, (int32_t)ivfoo1.x - 1 - 1);
	ivsub_f_2 -= 2;													eq(ivsub_f_2, (int32_t)ivfoo2.x - 2 - 2, (int32_t)ivfoo2.y - 2 - 2);
	ivsub_f_3 -= 3;													eq(ivsub_f_3, (int32_t)ivfoo3.x - 3 - 3, (int32_t)ivfoo3.y - 3 - 3, (int32_t)ivfoo3.z - 3 - 3);
	ivsub_f_4 -= 4;													eq(ivsub_f_4, (int32_t)ivfoo4.x - 4 - 4, (int32_t)ivfoo4.y - 4 - 4, (int32_t)ivfoo4.z - 4 - 4, (int32_t)ivfoo4.w - 4 - 4);

	int1 ivsub_swiz_a_1 = ivfoo1 - ivbar1.x;						eq(ivsub_swiz_a_1, (int32_t)ivfoo1 - (int32_t)ivbar1.x);
	int1 ivsub_swiz_b_1 = ivfoo1.r - ivbar1.x;						eq(ivsub_swiz_b_1, (int32_t)ivfoo1.r - (int32_t)ivbar1.x);
	int1 ivsub_swiz_c_1 = ivfoo1.r - ivbar1;						eq(ivsub_swiz_c_1, (int32_t)ivfoo1.r - (int32_t)ivbar1);
	ivsub_swiz_c_1.r = ivfoo4.r - ivbar4.r;

	int2 ivsub_swiz_a_2 = ivfoo2 - ivbar2.yx;						eq(ivsub_swiz_a_2, (int32_t)ivfoo2.x - (int32_t)ivbar2.y, (int32_t)ivfoo2.y - (int32_t)ivbar2.x);
	int2 ivsub_swiz_b_2 = ivfoo2.gr - ivbar2.yx;					eq(ivsub_swiz_b_2, (int32_t)ivfoo2.g - (int32_t)ivbar2.y, (int32_t)ivfoo2.r - (int32_t)ivbar2.x);
	int2 ivsub_swiz_c_2 = ivfoo2.rg - ivbar2;						eq(ivsub_swiz_c_2, (int32_t)ivfoo2.r - (int32_t)ivbar2.x, (int32_t)ivfoo2.g - (int32_t)ivbar2.y);
	ivsub_swiz_c_2.gr = ivfoo4.rg - ivbar4.gr;

	int3 ivsub_swiz_a_3 = ivfoo3 - ivbar3.yxz;						eq(ivsub_swiz_a_3, (int32_t)ivfoo3.x - (int32_t)ivbar3.y, (int32_t)ivfoo3.y - (int32_t)ivbar3.x, (int32_t)ivfoo3.z - (int32_t)ivbar3.z);
	int3 ivsub_swiz_b_3 = ivfoo3.bgr - ivbar3.xyz;					eq(ivsub_swiz_b_3, (int32_t)ivfoo3.b - (int32_t)ivbar3.x, (int32_t)ivfoo3.g - (int32_t)ivbar3.y, (int32_t)ivfoo3.r - (int32_t)ivbar3.z);
	int3 ivsub_swiz_c_3 = ivfoo3.bgr - ivbar3;						eq(ivsub_swiz_c_3, (int32_t)ivfoo3.b - (int32_t)ivbar3.x, (int32_t)ivfoo3.g - (int32_t)ivbar3.y, (int32_t)ivfoo3.r - (int32_t)ivbar3.z);
	ivsub_swiz_c_3.bgr = ivfoo4.grb - ivbar4.gbr;

	int4 ivsub_swiz_a_4 = ivfoo4 - ivbar4.yxzw;						eq(ivsub_swiz_a_4, (int32_t)ivfoo4.x - (int32_t)ivbar4.y, (int32_t)ivfoo4.y - (int32_t)ivbar4.x, (int32_t)ivfoo4.z - (int32_t)ivbar4.z, (int32_t)ivfoo4.w - (int32_t)ivbar4.w);
	int4 ivsub_swiz_b_4 = ivfoo4.bgra - ivbar4.yxzw;				eq(ivsub_swiz_b_4, (int32_t)ivfoo4.b - (int32_t)ivbar4.y, (int32_t)ivfoo4.g - (int32_t)ivbar4.x, (int32_t)ivfoo4.r - (int32_t)ivbar4.z, (int32_t)ivfoo4.a - (int32_t)ivbar4.w);
	int4 ivsub_swiz_c_4 = ivfoo4.bgra - ivbar4;						eq(ivsub_swiz_c_4, (int32_t)ivfoo4.b - (int32_t)ivbar4.x, (int32_t)ivfoo4.g - (int32_t)ivbar4.y, (int32_t)ivfoo4.r - (int32_t)ivbar4.z, (int32_t)ivfoo4.a - (int32_t)ivbar4.w);
	ivsub_swiz_c_4.bgra = ivfoo4.argb - ivbar4.ggbr;

	ivadd_swiz_a_1 -= ivfoo1;
	ivadd_swiz_b_1 -= ivfoo1.x;
	ivadd_swiz_c_1.x -= ivfoo1;
	ivadd_swiz_c_1.r -= ivfoo1.r;

	ivsub_swiz_a_2 -= ivfoo2;
	ivsub_swiz_b_2 -= ivfoo2.xy;
	ivsub_swiz_c_2.xy -= ivfoo2;
	ivsub_swiz_c_2.gr -= ivfoo2.rg;

	// Multiplication

	int1 ivmul1 = ivfoo1 * ivbar1;									eq(ivmul1, (int32_t)ivfoo1.x * (int32_t)ivbar1.x);
	int2 ivmul2 = ivfoo2 * ivbar2;									eq(ivmul2, (int32_t)ivfoo2.x * (int32_t)ivbar2.x, (int32_t)ivfoo2.y * (int32_t)ivbar2.y);
	int3 ivmul3 = ivfoo3 * ivbar3;									eq(ivmul3, (int32_t)ivfoo3.x * (int32_t)ivbar3.x, (int32_t)ivfoo3.y * (int32_t)ivbar3.y, (int32_t)ivfoo3.z * (int32_t)ivbar3.z);
	int4 ivmul4 = ivfoo4 * ivbar4;									eq(ivmul4, (int32_t)ivfoo4.x * (int32_t)ivbar4.x, (int32_t)ivfoo4.y * (int32_t)ivbar4.y, (int32_t)ivfoo4.z * (int32_t)ivbar4.z, (int32_t)ivfoo4.w * (int32_t)ivbar4.w);

	int1 ivmul_f_1 = ivfoo1 * 1;									eq(ivmul_f_1, (int32_t)ivfoo1.x * 1);
	int2 ivmul_f_2 = ivfoo2 * 2;									eq(ivmul_f_2, (int32_t)ivfoo2.x * 2, (int32_t)ivfoo2.y * 2);
	int3 ivmul_f_3 = ivfoo3 * 3;									eq(ivmul_f_3, (int32_t)ivfoo3.x * 3, (int32_t)ivfoo3.y * 3, (int32_t)ivfoo3.z * 3);
	int4 ivmul_f_4 = ivfoo4 * 4;									eq(ivmul_f_4, (int32_t)ivfoo4.x * 4, (int32_t)ivfoo4.y * 4, (int32_t)ivfoo4.z * 4, (int32_t)ivfoo4.w * 4);

	ivmul_f_1 *= 1;													eq(ivmul_f_1, (int32_t)ivfoo1.x * 1 * 1);
	ivmul_f_2 *= 2;													eq(ivmul_f_2, (int32_t)ivfoo2.x * 2 * 2, (int32_t)ivfoo2.y * 2 * 2);
	ivmul_f_3 *= 3;													eq(ivmul_f_3, (int32_t)ivfoo3.x * 3 * 3, (int32_t)ivfoo3.y * 3 * 3, (int32_t)ivfoo3.z * 3 * 3);
	ivmul_f_4 *= 4;													eq(ivmul_f_4, (int32_t)ivfoo4.x * 4 * 4, (int32_t)ivfoo4.y * 4 * 4, (int32_t)ivfoo4.z * 4 * 4, (int32_t)ivfoo4.w * 4 * 4);

	int1 ivmul_swiz_a_1 = ivfoo1 * ivbar1.x;
	int1 ivmul_swiz_b_1 = ivfoo1.r * ivbar1.x;
	int1 ivmul_swiz_c_1 = ivfoo1.r * ivbar1;

	int2 ivmul_swiz_a_2 = ivfoo2 * ivbar2.yx;
	int2 ivmul_swiz_b_2 = ivfoo2.gr * ivbar2.yx;
	int2 ivmul_swiz_c_2 = ivfoo2.rg * ivbar2;

	int3 ivmul_swiz_a_3 = ivfoo3 * ivbar3.yxz;
	int3 ivmul_swiz_b_3 = ivfoo3.rgb * ivbar3.xyz;
	int3 ivmul_swiz_c_3 = ivfoo3.bgr * ivbar3;

	int4 ivmul_swiz_a_4 = ivfoo4 * ivbar4.yxzw;
	int4 ivmul_swiz_b_4 = ivfoo4.bgra * ivbar4.yxzw;
	int4 ivmul_swiz_c_4 = ivfoo4.bgra * ivbar4;

	ivmul_swiz_a_2 *= ivfoo2;
	ivmul_swiz_b_2 *= ivfoo2.xy;
	ivmul_swiz_c_2.xy *= ivfoo2;
	ivmul_swiz_c_2.gr *= ivfoo2.rg;

	int1 vint = int1(1);
	int1 vint2 = int1(2);
	int1 vint3 = vint.r + vint2;
	vint.r = vint2.x;

	// Cast from float to int and viceversa

	float1 fcastfooi_1(ivfoo1);
	float2 fcastfooi_2(ivfoo2);
	float3 fcastfooi_3(ivfoo3);
	float4 fcastfooi_4(ivfoo4);

	fcastfooi_1 = ivfoo1;
	fcastfooi_2 = ivfoo2;
	fcastfooi_3 = ivfoo3;
	fcastfooi_4 = ivfoo4;

	float1 fcastbari_1 = ivfoo1;
	float2 fcastbari_2 = ivfoo2;
	float3 fcastbari_3 = ivfoo3;
	float4 fcastbari_4 = ivfoo4;

	// Bit shifting

	int1 ivshift_value_1 = int1(1);
	int2 ivshift_value_2 = int2(2, 3);
	int3 ivshift_value_3 = int3(1, 2, 4);
	int4 ivshift_value_4 = int4(2, 6, 3, 1);

	int1 ivshl_1 = ivfoo1 << ivshift_value_1; eq(ivshl_1, shift_left(ivfoo1.x, ivshift_value_1.x));
	int2 ivshl_2 = ivfoo2 << ivshift_value_2; eq(ivshl_2, shift_left(ivfoo2.x, ivshift_value_2.x), shift_left(ivfoo2.y, ivshift_value_2.y));
	int3 ivshl_3 = ivfoo3 << ivshift_value_3; eq(ivshl_3, shift_left(ivfoo3.x, ivshift_value_3.x), shift_left(ivfoo3.y, ivshift_value_3.y), shift_left(ivfoo3.z, ivshift_value_3.z));
	int4 ivshl_4 = ivfoo4 << ivshift_value_4; eq(ivshl_4, shift_left(ivfoo4.x, ivshift_value_4.x), shift_left(ivfoo4.y, ivshift_value_4.y), shift_left(ivfoo4.z, ivshift_value_4.z), shift_left(ivfoo4.w, ivshift_value_4.w));

	ivshl_2 = ivfoo2 << ivshift_value_1; eq(ivshl_2, shift_left(ivfoo2.x, ivshift_value_1.x), shift_left(ivfoo2.y, ivshift_value_1.x));
	ivshl_3 = ivfoo3 << ivshift_value_1; eq(ivshl_3, shift_left(ivfoo3.x, ivshift_value_1.x), shift_left(ivfoo3.y, ivshift_value_1.x), shift_left(ivfoo3.z, ivshift_value_1.x));
	ivshl_4 = ivfoo4 << ivshift_value_1; eq(ivshl_4, shift_left(ivfoo4.x, ivshift_value_1.x), shift_left(ivfoo4.y, ivshift_value_1.x), shift_left(ivfoo4.z, ivshift_value_1.x), shift_left(ivfoo4.w, ivshift_value_1.x));

	int1 ivshr_1 = ivfoo1 >> ivshift_value_1; eq(ivshr_1, shift_right(ivfoo1.x, ivshift_value_1.x));
	int2 ivshr_2 = ivfoo2 >> ivshift_value_2; eq(ivshr_2, shift_right(ivfoo2.x, ivshift_value_2.x), shift_right(ivfoo2.y, ivshift_value_2.y));
	int3 ivshr_3 = ivfoo3 >> ivshift_value_3; eq(ivshr_3, shift_right(ivfoo3.x, ivshift_value_3.x), shift_right(ivfoo3.y, ivshift_value_3.y), shift_right(ivfoo3.z, ivshift_value_3.z));
	int4 ivshr_4 = ivfoo4 >> ivshift_value_4; eq(ivshr_4, shift_right(ivfoo4.x, ivshift_value_4.x), shift_right(ivfoo4.y, ivshift_value_4.y), shift_right(ivfoo4.z, ivshift_value_4.z), shift_right(ivfoo4.w, ivshift_value_4.w));

	ivshr_2 = ivfoo2 >> ivshift_value_1; eq(ivshr_2, shift_right(ivfoo2.x, ivshift_value_1.x), shift_right(ivfoo2.y, ivshift_value_1.x));
	ivshr_3 = ivfoo3 >> ivshift_value_1; eq(ivshr_3, shift_right(ivfoo3.x, ivshift_value_1.x), shift_right(ivfoo3.y, ivshift_value_1.x), shift_right(ivfoo3.z, ivshift_value_1.x));
	ivshr_4 = ivfoo4 >> ivshift_value_1; eq(ivshr_4, shift_right(ivfoo4.x, ivshift_value_1.x), shift_right(ivfoo4.y, ivshift_value_1.x), shift_right(ivfoo4.z, ivshift_value_1.x), shift_right(ivfoo4.w, ivshift_value_1.x));

	//	int4 sat4i = saturate(b);
	//
	//	int3 c = a + b.zzw;
	//	int2 d = int2(1, 3);
	//	int2 e = d.yx + b.zz;
	//	int2 f = d.yx - b.zz;
	//	int2 g = d.yx * b.zz;
	//
	//	int2 iabs2 = abs(g);
	//
	//	float4 ficast4 = ivfoo4;
	//	float3 ficast3 = ivfoo3;
	//	float2 ficast2 = ivfoo2;
	//	float1 ficast1 = ivfoo1;
	//
	//	ficast4 = ivfoo4;
	//	ficast3 = ivfoo3;
	//	ficast2 = ivfoo2;
	//	ficast1 = ivfoo1;
	//
	//	float4 ficast_swiz_4 = ivfoo4.xxwz;
	//	float3 ficast_swiz_3 = ivfoo3.zyx;
	//	float2 ficast_swiz_2 = ivfoo2.yy;
	//	float1 ficast_swiz_1 = ivfoo1.x;
	//
	//	ficast_swiz_4 = ivfoo4.xxwz;
	//	ficast_swiz_3 = ivfoo3.zyx;
	//	ficast_swiz_2 = ivfoo2.yy;
	//	ficast_swiz_1 = ivfoo1.x;
	//
	//	int4 ifcast4 = int4(ivfoo1.xx, vfoo2);
	//
	//	// Infinities and NaNs
	//
	//	//float4 inf = -float4::one() / float4::zero(); //assert(all(inf != inf).x != 0.0f);
	//	//float4 nan = sqrt(-float4::one());

	float f1 = (rand() % 1000) / 100.0f; float f5 = (rand() % 1000) / 100.0f; float f9 = (rand() % 1000) / 100.0f; //float f13 = (rand() % 1000) / 100.0f; float f17 = (rand() % 1000) / 100.0f;
	float f2 = (rand() % 1000) / 100.0f; float f6 = (rand() % 1000) / 100.0f; float f10 = (rand() % 1000) / 100.0f; //float f14 = (rand() % 1000) / 100.0f; float f18 = (rand() % 1000) / 100.0f;
	float f3 = (rand() % 1000) / 100.0f; float f7 = (rand() % 1000) / 100.0f; //float f11 = (rand() % 1000) / 100.0f; float f15 = (rand() % 1000) / 100.0f; float f19 = (rand() % 1000) / 100.0f;
	float f4 = (rand() % 1000) / 100.0f; float f8 = (rand() % 1000) / 100.0f; //float f12 = (rand() % 1000) / 100.0f; float f16 = (rand() % 1000) / 100.0f; float f20 = (rand() % 1000) / 100.0f;

	// Initialization

	float1 vfoo1 = float1(f1);					eq(vfoo1, f1);
	float2 vfoo2 = float2(f2, f3);				eq(vfoo2, f2, f3);
	float3 vfoo3 = float3(f4, f5, f6);			eq(vfoo3, f4, f5, f6);
	float4 vfoo4 = float4(f7, f8, f9, f10);		eq(vfoo4, f7, f8, f9, f10);

	vfoo1 = float1(i1);							eq(vfoo1, (float)i1);
	vfoo2 = float2(i2, i3);						eq(vfoo2, (float)i2, (float)i3);
	vfoo3 = float3(i4, i5, i6);					eq(vfoo3, (float)i4, (float)i5, (float)i6);
	vfoo4 = float4(i7, i8, i9, i10);			eq(vfoo4, (float)i7, (float)i8, (float)i9, (float)i10);

	vfoo2 = float2(i2, f3);						eq(vfoo2, (float)i2, (float)f3);
	vfoo3 = float3(f4, i5, i6);					eq(vfoo3, (float)f4, (float)i5, (float)i6);
	vfoo4 = float4(i7, i8, f9, f10);			eq(vfoo4, (float)i7, (float)i8, (float)f9, (float)f10);

	vfoo1 = float1(ivfoo1);						eq(vfoo1, (float)ivfoo1.x);
	vfoo2 = float2(ivfoo2);						eq(vfoo2, (float)ivfoo2.x, (float)ivfoo2.y);
	vfoo3 = float3(ivfoo3);						eq(vfoo3, (float)ivfoo3.x, (float)ivfoo3.y, (float)ivfoo3.z);
	vfoo4 = float4(ivfoo4);						eq(vfoo4, (float)ivfoo4.x, (float)ivfoo4.y, (float)ivfoo4.z, (float)ivfoo4.w);
}