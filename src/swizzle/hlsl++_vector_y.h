// -------------------------------
// XYZW
// -------------------------------

component1<1> y;

component2<0, 1> xy;
component2<1, 0> yx;
component2<1, 1> yy;

component3<0, 0, 1> xxy;
component3<0, 1, 0> xyx;
component3<0, 1, 1> xyy;

component3<1, 0, 0> yxx;
component3<1, 0, 1> yxy;
component3<1, 1, 0> yyx;
component3<1, 1, 1> yyy;

component4<0, 0, 0, 1> xxxy;

component4<0, 0, 1, 0> xxyx;
component4<0, 0, 1, 1> xxyy;

component4<0, 1, 0, 0> xyxx;
component4<0, 1, 0, 1> xyxy;

component4<0, 1, 1, 0> xyyx;
component4<0, 1, 1, 1> xyyy;

component4<1, 0, 0, 0> yxxx;
component4<1, 0, 0, 1> yxxy;

component4<1, 0, 1, 0> yxyx;
component4<1, 0, 1, 1> yxyy;

component4<1, 1, 0, 0> yyxx;
component4<1, 1, 0, 1> yyxy;

component4<1, 1, 1, 0> yyyx;
component4<1, 1, 1, 1> yyyy;

// -------------------------------
// RGBA
// -------------------------------

component1<1> g;

component2<0, 1> rg;
component2<1, 0> gr;
component2<1, 1> gg;

component3<0, 0, 1> rrg;
component3<0, 1, 0> rgr;
component3<0, 1, 1> rgg;

component3<1, 0, 0> grr;
component3<1, 0, 1> grg;
component3<1, 1, 0> ggr;
component3<1, 1, 1> ggg;

component4<0, 0, 0, 1> rrrg;

component4<0, 0, 1, 0> rrgr;
component4<0, 0, 1, 1> rrgg;

component4<0, 1, 0, 0> rgrr;
component4<0, 1, 0, 1> rgrg;

component4<0, 1, 1, 0> rggr;
component4<0, 1, 1, 1> rggg;

component4<1, 0, 0, 0> grrr;
component4<1, 0, 0, 1> grrg;

component4<1, 0, 1, 0> grgr;
component4<1, 0, 1, 1> grgg;

component4<1, 1, 0, 0> ggrr;
component4<1, 1, 0, 1> ggrg;

component4<1, 1, 1, 0> gggr;
component4<1, 1, 1, 1> gggg;