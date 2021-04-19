// -------------------------------
// _mNM
// -------------------------------

hlslpp_declare_swizzle1(2, _m02);

hlslpp_declare_swizzle2(0, 2, _m00_m02);
hlslpp_declare_swizzle2(1, 2, _m01_m02);
hlslpp_declare_swizzle2(2, 0, _m02_m00);
hlslpp_declare_swizzle2(2, 1, _m02_m01);
hlslpp_declare_swizzle2(2, 2, _m02_m02);

hlslpp_declare_swizzle3(0, 0, 2, _m00_m00_m02);
hlslpp_declare_swizzle3(0, 1, 2, _m00_m01_m02);
hlslpp_declare_swizzle3(0, 2, 0, _m00_m02_m00);
hlslpp_declare_swizzle3(0, 2, 1, _m00_m02_m01);
hlslpp_declare_swizzle3(0, 2, 2, _m00_m02_m02);

hlslpp_declare_swizzle3(1, 0, 2, _m01_m00_m02);
hlslpp_declare_swizzle3(1, 1, 2, _m01_m01_m02);
hlslpp_declare_swizzle3(1, 2, 0, _m01_m02_m00);
hlslpp_declare_swizzle3(1, 2, 1, _m01_m02_m01);
hlslpp_declare_swizzle3(1, 2, 2, _m01_m02_m02);

hlslpp_declare_swizzle3(2, 0, 0, _m02_m00_m00);
hlslpp_declare_swizzle3(2, 0, 1, _m02_m00_m01);
hlslpp_declare_swizzle3(2, 0, 2, _m02_m00_m02);
hlslpp_declare_swizzle3(2, 1, 0, _m02_m01_m00);
hlslpp_declare_swizzle3(2, 1, 1, _m02_m01_m01);
hlslpp_declare_swizzle3(2, 1, 2, _m02_m01_m02);

hlslpp_declare_swizzle3(2, 2, 0, _m02_m02_m00);
hlslpp_declare_swizzle3(2, 2, 1, _m02_m02_m01);
hlslpp_declare_swizzle3(2, 2, 2, _m02_m02_m02);

hlslpp_declare_swizzle4(0, 0, 0, 2, _m00_m00_m00_m02);
hlslpp_declare_swizzle4(0, 0, 1, 2, _m00_m00_m01_m02);

hlslpp_declare_swizzle4(0, 0, 2, 0, _m00_m00_m02_m00);
hlslpp_declare_swizzle4(0, 0, 2, 1, _m00_m00_m02_m01);
hlslpp_declare_swizzle4(0, 0, 2, 2, _m00_m00_m02_m02);

hlslpp_declare_swizzle4(0, 1, 0, 2, _m00_m01_m00_m02);
hlslpp_declare_swizzle4(0, 1, 1, 2, _m00_m01_m01_m02);

hlslpp_declare_swizzle4(0, 1, 2, 0, _m00_m01_m02_m00);
hlslpp_declare_swizzle4(0, 1, 2, 1, _m00_m01_m02_m01);
hlslpp_declare_swizzle4(0, 1, 2, 2, _m00_m01_m02_m02);

hlslpp_declare_swizzle4(0, 2, 0, 0, _m00_m02_m00_m00);
hlslpp_declare_swizzle4(0, 2, 0, 1, _m00_m02_m00_m01);
hlslpp_declare_swizzle4(0, 2, 0, 2, _m00_m02_m00_m02);

hlslpp_declare_swizzle4(0, 2, 1, 0, _m00_m02_m01_m00);
hlslpp_declare_swizzle4(0, 2, 1, 1, _m00_m02_m01_m01);
hlslpp_declare_swizzle4(0, 2, 1, 2, _m00_m02_m01_m02);

hlslpp_declare_swizzle4(0, 2, 2, 0, _m00_m02_m02_m00);
hlslpp_declare_swizzle4(0, 2, 2, 1, _m00_m02_m02_m01);
hlslpp_declare_swizzle4(0, 2, 2, 2, _m00_m02_m02_m02);

hlslpp_declare_swizzle4(1, 0, 0, 2, _m01_m00_m00_m02);
hlslpp_declare_swizzle4(1, 0, 1, 2, _m01_m00_m01_m02);
hlslpp_declare_swizzle4(1, 0, 2, 0, _m01_m00_m02_m00);
hlslpp_declare_swizzle4(1, 0, 2, 1, _m01_m00_m02_m01);
hlslpp_declare_swizzle4(1, 0, 2, 2, _m01_m00_m02_m02);

hlslpp_declare_swizzle4(1, 1, 0, 2, _m01_m01_m00_m02);
hlslpp_declare_swizzle4(1, 1, 1, 2, _m01_m01_m01_m02);

hlslpp_declare_swizzle4(1, 1, 2, 0, _m01_m01_m02_m00);
hlslpp_declare_swizzle4(1, 1, 2, 1, _m01_m01_m02_m01);
hlslpp_declare_swizzle4(1, 1, 2, 2, _m01_m01_m02_m02);

hlslpp_declare_swizzle4(1, 2, 0, 0, _m01_m02_m00_m00);
hlslpp_declare_swizzle4(1, 2, 0, 1, _m01_m02_m00_m01);
hlslpp_declare_swizzle4(1, 2, 0, 2, _m01_m02_m00_m02);

hlslpp_declare_swizzle4(1, 2, 1, 0, _m01_m02_m01_m00);
hlslpp_declare_swizzle4(1, 2, 1, 1, _m01_m02_m01_m01);
hlslpp_declare_swizzle4(1, 2, 1, 2, _m01_m02_m01_m02);

hlslpp_declare_swizzle4(1, 2, 2, 0, _m01_m02_m02_m00);
hlslpp_declare_swizzle4(1, 2, 2, 1, _m01_m02_m02_m01);
hlslpp_declare_swizzle4(1, 2, 2, 2, _m01_m02_m02_m02);

hlslpp_declare_swizzle4(2, 0, 0, 0, _m02_m00_m00_m00);
hlslpp_declare_swizzle4(2, 0, 0, 1, _m02_m00_m00_m01);
hlslpp_declare_swizzle4(2, 0, 0, 2, _m02_m00_m00_m02);

hlslpp_declare_swizzle4(2, 0, 1, 0, _m02_m00_m01_m00);
hlslpp_declare_swizzle4(2, 0, 1, 1, _m02_m00_m01_m01);
hlslpp_declare_swizzle4(2, 0, 1, 2, _m02_m00_m01_m02);

hlslpp_declare_swizzle4(2, 0, 2, 0, _m02_m00_m02_m00);
hlslpp_declare_swizzle4(2, 0, 2, 1, _m02_m00_m02_m01);
hlslpp_declare_swizzle4(2, 0, 2, 2, _m02_m00_m02_m02);

hlslpp_declare_swizzle4(2, 1, 0, 0, _m02_m01_m00_m00);
hlslpp_declare_swizzle4(2, 1, 0, 1, _m02_m01_m00_m01);
hlslpp_declare_swizzle4(2, 1, 0, 2, _m02_m01_m00_m02);

hlslpp_declare_swizzle4(2, 1, 1, 0, _m02_m01_m01_m00);
hlslpp_declare_swizzle4(2, 1, 1, 1, _m02_m01_m01_m01);
hlslpp_declare_swizzle4(2, 1, 1, 2, _m02_m01_m01_m02);

hlslpp_declare_swizzle4(2, 1, 2, 0, _m02_m01_m02_m00);
hlslpp_declare_swizzle4(2, 1, 2, 1, _m02_m01_m02_m01);
hlslpp_declare_swizzle4(2, 1, 2, 2, _m02_m01_m02_m02);

hlslpp_declare_swizzle4(2, 2, 0, 0, _m02_m02_m00_m00);
hlslpp_declare_swizzle4(2, 2, 0, 1, _m02_m02_m00_m01);
hlslpp_declare_swizzle4(2, 2, 0, 2, _m02_m02_m00_m02);

hlslpp_declare_swizzle4(2, 2, 1, 0, _m02_m02_m01_m00);
hlslpp_declare_swizzle4(2, 2, 1, 1, _m02_m02_m01_m01);
hlslpp_declare_swizzle4(2, 2, 1, 2, _m02_m02_m01_m02);

hlslpp_declare_swizzle4(2, 2, 2, 0, _m02_m02_m02_m00);
hlslpp_declare_swizzle4(2, 2, 2, 1, _m02_m02_m02_m01);
hlslpp_declare_swizzle4(2, 2, 2, 2, _m02_m02_m02_m02);

// -------------------------------
// _NM
// -------------------------------

hlslpp_declare_swizzle1(2, _13);

hlslpp_declare_swizzle2(0, 2, _11_13);
hlslpp_declare_swizzle2(1, 2, _12_13);
hlslpp_declare_swizzle2(2, 0, _13_11);
hlslpp_declare_swizzle2(2, 1, _13_12);
hlslpp_declare_swizzle2(2, 2, _13_13);

hlslpp_declare_swizzle3(0, 0, 2, _11_11_13);
hlslpp_declare_swizzle3(0, 1, 2, _11_12_13);
hlslpp_declare_swizzle3(0, 2, 0, _11_13_11);
hlslpp_declare_swizzle3(0, 2, 1, _11_13_12);
hlslpp_declare_swizzle3(0, 2, 2, _11_13_13);

hlslpp_declare_swizzle3(1, 0, 2, _12_11_13);
hlslpp_declare_swizzle3(1, 1, 2, _12_12_13);
hlslpp_declare_swizzle3(1, 2, 0, _12_13_11);
hlslpp_declare_swizzle3(1, 2, 1, _12_13_12);
hlslpp_declare_swizzle3(1, 2, 2, _12_13_13);

hlslpp_declare_swizzle3(2, 0, 0, _13_11_11);
hlslpp_declare_swizzle3(2, 0, 1, _13_11_12);
hlslpp_declare_swizzle3(2, 0, 2, _13_11_13);
hlslpp_declare_swizzle3(2, 1, 0, _13_12_11);
hlslpp_declare_swizzle3(2, 1, 1, _13_12_12);
hlslpp_declare_swizzle3(2, 1, 2, _13_12_13);

hlslpp_declare_swizzle3(2, 2, 0, _13_13_11);
hlslpp_declare_swizzle3(2, 2, 1, _13_13_12);
hlslpp_declare_swizzle3(2, 2, 2, _13_13_13);

hlslpp_declare_swizzle4(0, 0, 0, 2, _11_11_11_13);
hlslpp_declare_swizzle4(0, 0, 1, 2, _11_11_12_13);

hlslpp_declare_swizzle4(0, 0, 2, 0, _11_11_13_11);
hlslpp_declare_swizzle4(0, 0, 2, 1, _11_11_13_12);
hlslpp_declare_swizzle4(0, 0, 2, 2, _11_11_13_13);

hlslpp_declare_swizzle4(0, 1, 0, 2, _11_12_11_13);
hlslpp_declare_swizzle4(0, 1, 1, 2, _11_12_12_13);

hlslpp_declare_swizzle4(0, 1, 2, 0, _11_12_13_11);
hlslpp_declare_swizzle4(0, 1, 2, 1, _11_12_13_12);
hlslpp_declare_swizzle4(0, 1, 2, 2, _11_12_13_13);

hlslpp_declare_swizzle4(0, 2, 0, 0, _11_13_11_11);
hlslpp_declare_swizzle4(0, 2, 0, 1, _11_13_11_12);
hlslpp_declare_swizzle4(0, 2, 0, 2, _11_13_11_13);

hlslpp_declare_swizzle4(0, 2, 1, 0, _11_13_12_11);
hlslpp_declare_swizzle4(0, 2, 1, 1, _11_13_12_12);
hlslpp_declare_swizzle4(0, 2, 1, 2, _11_13_12_13);

hlslpp_declare_swizzle4(0, 2, 2, 0, _11_13_13_11);
hlslpp_declare_swizzle4(0, 2, 2, 1, _11_13_13_12);
hlslpp_declare_swizzle4(0, 2, 2, 2, _11_13_13_13);

hlslpp_declare_swizzle4(1, 0, 0, 2, _12_11_11_13);
hlslpp_declare_swizzle4(1, 0, 1, 2, _12_11_12_13);
hlslpp_declare_swizzle4(1, 0, 2, 0, _12_11_13_11);
hlslpp_declare_swizzle4(1, 0, 2, 1, _12_11_13_12);
hlslpp_declare_swizzle4(1, 0, 2, 2, _12_11_13_13);

hlslpp_declare_swizzle4(1, 1, 0, 2, _12_12_11_13);
hlslpp_declare_swizzle4(1, 1, 1, 2, _12_12_12_13);

hlslpp_declare_swizzle4(1, 1, 2, 0, _12_12_13_11);
hlslpp_declare_swizzle4(1, 1, 2, 1, _12_12_13_12);
hlslpp_declare_swizzle4(1, 1, 2, 2, _12_12_13_13);

hlslpp_declare_swizzle4(1, 2, 0, 0, _12_13_11_11);
hlslpp_declare_swizzle4(1, 2, 0, 1, _12_13_11_12);
hlslpp_declare_swizzle4(1, 2, 0, 2, _12_13_11_13);

hlslpp_declare_swizzle4(1, 2, 1, 0, _12_13_12_11);
hlslpp_declare_swizzle4(1, 2, 1, 1, _12_13_12_12);
hlslpp_declare_swizzle4(1, 2, 1, 2, _12_13_12_13);

hlslpp_declare_swizzle4(1, 2, 2, 0, _12_13_13_11);
hlslpp_declare_swizzle4(1, 2, 2, 1, _12_13_13_12);
hlslpp_declare_swizzle4(1, 2, 2, 2, _12_13_13_13);

hlslpp_declare_swizzle4(2, 0, 0, 0, _13_11_11_11);
hlslpp_declare_swizzle4(2, 0, 0, 1, _13_11_11_12);
hlslpp_declare_swizzle4(2, 0, 0, 2, _13_11_11_13);

hlslpp_declare_swizzle4(2, 0, 1, 0, _13_11_12_11);
hlslpp_declare_swizzle4(2, 0, 1, 1, _13_11_12_12);
hlslpp_declare_swizzle4(2, 0, 1, 2, _13_11_12_13);

hlslpp_declare_swizzle4(2, 0, 2, 0, _13_11_13_11);
hlslpp_declare_swizzle4(2, 0, 2, 1, _13_11_13_12);
hlslpp_declare_swizzle4(2, 0, 2, 2, _13_11_13_13);

hlslpp_declare_swizzle4(2, 1, 0, 0, _13_12_11_11);
hlslpp_declare_swizzle4(2, 1, 0, 1, _13_12_11_12);
hlslpp_declare_swizzle4(2, 1, 0, 2, _13_12_11_13);

hlslpp_declare_swizzle4(2, 1, 1, 0, _13_12_12_11);
hlslpp_declare_swizzle4(2, 1, 1, 1, _13_12_12_12);
hlslpp_declare_swizzle4(2, 1, 1, 2, _13_12_12_13);

hlslpp_declare_swizzle4(2, 1, 2, 0, _13_12_13_11);
hlslpp_declare_swizzle4(2, 1, 2, 1, _13_12_13_12);
hlslpp_declare_swizzle4(2, 1, 2, 2, _13_12_13_13);

hlslpp_declare_swizzle4(2, 2, 0, 0, _13_13_11_11);
hlslpp_declare_swizzle4(2, 2, 0, 1, _13_13_11_12);
hlslpp_declare_swizzle4(2, 2, 0, 2, _13_13_11_13);

hlslpp_declare_swizzle4(2, 2, 1, 0, _13_13_12_11);
hlslpp_declare_swizzle4(2, 2, 1, 1, _13_13_12_12);
hlslpp_declare_swizzle4(2, 2, 1, 2, _13_13_12_13);

hlslpp_declare_swizzle4(2, 2, 2, 0, _13_13_13_11);
hlslpp_declare_swizzle4(2, 2, 2, 1, _13_13_13_12);
hlslpp_declare_swizzle4(2, 2, 2, 2, _13_13_13_13);