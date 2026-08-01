// Author: DeepSeek, NSDeathman
// Test suite for Math::half2 class

#include "AutotestCore.h"

namespace AfterMathTests
{
    void RunHalf2Tests(TestSuite& suite)
    {
        using namespace AfterMath;

        // Constants for half tests
        constexpr float HALF_EPSILON = 0.02f;        // General half precision
        constexpr float HALF_MATH_EPSILON = 2e-3f;   // Mathematical functions
        constexpr float HALF_ANGLE_EPSILON = 0.2f;   // Trigonometry
        constexpr float HALF_LARGE_EPSILON = 0.5f;   // Large values

        // ============================================================================
        // 1. Constructors
        // ============================================================================
        suite.section("Constructors");

        // Test default constructor
        {
            half2 v;
            suite.assert_approximately_equal(float(v.x), 0.0f, "Default constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 0.0f, "Default constructor y", HALF_EPSILON);
        }

        // Test constructor with half components
        {
            half2 v(half(1.5f), half(2.5f));
            suite.assert_approximately_equal(float(v.x), 1.5f, "Half component constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Half component constructor y", HALF_EPSILON);
        }

        // Test constructor with float components
        {
            half2 v(1.5f, 2.5f);
            suite.assert_approximately_equal(float(v.x), 1.5f, "Float component constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Float component constructor y", HALF_EPSILON);
        }

        // Test constructor with scalar (half)
        {
            half2 v(half(3.0f));
            suite.assert_approximately_equal(float(v.x), 3.0f, "Half scalar constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Half scalar constructor y", HALF_EPSILON);
        }

        // Test constructor with scalar (float)
        {
            half2 v(3.0f);
            suite.assert_approximately_equal(float(v.x), 3.0f, "Float scalar constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Float scalar constructor y", HALF_EPSILON);
        }

        // Test constructor from float2
        {
            float2 fv(4.0f, 5.0f);
            half2 v(fv);
            suite.assert_approximately_equal(float(v.x), 4.0f, "float2 constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 5.0f, "float2 constructor y", HALF_EPSILON);
        }

        // Test copy constructor
        {
            half2 original(6.0f, 7.0f);
            half2 copy(original);
            suite.assert_approximately_equal(float(copy.x), 6.0f, "Copy constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(copy.y), 7.0f, "Copy constructor y", HALF_EPSILON);
        }

        // Test static constructors
        {
            half2 zero = half2::zero();
            suite.assert_approximately_equal(float(zero.x), 0.0f, "zero() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero.y), 0.0f, "zero() y", HALF_EPSILON);

            half2 one = half2::one();
            suite.assert_approximately_equal(float(one.x), 1.0f, "one() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(one.y), 1.0f, "one() y", HALF_EPSILON);

            half2 unit_x = half2::unit_x();
            suite.assert_approximately_equal(float(unit_x.x), 1.0f, "unit_x() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_x.y), 0.0f, "unit_x() y", HALF_EPSILON);

            half2 unit_y = half2::unit_y();
            suite.assert_approximately_equal(float(unit_y.x), 0.0f, "unit_y() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_y.y), 1.0f, "unit_y() y", HALF_EPSILON);

            half2 uv = half2::uv(half(0.3f), half(0.7f));
            suite.assert_approximately_equal(float(uv.x), 0.3f, "uv() u", HALF_EPSILON);
            suite.assert_approximately_equal(float(uv.y), 0.7f, "uv() v", HALF_EPSILON);
        }

        // ============================================================================
        // 2. Assignment Operators
        // ============================================================================
        suite.section("Assignment Operators");

        // Test assignment with half scalar
        {
            half2 v;
            v = half(2.5f);
            suite.assert_approximately_equal(float(v.x), 2.5f, "Half scalar assignment x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Half scalar assignment y", HALF_EPSILON);
        }

        // Test assignment with float scalar
        {
            half2 v;
            v = 2.5f;
            suite.assert_approximately_equal(float(v.x), 2.5f, "Float scalar assignment x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Float scalar assignment y", HALF_EPSILON);
        }

        // Test assignment with float2
        {
            half2 v;
            float2 fv(3.5f, 4.5f);
            v = fv;
            suite.assert_approximately_equal(float(v.x), 3.5f, "float2 assignment x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.5f, "float2 assignment y", HALF_EPSILON);
        }

        // Test compound assignment operators (half2)
        {
            half2 v(1.0f, 2.0f);

            v += half2(3.0f, 4.0f);
            suite.assert_approximately_equal(float(v.x), 4.0f, "Operator += x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 6.0f, "Operator += y", HALF_EPSILON);

            v -= half2(1.0f, 2.0f);
            suite.assert_approximately_equal(float(v.x), 3.0f, "Operator -= x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.0f, "Operator -= y", HALF_EPSILON);

            v *= half2(2.0f, 3.0f);
            suite.assert_approximately_equal(float(v.x), 6.0f, "Operator *= x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 12.0f, "Operator *= y", HALF_EPSILON);

            v /= half2(2.0f, 3.0f);
            suite.assert_approximately_equal(float(v.x), 3.0f, "Operator /= x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.0f, "Operator /= y", HALF_EPSILON);
        }

        // Test compound assignment operators (scalars)
        {
            half2 v(2.0f, 3.0f);

            v *= half(2.0f);
            suite.assert_approximately_equal(float(v.x), 4.0f, "Operator *= half scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 6.0f, "Operator *= half scalar y", HALF_EPSILON);

            v /= half(2.0f);
            suite.assert_approximately_equal(float(v.x), 2.0f, "Operator /= half scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Operator /= half scalar y", HALF_EPSILON);

            v *= 2.0f;
            suite.assert_approximately_equal(float(v.x), 4.0f, "Operator *= float scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 6.0f, "Operator *= float scalar y", HALF_EPSILON);

            v /= 2.0f;
            suite.assert_approximately_equal(float(v.x), 2.0f, "Operator /= float scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Operator /= float scalar y", HALF_EPSILON);
        }

        // ============================================================================
        // 3. Binary Operators
        // ============================================================================
        suite.section("Binary Operators");

        // Test addition
        {
            half2 a(1.0f, 2.0f);
            half2 b(3.0f, 4.0f);
            half2 result = a + b;
            suite.assert_approximately_equal(float(result.x), 4.0f, "Operator + x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 6.0f, "Operator + y", HALF_EPSILON);
        }

        // Test subtraction
        {
            half2 a(5.0f, 6.0f);
            half2 b(2.0f, 3.0f);
            half2 result = a - b;
            suite.assert_approximately_equal(float(result.x), 3.0f, "Operator - x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 3.0f, "Operator - y", HALF_EPSILON);
        }

        // Test unary operators
        {
            half2 a(1.0f, 2.0f);
            half2 pos = +a;
            suite.assert_approximately_equal(float(pos.x), 1.0f, "Unary + x", HALF_EPSILON);
            suite.assert_approximately_equal(float(pos.y), 2.0f, "Unary + y", HALF_EPSILON);

            half2 neg = -a;
            suite.assert_approximately_equal(float(neg.x), -1.0f, "Unary - x", HALF_EPSILON);
            suite.assert_approximately_equal(float(neg.y), -2.0f, "Unary - y", HALF_EPSILON);
        }

        // Test scalar operations (half)
        {
            half2 v(2.0f, 3.0f);

            half2 result1 = v + half(1.0f);
            suite.assert_approximately_equal(float(result1.x), 3.0f, "Vector + half x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result1.y), 4.0f, "Vector + half y", HALF_EPSILON);

            half2 result2 = half(1.0f) + v;
            suite.assert_approximately_equal(float(result2.x), 3.0f, "half + vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result2.y), 4.0f, "half + vector y", HALF_EPSILON);

            half2 result3 = v * half(2.0f);
            suite.assert_approximately_equal(float(result3.x), 4.0f, "Vector * half x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result3.y), 6.0f, "Vector * half y", HALF_EPSILON);

            half2 result4 = half(2.0f) * v;
            suite.assert_approximately_equal(float(result4.x), 4.0f, "half * vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result4.y), 6.0f, "half * vector y", HALF_EPSILON);

            half2 result5 = v / half(2.0f);
            suite.assert_approximately_equal(float(result5.x), 1.0f, "Vector / half x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result5.y), 1.5f, "Vector / half y", HALF_EPSILON);
        }

        // Test scalar operations (float)
        {
            half2 v(2.0f, 3.0f);

            half2 result1 = v + 1.0f;
            suite.assert_approximately_equal(float(result1.x), 3.0f, "Vector + float x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result1.y), 4.0f, "Vector + float y", HALF_EPSILON);

            half2 result2 = 1.0f + v;
            suite.assert_approximately_equal(float(result2.x), 3.0f, "float + vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result2.y), 4.0f, "float + vector y", HALF_EPSILON);

            half2 result3 = v * 2.0f;
            suite.assert_approximately_equal(float(result3.x), 4.0f, "Vector * float x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result3.y), 6.0f, "Vector * float y", HALF_EPSILON);

            half2 result4 = 2.0f * v;
            suite.assert_approximately_equal(float(result4.x), 4.0f, "float * vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result4.y), 6.0f, "float * vector y", HALF_EPSILON);

            half2 result5 = v / 2.0f;
            suite.assert_approximately_equal(float(result5.x), 1.0f, "Vector / float x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result5.y), 1.5f, "Vector / float y", HALF_EPSILON);
        }

        // Test operations with float2
        {
            half2 hv(1.0f, 2.0f);
            float2 fv(3.0f, 4.0f);

            half2 add = hv + fv;
            suite.assert_approximately_equal(float(add.x), 4.0f, "half2 + float2 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(add.y), 6.0f, "half2 + float2 y", HALF_EPSILON);

            half2 add2 = fv + hv;
            suite.assert_approximately_equal(float(add2.x), 4.0f, "float2 + half2 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(add2.y), 6.0f, "float2 + half2 y", HALF_EPSILON);
        }

        // ============================================================================
        // 4. Access Operators and Conversions
        // ============================================================================
        suite.section("Access Operators and Conversions");

        // Test index operator
        {
            half2 v(7.0f, 8.0f);
            suite.assert_approximately_equal(float(v[0]), 7.0f, "Operator [] index 0", HALF_EPSILON);
            suite.assert_approximately_equal(float(v[1]), 8.0f, "Operator [] index 1", HALF_EPSILON);

            v[0] = half(9.0f);
            v[1] = half(10.0f);
            suite.assert_approximately_equal(float(v.x), 9.0f, "Operator [] mutable x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 10.0f, "Operator [] mutable y", HALF_EPSILON);
        }

        // Test conversion to float2
        {
            half2 v(1.5f, 2.5f);
            float2 fv = float2(v);
            suite.assert_approximately_equal(fv.x, 1.5f, "Conversion to float2 x", HALF_EPSILON);
            suite.assert_approximately_equal(fv.y, 2.5f, "Conversion to float2 y", HALF_EPSILON);
        }

        // Test to_float2 function
        {
            half2 v(3.0f, 4.0f);
            float2 fv = to_float2(v);
            suite.assert_approximately_equal(fv.x, 3.0f, "to_float2 x", HALF_EPSILON);
            suite.assert_approximately_equal(fv.y, 4.0f, "to_float2 y", HALF_EPSILON);
        }

        // Test to_half2 function
        {
            float2 fv(3.0f, 4.0f);
            half2 v = to_half2(fv);
            suite.assert_approximately_equal(float(v.x), 3.0f, "to_half2 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.0f, "to_half2 y", HALF_EPSILON);
        }

        // ============================================================================
        // 5. Mathematical Functions (NEW HLSL SYNTAX)
        // ============================================================================
        suite.section("Mathematical Functions");

        // Test length
        {
            half2 v(3.0f, 4.0f);
            half len = length(v);
            half len_sq = length_sq(v);

            suite.assert_approximately_equal(float(len), 5.0f, "length()", HALF_EPSILON);
            suite.assert_approximately_equal(float(len_sq), 25.0f, "length_sq()", HALF_EPSILON);

            half2 zero(0.0f, 0.0f);
            suite.assert_approximately_equal(float(length(zero)), 0.0f, "length() of zero vector", HALF_EPSILON);
        }

        // Test normalization
        {
            half2 v(3.0f, 4.0f);
            half2 normalized = normalize(v);
            float normalized_len = float(length(normalized));

            suite.assert_approximately_equal(normalized_len, 1.0f, "normalize() length", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.x), 0.6f, "normalize() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.y), 0.8f, "normalize() y", HALF_EPSILON);

            // Test normalization of zero vector
            half2 zero(0.0f, 0.0f);
            half2 zero_norm = normalize(zero);
            suite.assert_approximately_equal(float(zero_norm.x), 0.0f, "normalize() zero vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero_norm.y), 0.0f, "normalize() zero vector y", HALF_EPSILON);
        }

        // Test dot product
        {
            half2 a(1.0f, 2.0f);
            half2 b(3.0f, 4.0f);
            half dot_result = dot(a, b);
            suite.assert_approximately_equal(float(dot_result), 11.0f, "dot()", HALF_EPSILON);

            // Global function dot
            half global_dot = dot(a, b);
            suite.assert_approximately_equal(float(global_dot), 11.0f, "global dot()", HALF_EPSILON);

            // Orthogonal vectors
            half2 orth1(1.0f, 0.0f);
            half2 orth2(0.0f, 1.0f);
            half orth_dot = dot(orth1, orth2);
            suite.assert_approximately_equal(float(orth_dot), 0.0f, "dot() orthogonal vectors", HALF_EPSILON);
        }

        // Test cross product (2D)
        {
            half2 a(1.0f, 2.0f);
            half2 b(3.0f, 4.0f);
            half cross_result = cross(a, b);
            suite.assert_approximately_equal(float(cross_result), -2.0f, "cross()", HALF_EPSILON);
        }

        // Test distance
        {
            half2 a(1.0f, 2.0f);
            half2 b(4.0f, 6.0f);
            half dist = distance(a, b);
            half dist_sq = distance_sq(a, b);

            // (4-1)² + (6-2)² = 9 + 16 = 25
            suite.assert_approximately_equal(float(dist), 5.0f, "distance()", HALF_EPSILON);
            suite.assert_approximately_equal(float(dist_sq), 25.0f, "distance_sq()", HALF_EPSILON);

            // Global functions distance and distance_sq
            half global_distance = distance(a, b);
            half global_distance_sq = distance_sq(a, b);
            suite.assert_approximately_equal(float(global_distance), 5.0f, "global distance()", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_distance_sq), 25.0f, "global distance_sq()", HALF_EPSILON);
        }

        // Test perpendicular
        {
            half2 v(2.0f, 3.0f);
            half2 perp = perpendicular(v);
            half2 global_perp = perpendicular(v);

            suite.assert_approximately_equal(float(perp.x), -3.0f, "perpendicular() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(perp.y), 2.0f, "perpendicular() y", HALF_EPSILON);

            suite.assert_approximately_equal(float(global_perp.x), -3.0f, "global perpendicular() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_perp.y), 2.0f, "global perpendicular() y", HALF_EPSILON);
        }

        // Test angle
        {
            half2 v(1.0f, 0.0f);
            half angle_result = angle(v);
            suite.assert_approximately_equal(float(angle_result), 0.0f, "angle() for (1,0)", HALF_ANGLE_EPSILON);

            half2 v2(0.0f, 1.0f);
            half angle2 = angle(v2);
            suite.assert_approximately_equal(float(angle2), Constants::Constants<float>::Pi / 2.0f,
                "angle() for (0,1)", HALF_ANGLE_EPSILON);
        }

        // Test angle between vectors
        {
            half2 a(1.0f, 0.0f);
            half2 b(0.0f, 1.0f);
            half angle_ab = angle_between(a, b);
            suite.assert_approximately_equal(float(angle_ab), Constants::Constants<float>::Pi / 2.0f,
                "angle_between() 90 degrees", HALF_ANGLE_EPSILON);
        }

        // ============================================================================
        // 6. HLSL-like Functions
        // ============================================================================
        suite.section("HLSL-like Functions");

        // Test abs
        {
            half2 v(-1.5f, 2.5f);
            half2 result = abs(v);
            half2 global_result = abs(v);

            suite.assert_approximately_equal(float(result.x), 1.5f, "abs() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 2.5f, "abs() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.x), 1.5f, "global abs() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.y), 2.5f, "global abs() y", HALF_EPSILON);
        }

        // Test sign
        {
            half2 v(-2.0f, 3.0f);
            half2 result = sign(v);
            suite.assert_approximately_equal(float(result.x), -1.0f, "sign() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 1.0f, "sign() y", HALF_EPSILON);
        }

        // Test floor
        {
            half2 v(1.7f, -2.3f);
            half2 result = floor(v);
            suite.assert_approximately_equal(float(result.x), 1.0f, "floor() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), -3.0f, "floor() y", HALF_EPSILON);
        }

        // Test ceil
        {
            half2 v(1.2f, -2.7f);
            half2 result = ceil(v);
            suite.assert_approximately_equal(float(result.x), 2.0f, "ceil() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), -2.0f, "ceil() y", HALF_EPSILON);
        }

        // Test round
        {
            half2 v(1.4f, 1.6f);
            half2 result = round(v);
            suite.assert_approximately_equal(float(result.x), 1.0f, "round() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 2.0f, "round() y", HALF_EPSILON);
        }

        // Test frac (HLSL semantics)
        {
            half2 v(1.7f, -2.3f);
            half2 result = frac(v);
            // HLSL: frac(x) = x - floor(x)
            // frac(1.7) = 1.7 - 1.0 = 0.7
            // frac(-2.3) = -2.3 - (-3.0) = 0.7
            suite.assert_approximately_equal(float(result.x), 0.7f, "frac() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.7f, "frac() y", HALF_EPSILON);
        }

        // Test saturate
        {
            half2 v(-0.5f, 1.5f);
            half2 result = saturate(v);
            half2 global_result = saturate(v);

            suite.assert_approximately_equal(float(result.x), 0.0f, "saturate() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 1.0f, "saturate() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.x), 0.0f, "global saturate() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.y), 1.0f, "global saturate() y", HALF_EPSILON);
        }

        // Test step
        {
            half2 v(0.5f, 1.5f);
            half2 result = step(half(1.0f), v);
            half2 global_result = step(half(1.0f), v);

            suite.assert_approximately_equal(float(result.x), 0.0f, "step() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 1.0f, "step() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.x), 0.0f, "global step() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.y), 1.0f, "global step() y", HALF_EPSILON);
        }

        // Test smoothstep
        {
            half2 v(0.5f, 1.5f);
            half2 result = smoothstep(half(0.0f), half(2.0f), v);
            // For t=0.25: 3t² - 2t³ = 3*0.0625 - 2*0.015625 = 0.1875 - 0.03125 = 0.15625
            // For t=0.75: 3*0.5625 - 2*0.421875 = 1.6875 - 0.84375 = 0.84375
            suite.assert_approximately_equal(float(result.x), 0.15625f, "smoothstep() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.84375f, "smoothstep() y", HALF_EPSILON);
        }

        // Test min/max
        {
            half2 a(1.0f, 3.0f);
            half2 b(2.0f, 2.0f);

            half2 min_result = min(a, b);
            half2 max_result = max(a, b);
            half2 global_min = min(a, b);
            half2 global_max = max(a, b);

            suite.assert_approximately_equal(float(min_result.x), 1.0f, "min() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(min_result.y), 2.0f, "min() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(max_result.x), 2.0f, "max() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(max_result.y), 3.0f, "max() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_min.x), 1.0f, "global min() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_min.y), 2.0f, "global min() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_max.x), 2.0f, "global max() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_max.y), 3.0f, "global max() y", HALF_EPSILON);
        }

        // Test clamp
        {
            half2 v(2.5f, -0.5f);
            half2 min_val(1.0f, 0.0f);
            half2 max_val(2.0f, 1.0f);

            half2 clamped = clamp(v, min_val, max_val);
            suite.assert_approximately_equal(float(clamped.x), 2.0f, "clamp() vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(clamped.y), 0.0f, "clamp() vector y", HALF_EPSILON);

            half2 clamped_scalar = clamp(v, 0.0f, 1.0f);
            suite.assert_approximately_equal(float(clamped_scalar.x), 1.0f, "clamp() scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(clamped_scalar.y), 0.0f, "clamp() scalar y", HALF_EPSILON);
        }

        // ============================================================================
        // 7. Swizzle Operations
        // ============================================================================
        suite.section("Swizzle Operations");

        {
            half2 v(2.0f, 3.0f);

            half2 yx = v.yx();
            suite.assert_approximately_equal(float(yx.x), 3.0f, "yx() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(yx.y), 2.0f, "yx() y", HALF_EPSILON);

            half2 xx = v.xx();
            suite.assert_approximately_equal(float(xx.x), 2.0f, "xx() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(xx.y), 2.0f, "xx() y", HALF_EPSILON);

            half2 yy = v.yy();
            suite.assert_approximately_equal(float(yy.x), 3.0f, "yy() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(yy.y), 3.0f, "yy() y", HALF_EPSILON);
        }

        // ============================================================================
        // 8. Texture Coordinates
        // ============================================================================
        suite.section("Texture Coordinates");

        {
            half2 uv(0.3f, 0.7f);

            half u = uv.u();
            half v = uv.v();
            suite.assert_approximately_equal(float(u), 0.3f, "u()", HALF_EPSILON);
            suite.assert_approximately_equal(float(v), 0.7f, "v()", HALF_EPSILON);

            uv.set_u(half(0.4f));
            uv.set_v(half(0.8f));
            suite.assert_approximately_equal(float(uv.x), 0.4f, "set_u()", HALF_EPSILON);
            suite.assert_approximately_equal(float(uv.y), 0.8f, "set_v()", HALF_EPSILON);
        }

        // ============================================================================
        // 9. Utility Methods
        // ============================================================================
        suite.section("Utility Methods");

        // Test isValid
        {
            half2 valid(1.0f, 2.0f);
            suite.assert_true(valid.is_valid(), "is_valid() for valid vector");

            suite.assert_true(is_valid(valid), "global is_valid() for valid vector");
        }

        // Test approximately
        {
            half2 a(1.0f, 2.0f);
            half2 b(1.001f, 2.001f);
            half2 c(1.1f, 2.1f);

            suite.assert_true(approximately(a, b, 0.01f), "approximately() within epsilon");
            suite.assert_false(approximately(a, c, 0.01f), "approximately() outside epsilon");

            bool global_approx = approximately(a, b, 0.01f);
            suite.assert_true(global_approx, "global approximately() within epsilon");
        }

        // Test approximately_zero
        {
            half2 zero(0.0f, 0.0f);
            half2 near_zero(0.001f, 0.001f);
            half2 not_zero(0.1f, 0.1f);

            suite.assert_true(approximately_zero(zero, 0.01f), "approximately_zero() for zero");
            suite.assert_true(approximately_zero(near_zero, 0.01f), "approximately_zero() for near zero");
            suite.assert_false(approximately_zero(not_zero, 0.01f), "approximately_zero() for non-zero");
        }

        // Test is_normalized
        {
            half2 normalized(0.6f, 0.8f);
            half2 not_normalized(1.0f, 2.0f);

            suite.assert_true(is_normalized(normalized, 0.01f), "is_normalized() for normalized vector");
            suite.assert_false(is_normalized(not_normalized, 0.01f), "is_normalized() for non-normalized");

            bool global_normalized = is_normalized(normalized, 0.01f);
            suite.assert_true(global_normalized, "global is_normalized() for normalized vector");
        }

        // Test to_string
        {
            half2 v(1.5f, 2.5f);
            std::string str = v.to_string();

            // Check if expected values are in the string
            suite.assert_true(str.find("1.5") != std::string::npos || str.find("1.500") != std::string::npos,
                "to_string() contains x value");
            suite.assert_true(str.find("2.5") != std::string::npos || str.find("2.500") != std::string::npos,
                "to_string() contains y value");
        }

        // Test data()
        {
            half2 v(7.0f, 8.0f);
            const half* cdata = v.data();
            half* data = v.data();

            suite.assert_approximately_equal(float(cdata[0]), 7.0f, "data() const access x", HALF_EPSILON);
            suite.assert_approximately_equal(float(cdata[1]), 8.0f, "data() const access y", HALF_EPSILON);

            data[0] = half(9.0f);
            suite.assert_approximately_equal(float(v.x), 9.0f, "data() mutable modification x", HALF_EPSILON);
        }

        // ============================================================================
        // 10. Comparison Operators
        // ============================================================================
        suite.section("Comparison Operators");

        {
            half2 a(1.0f, 2.0f);
            half2 b(1.0f, 2.0f);
            half2 c(1.1f, 2.1f);

            suite.assert_true(a == b, "Operator == for equal vectors");
            suite.assert_false(a == c, "Operator == for different vectors");
            suite.assert_false(a != b, "Operator != for equal vectors");
            suite.assert_true(a != c, "Operator != for different vectors");
        }

        // ============================================================================
        // 11. Special Values
        // ============================================================================
        suite.section("Special Values");

        // Test with zeros
        {
            half2 pos_zero(0.0f, 0.0f);
            half2 neg_zero(-0.0f, -0.0f);

            suite.assert_true(pos_zero.is_zero(), "is_zero() for positive zero");
            suite.assert_true(neg_zero.is_zero(), "is_zero() for negative zero");
            suite.assert_true(pos_zero.is_all_zero(), "is_all_zero() for positive zero");
            suite.assert_true(neg_zero.is_all_zero(), "is_all_zero() for negative zero");

            bool global_zero = is_zero(pos_zero);
            bool global_all_zero = is_all_zero(pos_zero);
            suite.assert_true(global_zero, "global is_zero()");
            suite.assert_true(global_all_zero, "global is_all_zero()");
        }

        // Test with infinities
        {
            half2 pos_inf(std::numeric_limits<float>::infinity(), 1.0f);
            half2 neg_inf(-std::numeric_limits<float>::infinity(), 1.0f);

            suite.assert_true(pos_inf.is_inf(), "is_inf() for vector with positive infinity");
            suite.assert_true(neg_inf.is_inf(), "is_inf() for vector with negative infinity");

            bool global_inf = is_inf(pos_inf);
            suite.assert_true(global_inf, "global is_inf()");
        }

        // Test with NaN
        {
            half2 nan_vec(std::numeric_limits<float>::quiet_NaN(), 1.0f);

            suite.assert_true(nan_vec.is_nan(), "is_nan() for vector with NaN");

            bool global_nan = is_nan(nan_vec);
            suite.assert_true(global_nan, "global is_nan()");
        }

        // Test with finite values
        {
            half2 finite(1.0f, 2.0f);

            suite.assert_true(finite.is_finite(), "is_finite() for finite vector");
            suite.assert_true(finite.is_all_finite(), "is_all_finite() for finite vector");

            bool global_finite = is_finite(finite);
            bool global_all_finite = is_all_finite(finite);
            suite.assert_true(global_finite, "global is_finite()");
            suite.assert_true(global_all_finite, "global is_all_finite()");
        }

        // Test with positive/negative values
        {
            half2 pos(1.0f, 2.0f);
            half2 neg(-1.0f, -2.0f);
            half2 mixed(-1.0f, 2.0f);

            suite.assert_true(pos.is_positive(), "is_positive() for positive vector");
            suite.assert_true(pos.is_all_positive(), "is_all_positive() for positive vector");
            suite.assert_true(neg.is_negative(), "is_negative() for negative vector");
            suite.assert_true(neg.is_all_negative(), "is_all_negative() for negative vector");
            suite.assert_true(mixed.is_positive(), "is_positive() for mixed vector");
            suite.assert_true(mixed.is_negative(), "is_negative() for mixed vector");
            suite.assert_false(mixed.is_all_positive(), "is_all_positive() for mixed vector");
            suite.assert_false(mixed.is_all_negative(), "is_all_negative() for mixed vector");

            bool global_positive = is_positive(pos);
            bool global_all_positive = is_all_positive(pos);
            suite.assert_true(global_positive, "global is_positive()");
            suite.assert_true(global_all_positive, "global is_all_positive()");
        }

        // ============================================================================
        // 12. Linear Interpolation
        // ============================================================================
        suite.section("Linear Interpolation");

        {
            half2 a(0.0f, 0.0f);
            half2 b(10.0f, 20.0f);

            half2 lerp_result = lerp(a, b, half(0.5f));
            suite.assert_approximately_equal(float(lerp_result.x), 5.0f, "lerp() at 0.5 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_result.y), 10.0f, "lerp() at 0.5 y", HALF_EPSILON);

            half2 lerp_float = lerp(a, b, 0.5f);
            suite.assert_approximately_equal(float(lerp_float.x), 5.0f, "lerp() with float at 0.5 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_float.y), 10.0f, "lerp() with float at 0.5 y", HALF_EPSILON);

            half2 global_lerp = lerp(a, b, half(0.5f));
            suite.assert_approximately_equal(float(global_lerp.x), 5.0f, "global lerp() at 0.5 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_lerp.y), 10.0f, "global lerp() at 0.5 y", HALF_EPSILON);

            half2 global_lerp_float = lerp(a, b, 0.5f);
            suite.assert_approximately_equal(float(global_lerp_float.x), 5.0f, "global lerp() with float at 0.5 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_lerp_float.y), 10.0f, "global lerp() with float at 0.5 y", HALF_EPSILON);

            half2 lerp_start = lerp(a, b, half(0.0f));
            suite.assert_approximately_equal(float(lerp_start.x), 0.0f, "lerp() at 0.0 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_start.y), 0.0f, "lerp() at 0.0 y", HALF_EPSILON);

            half2 lerp_end = lerp(a, b, half(1.0f));
            suite.assert_approximately_equal(float(lerp_end.x), 10.0f, "lerp() at 1.0 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_end.y), 20.0f, "lerp() at 1.0 y", HALF_EPSILON);
        }

        // ============================================================================
        // 13. Global Constants
        // ============================================================================
        suite.section("Global Constants");

        {
            suite.assert_approximately_equal(float(half2_Zero.x), 0.0f, "half2_Zero x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half2_Zero.y), 0.0f, "half2_Zero y", HALF_EPSILON);

            suite.assert_approximately_equal(float(half2_One.x), 1.0f, "half2_One x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half2_One.y), 1.0f, "half2_One y", HALF_EPSILON);

            suite.assert_approximately_equal(float(half2_UnitX.x), 1.0f, "half2_UnitX x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half2_UnitX.y), 0.0f, "half2_UnitX y", HALF_EPSILON);

            suite.assert_approximately_equal(float(half2_UnitY.x), 0.0f, "half2_UnitY x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half2_UnitY.y), 1.0f, "half2_UnitY y", HALF_EPSILON);

            suite.assert_approximately_equal(float(half2_UV_Zero.x), 0.0f, "half2_UV_Zero x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half2_UV_Zero.y), 0.0f, "half2_UV_Zero y", HALF_EPSILON);

            suite.assert_approximately_equal(float(half2_UV_One.x), 1.0f, "half2_UV_One x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half2_UV_One.y), 1.0f, "half2_UV_One y", HALF_EPSILON);

            suite.assert_approximately_equal(float(half2_UV_Half.x), 0.5f, "half2_UV_Half x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half2_UV_Half.y), 0.5f, "half2_UV_Half y", HALF_EPSILON);

            suite.assert_approximately_equal(float(half2_Right.x), 1.0f, "half2_Right x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half2_Right.y), 0.0f, "half2_Right y", HALF_EPSILON);

            suite.assert_approximately_equal(float(half2_Left.x), -1.0f, "half2_Left x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half2_Left.y), 0.0f, "half2_Left y", HALF_EPSILON);

            suite.assert_approximately_equal(float(half2_Up.x), 0.0f, "half2_Up x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half2_Up.y), 1.0f, "half2_Up y", HALF_EPSILON);

            suite.assert_approximately_equal(float(half2_Down.x), 0.0f, "half2_Down x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half2_Down.y), -1.0f, "half2_Down y", HALF_EPSILON);
        }

        // ============================================================================
        // 14. Edge Cases
        // ============================================================================
        suite.section("Edge Cases");

        // Test with very small values
        {
            half2 tiny(1e-6f, 1e-6f);
            suite.assert_true(approximately_zero(tiny, 1e-3f), "Tiny values approximately_zero");
        }

        // Test with very large values
        {
            half2 huge(50000.0f, 50000.0f);
            suite.assert_false(approximately_zero(huge), "Huge values not approximately_zero");

            // Normalization of large values
            half2 normalized_huge = normalize(huge);
            float normalized_len = float(length(normalized_huge));
            suite.assert_approximately_equal(normalized_len, 1.0f, "Normalize huge values length", HALF_EPSILON);
        }

        // Test division by zero (vector)
        {
            half2 a(1.0f, 2.0f);
            half2 zero_vec(0.0f, 0.0f);

            half2 result = a / zero_vec;
            suite.assert_true(result.x.is_inf() || result.x.is_nan(), "Division by zero vector x produces non-finite");
            suite.assert_true(result.y.is_inf() || result.y.is_nan(), "Division by zero vector y produces non-finite");
        }

        // Test division by zero (scalar)
        {
            half2 v(1.0f, 2.0f);
            half2 result = v / 0.0f;

            suite.assert_true(result.x.is_inf() || result.x.is_nan(), "Division by zero scalar x produces non-finite");
            suite.assert_true(result.y.is_inf() || result.y.is_nan(), "Division by zero scalar y produces non-finite");
        }

        // Test normalization of very small vector
        {
            half2 tiny(1e-20f, 1e-20f);
            half2 normalized = normalize(tiny);

            // Should return zero vector because length is less than epsilon
            suite.assert_approximately_equal(float(normalized.x), 0.0f, "Normalize tiny vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.y), 0.0f, "Normalize tiny vector y", HALF_EPSILON);
        }

        // Test smoothstep with edge0 = edge1
        {
            half2 v(0.5f, 1.5f);
            half2 result = smoothstep(half(1.0f), half(1.0f), v);
            // When edge0 = edge1, use step(edge0)
            half2 step_result = step(half(1.0f), v);
            suite.assert_approximately_equal(float(result.x), float(step_result.x), "smoothstep() with equal edges x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), float(step_result.y), "smoothstep() with equal edges y", HALF_EPSILON);
        }

        // Test dot product with self
        {
            half2 v(3.0f, 4.0f);
            half dot_self = dot(v, v);
            half expected = length_sq(v);
            suite.assert_approximately_equal(float(dot_self), float(expected), "Dot product with self equals length squared", HALF_EPSILON);
        }

        // Test cross product with self
        {
            half2 v(2.0f, 3.0f);
            half cross_self = cross(v, v);
            suite.assert_approximately_equal(float(cross_self), 0.0f, "Cross product with self equals zero", HALF_EPSILON);
        }

        // Test angle of zero vector
        {
            half2 zero(0.0f, 0.0f);
            half angle_val = angle(zero);
            // Angle of zero vector is undefined, but atan2(0,0) usually returns 0
            suite.assert_approximately_equal(float(angle_val), 0.0f, "Angle of zero vector", HALF_ANGLE_EPSILON);
        }

        // Test is_normalized for zero vector
        {
            half2 zero(0.0f, 0.0f);
            suite.assert_false(is_normalized(zero), "Zero vector is not normalized");
        }

        // Test with numbers close to max half value
        {
            half max_half = half::max_value();
            half2 max_vec(max_half, max_half);

            // Make sure values are not NaN or Inf
            suite.assert_true(max_vec.is_finite(), "Vector with max half values is finite");

            // Normalization of vector with max values
            half2 normalized = normalize(max_vec);
            float normalized_len = float(length(normalized));
            suite.assert_approximately_equal(normalized_len, 1.0f, "Normalize max values length", HALF_EPSILON);
        }

        // Test with denormalized numbers
        {
            half min_denorm = half::min_denormal_value();
            half2 denorm_vec(min_denorm, min_denorm);

            suite.assert_true(denorm_vec.is_finite(), "Vector with denormalized values is finite");

            // Multiplication of denormalized numbers
            half2 multiplied = denorm_vec * half(2.0f);
            suite.assert_true(multiplied.is_finite(), "Multiplication of denormalized values is finite");
        }

        // Test saturation with negative numbers
        {
            half2 v(-2.0f, 0.5f);
            half2 saturated = saturate(v);

            suite.assert_approximately_equal(float(saturated.x), 0.0f, "saturate() negative value", HALF_EPSILON);
            suite.assert_approximately_equal(float(saturated.y), 0.5f, "saturate() positive value < 1", HALF_EPSILON);

            half2 v2(1.5f, -0.5f);
            half2 saturated2 = saturate(v2);

            suite.assert_approximately_equal(float(saturated2.x), 1.0f, "saturate() positive value > 1", HALF_EPSILON);
            suite.assert_approximately_equal(float(saturated2.y), 0.0f, "saturate() negative value", HALF_EPSILON);
        }

        // Test rounding of boundary values
        {
            half2 v1(1.49f, 1.51f);
            half2 rounded1 = round(v1);
            suite.assert_approximately_equal(float(rounded1.x), 1.0f, "round() 1.49", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded1.y), 2.0f, "round() 1.51", HALF_EPSILON);

            half2 v2(-1.49f, -1.51f);
            half2 rounded2 = round(v2);
            suite.assert_approximately_equal(float(rounded2.x), -1.0f, "round() -1.49", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded2.y), -2.0f, "round() -1.51", HALF_EPSILON);
        }

        // Test floor/ceil boundary values
        {
            // Use values that preserve fractional part in half
            half2 v(1.5f, -1.5f);

            half2 floored = floor(v);
            suite.assert_approximately_equal(float(floored.x), 1.0f, "floor() 1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(floored.y), -2.0f, "floor() -1.5", HALF_EPSILON);

            half2 ceiled = ceil(v);
            suite.assert_approximately_equal(float(ceiled.x), 2.0f, "ceil() 1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(ceiled.y), -1.0f, "ceil() -1.5", HALF_EPSILON);
        }
    }
}
