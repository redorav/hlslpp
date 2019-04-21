// -------------------------------
// XYZW
// -------------------------------

dswizzle1<1> y;

dswizzle2<0, 1> xy;
dswizzle2<1, 0> yx;
dswizzle2<1, 1> yy;

dswizzle3<0, 0, 1> xxy;
dswizzle3<0, 1, 0> xyx;
dswizzle3<0, 1, 1> xyy;

dswizzle3<1, 0, 0> yxx;
dswizzle3<1, 0, 1> yxy;
dswizzle3<1, 1, 0> yyx;
dswizzle3<1, 1, 1> yyy;

dswizzle4<0, 0, 0, 1> xxxy;

dswizzle4<0, 0, 1, 0> xxyx;
dswizzle4<0, 0, 1, 1> xxyy;

dswizzle4<0, 1, 0, 0> xyxx;
dswizzle4<0, 1, 0, 1> xyxy;

dswizzle4<0, 1, 1, 0> xyyx;
dswizzle4<0, 1, 1, 1> xyyy;

dswizzle4<1, 0, 0, 0> yxxx;
dswizzle4<1, 0, 0, 1> yxxy;

dswizzle4<1, 0, 1, 0> yxyx;
dswizzle4<1, 0, 1, 1> yxyy;

dswizzle4<1, 1, 0, 0> yyxx;
dswizzle4<1, 1, 0, 1> yyxy;

dswizzle4<1, 1, 1, 0> yyyx;
dswizzle4<1, 1, 1, 1> yyyy;

// -------------------------------
// RGBA
// -------------------------------

dswizzle1<1> g;

dswizzle2<0, 1> rg;
dswizzle2<1, 0> gr;
dswizzle2<1, 1> gg;

dswizzle3<0, 0, 1> rrg;
dswizzle3<0, 1, 0> rgr;
dswizzle3<0, 1, 1> rgg;

dswizzle3<1, 0, 0> grr;
dswizzle3<1, 0, 1> grg;
dswizzle3<1, 1, 0> ggr;
dswizzle3<1, 1, 1> ggg;

dswizzle4<0, 0, 0, 1> rrrg;

dswizzle4<0, 0, 1, 0> rrgr;
dswizzle4<0, 0, 1, 1> rrgg;

dswizzle4<0, 1, 0, 0> rgrr;
dswizzle4<0, 1, 0, 1> rgrg;

dswizzle4<0, 1, 1, 0> rggr;
dswizzle4<0, 1, 1, 1> rggg;

dswizzle4<1, 0, 0, 0> grrr;
dswizzle4<1, 0, 0, 1> grrg;

dswizzle4<1, 0, 1, 0> grgr;
dswizzle4<1, 0, 1, 1> grgg;

dswizzle4<1, 1, 0, 0> ggrr;
dswizzle4<1, 1, 0, 1> ggrg;

dswizzle4<1, 1, 1, 0> gggr;
dswizzle4<1, 1, 1, 1> gggg;