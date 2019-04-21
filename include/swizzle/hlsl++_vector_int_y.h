// -------------------------------
// XYZW
// -------------------------------

iswizzle1<1> y;

iswizzle2<0, 1> xy;
iswizzle2<1, 0> yx;
iswizzle2<1, 1> yy;

iswizzle3<0, 0, 1> xxy;
iswizzle3<0, 1, 0> xyx;
iswizzle3<0, 1, 1> xyy;

iswizzle3<1, 0, 0> yxx;
iswizzle3<1, 0, 1> yxy;
iswizzle3<1, 1, 0> yyx;
iswizzle3<1, 1, 1> yyy;

iswizzle4<0, 0, 0, 1> xxxy;

iswizzle4<0, 0, 1, 0> xxyx;
iswizzle4<0, 0, 1, 1> xxyy;

iswizzle4<0, 1, 0, 0> xyxx;
iswizzle4<0, 1, 0, 1> xyxy;

iswizzle4<0, 1, 1, 0> xyyx;
iswizzle4<0, 1, 1, 1> xyyy;

iswizzle4<1, 0, 0, 0> yxxx;
iswizzle4<1, 0, 0, 1> yxxy;

iswizzle4<1, 0, 1, 0> yxyx;
iswizzle4<1, 0, 1, 1> yxyy;

iswizzle4<1, 1, 0, 0> yyxx;
iswizzle4<1, 1, 0, 1> yyxy;

iswizzle4<1, 1, 1, 0> yyyx;
iswizzle4<1, 1, 1, 1> yyyy;

// -------------------------------
// RGBA
// -------------------------------

iswizzle1<1> g;

iswizzle2<0, 1> rg;
iswizzle2<1, 0> gr;
iswizzle2<1, 1> gg;

iswizzle3<0, 0, 1> rrg;
iswizzle3<0, 1, 0> rgr;
iswizzle3<0, 1, 1> rgg;

iswizzle3<1, 0, 0> grr;
iswizzle3<1, 0, 1> grg;
iswizzle3<1, 1, 0> ggr;
iswizzle3<1, 1, 1> ggg;

iswizzle4<0, 0, 0, 1> rrrg;

iswizzle4<0, 0, 1, 0> rrgr;
iswizzle4<0, 0, 1, 1> rrgg;

iswizzle4<0, 1, 0, 0> rgrr;
iswizzle4<0, 1, 0, 1> rgrg;

iswizzle4<0, 1, 1, 0> rggr;
iswizzle4<0, 1, 1, 1> rggg;

iswizzle4<1, 0, 0, 0> grrr;
iswizzle4<1, 0, 0, 1> grrg;

iswizzle4<1, 0, 1, 0> grgr;
iswizzle4<1, 0, 1, 1> grgg;

iswizzle4<1, 1, 0, 0> ggrr;
iswizzle4<1, 1, 0, 1> ggrg;

iswizzle4<1, 1, 1, 0> gggr;
iswizzle4<1, 1, 1, 1> gggg;