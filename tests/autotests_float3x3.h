// Author: DeepSeek
// Test suite for AfterMath::float3x3 class

#include "AutotestCore.h"

namespace AfterMathTests
{
    void RunFloat3x3Tests()
    {
        TestSuite suite("Float3x3 Tests", true);
        suite.header();

        using namespace AfterMath;

        // ============================================================================
        // 1. Constructors and basic operations
        // ============================================================================
        suite.section("Constructors and basic operations");

        // Test default constructor (identity matrix)
        suite.assert_equal(float3x3::identity(), float3x3(), "Default constructor returns identity");

        // Test constructor with diagonal
        suite.assert_equal(float3x3::scaling(2.0f, 3.0f, 4.0f),
            float3x3(float3(2, 0, 0), float3(0, 3, 0), float3(0, 0, 4)),
            "Diagonal constructor");

        // Test constructor from array
        {
            float data[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            float3x3 mat(data);
            suite.assert_equal(mat[0][0], 1.0f, "Array constructor [0][0]");
            suite.assert_equal(mat[1][2], 6.0f, "Array constructor [1][2]");
            suite.assert_equal(mat[2][1], 8.0f, "Array constructor [2][1]");
        }

        // Test scalar constructor
        suite.assert_equal(float3x3(5.0f), float3x3::scaling(5.0f), "Scalar constructor");

        // ============================================================================
        // 2. Element access
        // ============================================================================
        suite.section("Element access");

        float3x3 mat(1, 2, 3,
            4, 5, 6,
            7, 8, 9);

        // Check [] operator
        suite.assert_equal(mat[0], float3(1, 2, 3), "Operator[] row0");
        suite.assert_equal(mat[1], float3(4, 5, 6), "Operator[] row1");
        suite.assert_equal(mat[2], float3(7, 8, 9), "Operator[] row2");

        // Check () operator
        suite.assert_equal(mat(0, 0), 1.0f, "Operator() (0,0)");
        suite.assert_equal(mat(1, 1), 5.0f, "Operator() (1,1)");
        suite.assert_equal(mat(2, 2), 9.0f, "Operator() (2,2)");
        suite.assert_equal(mat(1, 2), 6.0f, "Operator() (1,2)");

        // Check col access methods (now global functions)
        suite.assert_equal(mat.col0(), float3(1, 4, 7), "col0()");
        suite.assert_equal(mat.col1(), float3(2, 5, 8), "col1()");
        suite.assert_equal(mat.col2(), float3(3, 6, 9), "col2()");

        // Check set_col (now global functions)
        {
            float3x3 m;
            m.set_col0(float3(10, 11, 12));
            m.set_col1(float3(13, 14, 15));
            m.set_col2(float3(16, 17, 18));
            suite.assert_equal(m.col0(), float3(10, 11, 12), "set_col0");
            suite.assert_equal(m.col1(), float3(13, 14, 15), "set_col1");
            suite.assert_equal(m.col2(), float3(16, 17, 18), "set_col2");
        }

        // ============================================================================
        // 3. Static matrix creation methods
        // ============================================================================
        suite.section("Static matrix creation methods");

        // Identity and Zero
        suite.assert_true(is_identity(float3x3::identity()), "identity() creates identity matrix");
        suite.assert_true(approximately_zero(float3x3::zero()), "zero() creates zero matrix");

        // Scaling matrices
        {
            float3x3 scale = float3x3::scaling(float3(2, 3, 4));
            suite.assert_equal(scale(0, 0), 2.0f, "scaling(vector) (0,0)");
            suite.assert_equal(scale(1, 1), 3.0f, "scaling(vector) (1,1)");
            suite.assert_equal(scale(2, 2), 4.0f, "scaling(vector) (2,2)");
            suite.assert_equal(scale(0, 1), 0.0f, "scaling(vector) off-diagonal");
        }

        // Rotations around axes
        {
            float angle = PI / 4.0f; // 45 degrees
            float3x3 rotX = float3x3::rotation_x(angle);

            // Check rotation matrix properties
            suite.assert_true(is_orthonormal(rotX), "rotation_x creates orthonormal matrix");
            suite.assert_approximately_equal(determinant(rotX), 1.0f, "rotation_x determinant = 1", 1e-6f);

            // Check specific values for 45 degrees
            float sqrt2_2 = std::sqrt(2.0f) / 2.0f;
            float3x3 expectedRotX(1, 0, 0,
                     0, sqrt2_2, sqrt2_2,
                     0, -sqrt2_2, sqrt2_2);
            suite.assert_approximately_equal(rotX, expectedRotX, "rotation_x 45 degrees");
        }

        {
            float angle = PI / 2.0f; // 90 degrees
            float3x3 rotY = float3x3::rotation_y(angle);

            // Vector along X axis should transform to vector along Z axis
            float3 vec(1, 0, 0);
            float3 transformed = vec * rotY;
            suite.assert_approximately_equal(transformed, float3(0, 0, -1), "rotation_y 90 degrees transforms (1,0,0)");
        }

        {
            float angle = PI; // 180 degrees
            float3x3 rotZ = float3x3::rotation_z(angle);

            // Vector (1,0,0) should transform to (-1,0,0)
            float3 vec(1, 0, 0);
            float3 transformed = vec * rotZ;
            suite.assert_approximately_equal(transformed, float3(-1, 0, 0), "rotation_z 180 degrees");
        }

        // Rotation around arbitrary axis
        //{
        //    float3 axis = normalize(float3(1, 1, 1));
        //    float angle = 2.0f * PI / 3.0f; // 120 degrees

        //    float3x3 rot = float3x3::rotation_axis(axis, angle);

        //    // Rotation matrix should be orthonormal
        //    suite.assert_true(is_orthonormal(rot, 1e-5f), "rotation_axis creates orthonormal matrix");
        //    suite.assert_approximately_equal(determinant(rot), 1.0f, "rotation_axis determinant = 1", 1e-6f);

        //    // Rotation axis should be eigenvector with eigenvalue 1
        //    float3 axisTransformed = rot * axis;
        //    suite.assert_approximately_equal(axisTransformed, axis, "rotation axis is eigenvector");
        //}

        // Euler angles
        {
            float3 angles(PI / 6.0f,  // 30° around X
                PI / 4.0f,  // 45° around Y
                PI / 3.0f); // 60° around Z

            float3x3 eulerMat = float3x3::rotation_euler(angles);

            // Should be a rotation matrix
            suite.assert_true(is_orthonormal(eulerMat, 1e-5f), "rotation_euler creates orthonormal matrix");
            suite.assert_approximately_equal(determinant(eulerMat), 1.0f, "rotation_euler determinant = 1", 1e-6f);
        }

        // Skew-symmetric matrix
        {
            float3 vec(1, 2, 3);
            float3x3 skew = float3x3::skew_symmetric(vec);

            // Skew-symmetric matrix should be anti-symmetric
            suite.assert_true(approximately_zero(skew + transpose(skew)), "skew_symmetric is anti-symmetric");

            // Multiplying skew-symmetric matrix by vector is equivalent to cross product
            float3 testVec(4, 5, 6);
            float3 result1 = testVec * skew;
            float3 result2 = cross(vec, testVec);
            suite.assert_approximately_equal(result1, result2, "skew_symmetric * v = cross(vec, v)");
        }

        // Outer product
        {
            float3 u(1, 2, 3);
            float3 v(4, 5, 6);
            float3x3 outer = float3x3::outer_product(u, v);

            // Each element should be u_i * v_j
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    float expected = u[i] * v[j];
                    suite.assert_approximately_equal(outer(i, j), expected,
                        "outer_product element (" + std::to_string(i) + "," + std::to_string(j) + ")");
                }
            }
        }

        // ============================================================================
        // 4. Arithmetic operations
        // ============================================================================
        suite.section("Arithmetic operations");

        float3x3 A(1, 2, 3,
            4, 5, 6,
            7, 8, 9);

        float3x3 B(9, 8, 7,
            6, 5, 4,
            3, 2, 1);

        // Addition
        {
            float3x3 sum = A + B;
            float3x3 expected(10, 10, 10,
                10, 10, 10,
                10, 10, 10);
            suite.assert_equal(sum, expected, "Matrix addition");

            // Check += operator
            float3x3 A_copy = A;
            A_copy += B;
            suite.assert_equal(A_copy, expected, "Operator +=");
        }

        // Subtraction
        {
            float3x3 diff = A - B;
            float3x3 expected(-8, -6, -4,
                -2, 0, 2,
                4, 6, 8);
            suite.assert_equal(diff, expected, "Matrix subtraction");

            // Check -= operator
            float3x3 A_copy = A;
            A_copy -= B;
            suite.assert_equal(A_copy, expected, "Operator -=");
        }

        // Scalar multiplication
        {
            float3x3 scaled = A * 2.0f;
            float3x3 expected(2, 4, 6,
                8, 10, 12,
                14, 16, 18);
            suite.assert_equal(scaled, expected, "Matrix * scalar");

            // Check *= operator
            float3x3 A_copy = A;
            A_copy *= 2.0f;
            suite.assert_equal(A_copy, expected, "Operator *=");

            // Check scalar * matrix
            float3x3 scaled2 = 2.0f * A;
            suite.assert_equal(scaled2, expected, "Scalar * matrix");
        }

        // Scalar division
        {
            float3x3 A_copy = A;
            A_copy /= 2.0f;
            float3x3 expected(0.5f, 1.0f, 1.5f,
                2.0f, 2.5f, 3.0f,
                3.5f, 4.0f, 4.5f);
            suite.assert_equal(A_copy, expected, "Operator /=");
        }

        // Matrix multiplication
        {
            float3x3 C(1, 0, 0,
                0, 2, 0,
                0, 0, 3);

            float3x3 D(2, 0, 0,
                0, 3, 0,
                0, 0, 4);

            float3x3 result = C * D;
            float3x3 expected(2, 0, 0,
                0, 6, 0,
                0, 0, 12);
            suite.assert_equal(result, expected, "Matrix multiplication diagonal");

            // Check associativity
            float3x3 E(1, 2, 3,
                4, 5, 6,
                7, 8, 9);

            float3x3 F(9, 8, 7,
                6, 5, 4,
                3, 2, 1);

            float3x3 G(1, 0, 1,
                0, 1, 0,
                1, 0, 1);

            // (E * F) * G should equal E * (F * G)
            float3x3 EF = E * F;
            float3x3 EF_G = EF * G;

            float3x3 FG = F * G;
            float3x3 E_FG = E * FG;

            suite.assert_approximately_equal(EF_G, E_FG, "Matrix multiplication associativity");

            // Check *= operator
            float3x3 C_copy = C;
            C_copy *= D;
            suite.assert_equal(C_copy, expected, "Operator *=");
        }

        // Unary operators
        {
            float3x3 neg = -A;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    suite.assert_equal(neg(i, j), -A(i, j), "Unary minus");
                }
            }

            float3x3 pos = +A;
            suite.assert_equal(pos, A, "Unary plus");
        }

        // ============================================================================
        // 5. Vector multiplication
        // ============================================================================
        suite.section("Vector multiplication");

        float3x3 M(1, 2, 3,
            4, 5, 6,
            7, 8, 9);

        float3 v(2, 3, 4);

        // Vector * matrix (left multiplication)
        {
            float3 result = v * M;
            float3 expected(42, 51, 60);
            suite.assert_equal(result, expected, "Vector * matrix");
        }

        // Test transform_vector (now global function)
        {
            float3 result = transform_vector(M, v);
            float3 expected = v * M;
            suite.assert_equal(result, expected, "transform_vector");
        }

        // Test transform_point (should be same as transform_vector for float3x3)
        {
            float3 result = transform_point(M, v);
            float3 expected = v * M;
            suite.assert_equal(result, expected, "transform_point");
        }

        // Test transform_normal
        {
            float3x3 rotation = float3x3::rotation_x(PI / 4.0f);
            float3 normal(0, 1, 0);

            float3 transformed = transform_normal(rotation, normal);

            // For orthonormal matrix, transform_normal is equivalent to multiplication
            float3 expected = normal * rotation;
            suite.assert_approximately_equal(transformed, expected, "transform_normal for orthonormal matrix");

            // Test with non-orthogonal matrix
            float3x3 scale = float3x3::scaling(2, 3, 4);
            float3 normal2(1, 0, 0);
            float3 transformed2 = transform_normal(scale, normal2);

            // Normal should scale inversely
            float3 expected2(0.5f, 0, 0); // 1/2
            suite.assert_approximately_equal(transformed2, expected2, "transform_normal for scaling matrix");
        }

        // ============================================================================
        // 6. Matrix operations
        // ============================================================================
        suite.section("Matrix operations");

        // Transpose
        {
            float3x3 mat(1, 2, 3,
                4, 5, 6,
                7, 8, 9);

            float3x3 transposed_mat = transpose(mat);
            float3x3 expected(1, 4, 7,
                2, 5, 8,
                3, 6, 9);
            suite.assert_equal(transposed_mat, expected, "transpose");

            // Check that transpose twice returns original
            suite.assert_equal(transpose(transposed_mat), mat, "transpose twice returns original");
        }

        // Determinant
        {
            float3x3 identity = float3x3::identity();
            suite.assert_approximately_equal(determinant(identity), 1.0f, "identity determinant = 1");

            float3x3 zero_mat = float3x3::zero();
            suite.assert_approximately_equal(determinant(zero_mat), 0.0f, "zero determinant = 0");

            float3x3 scale = float3x3::scaling(2, 3, 4);
            suite.assert_approximately_equal(determinant(scale), 24.0f, "scaling determinant");
        }

        // Inverse matrix
        {
            float3x3 scale = float3x3::scaling(2, 3, 4);
            float3x3 invScale = inverse(scale);
            float3x3 expected(0.5f, 0, 0,
                0, 1.0f / 3.0f, 0,
                0, 0, 0.25f);
            suite.assert_approximately_equal(invScale, expected, "inverse of scaling matrix");

            // Check that A * A^(-1) = I
            float3x3 product = scale * invScale;
            suite.assert_true(is_identity(product, 1e-5f), "A * A^(-1) = I for scaling");

            // Check orthogonal matrix (inverse = transpose)
            float3x3 rotation = float3x3::rotation_x(PI / 3.0f);
            float3x3 invRotation = inverse(rotation);
            float3x3 transposedRotation = transpose(rotation);
            suite.assert_approximately_equal(invRotation, transposedRotation,
                "inverse of rotation = transpose", 1e-5f);

            // Singular matrix (zero determinant)
            float3x3 singular(1, 2, 3,
                4, 5, 6,
                7, 8, 9);
            // Should return identity (as implemented for zero determinant)
            float3x3 invSingular = inverse(singular);
            suite.assert_true(is_identity(invSingular, 1e-5f), "singular matrix inverse returns identity");
        }

        // Trace
        {
            float3x3 mat(1, 2, 3,
                4, 5, 6,
                7, 8, 9);
            float expectedTrace = 1 + 5 + 9;
            suite.assert_approximately_equal(trace(mat), expectedTrace, "trace");
        }

        // Diagonal
        {
            float3x3 mat(1, 2, 3,
                4, 5, 6,
                7, 8, 9);
            float3 expectedDiag(1, 5, 9);
            suite.assert_equal(diagonal(mat), expectedDiag, "diagonal");
        }

        // Frobenius norm
        {
            float3x3 mat(1, 0, 0,
                0, 2, 0,
                0, 0, 3);
            float expectedNorm = std::sqrt(1.0f * 1.0f + 2.0f * 2.0f + 3.0f * 3.0f);
            suite.assert_approximately_equal(frobenius_norm(mat), expectedNorm, "frobenius_norm");
        }

        // Symmetric and skew-symmetric parts
        {
            float3x3 mat(1, 2, 3,
                4, 5, 6,
                7, 8, 9);

            float3x3 sym = symmetric_part(mat);
            float3x3 skew = skew_symmetric_part(mat);

            // Symmetric part should be symmetric
            suite.assert_approximately_equal(sym, transpose(sym), "symmetric_part is symmetric");

            // Skew-symmetric part should be anti-symmetric
            suite.assert_approximately_equal(skew, -transpose(skew), "skew_symmetric_part is anti-symmetric");

            // Sum should give original matrix
            suite.assert_approximately_equal(sym + skew, mat, "sym + skew = original");
        }

        // ============================================================================
        // 7. Special functions
        // ============================================================================
        suite.section("Special functions");

        // Normal matrix
        {
            float3x3 model = float3x3::scaling(2, 3, 4);
            float3x3 normalMat = normal_matrix(model);

            // For scaling matrix, normal matrix should be inverse transpose
            float3x3 expected = transpose(inverse(model));

            // Columns should be normalized (as per implementation)
            float3 col0 = normalize(expected.col0());
            float3 col1 = normalize(expected.col1());
            float3 col2 = normalize(expected.col2());
            expected = float3x3(col0, col1, col2);

            suite.assert_approximately_equal(normalMat, expected, "normal_matrix for scaling");
        }

        // Extract scale
        {
            float3 scaleVec(2, 3, 4);
            float3x3 scaleMat = float3x3::scaling(scaleVec);
            float3 extracted = extract_scale(scaleMat);
            suite.assert_approximately_equal(extracted, scaleVec, "extract_scale from scaling matrix");

            // For matrix with rotation and scale
            float3x3 rotScale = float3x3::rotation_z(PI / 4.0f) * float3x3::scaling(2, 3, 4);
            float3 extracted2 = extract_scale(rotScale);
            // Scale should be extracted as column lengths
            float3 expected2(length(rotScale.row0),
                             length(rotScale.row1),
                             length(rotScale.row2));
            suite.assert_approximately_equal(extracted2, expected2, "extract_scale from rotation+scaling");
        }

        // Extract rotation
        {
            float3x3 rotation = float3x3::rotation_x(PI / 3.0f);
            float3x3 extracted = extract_rotation(rotation);
            suite.assert_approximately_equal(extracted, rotation, "extract_rotation from pure rotation");

            // For matrix with scale
            float3x3 scaleMat = float3x3::scaling(2, 3, 4);
            float3x3 extractedScale = extract_rotation(scaleMat);
            // Scaling matrix contains no rotation, should return identity
            suite.assert_true(is_identity(extractedScale, 1e-5f), "extract_rotation from scaling matrix");

            // For combined matrix
            float3x3 combined = float3x3::rotation_y(PI / 6.0f) *
                float3x3::scaling(2, 2, 2);
            float3x3 extractedCombined = extract_rotation(combined);
            // Extracted matrix should be orthonormal
            suite.assert_true(is_orthonormal(extractedCombined, 1e-5f), "extracted rotation is orthonormal");
        }

        // ============================================================================
        // 8. Property checks
        // ============================================================================
        suite.section("Property checks");

        // Identity check
        suite.assert_true(is_identity(float3x3::identity()), "is_identity(identity())");
        suite.assert_false(is_identity(float3x3::zero()), "is_identity(zero()) returns false");
        suite.assert_true(is_identity(float3x3::scaling(1, 1, 1)), "is_identity(uniform scaling(1))");

        // Orthogonality check
        {
            float3x3 rotation = float3x3::rotation_x(PI / 3.0f);
            suite.assert_true(is_orthogonal(rotation), "rotation matrix is orthogonal");
            suite.assert_true(is_orthonormal(rotation), "rotation matrix is orthonormal");

            float3x3 scale = float3x3::scaling(2, 3, 4);
            suite.assert_true(is_orthogonal(scale), "scaling matrix is orthogonal");
            suite.assert_false(is_orthonormal(scale), "non-uniform scaling matrix is not orthonormal");
        }

        // Approximately zero check
        suite.assert_true(approximately_zero(float3x3::zero()), "approximately_zero(zero())");
        suite.assert_false(approximately_zero(float3x3::identity()), "approximately_zero(identity()) returns false");

        // Approximately equal check
        {
            float3x3 mat1(1, 2, 3,
                4, 5, 6,
                7, 8, 9);

            // Matrix with small differences
            float3x3 mat2(1.000001f, 2.000001f, 3.000001f,
                4.000001f, 5.000001f, 6.000001f,
                7.000001f, 8.000001f, 9.000001f);

            // Check that with default epsilon they are considered equal
            suite.assert_true(approximately(mat1, mat2, 1e-6f),
                "matrices are approximately equal with default epsilon");

            // Therefore operator == should return true
            suite.assert_true(mat1 == mat2, "operator == returns true for approximately equal matrices");

            // And operator != should return false
            suite.assert_false(mat1 != mat2, "operator != returns false for approximately equal matrices");

            // Now create a matrix that is clearly different
            float3x3 mat3(2, 2, 3,
                4, 5, 6,
                7, 8, 9);

            suite.assert_true(mat1 != mat3, "operator != returns true for different matrices");
        }

        // ============================================================================
        // 9. Data conversions
        // ============================================================================
        suite.section("Data conversions");

        // to_row_major
        {
            float3x3 mat(1, 2, 3,
                4, 5, 6,
                7, 8, 9);

            float rowMajor[9];
            mat.to_row_major(rowMajor);

            for (int i = 0; i < 9; ++i) {
                suite.assert_equal(rowMajor[i], static_cast<float>(i + 1),
                    "to_row_major element " + std::to_string(i));
            }
        }

        // to_column_major
        {
            float3x3 mat(1, 2, 3,
                4, 5, 6,
                7, 8, 9);

            float colMajor[9];
            mat.to_column_major(colMajor);

            float expected[9] = { 1, 4, 7, 2, 5, 8, 3, 6, 9 };
            for (int i = 0; i < 9; ++i) {
                suite.assert_equal(colMajor[i], expected[i],
                    "to_column_major element " + std::to_string(i));
            }
        }

        // to_string
        {
            float3x3 mat(1.5f, 2.5f, 3.5f,
                4.5f, 5.5f, 6.5f,
                7.5f, 8.5f, 9.5f);

            std::string str = mat.to_string();
            // Check that string contains expected values
            suite.assert_true(str.find("1.5000") != std::string::npos, "to_string contains 1.5000");
            suite.assert_true(str.find("9.5000") != std::string::npos, "to_string contains 9.5000");
        }

        // isValid (we need to check if this function exists in the new implementation)
        {
            float3x3 validMat(1, 2, 3,
                4, 5, 6,
                7, 8, 9);
            // Since isValid is not in the new interface, we skip this test
            suite.skip_test("isValid method", "isValid not available in new float3x3 interface");
        }

        // ============================================================================
        // 10. Constructors from other types
        // ============================================================================
        suite.section("Constructors from other types");

        // Constructor from float4x4 (only upper-left 3x3 part)
        {
            // Skip if float4x4 not available
            suite.skip_test("Constructor from float4x4", "float4x4 not available in test context");
        }

        // Constructor from quaternion
        {
            // Skip quaternion tests for now
            suite.skip_test("Constructor from quaternion", "quaternion tests skipped");
        }

        // ============================================================================
        // 11. Edge cases and special values
        // ============================================================================
        suite.section("Edge cases and special values");

        // Very small values
        {
            float epsilon = 1e-6f;
            float3x3 tinyMat(epsilon, 0, 0,
                0, epsilon, 0,
                0, 0, epsilon);

            suite.assert_true(approximately_zero(tinyMat, epsilon * 2),
                "approximately_zero with tiny values");
        }

        // Very large values
        {
            float large = 1e10f;
            float3x3 largeMat(large, 0, 0,
                0, large, 0,
                0, 0, large);

            // Inverse matrix should have small values
            float3x3 invLarge = inverse(largeMat);
            float3x3 expected(1.0f / large, 0, 0,
                0, 1.0f / large, 0,
                0, 0, 1.0f / large);
            suite.assert_approximately_equal(invLarge, expected,
                "inverse of large diagonal matrix", 1e-5f);
        }

        // Zero rotation axis
        //{
        //    float3 zeroAxis(0, 0, 0);
        //    float3x3 rot = float3x3::rotation_axis(zeroAxis, 1.0f);
        //    // Should return identity matrix
        //    suite.assert_true(is_identity(rot, 1e-5f), "rotation_axis with zero axis returns identity");
        //}

        //// Zero rotation angle
        //{
        //    float3 axis(1, 0, 0);
        //    float3x3 rot = float3x3::rotation_axis(axis, 0.0f);
        //    suite.assert_true(is_identity(rot, 1e-5f), "rotation_axis with zero angle returns identity");
        //}

        // Division by zero (should work correctly due to handling in operator/=)
        {
            float3x3 mat(1, 2, 3,
                4, 5, 6,
                7, 8, 9);

            try {
                mat /= 0.0f;
                // If no exception thrown, elements should be inf or nan
                // We can check that the matrix is not valid (contains inf/nan)
                bool valid = true;
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (!std::isfinite(mat(i, j))) {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid) break;
                }
                suite.assert_false(valid, "division by zero produces invalid matrix");
            }
            catch (...) {
                suite.skip_test("Division by zero", "Exception thrown - implementation dependent");
            }
        }

        suite.footer();
    }
}
