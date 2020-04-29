// -------------------------------
// XYZW
// -------------------------------

uswizzle1<2> z;

uswizzle2<0, 2> xz;
uswizzle2<1, 2> yz;
uswizzle2<2, 0> zx;
uswizzle2<2, 1> zy;
uswizzle2<2, 2> zz;

uswizzle3<0, 0, 2> xxz;
uswizzle3<0, 1, 2> xyz;
uswizzle3<0, 2, 0> xzx;
uswizzle3<0, 2, 1> xzy;
uswizzle3<0, 2, 2> xzz;

uswizzle3<1, 0, 2> yxz;
uswizzle3<1, 1, 2> yyz;
uswizzle3<1, 2, 0> yzx;
uswizzle3<1, 2, 1> yzy;
uswizzle3<1, 2, 2> yzz;

uswizzle3<2, 0, 0> zxx;
uswizzle3<2, 0, 1> zxy;
uswizzle3<2, 0, 2> zxz;
uswizzle3<2, 1, 0> zyx;
uswizzle3<2, 1, 1> zyy;
uswizzle3<2, 1, 2> zyz;

uswizzle3<2, 2, 0> zzx;
uswizzle3<2, 2, 1> zzy;
uswizzle3<2, 2, 2> zzz;

uswizzle4<0, 0, 0, 2> xxxz;
uswizzle4<0, 0, 1, 2> xxyz;

uswizzle4<0, 0, 2, 0> xxzx;
uswizzle4<0, 0, 2, 1> xxzy;
uswizzle4<0, 0, 2, 2> xxzz;

uswizzle4<0, 1, 0, 2> xyxz;
uswizzle4<0, 1, 1, 2> xyyz;

uswizzle4<0, 1, 2, 0> xyzx;
uswizzle4<0, 1, 2, 1> xyzy;
uswizzle4<0, 1, 2, 2> xyzz;

uswizzle4<0, 2, 0, 0> xzxx;
uswizzle4<0, 2, 0, 1> xzxy;
uswizzle4<0, 2, 0, 2> xzxz;

uswizzle4<0, 2, 1, 0> xzyx;
uswizzle4<0, 2, 1, 1> xzyy;
uswizzle4<0, 2, 1, 2> xzyz;

uswizzle4<0, 2, 2, 0> xzzx;
uswizzle4<0, 2, 2, 1> xzzy;
uswizzle4<0, 2, 2, 2> xzzz;

uswizzle4<1, 0, 0, 2> yxxz;
uswizzle4<1, 0, 1, 2> yxyz;
uswizzle4<1, 0, 2, 0> yxzx;
uswizzle4<1, 0, 2, 1> yxzy;
uswizzle4<1, 0, 2, 2> yxzz;

uswizzle4<1, 1, 0, 2> yyxz;
uswizzle4<1, 1, 1, 2> yyyz;

uswizzle4<1, 1, 2, 0> yyzx;
uswizzle4<1, 1, 2, 1> yyzy;
uswizzle4<1, 1, 2, 2> yyzz;

uswizzle4<1, 2, 0, 0> yzxx;
uswizzle4<1, 2, 0, 1> yzxy;
uswizzle4<1, 2, 0, 2> yzxz;

uswizzle4<1, 2, 1, 0> yzyx;
uswizzle4<1, 2, 1, 1> yzyy;
uswizzle4<1, 2, 1, 2> yzyz;

uswizzle4<1, 2, 2, 0> yzzx;
uswizzle4<1, 2, 2, 1> yzzy;
uswizzle4<1, 2, 2, 2> yzzz;

uswizzle4<2, 0, 0, 0> zxxx;
uswizzle4<2, 0, 0, 1> zxxy;
uswizzle4<2, 0, 0, 2> zxxz;

uswizzle4<2, 0, 1, 0> zxyx;
uswizzle4<2, 0, 1, 1> zxyy;
uswizzle4<2, 0, 1, 2> zxyz;

uswizzle4<2, 0, 2, 0> zxzx;
uswizzle4<2, 0, 2, 1> zxzy;
uswizzle4<2, 0, 2, 2> zxzz;

uswizzle4<2, 1, 0, 0> zyxx;
uswizzle4<2, 1, 0, 1> zyxy;
uswizzle4<2, 1, 0, 2> zyxz;

uswizzle4<2, 1, 1, 0> zyyx;
uswizzle4<2, 1, 1, 1> zyyy;
uswizzle4<2, 1, 1, 2> zyyz;

uswizzle4<2, 1, 2, 0> zyzx;
uswizzle4<2, 1, 2, 1> zyzy;
uswizzle4<2, 1, 2, 2> zyzz;

uswizzle4<2, 2, 0, 0> zzxx;
uswizzle4<2, 2, 0, 1> zzxy;
uswizzle4<2, 2, 0, 2> zzxz;

uswizzle4<2, 2, 1, 0> zzyx;
uswizzle4<2, 2, 1, 1> zzyy;
uswizzle4<2, 2, 1, 2> zzyz;

uswizzle4<2, 2, 2, 0> zzzx;
uswizzle4<2, 2, 2, 1> zzzy;
uswizzle4<2, 2, 2, 2> zzzz;

// -------------------------------
// RGBA
// -------------------------------

uswizzle1<2> b;

uswizzle2<0, 2> rb;
uswizzle2<1, 2> gb;
uswizzle2<2, 0> br;
uswizzle2<2, 1> bg;
uswizzle2<2, 2> bb;

uswizzle3<0, 0, 2> rrb;
uswizzle3<0, 1, 2> rgb;
uswizzle3<0, 2, 0> rbr;
uswizzle3<0, 2, 1> rbg;
uswizzle3<0, 2, 2> rbb;

uswizzle3<1, 0, 2> grb;
uswizzle3<1, 1, 2> ggb;
uswizzle3<1, 2, 0> gbr;
uswizzle3<1, 2, 1> gbg;
uswizzle3<1, 2, 2> gbb;

uswizzle3<2, 0, 0> brr;
uswizzle3<2, 0, 1> brg;
uswizzle3<2, 0, 2> brb;
uswizzle3<2, 1, 0> bgr;
uswizzle3<2, 1, 1> bgg;
uswizzle3<2, 1, 2> bgb;

uswizzle3<2, 2, 0> bbr;
uswizzle3<2, 2, 1> bbg;
uswizzle3<2, 2, 2> bbb;

uswizzle4<0, 0, 0, 2> rrrb;
uswizzle4<0, 0, 1, 2> rrgb;

uswizzle4<0, 0, 2, 0> rrbr;
uswizzle4<0, 0, 2, 1> rrbg;
uswizzle4<0, 0, 2, 2> rrbb;

uswizzle4<0, 1, 0, 2> rgrb;
uswizzle4<0, 1, 1, 2> rggb;

uswizzle4<0, 1, 2, 0> rgbr;
uswizzle4<0, 1, 2, 1> rgbg;
uswizzle4<0, 1, 2, 2> rgbb;

uswizzle4<0, 2, 0, 0> rbrr;
uswizzle4<0, 2, 0, 1> rbrg;
uswizzle4<0, 2, 0, 2> rbrb;

uswizzle4<0, 2, 1, 0> rbgr;
uswizzle4<0, 2, 1, 1> rbgg;
uswizzle4<0, 2, 1, 2> rbgb;

uswizzle4<0, 2, 2, 0> rbbr;
uswizzle4<0, 2, 2, 1> rbbg;
uswizzle4<0, 2, 2, 2> rbbb;

uswizzle4<1, 0, 0, 2> grrb;
uswizzle4<1, 0, 1, 2> grgb;
uswizzle4<1, 0, 2, 0> grbr;
uswizzle4<1, 0, 2, 1> grbg;
uswizzle4<1, 0, 2, 2> grbb;

uswizzle4<1, 1, 0, 2> ggrb;
uswizzle4<1, 1, 1, 2> gggb;

uswizzle4<1, 1, 2, 0> ggbr;
uswizzle4<1, 1, 2, 1> ggbg;
uswizzle4<1, 1, 2, 2> ggbb;

uswizzle4<1, 2, 0, 0> gbrr;
uswizzle4<1, 2, 0, 1> gbrg;
uswizzle4<1, 2, 0, 2> gbrb;

uswizzle4<1, 2, 1, 0> gbgr;
uswizzle4<1, 2, 1, 1> gbgg;
uswizzle4<1, 2, 1, 2> gbgb;

uswizzle4<1, 2, 2, 0> gbbr;
uswizzle4<1, 2, 2, 1> gbbg;
uswizzle4<1, 2, 2, 2> gbbb;

uswizzle4<2, 0, 0, 0> brrr;
uswizzle4<2, 0, 0, 1> brrg;
uswizzle4<2, 0, 0, 2> brrb;

uswizzle4<2, 0, 1, 0> brgr;
uswizzle4<2, 0, 1, 1> brgg;
uswizzle4<2, 0, 1, 2> brgb;

uswizzle4<2, 0, 2, 0> brbr;
uswizzle4<2, 0, 2, 1> brbg;
uswizzle4<2, 0, 2, 2> brbb;

uswizzle4<2, 1, 0, 0> bgrr;
uswizzle4<2, 1, 0, 1> bgrg;
uswizzle4<2, 1, 0, 2> bgrb;

uswizzle4<2, 1, 1, 0> bggr;
uswizzle4<2, 1, 1, 1> bggg;
uswizzle4<2, 1, 1, 2> bggb;

uswizzle4<2, 1, 2, 0> bgbr;
uswizzle4<2, 1, 2, 1> bgbg;
uswizzle4<2, 1, 2, 2> bgbb;

uswizzle4<2, 2, 0, 0> bbrr;
uswizzle4<2, 2, 0, 1> bbrg;
uswizzle4<2, 2, 0, 2> bbrb;

uswizzle4<2, 2, 1, 0> bbgr;
uswizzle4<2, 2, 1, 1> bbgg;
uswizzle4<2, 2, 1, 2> bbgb;

uswizzle4<2, 2, 2, 0> bbbr;
uswizzle4<2, 2, 2, 1> bbbg;
uswizzle4<2, 2, 2, 2> bbbb;