// -------------------------------
// _mNM
// -------------------------------

struct { swizzle1<1> _m01; };

struct { swizzle2<0, 1> _m00_m01; };
struct { swizzle2<1, 0> _m01_m00; };
struct { swizzle2<1, 1> _m01_m01; };

struct { swizzle3<0, 0, 1> _m00_m00_m01; };
struct { swizzle3<0, 1, 0> _m00_m01_m00; };
struct { swizzle3<0, 1, 1> _m00_m01_m01; };

struct { swizzle3<1, 0, 0> _m01_m00_m00; };
struct { swizzle3<1, 0, 1> _m01_m00_m01; };
struct { swizzle3<1, 1, 0> _m01_m01_m00; };
struct { swizzle3<1, 1, 1> _m01_m01_m01; };

struct { swizzle4<0, 0, 0, 1> _m00_m00_m00_m01; };

struct { swizzle4<0, 0, 1, 0> _m00_m00_m01_m00; };
struct { swizzle4<0, 0, 1, 1> _m00_m00_m01_m01; };

struct { swizzle4<0, 1, 0, 0> _m00_m01_m00_m00; };
struct { swizzle4<0, 1, 0, 1> _m00_m01_m00_m01; };

struct { swizzle4<0, 1, 1, 0> _m00_m01_m01_m00; };
struct { swizzle4<0, 1, 1, 1> _m00_m01_m01_m01; };

struct { swizzle4<1, 0, 0, 0> _m01_m00_m00_m00; };
struct { swizzle4<1, 0, 0, 1> _m01_m00_m00_m01; };

struct { swizzle4<1, 0, 1, 0> _m01_m00_m01_m00; };
struct { swizzle4<1, 0, 1, 1> _m01_m00_m01_m01; };

struct { swizzle4<1, 1, 0, 0> _m01_m01_m00_m00; };
struct { swizzle4<1, 1, 0, 1> _m01_m01_m00_m01; };

struct { swizzle4<1, 1, 1, 0> _m01_m01_m01_m00; };
struct { swizzle4<1, 1, 1, 1> _m01_m01_m01_m01; };

// -------------------------------
// _NM
// -------------------------------

struct { swizzle1<1> _12; };

struct { swizzle2<0, 1> _11_12; };
struct { swizzle2<1, 0> _12_11; };
struct { swizzle2<1, 1> _12_12; };

struct { swizzle3<0, 0, 1> _11_11_12; };
struct { swizzle3<0, 1, 0> _11_12_11; };
struct { swizzle3<0, 1, 1> _11_12_12; };

struct { swizzle3<1, 0, 0> _12_11_11; };
struct { swizzle3<1, 0, 1> _12_11_12; };
struct { swizzle3<1, 1, 0> _12_12_11; };
struct { swizzle3<1, 1, 1> _12_12_12; };

struct { swizzle4<0, 0, 0, 1> _11_11_11_12; };

struct { swizzle4<0, 0, 1, 0> _11_11_12_11; };
struct { swizzle4<0, 0, 1, 1> _11_11_12_12; };

struct { swizzle4<0, 1, 0, 0> _11_12_11_11; };
struct { swizzle4<0, 1, 0, 1> _11_12_11_12; };

struct { swizzle4<0, 1, 1, 0> _11_12_12_11; };
struct { swizzle4<0, 1, 1, 1> _11_12_12_12; };

struct { swizzle4<1, 0, 0, 0> _12_11_11_11; };
struct { swizzle4<1, 0, 0, 1> _12_11_11_12; };

struct { swizzle4<1, 0, 1, 0> _12_11_12_11; };
struct { swizzle4<1, 0, 1, 1> _12_11_12_12; };

struct { swizzle4<1, 1, 0, 0> _12_12_11_11; };
struct { swizzle4<1, 1, 0, 1> _12_12_11_12; };

struct { swizzle4<1, 1, 1, 0> _12_12_12_11; };
struct { swizzle4<1, 1, 1, 1> _12_12_12_12; };