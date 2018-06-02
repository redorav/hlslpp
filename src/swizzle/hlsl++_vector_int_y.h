// -------------------------------
// XYZW
// -------------------------------

icomponent1<1> y;

icomponent2<0, 1> xy;
icomponent2<1, 0> yx;
icomponent2<1, 1> yy;

icomponent3<0, 0, 1> xxy;
icomponent3<0, 1, 0> xyx;
icomponent3<0, 1, 1> xyy;

icomponent3<1, 0, 0> yxx;
icomponent3<1, 0, 1> yxy;
icomponent3<1, 1, 0> yyx;
icomponent3<1, 1, 1> yyy;

icomponent4<0, 0, 0, 1> xxxy;

icomponent4<0, 0, 1, 0> xxyx;
icomponent4<0, 0, 1, 1> xxyy;

icomponent4<0, 1, 0, 0> xyxx;
icomponent4<0, 1, 0, 1> xyxy;

icomponent4<0, 1, 1, 0> xyyx;
icomponent4<0, 1, 1, 1> xyyy;

icomponent4<1, 0, 0, 0> yxxx;
icomponent4<1, 0, 0, 1> yxxy;

icomponent4<1, 0, 1, 0> yxyx;
icomponent4<1, 0, 1, 1> yxyy;

icomponent4<1, 1, 0, 0> yyxx;
icomponent4<1, 1, 0, 1> yyxy;

icomponent4<1, 1, 1, 0> yyyx;
icomponent4<1, 1, 1, 1> yyyy;