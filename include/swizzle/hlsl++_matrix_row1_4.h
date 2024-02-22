#if HLSLPP_ENABLE_MATRIX_SWIZZLE_M00

// -------------------------------
// _mNM
// -------------------------------

hlslpp_swizzle_start swizzle1<3> _m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle2<0, 3> _m10_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<1, 3> _m11_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<2, 3> _m12_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 0> _m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 1> _m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 2> _m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 3> _m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 0, 3> _m10_m10_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 1, 3> _m10_m11_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 2, 3> _m10_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 3, 0> _m10_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 1> _m10_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 2> _m10_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 3> _m10_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 0, 3> _m11_m10_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 1, 3> _m11_m11_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 2, 3> _m11_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 3, 0> _m11_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 1> _m11_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 2> _m11_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 3> _m11_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 0, 3> _m12_m10_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 1, 3> _m12_m11_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 2, 3> _m12_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 3, 0> _m12_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 1> _m12_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 2> _m12_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 3> _m12_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 0, 0> _m13_m10_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 1> _m13_m10_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 2> _m13_m10_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 3> _m13_m10_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 1, 0> _m13_m11_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 1> _m13_m11_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 2> _m13_m11_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 3> _m13_m11_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 2, 0> _m13_m12_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 1> _m13_m12_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 2> _m13_m12_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 3> _m13_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 3, 0> _m13_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 1> _m13_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 2> _m13_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 3> _m13_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 0, 3> _m10_m10_m10_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 1, 3> _m10_m10_m11_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 2, 3> _m10_m10_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 3, 0> _m10_m10_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 1> _m10_m10_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 2> _m10_m10_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 3> _m10_m10_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 0, 3> _m10_m11_m10_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 1, 3> _m10_m11_m11_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 2, 3> _m10_m11_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 3, 0> _m10_m11_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 1> _m10_m11_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 2> _m10_m11_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 3> _m10_m11_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 0, 3> _m10_m12_m10_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 1, 3> _m10_m12_m11_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 2, 3> _m10_m12_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 3, 0> _m10_m12_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 1> _m10_m12_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 2> _m10_m12_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 3> _m10_m12_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 0, 0> _m10_m13_m10_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 1> _m10_m13_m10_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 2> _m10_m13_m10_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 3> _m10_m13_m10_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 1, 0> _m10_m13_m11_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 1> _m10_m13_m11_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 2> _m10_m13_m11_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 3> _m10_m13_m11_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 2, 0> _m10_m13_m12_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 1> _m10_m13_m12_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 2> _m10_m13_m12_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 3> _m10_m13_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 3, 0> _m10_m13_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 1> _m10_m13_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 2> _m10_m13_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 3> _m10_m13_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 0, 3> _m11_m10_m10_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 1, 3> _m11_m10_m11_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 2, 3> _m11_m10_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 3, 0> _m11_m10_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 1> _m11_m10_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 2> _m11_m10_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 3> _m11_m10_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 0, 3> _m11_m11_m10_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 1, 3> _m11_m11_m11_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 2, 3> _m11_m11_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 3, 0> _m11_m11_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 1> _m11_m11_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 2> _m11_m11_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 3> _m11_m11_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 0, 3> _m11_m12_m10_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 1, 3> _m11_m12_m11_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 2, 3> _m11_m12_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 3, 0> _m11_m12_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 1> _m11_m12_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 2> _m11_m12_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 3> _m11_m12_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 0, 0> _m11_m13_m10_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 1> _m11_m13_m10_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 2> _m11_m13_m10_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 3> _m11_m13_m10_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 1, 0> _m11_m13_m11_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 1> _m11_m13_m11_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 2> _m11_m13_m11_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 3> _m11_m13_m11_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 2, 0> _m11_m13_m12_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 1> _m11_m13_m12_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 2> _m11_m13_m12_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 3> _m11_m13_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 3, 0> _m11_m13_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 1> _m11_m13_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 2> _m11_m13_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 3> _m11_m13_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 0, 3> _m12_m10_m10_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 1, 3> _m12_m10_m11_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 2, 3> _m12_m10_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 3, 0> _m12_m10_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 1> _m12_m10_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 2> _m12_m10_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 3> _m12_m10_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 0, 3> _m12_m11_m10_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 1, 3> _m12_m11_m11_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 2, 3> _m12_m11_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 3, 0> _m12_m11_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 1> _m12_m11_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 2> _m12_m11_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 3> _m12_m11_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 0, 3> _m12_m12_m10_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 1, 3> _m12_m12_m11_m13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 2, 3> _m12_m12_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 3, 0> _m12_m12_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 1> _m12_m12_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 2> _m12_m12_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 3> _m12_m12_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 0, 0> _m12_m13_m10_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 1> _m12_m13_m10_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 2> _m12_m13_m10_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 3> _m12_m13_m10_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 1, 0> _m12_m13_m11_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 1> _m12_m13_m11_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 2> _m12_m13_m11_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 3> _m12_m13_m11_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 2, 0> _m12_m13_m12_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 1> _m12_m13_m12_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 2> _m12_m13_m12_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 3> _m12_m13_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 3, 0> _m12_m13_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 1> _m12_m13_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 2> _m12_m13_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 3> _m12_m13_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 0, 0> _m13_m10_m10_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 1> _m13_m10_m10_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 2> _m13_m10_m10_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 3> _m13_m10_m10_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 1, 0> _m13_m10_m11_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 1> _m13_m10_m11_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 2> _m13_m10_m11_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 3> _m13_m10_m11_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 2, 0> _m13_m10_m12_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 1> _m13_m10_m12_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 2> _m13_m10_m12_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 3> _m13_m10_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 3, 0> _m13_m10_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 1> _m13_m10_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 2> _m13_m10_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 3> _m13_m10_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 0, 0> _m13_m11_m10_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 1> _m13_m11_m10_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 2> _m13_m11_m10_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 3> _m13_m11_m10_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 1, 0> _m13_m11_m11_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 1> _m13_m11_m11_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 2> _m13_m11_m11_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 3> _m13_m11_m11_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 2, 0> _m13_m11_m12_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 1> _m13_m11_m12_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 2> _m13_m11_m12_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 3> _m13_m11_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 3, 0> _m13_m11_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 1> _m13_m11_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 2> _m13_m11_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 3> _m13_m11_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 0, 0> _m13_m12_m10_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 1> _m13_m12_m10_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 2> _m13_m12_m10_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 3> _m13_m12_m10_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 1, 0> _m13_m12_m11_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 1> _m13_m12_m11_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 2> _m13_m12_m11_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 3> _m13_m12_m11_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 2, 0> _m13_m12_m12_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 1> _m13_m12_m12_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 2> _m13_m12_m12_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 3> _m13_m12_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 3, 0> _m13_m12_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 1> _m13_m12_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 2> _m13_m12_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 3> _m13_m12_m13_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 0, 0> _m13_m13_m10_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 1> _m13_m13_m10_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 2> _m13_m13_m10_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 3> _m13_m13_m10_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 1, 0> _m13_m13_m11_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 1> _m13_m13_m11_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 2> _m13_m13_m11_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 3> _m13_m13_m11_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 2, 0> _m13_m13_m12_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 1> _m13_m13_m12_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 2> _m13_m13_m12_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 3> _m13_m13_m12_m13; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 3, 0> _m13_m13_m13_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 1> _m13_m13_m13_m11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 2> _m13_m13_m13_m12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 3> _m13_m13_m13_m13; hlslpp_swizzle_end

#endif

#if HLSLPP_ENABLE_MATRIX_SWIZZLE_11

// -------------------------------
// _NM
// -------------------------------

hlslpp_swizzle_start swizzle1<3> _24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle2<0, 3> _21_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<1, 3> _22_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<2, 3> _23_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 0> _24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 1> _24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 2> _24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 3> _24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 0, 3> _21_21_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 1, 3> _21_22_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 2, 3> _21_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 3, 0> _21_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 1> _21_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 2> _21_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 3> _21_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 0, 3> _22_21_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 1, 3> _22_22_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 2, 3> _22_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 3, 0> _22_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 1> _22_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 2> _22_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 3> _22_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 0, 3> _23_21_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 1, 3> _23_22_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 2, 3> _23_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 3, 0> _23_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 1> _23_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 2> _23_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 3> _23_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 0, 0> _24_21_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 1> _24_21_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 2> _24_21_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 3> _24_21_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 1, 0> _24_22_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 1> _24_22_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 2> _24_22_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 3> _24_22_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 2, 0> _24_23_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 1> _24_23_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 2> _24_23_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 3> _24_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 3, 0> _24_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 1> _24_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 2> _24_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 3> _24_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 0, 3> _21_21_21_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 1, 3> _21_21_22_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 2, 3> _21_21_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 3, 0> _21_21_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 1> _21_21_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 2> _21_21_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 3> _21_21_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 0, 3> _21_22_21_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 1, 3> _21_22_22_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 2, 3> _21_22_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 3, 0> _21_22_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 1> _21_22_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 2> _21_22_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 3> _21_22_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 0, 3> _21_23_21_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 1, 3> _21_23_22_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 2, 3> _21_23_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 3, 0> _21_23_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 1> _21_23_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 2> _21_23_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 3> _21_23_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 0, 0> _21_24_21_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 1> _21_24_21_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 2> _21_24_21_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 3> _21_24_21_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 1, 0> _21_24_22_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 1> _21_24_22_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 2> _21_24_22_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 3> _21_24_22_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 2, 0> _21_24_23_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 1> _21_24_23_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 2> _21_24_23_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 3> _21_24_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 3, 0> _21_24_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 1> _21_24_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 2> _21_24_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 3> _21_24_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 0, 3> _22_21_21_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 1, 3> _22_21_22_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 2, 3> _22_21_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 3, 0> _22_21_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 1> _22_21_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 2> _22_21_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 3> _22_21_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 0, 3> _22_22_21_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 1, 3> _22_22_22_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 2, 3> _22_22_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 3, 0> _22_22_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 1> _22_22_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 2> _22_22_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 3> _22_22_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 0, 3> _22_23_21_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 1, 3> _22_23_22_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 2, 3> _22_23_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 3, 0> _22_23_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 1> _22_23_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 2> _22_23_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 3> _22_23_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 0, 0> _22_24_21_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 1> _22_24_21_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 2> _22_24_21_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 3> _22_24_21_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 1, 0> _22_24_22_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 1> _22_24_22_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 2> _22_24_22_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 3> _22_24_22_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 2, 0> _22_24_23_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 1> _22_24_23_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 2> _22_24_23_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 3> _22_24_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 3, 0> _22_24_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 1> _22_24_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 2> _22_24_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 3> _22_24_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 0, 3> _23_21_21_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 1, 3> _23_21_22_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 2, 3> _23_21_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 3, 0> _23_21_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 1> _23_21_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 2> _23_21_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 3> _23_21_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 0, 3> _23_22_21_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 1, 3> _23_22_22_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 2, 3> _23_22_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 3, 0> _23_22_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 1> _23_22_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 2> _23_22_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 3> _23_22_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 0, 3> _23_23_21_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 1, 3> _23_23_22_24; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 2, 3> _23_23_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 3, 0> _23_23_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 1> _23_23_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 2> _23_23_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 3> _23_23_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 0, 0> _23_24_21_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 1> _23_24_21_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 2> _23_24_21_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 3> _23_24_21_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 1, 0> _23_24_22_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 1> _23_24_22_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 2> _23_24_22_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 3> _23_24_22_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 2, 0> _23_24_23_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 1> _23_24_23_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 2> _23_24_23_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 3> _23_24_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 3, 0> _23_24_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 1> _23_24_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 2> _23_24_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 3> _23_24_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 0, 0> _24_21_21_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 1> _24_21_21_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 2> _24_21_21_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 3> _24_21_21_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 1, 0> _24_21_22_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 1> _24_21_22_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 2> _24_21_22_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 3> _24_21_22_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 2, 0> _24_21_23_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 1> _24_21_23_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 2> _24_21_23_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 3> _24_21_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 3, 0> _24_21_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 1> _24_21_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 2> _24_21_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 3> _24_21_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 0, 0> _24_22_21_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 1> _24_22_21_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 2> _24_22_21_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 3> _24_22_21_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 1, 0> _24_22_22_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 1> _24_22_22_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 2> _24_22_22_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 3> _24_22_22_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 2, 0> _24_22_23_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 1> _24_22_23_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 2> _24_22_23_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 3> _24_22_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 3, 0> _24_22_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 1> _24_22_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 2> _24_22_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 3> _24_22_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 0, 0> _24_23_21_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 1> _24_23_21_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 2> _24_23_21_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 3> _24_23_21_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 1, 0> _24_23_22_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 1> _24_23_22_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 2> _24_23_22_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 3> _24_23_22_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 2, 0> _24_23_23_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 1> _24_23_23_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 2> _24_23_23_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 3> _24_23_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 3, 0> _24_23_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 1> _24_23_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 2> _24_23_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 3> _24_23_24_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 0, 0> _24_24_21_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 1> _24_24_21_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 2> _24_24_21_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 3> _24_24_21_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 1, 0> _24_24_22_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 1> _24_24_22_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 2> _24_24_22_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 3> _24_24_22_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 2, 0> _24_24_23_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 1> _24_24_23_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 2> _24_24_23_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 3> _24_24_23_24; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 3, 0> _24_24_24_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 1> _24_24_24_22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 2> _24_24_24_23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 3> _24_24_24_24; hlslpp_swizzle_end

#endif