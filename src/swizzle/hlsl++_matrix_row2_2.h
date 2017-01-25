// -------------------------------
// _mNM
// -------------------------------

component1<1> _m21;

component2<0, 1> _m20_m21;
component2<1, 0> _m21_m20;
component2<1, 1> _m21_m21;

component3<0, 0, 1> _m20_m20_m21;
component3<0, 1, 0> _m20_m21_m20;
component3<0, 1, 1> _m20_m21_m21;

component3<1, 0, 0> _m21_m20_m20;
component3<1, 0, 1> _m21_m20_m21;
component3<1, 1, 0> _m21_m21_m20;
component3<1, 1, 1> _m21_m21_m21;

component4<0, 0, 0, 1> _m20_m20_m20_m21;

component4<0, 0, 1, 0> _m20_m20_m21_m20;
component4<0, 0, 1, 1> _m20_m20_m21_m21;

component4<0, 1, 0, 0> _m20_m21_m20_m20;
component4<0, 1, 0, 1> _m20_m21_m20_m21;

component4<0, 1, 1, 0> _m20_m21_m21_m20;
component4<0, 1, 1, 1> _m20_m21_m21_m21;

component4<1, 0, 0, 0> _m21_m20_m20_m20;
component4<1, 0, 0, 1> _m21_m20_m20_m21;

component4<1, 0, 1, 0> _m21_m20_m21_m20;
component4<1, 0, 1, 1> _m21_m20_m21_m21;

component4<1, 1, 0, 0> _m21_m21_m20_m20;
component4<1, 1, 0, 1> _m21_m21_m20_m21;

component4<1, 1, 1, 0> _m21_m21_m21_m20;
component4<1, 1, 1, 1> _m21_m21_m21_m21;

// -------------------------------
// _NM
// -------------------------------

component1<1> _32;

component2<0, 1> _31_32;
component2<1, 0> _32_31;
component2<1, 1> _32_32;

component3<0, 0, 1> _31_31_32;
component3<0, 1, 0> _31_32_31;
component3<0, 1, 1> _31_32_32;

component3<1, 0, 0> _32_31_31;
component3<1, 0, 1> _32_31_32;
component3<1, 1, 0> _32_32_31;
component3<1, 1, 1> _32_32_32;

component4<0, 0, 0, 1> _31_31_31_32;

component4<0, 0, 1, 0> _31_31_32_31;
component4<0, 0, 1, 1> _31_31_32_32;

component4<0, 1, 0, 0> _31_32_31_31;
component4<0, 1, 0, 1> _31_32_31_32;

component4<0, 1, 1, 0> _31_32_32_31;
component4<0, 1, 1, 1> _31_32_32_32;

component4<1, 0, 0, 0> _32_31_31_31;
component4<1, 0, 0, 1> _32_31_31_32;

component4<1, 0, 1, 0> _32_31_32_31;
component4<1, 0, 1, 1> _32_31_32_32;

component4<1, 1, 0, 0> _32_32_31_31;
component4<1, 1, 0, 1> _32_32_31_32;

component4<1, 1, 1, 0> _32_32_32_31;
component4<1, 1, 1, 1> _32_32_32_32;