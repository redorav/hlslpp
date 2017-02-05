# HLSL++

HLSL++ is a small math library with the same syntax and specific features as hlsl. It features swizzling, all the expected math operators and functions from the hlsl documentation. The library is aimed mainly at game developers. It's meant to ease the C++ to shader bridge by providing a common interface and syntax. It makes use of SSE instructions on PC, and NEON is planned for the future.

# Example

hlsl++ should allow you to be as expressive with the math as you typically are when programming in the shader language. Constructs such as the following are possible.

float4 foo4 = float4(1, 2, 3, 4);

float2 bar2 = foo4.xz;

float2 logFoo2 = log(bar2.xy);

foo4.wx = logFoo2.yx;

float4 baz = float4(logFoo2, foo4.zz);

# Requirements

Required features for the library to compile are C++11 and SSE4.1

I employ some advanced features of C++11 such as anonymous unions and some template extensions that would make it much more complicated to implement in previous versions of C++.

I also use specific SSE4.1 intrinsics such as _mm_blend_ps and _mm_round_ps that make the code faster and easier to develop. Since it's aimed at game developers and most modern consoles and computers support it I though it best to not carry SSE2 implementations of these functions.

In some cases I have made conscious decisions to keep SSE2 versions of functions, such as the dot product, because my tests showed they were faster than the SSE4 equivalent (_mm_dp_ps in this case).

# Caveats

It's currently a very early work in progress and not production code.

# Features

Implemented:

* float1, float2, float3, float4 types
* Mixed constructors, e.g. float4(float2, float2)
* Efficient swizzling for all the floatN types
* Basic operators +, *, -, / and variants
* Per-component comparison operators ==, !=, >, <, >=, <= (no ternary operator as overloading is disallowed in C++)
* hlsl functions: abs, acos, all, any, asin, atan, ceil, clamp, cos, cross, degrees, dot, floor, frac, exp, exp2, isfinite, isinf, isnan, length, lerp, log, log2, log10, max, min, normalize, pow, radians, reflect, round, rsqrt, saturate, sign, sin, sqrt, step, trunc, tan,
* floatNxM types
* Native visualizers for Visual Studio which correctly parse with both MSVC and Clang


Missing:

* hlsl functions: smoothstep, atan2, cosh, sinh, tanh
* floatNxM basic operations
* floatNxM _m00_m01 style swizzling (rows implemented but missing columns)
* float1xM implicit conversions with floatM
* floatM to float1 implicit conversions
* floatM o float1 operations
* Integer types int1, int2, int3, int4