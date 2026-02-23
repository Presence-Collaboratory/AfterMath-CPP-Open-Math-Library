# AfterMath

**AfterMath** is a fully open-source mathematics library with HLSL-like syntax and SSE acceleration, available for commercial use.  
The library supports C++14, C++17, and C++20 standards and requires SSE4.2 instructions.

AfterMath provides a rich set of types and functions for vectors, matrices, quaternions, and 16‑bit half‑precision values. It is ideal for game development, real-time systems, scientific computing, and any applications where performance and ease of mathematical operations are important.

---

## Features

- **Vector types**
  - `float2`, `float3`, `float4` (with SSE acceleration)
  - `half`, `half2`, `half3`, `half4` (16‑bit half‑precision, optimal for GPU data transfer)
  - Template classes `TemplateVector2/3/4` for integral types (`int2`, `uint2`, `double2`, etc.)

- **Matrix types**
  - `float2x2`, `float3x3`, `float4x4` (row‑major storage, full set of operations)
  - Functions for creating transformation matrices (translation, rotation, scaling, perspective, look‑at)

- **Quaternions**
  - Full quaternion arithmetic, interpolation (slerp, nlerp), conversion to matrices and Euler angles
  - Storage in an SSE register (`__m128`) for maximum performance

- **Axis‑Aligned Bounding Box (AABB)**
  - Fast ray‑AABB intersection tests, containment tests, transformations
  - Optimized for physics engines and spatial partitioning systems

- **Mathematical utilities**
  - Constants (`PI`, `EPSILON`, `INFINITY`, etc.) for `float` and `double`
  - Robust floating‑point comparison functions (absolute/relative tolerance, ULP)
  - Fast approximations of trigonometric functions, square root, exponential, and logarithm (using lookup tables)
  - HLSL‑style functions: `saturate`, `lerp`, `step`, `smoothstep`, `reflect`, `refract`, and many others

- **Performance**
  - SSE intrinsics for operations on `float3`, `float4`, and matrices
  - Fast math functions with 360‑entry tables (sine, cosine, tangent)
  - Efficient conversion between half and single precision

- **Ease of use**
  - Intuitive HLSL‑like syntax for all operations
  - Seamless interoperability between `float` and `half` types
  - Single header inclusion: `#include <AfterMath/AfterMath.h>`

---

## Requirements

- Compiler with support for C++14, C++17, or C++20
- Processor with SSE4.2 support (to use optimized operations)
- The library is **header‑only**, so no compilation is required

---

## Quick Start

1. **Include the library** in your project:
   #include <AfterMath/AfterMath.h>
   
Use the namespace (optional, but convenient):

using namespace AfterMath;

2. Enable SSE support in your compiler settings:

MSVC: /arch:SSE4.2

GCC/clang: -msse4.2

---
## Usage Examples
1. **Vector arithmetic**

float3 a(1.0f, 2.0f, 3.0f);
float3 b(4.0f, 5.0f, 6.0f);

float3 c = a + b;               // (5, 7, 9)
float3 d = a * 2.0f;            // (2, 4, 6)
float  dot = dot(a, b);         // 32
float3 cross = cross(a, b);     // (-3, 6, -3)
float3 norm = normalize(a);     // unit vector

2. **Half‑precision vectors (memory‑saving)**
half2 texCoord(0.5f, 0.75f);
half3 normal = normalize(half3(1.0f, 2.0f, 3.0f));

// Convert back to float for computations
float2 f_tex = to_float2(texCoord);

3. **Matrix transformations**
float3 position(10.0f, 20.0f, 30.0f);

// Build world matrix: translation, rotation around Y, scaling
float4x4 world = float4x4::translation(position) *
                 float4x4::rotation_y(PI / 2.0f) *
                 float4x4::scaling(2.0f);

// Transform a point
float3 worldPos = world * position;

4. **Quaternions**
quaternion q = quaternion_axis_angle(float3(0,1,0), PI/2);  // 90° around Y
float3 v(1,0,0);
float3 rotated = q * v;              // (0,0,-1)

// Interpolate between two rotations
quaternion q1 = identity_quaternion();
quaternion q2 = quaternion_euler(0, PI, 0);
quaternion qSlerp = slerp(q1, q2, 0.5f);

5. **Ray‑AABB intersection**
AABB box(float3(0,0,0), float3(10,10,10));
float3 origin(5,5,-5);
float3 dir(0,0,1);
float tMin, tMax;
if (box.intersect_ray(origin, dir, tMin, tMax)) {
    printf("Hit at distance %f\n", tMin);
}

6. **Fast math approximations**
float angle = 45.0f; // degrees
float s = FastMath::fast_sin(angle);   // table lookup
float c = FastMath::fast_cos(angle);
float isqrt = FastMath::fast_inv_sqrt(2.0f); // ≈ 0.707

---
**Performance Notes**
Vector operations on float3 and float4 are implemented using SSE intrinsics.
For maximum efficiency, align your data to a 16‑byte boundary (e.g., with alignas(16)).

Half‑precision types (half*) are not accelerated by SIMD, but they significantly reduce memory bandwidth.
Use them for large arrays of normals, texture coordinates, or colors.

Fast math functions trade a small amount of accuracy for speed.
The tables have a 1‑degree resolution and use linear interpolation for fractional angles.

---
**License**
AfterMath is distributed under the MIT License.
You are free to use the library in both commercial and non‑commercial projects.

---
**Authors**
NSDeathman

DeepSeek

Gemini

and other contributors

---
**Acknowledgments**
Special thanks to the authors of the original half‑precision conversion algorithms and to the entire open‑source community for inspiration and ready‑to‑use solutions.

---
**AfterMath – when you need more than just arithmetic.**
