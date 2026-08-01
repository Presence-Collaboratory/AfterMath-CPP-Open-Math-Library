// autotests_quaternion.h
// Unit tests for quaternion class with HLSL-style global functions

#include "AutotestCore.h"

namespace AfterMathTests
{
    void RunQuaternionTests(TestSuite& suite)
    {
        using namespace AfterMath;

        // ============================================================================
        // 1. Constructors and Factory Methods
        // ============================================================================
        suite.section("Constructors and Factory Methods");

        // Default constructor (identity quaternion)
        suite.assert_approximately_equal(
            quaternion_to_matrix3x3(quaternion()),
            float3x3::identity(),
            "Default constructor creates identity"
        );

        // Component constructor
        suite.assert_equal(quaternion(1, 2, 3, 4).x, 1.0f, "Component constructor x");
        suite.assert_equal(quaternion(1, 2, 3, 4).y, 2.0f, "Component constructor y");
        suite.assert_equal(quaternion(1, 2, 3, 4).z, 3.0f, "Component constructor z");
        suite.assert_equal(quaternion(1, 2, 3, 4).w, 4.0f, "Component constructor w");

        // Axis-angle constructor
        {
            quaternion q = quaternion_axis_angle(float3::unit_x(), Constants::PI);
            float3 axis;
            float angle;
            quaternion_to_axis_angle(q, axis, angle);
            suite.assert_approximately_equal(axis, float3::unit_x(), "Axis-angle constructor axis");
            suite.assert_approximately_equal(angle, Constants::PI, "Axis-angle constructor angle");
        }

        // Euler angles constructor (Yaw-Pitch-Roll)
        {
            quaternion q = quaternion_euler(0.3f, 0.5f, 0.2f); // Yaw, Pitch, Roll
            float3 euler = quaternion_to_euler(q);
            suite.assert_approximately_equal(euler.x, 0.3f, "Euler constructor yaw", 1e-4f);
            suite.assert_approximately_equal(euler.y, 0.5f, "Euler constructor pitch", 1e-4f);
            suite.assert_approximately_equal(euler.z, 0.2f, "Euler constructor roll", 1e-4f);
        }

        // Matrix constructor
        {
            float3x3 rot = float3x3::rotation_x(Constants::HALF_PI);
            quaternion q = quaternion_from_matrix(rot);
            suite.assert_approximately_equal(quaternion_to_matrix3x3(q), rot, "Matrix constructor consistency", 1e-5f);
        }

        // Factory methods
        suite.assert_equal(identity_quaternion(), quaternion(0, 0, 0, 1), "Identity factory method");
        suite.assert_equal(zero_quaternion(), quaternion(0, 0, 0, 0), "Zero factory method");
        suite.assert_equal(quaternion_One, quaternion(1, 1, 1, 1), "One factory method");

        // Static rotation methods
        {
            quaternion rx = quaternion_rotation_x(Constants::HALF_PI);
            quaternion rx_axis = quaternion_axis_angle(float3::unit_x(), Constants::HALF_PI);
            suite.assert_approximately_equal(rx, rx_axis, "rotation_x method");
        }

        {
            quaternion ry = quaternion_rotation_y(Constants::HALF_PI);
            quaternion ry_axis = quaternion_axis_angle(float3::unit_y(), Constants::HALF_PI);
            suite.assert_approximately_equal(ry, ry_axis, "rotation_y method");
        }

        {
            quaternion rz = quaternion_rotation_z(Constants::HALF_PI);
            quaternion rz_axis = quaternion_axis_angle(float3::unit_z(), Constants::HALF_PI);
            suite.assert_approximately_equal(rz, rz_axis, "rotation_z method");
        }

        // ============================================================================
        // 2. Basic Operations
        // ============================================================================
        suite.section("Basic Operations");

        // Addition
        {
            quaternion a(1, 2, 3, 4);
            quaternion b(5, 6, 7, 8);
            quaternion c = a + b;
            suite.assert_equal(c.x, 6.0f, "Addition x");
            suite.assert_equal(c.y, 8.0f, "Addition y");
            suite.assert_equal(c.z, 10.0f, "Addition z");
            suite.assert_equal(c.w, 12.0f, "Addition w");
        }

        // Subtraction
        {
            quaternion a(5, 6, 7, 8);
            quaternion b(1, 2, 3, 4);
            quaternion c = a - b;
            suite.assert_equal(c.x, 4.0f, "Subtraction x");
            suite.assert_equal(c.y, 4.0f, "Subtraction y");
            suite.assert_equal(c.z, 4.0f, "Subtraction z");
            suite.assert_equal(c.w, 4.0f, "Subtraction w");
        }

        // Scalar multiplication
        {
            quaternion a(1, 2, 3, 4);
            quaternion b = a * 2.0f;
            suite.assert_equal(b.x, 2.0f, "Scalar multiplication x");
            suite.assert_equal(b.y, 4.0f, "Scalar multiplication y");
            suite.assert_equal(b.z, 6.0f, "Scalar multiplication z");
            suite.assert_equal(b.w, 8.0f, "Scalar multiplication w");
        }

        // Scalar division
        {
            quaternion a(2, 4, 6, 8);
            quaternion b = a / 2.0f;
            suite.assert_equal(b.x, 1.0f, "Scalar division x");
            suite.assert_equal(b.y, 2.0f, "Scalar division y");
            suite.assert_equal(b.z, 3.0f, "Scalar division z");
            suite.assert_equal(b.w, 4.0f, "Scalar division w");
        }

        // Negation
        {
            quaternion a(1, 2, 3, 4);
            quaternion b = -a;
            suite.assert_equal(b.x, -1.0f, "Negation x");
            suite.assert_equal(b.y, -2.0f, "Negation y");
            suite.assert_equal(b.z, -3.0f, "Negation z");
            suite.assert_equal(b.w, -4.0f, "Negation w");
        }

        // ============================================================================
        // 3. Quaternion Multiplication
        // ============================================================================
        suite.section("Quaternion Multiplication");

        // Multiplication with identity quaternion
        {
            quaternion q(1, 2, 3, 4);
            quaternion identity = identity_quaternion();
            suite.assert_approximately_equal(q * identity, q, "Multiplication with identity (right)");
            suite.assert_approximately_equal(identity * q, q, "Multiplication with identity (left)");
        }

        // Multiplication associativity
        {
            quaternion rx = quaternion_rotation_x(Constants::PI / 4);
            quaternion ry = quaternion_rotation_y(Constants::PI / 4);
            quaternion rz = quaternion_rotation_z(Constants::PI / 4);

            quaternion a = (rx * ry) * rz;
            quaternion b = rx * (ry * rz);
            suite.assert_approximately_equal(a, b, "Multiplication associativity", 1e-5f);
        }

        // Multiplication with inverse
        {
            quaternion q(1, 2, 3, 4);
            q = normalize(q);
            quaternion inv = inverse(q);
            suite.assert_approximately_equal(q * inv, identity_quaternion(), "Quaternion * inverse = identity", 1e-5f);
        }

        // ============================================================================
        // 4. Normalization and Length
        // ============================================================================
        suite.section("Normalization and Length");

        // Normalization
        {
            quaternion q(1, 2, 3, 4);
            quaternion n = normalize(q);
            suite.assert_approximately_equal(length(n), 1.0f, "Normalized length = 1", 1e-6f);
            suite.assert_true(is_normalized(n), "is_normalized() returns true for normalized quaternion");
        }

        // Length and squared length
        {
            quaternion q(3, 0, 4, 0);
            suite.assert_approximately_equal(length_sq(q), 25.0f, "Length squared");
            suite.assert_approximately_equal(length(q), 5.0f, "Length");
        }

        // Fast normalization
        {
            quaternion q(1, 2, 3, 4);
            quaternion n1 = normalize(q);
            quaternion n2 = fast_normalize(q);
            suite.assert_approximately_equal(n1, n2, "Fast normalization vs regular", 1e-3f);
        }

        // ============================================================================
        // 5. Conjugate and Inverse
        // ============================================================================
        suite.section("Conjugate and Inverse");

        // Conjugate
        {
            quaternion q(1, 2, 3, 4);
            quaternion conj = conjugate(q);
            suite.assert_equal(conj.x, -1.0f, "Conjugate x");
            suite.assert_equal(conj.y, -2.0f, "Conjugate y");
            suite.assert_equal(conj.z, -3.0f, "Conjugate z");
            suite.assert_equal(conj.w, 4.0f, "Conjugate w");
        }

        // Inverse of unit quaternion
        {
            quaternion q = normalize(quaternion(1, 2, 3, 4));
            quaternion inv = inverse(q);
            suite.assert_approximately_equal(inv, conjugate(q), "Inverse = conjugate for unit quaternion");
        }

        // ============================================================================
        // 6. Vector Transformation
        // ============================================================================
        suite.section("Vector Transformation");

        // Rotation by identity quaternion
        {
            float3 v(1, 2, 3);
            quaternion q = identity_quaternion();
            float3 rotated = q * v;
            suite.assert_approximately_equal(rotated, v, "Identity rotation leaves vector unchanged");
        }

        // 90 degree rotation around X axis
        {
            float3 v(0, 1, 0);
            quaternion q = quaternion_rotation_x(Constants::HALF_PI);
            float3 rotated = q * v;
            suite.assert_approximately_equal(rotated, float3(0, 0, 1), "90° X rotation", 1e-5f);
        }

        // 90 degree rotation around Y axis
        {
            float3 v(1, 0, 0);
            quaternion q = quaternion_rotation_y(Constants::HALF_PI);
            float3 rotated = q * v;
            suite.assert_approximately_equal(rotated, float3(0, 0, -1), "90° Y rotation", 1e-5f);
        }

        // 90 degree rotation around Z axis
        {
            float3 v(1, 0, 0);
            quaternion q = quaternion_rotation_z(Constants::HALF_PI);
            float3 rotated = q * v;
            suite.assert_approximately_equal(rotated, float3(0, 1, 0), "90° Z rotation", 1e-5f);
        }

        // Direction transformation
        {
            float3 dir = normalize(float3(1, 2, 3));
            quaternion q = quaternion_rotation_x(Constants::PI / 3);
            float3 transformed = transform_direction(q, dir);
            suite.assert_approximately_equal(length(transformed), 1.0f, "transform_direction preserves length", 1e-5f);
        }

        // ============================================================================
        // 7. Matrix Conversions
        // ============================================================================
        suite.section("Matrix Conversions");

        // Quaternion -> 3x3 matrix -> quaternion
        {
            quaternion q = normalize(quaternion(1, 2, 3, 4));
            float3x3 m = quaternion_to_matrix3x3(q);
            quaternion q2 = quaternion_from_matrix(m);
            // q and q2 may differ in sign (double cover)
            suite.assert_true(approximately(q, q2) || approximately(q, -q2),
                "Quaternion -> matrix3x3 -> quaternion round trip");
        }

        // Quaternion -> 4x4 matrix -> quaternion
        {
            quaternion q = normalize(quaternion(1, 2, 3, 4));
            float4x4 m = quaternion_to_matrix4x4(q);
            quaternion q2 = quaternion_from_matrix(m);
            suite.assert_true(approximately(q, q2) || approximately(q, -q2),
                "Quaternion -> matrix4x4 -> quaternion round trip");
        }

        // Rotation equivalence between quaternion and matrix
        {
            quaternion q = quaternion_rotation_y(Constants::PI / 3);
            float3 v(1, 2, 3);
            float3 rotated_q = q * v;
            float3 rotated_m = v * quaternion_to_matrix3x3(q);
            suite.assert_approximately_equal(rotated_q, rotated_m,
                "Quaternion and matrix rotation equivalence", 1e-5f);
        }

        // ============================================================================
        // 8. Euler Angle Conversions
        // ============================================================================
        suite.section("Euler Angle Conversions");

        // Direct creation from Euler angles
        {
            quaternion q = quaternion_euler(0.3f, 0.5f, 0.2f); // Yaw, Pitch, Roll
            float3 euler = quaternion_to_euler(q);
            suite.assert_approximately_equal(euler.x, 0.3f, "Yaw conversion", 1e-4f);
            suite.assert_approximately_equal(euler.y, 0.5f, "Pitch conversion", 1e-4f);
            suite.assert_approximately_equal(euler.z, 0.2f, "Roll conversion", 1e-4f);
        }

        // Round trip conversion for various angles
        {
            std::vector<float3> test_angles = {
                float3(0.3f, 0.2f, 0.1f),    // Yaw, Pitch, Roll
                float3(0.1f, 0.3f, 0.2f),
                float3(0.2f, 0.1f, 0.3f),
                float3(0.5f, 0.0f, 0.0f),    // Yaw only
                float3(0.0f, 0.5f, 0.0f),    // Pitch only
                float3(0.0f, 0.0f, 0.5f)     // Roll only
            };

            for (const auto& angles : test_angles) {
                quaternion q = quaternion_euler(angles);
                float3 euler_back = quaternion_to_euler(q);
                quaternion q_back = quaternion_euler(euler_back);

                // q and q_back should represent the same rotation
                float dot_val = std::abs(dot(q, q_back));
                suite.assert_true(dot_val > 0.9999f,
                    "Euler round trip for angles (y=" +
                    std::to_string(angles.x) + ", p=" +
                    std::to_string(angles.y) + ", r=" +
                    std::to_string(angles.z) + ")");
            }
        }

        // Yaw only rotation
        {
            float3 euler_yaw(0.3f, 0.0f, 0.0f);
            quaternion q_yaw = quaternion_euler(euler_yaw);
            float3 euler_back = quaternion_to_euler(q_yaw);
            suite.assert_approximately_equal(euler_back.x, 0.3f, "Yaw only rotation", 1e-4f);
        }

        // Pitch only rotation
        {
            float3 euler_pitch(0.0f, 0.5f, 0.0f);
            quaternion q_pitch = quaternion_euler(euler_pitch);
            float3 euler_back = quaternion_to_euler(q_pitch);
            suite.assert_approximately_equal(euler_back.y, 0.5f, "Pitch only rotation", 1e-4f);
        }

        // Roll only rotation
        {
            float3 euler_roll(0.0f, 0.0f, 0.2f);
            quaternion q_roll = quaternion_euler(euler_roll);
            float3 euler_back = quaternion_to_euler(q_roll);
            suite.assert_approximately_equal(euler_back.z, 0.2f, "Roll only rotation", 1e-4f);
        }

        // Consistency with rotation matrix
        {
            float3 euler(0.3f, 0.5f, 0.2f); // Yaw, Pitch, Roll
            quaternion q = quaternion_euler(euler);
            float3x3 m1 = quaternion_to_matrix3x3(q);

            // Create rotation matrix directly from Euler angles in Yaw->Pitch->Roll order
            float3x3 m2 = float3x3::rotation_z(euler.z) *
                          float3x3::rotation_x(euler.y) *
                          float3x3::rotation_y(euler.x);

            suite.assert_approximately_equal(m1, m2, "Euler to matrix consistency", 1e-4f);
        }

        // ============================================================================
        // 9. Axis-Angle Conversions
        // ============================================================================
        suite.section("Axis-Angle Conversions");

        // Round trip conversion
        {
            float3 axis = normalize(float3(1, 2, 3));
            float angle = 1.5f;
            quaternion q = quaternion_axis_angle(axis, angle);

            float3 axis2;
            float angle2;
            quaternion_to_axis_angle(q, axis2, angle2);

            // Axis may be inverted with angle change (q and -q represent the same rotation)
            quaternion q2 = quaternion_axis_angle(axis2, angle2);
            suite.assert_true(approximately(q, q2) || approximately(q, -q2),
                "Axis-angle -> quaternion -> axis-angle round trip");
        }

        // ============================================================================
        // 10. Look Rotation
        // ============================================================================
        suite.section("Look Rotation");

        // Look along Z axis
        {
            float3 forward = float3::unit_z();
            float3 up = float3::unit_y();
            quaternion q = quaternion_look_rotation(forward, up);

            // Should be identity (looking along Z with Y up)
            suite.assert_approximately_equal(q, identity_quaternion(),
                "Look rotation along Z axis");
        }

        // Look in arbitrary direction
        {
            float3 forward = normalize(float3(1, 0, 1));
            float3 up = float3::unit_y();
            quaternion q = quaternion_look_rotation(forward, up);

            // Forward vector should match
            float3 transformed_forward = q * float3::unit_z();
            suite.assert_approximately_equal(transformed_forward, forward,
                "Look rotation aligns forward vector", 1e-4f);

            // Up vector should be perpendicular to forward
            float3 transformed_up = q * float3::unit_y();
            float dot_val = dot(transformed_forward, transformed_up);
            suite.assert_approximately_equal(dot_val, 0.0f,
                "Look rotation keeps up perpendicular to forward", 1e-4f);
        }

        // ============================================================================
        // 11. Interpolation
        // ============================================================================
        suite.section("Interpolation");

        // NLERP between two quaternions
        {
            quaternion a = quaternion_rotation_x(0);
            quaternion b = quaternion_rotation_x(Constants::PI);
            quaternion mid = nlerp(a, b, 0.5f);

            // Result should be normalized
            suite.assert_approximately_equal(length(mid), 1.0f, "NLERP result normalized", 1e-6f);

            // Boundary checks
            suite.assert_approximately_equal(nlerp(a, b, 0.0f), a, "NLERP at t=0");
            suite.assert_approximately_equal(nlerp(a, b, 1.0f), b, "NLERP at t=1");
        }

        // SLERP between two quaternions
        {
            quaternion a = quaternion_rotation_x(0);
            quaternion b = quaternion_rotation_x(Constants::PI / 2);
            quaternion mid = slerp(a, b, 0.5f);
            quaternion mid_expected = quaternion_rotation_x(Constants::PI / 4);

            // Result should be normalized
            suite.assert_approximately_equal(length(mid), 1.0f, "SLERP result normalized", 1e-6f);
            suite.assert_approximately_equal(mid, mid_expected, "SLERP at t=0.5 equals 45° rotation", 1e-5f);

            // Boundary checks
            suite.assert_approximately_equal(slerp(a, b, 0.0f), a, "SLERP at t=0 returns a");
            suite.assert_approximately_equal(slerp(a, b, 1.0f), b, "SLERP at t=1 returns b");
        }

        // SLERP approximates NLERP for small angles
        {
            quaternion a = quaternion_rotation_x(0.1f);
            quaternion b = quaternion_rotation_x(0.2f);
            quaternion s = slerp(a, b, 0.5f);
            quaternion n = nlerp(a, b, 0.5f);
            suite.assert_approximately_equal(s, n, "SLERP approx NLERP for small angles", 1e-2f);
        }

        // ============================================================================
        // 12. From-To Rotation
        // ============================================================================
        suite.section("From-To Rotation");

        // Simple rotation from one vector to another
        {
            float3 from = float3::unit_x();
            float3 to = float3::unit_y();
            quaternion q = quaternion_from_to_rotation(from, to);

            float3 rotated = q * from;
            suite.assert_approximately_equal(normalize(rotated), to,
                "From-to rotation aligns vectors", 1e-5f);
        }

        // Opposite vectors (180 degree rotation)
        {
            float3 from = float3::unit_x();
            float3 to = -float3::unit_x();
            quaternion q = quaternion_from_to_rotation(from, to);

            float3 rotated = q * from;
            suite.assert_approximately_equal(normalize(rotated), to,
                "From-to rotation for opposite vectors", 1e-5f);
        }

        // ============================================================================
        // 13. Properties and Validation
        // ============================================================================
        suite.section("Properties and Validation");

        // Identity quaternion check
        {
            suite.assert_true(is_identity(identity_quaternion()), "Identity quaternion is_identity()");
            suite.assert_false(is_identity(quaternion(1, 0, 0, 1)), "Non-identity quaternion is not identity");
        }

        // Zero quaternion check
        {
            quaternion zero = zero_quaternion();
            suite.assert_true(approximately_zero(zero), "Zero quaternion approximately_zero()");
            suite.assert_false(approximately_zero(identity_quaternion()), "Identity not approximately zero");
        }

        // Validity check
        {
            quaternion valid(1, 2, 3, 4);
            suite.assert_true(is_valid(valid), "Normal quaternion is valid");
        }

        // Dot product
        {
            quaternion a(1, 2, 3, 4);
            quaternion b(5, 6, 7, 8);
            float dot_val = dot(a, b);
            float expected = 1 * 5 + 2 * 6 + 3 * 7 + 4 * 8;
            suite.assert_approximately_equal(dot_val, expected, "Dot product calculation");
        }

        // Approximate equality
        {
            quaternion a = normalize(quaternion(1, 2, 3, 4));
            quaternion b = normalize(quaternion(1.00001f, 2.00001f, 3.00001f, 4.00001f));
            suite.assert_true(approximately(a, b, 1e-4f), "Approximately equal for similar quaternions");
            suite.assert_true(approximately(a, -b, 1e-4f), "Quaternion and its negative represent the same rotation");
        }

        // ============================================================================
        // 14. Operators
        // ============================================================================
        suite.section("Operators");

        // Compound operators
        {
            quaternion a(1, 2, 3, 4);
            quaternion b(5, 6, 7, 8);

            quaternion a_plus_b = a;
            a_plus_b += b;
            suite.assert_approximately_equal(a_plus_b, a + b, "+= operator");

            quaternion a_minus_b = a;
            a_minus_b -= b;
            suite.assert_approximately_equal(a_minus_b, a - b, "-= operator");

            quaternion a_times_scalar = a;
            a_times_scalar *= 2.0f;
            suite.assert_approximately_equal(a_times_scalar, a * 2.0f, "*= scalar operator");

            quaternion a_div_scalar = a;
            a_div_scalar /= 2.0f;
            suite.assert_approximately_equal(a_div_scalar, a / 2.0f, "/= scalar operator");

            quaternion a_times_q = normalize(a);
            quaternion b_norm = normalize(b);
            quaternion a_times_b = a_times_q;
            a_times_b *= b_norm;
            suite.assert_approximately_equal(a_times_b, a_times_q * b_norm, "*= quaternion operator");
        }

        // Equality operators
        {
            quaternion a(1, 2, 3, 4);
            quaternion b(1, 2, 3, 4);
            quaternion c(5, 6, 7, 8);

            suite.assert_true(a == b, "== operator for equal quaternions");
            suite.assert_false(a == c, "== operator for different quaternions");
            suite.assert_true(a != c, "!= operator for different quaternions");
        }

        // ============================================================================
        // 15. SIMD Operations
        // ============================================================================
        suite.section("SIMD Operations");

        // SIMD get/set
        {
            quaternion q(1, 2, 3, 4);
            __m128 simd = q.get_simd();
            quaternion q2;
            q2.set_simd(simd);
            suite.assert_equal(q, q2, "SIMD get/set round trip");
        }

        // ============================================================================
        // 16. String Representation
        // ============================================================================
        suite.section("String Representation");

        {
            quaternion q(1.5f, 2.25f, 3.125f, 4.0625f);
            std::string str = q.to_string();
            suite.assert_true(str.length() > 0, "to_string() returns non-empty string");
            suite.assert_true(str.find("1.5") != std::string::npos ||
                str.find("1.500") != std::string::npos,
                "to_string() contains x value");
        }

        // ============================================================================
        // 17. Edge Cases
        // ============================================================================
        suite.section("Edge Cases");

        // Division by zero
        {
            quaternion q(1, 2, 3, 4);
            quaternion divided = q / 0.0f;
            suite.assert_false(is_valid(divided), "Division by zero produces invalid quaternion");
        }

        // Normalization of zero quaternion
        {
            quaternion zero = zero_quaternion();
            quaternion normalized = normalize(zero);
            suite.assert_approximately_equal(normalized, identity_quaternion(),
                "Normalizing zero quaternion returns identity");
        }

        // Inverse of zero quaternion
        {
            quaternion zero = zero_quaternion();
            quaternion inv = inverse(zero);
            suite.assert_approximately_equal(inv, identity_quaternion(),
                "Inverse of zero quaternion returns identity");
        }

        // Very small quaternion
        {
            quaternion tiny(1e-10f, 2e-10f, 3e-10f, 4e-10f);
            suite.assert_true(approximately_zero(tiny, 1e-5f), "Tiny quaternion approximately zero");
        }

        // Normalization of almost zero quaternion
        {
            quaternion tiny(1e-15f, 2e-15f, 3e-15f, 4e-15f);
            quaternion normalized = normalize(tiny);
            suite.assert_approximately_equal(length(normalized), 1.0f,
                "Normalization of tiny quaternion", 1e-6f);
        }
    }
}
