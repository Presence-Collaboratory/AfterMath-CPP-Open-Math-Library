// Author: DeepSeek
// Test suite for AfterMath::float2x2 class

#pragma once

#include "AutotestCore.h"

namespace AfterMathTests
{
    void RunFloat2x2Tests(TestSuite& suite)
    {
        using namespace AfterMath;

        // ============================================================================
        // 1. Constructors and basic operations
        // ============================================================================
        suite.section("Constructors and basic operations");

        // Test default constructor (identity matrix)
        suite.assert_equal(float2x2::identity(), float2x2(), "Default constructor returns identity");

        // Test constructor with two rows
        suite.assert_equal(float2x2(float2(1, 2), float2(3, 4)),
            float2x2(1, 2, 3, 4),
            "Constructor with two float2 rows");

        // Test constructor with four values
        {
            float2x2 mat(1.0f, 2.0f, 3.0f, 4.0f);
            suite.assert_equal(mat(0, 0), 1.0f, "4-param constructor (0,0)");
            suite.assert_equal(mat(0, 1), 2.0f, "4-param constructor (0,1)");
            suite.assert_equal(mat(1, 0), 3.0f, "4-param constructor (1,0)");
            suite.assert_equal(mat(1, 1), 4.0f, "4-param constructor (1,1)");
        }

        // Test constructor from array
        {
            float data[4] = { 1, 2, 3, 4 };
            float2x2 mat(data);
            suite.assert_equal(mat[0][0], 1.0f, "Array constructor [0][0]");
            suite.assert_equal(mat[0][1], 2.0f, "Array constructor [0][1]");
            suite.assert_equal(mat[1][0], 3.0f, "Array constructor [1][0]");
            suite.assert_equal(mat[1][1], 4.0f, "Array constructor [1][1]");
        }

        // Test scalar constructor
        {
            float2x2 mat(5.0f);
            suite.assert_equal(mat(0, 0), 5.0f, "Scalar constructor (0,0)");
            suite.assert_equal(mat(1, 1), 5.0f, "Scalar constructor (1,1)");
            suite.assert_equal(mat(0, 1), 0.0f, "Scalar constructor off-diagonal (0,1)");
            suite.assert_equal(mat(1, 0), 0.0f, "Scalar constructor off-diagonal (1,0)");
        }

        // Test constructor from diagonal vector
        {
            float2 diag(2.0f, 3.0f);
            float2x2 mat(diag);
            suite.assert_equal(mat(0, 0), 2.0f, "Diagonal vector constructor (0,0)");
            suite.assert_equal(mat(1, 1), 3.0f, "Diagonal vector constructor (1,1)");
            suite.assert_equal(mat(0, 1), 0.0f, "Diagonal vector constructor off-diagonal (0,1)");
            suite.assert_equal(mat(1, 0), 0.0f, "Diagonal vector constructor off-diagonal (1,0)");
        }

        // ============================================================================
        // 2. Element access
        // ============================================================================
        suite.section("Element access");

        float2x2 mat(1, 2, 3, 4);

        // Check [] operator
        suite.assert_equal(mat[0], float2(1, 2), "Operator[] row0");
        suite.assert_equal(mat[1], float2(3, 4), "Operator[] row1");

        // Check () operator
        suite.assert_equal(mat(0, 0), 1.0f, "Operator() (0,0)");
        suite.assert_equal(mat(0, 1), 2.0f, "Operator() (0,1)");
        suite.assert_equal(mat(1, 0), 3.0f, "Operator() (1,0)");
        suite.assert_equal(mat(1, 1), 4.0f, "Operator() (1,1)");

        // Check col access methods
        suite.assert_equal(mat.col0(), float2(1, 3), "col0()");
        suite.assert_equal(mat.col1(), float2(2, 4), "col1()");

        // Check set_col
        {
            float2x2 m;
            m.set_col0(float2(10, 11));
            m.set_col1(float2(12, 13));
            suite.assert_equal(m.col0(), float2(10, 11), "set_col0");
            suite.assert_equal(m.col1(), float2(12, 13), "set_col1");
        }

        // Check SSE data
        {
            __m128 sse = _mm_setr_ps(1, 2, 3, 4);
            float2x2 mat_sse(sse);
            suite.assert_equal(mat_sse, float2x2(1, 2, 3, 4), "SSE constructor and getter");

            __m128 retrieved = mat_sse.sse_data();
            float2x2 mat_from_sse(retrieved);
            suite.assert_equal(mat_from_sse, mat_sse, "SSE data roundtrip");
        }

        // ============================================================================
        // 3. Static matrix creation methods
        // ============================================================================
        suite.section("Static matrix creation methods");

        // Identity and Zero
        suite.assert_true(is_identity(float2x2::identity()), "identity() creates identity matrix");
        suite.assert_true(approximately_zero(float2x2::zero()), "zero() creates zero matrix");

        // Rotation matrix
        {
            float angle = PI / 4.0f; // 45 degrees
            float2x2 rot = float2x2::rotation(angle);

            // Check rotation matrix properties
            suite.assert_true(is_rotation(rot), "rotation() creates rotation matrix");
            suite.assert_approximately_equal(determinant(rot), 1.0f, "rotation determinant = 1", 1e-6f);

            // Check specific values for 45 degrees
            float sqrt2_2 = std::sqrt(2.0f) / 2.0f;
            float2x2 expected_rot(sqrt2_2, -sqrt2_2,
                sqrt2_2, sqrt2_2);
            suite.assert_approximately_equal(rot, expected_rot, "rotation 45 degrees");

            // Vector (1,0) should transform to (cos, sin)
            float2 vec(1, 0);
            float2 transformed = rot * vec;
            suite.assert_approximately_equal(transformed, float2(sqrt2_2, sqrt2_2),
                "rotation transforms (1,0) correctly");
        }

        // Scaling matrices
        {
            // From vector
            float2 scale_vec(2, 3);
            float2x2 scale = float2x2::scaling(scale_vec);
            suite.assert_equal(scale(0, 0), 2.0f, "scaling(vector) (0,0)");
            suite.assert_equal(scale(1, 1), 3.0f, "scaling(vector) (1,1)");
            suite.assert_equal(scale(0, 1), 0.0f, "scaling(vector) off-diagonal (0,1)");
            suite.assert_equal(scale(1, 0), 0.0f, "scaling(vector) off-diagonal (1,0)");

            // From two values
            float2x2 scale2 = float2x2::scaling(2.0f, 3.0f);
            suite.assert_equal(scale2, scale, "scaling(x,y) equals scaling(vector)");

            // Uniform scaling
            float2x2 uniform_scale = float2x2::scaling(5.0f);
            suite.assert_equal(uniform_scale(0, 0), 5.0f, "uniform scaling (0,0)");
            suite.assert_equal(uniform_scale(1, 1), 5.0f, "uniform scaling (1,1)");
            suite.assert_equal(uniform_scale(0, 1), 0.0f, "uniform scaling off-diagonal (0,1)");
            suite.assert_equal(uniform_scale(1, 0), 0.0f, "uniform scaling off-diagonal (1,0)");
        }

        // Shear matrix
        {
            float2 shear_vec(0.5f, 0.3f);
            float2x2 shear_mat = float2x2::shear(shear_vec);

            suite.assert_equal(shear_mat(0, 0), 1.0f, "shear (0,0)");
            suite.assert_equal(shear_mat(0, 1), 0.5f, "shear (0,1)");
            suite.assert_equal(shear_mat(1, 0), 0.3f, "shear (1,0)");
            suite.assert_equal(shear_mat(1, 1), 1.0f, "shear (1,1)");

            // From two values
            float2x2 shear_mat2 = float2x2::shear(0.5f, 0.3f);
            suite.assert_equal(shear_mat2, shear_mat, "shear(x,y) equals shear(vector)");

            // Test vector transformation
            float2 vec(1, 1);
            float2 sheared = shear_mat * vec;
            suite.assert_equal(sheared, float2(1.5f, 1.3f), "shear transformation");
        }

        // ============================================================================
        // 4. Arithmetic operations
        // ============================================================================
        suite.section("Arithmetic operations");

        float2x2 A(1, 2, 3, 4);
        float2x2 B(5, 6, 7, 8);

        // Addition
        {
            float2x2 sum = A + B;
            float2x2 expected(6, 8, 10, 12);
            suite.assert_equal(sum, expected, "Matrix addition");

            // Check += operator
            float2x2 A_copy = A;
            A_copy += B;
            suite.assert_equal(A_copy, expected, "Operator +=");
        }

        // Subtraction
        {
            float2x2 diff = A - B;
            float2x2 expected(-4, -4, -4, -4);
            suite.assert_equal(diff, expected, "Matrix subtraction");

            // Check -= operator
            float2x2 A_copy = A;
            A_copy -= B;
            suite.assert_equal(A_copy, expected, "Operator -=");
        }

        // Scalar multiplication
        {
            float2x2 scaled = A * 2.0f;
            float2x2 expected(2, 4, 6, 8);
            suite.assert_equal(scaled, expected, "Matrix * scalar");

            // Check *= operator
            float2x2 A_copy = A;
            A_copy *= 2.0f;
            suite.assert_equal(A_copy, expected, "Operator *=");

            // Check scalar * matrix
            float2x2 scaled2 = 2.0f * A;
            suite.assert_equal(scaled2, expected, "Scalar * matrix");
        }

        // Scalar division
        {
            float2x2 A_copy = A;
            A_copy /= 2.0f;
            float2x2 expected(0.5f, 1.0f, 1.5f, 2.0f);
            suite.assert_equal(A_copy, expected, "Operator /=");
        }

        // Matrix multiplication
        {
            float2x2 C(1, 0, 0, 2);
            float2x2 D(3, 0, 0, 4);
            float2x2 result = C * D;
            float2x2 expected(3, 0, 0, 8);
            suite.assert_equal(result, expected, "Matrix multiplication diagonal");

            // Non-diagonal matrices
            float2x2 E(1, 2, 3, 4);
            float2x2 F(2, 0, 1, 2);
            float2x2 EF = E * F;
            float2x2 expected_EF(4, 4, 10, 8);
            suite.assert_equal(EF, expected_EF, "Matrix multiplication non-diagonal");

            // Check *= operator
            float2x2 C_copy = C;
            C_copy *= D;
            suite.assert_equal(C_copy, expected, "Operator *=");
        }

        // Unary operators
        {
            float2x2 neg = -A;
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    suite.assert_equal(neg(i, j), -A(i, j), "Unary minus");
                }
            }

            float2x2 pos = +A;
            suite.assert_equal(pos, A, "Unary plus");
        }

        // ============================================================================
        // 5. Vector multiplication
        // ============================================================================
        suite.section("Vector multiplication");

        float2x2 M(1, 2, 3, 4);
        float2 v(2, 3);

        // Matrix * vector (right multiplication)
        {
            float2 result = M * v;
            float2 expected(8, 18); // (1*2 + 2*3, 3*2 + 4*3)
            suite.assert_equal(result, expected, "Matrix * vector");
        }

        // Vector * matrix (left multiplication)
        {
            float2 result = v * M;
            float2 expected(11.0f, 16.0f);
            suite.assert_equal(result, expected, "Vector * matrix (row vector multiplication)");
        }

        // Test transform_vector (global function)
        {
            float2 result = transform_vector(M, v);
            float2 expected = M * v;
            suite.assert_equal(result, expected, "transform_vector");
        }

        // Test transform_point (should be same as transform_vector for float2x2)
        {
            float2 result = transform_point(M, v);
            float2 expected = M * v;
            suite.assert_equal(result, expected, "transform_point");
        }

        // Test mul free functions
        {
            float2 mul_vec = mul(v, M);
            float2 expected(11.0f, 16.0f);
            suite.assert_equal(mul_vec, expected, "mul(vector, matrix) - row vector multiplication");
        }

        // ============================================================================
        // 6. Matrix operations
        // ============================================================================
        suite.section("Matrix operations");

        // Transpose
        {
            float2x2 mat(1, 2, 3, 4);
            float2x2 transposed_mat = transpose(mat);
            float2x2 expected(1, 3, 2, 4);
            suite.assert_equal(transposed_mat, expected, "transpose");

            // Check that transpose twice returns original
            suite.assert_equal(transpose(transposed_mat), mat, "transpose twice returns original");
        }

        // Determinant
        {
            float2x2 identity = float2x2::identity();
            suite.assert_approximately_equal(determinant(identity), 1.0f, "identity determinant = 1");

            float2x2 zero_mat = float2x2::zero();
            suite.assert_approximately_equal(determinant(zero_mat), 0.0f, "zero determinant = 0");

            float2x2 mat(1, 2, 3, 4);
            float expected_det = 1 * 4 - 2 * 3; // -2
            suite.assert_approximately_equal(determinant(mat), expected_det, "2x2 determinant calculation");
        }

        // Adjugate matrix
        {
            float2x2 mat(1, 2, 3, 4);
            float2x2 adj = adjugate(mat);
            float2x2 expected(4, -2, -3, 1);
            suite.assert_equal(adj, expected, "adjugate matrix");

            // Check property: A * adj(A) = det(A) * I
            float2x2 product = mat * adj;
            float2x2 det_times_identity = float2x2::identity() * determinant(mat);
            suite.assert_approximately_equal(product, det_times_identity, "A * adj(A) = det(A) * I");
        }

        // Inverse matrix
        {
            float2x2 scale = float2x2::scaling(2, 3);
            float2x2 invScale = inverse(scale);
            float2x2 expected(0.5f, 0, 0, 1.0f / 3.0f);
            suite.assert_approximately_equal(invScale, expected, "inverse of scaling matrix");

            // Check that A * A^(-1) = I
            float2x2 product = scale * invScale;
            suite.assert_true(is_identity(product, 1e-5f), "A * A^(-1) = I for scaling");

            // Check rotation matrix (inverse = transpose)
            float angle = PI / 6.0f;
            float2x2 rotation = float2x2::rotation(angle);
            float2x2 invRotation = inverse(rotation);
            float2x2 transposedRotation = transpose(rotation);
            suite.assert_approximately_equal(invRotation, transposedRotation,
                "inverse of rotation = transpose", 1e-5f);

            // Singular matrix (zero determinant)
            float2x2 singular(1, 2, 2, 4); // Linearly dependent rows
            // Should return identity (as implemented for zero determinant)
            float2x2 invSingular = inverse(singular);
            suite.assert_true(is_identity(invSingular, 1e-5f), "singular matrix inverse returns identity");
        }

        // Trace
        {
            float2x2 mat(1, 2, 3, 4);
            float expectedTrace = 1 + 4;
            suite.assert_approximately_equal(trace(mat), expectedTrace, "trace");
        }

        // Diagonal
        {
            float2x2 mat(1, 2, 3, 4);
            float2 expectedDiag(1, 4);
            suite.assert_equal(diagonal(mat), expectedDiag, "diagonal");
        }

        // Frobenius norm
        {
            float2x2 mat(1, 0, 0, 2);
            float expectedNorm = std::sqrt(1.0f * 1.0f + 2.0f * 2.0f);
            suite.assert_approximately_equal(frobenius_norm(mat), expectedNorm, "frobenius_norm");
        }

        // ============================================================================
        // 7. Special functions
        // ============================================================================
        suite.section("Special functions");

        // Get rotation angle
        {
            float angle = PI / 3.0f; // 60 degrees
            float2x2 rot = float2x2::rotation(angle);
            float extracted = get_rotation(rot);
            suite.assert_approximately_equal(extracted, angle, "get_rotation from pure rotation", 1e-5f);

            // Matrix with UNIFORM scale and rotation
            float2x2 rot_scale = float2x2::scaling(2.0f) * float2x2::rotation(angle);
            float extracted2 = get_rotation(rot_scale);
            suite.assert_approximately_equal(extracted2, angle, "get_rotation from uniform scaled rotation", 1e-5f);

            // Matrix with reflection (negative determinant)
            float2x2 reflect(1, 0, 0, -1); // Reflection across Y axis
            float extracted3 = get_rotation(reflect);
            // For matrices with reflection, get_rotation should return 0 (as per implementation)
            suite.assert_approximately_equal(extracted3, 0.0f, "get_rotation from reflection returns 0");
        }

        // Get scale
        {
            float2 scale_vec(2, 3);
            float2x2 scale_mat = float2x2::scaling(scale_vec);
            float2 extracted = get_scale(scale_mat);
            suite.assert_approximately_equal(extracted, scale_vec, "get_scale from scaling matrix");

            // For matrix with rotation and scale
            float angle = PI / 4.0f;
            float2x2 rot_scale = float2x2::rotation(angle) * float2x2::scaling(2, 3);
            float2 extracted2 = get_scale(rot_scale);
            // Scale should be extracted as column lengths
            float2 expected2(length(rot_scale.col0()),
                length(rot_scale.col1()));
            suite.assert_approximately_equal(extracted2, expected2, "get_scale from rotation+scaling");
        }

        // Set rotation
        {
            float2x2 mat = float2x2::scaling(2, 3);
            float new_angle = PI / 3.0f;

            set_rotation(mat, new_angle);
            float extracted = get_rotation(mat);
            suite.assert_approximately_equal(extracted, new_angle, "set_rotation", 1e-5f);

            // Scale should be preserved
            float2 scale = get_scale(mat);
            suite.assert_approximately_equal(scale, float2(2, 3), "set_rotation preserves scale", 1e-5f);
        }

        // Set scale
        {
            float2x2 mat = float2x2::rotation(PI / 4.0f);
            float2 new_scale(3, 4);

            set_scale(mat, new_scale);
            float2 extracted = get_scale(mat);
            suite.assert_approximately_equal(extracted, new_scale, "set_scale", 1e-5f);

            // Rotation should be preserved
            float angle = get_rotation(mat);
            suite.assert_approximately_equal(angle, PI / 4.0f,
                "set_scale preserves rotation", 1e-5f);
        }

        // ============================================================================
        // 8. Property checks
        // ============================================================================
        suite.section("Property checks");

        // Identity check
        suite.assert_true(is_identity(float2x2::identity()), "is_identity(identity())");
        suite.assert_false(is_identity(float2x2::zero()), "is_identity(zero()) returns false");
        suite.assert_true(is_identity(float2x2::scaling(1.0f)), "is_identity(uniform scaling(1))");

        // Orthogonality check
        {
            float2x2 rotation = float2x2::rotation(PI / 3.0f);
            suite.assert_true(is_orthogonal(rotation), "rotation matrix is orthogonal");

            float2x2 scale = float2x2::scaling(2, 3);
            suite.assert_true(is_orthogonal(scale), "scaling matrix is orthogonal");

            float2x2 non_ortho(1, 2, 3, 4);
            suite.assert_false(is_orthogonal(non_ortho), "non-orthogonal matrix detected");
        }

        // Rotation check
        {
            float2x2 rotation = float2x2::rotation(PI / 3.0f);
            suite.assert_true(is_rotation(rotation), "rotation matrix is rotation");

            float2x2 scale = float2x2::scaling(2, 2);
            suite.assert_false(is_rotation(scale), "uniform scaling is not rotation (det != 1)");

            float2x2 scale_non_uniform = float2x2::scaling(2, 3);
            suite.assert_false(is_rotation(scale_non_uniform), "non-uniform scaling is not rotation");
        }

        // Approximately zero check
        suite.assert_true(approximately_zero(float2x2::zero()), "approximately_zero(zero())");
        suite.assert_false(approximately_zero(float2x2::identity()), "approximately_zero(identity()) returns false");

        // Approximately equal check
        {
            float2x2 mat1(1, 2, 3, 4);

            // Matrix with small differences
            float2x2 mat2(1.000001f, 2.000001f, 3.000001f, 4.000001f);

            // Check that with default epsilon they are considered equal
            suite.assert_true(approximately(mat1, mat2, 1e-6f),
                "matrices are approximately equal with default epsilon");

            // Therefore operator == should return true
            suite.assert_true(mat1 == mat2, "operator == returns true for approximately equal matrices");

            // And operator != should return false
            suite.assert_false(mat1 != mat2, "operator != returns false for approximately equal matrices");

            // Now create a matrix that is clearly different
            float2x2 mat3(2, 2, 3, 4);

            suite.assert_true(mat1 != mat3, "operator != returns true for different matrices");
        }

        // ============================================================================
        // 9. Data conversions
        // ============================================================================
        suite.section("Data conversions");

        // to_row_major
        {
            float2x2 mat(1, 2, 3, 4);

            float rowMajor[4];
            mat.to_row_major(rowMajor);

            float expected[4] = { 1, 2, 3, 4 };
            for (int i = 0; i < 4; ++i) {
                suite.assert_equal(rowMajor[i], expected[i],
                    "to_row_major element " + std::to_string(i));
            }
        }

        // to_column_major
        {
            float2x2 mat(1, 2, 3, 4);

            float colMajor[4];
            mat.to_column_major(colMajor);

            float expected[4] = { 1, 3, 2, 4 };
            for (int i = 0; i < 4; ++i) {
                suite.assert_equal(colMajor[i], expected[i],
                    "to_column_major element " + std::to_string(i));
            }
        }

        // to_string
        {
            float2x2 mat(1.5f, 2.5f, 3.5f, 4.5f);

            std::string str = mat.to_string();
            // Check that string contains expected values
            suite.assert_true(str.find("1.5000") != std::string::npos, "to_string contains 1.5000");
            suite.assert_true(str.find("4.5000") != std::string::npos, "to_string contains 4.5000");
        }

        // ============================================================================
        // 10. Edge cases and special values
        // ============================================================================
        suite.section("Edge cases and special values");

        // Very small values
        {
            float epsilon = 1e-6f;
            float2x2 tinyMat(epsilon, 0, 0, epsilon);

            suite.assert_true(approximately_zero(tinyMat, epsilon * 2),
                "approximately_zero with tiny values");
        }

        // Very large values
        {
            float large = 1e10f;
            float2x2 largeMat(large, 0, 0, large);

            // Inverse matrix should have small values
            float2x2 invLarge = inverse(largeMat);
            float2x2 expected(1.0f / large, 0, 0, 1.0f / large);
            suite.assert_approximately_equal(invLarge, expected,
                "inverse of large diagonal matrix", 1e-5f);
        }

        // Zero rotation angle
        {
            float2x2 rot = float2x2::rotation(0.0f);
            suite.assert_true(is_identity(rot, 1e-5f), "rotation(0) returns identity");
        }

        // 90 degree rotation
        {
            float2x2 rot90 = float2x2::rotation(PI / 2.0f);
            float2 vec(1, 0);
            float2 transformed = rot90 * vec;
            suite.assert_approximately_equal(transformed, float2(0, 1), "rotation 90 degrees");
        }

        // 180 degree rotation
        {
            float2x2 rot180 = float2x2::rotation(PI);
            float2 vec(1, 0);
            float2 transformed = rot180 * vec;
            suite.assert_approximately_equal(transformed, float2(-1, 0), "rotation 180 degrees");
        }

        // 360 degree rotation
        {
            float2x2 rot360 = float2x2::rotation(2.0f * PI);
            suite.assert_true(is_identity(rot360, 1e-5f), "rotation(2pi) returns identity");
        }

        // Division by zero
        {
            float2x2 mat(1, 2, 3, 4);

            try {
                mat /= 0.0f;
                // If no exception thrown, elements should be inf or nan
                // Implementation uses 1.0f / scalar, which gives inf
                suite.assert_true(std::isinf(mat(0, 0)) || std::isnan(mat(0, 0)),
                    "division by zero produces inf/nan");
            }
            catch (...) {
                suite.skip_test("Division by zero", "Exception thrown - implementation dependent");
            }
        }

        // Matrix with negative scale (reflection)
        {
            float2x2 reflect(-1, 0, 0, 1); // Reflection across X axis
            suite.assert_approximately_equal(determinant(reflect), -1.0f,
                "reflection has determinant -1");

            float2 vec(1, 1);
            float2 reflected = reflect * vec;
            suite.assert_equal(reflected, float2(-1, 1), "reflection transformation");
        }

        // Complex transformation: rotation + scale + shear
        {
            float2x2 rot = float2x2::rotation(PI / 6.0f);
            float2x2 scale = float2x2::scaling(2, 3);
            float2x2 shear_mat = float2x2::shear(0.1f, 0.2f);

            float2x2 complex = rot * scale * shear_mat;

            // Check determinant
            float det_complex = determinant(complex);
            float det_expected = determinant(rot) * determinant(scale) * determinant(shear_mat);
            suite.assert_approximately_equal(det_complex, det_expected,
                "determinant of complex transformation", 1e-5f);

            // Check inverse
            float2x2 inv_complex = inverse(complex);
            float2x2 product = complex * inv_complex;
            suite.assert_true(is_identity(product, 1e-4f),
                "complex transformation has valid inverse");
        }
    }
}
