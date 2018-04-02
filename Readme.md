[![AppVeyor](https://ci.appveyor.com/api/projects/status/18dgjfa958f4xqkm/branch/master?svg=true)](https://ci.appveyor.com/project/redorav/hlslpp)
[![Travis CI](https://travis-ci.org/redorav/hlslpp.svg?branch=master)](https://travis-ci.org/redorav/hlslpp)

# HLSL++

HLSL++ is a small math library for C++ with the same syntax and features as hlsl, with support for SSE and NEON. It features swizzling and all the expected math operators and functions from the hlsl documentation. The library is aimed mainly at game developers. It's meant to ease the C++ to shader bridge by providing a common interface and syntax. It also adds some functionality that hlsl doesn't natively provide, such as convenient math functions and quaternions.

## Example

hlsl++ allows you to be as expressive with the math as you typically are when programming in the shader language. Constructs such as the following are possible.

```cpp
float4 foo4 = float4(1, 2, 3, 4);
float3 bar3 = foo4.xzy;
float2 logFoo2 = log(bar3.xz);
foo4.wx = logFoo2.yx;
float4 baz4 = float4(logFoo2, foo4.zz);
float4x4 fooMatrix4x4 = float4x4( 1, 2, 3, 4,
                                  5, 6, 7, 8,
                                  8, 7, 6, 5,
                                  4, 3, 2, 1);
float4 myTransformedVector = mul(fooMatrix4x4, baz4);
int2 ifoo2 = int2(1, 2);
int4 ifoo4 = int4(1, 2, 3, 4) + ifoo2.xyxy;
float4 fooCast4 = ifoo4.wwyx;
```

The natvis files provided for Visual Studio debugging allow you to see both vectors and the result of the swizzling in the debugging window in a programmer-friendly way.

<p align="center">
  <img align="center" src="/github/images/swizzle_natvis_preview.png?raw=true" alt="Swizzle Natvis Preview">
</p>

## Requirements

Required features for the library to compile are C++11, SSE4.1 for x86/64 and NEON for ARM. 

* Some features of C++11 such as anonymous unions and some template extensions would make it more complicated to implement in previous versions of C++.
* Specific SSE4.1 intrinsics such as _mm_blend_ps and _mm_round_ps make the code faster and easier to develop. Since it's aimed at game developers and most modern consoles and computers support it there are no SSE2 implementations of these functions without justification. In some cases SSE2 versions of functions, such as the dot product, can be faster than the SSE4 equivalent (_mm_dp_ps)

## How to use

Simply include hlsl++.h in your project and add an include path to the src directory. Do not include any of the other files as those get included as appropriate by the main header file. 

## Features

* float1, float2, float3, float4 types
* int1, int2, int3, int4 types
* floatNxM types
* quaternion type
* Conversion construction and assignment, e.g. float4(float2, float2) and int4(float2, int2)
* Efficient swizzling for all the floatN types
* Basic operators +, *, -, / for all vector and matrix types
* Per-component comparison operators ==, !=, >, <, >=, <= (no ternary operator as overloading is disallowed in C++)
* hlsl vector functions: abs, acos, all, any, asin, atan, ceil, clamp, cos, cosh, cross, degrees, dot, floor, frac, exp, exp2, isfinite, isinf, isnan, length, lerp, log, log2, log10, max, min, normalize, pow, radians, reflect, round, rsqrt, saturate, sign, sin, sinh, smoothstep, sqrt, step, trunc, tan, tanh
* Additional matrix functions: determinant, transpose, inverse (not in hlsl but very useful)
* Matrix multiplication for all NxM matrix combinations
* Native visualizers for Visual Studio (.natvis files) which correctly parse with both MSVC and Clang in Windows

Missing/planned:

* hlsl functions: atan2, modf
* floatNxM _m00_m01 style swizzling (rows implemented but missing columns)
* boolN types
