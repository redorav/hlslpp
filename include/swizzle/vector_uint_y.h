// -------------------------------
// XYZW
// -------------------------------

hlslpp_swizzle_start uswizzle1<1> y; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle2<0, 1> xy; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle2<1, 0> yx; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle2<1, 1> yy; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle3<0, 0, 1> xxy; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle3<0, 1, 0> xyx; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle3<0, 1, 1> xyy; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle3<1, 0, 0> yxx; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle3<1, 0, 1> yxy; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle3<1, 1, 0> yyx; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle3<1, 1, 1> yyy; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<0, 0, 0, 1> xxxy; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<0, 0, 1, 0> xxyx; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<0, 0, 1, 1> xxyy; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<0, 1, 0, 0> xyxx; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<0, 1, 0, 1> xyxy; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<0, 1, 1, 0> xyyx; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<0, 1, 1, 1> xyyy; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<1, 0, 0, 0> yxxx; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<1, 0, 0, 1> yxxy; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<1, 0, 1, 0> yxyx; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<1, 0, 1, 1> yxyy; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<1, 1, 0, 0> yyxx; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<1, 1, 0, 1> yyxy; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<1, 1, 1, 0> yyyx; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<1, 1, 1, 1> yyyy; hlslpp_swizzle_end

// -------------------------------
// RGBA
// -------------------------------

hlslpp_swizzle_start uswizzle1<1> g; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle2<0, 1> rg; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle2<1, 0> gr; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle2<1, 1> gg; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle3<0, 0, 1> rrg; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle3<0, 1, 0> rgr; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle3<0, 1, 1> rgg; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle3<1, 0, 0> grr; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle3<1, 0, 1> grg; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle3<1, 1, 0> ggr; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle3<1, 1, 1> ggg; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<0, 0, 0, 1> rrrg; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<0, 0, 1, 0> rrgr; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<0, 0, 1, 1> rrgg; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<0, 1, 0, 0> rgrr; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<0, 1, 0, 1> rgrg; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<0, 1, 1, 0> rggr; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<0, 1, 1, 1> rggg; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<1, 0, 0, 0> grrr; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<1, 0, 0, 1> grrg; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<1, 0, 1, 0> grgr; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<1, 0, 1, 1> grgg; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<1, 1, 0, 0> ggrr; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<1, 1, 0, 1> ggrg; hlslpp_swizzle_end

hlslpp_swizzle_start uswizzle4<1, 1, 1, 0> gggr; hlslpp_swizzle_end
hlslpp_swizzle_start uswizzle4<1, 1, 1, 1> gggg; hlslpp_swizzle_end