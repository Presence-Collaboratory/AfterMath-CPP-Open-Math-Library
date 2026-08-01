// Author: DeepSeek, NSDeathman
// Test suite for AfterMath::half3 class

#include "AutotestCore.h"

namespace AfterMathTests
{
    void RunHalf3Tests(TestSuite& suite)
    {
        using namespace AfterMath;

        // Constants for half tests
        constexpr float HALF_EPSILON = 0.002f;        // General half precision
        constexpr float HALF_MATH_EPSILON = 2e-3f;   // Mathematical functions
        constexpr float HALF_ANGLE_EPSILON = 0.2f;   // Trigonometry
        constexpr float HALF_LARGE_EPSILON = 0.5f;   // Large values

        // ============================================================================
        // 1. Constructors
        // ============================================================================
        suite.section("Constructors");

        // Test default constructor
        {
            half3 v;
            suite.assert_approximately_equal(float(v.x), 0.0f, "Default constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 0.0f, "Default constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 0.0f, "Default constructor z", HALF_EPSILON);
        }

        // Test constructor with half components
        {
            half3 v(half(1.5f), half(2.5f), half(3.5f));
            suite.assert_approximately_equal(float(v.x), 1.5f, "Half component constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Half component constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.5f, "Half component constructor z", HALF_EPSILON);
        }

        // Test constructor with float components
        {
            half3 v(1.5f, 2.5f, 3.5f);
            suite.assert_approximately_equal(float(v.x), 1.5f, "Float component constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Float component constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.5f, "Float component constructor z", HALF_EPSILON);
        }

        // Test constructor with scalar (half)
        {
            half3 v(half(3.0f));
            suite.assert_approximately_equal(float(v.x), 3.0f, "Half scalar constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Half scalar constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "Half scalar constructor z", HALF_EPSILON);
        }

        // Test constructor with scalar (float)
        {
            half3 v(3.0f);
            suite.assert_approximately_equal(float(v.x), 3.0f, "Float scalar constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Float scalar constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "Float scalar constructor z", HALF_EPSILON);
        }

        // Test constructor from float3
        {
            float3 fv(4.0f, 5.0f, 6.0f);
            half3 v(fv);
            suite.assert_approximately_equal(float(v.x), 4.0f, "float3 constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 5.0f, "float3 constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 6.0f, "float3 constructor z", HALF_EPSILON);
        }

        // Test constructor from half2 and z component
        {
            half2 xy(1.0f, 2.0f);
            half3 v(xy, half(3.0f));
            suite.assert_approximately_equal(float(v.x), 1.0f, "half2 + z constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.0f, "half2 + z constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "half2 + z constructor z", HALF_EPSILON);
        }

        // Test constructor from float2 and z component
        {
            float2 xy(1.0f, 2.0f);
            half3 v(xy, 3.0f);
            suite.assert_approximately_equal(float(v.x), 1.0f, "float2 + z constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.0f, "float2 + z constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "float2 + z constructor z", HALF_EPSILON);
        }

        // Test copy constructor
        {
            half3 original(6.0f, 7.0f, 8.0f);
            half3 copy(original);
            suite.assert_approximately_equal(float(copy.x), 6.0f, "Copy constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(copy.y), 7.0f, "Copy constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(copy.z), 8.0f, "Copy constructor z", HALF_EPSILON);
        }

        // Test static constructors
        {
            half3 zero = half3::zero();
            suite.assert_approximately_equal(float(zero.x), 0.0f, "zero() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero.y), 0.0f, "zero() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero.z), 0.0f, "zero() z", HALF_EPSILON);

            half3 one = half3::one();
            suite.assert_approximately_equal(float(one.x), 1.0f, "one() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(one.y), 1.0f, "one() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(one.z), 1.0f, "one() z", HALF_EPSILON);

            half3 unit_x = half3::unit_x();
            suite.assert_approximately_equal(float(unit_x.x), 1.0f, "unit_x() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_x.y), 0.0f, "unit_x() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_x.z), 0.0f, "unit_x() z", HALF_EPSILON);

            half3 unit_y = half3::unit_y();
            suite.assert_approximately_equal(float(unit_y.x), 0.0f, "unit_y() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_y.y), 1.0f, "unit_y() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_y.z), 0.0f, "unit_y() z", HALF_EPSILON);

            half3 unit_z = half3::unit_z();
            suite.assert_approximately_equal(float(unit_z.x), 0.0f, "unit_z() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_z.y), 0.0f, "unit_z() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_z.z), 1.0f, "unit_z() z", HALF_EPSILON);

            half3 forward = half3::forward();
            suite.assert_approximately_equal(float(forward.x), 0.0f, "forward() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(forward.y), 0.0f, "forward() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(forward.z), 1.0f, "forward() z", HALF_EPSILON);

            half3 up = half3::up();
            suite.assert_approximately_equal(float(up.x), 0.0f, "up() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(up.y), 1.0f, "up() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(up.z), 0.0f, "up() z", HALF_EPSILON);

            half3 right = half3::right();
            suite.assert_approximately_equal(float(right.x), 1.0f, "right() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(right.y), 0.0f, "right() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(right.z), 0.0f, "right() z", HALF_EPSILON);
        }

        // ============================================================================
        // 2. Assignment Operators
        // ============================================================================
        suite.section("Assignment Operators");

        // Test assignment with half scalar
        {
            half3 v;
            v = half(2.5f);
            suite.assert_approximately_equal(float(v.x), 2.5f, "Half scalar assignment x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Half scalar assignment y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 2.5f, "Half scalar assignment z", HALF_EPSILON);
        }

        // Test assignment with float scalar
        {
            half3 v;
            v = 2.5f;
            suite.assert_approximately_equal(float(v.x), 2.5f, "Float scalar assignment x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Float scalar assignment y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 2.5f, "Float scalar assignment z", HALF_EPSILON);
        }

        // Test assignment with float3
        {
            half3 v;
            float3 fv(3.5f, 4.5f, 5.5f);
            v = fv;
            suite.assert_approximately_equal(float(v.x), 3.5f, "float3 assignment x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.5f, "float3 assignment y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 5.5f, "float3 assignment z", HALF_EPSILON);
        }

        // Test compound assignment operators (half3)
        {
            half3 v(1.0f, 2.0f, 3.0f);

            v += half3(3.0f, 4.0f, 5.0f);
            suite.assert_approximately_equal(float(v.x), 4.0f, "Operator += x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 6.0f, "Operator += y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 8.0f, "Operator += z", HALF_EPSILON);

            v -= half3(1.0f, 2.0f, 3.0f);
            suite.assert_approximately_equal(float(v.x), 3.0f, "Operator -= x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.0f, "Operator -= y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 5.0f, "Operator -= z", HALF_EPSILON);

            v *= half3(2.0f, 3.0f, 4.0f);
            suite.assert_approximately_equal(float(v.x), 6.0f, "Operator *= x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 12.0f, "Operator *= y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 20.0f, "Operator *= z", HALF_EPSILON);

            v /= half3(2.0f, 3.0f, 4.0f);
            suite.assert_approximately_equal(float(v.x), 3.0f, "Operator /= x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.0f, "Operator /= y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 5.0f, "Operator /= z", HALF_EPSILON);
        }

        // Test compound assignment operators (scalars)
        {
            half3 v(2.0f, 3.0f, 4.0f);

            v *= half(2.0f);
            suite.assert_approximately_equal(float(v.x), 4.0f, "Operator *= half scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 6.0f, "Operator *= half scalar y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 8.0f, "Operator *= half scalar z", HALF_EPSILON);

            v /= half(2.0f);
            suite.assert_approximately_equal(float(v.x), 2.0f, "Operator /= half scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Operator /= half scalar y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 4.0f, "Operator /= half scalar z", HALF_EPSILON);

            v *= 2.0f;
            suite.assert_approximately_equal(float(v.x), 4.0f, "Operator *= float scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 6.0f, "Operator *= float scalar y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 8.0f, "Operator *= float scalar z", HALF_EPSILON);

            v /= 2.0f;
            suite.assert_approximately_equal(float(v.x), 2.0f, "Operator /= float scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Operator /= float scalar y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 4.0f, "Operator /= float scalar z", HALF_EPSILON);
        }

        // ============================================================================
        // 3. Binary Operators
        // ============================================================================
        suite.section("Binary Operators");

        // Test addition
        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 b(3.0f, 4.0f, 5.0f);
            half3 result = a + b;
            suite.assert_approximately_equal(float(result.x), 4.0f, "Operator + x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 6.0f, "Operator + y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 8.0f, "Operator + z", HALF_EPSILON);
        }

        // Test subtraction
        {
            half3 a(5.0f, 6.0f, 7.0f);
            half3 b(2.0f, 3.0f, 4.0f);
            half3 result = a - b;
            suite.assert_approximately_equal(float(result.x), 3.0f, "Operator - x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 3.0f, "Operator - y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 3.0f, "Operator - z", HALF_EPSILON);
        }

        // Test unary operators
        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 pos = +a;
            suite.assert_approximately_equal(float(pos.x), 1.0f, "Unary + x", HALF_EPSILON);
            suite.assert_approximately_equal(float(pos.y), 2.0f, "Unary + y", HALF_EPSILON);
            suite.assert_approximately_equal(float(pos.z), 3.0f, "Unary + z", HALF_EPSILON);

            half3 neg = -a;
            suite.assert_approximately_equal(float(neg.x), -1.0f, "Unary - x", HALF_EPSILON);
            suite.assert_approximately_equal(float(neg.y), -2.0f, "Unary - y", HALF_EPSILON);
            suite.assert_approximately_equal(float(neg.z), -3.0f, "Unary - z", HALF_EPSILON);
        }

        // Test scalar operations (half)
        {
            half3 v(2.0f, 3.0f, 4.0f);

            half3 result1 = v + half(1.0f);
            suite.assert_approximately_equal(float(result1.x), 3.0f, "Vector + half x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result1.y), 4.0f, "Vector + half y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result1.z), 5.0f, "Vector + half z", HALF_EPSILON);

            half3 result2 = half(1.0f) + v;
            suite.assert_approximately_equal(float(result2.x), 3.0f, "half + vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result2.y), 4.0f, "half + vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result2.z), 5.0f, "half + vector z", HALF_EPSILON);

            half3 result3 = v * half(2.0f);
            suite.assert_approximately_equal(float(result3.x), 4.0f, "Vector * half x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result3.y), 6.0f, "Vector * half y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result3.z), 8.0f, "Vector * half z", HALF_EPSILON);

            half3 result4 = half(2.0f) * v;
            suite.assert_approximately_equal(float(result4.x), 4.0f, "half * vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result4.y), 6.0f, "half * vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result4.z), 8.0f, "half * vector z", HALF_EPSILON);

            half3 result5 = v / half(2.0f);
            suite.assert_approximately_equal(float(result5.x), 1.0f, "Vector / half x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result5.y), 1.5f, "Vector / half y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result5.z), 2.0f, "Vector / half z", HALF_EPSILON);
        }

        // Test scalar operations (float)
        {
            half3 v(2.0f, 3.0f, 4.0f);

            half3 result1 = v + 1.0f;
            suite.assert_approximately_equal(float(result1.x), 3.0f, "Vector + float x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result1.y), 4.0f, "Vector + float y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result1.z), 5.0f, "Vector + float z", HALF_EPSILON);

            half3 result2 = 1.0f + v;
            suite.assert_approximately_equal(float(result2.x), 3.0f, "float + vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result2.y), 4.0f, "float + vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result2.z), 5.0f, "float + vector z", HALF_EPSILON);

            half3 result3 = v * 2.0f;
            suite.assert_approximately_equal(float(result3.x), 4.0f, "Vector * float x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result3.y), 6.0f, "Vector * float y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result3.z), 8.0f, "Vector * float z", HALF_EPSILON);

            half3 result4 = 2.0f * v;
            suite.assert_approximately_equal(float(result4.x), 4.0f, "float * vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result4.y), 6.0f, "float * vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result4.z), 8.0f, "float * vector z", HALF_EPSILON);

            half3 result5 = v / 2.0f;
            suite.assert_approximately_equal(float(result5.x), 1.0f, "Vector / float x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result5.y), 1.5f, "Vector / float y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result5.z), 2.0f, "Vector / float z", HALF_EPSILON);
        }

        // Test operations with float3
        {
            half3 hv(1.0f, 2.0f, 3.0f);
            float3 fv(3.0f, 4.0f, 5.0f);

            half3 add = hv + fv;
            suite.assert_approximately_equal(float(add.x), 4.0f, "half3 + float3 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(add.y), 6.0f, "half3 + float3 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(add.z), 8.0f, "half3 + float3 z", HALF_EPSILON);

            half3 add2 = fv + hv;
            suite.assert_approximately_equal(float(add2.x), 4.0f, "float3 + half3 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(add2.y), 6.0f, "float3 + half3 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(add2.z), 8.0f, "float3 + half3 z", HALF_EPSILON);

            half3 sub = hv - fv;
            suite.assert_approximately_equal(float(sub.x), -2.0f, "half3 - float3 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(sub.y), -2.0f, "half3 - float3 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(sub.z), -2.0f, "half3 - float3 z", HALF_EPSILON);

            half3 sub2 = fv - hv;
            suite.assert_approximately_equal(float(sub2.x), 2.0f, "float3 - half3 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(sub2.y), 2.0f, "float3 - half3 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(sub2.z), 2.0f, "float3 - half3 z", HALF_EPSILON);
        }

        // ============================================================================
        // 4. Access Operators and Conversions
        // ============================================================================
        suite.section("Access Operators and Conversions");

        // Test index operator
        {
            half3 v(7.0f, 8.0f, 9.0f);
            suite.assert_approximately_equal(float(v[0]), 7.0f, "Operator [] index 0", HALF_EPSILON);
            suite.assert_approximately_equal(float(v[1]), 8.0f, "Operator [] index 1", HALF_EPSILON);
            suite.assert_approximately_equal(float(v[2]), 9.0f, "Operator [] index 2", HALF_EPSILON);

            v[0] = half(10.0f);
            v[1] = half(11.0f);
            v[2] = half(12.0f);
            suite.assert_approximately_equal(float(v.x), 10.0f, "Operator [] mutable x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 11.0f, "Operator [] mutable y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 12.0f, "Operator [] mutable z", HALF_EPSILON);
        }

        // Test conversion to float3
        {
            half3 v(1.5f, 2.5f, 3.5f);
            float3 fv = float3(v);
            suite.assert_approximately_equal(fv.x, 1.5f, "Conversion to float3 x", HALF_EPSILON);
            suite.assert_approximately_equal(fv.y, 2.5f, "Conversion to float3 y", HALF_EPSILON);
            suite.assert_approximately_equal(fv.z, 3.5f, "Conversion to float3 z", HALF_EPSILON);
        }

        // Test to_float3 function
        {
            half3 v(3.0f, 4.0f, 5.0f);
            float3 fv = to_float3(v);
            suite.assert_approximately_equal(fv.x, 3.0f, "to_float3 x", HALF_EPSILON);
            suite.assert_approximately_equal(fv.y, 4.0f, "to_float3 y", HALF_EPSILON);
            suite.assert_approximately_equal(fv.z, 5.0f, "to_float3 z", HALF_EPSILON);
        }

        // Test to_half3 function
        {
            float3 fv(3.0f, 4.0f, 5.0f);
            half3 v = to_half3(fv);
            suite.assert_approximately_equal(float(v.x), 3.0f, "to_half3 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.0f, "to_half3 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 5.0f, "to_half3 z", HALF_EPSILON);
        }

        // ============================================================================
        // 5. Mathematical Functions (NEW HLSL SYNTAX)
        // ============================================================================
        suite.section("Mathematical Functions");

        // Test length
        {
            half3 v(2.0f, 3.0f, 6.0f);
            half len = length(v);
            half len_sq = length_sq(v);

            // sqrt(4 + 9 + 36) = sqrt(49) = 7
            suite.assert_approximately_equal(float(len), 7.0f, "length()", HALF_EPSILON);
            suite.assert_approximately_equal(float(len_sq), 49.0f, "length_sq()", HALF_EPSILON);

            half3 zero(0.0f, 0.0f, 0.0f);
            suite.assert_approximately_equal(float(length(zero)), 0.0f, "length() of zero vector", HALF_EPSILON);
        }

        // Test normalization
        {
            half3 v(2.0f, 3.0f, 6.0f);
            half3 normalized = normalize(v);
            float normalized_len = float(length(normalized));

            // (2/7, 3/7, 6/7) ≈ (0.2857, 0.4286, 0.8571)
            suite.assert_approximately_equal(normalized_len, 1.0f, "normalize() length", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.x), 2.0f / 7.0f, "normalize() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.y), 3.0f / 7.0f, "normalize() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.z), 6.0f / 7.0f, "normalize() z", HALF_EPSILON);

            // Test normalization of zero vector
            half3 zero(0.0f, 0.0f, 0.0f);
            half3 zero_norm = normalize(zero);
            suite.assert_approximately_equal(float(zero_norm.x), 0.0f, "normalize() zero vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero_norm.y), 0.0f, "normalize() zero vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero_norm.z), 0.0f, "normalize() zero vector z", HALF_EPSILON);
        }

        // Test dot product
        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 b(4.0f, 5.0f, 6.0f);
            half dot_result = dot(a, b);
            suite.assert_approximately_equal(float(dot_result), 32.0f, "dot()", HALF_EPSILON);

            // Global function dot
            half global_dot = dot(a, b);
            suite.assert_approximately_equal(float(global_dot), 32.0f, "global dot()", HALF_EPSILON);

            // Orthogonal vectors
            half3 orth1(1.0f, 0.0f, 0.0f);
            half3 orth2(0.0f, 1.0f, 0.0f);
            half orth_dot = dot(orth1, orth2);
            suite.assert_approximately_equal(float(orth_dot), 0.0f, "dot() orthogonal vectors", HALF_EPSILON);
        }

        // Test cross product
        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 b(4.0f, 5.0f, 6.0f);
            half3 cross_result = cross(a, b);

            // (2*6 - 3*5, 3*4 - 1*6, 1*5 - 2*4) = (12-15, 12-6, 5-8) = (-3, 6, -3)
            suite.assert_approximately_equal(float(cross_result.x), -3.0f, "cross() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_result.y), 6.0f, "cross() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_result.z), -3.0f, "cross() z", HALF_EPSILON);

            // Global function cross
            half3 global_cross = cross(a, b);
            suite.assert_approximately_equal(float(global_cross.x), -3.0f, "global cross() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_cross.y), 6.0f, "global cross() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_cross.z), -3.0f, "global cross() z", HALF_EPSILON);
        }

        // Test distance
        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 b(4.0f, 6.0f, 8.0f);
            half dist = distance(a, b);
            half dist_sq = distance_sq(a, b);

            // (4-1)² + (6-2)² + (8-3)² = 9 + 16 + 25 = 50
            suite.assert_approximately_equal(float(dist), std::sqrt(50.0f), "distance()", HALF_EPSILON);
            suite.assert_approximately_equal(float(dist_sq), 50.0f, "distance_sq()", HALF_EPSILON);

            // Global functions distance and distance_sq
            half global_distance = distance(a, b);
            half global_distance_sq = distance_sq(a, b);
            suite.assert_approximately_equal(float(global_distance), std::sqrt(50.0f), "global distance()", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_distance_sq), 50.0f, "global distance_sq()", HALF_EPSILON);
        }

        // ============================================================================
        // 6. HLSL-like Functions
        // ============================================================================
        suite.section("HLSL-like Functions");

        // Test abs
        {
            half3 v(-1.5f, 2.5f, -3.5f);
            half3 result = abs(v);

            suite.assert_approximately_equal(float(result.x), 1.5f, "abs() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 2.5f, "abs() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 3.5f, "abs() z", HALF_EPSILON);
        }

        // Test sign
        {
            half3 v(-2.0f, 0.0f, 3.0f);
            half3 result = sign(v);

            suite.assert_approximately_equal(float(result.x), -1.0f, "sign() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.0f, "sign() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 1.0f, "sign() z", HALF_EPSILON);
        }

        // Test floor
        {
            half3 v(1.7f, -2.3f, 3.1f);
            half3 result = floor(v);

            suite.assert_approximately_equal(float(result.x), 1.0f, "floor() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), -3.0f, "floor() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 3.0f, "floor() z", HALF_EPSILON);
        }

        // Test ceil
        {
            half3 v(1.2f, -2.7f, 3.9f);
            half3 result = ceil(v);

            suite.assert_approximately_equal(float(result.x), 2.0f, "ceil() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), -2.0f, "ceil() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 4.0f, "ceil() z", HALF_EPSILON);
        }

        // Test round
        {
            half3 v(1.4f, 1.6f, -1.5f);
            half3 result = round(v);

            suite.assert_approximately_equal(float(result.x), 1.0f, "round() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 2.0f, "round() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), -2.0f, "round() z", HALF_EPSILON);
        }

        // Test frac (HLSL semantics)
        {
            half3 v(1.7f, -2.3f, 3.0f);
            half3 result = frac(v);

            // HLSL: frac(x) = x - floor(x)
            // frac(1.7) = 1.7 - 1.0 = 0.7
            // frac(-2.3) = -2.3 - (-3.0) = 0.7
            // frac(3.0) = 3.0 - 3.0 = 0.0
            suite.assert_approximately_equal(float(result.x), 0.7f, "frac() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.7f, "frac() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 0.0f, "frac() z", HALF_EPSILON);
        }

        // Test saturate
        {
            half3 v(-0.5f, 0.5f, 1.5f);
            half3 result = saturate(v);

            suite.assert_approximately_equal(float(result.x), 0.0f, "saturate() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.5f, "saturate() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 1.0f, "saturate() z", HALF_EPSILON);
        }

        // Test step
        {
            half3 v(0.5f, 1.0f, 1.5f);
            half3 result = step(half(1.0f), v);

            suite.assert_approximately_equal(float(result.x), 0.0f, "step() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 1.0f, "step() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 1.0f, "step() z", HALF_EPSILON);
        }

        // Test smoothstep
        {
            half3 v(0.5f, 1.5f, 2.5f);
            half3 result = smoothstep(half(0.0f), half(2.0f), v);

            // For t=0.25: 3t² - 2t³ = 3*0.0625 - 2*0.015625 = 0.1875 - 0.03125 = 0.15625
            // For t=0.75: 3*0.5625 - 2*0.421875 = 1.6875 - 0.84375 = 0.84375
            // For t=1.25: clamp to [0,1], but t>1 => 1.0
            suite.assert_approximately_equal(float(result.x), 0.15625f, "smoothstep() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.84375f, "smoothstep() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 1.0f, "smoothstep() z", HALF_EPSILON);
        }

        // Test min/max
        {
            half3 a(1.0f, 3.0f, 5.0f);
            half3 b(2.0f, 2.0f, 6.0f);

            half3 min_result = min(a, b);
            half3 max_result = max(a, b);

            suite.assert_approximately_equal(float(min_result.x), 1.0f, "min() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(min_result.y), 2.0f, "min() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(min_result.z), 5.0f, "min() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(max_result.x), 2.0f, "max() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(max_result.y), 3.0f, "max() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(max_result.z), 6.0f, "max() z", HALF_EPSILON);
        }

        // Test clamp
        {
            half3 v(2.5f, -0.5f, 1.5f);
            half3 min_val(1.0f, 0.0f, 1.0f);
            half3 max_val(2.0f, 1.0f, 2.0f);

            half3 clamped = clamp(v, min_val, max_val);
            suite.assert_approximately_equal(float(clamped.x), 2.0f, "clamp() vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(clamped.y), 0.0f, "clamp() vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(clamped.z), 1.5f, "clamp() vector z", HALF_EPSILON);

            half3 clamped_scalar = clamp(v, 0.0f, 1.0f);
            suite.assert_approximately_equal(float(clamped_scalar.x), 1.0f, "clamp() scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(clamped_scalar.y), 0.0f, "clamp() scalar y", HALF_EPSILON);
            suite.assert_approximately_equal(float(clamped_scalar.z), 1.0f, "clamp() scalar z", HALF_EPSILON);
        }

        // ============================================================================
        // 7. Geometric Operations
        // ============================================================================
        suite.section("Geometric Operations");

        // Test reflection
        {
            half3 incident(1.0f, -1.0f, 0.0f);
            half3 normal(0.0f, 1.0f, 0.0f);
            half3 reflected = reflect(incident, normal);

            // Expect (1.0f, 1.0f, 0.0f) for mirror reflection
            suite.assert_approximately_equal(float(reflected.x), 1.0f, "reflect() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(reflected.y), 1.0f, "reflect() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(reflected.z), 0.0f, "reflect() z", HALF_EPSILON);
        }

        // Test refraction
        {
            half3 incident(1.0f, -1.0f, 0.0f);
            half3 normal(0.0f, 1.0f, 0.0f);
            half eta(0.9f);  // Refraction coefficient less than 1

            half3 refracted = refract(incident, normal, eta);

            // Check that result has expected direction
            suite.assert_true(refracted.is_finite(), "refract() returns finite vector");
        }

        // Test projection
        {
            half3 v(3.0f, 4.0f, 0.0f);
            half3 onto(1.0f, 0.0f, 0.0f);
            half3 projected = project(v, onto);

            // Projection (3,4,0) onto (1,0,0) = (3,0,0)
            suite.assert_approximately_equal(float(projected.x), 3.0f, "project() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.y), 0.0f, "project() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.z), 0.0f, "project() z", HALF_EPSILON);
        }

        // Test rejection
        {
            half3 v(3.0f, 4.0f, 0.0f);
            half3 from(1.0f, 0.0f, 0.0f);
            half3 rejected = reject(v, from);

            // Rejection (3,4,0) from (1,0,0) = (0,4,0)
            suite.assert_approximately_equal(float(rejected.x), 0.0f, "reject() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(rejected.y), 4.0f, "reject() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(rejected.z), 0.0f, "reject() z", HALF_EPSILON);
        }

        // Test angle between vectors
        {
            half3 a(1.0f, 0.0f, 0.0f);
            half3 b(0.0f, 1.0f, 0.0f);
            half angle = angle_between(a, b);

            // Angle between (1,0,0) and (0,1,0) = 90 degrees = π/2 radians
            suite.assert_approximately_equal(float(angle), Constants::Constants<float>::Pi / 2.0f,
                "angle_between() 90 degrees", HALF_ANGLE_EPSILON);
        }

        // ============================================================================
        // 8. Color Operations
        // ============================================================================
        suite.section("Color Operations");

        // Test luminance
        {
            half3 color(0.5f, 0.3f, 0.2f);
            half luma = luminance(color);

            // 0.2126*0.5 + 0.7152*0.3 + 0.0722*0.2 = 0.1063 + 0.21456 + 0.01444 = 0.3353
            float expected = 0.2126f * 0.5f + 0.7152f * 0.3f + 0.0722f * 0.2f;
            suite.assert_approximately_equal(float(luma), expected, "luminance()", HALF_EPSILON);
        }

        // Test RGB to grayscale conversion
        {
            half3 color(0.5f, 0.3f, 0.2f);
            half3 grayscale = rgb_to_grayscale(color);

            float expected = 0.2126f * 0.5f + 0.7152f * 0.3f + 0.0722f * 0.2f;
            suite.assert_approximately_equal(float(grayscale.x), expected, "rgb_to_grayscale() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(grayscale.y), expected, "rgb_to_grayscale() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(grayscale.z), expected, "rgb_to_grayscale() z", HALF_EPSILON);
        }

        // Test gamma correction
        {
            half3 color(0.25f, 0.5f, 0.75f);
            half gamma(2.0f);
            half3 corrected = gamma_correct(color, gamma);

            // gamma_correct(x) = pow(x, gamma)
            suite.assert_approximately_equal(float(corrected.x), 0.0625f, "gamma_correct() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(corrected.y), 0.25f, "gamma_correct() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(corrected.z), 0.5625f, "gamma_correct() z", HALF_EPSILON);
        }

        // Test sRGB <-> linear conversion
        {
            half3 srgb(0.5f, 0.5f, 0.5f);
            half3 linear = srgb_to_linear(srgb);

            // For value 0.5 in sRGB: 0.5 <= 0.04045 ? 0.5/12.92 : pow((0.5+0.055)/1.055, 2.4)
            // 0.5 > 0.04045, so: pow((0.5+0.055)/1.055, 2.4) ≈ pow(0.526, 2.4) ≈ 0.214
            float expected = std::pow((0.5f + 0.055f) / 1.055f, 2.4f);
            suite.assert_approximately_equal(float(linear.x), expected, "srgb_to_linear() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(linear.y), expected, "srgb_to_linear() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(linear.z), expected, "srgb_to_linear() z", HALF_EPSILON);

            // Reverse conversion
            half3 back_to_srgb = linear_to_srgb(linear);

            // Check that conversion is reversible with some precision
            suite.assert_approximately_equal(float(back_to_srgb.x), 0.5f, "linear_to_srgb() round-trip x", HALF_EPSILON);
            suite.assert_approximately_equal(float(back_to_srgb.y), 0.5f, "linear_to_srgb() round-trip y", HALF_EPSILON);
            suite.assert_approximately_equal(float(back_to_srgb.z), 0.5f, "linear_to_srgb() round-trip z", HALF_EPSILON);
        }

        // ============================================================================
        // 9. Swizzle Operations
        // ============================================================================
        suite.section("Swizzle Operations");

        {
            half3 v(2.0f, 3.0f, 4.0f);

            // 2D swizzles
            half2 xy = v.xy();
            suite.assert_approximately_equal(float(xy.x), 2.0f, "xy() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(xy.y), 3.0f, "xy() y", HALF_EPSILON);

            half2 xz = v.xz();
            suite.assert_approximately_equal(float(xz.x), 2.0f, "xz() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(xz.y), 4.0f, "xz() y", HALF_EPSILON);

            half2 yz = v.yz();
            suite.assert_approximately_equal(float(yz.x), 3.0f, "yz() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(yz.y), 4.0f, "yz() y", HALF_EPSILON);

            half2 yx = v.yx();
            suite.assert_approximately_equal(float(yx.x), 3.0f, "yx() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(yx.y), 2.0f, "yx() y", HALF_EPSILON);

            half2 zx = v.zx();
            suite.assert_approximately_equal(float(zx.x), 4.0f, "zx() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zx.y), 2.0f, "zx() y", HALF_EPSILON);

            half2 zy = v.zy();
            suite.assert_approximately_equal(float(zy.x), 4.0f, "zy() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zy.y), 3.0f, "zy() y", HALF_EPSILON);

            // 3D swizzles
            half3 yxz = v.yxz();
            suite.assert_approximately_equal(float(yxz.x), 3.0f, "yxz() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(yxz.y), 2.0f, "yxz() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(yxz.z), 4.0f, "yxz() z", HALF_EPSILON);

            half3 zxy = v.zxy();
            suite.assert_approximately_equal(float(zxy.x), 4.0f, "zxy() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zxy.y), 2.0f, "zxy() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(zxy.z), 3.0f, "zxy() z", HALF_EPSILON);

            half3 zyx = v.zyx();
            suite.assert_approximately_equal(float(zyx.x), 4.0f, "zyx() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zyx.y), 3.0f, "zyx() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(zyx.z), 2.0f, "zyx() z", HALF_EPSILON);

            half3 xzy = v.xzy();
            suite.assert_approximately_equal(float(xzy.x), 2.0f, "xzy() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(xzy.y), 4.0f, "xzy() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(xzy.z), 3.0f, "xzy() z", HALF_EPSILON);
        }

        // Color swizzles
        {
            half3 color(0.2f, 0.4f, 0.6f);

            suite.assert_approximately_equal(float(color.r()), 0.2f, "r()", HALF_EPSILON);
            suite.assert_approximately_equal(float(color.g()), 0.4f, "g()", HALF_EPSILON);
            suite.assert_approximately_equal(float(color.b()), 0.6f, "b()", HALF_EPSILON);

            half2 rg = color.rg();
            suite.assert_approximately_equal(float(rg.x), 0.2f, "rg() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(rg.y), 0.4f, "rg() y", HALF_EPSILON);

            half2 rb = color.rb();
            suite.assert_approximately_equal(float(rb.x), 0.2f, "rb() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(rb.y), 0.6f, "rb() y", HALF_EPSILON);

            half2 gb = color.gb();
            suite.assert_approximately_equal(float(gb.x), 0.4f, "gb() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(gb.y), 0.6f, "gb() y", HALF_EPSILON);

            half3 rgb = color.rgb();
            suite.assert_approximately_equal(float(rgb.x), 0.2f, "rgb() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(rgb.y), 0.4f, "rgb() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(rgb.z), 0.6f, "rgb() z", HALF_EPSILON);

            half3 bgr = color.bgr();
            suite.assert_approximately_equal(float(bgr.x), 0.6f, "bgr() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(bgr.y), 0.4f, "bgr() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(bgr.z), 0.2f, "bgr() z", HALF_EPSILON);

            half3 gbr = color.gbr();
            suite.assert_approximately_equal(float(gbr.x), 0.4f, "gbr() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(gbr.y), 0.6f, "gbr() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(gbr.z), 0.2f, "gbr() z", HALF_EPSILON);
        }

        // ============================================================================
        // 10. Utility Methods
        // ============================================================================
        suite.section("Utility Methods");

        // Test isValid
        {
            half3 valid(1.0f, 2.0f, 3.0f);
            suite.assert_true(valid.is_valid(), "is_valid() for valid vector");
            suite.assert_true(is_valid(valid), "global is_valid() for valid vector");
        }

        // Test approximately
        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 b(1.001f, 2.001f, 3.001f);
            half3 c(1.1f, 2.1f, 3.1f);

            suite.assert_true(approximately(a, b, 0.01f), "approximately() within epsilon");
            suite.assert_false(approximately(a, c, 0.01f), "approximately() outside epsilon");

            bool global_approx = approximately(a, b, 0.01f);
            suite.assert_true(global_approx, "global approximately() within epsilon");
        }

        // Test approximately_zero
        {
            half3 zero(0.0f, 0.0f, 0.0f);
            half3 near_zero(0.001f, 0.001f, 0.001f);
            half3 not_zero(0.1f, 0.1f, 0.1f);

            suite.assert_true(approximately_zero(zero, 0.01f), "approximately_zero() for zero");
            suite.assert_true(approximately_zero(near_zero, 0.01f), "approximately_zero() for near zero");
            suite.assert_false(approximately_zero(not_zero, 0.01f), "approximately_zero() for non-zero");
        }

        // Test is_normalized
        {
            half3 normalized(0.26726124f, 0.53452248f, 0.80178373f); // (1,2,3) normalized
            half3 not_normalized(1.0f, 2.0f, 3.0f);

            suite.assert_true(is_normalized(normalized, 0.01f), "is_normalized() for normalized vector");
            suite.assert_false(is_normalized(not_normalized, 0.01f), "is_normalized() for non-normalized");

            bool global_normalized = is_normalized(normalized, 0.01f);
            suite.assert_true(global_normalized, "global is_normalized() for normalized vector");
        }

        // Test to_string
        {
            half3 v(1.5f, 2.5f, 3.5f);
            std::string str = v.to_string();

            // Check if expected values are in the string
            suite.assert_true(str.find("1.5") != std::string::npos || str.find("1.500") != std::string::npos,
                "to_string() contains x value");
            suite.assert_true(str.find("2.5") != std::string::npos || str.find("2.500") != std::string::npos,
                "to_string() contains y value");
            suite.assert_true(str.find("3.5") != std::string::npos || str.find("3.500") != std::string::npos,
                "to_string() contains z value");
        }

        // Test data()
        {
            half3 v(7.0f, 8.0f, 9.0f);
            const half* cdata = v.data();
            half* data = v.data();

            suite.assert_approximately_equal(float(cdata[0]), 7.0f, "data() const access x", HALF_EPSILON);
            suite.assert_approximately_equal(float(cdata[1]), 8.0f, "data() const access y", HALF_EPSILON);
            suite.assert_approximately_equal(float(cdata[2]), 9.0f, "data() const access z", HALF_EPSILON);

            data[0] = half(10.0f);
            suite.assert_approximately_equal(float(v.x), 10.0f, "data() mutable modification x", HALF_EPSILON);
        }

        // Test set_xy
        {
            half3 v(1.0f, 2.0f, 3.0f);
            half2 xy(4.0f, 5.0f);
            v.set_xy(xy);

            suite.assert_approximately_equal(float(v.x), 4.0f, "set_xy() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 5.0f, "set_xy() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "set_xy() preserves z", HALF_EPSILON);
        }

        // Test ensure_normalized
        {
            half3 normal(1.0f, 2.0f, 3.0f);
            half3 fallback(0.0f, 0.0f, 1.0f);
            half3 ensured = ensure_normalized(normal, fallback);

            // ensure_normalized should normalize the vector
            float flength = float(length(ensured));
            suite.assert_approximately_equal(flength, 1.0f, "ensure_normalized() length", HALF_EPSILON);

            // Test with zero vector (should return fallback)
            half3 zero(0.0f, 0.0f, 0.0f);
            half3 zero_ensured = ensure_normalized(zero, fallback);
            suite.assert_true(zero_ensured == fallback, "ensure_normalized() returns fallback for zero vector");
        }

        // ============================================================================
        // 11. Comparison Operators
        // ============================================================================
        suite.section("Comparison Operators");

        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 b(1.0f, 2.0f, 3.0f);
            half3 c(1.1f, 2.1f, 3.1f);

            suite.assert_true(a == b, "Operator == for equal vectors");
            suite.assert_false(a == c, "Operator == for different vectors");
            suite.assert_false(a != b, "Operator != for equal vectors");
            suite.assert_true(a != c, "Operator != for different vectors");
        }

        // ============================================================================
        // 12. Special Values
        // ============================================================================
        suite.section("Special Values");

        // Test with zeros
        {
            half3 pos_zero(0.0f, 0.0f, 0.0f);
            half3 neg_zero(-0.0f, -0.0f, -0.0f);

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
            half3 pos_inf(std::numeric_limits<float>::infinity(), 1.0f, 2.0f);
            half3 neg_inf(-std::numeric_limits<float>::infinity(), 1.0f, 2.0f);

            suite.assert_true(pos_inf.is_inf(), "is_inf() for vector with positive infinity");
            suite.assert_true(neg_inf.is_inf(), "is_inf() for vector with negative infinity");
            suite.assert_true(pos_inf.is_positive_inf(), "is_positive_inf() for vector with positive infinity");
            suite.assert_true(neg_inf.is_negative_inf(), "is_negative_inf() for vector with negative infinity");

            bool global_inf = is_inf(pos_inf);
            bool global_pos_inf = is_positive_inf(pos_inf);
            bool global_neg_inf = is_negative_inf(neg_inf);
            suite.assert_true(global_inf, "global is_inf()");
            suite.assert_true(global_pos_inf, "global is_positive_inf()");
            suite.assert_true(global_neg_inf, "global is_negative_inf()");
        }

        // Test with NaN
        {
            half3 nan_vec(std::numeric_limits<float>::quiet_NaN(), 1.0f, 2.0f);
            half3 all_nan_vec(std::numeric_limits<float>::quiet_NaN(),
                std::numeric_limits<float>::quiet_NaN(),
                std::numeric_limits<float>::quiet_NaN());

            suite.assert_true(nan_vec.is_nan(), "is_nan() for vector with NaN");
            suite.assert_true(all_nan_vec.is_all_nan(), "is_all_nan() for all-NaN vector");

            bool global_nan = is_nan(nan_vec);
            bool global_all_nan = is_all_nan(all_nan_vec);
            suite.assert_true(global_nan, "global is_nan()");
        }

        // Test with finite values
        {
            half3 finite(1.0f, 2.0f, 3.0f);

            suite.assert_true(finite.is_finite(), "is_finite() for finite vector");
            suite.assert_true(finite.is_all_finite(), "is_all_finite() for finite vector");

            bool global_finite = is_finite(finite);
            bool global_all_finite = is_all_finite(finite);
            suite.assert_true(global_finite, "global is_finite()");
            suite.assert_true(global_all_finite, "global is_all_finite()");
        }

        // Test with positive/negative values
        {
            half3 pos(1.0f, 2.0f, 3.0f);
            half3 neg(-1.0f, -2.0f, -3.0f);
            half3 mixed(-1.0f, 2.0f, -3.0f);

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

        // Test with positive/negative zeros
        {
            half3 pos_zero(0.0f, 0.0f, 0.0f);
            half3 neg_zero(-0.0f, -0.0f, -0.0f);
            half3 mixed_zero(0.0f, -0.0f, 0.0f);

            suite.assert_true(pos_zero.is_positive_zero(), "is_positive_zero() for positive zero");
            suite.assert_true(neg_zero.is_negative_zero(), "is_negative_zero() for negative zero");
            suite.assert_true(mixed_zero.is_positive_zero(), "is_positive_zero() for mixed zero vector");
            suite.assert_true(mixed_zero.is_negative_zero(), "is_negative_zero() for mixed zero vector");
        }

        // ============================================================================
        // 13. Linear Interpolation
        // ============================================================================
        suite.section("Linear Interpolation");

        {
            half3 a(0.0f, 0.0f, 0.0f);
            half3 b(10.0f, 20.0f, 30.0f);

            half3 lerp_result = lerp(a, b, half(0.5f));
            suite.assert_approximately_equal(float(lerp_result.x), 5.0f, "lerp() at 0.5 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_result.y), 10.0f, "lerp() at 0.5 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_result.z), 15.0f, "lerp() at 0.5 z", HALF_EPSILON);

            half3 lerp_float = lerp(a, b, 0.5f);
            suite.assert_approximately_equal(float(lerp_float.x), 5.0f, "lerp() with float at 0.5 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_float.y), 10.0f, "lerp() with float at 0.5 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_float.z), 15.0f, "lerp() with float at 0.5 z", HALF_EPSILON);

            half3 global_lerp = lerp(a, b, half(0.5f));
            suite.assert_approximately_equal(float(global_lerp.x), 5.0f, "global lerp() at 0.5 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_lerp.y), 10.0f, "global lerp() at 0.5 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_lerp.z), 15.0f, "global lerp() at 0.5 z", HALF_EPSILON);

            half3 lerp_start = lerp(a, b, half(0.0f));
            suite.assert_approximately_equal(float(lerp_start.x), 0.0f, "lerp() at 0.0 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_start.y), 0.0f, "lerp() at 0.0 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_start.z), 0.0f, "lerp() at 0.0 z", HALF_EPSILON);

            half3 lerp_end = lerp(a, b, half(1.0f));
            suite.assert_approximately_equal(float(lerp_end.x), 10.0f, "lerp() at 1.0 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_end.y), 20.0f, "lerp() at 1.0 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_end.z), 30.0f, "lerp() at 1.0 z", HALF_EPSILON);
        }

        // ============================================================================
        // 14. Global Constants
        // ============================================================================
        suite.section("Global Constants");

        {
            suite.assert_approximately_equal(float(half3_Zero.x), 0.0f, "half3_Zero x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Zero.y), 0.0f, "half3_Zero y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Zero.z), 0.0f, "half3_Zero z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_One.x), 1.0f, "half3_One x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_One.y), 1.0f, "half3_One y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_One.z), 1.0f, "half3_One z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_UnitX.x), 1.0f, "half3_UnitX x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_UnitX.y), 0.0f, "half3_UnitX y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_UnitX.z), 0.0f, "half3_UnitX z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_UnitY.x), 0.0f, "half3_UnitY x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_UnitY.y), 1.0f, "half3_UnitY y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_UnitY.z), 0.0f, "half3_UnitY z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_UnitZ.x), 0.0f, "half3_UnitZ x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_UnitZ.y), 0.0f, "half3_UnitZ y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_UnitZ.z), 1.0f, "half3_UnitZ z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_Forward.x), 0.0f, "half3_Forward x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Forward.y), 0.0f, "half3_Forward y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Forward.z), 1.0f, "half3_Forward z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_Up.x), 0.0f, "half3_Up x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Up.y), 1.0f, "half3_Up y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Up.z), 0.0f, "half3_Up z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_Right.x), 1.0f, "half3_Right x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Right.y), 0.0f, "half3_Right y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Right.z), 0.0f, "half3_Right z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_Red.x), 1.0f, "half3_Red x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Red.y), 0.0f, "half3_Red y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Red.z), 0.0f, "half3_Red z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_Green.x), 0.0f, "half3_Green x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Green.y), 1.0f, "half3_Green y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Green.z), 0.0f, "half3_Green z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_Blue.x), 0.0f, "half3_Blue x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Blue.y), 0.0f, "half3_Blue y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Blue.z), 1.0f, "half3_Blue z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_White.x), 1.0f, "half3_White x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_White.y), 1.0f, "half3_White y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_White.z), 1.0f, "half3_White z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_Black.x), 0.0f, "half3_Black x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Black.y), 0.0f, "half3_Black y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Black.z), 0.0f, "half3_Black z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_Yellow.x), 1.0f, "half3_Yellow x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Yellow.y), 1.0f, "half3_Yellow y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Yellow.z), 0.0f, "half3_Yellow z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_Cyan.x), 0.0f, "half3_Cyan x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Cyan.y), 1.0f, "half3_Cyan y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Cyan.z), 1.0f, "half3_Cyan z", HALF_EPSILON);

            suite.assert_approximately_equal(float(half3_Magenta.x), 1.0f, "half3_Magenta x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Magenta.y), 0.0f, "half3_Magenta y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half3_Magenta.z), 1.0f, "half3_Magenta z", HALF_EPSILON);
        }

        // ============================================================================
        // 15. Edge Cases
        // ============================================================================
        suite.section("Edge Cases");

        // Test with very small values
        {
            half3 tiny(1e-6f, 1e-6f, 1e-6f);
            suite.assert_true(approximately_zero(tiny, 1e-3f), "Tiny values approximately_zero");
        }

        // Test with very large values
        {
            half3 huge(50000.0f, 50000.0f, 50000.0f);
            suite.assert_false(approximately_zero(huge), "Huge values not approximately_zero");

            // Normalization of large values
            half3 normalized_huge = normalize(huge);
            float normalized_len = float(length(normalized_huge));
            suite.assert_approximately_equal(normalized_len, 1.0f, "Normalize huge values length", HALF_EPSILON);
        }

        // Test division by zero (vector)
        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 zero_vec(0.0f, 0.0f, 0.0f);

            half3 result = a / zero_vec;
            suite.assert_true(result.x.is_inf() || result.x.is_nan(), "Division by zero vector x produces non-finite");
            suite.assert_true(result.y.is_inf() || result.y.is_nan(), "Division by zero vector y produces non-finite");
            suite.assert_true(result.z.is_inf() || result.z.is_nan(), "Division by zero vector z produces non-finite");
        }

        // Test division by zero (scalar)
        {
            half3 v(1.0f, 2.0f, 3.0f);
            half3 result = v / 0.0f;

            suite.assert_true(result.x.is_inf() || result.x.is_nan(), "Division by zero scalar x produces non-finite");
            suite.assert_true(result.y.is_inf() || result.y.is_nan(), "Division by zero scalar y produces non-finite");
            suite.assert_true(result.z.is_inf() || result.z.is_nan(), "Division by zero scalar z produces non-finite");
        }

        // Test normalization of very small vector
        {
            half3 tiny(1e-20f, 1e-20f, 1e-20f);
            half3 normalized = normalize(tiny);

            // Should return zero vector because length is less than epsilon
            suite.assert_approximately_equal(float(normalized.x), 0.0f, "Normalize tiny vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.y), 0.0f, "Normalize tiny vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.z), 0.0f, "Normalize tiny vector z", HALF_EPSILON);
        }

        // Test smoothstep with edge0 = edge1
        {
            half3 v(0.5f, 1.5f, 2.5f);
            half3 result = smoothstep(half(1.0f), half(1.0f), v);
            // When edge0 = edge1, use step(edge0)
            half3 step_result = step(half(1.0f), v);
            suite.assert_approximately_equal(float(result.x), float(step_result.x), "smoothstep() with equal edges x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), float(step_result.y), "smoothstep() with equal edges y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), float(step_result.z), "smoothstep() with equal edges z", HALF_EPSILON);
        }

        // Test dot product with self
        {
            half3 v(3.0f, 4.0f, 5.0f);
            half dot_self = dot(v, v);
            half expected = length_sq(v);
            suite.assert_approximately_equal(float(dot_self), float(expected), "Dot product with self equals length squared", HALF_EPSILON);
        }

        // Test cross product with self
        {
            half3 v(2.0f, 3.0f, 4.0f);
            half3 cross_self = cross(v, v);
            // Cross product of vector with itself = zero vector
            suite.assert_approximately_equal(float(cross_self.x), 0.0f, "Cross product with self x", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_self.y), 0.0f, "Cross product with self y", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_self.z), 0.0f, "Cross product with self z", HALF_EPSILON);
        }

        // Test is_normalized for zero vector
        {
            half3 zero(0.0f, 0.0f, 0.0f);
            suite.assert_false(is_normalized(zero), "Zero vector is not normalized");
        }

        // Test with numbers close to max half value
        {
            float max_half_val = float(half::max_value());
            half3 max_vec(max_half_val, max_half_val, max_half_val);

            // Make sure values are not NaN or Inf
            suite.assert_true(max_vec.is_finite(), "Vector with max half values is finite");

            // Normalization of vector with max values
            half3 normalized = normalize(max_vec);
            float normalized_len = float(length(normalized));
            suite.assert_approximately_equal(normalized_len, 1.0f, "Normalize max values length", HALF_EPSILON);
        }

        // Test with denormalized numbers
        {
            half min_denorm = half::min_denormal_value();
            half3 denorm_vec(min_denorm, min_denorm, min_denorm);

            suite.assert_true(denorm_vec.is_finite(), "Vector with denormalized values is finite");

            // Multiplication of denormalized numbers
            half3 multiplied = denorm_vec * half(2.0f);
            suite.assert_true(multiplied.is_finite(), "Multiplication of denormalized values is finite");
        }

        // Test saturation with negative numbers
        {
            half3 v(-2.0f, 0.5f, 1.5f);
            half3 saturated = saturate(v);

            suite.assert_approximately_equal(float(saturated.x), 0.0f, "saturate() negative value", HALF_EPSILON);
            suite.assert_approximately_equal(float(saturated.y), 0.5f, "saturate() positive value < 1", HALF_EPSILON);
            suite.assert_approximately_equal(float(saturated.z), 1.0f, "saturate() positive value > 1", HALF_EPSILON);
        }

        // Test rounding of boundary values
        {
            half3 v1(1.49f, 1.51f, -1.49f);
            half3 rounded1 = round(v1);
            suite.assert_approximately_equal(float(rounded1.x), 1.0f, "round() 1.49", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded1.y), 2.0f, "round() 1.51", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded1.z), -1.0f, "round() -1.49", HALF_EPSILON);

            half3 v2(-1.51f, 2.49f, 2.51f);
            half3 rounded2 = round(v2);
            suite.assert_approximately_equal(float(rounded2.x), -2.0f, "round() -1.51", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded2.y), 2.0f, "round() 2.49", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded2.z), 3.0f, "round() 2.51", HALF_EPSILON);
        }

        // Test floor/ceil boundary values
        {
            half3 v(1.5f, -1.5f, 2.3f);

            half3 floored = floor(v);
            suite.assert_approximately_equal(float(floored.x), 1.0f, "floor() 1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(floored.y), -2.0f, "floor() -1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(floored.z), 2.0f, "floor() 2.3", HALF_EPSILON);

            half3 ceiled = ceil(v);
            suite.assert_approximately_equal(float(ceiled.x), 2.0f, "ceil() 1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(ceiled.y), -1.0f, "ceil() -1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(ceiled.z), 3.0f, "ceil() 2.3", HALF_EPSILON);
        }

        // Test refraction with total internal reflection
        {
            half3 incident(0.7071f, -0.7071f, 0.0f); // Directed at 45° angle
            half3 normal(0.0f, 1.0f, 0.0f); // Upward normal
            half eta(2.0f); // Refraction coefficient > 1 (from denser to rarer medium)

            half3 refracted = refract(incident, normal, eta);

            // With eta > 1 and certain angles, total internal reflection occurs
            // Should return zero vector
            suite.assert_approximately_equal(float(refracted.x), 0.0f, "refract() total internal reflection x", HALF_EPSILON);
            suite.assert_approximately_equal(float(refracted.y), 0.0f, "refract() total internal reflection y", HALF_EPSILON);
            suite.assert_approximately_equal(float(refracted.z), 0.0f, "refract() total internal reflection z", HALF_EPSILON);
        }

        // Test projection of zero vector
        {
            half3 zero(0.0f, 0.0f, 0.0f);
            half3 onto(1.0f, 0.0f, 0.0f);
            half3 projected = project(zero, onto);

            suite.assert_approximately_equal(float(projected.x), 0.0f, "project() zero vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.y), 0.0f, "project() zero vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.z), 0.0f, "project() zero vector z", HALF_EPSILON);
        }

        // Test projection onto zero vector
        {
            half3 v(1.0f, 2.0f, 3.0f);
            half3 zero(0.0f, 0.0f, 0.0f);
            half3 projected = project(v, zero);

            suite.assert_approximately_equal(float(projected.x), 0.0f, "project() onto zero vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.y), 0.0f, "project() onto zero vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.z), 0.0f, "project() onto zero vector z", HALF_EPSILON);
        }

        // Test rejection from self
        {
            half3 v(1.0f, 2.0f, 3.0f);
            half3 rejected = reject(v, v);

            // Rejection of vector from itself should give zero vector
            suite.assert_approximately_equal(float(rejected.x), 0.0f, "reject() from self x", HALF_EPSILON);
            suite.assert_approximately_equal(float(rejected.y), 0.0f, "reject() from self y", HALF_EPSILON);
            suite.assert_approximately_equal(float(rejected.z), 0.0f, "reject() from self z", HALF_EPSILON);
        }

        // Test angle between parallel vectors
        {
            half3 a(1.0f, 0.0f, 0.0f);
            half3 b(2.0f, 0.0f, 0.0f); // Parallel to a
            half angle = angle_between(a, b);

            suite.assert_approximately_equal(float(angle), 0.0f, "angle_between() parallel vectors", HALF_ANGLE_EPSILON);
        }

        // Test angle between opposite vectors
        {
            half3 a(1.0f, 0.0f, 0.0f);
            half3 b(-1.0f, 0.0f, 0.0f); // Opposite to a
            half angle = angle_between(a, b);

            suite.assert_approximately_equal(float(angle), Constants::Constants<float>::Pi,
                "angle_between() opposite vectors", HALF_ANGLE_EPSILON);
        }

        // Test angle with zero vector
        {
            half3 a(1.0f, 0.0f, 0.0f);
            half3 zero(0.0f, 0.0f, 0.0f);
            half angle = angle_between(a, zero);

            // Angle with zero vector is undefined, but implementation returns 0
            suite.assert_approximately_equal(float(angle), 0.0f, "angle_between() with zero vector", HALF_ANGLE_EPSILON);
        }
    }
} // namespace AfterMathTests
