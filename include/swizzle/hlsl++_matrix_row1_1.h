#if HLSLPP_ENABLE_MATRIX_SWIZZLE_M00

// -------------------------------
// _mNM
// -------------------------------

hlslpp_swizzle_start swizzle1<0> _m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<0, 0> _m10_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 0, 0> _m10_m10_m10; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 0, 0> _m10_m10_m10_m10; hlslpp_swizzle_end

#endif

#if HLSLPP_ENABLE_MATRIX_SWIZZLE_11

// -------------------------------
// _NM
// -------------------------------

hlslpp_swizzle_start swizzle1<0> _21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle2<0, 0> _21_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle3<0, 0, 0> _21_21_21; hlslpp_swizzle_end
hlslpp_swizzle_start swizzle4<0, 0, 0, 0> _21_21_21_21; hlslpp_swizzle_end

#endif