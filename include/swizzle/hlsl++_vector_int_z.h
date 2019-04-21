// -------------------------------
// XYZW
// -------------------------------

iswizzle1<2> z;

iswizzle2<0, 2> xz;
iswizzle2<1, 2> yz;
iswizzle2<2, 0> zx;
iswizzle2<2, 1> zy;
iswizzle2<2, 2> zz;

iswizzle3<0, 0, 2> xxz;
iswizzle3<0, 1, 2> xyz;
iswizzle3<0, 2, 0> xzx;
iswizzle3<0, 2, 1> xzy;
iswizzle3<0, 2, 2> xzz;

iswizzle3<1, 0, 2> yxz;
iswizzle3<1, 1, 2> yyz;
iswizzle3<1, 2, 0> yzx;
iswizzle3<1, 2, 1> yzy;
iswizzle3<1, 2, 2> yzz;

iswizzle3<2, 0, 0> zxx;
iswizzle3<2, 0, 1> zxy;
iswizzle3<2, 0, 2> zxz;
iswizzle3<2, 1, 0> zyx;
iswizzle3<2, 1, 1> zyy;
iswizzle3<2, 1, 2> zyz;

iswizzle3<2, 2, 0> zzx;
iswizzle3<2, 2, 1> zzy;
iswizzle3<2, 2, 2> zzz;

iswizzle4<0, 0, 0, 2> xxxz;
iswizzle4<0, 0, 1, 2> xxyz;

iswizzle4<0, 0, 2, 0> xxzx;
iswizzle4<0, 0, 2, 1> xxzy;
iswizzle4<0, 0, 2, 2> xxzz;

iswizzle4<0, 1, 0, 2> xyxz;
iswizzle4<0, 1, 1, 2> xyyz;

iswizzle4<0, 1, 2, 0> xyzx;
iswizzle4<0, 1, 2, 1> xyzy;
iswizzle4<0, 1, 2, 2> xyzz;

iswizzle4<0, 2, 0, 0> xzxx;
iswizzle4<0, 2, 0, 1> xzxy;
iswizzle4<0, 2, 0, 2> xzxz;

iswizzle4<0, 2, 1, 0> xzyx;
iswizzle4<0, 2, 1, 1> xzyy;
iswizzle4<0, 2, 1, 2> xzyz;

iswizzle4<0, 2, 2, 0> xzzx;
iswizzle4<0, 2, 2, 1> xzzy;
iswizzle4<0, 2, 2, 2> xzzz;

iswizzle4<1, 0, 0, 2> yxxz;
iswizzle4<1, 0, 1, 2> yxyz;
iswizzle4<1, 0, 2, 0> yxzx;
iswizzle4<1, 0, 2, 1> yxzy;
iswizzle4<1, 0, 2, 2> yxzz;

iswizzle4<1, 1, 0, 2> yyxz;
iswizzle4<1, 1, 1, 2> yyyz;

iswizzle4<1, 1, 2, 0> yyzx;
iswizzle4<1, 1, 2, 1> yyzy;
iswizzle4<1, 1, 2, 2> yyzz;

iswizzle4<1, 2, 0, 0> yzxx;
iswizzle4<1, 2, 0, 1> yzxy;
iswizzle4<1, 2, 0, 2> yzxz;

iswizzle4<1, 2, 1, 0> yzyx;
iswizzle4<1, 2, 1, 1> yzyy;
iswizzle4<1, 2, 1, 2> yzyz;

iswizzle4<1, 2, 2, 0> yzzx;
iswizzle4<1, 2, 2, 1> yzzy;
iswizzle4<1, 2, 2, 2> yzzz;

iswizzle4<2, 0, 0, 0> zxxx;
iswizzle4<2, 0, 0, 1> zxxy;
iswizzle4<2, 0, 0, 2> zxxz;

iswizzle4<2, 0, 1, 0> zxyx;
iswizzle4<2, 0, 1, 1> zxyy;
iswizzle4<2, 0, 1, 2> zxyz;

iswizzle4<2, 0, 2, 0> zxzx;
iswizzle4<2, 0, 2, 1> zxzy;
iswizzle4<2, 0, 2, 2> zxzz;

iswizzle4<2, 1, 0, 0> zyxx;
iswizzle4<2, 1, 0, 1> zyxy;
iswizzle4<2, 1, 0, 2> zyxz;

iswizzle4<2, 1, 1, 0> zyyx;
iswizzle4<2, 1, 1, 1> zyyy;
iswizzle4<2, 1, 1, 2> zyyz;

iswizzle4<2, 1, 2, 0> zyzx;
iswizzle4<2, 1, 2, 1> zyzy;
iswizzle4<2, 1, 2, 2> zyzz;

iswizzle4<2, 2, 0, 0> zzxx;
iswizzle4<2, 2, 0, 1> zzxy;
iswizzle4<2, 2, 0, 2> zzxz;

iswizzle4<2, 2, 1, 0> zzyx;
iswizzle4<2, 2, 1, 1> zzyy;
iswizzle4<2, 2, 1, 2> zzyz;

iswizzle4<2, 2, 2, 0> zzzx;
iswizzle4<2, 2, 2, 1> zzzy;
iswizzle4<2, 2, 2, 2> zzzz;

// -------------------------------
// RGBA
// -------------------------------

iswizzle1<2> b;

iswizzle2<0, 2> rb;
iswizzle2<1, 2> gb;
iswizzle2<2, 0> br;
iswizzle2<2, 1> bg;
iswizzle2<2, 2> bb;

iswizzle3<0, 0, 2> rrb;
iswizzle3<0, 1, 2> rgb;
iswizzle3<0, 2, 0> rbr;
iswizzle3<0, 2, 1> rbg;
iswizzle3<0, 2, 2> rbb;

iswizzle3<1, 0, 2> grb;
iswizzle3<1, 1, 2> ggb;
iswizzle3<1, 2, 0> gbr;
iswizzle3<1, 2, 1> gbg;
iswizzle3<1, 2, 2> gbb;

iswizzle3<2, 0, 0> brr;
iswizzle3<2, 0, 1> brg;
iswizzle3<2, 0, 2> brb;
iswizzle3<2, 1, 0> bgr;
iswizzle3<2, 1, 1> bgg;
iswizzle3<2, 1, 2> bgb;

iswizzle3<2, 2, 0> bbr;
iswizzle3<2, 2, 1> bbg;
iswizzle3<2, 2, 2> bbb;

iswizzle4<0, 0, 0, 2> rrrb;
iswizzle4<0, 0, 1, 2> rrgb;

iswizzle4<0, 0, 2, 0> rrbr;
iswizzle4<0, 0, 2, 1> rrbg;
iswizzle4<0, 0, 2, 2> rrbb;

iswizzle4<0, 1, 0, 2> rgrb;
iswizzle4<0, 1, 1, 2> rggb;

iswizzle4<0, 1, 2, 0> rgbr;
iswizzle4<0, 1, 2, 1> rgbg;
iswizzle4<0, 1, 2, 2> rgbb;

iswizzle4<0, 2, 0, 0> rbrr;
iswizzle4<0, 2, 0, 1> rbrg;
iswizzle4<0, 2, 0, 2> rbrb;

iswizzle4<0, 2, 1, 0> rbgr;
iswizzle4<0, 2, 1, 1> rbgg;
iswizzle4<0, 2, 1, 2> rbgb;

iswizzle4<0, 2, 2, 0> rbbr;
iswizzle4<0, 2, 2, 1> rbbg;
iswizzle4<0, 2, 2, 2> rbbb;

iswizzle4<1, 0, 0, 2> grrb;
iswizzle4<1, 0, 1, 2> grgb;
iswizzle4<1, 0, 2, 0> grbr;
iswizzle4<1, 0, 2, 1> grbg;
iswizzle4<1, 0, 2, 2> grbb;

iswizzle4<1, 1, 0, 2> ggrb;
iswizzle4<1, 1, 1, 2> gggb;

iswizzle4<1, 1, 2, 0> ggbr;
iswizzle4<1, 1, 2, 1> ggbg;
iswizzle4<1, 1, 2, 2> ggbb;

iswizzle4<1, 2, 0, 0> gbrr;
iswizzle4<1, 2, 0, 1> gbrg;
iswizzle4<1, 2, 0, 2> gbrb;

iswizzle4<1, 2, 1, 0> gbgr;
iswizzle4<1, 2, 1, 1> gbgg;
iswizzle4<1, 2, 1, 2> gbgb;

iswizzle4<1, 2, 2, 0> gbbr;
iswizzle4<1, 2, 2, 1> gbbg;
iswizzle4<1, 2, 2, 2> gbbb;

iswizzle4<2, 0, 0, 0> brrr;
iswizzle4<2, 0, 0, 1> brrg;
iswizzle4<2, 0, 0, 2> brrb;

iswizzle4<2, 0, 1, 0> brgr;
iswizzle4<2, 0, 1, 1> brgg;
iswizzle4<2, 0, 1, 2> brgb;

iswizzle4<2, 0, 2, 0> brbr;
iswizzle4<2, 0, 2, 1> brbg;
iswizzle4<2, 0, 2, 2> brbb;

iswizzle4<2, 1, 0, 0> bgrr;
iswizzle4<2, 1, 0, 1> bgrg;
iswizzle4<2, 1, 0, 2> bgrb;

iswizzle4<2, 1, 1, 0> bggr;
iswizzle4<2, 1, 1, 1> bggg;
iswizzle4<2, 1, 1, 2> bggb;

iswizzle4<2, 1, 2, 0> bgbr;
iswizzle4<2, 1, 2, 1> bgbg;
iswizzle4<2, 1, 2, 2> bgbb;

iswizzle4<2, 2, 0, 0> bbrr;
iswizzle4<2, 2, 0, 1> bbrg;
iswizzle4<2, 2, 0, 2> bbrb;

iswizzle4<2, 2, 1, 0> bbgr;
iswizzle4<2, 2, 1, 1> bbgg;
iswizzle4<2, 2, 1, 2> bbgb;

iswizzle4<2, 2, 2, 0> bbbr;
iswizzle4<2, 2, 2, 1> bbbg;
iswizzle4<2, 2, 2, 2> bbbb;