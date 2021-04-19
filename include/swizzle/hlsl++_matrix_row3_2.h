// -------------------------------
// _mNM
// -------------------------------

struct { swizzle1<1> _m31; };

struct { swizzle2<0, 1> _m30_m31; };
struct { swizzle2<1, 0> _m31_m30; };
struct { swizzle2<1, 1> _m31_m31; };

struct { swizzle3<0, 0, 1> _m30_m30_m31; };
struct { swizzle3<0, 1, 0> _m30_m31_m30; };
struct { swizzle3<0, 1, 1> _m30_m31_m31; };

struct { swizzle3<1, 0, 0> _m31_m30_m30; };
struct { swizzle3<1, 0, 1> _m31_m30_m31; };
struct { swizzle3<1, 1, 0> _m31_m31_m30; };
struct { swizzle3<1, 1, 1> _m31_m31_m31; };

struct { swizzle4<0, 0, 0, 1> _m30_m30_m30_m31; };

struct { swizzle4<0, 0, 1, 0> _m30_m30_m31_m30; };
struct { swizzle4<0, 0, 1, 1> _m30_m30_m31_m31; };

struct { swizzle4<0, 1, 0, 0> _m30_m31_m30_m30; };
struct { swizzle4<0, 1, 0, 1> _m30_m31_m30_m31; };

struct { swizzle4<0, 1, 1, 0> _m30_m31_m31_m30; };
struct { swizzle4<0, 1, 1, 1> _m30_m31_m31_m31; };

struct { swizzle4<1, 0, 0, 0> _m31_m30_m30_m30; };
struct { swizzle4<1, 0, 0, 1> _m31_m30_m30_m31; };

struct { swizzle4<1, 0, 1, 0> _m31_m30_m31_m30; };
struct { swizzle4<1, 0, 1, 1> _m31_m30_m31_m31; };

struct { swizzle4<1, 1, 0, 0> _m31_m31_m30_m30; };
struct { swizzle4<1, 1, 0, 1> _m31_m31_m30_m31; };

struct { swizzle4<1, 1, 1, 0> _m31_m31_m31_m30; };
struct { swizzle4<1, 1, 1, 1> _m31_m31_m31_m31; };

// -------------------------------
// _NM
// -------------------------------

struct { swizzle1<1> _42; };

struct { swizzle2<0, 1> _41_42; };
struct { swizzle2<1, 0> _42_41; };
struct { swizzle2<1, 1> _42_42; };

struct { swizzle3<0, 0, 1> _41_41_42; };
struct { swizzle3<0, 1, 0> _41_42_41; };
struct { swizzle3<0, 1, 1> _41_42_42; };

struct { swizzle3<1, 0, 0> _42_41_41; };
struct { swizzle3<1, 0, 1> _42_41_42; };
struct { swizzle3<1, 1, 0> _42_42_41; };
struct { swizzle3<1, 1, 1> _42_42_42; };

struct { swizzle4<0, 0, 0, 1> _41_41_41_42; };

struct { swizzle4<0, 0, 1, 0> _41_41_42_41; };
struct { swizzle4<0, 0, 1, 1> _41_41_42_42; };

struct { swizzle4<0, 1, 0, 0> _41_42_41_41; };
struct { swizzle4<0, 1, 0, 1> _41_42_41_42; };

struct { swizzle4<0, 1, 1, 0> _41_42_42_41; };
struct { swizzle4<0, 1, 1, 1> _41_42_42_42; };

struct { swizzle4<1, 0, 0, 0> _42_41_41_41; };
struct { swizzle4<1, 0, 0, 1> _42_41_41_42; };

struct { swizzle4<1, 0, 1, 0> _42_41_42_41; };
struct { swizzle4<1, 0, 1, 1> _42_41_42_42; };

struct { swizzle4<1, 1, 0, 0> _42_42_41_41; };
struct { swizzle4<1, 1, 0, 1> _42_42_41_42; };

struct { swizzle4<1, 1, 1, 0> _42_42_42_41; };
struct { swizzle4<1, 1, 1, 1> _42_42_42_42; };