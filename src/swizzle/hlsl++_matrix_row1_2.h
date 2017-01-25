// -------------------------------
// _mNM
// -------------------------------

component1<1> _m11;

component2<0, 1> _m10_m11;
component2<1, 0> _m11_m10;
component2<1, 1> _m11_m11;

component3<0, 0, 1> _m10_m10_m11;
component3<0, 1, 0> _m10_m11_m10;
component3<0, 1, 1> _m10_m11_m11;

component3<1, 0, 0> _m11_m10_m10;
component3<1, 0, 1> _m11_m10_m11;
component3<1, 1, 0> _m11_m11_m10;
component3<1, 1, 1> _m11_m11_m11;

component4<0, 0, 0, 1> _m10_m10_m10_m11;

component4<0, 0, 1, 0> _m10_m10_m11_m10;
component4<0, 0, 1, 1> _m10_m10_m11_m11;

component4<0, 1, 0, 0> _m10_m11_m10_m10;
component4<0, 1, 0, 1> _m10_m11_m10_m11;

component4<0, 1, 1, 0> _m10_m11_m11_m10;
component4<0, 1, 1, 1> _m10_m11_m11_m11;

component4<1, 0, 0, 0> _m11_m10_m10_m10;
component4<1, 0, 0, 1> _m11_m10_m10_m11;

component4<1, 0, 1, 0> _m11_m10_m11_m10;
component4<1, 0, 1, 1> _m11_m10_m11_m11;

component4<1, 1, 0, 0> _m11_m11_m10_m10;
component4<1, 1, 0, 1> _m11_m11_m10_m11;

component4<1, 1, 1, 0> _m11_m11_m11_m10;
component4<1, 1, 1, 1> _m11_m11_m11_m11;

// -------------------------------
// _NM
// -------------------------------

component1<1> _22;

component2<0, 1> _21_22;
component2<1, 0> _22_21;
component2<1, 1> _22_22;

component3<0, 0, 1> _21_21_22;
component3<0, 1, 0> _21_22_21;
component3<0, 1, 1> _21_22_22;

component3<1, 0, 0> _22_21_21;
component3<1, 0, 1> _22_21_22;
component3<1, 1, 0> _22_22_21;
component3<1, 1, 1> _22_22_22;

component4<0, 0, 0, 1> _21_21_21_22;

component4<0, 0, 1, 0> _21_21_22_21;
component4<0, 0, 1, 1> _21_21_22_22;

component4<0, 1, 0, 0> _21_22_21_21;
component4<0, 1, 0, 1> _21_22_21_22;

component4<0, 1, 1, 0> _21_22_22_21;
component4<0, 1, 1, 1> _21_22_22_22;

component4<1, 0, 0, 0> _22_21_21_21;
component4<1, 0, 0, 1> _22_21_21_22;

component4<1, 0, 1, 0> _22_21_22_21;
component4<1, 0, 1, 1> _22_21_22_22;

component4<1, 1, 0, 0> _22_22_21_21;
component4<1, 1, 0, 1> _22_22_21_22;

component4<1, 1, 1, 0> _22_22_22_21;
component4<1, 1, 1, 1> _22_22_22_22;