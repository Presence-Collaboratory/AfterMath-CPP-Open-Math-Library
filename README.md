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

Below are practical examples demonstrating AfterMath’s vector types and HLSL‑style global functions.  
All examples assume you have included the library and are using the `AfterMath` namespace.

```cpp
#include <AfterMath/AfterMath.h>
using namespace AfterMath;
```

1. **Working with float2 (2D vectors)**
```cpp
// Construction
float2 a(1.0f, 2.0f);
float2 b(3.0f, 4.0f);
float2 zero = float2::zero();          // (0,0)
float2 unitX = float2::unit_x();       // (1,0)

// Arithmetic
float2 sum = a + b;                     // (4, 6)
float2 diff = a - b;                     // (-2, -2)
float2 scaled = a * 2.5f;                // (2.5, 5.0)
float2 product = a * b;                  // component‑wise: (3, 8)
float2 divided = a / b;                  // component‑wise: (1/3, 2/4) = (0.333, 0.5)

// Length and normalization
float len = length(a);                    // √(1²+2²) ≈ 2.236
float lenSq = length_sq(a);                // 5
float2 norm = normalize(a);                // ≈ (0.447, 0.894)

// Dot and cross (2D cross returns scalar)
float dotVal = dot(a, b);                  // 1*3 + 2*4 = 11
float crossVal = cross(a, b);              // 1*4 - 2*3 = -2

// Geometric operations
float2 perp = perpendicular(a);            // (-2, 1)
float2 reflected = reflect(a, float2(0,1)); // reflect across Y axis: (1,-2)
float2 rotated = rotate(a, PI/2);          // rotate 90°: (-2, 1)

// Interpolation
float2 lerped = lerp(a, b, 0.3f);          // a + (b-a)*0.3 = (1.6, 2.6)

// HLSL‑style component functions
float2 absVec = abs(a);                     // (1,2)
float2 floorVec = floor(float2(1.7f, 2.3f)); // (1,2)
float2 fracVec = frac(float2(1.7f, 2.3f));   // (0.7, 0.3)
float2 satVec = saturate(float2(0.2f, 1.5f)); // (0.2, 1.0)
```

2. **Working with float3 (3D vectors)**
```cpp
float3 a(1.0f, 2.0f, 3.0f);
float3 b(4.0f, 5.0f, 6.0f);

// Basic arithmetic (similar to float2)
float3 sum = a + b;                         // (5, 7, 9)
float3 crossProd = cross(a, b);              // (2*6 - 3*5, 3*4 - 1*6, 1*5 - 2*4) = (-3, 6, -3)
float dotProd = dot(a, b);                   // 1*4 + 2*5 + 3*6 = 32

// Length and normalization
float len = length(a);                        // √14 ≈ 3.742
float3 norm = normalize(a);                    // ≈ (0.267, 0.535, 0.802)

// Angle between vectors
float angle = angle_between(a, b);            // ≈ 0.225 rad (~12.9°)

// Reflection and refraction
float3 normal = float3(0,1,0);
float3 incident = float3(1,-1,0);
float3 reflected = reflect(incident, normal); // (1,1,0)
float3 refracted = refract(incident, normal, 1.5f); // depends on eta

// Projection and rejection
float3 onto = float3(1,0,0);
float3 proj = project(a, onto);               // (1,0,0)
float3 rej = reject(a, onto);                  // (0,2,3)

// Swizzle operations
float2 xy = a.xy();                            // (1,2)
float3 xzy = a.xzy();                          // (1,3,2)
float3 yxz = a.yxz();                          // (2,1,3)
```

3. **Working with float4 (4D vectors / homogeneous coordinates / colors)**
```cpp
float4 a(1.0f, 2.0f, 3.0f, 4.0f);
float4 b(5.0f, 6.0f, 7.0f, 8.0f);

// Arithmetic
float4 sum = a + b;                            // (6,8,10,12)
float4 componentMul = a * b;                    // (5,12,21,32)

// Dot product (full 4D) and 3D dot (ignoring w)
float dot4 = dot(a, b);                         // 1*5 + 2*6 + 3*7 + 4*8 = 70
float dot3 = dot3(a, b);                        // 1*5 + 2*6 + 3*7 = 38

// Length and normalization
float len = length(a);                           // √(1+4+9+16) = √30 ≈ 5.477
float4 norm = normalize(a);                       // ≈ (0.183, 0.365, 0.548, 0.730)

// Color operations
float4 color(0.2f, 0.4f, 0.6f, 0.8f);
float lum = luminance(color);                    // 0.2126*0.2 + 0.7152*0.4 + 0.0722*0.6 ≈ 0.374
float4 gray = grayscale(color);                   // (lum, lum, lum, 0.8)
float4 premul = premultiply_alpha(color);         // (0.16, 0.32, 0.48, 0.8)
float4 unpremul = unpremultiply_alpha(premul);    // back to original

// Homogeneous coordinates
float4 pointH = to_homogeneous(float3(1,2,3));   // (1,2,3,1)
float3 point3D = project(pointH);                 // (1,2,3)  (divide by w)

// Swizzles
float2 rg = color.rg();                           // (0.2, 0.4)
float4 bgra = color.bgra();                       // (0.6, 0.4, 0.2, 0.8)
```

4. **HLSL‑style Global Functions (applied to any vector type)**
```cpp
float3 v(0.5f, -0.8f, 0.3f);

// Basic component‑wise functions
float3 v_abs = abs(v);                    // (0.5, 0.8, 0.3)
float3 v_sign = sign(v);                   // (1, -1, 1)
float3 v_floor = floor(v);                  // (0, -1, 0)
float3 v_ceil = ceil(v);                    // (1, 0, 1)
float3 v_frac = frac(v);                    // (0.5, 0.2, 0.3)   (for positive parts only)

// Saturation and step
float3 v_sat = saturate(v);                 // clamps to [0,1] → (0.5, 0, 0.3)
float3 v_step = step(0.2f, v);              // (1, 0, 1)   (1 if component ≥ 0.2)

// Smoothstep
float3 v_smooth = smoothstep(0.2f, 0.8f, v); // smooth interpolation per component

// Min / max / clamp
float3 minVal = min(v, float3(0.0f, -0.5f, 0.2f));
float3 maxVal = max(v, float3(0.0f, -0.5f, 0.2f));
float3 clamped = clamp(v, -0.5f, 0.5f);      // per‑component clamp to [-0.5, 0.5]

// Interpolation
float3 a(1,2,3), b(4,5,6);
float3 lerped = lerp(a, b, 0.25f);          // (1.75, 2.75, 3.75)
```

5. **Using approximately for floating‑point comparisons**
```cpp
float3 x(1.0f, 2.0f, 3.0f);
float3 y(1.000001f, 2.0f, 3.0f);

if (approximately(x, y)) {                   // true (within default epsilon)
    // vectors are considered equal
}

if (approximately_zero(x - y)) {              // also true
    // difference is nearly zero
}
```

7. **Half‑precision vectors (memory‑saving)**
```cpp
half2 texCoord(0.5f, 0.75f);
half3 normal = normalize(half3(1.0f, 2.0f, 3.0f));

// Convert back to float for computations
float2 f_tex = to_float2(texCoord);
```

8. **Matrix transformations**
```cpp
float3 position(10.0f, 20.0f, 30.0f);

// Build world matrix: translation, rotation around Y, scaling
float4x4 world = float4x4::translation(position) *
                 float4x4::rotation_y(PI / 2.0f) *
                 float4x4::scaling(2.0f);

// Transform a point
float3 worldPos = world * position;
```

9. **Quaternions**
```cpp
quaternion q = quaternion_axis_angle(float3(0,1,0), PI/2);  // 90° around Y
float3 v(1,0,0);
float3 rotated = q * v;              // (0,0,-1)

// Interpolate between two rotations
quaternion q1 = identity_quaternion();
quaternion q2 = quaternion_euler(0, PI, 0);
quaternion qSlerp = slerp(q1, q2, 0.5f);
```

10. **Ray‑AABB intersection**
```cpp
AABB box(float3(0,0,0), float3(10,10,10));
float3 origin(5,5,-5);
float3 dir(0,0,1);
float tMin, tMax;
if (box.intersect_ray(origin, dir, tMin, tMax)) {
    printf("Hit at distance %f\n", tMin);
}
```

11. **Fast math approximations**
```cpp
float angle = 45.0f; // degrees
float s = FastMath::fast_sin(angle);   // table lookup
float c = FastMath::fast_cos(angle);
float isqrt = FastMath::fast_inv_sqrt(2.0f); // ≈ 0.707
```

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
