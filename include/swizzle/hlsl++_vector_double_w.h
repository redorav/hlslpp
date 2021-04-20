// -------------------------------
// XYZW
// -------------------------------

hlslpp_declare_swizzle1(dswizzle1, 3, w);

hlslpp_declare_swizzle2(dswizzle2, 0, 3, xw);
hlslpp_declare_swizzle2(dswizzle2, 1, 3, yw);
hlslpp_declare_swizzle2(dswizzle2, 2, 3, zw);
hlslpp_declare_swizzle2(dswizzle2, 3, 0, wx);
hlslpp_declare_swizzle2(dswizzle2, 3, 1, wy);
hlslpp_declare_swizzle2(dswizzle2, 3, 2, wz);
hlslpp_declare_swizzle2(dswizzle2, 3, 3, ww);

hlslpp_declare_swizzle3(dswizzle3, 0, 0, 3, xxw);
hlslpp_declare_swizzle3(dswizzle3, 0, 1, 3, xyw);
hlslpp_declare_swizzle3(dswizzle3, 0, 2, 3, xzw);

hlslpp_declare_swizzle3(dswizzle3, 0, 3, 0, xwx);
hlslpp_declare_swizzle3(dswizzle3, 0, 3, 1, xwy);
hlslpp_declare_swizzle3(dswizzle3, 0, 3, 2, xwz);
hlslpp_declare_swizzle3(dswizzle3, 0, 3, 3, xww);

hlslpp_declare_swizzle3(dswizzle3, 1, 0, 3, yxw);
hlslpp_declare_swizzle3(dswizzle3, 1, 1, 3, yyw);
hlslpp_declare_swizzle3(dswizzle3, 1, 2, 3, yzw);

hlslpp_declare_swizzle3(dswizzle3, 1, 3, 0, ywx);
hlslpp_declare_swizzle3(dswizzle3, 1, 3, 1, ywy);
hlslpp_declare_swizzle3(dswizzle3, 1, 3, 2, ywz);
hlslpp_declare_swizzle3(dswizzle3, 1, 3, 3, yww);

hlslpp_declare_swizzle3(dswizzle3, 2, 0, 3, zxw);
hlslpp_declare_swizzle3(dswizzle3, 2, 1, 3, zyw);
hlslpp_declare_swizzle3(dswizzle3, 2, 2, 3, zzw);

hlslpp_declare_swizzle3(dswizzle3, 2, 3, 0, zwx);
hlslpp_declare_swizzle3(dswizzle3, 2, 3, 1, zwy);
hlslpp_declare_swizzle3(dswizzle3, 2, 3, 2, zwz);
hlslpp_declare_swizzle3(dswizzle3, 2, 3, 3, zww);

hlslpp_declare_swizzle3(dswizzle3, 3, 0, 0, wxx);
hlslpp_declare_swizzle3(dswizzle3, 3, 0, 1, wxy);
hlslpp_declare_swizzle3(dswizzle3, 3, 0, 2, wxz);
hlslpp_declare_swizzle3(dswizzle3, 3, 0, 3, wxw);

hlslpp_declare_swizzle3(dswizzle3, 3, 1, 0, wyx);
hlslpp_declare_swizzle3(dswizzle3, 3, 1, 1, wyy);
hlslpp_declare_swizzle3(dswizzle3, 3, 1, 2, wyz);
hlslpp_declare_swizzle3(dswizzle3, 3, 1, 3, wyw);

hlslpp_declare_swizzle3(dswizzle3, 3, 2, 0, wzx);
hlslpp_declare_swizzle3(dswizzle3, 3, 2, 1, wzy);
hlslpp_declare_swizzle3(dswizzle3, 3, 2, 2, wzz);
hlslpp_declare_swizzle3(dswizzle3, 3, 2, 3, wzw);

hlslpp_declare_swizzle3(dswizzle3, 3, 3, 0, wwx);
hlslpp_declare_swizzle3(dswizzle3, 3, 3, 1, wwy);
hlslpp_declare_swizzle3(dswizzle3, 3, 3, 2, wwz);
hlslpp_declare_swizzle3(dswizzle3, 3, 3, 3, www);

hlslpp_declare_swizzle4(dswizzle4, 0, 0, 0, 3, xxxw);
hlslpp_declare_swizzle4(dswizzle4, 0, 0, 1, 3, xxyw);
hlslpp_declare_swizzle4(dswizzle4, 0, 0, 2, 3, xxzw);

hlslpp_declare_swizzle4(dswizzle4, 0, 0, 3, 0, xxwx);
hlslpp_declare_swizzle4(dswizzle4, 0, 0, 3, 1, xxwy);
hlslpp_declare_swizzle4(dswizzle4, 0, 0, 3, 2, xxwz);
hlslpp_declare_swizzle4(dswizzle4, 0, 0, 3, 3, xxww);

hlslpp_declare_swizzle4(dswizzle4, 0, 1, 0, 3, xyxw);
hlslpp_declare_swizzle4(dswizzle4, 0, 1, 1, 3, xyyw);
hlslpp_declare_swizzle4(dswizzle4, 0, 1, 2, 3, xyzw);

hlslpp_declare_swizzle4(dswizzle4, 0, 1, 3, 0, xywx);
hlslpp_declare_swizzle4(dswizzle4, 0, 1, 3, 1, xywy);
hlslpp_declare_swizzle4(dswizzle4, 0, 1, 3, 2, xywz);
hlslpp_declare_swizzle4(dswizzle4, 0, 1, 3, 3, xyww);

hlslpp_declare_swizzle4(dswizzle4, 0, 2, 0, 3, xzxw);
hlslpp_declare_swizzle4(dswizzle4, 0, 2, 1, 3, xzyw);
hlslpp_declare_swizzle4(dswizzle4, 0, 2, 2, 3, xzzw);

hlslpp_declare_swizzle4(dswizzle4, 0, 2, 3, 0, xzwx);
hlslpp_declare_swizzle4(dswizzle4, 0, 2, 3, 1, xzwy);
hlslpp_declare_swizzle4(dswizzle4, 0, 2, 3, 2, xzwz);
hlslpp_declare_swizzle4(dswizzle4, 0, 2, 3, 3, xzww);

hlslpp_declare_swizzle4(dswizzle4, 0, 3, 0, 0, xwxx);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 0, 1, xwxy);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 0, 2, xwxz);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 0, 3, xwxw);

hlslpp_declare_swizzle4(dswizzle4, 0, 3, 1, 0, xwyx);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 1, 1, xwyy);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 1, 2, xwyz);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 1, 3, xwyw);

hlslpp_declare_swizzle4(dswizzle4, 0, 3, 2, 0, xwzx);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 2, 1, xwzy);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 2, 2, xwzz);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 2, 3, xwzw);

hlslpp_declare_swizzle4(dswizzle4, 0, 3, 3, 0, xwwx);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 3, 1, xwwy);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 3, 2, xwwz);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 3, 3, xwww);

hlslpp_declare_swizzle4(dswizzle4, 1, 0, 0, 3, yxxw);
hlslpp_declare_swizzle4(dswizzle4, 1, 0, 1, 3, yxyw);
hlslpp_declare_swizzle4(dswizzle4, 1, 0, 2, 3, yxzw);

hlslpp_declare_swizzle4(dswizzle4, 1, 0, 3, 0, yxwx);
hlslpp_declare_swizzle4(dswizzle4, 1, 0, 3, 1, yxwy);
hlslpp_declare_swizzle4(dswizzle4, 1, 0, 3, 2, yxwz);
hlslpp_declare_swizzle4(dswizzle4, 1, 0, 3, 3, yxww);

hlslpp_declare_swizzle4(dswizzle4, 1, 1, 0, 3, yyxw);
hlslpp_declare_swizzle4(dswizzle4, 1, 1, 1, 3, yyyw);
hlslpp_declare_swizzle4(dswizzle4, 1, 1, 2, 3, yyzw);

hlslpp_declare_swizzle4(dswizzle4, 1, 1, 3, 0, yywx);
hlslpp_declare_swizzle4(dswizzle4, 1, 1, 3, 1, yywy);
hlslpp_declare_swizzle4(dswizzle4, 1, 1, 3, 2, yywz);
hlslpp_declare_swizzle4(dswizzle4, 1, 1, 3, 3, yyww);

hlslpp_declare_swizzle4(dswizzle4, 1, 2, 0, 3, yzxw);
hlslpp_declare_swizzle4(dswizzle4, 1, 2, 1, 3, yzyw);
hlslpp_declare_swizzle4(dswizzle4, 1, 2, 2, 3, yzzw);

hlslpp_declare_swizzle4(dswizzle4, 1, 2, 3, 0, yzwx);
hlslpp_declare_swizzle4(dswizzle4, 1, 2, 3, 1, yzwy);
hlslpp_declare_swizzle4(dswizzle4, 1, 2, 3, 2, yzwz);
hlslpp_declare_swizzle4(dswizzle4, 1, 2, 3, 3, yzww);

hlslpp_declare_swizzle4(dswizzle4, 1, 3, 0, 0, ywxx);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 0, 1, ywxy);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 0, 2, ywxz);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 0, 3, ywxw);

hlslpp_declare_swizzle4(dswizzle4, 1, 3, 1, 0, ywyx);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 1, 1, ywyy);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 1, 2, ywyz);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 1, 3, ywyw);

hlslpp_declare_swizzle4(dswizzle4, 1, 3, 2, 0, ywzx);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 2, 1, ywzy);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 2, 2, ywzz);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 2, 3, ywzw);

hlslpp_declare_swizzle4(dswizzle4, 1, 3, 3, 0, ywwx);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 3, 1, ywwy);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 3, 2, ywwz);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 3, 3, ywww);

hlslpp_declare_swizzle4(dswizzle4, 2, 0, 0, 3, zxxw);
hlslpp_declare_swizzle4(dswizzle4, 2, 0, 1, 3, zxyw);
hlslpp_declare_swizzle4(dswizzle4, 2, 0, 2, 3, zxzw);

hlslpp_declare_swizzle4(dswizzle4, 2, 0, 3, 0, zxwx);
hlslpp_declare_swizzle4(dswizzle4, 2, 0, 3, 1, zxwy);
hlslpp_declare_swizzle4(dswizzle4, 2, 0, 3, 2, zxwz);
hlslpp_declare_swizzle4(dswizzle4, 2, 0, 3, 3, zxww);

hlslpp_declare_swizzle4(dswizzle4, 2, 1, 0, 3, zyxw);
hlslpp_declare_swizzle4(dswizzle4, 2, 1, 1, 3, zyyw);
hlslpp_declare_swizzle4(dswizzle4, 2, 1, 2, 3, zyzw);

hlslpp_declare_swizzle4(dswizzle4, 2, 1, 3, 0, zywx);
hlslpp_declare_swizzle4(dswizzle4, 2, 1, 3, 1, zywy);
hlslpp_declare_swizzle4(dswizzle4, 2, 1, 3, 2, zywz);
hlslpp_declare_swizzle4(dswizzle4, 2, 1, 3, 3, zyww);

hlslpp_declare_swizzle4(dswizzle4, 2, 2, 0, 3, zzxw);
hlslpp_declare_swizzle4(dswizzle4, 2, 2, 1, 3, zzyw);
hlslpp_declare_swizzle4(dswizzle4, 2, 2, 2, 3, zzzw);

hlslpp_declare_swizzle4(dswizzle4, 2, 2, 3, 0, zzwx);
hlslpp_declare_swizzle4(dswizzle4, 2, 2, 3, 1, zzwy);
hlslpp_declare_swizzle4(dswizzle4, 2, 2, 3, 2, zzwz);
hlslpp_declare_swizzle4(dswizzle4, 2, 2, 3, 3, zzww);

hlslpp_declare_swizzle4(dswizzle4, 2, 3, 0, 0, zwxx);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 0, 1, zwxy);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 0, 2, zwxz);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 0, 3, zwxw);

hlslpp_declare_swizzle4(dswizzle4, 2, 3, 1, 0, zwyx);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 1, 1, zwyy);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 1, 2, zwyz);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 1, 3, zwyw);

hlslpp_declare_swizzle4(dswizzle4, 2, 3, 2, 0, zwzx);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 2, 1, zwzy);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 2, 2, zwzz);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 2, 3, zwzw);

hlslpp_declare_swizzle4(dswizzle4, 2, 3, 3, 0, zwwx);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 3, 1, zwwy);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 3, 2, zwwz);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 3, 3, zwww);

hlslpp_declare_swizzle4(dswizzle4, 3, 0, 0, 0, wxxx);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 0, 1, wxxy);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 0, 2, wxxz);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 0, 3, wxxw);

hlslpp_declare_swizzle4(dswizzle4, 3, 0, 1, 0, wxyx);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 1, 1, wxyy);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 1, 2, wxyz);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 1, 3, wxyw);

hlslpp_declare_swizzle4(dswizzle4, 3, 0, 2, 0, wxzx);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 2, 1, wxzy);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 2, 2, wxzz);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 2, 3, wxzw);

hlslpp_declare_swizzle4(dswizzle4, 3, 0, 3, 0, wxwx);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 3, 1, wxwy);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 3, 2, wxwz);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 3, 3, wxww);

hlslpp_declare_swizzle4(dswizzle4, 3, 1, 0, 0, wyxx);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 0, 1, wyxy);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 0, 2, wyxz);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 0, 3, wyxw);

hlslpp_declare_swizzle4(dswizzle4, 3, 1, 1, 0, wyyx);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 1, 1, wyyy);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 1, 2, wyyz);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 1, 3, wyyw);

hlslpp_declare_swizzle4(dswizzle4, 3, 1, 2, 0, wyzx);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 2, 1, wyzy);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 2, 2, wyzz);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 2, 3, wyzw);

hlslpp_declare_swizzle4(dswizzle4, 3, 1, 3, 0, wywx);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 3, 1, wywy);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 3, 2, wywz);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 3, 3, wyww);

hlslpp_declare_swizzle4(dswizzle4, 3, 2, 0, 0, wzxx);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 0, 1, wzxy);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 0, 2, wzxz);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 0, 3, wzxw);

hlslpp_declare_swizzle4(dswizzle4, 3, 2, 1, 0, wzyx);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 1, 1, wzyy);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 1, 2, wzyz);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 1, 3, wzyw);

hlslpp_declare_swizzle4(dswizzle4, 3, 2, 2, 0, wzzx);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 2, 1, wzzy);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 2, 2, wzzz);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 2, 3, wzzw);

hlslpp_declare_swizzle4(dswizzle4, 3, 2, 3, 0, wzwx);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 3, 1, wzwy);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 3, 2, wzwz);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 3, 3, wzww);

hlslpp_declare_swizzle4(dswizzle4, 3, 3, 0, 0, wwxx);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 0, 1, wwxy);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 0, 2, wwxz);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 0, 3, wwxw);

hlslpp_declare_swizzle4(dswizzle4, 3, 3, 1, 0, wwyx);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 1, 1, wwyy);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 1, 2, wwyz);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 1, 3, wwyw);

hlslpp_declare_swizzle4(dswizzle4, 3, 3, 2, 0, wwzx);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 2, 1, wwzy);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 2, 2, wwzz);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 2, 3, wwzw);

hlslpp_declare_swizzle4(dswizzle4, 3, 3, 3, 0, wwwx);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 3, 1, wwwy);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 3, 2, wwwz);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 3, 3, wwww);

// -------------------------------
// RGBA
// -------------------------------

hlslpp_declare_swizzle1(dswizzle1, 3, a);

hlslpp_declare_swizzle2(dswizzle2, 0, 3, ra);
hlslpp_declare_swizzle2(dswizzle2, 1, 3, ga);
hlslpp_declare_swizzle2(dswizzle2, 2, 3, ba);
hlslpp_declare_swizzle2(dswizzle2, 3, 0, ar);
hlslpp_declare_swizzle2(dswizzle2, 3, 1, ag);
hlslpp_declare_swizzle2(dswizzle2, 3, 2, ab);
hlslpp_declare_swizzle2(dswizzle2, 3, 3, aa);

hlslpp_declare_swizzle3(dswizzle3, 0, 0, 3, rra);
hlslpp_declare_swizzle3(dswizzle3, 0, 1, 3, rga);
hlslpp_declare_swizzle3(dswizzle3, 0, 2, 3, rba);

hlslpp_declare_swizzle3(dswizzle3, 0, 3, 0, rar);
hlslpp_declare_swizzle3(dswizzle3, 0, 3, 1, rag);
hlslpp_declare_swizzle3(dswizzle3, 0, 3, 2, rab);
hlslpp_declare_swizzle3(dswizzle3, 0, 3, 3, raa);

hlslpp_declare_swizzle3(dswizzle3, 1, 0, 3, gra);
hlslpp_declare_swizzle3(dswizzle3, 1, 1, 3, gga);
hlslpp_declare_swizzle3(dswizzle3, 1, 2, 3, gba);

hlslpp_declare_swizzle3(dswizzle3, 1, 3, 0, gar);
hlslpp_declare_swizzle3(dswizzle3, 1, 3, 1, gag);
hlslpp_declare_swizzle3(dswizzle3, 1, 3, 2, gab);
hlslpp_declare_swizzle3(dswizzle3, 1, 3, 3, gaa);

hlslpp_declare_swizzle3(dswizzle3, 2, 0, 3, bra);
hlslpp_declare_swizzle3(dswizzle3, 2, 1, 3, bga);
hlslpp_declare_swizzle3(dswizzle3, 2, 2, 3, bba);

hlslpp_declare_swizzle3(dswizzle3, 2, 3, 0, bar);
hlslpp_declare_swizzle3(dswizzle3, 2, 3, 1, bag);
hlslpp_declare_swizzle3(dswizzle3, 2, 3, 2, bab);
hlslpp_declare_swizzle3(dswizzle3, 2, 3, 3, baa);

hlslpp_declare_swizzle3(dswizzle3, 3, 0, 0, arr);
hlslpp_declare_swizzle3(dswizzle3, 3, 0, 1, arg);
hlslpp_declare_swizzle3(dswizzle3, 3, 0, 2, arb);
hlslpp_declare_swizzle3(dswizzle3, 3, 0, 3, ara);

hlslpp_declare_swizzle3(dswizzle3, 3, 1, 0, agr);
hlslpp_declare_swizzle3(dswizzle3, 3, 1, 1, agg);
hlslpp_declare_swizzle3(dswizzle3, 3, 1, 2, agb);
hlslpp_declare_swizzle3(dswizzle3, 3, 1, 3, aga);

hlslpp_declare_swizzle3(dswizzle3, 3, 2, 0, abr);
hlslpp_declare_swizzle3(dswizzle3, 3, 2, 1, abg);
hlslpp_declare_swizzle3(dswizzle3, 3, 2, 2, abb);
hlslpp_declare_swizzle3(dswizzle3, 3, 2, 3, aba);

hlslpp_declare_swizzle3(dswizzle3, 3, 3, 0, aar);
hlslpp_declare_swizzle3(dswizzle3, 3, 3, 1, aag);
hlslpp_declare_swizzle3(dswizzle3, 3, 3, 2, aab);
hlslpp_declare_swizzle3(dswizzle3, 3, 3, 3, aaa);

hlslpp_declare_swizzle4(dswizzle4, 0, 0, 0, 3, rrra);
hlslpp_declare_swizzle4(dswizzle4, 0, 0, 1, 3, rrga);
hlslpp_declare_swizzle4(dswizzle4, 0, 0, 2, 3, rrba);

hlslpp_declare_swizzle4(dswizzle4, 0, 0, 3, 0, rrar);
hlslpp_declare_swizzle4(dswizzle4, 0, 0, 3, 1, rrag);
hlslpp_declare_swizzle4(dswizzle4, 0, 0, 3, 2, rrab);
hlslpp_declare_swizzle4(dswizzle4, 0, 0, 3, 3, rraa);

hlslpp_declare_swizzle4(dswizzle4, 0, 1, 0, 3, rgra);
hlslpp_declare_swizzle4(dswizzle4, 0, 1, 1, 3, rgga);
hlslpp_declare_swizzle4(dswizzle4, 0, 1, 2, 3, rgba);

hlslpp_declare_swizzle4(dswizzle4, 0, 1, 3, 0, rgar);
hlslpp_declare_swizzle4(dswizzle4, 0, 1, 3, 1, rgag);
hlslpp_declare_swizzle4(dswizzle4, 0, 1, 3, 2, rgab);
hlslpp_declare_swizzle4(dswizzle4, 0, 1, 3, 3, rgaa);

hlslpp_declare_swizzle4(dswizzle4, 0, 2, 0, 3, rbra);
hlslpp_declare_swizzle4(dswizzle4, 0, 2, 1, 3, rbga);
hlslpp_declare_swizzle4(dswizzle4, 0, 2, 2, 3, rbba);

hlslpp_declare_swizzle4(dswizzle4, 0, 2, 3, 0, rbar);
hlslpp_declare_swizzle4(dswizzle4, 0, 2, 3, 1, rbag);
hlslpp_declare_swizzle4(dswizzle4, 0, 2, 3, 2, rbab);
hlslpp_declare_swizzle4(dswizzle4, 0, 2, 3, 3, rbaa);

hlslpp_declare_swizzle4(dswizzle4, 0, 3, 0, 0, rarr);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 0, 1, rarg);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 0, 2, rarb);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 0, 3, rara);

hlslpp_declare_swizzle4(dswizzle4, 0, 3, 1, 0, ragr);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 1, 1, ragg);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 1, 2, ragb);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 1, 3, raga);

hlslpp_declare_swizzle4(dswizzle4, 0, 3, 2, 0, rabr);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 2, 1, rabg);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 2, 2, rabb);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 2, 3, raba);

hlslpp_declare_swizzle4(dswizzle4, 0, 3, 3, 0, raar);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 3, 1, raag);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 3, 2, raab);
hlslpp_declare_swizzle4(dswizzle4, 0, 3, 3, 3, raaa);

hlslpp_declare_swizzle4(dswizzle4, 1, 0, 0, 3, grra);
hlslpp_declare_swizzle4(dswizzle4, 1, 0, 1, 3, grga);
hlslpp_declare_swizzle4(dswizzle4, 1, 0, 2, 3, grba);

hlslpp_declare_swizzle4(dswizzle4, 1, 0, 3, 0, grar);
hlslpp_declare_swizzle4(dswizzle4, 1, 0, 3, 1, grag);
hlslpp_declare_swizzle4(dswizzle4, 1, 0, 3, 2, grab);
hlslpp_declare_swizzle4(dswizzle4, 1, 0, 3, 3, graa);

hlslpp_declare_swizzle4(dswizzle4, 1, 1, 0, 3, ggra);
hlslpp_declare_swizzle4(dswizzle4, 1, 1, 1, 3, ggga);
hlslpp_declare_swizzle4(dswizzle4, 1, 1, 2, 3, ggba);

hlslpp_declare_swizzle4(dswizzle4, 1, 1, 3, 0, ggar);
hlslpp_declare_swizzle4(dswizzle4, 1, 1, 3, 1, ggag);
hlslpp_declare_swizzle4(dswizzle4, 1, 1, 3, 2, ggab);
hlslpp_declare_swizzle4(dswizzle4, 1, 1, 3, 3, ggaa);

hlslpp_declare_swizzle4(dswizzle4, 1, 2, 0, 3, gbra);
hlslpp_declare_swizzle4(dswizzle4, 1, 2, 1, 3, gbga);
hlslpp_declare_swizzle4(dswizzle4, 1, 2, 2, 3, gbba);

hlslpp_declare_swizzle4(dswizzle4, 1, 2, 3, 0, gbar);
hlslpp_declare_swizzle4(dswizzle4, 1, 2, 3, 1, gbag);
hlslpp_declare_swizzle4(dswizzle4, 1, 2, 3, 2, gbab);
hlslpp_declare_swizzle4(dswizzle4, 1, 2, 3, 3, gbaa);

hlslpp_declare_swizzle4(dswizzle4, 1, 3, 0, 0, garr);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 0, 1, garg);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 0, 2, garb);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 0, 3, gara);

hlslpp_declare_swizzle4(dswizzle4, 1, 3, 1, 0, gagr);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 1, 1, gagg);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 1, 2, gagb);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 1, 3, gaga);

hlslpp_declare_swizzle4(dswizzle4, 1, 3, 2, 0, gabr);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 2, 1, gabg);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 2, 2, gabb);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 2, 3, gaba);

hlslpp_declare_swizzle4(dswizzle4, 1, 3, 3, 0, gaar);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 3, 1, gaag);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 3, 2, gaab);
hlslpp_declare_swizzle4(dswizzle4, 1, 3, 3, 3, gaaa);

hlslpp_declare_swizzle4(dswizzle4, 2, 0, 0, 3, brra);
hlslpp_declare_swizzle4(dswizzle4, 2, 0, 1, 3, brga);
hlslpp_declare_swizzle4(dswizzle4, 2, 0, 2, 3, brba);

hlslpp_declare_swizzle4(dswizzle4, 2, 0, 3, 0, brar);
hlslpp_declare_swizzle4(dswizzle4, 2, 0, 3, 1, brag);
hlslpp_declare_swizzle4(dswizzle4, 2, 0, 3, 2, brab);
hlslpp_declare_swizzle4(dswizzle4, 2, 0, 3, 3, braa);

hlslpp_declare_swizzle4(dswizzle4, 2, 1, 0, 3, bgra);
hlslpp_declare_swizzle4(dswizzle4, 2, 1, 1, 3, bgga);
hlslpp_declare_swizzle4(dswizzle4, 2, 1, 2, 3, bgba);

hlslpp_declare_swizzle4(dswizzle4, 2, 1, 3, 0, bgar);
hlslpp_declare_swizzle4(dswizzle4, 2, 1, 3, 1, bgag);
hlslpp_declare_swizzle4(dswizzle4, 2, 1, 3, 2, bgab);
hlslpp_declare_swizzle4(dswizzle4, 2, 1, 3, 3, bgaa);

hlslpp_declare_swizzle4(dswizzle4, 2, 2, 0, 3, bbra);
hlslpp_declare_swizzle4(dswizzle4, 2, 2, 1, 3, bbga);
hlslpp_declare_swizzle4(dswizzle4, 2, 2, 2, 3, bbba);

hlslpp_declare_swizzle4(dswizzle4, 2, 2, 3, 0, bbar);
hlslpp_declare_swizzle4(dswizzle4, 2, 2, 3, 1, bbag);
hlslpp_declare_swizzle4(dswizzle4, 2, 2, 3, 2, bbab);
hlslpp_declare_swizzle4(dswizzle4, 2, 2, 3, 3, bbaa);

hlslpp_declare_swizzle4(dswizzle4, 2, 3, 0, 0, barr);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 0, 1, barg);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 0, 2, barb);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 0, 3, bara);

hlslpp_declare_swizzle4(dswizzle4, 2, 3, 1, 0, bagr);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 1, 1, bagg);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 1, 2, bagb);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 1, 3, baga);

hlslpp_declare_swizzle4(dswizzle4, 2, 3, 2, 0, babr);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 2, 1, babg);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 2, 2, babb);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 2, 3, baba);

hlslpp_declare_swizzle4(dswizzle4, 2, 3, 3, 0, baar);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 3, 1, baag);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 3, 2, baab);
hlslpp_declare_swizzle4(dswizzle4, 2, 3, 3, 3, baaa);

hlslpp_declare_swizzle4(dswizzle4, 3, 0, 0, 0, arrr);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 0, 1, arrg);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 0, 2, arrb);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 0, 3, arra);

hlslpp_declare_swizzle4(dswizzle4, 3, 0, 1, 0, argr);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 1, 1, argg);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 1, 2, argb);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 1, 3, arga);

hlslpp_declare_swizzle4(dswizzle4, 3, 0, 2, 0, arbr);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 2, 1, arbg);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 2, 2, arbb);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 2, 3, arba);

hlslpp_declare_swizzle4(dswizzle4, 3, 0, 3, 0, arar);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 3, 1, arag);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 3, 2, arab);
hlslpp_declare_swizzle4(dswizzle4, 3, 0, 3, 3, araa);

hlslpp_declare_swizzle4(dswizzle4, 3, 1, 0, 0, agrr);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 0, 1, agrg);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 0, 2, agrb);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 0, 3, agra);

hlslpp_declare_swizzle4(dswizzle4, 3, 1, 1, 0, aggr);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 1, 1, aggg);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 1, 2, aggb);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 1, 3, agga);

hlslpp_declare_swizzle4(dswizzle4, 3, 1, 2, 0, agbr);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 2, 1, agbg);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 2, 2, agbb);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 2, 3, agba);

hlslpp_declare_swizzle4(dswizzle4, 3, 1, 3, 0, agar);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 3, 1, agag);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 3, 2, agab);
hlslpp_declare_swizzle4(dswizzle4, 3, 1, 3, 3, agaa);

hlslpp_declare_swizzle4(dswizzle4, 3, 2, 0, 0, abrr);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 0, 1, abrg);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 0, 2, abrb);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 0, 3, abra);

hlslpp_declare_swizzle4(dswizzle4, 3, 2, 1, 0, abgr);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 1, 1, abgg);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 1, 2, abgb);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 1, 3, abga);

hlslpp_declare_swizzle4(dswizzle4, 3, 2, 2, 0, abbr);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 2, 1, abbg);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 2, 2, abbb);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 2, 3, abba);

hlslpp_declare_swizzle4(dswizzle4, 3, 2, 3, 0, abar);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 3, 1, abag);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 3, 2, abab);
hlslpp_declare_swizzle4(dswizzle4, 3, 2, 3, 3, abaa);

hlslpp_declare_swizzle4(dswizzle4, 3, 3, 0, 0, aarr);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 0, 1, aarg);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 0, 2, aarb);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 0, 3, aara);

hlslpp_declare_swizzle4(dswizzle4, 3, 3, 1, 0, aagr);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 1, 1, aagg);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 1, 2, aagb);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 1, 3, aaga);

hlslpp_declare_swizzle4(dswizzle4, 3, 3, 2, 0, aabr);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 2, 1, aabg);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 2, 2, aabb);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 2, 3, aaba);

hlslpp_declare_swizzle4(dswizzle4, 3, 3, 3, 0, aaar);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 3, 1, aaag);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 3, 2, aaab);
hlslpp_declare_swizzle4(dswizzle4, 3, 3, 3, 3, aaaa);