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