// Author: DeepSeek
// Test suite for AfterMath::float3 class with HLSL-like syntax

#include "AutotestCore.h"

namespace AfterMathTests
{
    void RunFloat3Tests(TestSuite& suite)
    {
        using namespace AfterMath;

        // ============================================================================
        // 1. Constructors
        // ============================================================================
        suite.section("Constructors");

        // Default constructor test
        {
            float3 v;
            suite.assert_approximately_equal(v.x, 0.0f, "Default constructor x");
            suite.assert_approximately_equal(v.y, 0.0f, "Default constructor y");
            suite.assert_approximately_equal(v.z, 0.0f, "Default constructor z");
        }

        // Component constructor test
        {
            float3 v(1.5f, 2.5f, 3.5f);
            suite.assert_approximately_equal(v.x, 1.5f, "Component constructor x");
            suite.assert_approximately_equal(v.y, 2.5f, "Component constructor y");
            suite.assert_approximately_equal(v.z, 3.5f, "Component constructor z");
        }

        // Scalar constructor test
        {
            float3 v(3.0f);
            suite.assert_approximately_equal(v.x, 3.0f, "Scalar constructor x");
            suite.assert_approximately_equal(v.y, 3.0f, "Scalar constructor y");
            suite.assert_approximately_equal(v.z, 3.0f, "Scalar constructor z");
        }

        // Constructor from array
        {
            float data[3] = { 4.0f, 5.0f, 6.0f };
            float3 v(data);
            suite.assert_approximately_equal(v.x, 4.0f, "Array constructor x");
            suite.assert_approximately_equal(v.y, 5.0f, "Array constructor y");
            suite.assert_approximately_equal(v.z, 6.0f, "Array constructor z");
        }

        // Copy constructor test
        {
            float3 original(6.0f, 7.0f, 8.0f);
            float3 copy(original);
            suite.assert_approximately_equal(copy.x, 6.0f, "Copy constructor x");
            suite.assert_approximately_equal(copy.y, 7.0f, "Copy constructor y");
            suite.assert_approximately_equal(copy.z, 8.0f, "Copy constructor z");
        }

        // Static constructors test
        {
            suite.assert_approximately_equal(float3::zero(), float3(0.0f, 0.0f, 0.0f), "zero()");
            suite.assert_approximately_equal(float3::one(), float3(1.0f, 1.0f, 1.0f), "one()");
            suite.assert_approximately_equal(float3::unit_x(), float3(1.0f, 0.0f, 0.0f), "unit_x()");
            suite.assert_approximately_equal(float3::unit_y(), float3(0.0f, 1.0f, 0.0f), "unit_y()");
            suite.assert_approximately_equal(float3::unit_z(), float3(0.0f, 0.0f, 1.0f), "unit_z()");
            suite.assert_approximately_equal(float3::forward(), float3(0.0f, 0.0f, 1.0f), "forward()");
            suite.assert_approximately_equal(float3::up(), float3(0.0f, 1.0f, 0.0f), "up()");
            suite.assert_approximately_equal(float3::right(), float3(1.0f, 0.0f, 0.0f), "right()");
        }

        // ============================================================================
        // 2. Assignment operators
        // ============================================================================
        suite.section("Assignment operators");

        // Scalar assignment test
        {
            float3 v;
            v = 2.5f;
            suite.assert_approximately_equal(v.x, 2.5f, "Scalar assignment x");
            suite.assert_approximately_equal(v.y, 2.5f, "Scalar assignment y");
            suite.assert_approximately_equal(v.z, 2.5f, "Scalar assignment z");
        }

        // Compound assignment operators test
        {
            float3 v(1.0f, 2.0f, 3.0f);

            v += float3(3.0f, 4.0f, 5.0f);
            suite.assert_approximately_equal(v, float3(4.0f, 6.0f, 8.0f), "Operator +=");

            v -= float3(1.0f, 2.0f, 3.0f);
            suite.assert_approximately_equal(v, float3(3.0f, 4.0f, 5.0f), "Operator -=");

            v *= float3(2.0f, 3.0f, 4.0f);
            suite.assert_approximately_equal(v, float3(6.0f, 12.0f, 20.0f), "Operator *=");

            v /= float3(2.0f, 3.0f, 4.0f);
            suite.assert_approximately_equal(v, float3(3.0f, 4.0f, 5.0f), "Operator /=");

            v *= 2.0f;
            suite.assert_approximately_equal(v, float3(6.0f, 8.0f, 10.0f), "Operator *= scalar");

            v /= 2.0f;
            suite.assert_approximately_equal(v, float3(3.0f, 4.0f, 5.0f), "Operator /= scalar");
        }

        // ============================================================================
        // 3. Binary and unary operators
        // ============================================================================
        suite.section("Binary and unary operators");

        // Addition test
        {
            float3 a(1.0f, 2.0f, 3.0f);
            float3 b(4.0f, 5.0f, 6.0f);
            float3 result = a + b;
            suite.assert_approximately_equal(result, float3(5.0f, 7.0f, 9.0f), "Operator +");
        }

        // Subtraction test
        {
            float3 a(5.0f, 6.0f, 7.0f);
            float3 b(2.0f, 3.0f, 4.0f);
            float3 result = a - b;
            suite.assert_approximately_equal(result, float3(3.0f, 3.0f, 3.0f), "Operator -");
        }

        // Component-wise multiplication test
        {
            float3 a(2.0f, 3.0f, 4.0f);
            float3 b(1.0f, 2.0f, 3.0f);
            float3 result = a * b;
            suite.assert_approximately_equal(result, float3(2.0f, 6.0f, 12.0f), "Operator * (component-wise)");
        }

        // Component-wise division test
        {
            float3 a(6.0f, 8.0f, 10.0f);
            float3 b(2.0f, 4.0f, 5.0f);
            float3 result = a / b;
            suite.assert_approximately_equal(result, float3(3.0f, 2.0f, 2.0f), "Operator / (component-wise)");
        }

        // Unary operators test
        {
            float3 a(1.0f, -2.0f, 3.0f);
            suite.assert_approximately_equal(+a, float3(1.0f, -2.0f, 3.0f), "Unary +");
            suite.assert_approximately_equal(-a, float3(-1.0f, 2.0f, -3.0f), "Unary -");
        }

        // Scalar operations test
        {
            float3 v(2.0f, 3.0f, 4.0f);

            float3 result1 = v * 2.0f;
            suite.assert_approximately_equal(result1, float3(4.0f, 6.0f, 8.0f), "Vector * scalar");

            float3 result2 = 2.0f * v;
            suite.assert_approximately_equal(result2, float3(4.0f, 6.0f, 8.0f), "Scalar * vector");

            float3 result3 = v / 2.0f;
            suite.assert_approximately_equal(result3, float3(1.0f, 1.5f, 2.0f), "Vector / scalar");

            float3 result4 = 12.0f / v;
            suite.assert_approximately_equal(result4, float3(6.0f, 4.0f, 3.0f), "Scalar / vector");
        }

        // ============================================================================
        // 4. Access and conversion operators
        // ============================================================================
        suite.section("Access and conversion operators");

        // Index operator test
        {
            float3 v(7.0f, 8.0f, 9.0f);
            suite.assert_approximately_equal(v[0], 7.0f, "Operator [] index 0");
            suite.assert_approximately_equal(v[1], 8.0f, "Operator [] index 1");
            suite.assert_approximately_equal(v[2], 9.0f, "Operator [] index 2");

            v[0] = 10.0f;
            v[1] = 11.0f;
            v[2] = 12.0f;
            suite.assert_approximately_equal(v.x, 10.0f, "Operator [] mutable x");
            suite.assert_approximately_equal(v.y, 11.0f, "Operator [] mutable y");
            suite.assert_approximately_equal(v.z, 12.0f, "Operator [] mutable z");
        }

        // Pointer conversion test
        {
            float3 v(1.0f, 2.0f, 3.0f);
            const float* ptr = v;
            suite.assert_approximately_equal(ptr[0], 1.0f, "Conversion to const float* index 0");
            suite.assert_approximately_equal(ptr[1], 2.0f, "Conversion to const float* index 1");
            suite.assert_approximately_equal(ptr[2], 3.0f, "Conversion to const float* index 2");

            float* mutable_ptr = v;
            mutable_ptr[0] = 4.0f;
            suite.assert_approximately_equal(v.x, 4.0f, "Conversion to float* mutable");
        }

        // __m128 conversion test
        {
            float3 v(1.0f, 2.0f, 3.0f);
            __m128 simd = v;
            alignas(16) float temp[4];
            _mm_store_ps(temp, simd);
            suite.assert_approximately_equal(temp[0], 1.0f, "Conversion to __m128 x", 1e-6f);
            suite.assert_approximately_equal(temp[1], 2.0f, "Conversion to __m128 y", 1e-6f);
            suite.assert_approximately_equal(temp[2], 3.0f, "Conversion to __m128 z", 1e-6f);
        }

        // ============================================================================
        // 5. Mathematical functions (HLSL-style syntax)
        // ============================================================================
        suite.section("Mathematical functions (HLSL-style syntax)");

        // Length test
        {
            float3 v(2.0f, 3.0f, 6.0f);
            // √(4 + 9 + 36) = √49 = 7
            suite.assert_approximately_equal(length(v), 7.0f, "length()");
            suite.assert_approximately_equal(length_sq(v), 49.0f, "length_sq()");

            float3 zero(0.0f, 0.0f, 0.0f);
            suite.assert_approximately_equal(length(zero), 0.0f, "length() of zero vector");
        }

        // Normalization test
        {
            float3 v(2.0f, 3.0f, 6.0f);
            float3 normalized = normalize(v);
            float expected_len = 1.0f;
            suite.assert_approximately_equal(length(normalized), expected_len, "normalize() length", 1e-6f);
            suite.assert_approximately_equal(normalized.x, 2.0f / 7.0f, "normalize() x", 1e-6f);
            suite.assert_approximately_equal(normalized.y, 3.0f / 7.0f, "normalize() y", 1e-6f);
            suite.assert_approximately_equal(normalized.z, 6.0f / 7.0f, "normalize() z", 1e-6f);

            // Zero vector normalization test
            float3 zero(0.0f, 0.0f, 0.0f);
            float3 zero_norm = normalize(zero);
            suite.assert_approximately_equal(zero_norm, float3::zero(), "normalize() zero vector");
        }

        // Dot product test
        {
            float3 a(1.0f, 2.0f, 3.0f);
            float3 b(4.0f, 5.0f, 6.0f);
            float dot_result = dot(a, b);
            suite.assert_approximately_equal(dot_result, 32.0f, "dot()"); // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32

            // Orthogonal vectors
            float3 orth1(1.0f, 0.0f, 0.0f);
            float3 orth2(0.0f, 1.0f, 0.0f);
            suite.assert_approximately_equal(dot(orth1, orth2), 0.0f, "dot() orthogonal vectors");
        }

        // Cross product test
        {
            float3 a(1.0f, 0.0f, 0.0f);
            float3 b(0.0f, 1.0f, 0.0f);
            float3 cross_result = cross(a, b);
            suite.assert_approximately_equal(cross_result, float3(0.0f, 0.0f, 1.0f), "cross() i * j = k");

            float3 c(2.0f, 3.0f, 4.0f);
            float3 d(5.0f, 6.0f, 7.0f);
            float3 cross2 = cross(c, d);
            // (3*7 - 4*6, 4*5 - 2*7, 2*6 - 3*5) = (21-24, 20-14, 12-15) = (-3, 6, -3)
            suite.assert_approximately_equal(cross2, float3(-3.0f, 6.0f, -3.0f), "cross() arbitrary vectors");

            // Cross product of vector with itself is zero
            suite.assert_approximately_equal(cross(a, a), float3::zero(), "cross() vector with itself");
        }

        // Distance test
        {
            float3 a(1.0f, 2.0f, 3.0f);
            float3 b(4.0f, 6.0f, 8.0f);
            float dist = distance(a, b);
            float dist_sq = distance_sq(a, b);

            // (4-1)² + (6-2)² + (8-3)² = 9 + 16 + 25 = 50
            suite.assert_approximately_equal(dist, std::sqrt(50.0f), "distance()");
            suite.assert_approximately_equal(dist_sq, 50.0f, "distance_sq()");
        }

        // ============================================================================
        // 6. HLSL-like functions
        // ============================================================================
        suite.section("HLSL-like functions");

        // abs test
        {
            float3 v(-1.5f, 2.5f, -3.5f);
            float3 result = abs(v);
            suite.assert_approximately_equal(result, float3(1.5f, 2.5f, 3.5f), "abs()");
        }

        // sign test
        {
            float3 v(-2.0f, 0.0f, 3.0f);
            float3 result = sign(v);
            suite.assert_approximately_equal(result, float3(-1.0f, 0.0f, 1.0f), "sign()");
        }

        // floor test
        {
            float3 v(1.7f, -2.3f, 3.9f);
            float3 result = floor(v);
            suite.assert_approximately_equal(result, float3(1.0f, -3.0f, 3.0f), "floor()");
        }

        // ceil test
        {
            float3 v(1.2f, -2.7f, 3.1f);
            float3 result = ceil(v);
            suite.assert_approximately_equal(result, float3(2.0f, -2.0f, 4.0f), "ceil()");
        }

        // round test
        {
            float3 v(1.4f, 1.6f, -1.5f);
            float3 result = round(v);
            suite.assert_approximately_equal(result, float3(1.0f, 2.0f, -2.0f), "round()");
        }

        // frac test
        {
            float3 v(1.7f, -2.3f, 3.0f);
            float3 result = frac(v);
            suite.assert_approximately_equal(result.x, 0.7f, "frac() x", 1e-6f);
            suite.assert_approximately_equal(result.y, 0.7f, "frac() y", 1e-6f); // -2.3 - (-3) = 0.7
            suite.assert_approximately_equal(result.z, 0.0f, "frac() z", 1e-6f);
        }

        // saturate test
        {
            float3 v(-0.5f, 0.5f, 1.5f);
            float3 result = saturate(v);
            suite.assert_approximately_equal(result, float3(0.0f, 0.5f, 1.0f), "saturate()");
        }

        // step test
        {
            float3 v(0.5f, 1.0f, 1.5f);
            float3 result = step(1.0f, v);
            suite.assert_approximately_equal(result, float3(0.0f, 1.0f, 1.0f), "step()");
        }

        // clamp test (component-wise)
        {
            float3 v(0.5f, 1.5f, -0.5f);
            float3 min_val(0.0f, 0.0f, 0.0f);
            float3 max_val(1.0f, 1.0f, 1.0f);
            float3 result = clamp(v, min_val, max_val);
            suite.assert_approximately_equal(result, float3(0.5f, 1.0f, 0.0f), "clamp() component-wise");
        }

        // clamp test (scalar)
        {
            float3 v(0.5f, 1.5f, -0.5f);
            float3 result = clamp(v, 0.0f, 1.0f);
            suite.assert_approximately_equal(result, float3(0.5f, 1.0f, 0.0f), "clamp() scalar");
        }

        // min/max test
        {
            float3 a(1.0f, 3.0f, 5.0f);
            float3 b(2.0f, 2.0f, 6.0f);

            float3 min_result = min(a, b);
            suite.assert_approximately_equal(min_result, float3(1.0f, 2.0f, 5.0f), "min()");

            float3 max_result = max(a, b);
            suite.assert_approximately_equal(max_result, float3(2.0f, 3.0f, 6.0f), "max()");
        }

        // smoothstep test
        {
            float3 v(0.25f, 0.5f, 0.75f);
            float3 result = smoothstep(0.0f, 1.0f, v);
            // smoothstep formula: t*t*(3-2t) for t in [0,1]
            float expected_x = 0.25f * 0.25f * (3.0f - 2.0f * 0.25f); // ~0.15625
            float expected_y = 0.5f; // 0.5*0.5*(3-1) = 0.25*2 = 0.5
            float expected_z = 0.75f * 0.75f * (3.0f - 2.0f * 0.75f); // 0.5625*(3-1.5)=0.5625*1.5=0.84375

            suite.assert_approximately_equal(result.x, expected_x, "smoothstep() x", 1e-6f);
            suite.assert_approximately_equal(result.y, expected_y, "smoothstep() y", 1e-6f);
            suite.assert_approximately_equal(result.z, expected_z, "smoothstep() z", 1e-6f);
        }

        // ============================================================================
        // 7. Geometric operations
        // ============================================================================
        suite.section("Geometric operations");

        // Reflection test
        {
            float3 incident(1.0f, -1.0f, 0.0f);
            float3 normal(0.0f, 1.0f, 0.0f); // Up normal
            normal = normalize(normal);
            float3 reflected = reflect(incident, normal);
            // R = I - 2*(I·N)*N = (1,-1,0) - 2*(-1)*(0,1,0) = (1,-1,0) + (0,2,0) = (1,1,0)
            suite.assert_approximately_equal(reflected, float3(1.0f, 1.0f, 0.0f), "reflect()");
        }

        // Refraction test (total internal reflection)
        {
            // Water to air transition: n_water = 1.33, n_air = 1.0
            // eta = n_incident / n_transmitted = 1.33 / 1.0 = 1.33
            float eta_water_to_air = 1.33f;

            // Critical angle: θ_c = arcsin(1/eta) = arcsin(1/1.33) ≈ 48.8°
            // 60° > 48.8° → total internal reflection expected
            float3 incident_large(0.866f, -0.5f, 0.0f); // 60° angle
            float3 normal(0.0f, 1.0f, 0.0f);
            normal = normalize(normal);

            float3 total_reflection = refract(incident_large, normal, eta_water_to_air);
            // Should return zero vector for total internal reflection
            suite.assert_approximately_equal(total_reflection, float3::zero(),
                "refract() total internal reflection", 1e-6f);
        }

        // Projection test
        {
            float3 v(2.0f, 3.0f, 4.0f);
            float3 onto(1.0f, 0.0f, 0.0f); // X axis

            float3 projected = project(v, onto);
            suite.assert_approximately_equal(projected, float3(2.0f, 0.0f, 0.0f), "project() onto X axis");

            // Projection onto itself should return itself
            float3 self_projected = project(v, v);
            suite.assert_approximately_equal(self_projected, v, "project() onto itself");
        }

        // Rejection test
        {
            float3 v(2.0f, 3.0f, 4.0f);
            float3 onto(1.0f, 0.0f, 0.0f); // X axis

            float3 rejected = reject(v, onto);
            // v = (2,3,4), projection on X = (2,0,0), rejection = (0,3,4)
            suite.assert_approximately_equal(rejected, float3(0.0f, 3.0f, 4.0f), "reject() from X axis");

            // Rejection from itself should return zero
            float3 self_rejected = reject(v, v);
            suite.assert_approximately_equal(self_rejected, float3::zero(), "reject() from itself");
        }

        // Linear interpolation test
        {
            float3 a(0.0f, 0.0f, 0.0f);
            float3 b(10.0f, 20.0f, 30.0f);

            float3 lerp_result = lerp(a, b, 0.5f);
            suite.assert_approximately_equal(lerp_result, float3(5.0f, 10.0f, 15.0f), "lerp() at 0.5");

            float3 lerp_start = lerp(a, b, 0.0f);
            suite.assert_approximately_equal(lerp_start, a, "lerp() at 0.0");

            float3 lerp_end = lerp(a, b, 1.0f);
            suite.assert_approximately_equal(lerp_end, b, "lerp() at 1.0");
        }

        // Spherical linear interpolation test
        {
            float3 a(1.0f, 0.0f, 0.0f);
            float3 b(0.0f, 1.0f, 0.0f);

            a = normalize(a);
            b = normalize(b);

            float3 slerp_result = slerp(a, b, 0.5f);
            float expected_length = 1.0f;
            suite.assert_approximately_equal(length(slerp_result), expected_length, "slerp() length", 1e-6f);

            // Midpoint between (1,0,0) and (0,1,0) should be approximately (√2/2, √2/2, 0)
            float expected_val = std::sqrt(2.0f) / 2.0f;
            suite.assert_approximately_equal(slerp_result.x, expected_val, "slerp() x at 0.5", 1e-6f);
            suite.assert_approximately_equal(slerp_result.y, expected_val, "slerp() y at 0.5", 1e-6f);
            suite.assert_approximately_equal(slerp_result.z, 0.0f, "slerp() z at 0.5", 1e-6f);
        }

        // Angle between test
        {
            float3 a(1.0f, 0.0f, 0.0f);
            float3 b(0.0f, 1.0f, 0.0f);
            float angle = angle_between(a, b);
            suite.assert_approximately_equal(angle, PI / 2.0f, "angle_between() 90 degrees", 1e-6f);
        }

        // ============================================================================
// 8. Swizzle operations
// ============================================================================
        suite.section("Swizzle operations");

        {
            float3 v(2.0f, 3.0f, 4.0f);

            // 2-component swizzles
            suite.assert_approximately_equal(v.xx(), float2(2.0f, 2.0f), "xx()");
            suite.assert_approximately_equal(v.xy(), float2(2.0f, 3.0f), "xy()");
            suite.assert_approximately_equal(v.xz(), float2(2.0f, 4.0f), "xz()");
            suite.assert_approximately_equal(v.yx(), float2(3.0f, 2.0f), "yx()");
            suite.assert_approximately_equal(v.yy(), float2(3.0f, 3.0f), "yy()");
            suite.assert_approximately_equal(v.yz(), float2(3.0f, 4.0f), "yz()");
            suite.assert_approximately_equal(v.zx(), float2(4.0f, 2.0f), "zx()");
            suite.assert_approximately_equal(v.zy(), float2(4.0f, 3.0f), "zy()");
            suite.assert_approximately_equal(v.zz(), float2(4.0f, 4.0f), "zz()");

            // 3-component swizzles (selected ones)
            suite.assert_approximately_equal(v.xxx(), float3(2.0f, 2.0f, 2.0f), "xxx()");
            suite.assert_approximately_equal(v.xxy(), float3(2.0f, 2.0f, 3.0f), "xxy()");
            suite.assert_approximately_equal(v.xxz(), float3(2.0f, 2.0f, 4.0f), "xxz()");
            suite.assert_approximately_equal(v.xyx(), float3(2.0f, 3.0f, 2.0f), "xyx()");
            suite.assert_approximately_equal(v.xyy(), float3(2.0f, 3.0f, 3.0f), "xyy()");
            suite.assert_approximately_equal(v.xyz(), float3(2.0f, 3.0f, 4.0f), "xyz()");
            suite.assert_approximately_equal(v.xzx(), float3(2.0f, 4.0f, 2.0f), "xzx()");
            suite.assert_approximately_equal(v.xzy(), float3(2.0f, 4.0f, 3.0f), "xzy()");
            suite.assert_approximately_equal(v.xzz(), float3(2.0f, 4.0f, 4.0f), "xzz()");

            suite.assert_approximately_equal(v.yxx(), float3(3.0f, 2.0f, 2.0f), "yxx()");
            suite.assert_approximately_equal(v.yxy(), float3(3.0f, 2.0f, 3.0f), "yxy()");
            suite.assert_approximately_equal(v.yxz(), float3(3.0f, 2.0f, 4.0f), "yxz()");
            suite.assert_approximately_equal(v.yyx(), float3(3.0f, 3.0f, 2.0f), "yyx()");
            suite.assert_approximately_equal(v.yyy(), float3(3.0f, 3.0f, 3.0f), "yyy()");
            suite.assert_approximately_equal(v.yyz(), float3(3.0f, 3.0f, 4.0f), "yyz()");
            suite.assert_approximately_equal(v.yzx(), float3(3.0f, 4.0f, 2.0f), "yzx()");
            suite.assert_approximately_equal(v.yzy(), float3(3.0f, 4.0f, 3.0f), "yzy()");
            suite.assert_approximately_equal(v.yzz(), float3(3.0f, 4.0f, 4.0f), "yzz()");

            suite.assert_approximately_equal(v.zxx(), float3(4.0f, 2.0f, 2.0f), "zxx()");
            suite.assert_approximately_equal(v.zxy(), float3(4.0f, 2.0f, 3.0f), "zxy()");
            suite.assert_approximately_equal(v.zxz(), float3(4.0f, 2.0f, 4.0f), "zxz()");
            suite.assert_approximately_equal(v.zyx(), float3(4.0f, 3.0f, 2.0f), "zyx()");
            suite.assert_approximately_equal(v.zyy(), float3(4.0f, 3.0f, 3.0f), "zyy()");
            suite.assert_approximately_equal(v.zyz(), float3(4.0f, 3.0f, 4.0f), "zyz()");
            suite.assert_approximately_equal(v.zzx(), float3(4.0f, 4.0f, 2.0f), "zzx()");
            suite.assert_approximately_equal(v.zzy(), float3(4.0f, 4.0f, 3.0f), "zzy()");
            suite.assert_approximately_equal(v.zzz(), float3(4.0f, 4.0f, 4.0f), "zzz()");

            // Color swizzles (1-component)
            suite.assert_approximately_equal(v.r(), 2.0f, "r()");
            suite.assert_approximately_equal(v.g(), 3.0f, "g()");
            suite.assert_approximately_equal(v.b(), 4.0f, "b()");

            // Color swizzles (2-component)
            suite.assert_approximately_equal(v.rr(), float2(2.0f, 2.0f), "rr()");
            suite.assert_approximately_equal(v.rg(), float2(2.0f, 3.0f), "rg()");
            suite.assert_approximately_equal(v.rb(), float2(2.0f, 4.0f), "rb()");
            suite.assert_approximately_equal(v.gr(), float2(3.0f, 2.0f), "gr()");
            suite.assert_approximately_equal(v.gg(), float2(3.0f, 3.0f), "gg()");
            suite.assert_approximately_equal(v.gb(), float2(3.0f, 4.0f), "gb()");
            suite.assert_approximately_equal(v.br(), float2(4.0f, 2.0f), "br()");
            suite.assert_approximately_equal(v.bg(), float2(4.0f, 3.0f), "bg()");
            suite.assert_approximately_equal(v.bb(), float2(4.0f, 4.0f), "bb()");

            // Color swizzles (3-component - selected ones)
            suite.assert_approximately_equal(v.rrr(), float3(2.0f, 2.0f, 2.0f), "rrr()");
            suite.assert_approximately_equal(v.rgb(), float3(2.0f, 3.0f, 4.0f), "rgb()");
            suite.assert_approximately_equal(v.bgr(), float3(4.0f, 3.0f, 2.0f), "bgr()");
            suite.assert_approximately_equal(v.gbr(), float3(3.0f, 4.0f, 2.0f), "gbr()");
            suite.assert_approximately_equal(v.brg(), float3(4.0f, 2.0f, 3.0f), "brg()");
            suite.assert_approximately_equal(v.grb(), float3(3.0f, 2.0f, 4.0f), "grb()");
            suite.assert_approximately_equal(v.rbg(), float3(2.0f, 4.0f, 3.0f), "rbg()");

            // Texture coordinate swizzles
            suite.assert_approximately_equal(v.st(), float2(2.0f, 3.0f), "st()");
            suite.assert_approximately_equal(v.ts(), float2(3.0f, 2.0f), "ts()");
            suite.assert_approximately_equal(v.sp(), float2(2.0f, 4.0f), "sp()");
            suite.assert_approximately_equal(v.ps(), float2(4.0f, 2.0f), "ps()");

            // Utility swizzle functions
            suite.assert_approximately_equal(v.max_component(), 4.0f, "max_component()");
            suite.assert_approximately_equal(v.min_component(), 2.0f, "min_component()");
            suite.assert_equal(v.max_component_index(), 2, "max_component_index()");
            suite.assert_equal(v.min_component_index(), 0, "min_component_index()");
            suite.assert_approximately_equal(v.sum(), 9.0f, "sum()");
            suite.assert_approximately_equal(v.product(), 24.0f, "product()");
            suite.assert_approximately_equal(v.average(), 3.0f, "average()");
        }

        // ============================================================================
        // 9. Utility methods
        // ============================================================================
        suite.section("Utility methods");

        // isValid test
        {
            float3 valid(1.0f, 2.0f, 3.0f);
            suite.assert_true(isValid(valid), "isValid() for valid vector");

            suite.skip_test("isValid() with NaN/INF", "Requires special NaN/INF construction");
        }

        // approximately test
        {
            float3 a(1.0f, 2.0f, 3.0f);
            float3 b(1.000001f, 2.000001f, 3.000001f);
            float3 c(1.1f, 2.1f, 3.1f);

            suite.assert_true(approximately(a, b, 1e-5f), "approximately() within epsilon");
            suite.assert_false(approximately(a, c, 1e-5f), "approximately() outside epsilon");
        }

        // approximately_zero test
        {
            float3 zero(0.0f, 0.0f, 0.0f);
            float3 near_zero(0.000001f, 0.000001f, 0.000001f);
            float3 not_zero(0.1f, 0.1f, 0.1f);

            // Using length_sq for comparison
            suite.assert_true(length_sq(zero) <= 1e-10f, "Zero vector has zero length_sq");
            suite.assert_true(length_sq(near_zero) <= 1e-8f, "Near zero vector has small length_sq");
            suite.assert_false(length_sq(not_zero) <= 1e-10f, "Non-zero vector doesn't have small length_sq");
        }

        // is_normalized test
        {
            float3 normalized(0.267261f, 0.534522f, 0.801784f); // (1,2,3) normalized
            float3 not_normalized(1.0f, 2.0f, 3.0f);

            suite.assert_true(is_normalized(normalized, 1e-5f), "is_normalized() for normalized vector");
            suite.assert_false(is_normalized(not_normalized, 1e-5f), "is_normalized() for non-normalized");
        }

        // to_string test
        {
            float3 v(1.5f, 2.5f, 3.5f);
            std::string str = v.to_string();

            // Check for expected values in string
            suite.assert_true(str.find("1.5") != std::string::npos || str.find("1.500") != std::string::npos,
                "to_string() contains x value");
            suite.assert_true(str.find("2.5") != std::string::npos || str.find("2.500") != std::string::npos,
                "to_string() contains y value");
            suite.assert_true(str.find("3.5") != std::string::npos || str.find("3.500") != std::string::npos,
                "to_string() contains z value");
        }

        // data() test
        {
            float3 v(7.0f, 8.0f, 9.0f);
            const float* cdata = v.data();
            float* data = v.data();

            suite.assert_approximately_equal(cdata[0], 7.0f, "data() const access x");
            suite.assert_approximately_equal(cdata[1], 8.0f, "data() const access y");
            suite.assert_approximately_equal(cdata[2], 9.0f, "data() const access z");

            data[0] = 10.0f;
            suite.assert_approximately_equal(v.x, 10.0f, "data() mutable modification");
        }

        // Component operations test
        {
            float3 v(2.0f, 3.0f, 4.0f);

            suite.assert_approximately_equal(v.min_component(), 2.0f, "min_component()");
            suite.assert_approximately_equal(v.max_component(), 4.0f, "max_component()");
            suite.assert_equal(v.min_component_index(), 0, "min_component_index()");
            suite.assert_equal(v.max_component_index(), 2, "max_component_index()");
            suite.assert_approximately_equal(v.sum_components(), 9.0f, "sum_components()");
            suite.assert_approximately_equal(v.product_components(), 24.0f, "product_components()");
            suite.assert_approximately_equal(v.average(), 3.0f, "average()");
        }

        // has_nan, has_infinite, all_finite test
        {
            float3 v(1.0f, 2.0f, 3.0f);
            suite.assert_false(v.has_nan(), "has_nan() for normal vector");
            suite.assert_false(v.has_infinite(), "has_infinite() for normal vector");
            suite.assert_true(v.all_finite(), "all_finite() for normal vector");

            suite.skip_test("has_nan() with NaN", "Requires NaN construction");
            suite.skip_test("has_infinite() with INF", "Requires INF construction");
        }

        // ============================================================================
        // 10. Comparison operators
        // ============================================================================
        suite.section("Comparison operators");

        {
            float3 a(1.0f, 2.0f, 3.0f);
            float3 b(1.0f, 2.0f, 3.0f);
            float3 c(1.1f, 2.1f, 3.1f);

            suite.assert_true(a == b, "Operator == for equal vectors");
            suite.assert_false(a == c, "Operator == for different vectors");
            suite.assert_false(a != b, "Operator != for equal vectors");
            suite.assert_true(a != c, "Operator != for different vectors");
        }

        // ============================================================================
        // 11. Global operators and functions
        // ============================================================================
        suite.section("Global operators and functions");

        // Test global operators (already tested above)
        {
            float3 a(2.0f, 3.0f, 4.0f);
            float3 b(1.0f, 2.0f, 3.0f);

            float3 add_result = a + b;
            suite.assert_approximately_equal(add_result, float3(3.0f, 5.0f, 7.0f), "Global operator +");

            float3 sub_result = a - b;
            suite.assert_approximately_equal(sub_result, float3(1.0f, 1.0f, 1.0f), "Global operator -");

            float3 mul_result = a * b;
            suite.assert_approximately_equal(mul_result, float3(2.0f, 6.0f, 12.0f), "Global operator *");

            float3 div_result = a / b;
            suite.assert_approximately_equal(div_result, float3(2.0f, 1.5f, 4.0f / 3.0f), "Global operator /", 1e-6f);
        }

        // Test global mathematical functions (already tested above)
        {
            float3 a(1.0f, 2.0f, 3.0f);
            float3 b(4.0f, 6.0f, 8.0f);

            suite.assert_approximately_equal(distance(a, b), std::sqrt(50.0f), "Global distance()");
            suite.assert_approximately_equal(distance_sq(a, b), 50.0f, "Global distance_sq()");
            suite.assert_approximately_equal(dot(a, b), 40.0f, "Global dot()");

            float3 cross_result = cross(a, b);
            // (2*8 - 3*6, 3*4 - 1*8, 1*6 - 2*4) = (16-18, 12-8, 6-8) = (-2, 4, -2)
            suite.assert_approximately_equal(cross_result, float3(-2.0f, 4.0f, -2.0f), "Global cross()");

            float3 norm = normalize(a);
            suite.assert_approximately_equal(length(norm), 1.0f, "Global normalize() length", 1e-6f);

            float3 lerp_result = lerp(a, b, 0.5f);
            suite.assert_approximately_equal(lerp_result, float3(2.5f, 4.0f, 5.5f), "Global lerp()");
        }

        // Test global approximately and other utilities
        {
            float3 a(1.0f, 2.0f, 3.0f);
            float3 b(1.000001f, 2.000001f, 3.000001f);

            suite.assert_true(approximately(a, b, 1e-5f), "Global approximately()");
            suite.assert_true(is_normalized(float3(1.0f, 0.0f, 0.0f), 1e-5f), "Global is_normalized()");
            suite.assert_true(isValid(a), "Global isValid()");
        }

        // Test global geometric functions
        {
            float3 incident(1.0f, -1.0f, 0.0f);
            float3 normal(0.0f, 1.0f, 0.0f);
            normal = normalize(normal);

            float3 reflected = reflect(incident, normal);
            suite.assert_approximately_equal(reflected, float3(1.0f, 1.0f, 0.0f), "Global reflect()");

            float3 v(2.0f, 3.0f, 4.0f);
            float3 onto(1.0f, 0.0f, 0.0f);

            float3 projected = project(v, onto);
            suite.assert_approximately_equal(projected, float3(2.0f, 0.0f, 0.0f), "Global project()");

            float3 rejected = reject(v, onto);
            suite.assert_approximately_equal(rejected, float3(0.0f, 3.0f, 4.0f), "Global reject()");
        }

        // Test global HLSL functions (already tested above)
        {
            float3 v(-1.5f, 2.5f, -3.5f);

            suite.assert_approximately_equal(abs(v), float3(1.5f, 2.5f, 3.5f), "Global abs()");
            suite.assert_approximately_equal(sign(v), float3(-1.0f, 1.0f, -1.0f), "Global sign()");
            suite.assert_approximately_equal(floor(v), float3(-2.0f, 2.0f, -4.0f), "Global floor()");
            suite.assert_approximately_equal(ceil(v), float3(-1.0f, 3.0f, -3.0f), "Global ceil()");
            suite.assert_approximately_equal(saturate(float3(-0.5f, 0.5f, 1.5f)),
                float3(0.0f, 0.5f, 1.0f), "Global saturate()");
        }

        // Test global clamp, min, max
        {
            float3 v(0.5f, 1.5f, -0.5f);
            float3 min_val(0.0f, 0.0f, 0.0f);
            float3 max_val(1.0f, 1.0f, 1.0f);

            float3 clamped = clamp(v, min_val, max_val);
            suite.assert_approximately_equal(clamped, float3(0.5f, 1.0f, 0.0f), "Global clamp()");

            float3 a(1.0f, 3.0f, 5.0f);
            float3 b(2.0f, 2.0f, 6.0f);

            float3 min_result = min(a, b);
            suite.assert_approximately_equal(min_result, float3(1.0f, 2.0f, 5.0f), "Global min()");

            float3 max_result = max(a, b);
            suite.assert_approximately_equal(max_result, float3(2.0f, 3.0f, 6.0f), "Global max()");
        }

        // Test global component operations
        {
            float3 v(2.0f, 3.0f, 4.0f);

            suite.assert_approximately_equal(min_component(v), 2.0f, "Global min_component()");
            suite.assert_approximately_equal(max_component(v), 4.0f, "Global max_component()");
            suite.assert_approximately_equal(sum_components(v), 9.0f, "Global sum_components()");
            suite.assert_approximately_equal(product_components(v), 24.0f, "Global product_components()");
            suite.assert_approximately_equal(average(v), 3.0f, "Global average()");
        }

        // ============================================================================
        // 12. Edge cases
        // ============================================================================
        suite.section("Edge cases");

        // Test with very small values
        {
            float epsilon = 1e-30f;
            float3 tiny(epsilon, epsilon, epsilon);
            // Use length_sq for comparison
            suite.assert_true(length_sq(tiny) <= 1e-50f, "Tiny values have very small length_sq");
        }

        // Test with very large values
        {
            float large = 1e10f;
            float3 huge(large, large, large);
            suite.assert_false(length_sq(huge) <= 1.0f, "Huge values don't have small length_sq");

            float3 normalized_huge = normalize(huge);
            float expected_length = 1.0f;
            suite.assert_approximately_equal(length(normalized_huge), expected_length,
                "Normalize huge values", 1e-6f);
        }

        // Test division by zero (vector)
        {
            float3 a(1.0f, 2.0f, 3.0f);
            float3 zero_vec(0.0f, 0.0f, 0.0f);

            // Should produce infinities or NaN
            float3 result = a / zero_vec;

            // Check that result contains non-finite values
            suite.assert_true(!std::isfinite(result.x) || !std::isfinite(result.y) || !std::isfinite(result.z),
                "Division by zero vector produces non-finite values");
        }

        // Test division by zero (scalar)
        {
            float3 v(1.0f, 2.0f, 3.0f);
            float3 result = v / 0.0f;

            suite.assert_true(!std::isfinite(result.x) && !std::isfinite(result.y) && !std::isfinite(result.z),
                "Division by zero scalar produces non-finite values");
        }

        // Test normalization of very small vector
        {
            float3 tiny(1e-20f, 1e-20f, 1e-20f);
            float3 normalized = normalize(tiny);

            // Should return zero vector since length is less than epsilon
            suite.assert_approximately_equal(normalized, float3::zero(),
                "Normalize tiny vector returns zero");
        }

        // Test slerp with parallel vectors
        {
            float3 a(1.0f, 0.0f, 0.0f);
            float3 b(2.0f, 0.0f, 0.0f); // Collinear but not normalized

            a = normalize(a);
            b = normalize(b);

            float3 slerp_result = slerp(a, b, 0.5f);
            suite.assert_approximately_equal(length(slerp_result), 1.0f,
                "slerp() with parallel vectors length", 1e-6f);
            suite.assert_approximately_equal(slerp_result, a,
                "slerp() with parallel vectors returns first", 1e-6f);
        }

        // Test slerp with opposite vectors
        {
            float3 a(1.0f, 0.0f, 0.0f);
            float3 b(-1.0f, 0.0f, 0.0f);

            a = normalize(a);
            b = normalize(b);

            float3 slerp_result = slerp(a, b, 0.5f);
            // With opposite vectors, slerp should work correctly
            suite.assert_approximately_equal(length(slerp_result), 1.0f,
                "slerp() with opposite vectors length", 1e-6f);
        }

        // Test reflection with zero normal
        {
            float3 v(1.0f, 2.0f, 3.0f);
            float3 zero_normal(0.0f, 0.0f, 0.0f);

            float3 reflected = reflect(v, zero_normal);
            // R = I - 2*(I·N)*N = I - 0 = I
            suite.assert_approximately_equal(reflected, v, "Reflect with zero normal returns original");
        }

        // Test projection onto zero vector
        {
            float3 v(1.0f, 2.0f, 3.0f);
            float3 zero(0.0f, 0.0f, 0.0f);

            float3 projected = project(v, zero);
            suite.assert_approximately_equal(projected, float3::zero(), "Project onto zero vector returns zero");
        }

        // Test rejection from zero vector
        {
            float3 v(1.0f, 2.0f, 3.0f);
            float3 zero(0.0f, 0.0f, 0.0f);

            float3 rejected = reject(v, zero);
            suite.assert_approximately_equal(rejected, v, "Reject from zero vector returns original");
        }

        // Test is_normalized for zero vector
        {
            float3 zero(0.0f, 0.0f, 0.0f);
            suite.assert_false(is_normalized(zero), "Zero vector is not normalized");
        }

        // Test are_orthogonal and is_orthonormal_basis
        {
            float3 x(1.0f, 0.0f, 0.0f);
            float3 y(0.0f, 1.0f, 0.0f);
            float3 z(0.0f, 0.0f, 1.0f);

            suite.assert_true(are_orthogonal(x, y, 1e-6f), "are_orthogonal() for orthogonal vectors");
            suite.assert_true(is_orthonormal_basis(x, y, z, 1e-6f), "is_orthonormal_basis() for standard basis");

            float3 not_orth(1.0f, 1.0f, 0.0f);
            suite.assert_false(are_orthogonal(x, not_orth, 1e-6f), "are_orthogonal() for non-orthogonal vectors");
        }
    }
}
