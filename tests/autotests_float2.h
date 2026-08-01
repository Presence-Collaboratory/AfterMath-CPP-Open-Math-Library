// Author: DeepSeek, NSDeathman
// Test suite for AfterMath::float2 class with HLSL-like syntax

#include "AutotestCore.h"

namespace AfterMathTests
{
    void RunFloat2Tests(TestSuite& suite)
    {
        using namespace AfterMath;

        const float PI = 3.14159265358979323846f;
        const float EPSILON = 1e-6f;

        // ============================================================================
        // 1. Constructors
        // ============================================================================
        suite.section("Constructors");

        // Default constructor test
        {
            float2 v;
            suite.assert_approximately_equal(v.x, 0.0f, "Default constructor x");
            suite.assert_approximately_equal(v.y, 0.0f, "Default constructor y");
        }

        // Component constructor test
        {
            float2 v(1.5f, 2.5f);
            suite.assert_approximately_equal(v.x, 1.5f, "Component constructor x");
            suite.assert_approximately_equal(v.y, 2.5f, "Component constructor y");
        }

        // Scalar constructor test
        {
            float2 v(3.0f);
            suite.assert_approximately_equal(v.x, 3.0f, "Scalar constructor x");
            suite.assert_approximately_equal(v.y, 3.0f, "Scalar constructor y");
        }

        // Array constructor test
        {
            float data[2] = { 4.0f, 5.0f };
            float2 v(data);
            suite.assert_approximately_equal(v.x, 4.0f, "Array constructor x");
            suite.assert_approximately_equal(v.y, 5.0f, "Array constructor y");
        }

        // Copy constructor test
        {
            float2 original(6.0f, 7.0f);
            float2 copy(original);
            suite.assert_approximately_equal(copy.x, 6.0f, "Copy constructor x");
            suite.assert_approximately_equal(copy.y, 7.0f, "Copy constructor y");
        }

        // Static constructors test
        {
            suite.assert_approximately_equal(float2::zero(), float2(0.0f, 0.0f), "zero()");
            suite.assert_approximately_equal(float2::one(), float2(1.0f, 1.0f), "one()");
            suite.assert_approximately_equal(float2::unit_x(), float2(1.0f, 0.0f), "unit_x()");
            suite.assert_approximately_equal(float2::unit_y(), float2(0.0f, 1.0f), "unit_y()");
        }

        // ============================================================================
        // 2. Assignment Operators
        // ============================================================================
        suite.section("Assignment Operators");

        // Scalar assignment test
        {
            float2 v;
            v = 2.5f;
            suite.assert_approximately_equal(v.x, 2.5f, "Scalar assignment x");
            suite.assert_approximately_equal(v.y, 2.5f, "Scalar assignment y");
        }

        // Compound assignment operators test
        {
            float2 v(1.0f, 2.0f);

            v += float2(3.0f, 4.0f);
            suite.assert_approximately_equal(v, float2(4.0f, 6.0f), "Operator +=");

            v -= float2(1.0f, 2.0f);
            suite.assert_approximately_equal(v, float2(3.0f, 4.0f), "Operator -=");

            v *= float2(2.0f, 3.0f);
            suite.assert_approximately_equal(v, float2(6.0f, 12.0f), "Operator *=");

            v /= float2(2.0f, 3.0f);
            suite.assert_approximately_equal(v, float2(3.0f, 4.0f), "Operator /=");

            v *= 2.0f;
            suite.assert_approximately_equal(v, float2(6.0f, 8.0f), "Operator *= scalar");

            v /= 2.0f;
            suite.assert_approximately_equal(v, float2(3.0f, 4.0f), "Operator /= scalar");
        }

        // ============================================================================
        // 3. Binary Operators
        // ============================================================================
        suite.section("Binary Operators");

        // Addition test
        {
            float2 a(1.0f, 2.0f);
            float2 b(3.0f, 4.0f);
            float2 result = a + b;
            suite.assert_approximately_equal(result, float2(4.0f, 6.0f), "Operator +");
        }

        // Subtraction test
        {
            float2 a(5.0f, 6.0f);
            float2 b(2.0f, 3.0f);
            float2 result = a - b;
            suite.assert_approximately_equal(result, float2(3.0f, 3.0f), "Operator -");
        }

        // Unary operators test
        {
            float2 a(1.0f, 2.0f);
            suite.assert_approximately_equal(+a, float2(1.0f, 2.0f), "Unary +");
            suite.assert_approximately_equal(-a, float2(-1.0f, -2.0f), "Unary -");
        }

        // Scalar operations test
        {
            float2 v(2.0f, 3.0f);

            float2 result1 = v + 1.0f;
            suite.assert_approximately_equal(result1, float2(3.0f, 4.0f), "Vector + scalar");

            float2 result2 = v - 1.0f;
            suite.assert_approximately_equal(result2, float2(1.0f, 2.0f), "Vector - scalar");

            float2 result3 = v * 2.0f;
            suite.assert_approximately_equal(result3, float2(4.0f, 6.0f), "Vector * scalar");

            float2 result4 = 2.0f * v;
            suite.assert_approximately_equal(result4, float2(4.0f, 6.0f), "Scalar * vector");

            float2 result5 = v / 2.0f;
            suite.assert_approximately_equal(result5, float2(1.0f, 1.5f), "Vector / scalar");

            float2 result6 = 2.0f + v;
            suite.assert_approximately_equal(result6, float2(4.0f, 5.0f), "Scalar + vector");
        }

        // ============================================================================
        // 4. Access and Conversion Operators
        // ============================================================================
        suite.section("Access and Conversion Operators");

        // Indexing operator test
        {
            float2 v(7.0f, 8.0f);
            suite.assert_approximately_equal(v[0], 7.0f, "Operator [] index 0");
            suite.assert_approximately_equal(v[1], 8.0f, "Operator [] index 1");

            v[0] = 9.0f;
            v[1] = 10.0f;
            suite.assert_approximately_equal(v.x, 9.0f, "Operator [] mutable x");
            suite.assert_approximately_equal(v.y, 10.0f, "Operator [] mutable y");
        }

        // Pointer conversion test
        {
            float2 v(1.0f, 2.0f);
            const float* ptr = v;
            suite.assert_approximately_equal(ptr[0], 1.0f, "Conversion to const float* index 0");
            suite.assert_approximately_equal(ptr[1], 2.0f, "Conversion to const float* index 1");

            float* mutable_ptr = v;
            mutable_ptr[0] = 3.0f;
            suite.assert_approximately_equal(v.x, 3.0f, "Conversion to float* mutable");
        }

        // ============================================================================
        // 5. Global Mathematical Functions (HLSL Style)
        // ============================================================================
        suite.section("Global Mathematical Functions (HLSL Style)");

        // Length functions test
        {
            float2 v(3.0f, 4.0f);
            suite.assert_approximately_equal(length(v), 5.0f, "length()");
            suite.assert_approximately_equal(length_sq(v), 25.0f, "length_sq()");

            float2 zero(0.0f, 0.0f);
            suite.assert_approximately_equal(length(zero), 0.0f, "length() of zero vector");
        }

        // Normalization test
        {
            float2 v(3.0f, 4.0f);
            float2 normalized = normalize(v);
            float expected_len = 1.0f;
            suite.assert_approximately_equal(length(normalized), expected_len, "normalize() length");
            suite.assert_approximately_equal(normalized.x, 0.6f, "normalize() x");
            suite.assert_approximately_equal(normalized.y, 0.8f, "normalize() y");

            // Zero vector normalization test
            float2 zero(0.0f, 0.0f);
            float2 zero_norm = normalize(zero);
            suite.assert_approximately_equal(zero_norm, float2::zero(), "normalize() zero vector");
        }

        // Dot product test
        {
            float2 a(1.0f, 2.0f);
            float2 b(3.0f, 4.0f);
            float dot_result = dot(a, b);
            suite.assert_approximately_equal(dot_result, 11.0f, "dot()");

            // Orthogonal vectors
            float2 orth1(1.0f, 0.0f);
            float2 orth2(0.0f, 1.0f);
            suite.assert_approximately_equal(dot(orth1, orth2), 0.0f, "dot() orthogonal vectors");
        }

        // Cross product test (2D)
        {
            float2 a(1.0f, 2.0f);
            float2 b(3.0f, 4.0f);
            float cross_result = cross(a, b);
            suite.assert_approximately_equal(cross_result, -2.0f, "cross()");
        }

        // Distance functions test
        {
            float2 a(1.0f, 2.0f);
            float2 b(4.0f, 6.0f);
            float dist = distance(a, b);
            float dist_sq = distance_sq(a, b);

            // (4-1)² + (6-2)² = 9 + 16 = 25
            suite.assert_approximately_equal(dist, 5.0f, "distance()");
            suite.assert_approximately_equal(dist_sq, 25.0f, "distance_sq()");
        }

        // ============================================================================
        // 6. HLSL-like Functions
        // ============================================================================
        suite.section("HLSL-like Functions");

        // abs test
        {
            float2 v(-1.5f, 2.5f);
            float2 result = abs(v);
            suite.assert_approximately_equal(result, float2(1.5f, 2.5f), "abs()");
        }

        // sign test
        {
            float2 v(-2.0f, 3.0f);
            float2 result = sign(v);
            suite.assert_approximately_equal(result, float2(-1.0f, 1.0f), "sign() positive/negative");

            float2 zero_mixed(0.0f, -0.0f);
            float2 sign_zero = sign(zero_mixed);
            suite.assert_approximately_equal(sign_zero, float2(0.0f, 0.0f), "sign() zero");
        }

        // floor test
        {
            float2 v(1.7f, -2.3f);
            float2 result = floor(v);
            suite.assert_approximately_equal(result, float2(1.0f, -3.0f), "floor()");
        }

        // ceil test
        {
            float2 v(1.2f, -2.7f);
            float2 result = ceil(v);
            suite.assert_approximately_equal(result, float2(2.0f, -2.0f), "ceil()");
        }

        // round test
        {
            float2 v(1.4f, 1.6f);
            float2 result = round(v);
            suite.assert_approximately_equal(result, float2(1.0f, 2.0f), "round()");
        }

        // frac test
        {
            float2 v(1.7f, -2.3f);
            float2 result = frac(v);
            suite.assert_approximately_equal(result.x, 0.7f, "frac() x", 1e-6f);
            suite.assert_approximately_equal(result.y, 0.7f, "frac() y", 1e-6f); // -2.3 - (-3) = 0.7
        }

        // saturate test
        {
            float2 v(-0.5f, 1.5f);
            float2 result = saturate(v);
            suite.assert_approximately_equal(result, float2(0.0f, 1.0f), "saturate()");
        }

        // step test
        {
            float2 v(0.5f, 1.5f);
            float2 result = step(1.0f, v);
            suite.assert_approximately_equal(result, float2(0.0f, 1.0f), "step()");
        }

        // smoothstep test
        {
            float2 v(0.5f, 1.5f);
            float2 result = smoothstep(0.0f, 2.0f, v);
            // For t=0.25: 3t² - 2t³ = 3*0.0625 - 2*0.015625 = 0.1875 - 0.03125 = 0.15625
            // For t=0.75: 3*0.5625 - 2*0.421875 = 1.6875 - 0.84375 = 0.84375
            suite.assert_approximately_equal(result.x, 0.15625f, "smoothstep() x", 1e-6f);
            suite.assert_approximately_equal(result.y, 0.84375f, "smoothstep() y", 1e-6f);
        }

        // ============================================================================
        // 7. Geometric Operations
        // ============================================================================
        suite.section("Geometric Operations");

        // Perpendicular test
        {
            float2 v(2.0f, 3.0f);
            float2 perp = perpendicular(v);
            suite.assert_approximately_equal(perp, float2(-3.0f, 2.0f), "perpendicular()");
        }

        // Reflection test
        {
            float2 incident(1.0f, -1.0f);
            float2 normal(0.0f, 1.0f); // Upward normal
            float2 reflected = reflect(incident, normalize(normal));
            // R = I - 2*(I·N)*N = (1,-1) - 2*(-1)*(0,1) = (1,-1) + (0,2) = (1,1)
            suite.assert_approximately_equal(reflected, float2(1.0f, 1.0f), "reflect()");
        }

        // Refraction test
        {
            float2 incident(1.0f, -1.0f);
            float2 normal(0.0f, 1.0f);
            normal = normalize(normal);

            // For eta = 1.0 (same medium) - vector should remain unchanged
            float2 refracted = refract(incident, normal, 1.0f);
            suite.assert_approximately_equal(refracted, incident, "refract() with eta=1.0");

            // For eta = 0.5 - calculate expected result
            // incident = (1, -1), normal = (0, 1), eta = 0.5
            // d = dot(incident, normal) = -1
            // k = 1 - eta² * (1 - d²) = 1 - 0.25 * (1 - 1) = 1
            // refracted = eta * incident - (eta * d + sqrt(k)) * normal
            // = 0.5 * (1, -1) - (0.5 * (-1) + 1) * (0, 1)
            // = (0.5, -0.5) - (0.5) * (0, 1)
            // = (0.5, -1.0)
            float2 refracted2 = refract(incident, normal, 0.5f);
            float2 expected2(0.5f, -1.0f);
            suite.assert_approximately_equal(refracted2, expected2, "refract() with eta=0.5");

            // Test total internal reflection: WATER→AIR
            // n1 = 1.33 (water), n2 = 1.0 (air), eta = n2/n1 = 1.0/1.33 approx 0.7519
            // Critical angle: θ_c = arcsin(eta) = arcsin(0.7519) approx 48.8°
            // Take incident angle 60° > 48.8° - should result in total internal reflection

            float angle = PI / 3.0f; // 60°
            float2 incident_large_angle(std::sin(angle), -std::cos(angle));

            float eta_water_to_air = 1.33f;
            float2 total_reflection = refract(incident_large_angle, normal, eta_water_to_air);

            // Should return zero vector for total internal reflection
            suite.assert_approximately_equal(total_reflection, float2::zero(),
                "refract() total internal reflection for 60° angle, water->air");
        }

        // Rotation test
        {
            float2 v(1.0f, 0.0f);
            float angle = PI / 2.0f; // 90 degrees
            float2 rotated = rotate(v, angle);
            suite.assert_approximately_equal(rotated.x, 0.0f, "rotate() 90° x", 1e-6f);
            suite.assert_approximately_equal(rotated.y, 1.0f, "rotate() 90° y", 1e-6f);

            // 180 degrees
            float2 rotated180 = rotate(v, PI);
            suite.assert_approximately_equal(rotated180.x, -1.0f, "rotate() 180° x", 1e-6f);
            suite.assert_approximately_equal(rotated180.y, 0.0f, "rotate() 180° y", 1e-6f);
        }

        // Angle test
        {
            float2 v(1.0f, 0.0f);
            float ang = angle(v);
            suite.assert_approximately_equal(ang, 0.0f, "angle() for (1,0)");

            float2 v2(0.0f, 1.0f);
            float angle2 = angle(v2);
            suite.assert_approximately_equal(angle2, PI / 2.0f, "angle() for (0,1)");

            float2 v3(-1.0f, 0.0f);
            float angle3 = angle(v3);
            suite.assert_approximately_equal(angle3, PI, "angle() for (-1,0)", 1e-6f);
        }

        // ============================================================================
        // 8. Swizzle Operations
        // ============================================================================
        suite.section("Swizzle Operations");

        {
            float2 v(2.0f, 3.0f);

            suite.assert_approximately_equal(v.yx(), float2(3.0f, 2.0f), "yx()");
            suite.assert_approximately_equal(v.xx(), float2(2.0f, 2.0f), "xx()");
            suite.assert_approximately_equal(v.yy(), float2(3.0f, 3.0f), "yy()");
        }

        // ============================================================================
        // 9. Utility Functions
        // ============================================================================
        suite.section("Utility Functions");

        // isValid test
        {
            float2 valid(1.0f, 2.0f);
            suite.assert_true(isValid(valid), "isValid() for valid vector");

            // Note: For NaN and INF tests, special construction is required
            suite.skip_test("isValid() with NaN/INF", "Requires special NaN/INF construction");
        }

        // approximately test
        {
            float2 a(1.0f, 2.0f);
            float2 b(1.000001f, 2.000001f);
            float2 c(1.1f, 2.1f);

            suite.assert_true(approximately(a, b, 1e-5f), "approximately() within epsilon");
            suite.assert_false(approximately(a, c, 1e-5f), "approximately() outside epsilon");
        }

        // approximately_zero test (using length_sq)
        {
            float2 zero(0.0f, 0.0f);
            float2 near_zero(0.000001f, 0.000001f);
            float2 not_zero(0.1f, 0.1f);

            suite.assert_true(zero.length_sq() <= EPSILON * EPSILON, "approximately_zero() for zero");
            suite.assert_true(near_zero.length_sq() <= 1e-4f * 1e-4f, "approximately_zero() for near zero");
            suite.assert_false(not_zero.length_sq() <= EPSILON * EPSILON, "approximately_zero() for non-zero");
        }

        // is_normalized test (using length_sq)
        {
            float2 normalized(0.6f, 0.8f);
            float2 not_normalized(1.0f, 2.0f);

            suite.assert_true(std::abs(length_sq(normalized) - 1.0f) <= EPSILON, "is_normalized() for normalized vector");
            suite.assert_false(std::abs(length_sq(not_normalized) - 1.0f) <= EPSILON, "is_normalized() for non-normalized");
        }

        // to_string test
        {
            float2 v(1.5f, 2.5f);
            std::string str = v.to_string();

            // Check for expected values in string
            suite.assert_true(str.find("1.5") != std::string::npos || str.find("1.500") != std::string::npos,
                "to_string() contains x value");
            suite.assert_true(str.find("2.5") != std::string::npos || str.find("2.500") != std::string::npos,
                "to_string() contains y value");
        }

        // data() test
        {
            float2 v(7.0f, 8.0f);
            const float* cdata = v.data();
            float* data = v.data();

            suite.assert_approximately_equal(cdata[0], 7.0f, "data() const access x");
            suite.assert_approximately_equal(cdata[1], 8.0f, "data() const access y");

            data[0] = 9.0f;
            suite.assert_approximately_equal(v.x, 9.0f, "data() mutable modification");
        }

        // ============================================================================
        // 10. Comparison Operators
        // ============================================================================
        suite.section("Comparison Operators");

        {
            float2 a(1.0f, 2.0f);
            float2 b(1.0f, 2.0f);
            float2 c(1.1f, 2.1f);

            suite.assert_true(a == b, "Operator == for equal vectors");
            suite.assert_false(a == c, "Operator == for different vectors");
            suite.assert_false(a != b, "Operator != for equal vectors");
            suite.assert_true(a != c, "Operator != for different vectors");
        }

        // ============================================================================
        // 11. Global Operators
        // ============================================================================
        suite.section("Global Operators");

        // Multiplication and division of vectors test
        {
            float2 a(2.0f, 3.0f);
            float2 b(4.0f, 5.0f);

            float2 mul_result = a * b;
            suite.assert_approximately_equal(mul_result, float2(8.0f, 15.0f), "Global operator *");

            float2 div_result = a / b;
            suite.assert_approximately_equal(div_result, float2(0.5f, 0.6f), "Global operator /");
        }

        // ============================================================================
        // 12. Global Mathematical Functions
        // ============================================================================
        suite.section("Global Mathematical Functions");

        // distance and distance_sq test (already tested in section 5)

        // dot and cross test (already tested in section 5)

        // approximately global test (already tested in section 9)

        // isValid global test (already tested in section 9)

        // Linear interpolation test
        {
            float2 a(0.0f, 0.0f);
            float2 b(10.0f, 20.0f);

            float2 lerp_result = lerp(a, b, 0.5f);
            suite.assert_approximately_equal(lerp_result, float2(5.0f, 10.0f), "Global lerp() at 0.5");

            float2 lerp_start = lerp(a, b, 0.0f);
            suite.assert_approximately_equal(lerp_start, a, "Global lerp() at 0.0");

            float2 lerp_end = lerp(a, b, 1.0f);
            suite.assert_approximately_equal(lerp_end, b, "Global lerp() at 1.0");
        }

        // Spherical linear interpolation test
        {
            float2 a(1.0f, 0.0f);
            float2 b(0.0f, 1.0f);

            a = normalize(a);
            b = normalize(b);

            float2 slerp_result = slerp(a, b, 0.5f);
            float expected_length = 1.0f;
            suite.assert_approximately_equal(length(slerp_result), expected_length, "Global slerp() length");

            // Midway between (1,0) and (0,1) should be approximately (√2/2, √2/2)
            float expected_val = std::sqrt(2.0f) / 2.0f;
            suite.assert_approximately_equal(slerp_result.x, expected_val, "Global slerp() x at 0.5", 1e-6f);
            suite.assert_approximately_equal(slerp_result.y, expected_val, "Global slerp() y at 0.5", 1e-6f);
        }

        // angle_between test
        {
            float2 a(1.0f, 0.0f);
            float2 b(0.0f, 1.0f);
            float2 c(-1.0f, 0.0f);

            float angle_ab = angle_between(a, b);
            suite.assert_approximately_equal(angle_ab, PI / 2.0f,
                "Global angle_between() 90 degrees");

            float angle_ac = angle_between(a, c);
            suite.assert_approximately_equal(angle_ac, PI,
                "Global angle_between() 180 degrees", 1e-6f);
        }

        // signed_angle_between test
        {
            float2 a(1.0f, 0.0f);
            float2 b(0.0f, 1.0f);
            float2 c(0.0f, -1.0f);

            float angle_ab = signed_angle_between(a, b);
            float angle_ac = signed_angle_between(a, c);

            suite.assert_approximately_equal(angle_ab, PI / 2.0f,
                "Global signed_angle_between() positive 90");
            suite.assert_approximately_equal(angle_ac, -PI / 2.0f,
                "Global signed_angle_between() negative 90", 1e-6f);
        }

        // Projection test
        {
            float2 v(2.0f, 3.0f);
            float2 onto(1.0f, 0.0f); // X axis

            float2 projected = project(v, onto);
            suite.assert_approximately_equal(projected, float2(2.0f, 0.0f), "Global project() onto X axis");

            // Projection onto itself should return itself
            float2 self_projected = project(v, v);
            suite.assert_approximately_equal(self_projected, v, "Global project() onto itself");
        }

        // Rejection test
        {
            float2 v(2.0f, 3.0f);
            float2 onto(1.0f, 0.0f); // X axis

            float2 rejected = reject(v, onto);
            // v = (2,3), projection on X = (2,0), rejection = (0,3)
            suite.assert_approximately_equal(rejected, float2(0.0f, 3.0f), "Global reject() from X axis");

            // Rejection from itself should give 0
            float2 self_rejected = reject(v, v);
            suite.assert_approximately_equal(self_rejected, float2::zero(), "Global reject() from itself");
        }

        // ============================================================================
        // 13. Global HLSL Functions
        // ============================================================================
        suite.section("Global HLSL Functions");

        {
            float2 v(-1.5f, 2.5f);

            suite.assert_approximately_equal(abs(v), float2(1.5f, 2.5f), "Global abs()");
            suite.assert_approximately_equal(sign(v), float2(-1.0f, 1.0f), "Global sign()");
            suite.assert_approximately_equal(floor(v), float2(-2.0f, 2.0f), "Global floor()");
            suite.assert_approximately_equal(ceil(v), float2(-1.0f, 3.0f), "Global ceil()");
            suite.assert_approximately_equal(round(float2(1.4f, 1.6f)), float2(1.0f, 2.0f), "Global round()");
            suite.assert_approximately_equal(saturate(float2(-0.5f, 1.5f)), float2(0.0f, 1.0f), "Global saturate()");
        }

        // clamp, min, max test
        {
            float2 v(0.5f, 1.5f);
            float2 min_val(0.0f, 0.0f);
            float2 max_val(1.0f, 1.0f);

            float2 clamped = clamp(v, min_val, max_val);
            suite.assert_approximately_equal(clamped, float2(0.5f, 1.0f), "Global clamp()");

            float2 a(1.0f, 3.0f);
            float2 b(2.0f, 2.0f);

            float2 min_result = min(a, b);
            suite.assert_approximately_equal(min_result, float2(1.0f, 2.0f), "Global min()");

            float2 max_result = max(a, b);
            suite.assert_approximately_equal(max_result, float2(2.0f, 3.0f), "Global max()");
        }

        // ============================================================================
        // 14. Utility Global Functions
        // ============================================================================
        suite.section("Utility Global Functions");

        // distance_to_line_segment test
        {
            float2 point(0.0f, 0.0f);
            float2 line_start(1.0f, 0.0f);
            float2 line_end(3.0f, 0.0f);

            float dist = distance_to_line_segment(point, line_start, line_end);
            // Distance from (0,0) to segment [(1,0),(3,0)] = 1.0
            suite.assert_approximately_equal(dist, 1.0f, "distance_to_line_segment() to horizontal line");

            // Point inside segment projection
            float2 point2(2.0f, 2.0f);
            float dist2 = distance_to_line_segment(point2, line_start, line_end);
            // Distance from (2,2) to horizontal line at y=0 = 2.0
            suite.assert_approximately_equal(dist2, 2.0f, "distance_to_line_segment() perpendicular to middle");

            // Point closer to start of segment
            float2 point3(0.0f, 2.0f);
            float dist3 = distance_to_line_segment(point3, line_start, line_end);
            // Distance to start point (1,0): √((0-1)² + (2-0)²) = √(1 + 4) = √5 approx 2.236
            suite.assert_approximately_equal(dist3, std::sqrt(5.0f), "distance_to_line_segment() closest to start");
        }

        // ============================================================================
        // 15. Edge Cases
        // ============================================================================
        suite.section("Edge Cases");

        // Very small values test
        {
            float epsilon = 1e-30f;
            float2 tiny(epsilon, epsilon);
            suite.assert_true(tiny.length_sq() <= 1e-20f * 1e-20f, "Tiny values approximately_zero");
        }

        // Very large values test
        {
            float large = 1e10f;
            float2 huge(large, large);
            suite.assert_false(huge.length_sq() <= EPSILON * EPSILON, "Huge values not approximately_zero");

            float2 normalized_huge = normalize(huge);
            float expected_length = 1.0f;
            suite.assert_approximately_equal(length(normalized_huge), expected_length,
                "Normalize huge values", 1e-6f);
        }

        // Division by zero (vector)
        {
            float2 a(1.0f, 2.0f);
            float2 zero_vec(0.0f, 0.0f);

            // Should cause division by zero, but we'll check what happens
            // In C++ float division by zero gives inf or NaN
            float2 result = a / zero_vec;

            // Check that result contains infinities or NaN
            suite.assert_true(!std::isfinite(result.x) || !std::isfinite(result.y),
                "Division by zero vector produces non-finite values");
        }

        // Division by zero (scalar)
        {
            float2 v(1.0f, 2.0f);
            float2 result = v / 0.0f;

            suite.assert_true(!std::isfinite(result.x) && !std::isfinite(result.y),
                "Division by zero scalar produces non-finite values");
        }

        // Normalization of very small vector
        {
            float2 tiny(1e-20f, 1e-20f);
            float2 normalized = normalize(tiny);

            // Should return zero vector since length is less than epsilon
            suite.assert_approximately_equal(normalized, float2::zero(),
                "Normalize tiny vector returns zero");
        }

        // smoothstep with edge0 = edge1
        {
            float2 v(0.5f, 1.5f);
            float2 result = smoothstep(1.0f, 1.0f, v);
            // When edge0 = edge1, step(edge0) is used
            suite.assert_approximately_equal(result, step(1.0f, v), "smoothstep() with equal edges");
        }

        // Rotation of zero vector
        {
            float2 zero(0.0f, 0.0f);
            float2 rotated = rotate(zero, 1.0f);
            suite.assert_approximately_equal(rotated, zero, "Rotate zero vector");
        }

        // Reflection from zero normal
        {
            float2 v(1.0f, 2.0f);
            float2 zero_normal(0.0f, 0.0f);

            // Normal should be normalized, but zero vector cannot be normalized
            // In code we use dot(normal), where normal is a parameter
            // Check what happens when called with unnormalized zero vector
            float2 reflected = reflect(v, zero_normal);
            // R = I - 2*(I·N)*N = I - 0 = I
            suite.assert_approximately_equal(reflected, v, "Reflect with zero normal returns original");
        }

        // Dot product with itself
        {
            float2 v(3.0f, 4.0f);
            float dot_self = dot(v, v);
            float expected = length_sq(v);
            suite.assert_approximately_equal(dot_self, expected, "Dot product with self equals length squared");
        }

        // Cross product with itself
        {
            float2 v(2.0f, 3.0f);
            float cross_self = cross(v, v);
            suite.assert_approximately_equal(cross_self, 0.0f, "Cross product with self equals zero");
        }

        // Angle of zero vector
        {
            float2 zero(0.0f, 0.0f);
            float ang = angle(zero);
            // Angle of zero vector is undefined, but atan2(0,0) usually returns 0
            suite.assert_approximately_equal(ang, 0.0f, "Angle of zero vector");
        }

        // is_normalized for zero vector
        {
            float2 zero(0.0f, 0.0f);
            suite.assert_false(std::abs(length_sq(zero) - 1.0f) <= EPSILON, "Zero vector is not normalized");
        }
    }
}
