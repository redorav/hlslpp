// -------------------------------
// XYZW
// -------------------------------

hlslpp_declare_swizzle1(swizzle1, 1, y);

hlslpp_declare_swizzle2(swizzle2, 0, 1, xy);
hlslpp_declare_swizzle2(swizzle2, 1, 0, yx);
hlslpp_declare_swizzle2(swizzle2, 1, 1, yy);

hlslpp_declare_swizzle3(swizzle3, 0, 0, 1, xxy);
hlslpp_declare_swizzle3(swizzle3, 0, 1, 0, xyx);
hlslpp_declare_swizzle3(swizzle3, 0, 1, 1, xyy);

hlslpp_declare_swizzle3(swizzle3, 1, 0, 0, yxx);
hlslpp_declare_swizzle3(swizzle3, 1, 0, 1, yxy);
hlslpp_declare_swizzle3(swizzle3, 1, 1, 0, yyx);
hlslpp_declare_swizzle3(swizzle3, 1, 1, 1, yyy);

hlslpp_declare_swizzle4(swizzle4, 0, 0, 0, 1, xxxy);

hlslpp_declare_swizzle4(swizzle4, 0, 0, 1, 0, xxyx);
hlslpp_declare_swizzle4(swizzle4, 0, 0, 1, 1, xxyy);

hlslpp_declare_swizzle4(swizzle4, 0, 1, 0, 0, xyxx);
hlslpp_declare_swizzle4(swizzle4, 0, 1, 0, 1, xyxy);

hlslpp_declare_swizzle4(swizzle4, 0, 1, 1, 0, xyyx);
hlslpp_declare_swizzle4(swizzle4, 0, 1, 1, 1, xyyy);

hlslpp_declare_swizzle4(swizzle4, 1, 0, 0, 0, yxxx);
hlslpp_declare_swizzle4(swizzle4, 1, 0, 0, 1, yxxy);

hlslpp_declare_swizzle4(swizzle4, 1, 0, 1, 0, yxyx);
hlslpp_declare_swizzle4(swizzle4, 1, 0, 1, 1, yxyy);

hlslpp_declare_swizzle4(swizzle4, 1, 1, 0, 0, yyxx);
hlslpp_declare_swizzle4(swizzle4, 1, 1, 0, 1, yyxy);

hlslpp_declare_swizzle4(swizzle4, 1, 1, 1, 0, yyyx);
hlslpp_declare_swizzle4(swizzle4, 1, 1, 1, 1, yyyy);

// -------------------------------
// RGBA
// -------------------------------

hlslpp_declare_swizzle1(swizzle1, 1, g);

hlslpp_declare_swizzle2(swizzle2, 0, 1, rg);
hlslpp_declare_swizzle2(swizzle2, 1, 0, gr);
hlslpp_declare_swizzle2(swizzle2, 1, 1, gg);

hlslpp_declare_swizzle3(swizzle3, 0, 0, 1, rrg);
hlslpp_declare_swizzle3(swizzle3, 0, 1, 0, rgr);
hlslpp_declare_swizzle3(swizzle3, 0, 1, 1, rgg);

hlslpp_declare_swizzle3(swizzle3, 1, 0, 0, grr);
hlslpp_declare_swizzle3(swizzle3, 1, 0, 1, grg);
hlslpp_declare_swizzle3(swizzle3, 1, 1, 0, ggr);
hlslpp_declare_swizzle3(swizzle3, 1, 1, 1, ggg);

hlslpp_declare_swizzle4(swizzle4, 0, 0, 0, 1, rrrg);

hlslpp_declare_swizzle4(swizzle4, 0, 0, 1, 0, rrgr);
hlslpp_declare_swizzle4(swizzle4, 0, 0, 1, 1, rrgg);

hlslpp_declare_swizzle4(swizzle4, 0, 1, 0, 0, rgrr);
hlslpp_declare_swizzle4(swizzle4, 0, 1, 0, 1, rgrg);

hlslpp_declare_swizzle4(swizzle4, 0, 1, 1, 0, rggr);
hlslpp_declare_swizzle4(swizzle4, 0, 1, 1, 1, rggg);

hlslpp_declare_swizzle4(swizzle4, 1, 0, 0, 0, grrr);
hlslpp_declare_swizzle4(swizzle4, 1, 0, 0, 1, grrg);

hlslpp_declare_swizzle4(swizzle4, 1, 0, 1, 0, grgr);
hlslpp_declare_swizzle4(swizzle4, 1, 0, 1, 1, grgg);

hlslpp_declare_swizzle4(swizzle4, 1, 1, 0, 0, ggrr);
hlslpp_declare_swizzle4(swizzle4, 1, 1, 0, 1, ggrg);

hlslpp_declare_swizzle4(swizzle4, 1, 1, 1, 0, gggr);
hlslpp_declare_swizzle4(swizzle4, 1, 1, 1, 1, gggg);