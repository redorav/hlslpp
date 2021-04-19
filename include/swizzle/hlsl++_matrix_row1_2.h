// -------------------------------
// _mNM
// -------------------------------

struct { swizzle1<1> _m11; };

struct { swizzle2<0, 1> _m10_m11; };
struct { swizzle2<1, 0> _m11_m10; };
struct { swizzle2<1, 1> _m11_m11; };

struct { swizzle3<0, 0, 1> _m10_m10_m11; };
struct { swizzle3<0, 1, 0> _m10_m11_m10; };
struct { swizzle3<0, 1, 1> _m10_m11_m11; };

struct { swizzle3<1, 0, 0> _m11_m10_m10; };
struct { swizzle3<1, 0, 1> _m11_m10_m11; };
struct { swizzle3<1, 1, 0> _m11_m11_m10; };
struct { swizzle3<1, 1, 1> _m11_m11_m11; };

struct { swizzle4<0, 0, 0, 1> _m10_m10_m10_m11; };

struct { swizzle4<0, 0, 1, 0> _m10_m10_m11_m10; };
struct { swizzle4<0, 0, 1, 1> _m10_m10_m11_m11; };

struct { swizzle4<0, 1, 0, 0> _m10_m11_m10_m10; };
struct { swizzle4<0, 1, 0, 1> _m10_m11_m10_m11; };

struct { swizzle4<0, 1, 1, 0> _m10_m11_m11_m10; };
struct { swizzle4<0, 1, 1, 1> _m10_m11_m11_m11; };

struct { swizzle4<1, 0, 0, 0> _m11_m10_m10_m10; };
struct { swizzle4<1, 0, 0, 1> _m11_m10_m10_m11; };

struct { swizzle4<1, 0, 1, 0> _m11_m10_m11_m10; };
struct { swizzle4<1, 0, 1, 1> _m11_m10_m11_m11; };

struct { swizzle4<1, 1, 0, 0> _m11_m11_m10_m10; };
struct { swizzle4<1, 1, 0, 1> _m11_m11_m10_m11; };

struct { swizzle4<1, 1, 1, 0> _m11_m11_m11_m10; };
struct { swizzle4<1, 1, 1, 1> _m11_m11_m11_m11; };

// -------------------------------
// _NM
// -------------------------------

struct { swizzle1<1> _22; };

struct { swizzle2<0, 1> _21_22; };
struct { swizzle2<1, 0> _22_21; };
struct { swizzle2<1, 1> _22_22; };

struct { swizzle3<0, 0, 1> _21_21_22; };
struct { swizzle3<0, 1, 0> _21_22_21; };
struct { swizzle3<0, 1, 1> _21_22_22; };

struct { swizzle3<1, 0, 0> _22_21_21; };
struct { swizzle3<1, 0, 1> _22_21_22; };
struct { swizzle3<1, 1, 0> _22_22_21; };
struct { swizzle3<1, 1, 1> _22_22_22; };

struct { swizzle4<0, 0, 0, 1> _21_21_21_22; };

struct { swizzle4<0, 0, 1, 0> _21_21_22_21; };
struct { swizzle4<0, 0, 1, 1> _21_21_22_22; };

struct { swizzle4<0, 1, 0, 0> _21_22_21_21; };
struct { swizzle4<0, 1, 0, 1> _21_22_21_22; };

struct { swizzle4<0, 1, 1, 0> _21_22_22_21; };
struct { swizzle4<0, 1, 1, 1> _21_22_22_22; };

struct { swizzle4<1, 0, 0, 0> _22_21_21_21; };
struct { swizzle4<1, 0, 0, 1> _22_21_21_22; };

struct { swizzle4<1, 0, 1, 0> _22_21_22_21; };
struct { swizzle4<1, 0, 1, 1> _22_21_22_22; };

struct { swizzle4<1, 1, 0, 0> _22_22_21_21; };
struct { swizzle4<1, 1, 0, 1> _22_22_21_22; };

struct { swizzle4<1, 1, 1, 0> _22_22_22_21; };
struct { swizzle4<1, 1, 1, 1> _22_22_22_22; };