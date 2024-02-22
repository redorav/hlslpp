#if HLSLPP_ENABLE_MATRIX_SWIZZLE_M00

// -------------------------------
// _mNM
// -------------------------------

hlslpp_swizzle_start swizzle1<3> _m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle2<0, 3> _m30_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<1, 3> _m31_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<2, 3> _m32_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 0> _m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 1> _m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 2> _m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 3> _m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 0, 3> _m30_m30_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 1, 3> _m30_m31_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 2, 3> _m30_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 3, 0> _m30_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 1> _m30_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 2> _m30_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 3> _m30_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 0, 3> _m31_m30_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 1, 3> _m31_m31_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 2, 3> _m31_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 3, 0> _m31_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 1> _m31_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 2> _m31_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 3> _m31_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 0, 3> _m32_m30_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 1, 3> _m32_m31_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 2, 3> _m32_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 3, 0> _m32_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 1> _m32_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 2> _m32_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 3> _m32_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 0, 0> _m33_m30_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 1> _m33_m30_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 2> _m33_m30_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 3> _m33_m30_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 1, 0> _m33_m31_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 1> _m33_m31_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 2> _m33_m31_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 3> _m33_m31_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 2, 0> _m33_m32_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 1> _m33_m32_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 2> _m33_m32_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 3> _m33_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 3, 0> _m33_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 1> _m33_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 2> _m33_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 3> _m33_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 0, 3> _m30_m30_m30_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 1, 3> _m30_m30_m31_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 2, 3> _m30_m30_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 3, 0> _m30_m30_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 1> _m30_m30_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 2> _m30_m30_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 3> _m30_m30_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 0, 3> _m30_m31_m30_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 1, 3> _m30_m31_m31_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 2, 3> _m30_m31_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 3, 0> _m30_m31_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 1> _m30_m31_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 2> _m30_m31_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 3> _m30_m31_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 0, 3> _m30_m32_m30_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 1, 3> _m30_m32_m31_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 2, 3> _m30_m32_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 3, 0> _m30_m32_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 1> _m30_m32_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 2> _m30_m32_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 3> _m30_m32_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 0, 0> _m30_m33_m30_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 1> _m30_m33_m30_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 2> _m30_m33_m30_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 3> _m30_m33_m30_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 1, 0> _m30_m33_m31_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 1> _m30_m33_m31_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 2> _m30_m33_m31_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 3> _m30_m33_m31_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 2, 0> _m30_m33_m32_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 1> _m30_m33_m32_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 2> _m30_m33_m32_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 3> _m30_m33_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 3, 0> _m30_m33_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 1> _m30_m33_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 2> _m30_m33_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 3> _m30_m33_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 0, 3> _m31_m30_m30_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 1, 3> _m31_m30_m31_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 2, 3> _m31_m30_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 3, 0> _m31_m30_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 1> _m31_m30_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 2> _m31_m30_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 3> _m31_m30_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 0, 3> _m31_m31_m30_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 1, 3> _m31_m31_m31_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 2, 3> _m31_m31_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 3, 0> _m31_m31_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 1> _m31_m31_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 2> _m31_m31_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 3> _m31_m31_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 0, 3> _m31_m32_m30_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 1, 3> _m31_m32_m31_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 2, 3> _m31_m32_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 3, 0> _m31_m32_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 1> _m31_m32_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 2> _m31_m32_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 3> _m31_m32_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 0, 0> _m31_m33_m30_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 1> _m31_m33_m30_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 2> _m31_m33_m30_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 3> _m31_m33_m30_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 1, 0> _m31_m33_m31_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 1> _m31_m33_m31_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 2> _m31_m33_m31_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 3> _m31_m33_m31_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 2, 0> _m31_m33_m32_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 1> _m31_m33_m32_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 2> _m31_m33_m32_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 3> _m31_m33_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 3, 0> _m31_m33_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 1> _m31_m33_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 2> _m31_m33_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 3> _m31_m33_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 0, 3> _m32_m30_m30_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 1, 3> _m32_m30_m31_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 2, 3> _m32_m30_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 3, 0> _m32_m30_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 1> _m32_m30_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 2> _m32_m30_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 3> _m32_m30_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 0, 3> _m32_m31_m30_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 1, 3> _m32_m31_m31_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 2, 3> _m32_m31_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 3, 0> _m32_m31_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 1> _m32_m31_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 2> _m32_m31_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 3> _m32_m31_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 0, 3> _m32_m32_m30_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 1, 3> _m32_m32_m31_m33; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 2, 3> _m32_m32_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 3, 0> _m32_m32_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 1> _m32_m32_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 2> _m32_m32_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 3> _m32_m32_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 0, 0> _m32_m33_m30_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 1> _m32_m33_m30_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 2> _m32_m33_m30_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 3> _m32_m33_m30_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 1, 0> _m32_m33_m31_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 1> _m32_m33_m31_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 2> _m32_m33_m31_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 3> _m32_m33_m31_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 2, 0> _m32_m33_m32_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 1> _m32_m33_m32_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 2> _m32_m33_m32_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 3> _m32_m33_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 3, 0> _m32_m33_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 1> _m32_m33_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 2> _m32_m33_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 3> _m32_m33_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 0, 0> _m33_m30_m30_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 1> _m33_m30_m30_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 2> _m33_m30_m30_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 3> _m33_m30_m30_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 1, 0> _m33_m30_m31_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 1> _m33_m30_m31_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 2> _m33_m30_m31_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 3> _m33_m30_m31_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 2, 0> _m33_m30_m32_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 1> _m33_m30_m32_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 2> _m33_m30_m32_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 3> _m33_m30_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 3, 0> _m33_m30_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 1> _m33_m30_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 2> _m33_m30_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 3> _m33_m30_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 0, 0> _m33_m31_m30_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 1> _m33_m31_m30_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 2> _m33_m31_m30_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 3> _m33_m31_m30_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 1, 0> _m33_m31_m31_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 1> _m33_m31_m31_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 2> _m33_m31_m31_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 3> _m33_m31_m31_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 2, 0> _m33_m31_m32_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 1> _m33_m31_m32_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 2> _m33_m31_m32_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 3> _m33_m31_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 3, 0> _m33_m31_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 1> _m33_m31_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 2> _m33_m31_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 3> _m33_m31_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 0, 0> _m33_m32_m30_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 1> _m33_m32_m30_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 2> _m33_m32_m30_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 3> _m33_m32_m30_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 1, 0> _m33_m32_m31_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 1> _m33_m32_m31_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 2> _m33_m32_m31_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 3> _m33_m32_m31_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 2, 0> _m33_m32_m32_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 1> _m33_m32_m32_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 2> _m33_m32_m32_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 3> _m33_m32_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 3, 0> _m33_m32_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 1> _m33_m32_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 2> _m33_m32_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 3> _m33_m32_m33_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 0, 0> _m33_m33_m30_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 1> _m33_m33_m30_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 2> _m33_m33_m30_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 3> _m33_m33_m30_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 1, 0> _m33_m33_m31_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 1> _m33_m33_m31_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 2> _m33_m33_m31_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 3> _m33_m33_m31_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 2, 0> _m33_m33_m32_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 1> _m33_m33_m32_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 2> _m33_m33_m32_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 3> _m33_m33_m32_m33; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 3, 0> _m33_m33_m33_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 1> _m33_m33_m33_m31; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 2> _m33_m33_m33_m32; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 3> _m33_m33_m33_m33; hlslpp_swizzle_end

#endif

#if HLSLPP_ENABLE_MATRIX_SWIZZLE_11

// -------------------------------
// _NM
// -------------------------------

hlslpp_swizzle_start swizzle1<3> _44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle2<0, 3> _41_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<1, 3> _42_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<2, 3> _43_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 0> _44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 1> _44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 2> _44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 3> _44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 0, 3> _41_41_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 1, 3> _41_42_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 2, 3> _41_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 3, 0> _41_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 1> _41_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 2> _41_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 3> _41_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 0, 3> _42_41_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 1, 3> _42_42_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 2, 3> _42_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 3, 0> _42_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 1> _42_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 2> _42_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 3> _42_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 0, 3> _43_41_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 1, 3> _43_42_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 2, 3> _43_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 3, 0> _43_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 1> _43_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 2> _43_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 3> _43_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 0, 0> _44_41_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 1> _44_41_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 2> _44_41_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 3> _44_41_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 1, 0> _44_42_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 1> _44_42_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 2> _44_42_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 3> _44_42_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 2, 0> _44_43_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 1> _44_43_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 2> _44_43_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 3> _44_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 3, 0> _44_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 1> _44_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 2> _44_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 3> _44_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 0, 3> _41_41_41_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 1, 3> _41_41_42_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 2, 3> _41_41_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 3, 0> _41_41_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 1> _41_41_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 2> _41_41_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 3> _41_41_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 0, 3> _41_42_41_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 1, 3> _41_42_42_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 2, 3> _41_42_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 3, 0> _41_42_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 1> _41_42_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 2> _41_42_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 3> _41_42_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 0, 3> _41_43_41_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 1, 3> _41_43_42_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 2, 3> _41_43_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 3, 0> _41_43_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 1> _41_43_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 2> _41_43_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 3> _41_43_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 0, 0> _41_44_41_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 1> _41_44_41_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 2> _41_44_41_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 3> _41_44_41_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 1, 0> _41_44_42_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 1> _41_44_42_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 2> _41_44_42_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 3> _41_44_42_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 2, 0> _41_44_43_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 1> _41_44_43_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 2> _41_44_43_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 3> _41_44_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 3, 0> _41_44_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 1> _41_44_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 2> _41_44_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 3> _41_44_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 0, 3> _42_41_41_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 1, 3> _42_41_42_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 2, 3> _42_41_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 3, 0> _42_41_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 1> _42_41_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 2> _42_41_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 3> _42_41_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 0, 3> _42_42_41_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 1, 3> _42_42_42_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 2, 3> _42_42_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 3, 0> _42_42_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 1> _42_42_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 2> _42_42_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 3> _42_42_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 0, 3> _42_43_41_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 1, 3> _42_43_42_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 2, 3> _42_43_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 3, 0> _42_43_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 1> _42_43_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 2> _42_43_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 3> _42_43_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 0, 0> _42_44_41_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 1> _42_44_41_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 2> _42_44_41_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 3> _42_44_41_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 1, 0> _42_44_42_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 1> _42_44_42_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 2> _42_44_42_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 3> _42_44_42_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 2, 0> _42_44_43_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 1> _42_44_43_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 2> _42_44_43_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 3> _42_44_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 3, 0> _42_44_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 1> _42_44_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 2> _42_44_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 3> _42_44_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 0, 3> _43_41_41_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 1, 3> _43_41_42_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 2, 3> _43_41_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 3, 0> _43_41_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 1> _43_41_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 2> _43_41_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 3> _43_41_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 0, 3> _43_42_41_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 1, 3> _43_42_42_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 2, 3> _43_42_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 3, 0> _43_42_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 1> _43_42_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 2> _43_42_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 3> _43_42_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 0, 3> _43_43_41_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 1, 3> _43_43_42_44; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 2, 3> _43_43_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 3, 0> _43_43_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 1> _43_43_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 2> _43_43_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 3> _43_43_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 0, 0> _43_44_41_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 1> _43_44_41_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 2> _43_44_41_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 3> _43_44_41_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 1, 0> _43_44_42_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 1> _43_44_42_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 2> _43_44_42_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 3> _43_44_42_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 2, 0> _43_44_43_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 1> _43_44_43_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 2> _43_44_43_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 3> _43_44_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 3, 0> _43_44_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 1> _43_44_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 2> _43_44_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 3> _43_44_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 0, 0> _44_41_41_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 1> _44_41_41_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 2> _44_41_41_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 3> _44_41_41_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 1, 0> _44_41_42_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 1> _44_41_42_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 2> _44_41_42_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 3> _44_41_42_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 2, 0> _44_41_43_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 1> _44_41_43_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 2> _44_41_43_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 3> _44_41_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 3, 0> _44_41_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 1> _44_41_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 2> _44_41_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 3> _44_41_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 0, 0> _44_42_41_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 1> _44_42_41_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 2> _44_42_41_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 3> _44_42_41_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 1, 0> _44_42_42_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 1> _44_42_42_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 2> _44_42_42_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 3> _44_42_42_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 2, 0> _44_42_43_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 1> _44_42_43_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 2> _44_42_43_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 3> _44_42_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 3, 0> _44_42_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 1> _44_42_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 2> _44_42_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 3> _44_42_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 0, 0> _44_43_41_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 1> _44_43_41_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 2> _44_43_41_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 3> _44_43_41_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 1, 0> _44_43_42_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 1> _44_43_42_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 2> _44_43_42_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 3> _44_43_42_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 2, 0> _44_43_43_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 1> _44_43_43_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 2> _44_43_43_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 3> _44_43_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 3, 0> _44_43_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 1> _44_43_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 2> _44_43_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 3> _44_43_44_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 0, 0> _44_44_41_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 1> _44_44_41_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 2> _44_44_41_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 3> _44_44_41_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 1, 0> _44_44_42_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 1> _44_44_42_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 2> _44_44_42_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 3> _44_44_42_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 2, 0> _44_44_43_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 1> _44_44_43_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 2> _44_44_43_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 3> _44_44_43_44; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 3, 0> _44_44_44_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 1> _44_44_44_42; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 2> _44_44_44_43; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 3> _44_44_44_44; hlslpp_swizzle_end

#endif