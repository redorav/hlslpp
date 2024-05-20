#if HLSLPP_ENABLE_MATRIX_SWIZZLE_M00

// -------------------------------
// _mNM
// -------------------------------

hlslpp_swizzle_start swizzle1<3> _m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle2<0, 3> _m00_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<1, 3> _m01_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<2, 3> _m02_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 0> _m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 1> _m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 2> _m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 3> _m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 0, 3> _m00_m00_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 1, 3> _m00_m01_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 2, 3> _m00_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 3, 0> _m00_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 1> _m00_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 2> _m00_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 3> _m00_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 0, 3> _m01_m00_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 1, 3> _m01_m01_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 2, 3> _m01_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 3, 0> _m01_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 1> _m01_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 2> _m01_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 3> _m01_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 0, 3> _m02_m00_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 1, 3> _m02_m01_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 2, 3> _m02_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 3, 0> _m02_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 1> _m02_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 2> _m02_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 3> _m02_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 0, 0> _m03_m00_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 1> _m03_m00_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 2> _m03_m00_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 3> _m03_m00_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 1, 0> _m03_m01_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 1> _m03_m01_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 2> _m03_m01_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 3> _m03_m01_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 2, 0> _m03_m02_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 1> _m03_m02_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 2> _m03_m02_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 3> _m03_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 3, 0> _m03_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 1> _m03_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 2> _m03_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 3> _m03_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 0, 3> _m00_m00_m00_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 1, 3> _m00_m00_m01_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 2, 3> _m00_m00_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 3, 0> _m00_m00_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 1> _m00_m00_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 2> _m00_m00_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 3> _m00_m00_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 0, 3> _m00_m01_m00_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 1, 3> _m00_m01_m01_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 2, 3> _m00_m01_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 3, 0> _m00_m01_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 1> _m00_m01_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 2> _m00_m01_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 3> _m00_m01_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 0, 3> _m00_m02_m00_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 1, 3> _m00_m02_m01_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 2, 3> _m00_m02_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 3, 0> _m00_m02_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 1> _m00_m02_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 2> _m00_m02_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 3> _m00_m02_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 0, 0> _m00_m03_m00_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 1> _m00_m03_m00_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 2> _m00_m03_m00_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 3> _m00_m03_m00_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 1, 0> _m00_m03_m01_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 1> _m00_m03_m01_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 2> _m00_m03_m01_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 3> _m00_m03_m01_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 2, 0> _m00_m03_m02_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 1> _m00_m03_m02_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 2> _m00_m03_m02_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 3> _m00_m03_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 3, 0> _m00_m03_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 1> _m00_m03_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 2> _m00_m03_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 3> _m00_m03_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 0, 3> _m01_m00_m00_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 1, 3> _m01_m00_m01_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 2, 3> _m01_m00_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 3, 0> _m01_m00_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 1> _m01_m00_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 2> _m01_m00_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 3> _m01_m00_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 0, 3> _m01_m01_m00_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 1, 3> _m01_m01_m01_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 2, 3> _m01_m01_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 3, 0> _m01_m01_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 1> _m01_m01_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 2> _m01_m01_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 3> _m01_m01_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 0, 3> _m01_m02_m00_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 1, 3> _m01_m02_m01_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 2, 3> _m01_m02_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 3, 0> _m01_m02_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 1> _m01_m02_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 2> _m01_m02_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 3> _m01_m02_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 0, 0> _m01_m03_m00_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 1> _m01_m03_m00_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 2> _m01_m03_m00_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 3> _m01_m03_m00_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 1, 0> _m01_m03_m01_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 1> _m01_m03_m01_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 2> _m01_m03_m01_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 3> _m01_m03_m01_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 2, 0> _m01_m03_m02_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 1> _m01_m03_m02_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 2> _m01_m03_m02_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 3> _m01_m03_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 3, 0> _m01_m03_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 1> _m01_m03_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 2> _m01_m03_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 3> _m01_m03_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 0, 3> _m02_m00_m00_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 1, 3> _m02_m00_m01_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 2, 3> _m02_m00_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 3, 0> _m02_m00_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 1> _m02_m00_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 2> _m02_m00_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 3> _m02_m00_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 0, 3> _m02_m01_m00_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 1, 3> _m02_m01_m01_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 2, 3> _m02_m01_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 3, 0> _m02_m01_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 1> _m02_m01_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 2> _m02_m01_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 3> _m02_m01_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 0, 3> _m02_m02_m00_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 1, 3> _m02_m02_m01_m03; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 2, 3> _m02_m02_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 3, 0> _m02_m02_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 1> _m02_m02_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 2> _m02_m02_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 3> _m02_m02_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 0, 0> _m02_m03_m00_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 1> _m02_m03_m00_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 2> _m02_m03_m00_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 3> _m02_m03_m00_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 1, 0> _m02_m03_m01_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 1> _m02_m03_m01_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 2> _m02_m03_m01_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 3> _m02_m03_m01_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 2, 0> _m02_m03_m02_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 1> _m02_m03_m02_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 2> _m02_m03_m02_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 3> _m02_m03_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 3, 0> _m02_m03_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 1> _m02_m03_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 2> _m02_m03_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 3> _m02_m03_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 0, 0> _m03_m00_m00_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 1> _m03_m00_m00_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 2> _m03_m00_m00_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 3> _m03_m00_m00_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 1, 0> _m03_m00_m01_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 1> _m03_m00_m01_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 2> _m03_m00_m01_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 3> _m03_m00_m01_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 2, 0> _m03_m00_m02_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 1> _m03_m00_m02_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 2> _m03_m00_m02_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 3> _m03_m00_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 3, 0> _m03_m00_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 1> _m03_m00_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 2> _m03_m00_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 3> _m03_m00_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 0, 0> _m03_m01_m00_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 1> _m03_m01_m00_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 2> _m03_m01_m00_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 3> _m03_m01_m00_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 1, 0> _m03_m01_m01_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 1> _m03_m01_m01_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 2> _m03_m01_m01_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 3> _m03_m01_m01_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 2, 0> _m03_m01_m02_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 1> _m03_m01_m02_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 2> _m03_m01_m02_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 3> _m03_m01_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 3, 0> _m03_m01_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 1> _m03_m01_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 2> _m03_m01_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 3> _m03_m01_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 0, 0> _m03_m02_m00_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 1> _m03_m02_m00_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 2> _m03_m02_m00_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 3> _m03_m02_m00_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 1, 0> _m03_m02_m01_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 1> _m03_m02_m01_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 2> _m03_m02_m01_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 3> _m03_m02_m01_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 2, 0> _m03_m02_m02_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 1> _m03_m02_m02_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 2> _m03_m02_m02_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 3> _m03_m02_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 3, 0> _m03_m02_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 1> _m03_m02_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 2> _m03_m02_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 3> _m03_m02_m03_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 0, 0> _m03_m03_m00_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 1> _m03_m03_m00_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 2> _m03_m03_m00_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 3> _m03_m03_m00_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 1, 0> _m03_m03_m01_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 1> _m03_m03_m01_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 2> _m03_m03_m01_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 3> _m03_m03_m01_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 2, 0> _m03_m03_m02_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 1> _m03_m03_m02_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 2> _m03_m03_m02_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 3> _m03_m03_m02_m03; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 3, 0> _m03_m03_m03_m00; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 1> _m03_m03_m03_m01; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 2> _m03_m03_m03_m02; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 3> _m03_m03_m03_m03; hlslpp_swizzle_end

#endif

#if HLSLPP_ENABLE_MATRIX_SWIZZLE_11

// -------------------------------
// _NM
// -------------------------------

hlslpp_swizzle_start swizzle1<3> _14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle2<0, 3> _11_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<1, 3> _12_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<2, 3> _13_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 0> _14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 1> _14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 2> _14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<3, 3> _14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 0, 3> _11_11_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 1, 3> _11_12_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 2, 3> _11_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<0, 3, 0> _11_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 1> _11_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 2> _11_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 3, 3> _11_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 0, 3> _12_11_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 1, 3> _12_12_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 2, 3> _12_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<1, 3, 0> _12_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 1> _12_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 2> _12_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<1, 3, 3> _12_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 0, 3> _13_11_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 1, 3> _13_12_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 2, 3> _13_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<2, 3, 0> _13_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 1> _13_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 2> _13_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<2, 3, 3> _13_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 0, 0> _14_11_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 1> _14_11_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 2> _14_11_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 0, 3> _14_11_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 1, 0> _14_12_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 1> _14_12_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 2> _14_12_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 1, 3> _14_12_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 2, 0> _14_13_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 1> _14_13_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 2> _14_13_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 2, 3> _14_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle3<3, 3, 0> _14_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 1> _14_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 2> _14_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<3, 3, 3> _14_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 0, 3> _11_11_11_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 1, 3> _11_11_12_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 2, 3> _11_11_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 0, 3, 0> _11_11_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 1> _11_11_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 2> _11_11_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 3, 3> _11_11_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 0, 3> _11_12_11_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 1, 3> _11_12_12_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 2, 3> _11_12_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 1, 3, 0> _11_12_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 1> _11_12_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 2> _11_12_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 1, 3, 3> _11_12_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 0, 3> _11_13_11_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 1, 3> _11_13_12_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 2, 3> _11_13_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 2, 3, 0> _11_13_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 1> _11_13_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 2> _11_13_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 2, 3, 3> _11_13_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 0, 0> _11_14_11_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 1> _11_14_11_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 2> _11_14_11_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 0, 3> _11_14_11_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 1, 0> _11_14_12_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 1> _11_14_12_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 2> _11_14_12_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 1, 3> _11_14_12_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 2, 0> _11_14_13_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 1> _11_14_13_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 2> _11_14_13_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 2, 3> _11_14_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<0, 3, 3, 0> _11_14_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 1> _11_14_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 2> _11_14_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 3, 3, 3> _11_14_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 0, 3> _12_11_11_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 1, 3> _12_11_12_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 2, 3> _12_11_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 0, 3, 0> _12_11_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 1> _12_11_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 2> _12_11_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 0, 3, 3> _12_11_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 0, 3> _12_12_11_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 1, 3> _12_12_12_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 2, 3> _12_12_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 1, 3, 0> _12_12_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 1> _12_12_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 2> _12_12_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 1, 3, 3> _12_12_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 0, 3> _12_13_11_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 1, 3> _12_13_12_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 2, 3> _12_13_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 2, 3, 0> _12_13_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 1> _12_13_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 2> _12_13_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 2, 3, 3> _12_13_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 0, 0> _12_14_11_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 1> _12_14_11_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 2> _12_14_11_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 0, 3> _12_14_11_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 1, 0> _12_14_12_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 1> _12_14_12_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 2> _12_14_12_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 1, 3> _12_14_12_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 2, 0> _12_14_13_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 1> _12_14_13_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 2> _12_14_13_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 2, 3> _12_14_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<1, 3, 3, 0> _12_14_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 1> _12_14_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 2> _12_14_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<1, 3, 3, 3> _12_14_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 0, 3> _13_11_11_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 1, 3> _13_11_12_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 2, 3> _13_11_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 0, 3, 0> _13_11_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 1> _13_11_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 2> _13_11_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 0, 3, 3> _13_11_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 0, 3> _13_12_11_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 1, 3> _13_12_12_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 2, 3> _13_12_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 1, 3, 0> _13_12_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 1> _13_12_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 2> _13_12_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 1, 3, 3> _13_12_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 0, 3> _13_13_11_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 1, 3> _13_13_12_14; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 2, 3> _13_13_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 2, 3, 0> _13_13_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 1> _13_13_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 2> _13_13_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 2, 3, 3> _13_13_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 0, 0> _13_14_11_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 1> _13_14_11_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 2> _13_14_11_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 0, 3> _13_14_11_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 1, 0> _13_14_12_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 1> _13_14_12_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 2> _13_14_12_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 1, 3> _13_14_12_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 2, 0> _13_14_13_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 1> _13_14_13_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 2> _13_14_13_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 2, 3> _13_14_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<2, 3, 3, 0> _13_14_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 1> _13_14_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 2> _13_14_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<2, 3, 3, 3> _13_14_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 0, 0> _14_11_11_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 1> _14_11_11_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 2> _14_11_11_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 0, 3> _14_11_11_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 1, 0> _14_11_12_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 1> _14_11_12_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 2> _14_11_12_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 1, 3> _14_11_12_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 2, 0> _14_11_13_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 1> _14_11_13_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 2> _14_11_13_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 2, 3> _14_11_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 0, 3, 0> _14_11_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 1> _14_11_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 2> _14_11_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 0, 3, 3> _14_11_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 0, 0> _14_12_11_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 1> _14_12_11_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 2> _14_12_11_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 0, 3> _14_12_11_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 1, 0> _14_12_12_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 1> _14_12_12_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 2> _14_12_12_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 1, 3> _14_12_12_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 2, 0> _14_12_13_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 1> _14_12_13_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 2> _14_12_13_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 2, 3> _14_12_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 1, 3, 0> _14_12_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 1> _14_12_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 2> _14_12_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 1, 3, 3> _14_12_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 0, 0> _14_13_11_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 1> _14_13_11_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 2> _14_13_11_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 0, 3> _14_13_11_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 1, 0> _14_13_12_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 1> _14_13_12_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 2> _14_13_12_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 1, 3> _14_13_12_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 2, 0> _14_13_13_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 1> _14_13_13_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 2> _14_13_13_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 2, 3> _14_13_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 2, 3, 0> _14_13_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 1> _14_13_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 2> _14_13_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 2, 3, 3> _14_13_14_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 0, 0> _14_14_11_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 1> _14_14_11_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 2> _14_14_11_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 0, 3> _14_14_11_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 1, 0> _14_14_12_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 1> _14_14_12_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 2> _14_14_12_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 1, 3> _14_14_12_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 2, 0> _14_14_13_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 1> _14_14_13_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 2> _14_14_13_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 2, 3> _14_14_13_14; hlslpp_swizzle_end

hlslpp_swizzle_start swizzle4<3, 3, 3, 0> _14_14_14_11; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 1> _14_14_14_12; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 2> _14_14_14_13; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<3, 3, 3, 3> _14_14_14_14; hlslpp_swizzle_end

#endif