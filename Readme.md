[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![AppVeyor](https://ci.appveyor.com/api/projects/status/18dgjfa958f4xqkm/branch/master?svg=true)](https://ci.appveyor.com/project/redorav/hlslpp)

# HLSL++

Small header-only math library for C++ with the same syntax as the hlsl shading language. It features swizzling and all the operators and functions from the [hlsl documentation](https://docs.microsoft.com/en-us/windows/desktop/direct3dhlsl/dx-graphics-hlsl-reference). The library is aimed mainly at game developers as it's meant to ease the C++ to shader bridge by providing common syntax, but can be used for any application requiring fast, portable math. It also adds some functionality that hlsl doesn't natively provide, such as convenient matrix functions, quaternions, data packing functions and extended vectors such as float8 (8-component float) that take advantage of wide SIMD registers.

## Platforms

- SSE/AVX/AVX2/AVX512: x86/x64 devices like PC, Intel Mac, PS4/5, Xbox One/Series
- NEON: ARM devices like Android, Mac M1, iOS, Switch
- WASM

## Example

hlsl++ allows you to be as expressive in C++ as when programming in the shader language. Constructs such as the following are possible.

```hlsl
// Native types
float4 foo4 = float4(1, 2, 3, 4);

// Swizzling
float3 bar3 = foo4.xzy;

// HLSL functions
float2 logFoo2 = log(bar3.xz);

// Swizzle of swizzle
foo4.wx = logFoo2.yx;

// Combined constructors
float4 baz4 = float4(logFoo2, foo4.zz);

// Matrices
float4x4 fooMatrix4x4 = float4x4( 1, 2, 3, 4,
                                  5, 6, 7, 8,
                                  8, 7, 6, 5,
                                  4, 3, 2, 1);

// Matrix transformations
float4 myTransformedVector = mul(fooMatrix4x4, baz4);

// Integer operations
int2 ifoo2 = int2(1, 2);
int4 ifoo4 = int4(1, 2, 3, 4) + ifoo2.xyxy;

// Casts
float4 fooCast4 = ifoo4.wwyx;

// Float8
float8 foo8 = float8(1, 2, 3, 4, 5, 6, 7, 8);
float8 bar8 = float8(1, 2, 3, 4, 5, 6, 7, 8);
float8 add8 = foo8 + bar8;

// Data packing
uint rgba8Packed     = pack_float4_rgba8_unorm(foo4);
float4 rgba8Unpacked = unpack_rgba8_unorm_float4(rgba8Packed);
```

The natvis files provided for Visual Studio debugging allow you to see both vectors and the result of the swizzling in the debugging window in a programmer-friendly way.

<p align="center">
  <img align="center" src="/github/images/swizzle_natvis_preview.png?raw=true" alt="Swizzle Natvis Preview">
</p>

## Requirements

The only required features are a C++ compiler supporting anonymous unions, and SIMD extensions depending on your target platform (SSE/NEON/WASM). If your target platform does not have SIMD support, it can also fall back to a scalar implementation. As a curiosity it also includes an Xbox 360 implementation.

## How to use

```cpp
// The quickest way, expensive in compile times but good for fast iteration
#include "hlsl++.h"

// If you care about compile times in your cpp files
#include "hlsl++/vector_float.h"
#include "hlsl++/matrix_float.h"

// If you only need type information (e.g. in header files) and don't use any functions
#include "hlsl++/vector_float_type.h"
#include "hlsl++/quaternion_type.h"
```

* Remember to add an include path to ```"include"```. IMPORTANT NOTE: The include structure has changed to remove prefixes and move towards a sensible folder hierarchy. Compatibility includes will stay around for a bit but will eventually be removed (probably in version 4.0)
* Windows has defines for min and max so if you're using this library and the <windows.h> header remember to #define NOMINMAX before including it
* To force the scalar version of the library, define ```HLSLPP_SCALAR``` globally. The scalar library is only different from the SIMD version in its use of regular floats to represent vectors. It should only be used if your platform (e.g. embedded) does not have native SIMD support. It can also be used to compare performance
* To enable the transforms feature, define ```HLSLPP_FEATURE_TRANSFORM``` globally
* The f32 members of floatN (and other types) and the [ ] operators make use of the union directly, so the generated code is up to the compiler. Use with care
* The f32 members of floatN (and other types) have the & operator overridden to take the address of the individual float. This is very useful to pass to libraries that expect data pointers like imgui

## Features

* SSE/AVX/AVX2/AVX512, NEON, Xbox360, WebAssembly and scalar versions
* float1, float2, float3, float4, float8
* int1, int2, int3, int4
* uint1, uint2, uint3, uint4
* double1, double2, double3, double4
* floatNxM
* quaternion
* Conversion construction and assignment, e.g. float4(float2, float2) and int4(float2, int2)
* Efficient swizzling for all vector types
* Basic operators +, *, -, / for all vector and matrix types
* Per-component comparison operators ==, !=, >, <, >=, <= (no ternary operator as overloading is disallowed in C++)
* HLSL float functions: abs, acos, all, any, asin, atan, atan2, ceil, clamp, cos, cosh, cross, degrees, distance, dot, exp, exp2, floor, fmod, frac, isfinite, isinf, isnan, length, lerp, log, log2, log10, mad, max, min, modf, normalize, pow, radians, rcp, reflect, refract, round, rsqrt, saturate, select, sign, sin, sincos, sinh, smoothstep, sqrt, step, tan, tanh, trunc
* HLSL int/uint functions: countbits, firstbithigh, firstbitlow, reversebits
* Additional functions not in HLSL: copysign
* Additional matrix functions: determinant, transpose, inverse, adjoint
* Matrix multiplication for all NxM matrix combinations
* Data packing functions such as pack_float4_rgba8_unorm or pack_float3_rg11b10f
* Transformation matrices for scale, rotation and translation, as well as world-to-view look_at and view-to-projection orthographic/perspective coordinate transformations. These static functions are optionally available for matrix types float2x2, float3x3, float4x4 when hlsl++.h is compiled with HLSLPP_FEATURE_TRANSFORM definition.
* Native visualizers for Visual Studio (.natvis files) which correctly parse with both MSVC and Clang in Windows

Missing/planned:

* boolN types
