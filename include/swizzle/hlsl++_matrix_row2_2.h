// -------------------------------
// _mNM
// -------------------------------

struct { swizzle1<1> _m21; };

struct { swizzle2<0, 1> _m20_m21; };
struct { swizzle2<1, 0> _m21_m20; };
struct { swizzle2<1, 1> _m21_m21; };

struct { swizzle3<0, 0, 1> _m20_m20_m21; };
struct { swizzle3<0, 1, 0> _m20_m21_m20; };
struct { swizzle3<0, 1, 1> _m20_m21_m21; };

struct { swizzle3<1, 0, 0> _m21_m20_m20; };
struct { swizzle3<1, 0, 1> _m21_m20_m21; };
struct { swizzle3<1, 1, 0> _m21_m21_m20; };
struct { swizzle3<1, 1, 1> _m21_m21_m21; };

struct { swizzle4<0, 0, 0, 1> _m20_m20_m20_m21; };

struct { swizzle4<0, 0, 1, 0> _m20_m20_m21_m20; };
struct { swizzle4<0, 0, 1, 1> _m20_m20_m21_m21; };

struct { swizzle4<0, 1, 0, 0> _m20_m21_m20_m20; };
struct { swizzle4<0, 1, 0, 1> _m20_m21_m20_m21; };

struct { swizzle4<0, 1, 1, 0> _m20_m21_m21_m20; };
struct { swizzle4<0, 1, 1, 1> _m20_m21_m21_m21; };

struct { swizzle4<1, 0, 0, 0> _m21_m20_m20_m20; };
struct { swizzle4<1, 0, 0, 1> _m21_m20_m20_m21; };

struct { swizzle4<1, 0, 1, 0> _m21_m20_m21_m20; };
struct { swizzle4<1, 0, 1, 1> _m21_m20_m21_m21; };

struct { swizzle4<1, 1, 0, 0> _m21_m21_m20_m20; };
struct { swizzle4<1, 1, 0, 1> _m21_m21_m20_m21; };

struct { swizzle4<1, 1, 1, 0> _m21_m21_m21_m20; };
struct { swizzle4<1, 1, 1, 1> _m21_m21_m21_m21; };

// -------------------------------
// _NM
// -------------------------------

struct { swizzle1<1> _32; };

struct { swizzle2<0, 1> _31_32; };
struct { swizzle2<1, 0> _32_31; };
struct { swizzle2<1, 1> _32_32; };

struct { swizzle3<0, 0, 1> _31_31_32; };
struct { swizzle3<0, 1, 0> _31_32_31; };
struct { swizzle3<0, 1, 1> _31_32_32; };

struct { swizzle3<1, 0, 0> _32_31_31; };
struct { swizzle3<1, 0, 1> _32_31_32; };
struct { swizzle3<1, 1, 0> _32_32_31; };
struct { swizzle3<1, 1, 1> _32_32_32; };

struct { swizzle4<0, 0, 0, 1> _31_31_31_32; };

struct { swizzle4<0, 0, 1, 0> _31_31_32_31; };
struct { swizzle4<0, 0, 1, 1> _31_31_32_32; };

struct { swizzle4<0, 1, 0, 0> _31_32_31_31; };
struct { swizzle4<0, 1, 0, 1> _31_32_31_32; };

struct { swizzle4<0, 1, 1, 0> _31_32_32_31; };
struct { swizzle4<0, 1, 1, 1> _31_32_32_32; };

struct { swizzle4<1, 0, 0, 0> _32_31_31_31; };
struct { swizzle4<1, 0, 0, 1> _32_31_31_32; };

struct { swizzle4<1, 0, 1, 0> _32_31_32_31; };
struct { swizzle4<1, 0, 1, 1> _32_31_32_32; };

struct { swizzle4<1, 1, 0, 0> _32_32_31_31; };
struct { swizzle4<1, 1, 0, 1> _32_32_31_32; };

struct { swizzle4<1, 1, 1, 0> _32_32_32_31; };
struct { swizzle4<1, 1, 1, 1> _32_32_32_32; };