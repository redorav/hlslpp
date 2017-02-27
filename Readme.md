[![AppVeyor](https://ci.appveyor.com/api/projects/status/18dgjfa958f4xqkm/branch/master?svg=true)](https://ci.appveyor.com/project/redorav/hlslpp)

# HLSL++

HLSL++ is a small math library for C++ with the same syntax and features as hlsl. It features swizzling and all the expected math operators and functions from the hlsl documentation. The library is aimed mainly at game developers. It's meant to ease the C++ to shader bridge by providing a common interface and syntax. It makes use of SSE instructions on PC, and NEON is planned for the future.

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

# Requirements

Required features for the library to compile are C++11 and SSE4.1

I employ some advanced features of C++11 such as anonymous unions and some template extensions that would make it more complicated to implement in previous versions of C++.

I also use specific SSE4.1 intrinsics such as _mm_blend_ps and _mm_round_ps that make the code faster and easier to develop. Since it's aimed at game developers and most modern consoles and computers support it I though it best to not carry SSE2 implementations of these functions.

In some cases I have made conscious decisions to keep SSE2 versions of functions, such as the dot product, because my tests showed they were faster than the SSE4 equivalent (_mm_dp_ps in this case).

# Features

Implemented:

* float1, float2, float3, float4 types
* Mixed constructors, e.g. float4(float2, float2)
* Efficient swizzling for all the floatN types
* floatN basic operators +, *, -, / and variants
* Per-component comparison operators ==, !=, >, <, >=, <= (no ternary operator as overloading is disallowed in C++)
* hlsl vector functions: abs, acos, all, any, asin, atan, ceil, clamp, cos, cross, degrees, dot, floor, frac, exp, exp2, isfinite, isinf, isnan, length, lerp, log, log2, log10, max, min, normalize, pow, radians, reflect, round, rsqrt, saturate, sign, sin, sqrt, step, trunc, tan
* hlsl matrix functions: determinant, transpose
* non-hlsl matrix functions: inverse
* floatNxM (all the matrix) types
* floatNxM basic operators +, *, -, / and variants
* Matrix multiplication for all NxM matrix combinations
* float1xM explicit conversions with floatN (e.g. casting a float4 to 4x1 or 1x4)
* Native visualizers for Visual Studio (.natvis files) which correctly parse with both MSVC and Clang

Missing:

* hlsl functions: smoothstep, atan2, cosh, sinh, tanh
* floatNxM _m00_m01 style swizzling (rows implemented but missing columns)
* floatM to float1 implicit conversions
* Integer types int1, int2, int3, int4