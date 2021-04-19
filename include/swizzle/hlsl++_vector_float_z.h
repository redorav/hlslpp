// -------------------------------
// XYZW
// -------------------------------

swizzle1<2> z;

swizzle2<0, 2> xz;
swizzle2<1, 2> yz;
swizzle2<2, 0> zx;
swizzle2<2, 1> zy;
swizzle2<2, 2> zz;

swizzle3<0, 0, 2> xxz;
swizzle3<0, 1, 2> xyz;
swizzle3<0, 2, 0> xzx;
swizzle3<0, 2, 1> xzy;
swizzle3<0, 2, 2> xzz;

swizzle3<1, 0, 2> yxz;
swizzle3<1, 1, 2> yyz;
swizzle3<1, 2, 0> yzx;
swizzle3<1, 2, 1> yzy;
swizzle3<1, 2, 2> yzz;

swizzle3<2, 0, 0> zxx;
swizzle3<2, 0, 1> zxy;
swizzle3<2, 0, 2> zxz;
swizzle3<2, 1, 0> zyx;
swizzle3<2, 1, 1> zyy;
swizzle3<2, 1, 2> zyz;

swizzle3<2, 2, 0> zzx;
swizzle3<2, 2, 1> zzy;
swizzle3<2, 2, 2> zzz;

swizzle4<0, 0, 0, 2> xxxz;
swizzle4<0, 0, 1, 2> xxyz;

swizzle4<0, 0, 2, 0> xxzx;
swizzle4<0, 0, 2, 1> xxzy;
swizzle4<0, 0, 2, 2> xxzz;

swizzle4<0, 1, 0, 2> xyxz;
swizzle4<0, 1, 1, 2> xyyz;

swizzle4<0, 1, 2, 0> xyzx;
swizzle4<0, 1, 2, 1> xyzy;
swizzle4<0, 1, 2, 2> xyzz;

swizzle4<0, 2, 0, 0> xzxx;
swizzle4<0, 2, 0, 1> xzxy;
swizzle4<0, 2, 0, 2> xzxz;

swizzle4<0, 2, 1, 0> xzyx;
swizzle4<0, 2, 1, 1> xzyy;
swizzle4<0, 2, 1, 2> xzyz;

swizzle4<0, 2, 2, 0> xzzx;
swizzle4<0, 2, 2, 1> xzzy;
swizzle4<0, 2, 2, 2> xzzz;

swizzle4<1, 0, 0, 2> yxxz;
swizzle4<1, 0, 1, 2> yxyz;
swizzle4<1, 0, 2, 0> yxzx;
swizzle4<1, 0, 2, 1> yxzy;
swizzle4<1, 0, 2, 2> yxzz;

swizzle4<1, 1, 0, 2> yyxz;
swizzle4<1, 1, 1, 2> yyyz;

swizzle4<1, 1, 2, 0> yyzx;
swizzle4<1, 1, 2, 1> yyzy;
swizzle4<1, 1, 2, 2> yyzz;

swizzle4<1, 2, 0, 0> yzxx;
swizzle4<1, 2, 0, 1> yzxy;
swizzle4<1, 2, 0, 2> yzxz;

swizzle4<1, 2, 1, 0> yzyx;
swizzle4<1, 2, 1, 1> yzyy;
swizzle4<1, 2, 1, 2> yzyz;

swizzle4<1, 2, 2, 0> yzzx;
swizzle4<1, 2, 2, 1> yzzy;
swizzle4<1, 2, 2, 2> yzzz;

swizzle4<2, 0, 0, 0> zxxx;
swizzle4<2, 0, 0, 1> zxxy;
swizzle4<2, 0, 0, 2> zxxz;

swizzle4<2, 0, 1, 0> zxyx;
swizzle4<2, 0, 1, 1> zxyy;
swizzle4<2, 0, 1, 2> zxyz;

swizzle4<2, 0, 2, 0> zxzx;
swizzle4<2, 0, 2, 1> zxzy;
swizzle4<2, 0, 2, 2> zxzz;

swizzle4<2, 1, 0, 0> zyxx;
swizzle4<2, 1, 0, 1> zyxy;
swizzle4<2, 1, 0, 2> zyxz;

swizzle4<2, 1, 1, 0> zyyx;
swizzle4<2, 1, 1, 1> zyyy;
swizzle4<2, 1, 1, 2> zyyz;

swizzle4<2, 1, 2, 0> zyzx;
swizzle4<2, 1, 2, 1> zyzy;
swizzle4<2, 1, 2, 2> zyzz;

swizzle4<2, 2, 0, 0> zzxx;
swizzle4<2, 2, 0, 1> zzxy;
swizzle4<2, 2, 0, 2> zzxz;

swizzle4<2, 2, 1, 0> zzyx;
swizzle4<2, 2, 1, 1> zzyy;
swizzle4<2, 2, 1, 2> zzyz;

swizzle4<2, 2, 2, 0> zzzx;
swizzle4<2, 2, 2, 1> zzzy;
swizzle4<2, 2, 2, 2> zzzz;

// -------------------------------
// RGBA
// -------------------------------

swizzle1<2> b;

swizzle2<0, 2> rb;
swizzle2<1, 2> gb;
swizzle2<2, 0> br;
swizzle2<2, 1> bg;
swizzle2<2, 2> bb;

swizzle3<0, 0, 2> rrb;
swizzle3<0, 1, 2> rgb;
swizzle3<0, 2, 0> rbr;
swizzle3<0, 2, 1> rbg;
swizzle3<0, 2, 2> rbb;

swizzle3<1, 0, 2> grb;
swizzle3<1, 1, 2> ggb;
swizzle3<1, 2, 0> gbr;
swizzle3<1, 2, 1> gbg;
swizzle3<1, 2, 2> gbb;

swizzle3<2, 0, 0> brr;
swizzle3<2, 0, 1> brg;
swizzle3<2, 0, 2> brb;
swizzle3<2, 1, 0> bgr;
swizzle3<2, 1, 1> bgg;
swizzle3<2, 1, 2> bgb;

swizzle3<2, 2, 0> bbr;
swizzle3<2, 2, 1> bbg;
swizzle3<2, 2, 2> bbb;

swizzle4<0, 0, 0, 2> rrrb;
swizzle4<0, 0, 1, 2> rrgb;

swizzle4<0, 0, 2, 0> rrbr;
swizzle4<0, 0, 2, 1> rrbg;
swizzle4<0, 0, 2, 2> rrbb;

swizzle4<0, 1, 0, 2> rgrb;
swizzle4<0, 1, 1, 2> rggb;

swizzle4<0, 1, 2, 0> rgbr;
swizzle4<0, 1, 2, 1> rgbg;
swizzle4<0, 1, 2, 2> rgbb;

swizzle4<0, 2, 0, 0> rbrr;
swizzle4<0, 2, 0, 1> rbrg;
swizzle4<0, 2, 0, 2> rbrb;

swizzle4<0, 2, 1, 0> rbgr;
swizzle4<0, 2, 1, 1> rbgg;
swizzle4<0, 2, 1, 2> rbgb;

swizzle4<0, 2, 2, 0> rbbr;
swizzle4<0, 2, 2, 1> rbbg;
swizzle4<0, 2, 2, 2> rbbb;

swizzle4<1, 0, 0, 2> grrb;
swizzle4<1, 0, 1, 2> grgb;
swizzle4<1, 0, 2, 0> grbr;
swizzle4<1, 0, 2, 1> grbg;
swizzle4<1, 0, 2, 2> grbb;

swizzle4<1, 1, 0, 2> ggrb;
swizzle4<1, 1, 1, 2> gggb;

swizzle4<1, 1, 2, 0> ggbr;
swizzle4<1, 1, 2, 1> ggbg;
swizzle4<1, 1, 2, 2> ggbb;

swizzle4<1, 2, 0, 0> gbrr;
swizzle4<1, 2, 0, 1> gbrg;
swizzle4<1, 2, 0, 2> gbrb;

swizzle4<1, 2, 1, 0> gbgr;
swizzle4<1, 2, 1, 1> gbgg;
swizzle4<1, 2, 1, 2> gbgb;

swizzle4<1, 2, 2, 0> gbbr;
swizzle4<1, 2, 2, 1> gbbg;
swizzle4<1, 2, 2, 2> gbbb;

swizzle4<2, 0, 0, 0> brrr;
swizzle4<2, 0, 0, 1> brrg;
swizzle4<2, 0, 0, 2> brrb;

swizzle4<2, 0, 1, 0> brgr;
swizzle4<2, 0, 1, 1> brgg;
swizzle4<2, 0, 1, 2> brgb;

swizzle4<2, 0, 2, 0> brbr;
swizzle4<2, 0, 2, 1> brbg;
swizzle4<2, 0, 2, 2> brbb;

swizzle4<2, 1, 0, 0> bgrr;
swizzle4<2, 1, 0, 1> bgrg;
swizzle4<2, 1, 0, 2> bgrb;

swizzle4<2, 1, 1, 0> bggr;
swizzle4<2, 1, 1, 1> bggg;
swizzle4<2, 1, 1, 2> bggb;

swizzle4<2, 1, 2, 0> bgbr;
swizzle4<2, 1, 2, 1> bgbg;
swizzle4<2, 1, 2, 2> bgbb;

swizzle4<2, 2, 0, 0> bbrr;
swizzle4<2, 2, 0, 1> bbrg;
swizzle4<2, 2, 0, 2> bbrb;

swizzle4<2, 2, 1, 0> bbgr;
swizzle4<2, 2, 1, 1> bbgg;
swizzle4<2, 2, 1, 2> bbgb;

swizzle4<2, 2, 2, 0> bbbr;
swizzle4<2, 2, 2, 1> bbbg;
swizzle4<2, 2, 2, 2> bbbb;