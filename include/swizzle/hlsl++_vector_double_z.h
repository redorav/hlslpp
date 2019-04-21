// -------------------------------
// XYZW
// -------------------------------

dswizzle1<2> z;

dswizzle2<0, 2> xz;
dswizzle2<1, 2> yz;
dswizzle2<2, 0> zx;
dswizzle2<2, 1> zy;
dswizzle2<2, 2> zz;

dswizzle3<0, 0, 2> xxz;
dswizzle3<0, 1, 2> xyz;
dswizzle3<0, 2, 0> xzx;
dswizzle3<0, 2, 1> xzy;
dswizzle3<0, 2, 2> xzz;

dswizzle3<1, 0, 2> yxz;
dswizzle3<1, 1, 2> yyz;
dswizzle3<1, 2, 0> yzx;
dswizzle3<1, 2, 1> yzy;
dswizzle3<1, 2, 2> yzz;

dswizzle3<2, 0, 0> zxx;
dswizzle3<2, 0, 1> zxy;
dswizzle3<2, 0, 2> zxz;
dswizzle3<2, 1, 0> zyx;
dswizzle3<2, 1, 1> zyy;
dswizzle3<2, 1, 2> zyz;

dswizzle3<2, 2, 0> zzx;
dswizzle3<2, 2, 1> zzy;
dswizzle3<2, 2, 2> zzz;

dswizzle4<0, 0, 0, 2> xxxz;
dswizzle4<0, 0, 1, 2> xxyz;

dswizzle4<0, 0, 2, 0> xxzx;
dswizzle4<0, 0, 2, 1> xxzy;
dswizzle4<0, 0, 2, 2> xxzz;

dswizzle4<0, 1, 0, 2> xyxz;
dswizzle4<0, 1, 1, 2> xyyz;

dswizzle4<0, 1, 2, 0> xyzx;
dswizzle4<0, 1, 2, 1> xyzy;
dswizzle4<0, 1, 2, 2> xyzz;

dswizzle4<0, 2, 0, 0> xzxx;
dswizzle4<0, 2, 0, 1> xzxy;
dswizzle4<0, 2, 0, 2> xzxz;

dswizzle4<0, 2, 1, 0> xzyx;
dswizzle4<0, 2, 1, 1> xzyy;
dswizzle4<0, 2, 1, 2> xzyz;

dswizzle4<0, 2, 2, 0> xzzx;
dswizzle4<0, 2, 2, 1> xzzy;
dswizzle4<0, 2, 2, 2> xzzz;

dswizzle4<1, 0, 0, 2> yxxz;
dswizzle4<1, 0, 1, 2> yxyz;
dswizzle4<1, 0, 2, 0> yxzx;
dswizzle4<1, 0, 2, 1> yxzy;
dswizzle4<1, 0, 2, 2> yxzz;

dswizzle4<1, 1, 0, 2> yyxz;
dswizzle4<1, 1, 1, 2> yyyz;

dswizzle4<1, 1, 2, 0> yyzx;
dswizzle4<1, 1, 2, 1> yyzy;
dswizzle4<1, 1, 2, 2> yyzz;

dswizzle4<1, 2, 0, 0> yzxx;
dswizzle4<1, 2, 0, 1> yzxy;
dswizzle4<1, 2, 0, 2> yzxz;

dswizzle4<1, 2, 1, 0> yzyx;
dswizzle4<1, 2, 1, 1> yzyy;
dswizzle4<1, 2, 1, 2> yzyz;

dswizzle4<1, 2, 2, 0> yzzx;
dswizzle4<1, 2, 2, 1> yzzy;
dswizzle4<1, 2, 2, 2> yzzz;

dswizzle4<2, 0, 0, 0> zxxx;
dswizzle4<2, 0, 0, 1> zxxy;
dswizzle4<2, 0, 0, 2> zxxz;

dswizzle4<2, 0, 1, 0> zxyx;
dswizzle4<2, 0, 1, 1> zxyy;
dswizzle4<2, 0, 1, 2> zxyz;

dswizzle4<2, 0, 2, 0> zxzx;
dswizzle4<2, 0, 2, 1> zxzy;
dswizzle4<2, 0, 2, 2> zxzz;

dswizzle4<2, 1, 0, 0> zyxx;
dswizzle4<2, 1, 0, 1> zyxy;
dswizzle4<2, 1, 0, 2> zyxz;

dswizzle4<2, 1, 1, 0> zyyx;
dswizzle4<2, 1, 1, 1> zyyy;
dswizzle4<2, 1, 1, 2> zyyz;

dswizzle4<2, 1, 2, 0> zyzx;
dswizzle4<2, 1, 2, 1> zyzy;
dswizzle4<2, 1, 2, 2> zyzz;

dswizzle4<2, 2, 0, 0> zzxx;
dswizzle4<2, 2, 0, 1> zzxy;
dswizzle4<2, 2, 0, 2> zzxz;

dswizzle4<2, 2, 1, 0> zzyx;
dswizzle4<2, 2, 1, 1> zzyy;
dswizzle4<2, 2, 1, 2> zzyz;

dswizzle4<2, 2, 2, 0> zzzx;
dswizzle4<2, 2, 2, 1> zzzy;
dswizzle4<2, 2, 2, 2> zzzz;

// -------------------------------
// RGBA
// -------------------------------

dswizzle1<2> b;

dswizzle2<0, 2> rb;
dswizzle2<1, 2> gb;
dswizzle2<2, 0> br;
dswizzle2<2, 1> bg;
dswizzle2<2, 2> bb;

dswizzle3<0, 0, 2> rrb;
dswizzle3<0, 1, 2> rgb;
dswizzle3<0, 2, 0> rbr;
dswizzle3<0, 2, 1> rbg;
dswizzle3<0, 2, 2> rbb;

dswizzle3<1, 0, 2> grb;
dswizzle3<1, 1, 2> ggb;
dswizzle3<1, 2, 0> gbr;
dswizzle3<1, 2, 1> gbg;
dswizzle3<1, 2, 2> gbb;

dswizzle3<2, 0, 0> brr;
dswizzle3<2, 0, 1> brg;
dswizzle3<2, 0, 2> brb;
dswizzle3<2, 1, 0> bgr;
dswizzle3<2, 1, 1> bgg;
dswizzle3<2, 1, 2> bgb;

dswizzle3<2, 2, 0> bbr;
dswizzle3<2, 2, 1> bbg;
dswizzle3<2, 2, 2> bbb;

dswizzle4<0, 0, 0, 2> rrrb;
dswizzle4<0, 0, 1, 2> rrgb;

dswizzle4<0, 0, 2, 0> rrbr;
dswizzle4<0, 0, 2, 1> rrbg;
dswizzle4<0, 0, 2, 2> rrbb;

dswizzle4<0, 1, 0, 2> rgrb;
dswizzle4<0, 1, 1, 2> rggb;

dswizzle4<0, 1, 2, 0> rgbr;
dswizzle4<0, 1, 2, 1> rgbg;
dswizzle4<0, 1, 2, 2> rgbb;

dswizzle4<0, 2, 0, 0> rbrr;
dswizzle4<0, 2, 0, 1> rbrg;
dswizzle4<0, 2, 0, 2> rbrb;

dswizzle4<0, 2, 1, 0> rbgr;
dswizzle4<0, 2, 1, 1> rbgg;
dswizzle4<0, 2, 1, 2> rbgb;

dswizzle4<0, 2, 2, 0> rbbr;
dswizzle4<0, 2, 2, 1> rbbg;
dswizzle4<0, 2, 2, 2> rbbb;

dswizzle4<1, 0, 0, 2> grrb;
dswizzle4<1, 0, 1, 2> grgb;
dswizzle4<1, 0, 2, 0> grbr;
dswizzle4<1, 0, 2, 1> grbg;
dswizzle4<1, 0, 2, 2> grbb;

dswizzle4<1, 1, 0, 2> ggrb;
dswizzle4<1, 1, 1, 2> gggb;

dswizzle4<1, 1, 2, 0> ggbr;
dswizzle4<1, 1, 2, 1> ggbg;
dswizzle4<1, 1, 2, 2> ggbb;

dswizzle4<1, 2, 0, 0> gbrr;
dswizzle4<1, 2, 0, 1> gbrg;
dswizzle4<1, 2, 0, 2> gbrb;

dswizzle4<1, 2, 1, 0> gbgr;
dswizzle4<1, 2, 1, 1> gbgg;
dswizzle4<1, 2, 1, 2> gbgb;

dswizzle4<1, 2, 2, 0> gbbr;
dswizzle4<1, 2, 2, 1> gbbg;
dswizzle4<1, 2, 2, 2> gbbb;

dswizzle4<2, 0, 0, 0> brrr;
dswizzle4<2, 0, 0, 1> brrg;
dswizzle4<2, 0, 0, 2> brrb;

dswizzle4<2, 0, 1, 0> brgr;
dswizzle4<2, 0, 1, 1> brgg;
dswizzle4<2, 0, 1, 2> brgb;

dswizzle4<2, 0, 2, 0> brbr;
dswizzle4<2, 0, 2, 1> brbg;
dswizzle4<2, 0, 2, 2> brbb;

dswizzle4<2, 1, 0, 0> bgrr;
dswizzle4<2, 1, 0, 1> bgrg;
dswizzle4<2, 1, 0, 2> bgrb;

dswizzle4<2, 1, 1, 0> bggr;
dswizzle4<2, 1, 1, 1> bggg;
dswizzle4<2, 1, 1, 2> bggb;

dswizzle4<2, 1, 2, 0> bgbr;
dswizzle4<2, 1, 2, 1> bgbg;
dswizzle4<2, 1, 2, 2> bgbb;

dswizzle4<2, 2, 0, 0> bbrr;
dswizzle4<2, 2, 0, 1> bbrg;
dswizzle4<2, 2, 0, 2> bbrb;

dswizzle4<2, 2, 1, 0> bbgr;
dswizzle4<2, 2, 1, 1> bbgg;
dswizzle4<2, 2, 1, 2> bbgb;

dswizzle4<2, 2, 2, 0> bbbr;
dswizzle4<2, 2, 2, 1> bbbg;
dswizzle4<2, 2, 2, 2> bbbb;