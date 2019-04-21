// -------------------------------
// XYZW
// -------------------------------

swizzle1<1> y;

swizzle2<0, 1> xy;
swizzle2<1, 0> yx;
swizzle2<1, 1> yy;

swizzle3<0, 0, 1> xxy;
swizzle3<0, 1, 0> xyx;
swizzle3<0, 1, 1> xyy;

swizzle3<1, 0, 0> yxx;
swizzle3<1, 0, 1> yxy;
swizzle3<1, 1, 0> yyx;
swizzle3<1, 1, 1> yyy;

swizzle4<0, 0, 0, 1> xxxy;

swizzle4<0, 0, 1, 0> xxyx;
swizzle4<0, 0, 1, 1> xxyy;

swizzle4<0, 1, 0, 0> xyxx;
swizzle4<0, 1, 0, 1> xyxy;

swizzle4<0, 1, 1, 0> xyyx;
swizzle4<0, 1, 1, 1> xyyy;

swizzle4<1, 0, 0, 0> yxxx;
swizzle4<1, 0, 0, 1> yxxy;

swizzle4<1, 0, 1, 0> yxyx;
swizzle4<1, 0, 1, 1> yxyy;

swizzle4<1, 1, 0, 0> yyxx;
swizzle4<1, 1, 0, 1> yyxy;

swizzle4<1, 1, 1, 0> yyyx;
swizzle4<1, 1, 1, 1> yyyy;

// -------------------------------
// RGBA
// -------------------------------

swizzle1<1> g;

swizzle2<0, 1> rg;
swizzle2<1, 0> gr;
swizzle2<1, 1> gg;

swizzle3<0, 0, 1> rrg;
swizzle3<0, 1, 0> rgr;
swizzle3<0, 1, 1> rgg;

swizzle3<1, 0, 0> grr;
swizzle3<1, 0, 1> grg;
swizzle3<1, 1, 0> ggr;
swizzle3<1, 1, 1> ggg;

swizzle4<0, 0, 0, 1> rrrg;

swizzle4<0, 0, 1, 0> rrgr;
swizzle4<0, 0, 1, 1> rrgg;

swizzle4<0, 1, 0, 0> rgrr;
swizzle4<0, 1, 0, 1> rgrg;

swizzle4<0, 1, 1, 0> rggr;
swizzle4<0, 1, 1, 1> rggg;

swizzle4<1, 0, 0, 0> grrr;
swizzle4<1, 0, 0, 1> grrg;

swizzle4<1, 0, 1, 0> grgr;
swizzle4<1, 0, 1, 1> grgg;

swizzle4<1, 1, 0, 0> ggrr;
swizzle4<1, 1, 0, 1> ggrg;

swizzle4<1, 1, 1, 0> gggr;
swizzle4<1, 1, 1, 1> gggg;