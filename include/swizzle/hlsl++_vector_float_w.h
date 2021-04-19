// -------------------------------
// XYZW
// -------------------------------

struct { swizzle1<3> w; };

struct { swizzle2<0, 3> xw; };
struct { swizzle2<1, 3> yw; };
struct { swizzle2<2, 3> zw; };
struct { swizzle2<3, 0> wx; };
struct { swizzle2<3, 1> wy; };
struct { swizzle2<3, 2> wz; };
struct { swizzle2<3, 3> ww; };

struct { swizzle3<0, 0, 3> xxw; };
struct { swizzle3<0, 1, 3> xyw; };
struct { swizzle3<0, 2, 3> xzw; };

struct { swizzle3<0, 3, 0> xwx; };
struct { swizzle3<0, 3, 1> xwy; };
struct { swizzle3<0, 3, 2> xwz; };
struct { swizzle3<0, 3, 3> xww; };

struct { swizzle3<1, 0, 3> yxw; };
struct { swizzle3<1, 1, 3> yyw; };
struct { swizzle3<1, 2, 3> yzw; };

struct { swizzle3<1, 3, 0> ywx; };
struct { swizzle3<1, 3, 1> ywy; };
struct { swizzle3<1, 3, 2> ywz; };
struct { swizzle3<1, 3, 3> yww; };

struct { swizzle3<2, 0, 3> zxw; };
struct { swizzle3<2, 1, 3> zyw; };
struct { swizzle3<2, 2, 3> zzw; };

struct { swizzle3<2, 3, 0> zwx; };
struct { swizzle3<2, 3, 1> zwy; };
struct { swizzle3<2, 3, 2> zwz; };
struct { swizzle3<2, 3, 3> zww; };

struct { swizzle3<3, 0, 0> wxx; };
struct { swizzle3<3, 0, 1> wxy; };
struct { swizzle3<3, 0, 2> wxz; };
struct { swizzle3<3, 0, 3> wxw; };

struct { swizzle3<3, 1, 0> wyx; };
struct { swizzle3<3, 1, 1> wyy; };
struct { swizzle3<3, 1, 2> wyz; };
struct { swizzle3<3, 1, 3> wyw; };

struct { swizzle3<3, 2, 0> wzx; };
struct { swizzle3<3, 2, 1> wzy; };
struct { swizzle3<3, 2, 2> wzz; };
struct { swizzle3<3, 2, 3> wzw; };

struct { swizzle3<3, 3, 0> wwx; };
struct { swizzle3<3, 3, 1> wwy; };
struct { swizzle3<3, 3, 2> wwz; };
struct { swizzle3<3, 3, 3> www; };

struct { swizzle4<0, 0, 0, 3> xxxw; };
struct { swizzle4<0, 0, 1, 3> xxyw; };
struct { swizzle4<0, 0, 2, 3> xxzw; };

struct { swizzle4<0, 0, 3, 0> xxwx; };
struct { swizzle4<0, 0, 3, 1> xxwy; };
struct { swizzle4<0, 0, 3, 2> xxwz; };
struct { swizzle4<0, 0, 3, 3> xxww; };

struct { swizzle4<0, 1, 0, 3> xyxw; };
struct { swizzle4<0, 1, 1, 3> xyyw; };
struct { swizzle4<0, 1, 2, 3> xyzw; };

struct { swizzle4<0, 1, 3, 0> xywx; };
struct { swizzle4<0, 1, 3, 1> xywy; };
struct { swizzle4<0, 1, 3, 2> xywz; };
struct { swizzle4<0, 1, 3, 3> xyww; };

struct { swizzle4<0, 2, 0, 3> xzxw; };
struct { swizzle4<0, 2, 1, 3> xzyw; };
struct { swizzle4<0, 2, 2, 3> xzzw; };

struct { swizzle4<0, 2, 3, 0> xzwx; };
struct { swizzle4<0, 2, 3, 1> xzwy; };
struct { swizzle4<0, 2, 3, 2> xzwz; };
struct { swizzle4<0, 2, 3, 3> xzww; };

struct { swizzle4<0, 3, 0, 0> xwxx; };
struct { swizzle4<0, 3, 0, 1> xwxy; };
struct { swizzle4<0, 3, 0, 2> xwxz; };
struct { swizzle4<0, 3, 0, 3> xwxw; };

struct { swizzle4<0, 3, 1, 0> xwyx; };
struct { swizzle4<0, 3, 1, 1> xwyy; };
struct { swizzle4<0, 3, 1, 2> xwyz; };
struct { swizzle4<0, 3, 1, 3> xwyw; };

struct { swizzle4<0, 3, 2, 0> xwzx; };
struct { swizzle4<0, 3, 2, 1> xwzy; };
struct { swizzle4<0, 3, 2, 2> xwzz; };
struct { swizzle4<0, 3, 2, 3> xwzw; };

struct { swizzle4<0, 3, 3, 0> xwwx; };
struct { swizzle4<0, 3, 3, 1> xwwy; };
struct { swizzle4<0, 3, 3, 2> xwwz; };
struct { swizzle4<0, 3, 3, 3> xwww; };

struct { swizzle4<1, 0, 0, 3> yxxw; };
struct { swizzle4<1, 0, 1, 3> yxyw; };
struct { swizzle4<1, 0, 2, 3> yxzw; };

struct { swizzle4<1, 0, 3, 0> yxwx; };
struct { swizzle4<1, 0, 3, 1> yxwy; };
struct { swizzle4<1, 0, 3, 2> yxwz; };
struct { swizzle4<1, 0, 3, 3> yxww; };

struct { swizzle4<1, 1, 0, 3> yyxw; };
struct { swizzle4<1, 1, 1, 3> yyyw; };
struct { swizzle4<1, 1, 2, 3> yyzw; };

struct { swizzle4<1, 1, 3, 0> yywx; };
struct { swizzle4<1, 1, 3, 1> yywy; };
struct { swizzle4<1, 1, 3, 2> yywz; };
struct { swizzle4<1, 1, 3, 3> yyww; };

struct { swizzle4<1, 2, 0, 3> yzxw; };
struct { swizzle4<1, 2, 1, 3> yzyw; };
struct { swizzle4<1, 2, 2, 3> yzzw; };

struct { swizzle4<1, 2, 3, 0> yzwx; };
struct { swizzle4<1, 2, 3, 1> yzwy; };
struct { swizzle4<1, 2, 3, 2> yzwz; };
struct { swizzle4<1, 2, 3, 3> yzww; };

struct { swizzle4<1, 3, 0, 0> ywxx; };
struct { swizzle4<1, 3, 0, 1> ywxy; };
struct { swizzle4<1, 3, 0, 2> ywxz; };
struct { swizzle4<1, 3, 0, 3> ywxw; };

struct { swizzle4<1, 3, 1, 0> ywyx; };
struct { swizzle4<1, 3, 1, 1> ywyy; };
struct { swizzle4<1, 3, 1, 2> ywyz; };
struct { swizzle4<1, 3, 1, 3> ywyw; };

struct { swizzle4<1, 3, 2, 0> ywzx; };
struct { swizzle4<1, 3, 2, 1> ywzy; };
struct { swizzle4<1, 3, 2, 2> ywzz; };
struct { swizzle4<1, 3, 2, 3> ywzw; };

struct { swizzle4<1, 3, 3, 0> ywwx; };
struct { swizzle4<1, 3, 3, 1> ywwy; };
struct { swizzle4<1, 3, 3, 2> ywwz; };
struct { swizzle4<1, 3, 3, 3> ywww; };

struct { swizzle4<2, 0, 0, 3> zxxw; };
struct { swizzle4<2, 0, 1, 3> zxyw; };
struct { swizzle4<2, 0, 2, 3> zxzw; };

struct { swizzle4<2, 0, 3, 0> zxwx; };
struct { swizzle4<2, 0, 3, 1> zxwy; };
struct { swizzle4<2, 0, 3, 2> zxwz; };
struct { swizzle4<2, 0, 3, 3> zxww; };

struct { swizzle4<2, 1, 0, 3> zyxw; };
struct { swizzle4<2, 1, 1, 3> zyyw; };
struct { swizzle4<2, 1, 2, 3> zyzw; };

struct { swizzle4<2, 1, 3, 0> zywx; };
struct { swizzle4<2, 1, 3, 1> zywy; };
struct { swizzle4<2, 1, 3, 2> zywz; };
struct { swizzle4<2, 1, 3, 3> zyww; };

struct { swizzle4<2, 2, 0, 3> zzxw; };
struct { swizzle4<2, 2, 1, 3> zzyw; };
struct { swizzle4<2, 2, 2, 3> zzzw; };

struct { swizzle4<2, 2, 3, 0> zzwx; };
struct { swizzle4<2, 2, 3, 1> zzwy; };
struct { swizzle4<2, 2, 3, 2> zzwz; };
struct { swizzle4<2, 2, 3, 3> zzww; };

struct { swizzle4<2, 3, 0, 0> zwxx; };
struct { swizzle4<2, 3, 0, 1> zwxy; };
struct { swizzle4<2, 3, 0, 2> zwxz; };
struct { swizzle4<2, 3, 0, 3> zwxw; };

struct { swizzle4<2, 3, 1, 0> zwyx; };
struct { swizzle4<2, 3, 1, 1> zwyy; };
struct { swizzle4<2, 3, 1, 2> zwyz; };
struct { swizzle4<2, 3, 1, 3> zwyw; };

struct { swizzle4<2, 3, 2, 0> zwzx; };
struct { swizzle4<2, 3, 2, 1> zwzy; };
struct { swizzle4<2, 3, 2, 2> zwzz; };
struct { swizzle4<2, 3, 2, 3> zwzw; };

struct { swizzle4<2, 3, 3, 0> zwwx; };
struct { swizzle4<2, 3, 3, 1> zwwy; };
struct { swizzle4<2, 3, 3, 2> zwwz; };
struct { swizzle4<2, 3, 3, 3> zwww; };

struct { swizzle4<3, 0, 0, 0> wxxx; };
struct { swizzle4<3, 0, 0, 1> wxxy; };
struct { swizzle4<3, 0, 0, 2> wxxz; };
struct { swizzle4<3, 0, 0, 3> wxxw; };

struct { swizzle4<3, 0, 1, 0> wxyx; };
struct { swizzle4<3, 0, 1, 1> wxyy; };
struct { swizzle4<3, 0, 1, 2> wxyz; };
struct { swizzle4<3, 0, 1, 3> wxyw; };

struct { swizzle4<3, 0, 2, 0> wxzx; };
struct { swizzle4<3, 0, 2, 1> wxzy; };
struct { swizzle4<3, 0, 2, 2> wxzz; };
struct { swizzle4<3, 0, 2, 3> wxzw; };

struct { swizzle4<3, 0, 3, 0> wxwx; };
struct { swizzle4<3, 0, 3, 1> wxwy; };
struct { swizzle4<3, 0, 3, 2> wxwz; };
struct { swizzle4<3, 0, 3, 3> wxww; };

struct { swizzle4<3, 1, 0, 0> wyxx; };
struct { swizzle4<3, 1, 0, 1> wyxy; };
struct { swizzle4<3, 1, 0, 2> wyxz; };
struct { swizzle4<3, 1, 0, 3> wyxw; };

struct { swizzle4<3, 1, 1, 0> wyyx; };
struct { swizzle4<3, 1, 1, 1> wyyy; };
struct { swizzle4<3, 1, 1, 2> wyyz; };
struct { swizzle4<3, 1, 1, 3> wyyw; };

struct { swizzle4<3, 1, 2, 0> wyzx; };
struct { swizzle4<3, 1, 2, 1> wyzy; };
struct { swizzle4<3, 1, 2, 2> wyzz; };
struct { swizzle4<3, 1, 2, 3> wyzw; };

struct { swizzle4<3, 1, 3, 0> wywx; };
struct { swizzle4<3, 1, 3, 1> wywy; };
struct { swizzle4<3, 1, 3, 2> wywz; };
struct { swizzle4<3, 1, 3, 3> wyww; };

struct { swizzle4<3, 2, 0, 0> wzxx; };
struct { swizzle4<3, 2, 0, 1> wzxy; };
struct { swizzle4<3, 2, 0, 2> wzxz; };
struct { swizzle4<3, 2, 0, 3> wzxw; };

struct { swizzle4<3, 2, 1, 0> wzyx; };
struct { swizzle4<3, 2, 1, 1> wzyy; };
struct { swizzle4<3, 2, 1, 2> wzyz; };
struct { swizzle4<3, 2, 1, 3> wzyw; };

struct { swizzle4<3, 2, 2, 0> wzzx; };
struct { swizzle4<3, 2, 2, 1> wzzy; };
struct { swizzle4<3, 2, 2, 2> wzzz; };
struct { swizzle4<3, 2, 2, 3> wzzw; };

struct { swizzle4<3, 2, 3, 0> wzwx; };
struct { swizzle4<3, 2, 3, 1> wzwy; };
struct { swizzle4<3, 2, 3, 2> wzwz; };
struct { swizzle4<3, 2, 3, 3> wzww; };

struct { swizzle4<3, 3, 0, 0> wwxx; };
struct { swizzle4<3, 3, 0, 1> wwxy; };
struct { swizzle4<3, 3, 0, 2> wwxz; };
struct { swizzle4<3, 3, 0, 3> wwxw; };

struct { swizzle4<3, 3, 1, 0> wwyx; };
struct { swizzle4<3, 3, 1, 1> wwyy; };
struct { swizzle4<3, 3, 1, 2> wwyz; };
struct { swizzle4<3, 3, 1, 3> wwyw; };

struct { swizzle4<3, 3, 2, 0> wwzx; };
struct { swizzle4<3, 3, 2, 1> wwzy; };
struct { swizzle4<3, 3, 2, 2> wwzz; };
struct { swizzle4<3, 3, 2, 3> wwzw; };

struct { swizzle4<3, 3, 3, 0> wwwx; };
struct { swizzle4<3, 3, 3, 1> wwwy; };
struct { swizzle4<3, 3, 3, 2> wwwz; };
struct { swizzle4<3, 3, 3, 3> wwww; };

// -------------------------------
// RGBA
// -------------------------------

struct { swizzle1<3> a; };

struct { swizzle2<0, 3> ra; };
struct { swizzle2<1, 3> ga; };
struct { swizzle2<2, 3> ba; };
struct { swizzle2<3, 0> ar; };
struct { swizzle2<3, 1> ag; };
struct { swizzle2<3, 2> ab; };
struct { swizzle2<3, 3> aa; };

struct { swizzle3<0, 0, 3> rra; };
struct { swizzle3<0, 1, 3> rga; };
struct { swizzle3<0, 2, 3> rba; };

struct { swizzle3<0, 3, 0> rar; };
struct { swizzle3<0, 3, 1> rag; };
struct { swizzle3<0, 3, 2> rab; };
struct { swizzle3<0, 3, 3> raa; };

struct { swizzle3<1, 0, 3> gra; };
struct { swizzle3<1, 1, 3> gga; };
struct { swizzle3<1, 2, 3> gba; };

struct { swizzle3<1, 3, 0> gar; };
struct { swizzle3<1, 3, 1> gag; };
struct { swizzle3<1, 3, 2> gab; };
struct { swizzle3<1, 3, 3> gaa; };

struct { swizzle3<2, 0, 3> bra; };
struct { swizzle3<2, 1, 3> bga; };
struct { swizzle3<2, 2, 3> bba; };

struct { swizzle3<2, 3, 0> bar; };
struct { swizzle3<2, 3, 1> bag; };
struct { swizzle3<2, 3, 2> bab; };
struct { swizzle3<2, 3, 3> baa; };

struct { swizzle3<3, 0, 0> arr; };
struct { swizzle3<3, 0, 1> arg; };
struct { swizzle3<3, 0, 2> arb; };
struct { swizzle3<3, 0, 3> ara; };

struct { swizzle3<3, 1, 0> agr; };
struct { swizzle3<3, 1, 1> agg; };
struct { swizzle3<3, 1, 2> agb; };
struct { swizzle3<3, 1, 3> aga; };

struct { swizzle3<3, 2, 0> abr; };
struct { swizzle3<3, 2, 1> abg; };
struct { swizzle3<3, 2, 2> abb; };
struct { swizzle3<3, 2, 3> aba; };

struct { swizzle3<3, 3, 0> aar; };
struct { swizzle3<3, 3, 1> aag; };
struct { swizzle3<3, 3, 2> aab; };
struct { swizzle3<3, 3, 3> aaa; };

struct { swizzle4<0, 0, 0, 3> rrra; };
struct { swizzle4<0, 0, 1, 3> rrga; };
struct { swizzle4<0, 0, 2, 3> rrba; };

struct { swizzle4<0, 0, 3, 0> rrar; };
struct { swizzle4<0, 0, 3, 1> rrag; };
struct { swizzle4<0, 0, 3, 2> rrab; };
struct { swizzle4<0, 0, 3, 3> rraa; };

struct { swizzle4<0, 1, 0, 3> rgra; };
struct { swizzle4<0, 1, 1, 3> rgga; };
struct { swizzle4<0, 1, 2, 3> rgba; };

struct { swizzle4<0, 1, 3, 0> rgar; };
struct { swizzle4<0, 1, 3, 1> rgag; };
struct { swizzle4<0, 1, 3, 2> rgab; };
struct { swizzle4<0, 1, 3, 3> rgaa; };

struct { swizzle4<0, 2, 0, 3> rbra; };
struct { swizzle4<0, 2, 1, 3> rbga; };
struct { swizzle4<0, 2, 2, 3> rbba; };

struct { swizzle4<0, 2, 3, 0> rbar; };
struct { swizzle4<0, 2, 3, 1> rbag; };
struct { swizzle4<0, 2, 3, 2> rbab; };
struct { swizzle4<0, 2, 3, 3> rbaa; };

struct { swizzle4<0, 3, 0, 0> rarr; };
struct { swizzle4<0, 3, 0, 1> rarg; };
struct { swizzle4<0, 3, 0, 2> rarb; };
struct { swizzle4<0, 3, 0, 3> rara; };

struct { swizzle4<0, 3, 1, 0> ragr; };
struct { swizzle4<0, 3, 1, 1> ragg; };
struct { swizzle4<0, 3, 1, 2> ragb; };
struct { swizzle4<0, 3, 1, 3> raga; };

struct { swizzle4<0, 3, 2, 0> rabr; };
struct { swizzle4<0, 3, 2, 1> rabg; };
struct { swizzle4<0, 3, 2, 2> rabb; };
struct { swizzle4<0, 3, 2, 3> raba; };

struct { swizzle4<0, 3, 3, 0> raar; };
struct { swizzle4<0, 3, 3, 1> raag; };
struct { swizzle4<0, 3, 3, 2> raab; };
struct { swizzle4<0, 3, 3, 3> raaa; };

struct { swizzle4<1, 0, 0, 3> grra; };
struct { swizzle4<1, 0, 1, 3> grga; };
struct { swizzle4<1, 0, 2, 3> grba; };

struct { swizzle4<1, 0, 3, 0> grar; };
struct { swizzle4<1, 0, 3, 1> grag; };
struct { swizzle4<1, 0, 3, 2> grab; };
struct { swizzle4<1, 0, 3, 3> graa; };

struct { swizzle4<1, 1, 0, 3> ggra; };
struct { swizzle4<1, 1, 1, 3> ggga; };
struct { swizzle4<1, 1, 2, 3> ggba; };

struct { swizzle4<1, 1, 3, 0> ggar; };
struct { swizzle4<1, 1, 3, 1> ggag; };
struct { swizzle4<1, 1, 3, 2> ggab; };
struct { swizzle4<1, 1, 3, 3> ggaa; };

struct { swizzle4<1, 2, 0, 3> gbra; };
struct { swizzle4<1, 2, 1, 3> gbga; };
struct { swizzle4<1, 2, 2, 3> gbba; };

struct { swizzle4<1, 2, 3, 0> gbar; };
struct { swizzle4<1, 2, 3, 1> gbag; };
struct { swizzle4<1, 2, 3, 2> gbab; };
struct { swizzle4<1, 2, 3, 3> gbaa; };

struct { swizzle4<1, 3, 0, 0> garr; };
struct { swizzle4<1, 3, 0, 1> garg; };
struct { swizzle4<1, 3, 0, 2> garb; };
struct { swizzle4<1, 3, 0, 3> gara; };

struct { swizzle4<1, 3, 1, 0> gagr; };
struct { swizzle4<1, 3, 1, 1> gagg; };
struct { swizzle4<1, 3, 1, 2> gagb; };
struct { swizzle4<1, 3, 1, 3> gaga; };

struct { swizzle4<1, 3, 2, 0> gabr; };
struct { swizzle4<1, 3, 2, 1> gabg; };
struct { swizzle4<1, 3, 2, 2> gabb; };
struct { swizzle4<1, 3, 2, 3> gaba; };

struct { swizzle4<1, 3, 3, 0> gaar; };
struct { swizzle4<1, 3, 3, 1> gaag; };
struct { swizzle4<1, 3, 3, 2> gaab; };
struct { swizzle4<1, 3, 3, 3> gaaa; };

struct { swizzle4<2, 0, 0, 3> brra; };
struct { swizzle4<2, 0, 1, 3> brga; };
struct { swizzle4<2, 0, 2, 3> brba; };

struct { swizzle4<2, 0, 3, 0> brar; };
struct { swizzle4<2, 0, 3, 1> brag; };
struct { swizzle4<2, 0, 3, 2> brab; };
struct { swizzle4<2, 0, 3, 3> braa; };

struct { swizzle4<2, 1, 0, 3> bgra; };
struct { swizzle4<2, 1, 1, 3> bgga; };
struct { swizzle4<2, 1, 2, 3> bgba; };

struct { swizzle4<2, 1, 3, 0> bgar; };
struct { swizzle4<2, 1, 3, 1> bgag; };
struct { swizzle4<2, 1, 3, 2> bgab; };
struct { swizzle4<2, 1, 3, 3> bgaa; };

struct { swizzle4<2, 2, 0, 3> bbra; };
struct { swizzle4<2, 2, 1, 3> bbga; };
struct { swizzle4<2, 2, 2, 3> bbba; };

struct { swizzle4<2, 2, 3, 0> bbar; };
struct { swizzle4<2, 2, 3, 1> bbag; };
struct { swizzle4<2, 2, 3, 2> bbab; };
struct { swizzle4<2, 2, 3, 3> bbaa; };

struct { swizzle4<2, 3, 0, 0> barr; };
struct { swizzle4<2, 3, 0, 1> barg; };
struct { swizzle4<2, 3, 0, 2> barb; };
struct { swizzle4<2, 3, 0, 3> bara; };

struct { swizzle4<2, 3, 1, 0> bagr; };
struct { swizzle4<2, 3, 1, 1> bagg; };
struct { swizzle4<2, 3, 1, 2> bagb; };
struct { swizzle4<2, 3, 1, 3> baga; };

struct { swizzle4<2, 3, 2, 0> babr; };
struct { swizzle4<2, 3, 2, 1> babg; };
struct { swizzle4<2, 3, 2, 2> babb; };
struct { swizzle4<2, 3, 2, 3> baba; };

struct { swizzle4<2, 3, 3, 0> baar; };
struct { swizzle4<2, 3, 3, 1> baag; };
struct { swizzle4<2, 3, 3, 2> baab; };
struct { swizzle4<2, 3, 3, 3> baaa; };

struct { swizzle4<3, 0, 0, 0> arrr; };
struct { swizzle4<3, 0, 0, 1> arrg; };
struct { swizzle4<3, 0, 0, 2> arrb; };
struct { swizzle4<3, 0, 0, 3> arra; };

struct { swizzle4<3, 0, 1, 0> argr; };
struct { swizzle4<3, 0, 1, 1> argg; };
struct { swizzle4<3, 0, 1, 2> argb; };
struct { swizzle4<3, 0, 1, 3> arga; };

struct { swizzle4<3, 0, 2, 0> arbr; };
struct { swizzle4<3, 0, 2, 1> arbg; };
struct { swizzle4<3, 0, 2, 2> arbb; };
struct { swizzle4<3, 0, 2, 3> arba; };

struct { swizzle4<3, 0, 3, 0> arar; };
struct { swizzle4<3, 0, 3, 1> arag; };
struct { swizzle4<3, 0, 3, 2> arab; };
struct { swizzle4<3, 0, 3, 3> araa; };

struct { swizzle4<3, 1, 0, 0> agrr; };
struct { swizzle4<3, 1, 0, 1> agrg; };
struct { swizzle4<3, 1, 0, 2> agrb; };
struct { swizzle4<3, 1, 0, 3> agra; };

struct { swizzle4<3, 1, 1, 0> aggr; };
struct { swizzle4<3, 1, 1, 1> aggg; };
struct { swizzle4<3, 1, 1, 2> aggb; };
struct { swizzle4<3, 1, 1, 3> agga; };

struct { swizzle4<3, 1, 2, 0> agbr; };
struct { swizzle4<3, 1, 2, 1> agbg; };
struct { swizzle4<3, 1, 2, 2> agbb; };
struct { swizzle4<3, 1, 2, 3> agba; };

struct { swizzle4<3, 1, 3, 0> agar; };
struct { swizzle4<3, 1, 3, 1> agag; };
struct { swizzle4<3, 1, 3, 2> agab; };
struct { swizzle4<3, 1, 3, 3> agaa; };

struct { swizzle4<3, 2, 0, 0> abrr; };
struct { swizzle4<3, 2, 0, 1> abrg; };
struct { swizzle4<3, 2, 0, 2> abrb; };
struct { swizzle4<3, 2, 0, 3> abra; };

struct { swizzle4<3, 2, 1, 0> abgr; };
struct { swizzle4<3, 2, 1, 1> abgg; };
struct { swizzle4<3, 2, 1, 2> abgb; };
struct { swizzle4<3, 2, 1, 3> abga; };

struct { swizzle4<3, 2, 2, 0> abbr; };
struct { swizzle4<3, 2, 2, 1> abbg; };
struct { swizzle4<3, 2, 2, 2> abbb; };
struct { swizzle4<3, 2, 2, 3> abba; };

struct { swizzle4<3, 2, 3, 0> abar; };
struct { swizzle4<3, 2, 3, 1> abag; };
struct { swizzle4<3, 2, 3, 2> abab; };
struct { swizzle4<3, 2, 3, 3> abaa; };

struct { swizzle4<3, 3, 0, 0> aarr; };
struct { swizzle4<3, 3, 0, 1> aarg; };
struct { swizzle4<3, 3, 0, 2> aarb; };
struct { swizzle4<3, 3, 0, 3> aara; };

struct { swizzle4<3, 3, 1, 0> aagr; };
struct { swizzle4<3, 3, 1, 1> aagg; };
struct { swizzle4<3, 3, 1, 2> aagb; };
struct { swizzle4<3, 3, 1, 3> aaga; };

struct { swizzle4<3, 3, 2, 0> aabr; };
struct { swizzle4<3, 3, 2, 1> aabg; };
struct { swizzle4<3, 3, 2, 2> aabb; };
struct { swizzle4<3, 3, 2, 3> aaba; };

struct { swizzle4<3, 3, 3, 0> aaar; };
struct { swizzle4<3, 3, 3, 1> aaag; };
struct { swizzle4<3, 3, 3, 2> aaab; };
struct { swizzle4<3, 3, 3, 3> aaaa; };