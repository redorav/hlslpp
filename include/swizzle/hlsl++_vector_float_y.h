// -------------------------------
// XYZW
// -------------------------------

struct { swizzle1<1> y; };

struct { swizzle2<0, 1> xy; };
struct { swizzle2<1, 0> yx; };
struct { swizzle2<1, 1> yy; };

struct { swizzle3<0, 0, 1> xxy; };
struct { swizzle3<0, 1, 0> xyx; };
struct { swizzle3<0, 1, 1> xyy; };

struct { swizzle3<1, 0, 0> yxx; };
struct { swizzle3<1, 0, 1> yxy; };
struct { swizzle3<1, 1, 0> yyx; };
struct { swizzle3<1, 1, 1> yyy; };

struct { swizzle4<0, 0, 0, 1> xxxy; };

struct { swizzle4<0, 0, 1, 0> xxyx; };
struct { swizzle4<0, 0, 1, 1> xxyy; };

struct { swizzle4<0, 1, 0, 0> xyxx; };
struct { swizzle4<0, 1, 0, 1> xyxy; };

struct { swizzle4<0, 1, 1, 0> xyyx; };
struct { swizzle4<0, 1, 1, 1> xyyy; };

struct { swizzle4<1, 0, 0, 0> yxxx; };
struct { swizzle4<1, 0, 0, 1> yxxy; };

struct { swizzle4<1, 0, 1, 0> yxyx; };
struct { swizzle4<1, 0, 1, 1> yxyy; };

struct { swizzle4<1, 1, 0, 0> yyxx; };
struct { swizzle4<1, 1, 0, 1> yyxy; };

struct { swizzle4<1, 1, 1, 0> yyyx; };
struct { swizzle4<1, 1, 1, 1> yyyy; };

// -------------------------------
// RGBA
// -------------------------------

struct { swizzle1<1> g; };

struct { swizzle2<0, 1> rg; };
struct { swizzle2<1, 0> gr; };
struct { swizzle2<1, 1> gg; };

struct { swizzle3<0, 0, 1> rrg; };
struct { swizzle3<0, 1, 0> rgr; };
struct { swizzle3<0, 1, 1> rgg; };

struct { swizzle3<1, 0, 0> grr; };
struct { swizzle3<1, 0, 1> grg; };
struct { swizzle3<1, 1, 0> ggr; };
struct { swizzle3<1, 1, 1> ggg; };

struct { swizzle4<0, 0, 0, 1> rrrg; };

struct { swizzle4<0, 0, 1, 0> rrgr; };
struct { swizzle4<0, 0, 1, 1> rrgg; };

struct { swizzle4<0, 1, 0, 0> rgrr; };
struct { swizzle4<0, 1, 0, 1> rgrg; };

struct { swizzle4<0, 1, 1, 0> rggr; };
struct { swizzle4<0, 1, 1, 1> rggg; };

struct { swizzle4<1, 0, 0, 0> grrr; };
struct { swizzle4<1, 0, 0, 1> grrg; };

struct { swizzle4<1, 0, 1, 0> grgr; };
struct { swizzle4<1, 0, 1, 1> grgg; };

struct { swizzle4<1, 1, 0, 0> ggrr; };
struct { swizzle4<1, 1, 0, 1> ggrg; };

struct { swizzle4<1, 1, 1, 0> gggr; };
struct { swizzle4<1, 1, 1, 1> gggg; };