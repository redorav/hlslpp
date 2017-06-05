[![AppVeyor](https://ci.appveyor.com/api/projects/status/18dgjfa958f4xqkm/branch/master?svg=true)](https://ci.appveyor.com/project/redorav/hlslpp)
[![Travis CI](https://travis-ci.org/redorav/hlslpp.svg?branch=master)](https://travis-ci.org/redorav/hlslpp)

# HLSL++

HLSL++ is a small math library for C++ with the same syntax and features as hlsl, with support for SSE and NEON. It features swizzling and all the expected math operators and functions from the hlsl documentation. The library is aimed mainly at game developers. It's meant to ease the C++ to shader bridge by providing a common interface and syntax.

# Example

hlsl++ should allow you to be as expressive with the math as you typically are when programming in the shader language. Constructs such as the following are possible.

```cpp
float4 foo4 = float4(1, 2, 3, 4);
float3 bar3 = foo4.xzy;
float2 logFoo2 = log(bar3.xz);
foo4.wx = logFoo2.yx;
float4 baz4 = float4(logFoo2, foo4.zz);
float4x4 fooMatrix4x4 = float4x4(	1, 2, 3, 4,
									5, 6, 7, 8,
									8, 7, 6, 5,
									4, 3, 2, 1);
float4 myTransformedVector = mul(fooMatrix4x4, baz4);
```

The natvis files provided for Visual Studio debugging allow you to see both vectors and the result of the swizzling in the debugging window in a programmer-friendly way.

![Alt text](/github/images/swizzle_natvis_preview.png?raw=true "Swizzle Natvis Preview")

# Requirements

Required features for the library to compile are C++11, and SSE4.1 for x86/64 and NEON for ARM. 

* I use some features of C++11 such as anonymous unions and some template extensions that would make it more complicated to implement in previous versions of C++.
* I also use specific SSE4.1 intrinsics such as _mm_blend_ps and _mm_round_ps that make the code faster and easier to develop. Since it's aimed at game developers and most modern consoles and computers support it I though it best not to carry SSE2 implementations of these functions without justification. In some cases I have made conscious decisions to keep SSE2 versions of functions, such as the dot product, because my tests showed they were faster than the SSE4 equivalent (_mm_dp_ps in this case)

# Features

* float1, float2, float3, float4 types
* floatNxM (all the matrix) types
* Native visualizers for Visual Studio (.natvis files) which correctly parse with both MSVC and Clang
* Mixed constructors, e.g. float4(float2, float2)
* Efficient swizzling for all the floatN types
* Basic operators +, *, -, / for both vector and matrix types
* Per-component comparison operators ==, !=, >, <, >=, <= (no ternary operator as overloading is disallowed in C++)
* hlsl vector functions: abs, acos, all, any, asin, atan, ceil, clamp, cos, cross, degrees, dot, floor, frac, exp, exp2, isfinite, isinf, isnan, length, lerp, log, log2, log10, max, min, normalize, pow, radians, reflect, round, rsqrt, saturate, sign, sin, sqrt, step, trunc, tan
* hlsl matrix functions: determinant, transpose, inverse (not in hlsl but very useful)
* Matrix multiplication for all NxM matrix combinations
* float1xM explicit conversions with floatN (e.g. casting a float4 to 4x1 or 1x4)

Missing/planned:

* hlsl functions: smoothstep, atan2, cosh, sinh, tanh
* floatNxM _m00_m01 style swizzling (rows implemented but missing columns)
* Integer/bool vector types