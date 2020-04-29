// -------------------------------
// XYZW
// -------------------------------

uswizzle1<1> y;

uswizzle2<0, 1> xy;
uswizzle2<1, 0> yx;
uswizzle2<1, 1> yy;

uswizzle3<0, 0, 1> xxy;
uswizzle3<0, 1, 0> xyx;
uswizzle3<0, 1, 1> xyy;

uswizzle3<1, 0, 0> yxx;
uswizzle3<1, 0, 1> yxy;
uswizzle3<1, 1, 0> yyx;
uswizzle3<1, 1, 1> yyy;

uswizzle4<0, 0, 0, 1> xxxy;

uswizzle4<0, 0, 1, 0> xxyx;
uswizzle4<0, 0, 1, 1> xxyy;

uswizzle4<0, 1, 0, 0> xyxx;
uswizzle4<0, 1, 0, 1> xyxy;

uswizzle4<0, 1, 1, 0> xyyx;
uswizzle4<0, 1, 1, 1> xyyy;

uswizzle4<1, 0, 0, 0> yxxx;
uswizzle4<1, 0, 0, 1> yxxy;

uswizzle4<1, 0, 1, 0> yxyx;
uswizzle4<1, 0, 1, 1> yxyy;

uswizzle4<1, 1, 0, 0> yyxx;
uswizzle4<1, 1, 0, 1> yyxy;

uswizzle4<1, 1, 1, 0> yyyx;
uswizzle4<1, 1, 1, 1> yyyy;

// -------------------------------
// RGBA
// -------------------------------

uswizzle1<1> g;

uswizzle2<0, 1> rg;
uswizzle2<1, 0> gr;
uswizzle2<1, 1> gg;

uswizzle3<0, 0, 1> rrg;
uswizzle3<0, 1, 0> rgr;
uswizzle3<0, 1, 1> rgg;

uswizzle3<1, 0, 0> grr;
uswizzle3<1, 0, 1> grg;
uswizzle3<1, 1, 0> ggr;
uswizzle3<1, 1, 1> ggg;

uswizzle4<0, 0, 0, 1> rrrg;

uswizzle4<0, 0, 1, 0> rrgr;
uswizzle4<0, 0, 1, 1> rrgg;

uswizzle4<0, 1, 0, 0> rgrr;
uswizzle4<0, 1, 0, 1> rgrg;

uswizzle4<0, 1, 1, 0> rggr;
uswizzle4<0, 1, 1, 1> rggg;

uswizzle4<1, 0, 0, 0> grrr;
uswizzle4<1, 0, 0, 1> grrg;

uswizzle4<1, 0, 1, 0> grgr;
uswizzle4<1, 0, 1, 1> grgg;

uswizzle4<1, 1, 0, 0> ggrr;
uswizzle4<1, 1, 0, 1> ggrg;

uswizzle4<1, 1, 1, 0> gggr;
uswizzle4<1, 1, 1, 1> gggg;