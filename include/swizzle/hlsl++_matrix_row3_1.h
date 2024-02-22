#if HLSLPP_ENABLE_MATRIX_SWIZZLE_M00

// -------------------------------
// _mNM
// -------------------------------

hlslpp_swizzle_start swizzle1<0> _m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<0, 0> _m30_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 0, 0> _m30_m30_m30; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 0, 0> _m30_m30_m30_m30; hlslpp_swizzle_end

#endif

#if HLSLPP_ENABLE_MATRIX_SWIZZLE_11

// -------------------------------
// _NM
// -------------------------------

hlslpp_swizzle_start swizzle1<0> _41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<0, 0> _41_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 0, 0> _41_41_41; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 0, 0> _41_41_41_41; hlslpp_swizzle_end

#endif