#include "hlsl++/vector_int.h"
#include "hlsl++/vector_uint.h"
#include "hlsl++/dependent.h"

#include "unit_tests.h"

void RunUnitTestsVectorInt()
{
	using namespace hlslpp_unit;

	// Integer

	int32_t i1 = (rand() % 1000); int32_t i5 = (rand() % 1000); int32_t i9 = (rand() % 1000); int32_t i13 = (rand() % 1000); int32_t i17 = (rand() % 1000);
	int32_t i2 = (rand() % 1000); int32_t i6 = (rand() % 1000); int32_t i10 = (rand() % 1000); int32_t i14 = (rand() % 1000); int32_t i18 = (rand() % 1000);
	int32_t i3 = (rand() % 1000); int32_t i7 = (rand() % 1000); int32_t i11 = (rand() % 1000); int32_t i15 = (rand() % 1000); int32_t i19 = (rand() % 1000);
	int32_t i4 = (rand() % 1000); int32_t i8 = (rand() % 1000); int32_t i12 = (rand() % 1000); int32_t i16 = (rand() % 1000); int32_t i20 = (rand() % 1000);

	hlslpp_unit::BeginTest("Integer Initialization");

	int1 ivfoo1 = int1(i1);						hlslpp_check(eq(ivfoo1, i1));
	int2 ivfoo2 = int2(i2, i3);					hlslpp_check(eq(ivfoo2, i2, i3));
	int3 ivfoo3 = int3(i4, i5, i6);				hlslpp_check(eq(ivfoo3, i4, i5, i6));
	int4 ivfoo4 = int4(i7, i8, i9, i10);		hlslpp_check(eq(ivfoo4, i7, i8, i9, i10));

	int1 ivfoo_dc_1;
	int2 ivfoo_dc_2;
	int3 ivfoo_dc_3;
	int4 ivfoo_dc_4;

	ivfoo1 = int1(i1);											hlslpp_check(eq(ivfoo1, i1));
	ivfoo2 = int2(i2, i3);										hlslpp_check(eq(ivfoo2, i2, i3));
	ivfoo3 = int3(i4, i5, i6);									hlslpp_check(eq(ivfoo3, i4, i5, i6));
	ivfoo4 = int4(i7, i8, i9, i10);								hlslpp_check(eq(ivfoo4, i7, i8, i9, i10));

	int1 ivbar1 = ivfoo1.x;										hlslpp_check(eq(ivbar1, i1));
	int2 ivbar2 = ivfoo2.gr;									hlslpp_check(eq(ivbar2, i3, i2));
	int3 ivbar3 = ivfoo3.zyx;									hlslpp_check(eq(ivbar3, i6, i5, i4));
	int4 ivbar4 = ivfoo4.bgra;									hlslpp_check(eq(ivbar4, i9, i8, i7, i10));

	ivbar1 = i11;												hlslpp_check(eq(ivbar1, i11));
	ivbar2 = int2(i12, i13);									hlslpp_check(eq(ivbar2, i12, i13));
	ivbar3 = int3(i14, i15, i16);								hlslpp_check(eq(ivbar3, i14, i15, i16));
	ivbar4 = int4(i17, i18, i19, i20);							hlslpp_check(eq(ivbar4, i17, i18, i19, i20));

	int1 ivbaz1 = int1(2);										hlslpp_check(eq(ivbaz1, 2));
	int2 ivbaz2 = int2(3, 7);									hlslpp_check(eq(ivbaz2, 3, 7));
	int3 ivbaz3 = int3(1, 4, 8);								hlslpp_check(eq(ivbaz3, 1, 4, 8));
	int4 ivbaz4 = int4(0, 2, 6, 10);							hlslpp_check(eq(ivbaz4, 0, 2, 6, 10));

	int2 ivfoo_mix_2_a = int2(ivfoo1, ivbar1);					hlslpp_check(eq(ivfoo_mix_2_a, ivfoo1, ivbar1));
	int2 ivfoo_mix_2_b = int2(ivfoo2.y, ivbar1);				hlslpp_check(eq(ivfoo_mix_2_b, ivfoo2.y, ivbar1));
	int2 ivfoo_mix_2_c = int2(ivfoo1, ivbar1.x);				hlslpp_check(eq(ivfoo_mix_2_c, ivfoo1, ivbar1.x));
	int2 ivfoo_mix_2_d = int2(ivfoo1.x, ivbar2.y);				hlslpp_check(eq(ivfoo_mix_2_d, ivfoo1.x, ivbar2.y));

	int2 ivfoo_mix_2_f_a = int2(ivfoo1, i1);					hlslpp_check(eq(ivfoo_mix_2_f_a, ivfoo1.x, i1));
	int2 ivfoo_mix_2_f_b = int2(i2, ivbar1);					hlslpp_check(eq(ivfoo_mix_2_f_b, i2, ivbar1));
	int2 ivfoo_mix_2_f_c = int2(ivfoo2.y, i1);					hlslpp_check(eq(ivfoo_mix_2_f_c, ivfoo2.y, i1));
	int2 ivfoo_mix_2_f_d = int2(i2, ivbar3.z);					hlslpp_check(eq(ivfoo_mix_2_f_d, i2, ivbar3.z));
	int2 ivfoo_mix_2_f_e = int2(i3, i4);						hlslpp_check(eq(ivfoo_mix_2_f_e, i3, i4));

	int3 ivfoo_mix_3_a = int3(ivfoo1, ivbar1, ivbaz1);			hlslpp_check(eq(ivfoo_mix_3_a, ivfoo1.x, ivbar1.x, ivbaz1.x));
	int3 ivfoo_mix_3_b = int3(ivfoo2, ivbar1);					hlslpp_check(eq(ivfoo_mix_3_b, ivfoo2.x, ivfoo2.y, ivbar1.x));
	int3 ivfoo_mix_3_c = int3(ivbar1, ivbar2);					hlslpp_check(eq(ivfoo_mix_3_c, ivbar1.x, ivbar2.x, ivbar2.y));

	int3 ivfoo_mix_3_d = int3(ivfoo1, ivbar1, ivbaz1.x);		hlslpp_check(eq(ivfoo_mix_3_d, ivfoo1.x, ivbar1.x, ivbaz1.x));
	int3 ivfoo_mix_3_e = int3(ivfoo1, ivbar1.x, ivbaz1);		hlslpp_check(eq(ivfoo_mix_3_e, ivfoo1.x, ivbar1.x, ivbaz1.x));
	int3 ivfoo_mix_3_f = int3(ivfoo1.x, ivbar1, ivbaz1);		hlslpp_check(eq(ivfoo_mix_3_f, ivfoo1.x, ivbar1.x, ivbaz1.x));

	int3 ivfoo_mix_3_g = int3(ivfoo1, ivbar1.x, ivbaz1.x);		hlslpp_check(eq(ivfoo_mix_3_g, ivfoo1.x, ivbar1.x, ivbaz1.x));
	int3 ivfoo_mix_3_h = int3(ivfoo1.x, ivbar1, ivbaz1.x);		hlslpp_check(eq(ivfoo_mix_3_h, ivfoo1.x, ivbar1.x, ivbaz1.x));
	int3 ivfoo_mix_3_i = int3(ivfoo1.x, ivbar1.x, ivbaz1);		hlslpp_check(eq(ivfoo_mix_3_i, ivfoo1.x, ivbar1.x, ivbaz1.x));
	int3 ivfoo_mix_3_j = int3(ivfoo1.x, ivbar1.x, ivbaz1.x);	hlslpp_check(eq(ivfoo_mix_3_j, ivfoo1.x, ivbar1.x, ivbaz1.x));

	int3 ivfoo_mix_3_f_a = int3(ivfoo1, ivbar1, i1);			hlslpp_check(eq(ivfoo_mix_3_f_a, ivfoo1.x, ivbar1.x, i1));
	int3 ivfoo_mix_3_f_b = int3(ivfoo1, i1, ivbaz1);			hlslpp_check(eq(ivfoo_mix_3_f_b, ivfoo1.x, i1, ivbaz1.x));
	int3 ivfoo_mix_3_f_c = int3(i1, ivbar1, ivbaz1);			hlslpp_check(eq(ivfoo_mix_3_f_c, i1, ivbar1.x, ivbaz1.x));

	int3 ivfoo_mix_3_f_d = int3(ivfoo1, i1, i2);				hlslpp_check(eq(ivfoo_mix_3_f_d, ivfoo1.x, i1, i2));
	int3 ivfoo_mix_3_f_e = int3(i1, ivbar1, i2);				hlslpp_check(eq(ivfoo_mix_3_f_e, i1, ivbar1.x, i2));
	int3 ivfoo_mix_3_f_f = int3(i1, i2, ivbaz1);				hlslpp_check(eq(ivfoo_mix_3_f_f, i1, i2, ivbaz1));

	int3 ivfoo_mix_3_f_g = int3(ivfoo1.x, i1, i2);				hlslpp_check(eq(ivfoo_mix_3_f_g, ivfoo1.x, i1, i2));
	int3 ivfoo_mix_3_f_h = int3(i1, ivbar2.y, i2);				hlslpp_check(eq(ivfoo_mix_3_f_h, i1, ivbar2.y, i2));
	int3 ivfoo_mix_3_f_i = int3(i1, i2, ivbaz3.z);				hlslpp_check(eq(ivfoo_mix_3_f_i, i1, i2, ivbaz3.z));

	int3 ivfoo_mix_3_f_j = int3(ivfoo1.x, ivbar2.y, i2);		hlslpp_check(eq(ivfoo_mix_3_f_j, ivfoo1.x, ivbar2.y, i2));
	int3 ivfoo_mix_3_f_k = int3(i1, ivbar2.y, ivbaz3.x);		hlslpp_check(eq(ivfoo_mix_3_f_k, i1, ivbar2.y, ivbaz3.x));
	int3 ivfoo_mix_3_f_l = int3(ivfoo1.x, i2, ivbaz3.z);		hlslpp_check(eq(ivfoo_mix_3_f_l, ivfoo1.x, i2, ivbaz3.z));

	int3 ivfoo_mix_3_f_m = int3(ivfoo2, i1);					hlslpp_check(eq(ivfoo_mix_3_f_m, ivfoo2.x, ivfoo2.y, i1));
	int3 ivfoo_mix_3_f_n = int3(i2, ivbar2);					hlslpp_check(eq(ivfoo_mix_3_f_n, i2, ivbar2.x, ivbar2.y));

	int3 ivfoo_mix_3_f_o = int3(ivfoo2.xy, i1);					hlslpp_check(eq(ivfoo_mix_3_f_o, ivfoo2.x, ivfoo2.y, i1));
	int3 ivfoo_mix_3_f_p = int3(i2, ivbar2.xy);					hlslpp_check(eq(ivfoo_mix_3_f_p, i2, ivbar2.x, ivbar2.y));

	int4 ivfoo_mix_4_a = int4(ivbaz1, ivbaz2.x, ivbaz3.x, 5);		hlslpp_check(eq(ivfoo_mix_4_a, ivbaz1.x, ivbaz2.x, ivbaz3.x, 5));
	int4 ivfoo_mix_4_b = int4(ivbaz1, ivbaz3);						hlslpp_check(eq(ivfoo_mix_4_b, ivbaz1.x, ivbaz3.x, ivbaz3.y, ivbaz3.z));
	int4 ivfoo_mix_4_c = int4(ivbaz3, ivbaz1);						hlslpp_check(eq(ivfoo_mix_4_c, ivbaz3.x, ivbaz3.y, ivbaz3.z, ivbaz1.x));
	int4 ivfoo_mix_4_d = int4(ivbaz2, ivbar2);						hlslpp_check(eq(ivfoo_mix_4_d, ivbaz2.x, ivbaz2.y, ivbar2.x, ivbar2.y));
	int4 ivfoo_mix_4_e = int4(ivbaz2, ivbar1, ivbaz1);				hlslpp_check(eq(ivfoo_mix_4_e, ivbaz2.x, ivbaz2.y, ivbar1.x, ivbaz1.x));
	int4 ivfoo_mix_4_f = int4(ivbar1, ivbaz2, ivbaz1);				hlslpp_check(eq(ivfoo_mix_4_f, ivbar1.x, ivbaz2.x, ivbaz2.y, ivbaz1.x));
	int4 ivfoo_mix_4_g = int4(ivbar1, ivbaz1, ivbaz2);				hlslpp_check(eq(ivfoo_mix_4_g, ivbar1.x, ivbaz1.x, ivbaz2.x, ivbaz2.y));

	int4 ivfoo_mix_4_f_a = int4(i1, ivfoo1, ivbar1, ivbaz1);		hlslpp_check(eq(ivfoo_mix_4_f_a, i1, ivfoo1, ivbar1, ivbaz1));
	int4 ivfoo_mix_4_f_b = int4(i2, i3, ivbar1, ivbaz1);			hlslpp_check(eq(ivfoo_mix_4_f_b, i2, i3, ivbar1, ivbaz1));
	int4 ivfoo_mix_4_f_c = int4(i4, i5, i6, ivbaz1);				hlslpp_check(eq(ivfoo_mix_4_f_c, i4, i5, i6, ivbaz1));

	int4 ivfoo_mix_4_f_d = int4(i1, ivfoo1.x, ivbar2.y, ivbaz3.z);	hlslpp_check(eq(ivfoo_mix_4_f_d, i1, ivfoo1, ivbar2.y, ivbaz3.z));
	int4 ivfoo_mix_4_f_e = int4(i2, i3, ivbar2.y, ivbaz3.z);		hlslpp_check(eq(ivfoo_mix_4_f_e, i2, i3, ivbar2.y, ivbaz3.z));
	int4 ivfoo_mix_4_f_f = int4(i4, i5, i6, ivbaz3.z);				hlslpp_check(eq(ivfoo_mix_4_f_f, i4, i5, i6, ivbaz3.z));

	int4 ivfoo_mix_4_f_g = int4(i1, ivfoo1, ivbar2.y, ivbaz3.z);	hlslpp_check(eq(ivfoo_mix_4_f_g, i1, ivfoo1, ivbar2.y, ivbaz3.z));
	int4 ivfoo_mix_4_f_h = int4(i2, ivfoo1, ivbar1, ivbaz3.z);		hlslpp_check(eq(ivfoo_mix_4_f_h, i2, ivfoo1, ivbar1, ivbaz3.z));
	int4 ivfoo_mix_4_f_i = int4(i3, ivfoo1.x, ivbar1, ivbaz3.z);	hlslpp_check(eq(ivfoo_mix_4_f_i, i3, ivfoo1.x, ivbar1, ivbaz3.z));
	int4 ivfoo_mix_4_f_j = int4(i4, ivfoo1.x, ivbar2.y, ivbaz1);	hlslpp_check(eq(ivfoo_mix_4_f_j, i4, ivfoo1.x, ivbar2.y, ivbaz1));

	int4 ivfoo_mix_4_f_k = int4(i1, i2, ivbar1, ivbaz3.z);			hlslpp_check(eq(ivfoo_mix_4_f_k, i1, i2, ivbar1, ivbaz3.z));
	int4 ivfoo_mix_4_f_l = int4(i3, i4, ivbar2.y, ivbaz1);			hlslpp_check(eq(ivfoo_mix_4_f_l, i3, i4, ivbar2.y, ivbaz1));

	hlslpp_unit::EndTest();

	hlslpp_unit::BeginTest("Integer Assignment and Swizzle");

	int1 ivassign1 = ivfoo1.x;										hlslpp_check(eq(ivassign1.x, ivfoo1.x));
	ivassign1 = ivfoo1.r;											hlslpp_check(eq(ivassign1.x, ivfoo1.x));
	ivassign1.r = ivfoo1;											hlslpp_check(eq(ivassign1.x, ivfoo1.x));
	ivassign1.r = ivfoo1.r;											hlslpp_check(eq(ivassign1.x, ivfoo1.x));

	int2 ivassign2 = ivfoo2.yx;										hlslpp_check(eq(ivassign2, ivfoo2.y, ivfoo2.x));
	ivassign2 = ivfoo2.yy;											hlslpp_check(eq(ivassign2, ivfoo2.y, ivfoo2.y));
	ivassign2.rg = ivfoo2;											hlslpp_check(eq(ivassign2, ivfoo2.x, ivfoo2.y));
	ivassign2.rg = ivfoo2.gr;										hlslpp_check(eq(ivassign2, ivfoo2.y, ivfoo2.x));

	int3 ivassign3 = ivfoo3.yxz;									hlslpp_check(eq(ivassign3, ivfoo3.y, ivfoo3.x, ivfoo3.z));
	ivassign3 = ivfoo3.yyx;											hlslpp_check(eq(ivassign3, ivfoo3.y, ivfoo3.y, ivfoo3.x));
	ivassign3.rbg = ivfoo3;											hlslpp_check(eq(ivassign3, ivfoo3.x, ivfoo3.z, ivfoo3.y));
	ivassign3.rgb = ivfoo3.grr;										hlslpp_check(eq(ivassign3, ivfoo3.y, ivfoo3.x, ivfoo3.x));

	int4 ivassign4 = ivfoo4.yxzw;									hlslpp_check(eq(ivassign4, ivfoo4.y, ivfoo4.x, ivfoo4.z, ivfoo4.w));
	ivassign4 = ivfoo4.yyxx;										hlslpp_check(eq(ivassign4, ivfoo4.y, ivfoo4.y, ivfoo4.x, ivfoo4.x));
	ivassign4.bgra = ivfoo4;										hlslpp_check(eq(ivassign4, ivfoo4.b, ivfoo4.g, ivfoo4.r, ivfoo4.a));
	ivassign4.rgba = ivfoo4.grba;									hlslpp_check(eq(ivassign4, ivfoo4.g, ivfoo4.r, ivfoo4.b, ivfoo4.a));

	//	int2 ivneg_swiz_2 = -ivfoo2.yx;									//assert(ivassign2.x == (int32_t)ivfoo2.y && ivassign2.y == (int32_t)ivfoo2.x);

	hlslpp_unit::EndTest();

	hlslpp_unit::BeginTest("Integer Stomping Tests (Writing One Variable Stomping Others)");
	{
		ivassign2 = int2(i1, i2);
		ivassign2.r = ivfoo1.x;											hlslpp_check(eq(ivassign2, ivfoo1.x, i2));

		ivassign3 = int3(i1, i2, i3);
		ivassign3.rg = ivfoo3.rg;										hlslpp_check(eq(ivassign3, ivfoo3.r, ivfoo3.g, i3));

		ivassign3 = int3(i1, i2, i3);
		ivassign3.z = ivfoo3.z;											hlslpp_check(eq(ivassign3, i1, i2, ivfoo3.z));

		ivassign4 = int4(i1, i2, i3, i4);
		ivassign4.y = ivfoo4.y;											hlslpp_check(eq(ivassign4, i1, ivfoo4.y, i3, i4));
	}
	hlslpp_unit::EndTest();

	hlslpp_unit::BeginTest("Float Addition");
	{
		int1 ivadd1 = ivfoo1 + ivbar1;									hlslpp_check(eq(ivadd1, (int32_t)ivfoo1.x + (int32_t)ivbar1.x));
		int2 ivadd2 = ivfoo2 + ivbar2;									hlslpp_check(eq(ivadd2, (int32_t)ivfoo2.x + (int32_t)ivbar2.x, (int32_t)ivfoo2.y + (int32_t)ivbar2.y));
		int3 ivadd3 = ivfoo3 + ivbar3;									hlslpp_check(eq(ivadd3, (int32_t)ivfoo3.x + (int32_t)ivbar3.x, (int32_t)ivfoo3.y + (int32_t)ivbar3.y, (int32_t)ivfoo3.z + (int32_t)ivbar3.z));
		int4 ivadd4 = ivfoo4 + ivbar4;									hlslpp_check(eq(ivadd4, (int32_t)ivfoo4.x + (int32_t)ivbar4.x, (int32_t)ivfoo4.y + (int32_t)ivbar4.y, (int32_t)ivfoo4.z + (int32_t)ivbar4.z, (int32_t)ivfoo4.w + (int32_t)ivbar4.w));

		int1 ivadd_f_1 = ivfoo1 + 1;									hlslpp_check(eq(ivadd_f_1, (int32_t)ivfoo1.x + 1));
		int2 ivadd_f_2 = ivfoo2 + 2;									hlslpp_check(eq(ivadd_f_2, (int32_t)ivfoo2.x + 2, (int32_t)ivfoo2.y + 2));
		int3 ivadd_f_3 = ivfoo3 + 3;									hlslpp_check(eq(ivadd_f_3, (int32_t)ivfoo3.x + 3, (int32_t)ivfoo3.y + 3, (int32_t)ivfoo3.z + 3));
		int4 ivadd_f_4 = ivfoo4 + 4;									hlslpp_check(eq(ivadd_f_4, (int32_t)ivfoo4.x + 4, (int32_t)ivfoo4.y + 4, (int32_t)ivfoo4.z + 4, (int32_t)ivfoo4.w + 4));

		int1 ivadd_inv_f_1 = 1 + ivfoo1;								hlslpp_check(eq(ivadd_inv_f_1, (int32_t)ivfoo1.x + 1));
		int2 ivadd_inv_f_2 = 2 + ivfoo2;								hlslpp_check(eq(ivadd_inv_f_2, (int32_t)ivfoo2.x + 2, (int32_t)ivfoo2.y + 2));
		int3 ivadd_inv_f_3 = 3 + ivfoo3;								hlslpp_check(eq(ivadd_inv_f_3, (int32_t)ivfoo3.x + 3, (int32_t)ivfoo3.y + 3, (int32_t)ivfoo3.z + 3));
		int4 ivadd_inv_f_4 = 4 + ivfoo4;								hlslpp_check(eq(ivadd_inv_f_4, (int32_t)ivfoo4.x + 4, (int32_t)ivfoo4.y + 4, (int32_t)ivfoo4.z + 4, (int32_t)ivfoo4.w + 4));

		ivadd_f_1 += 1;													hlslpp_check(eq(ivadd_f_1, (int32_t)ivfoo1.x + 1 + 1));
		ivadd_f_2 += 2;													hlslpp_check(eq(ivadd_f_2, (int32_t)ivfoo2.x + 2 + 2, (int32_t)ivfoo2.y + 2 + 2));
		ivadd_f_3 += 3;													hlslpp_check(eq(ivadd_f_3, (int32_t)ivfoo3.x + 3 + 3, (int32_t)ivfoo3.y + 3 + 3, (int32_t)ivfoo3.z + 3 + 3));
		ivadd_f_4 += 4;													hlslpp_check(eq(ivadd_f_4, (int32_t)ivfoo4.x + 4 + 4, (int32_t)ivfoo4.y + 4 + 4, (int32_t)ivfoo4.z + 4 + 4, (int32_t)ivfoo4.w + 4 + 4));

		ivadd_f_2.y += 2;												hlslpp_check(eq(ivadd_f_2, (int32_t)ivfoo2.x + 2 + 2, (int32_t)ivfoo2.y + 2 + 2 + 2));
		ivadd_f_3.z += 3;												hlslpp_check(eq(ivadd_f_3, (int32_t)ivfoo3.x + 3 + 3, (int32_t)ivfoo3.y + 3 + 3, (int32_t)ivfoo3.z + 3 + 3 + 3));
		ivadd_f_4.w += 4;												hlslpp_check(eq(ivadd_f_4, (int32_t)ivfoo4.x + 4 + 4, (int32_t)ivfoo4.y + 4 + 4, (int32_t)ivfoo4.z + 4 + 4, (int32_t)ivfoo4.w + 4 + 4 + 4));

		int1 ivadd_swiz_a_1 = ivfoo1 + ivbar1.x;						hlslpp_check(eq(ivadd_swiz_a_1, (int32_t)ivfoo1 + (int32_t)ivbar1.x));
		int1 ivadd_swiz_b_1 = ivfoo1.r + ivbar1.x;						hlslpp_check(eq(ivadd_swiz_b_1, (int32_t)ivfoo1.r + (int32_t)ivbar1.x));
		int1 ivadd_swiz_c_1 = ivfoo1.r + ivbar1;						hlslpp_check(eq(ivadd_swiz_c_1, (int32_t)ivfoo1.r + (int32_t)ivbar1));

		int2 ivadd_swiz_a_2 = ivfoo2 + ivbar2.yx;						hlslpp_check(eq(ivadd_swiz_a_2, (int32_t)ivfoo2.x + (int32_t)ivbar2.y, (int32_t)ivfoo2.y + (int32_t)ivbar2.x));
		int2 ivadd_swiz_b_2 = ivfoo2.gr + ivbar2.yx;					hlslpp_check(eq(ivadd_swiz_b_2, (int32_t)ivfoo2.g + (int32_t)ivbar2.y, (int32_t)ivfoo2.r + (int32_t)ivbar2.x));
		int2 ivadd_swiz_c_2 = ivfoo2.rg + ivbar2;						hlslpp_check(eq(ivadd_swiz_c_2, (int32_t)ivfoo2.r + (int32_t)ivbar2.x, (int32_t)ivfoo2.g + (int32_t)ivbar2.y));

		int3 ivadd_swiz_a_3 = ivfoo3 + ivbar3.yxz;						hlslpp_check(eq(ivadd_swiz_a_3, (int32_t)ivfoo3.x + (int32_t)ivbar3.y, (int32_t)ivfoo3.y + (int32_t)ivbar3.x, (int32_t)ivfoo3.z + (int32_t)ivbar3.z));
		int3 ivadd_swiz_b_3 = ivfoo3.bgr + ivbar3.xyz;					hlslpp_check(eq(ivadd_swiz_b_3, (int32_t)ivfoo3.b + (int32_t)ivbar3.x, (int32_t)ivfoo3.g + (int32_t)ivbar3.y, (int32_t)ivfoo3.r + (int32_t)ivbar3.z));
		int3 ivadd_swiz_c_3 = ivfoo3.bgr + ivbar3;						hlslpp_check(eq(ivadd_swiz_c_3, (int32_t)ivfoo3.b + (int32_t)ivbar3.x, (int32_t)ivfoo3.g + (int32_t)ivbar3.y, (int32_t)ivfoo3.r + (int32_t)ivbar3.z));

		int4 ivadd_swiz_a_4 = ivfoo4 + ivbar4.yxzw;						hlslpp_check(eq(ivadd_swiz_a_4, (int32_t)ivfoo4.x + (int32_t)ivbar4.y, (int32_t)ivfoo4.y + (int32_t)ivbar4.x, (int32_t)ivfoo4.z + (int32_t)ivbar4.z, (int32_t)ivfoo4.w + (int32_t)ivbar4.w));
		int4 ivadd_swiz_b_4 = ivfoo4.bgra + ivbar4.yxzw;				hlslpp_check(eq(ivadd_swiz_b_4, (int32_t)ivfoo4.b + (int32_t)ivbar4.y, (int32_t)ivfoo4.g + (int32_t)ivbar4.x, (int32_t)ivfoo4.r + (int32_t)ivbar4.z, (int32_t)ivfoo4.a + (int32_t)ivbar4.w));
		int4 ivadd_swiz_c_4 = ivfoo4.bgra + ivbar4;						hlslpp_check(eq(ivadd_swiz_c_4, (int32_t)ivfoo4.b + (int32_t)ivbar4.x, (int32_t)ivfoo4.g + (int32_t)ivbar4.y, (int32_t)ivfoo4.r + (int32_t)ivbar4.z, (int32_t)ivfoo4.a + (int32_t)ivbar4.w));

		ivadd_swiz_a_1 += ivfoo1;
		ivadd_swiz_b_1 += ivfoo1.x;
		ivadd_swiz_c_1.x += ivfoo1;
		ivadd_swiz_c_1.r += ivfoo1.r;

		ivadd_swiz_a_2 += ivfoo2;
		ivadd_swiz_b_2 += ivfoo2.xy;
		ivadd_swiz_c_2.xy += ivfoo2;
		ivadd_swiz_c_2.gr += ivfoo2.rg;
	}
	hlslpp_unit::EndTest();

	hlslpp_unit::BeginTest("Integer Subtraction");
	{
		int1 ivsub1 = ivfoo1 - ivbar1;									hlslpp_check(eq(ivsub1, (int32_t)ivfoo1.x - (int32_t)ivbar1.x));
		int2 ivsub2 = ivfoo2 - ivbar2;									hlslpp_check(eq(ivsub2, (int32_t)ivfoo2.x - (int32_t)ivbar2.x, (int32_t)ivfoo2.y - (int32_t)ivbar2.y));
		int3 ivsub3 = ivfoo3 - ivbar3;									hlslpp_check(eq(ivsub3, (int32_t)ivfoo3.x - (int32_t)ivbar3.x, (int32_t)ivfoo3.y - (int32_t)ivbar3.y, (int32_t)ivfoo3.z - (int32_t)ivbar3.z));
		int4 ivsub4 = ivfoo4 - ivbar4;									hlslpp_check(eq(ivsub4, (int32_t)ivfoo4.x - (int32_t)ivbar4.x, (int32_t)ivfoo4.y - (int32_t)ivbar4.y, (int32_t)ivfoo4.z - (int32_t)ivbar4.z, (int32_t)ivfoo4.w - (int32_t)ivbar4.w));

		int1 ivsub_f_1 = ivfoo1 - 1;									hlslpp_check(eq(ivsub_f_1, (int32_t)ivfoo1.x - 1));
		int2 ivsub_f_2 = ivfoo2 - 2;									hlslpp_check(eq(ivsub_f_2, (int32_t)ivfoo2.x - 2, (int32_t)ivfoo2.y - 2));
		int3 ivsub_f_3 = ivfoo3 - 3;									hlslpp_check(eq(ivsub_f_3, (int32_t)ivfoo3.x - 3, (int32_t)ivfoo3.y - 3, (int32_t)ivfoo3.z - 3));
		int4 ivsub_f_4 = ivfoo4 - 4;									hlslpp_check(eq(ivsub_f_4, (int32_t)ivfoo4.x - 4, (int32_t)ivfoo4.y - 4, (int32_t)ivfoo4.z - 4, (int32_t)ivfoo4.w - 4));

		ivsub_f_1 -= 1;													hlslpp_check(eq(ivsub_f_1, (int32_t)ivfoo1.x - 1 - 1));
		ivsub_f_2 -= 2;													hlslpp_check(eq(ivsub_f_2, (int32_t)ivfoo2.x - 2 - 2, (int32_t)ivfoo2.y - 2 - 2));
		ivsub_f_3 -= 3;													hlslpp_check(eq(ivsub_f_3, (int32_t)ivfoo3.x - 3 - 3, (int32_t)ivfoo3.y - 3 - 3, (int32_t)ivfoo3.z - 3 - 3));
		ivsub_f_4 -= 4;													hlslpp_check(eq(ivsub_f_4, (int32_t)ivfoo4.x - 4 - 4, (int32_t)ivfoo4.y - 4 - 4, (int32_t)ivfoo4.z - 4 - 4, (int32_t)ivfoo4.w - 4 - 4));

		ivsub_f_2.y -= 2;												hlslpp_check(eq(ivsub_f_2, (int32_t)ivfoo2.x - 2 - 2, (int32_t)ivfoo2.y - 2 - 2 - 2));
		ivsub_f_3.z -= 3;												hlslpp_check(eq(ivsub_f_3, (int32_t)ivfoo3.x - 3 - 3, (int32_t)ivfoo3.y - 3 - 3, (int32_t)ivfoo3.z - 3 - 3 - 3));
		ivsub_f_4.w -= 4;												hlslpp_check(eq(ivsub_f_4, (int32_t)ivfoo4.x - 4 - 4, (int32_t)ivfoo4.y - 4 - 4, (int32_t)ivfoo4.z - 4 - 4, (int32_t)ivfoo4.w - 4 - 4 - 4));

		int1 ivsub_swiz_a_1 = ivfoo1 - ivbar1.x;						hlslpp_check(eq(ivsub_swiz_a_1, (int32_t)ivfoo1 - (int32_t)ivbar1.x));
		int1 ivsub_swiz_b_1 = ivfoo1.r - ivbar1.x;						hlslpp_check(eq(ivsub_swiz_b_1, (int32_t)ivfoo1.r - (int32_t)ivbar1.x));
		int1 ivsub_swiz_c_1 = ivfoo1.r - ivbar1;						hlslpp_check(eq(ivsub_swiz_c_1, (int32_t)ivfoo1.r - (int32_t)ivbar1));
		ivsub_swiz_c_1.r = ivfoo4.r - ivbar4.r;

		int2 ivsub_swiz_a_2 = ivfoo2 - ivbar2.yx;						hlslpp_check(eq(ivsub_swiz_a_2, (int32_t)ivfoo2.x - (int32_t)ivbar2.y, (int32_t)ivfoo2.y - (int32_t)ivbar2.x));
		int2 ivsub_swiz_b_2 = ivfoo2.gr - ivbar2.yx;					hlslpp_check(eq(ivsub_swiz_b_2, (int32_t)ivfoo2.g - (int32_t)ivbar2.y, (int32_t)ivfoo2.r - (int32_t)ivbar2.x));
		int2 ivsub_swiz_c_2 = ivfoo2.rg - ivbar2;						hlslpp_check(eq(ivsub_swiz_c_2, (int32_t)ivfoo2.r - (int32_t)ivbar2.x, (int32_t)ivfoo2.g - (int32_t)ivbar2.y));
		ivsub_swiz_c_2.gr = ivfoo4.rg - ivbar4.gr;

		int3 ivsub_swiz_a_3 = ivfoo3 - ivbar3.yxz;						hlslpp_check(eq(ivsub_swiz_a_3, (int32_t)ivfoo3.x - (int32_t)ivbar3.y, (int32_t)ivfoo3.y - (int32_t)ivbar3.x, (int32_t)ivfoo3.z - (int32_t)ivbar3.z));
		int3 ivsub_swiz_b_3 = ivfoo3.bgr - ivbar3.xyz;					hlslpp_check(eq(ivsub_swiz_b_3, (int32_t)ivfoo3.b - (int32_t)ivbar3.x, (int32_t)ivfoo3.g - (int32_t)ivbar3.y, (int32_t)ivfoo3.r - (int32_t)ivbar3.z));
		int3 ivsub_swiz_c_3 = ivfoo3.bgr - ivbar3;						hlslpp_check(eq(ivsub_swiz_c_3, (int32_t)ivfoo3.b - (int32_t)ivbar3.x, (int32_t)ivfoo3.g - (int32_t)ivbar3.y, (int32_t)ivfoo3.r - (int32_t)ivbar3.z));
		ivsub_swiz_c_3.bgr = ivfoo4.grb - ivbar4.gbr;

		int4 ivsub_swiz_a_4 = ivfoo4 - ivbar4.yxzw;						hlslpp_check(eq(ivsub_swiz_a_4, (int32_t)ivfoo4.x - (int32_t)ivbar4.y, (int32_t)ivfoo4.y - (int32_t)ivbar4.x, (int32_t)ivfoo4.z - (int32_t)ivbar4.z, (int32_t)ivfoo4.w - (int32_t)ivbar4.w));
		int4 ivsub_swiz_b_4 = ivfoo4.bgra - ivbar4.yxzw;				hlslpp_check(eq(ivsub_swiz_b_4, (int32_t)ivfoo4.b - (int32_t)ivbar4.y, (int32_t)ivfoo4.g - (int32_t)ivbar4.x, (int32_t)ivfoo4.r - (int32_t)ivbar4.z, (int32_t)ivfoo4.a - (int32_t)ivbar4.w));
		int4 ivsub_swiz_c_4 = ivfoo4.bgra - ivbar4;						hlslpp_check(eq(ivsub_swiz_c_4, (int32_t)ivfoo4.b - (int32_t)ivbar4.x, (int32_t)ivfoo4.g - (int32_t)ivbar4.y, (int32_t)ivfoo4.r - (int32_t)ivbar4.z, (int32_t)ivfoo4.a - (int32_t)ivbar4.w));
		ivsub_swiz_c_4.bgra = ivfoo4.argb - ivbar4.ggbr;

		ivsub_swiz_a_1 -= ivfoo1;
		ivsub_swiz_b_1 -= ivfoo1.x;
		ivsub_swiz_c_1.x -= ivfoo1;
		ivsub_swiz_c_1.r -= ivfoo1.r;

		ivsub_swiz_a_2 -= ivfoo2;
		ivsub_swiz_b_2 -= ivfoo2.xy;
		ivsub_swiz_c_2.xy -= ivfoo2;
		ivsub_swiz_c_2.gr -= ivfoo2.rg;
	}
	hlslpp_unit::EndTest();

	hlslpp_unit::BeginTest("Integer Multiplication");
	{
		int1 ivmul1 = ivfoo1 * ivbar1;									hlslpp_check(eq(ivmul1, (int32_t)ivfoo1.x * (int32_t)ivbar1.x));
		int2 ivmul2 = ivfoo2 * ivbar2;									hlslpp_check(eq(ivmul2, (int32_t)ivfoo2.x * (int32_t)ivbar2.x, (int32_t)ivfoo2.y * (int32_t)ivbar2.y));
		int3 ivmul3 = ivfoo3 * ivbar3;									hlslpp_check(eq(ivmul3, (int32_t)ivfoo3.x * (int32_t)ivbar3.x, (int32_t)ivfoo3.y * (int32_t)ivbar3.y, (int32_t)ivfoo3.z * (int32_t)ivbar3.z));
		int4 ivmul4 = ivfoo4 * ivbar4;									hlslpp_check(eq(ivmul4, (int32_t)ivfoo4.x * (int32_t)ivbar4.x, (int32_t)ivfoo4.y * (int32_t)ivbar4.y, (int32_t)ivfoo4.z * (int32_t)ivbar4.z, (int32_t)ivfoo4.w * (int32_t)ivbar4.w));

		int1 ivmul_f_1 = ivfoo1 * 1;									hlslpp_check(eq(ivmul_f_1, (int32_t)ivfoo1.x * 1));
		int2 ivmul_f_2 = ivfoo2 * 2;									hlslpp_check(eq(ivmul_f_2, (int32_t)ivfoo2.x * 2, (int32_t)ivfoo2.y * 2));
		int3 ivmul_f_3 = ivfoo3 * 3;									hlslpp_check(eq(ivmul_f_3, (int32_t)ivfoo3.x * 3, (int32_t)ivfoo3.y * 3, (int32_t)ivfoo3.z * 3));
		int4 ivmul_f_4 = ivfoo4 * 4;									hlslpp_check(eq(ivmul_f_4, (int32_t)ivfoo4.x * 4, (int32_t)ivfoo4.y * 4, (int32_t)ivfoo4.z * 4, (int32_t)ivfoo4.w * 4));

		ivmul_f_1 *= 1;													hlslpp_check(eq(ivmul_f_1, (int32_t)ivfoo1.x * 1 * 1));
		ivmul_f_2 *= 2;													hlslpp_check(eq(ivmul_f_2, (int32_t)ivfoo2.x * 2 * 2, (int32_t)ivfoo2.y * 2 * 2));
		ivmul_f_3 *= 3;													hlslpp_check(eq(ivmul_f_3, (int32_t)ivfoo3.x * 3 * 3, (int32_t)ivfoo3.y * 3 * 3, (int32_t)ivfoo3.z * 3 * 3));
		ivmul_f_4 *= 4;													hlslpp_check(eq(ivmul_f_4, (int32_t)ivfoo4.x * 4 * 4, (int32_t)ivfoo4.y * 4 * 4, (int32_t)ivfoo4.z * 4 * 4, (int32_t)ivfoo4.w * 4 * 4));

		ivmul_f_2.y *= 2;												hlslpp_check(eq(ivmul_f_2, (int32_t)ivfoo2.x * 2 * 2, (int32_t)ivfoo2.y * 2 * 2 * 2));
		ivmul_f_3.z *= 3;												hlslpp_check(eq(ivmul_f_3, (int32_t)ivfoo3.x * 3 * 3, (int32_t)ivfoo3.y * 3 * 3, (int32_t)ivfoo3.z * 3 * 3 * 3));
		ivmul_f_4.w *= 4;												hlslpp_check(eq(ivmul_f_4, (int32_t)ivfoo4.x * 4 * 4, (int32_t)ivfoo4.y * 4 * 4, (int32_t)ivfoo4.z * 4 * 4, (int32_t)ivfoo4.w * 4 * 4 * 4));

		int1 ivmul_swiz_a_1 = ivfoo1 * ivbar1.x;   hlslpp_unit_unused(ivmul_swiz_a_1);
		int1 ivmul_swiz_b_1 = ivfoo1.r * ivbar1.x; hlslpp_unit_unused(ivmul_swiz_b_1);
		int1 ivmul_swiz_c_1 = ivfoo1.r * ivbar1;   hlslpp_unit_unused(ivmul_swiz_c_1);

		int2 ivmul_swiz_a_2 = ivfoo2 * ivbar2.yx;    hlslpp_unit_unused(ivmul_swiz_a_2);
		int2 ivmul_swiz_b_2 = ivfoo2.gr * ivbar2.yx; hlslpp_unit_unused(ivmul_swiz_b_2);
		int2 ivmul_swiz_c_2 = ivfoo2.rg * ivbar2;    hlslpp_unit_unused(ivmul_swiz_c_2);

		int3 ivmul_swiz_a_3 = ivfoo3 * ivbar3.yxz;     hlslpp_unit_unused(ivmul_swiz_a_3);
		int3 ivmul_swiz_b_3 = ivfoo3.rgb * ivbar3.xyz; hlslpp_unit_unused(ivmul_swiz_b_3);
		int3 ivmul_swiz_c_3 = ivfoo3.bgr * ivbar3;     hlslpp_unit_unused(ivmul_swiz_c_3);

		int4 ivmul_swiz_a_4 = ivfoo4 * ivbar4.yxzw;      hlslpp_unit_unused(ivmul_swiz_a_4);
		int4 ivmul_swiz_b_4 = ivfoo4.bgra * ivbar4.yxzw; hlslpp_unit_unused(ivmul_swiz_b_4);
		int4 ivmul_swiz_c_4 = ivfoo4.bgra * ivbar4;      hlslpp_unit_unused(ivmul_swiz_c_4);

		ivmul_swiz_a_2 *= ivfoo2;
		ivmul_swiz_b_2 *= ivfoo2.xy;
		ivmul_swiz_c_2.xy *= ivfoo2;
		ivmul_swiz_c_2.gr *= ivfoo2.rg;

		int1 vint = int1(1);
		int1 vint2 = int1(2);
		int1 vint3 = vint.r + vint2; hlslpp_unit_unused(vint3);
		vint.r = vint2.x;
	}
	hlslpp_unit::EndTest();

	hlslpp_unit::BeginTest("Integer Division");
	{
		int1 ivdivbar1 = select(ivbar1 == 0, 1, ivbar1);
		int2 ivdivbar2 = select(ivbar2 == 0, 1, ivbar2);
		int3 ivdivbar3 = select(ivbar3 == 0, 1, ivbar3);
		int4 ivdivbar4 = select(ivbar4 == 0, 1, ivbar4);

		int1 ivdiv1 = ivfoo1 / ivdivbar1;  hlslpp_check(eq(ivdiv1, (int32_t)ivfoo1.x / (int32_t)ivdivbar1.x));
		int2 ivdiv2 = ivfoo2 / ivdivbar2;  hlslpp_check(eq(ivdiv2, (int32_t)ivfoo2.x / (int32_t)ivdivbar2.x, (int32_t)ivfoo2.y / (int32_t)ivdivbar2.y));
		int3 ivdiv3 = ivfoo3 / ivdivbar3;  hlslpp_check(eq(ivdiv3, (int32_t)ivfoo3.x / (int32_t)ivdivbar3.x, (int32_t)ivfoo3.y / (int32_t)ivdivbar3.y, (int32_t)ivfoo3.z / (int32_t)ivdivbar3.z));
		int4 ivdiv4 = ivfoo4 / ivdivbar4;  hlslpp_check(eq(ivdiv4, (int32_t)ivfoo4.x / (int32_t)ivdivbar4.x, (int32_t)ivfoo4.y / (int32_t)ivdivbar4.y, (int32_t)ivfoo4.z / (int32_t)ivdivbar4.z, (int32_t)ivfoo4.w / (int32_t)ivdivbar4.w));

		int1 ivdiv_f_1 = ivfoo1 / 1;    hlslpp_check(eq(ivdiv_f_1, (int32_t)ivfoo1.x / 1));
		int2 ivdiv_f_2 = ivfoo2 / 2;    hlslpp_check(eq(ivdiv_f_2, (int32_t)ivfoo2.x / 2, (int32_t)ivfoo2.y / 2));
		int3 ivdiv_f_3 = ivfoo3 / 3;    hlslpp_check(eq(ivdiv_f_3, (int32_t)ivfoo3.x / 3, (int32_t)ivfoo3.y / 3, (int32_t)ivfoo3.z / 3));
		int4 ivdiv_f_4 = ivfoo4 / 4;    hlslpp_check(eq(ivdiv_f_4, (int32_t)ivfoo4.x / 4, (int32_t)ivfoo4.y / 4, (int32_t)ivfoo4.z / 4, (int32_t)ivfoo4.w / 4));

		ivdiv_f_1 /= 1;                 hlslpp_check(eq(ivdiv_f_1, (int32_t)ivfoo1.x / 1 / 1));
		ivdiv_f_2 /= 2;                 hlslpp_check(eq(ivdiv_f_2, (int32_t)ivfoo2.x / 2 / 2, (int32_t)ivfoo2.y / 2 / 2));
		ivdiv_f_3 /= 3;                 hlslpp_check(eq(ivdiv_f_3, (int32_t)ivfoo3.x / 3 / 3, (int32_t)ivfoo3.y / 3 / 3, (int32_t)ivfoo3.z / 3 / 3));
		ivdiv_f_4 /= 4;                 hlslpp_check(eq(ivdiv_f_4, (int32_t)ivfoo4.x / 4 / 4, (int32_t)ivfoo4.y / 4 / 4, (int32_t)ivfoo4.z / 4 / 4, (int32_t)ivfoo4.w / 4 / 4));

		ivdiv_f_2.y /= 2;               hlslpp_check(eq(ivdiv_f_2, (int32_t)ivfoo2.x / 2 / 2, (int32_t)ivfoo2.y / 2 / 2 / 2));
		ivdiv_f_3.z /= 3;               hlslpp_check(eq(ivdiv_f_3, (int32_t)ivfoo3.x / 3 / 3, (int32_t)ivfoo3.y / 3 / 3, (int32_t)ivfoo3.z / 3 / 3 / 3));
		ivdiv_f_4.w /= 4;               hlslpp_check(eq(ivdiv_f_4, (int32_t)ivfoo4.x / 4 / 4, (int32_t)ivfoo4.y / 4 / 4, (int32_t)ivfoo4.z / 4 / 4, (int32_t)ivfoo4.w / 4 / 4 / 4));
	}
	hlslpp_unit::EndTest();

	hlslpp_unit::BeginTest("Integer Comparison");
	{
		// Equality
		int1 iveq1 = ivfoo1 == ivfoo1;  hlslpp_check(eq(all(iveq1), true));
		int2 iveq2 = ivfoo2 == ivfoo2;  hlslpp_check(eq(all(iveq2), true));
		int3 iveq3 = ivfoo3 == ivfoo3;  hlslpp_check(eq(all(iveq3), true));
		int4 iveq4 = ivfoo4 == ivfoo4;  hlslpp_check(eq(all(iveq4), true));

		// Equality
		int1 ivneq1 = ivfoo1 != ivfoo1;  hlslpp_check(eq(any(ivneq1), false));
		int2 ivneq2 = ivfoo2 != ivfoo2;  hlslpp_check(eq(any(ivneq2), false));
		int3 ivneq3 = ivfoo3 != ivfoo3;  hlslpp_check(eq(any(ivneq3), false));
		int4 ivneq4 = ivfoo4 != ivfoo4;  hlslpp_check(eq(any(ivneq4), false));

		// Less
		int1 ivlt1 = ivfoo1 < (ivfoo1 + int1(1));           hlslpp_check(eq(all(ivlt1), true));
		int2 ivlt2 = ivfoo2 < (ivfoo2 + int2(1, 1));        hlslpp_check(eq(all(ivlt2), true));
		int3 ivlt3 = ivfoo3 < (ivfoo3 + int3(1, 1, 1));     hlslpp_check(eq(all(ivlt3), true));
		int4 ivlt4 = ivfoo4 < (ivfoo4 + int4(1, 1, 1, 1));  hlslpp_check(eq(all(ivlt4), true));

		// Less or equal
		int1 ivle1 = ivfoo1 <= (ivfoo1 + int1(0));           hlslpp_check(eq(all(ivle1), true));
		int2 ivle2 = ivfoo2 <= (ivfoo2 + int2(1, 0));        hlslpp_check(eq(all(ivle2), true));
		int3 ivle3 = ivfoo3 <= (ivfoo3 + int3(0, 1, 0));     hlslpp_check(eq(all(ivle3), true));
		int4 ivle4 = ivfoo4 <= (ivfoo4 + int4(1, 0, 1, 0));  hlslpp_check(eq(all(ivle4), true));

		// Greater
		int1 ivgr1 = ivfoo1 > (ivfoo1 - int1(1));           hlslpp_check(eq(all(ivgr1), true));
		int2 ivgr2 = ivfoo2 > (ivfoo2 - int2(1, 1));        hlslpp_check(eq(all(ivgr2), true));
		int3 ivgr3 = ivfoo3 > (ivfoo3 - int3(1, 1, 1));     hlslpp_check(eq(all(ivgr3), true));
		int4 ivgr4 = ivfoo4 > (ivfoo4 - int4(1, 1, 1, 1));  hlslpp_check(eq(all(ivgr4), true));

		// Greater or equal
		int1 ivge1 = ivfoo1 >= (ivfoo1 - int1(0));           hlslpp_check(eq(all(ivge1), true));
		int2 ivge2 = ivfoo2 >= (ivfoo2 - int2(1, 0));        hlslpp_check(eq(all(ivge2), true));
		int3 ivge3 = ivfoo3 >= (ivfoo3 - int3(0, 1, 0));     hlslpp_check(eq(all(ivge3), true));
		int4 ivge4 = ivfoo4 >= (ivfoo4 - int4(1, 0, 1, 0));  hlslpp_check(eq(all(ivge4), true));

		// Checking that swizzle1 comparison operators are correctly overloaded
		if (iveq1.x == ivlt1.x)
		{
		}
	}
	hlslpp_unit::EndTest();

	// Cast from float to int and viceversa

	float1 fcastfooi_1(ivfoo1);
	float2 fcastfooi_2(ivfoo2);
	float3 fcastfooi_3(ivfoo3);
	float4 fcastfooi_4(ivfoo4);

	fcastfooi_1 = ivfoo1;
	fcastfooi_2 = ivfoo2;
	fcastfooi_3 = ivfoo3;
	fcastfooi_4 = ivfoo4;

	float1 fcastbari_1 = ivfoo1; hlslpp_check(eq(fcastbari_1, (float)fcastfooi_1.x));
	float2 fcastbari_2 = ivfoo2; hlslpp_check(eq(fcastbari_2, (float)fcastfooi_2.x, (float)fcastfooi_2.y));
	float3 fcastbari_3 = ivfoo3; hlslpp_check(eq(fcastbari_3, (float)fcastfooi_3.x, (float)fcastfooi_3.y, (float)fcastfooi_3.z));
	float4 fcastbari_4 = ivfoo4; hlslpp_check(eq(fcastbari_4, (float)fcastfooi_4.x, (float)fcastfooi_4.y, (float)fcastfooi_4.z, (float)fcastfooi_4.w));

	hlslpp_unit::BeginTest("Integer-Float Reinterpret");
	{
		union fint
		{
			explicit fint(float f) : f(f) {}
			explicit fint(uint32_t u) : u(u) {}
			explicit fint(int32_t i) : i(i) {}

			float f;
			uint32_t u;
			int32_t i;
		};

		fint fval[4] = { fint(1.0f), fint(2.0f), fint(3.0f), fint(4.0f) };

		uint1 uiasfloat_1(fval[0].u);
		float1 fuiasfloat_1 = asfloat(uiasfloat_1); hlslpp_check(eq(fuiasfloat_1, fval[0].f));

		uint2 uiasfloat_2 = uint2(fval[0].u, fval[1].u);
		float2 fuiasfloat_2 = asfloat(uiasfloat_2); hlslpp_check(eq(fuiasfloat_2, fval[0].f, fval[1].f));

		uint3 uiasfloat_3 = uint3(fval[0].u, fval[1].u, fval[2].u);
		float3 fuiasfloat_3 = asfloat(uiasfloat_3); hlslpp_check(eq(fuiasfloat_3, fval[0].f, fval[1].f, fval[2].f));

		uint4 uiasfloat_4 = uint4(fval[0].u,fval[1].u, fval[2].u, fval[3].u);
		float4 fuiasfloat_4 = asfloat(uiasfloat_4); hlslpp_check(eq(fuiasfloat_4, fval[0].f, fval[1].f, fval[2].f, fval[3].f));

		int1 iasfloat_1(fval[0].i);
		float1 fiasfloat_1 = asfloat(iasfloat_1); hlslpp_check(eq(fiasfloat_1, fval[0].f));

		int2 iasfloat_2(fval[0].i, fval[1].i);
		float2 fiasfloat_2 = asfloat(iasfloat_2); hlslpp_check(eq(fiasfloat_2, fval[0].f, fval[1].f));

		int3 iasfloat_3(fval[0].i, fval[1].i, fval[2].i);
		float3 fiasfloat_3 = asfloat(iasfloat_3); hlslpp_check(eq(fiasfloat_3, fval[0].f, fval[1].f, fval[2].f));

		int4 iasfloat_4(fval[0].i, fval[1].i, fval[2].i, fval[3].i);
		float4 fiasfloat_4 = asfloat(iasfloat_4); hlslpp_check(eq(fiasfloat_4, fval[0].f, fval[1].f, fval[2].f, fval[3].f));

		fint uival[4] = { fint(7u), fint(8u), fint(9u), fint(10u) };

		float1 fasuint_1(uival[0].f);
		uint1 uisuint_1 = asuint(fasuint_1); hlslpp_check(eq(uisuint_1, uival[0].u));

		float2 fasuint_2(uival[0].f, uival[1].f);
		uint2 uisuint_2 = asuint(fasuint_2); hlslpp_check(eq(uisuint_2, uival[0].u, uival[1].u));

		float3 fasuint_3(uival[0].f, uival[1].f, uival[2].f);
		uint3 uisuint_3 = asuint(fasuint_3); hlslpp_check(eq(uisuint_3, uival[0].u, uival[1].u, uival[2].u));

		float4 fasuint_4(uival[0].f, uival[1].f, uival[2].f, uival[3].f);
		uint4 uisuint_4 = asuint(fasuint_4); hlslpp_check(eq(uisuint_4, uival[0].u, uival[1].u, uival[2].u, uival[3].u));

		fint ival[4] = { fint(11), fint(12), fint(13), fint(14) };

		float1 fasint_1(ival[0].f);
		int1 isuint_1 = asint(fasint_1); hlslpp_check(eq(isuint_1, ival[0].i));

		float2 fasint_2(ival[0].f, ival[1].f);
		int2 isuint_2 = asint(fasint_2); hlslpp_check(eq(isuint_2, ival[0].i, ival[1].i));

		float3 fasint_3(ival[0].f, ival[1].f, ival[2].f);
		int3 isuint_3 = asint(fasint_3); hlslpp_check(eq(isuint_3, ival[0].i, ival[1].i, ival[2].i));

		float4 fasint_4(ival[0].f, ival[1].f, ival[2].f, ival[3].f);
		int4 isuint_4 = asint(fasint_4); hlslpp_check(eq(isuint_4, ival[0].i, ival[1].i, ival[2].i, ival[3].i));
	}
	hlslpp_unit::EndTest();

	hlslpp_unit::BeginTest("Integer Bit-Shifting");
	{
		int1 ivshift_value_1 = int1(1);
		int2 ivshift_value_2 = int2(2, 3);
		int3 ivshift_value_3 = int3(1, 2, 4);
		int4 ivshift_value_4 = int4(2, 6, 3, 1);

		int1 ivshl_1 = ivfoo1 << ivshift_value_1; hlslpp_check(eq(ivshl_1, shift_left(ivfoo1.x, ivshift_value_1.x)));
		int2 ivshl_2 = ivfoo2 << ivshift_value_2; hlslpp_check(eq(ivshl_2, shift_left(ivfoo2.x, ivshift_value_2.x), shift_left(ivfoo2.y, ivshift_value_2.y)));
		int3 ivshl_3 = ivfoo3 << ivshift_value_3; hlslpp_check(eq(ivshl_3, shift_left(ivfoo3.x, ivshift_value_3.x), shift_left(ivfoo3.y, ivshift_value_3.y), shift_left(ivfoo3.z, ivshift_value_3.z)));
		int4 ivshl_4 = ivfoo4 << ivshift_value_4; hlslpp_check(eq(ivshl_4, shift_left(ivfoo4.x, ivshift_value_4.x), shift_left(ivfoo4.y, ivshift_value_4.y), shift_left(ivfoo4.z, ivshift_value_4.z), shift_left(ivfoo4.w, ivshift_value_4.w)));

		ivshl_2 = ivfoo2 << ivshift_value_1; hlslpp_check(eq(ivshl_2, shift_left(ivfoo2.x, ivshift_value_1.x), shift_left(ivfoo2.y, ivshift_value_1.x)));
		ivshl_3 = ivfoo3 << ivshift_value_1; hlslpp_check(eq(ivshl_3, shift_left(ivfoo3.x, ivshift_value_1.x), shift_left(ivfoo3.y, ivshift_value_1.x), shift_left(ivfoo3.z, ivshift_value_1.x)));
		ivshl_4 = ivfoo4 << ivshift_value_1; hlslpp_check(eq(ivshl_4, shift_left(ivfoo4.x, ivshift_value_1.x), shift_left(ivfoo4.y, ivshift_value_1.x), shift_left(ivfoo4.z, ivshift_value_1.x), shift_left(ivfoo4.w, ivshift_value_1.x)));

		int1 ivshr_1 = ivfoo1 >> ivshift_value_1; hlslpp_check(eq(ivshr_1, shift_right(ivfoo1.x, ivshift_value_1.x)));
		int2 ivshr_2 = ivfoo2 >> ivshift_value_2; hlslpp_check(eq(ivshr_2, shift_right(ivfoo2.x, ivshift_value_2.x), shift_right(ivfoo2.y, ivshift_value_2.y)));
		int3 ivshr_3 = ivfoo3 >> ivshift_value_3; hlslpp_check(eq(ivshr_3, shift_right(ivfoo3.x, ivshift_value_3.x), shift_right(ivfoo3.y, ivshift_value_3.y), shift_right(ivfoo3.z, ivshift_value_3.z)));
		int4 ivshr_4 = ivfoo4 >> ivshift_value_4; hlslpp_check(eq(ivshr_4, shift_right(ivfoo4.x, ivshift_value_4.x), shift_right(ivfoo4.y, ivshift_value_4.y), shift_right(ivfoo4.z, ivshift_value_4.z), shift_right(ivfoo4.w, ivshift_value_4.w)));

		ivshr_2 = ivfoo2 >> ivshift_value_1; hlslpp_check(eq(ivshr_2, shift_right(ivfoo2.x, ivshift_value_1.x), shift_right(ivfoo2.y, ivshift_value_1.x)));
		ivshr_3 = ivfoo3 >> ivshift_value_1; hlslpp_check(eq(ivshr_3, shift_right(ivfoo3.x, ivshift_value_1.x), shift_right(ivfoo3.y, ivshift_value_1.x), shift_right(ivfoo3.z, ivshift_value_1.x)));
		ivshr_4 = ivfoo4 >> ivshift_value_1; hlslpp_check(eq(ivshr_4, shift_right(ivfoo4.x, ivshift_value_1.x), shift_right(ivfoo4.y, ivshift_value_1.x), shift_right(ivfoo4.z, ivshift_value_1.x), shift_right(ivfoo4.w, ivshift_value_1.x)));
	}
	hlslpp_unit::EndTest();

	hlslpp_unit::BeginTest("Integer Functions");
	{
		bool ivall1 = all(ivfoo1);				hlslpp_check(eq(ivall1, ivfoo1.x != 0));
		bool ivall2 = all(ivfoo2);				hlslpp_check(eq(ivall2, ivfoo2.x != 0 && ivfoo2.y != 0));
		bool ivall3 = all(ivfoo3);				hlslpp_check(eq(ivall3, ivfoo3.x != 0 && ivfoo3.y != 0 && ivfoo3.z != 0));
		bool ivall4 = all(ivfoo4);				hlslpp_check(eq(ivall4, ivfoo4.x != 0 && ivfoo4.y != 0 && ivfoo4.z != 0 && ivfoo4.w != 0));

		bool ivall_swiz_1 = all(ivfoo1.r);		hlslpp_check(eq(ivall_swiz_1, ivfoo1.r != 0));
		bool ivall_swiz_2 = all(ivfoo2.yx);		hlslpp_check(eq(ivall_swiz_2, ivfoo2.y != 0 && ivfoo2.x != 0));
		bool ivall_swiz_3 = all(ivfoo3.bgr);	hlslpp_check(eq(ivall_swiz_3, ivfoo3.b != 0 && ivfoo3.g != 0 && ivfoo3.r != 0));
		bool ivall_swiz_4 = all(ivfoo4.wwww);	hlslpp_check(eq(ivall_swiz_4, ivfoo4.w != 0));

		bool ivany1 = any(ivfoo1);				hlslpp_check(eq(ivany1, ivfoo1.x != 0));
		bool ivany2 = any(ivfoo2);				hlslpp_check(eq(ivany2, ivfoo2.x != 0 || ivfoo2.y != 0));
		bool ivany3 = any(ivfoo3);				hlslpp_check(eq(ivany3, ivfoo3.x != 0 || ivfoo3.y != 0 || ivfoo3.z != 0));
		bool ivany4 = any(ivfoo4);				hlslpp_check(eq(ivany4, ivfoo4.x != 0 || ivfoo4.y != 0 || ivfoo4.z != 0 || ivfoo4.w != 0));

		bool ivany_swiz_1 = any(ivfoo1.r);		hlslpp_check(eq(ivany_swiz_1, ivfoo1.x != 0));
		bool ivany_swiz_2 = any(ivfoo2.yx);		hlslpp_check(eq(ivany_swiz_2, ivfoo2.y != 0 || ivfoo2.x != 0));
		bool ivany_swiz_3 = any(ivfoo3.bgr);	hlslpp_check(eq(ivany_swiz_3, ivfoo3.b != 0 || ivfoo3.g != 0 || ivfoo3.r != 0));
		bool ivany_swiz_4 = any(ivfoo4.wwww);	hlslpp_check(eq(ivany_swiz_4, ivfoo4.w != 0));

		int1 ivabs1 = abs(ivfoo1);								hlslpp_check(eq(ivabs1, abs((int32_t)ivfoo1.x)));
		int2 ivabs2 = abs(ivfoo2);								hlslpp_check(eq(ivabs2, abs((int32_t)ivfoo2.x), abs((int32_t)ivfoo2.y)));
		int3 ivabs3 = abs(ivfoo3);								hlslpp_check(eq(ivabs3, abs((int32_t)ivfoo3.x), abs((int32_t)ivfoo3.y), abs((int32_t)ivfoo3.z)));
		int4 ivabs4 = abs(ivfoo4);								hlslpp_check(eq(ivabs4, abs((int32_t)ivfoo4.x), abs((int32_t)ivfoo4.y), abs((int32_t)ivfoo4.z), abs((int32_t)ivfoo4.w)));

		int1 ivabsneg_1 = abs(-ivfoo1);							hlslpp_check(eq(ivabsneg_1, abs((int32_t)-ivfoo1)));
		int2 ivabsneg_2 = abs(-ivfoo2);							hlslpp_check(eq(ivabsneg_2, abs((int32_t)-ivfoo2.x), abs((int32_t)-ivfoo2.y)));
		int3 ivabsneg_3 = abs(-ivfoo3);							hlslpp_check(eq(ivabsneg_3, abs((int32_t)-ivfoo3.x), abs((int32_t)-ivfoo3.y), abs((int32_t)-ivfoo3.z)));
		int4 ivabsneg_4 = abs(-ivfoo4);							hlslpp_check(eq(ivabsneg_4, abs((int32_t)-ivfoo4.x), abs((int32_t)-ivfoo4.y), abs((int32_t)-ivfoo4.z), abs((int32_t)-ivfoo4.w)));

		int1 ivabs_swiz_1 = abs(ivfoo1.r);						hlslpp_check(eq(ivabs_swiz_1, abs((int32_t)ivfoo1.x)));
		int2 ivabs_swiz_2 = abs(ivfoo2.yx);						hlslpp_check(eq(ivabs_swiz_2, abs((int32_t)ivfoo2.g), abs((int32_t)ivfoo2.r)));
		int3 ivabs_swiz_3 = abs(ivfoo3.bgr);					hlslpp_check(eq(ivabs_swiz_3, abs((int32_t)ivfoo3.b), abs((int32_t)ivfoo3.g), abs((int32_t)ivfoo3.r)));
		int4 ivabs_swiz_4 = abs(ivfoo4.wwww);					hlslpp_check(eq(ivabs_swiz_4, abs((int32_t)ivfoo4.a), abs((int32_t)ivfoo4.a), abs((int32_t)ivfoo4.a), abs((int32_t)ivfoo4.a)));

		int1 ivselect1 = select(ivbaz1, ivfoo1, ivbar1);		hlslpp_check(eq(ivselect1, ivbaz1.x != 0 ? ivfoo1.x : ivbar1.x));
		int2 ivselect2 = select(ivbaz2, ivfoo2, ivbar2);		hlslpp_check(eq(ivselect2, ivbaz2.x != 0 ? ivfoo2.x : ivbar2.x, ivbaz2.y != 0 ? ivfoo2.y : ivbar2.y));
		int3 ivselect3 = select(ivbaz3, ivfoo3, ivbar3);		hlslpp_check(eq(ivselect3, ivbaz3.x != 0 ? ivfoo3.x : ivbar3.x, ivbaz3.y != 0 ? ivfoo3.y : ivbar3.y, ivbaz3.z != 0 ? ivfoo3.z : ivbar3.z));
		int4 ivselect4 = select(ivbaz4, ivfoo4, ivbar4);		hlslpp_check(eq(ivselect4, ivbaz4.x != 0 ? ivfoo4.x : ivbar4.x, ivbaz4.y != 0 ? ivfoo4.y : ivbar4.y, ivbaz4.z != 0 ? ivfoo4.z : ivbar4.z, ivbaz4.w != 0 ? ivfoo4.w : ivbar4.w));
	}
	hlslpp_unit::EndTest();

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

	hlslpp_unit::BeginTest("Integer Float Conversions");
	{
		float f1 = (float)(rand() % 1000) / 100.0f; float f5 = (float)(rand() % 1000) / 100.0f; float f9 = (float)(rand() % 1000) / 100.0f; //float f13 = (rand() % 1000) / 100.0f; float f17 = (rand() % 1000) / 100.0f;
		float f2 = (float)(rand() % 1000) / 100.0f; float f6 = (float)(rand() % 1000) / 100.0f; float f10 = (float)(rand() % 1000) / 100.0f; //float f14 = (rand() % 1000) / 100.0f; float f18 = (rand() % 1000) / 100.0f;
		float f3 = (float)(rand() % 1000) / 100.0f; float f7 = (float)(rand() % 1000) / 100.0f; //float f11 = (rand() % 1000) / 100.0f; float f15 = (rand() % 1000) / 100.0f; float f19 = (rand() % 1000) / 100.0f;
		float f4 = (float)(rand() % 1000) / 100.0f; float f8 = (float)(rand() % 1000) / 100.0f; //float f12 = (rand() % 1000) / 100.0f; float f16 = (rand() % 1000) / 100.0f; float f20 = (rand() % 1000) / 100.0f;

		// Initialization

		float1 vfoo1 = float1(f1);					hlslpp_check(eq(vfoo1, f1));
		float2 vfoo2 = float2(f2, f3);				hlslpp_check(eq(vfoo2, f2, f3));
		float3 vfoo3 = float3(f4, f5, f6);			hlslpp_check(eq(vfoo3, f4, f5, f6));
		float4 vfoo4 = float4(f7, f8, f9, f10);		hlslpp_check(eq(vfoo4, f7, f8, f9, f10));

		vfoo1 = float1(i1);							hlslpp_check(eq(vfoo1, (float)i1));
		vfoo2 = float2(i2, i3);						hlslpp_check(eq(vfoo2, (float)i2, (float)i3));
		vfoo3 = float3(i4, i5, i6);					hlslpp_check(eq(vfoo3, (float)i4, (float)i5, (float)i6));
		vfoo4 = float4(i7, i8, i9, i10);			hlslpp_check(eq(vfoo4, (float)i7, (float)i8, (float)i9, (float)i10));

		vfoo2 = float2(i2, f3);						hlslpp_check(eq(vfoo2, (float)i2, (float)f3));
		vfoo3 = float3(f4, i5, i6);					hlslpp_check(eq(vfoo3, (float)f4, (float)i5, (float)i6));
		vfoo4 = float4(i7, i8, f9, f10);			hlslpp_check(eq(vfoo4, (float)i7, (float)i8, (float)f9, (float)f10));

		vfoo1 = float1(ivfoo1);						hlslpp_check(eq(vfoo1, (float)ivfoo1.x));
		vfoo2 = float2(ivfoo2);						hlslpp_check(eq(vfoo2, (float)ivfoo2.x, (float)ivfoo2.y));
		vfoo3 = float3(ivfoo3);						hlslpp_check(eq(vfoo3, (float)ivfoo3.x, (float)ivfoo3.y, (float)ivfoo3.z));
		vfoo4 = float4(ivfoo4);						hlslpp_check(eq(vfoo4, (float)ivfoo4.x, (float)ivfoo4.y, (float)ivfoo4.z, (float)ivfoo4.w));

		// Conversion

		vfoo1 = float1(f1);							hlslpp_check(eq(vfoo1, f1));
		vfoo2 = float2(f2, f3);						hlslpp_check(eq(vfoo2, f2, f3));
		vfoo3 = float3(f4, f5, f6);					hlslpp_check(eq(vfoo3, f4, f5, f6));
		vfoo4 = float4(f7, f8, f9, f10);			hlslpp_check(eq(vfoo4, f7, f8, f9, f10));

		int1 icfoo1 = int1(vfoo1);					hlslpp_check(eq(icfoo1, (int32_t)vfoo1.x));
		int2 icfoo2 = int2(-vfoo2);					hlslpp_check(eq(icfoo2, (int32_t)-vfoo2.x, (int32_t)-vfoo2.y));
		int3 icfoo3 = int3(vfoo3);					hlslpp_check(eq(icfoo3, (int32_t)vfoo3.x, (int32_t)vfoo3.y, (int32_t)vfoo3.z));
		int4 icfoo4 = int4(-vfoo4);					hlslpp_check(eq(icfoo4, (int32_t)-vfoo4.x, (int32_t)-vfoo4.y, (int32_t)-vfoo4.z, (int32_t)-vfoo4.w));
	}
	hlslpp_unit::EndTest();
}
