#if HLSLPP_ENABLE_MATRIX_SWIZZLE_M00

// -------------------------------
// _mNM
// -------------------------------

hlslpp_swizzle_start swizzle1<3> _m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle2<0, 3> _m20_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<1, 3> _m21_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<2, 3> _m22_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 0> _m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 1> _m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 2> _m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 3> _m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 0, 3> _m20_m20_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 1, 3> _m20_m21_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 2, 3> _m20_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 3, 0> _m20_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 1> _m20_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 2> _m20_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 3> _m20_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 0, 3> _m21_m20_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 1, 3> _m21_m21_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 2, 3> _m21_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 3, 0> _m21_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 1> _m21_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 2> _m21_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 3> _m21_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 0, 3> _m22_m20_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 1, 3> _m22_m21_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 2, 3> _m22_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 3, 0> _m22_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 1> _m22_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 2> _m22_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 3> _m22_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 0, 0> _m23_m20_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 1> _m23_m20_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 2> _m23_m20_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 3> _m23_m20_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 1, 0> _m23_m21_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 1> _m23_m21_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 2> _m23_m21_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 3> _m23_m21_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 2, 0> _m23_m22_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 1> _m23_m22_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 2> _m23_m22_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 3> _m23_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 3, 0> _m23_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 1> _m23_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 2> _m23_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 3> _m23_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 0, 3> _m20_m20_m20_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 1, 3> _m20_m20_m21_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 2, 3> _m20_m20_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 3, 0> _m20_m20_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 1> _m20_m20_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 2> _m20_m20_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 3> _m20_m20_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 0, 3> _m20_m21_m20_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 1, 3> _m20_m21_m21_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 2, 3> _m20_m21_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 3, 0> _m20_m21_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 1> _m20_m21_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 2> _m20_m21_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 3> _m20_m21_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 0, 3> _m20_m22_m20_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 1, 3> _m20_m22_m21_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 2, 3> _m20_m22_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 3, 0> _m20_m22_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 1> _m20_m22_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 2> _m20_m22_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 3> _m20_m22_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 0, 0> _m20_m23_m20_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 1> _m20_m23_m20_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 2> _m20_m23_m20_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 3> _m20_m23_m20_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 1, 0> _m20_m23_m21_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 1> _m20_m23_m21_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 2> _m20_m23_m21_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 3> _m20_m23_m21_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 2, 0> _m20_m23_m22_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 1> _m20_m23_m22_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 2> _m20_m23_m22_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 3> _m20_m23_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 3, 0> _m20_m23_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 1> _m20_m23_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 2> _m20_m23_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 3> _m20_m23_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 0, 3> _m21_m20_m20_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 1, 3> _m21_m20_m21_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 2, 3> _m21_m20_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 3, 0> _m21_m20_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 1> _m21_m20_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 2> _m21_m20_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 3> _m21_m20_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 0, 3> _m21_m21_m20_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 1, 3> _m21_m21_m21_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 2, 3> _m21_m21_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 3, 0> _m21_m21_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 1> _m21_m21_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 2> _m21_m21_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 3> _m21_m21_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 0, 3> _m21_m22_m20_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 1, 3> _m21_m22_m21_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 2, 3> _m21_m22_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 3, 0> _m21_m22_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 1> _m21_m22_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 2> _m21_m22_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 3> _m21_m22_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 0, 0> _m21_m23_m20_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 1> _m21_m23_m20_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 2> _m21_m23_m20_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 3> _m21_m23_m20_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 1, 0> _m21_m23_m21_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 1> _m21_m23_m21_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 2> _m21_m23_m21_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 3> _m21_m23_m21_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 2, 0> _m21_m23_m22_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 1> _m21_m23_m22_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 2> _m21_m23_m22_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 3> _m21_m23_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 3, 0> _m21_m23_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 1> _m21_m23_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 2> _m21_m23_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 3> _m21_m23_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 0, 3> _m22_m20_m20_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 1, 3> _m22_m20_m21_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 2, 3> _m22_m20_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 3, 0> _m22_m20_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 1> _m22_m20_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 2> _m22_m20_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 3> _m22_m20_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 0, 3> _m22_m21_m20_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 1, 3> _m22_m21_m21_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 2, 3> _m22_m21_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 3, 0> _m22_m21_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 1> _m22_m21_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 2> _m22_m21_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 3> _m22_m21_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 0, 3> _m22_m22_m20_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 1, 3> _m22_m22_m21_m23; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 2, 3> _m22_m22_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 3, 0> _m22_m22_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 1> _m22_m22_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 2> _m22_m22_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 3> _m22_m22_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 0, 0> _m22_m23_m20_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 1> _m22_m23_m20_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 2> _m22_m23_m20_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 3> _m22_m23_m20_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 1, 0> _m22_m23_m21_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 1> _m22_m23_m21_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 2> _m22_m23_m21_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 3> _m22_m23_m21_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 2, 0> _m22_m23_m22_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 1> _m22_m23_m22_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 2> _m22_m23_m22_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 3> _m22_m23_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 3, 0> _m22_m23_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 1> _m22_m23_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 2> _m22_m23_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 3> _m22_m23_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 0, 0> _m23_m20_m20_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 1> _m23_m20_m20_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 2> _m23_m20_m20_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 3> _m23_m20_m20_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 1, 0> _m23_m20_m21_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 1> _m23_m20_m21_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 2> _m23_m20_m21_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 3> _m23_m20_m21_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 2, 0> _m23_m20_m22_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 1> _m23_m20_m22_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 2> _m23_m20_m22_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 3> _m23_m20_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 3, 0> _m23_m20_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 1> _m23_m20_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 2> _m23_m20_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 3> _m23_m20_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 0, 0> _m23_m21_m20_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 1> _m23_m21_m20_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 2> _m23_m21_m20_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 3> _m23_m21_m20_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 1, 0> _m23_m21_m21_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 1> _m23_m21_m21_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 2> _m23_m21_m21_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 3> _m23_m21_m21_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 2, 0> _m23_m21_m22_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 1> _m23_m21_m22_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 2> _m23_m21_m22_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 3> _m23_m21_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 3, 0> _m23_m21_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 1> _m23_m21_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 2> _m23_m21_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 3> _m23_m21_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 0, 0> _m23_m22_m20_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 1> _m23_m22_m20_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 2> _m23_m22_m20_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 3> _m23_m22_m20_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 1, 0> _m23_m22_m21_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 1> _m23_m22_m21_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 2> _m23_m22_m21_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 3> _m23_m22_m21_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 2, 0> _m23_m22_m22_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 1> _m23_m22_m22_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 2> _m23_m22_m22_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 3> _m23_m22_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 3, 0> _m23_m22_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 1> _m23_m22_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 2> _m23_m22_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 3> _m23_m22_m23_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 0, 0> _m23_m23_m20_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 1> _m23_m23_m20_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 2> _m23_m23_m20_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 3> _m23_m23_m20_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 1, 0> _m23_m23_m21_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 1> _m23_m23_m21_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 2> _m23_m23_m21_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 3> _m23_m23_m21_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 2, 0> _m23_m23_m22_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 1> _m23_m23_m22_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 2> _m23_m23_m22_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 3> _m23_m23_m22_m23; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 3, 0> _m23_m23_m23_m20; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 1> _m23_m23_m23_m21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 2> _m23_m23_m23_m22; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 3> _m23_m23_m23_m23; hlslpp_swizzle_end

#endif

#if HLSLPP_ENABLE_MATRIX_SWIZZLE_11

// -------------------------------
// _NM
// -------------------------------

hlslpp_swizzle_start swizzle1<3> _34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle2<0, 3> _31_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<1, 3> _32_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<2, 3> _33_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 0> _34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 1> _34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 2> _34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 3> _34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 0, 3> _31_31_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 1, 3> _31_32_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 2, 3> _31_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 3, 0> _31_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 1> _31_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 2> _31_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 3> _31_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 0, 3> _32_31_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 1, 3> _32_32_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 2, 3> _32_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 3, 0> _32_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 1> _32_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 2> _32_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 3> _32_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 0, 3> _33_31_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 1, 3> _33_32_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 2, 3> _33_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 3, 0> _33_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 1> _33_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 2> _33_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 3> _33_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 0, 0> _34_31_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 1> _34_31_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 2> _34_31_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 3> _34_31_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 1, 0> _34_32_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 1> _34_32_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 2> _34_32_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 3> _34_32_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 2, 0> _34_33_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 1> _34_33_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 2> _34_33_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 3> _34_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 3, 0> _34_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 1> _34_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 2> _34_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 3> _34_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 0, 3> _31_31_31_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 1, 3> _31_31_32_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 2, 3> _31_31_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 3, 0> _31_31_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 1> _31_31_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 2> _31_31_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 3> _31_31_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 0, 3> _31_32_31_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 1, 3> _31_32_32_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 2, 3> _31_32_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 3, 0> _31_32_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 1> _31_32_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 2> _31_32_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 3> _31_32_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 0, 3> _31_33_31_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 1, 3> _31_33_32_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 2, 3> _31_33_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 3, 0> _31_33_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 1> _31_33_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 2> _31_33_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 3> _31_33_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 0, 0> _31_34_31_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 1> _31_34_31_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 2> _31_34_31_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 3> _31_34_31_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 1, 0> _31_34_32_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 1> _31_34_32_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 2> _31_34_32_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 3> _31_34_32_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 2, 0> _31_34_33_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 1> _31_34_33_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 2> _31_34_33_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 3> _31_34_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 3, 0> _31_34_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 1> _31_34_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 2> _31_34_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 3> _31_34_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 0, 3> _32_31_31_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 1, 3> _32_31_32_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 2, 3> _32_31_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 3, 0> _32_31_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 1> _32_31_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 2> _32_31_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 3> _32_31_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 0, 3> _32_32_31_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 1, 3> _32_32_32_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 2, 3> _32_32_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 3, 0> _32_32_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 1> _32_32_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 2> _32_32_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 3> _32_32_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 0, 3> _32_33_31_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 1, 3> _32_33_32_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 2, 3> _32_33_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 3, 0> _32_33_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 1> _32_33_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 2> _32_33_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 3> _32_33_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 0, 0> _32_34_31_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 1> _32_34_31_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 2> _32_34_31_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 3> _32_34_31_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 1, 0> _32_34_32_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 1> _32_34_32_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 2> _32_34_32_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 3> _32_34_32_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 2, 0> _32_34_33_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 1> _32_34_33_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 2> _32_34_33_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 3> _32_34_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 3, 0> _32_34_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 1> _32_34_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 2> _32_34_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 3> _32_34_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 0, 3> _33_31_31_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 1, 3> _33_31_32_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 2, 3> _33_31_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 3, 0> _33_31_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 1> _33_31_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 2> _33_31_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 3> _33_31_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 0, 3> _33_32_31_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 1, 3> _33_32_32_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 2, 3> _33_32_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 3, 0> _33_32_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 1> _33_32_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 2> _33_32_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 3> _33_32_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 0, 3> _33_33_31_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 1, 3> _33_33_32_34; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 2, 3> _33_33_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 3, 0> _33_33_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 1> _33_33_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 2> _33_33_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 3> _33_33_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 0, 0> _33_34_31_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 1> _33_34_31_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 2> _33_34_31_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 3> _33_34_31_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 1, 0> _33_34_32_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 1> _33_34_32_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 2> _33_34_32_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 3> _33_34_32_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 2, 0> _33_34_33_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 1> _33_34_33_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 2> _33_34_33_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 3> _33_34_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 3, 0> _33_34_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 1> _33_34_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 2> _33_34_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 3> _33_34_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 0, 0> _34_31_31_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 1> _34_31_31_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 2> _34_31_31_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 3> _34_31_31_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 1, 0> _34_31_32_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 1> _34_31_32_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 2> _34_31_32_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 3> _34_31_32_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 2, 0> _34_31_33_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 1> _34_31_33_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 2> _34_31_33_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 3> _34_31_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 3, 0> _34_31_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 1> _34_31_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 2> _34_31_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 3> _34_31_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 0, 0> _34_32_31_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 1> _34_32_31_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 2> _34_32_31_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 3> _34_32_31_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 1, 0> _34_32_32_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 1> _34_32_32_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 2> _34_32_32_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 3> _34_32_32_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 2, 0> _34_32_33_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 1> _34_32_33_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 2> _34_32_33_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 3> _34_32_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 3, 0> _34_32_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 1> _34_32_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 2> _34_32_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 3> _34_32_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 0, 0> _34_33_31_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 1> _34_33_31_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 2> _34_33_31_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 3> _34_33_31_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 1, 0> _34_33_32_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 1> _34_33_32_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 2> _34_33_32_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 3> _34_33_32_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 2, 0> _34_33_33_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 1> _34_33_33_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 2> _34_33_33_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 3> _34_33_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 3, 0> _34_33_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 1> _34_33_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 2> _34_33_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 3> _34_33_34_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 0, 0> _34_34_31_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 1> _34_34_31_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 2> _34_34_31_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 3> _34_34_31_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 1, 0> _34_34_32_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 1> _34_34_32_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 2> _34_34_32_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 3> _34_34_32_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 2, 0> _34_34_33_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 1> _34_34_33_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 2> _34_34_33_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 3> _34_34_33_34; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 3, 0> _34_34_34_31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 1> _34_34_34_32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 2> _34_34_34_33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 3> _34_34_34_34; hlslpp_swizzle_end

#endif