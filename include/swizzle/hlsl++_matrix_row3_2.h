// -------------------------------
// _mNM
// -------------------------------

hlslpp_declare_swizzle1(1, _m31);

hlslpp_declare_swizzle2(0, 1, _m30_m31);
hlslpp_declare_swizzle2(1, 0, _m31_m30);
hlslpp_declare_swizzle2(1, 1, _m31_m31);

hlslpp_declare_swizzle3(0, 0, 1, _m30_m30_m31);
hlslpp_declare_swizzle3(0, 1, 0, _m30_m31_m30);
hlslpp_declare_swizzle3(0, 1, 1, _m30_m31_m31);

hlslpp_declare_swizzle3(1, 0, 0, _m31_m30_m30);
hlslpp_declare_swizzle3(1, 0, 1, _m31_m30_m31);
hlslpp_declare_swizzle3(1, 1, 0, _m31_m31_m30);
hlslpp_declare_swizzle3(1, 1, 1, _m31_m31_m31);

hlslpp_declare_swizzle4(0, 0, 0, 1, _m30_m30_m30_m31);

hlslpp_declare_swizzle4(0, 0, 1, 0, _m30_m30_m31_m30);
hlslpp_declare_swizzle4(0, 0, 1, 1, _m30_m30_m31_m31);

hlslpp_declare_swizzle4(0, 1, 0, 0, _m30_m31_m30_m30);
hlslpp_declare_swizzle4(0, 1, 0, 1, _m30_m31_m30_m31);

hlslpp_declare_swizzle4(0, 1, 1, 0, _m30_m31_m31_m30);
hlslpp_declare_swizzle4(0, 1, 1, 1, _m30_m31_m31_m31);

hlslpp_declare_swizzle4(1, 0, 0, 0, _m31_m30_m30_m30);
hlslpp_declare_swizzle4(1, 0, 0, 1, _m31_m30_m30_m31);

hlslpp_declare_swizzle4(1, 0, 1, 0, _m31_m30_m31_m30);
hlslpp_declare_swizzle4(1, 0, 1, 1, _m31_m30_m31_m31);

hlslpp_declare_swizzle4(1, 1, 0, 0, _m31_m31_m30_m30);
hlslpp_declare_swizzle4(1, 1, 0, 1, _m31_m31_m30_m31);

hlslpp_declare_swizzle4(1, 1, 1, 0, _m31_m31_m31_m30);
hlslpp_declare_swizzle4(1, 1, 1, 1, _m31_m31_m31_m31);

// -------------------------------
// _NM
// -------------------------------

hlslpp_declare_swizzle1(1, _42);

hlslpp_declare_swizzle2(0, 1, _41_42);
hlslpp_declare_swizzle2(1, 0, _42_41);
hlslpp_declare_swizzle2(1, 1, _42_42);

hlslpp_declare_swizzle3(0, 0, 1, _41_41_42);
hlslpp_declare_swizzle3(0, 1, 0, _41_42_41);
hlslpp_declare_swizzle3(0, 1, 1, _41_42_42);

hlslpp_declare_swizzle3(1, 0, 0, _42_41_41);
hlslpp_declare_swizzle3(1, 0, 1, _42_41_42);
hlslpp_declare_swizzle3(1, 1, 0, _42_42_41);
hlslpp_declare_swizzle3(1, 1, 1, _42_42_42);

hlslpp_declare_swizzle4(0, 0, 0, 1, _41_41_41_42);

hlslpp_declare_swizzle4(0, 0, 1, 0, _41_41_42_41);
hlslpp_declare_swizzle4(0, 0, 1, 1, _41_41_42_42);

hlslpp_declare_swizzle4(0, 1, 0, 0, _41_42_41_41);
hlslpp_declare_swizzle4(0, 1, 0, 1, _41_42_41_42);

hlslpp_declare_swizzle4(0, 1, 1, 0, _41_42_42_41);
hlslpp_declare_swizzle4(0, 1, 1, 1, _41_42_42_42);

hlslpp_declare_swizzle4(1, 0, 0, 0, _42_41_41_41);
hlslpp_declare_swizzle4(1, 0, 0, 1, _42_41_41_42);

hlslpp_declare_swizzle4(1, 0, 1, 0, _42_41_42_41);
hlslpp_declare_swizzle4(1, 0, 1, 1, _42_41_42_42);

hlslpp_declare_swizzle4(1, 1, 0, 0, _42_42_41_41);
hlslpp_declare_swizzle4(1, 1, 0, 1, _42_42_41_42);

hlslpp_declare_swizzle4(1, 1, 1, 0, _42_42_42_41);
hlslpp_declare_swizzle4(1, 1, 1, 1, _42_42_42_42);