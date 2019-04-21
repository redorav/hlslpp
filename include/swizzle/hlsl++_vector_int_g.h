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