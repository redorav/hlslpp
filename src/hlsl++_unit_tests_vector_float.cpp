#include "hlsl++.h"

#include "hlsl++_unit_tests.h"

float GetRandomFloat()
{
	return (rand() % 1000) / 100.0f - 5.0f;
}

void RunUnitTestsVectorFloat()
{
	using namespace hlslpp_unit;

	//------
	// Float
	//------

	float f1 = GetRandomFloat();
	float f2 = GetRandomFloat();
	float f3 = GetRandomFloat();
	float f4 = GetRandomFloat();

	float f5 = GetRandomFloat();
	float f6 = GetRandomFloat();
	float f7 = GetRandomFloat();
	float f8 = GetRandomFloat();

	float f9 = GetRandomFloat();
	float f10 = GetRandomFloat();
	float f11 = GetRandomFloat();
	float f12 = GetRandomFloat();

	float f13 = GetRandomFloat();
	float f14 = GetRandomFloat();
	float f15 = GetRandomFloat();
	float f16 = GetRandomFloat();

	float f17 = GetRandomFloat();
	float f18 = GetRandomFloat();
	float f19 = GetRandomFloat();
	float f20 = GetRandomFloat();

	float f21 = GetRandomFloat();
	float f22 = GetRandomFloat();
	float f23 = GetRandomFloat();
	float f24 = GetRandomFloat();

	float f25 = GetRandomFloat();
	float f26 = GetRandomFloat();
	float f27 = GetRandomFloat();
	float f28 = GetRandomFloat();

	// Initialization

	float1 vfoo1 = float1(f1);												eq(vfoo1, f1);
	float2 vfoo2 = float2(f2, f3);											eq(vfoo2, f2, f3);
	float3 vfoo3 = float3(f4, f5, f6);										eq(vfoo3, f4, f5, f6);
	float4 vfoo4 = float4(f7, f8, f9, f10);									eq(vfoo4, f7, f8, f9, f10);

	// Default constructors

	float1 vfoo_dc_1;
	float2 vfoo_dc_2;
	float3 vfoo_dc_3;
	float4 vfoo_dc_4;

	vfoo1 = float1(f1);														eq(vfoo1, f1);
	vfoo2 = float2(f2, f3);													eq(vfoo2, f2, f3);
	vfoo3 = float3(f4, f5, f6);												eq(vfoo3, f4, f5, f6);
	vfoo4 = float4(f7, f8, f9, f10);										eq(vfoo4, f7, f8, f9, f10);

	float1 vbar1 = vfoo1.x;													eq(vbar1, f1);
	float2 vbar2 = vfoo2.gr;												eq(vbar2, f3, f2);
	float3 vbar3 = vfoo3.zyx;												eq(vbar3, f6, f5, f4);
	float4 vbar4 = vfoo4.bgra;												eq(vbar4, f9, f8, f7, f10);

	vbar1 = f11;															eq(vbar1, f11);
	vbar2 = float2(f12, f13);												eq(vbar2, f12, f13);
	vbar3 = float3(f14, f15, f16);											eq(vbar3, f14, f15, f16);
	vbar4 = float4(f17, f18, f19, f20);										eq(vbar4, f17, f18, f19, f20);

	float1 vbaz1 = float1(0.2f);											eq(vbaz1, 0.2f);
	float2 vbaz2 = float2(0.3f, 0.7f);										eq(vbaz2, 0.3f, 0.7f);
	float3 vbaz3 = float3(0.1f, 0.4f, 0.8f);								eq(vbaz3, 0.1f, 0.4f, 0.8f);
	float4 vbaz4 = float4(0.0f, 0.2f, 0.6f, 1.0f);							eq(vbaz4, 0.0f, 0.2f, 0.6f, 1.0f);

	float2 vfoo_mix_2_a = float2(vfoo1, vbar1);								eq(vfoo_mix_2_a, vfoo1, vbar1);
	float2 vfoo_mix_2_b = float2(vfoo2.y, vbar1);							eq(vfoo_mix_2_b, vfoo2.y, vbar1);
	float2 vfoo_mix_2_c = float2(vfoo1, vbar1.x);							eq(vfoo_mix_2_c, vfoo1, vbar1.x);
	float2 vfoo_mix_2_d = float2(vfoo1.x, vbar2.y);							eq(vfoo_mix_2_d, vfoo1.x, vbar2.y);

	float2 vfoo_mix_2_f_a = float2(vfoo1, f1);								eq(vfoo_mix_2_f_a, vfoo1.x, f1);
	float2 vfoo_mix_2_f_b = float2(f2, vbar1);								eq(vfoo_mix_2_f_b, f2, vbar1);
	float2 vfoo_mix_2_f_c = float2(vfoo2.y, f1);							eq(vfoo_mix_2_f_c, vfoo2.y, f1);
	float2 vfoo_mix_2_f_d = float2(f2, vbar3.z);							eq(vfoo_mix_2_f_d, f2, vbar3.z);
	float2 vfoo_mix_2_f_e = float2(f3, f4);									eq(vfoo_mix_2_f_e, f3, f4);

	float3 vfoo_mix_3_a = float3(vfoo1, vbar1, vbaz1);						eq(vfoo_mix_3_a, vfoo1.x, vbar1.x, vbaz1.x);
	float3 vfoo_mix_3_b = float3(vfoo2, vbar1);								eq(vfoo_mix_3_b, vfoo2.x, vfoo2.y, vbar1.x);
	float3 vfoo_mix_3_c = float3(vbar1, vbar2);								eq(vfoo_mix_3_c, vbar1.x, vbar2.x, vbar2.y);

	float3 vfoo_mix_3_d = float3(vfoo1, vbar1, vbaz1.x);					eq(vfoo_mix_3_d, vfoo1.x, vbar1.x, vbaz1.x);
	float3 vfoo_mix_3_e = float3(vfoo1, vbar1.x, vbaz1);					eq(vfoo_mix_3_e, vfoo1.x, vbar1.x, vbaz1.x);
	float3 vfoo_mix_3_f = float3(vfoo1.x, vbar1, vbaz1);					eq(vfoo_mix_3_f, vfoo1.x, vbar1.x, vbaz1.x);

	float3 vfoo_mix_3_g = float3(vfoo1, vbar1.x, vbaz1.x);					eq(vfoo_mix_3_g, vfoo1.x, vbar1.x, vbaz1.x);
	float3 vfoo_mix_3_h = float3(vfoo1.x, vbar1, vbaz1.x);					eq(vfoo_mix_3_h, vfoo1.x, vbar1.x, vbaz1.x);
	float3 vfoo_mix_3_i = float3(vfoo1.x, vbar1.x, vbaz1);					eq(vfoo_mix_3_i, vfoo1.x, vbar1.x, vbaz1.x);
	float3 vfoo_mix_3_j = float3(vfoo1.x, vbar1.x, vbaz1.x);				eq(vfoo_mix_3_j, vfoo1.x, vbar1.x, vbaz1.x);

	float3 vfoo_mix_3_f_a = float3(vfoo1, vbar1, f1);						eq(vfoo_mix_3_f_a, vfoo1.x, vbar1.x, f1);
	float3 vfoo_mix_3_f_b = float3(vfoo1, f1, vbaz1);						eq(vfoo_mix_3_f_b, vfoo1.x, f1, vbaz1.x);
	float3 vfoo_mix_3_f_c = float3(f1, vbar1, vbaz1);						eq(vfoo_mix_3_f_c, f1, vbar1.x, vbaz1.x);

	float3 vfoo_mix_3_f_d = float3(vfoo1, f1, f2);							eq(vfoo_mix_3_f_d, vfoo1.x, f1, f2);
	float3 vfoo_mix_3_f_e = float3(f1, vbar1, f2);							eq(vfoo_mix_3_f_e, f1, vbar1.x, f2);
	float3 vfoo_mix_3_f_f = float3(f1, f2, vbaz1);							eq(vfoo_mix_3_f_f, f1, f2, vbaz1);

	float3 vfoo_mix_3_f_g = float3(vfoo1.x, f1, f2);						eq(vfoo_mix_3_f_g, vfoo1.x, f1, f2);
	float3 vfoo_mix_3_f_h = float3(f1, vbar2.y, f2);						eq(vfoo_mix_3_f_h, f1, vbar2.y, f2);
	float3 vfoo_mix_3_f_i = float3(f1, f2, vbaz3.z);						eq(vfoo_mix_3_f_i, f1, f2, vbaz3.z);

	float3 vfoo_mix_3_f_j = float3(vfoo1.x, vbar2.y, f2);					eq(vfoo_mix_3_f_j, vfoo1.x, vbar2.y, f2);
	float3 vfoo_mix_3_f_k = float3(f1, vbar2.y, vbaz3.x);					eq(vfoo_mix_3_f_k, f1, vbar2.y, vbaz3.x);
	float3 vfoo_mix_3_f_l = float3(vfoo1.x, f2, vbaz3.z);					eq(vfoo_mix_3_f_l, vfoo1.x, f2, vbaz3.z);

	float3 vfoo_mix_3_f_m = float3(vfoo2, f1);								eq(vfoo_mix_3_f_m, vfoo2.x, vfoo2.y, f1);
	float3 vfoo_mix_3_f_n = float3(f2, vbar2);								eq(vfoo_mix_3_f_n, f2, vbar2.x, vbar2.y);

	float3 vfoo_mix_3_f_o = float3(vfoo2.xy, f1);							eq(vfoo_mix_3_f_o, vfoo2.x, vfoo2.y, f1);
	float3 vfoo_mix_3_f_p = float3(f2, vbar2.xy);							eq(vfoo_mix_3_f_p, f2, vbar2.x, vbar2.y);

	float4 vfoo_mix_4_a = float4(vbaz1, vbaz2.x, vbaz3.x, 0.5f);			eq(vfoo_mix_4_a, vbaz1.x, vbaz2.x, vbaz3.x, 0.5f);
	float4 vfoo_mix_4_b = float4(vbaz1, vbaz3);								eq(vfoo_mix_4_b, vbaz1.x, vbaz3.x, vbaz3.y, vbaz3.z);
	float4 vfoo_mix_4_c = float4(vbaz3, vbaz1);								eq(vfoo_mix_4_c, vbaz3.x, vbaz3.y, vbaz3.z, vbaz1.x);
	float4 vfoo_mix_4_d = float4(vbaz2, vbar2);								eq(vfoo_mix_4_d, vbaz2.x, vbaz2.y, vbar2.x, vbar2.y);
	float4 vfoo_mix_4_e = float4(vbaz2, vbar1, vbaz1);						eq(vfoo_mix_4_e, vbaz2.x, vbaz2.y, vbar1.x, vbaz1.x);
	float4 vfoo_mix_4_f = float4(vbar1, vbaz2, vbaz1);						eq(vfoo_mix_4_f, vbar1.x, vbaz2.x, vbaz2.y, vbaz1.x);
	float4 vfoo_mix_4_g = float4(vbar1, vbaz1, vbaz2);						eq(vfoo_mix_4_g, vbar1.x, vbaz1.x, vbaz2.x, vbaz2.y);

	float4 vfoo_mix_4_f_a = float4(f1, vfoo1, vbar1, vbaz1);				eq(vfoo_mix_4_f_a, f1, vfoo1, vbar1, vbaz1);
	float4 vfoo_mix_4_f_b = float4(f2, f3, vbar1, vbaz1);					eq(vfoo_mix_4_f_b, f2, f3, vbar1, vbaz1);
	float4 vfoo_mix_4_f_c = float4(f4, f5, f6, vbaz1);						eq(vfoo_mix_4_f_c, f4, f5, f6, vbaz1);

	float4 vfoo_mix_4_f_d = float4(f1, vfoo1.x, vbar2.y, vbaz3.z);			eq(vfoo_mix_4_f_d, f1, vfoo1, vbar2.y, vbaz3.z);
	float4 vfoo_mix_4_f_e = float4(f2, f3, vbar2.y, vbaz3.z);				eq(vfoo_mix_4_f_e, f2, f3, vbar2.y, vbaz3.z);
	float4 vfoo_mix_4_f_f = float4(f4, f5, f6, vbaz3.z);					eq(vfoo_mix_4_f_f, f4, f5, f6, vbaz3.z);

	float4 vfoo_mix_4_f_g = float4(f1, vfoo1, vbar2.y, vbaz3.z);			eq(vfoo_mix_4_f_g, f1, vfoo1, vbar2.y, vbaz3.z);
	float4 vfoo_mix_4_f_h = float4(f2, vfoo1, vbar1, vbaz3.z);				eq(vfoo_mix_4_f_h, f2, vfoo1, vbar1, vbaz3.z);
	float4 vfoo_mix_4_f_i = float4(f3, vfoo1.x, vbar1, vbaz3.z);			eq(vfoo_mix_4_f_i, f3, vfoo1.x, vbar1, vbaz3.z);
	float4 vfoo_mix_4_f_j = float4(f4, vfoo1.x, vbar2.y, vbaz1);			eq(vfoo_mix_4_f_j, f4, vfoo1.x, vbar2.y, vbaz1);

	float4 vfoo_mix_4_f_k = float4(f1, f2, vbar1, vbaz3.z);					eq(vfoo_mix_4_f_k, f1, f2, vbar1, vbaz3.z);
	float4 vfoo_mix_4_f_l = float4(f3, f4, vbar2.y, vbaz1);					eq(vfoo_mix_4_f_l, f3, f4, vbar2.y, vbaz1);

	// Assignment and swizzle

	float1 vassign1 = vfoo1.x;												eq(vassign1.x, vfoo1.x);
	vassign1 = vfoo2.y;														eq(vassign1.x, vfoo2.y);
	vassign1.r = vfoo1;														eq(vassign1.x, vfoo1.x);
	vassign1.r = vfoo2.y;													eq(vassign1.x, vfoo2.y);
	vassign1.r = f1;														eq(vassign1.x, f1);

	float2 vassign2 = vfoo2.yx;												eq(vassign2, vfoo2.y, vfoo2.x);
	vassign2 = vfoo2.yy;													eq(vassign2, vfoo2.y, vfoo2.y);
	vassign2.rg = vfoo2;													eq(vassign2, vfoo2.x, vfoo2.y);
	vassign2.rg = vfoo2.gr;													eq(vassign2, vfoo2.y, vfoo2.x);
	vassign2.rg = f2;														eq(vassign2, f2, f2);

	float3 vassign3 = vfoo3.yxz;											eq(vassign3, vfoo3.y, vfoo3.x, vfoo3.z);
	vassign3 = vfoo3.yyx;													eq(vassign3, vfoo3.y, vfoo3.y, vfoo3.x);
	vassign3.rbg = vfoo3;													eq(vassign3, vfoo3.x, vfoo3.z, vfoo3.y);
	vassign3.rgb = vfoo3.grr;												eq(vassign3, vfoo3.y, vfoo3.x, vfoo3.x);

	float4 vassign4 = vfoo4.yxzw;											eq(vassign4, vfoo4.y, vfoo4.x, vfoo4.z, vfoo4.w);
	vassign4 = vfoo4.yyxx;													eq(vassign4, vfoo4.y, vfoo4.y, vfoo4.x, vfoo4.x);
	vassign4.bgra = vfoo4;													eq(vassign4, vfoo4.b, vfoo4.g, vfoo4.r, vfoo4.a);
	vassign4.rgba = vfoo4.grba;												eq(vassign4, vfoo4.g, vfoo4.r, vfoo4.b, vfoo4.a);

	float2 vneg_swiz_2 = -vfoo2.yx;											assert(vneg_swiz_2.x == -(float)vfoo2.y && vneg_swiz_2.y == -(float)vfoo2.x);

	// Addition

	float1 vadd1 = vfoo1 + vbar1;											eq(vadd1, (float)vfoo1.x + (float)vbar1.x);
	float2 vadd2 = vfoo2 + vbar2;											eq(vadd2, (float)vfoo2.x + (float)vbar2.x, (float)vfoo2.y + (float)vbar2.y);
	float3 vadd3 = vfoo3 + vbar3;											eq(vadd3, (float)vfoo3.x + (float)vbar3.x, (float)vfoo3.y + (float)vbar3.y, (float)vfoo3.z + (float)vbar3.z);
	float4 vadd4 = vfoo4 + vbar4;											eq(vadd4, (float)vfoo4.x + (float)vbar4.x, (float)vfoo4.y + (float)vbar4.y, (float)vfoo4.z + (float)vbar4.z, (float)vfoo4.w + (float)vbar4.w);

	float1 vadd_f_1 = vfoo1 + 0.1f;											eq(vadd_f_1, (float)vfoo1.x + 0.1f);
	float1 vadd_f_1_b = 0.1f + vfoo1;										eq(vadd_f_1, 0.1f + (float)vfoo1.x);
	float2 vadd_f_2 = vfoo2 + 0.2f;											eq(vadd_f_2, (float)vfoo2.x + 0.2f, (float)vfoo2.y + 0.2f);
	float3 vadd_f_3 = vfoo3 + 0.3f;											eq(vadd_f_3, (float)vfoo3.x + 0.3f, (float)vfoo3.y + 0.3f, (float)vfoo3.z + 0.3f);
	float4 vadd_f_4 = vfoo4 + 0.4f;											eq(vadd_f_4, (float)vfoo4.x + 0.4f, (float)vfoo4.y + 0.4f, (float)vfoo4.z + 0.4f, (float)vfoo4.w + 0.4f);

	vadd_f_1 += 0.1f;														eq(vadd_f_1, (float)vfoo1.x + 0.1f + 0.1f);
	vadd_f_2 += 0.2f;														eq(vadd_f_2, (float)vfoo2.x + 0.2f + 0.2f, (float)vfoo2.y + 0.2f + 0.2f);
	vadd_f_3 += 0.3f;														eq(vadd_f_3, (float)vfoo3.x + 0.3f + 0.3f, (float)vfoo3.y + 0.3f + 0.3f, (float)vfoo3.z + 0.3f + 0.3f);
	vadd_f_4 += 0.4f;														eq(vadd_f_4, (float)vfoo4.x + 0.4f + 0.4f, (float)vfoo4.y + 0.4f + 0.4f, (float)vfoo4.z + 0.4f + 0.4f, (float)vfoo4.w + 0.4f + 0.4f);

	float1 vadd_swiz_a_1 = vfoo1 + vbar1.x;									eq(vadd_swiz_a_1, (float)vfoo1 + (float)vbar1.x);
	float1 vadd_swiz_b_1 = vfoo1.r + vbar1.x;								eq(vadd_swiz_b_1, (float)vfoo1.r + (float)vbar1.x);
	float1 vadd_swiz_c_1 = vfoo1.r + vbar1;									eq(vadd_swiz_c_1, (float)vfoo1.r + (float)vbar1);

	float2 vadd_swiz_a_2 = vfoo2 + vbar2.yx;								eq(vadd_swiz_a_2, (float)vfoo2.x + (float)vbar2.y, (float)vfoo2.y + (float)vbar2.x);
	float2 vadd_swiz_b_2 = vfoo2.gr + vbar2.yx;								eq(vadd_swiz_b_2, (float)vfoo2.g + (float)vbar2.y, (float)vfoo2.r + (float)vbar2.x);
	float2 vadd_swiz_c_2 = vfoo2.rg + vbar2;								eq(vadd_swiz_c_2, (float)vfoo2.r + (float)vbar2.x, (float)vfoo2.g + (float)vbar2.y);

	float3 vadd_swiz_a_3 = vfoo3 + vbar3.yxz;								eq(vadd_swiz_a_3, (float)vfoo3.x + (float)vbar3.y, (float)vfoo3.y + (float)vbar3.x, (float)vfoo3.z + (float)vbar3.z);
	float3 vadd_swiz_b_3 = vfoo3.bgr + vbar3.xyz;							eq(vadd_swiz_b_3, (float)vfoo3.b + (float)vbar3.x, (float)vfoo3.g + (float)vbar3.y, (float)vfoo3.r + (float)vbar3.z);
	float3 vadd_swiz_c_3 = vfoo3.bgr + vbar3;								eq(vadd_swiz_c_3, (float)vfoo3.b + (float)vbar3.x, (float)vfoo3.g + (float)vbar3.y, (float)vfoo3.r + (float)vbar3.z);

	float4 vadd_swiz_a_4 = vfoo4 + vbar4.yxzw;								eq(vadd_swiz_a_4, (float)vfoo4.x + (float)vbar4.y, (float)vfoo4.y + (float)vbar4.x, (float)vfoo4.z + (float)vbar4.z, (float)vfoo4.w + (float)vbar4.w);
	float4 vadd_swiz_b_4 = vfoo4.bgra + vbar4.yxzw;							eq(vadd_swiz_b_4, (float)vfoo4.b + (float)vbar4.y, (float)vfoo4.g + (float)vbar4.x, (float)vfoo4.r + (float)vbar4.z, (float)vfoo4.a + (float)vbar4.w);
	float4 vadd_swiz_c_4 = vfoo4.bgra + vbar4;								eq(vadd_swiz_c_4, (float)vfoo4.b + (float)vbar4.x, (float)vfoo4.g + (float)vbar4.y, (float)vfoo4.r + (float)vbar4.z, (float)vfoo4.a + (float)vbar4.w);

	vadd_swiz_a_1 += vfoo1;
	vadd_swiz_b_1 += vfoo1.x;
	vadd_swiz_c_1.x += vfoo1;
	vadd_swiz_c_1.r += vfoo1.r;

	vadd_swiz_a_2 += vfoo2;
	vadd_swiz_b_2 += vfoo2.xy;
	vadd_swiz_c_2.xy += vfoo2;
	vadd_swiz_c_2.gr += vfoo2.rg;

	// Subtraction

	float1 vsub1 = vfoo1 - vbar1;											eq(vsub1, (float)vfoo1.x - (float)vbar1.x);
	float2 vsub2 = vfoo2 - vbar2;											eq(vsub2, (float)vfoo2.x - (float)vbar2.x, (float)vfoo2.y - (float)vbar2.y);
	float3 vsub3 = vfoo3 - vbar3;											eq(vsub3, (float)vfoo3.x - (float)vbar3.x, (float)vfoo3.y - (float)vbar3.y, (float)vfoo3.z - (float)vbar3.z);
	float4 vsub4 = vfoo4 - vbar4;											eq(vsub4, (float)vfoo4.x - (float)vbar4.x, (float)vfoo4.y - (float)vbar4.y, (float)vfoo4.z - (float)vbar4.z, (float)vfoo4.w - (float)vbar4.w);

	float1 vsub_f_1 = vfoo1 - 0.1f;											eq(vsub_f_1, (float)vfoo1.x - 0.1f);
	float2 vsub_f_2 = vfoo2 - 0.2f;											eq(vsub_f_2, (float)vfoo2.x - 0.2f, (float)vfoo2.y - 0.2f);
	float3 vsub_f_3 = vfoo3 - 0.3f;											eq(vsub_f_3, (float)vfoo3.x - 0.3f, (float)vfoo3.y - 0.3f, (float)vfoo3.z - 0.3f);
	float4 vsub_f_4 = vfoo4 - 0.4f;											eq(vsub_f_4, (float)vfoo4.x - 0.4f, (float)vfoo4.y - 0.4f, (float)vfoo4.z - 0.4f, (float)vfoo4.w - 0.4f);

	vsub_f_1 -= 0.1f;														eq(vsub_f_1, (float)vfoo1.x - 0.1f - 0.1f);
	vsub_f_2 -= 0.2f;														eq(vsub_f_2, (float)vfoo2.x - 0.2f - 0.2f, (float)vfoo2.y - 0.2f - 0.2f);
	vsub_f_3 -= 0.3f;														eq(vsub_f_3, (float)vfoo3.x - 0.3f - 0.3f, (float)vfoo3.y - 0.3f - 0.3f, (float)vfoo3.z - 0.3f - 0.3f);
	vsub_f_4 -= 0.4f;														eq(vsub_f_4, (float)vfoo4.x - 0.4f - 0.4f, (float)vfoo4.y - 0.4f - 0.4f, (float)vfoo4.z - 0.4f - 0.4f, (float)vfoo4.w - 0.4f - 0.4f);

	float1 vsub_swiz_a_1 = vfoo1 - vbar1.x;									eq(vsub_swiz_a_1, (float)vfoo1 - (float)vbar1.x);
	float1 vsub_swiz_b_1 = vfoo1.r - vbar1.x;								eq(vsub_swiz_b_1, (float)vfoo1.r - (float)vbar1.x);
	float1 vsub_swiz_c_1 = vfoo1.r - vbar1;									eq(vsub_swiz_c_1, (float)vfoo1.r - (float)vbar1);
	vsub_swiz_c_1.r = vfoo4.r - vbar4.r;

	float2 vsub_swiz_a_2 = vfoo2 - vbar2.yx;								eq(vsub_swiz_a_2, (float)vfoo2.x - (float)vbar2.y, (float)vfoo2.y - (float)vbar2.x);
	float2 vsub_swiz_b_2 = vfoo2.gr - vbar2.yx;								eq(vsub_swiz_b_2, (float)vfoo2.g - (float)vbar2.y, (float)vfoo2.r - (float)vbar2.x);
	float2 vsub_swiz_c_2 = vfoo2.rg - vbar2;								eq(vsub_swiz_c_2, (float)vfoo2.r - (float)vbar2.x, (float)vfoo2.g - (float)vbar2.y);
	vsub_swiz_c_2.gr = vfoo4.rg - vbar4.gr;

	float3 vsub_swiz_a_3 = vfoo3 - vbar3.yxz;								eq(vsub_swiz_a_3, (float)vfoo3.x - (float)vbar3.y, (float)vfoo3.y - (float)vbar3.x, (float)vfoo3.z - (float)vbar3.z);
	float3 vsub_swiz_b_3 = vfoo3.bgr - vbar3.xyz;							eq(vsub_swiz_b_3, (float)vfoo3.b - (float)vbar3.x, (float)vfoo3.g - (float)vbar3.y, (float)vfoo3.r - (float)vbar3.z);
	float3 vsub_swiz_c_3 = vfoo3.bgr - vbar3;								eq(vsub_swiz_c_3, (float)vfoo3.b - (float)vbar3.x, (float)vfoo3.g - (float)vbar3.y, (float)vfoo3.r - (float)vbar3.z);
	vsub_swiz_c_3.bgr = vfoo4.grb - vbar4.gbr;

	float4 vsub_swiz_a_4 = vfoo4 - vbar4.yxzw;								eq(vsub_swiz_a_4, (float)vfoo4.x - (float)vbar4.y, (float)vfoo4.y - (float)vbar4.x, (float)vfoo4.z - (float)vbar4.z, (float)vfoo4.w - (float)vbar4.w);
	float4 vsub_swiz_b_4 = vfoo4.bgra - vbar4.yxzw;							eq(vsub_swiz_b_4, (float)vfoo4.b - (float)vbar4.y, (float)vfoo4.g - (float)vbar4.x, (float)vfoo4.r - (float)vbar4.z, (float)vfoo4.a - (float)vbar4.w);
	float4 vsub_swiz_c_4 = vfoo4.bgra - vbar4;								eq(vsub_swiz_c_4, (float)vfoo4.b - (float)vbar4.x, (float)vfoo4.g - (float)vbar4.y, (float)vfoo4.r - (float)vbar4.z, (float)vfoo4.a - (float)vbar4.w);
	vsub_swiz_c_4.bgra = vfoo4.argb - vbar4.ggbr;

	vadd_swiz_a_1 -= vfoo1;
	vadd_swiz_b_1 -= vfoo1.x;
	vadd_swiz_c_1.x -= vfoo1;
	vadd_swiz_c_1.r -= vfoo1.r;

	vsub_swiz_a_2 -= vfoo2;
	vsub_swiz_b_2 -= vfoo2.xy;
	vsub_swiz_c_2.xy -= vfoo2;
	vsub_swiz_c_2.gr -= vfoo2.rg;

	// Multiplication

	float1 vmul1 = vfoo1 * vbar1;						eq(vmul1, (float)vfoo1.x * (float)vbar1.x);
	float2 vmul2 = vfoo2 * vbar2;						eq(vmul2, (float)vfoo2.x * (float)vbar2.x, (float)vfoo2.y * (float)vbar2.y);
	float3 vmul3 = vfoo3 * vbar3;						eq(vmul3, (float)vfoo3.x * (float)vbar3.x, (float)vfoo3.y * (float)vbar3.y, (float)vfoo3.z * (float)vbar3.z);
	float4 vmul4 = vfoo4 * vbar4;						eq(vmul4, (float)vfoo4.x * (float)vbar4.x, (float)vfoo4.y * (float)vbar4.y, (float)vfoo4.z * (float)vbar4.z, (float)vfoo4.w * (float)vbar4.w);

	float1 vmul_f_1 = vfoo1 * 0.1f;						eq(vmul_f_1, (float)vfoo1.x * 0.1f);
	float2 vmul_f_2 = vfoo2 * 0.2f;						eq(vmul_f_2, (float)vfoo2.x * 0.2f, (float)vfoo2.y * 0.2f);
	float3 vmul_f_3 = vfoo3 * 0.3f;						eq(vmul_f_3, (float)vfoo3.x * 0.3f, (float)vfoo3.y * 0.3f, (float)vfoo3.z * 0.3f);
	float4 vmul_f_4 = vfoo4 * 0.4f;						eq(vmul_f_4, (float)vfoo4.x * 0.4f, (float)vfoo4.y * 0.4f, (float)vfoo4.z * 0.4f, (float)vfoo4.w * 0.4f);

	vmul_f_1 *= 0.1f;									eq(vmul_f_1, (float)vfoo1.x * 0.1f * 0.1f);
	vmul_f_2 *= 0.2f;									eq(vmul_f_2, (float)vfoo2.x * 0.2f * 0.2f, (float)vfoo2.y * 0.2f * 0.2f);
	vmul_f_3 *= 0.3f;									eq(vmul_f_3, (float)vfoo3.x * 0.3f * 0.3f, (float)vfoo3.y * 0.3f * 0.3f, (float)vfoo3.z * 0.3f * 0.3f);
	vmul_f_4 *= 0.4f;									eq(vmul_f_4, (float)vfoo4.x * 0.4f * 0.4f, (float)vfoo4.y * 0.4f * 0.4f, (float)vfoo4.z * 0.4f * 0.4f, (float)vfoo4.w * 0.4f * 0.4f);

	float1 vmul_swiz_a_1 = vfoo1 * vbar1.x;				eq(vmul_swiz_a_1, (float)vfoo1 * (float)vbar1.x);
	float1 vmul_swiz_b_1 = vfoo1.r * vbar1.x;			eq(vmul_swiz_b_1, (float)vfoo1.r * (float)vbar1.x);
	float1 vmul_swiz_c_1 = vfoo1.r * vbar1;				eq(vmul_swiz_c_1, (float)vfoo1.r * (float)vbar1);

	float2 vmul_swiz_a_2 = vfoo2 * vbar2.yx;			eq(vmul_swiz_a_2, (float)vfoo2.x * (float)vbar2.y, (float)vfoo2.y * (float)vbar2.x);
	float2 vmul_swiz_b_2 = vfoo2.gr * vbar2.yx;			eq(vmul_swiz_b_2, (float)vfoo2.g * (float)vbar2.y, (float)vfoo2.r * (float)vbar2.x);
	float2 vmul_swiz_c_2 = vfoo2.rg * vbar2;			eq(vmul_swiz_c_2, (float)vfoo2.r * (float)vbar2.x, (float)vfoo2.g * (float)vbar2.y);

	float3 vmul_swiz_a_3 = vfoo3 * vbar3.yxz;			eq(vmul_swiz_a_3, (float)vfoo3.x * (float)vbar3.y, (float)vfoo3.y * (float)vbar3.x, (float)vfoo3.z * (float)vbar3.z);
	float3 vmul_swiz_b_3 = vfoo3.rgb * vbar3.xyz;		eq(vmul_swiz_b_3, (float)vfoo3.r * (float)vbar3.x, (float)vfoo3.g * (float)vbar3.y, (float)vfoo3.b * (float)vbar3.z);
	float3 vmul_swiz_c_3 = vfoo3.bgr * vbar3;			eq(vmul_swiz_c_3, (float)vfoo3.b * (float)vbar3.x, (float)vfoo3.g * (float)vbar3.y, (float)vfoo3.r * (float)vbar3.z);

	float4 vmul_swiz_b_4 = vfoo4.bgra * vbar4.yxzw;		eq(vmul_swiz_b_4, (float)vfoo4.b * (float)vbar4.y, (float)vfoo4.g * (float)vbar4.x, (float)vfoo4.r * (float)vbar4.z, (float)vfoo4.a * (float)vbar4.w);
	float4 vmul_swiz_c_4 = vfoo4.bgra * vbar4;			eq(vmul_swiz_c_4, (float)vfoo4.b * (float)vbar4.x, (float)vfoo4.g * (float)vbar4.y, (float)vfoo4.r * (float)vbar4.z, (float)vfoo4.a * (float)vbar4.w);
	float4 vmul_swiz_a_4 = vfoo4 * vbar4.yxzw;			eq(vmul_swiz_a_4, (float)vfoo4.x * (float)vbar4.y, (float)vfoo4.y * (float)vbar4.x, (float)vfoo4.z * (float)vbar4.z, (float)vfoo4.w * (float)vbar4.w);

	vmul_swiz_a_2 *= vfoo2;
	vmul_swiz_b_2 *= vfoo2.xy;
	vmul_swiz_c_2.xy *= vfoo2;
	vmul_swiz_c_2.gr *= vfoo2.rg;

	// Division

	float tolDiv = 1e-2f;

	float1 vdiv1 = vfoo1 / vbar1;						eq(vdiv1, div(vfoo1.x, vbar1.x), tolDiv);
	float2 vdiv2 = vfoo2 / vbar2;						eq(vdiv2, div(vfoo2.x, vbar2.x), div(vfoo2.y, vbar2.y), tolDiv);
	float3 vdiv3 = vfoo3 / vbar3;						eq(vdiv3, div(vfoo3.x, vbar3.x), div(vfoo3.y, vbar3.y), div(vfoo3.z, vbar3.z), tolDiv);
	float4 vdiv4 = vfoo4 / vbar4;						eq(vdiv4, div(vfoo4.x, vbar4.x), div(vfoo4.y, vbar4.y), div(vfoo4.z, vbar4.z), div(vfoo4.w, vbar4.w), tolDiv);

	float1 vdiv_f_1 = vfoo1 / 0.1f;						eq(vdiv_f_1, div(vfoo1.x, 0.1f), tolDiv);
	float2 vdiv_f_2 = vfoo2 / 0.2f;						eq(vdiv_f_2, div(vfoo2.x, 0.2f), div(vfoo2.y, 0.2f), tolDiv);
	float3 vdiv_f_3 = vfoo3 / 0.3f;						eq(vdiv_f_3, div(vfoo3.x, 0.3f), div(vfoo3.y, 0.3f), div(vfoo3.z, 0.3f), tolDiv);
	float4 vdiv_f_4 = vfoo4 / 0.4f;						eq(vdiv_f_4, div(vfoo4.x, 0.4f), div(vfoo4.y, 0.4f), div(vfoo4.z, 0.4f), div(vfoo4.w, 0.4f), tolDiv);

	vdiv_f_1 /= 0.1f;									eq(vdiv_f_1, div(div(vfoo1.x, 0.1f), 0.1f), tolDiv);
	vdiv_f_2 /= 0.2f;									eq(vdiv_f_2, div(div(vfoo2.x, 0.2f), 0.2f), div(div(vfoo2.y, 0.2f), 0.2f), tolDiv);
	vdiv_f_3 /= 0.3f;									eq(vdiv_f_3, div(div(vfoo3.x, 0.3f), 0.3f), div(div(vfoo3.y, 0.3f), 0.3f), div(div(vfoo3.z, 0.3f), 0.3f), tolDiv);
	vdiv_f_4 /= 0.4f;									eq(vdiv_f_4, div(div(vfoo4.x, 0.4f), 0.4f), div(div(vfoo4.y, 0.4f), 0.4f), div(div(vfoo4.z, 0.4f), 0.4f), div(div(vfoo4.w, 0.4f), 0.4f), tolDiv);

	float1 vdiv_swiz_a_1 = vfoo1 / vbar1.x;				eq(vdiv_swiz_a_1, div(vfoo1.x, vbar1.x), tolDiv);
	float1 vdiv_swiz_b_1 = vfoo1.r / vbar1.x;			eq(vdiv_swiz_b_1, div(vfoo1.r, vbar1.x), tolDiv);
	float1 vdiv_swiz_c_1 = vfoo1.r / vbar1;				eq(vdiv_swiz_c_1, div(vfoo1.r, vbar1), tolDiv);

	float2 vdiv_swiz_a_2 = vfoo2 / vbar2.yx;			eq(vdiv_swiz_a_2, div(vfoo2.x, vbar2.y), div(vfoo2.y, vbar2.x), tolDiv);
	float2 vdiv_swiz_b_2 = vfoo2.gr / vbar2.yx;			eq(vdiv_swiz_b_2, div(vfoo2.g, vbar2.y), div(vfoo2.r, vbar2.x), tolDiv);
	float2 vdiv_swiz_c_2 = vfoo2.rg / vbar2;			eq(vdiv_swiz_c_2, div(vfoo2.r, vbar2.x), div(vfoo2.g, vbar2.y), tolDiv);

	float3 vdiv_swiz_a_3 = vfoo3 / vbar3.yxz;			eq(vdiv_swiz_a_3, div(vfoo3.x, vbar3.y), div(vfoo3.y, vbar3.x), div(vfoo3.z, vbar3.z), tolDiv);
	float3 vdiv_swiz_b_3 = vfoo3.rgb / vbar3.xyz;		eq(vdiv_swiz_b_3, div(vfoo3.r, vbar3.x), div(vfoo3.g, vbar3.y), div(vfoo3.b, vbar3.z), tolDiv);
	float3 vdiv_swiz_c_3 = vfoo3.bgr / vbar3;			eq(vdiv_swiz_c_3, div(vfoo3.b, vbar3.x), div(vfoo3.g, vbar3.y), div(vfoo3.r, vbar3.z), tolDiv);

	float4 vdiv_swiz_a_4 = vfoo4 / vbar4.yxzw;			eq(vdiv_swiz_a_4, div(vfoo4.x, vbar4.y), div(vfoo4.y, vbar4.x), div(vfoo4.z, vbar4.z), div(vfoo4.w, vbar4.w), tolDiv);
	float4 vdiv_swiz_b_4 = vfoo4.bgra / vbar4.yxzw;		eq(vdiv_swiz_b_4, div(vfoo4.b, vbar4.y), div(vfoo4.g, vbar4.x), div(vfoo4.r, vbar4.z), div(vfoo4.a, vbar4.w), tolDiv);
	float4 vdiv_swiz_c_4 = vfoo4.bgar / vbar4;			eq(vdiv_swiz_c_4, div(vfoo4.b, vbar4.x), div(vfoo4.g, vbar4.y), div(vfoo4.a, vbar4.z), div(vfoo4.r, vbar4.w), tolDiv);

	vdiv_swiz_a_2 /= vfoo2;
	vdiv_swiz_b_2 /= vfoo2.xy;
	vdiv_swiz_c_2.xy /= vfoo2;
	vdiv_swiz_c_2.gr /= vfoo2.rg;

	// Comparison

	float1 vgt1 = vfoo1 > vbar1;							eq(vgt1, (float)vfoo1.x > (float)vbar1.x);
	float2 vgt2 = vfoo2 > vbar2;							eq(vgt2, (float)vfoo2.x > (float)vbar2.x, (float)vfoo2.y > (float)vbar2.y);
	float3 vgt3 = vfoo3 > vbar3;							eq(vgt3, (float)vfoo3.x > (float)vbar3.x, (float)vfoo3.y > (float)vbar3.y, (float)vfoo3.z > (float)vbar3.z);
	float4 vgt4 = vfoo4 > vbar4;							eq(vgt4, (float)vfoo4.x > (float)vbar4.x, (float)vfoo4.y > (float)vbar4.y, (float)vfoo4.z > (float)vbar4.z, (float)vfoo4.w > (float)vbar4.w);

	float1 vlt1 = vfoo1 < vbar1;							eq(vlt1, (float)vfoo1.x < (float)vbar1.x);
	float2 vlt2 = vfoo2 < vbar2;							eq(vlt2, (float)vfoo2.x < (float)vbar2.x, (float)vfoo2.y < (float)vbar2.y);
	float3 vlt3 = vfoo3 < vbar3;							eq(vlt3, (float)vfoo3.x < (float)vbar3.x, (float)vfoo3.y < (float)vbar3.y, (float)vfoo3.z < (float)vbar3.z);
	float4 vlt4 = vfoo4 < vbar4;							eq(vlt4, (float)vfoo4.x < (float)vbar4.x, (float)vfoo4.y < (float)vbar4.y, (float)vfoo4.z < (float)vbar4.z, (float)vfoo4.w < (float)vbar4.w);

	float1 vge1 = vfoo1 >= vbar1;							eq(vge1, (float)vfoo1.x >= (float)vbar1.x);
	float2 vge2 = vfoo2 >= vbar2;							eq(vge2, (float)vfoo2.x >= (float)vbar2.x, (float)vfoo2.y >= (float)vbar2.y);
	float3 vge3 = vfoo3 >= vbar3;							eq(vge3, (float)vfoo3.x >= (float)vbar3.x, (float)vfoo3.y >= (float)vbar3.y, (float)vfoo3.z >= (float)vbar3.z);
	float4 vge4 = vfoo4 >= vbar4;							eq(vge4, (float)vfoo4.x >= (float)vbar4.x, (float)vfoo4.y >= (float)vbar4.y, (float)vfoo4.z >= (float)vbar4.z, (float)vfoo4.w >= (float)vbar4.w);

	float1 vle1 = vfoo1 <= vbar1;							eq(vle1, (float)vfoo1.x <= (float)vbar1.x);
	float2 vle2 = vfoo2 <= vbar2;							eq(vle2, (float)vfoo2.x <= (float)vbar2.x, (float)vfoo2.y <= (float)vbar2.y);
	float3 vle3 = vfoo3 <= vbar3;							eq(vle3, (float)vfoo3.x <= (float)vbar3.x, (float)vfoo3.y <= (float)vbar3.y, (float)vfoo3.z <= (float)vbar3.z);
	float4 vle4 = vfoo4 <= vbar4;							eq(vle4, (float)vfoo4.x <= (float)vbar4.x, (float)vfoo4.y <= (float)vbar4.y, (float)vfoo4.z <= (float)vbar4.z, (float)vfoo4.w <= (float)vbar4.w);

	float1 veq1 = vfoo1 == vbar1;							eq(veq1, (float)vfoo1.x == (float)vbar1.x);
	float2 veq2 = vfoo2 == vbar2;							eq(veq2, (float)vfoo2.x == (float)vbar2.x, (float)vfoo2.y == (float)vbar2.y);
	float3 veq3 = vfoo3 == vbar3;							eq(veq3, (float)vfoo3.x == (float)vbar3.x, (float)vfoo3.y == (float)vbar3.y, (float)vfoo3.z == (float)vbar3.z);
	float4 veq4 = vfoo4 == vbar4;							eq(veq4, (float)vfoo4.x == (float)vbar4.x, (float)vfoo4.y == (float)vbar4.y, (float)vfoo4.z == (float)vbar4.z, (float)vfoo4.w == (float)vbar4.w);

	float1 vneq1 = vfoo1 != vbar1;							eq(vneq1, (float)vfoo1.x != (float)vbar1.x);
	float2 vneq2 = vfoo2 != vbar2;							eq(vneq2, (float)vfoo2.x != (float)vbar2.x, (float)vfoo2.y != (float)vbar2.y);
	float3 vneq3 = vfoo3 != vbar3;							eq(vneq3, (float)vfoo3.x != (float)vbar3.x, (float)vfoo3.y != (float)vbar3.y, (float)vfoo3.z != (float)vbar3.z);
	float4 vneq4 = vfoo4 != vbar4;							eq(vneq4, (float)vfoo4.x != (float)vbar4.x, (float)vfoo4.y != (float)vbar4.y, (float)vfoo4.z != (float)vbar4.z, (float)vfoo4.w != (float)vbar4.w);

	float1 vneg_1 = -vbar1.r;								eq(vneg_1, -vbar1.r);
	float2 vneg_2 = -vbar2.gr;								eq(vneg_2, (float)-vbar2.g, (float)-vbar2.r);
	float3 vneg_3 = -vbar3.bgg;								eq(vneg_3, (float)-vbar3.b, (float)-vbar3.g, (float)-vbar3.g);
	float4 vneg_4 = -vbar4.rbgr;							eq(vneg_4, (float)-vbar4.r, (float)-vbar4.b, (float)-vbar4.g, (float)-vbar4.r);

	float1 vabs1 = abs(vfoo1);								eq(vabs1, abs((float)vfoo1.x));
	float2 vabs2 = abs(vfoo2);								eq(vabs2, abs((float)vfoo2.x), abs((float)vfoo2.y));
	float3 vabs3 = abs(vfoo3);								eq(vabs3, abs((float)vfoo3.x), abs((float)vfoo3.y), abs((float)vfoo3.z));
	float4 vabs4 = abs(vfoo4);								eq(vabs4, abs((float)vfoo4.x), abs((float)vfoo4.y), abs((float)vfoo4.z), abs((float)vfoo4.w));

	float1 vabsneg_1 = abs(-vfoo1);							eq(vabsneg_1, abs((float)-vfoo1));
	float2 vabsneg_2 = abs(-vfoo2);							eq(vabsneg_2, abs((float)-vfoo2.x), abs((float)-vfoo2.y));
	float3 vabsneg_3 = abs(-vfoo3);							eq(vabsneg_3, abs((float)-vfoo3.x), abs((float)-vfoo3.y), abs((float)-vfoo3.z));
	float4 vabsneg_4 = abs(-vfoo4);							eq(vabsneg_4, abs((float)-vfoo4.x), abs((float)-vfoo4.y), abs((float)-vfoo4.z), abs((float)-vfoo4.w));

	float1 vabs_swiz_1 = abs(vfoo1.r);						eq(vabs_swiz_1, abs((float)vfoo1.x));
	float2 vabs_swiz_2 = abs(vfoo2.yx);						eq(vabs_swiz_2, abs((float)vfoo2.g), abs((float)vfoo2.r));
	float3 vabs_swiz_3 = abs(vfoo3.bgr);					eq(vabs_swiz_3, abs((float)vfoo3.b), abs((float)vfoo3.g), abs((float)vfoo3.r));
	float4 vabs_swiz_4 = abs(vfoo4.wwww);					eq(vabs_swiz_4, abs((float)vfoo4.a), abs((float)vfoo4.a), abs((float)vfoo4.a), abs((float)vfoo4.a));

	// For transcendental functions, we loop through the valid range and calculate the maximum error

	// Max abs error [SSE : 1.54972076e-6] [NEON : ]
	// maxErrorExhaustive(hlslpp::acos, std::acos, "acos", -1.0f, 1.0f);

	// Max abs error [SSE : 1.5348196e-6] [NEON : ]
	// maxErrorExhaustive(hlslpp::asin, std::asin, "asin", -1.0f, 1.0f);

	// Max abs error [SSE : 2.74181366e-6] [NEON : ]
	// maxErrorExhaustive(hlslpp::atan, std::atan, "atan", -1.0f, 1.0f);

	//float1 test1 = -9910.1543f;
	//float1 tanTest1 = cos(test1);
	//float tanTests1 = cos(-9910.1543f);

	//float1 test1 = -9911.72559f;
	//float1 tanTest1 = sin(test1);
	//float tanTests1 = sin(-9911.72559f);

	//float1 test2 = 1.57079637f;
	//float1 tanTest2 = tan(test2);
	//float tanTests2 = tan(1.57079637f);

	// Max abs error [SSE : 8.6594373e-6] [NEON : ]
	//maxErrorExhaustive(hlslpp::cos, std::cos, "cos", -10000.0f, 10000.0f);

	// Max abs error [SSE : 5.60283661e-6] [NEON : ]
	//maxErrorExhaustive(hlslpp::sin, std::sin, "sin", -10000.0f, 10000.0f);

	// Max abs error [SSE : 2.38418579e-6] [NEON : ]
	// It's hard to get a good error estimate on a big range since in all multiples of pi/2 the numerical discrepancy is huge
	//maxErrorExhaustive(hlslpp::tan, std::tan, "tan", -1.55f, 1.55f);
	//maxErrorExhaustive(hlslpp::tan, std::tan, "tan", 1.55f, 4.7f);
	//maxErrorExhaustive(hlslpp::tan, std::tan, "tan", -4.7f, -1.55f);

	// Max abs error [SSE : 0] [NEON : ]
	// maxErrorExhaustive(hlslpp::sqrt, std::sqrt, "sqrt", 0.0f, FLT_MAX);

	// Max abs error		[SSE : 1.88894e25] [NEON : ]
	// Max relative error	[SSE : 7.671364e-6] [NEON : ]
	//maxErrorExhaustive(hlslpp::exp, std::exp, "exp", -70.0f, 70.0f);

	// Max abs error		[SSE : 3.022314e23] [NEON : ]
	// Max relative error	[SSE : 3.50801372e-7] [NEON : ]
	// The exp family of functions has a huge range and at very high numbers the precision breaks. However the relative
	// error remains quite small
	//maxErrorExhaustive(hlslpp::exp2, std::exp2, "exp2", -100.0f, 100.0f);

	// Max abs error		[SSE : 2.28881836e-5] [NEON : ]
	//maxErrorExhaustive(hlslpp::log, std::log, "log", 1e-36f, FLT_MAX);

	// Max abs error		[SSE : 1.52587891e-5] [NEON : ]
	//maxErrorExhaustive(hlslpp::log2, std::log2, "log2", 1e-36f, FLT_MAX);

	// Max abs error		[SSE : 3.43322754e-5] [NEON : ]
	//maxErrorExhaustive(hlslpp::log10, std::log10, "log10", 1e-36f, FLT_MAX);

	// Max abs error [SSE : 0] [NEON : ]
	//maxErrorExhaustive(hlslpp::frac, hlslpp_unit::frac, "frac", -FLT_MAX, FLT_MAX);

	bool vall1 = all(vfoo1);				eq(vall1, vfoo1.x != 0.0f);
	bool vall2 = all(vfoo2);				eq(vall2, vfoo2.x != 0.0f && vfoo2.y != 0.0f);
	bool vall3 = all(vfoo3);				eq(vall3, vfoo3.x != 0.0f && vfoo3.y != 0.0f && vfoo3.z != 0.0f);
	bool vall4 = all(vfoo4);				eq(vall4, vfoo4.x != 0.0f && vfoo4.y != 0.0f && vfoo4.z != 0.0f && vfoo4.w != 0.0f);

	bool vall_swiz_1 = all(vfoo1.r);		eq(vall_swiz_1, vfoo1.r != 0.0f);
	bool vall_swiz_2 = all(vfoo2.yx);		eq(vall_swiz_2, vfoo2.y != 0.0f && vfoo2.x != 0.0f);
	bool vall_swiz_3 = all(vfoo3.bgr);		eq(vall_swiz_3, vfoo3.b != 0.0f && vfoo3.g != 0.0f && vfoo3.r != 0.0f);
	bool vall_swiz_4 = all(vfoo4.wwww);		eq(vall_swiz_4, vfoo4.w != 0.0f);

	bool vany1 = any(vfoo1);				eq(vany1, vfoo1.x != 0.0f);
	bool vany2 = any(vfoo2);				eq(vany2, vfoo2.x != 0.0f || vfoo2.y != 0.0f);
	bool vany3 = any(vfoo3);				eq(vany3, vfoo3.x != 0.0f || vfoo3.y != 0.0f || vfoo3.z != 0.0f);
	bool vany4 = any(vfoo4);				eq(vany4, vfoo4.x != 0.0f || vfoo4.y != 0.0f || vfoo4.z != 0.0f || vfoo4.w != 0.0f);

	bool vany_swiz_1 = any(vfoo1.r);		eq(vany_swiz_1, vfoo1.x != 0.0f);
	bool vany_swiz_2 = any(vfoo2.yx);		eq(vany_swiz_2, vfoo2.y != 0.0f || vfoo2.x != 0.0f);
	bool vany_swiz_3 = any(vfoo3.bgr);		eq(vany_swiz_3, vfoo3.b != 0.0f || vfoo3.g != 0.0f || vfoo3.r != 0.0f);
	bool vany_swiz_4 = any(vfoo4.wwww);		eq(vany_swiz_4, vfoo4.w != 0.0f);

	float1 vacos1 = acos(vfoo1);
	float2 vacos2 = acos(vfoo2);
	float3 vacos3 = acos(vfoo3);
	float4 vacos4 = acos(vfoo4);

	float1 vacos_swiz_1 = acos(vfoo1.r);
	float2 vacos_swiz_2 = acos(vfoo2.yx);
	float3 vacos_swiz_3 = acos(vfoo3.bgr);
	float4 vacos_swiz_4 = acos(vfoo4.wwww);

	float1 vasin1 = asin(vfoo1);
	float2 vasin2 = asin(vfoo2);
	float3 vasin3 = asin(vfoo3);
	float4 vasin4 = asin(vfoo4);

	float1 vasin_swiz_1 = asin(vfoo1.r);
	float2 vasin_swiz_2 = asin(vfoo2.yx);
	float3 vasin_swiz_3 = asin(vfoo3.bgr);
	float4 vasin_swiz_4 = asin(vfoo4.wwww);

	float1 vatan1 = atan(vfoo1);
	float2 vatan2 = atan(vfoo2);
	float3 vatan3 = atan(vfoo3);
	float4 vatan4 = atan(vfoo4);

	float1 vatan_swiz_1 = atan(vfoo1.r);
	float2 vatan_swiz_2 = atan(vfoo2.yx);
	float3 vatan_swiz_3 = atan(vfoo3.bgr);
	float4 vatan_swiz_4 = atan(vfoo4.wwww);

	float1 vceil1 = ceil(vfoo1);							eq(vceil1, ceil((float)vfoo1.x));
	float2 vceil2 = ceil(vfoo2);							eq(vceil2, ceil((float)vfoo2.x), ceil((float)vfoo2.y));
	float3 vceil3 = ceil(vfoo3);							eq(vceil3, ceil((float)vfoo3.x), ceil((float)vfoo3.y), ceil((float)vfoo3.z));
	float4 vceil4 = ceil(vfoo4);							eq(vceil4, ceil((float)vfoo4.x), ceil((float)vfoo4.y), ceil((float)vfoo4.z), ceil((float)vfoo4.w));

	float1 vceil_swiz_1 = ceil(vfoo1.r);					eq(vceil_swiz_1, ceil((float)vfoo1.r));
	float2 vceil_swiz_2 = ceil(vfoo2.xx);					eq(vceil_swiz_2, ceil((float)vfoo2.x), ceil((float)vfoo2.x));
	float3 vceil_swiz_3 = ceil(vfoo3.rrg);					eq(vceil_swiz_3, ceil((float)vfoo3.r), ceil((float)vfoo3.r), ceil((float)vfoo3.g));
	float4 vceil_swiz_4 = ceil(vfoo4.yzwx);					eq(vceil_swiz_4, ceil((float)vfoo4.y), ceil((float)vfoo4.z), ceil((float)vfoo4.w), ceil((float)vfoo4.x));

	float1 vclamp1 = clamp(vfoo1, vbar1, vbaz1);
	float2 vclamp2 = clamp(vfoo2, vbar2, vbaz2);
	float3 vclamp3 = clamp(vfoo3, vbar3, vbaz3);
	float4 vclamp4 = clamp(vfoo4, vbar4, vbaz4);

	float1 vclamp_swiz_1 = clamp(vfoo1.r, vbar1, vbaz1);
	float2 vclamp_swiz_2 = clamp(vfoo2.yx, vbar2, vbaz2);
	float3 vclamp_swiz_3 = clamp(vfoo3.xxy, vbar3, vbaz3);
	float4 vclamp_swiz_4 = clamp(vfoo4.wwxy, vbar4, vbaz4);

	float1 vcos1 = cos(vfoo1);
	float2 vcos2 = cos(vfoo2);
	float3 vcos3 = cos(vfoo3);
	float4 vcos4 = cos(vfoo4);

	float1 vcos_swiz_1 = cos(vfoo1.x);
	float2 vcos_swiz_2 = cos(vfoo2.yy);
	float3 vcos_swiz_3 = cos(vfoo3.rrg);
	float4 vcos_swiz_4 = cos(vfoo4.rrbg);

	float1 vcosh1 = cosh(vfoo1);
	float2 vcosh2 = cosh(vfoo2);
	float3 vcosh3 = cosh(vfoo3);
	float4 vcosh4 = cosh(vfoo4);

	float1 vcosh_swiz_1 = cosh(vfoo1.x);
	float2 vcosh_swiz_2 = cosh(vfoo2.yy);
	float3 vcosh_swiz_3 = cosh(vfoo3.rrg);
	float4 vcosh_swiz_4 = cosh(vfoo4.rrbg);

	float3 vcross3 = cross(vfoo3, vbar3);
	float3 vcross_swiz_3_a = cross(vfoo3, vbar3.yyx);
	float3 vcross_swiz_3_b = cross(vfoo3.xyz, vbar3);
	float3 vcross_swiz_3_c = cross(vfoo3.yzx, vbar3.yyx);

	float1 vdot2 = dot(vfoo2, vbar2);
	float1 vdot2_a = dot(vfoo2, vbar2.yx);
	float1 vdot2_b = dot(vfoo2.rg, vbar2);
	float1 vdot2_c = dot(vfoo2.gr, vbar2.yx);

	float1 vdot3 = dot(vfoo3, vbar3);
	float1 vdot3_a = dot(vfoo3, vbar3.bgr);
	float1 vdot3_b = dot(vfoo3.rrg, vbar3);
	float1 vdot3_c = dot(vfoo3.rrg, vbar3);

	float1 vdot4 = dot(vfoo4, vbar4);
	float1 vdot4_a = dot(vfoo4, vbar4.bgra);
	float1 vdot4_b = dot(vfoo4.rrgb, vbar4);
	float1 vdot4_c = dot(vfoo4.rrgg, vbar4);

	float1 vfloor1 = floor(vfoo1);					eq(vfloor1, floor((float)vfoo1.x));
	float2 vfloor2 = floor(vfoo2);					eq(vfloor2, floor((float)vfoo2.x), floor((float)vfoo2.y));
	float3 vfloor3 = floor(vfoo3);					eq(vfloor3, floor((float)vfoo3.x), floor((float)vfoo3.y), floor((float)vfoo3.z));
	float4 vfloor4 = floor(vfoo4);					eq(vfloor4, floor((float)vfoo4.x), floor((float)vfoo4.y), floor((float)vfoo4.z), floor((float)vfoo4.w));

	float1 vfloor_swiz_1 = floor(vfoo1.r);			eq(vfloor_swiz_1, floor((float)vfoo1.r));
	float2 vfloor_swiz_2 = floor(vfoo2.yx);			eq(vfloor_swiz_2, floor((float)vfoo2.y), floor((float)vfoo2.x));
	float3 vfloor_swiz_3 = floor(vfoo3.xxy);		eq(vfloor_swiz_3, floor((float)vfoo3.x), floor((float)vfoo3.x), floor((float)vfoo3.y));
	float4 vfloor_swiz_4 = floor(vfoo4.wwxy);		eq(vfloor_swiz_4, floor((float)vfoo4.w), floor((float)vfoo4.w), floor((float)vfoo4.x), floor((float)vfoo4.y));

	float1 vfmod1 = fmod(vfoo1, vbar1);
	float2 vfmod2 = fmod(vfoo2, vbar2);
	float3 vfmod3 = fmod(vfoo3, vbar3);
	float4 vfmod4 = fmod(vfoo4, vbar4);

	float1 vfrac1 = frac(vfoo1);
	float2 vfrac2 = frac(vfoo2);
	float3 vfrac3 = frac(vfoo3);
	float4 vfrac4 = frac(vfoo4);

	float1 vfrac_swiz_1 = frac(vfoo1.r);
	float2 vfrac_swiz_2 = frac(vfoo2.xy);
	float3 vfrac_swiz_3 = frac(vfoo3.bgr);
	float4 vfrac_swiz_4 = frac(vfoo4.wzzy);

	float1 vexp1 = exp(vfoo1);
	float2 vexp2 = exp(vfoo2);
	float3 vexp3 = exp(vfoo3);
	float4 vexp4 = exp(vfoo4);

	float1 vexp_swiz_1 = exp(vfoo1.r);
	float2 vexp_swiz_2 = exp(vfoo2.yx);
	float3 vexp_swiz_3 = exp(vfoo3.brr);
	float4 vexp_swiz_4 = exp(vfoo4.wxzy);

	float1 vexp2_1 = exp2(vfoo1);
	float2 vexp2_2 = exp2(vfoo2);
	float3 vexp2_3 = exp2(vfoo3);
	float4 vexp2_4 = exp2(vfoo4);

	float1 vexp2_swiz_1 = exp2(vfoo1.r);
	float2 vexp2_swiz_2 = exp2(vfoo2.xy);
	float3 vexp2_swiz_3 = exp2(vfoo3.bgr);
	float4 vexp2_swiz_4 = exp2(vfoo4.wxxy);

	float1 visfinite_1 = isfinite(vfoo1);
	float2 visfinite_2 = isfinite(vfoo2);
	float3 visfinite_3 = isfinite(vfoo3);
	float4 visfinite_4 = isfinite(vfoo4);

	float1 visfinite_swiz_1 = isfinite(vfoo1.r);
	float2 visfinite_swiz_2 = isfinite(vfoo2.xy);
	float3 visfinite_swiz_3 = isfinite(vfoo3.bgr);
	float4 visfinite_swiz_4 = isfinite(vfoo4.wxxy);

	float1 visinf_1 = isinf(vfoo1);
	float2 visinf_2 = isinf(vfoo2);
	float3 visinf_3 = isinf(vfoo3);
	float4 visinf_4 = isinf(vfoo4);

	float1 visinf_swiz_1 = isinf(vfoo1.r);
	float2 visinf_swiz_2 = isinf(vfoo2.xy);
	float3 visinf_swiz_3 = isinf(vfoo3.bgr);
	float4 visinf_swiz_4 = isinf(vfoo4.wxxy);

	float1 visnan_1 = isnan(vfoo1);
	float2 visnan_2 = isnan(vfoo2);
	float3 visnan_3 = isnan(vfoo3);
	float4 visnan_4 = isnan(vfoo4);

	float1 visnan_swiz_1 = isnan(vfoo1.r);
	float2 visnan_swiz_2 = isnan(vfoo2.xy);
	float3 visnan_swiz_3 = isnan(vfoo3.bgr);
	float4 visnan_swiz_4 = isnan(vfoo4.wxxy);

	float1 vlength_1 = length(vfoo1);
	float1 vlength_2 = length(vfoo2);
	float1 vlength_3 = length(vfoo3);
	float1 vlength_4 = length(vfoo4);

	float1 vlength_swiz_1 = length(vfoo1.r);
	float1 vlength_swiz_2 = length(vfoo2.xy);
	float1 vlength_swiz_3 = length(vfoo3.rgb);
	float1 vlength_swiz_4 = length(vfoo4.wwxy);

	float1 vlerp1 = lerp(vfoo1, vbar1, vbaz1);					eq(vlerp1, lerpf(vfoo1.r, vbar1.r, vbaz1.r));
	float2 vlerp2 = lerp(vfoo2, vbar2, vbaz2);					eq(vlerp2, lerpf(vfoo2.r, vbar2.r, vbaz2.r), lerpf(vfoo2.g, vbar2.g, vbaz2.g));
	float3 vlerp3 = lerp(vfoo3, vbar3, vbaz3);					eq(vlerp3, lerpf(vfoo3.r, vbar3.r, vbaz3.r), lerpf(vfoo3.g, vbar3.g, vbaz3.g), lerpf(vfoo3.b, vbar3.b, vbaz3.b));
	float4 vlerp4 = lerp(vfoo4, vbar4, vbaz4);					eq(vlerp4, lerpf(vfoo4.r, vbar4.r, vbaz4.r), lerpf(vfoo4.g, vbar4.g, vbaz4.g), lerpf(vfoo4.b, vbar4.b, vbaz4.b), lerpf(vfoo4.a, vbar4.a, vbaz4.a));

	float1 vlerpf_1 = lerp(vfoo1, vbar1, 0.3f);					eq(vlerpf_1, lerpf(vfoo1.r, vbar1.r, 0.3f));
	float2 vlerpf_2 = lerp(vfoo2, vbar2, 0.3f);					eq(vlerpf_2, lerpf(vfoo2.r, vbar2.r, 0.3f), lerpf(vfoo2.g, vbar2.g, 0.3f));
	float3 vlerpf_3 = lerp(vfoo3, vbar3, 0.5f);					eq(vlerpf_3, lerpf(vfoo3.r, vbar3.r, 0.5f), lerpf(vfoo3.g, vbar3.g, 0.5f), lerpf(vfoo3.b, vbar3.b, 0.5f));
	float4 vlerpf_4 = lerp(vfoo4, vbar4, 0.7f);					eq(vlerpf_4, lerpf(vfoo4.r, vbar4.r, 0.7f), lerpf(vfoo4.g, vbar4.g, 0.7f), lerpf(vfoo4.b, vbar4.b, 0.7f), lerpf(vfoo4.a, vbar4.a, 0.7f));

	float1 vlerp_swiz_1 = lerp(vfoo1, vbar1, vbaz1.r);			eq(vlerp_swiz_1, lerpf(vfoo1.r, vbar1.r, vbaz1.r));
	float2 vlerp_swiz_2 = lerp(vfoo2, vbar2, vbaz2.rg);			eq(vlerp_swiz_2, lerpf(vfoo2.r, vbar2.r, vbaz2.r), lerpf(vfoo2.g, vbar2.g, vbaz2.g));
	float3 vlerp_swiz_3 = lerp(vfoo3, vbar3, vbaz3.bgr);		eq(vlerp_swiz_3, lerpf(vfoo3.r, vbar3.r, vbaz3.b), lerpf(vfoo3.g, vbar3.g, vbaz3.g), lerpf(vfoo3.b, vbar3.b, vbaz3.r));
	float4 vlerp_swiz_4 = lerp(vfoo4, vbar4, vbaz4.rgba);		eq(vlerp_swiz_4, lerpf(vfoo4.r, vbar4.r, vbaz4.r), lerpf(vfoo4.g, vbar4.g, vbaz4.g), lerpf(vfoo4.b, vbar4.b, vbaz4.b), lerpf(vfoo4.a, vbar4.a, vbaz4.a));

	float1 vlog1 = log(vfoo1);
	float2 vlog2 = log(vfoo2);
	float3 vlog3 = log(vfoo3);
	float4 vlog4 = log(vfoo4);

	float1 vlog_swiz_1 = log(vfoo1.r);
	float2 vlog_swiz_2 = log(vfoo2.yx);
	float3 vlog_swiz_3 = log(vfoo3.rrg);
	float4 vlog_swiz_4 = log(vfoo4.wwxy);

	float1 vlog2_1 = log2(vfoo1);
	float2 vlog2_2 = log2(vfoo2);
	float3 vlog2_3 = log2(vfoo3);
	float4 vlog2_4 = log2(vfoo4);

	float1 vlog2_swiz_1 = log2(vfoo1.r);
	float2 vlog2_swiz_2 = log2(vfoo2.yx);
	float3 vlog2_swiz_3 = log2(vfoo3.gbr);
	float4 vlog2_swiz_4 = log2(vfoo4.yyxw);

	float1 vlog10_1 = log10(vfoo1);
	float2 vlog10_2 = log10(vfoo2);
	float3 vlog10_3 = log10(vfoo3);
	float4 vlog10_4 = log10(vfoo4);

	float1 vlog10_swiz_1 = log10(vfoo1.r);
	float2 vlog10_swiz_2 = log10(vfoo2.rg);
	float3 vlog10_swiz_3 = log10(vfoo3.yxy);
	float4 vlog10_swiz_4 = log10(vfoo4.yyzw);

	float1 vmin_1 = min(vfoo1, vbar1);
	float2 vmin_2 = min(vfoo2, vbar2);
	float3 vmin_3 = min(vfoo3, vbar3);
	float4 vmin_4 = min(vfoo4, vbar4);

	float1 vmin_swiz_1 = min(vfoo1.r, vbar1.r);
	float2 vmin_swiz_2 = min(vfoo2.gr, vbar2.rg);
	float3 vmin_swiz_3 = min(vfoo3.ggb, vbar3.bgr);
	float4 vmin_swiz_4 = min(vfoo4.gggg, vbar4.brgr);

	float1 vmax_1 = max(vfoo1, vbar1);
	float2 vmax_2 = max(vfoo2, vbar2);
	float3 vmax_3 = max(vfoo3, vbar3);
	float4 vmax_4 = max(vfoo4, vbar4);

	float1 vmax_swiz_1 = max(vfoo1.r, vbar1.x);
	float2 vmax_swiz_2 = max(vfoo2.rg, vbar2.yx);
	float3 vmax_swiz_3 = max(vfoo3.gbr, vbar3.xyy);
	float4 vmax_swiz_4 = max(vfoo4.brga, vbar4.yxzw);

	float1 vnormalize_foo_1 = normalize(vfoo1);
	float2 vnormalize_foo_2 = normalize(vfoo2);
	float3 vnormalize_foo_3 = normalize(vfoo3);
	float4 vnormalize_foo_4 = normalize(vfoo4);

	float1 vnormalize_bar_1 = normalize(vbar1);
	float2 vnormalize_bar_2 = normalize(vbar2);
	float3 vnormalize_bar_3 = normalize(vbar3);
	float4 vnormalize_bar_4 = normalize(vbar4);

	float1 vnormalize_swiz_1 = normalize(vfoo1.r);
	float2 vnormalize_swiz_2 = normalize(vfoo2.rg);
	float3 vnormalize_swiz_3 = normalize(vfoo3.gbr);
	float4 vnormalize_swiz_4 = normalize(vfoo4.brga);

	float1 vpow_1 = pow(vfoo1, vbar1);
	float2 vpow_2 = pow(vfoo2, vbar2);
	float3 vpow_3 = pow(vfoo3, vbar3);
	float4 vpow_4 = pow(vfoo4, vbar4);

	float1 vpow_swiz_1 = pow(vfoo1.r, vbar1.r);
	float2 vpow_swiz_2 = pow(vfoo2.rg, vbar2.xy);
	float3 vpow_swiz_3 = pow(vfoo3.bgr, vbar3.yyx);
	float4 vpow_swiz_4 = pow(vfoo4.yyxw, vbar4.xxyw);

	float1 vpow_swiz_1_a = pow(vfoo1, vbar1.r);
	float2 vpow_swiz_2_a = pow(vfoo2, vbar2.xy);
	float3 vpow_swiz_3_a = pow(vfoo3, vbar3.yyx);
	float4 vpow_swiz_4_a = pow(vfoo4, vbar4.xxyw);

	float1 vpow_swiz_1_b = pow(vfoo1.r, vbar1);
	float2 vpow_swiz_2_b = pow(vfoo2.rg, vbar2);
	float3 vpow_swiz_3_b = pow(vfoo3.bgr, vbar3);
	float4 vpow_swiz_4_b = pow(vfoo4.yyxw, vbar4);

	float1 vradians1 = radians(vfoo1);
	float2 vradians2 = radians(vfoo2);
	float3 vradians3 = radians(vfoo3);
	float4 vradians4 = radians(vfoo4);

	float1 vradians_swiz_1 = radians(vfoo1.r);
	float2 vradians_swiz_2 = radians(vfoo2.rg);
	float3 vradians_swiz_3 = radians(vfoo3.bgr);
	float4 vradians_swiz_4 = radians(vfoo4.yyxw);

	float1 vreflect1 = reflect(vfoo1, vbar1);
	float2 vreflect2 = reflect(vfoo2, vbar2);
	float3 vreflect3 = reflect(vfoo3, vbar3);
	float4 vreflect4 = reflect(vfoo4, vbar4);

	float1 vreflect_swiz_1 = reflect(vfoo1.r, vbar1);
	float2 vreflect_swiz_2 = reflect(vfoo2.xy, vbar2);
	float3 vreflect_swiz_3 = reflect(vfoo3.bgr, vbar3);
	float4 vreflect_swiz_4 = reflect(vfoo4.xxzy, vbar4);

	float1 vreflect_swiz_1_a = reflect(vfoo1, vbar1.r);
	float2 vreflect_swiz_2_a = reflect(vfoo2, vbar2.yx);
	float3 vreflect_swiz_3_a = reflect(vfoo3, vbar3.ggr);
	float4 vreflect_swiz_4_a = reflect(vfoo4, vbar4.wxyy);

	float1 vreflect_swiz_1_b = reflect(vfoo1.r, vbar1.r);
	float2 vreflect_swiz_2_b = reflect(vfoo2.xy, vbar2.yx);
	float3 vreflect_swiz_3_b = reflect(vfoo3.bgr, vbar3.ggr);
	float4 vreflect_swiz_4_b = reflect(vfoo4.xxzy, vbar4.wxyy);

	float1 vrefract1 = refract(vnormalize_foo_1, vnormalize_bar_1, float1(0.1f));
	float2 vrefract2 = refract(vnormalize_foo_2, vnormalize_bar_2, float1(-0.7f));
	float3 vrefract3 = refract(vnormalize_foo_3, vnormalize_bar_3, float1(0.1f));
	float4 vrefract4 = refract(vnormalize_foo_4, vnormalize_bar_4, float1(0.1f));

	float1 vrsqrt1 = rsqrt(vfoo1);
	float2 vrsqrt2 = rsqrt(vfoo2);
	float3 vrsqrt3 = rsqrt(vfoo3);
	float4 vrsqrt4 = rsqrt(vfoo4);

	float1 vrsqrt_swiz_1 = rsqrt(vfoo1.r);
	float2 vrsqrt_swiz_2 = rsqrt(vfoo2.rg);
	float3 vrsqrt_swiz_3 = rsqrt(vfoo3.bgr);
	float4 vrsqrt_swiz_4 = rsqrt(vfoo4.yyxw);

	float1 vround1 = round(vfoo1);
	float2 vround2 = round(vfoo2);
	float3 vround3 = round(vfoo3);
	float4 vround4 = round(vfoo4);

	float1 vround_swiz_1 = round(vfoo1.r);
	float2 vround_swiz_2 = round(vfoo2.gr);
	float3 vround_swiz_3 = round(vfoo3.yyx);
	float4 vround_swiz_4 = round(vfoo4.wwyx);

	float1 vsaturate1 = saturate(vfoo1);
	float2 vsaturate2 = saturate(vfoo2);
	float3 vsaturate3 = saturate(vfoo3);
	float4 vsaturate4 = saturate(vfoo4);

	float1 vsaturate_swiz_1 = saturate(vfoo1.r);
	float2 vsaturate_swiz_2 = saturate(vfoo2.xy);
	float3 vsaturate_swiz_3 = saturate(vfoo3.ggr);
	float4 vsaturate_swiz_4 = saturate(vfoo4.wyyx);

	float1 vsign1 = sign(vfoo1);
	float2 vsign2 = sign(vfoo2);
	float3 vsign3 = sign(vfoo3);
	float4 vsign4 = sign(vfoo4);

	float1 vsign_swiz_1 = sign(vfoo1.x);
	float2 vsign_swiz_2 = sign(vfoo2.gg);
	float3 vsign_swiz_3 = sign(vfoo3.bbb);
	float4 vsign_swiz_4 = sign(vfoo4.xxyz);

	float1 vsin1 = sin(vfoo1);
	float2 vsin2 = sin(vfoo2);
	float3 vsin3 = sin(vfoo3);
	float4 vsin4 = sin(vfoo4);

	float1 vsin_swiz_1 = sin(vfoo1.x);
	float2 vsin_swiz_2 = sin(vfoo2.yy);
	float3 vsin_swiz_3 = sin(vfoo3.rrg);
	float4 vsin_swiz_4 = sin(vfoo4.rrbg);

	float1 vsinh1 = sinh(vfoo1);
	float2 vsinh2 = sinh(vfoo2);
	float3 vsinh3 = sinh(vfoo3);
	float4 vsinh4 = sinh(vfoo4);

	float1 vsinh_swiz_1 = sinh(vfoo1.x);
	float2 vsinh_swiz_2 = sinh(vfoo2.yy);
	float3 vsinh_swiz_3 = sinh(vfoo3.rrg);
	float4 vsinh_swiz_4 = sinh(vfoo4.rrbg);

	float1 vsmoothstep_1 = smoothstep(vfoo1, vfoo1 + 2.0f, vbar1);
	float2 vsmoothstep_2 = smoothstep(vfoo2, vfoo2 + 5.0f, vbar2);
	float3 vsmoothstep_3 = smoothstep(vfoo3, vfoo3 + 8.0f, vbar3);
	float4 vsmoothstep_4 = smoothstep(vfoo4, vfoo4 + 3.0f, vbar4);

	float1 vsmoothstep_swiz_1 = smoothstep(vfoo1.x, vfoo1.x, vfoo1.x);
	float2 vsmoothstep_swiz_2 = smoothstep(vfoo2.yy, vfoo2.yy, vfoo2.yy);
	float3 vsmoothstep_swiz_3 = smoothstep(vfoo3.rrg, vfoo3.rrg, vfoo3.rrg);
	float4 vsmoothstep_swiz_4 = smoothstep(vfoo4.rrbg, vfoo4.rrbg, vfoo4.rrbg);

	float1 vsqrt1 = sqrt(vfoo1);
	float2 vsqrt2 = sqrt(vfoo2);
	float3 vsqrt3 = sqrt(vfoo3);
	float4 vsqrt4 = sqrt(vfoo4);

	float1 vsqrt_swiz_1 = sqrt(vfoo1.r);
	float2 vsqrt_swiz_2 = sqrt(vfoo2.rr);
	float3 vsqrt_swiz_3 = sqrt(vfoo3.yyy);
	float4 vsqrt_swiz_4 = sqrt(vfoo4.wwwx);

	float1 vstep1 = step(vfoo1, vbar1);
	float2 vstep2 = step(vfoo2, vbar2);
	float3 vstep3 = step(vfoo3, vbar3);
	float4 vstep4 = step(vfoo4, vbar4);

	float1 vstep_swiz_1 = step(vfoo1, vbar1.x);
	float2 vstep_swiz_2 = step(vfoo2, vbar2.yx);
	float3 vstep_swiz_3 = step(vfoo3, vbar3.xxy);
	float4 vstep_swiz_4 = step(vfoo4, vbar4.zzzw);

	float1 vstep_swiz_1_a = step(vfoo1.x, vbar1);
	float2 vstep_swiz_2_a = step(vfoo2.yx, vbar2);
	float3 vstep_swiz_3_a = step(vfoo3.xxy, vbar3);
	float4 vstep_swiz_4_a = step(vfoo4.zzwx, vbar4);

	float1 vstep_swiz_1_b = step(vfoo1.x, vbar1.x);
	float2 vstep_swiz_2_b = step(vfoo2.yx, vbar2.yx);
	float3 vstep_swiz_3_b = step(vfoo3.xxz, vbar3.xxy);
	float4 vstep_swiz_4_b = step(vfoo4.zwyx, vbar4.zzzw);

	float1 vtan1 = tan(vfoo1);
	float2 vtan2 = tan(vfoo2);
	float3 vtan3 = tan(vfoo3);
	float4 vtan4 = tan(vfoo4);

	float1 vtan_swiz_1 = tan(vfoo1.r);
	float2 vtan_swiz_2 = tan(vfoo2.yy);
	float3 vtan_swiz_3 = tan(vfoo3.zzz);
	float4 vtan_swiz_4 = tan(vfoo4.wwzw);

	float1 vtanh1 = tanh(vfoo1);
	float2 vtanh2 = tanh(vfoo2);
	float3 vtanh3 = tanh(vfoo3);
	float4 vtanh4 = tanh(vfoo4);

	float1 vtanh_swiz_1 = tanh(vfoo1.r);
	float2 vtanh_swiz_2 = tanh(vfoo2.yy);
	float3 vtanh_swiz_3 = tanh(vfoo3.zzz);
	float4 vtanh_swiz_4 = tanh(vfoo4.wwzw);

	float1 vtrunc1 = trunc(vfoo1);				eq(vtrunc1, truncf((float)vfoo1.x));
	float2 vtrunc2 = trunc(vfoo2);				eq(vtrunc2, truncf((float)vfoo2.x), truncf((float)vfoo2.y));
	float3 vtrunc3 = trunc(vfoo3);				eq(vtrunc3, truncf((float)vfoo3.x), truncf((float)vfoo3.y), truncf((float)vfoo3.z));
	float4 vtrunc4 = trunc(vfoo4);				eq(vtrunc4, truncf((float)vfoo4.x), truncf((float)vfoo4.y), truncf((float)vfoo4.z), truncf((float)vfoo4.w));

	float1 vtrunc_swiz_1 = trunc(vfoo1.r);		eq(vtrunc_swiz_1, truncf((float)vfoo1.r));
	float2 vtrunc_swiz_2 = trunc(vfoo2.yy);		eq(vtrunc_swiz_2, truncf((float)vfoo2.y), truncf((float)vfoo2.y));
	float3 vtrunc_swiz_3 = trunc(vfoo3.zzz);	eq(vtrunc_swiz_3, truncf((float)vfoo3.z), truncf((float)vfoo3.z), truncf((float)vfoo3.z));
	float4 vtrunc_swiz_4 = trunc(vfoo4.wwzw);	eq(vtrunc_swiz_4, truncf((float)vfoo4.w), truncf((float)vfoo4.w), truncf((float)vfoo4.z), truncf((float)vfoo4.w));

	vtrunc_swiz_3.zxy--;

	vtrunc_swiz_4++;

	// Storage

	float vstore1[1];
	float vstore2[2];
	float vstore3[3];
	float vstore4[4];

	store(vfoo1, vstore1);			eq(vfoo1, vstore1[0]);
	store(vfoo2, vstore2);			eq(vfoo2, vstore2[0], vstore2[1]);
	store(vfoo3, vstore3);			eq(vfoo3, vstore3[0], vstore3[1], vstore3[2]);
	store(vfoo4, vstore4);			eq(vfoo4, vstore4[0], vstore4[1], vstore4[2], vstore4[3]);

	// Loading

	float vload1[1] = { f10 };
	float vload2[2] = { f11, f12 };
	float vload3[3] = { f13, f14, f15 };
	float vload4[4] = { f16, f17, f18, f19 };

	load(vfoo1, vload1);			eq(vfoo1, vload1[0]);
	load(vfoo2, vload2);			eq(vfoo2, vload2[0], vload2[1]);
	load(vfoo3, vload3);			eq(vfoo3, vload3[0], vload3[1], vload3[2]);
	load(vfoo4, vload4);			eq(vfoo4, vload4[0], vload4[1], vload4[2], vload4[3]);

#if defined(HLSLPP_FLOAT8)

	//-------
	// Float8
	//-------

	float8 vfoo8 = float8(f11, f12, f13, f14, f15, f16, f17, f18);	eq(vfoo8, f11, f12, f13, f14, f15, f16, f17, f18);

	float8 vfoo_dc_8;

	vfoo8 = float8(f11, f12, f13, f14, f15, f16, f17, f18);	eq(vfoo8, f11, f12, f13, f14, f15, f16, f17, f18);

	//float8 vbar8 = vfoo8.bgra;												eq(vbar8, f9, f8, f7, f10);

	float8 vbar8 = float8(f19, f20, f21, f22, f23, f24, f25, f26);	eq(vbar8, f19, f20, f21, f22, f23, f24, f25, f26);

	float8 vbaz8 = float8(0.0f, 0.2f, 0.6f, 1.0f, 1.2f, 1.4f, 1.6f, 1.8f);	eq(vbaz8, 0.0f, 0.2f, 0.6f, 1.0f, 1.2f, 1.4f, 1.6f, 1.8f);

	//float8 vfoo_mix_8_a = float8(vbaz1, vbaz2.x, vbaz3.x, 0.5f);			eq(vfoo_mix_4_a, vbaz1.x, vbaz2.x, vbaz3.x, 0.5f);
	//float8 vfoo_mix_8_b = float8(vbaz1, vbaz3);								eq(vfoo_mix_4_b, vbaz1.x, vbaz3.x, vbaz3.y, vbaz3.z);
	//float8 vfoo_mix_8_c = float8(vbaz3, vbaz1);								eq(vfoo_mix_4_c, vbaz3.x, vbaz3.y, vbaz3.z, vbaz1.x);
	//float8 vfoo_mix_8_d = float8(vbaz2, vbar2);								eq(vfoo_mix_4_d, vbaz2.x, vbaz2.y, vbar2.x, vbar2.y);
	//float8 vfoo_mix_8_e = float8(vbaz2, vbar1, vbaz1);						eq(vfoo_mix_4_e, vbaz2.x, vbaz2.y, vbar1.x, vbaz1.x);
	//float8 vfoo_mix_8_f = float8(vbar1, vbaz2, vbaz1);						eq(vfoo_mix_4_f, vbar1.x, vbaz2.x, vbaz2.y, vbaz1.x);
	//float8 vfoo_mix_8_g = float8(vbar1, vbaz1, vbaz2);						eq(vfoo_mix_4_g, vbar1.x, vbaz1.x, vbaz2.x, vbaz2.y);

	//float8 vfoo_mix_4_f_a = float8(f1, vfoo1, vbar1, vbaz1);				eq(vfoo_mix_4_f_a, f1, vfoo1, vbar1, vbaz1);
	//float8 vfoo_mix_4_f_b = float8(f2, f3, vbar1, vbaz1);					eq(vfoo_mix_4_f_b, f2, f3, vbar1, vbaz1);
	//float8 vfoo_mix_4_f_c = float8(f4, f5, f6, vbaz1);						eq(vfoo_mix_4_f_c, f4, f5, f6, vbaz1);
	//
	//float8 vfoo_mix_4_f_d = float8(f1, vfoo1.x, vbar2.y, vbaz3.z);			eq(vfoo_mix_4_f_d, f1, vfoo1, vbar2.y, vbaz3.z);
	//float8 vfoo_mix_4_f_e = float8(f2, f3, vbar2.y, vbaz3.z);				eq(vfoo_mix_4_f_e, f2, f3, vbar2.y, vbaz3.z);
	//float8 vfoo_mix_4_f_f = float8(f4, f5, f6, vbaz3.z);					eq(vfoo_mix_4_f_f, f4, f5, f6, vbaz3.z);
	//
	//float8 vfoo_mix_4_f_g = float8(f1, vfoo1, vbar2.y, vbaz3.z);			eq(vfoo_mix_4_f_g, f1, vfoo1, vbar2.y, vbaz3.z);
	//float8 vfoo_mix_4_f_h = float8(f2, vfoo1, vbar1, vbaz3.z);				eq(vfoo_mix_4_f_h, f2, vfoo1, vbar1, vbaz3.z);
	//float8 vfoo_mix_4_f_i = float8(f3, vfoo1.x, vbar1, vbaz3.z);			eq(vfoo_mix_4_f_i, f3, vfoo1.x, vbar1, vbaz3.z);
	//float8 vfoo_mix_4_f_j = float8(f4, vfoo1.x, vbar2.y, vbaz1);			eq(vfoo_mix_4_f_j, f4, vfoo1.x, vbar2.y, vbaz1);
	//
	//float8 vfoo_mix_4_f_k = float8(f1, f2, vbar1, vbaz3.z);					eq(vfoo_mix_4_f_k, f1, f2, vbar1, vbaz3.z);
	//float8 vfoo_mix_4_f_l = float8(f3, f4, vbar2.y, vbaz1);					eq(vfoo_mix_4_f_l, f3, f4, vbar2.y, vbaz1);

	// Addition

	float8 vadd8 = vfoo8 + vbar8;
	//eq(vadd8,
	//	(float)vfoo8.x + (float)vbar8.x, (float)vfoo8.y + (float)vbar8.y, (float)vfoo8.z + (float)vbar8.z, (float)vfoo8.w + (float)vbar8.w,	
	//	(float)vfoo8.x + (float)vbar8.x, (float)vfoo8.y + (float)vbar8.y, (float)vfoo8.z + (float)vbar8.z, (float)vfoo8.w + (float)vbar8.w);

	float8 vadd_f_8 = vfoo8 + 0.4f;											//eq(vadd_f_4, (float)vfoo8.x + 0.4f, (float)vfoo8.y + 0.4f, (float)vfoo8.z + 0.4f, (float)vfoo8.w + 0.4f);

	vadd_f_8 += 0.4f;														//eq(vadd_f_4, (float)vfoo8.x + 0.4f + 0.4f, (float)vfoo8.y + 0.4f + 0.4f, (float)vfoo8.z + 0.4f + 0.4f, (float)vfoo8.w + 0.4f + 0.4f);
	
	// Subtraction

	float8 vsub8 = vfoo8 - vbar8;											//eq(vsub4, (float)vfoo8.x - (float)vbar8.x, (float)vfoo8.y - (float)vbar8.y, (float)vfoo8.z - (float)vbar8.z, (float)vfoo8.w - (float)vbar8.w);

	float8 vsub_f_8 = vfoo8 - 0.4f;											//eq(vsub_f_4, (float)vfoo8.x - 0.4f, (float)vfoo8.y - 0.4f, (float)vfoo8.z - 0.4f, (float)vfoo8.w - 0.4f);

	vsub_f_8 -= 0.4f;														//eq(vsub_f_4, (float)vfoo8.x - 0.4f - 0.4f, (float)vfoo8.y - 0.4f - 0.4f, (float)vfoo8.z - 0.4f - 0.4f, (float)vfoo8.w - 0.4f - 0.4f);

	// Multiplication

	float8 vmul8 = vfoo8 * vbar8;						//eq(vmul4, (float)vfoo8.x * (float)vbar8.x, (float)vfoo8.y * (float)vbar8.y, (float)vfoo8.z * (float)vbar8.z, (float)vfoo8.w * (float)vbar8.w);

	float8 vmul_f_8 = vfoo8 * 0.4f;						//eq(vmul_f_4, (float)vfoo8.x * 0.4f, (float)vfoo8.y * 0.4f, (float)vfoo8.z * 0.4f, (float)vfoo8.w * 0.4f);

	vmul_f_8 *= 0.4f;									//eq(vmul_f_4, (float)vfoo8.x * 0.4f * 0.4f, (float)vfoo8.y * 0.4f * 0.4f, (float)vfoo8.z * 0.4f * 0.4f, (float)vfoo8.w * 0.4f * 0.4f);
	
	// Division

	float8 vdiv8 = vfoo8 / vbar8;						//eq(vdiv4, div(vfoo8.x, vbar8.x), div(vfoo8.y, vbar8.y), div(vfoo8.z, vbar8.z), div(vfoo8.w, vbar8.w), tolDiv);

	float8 vdiv_f_8 = vfoo8 / 0.4f;						//eq(vdiv_f_4, div(vfoo8.x, 0.4f), div(vfoo8.y, 0.4f), div(vfoo8.z, 0.4f), div(vfoo8.w, 0.4f), tolDiv);

	vdiv_f_8 /= 0.4f;									//eq(vdiv_f_4, div(div(vfoo8.x, 0.4f), 0.4f), div(div(vfoo8.y, 0.4f), 0.4f), div(div(vfoo8.z, 0.4f), 0.4f), div(div(vfoo8.w, 0.4f), 0.4f), tolDiv);
	
	// Comparison

	float8 vgt8 = vfoo8 > vbar8;							//eq(vgt4, (float)vfoo8.x > (float)vbar8.x, (float)vfoo8.y > (float)vbar8.y, (float)vfoo8.z > (float)vbar8.z, (float)vfoo8.w > (float)vbar8.w);

	float8 vlt8 = vfoo8 < vbar8;							//eq(vlt4, (float)vfoo8.x < (float)vbar8.x, (float)vfoo8.y < (float)vbar8.y, (float)vfoo8.z < (float)vbar8.z, (float)vfoo8.w < (float)vbar8.w);

	float8 vge8 = vfoo8 >= vbar8;							//eq(vge4, (float)vfoo8.x >= (float)vbar8.x, (float)vfoo8.y >= (float)vbar8.y, (float)vfoo8.z >= (float)vbar8.z, (float)vfoo8.w >= (float)vbar8.w);

	float8 vle8 = vfoo8 <= vbar8;							//eq(vle4, (float)vfoo8.x <= (float)vbar8.x, (float)vfoo8.y <= (float)vbar8.y, (float)vfoo8.z <= (float)vbar8.z, (float)vfoo8.w <= (float)vbar8.w);

	float8 veq8 = vfoo8 == vbar8;							//eq(veq4, (float)vfoo8.x == (float)vbar8.x, (float)vfoo8.y == (float)vbar8.y, (float)vfoo8.z == (float)vbar8.z, (float)vfoo8.w == (float)vbar8.w);

	float8 vneq8 = vfoo8 != vbar8;							//eq(vneq4, (float)vfoo8.x != (float)vbar8.x, (float)vfoo8.y != (float)vbar8.y, (float)vfoo8.z != (float)vbar8.z, (float)vfoo8.w != (float)vbar8.w);

	float8 vabs8 = abs(vfoo8);								//eq(vabs4, abs((float)vfoo8.x), abs((float)vfoo8.y), abs((float)vfoo8.z), abs((float)vfoo8.w));

	float8 vabsneg_8 = abs(-vfoo8);							//eq(vabsneg_4, abs((float)-vfoo8.x), abs((float)-vfoo8.y), abs((float)-vfoo8.z), abs((float)-vfoo8.w));

	bool vall8 = all(vfoo8);				//eq(vall4, vfoo8.x != 0.0f && vfoo8.y != 0.0f && vfoo8.z != 0.0f && vfoo8.w != 0.0f);

	bool vany8 = any(vfoo8);				//eq(vany4, vfoo8.x != 0.0f || vfoo8.y != 0.0f || vfoo8.z != 0.0f || vfoo8.w != 0.0f);

	float8 vacos8 = acos(vfoo8);

	float8 vasin8 = asin(vfoo8);

	float8 vatan8 = atan(vfoo8);

	float8 vceil8 = ceil(vfoo8);							//eq(vceil4, ceil((float)vfoo8.x), ceil((float)vfoo8.y), ceil((float)vfoo8.z), ceil((float)vfoo8.w));

	float8 vclamp8 = clamp(vfoo8, vbar8, vbaz8);

	float8 vcos8 = cos(vfoo8);

	float8 vcosh8 = cosh(vfoo8);

	float1 vdot8 = dot(vfoo8, vbar8);

	float8 vfloor8 = floor(vfoo8);					//eq(vfloor4, floor((float)vfoo8.x), floor((float)vfoo8.y), floor((float)vfoo8.z), floor((float)vfoo8.w));
	
	float8 vfmod8 = fmod(vfoo8, vbar8);

	float8 vfrac8 = frac(vfoo8);

	float8 vexp8 = exp(vfoo8);

	float8 vexp2_8 = exp2(vfoo8);

	float8 visfinite_8 = isfinite(vfoo8);

	float8 visinf_8 = isinf(vfoo8);

	float8 visnan_8 = isnan(vfoo8);

	float1 vlength_8 = length(vfoo8);

	float8 vlerp8 = lerp(vfoo8, vbar8, vbaz8);					//eq(vlerp4, lerpf(vfoo8.r, vbar8.r, vbaz8.r), lerpf(vfoo8.g, vbar8.g, vbaz8.g), lerpf(vfoo8.b, vbar8.b, vbaz8.b), lerpf(vfoo8.a, vbar8.a, vbaz8.a));

	float8 vlerpf_8 = lerp(vfoo8, vbar8, 0.7f);					//eq(vlerpf_4, lerpf(vfoo8.r, vbar8.r, 0.7f), lerpf(vfoo8.g, vbar8.g, 0.7f), lerpf(vfoo8.b, vbar8.b, 0.7f), lerpf(vfoo8.a, vbar8.a, 0.7f));

	float8 vlog8 = log(vfoo8);

	float8 vlog2_8 = log2(vfoo8);

	float8 vlog10_8 = log10(vfoo8);

	float8 vmin_8 = min(vfoo8, vbar8);

	float8 vmax_8 = max(vfoo8, vbar8);

	float8 vnormalize_foo_8 = normalize(vfoo8);

	float8 vnormalize_bar_8 = normalize(vbar8);

	float8 vpow_8 = pow(vfoo8, vbar8);

	float8 vradians8 = radians(vfoo8);

	float8 vreflect8 = reflect(vfoo8, vbar8);

	float8 vrefract8 = refract(vnormalize_foo_8, vnormalize_bar_8, float1(0.1f));

	float8 vrsqrt8 = rsqrt(vfoo8);

	float8 vround8 = round(vfoo8);

	float8 vsaturate8 = saturate(vfoo8);

	float8 vsign8 = sign(vfoo8);

	float8 vsin8 = sin(vfoo8);

	float8 vsinh8 = sinh(vfoo8);

	float8 vsmoothstep_8 = smoothstep(vfoo8, vfoo8 + 3.0f, vbar8);

	float8 vsqrt8 = sqrt(vfoo8);

	float8 vstep8 = step(vfoo8, vbar8);

	float8 vtan8 = tan(vfoo8);

	float8 vtanh8 = tanh(vfoo8);

	float8 vtrunc8 = trunc(vfoo8);

	// Storage
	float vstore8[8];
	store(vfoo8, vstore8);			eq(vfoo8, vstore8[0], vstore8[1], vstore8[2], vstore8[3], vstore8[4], vstore8[5], vstore8[6], vstore8[7]);

	// Loading
	float vload8[8] = { f16, f17, f18, f19, f20, f21, f22, f23 };
	load(vfoo8, vload8);			eq(vfoo8, vload8[0], vload8[1], vload8[2], vload8[3], vload8[4], vload8[5], vload8[6], vload8[7]);

#endif
}