[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE.md)
[![AppVeyor](https://ci.appveyor.com/api/projects/status/18dgjfa958f4xqkm/branch/master?svg=true)](https://ci.appveyor.com/project/redorav/hlslpp)
[![Travis CI](https://travis-ci.org/redorav/hlslpp.svg?branch=master)](https://travis-ci.org/redorav/hlslpp)

# HLSL++

Small header-only math library for C++ with the same syntax as the hlsl shading language. It supports any SSE4.1 (x86/x64, PS4, Xbox One) and NEON (ARM, ARM64, Switch) platforms. It features swizzling and all the operators and functions from the [hlsl documentation](https://docs.microsoft.com/en-us/windows/desktop/direct3dhlsl/dx-graphics-hlsl-reference). The library is aimed mainly at game developers as it's meant to ease the C++ to shader bridge by providing common syntax, but can be used for any application requiring portable math. It also adds some functionality that hlsl doesn't natively provide, such as convenient matrix rotation functions and quaternions.

## Example

hlsl++ allows you to be as expressive in C++ as when programming in the shader language. Constructs such as the following are possible.

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

The only required features are a C++ compiler supporting anonymous unions, and SSE4.1 or NEON depending on your target platform. As a curiosity it also includes an Xbox 360 implementation.

* Specific SSE4.1 intrinsics such as _mm_blend_ps and _mm_round_ps make the code faster and easier to develop. Since it's aimed at game developers and most modern consoles and computers support it there are no SSE2 implementations of these functions. In some cases SSE2 versions of functions, such as the dot product, can be faster than the SSE4 equivalent (_mm_dp_ps)

## How to use

#include hlsl++.h in your project and add an include path to the directory where it lives. hlsl++.h pulls in other headers that live in the same folder.

## Features

* float1, float2, float3, float4
* int1, int2, int3, int4
* double1, double2, double3, double4
* floatNxM
* quaternion
* Conversion construction and assignment, e.g. float4(float2, float2) and int4(float2, int2)
* Efficient swizzling for all vector types
* Basic operators +, *, -, / for all vector and matrix types
* Per-component comparison operators ==, !=, >, <, >=, <= (no ternary operator as overloading is disallowed in C++)
* hlsl vector functions: abs, acos, all, any, asin, atan, ceil, clamp, cos, cosh, cross, degrees, dot, floor, fmod, frac, exp, exp2, isfinite, isinf, isnan, length, lerp, log, log2, log10, max, min, modf, normalize, pow, radians, reflect, refract, round, rsqrt, saturate, sign, sin, sinh, smoothstep, sqrt, step, trunc, tan, tanh
* Additional matrix functions: determinant, transpose, inverse (not in hlsl but very useful)
* Matrix multiplication for all NxM matrix combinations
* Native visualizers for Visual Studio (.natvis files) which correctly parse with both MSVC and Clang in Windows

Missing/planned:

* hlsl functions: atan2
* floatNxM _m00_m01 style swizzling (rows implemented but missing columns)
* boolN types
