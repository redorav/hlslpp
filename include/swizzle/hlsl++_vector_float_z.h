// -------------------------------
// XYZW
// -------------------------------

hlslpp_declare_swizzle1(2, z);

hlslpp_declare_swizzle2(0, 2, xz);
hlslpp_declare_swizzle2(1, 2, yz);
hlslpp_declare_swizzle2(2, 0, zx);
hlslpp_declare_swizzle2(2, 1, zy);
hlslpp_declare_swizzle2(2, 2, zz);

hlslpp_declare_swizzle3(0, 0, 2, xxz);
hlslpp_declare_swizzle3(0, 1, 2, xyz);
hlslpp_declare_swizzle3(0, 2, 0, xzx);
hlslpp_declare_swizzle3(0, 2, 1, xzy);
hlslpp_declare_swizzle3(0, 2, 2, xzz);

hlslpp_declare_swizzle3(1, 0, 2, yxz);
hlslpp_declare_swizzle3(1, 1, 2, yyz);
hlslpp_declare_swizzle3(1, 2, 0, yzx);
hlslpp_declare_swizzle3(1, 2, 1, yzy);
hlslpp_declare_swizzle3(1, 2, 2, yzz);

hlslpp_declare_swizzle3(2, 0, 0, zxx);
hlslpp_declare_swizzle3(2, 0, 1, zxy);
hlslpp_declare_swizzle3(2, 0, 2, zxz);
hlslpp_declare_swizzle3(2, 1, 0, zyx);
hlslpp_declare_swizzle3(2, 1, 1, zyy);
hlslpp_declare_swizzle3(2, 1, 2, zyz);

hlslpp_declare_swizzle3(2, 2, 0, zzx);
hlslpp_declare_swizzle3(2, 2, 1, zzy);
hlslpp_declare_swizzle3(2, 2, 2, zzz);

hlslpp_declare_swizzle4(0, 0, 0, 2, xxxz);
hlslpp_declare_swizzle4(0, 0, 1, 2, xxyz);

hlslpp_declare_swizzle4(0, 0, 2, 0, xxzx);
hlslpp_declare_swizzle4(0, 0, 2, 1, xxzy);
hlslpp_declare_swizzle4(0, 0, 2, 2, xxzz);

hlslpp_declare_swizzle4(0, 1, 0, 2, xyxz);
hlslpp_declare_swizzle4(0, 1, 1, 2, xyyz);

hlslpp_declare_swizzle4(0, 1, 2, 0, xyzx);
hlslpp_declare_swizzle4(0, 1, 2, 1, xyzy);
hlslpp_declare_swizzle4(0, 1, 2, 2, xyzz);

hlslpp_declare_swizzle4(0, 2, 0, 0, xzxx);
hlslpp_declare_swizzle4(0, 2, 0, 1, xzxy);
hlslpp_declare_swizzle4(0, 2, 0, 2, xzxz);

hlslpp_declare_swizzle4(0, 2, 1, 0, xzyx);
hlslpp_declare_swizzle4(0, 2, 1, 1, xzyy);
hlslpp_declare_swizzle4(0, 2, 1, 2, xzyz);

hlslpp_declare_swizzle4(0, 2, 2, 0, xzzx);
hlslpp_declare_swizzle4(0, 2, 2, 1, xzzy);
hlslpp_declare_swizzle4(0, 2, 2, 2, xzzz);

hlslpp_declare_swizzle4(1, 0, 0, 2, yxxz);
hlslpp_declare_swizzle4(1, 0, 1, 2, yxyz);
hlslpp_declare_swizzle4(1, 0, 2, 0, yxzx);
hlslpp_declare_swizzle4(1, 0, 2, 1, yxzy);
hlslpp_declare_swizzle4(1, 0, 2, 2, yxzz);

hlslpp_declare_swizzle4(1, 1, 0, 2, yyxz);
hlslpp_declare_swizzle4(1, 1, 1, 2, yyyz);

hlslpp_declare_swizzle4(1, 1, 2, 0, yyzx);
hlslpp_declare_swizzle4(1, 1, 2, 1, yyzy);
hlslpp_declare_swizzle4(1, 1, 2, 2, yyzz);

hlslpp_declare_swizzle4(1, 2, 0, 0, yzxx);
hlslpp_declare_swizzle4(1, 2, 0, 1, yzxy);
hlslpp_declare_swizzle4(1, 2, 0, 2, yzxz);

hlslpp_declare_swizzle4(1, 2, 1, 0, yzyx);
hlslpp_declare_swizzle4(1, 2, 1, 1, yzyy);
hlslpp_declare_swizzle4(1, 2, 1, 2, yzyz);

hlslpp_declare_swizzle4(1, 2, 2, 0, yzzx);
hlslpp_declare_swizzle4(1, 2, 2, 1, yzzy);
hlslpp_declare_swizzle4(1, 2, 2, 2, yzzz);

hlslpp_declare_swizzle4(2, 0, 0, 0, zxxx);
hlslpp_declare_swizzle4(2, 0, 0, 1, zxxy);
hlslpp_declare_swizzle4(2, 0, 0, 2, zxxz);

hlslpp_declare_swizzle4(2, 0, 1, 0, zxyx);
hlslpp_declare_swizzle4(2, 0, 1, 1, zxyy);
hlslpp_declare_swizzle4(2, 0, 1, 2, zxyz);

hlslpp_declare_swizzle4(2, 0, 2, 0, zxzx);
hlslpp_declare_swizzle4(2, 0, 2, 1, zxzy);
hlslpp_declare_swizzle4(2, 0, 2, 2, zxzz);

hlslpp_declare_swizzle4(2, 1, 0, 0, zyxx);
hlslpp_declare_swizzle4(2, 1, 0, 1, zyxy);
hlslpp_declare_swizzle4(2, 1, 0, 2, zyxz);

hlslpp_declare_swizzle4(2, 1, 1, 0, zyyx);
hlslpp_declare_swizzle4(2, 1, 1, 1, zyyy);
hlslpp_declare_swizzle4(2, 1, 1, 2, zyyz);

hlslpp_declare_swizzle4(2, 1, 2, 0, zyzx);
hlslpp_declare_swizzle4(2, 1, 2, 1, zyzy);
hlslpp_declare_swizzle4(2, 1, 2, 2, zyzz);

hlslpp_declare_swizzle4(2, 2, 0, 0, zzxx);
hlslpp_declare_swizzle4(2, 2, 0, 1, zzxy);
hlslpp_declare_swizzle4(2, 2, 0, 2, zzxz);

hlslpp_declare_swizzle4(2, 2, 1, 0, zzyx);
hlslpp_declare_swizzle4(2, 2, 1, 1, zzyy);
hlslpp_declare_swizzle4(2, 2, 1, 2, zzyz);

hlslpp_declare_swizzle4(2, 2, 2, 0, zzzx);
hlslpp_declare_swizzle4(2, 2, 2, 1, zzzy);
hlslpp_declare_swizzle4(2, 2, 2, 2, zzzz);

// -------------------------------
// RGBA
// -------------------------------

hlslpp_declare_swizzle1(2, b);

hlslpp_declare_swizzle2(0, 2, rb);
hlslpp_declare_swizzle2(1, 2, gb);
hlslpp_declare_swizzle2(2, 0, br);
hlslpp_declare_swizzle2(2, 1, bg);
hlslpp_declare_swizzle2(2, 2, bb);

hlslpp_declare_swizzle3(0, 0, 2, rrb);
hlslpp_declare_swizzle3(0, 1, 2, rgb);
hlslpp_declare_swizzle3(0, 2, 0, rbr);
hlslpp_declare_swizzle3(0, 2, 1, rbg);
hlslpp_declare_swizzle3(0, 2, 2, rbb);

hlslpp_declare_swizzle3(1, 0, 2, grb);
hlslpp_declare_swizzle3(1, 1, 2, ggb);
hlslpp_declare_swizzle3(1, 2, 0, gbr);
hlslpp_declare_swizzle3(1, 2, 1, gbg);
hlslpp_declare_swizzle3(1, 2, 2, gbb);

hlslpp_declare_swizzle3(2, 0, 0, brr);
hlslpp_declare_swizzle3(2, 0, 1, brg);
hlslpp_declare_swizzle3(2, 0, 2, brb);
hlslpp_declare_swizzle3(2, 1, 0, bgr);
hlslpp_declare_swizzle3(2, 1, 1, bgg);
hlslpp_declare_swizzle3(2, 1, 2, bgb);

hlslpp_declare_swizzle3(2, 2, 0, bbr);
hlslpp_declare_swizzle3(2, 2, 1, bbg);
hlslpp_declare_swizzle3(2, 2, 2, bbb);

hlslpp_declare_swizzle4(0, 0, 0, 2, rrrb);
hlslpp_declare_swizzle4(0, 0, 1, 2, rrgb);

hlslpp_declare_swizzle4(0, 0, 2, 0, rrbr);
hlslpp_declare_swizzle4(0, 0, 2, 1, rrbg);
hlslpp_declare_swizzle4(0, 0, 2, 2, rrbb);

hlslpp_declare_swizzle4(0, 1, 0, 2, rgrb);
hlslpp_declare_swizzle4(0, 1, 1, 2, rggb);

hlslpp_declare_swizzle4(0, 1, 2, 0, rgbr);
hlslpp_declare_swizzle4(0, 1, 2, 1, rgbg);
hlslpp_declare_swizzle4(0, 1, 2, 2, rgbb);

hlslpp_declare_swizzle4(0, 2, 0, 0, rbrr);
hlslpp_declare_swizzle4(0, 2, 0, 1, rbrg);
hlslpp_declare_swizzle4(0, 2, 0, 2, rbrb);

hlslpp_declare_swizzle4(0, 2, 1, 0, rbgr);
hlslpp_declare_swizzle4(0, 2, 1, 1, rbgg);
hlslpp_declare_swizzle4(0, 2, 1, 2, rbgb);

hlslpp_declare_swizzle4(0, 2, 2, 0, rbbr);
hlslpp_declare_swizzle4(0, 2, 2, 1, rbbg);
hlslpp_declare_swizzle4(0, 2, 2, 2, rbbb);

hlslpp_declare_swizzle4(1, 0, 0, 2, grrb);
hlslpp_declare_swizzle4(1, 0, 1, 2, grgb);
hlslpp_declare_swizzle4(1, 0, 2, 0, grbr);
hlslpp_declare_swizzle4(1, 0, 2, 1, grbg);
hlslpp_declare_swizzle4(1, 0, 2, 2, grbb);

hlslpp_declare_swizzle4(1, 1, 0, 2, ggrb);
hlslpp_declare_swizzle4(1, 1, 1, 2, gggb);

hlslpp_declare_swizzle4(1, 1, 2, 0, ggbr);
hlslpp_declare_swizzle4(1, 1, 2, 1, ggbg);
hlslpp_declare_swizzle4(1, 1, 2, 2, ggbb);

hlslpp_declare_swizzle4(1, 2, 0, 0, gbrr);
hlslpp_declare_swizzle4(1, 2, 0, 1, gbrg);
hlslpp_declare_swizzle4(1, 2, 0, 2, gbrb);

hlslpp_declare_swizzle4(1, 2, 1, 0, gbgr);
hlslpp_declare_swizzle4(1, 2, 1, 1, gbgg);
hlslpp_declare_swizzle4(1, 2, 1, 2, gbgb);

hlslpp_declare_swizzle4(1, 2, 2, 0, gbbr);
hlslpp_declare_swizzle4(1, 2, 2, 1, gbbg);
hlslpp_declare_swizzle4(1, 2, 2, 2, gbbb);

hlslpp_declare_swizzle4(2, 0, 0, 0, brrr);
hlslpp_declare_swizzle4(2, 0, 0, 1, brrg);
hlslpp_declare_swizzle4(2, 0, 0, 2, brrb);

hlslpp_declare_swizzle4(2, 0, 1, 0, brgr);
hlslpp_declare_swizzle4(2, 0, 1, 1, brgg);
hlslpp_declare_swizzle4(2, 0, 1, 2, brgb);

hlslpp_declare_swizzle4(2, 0, 2, 0, brbr);
hlslpp_declare_swizzle4(2, 0, 2, 1, brbg);
hlslpp_declare_swizzle4(2, 0, 2, 2, brbb);

hlslpp_declare_swizzle4(2, 1, 0, 0, bgrr);
hlslpp_declare_swizzle4(2, 1, 0, 1, bgrg);
hlslpp_declare_swizzle4(2, 1, 0, 2, bgrb);

hlslpp_declare_swizzle4(2, 1, 1, 0, bggr);
hlslpp_declare_swizzle4(2, 1, 1, 1, bggg);
hlslpp_declare_swizzle4(2, 1, 1, 2, bggb);

hlslpp_declare_swizzle4(2, 1, 2, 0, bgbr);
hlslpp_declare_swizzle4(2, 1, 2, 1, bgbg);
hlslpp_declare_swizzle4(2, 1, 2, 2, bgbb);

hlslpp_declare_swizzle4(2, 2, 0, 0, bbrr);
hlslpp_declare_swizzle4(2, 2, 0, 1, bbrg);
hlslpp_declare_swizzle4(2, 2, 0, 2, bbrb);

hlslpp_declare_swizzle4(2, 2, 1, 0, bbgr);
hlslpp_declare_swizzle4(2, 2, 1, 1, bbgg);
hlslpp_declare_swizzle4(2, 2, 1, 2, bbgb);

hlslpp_declare_swizzle4(2, 2, 2, 0, bbbr);
hlslpp_declare_swizzle4(2, 2, 2, 1, bbbg);
hlslpp_declare_swizzle4(2, 2, 2, 2, bbbb);