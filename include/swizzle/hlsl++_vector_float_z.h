// -------------------------------
// XYZW
// -------------------------------

struct { swizzle1<2> z; };

struct { swizzle2<0, 2> xz; };
struct { swizzle2<1, 2> yz; };
struct { swizzle2<2, 0> zx; };
struct { swizzle2<2, 1> zy; };
struct { swizzle2<2, 2> zz; };

struct { swizzle3<0, 0, 2> xxz; };
struct { swizzle3<0, 1, 2> xyz; };
struct { swizzle3<0, 2, 0> xzx; };
struct { swizzle3<0, 2, 1> xzy; };
struct { swizzle3<0, 2, 2> xzz; };

struct { swizzle3<1, 0, 2> yxz; };
struct { swizzle3<1, 1, 2> yyz; };
struct { swizzle3<1, 2, 0> yzx; };
struct { swizzle3<1, 2, 1> yzy; };
struct { swizzle3<1, 2, 2> yzz; };

struct { swizzle3<2, 0, 0> zxx; };
struct { swizzle3<2, 0, 1> zxy; };
struct { swizzle3<2, 0, 2> zxz; };
struct { swizzle3<2, 1, 0> zyx; };
struct { swizzle3<2, 1, 1> zyy; };
struct { swizzle3<2, 1, 2> zyz; };

struct { swizzle3<2, 2, 0> zzx; };
struct { swizzle3<2, 2, 1> zzy; };
struct { swizzle3<2, 2, 2> zzz; };

struct { swizzle4<0, 0, 0, 2> xxxz; };
struct { swizzle4<0, 0, 1, 2> xxyz; };

struct { swizzle4<0, 0, 2, 0> xxzx; };
struct { swizzle4<0, 0, 2, 1> xxzy; };
struct { swizzle4<0, 0, 2, 2> xxzz; };

struct { swizzle4<0, 1, 0, 2> xyxz; };
struct { swizzle4<0, 1, 1, 2> xyyz; };

struct { swizzle4<0, 1, 2, 0> xyzx; };
struct { swizzle4<0, 1, 2, 1> xyzy; };
struct { swizzle4<0, 1, 2, 2> xyzz; };

struct { swizzle4<0, 2, 0, 0> xzxx; };
struct { swizzle4<0, 2, 0, 1> xzxy; };
struct { swizzle4<0, 2, 0, 2> xzxz; };

struct { swizzle4<0, 2, 1, 0> xzyx; };
struct { swizzle4<0, 2, 1, 1> xzyy; };
struct { swizzle4<0, 2, 1, 2> xzyz; };

struct { swizzle4<0, 2, 2, 0> xzzx; };
struct { swizzle4<0, 2, 2, 1> xzzy; };
struct { swizzle4<0, 2, 2, 2> xzzz; };

struct { swizzle4<1, 0, 0, 2> yxxz; };
struct { swizzle4<1, 0, 1, 2> yxyz; };
struct { swizzle4<1, 0, 2, 0> yxzx; };
struct { swizzle4<1, 0, 2, 1> yxzy; };
struct { swizzle4<1, 0, 2, 2> yxzz; };

struct { swizzle4<1, 1, 0, 2> yyxz; };
struct { swizzle4<1, 1, 1, 2> yyyz; };

struct { swizzle4<1, 1, 2, 0> yyzx; };
struct { swizzle4<1, 1, 2, 1> yyzy; };
struct { swizzle4<1, 1, 2, 2> yyzz; };

struct { swizzle4<1, 2, 0, 0> yzxx; };
struct { swizzle4<1, 2, 0, 1> yzxy; };
struct { swizzle4<1, 2, 0, 2> yzxz; };

struct { swizzle4<1, 2, 1, 0> yzyx; };
struct { swizzle4<1, 2, 1, 1> yzyy; };
struct { swizzle4<1, 2, 1, 2> yzyz; };

struct { swizzle4<1, 2, 2, 0> yzzx; };
struct { swizzle4<1, 2, 2, 1> yzzy; };
struct { swizzle4<1, 2, 2, 2> yzzz; };

struct { swizzle4<2, 0, 0, 0> zxxx; };
struct { swizzle4<2, 0, 0, 1> zxxy; };
struct { swizzle4<2, 0, 0, 2> zxxz; };

struct { swizzle4<2, 0, 1, 0> zxyx; };
struct { swizzle4<2, 0, 1, 1> zxyy; };
struct { swizzle4<2, 0, 1, 2> zxyz; };

struct { swizzle4<2, 0, 2, 0> zxzx; };
struct { swizzle4<2, 0, 2, 1> zxzy; };
struct { swizzle4<2, 0, 2, 2> zxzz; };

struct { swizzle4<2, 1, 0, 0> zyxx; };
struct { swizzle4<2, 1, 0, 1> zyxy; };
struct { swizzle4<2, 1, 0, 2> zyxz; };

struct { swizzle4<2, 1, 1, 0> zyyx; };
struct { swizzle4<2, 1, 1, 1> zyyy; };
struct { swizzle4<2, 1, 1, 2> zyyz; };

struct { swizzle4<2, 1, 2, 0> zyzx; };
struct { swizzle4<2, 1, 2, 1> zyzy; };
struct { swizzle4<2, 1, 2, 2> zyzz; };

struct { swizzle4<2, 2, 0, 0> zzxx; };
struct { swizzle4<2, 2, 0, 1> zzxy; };
struct { swizzle4<2, 2, 0, 2> zzxz; };

struct { swizzle4<2, 2, 1, 0> zzyx; };
struct { swizzle4<2, 2, 1, 1> zzyy; };
struct { swizzle4<2, 2, 1, 2> zzyz; };

struct { swizzle4<2, 2, 2, 0> zzzx; };
struct { swizzle4<2, 2, 2, 1> zzzy; };
struct { swizzle4<2, 2, 2, 2> zzzz; };

// -------------------------------
// RGBA
// -------------------------------

struct { swizzle1<2> b; };

struct { swizzle2<0, 2> rb; };
struct { swizzle2<1, 2> gb; };
struct { swizzle2<2, 0> br; };
struct { swizzle2<2, 1> bg; };
struct { swizzle2<2, 2> bb; };

struct { swizzle3<0, 0, 2> rrb; };
struct { swizzle3<0, 1, 2> rgb; };
struct { swizzle3<0, 2, 0> rbr; };
struct { swizzle3<0, 2, 1> rbg; };
struct { swizzle3<0, 2, 2> rbb; };

struct { swizzle3<1, 0, 2> grb; };
struct { swizzle3<1, 1, 2> ggb; };
struct { swizzle3<1, 2, 0> gbr; };
struct { swizzle3<1, 2, 1> gbg; };
struct { swizzle3<1, 2, 2> gbb; };

struct { swizzle3<2, 0, 0> brr; };
struct { swizzle3<2, 0, 1> brg; };
struct { swizzle3<2, 0, 2> brb; };
struct { swizzle3<2, 1, 0> bgr; };
struct { swizzle3<2, 1, 1> bgg; };
struct { swizzle3<2, 1, 2> bgb; };

struct { swizzle3<2, 2, 0> bbr; };
struct { swizzle3<2, 2, 1> bbg; };
struct { swizzle3<2, 2, 2> bbb; };

struct { swizzle4<0, 0, 0, 2> rrrb; };
struct { swizzle4<0, 0, 1, 2> rrgb; };

struct { swizzle4<0, 0, 2, 0> rrbr; };
struct { swizzle4<0, 0, 2, 1> rrbg; };
struct { swizzle4<0, 0, 2, 2> rrbb; };

struct { swizzle4<0, 1, 0, 2> rgrb; };
struct { swizzle4<0, 1, 1, 2> rggb; };

struct { swizzle4<0, 1, 2, 0> rgbr; };
struct { swizzle4<0, 1, 2, 1> rgbg; };
struct { swizzle4<0, 1, 2, 2> rgbb; };

struct { swizzle4<0, 2, 0, 0> rbrr; };
struct { swizzle4<0, 2, 0, 1> rbrg; };
struct { swizzle4<0, 2, 0, 2> rbrb; };

struct { swizzle4<0, 2, 1, 0> rbgr; };
struct { swizzle4<0, 2, 1, 1> rbgg; };
struct { swizzle4<0, 2, 1, 2> rbgb; };

struct { swizzle4<0, 2, 2, 0> rbbr; };
struct { swizzle4<0, 2, 2, 1> rbbg; };
struct { swizzle4<0, 2, 2, 2> rbbb; };

struct { swizzle4<1, 0, 0, 2> grrb; };
struct { swizzle4<1, 0, 1, 2> grgb; };
struct { swizzle4<1, 0, 2, 0> grbr; };
struct { swizzle4<1, 0, 2, 1> grbg; };
struct { swizzle4<1, 0, 2, 2> grbb; };

struct { swizzle4<1, 1, 0, 2> ggrb; };
struct { swizzle4<1, 1, 1, 2> gggb; };

struct { swizzle4<1, 1, 2, 0> ggbr; };
struct { swizzle4<1, 1, 2, 1> ggbg; };
struct { swizzle4<1, 1, 2, 2> ggbb; };

struct { swizzle4<1, 2, 0, 0> gbrr; };
struct { swizzle4<1, 2, 0, 1> gbrg; };
struct { swizzle4<1, 2, 0, 2> gbrb; };

struct { swizzle4<1, 2, 1, 0> gbgr; };
struct { swizzle4<1, 2, 1, 1> gbgg; };
struct { swizzle4<1, 2, 1, 2> gbgb; };

struct { swizzle4<1, 2, 2, 0> gbbr; };
struct { swizzle4<1, 2, 2, 1> gbbg; };
struct { swizzle4<1, 2, 2, 2> gbbb; };

struct { swizzle4<2, 0, 0, 0> brrr; };
struct { swizzle4<2, 0, 0, 1> brrg; };
struct { swizzle4<2, 0, 0, 2> brrb; };

struct { swizzle4<2, 0, 1, 0> brgr; };
struct { swizzle4<2, 0, 1, 1> brgg; };
struct { swizzle4<2, 0, 1, 2> brgb; };

struct { swizzle4<2, 0, 2, 0> brbr; };
struct { swizzle4<2, 0, 2, 1> brbg; };
struct { swizzle4<2, 0, 2, 2> brbb; };

struct { swizzle4<2, 1, 0, 0> bgrr; };
struct { swizzle4<2, 1, 0, 1> bgrg; };
struct { swizzle4<2, 1, 0, 2> bgrb; };

struct { swizzle4<2, 1, 1, 0> bggr; };
struct { swizzle4<2, 1, 1, 1> bggg; };
struct { swizzle4<2, 1, 1, 2> bggb; };

struct { swizzle4<2, 1, 2, 0> bgbr; };
struct { swizzle4<2, 1, 2, 1> bgbg; };
struct { swizzle4<2, 1, 2, 2> bgbb; };

struct { swizzle4<2, 2, 0, 0> bbrr; };
struct { swizzle4<2, 2, 0, 1> bbrg; };
struct { swizzle4<2, 2, 0, 2> bbrb; };

struct { swizzle4<2, 2, 1, 0> bbgr; };
struct { swizzle4<2, 2, 1, 1> bbgg; };
struct { swizzle4<2, 2, 1, 2> bbgb; };

struct { swizzle4<2, 2, 2, 0> bbbr; };
struct { swizzle4<2, 2, 2, 1> bbbg; };
struct { swizzle4<2, 2, 2, 2> bbbb; };