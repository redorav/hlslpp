// -------------------------------
// _mNM
// -------------------------------

component1<1> _m01;

component2<0, 1> _m00_m01;
component2<1, 0> _m01_m00;
component2<1, 1> _m01_m01;

component3<0, 0, 1> _m00_m00_m01;
component3<0, 1, 0> _m00_m01_m00;
component3<0, 1, 1> _m00_m01_m01;

component3<1, 0, 0> _m01_m00_m00;
component3<1, 0, 1> _m01_m00_m01;
component3<1, 1, 0> _m01_m01_m00;
component3<1, 1, 1> _m01_m01_m01;

component4<0, 0, 0, 1> _m00_m00_m00_m01;

component4<0, 0, 1, 0> _m00_m00_m01_m00;
component4<0, 0, 1, 1> _m00_m00_m01_m01;

component4<0, 1, 0, 0> _m00_m01_m00_m00;
component4<0, 1, 0, 1> _m00_m01_m00_m01;

component4<0, 1, 1, 0> _m00_m01_m01_m00;
component4<0, 1, 1, 1> _m00_m01_m01_m01;

component4<1, 0, 0, 0> _m01_m00_m00_m00;
component4<1, 0, 0, 1> _m01_m00_m00_m01;

component4<1, 0, 1, 0> _m01_m00_m01_m00;
component4<1, 0, 1, 1> _m01_m00_m01_m01;

component4<1, 1, 0, 0> _m01_m01_m00_m00;
component4<1, 1, 0, 1> _m01_m01_m00_m01;

component4<1, 1, 1, 0> _m01_m01_m01_m00;
component4<1, 1, 1, 1> _m01_m01_m01_m01;

// -------------------------------
// _NM
// -------------------------------

component1<1> _12;

component2<0, 1> _11_12;
component2<1, 0> _12_11;
component2<1, 1> _12_12;

component3<0, 0, 1> _11_11_12;
component3<0, 1, 0> _11_12_11;
component3<0, 1, 1> _11_12_12;

component3<1, 0, 0> _12_11_11;
component3<1, 0, 1> _12_11_12;
component3<1, 1, 0> _12_12_11;
component3<1, 1, 1> _12_12_12;

component4<0, 0, 0, 1> _11_11_11_12;

component4<0, 0, 1, 0> _11_11_12_11;
component4<0, 0, 1, 1> _11_11_12_12;

component4<0, 1, 0, 0> _11_12_11_11;
component4<0, 1, 0, 1> _11_12_11_12;

component4<0, 1, 1, 0> _11_12_12_11;
component4<0, 1, 1, 1> _11_12_12_12;

component4<1, 0, 0, 0> _12_11_11_11;
component4<1, 0, 0, 1> _12_11_11_12;

component4<1, 0, 1, 0> _12_11_12_11;
component4<1, 0, 1, 1> _12_11_12_12;

component4<1, 1, 0, 0> _12_12_11_11;
component4<1, 1, 0, 1> _12_12_11_12;

component4<1, 1, 1, 0> _12_12_12_11;
component4<1, 1, 1, 1> _12_12_12_12;