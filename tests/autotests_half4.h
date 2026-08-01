// Author: DeepSeek, NSDeathman
// Test suite for AfterMath::half4 class

#include "AutotestCore.h"

namespace AfterMathTests
{
    void RunHalf4Tests(TestSuite& suite)
    {
        using namespace AfterMath;

        // Constants for half tests
        constexpr float HALF_EPSILON = 0.02f;        // General half precision
        constexpr float HALF_MATH_EPSILON = 0.02f;   // Mathematical functions
        constexpr float HALF_ANGLE_EPSILON = 0.2f;   // Trigonometry
        constexpr float HALF_LARGE_EPSILON = 0.5f;   // Large values
        constexpr float COLOR_EPSILON = 0.01f;       // Color operations

        // ============================================================================
        // 1. Constructors
        // ============================================================================
        suite.section("Constructors");

        // Test default constructor
        {
            half4 v;
            suite.assert_approximately_equal(float(v.x), 0.0f, "Default constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 0.0f, "Default constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 0.0f, "Default constructor z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 0.0f, "Default constructor w", HALF_EPSILON);
        }

        // Test constructor with half components
        {
            half4 v(half(1.5f), half(2.5f), half(3.5f), half(4.5f));
            suite.assert_approximately_equal(float(v.x), 1.5f, "Half component constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Half component constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.5f, "Half component constructor z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 4.5f, "Half component constructor w", HALF_EPSILON);
        }

        // Test constructor with float components
        {
            half4 v(1.5f, 2.5f, 3.5f, 4.5f);
            suite.assert_approximately_equal(float(v.x), 1.5f, "Float component constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Float component constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.5f, "Float component constructor z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 4.5f, "Float component constructor w", HALF_EPSILON);
        }

        // Test constructor with scalar (half)
        {
            half4 v(half(3.0f));
            suite.assert_approximately_equal(float(v.x), 3.0f, "Half scalar constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Half scalar constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "Half scalar constructor z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 3.0f, "Half scalar constructor w", HALF_EPSILON);
        }

        // Test constructor with scalar (float)
        {
            half4 v(3.0f);
            suite.assert_approximately_equal(float(v.x), 3.0f, "Float scalar constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Float scalar constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "Float scalar constructor z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 3.0f, "Float scalar constructor w", HALF_EPSILON);
        }

        // Test constructor from float4
        {
            float4 fv(4.0f, 5.0f, 6.0f, 7.0f);
            half4 v(fv);
            suite.assert_approximately_equal(float(v.x), 4.0f, "float4 constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 5.0f, "float4 constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 6.0f, "float4 constructor z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 7.0f, "float4 constructor w", HALF_EPSILON);
        }

        // Test constructor from half2 and z, w components
        {
            half2 xy(1.0f, 2.0f);
            half4 v(xy, half(3.0f), half(4.0f));
            suite.assert_approximately_equal(float(v.x), 1.0f, "half2 + z, w constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.0f, "half2 + z, w constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "half2 + z, w constructor z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 4.0f, "half2 + z, w constructor w", HALF_EPSILON);
        }

        // Test constructor from half3 and w component
        {
            half3 xyz(1.0f, 2.0f, 3.0f);
            half4 v(xyz, half(4.0f));
            suite.assert_approximately_equal(float(v.x), 1.0f, "half3 + w constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.0f, "half3 + w constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "half3 + w constructor z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 4.0f, "half3 + w constructor w", HALF_EPSILON);
        }

        // Test constructor from float2 and z, w components
        {
            float2 xy(1.0f, 2.0f);
            half4 v(xy, 3.0f, 4.0f);
            suite.assert_approximately_equal(float(v.x), 1.0f, "float2 + z, w constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.0f, "float2 + z, w constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "float2 + z, w constructor z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 4.0f, "float2 + z, w constructor w", HALF_EPSILON);
        }

        // Test constructor from float3 and w component
        {
            float3 xyz(1.0f, 2.0f, 3.0f);
            half4 v(xyz, 4.0f);
            suite.assert_approximately_equal(float(v.x), 1.0f, "float3 + w constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.0f, "float3 + w constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "float3 + w constructor z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 4.0f, "float3 + w constructor w", HALF_EPSILON);
        }

        // Test copy constructor
        {
            half4 original(6.0f, 7.0f, 8.0f, 9.0f);
            half4 copy(original);
            suite.assert_approximately_equal(float(copy.x), 6.0f, "Copy constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(copy.y), 7.0f, "Copy constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(copy.z), 8.0f, "Copy constructor z", HALF_EPSILON);
            suite.assert_approximately_equal(float(copy.w), 9.0f, "Copy constructor w", HALF_EPSILON);
        }

        // Test static constructors
        {
            half4 zero = half4::zero();
            suite.assert_approximately_equal(float(zero.x), 0.0f, "zero() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero.y), 0.0f, "zero() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero.z), 0.0f, "zero() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero.w), 0.0f, "zero() w", HALF_EPSILON);

            half4 one = half4::one();
            suite.assert_approximately_equal(float(one.x), 1.0f, "one() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(one.y), 1.0f, "one() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(one.z), 1.0f, "one() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(one.w), 1.0f, "one() w", HALF_EPSILON);

            half4 unit_x = half4::unit_x();
            suite.assert_approximately_equal(float(unit_x.x), 1.0f, "unit_x() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_x.y), 0.0f, "unit_x() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_x.z), 0.0f, "unit_x() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_x.w), 0.0f, "unit_x() w", HALF_EPSILON);

            half4 unit_y = half4::unit_y();
            suite.assert_approximately_equal(float(unit_y.x), 0.0f, "unit_y() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_y.y), 1.0f, "unit_y() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_y.z), 0.0f, "unit_y() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_y.w), 0.0f, "unit_y() w", HALF_EPSILON);

            half4 unit_z = half4::unit_z();
            suite.assert_approximately_equal(float(unit_z.x), 0.0f, "unit_z() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_z.y), 0.0f, "unit_z() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_z.z), 1.0f, "unit_z() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_z.w), 0.0f, "unit_z() w", HALF_EPSILON);

            half4 unit_w = half4::unit_w();
            suite.assert_approximately_equal(float(unit_w.x), 0.0f, "unit_w() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_w.y), 0.0f, "unit_w() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_w.z), 0.0f, "unit_w() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(unit_w.w), 1.0f, "unit_w() w", HALF_EPSILON);

            // Test from_rgba
            half4 color = half4::from_rgba(255, 128, 64, 192);
            suite.assert_approximately_equal(float(color.x), 1.0f, "from_rgba() r", COLOR_EPSILON);
            suite.assert_approximately_equal(float(color.y), 0.5f, "from_rgba() g", COLOR_EPSILON);
            suite.assert_approximately_equal(float(color.z), 0.25f, "from_rgba() b", COLOR_EPSILON);
            suite.assert_approximately_equal(float(color.w), 0.75f, "from_rgba() a", COLOR_EPSILON);
        }

        // ============================================================================
        // 2. Assignment Operators
        // ============================================================================
        suite.section("Assignment Operators");

        // Test assignment with half scalar
        {
            half4 v;
            v = half(2.5f);
            suite.assert_approximately_equal(float(v.x), 2.5f, "Half scalar assignment x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Half scalar assignment y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 2.5f, "Half scalar assignment z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 2.5f, "Half scalar assignment w", HALF_EPSILON);
        }

        // Test assignment with float scalar
        {
            half4 v;
            v = 2.5f;
            suite.assert_approximately_equal(float(v.x), 2.5f, "Float scalar assignment x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Float scalar assignment y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 2.5f, "Float scalar assignment z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 2.5f, "Float scalar assignment w", HALF_EPSILON);
        }

        // Test assignment with float4
        {
            half4 v;
            float4 fv(3.5f, 4.5f, 5.5f, 6.5f);
            v = fv;
            suite.assert_approximately_equal(float(v.x), 3.5f, "float4 assignment x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.5f, "float4 assignment y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 5.5f, "float4 assignment z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 6.5f, "float4 assignment w", HALF_EPSILON);
        }

        // Test assignment with half3
        {
            half4 v(1.0f, 2.0f, 3.0f, 4.0f);
            half3 xyz(5.0f, 6.0f, 7.0f);
            v = xyz;
            suite.assert_approximately_equal(float(v.x), 5.0f, "half3 assignment x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 6.0f, "half3 assignment y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 7.0f, "half3 assignment z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 4.0f, "half3 assignment preserves w", HALF_EPSILON);
        }

        // Test compound assignment operators (half4)
        {
            half4 v(1.0f, 2.0f, 3.0f, 4.0f);

            v += half4(3.0f, 4.0f, 5.0f, 6.0f);
            suite.assert_approximately_equal(float(v.x), 4.0f, "Operator += x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 6.0f, "Operator += y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 8.0f, "Operator += z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 10.0f, "Operator += w", HALF_EPSILON);

            v -= half4(1.0f, 2.0f, 3.0f, 4.0f);
            suite.assert_approximately_equal(float(v.x), 3.0f, "Operator -= x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.0f, "Operator -= y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 5.0f, "Operator -= z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 6.0f, "Operator -= w", HALF_EPSILON);

            v *= half4(2.0f, 3.0f, 4.0f, 5.0f);
            suite.assert_approximately_equal(float(v.x), 6.0f, "Operator *= x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 12.0f, "Operator *= y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 20.0f, "Operator *= z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 30.0f, "Operator *= w", HALF_EPSILON);

            v /= half4(2.0f, 3.0f, 4.0f, 5.0f);
            suite.assert_approximately_equal(float(v.x), 3.0f, "Operator /= x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.0f, "Operator /= y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 5.0f, "Operator /= z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 6.0f, "Operator /= w", HALF_EPSILON);
        }

        // Test compound assignment operators (scalars)
        {
            half4 v(2.0f, 3.0f, 4.0f, 5.0f);

            v *= half(2.0f);
            suite.assert_approximately_equal(float(v.x), 4.0f, "Operator *= half scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 6.0f, "Operator *= half scalar y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 8.0f, "Operator *= half scalar z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 10.0f, "Operator *= half scalar w", HALF_EPSILON);

            v /= half(2.0f);
            suite.assert_approximately_equal(float(v.x), 2.0f, "Operator /= half scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Operator /= half scalar y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 4.0f, "Operator /= half scalar z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 5.0f, "Operator /= half scalar w", HALF_EPSILON);

            v *= 2.0f;
            suite.assert_approximately_equal(float(v.x), 4.0f, "Operator *= float scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 6.0f, "Operator *= float scalar y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 8.0f, "Operator *= float scalar z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 10.0f, "Operator *= float scalar w", HALF_EPSILON);

            v /= 2.0f;
            suite.assert_approximately_equal(float(v.x), 2.0f, "Operator /= float scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Operator /= float scalar y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 4.0f, "Operator /= float scalar z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 5.0f, "Operator /= float scalar w", HALF_EPSILON);
        }

        // ============================================================================
        // 3. Binary Operators
        // ============================================================================
        suite.section("Binary Operators");

        // Test addition
        {
            half4 a(1.0f, 2.0f, 3.0f, 4.0f);
            half4 b(3.0f, 4.0f, 5.0f, 6.0f);
            half4 result = a + b;
            suite.assert_approximately_equal(float(result.x), 4.0f, "Operator + x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 6.0f, "Operator + y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 8.0f, "Operator + z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.w), 10.0f, "Operator + w", HALF_EPSILON);
        }

        // Test subtraction
        {
            half4 a(5.0f, 6.0f, 7.0f, 8.0f);
            half4 b(2.0f, 3.0f, 4.0f, 5.0f);
            half4 result = a - b;
            suite.assert_approximately_equal(float(result.x), 3.0f, "Operator - x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 3.0f, "Operator - y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 3.0f, "Operator - z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.w), 3.0f, "Operator - w", HALF_EPSILON);
        }

        // Test unary operators
        {
            half4 a(1.0f, 2.0f, 3.0f, 4.0f);
            half4 pos = +a;
            suite.assert_approximately_equal(float(pos.x), 1.0f, "Unary + x", HALF_EPSILON);
            suite.assert_approximately_equal(float(pos.y), 2.0f, "Unary + y", HALF_EPSILON);
            suite.assert_approximately_equal(float(pos.z), 3.0f, "Unary + z", HALF_EPSILON);
            suite.assert_approximately_equal(float(pos.w), 4.0f, "Unary + w", HALF_EPSILON);

            half4 neg = -a;
            suite.assert_approximately_equal(float(neg.x), -1.0f, "Unary - x", HALF_EPSILON);
            suite.assert_approximately_equal(float(neg.y), -2.0f, "Unary - y", HALF_EPSILON);
            suite.assert_approximately_equal(float(neg.z), -3.0f, "Unary - z", HALF_EPSILON);
            suite.assert_approximately_equal(float(neg.w), -4.0f, "Unary - w", HALF_EPSILON);
        }

        // Test scalar operations (half)
        {
            half4 v(2.0f, 3.0f, 4.0f, 5.0f);

            half4 result1 = v + half(1.0f);
            suite.assert_approximately_equal(float(result1.x), 3.0f, "Vector + half x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result1.y), 4.0f, "Vector + half y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result1.z), 5.0f, "Vector + half z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result1.w), 6.0f, "Vector + half w", HALF_EPSILON);

            half4 result2 = half(1.0f) + v;
            suite.assert_approximately_equal(float(result2.x), 3.0f, "half + vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result2.y), 4.0f, "half + vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result2.z), 5.0f, "half + vector z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result2.w), 6.0f, "half + vector w", HALF_EPSILON);

            half4 result3 = v * half(2.0f);
            suite.assert_approximately_equal(float(result3.x), 4.0f, "Vector * half x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result3.y), 6.0f, "Vector * half y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result3.z), 8.0f, "Vector * half z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result3.w), 10.0f, "Vector * half w", HALF_EPSILON);

            half4 result4 = half(2.0f) * v;
            suite.assert_approximately_equal(float(result4.x), 4.0f, "half * vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result4.y), 6.0f, "half * vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result4.z), 8.0f, "half * vector z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result4.w), 10.0f, "half * vector w", HALF_EPSILON);

            half4 result5 = v / half(2.0f);
            suite.assert_approximately_equal(float(result5.x), 1.0f, "Vector / half x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result5.y), 1.5f, "Vector / half y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result5.z), 2.0f, "Vector / half z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result5.w), 2.5f, "Vector / half w", HALF_EPSILON);
        }

        // Test scalar operations (float)
        {
            half4 v(2.0f, 3.0f, 4.0f, 5.0f);

            half4 result1 = v + 1.0f;
            suite.assert_approximately_equal(float(result1.x), 3.0f, "Vector + float x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result1.y), 4.0f, "Vector + float y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result1.z), 5.0f, "Vector + float z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result1.w), 6.0f, "Vector + float w", HALF_EPSILON);

            half4 result2 = 1.0f + v;
            suite.assert_approximately_equal(float(result2.x), 3.0f, "float + vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result2.y), 4.0f, "float + vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result2.z), 5.0f, "float + vector z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result2.w), 6.0f, "float + vector w", HALF_EPSILON);

            half4 result3 = v * 2.0f;
            suite.assert_approximately_equal(float(result3.x), 4.0f, "Vector * float x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result3.y), 6.0f, "Vector * float y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result3.z), 8.0f, "Vector * float z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result3.w), 10.0f, "Vector * float w", HALF_EPSILON);

            half4 result4 = 2.0f * v;
            suite.assert_approximately_equal(float(result4.x), 4.0f, "float * vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result4.y), 6.0f, "float * vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result4.z), 8.0f, "float * vector z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result4.w), 10.0f, "float * vector w", HALF_EPSILON);

            half4 result5 = v / 2.0f;
            suite.assert_approximately_equal(float(result5.x), 1.0f, "Vector / float x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result5.y), 1.5f, "Vector / float y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result5.z), 2.0f, "Vector / float z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result5.w), 2.5f, "Vector / float w", HALF_EPSILON);
        }

        // Test operations with float4
        {
            half4 hv(1.0f, 2.0f, 3.0f, 4.0f);
            float4 fv(3.0f, 4.0f, 5.0f, 6.0f);

            half4 add = hv + fv;
            suite.assert_approximately_equal(float(add.x), 4.0f, "half4 + float4 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(add.y), 6.0f, "half4 + float4 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(add.z), 8.0f, "half4 + float4 z", HALF_EPSILON);
            suite.assert_approximately_equal(float(add.w), 10.0f, "half4 + float4 w", HALF_EPSILON);

            half4 add2 = fv + hv;
            suite.assert_approximately_equal(float(add2.x), 4.0f, "float4 + half4 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(add2.y), 6.0f, "float4 + half4 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(add2.z), 8.0f, "float4 + half4 z", HALF_EPSILON);
            suite.assert_approximately_equal(float(add2.w), 10.0f, "float4 + half4 w", HALF_EPSILON);

            half4 sub = hv - fv;
            suite.assert_approximately_equal(float(sub.x), -2.0f, "half4 - float4 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(sub.y), -2.0f, "half4 - float4 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(sub.z), -2.0f, "half4 - float4 z", HALF_EPSILON);
            suite.assert_approximately_equal(float(sub.w), -2.0f, "half4 - float4 w", HALF_EPSILON);

            half4 sub2 = fv - hv;
            suite.assert_approximately_equal(float(sub2.x), 2.0f, "float4 - half4 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(sub2.y), 2.0f, "float4 - half4 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(sub2.z), 2.0f, "float4 - half4 z", HALF_EPSILON);
            suite.assert_approximately_equal(float(sub2.w), 2.0f, "float4 - half4 w", HALF_EPSILON);
        }

        // ============================================================================
        // 4. Access Operators and Conversions
        // ============================================================================
        suite.section("Access Operators and Conversions");

        // Test index operator
        {
            half4 v(7.0f, 8.0f, 9.0f, 10.0f);
            suite.assert_approximately_equal(float(v[0]), 7.0f, "Operator [] index 0", HALF_EPSILON);
            suite.assert_approximately_equal(float(v[1]), 8.0f, "Operator [] index 1", HALF_EPSILON);
            suite.assert_approximately_equal(float(v[2]), 9.0f, "Operator [] index 2", HALF_EPSILON);
            suite.assert_approximately_equal(float(v[3]), 10.0f, "Operator [] index 3", HALF_EPSILON);

            v[0] = half(11.0f);
            v[1] = half(12.0f);
            v[2] = half(13.0f);
            v[3] = half(14.0f);
            suite.assert_approximately_equal(float(v.x), 11.0f, "Operator [] mutable x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 12.0f, "Operator [] mutable y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 13.0f, "Operator [] mutable z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 14.0f, "Operator [] mutable w", HALF_EPSILON);
        }

        // Test conversion to float4
        {
            half4 v(1.5f, 2.5f, 3.5f, 4.5f);
            float4 fv = float4(v);
            suite.assert_approximately_equal(fv.x, 1.5f, "Conversion to float4 x", HALF_EPSILON);
            suite.assert_approximately_equal(fv.y, 2.5f, "Conversion to float4 y", HALF_EPSILON);
            suite.assert_approximately_equal(fv.z, 3.5f, "Conversion to float4 z", HALF_EPSILON);
            suite.assert_approximately_equal(fv.w, 4.5f, "Conversion to float4 w", HALF_EPSILON);
        }

        // Test to_float4 function
        {
            half4 v(3.0f, 4.0f, 5.0f, 6.0f);
            float4 fv = to_float4(v);
            suite.assert_approximately_equal(fv.x, 3.0f, "to_float4 x", HALF_EPSILON);
            suite.assert_approximately_equal(fv.y, 4.0f, "to_float4 y", HALF_EPSILON);
            suite.assert_approximately_equal(fv.z, 5.0f, "to_float4 z", HALF_EPSILON);
            suite.assert_approximately_equal(fv.w, 6.0f, "to_float4 w", HALF_EPSILON);
        }

        // Test to_half4 function
        {
            float4 fv(3.0f, 4.0f, 5.0f, 6.0f);
            half4 v = to_half4(fv);
            suite.assert_approximately_equal(float(v.x), 3.0f, "to_half4 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.0f, "to_half4 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 5.0f, "to_half4 z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 6.0f, "to_half4 w", HALF_EPSILON);
        }

        // ============================================================================
        // 5. Mathematical Functions (GLOBAL FUNCTIONS)
        // ============================================================================
        suite.section("Mathematical Functions");

        // Test length
        {
            half4 v(2.0f, 3.0f, 6.0f, 4.0f);
            half len = length(v);
            half len_sq = length_sq(v);

            // sqrt(4 + 9 + 36 + 16) = sqrt(65) ≈ 8.0623
            suite.assert_approximately_equal(float(len), 8.0623f, "length()", HALF_MATH_EPSILON);
            suite.assert_approximately_equal(float(len_sq), 65.0f, "length_sq()", HALF_EPSILON);

            half4 zero(0.0f, 0.0f, 0.0f, 0.0f);
            suite.assert_approximately_equal(float(length(zero)), 0.0f, "length() of zero vector", HALF_EPSILON);
        }

        // Test normalization
        {
            half4 v(2.0f, 3.0f, 6.0f, 4.0f);
            half4 normalized = normalize(v);
            float normalized_len = float(length(normalized));

            suite.assert_approximately_equal(normalized_len, 1.0f, "normalize() length", HALF_MATH_EPSILON);

            // Check normalized components
            float inv_len = 1.0f / 8.0623f;
            suite.assert_approximately_equal(float(normalized.x), 2.0f * inv_len, "normalize() x", HALF_MATH_EPSILON);
            suite.assert_approximately_equal(float(normalized.y), 3.0f * inv_len, "normalize() y", HALF_MATH_EPSILON);
            suite.assert_approximately_equal(float(normalized.z), 6.0f * inv_len, "normalize() z", HALF_MATH_EPSILON);
            suite.assert_approximately_equal(float(normalized.w), 4.0f * inv_len, "normalize() w", HALF_MATH_EPSILON);

            // Test normalizing zero vector
            half4 zero(0.0f, 0.0f, 0.0f, 0.0f);
            half4 zero_norm = normalize(zero);
            suite.assert_approximately_equal(float(zero_norm.x), 0.0f, "normalize() zero vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero_norm.y), 0.0f, "normalize() zero vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero_norm.z), 0.0f, "normalize() zero vector z", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero_norm.w), 0.0f, "normalize() zero vector w", HALF_EPSILON);
        }

        // Test dot product
        {
            half4 a(1.0f, 2.0f, 3.0f, 4.0f);
            half4 b(5.0f, 6.0f, 7.0f, 8.0f);
            half dot_result = dot(a, b);
            suite.assert_approximately_equal(float(dot_result), 70.0f, "dot()", HALF_EPSILON); // 1*5 + 2*6 + 3*7 + 4*8 = 5+12+21+32=70

            // Orthogonal vectors (only first three components)
            half4 orth1(1.0f, 0.0f, 0.0f, 0.0f);
            half4 orth2(0.0f, 1.0f, 0.0f, 0.0f);
            half orth_dot = dot(orth1, orth2);
            suite.assert_approximately_equal(float(orth_dot), 0.0f, "dot() orthogonal vectors", HALF_EPSILON);
        }

        // Test 3D dot product (dot3)
        {
            half4 a(1.0f, 2.0f, 3.0f, 4.0f);
            half4 b(5.0f, 6.0f, 7.0f, 8.0f);
            half dot3_result = dot3(a, b);
            suite.assert_approximately_equal(float(dot3_result), 38.0f, "dot3()", HALF_EPSILON); // 1*5 + 2*6 + 3*7 = 5+12+21=38
        }

        // Test cross product (3D)
        {
            half4 a(1.0f, 2.0f, 3.0f, 4.0f);
            half4 b(5.0f, 6.0f, 7.0f, 8.0f);
            half4 cross_result = cross(a, b);

            // (2*7 - 3*6, 3*5 - 1*7, 1*6 - 2*5, 0) = (14-18, 15-7, 6-10, 0) = (-4, 8, -4, 0)
            suite.assert_approximately_equal(float(cross_result.x), -4.0f, "cross() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_result.y), 8.0f, "cross() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_result.z), -4.0f, "cross() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_result.w), 0.0f, "cross() w should be 0", HALF_EPSILON);
        }

        // Test distance
        {
            half4 a(1.0f, 2.0f, 3.0f, 4.0f);
            half4 b(4.0f, 6.0f, 8.0f, 10.0f);
            half dist = distance(a, b);
            half dist_sq = distance_sq(a, b);

            // (4-1)² + (6-2)² + (8-3)² + (10-4)² = 9 + 16 + 25 + 36 = 86
            suite.assert_approximately_equal(float(dist), std::sqrt(86.0f), "distance()", HALF_MATH_EPSILON);
            suite.assert_approximately_equal(float(dist_sq), 86.0f, "distance_sq()", HALF_EPSILON);
        }

        // Test reflection
        {
            half4 incident(1.0f, -1.0f, 0.0f, 0.0f);
            half4 normal(0.0f, 1.0f, 0.0f, 0.0f);
            half4 reflected = reflect(incident, normal);

            // Reflected vector should be (1, 1, 0, 0)
            suite.assert_approximately_equal(float(reflected.x), 1.0f, "reflect() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(reflected.y), 1.0f, "reflect() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(reflected.z), 0.0f, "reflect() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(reflected.w), 0.0f, "reflect() w", HALF_EPSILON);
        }

        // Test angle between
        {
            half4 a(1.0f, 0.0f, 0.0f, 0.0f);
            half4 b(0.0f, 1.0f, 0.0f, 0.0f);
            half angle = angle_between(a, b);

            suite.assert_approximately_equal(float(angle), Constants::FloatConstants::HalfPi, "angle_between() 90 degrees", HALF_ANGLE_EPSILON);
        }

        // ============================================================================
        // 6. HLSL-like Functions (GLOBAL FUNCTIONS)
        // ============================================================================
        suite.section("HLSL-like Functions");

        // Test abs
        {
            half4 v(-1.5f, 2.5f, -3.5f, 4.5f);
            half4 result = abs(v);

            suite.assert_approximately_equal(float(result.x), 1.5f, "abs() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 2.5f, "abs() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 3.5f, "abs() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.w), 4.5f, "abs() w", HALF_EPSILON);
        }

        // Test sign
        {
            half4 v(-2.0f, 0.0f, 3.0f, -0.5f);
            half4 result = sign(v);

            suite.assert_approximately_equal(float(result.x), -1.0f, "sign() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.0f, "sign() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 1.0f, "sign() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.w), -1.0f, "sign() w", HALF_EPSILON);
        }

        // Test floor
        {
            half4 v(1.7f, -2.3f, 3.1f, -4.9f);
            half4 result = floor(v);

            suite.assert_approximately_equal(float(result.x), 1.0f, "floor() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), -3.0f, "floor() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 3.0f, "floor() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.w), -5.0f, "floor() w", HALF_EPSILON);
        }

        // Test ceil
        {
            half4 v(1.2f, -2.7f, 3.9f, -4.1f);
            half4 result = ceil(v);

            suite.assert_approximately_equal(float(result.x), 2.0f, "ceil() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), -2.0f, "ceil() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 4.0f, "ceil() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.w), -4.0f, "ceil() w", HALF_EPSILON);
        }

        // Test round
        {
            half4 v(1.4f, 1.6f, -1.5f, -2.4f);
            half4 result = round(v);

            suite.assert_approximately_equal(float(result.x), 1.0f, "round() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 2.0f, "round() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), -2.0f, "round() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.w), -2.0f, "round() w", HALF_EPSILON);
        }

        // Test frac (HLSL semantics)
        {
            half4 v(1.7f, -2.3f, 3.0f, -4.8f);
            half4 result = frac(v);

            // HLSL: frac(x) = x - floor(x)
            // frac(1.7) = 1.7 - 1.0 = 0.7
            // frac(-2.3) = -2.3 - (-3.0) = 0.7
            // frac(3.0) = 3.0 - 3.0 = 0.0
            // frac(-4.8) = -4.8 - (-5.0) = 0.2
            suite.assert_approximately_equal(float(result.x), 0.7f, "frac() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.7f, "frac() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 0.0f, "frac() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.w), 0.2f, "frac() w", HALF_EPSILON);
        }

        // Test saturate
        {
            half4 v(-0.5f, 0.5f, 1.5f, 2.0f);
            half4 result = saturate(v);

            suite.assert_approximately_equal(float(result.x), 0.0f, "saturate() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.5f, "saturate() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 1.0f, "saturate() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.w), 1.0f, "saturate() w", HALF_EPSILON);
        }

        // Test step
        {
            half4 v(0.5f, 1.0f, 1.5f, 2.0f);
            half4 result = step(half(1.0f), v);

            suite.assert_approximately_equal(float(result.x), 0.0f, "step() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 1.0f, "step() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 1.0f, "step() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.w), 1.0f, "step() w", HALF_EPSILON);
        }

        // Test smoothstep
        {
            half4 v(0.5f, 1.5f, 2.5f, 0.0f);
            half4 result = smoothstep(half(0.0f), half(2.0f), v);

            // For t=0.25: 3t² - 2t³ = 3*0.0625 - 2*0.015625 = 0.1875 - 0.03125 = 0.15625
            // For t=0.75: 3*0.5625 - 2*0.421875 = 1.6875 - 0.84375 = 0.84375
            // For t=1.25: clamp to [0,1], but t>1 => 1.0
            // For t=0.0: 0.0
            suite.assert_approximately_equal(float(result.x), 0.15625f, "smoothstep() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.84375f, "smoothstep() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 1.0f, "smoothstep() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.w), 0.0f, "smoothstep() w", HALF_EPSILON);
        }

        // Test min/max
        {
            half4 a(1.0f, 3.0f, 5.0f, 7.0f);
            half4 b(2.0f, 2.0f, 6.0f, 8.0f);

            half4 min_result = min(a, b);
            half4 max_result = max(a, b);

            suite.assert_approximately_equal(float(min_result.x), 1.0f, "min() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(min_result.y), 2.0f, "min() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(min_result.z), 5.0f, "min() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(min_result.w), 7.0f, "min() w", HALF_EPSILON);
            suite.assert_approximately_equal(float(max_result.x), 2.0f, "max() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(max_result.y), 3.0f, "max() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(max_result.z), 6.0f, "max() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(max_result.w), 8.0f, "max() w", HALF_EPSILON);
        }

        // Test clamp
        {
            half4 v(2.5f, -0.5f, 1.5f, 3.0f);
            half4 min_val(1.0f, 0.0f, 1.0f, 2.0f);
            half4 max_val(2.0f, 1.0f, 2.0f, 2.5f);

            half4 clamped = clamp(v, min_val, max_val);
            suite.assert_approximately_equal(float(clamped.x), 2.0f, "clamp() vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(clamped.y), 0.0f, "clamp() vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(clamped.z), 1.5f, "clamp() vector z", HALF_EPSILON);
            suite.assert_approximately_equal(float(clamped.w), 2.5f, "clamp() vector w", HALF_EPSILON);

            half4 clamped_scalar = clamp(v, 0.0f, 1.0f);
            suite.assert_approximately_equal(float(clamped_scalar.x), 1.0f, "clamp() scalar x", HALF_EPSILON);
            suite.assert_approximately_equal(float(clamped_scalar.y), 0.0f, "clamp() scalar y", HALF_EPSILON);
            suite.assert_approximately_equal(float(clamped_scalar.z), 1.0f, "clamp() scalar z", HALF_EPSILON);
            suite.assert_approximately_equal(float(clamped_scalar.w), 1.0f, "clamp() scalar w", HALF_EPSILON);
        }

        // ============================================================================
        // 7. Color Operations (GLOBAL FUNCTIONS)
        // ============================================================================
        suite.section("Color Operations");

        // Test luminance
        {
            half4 color(0.5f, 0.3f, 0.2f, 1.0f);
            half luma = luminance(color);

            // 0.2126*0.5 + 0.7152*0.3 + 0.0722*0.2 = 0.1063 + 0.21456 + 0.01444 = 0.3353
            float expected = 0.2126f * 0.5f + 0.7152f * 0.3f + 0.0722f * 0.2f;
            suite.assert_approximately_equal(float(luma), expected, "luminance()", COLOR_EPSILON);
        }

        // Test brightness
        {
            half4 color(0.5f, 0.3f, 0.2f, 1.0f);
            half bright = brightness(color);

            // (0.5 + 0.3 + 0.2) / 3 = 1.0 / 3 ≈ 0.3333
            float expected = (0.5f + 0.3f + 0.2f) / 3.0f;
            suite.assert_approximately_equal(float(bright), expected, "brightness()", COLOR_EPSILON);
        }

        // Test alpha premultiplication
        {
            half4 color(0.5f, 0.3f, 0.2f, 0.5f);
            half4 premultiplied = premultiply_alpha(color);

            suite.assert_approximately_equal(float(premultiplied.x), 0.25f, "premultiply_alpha() x", COLOR_EPSILON);
            suite.assert_approximately_equal(float(premultiplied.y), 0.15f, "premultiply_alpha() y", COLOR_EPSILON);
            suite.assert_approximately_equal(float(premultiplied.z), 0.1f, "premultiply_alpha() z", COLOR_EPSILON);
            suite.assert_approximately_equal(float(premultiplied.w), 0.5f, "premultiply_alpha() w", COLOR_EPSILON);
        }

        // Test alpha unpremultiplication
        {
            // First premultiply, then check reverse transformation
            half4 original(0.5f, 0.3f, 0.2f, 0.5f);
            half4 premultiplied = premultiply_alpha(original);
            half4 unpremultiplied = unpremultiply_alpha(premultiplied);

            // Should return to original values (with some precision)
            suite.assert_approximately_equal(float(unpremultiplied.x), 0.5f, "unpremultiply_alpha() x", COLOR_EPSILON);
            suite.assert_approximately_equal(float(unpremultiplied.y), 0.3f, "unpremultiply_alpha() y", COLOR_EPSILON);
            suite.assert_approximately_equal(float(unpremultiplied.z), 0.2f, "unpremultiply_alpha() z", COLOR_EPSILON);
            suite.assert_approximately_equal(float(unpremultiplied.w), 0.5f, "unpremultiply_alpha() w", COLOR_EPSILON);
        }

        // Test grayscale
        {
            half4 color(0.5f, 0.3f, 0.2f, 1.0f);
            half4 grayscale = rgb_to_grayscale(color);

            float luma = 0.2126f * 0.5f + 0.7152f * 0.3f + 0.0722f * 0.2f;
            suite.assert_approximately_equal(float(grayscale.x), luma, "rgb_to_grayscale() x", COLOR_EPSILON);
            suite.assert_approximately_equal(float(grayscale.y), luma, "rgb_to_grayscale() y", COLOR_EPSILON);
            suite.assert_approximately_equal(float(grayscale.z), luma, "rgb_to_grayscale() z", COLOR_EPSILON);
            suite.assert_approximately_equal(float(grayscale.w), 1.0f, "rgb_to_grayscale() preserves alpha", COLOR_EPSILON);
        }

        // Test sRGB <-> linear conversion
        {
            half4 srgb(0.5f, 0.5f, 0.5f, 1.0f);
            half4 linear = srgb_to_linear(srgb);

            // For value 0.5 in sRGB: 0.5 <= 0.04045 ? 0.5/12.92 : pow((0.5+0.055)/1.055, 2.4)
            // 0.5 > 0.04045, so: pow((0.5+0.055)/1.055, 2.4) ≈ pow(0.526, 2.4) ≈ 0.214
            float expected = std::pow((0.5f + 0.055f) / 1.055f, 2.4f);
            suite.assert_approximately_equal(float(linear.x), expected, "srgb_to_linear() x", COLOR_EPSILON);
            suite.assert_approximately_equal(float(linear.y), expected, "srgb_to_linear() y", COLOR_EPSILON);
            suite.assert_approximately_equal(float(linear.z), expected, "srgb_to_linear() z", COLOR_EPSILON);
            suite.assert_approximately_equal(float(linear.w), 1.0f, "srgb_to_linear() preserves alpha", COLOR_EPSILON);

            // Reverse conversion
            half4 back_to_srgb = linear_to_srgb(linear);

            // Check that conversion is reversible with some precision
            suite.assert_approximately_equal(float(back_to_srgb.x), 0.5f, "linear_to_srgb() round-trip x", COLOR_EPSILON);
            suite.assert_approximately_equal(float(back_to_srgb.y), 0.5f, "linear_to_srgb() round-trip y", COLOR_EPSILON);
            suite.assert_approximately_equal(float(back_to_srgb.z), 0.5f, "linear_to_srgb() round-trip z", COLOR_EPSILON);
            suite.assert_approximately_equal(float(back_to_srgb.w), 1.0f, "linear_to_srgb() round-trip preserves alpha", COLOR_EPSILON);
        }

        // ============================================================================
        // 8. Geometric Operations (GLOBAL FUNCTIONS)
        // ============================================================================
        suite.section("Geometric Operations");

        // Test projection (division by w)
        {
            half4 v(2.0f, 4.0f, 6.0f, 2.0f);
            half3 projected = project(v);

            // (2/2, 4/2, 6/2) = (1, 2, 3)
            suite.assert_approximately_equal(float(projected.x), 1.0f, "project() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.y), 2.0f, "project() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.z), 3.0f, "project() z", HALF_EPSILON);

            // Test with w = 0 (should return zero vector)
            half4 zero_w(2.0f, 4.0f, 6.0f, 0.0f);
            half3 projected_zero = project(zero_w);
            suite.assert_approximately_equal(float(projected_zero.x), 0.0f, "project() with w=0 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected_zero.y), 0.0f, "project() with w=0 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected_zero.z), 0.0f, "project() with w=0 z", HALF_EPSILON);
        }

        // Test conversion to homogeneous coordinates
        {
            half4 v(2.0f, 4.0f, 6.0f, 8.0f);
            half4 homogeneous = to_homogeneous(v);

            // (2, 4, 6, 1)
            suite.assert_approximately_equal(float(homogeneous.x), 2.0f, "to_homogeneous() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(homogeneous.y), 4.0f, "to_homogeneous() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(homogeneous.z), 6.0f, "to_homogeneous() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(homogeneous.w), 1.0f, "to_homogeneous() w becomes 1", HALF_EPSILON);
        }

        // Test ensure_normalized utility
        {
            half4 normalized(0.182574f, 0.365148f, 0.547723f, 0.730297f); // Normalized (1,2,3,4)
            half4 not_normalized(1.0f, 2.0f, 3.0f, 4.0f);

            half4 ensured = ensure_normalized(not_normalized);
            float ensured_len = float(length(ensured));

            suite.assert_approximately_equal(ensured_len, 1.0f, "ensure_normalized() length", HALF_MATH_EPSILON);

            // Test with fallback
            half4 zero(0.0f, 0.0f, 0.0f, 0.0f);
            half4 with_fallback = ensure_normalized(zero, half4::unit_w());
            suite.assert_approximately_equal(float(with_fallback.x), 0.0f, "ensure_normalized() fallback x", HALF_EPSILON);
            suite.assert_approximately_equal(float(with_fallback.y), 0.0f, "ensure_normalized() fallback y", HALF_EPSILON);
            suite.assert_approximately_equal(float(with_fallback.z), 0.0f, "ensure_normalized() fallback z", HALF_EPSILON);
            suite.assert_approximately_equal(float(with_fallback.w), 1.0f, "ensure_normalized() fallback w", HALF_EPSILON);
        }

        // ============================================================================
        // 9. Swizzle Operations
        // ============================================================================
        suite.section("Swizzle Operations");

        {
            half4 v(2.0f, 3.0f, 4.0f, 5.0f);

            // 2D swizzles
            half2 xy = v.xy();
            suite.assert_approximately_equal(float(xy.x), 2.0f, "xy() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(xy.y), 3.0f, "xy() y", HALF_EPSILON);

            half2 xz = v.xz();
            suite.assert_approximately_equal(float(xz.x), 2.0f, "xz() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(xz.y), 4.0f, "xz() y", HALF_EPSILON);

            half2 xw = v.xw();
            suite.assert_approximately_equal(float(xw.x), 2.0f, "xw() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(xw.y), 5.0f, "xw() y", HALF_EPSILON);

            half2 yz = v.yz();
            suite.assert_approximately_equal(float(yz.x), 3.0f, "yz() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(yz.y), 4.0f, "yz() y", HALF_EPSILON);

            half2 yw = v.yw();
            suite.assert_approximately_equal(float(yw.x), 3.0f, "yw() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(yw.y), 5.0f, "yw() y", HALF_EPSILON);

            half2 zw = v.zw();
            suite.assert_approximately_equal(float(zw.x), 4.0f, "zw() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zw.y), 5.0f, "zw() y", HALF_EPSILON);

            // 3D swizzles
            half3 xyz = v.xyz();
            suite.assert_approximately_equal(float(xyz.x), 2.0f, "xyz() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(xyz.y), 3.0f, "xyz() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(xyz.z), 4.0f, "xyz() z", HALF_EPSILON);

            half3 xyw = v.xyw();
            suite.assert_approximately_equal(float(xyw.x), 2.0f, "xyw() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(xyw.y), 3.0f, "xyw() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(xyw.z), 5.0f, "xyw() z", HALF_EPSILON);

            half3 xzw = v.xzw();
            suite.assert_approximately_equal(float(xzw.x), 2.0f, "xzw() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(xzw.y), 4.0f, "xzw() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(xzw.z), 5.0f, "xzw() z", HALF_EPSILON);

            half3 yzw = v.yzw();
            suite.assert_approximately_equal(float(yzw.x), 3.0f, "yzw() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(yzw.y), 4.0f, "yzw() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(yzw.z), 5.0f, "yzw() z", HALF_EPSILON);

            // 4D swizzles
            half4 yxzw = v.yxzw();
            suite.assert_approximately_equal(float(yxzw.x), 3.0f, "yxzw() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(yxzw.y), 2.0f, "yxzw() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(yxzw.z), 4.0f, "yxzw() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(yxzw.w), 5.0f, "yxzw() w", HALF_EPSILON);

            half4 zxyw = v.zxyw();
            suite.assert_approximately_equal(float(zxyw.x), 4.0f, "zxyw() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zxyw.y), 2.0f, "zxyw() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(zxyw.z), 3.0f, "zxyw() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(zxyw.w), 5.0f, "zxyw() w", HALF_EPSILON);

            half4 zyxw = v.zyxw();
            suite.assert_approximately_equal(float(zyxw.x), 4.0f, "zyxw() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zyxw.y), 3.0f, "zyxw() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(zyxw.z), 2.0f, "zyxw() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(zyxw.w), 5.0f, "zyxw() w", HALF_EPSILON);

            half4 wzyx = v.wzyx();
            suite.assert_approximately_equal(float(wzyx.x), 5.0f, "wzyx() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(wzyx.y), 4.0f, "wzyx() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(wzyx.z), 3.0f, "wzyx() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(wzyx.w), 2.0f, "wzyx() w", HALF_EPSILON);
        }

        // Color swizzles
        {
            half4 color(0.2f, 0.4f, 0.6f, 0.8f);

            suite.assert_approximately_equal(float(color.r()), 0.2f, "r()", HALF_EPSILON);
            suite.assert_approximately_equal(float(color.g()), 0.4f, "g()", HALF_EPSILON);
            suite.assert_approximately_equal(float(color.b()), 0.6f, "b()", HALF_EPSILON);
            suite.assert_approximately_equal(float(color.a()), 0.8f, "a()", HALF_EPSILON);

            half2 rg = color.rg();
            suite.assert_approximately_equal(float(rg.x), 0.2f, "rg() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(rg.y), 0.4f, "rg() y", HALF_EPSILON);

            half2 rb = color.rb();
            suite.assert_approximately_equal(float(rb.x), 0.2f, "rb() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(rb.y), 0.6f, "rb() y", HALF_EPSILON);

            half2 ra = color.ra();
            suite.assert_approximately_equal(float(ra.x), 0.2f, "ra() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(ra.y), 0.8f, "ra() y", HALF_EPSILON);

            half2 gb = color.gb();
            suite.assert_approximately_equal(float(gb.x), 0.4f, "gb() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(gb.y), 0.6f, "gb() y", HALF_EPSILON);

            half2 ga = color.ga();
            suite.assert_approximately_equal(float(ga.x), 0.4f, "ga() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(ga.y), 0.8f, "ga() y", HALF_EPSILON);

            half2 ba = color.ba();
            suite.assert_approximately_equal(float(ba.x), 0.6f, "ba() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(ba.y), 0.8f, "ba() y", HALF_EPSILON);

            half3 rgb = color.rgb();
            suite.assert_approximately_equal(float(rgb.x), 0.2f, "rgb() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(rgb.y), 0.4f, "rgb() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(rgb.z), 0.6f, "rgb() z", HALF_EPSILON);

            half3 rga = color.rga();
            suite.assert_approximately_equal(float(rga.x), 0.2f, "rga() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(rga.y), 0.4f, "rga() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(rga.z), 0.8f, "rga() z", HALF_EPSILON);

            half3 rba = color.rba();
            suite.assert_approximately_equal(float(rba.x), 0.2f, "rba() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(rba.y), 0.6f, "rba() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(rba.z), 0.8f, "rba() z", HALF_EPSILON);

            half3 gba = color.gba();
            suite.assert_approximately_equal(float(gba.x), 0.4f, "gba() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(gba.y), 0.6f, "gba() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(gba.z), 0.8f, "gba() z", HALF_EPSILON);

            half4 grba = color.grba();
            suite.assert_approximately_equal(float(grba.x), 0.4f, "grba() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(grba.y), 0.2f, "grba() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(grba.z), 0.6f, "grba() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(grba.w), 0.8f, "grba() w", HALF_EPSILON);

            half4 brga = color.brga();
            suite.assert_approximately_equal(float(brga.x), 0.6f, "brga() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(brga.y), 0.2f, "brga() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(brga.z), 0.4f, "brga() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(brga.w), 0.8f, "brga() w", HALF_EPSILON);

            half4 bgra = color.bgra();
            suite.assert_approximately_equal(float(bgra.x), 0.6f, "bgra() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(bgra.y), 0.4f, "bgra() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(bgra.z), 0.2f, "bgra() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(bgra.w), 0.8f, "bgra() w", HALF_EPSILON);

            half4 abgr = color.abgr();
            suite.assert_approximately_equal(float(abgr.x), 0.8f, "abgr() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(abgr.y), 0.6f, "abgr() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(abgr.z), 0.4f, "abgr() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(abgr.w), 0.2f, "abgr() w", HALF_EPSILON);
        }

        // ============================================================================
        // 10. Utility Methods
        // ============================================================================
        suite.section("Utility Methods");

        // Test isValid
        {
            half4 valid(1.0f, 2.0f, 3.0f, 4.0f);
            suite.assert_true(valid.is_valid(), "is_valid() for valid vector");
            suite.assert_true(is_valid(valid), "global is_valid() for valid vector");
        }

        // Test approximately
        {
            half4 a(1.0f, 2.0f, 3.0f, 4.0f);
            half4 b(1.001f, 2.001f, 3.001f, 4.001f);
            half4 c(1.1f, 2.1f, 3.1f, 4.1f);

            suite.assert_true(approximately(a, b, 0.01f), "approximately() within epsilon");
            suite.assert_false(approximately(a, c, 0.01f), "approximately() outside epsilon");

            bool global_approx = approximately(a, b, 0.01f);
            suite.assert_true(global_approx, "global approximately() within epsilon");
        }

        // Test approximately_zero
        {
            half4 zero(0.0f, 0.0f, 0.0f, 0.0f);
            half4 near_zero(0.001f, 0.001f, 0.001f, 0.001f);
            half4 not_zero(0.1f, 0.1f, 0.1f, 0.1f);

            suite.assert_true(approximately_zero(zero, 0.01f), "approximately_zero() for zero");
            suite.assert_true(approximately_zero(near_zero, 0.01f), "approximately_zero() for near zero");
            suite.assert_false(approximately_zero(not_zero, 0.01f), "approximately_zero() for non-zero");
        }

        // Test is_normalized
        {
            half4 normalized(0.182574f, 0.365148f, 0.547723f, 0.730297f); // Normalized (1,2,3,4)
            half4 not_normalized(1.0f, 2.0f, 3.0f, 4.0f);

            suite.assert_true(is_normalized(normalized, 0.01f), "is_normalized() for normalized vector");
            suite.assert_false(is_normalized(not_normalized, 0.01f), "is_normalized() for non-normalized");

            bool global_normalized = is_normalized(normalized, 0.01f);
            suite.assert_true(global_normalized, "global is_normalized() for normalized vector");
        }

        // Test to_string
        {
            half4 v(1.5f, 2.5f, 3.5f, 4.5f);
            std::string str = v.to_string();

            // Check for expected values in string
            suite.assert_true(str.find("1.5") != std::string::npos || str.find("1.500") != std::string::npos,
                "to_string() contains x value");
            suite.assert_true(str.find("2.5") != std::string::npos || str.find("2.500") != std::string::npos,
                "to_string() contains y value");
            suite.assert_true(str.find("3.5") != std::string::npos || str.find("3.500") != std::string::npos,
                "to_string() contains z value");
            suite.assert_true(str.find("4.5") != std::string::npos || str.find("4.500") != std::string::npos,
                "to_string() contains w value");
        }

        // Test data()
        {
            half4 v(7.0f, 8.0f, 9.0f, 10.0f);
            const half* cdata = v.data();
            half* data = v.data();

            suite.assert_approximately_equal(float(cdata[0]), 7.0f, "data() const access x", HALF_EPSILON);
            suite.assert_approximately_equal(float(cdata[1]), 8.0f, "data() const access y", HALF_EPSILON);
            suite.assert_approximately_equal(float(cdata[2]), 9.0f, "data() const access z", HALF_EPSILON);
            suite.assert_approximately_equal(float(cdata[3]), 10.0f, "data() const access w", HALF_EPSILON);

            data[0] = half(11.0f);
            suite.assert_approximately_equal(float(v.x), 11.0f, "data() mutable modification x", HALF_EPSILON);
        }

        // Test set_xyz
        {
            half4 v(1.0f, 2.0f, 3.0f, 4.0f);
            half3 xyz(5.0f, 6.0f, 7.0f);
            v.set_xyz(xyz);

            suite.assert_approximately_equal(float(v.x), 5.0f, "set_xyz() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 6.0f, "set_xyz() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 7.0f, "set_xyz() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 4.0f, "set_xyz() preserves w", HALF_EPSILON);
        }

        // Test set_xy
        {
            half4 v(1.0f, 2.0f, 3.0f, 4.0f);
            half2 xy(5.0f, 6.0f);
            v.set_xy(xy);

            suite.assert_approximately_equal(float(v.x), 5.0f, "set_xy() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 6.0f, "set_xy() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "set_xy() preserves z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 4.0f, "set_xy() preserves w", HALF_EPSILON);
        }

        // Test set_zw
        {
            half4 v(1.0f, 2.0f, 3.0f, 4.0f);
            half2 zw(5.0f, 6.0f);
            v.set_zw(zw);

            suite.assert_approximately_equal(float(v.x), 1.0f, "set_zw() preserves x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.0f, "set_zw() preserves y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 5.0f, "set_zw() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.w), 6.0f, "set_zw() w", HALF_EPSILON);
        }

        // ============================================================================
        // 11. Comparison Operators
        // ============================================================================
        suite.section("Comparison Operators");

        {
            half4 a(1.0f, 2.0f, 3.0f, 4.0f);
            half4 b(1.0f, 2.0f, 3.0f, 4.0f);
            half4 c(1.1f, 2.1f, 3.1f, 4.1f);

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
            half4 pos_zero(0.0f, 0.0f, 0.0f, 0.0f);
            half4 neg_zero(-0.0f, -0.0f, -0.0f, -0.0f);

            suite.assert_true(pos_zero.is_zero(), "is_zero() for positive zero");
            suite.assert_true(neg_zero.is_zero(), "is_zero() for negative zero");
            suite.assert_true(pos_zero.is_all_zero(), "is_all_zero() for positive zero");
            suite.assert_true(neg_zero.is_all_zero(), "is_all_zero() for negative zero");
        }

        // Test with infinities
        {
            half4 pos_inf(std::numeric_limits<float>::infinity(), 1.0f, 2.0f, 3.0f);
            half4 neg_inf(-std::numeric_limits<float>::infinity(), 1.0f, 2.0f, 3.0f);
            half4 all_pos_inf(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(),
                std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
            half4 all_neg_inf(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(),
                -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());

            suite.assert_true(pos_inf.is_inf(), "is_inf() for vector with positive infinity");
            suite.assert_true(neg_inf.is_inf(), "is_inf() for vector with negative infinity");
            suite.assert_true(all_pos_inf.is_all_inf(), "is_all_inf() for all positive infinity");
            suite.assert_true(all_neg_inf.is_all_inf(), "is_all_inf() for all negative infinity");
            suite.assert_true(pos_inf.is_positive_inf(), "is_positive_inf() for vector with positive infinity");
            suite.assert_true(neg_inf.is_negative_inf(), "is_negative_inf() for vector with negative infinity");
            suite.assert_true(all_pos_inf.is_all_positive_inf(), "is_all_positive_inf() for all positive infinity");
            suite.assert_true(all_neg_inf.is_all_negative_inf(), "is_all_negative_inf() for all negative infinity");
        }

        // Test with NaN
        {
            half4 nan_vec(std::numeric_limits<float>::quiet_NaN(), 1.0f, 2.0f, 3.0f);
            half4 all_nan(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN(),
                std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN());

            suite.assert_true(nan_vec.is_nan(), "is_nan() for vector with NaN");
            suite.assert_true(all_nan.is_all_nan(), "is_all_nan() for all-NaN vector");
        }

        // Test with finite values
        {
            half4 finite(1.0f, 2.0f, 3.0f, 4.0f);

            suite.assert_true(finite.is_finite(), "is_finite() for finite vector");
            suite.assert_true(finite.is_all_finite(), "is_all_finite() for finite vector");
        }

        // Test with positive/negative values
        {
            half4 pos(1.0f, 2.0f, 3.0f, 4.0f);
            half4 neg(-1.0f, -2.0f, -3.0f, -4.0f);
            half4 mixed(-1.0f, 2.0f, -3.0f, 4.0f);

            suite.assert_true(pos.is_positive(), "is_positive() for positive vector");
            suite.assert_true(pos.is_all_positive(), "is_all_positive() for positive vector");
            suite.assert_true(neg.is_negative(), "is_negative() for negative vector");
            suite.assert_true(neg.is_all_negative(), "is_all_negative() for negative vector");
            suite.assert_true(mixed.is_positive(), "is_positive() for mixed vector");
            suite.assert_true(mixed.is_negative(), "is_negative() for mixed vector");
            suite.assert_false(mixed.is_all_positive(), "is_all_positive() for mixed vector");
            suite.assert_false(mixed.is_all_negative(), "is_all_negative() for mixed vector");
        }

        // Test with positive/negative zeros
        {
            half4 pos_zero(0.0f, 0.0f, 0.0f, 0.0f);
            half4 neg_zero(-0.0f, -0.0f, -0.0f, -0.0f);
            half4 mixed_zero(0.0f, -0.0f, 0.0f, -0.0f);

            suite.assert_true(pos_zero.is_positive_zero(), "is_positive_zero() for positive zero");
            suite.assert_true(pos_zero.is_all_positive_zero(), "is_all_positive_zero() for all positive zero");
            suite.assert_true(neg_zero.is_negative_zero(), "is_negative_zero() for negative zero");
            suite.assert_true(neg_zero.is_all_negative_zero(), "is_all_negative_zero() for all negative zero");
            suite.assert_true(mixed_zero.is_positive_zero(), "is_positive_zero() for mixed zero vector");
            suite.assert_true(mixed_zero.is_negative_zero(), "is_negative_zero() for mixed zero vector");
        }

        // Test with normal numbers
        {
            half min_denorm = half::min_denormal_value();
            half4 denormal_vec(min_denorm, min_denorm, min_denorm, min_denorm);

            suite.assert_false(denormal_vec.is_normal(),
                "is_normal() for denormal vector");
            suite.assert_false(denormal_vec.is_all_normal(),
                "is_all_normal() for all denormal vector");

            // Additionally check that this is indeed a denormalized value
            uint16_t bits = min_denorm.data;
            uint16_t exp = (bits >> 10) & 0x1F;
            suite.assert_equal(exp, (uint16_t)0, "min_denormal_value has exponent 0");
        }

        // ============================================================================
        // 13. Linear Interpolation
        // ============================================================================
        suite.section("Linear Interpolation");

        {
            half4 a(0.0f, 0.0f, 0.0f, 0.0f);
            half4 b(10.0f, 20.0f, 30.0f, 40.0f);

            half4 lerp_result = lerp(a, b, half(0.5f));
            suite.assert_approximately_equal(float(lerp_result.x), 5.0f, "lerp() at 0.5 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_result.y), 10.0f, "lerp() at 0.5 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_result.z), 15.0f, "lerp() at 0.5 z", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_result.w), 20.0f, "lerp() at 0.5 w", HALF_EPSILON);

            half4 lerp_float = lerp(a, b, 0.5f);
            suite.assert_approximately_equal(float(lerp_float.x), 5.0f, "lerp() with float at 0.5 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_float.y), 10.0f, "lerp() with float at 0.5 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_float.z), 15.0f, "lerp() with float at 0.5 z", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_float.w), 20.0f, "lerp() with float at 0.5 w", HALF_EPSILON);

            half4 lerp_start = lerp(a, b, half(0.0f));
            suite.assert_approximately_equal(float(lerp_start.x), 0.0f, "lerp() at 0.0 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_start.y), 0.0f, "lerp() at 0.0 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_start.z), 0.0f, "lerp() at 0.0 z", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_start.w), 0.0f, "lerp() at 0.0 w", HALF_EPSILON);

            half4 lerp_end = lerp(a, b, half(1.0f));
            suite.assert_approximately_equal(float(lerp_end.x), 10.0f, "lerp() at 1.0 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_end.y), 20.0f, "lerp() at 1.0 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_end.z), 30.0f, "lerp() at 1.0 z", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_end.w), 40.0f, "lerp() at 1.0 w", HALF_EPSILON);
        }

        // ============================================================================
        // 14. Global Constants
        // ============================================================================
        suite.section("Global Constants");

        {
            suite.assert_approximately_equal(float(half4_Zero.x), 0.0f, "half4_Zero x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Zero.y), 0.0f, "half4_Zero y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Zero.z), 0.0f, "half4_Zero z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Zero.w), 0.0f, "half4_Zero w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_One.x), 1.0f, "half4_One x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_One.y), 1.0f, "half4_One y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_One.z), 1.0f, "half4_One z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_One.w), 1.0f, "half4_One w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_UnitX.x), 1.0f, "half4_UnitX x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_UnitX.y), 0.0f, "half4_UnitX y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_UnitX.z), 0.0f, "half4_UnitX z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_UnitX.w), 0.0f, "half4_UnitX w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_UnitY.x), 0.0f, "half4_UnitY x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_UnitY.y), 1.0f, "half4_UnitY y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_UnitY.z), 0.0f, "half4_UnitY z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_UnitY.w), 0.0f, "half4_UnitY w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_UnitZ.x), 0.0f, "half4_UnitZ x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_UnitZ.y), 0.0f, "half4_UnitZ y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_UnitZ.z), 1.0f, "half4_UnitZ z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_UnitZ.w), 0.0f, "half4_UnitZ w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_UnitW.x), 0.0f, "half4_UnitW x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_UnitW.y), 0.0f, "half4_UnitW y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_UnitW.z), 0.0f, "half4_UnitW z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_UnitW.w), 1.0f, "half4_UnitW w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_Red.x), 1.0f, "half4_Red x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Red.y), 0.0f, "half4_Red y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Red.z), 0.0f, "half4_Red z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Red.w), 1.0f, "half4_Red w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_Green.x), 0.0f, "half4_Green x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Green.y), 1.0f, "half4_Green y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Green.z), 0.0f, "half4_Green z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Green.w), 1.0f, "half4_Green w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_Blue.x), 0.0f, "half4_Blue x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Blue.y), 0.0f, "half4_Blue y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Blue.z), 1.0f, "half4_Blue z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Blue.w), 1.0f, "half4_Blue w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_White.x), 1.0f, "half4_White x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_White.y), 1.0f, "half4_White y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_White.z), 1.0f, "half4_White z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_White.w), 1.0f, "half4_White w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_Black.x), 0.0f, "half4_Black x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Black.y), 0.0f, "half4_Black y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Black.z), 0.0f, "half4_Black z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Black.w), 1.0f, "half4_Black w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_Transparent.x), 0.0f, "half4_Transparent x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Transparent.y), 0.0f, "half4_Transparent y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Transparent.z), 0.0f, "half4_Transparent z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Transparent.w), 0.0f, "half4_Transparent w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_Yellow.x), 1.0f, "half4_Yellow x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Yellow.y), 1.0f, "half4_Yellow y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Yellow.z), 0.0f, "half4_Yellow z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Yellow.w), 1.0f, "half4_Yellow w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_Cyan.x), 0.0f, "half4_Cyan x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Cyan.y), 1.0f, "half4_Cyan y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Cyan.z), 1.0f, "half4_Cyan z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Cyan.w), 1.0f, "half4_Cyan w", HALF_EPSILON);

            suite.assert_approximately_equal(float(half4_Magenta.x), 1.0f, "half4_Magenta x", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Magenta.y), 0.0f, "half4_Magenta y", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Magenta.z), 1.0f, "half4_Magenta z", HALF_EPSILON);
            suite.assert_approximately_equal(float(half4_Magenta.w), 1.0f, "half4_Magenta w", HALF_EPSILON);
        }

        // ============================================================================
        // 15. Edge Cases
        // ============================================================================
        suite.section("Edge Cases");

        // Test with very small values
        {
            half4 tiny(1e-6f, 1e-6f, 1e-6f, 1e-6f);
            suite.assert_true(approximately_zero(tiny, 1e-3f), "Tiny values approximately_zero");
        }

        // Test with very large values
        {
            half4 huge(50000.0f, 50000.0f, 50000.0f, 50000.0f);
            suite.assert_false(approximately_zero(huge), "Huge values not approximately_zero");

            // Normalization of large values
            half4 normalized_huge = normalize(huge);
            float normalized_len = float(length(normalized_huge));
            suite.assert_approximately_equal(normalized_len, 1.0f, "Normalize huge values length", HALF_EPSILON);
        }

        // Test division by zero (vector)
        {
            half4 a(1.0f, 2.0f, 3.0f, 4.0f);
            half4 zero_vec(0.0f, 0.0f, 0.0f, 0.0f);

            half4 result = a / zero_vec;
            suite.assert_true(result.x.is_inf() || result.x.is_nan(), "Division by zero vector x produces non-finite");
            suite.assert_true(result.y.is_inf() || result.y.is_nan(), "Division by zero vector y produces non-finite");
            suite.assert_true(result.z.is_inf() || result.z.is_nan(), "Division by zero vector z produces non-finite");
            suite.assert_true(result.w.is_inf() || result.w.is_nan(), "Division by zero vector w produces non-finite");
        }

        // Test division by zero (scalar)
        {
            half4 v(1.0f, 2.0f, 3.0f, 4.0f);
            half4 result = v / 0.0f;

            suite.assert_true(result.x.is_inf() || result.x.is_nan(), "Division by zero scalar x produces non-finite");
            suite.assert_true(result.y.is_inf() || result.y.is_nan(), "Division by zero scalar y produces non-finite");
            suite.assert_true(result.z.is_inf() || result.z.is_nan(), "Division by zero scalar z produces non-finite");
            suite.assert_true(result.w.is_inf() || result.w.is_nan(), "Division by zero scalar w produces non-finite");
        }

        // Test normalization of very small vector
        {
            half4 tiny(1e-20f, 1e-20f, 1e-20f, 1e-20f);
            half4 normalized = normalize(tiny);

            // Should return zero vector because length is less than epsilon
            suite.assert_approximately_equal(float(normalized.x), 0.0f, "Normalize tiny vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.y), 0.0f, "Normalize tiny vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.z), 0.0f, "Normalize tiny vector z", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.w), 0.0f, "Normalize tiny vector w", HALF_EPSILON);
        }

        // Test smoothstep with edge0 = edge1
        {
            half4 v(0.5f, 1.5f, 2.5f, 0.0f);
            half4 result = smoothstep(half(1.0f), half(1.0f), v);
            // When edge0 = edge1, step(edge0) is used
            half4 step_result = step(half(1.0f), v);
            suite.assert_approximately_equal(float(result.x), float(step_result.x), "smoothstep() with equal edges x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), float(step_result.y), "smoothstep() with equal edges y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), float(step_result.z), "smoothstep() with equal edges z", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.w), float(step_result.w), "smoothstep() with equal edges w", HALF_EPSILON);
        }

        // Test dot product with itself
        {
            half4 v(3.0f, 4.0f, 5.0f, 6.0f);
            half dot_self = dot(v, v);
            half expected = length_sq(v);
            suite.assert_approximately_equal(float(dot_self), float(expected), "Dot product with self equals length squared", HALF_EPSILON);
        }

        // Test 3D dot product with itself
        {
            half4 v(3.0f, 4.0f, 5.0f, 6.0f);
            half dot3_self = dot3(v, v);
            half expected = v.x * v.x + v.y * v.y + v.z * v.z;
            suite.assert_approximately_equal(float(dot3_self), float(expected), "Dot3 product with self equals length3 squared", HALF_EPSILON);
        }

        // Test cross product with itself
        {
            half4 v(2.0f, 3.0f, 4.0f, 5.0f);
            half4 cross_self = cross(v, v);
            // Cross product of vector with itself = zero vector
            suite.assert_approximately_equal(float(cross_self.x), 0.0f, "Cross product with self x", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_self.y), 0.0f, "Cross product with self y", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_self.z), 0.0f, "Cross product with self z", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_self.w), 0.0f, "Cross product with self w", HALF_EPSILON);
        }

        // Test is_normalized for zero vector
        {
            half4 zero(0.0f, 0.0f, 0.0f, 0.0f);
            suite.assert_false(is_normalized(zero), "Zero vector is not normalized");
        }

        // Test with numbers close to maximum half value
        {
            half max_half = half::max_value();
            half4 max_vec(max_half, max_half, max_half, max_half);

            // Make sure values didn't become NaN or Inf
            suite.assert_true(max_vec.is_finite(), "Vector with max half values is finite");

            // Normalization of vector with maximum values
            half4 normalized = normalize(max_vec);
            float normalized_len = float(length(normalized));
            suite.assert_approximately_equal(normalized_len, 1.0f, "Normalize max values length", HALF_EPSILON);
        }

        // Test with denormalized numbers
        {
            half min_denorm = half::min_denormal_value();
            half4 denorm_vec(min_denorm, min_denorm, min_denorm, min_denorm);

            suite.assert_true(denorm_vec.is_finite(), "Vector with denormalized values is finite");

            // Multiplication of denormalized numbers
            half4 multiplied = denorm_vec * half(2.0f);
            suite.assert_true(multiplied.is_finite(), "Multiplication of denormalized values is finite");
        }

        // Test saturation with negative numbers
        {
            half4 v(-2.0f, 0.5f, 1.5f, 2.0f);
            half4 saturated = saturate(v);

            suite.assert_approximately_equal(float(saturated.x), 0.0f, "saturate() negative value", HALF_EPSILON);
            suite.assert_approximately_equal(float(saturated.y), 0.5f, "saturate() positive value < 1", HALF_EPSILON);
            suite.assert_approximately_equal(float(saturated.z), 1.0f, "saturate() positive value > 1", HALF_EPSILON);
            suite.assert_approximately_equal(float(saturated.w), 1.0f, "saturate() positive value > 1", HALF_EPSILON);
        }

        // Test rounding edge values
        {
            half4 v1(1.49f, 1.51f, -1.49f, -1.51f);
            half4 rounded1 = round(v1);
            suite.assert_approximately_equal(float(rounded1.x), 1.0f, "round() 1.49", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded1.y), 2.0f, "round() 1.51", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded1.z), -1.0f, "round() -1.49", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded1.w), -2.0f, "round() -1.51", HALF_EPSILON);

            half4 v2(-1.51f, 2.49f, 2.51f, -2.49f);
            half4 rounded2 = round(v2);
            suite.assert_approximately_equal(float(rounded2.x), -2.0f, "round() -1.51", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded2.y), 2.0f, "round() 2.49", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded2.z), 3.0f, "round() 2.51", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded2.w), -2.0f, "round() -2.49", HALF_EPSILON);
        }

        // Test floor/ceil edge values
        {
            half4 v(1.5f, -1.5f, 2.3f, -2.3f);

            half4 floored = floor(v);
            suite.assert_approximately_equal(float(floored.x), 1.0f, "floor() 1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(floored.y), -2.0f, "floor() -1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(floored.z), 2.0f, "floor() 2.3", HALF_EPSILON);
            suite.assert_approximately_equal(float(floored.w), -3.0f, "floor() -2.3", HALF_EPSILON);

            half4 ceiled = ceil(v);
            suite.assert_approximately_equal(float(ceiled.x), 2.0f, "ceil() 1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(ceiled.y), -1.0f, "ceil() -1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(ceiled.z), 3.0f, "ceil() 2.3", HALF_EPSILON);
            suite.assert_approximately_equal(float(ceiled.w), -2.0f, "ceil() -2.3", HALF_EPSILON);
        }

        // Test unpremultiply_alpha with alpha = 0
        {
            half4 color(0.5f, 0.3f, 0.2f, 0.0f);
            half4 unpremultiplied = unpremultiply_alpha(color);

            // With alpha = 0, should return original RGB values
            suite.assert_approximately_equal(float(unpremultiplied.x), 0.5f, "unpremultiply_alpha() with alpha=0 x", COLOR_EPSILON);
            suite.assert_approximately_equal(float(unpremultiplied.y), 0.3f, "unpremultiply_alpha() with alpha=0 y", COLOR_EPSILON);
            suite.assert_approximately_equal(float(unpremultiplied.z), 0.2f, "unpremultiply_alpha() with alpha=0 z", COLOR_EPSILON);
            suite.assert_approximately_equal(float(unpremultiplied.w), 0.0f, "unpremultiply_alpha() with alpha=0 w", COLOR_EPSILON);
        }

        // Test unpremultiply_alpha with very small alpha
        {
            half4 color(1e-7f, 1e-7f, 1e-7f, 1e-8f); // Very small values
            half4 unpremultiplied = unpremultiply_alpha(color);

            // Should correctly handle very small values without division by zero
            suite.assert_true(unpremultiplied.is_finite(), "unpremultiply_alpha() with tiny alpha returns finite values");
        }

        // Test projection with w = very small value
        {
            half4 v(2.0f, 4.0f, 6.0f, 1e-20f);
            half3 projected = project(v);

            // With very small w, should return zero vector
            suite.assert_approximately_equal(float(projected.x), 0.0f, "project() with tiny w x", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.y), 0.0f, "project() with tiny w y", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.z), 0.0f, "project() with tiny w z", HALF_EPSILON);
        }

        // Test cross product with zero components
        {
            half4 a(1.0f, 0.0f, 0.0f, 0.0f);
            half4 b(0.0f, 1.0f, 0.0f, 0.0f);
            half4 cross_result = cross(a, b);

            // (1,0,0) × (0,1,0) = (0,0,1)
            suite.assert_approximately_equal(float(cross_result.x), 0.0f, "cross() unit vectors x", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_result.y), 0.0f, "cross() unit vectors y", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_result.z), 1.0f, "cross() unit vectors z", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_result.w), 0.0f, "cross() unit vectors w", HALF_EPSILON);
        }

        // Test dot product with zero vector
        {
            half4 a(1.0f, 2.0f, 3.0f, 4.0f);
            half4 zero(0.0f, 0.0f, 0.0f, 0.0f);
            half dot_result = dot(a, zero);

            suite.assert_approximately_equal(float(dot_result), 0.0f, "dot() with zero vector", HALF_EPSILON);
        }

        // Test distance to itself
        {
            half4 v(1.0f, 2.0f, 3.0f, 4.0f);
            half dist_self = distance(v, v);

            suite.assert_approximately_equal(float(dist_self), 0.0f, "distance() to self", HALF_EPSILON);
        }

        // Test sRGB/linear conversion for edge values
        {
            // Value below threshold (0.04045)
            half4 srgb_low(0.02f, 0.02f, 0.02f, 1.0f);
            half4 linear_low = srgb_to_linear(srgb_low);
            // 0.02 <= 0.04045, so: 0.02/12.92 ≈ 0.001548
            float expected_low = 0.02f / 12.92f;
            suite.assert_approximately_equal(float(linear_low.x), expected_low, "srgb_to_linear() low value x", COLOR_EPSILON);

            // Value above threshold
            half4 srgb_high(0.8f, 0.8f, 0.8f, 1.0f);
            half4 linear_high = srgb_to_linear(srgb_high);
            // 0.8 > 0.04045, so: pow((0.8+0.055)/1.055, 2.4) ≈ pow(0.810, 2.4) ≈ 0.6038
            float expected_high = std::pow((0.8f + 0.055f) / 1.055f, 2.4f);
            suite.assert_approximately_equal(float(linear_high.x), expected_high, "srgb_to_linear() high value x", COLOR_EPSILON);
        }

        // Test linear/sRGB conversion for edge values
        {
            // Value below threshold (0.0031308)
            half4 linear_low(0.002f, 0.002f, 0.002f, 1.0f);
            half4 srgb_low = linear_to_srgb(linear_low);
            // 0.002 <= 0.0031308, so: 0.002 * 12.92 = 0.02584
            float expected_low = 0.002f * 12.92f;
            suite.assert_approximately_equal(float(srgb_low.x), expected_low, "linear_to_srgb() low value x", COLOR_EPSILON);

            // Value above threshold
            half4 linear_high(0.5f, 0.5f, 0.5f, 1.0f);
            half4 srgb_high = linear_to_srgb(linear_high);
            // 0.5 > 0.0031308, so: 1.055 * pow(0.5, 1/2.4) - 0.055 ≈ 1.055*0.735 - 0.055 ≈ 0.720
            float expected_high = 1.055f * std::pow(0.5f, 1.0f / 2.4f) - 0.055f;
            suite.assert_approximately_equal(float(srgb_high.x), expected_high, "linear_to_srgb() high value x", COLOR_EPSILON);
        }
    }
} // namespace AfterMathTests
