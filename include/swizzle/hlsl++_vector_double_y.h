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