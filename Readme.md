# HLSL++

HLSL++ is a small math library with the same syntax and specific features as hlsl. It features swizzling, all the expected operators and all the functions from the hlsl documentation. The library is aimed mainly at game developers. It's meant to ease the C++ to shader bridge by providing common interface and syntax. It makes use of SSE instructions on PC.

# Example

hlsl++ should allow you to be as expressive with the math as you typically are when programming in a shader language. Constructs such as the following are possible.

float4 foo = float4(1, 2, 3, 4);

float2 bar = foo.xz;

float2 logFoo = log(bar.xy);

foo.wx = logFoo.yx;

# Requirements

Required features for the library to compile are C++11 and SSE4.1

# Caveats

It's currently a very early work in progress and not production code.

# Features

Implemented:

* float1, float2, float3, float4 types
* Efficient swizzling for all the floatN types
* Basic operators +, *, -, / and variants
* Per-component boolean operators
* hlsl functions: abs, acos, all, any, asin, atan, ceil, clamp, cos, cross, degrees, dot, floor, frac, exp, exp2, isfinite, isinf, isnan, length, lerp, log, log2, log10, max, min, normalize, pow, radians, reflect, round, rsqrt, saturate, sign, sin, sqrt, step, trunc, tan,
* floatNxM types

Missing:

* hlsl functions: smoothstep, atan2, cosh, sinh, tanh
* floatNxM operations.
* floatNxM _m00_m01 style swizzling (rows implemented but missing columns)
* float1xM implicit conversions with floatM
* floatM to float1 implicit conversions
* Mixed constructors (e.g. float4(float2, float2))
* floatM o float1 operations
* Integer types int1, int2, int3, int4