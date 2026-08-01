// Author: DeepSeek
// Test suite for AfterMath::float4x4 class

#include "AutotestCore.h"

namespace AfterMathTests
{
    void RunFloat4x4Tests(TestSuite& suite)
    {
        using namespace AfterMath;

        // ============================================================================
        // 1. Constructors and basic operations
        // ============================================================================
        suite.section("Constructors and basic operations");

        // Test default constructor (identity matrix)
        suite.assert_equal(float4x4::identity(), float4x4(), "Default constructor returns identity");

        // Test constructor with 4 vectors
        {
            float4x4 mat(
                float4(1, 2, 3, 4),
                float4(5, 6, 7, 8),
                float4(9, 10, 11, 12),
                float4(13, 14, 15, 16)
            );
            suite.assert_equal(mat.row0, float4(1, 2, 3, 4), "Constructor from 4 vectors row0");
            suite.assert_equal(mat.row3, float4(13, 14, 15, 16), "Constructor from 4 vectors row3");
        }

        // Test constructor with 16 scalars
        {
            float4x4 mat(
                1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            suite.assert_equal(mat(0, 0), 1.0f, "Scalar constructor (0,0)");
            suite.assert_equal(mat(1, 1), 6.0f, "Scalar constructor (1,1)");
            suite.assert_equal(mat(2, 2), 11.0f, "Scalar constructor (2,2)");
            suite.assert_equal(mat(3, 3), 16.0f, "Scalar constructor (3,3)");
        }

        // Test constructor from array
        {
            float data[16] = {
                1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            };
            float4x4 mat(data);
            suite.assert_equal(mat[0][0], 1.0f, "Array constructor [0][0]");
            suite.assert_equal(mat[1][2], 7.0f, "Array constructor [1][2]");
            suite.assert_equal(mat[3][3], 16.0f, "Array constructor [3][3]");
        }

        // Test scalar constructor
        float4x4 scalarMat(5.0f);
        float4x4 expectedScaling = float4x4::scaling(5.0f);
        expectedScaling(3, 3) = 5.0f; // Scalar constructor sets (3,3) to 5
        suite.assert_equal(scalarMat, expectedScaling, "Scalar constructor creates matrix with scalar on diagonal");

        // Test constructor from diagonal
        {
            float4x4 mat(float4(2, 3, 4, 5));
            suite.assert_equal(mat(0, 0), 2.0f, "Diagonal constructor (0,0)");
            suite.assert_equal(mat(1, 1), 3.0f, "Diagonal constructor (1,1)");
            suite.assert_equal(mat(2, 2), 4.0f, "Diagonal constructor (2,2)");
            suite.assert_equal(mat(3, 3), 5.0f, "Diagonal constructor (3,3)");
            suite.assert_equal(mat(0, 1), 0.0f, "Diagonal constructor off-diagonal (0,1)");
        }

        // ============================================================================
        // 2. Element access
        // ============================================================================
        suite.section("Element access");

        float4x4 mat(
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
        );

        // Check [] operator
        suite.assert_equal(mat[0], float4(1, 2, 3, 4), "Operator[] row0");
        suite.assert_equal(mat[1], float4(5, 6, 7, 8), "Operator[] row1");
        suite.assert_equal(mat[2], float4(9, 10, 11, 12), "Operator[] row2");
        suite.assert_equal(mat[3], float4(13, 14, 15, 16), "Operator[] row3");

        // Check () operator
        suite.assert_equal(mat(0, 0), 1.0f, "Operator() (0,0)");
        suite.assert_equal(mat(1, 1), 6.0f, "Operator() (1,1)");
        suite.assert_equal(mat(2, 2), 11.0f, "Operator() (2,2)");
        suite.assert_equal(mat(3, 3), 16.0f, "Operator() (3,3)");
        suite.assert_equal(mat(1, 2), 7.0f, "Operator() (1,2)");
        suite.assert_equal(mat(3, 0), 13.0f, "Operator() (3,0)");

        // Check column access functions
        suite.assert_equal(mat.col0(), float4(1, 5, 9, 13), "col0()");
        suite.assert_equal(mat.col1(), float4(2, 6, 10, 14), "col1()");
        suite.assert_equal(mat.col2(), float4(3, 7, 11, 15), "col2()");
        suite.assert_equal(mat.col3(), float4(4, 8, 12, 16), "col3()");

        // Check set_col functions
        {
            float4x4 m;
            m.set_col0(float4(10, 11, 12, 13));
            m.set_col1(float4(14, 15, 16, 17));
            m.set_col2(float4(18, 19, 20, 21));
            m.set_col3(float4(22, 23, 24, 25));
            suite.assert_equal(m.col0(), float4(10, 11, 12, 13), "set_col0");
            suite.assert_equal(m.col1(), float4(14, 15, 16, 17), "set_col1");
            suite.assert_equal(m.col2(), float4(18, 19, 20, 21), "set_col2");
            suite.assert_equal(m.col3(), float4(22, 23, 24, 25), "set_col3");
        }

        // ============================================================================
        // 3. Static matrix creation methods
        // ============================================================================
        suite.section("Static matrix creation methods");

        // Identity and Zero
        suite.assert_true(is_identity(float4x4::identity()), "identity() creates identity matrix");
        suite.assert_true(approximately_zero(float4x4::zero()), "zero() creates zero matrix");

        // Translation matrix
        {
            float3 translation(2, 3, 4);
            float4x4 transMat = float4x4::translation(translation);

            // Check translation matrix structure
            suite.assert_true(is_affine(transMat), "translation matrix is affine");
            suite.assert_equal(get_translation(transMat), translation, "get_translation() returns correct translation");
            suite.assert_equal(transMat(3, 0), 2.0f, "translation matrix (3,0)");
            suite.assert_equal(transMat(3, 1), 3.0f, "translation matrix (3,1)");
            suite.assert_equal(transMat(3, 2), 4.0f, "translation matrix (3,2)");
            suite.assert_equal(transMat(3, 3), 1.0f, "translation matrix (3,3)");

            // Check that upper 3x3 part is identity
            suite.assert_equal(transMat(0, 0), 1.0f, "translation matrix rotation part (0,0)");
            suite.assert_equal(transMat(1, 1), 1.0f, "translation matrix rotation part (1,1)");
            suite.assert_equal(transMat(2, 2), 1.0f, "translation matrix rotation part (2,2)");
        }

        // Scaling matrix
        {
            float3 scale(2, 3, 4);
            float4x4 scaleMat = float4x4::scaling(scale);

            suite.assert_equal(get_scale(scaleMat), scale, "get_scale() returns correct scale");
            suite.assert_equal(scaleMat(0, 0), 2.0f, "scaling matrix (0,0)");
            suite.assert_equal(scaleMat(1, 1), 3.0f, "scaling matrix (1,1)");
            suite.assert_equal(scaleMat(2, 2), 4.0f, "scaling matrix (2,2)");
            suite.assert_equal(scaleMat(3, 3), 1.0f, "scaling matrix (3,3)");

            // Check uniform scaling
            float4x4 uniformScale = float4x4::scaling(5.0f);
            suite.assert_equal(get_scale(uniformScale), float3(5, 5, 5), "uniform scaling matrix");
        }

        // Rotation matrices
        {
            float angle = PI / 4.0f; // 45 degrees

            // Rotation around X
            float4x4 rotX = float4x4::rotation_x(angle);
            suite.assert_true(is_affine(rotX), "rotation_x creates affine matrix");
            suite.assert_approximately_equal(determinant(rotX), 1.0f, "rotation_x determinant = 1", 1e-6f);

            // Rotation around Y
            float4x4 rotY = float4x4::rotation_y(angle);
            suite.assert_true(is_affine(rotY), "rotation_y creates affine matrix");
            suite.assert_approximately_equal(determinant(rotY), 1.0f, "rotation_y determinant = 1", 1e-6f);

            // Rotation around Z
            float4x4 rotZ = float4x4::rotation_z(angle);
            suite.assert_true(is_affine(rotZ), "rotation_z creates affine matrix");
            suite.assert_approximately_equal(determinant(rotZ), 1.0f, "rotation_z determinant = 1", 1e-6f);

            // Check specific rotation
            float4x4 rotY90 = float4x4::rotation_y(PI / 2.0f);
            float3 point(1, 0, 0);
            float3 transformed = transform_point(rotY90, point);
            suite.assert_approximately_equal(transformed, float3(0, 0, -1), "rotation_y 90 degrees", 1e-5f);
        }

        // Rotation around arbitrary axis
        {
            float3 axis = normalize(float3(1, 1, 1));
            float angle = PI / 3.0f; // 60 degrees

            float4x4 rot = rotation_axis(axis, angle);
            suite.assert_true(is_affine(rot), "rotation_axis creates affine matrix");
            suite.assert_approximately_equal(determinant(rot), 1.0f, "rotation_axis determinant = 1", 1e-6f);

            // Rotation axis should be eigenvector
            float3 axisTransformed = transform_vector(rot, axis);
            suite.assert_approximately_equal(axisTransformed, axis, "rotation axis is eigenvector", 1e-5f);
        }

        // Euler angles
        {
            float3 angles(
                PI / 6.0f,  // 30° around X
                PI / 4.0f,  // 45° around Y
                PI / 3.0f   // 60° around Z
            );

            float4x4 eulerMat = float4x4::rotation_euler(angles);
            suite.assert_true(is_affine(eulerMat), "rotation_euler creates affine matrix");
            suite.assert_approximately_equal(determinant(eulerMat), 1.0f, "rotation_euler determinant = 1", 1e-6f);
        }

        // Projection matrices
        {
            float fov = PI / 3.0f; // 60 degrees
            float aspect = 16.0f / 9.0f;
            float zNear = 0.1f;
            float zFar = 100.0f;

            // Perspective projection
            float4x4 persp = float4x4::perspective(fov, aspect, zNear, zFar);
            suite.assert_false(is_affine(persp), "perspective matrix is not affine");
            suite.assert_not_equal(determinant(persp), 0.0f, "perspective matrix has non-zero determinant");

            // Orthographic projection
            float4x4 ortho = float4x4::orthographic(800.0f, 600.0f, 0.1f, 100.0f);
            suite.assert_true(is_affine(ortho), "orthographic matrix is affine");
        }

        // View matrix (look at)
        {
            float3 eye(0, 0, 5);
            float3 target(0, 0, 0);
            float3 up(0, 1, 0);

            float4x4 view = look_at(eye, target, up);
            suite.assert_true(is_affine(view), "look_at matrix is affine");

            // Point in space should transform correctly
            float3 worldPoint(1, 2, 3);
            float3 viewPoint = transform_point(view, worldPoint);

            // We don't know exact coordinates, but can check properties
            suite.assert_true(std::isfinite(viewPoint.x) && std::isfinite(viewPoint.y) && std::isfinite(viewPoint.z),
                "look_at transform produces finite coordinates");
        }

        // ============================================================================
        // 4. Arithmetic operations
        // ============================================================================
        suite.section("Arithmetic operations");

        float4x4 A(
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
        );

        float4x4 B(
            16, 15, 14, 13,
            12, 11, 10, 9,
            8, 7, 6, 5,
            4, 3, 2, 1
        );

        // Addition
        {
            float4x4 sum = A + B;
            float4x4 expected(
                17, 17, 17, 17,
                17, 17, 17, 17,
                17, 17, 17, 17,
                17, 17, 17, 17
            );
            suite.assert_equal(sum, expected, "Matrix addition");

            // Check += operator
            float4x4 A_copy = A;
            A_copy += B;
            suite.assert_equal(A_copy, expected, "Operator +=");
        }

        // Subtraction
        {
            float4x4 diff = A - B;
            float4x4 expected(
                -15, -13, -11, -9,
                -7, -5, -3, -1,
                1, 3, 5, 7,
                9, 11, 13, 15
            );
            suite.assert_equal(diff, expected, "Matrix subtraction");

            // Check -= operator
            float4x4 A_copy = A;
            A_copy -= B;
            suite.assert_equal(A_copy, expected, "Operator -=");
        }

        // Scalar multiplication
        {
            float4x4 scaled = A * 2.0f;
            float4x4 expected(
                2, 4, 6, 8,
                10, 12, 14, 16,
                18, 20, 22, 24,
                26, 28, 30, 32
            );
            suite.assert_equal(scaled, expected, "Matrix * scalar");

            // Check *= operator
            float4x4 A_copy = A;
            A_copy *= 2.0f;
            suite.assert_equal(A_copy, expected, "Operator *=");

            // Check scalar * matrix
            float4x4 scaled2 = 2.0f * A;
            suite.assert_equal(scaled2, expected, "Scalar * matrix");
        }

        // Scalar division
        {
            float4x4 A_copy = A;
            A_copy /= 2.0f;
            float4x4 expected(
                0.5f, 1.0f, 1.5f, 2.0f,
                2.5f, 3.0f, 3.5f, 4.0f,
                4.5f, 5.0f, 5.5f, 6.0f,
                6.5f, 7.0f, 7.5f, 8.0f
            );
            suite.assert_equal(A_copy, expected, "Operator /=");
        }

        // Matrix multiplication
        {
            // Diagonal matrices for simple verification
            float4x4 C = float4x4::scaling(2, 3, 4);
            float4x4 D = float4x4::scaling(3, 4, 5);

            float4x4 result = C * D;
            float4x4 expected = float4x4::scaling(6, 12, 20);
            suite.assert_approximately_equal(result, expected, "Matrix multiplication of scaling matrices", 1e-5f);

            // Check associativity (A*B)*C = A*(B*C)
            float4x4 E = float4x4::translation(1, 2, 3);
            float4x4 F = float4x4::rotation_x(PI / 6.0f);
            float4x4 G = float4x4::scaling(2, 2, 2);

            float4x4 EF = E * F;
            float4x4 EF_G = EF * G;

            float4x4 FG = F * G;
            float4x4 E_FG = E * FG;

            suite.assert_approximately_equal(EF_G, E_FG, "Matrix multiplication associativity", 1e-5f);

            // Check *= operator
            float4x4 C_copy = C;
            C_copy *= D;
            suite.assert_approximately_equal(C_copy, expected, "Operator *=", 1e-5f);
        }

        // Unary operators
        {
            float4x4 neg = -A;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    suite.assert_equal(neg(i, j), -A(i, j), "Unary minus element (" + std::to_string(i) + "," + std::to_string(j) + ")");
                }
            }

            float4x4 pos = +A;
            suite.assert_equal(pos, A, "Unary plus");
        }

        // ============================================================================
        // 5. Vector multiplication
        // ============================================================================
        suite.section("Vector multiplication");

        float4x4 M = float4x4::scaling(2, 3, 4) * float4x4::translation(1, 2, 3);
        float3 point(1, 1, 1);
        float3 vector(1, 0, 0);
        float4 homogPoint(1, 1, 1, 1);
        float4 homogVector(1, 0, 0, 0);

        // Point transformation
        {
            float3 transformed = transform_point(M, point);
            // Expected: point (1,1,1) scaled (2,3,4) => (2,3,4), then translated (1,2,3) => (3,5,7)
            float3 expected(3, 5, 7);
            suite.assert_approximately_equal(transformed, expected, "transform_point", 1e-5f);
        }

        // Vector transformation (no translation)
        {
            float3 transformed = transform_vector(M, vector);
            // Vector should not be translated, only scaled and rotated
            // In this case only scaling: (1,0,0) * 2 = (2,0,0)
            float3 expected(2, 0, 0);
            suite.assert_approximately_equal(transformed, expected, "transform_vector", 1e-5f);
        }

        // Direction transformation (normalized after transformation)
        {
            float3 direction(1, 0, 0);
            float3 transformed = transform_direction(M, direction);
            // Direction should be normalized after scaling
            float3 expected(1, 0, 0); // Scaling by 2, but normalization returns unit vector
            suite.assert_approximately_equal(transformed, expected, "transform_direction", 1e-5f);
        }

        // Homogeneous vector multiplication
        {
            float4 transformed = transform_vector(M, homogPoint);
            // Expected: (1,1,1,1) transforms to (3,5,7,1)
            float4 expected(3, 5, 7, 1);
            suite.assert_approximately_equal(transformed, expected, "transform_vector with homogeneous point", 1e-5f);

            float4 transformedVec = transform_vector(M, homogVector);
            // Vector with w=0 should not be translated
            float4 expectedVec(2, 0, 0, 0);
            suite.assert_approximately_equal(transformedVec, expectedVec, "transform_vector with homogeneous vector", 1e-5f);
        }

        // Operator * for vector and matrix
        {
            float3 result = point * M;  // Operator * uses transform_point
            float3 expected = transform_point(M, point);
            suite.assert_approximately_equal(result, expected, "point * matrix operator", 1e-5f);

            float4 result4 = homogPoint * M;  // Operator * uses transform_vector
            float4 expected4 = transform_vector(M, homogPoint);
            suite.assert_approximately_equal(result4, expected4, "float4 * matrix operator", 1e-5f);
        }

        // ============================================================================
        // 6. Matrix operations
        // ============================================================================
        suite.section("Matrix operations");

        // Transpose
        {
            float4x4 mat(
                1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );

            float4x4 transposed_mat = transpose(mat);
            float4x4 expected(
                1, 5, 9, 13,
                2, 6, 10, 14,
                3, 7, 11, 15,
                4, 8, 12, 16
            );
            suite.assert_equal(transposed_mat, expected, "transpose");

            // Check that transpose twice returns original
            suite.assert_equal(transpose(transposed_mat), mat, "transpose twice returns original");
        }

        // Determinant
        {
            float4x4 identity = float4x4::identity();
            suite.assert_approximately_equal(determinant(identity), 1.0f, "identity determinant = 1");

            float4x4 zero_mat = float4x4::zero();
            suite.assert_approximately_equal(determinant(zero_mat), 0.0f, "zero determinant = 0");

            float4x4 scale = float4x4::scaling(2, 3, 4);
            suite.assert_approximately_equal(determinant(scale), 24.0f, "scaling determinant");
        }

        // Inverse matrix (affine)
        {
            float4x4 affine = float4x4::translation(1, 2, 3) *
                float4x4::rotation_x(PI / 4.0f) *
                float4x4::scaling(2, 3, 4);

            float4x4 inverseAffine = inverse(affine);

            // Check that A * A^(-1) = I
            float4x4 product = affine * inverseAffine;
            suite.assert_true(is_identity(product, 1e-5f), "A * A^(-1) = I for affine matrix");

            // Check that A^(-1) * A = I
            float4x4 product2 = inverseAffine * affine;
            suite.assert_true(is_identity(product2, 1e-5f), "A^(-1) * A = I for affine matrix");
        }

        // Inverse matrix (full)
        {
            // Create non-affine matrix (projection)
            float4x4 persp = float4x4::perspective(
                PI / 3.0f,
                16.0f / 9.0f,
                0.1f,
                100.0f
            );

            float4x4 inversePersp = inverse(persp);

            // Check that determinant of product is close to 1
            float4x4 product = persp * inversePersp;
            suite.assert_approximately_equal(determinant(product), 1.0f, "perspective matrix inverse check", 1e-5f);
        }

        // Inverse affine matrix (optimized version)
        {
            // Note: We removed inverted_affine() method, using inverse() for all matrices
            // inverse() will use optimized path for affine matrices
            float4x4 affine = float4x4::translation(1, 2, 3) *
                float4x4::rotation_x(PI / 6.0f) *
                float4x4::scaling(2, 3, 4);

            float4x4 inv = inverse(affine);
            suite.assert_true(is_identity(affine * inv, 1e-5f), "inverse works for affine matrix");
        }

        // Adjugate matrix
        {
            float4x4 mat = float4x4::scaling(2, 3, 4);
            float4x4 adj = adjugate(mat);

            // For diagonal matrix, adjugate matrix is also diagonal
            float det = determinant(mat); // 2*3*4*1 = 24

            // Cofactors for diagonal matrix:
            // (0,0): 3*4*1 = 12
            // (1,1): 2*4*1 = 8
            // (2,2): 2*3*1 = 6
            // (3,3): 2*3*4 = 24

            // Check diagonal elements
            suite.assert_approximately_equal(adj(0, 0), 12.0f, "adjugate (0,0)", 1e-5f);
            suite.assert_approximately_equal(adj(1, 1), 8.0f, "adjugate (1,1)", 1e-5f);
            suite.assert_approximately_equal(adj(2, 2), 6.0f, "adjugate (2,2)", 1e-5f);
            suite.assert_approximately_equal(adj(3, 3), 24.0f, "adjugate (3,3)", 1e-5f);

            // Check that off-diagonal elements are 0
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (i != j) {
                        suite.assert_approximately_equal(adj(i, j), 0.0f,
                            "adjugate off-diagonal (" + std::to_string(i) + "," + std::to_string(j) + ")", 1e-5f);
                    }
                }
            }
        }

        // Trace
        {
            float4x4 mat(
                1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            float expectedTrace = 1 + 6 + 11 + 16;
            suite.assert_approximately_equal(trace(mat), expectedTrace, "trace");
        }

        // Diagonal
        {
            float4x4 mat(
                1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            float4 expectedDiag(1, 6, 11, 16);
            suite.assert_equal(diagonal(mat), expectedDiag, "diagonal");
        }

        // Frobenius norm
        {
            float4x4 mat = float4x4::scaling(2, 3, 4);
            float expectedNorm = std::sqrt(2.0f * 2.0f + 3.0f * 3.0f + 4.0f * 4.0f + 1.0f * 1.0f); // Diagonal elements: 2,3,4,1
            suite.assert_approximately_equal(frobenius_norm(mat), expectedNorm, "frobenius_norm", 1e-5f);
        }

        // ============================================================================
        // 7. Special functions
        // ============================================================================
        suite.section("Special functions");

        // Getting and setting translation
        {
            float3 translation(5, 6, 7);
            float4x4 mat = float4x4::translation(translation);
            suite.assert_equal(get_translation(mat), translation, "get_translation");

            suite.assert_equal(mat(3, 0), 5.0f, "translation sets (3,0)");
            suite.assert_equal(mat(3, 1), 6.0f, "translation sets (3,1)");
            suite.assert_equal(mat(3, 2), 7.0f, "translation sets (3,2)");

            // Make sure rest of matrix didn't change
            suite.assert_true(is_affine(mat), "matrix remains affine after setting translation");
            suite.assert_equal(mat(0, 0), 1.0f, "translation doesn't affect (0,0)");
        }

        // Getting scale
        {
            float3 scale(2, 3, 4);
            float4x4 mat = float4x4::scaling(scale) * float4x4::rotation_z(PI / 4.0f);

            float3 extractedScale = get_scale(mat);
            suite.assert_approximately_equal(extractedScale, scale, "get_scale", 1e-5f);

            // Check that matrix remains affine
            suite.assert_true(is_affine(mat), "matrix remains affine");
        }

        // ============================================================================
        // 8. Property checks
        // ============================================================================
        suite.section("Property checks");

        // Identity check
        suite.assert_true(is_identity(float4x4::identity()), "is_identity(identity())");
        suite.assert_false(is_identity(float4x4::zero()), "is_identity(zero()) returns false");
        suite.assert_true(is_identity(float4x4::scaling(1, 1, 1)), "is_identity(uniform scaling(1))");

        // Affine check
        {
            float4x4 affine = float4x4::translation(1, 2, 3);
            suite.assert_true(is_affine(affine), "translation matrix is affine");

            float4x4 nonAffine = float4x4::perspective(PI / 3, 1.0f, 0.1f, 100.0f);
            suite.assert_false(is_affine(nonAffine), "perspective matrix is not affine");
        }

        // Orthogonality check
        {
            float4x4 rotation = float4x4::rotation_x(PI / 3.0f);
            suite.assert_true(is_orthogonal(rotation), "rotation matrix is orthogonal");

            float4x4 scale = float4x4::scaling(2, 3, 4);
            suite.assert_false(is_orthogonal(scale), "non-uniform scaling matrix is not orthogonal");

            float4x4 uniformScale = float4x4::scaling(2);
            suite.assert_false(is_orthogonal(uniformScale), "uniform scaling matrix is not orthogonal (length != 1)");
        }

        // Approximately zero check
        suite.assert_true(approximately_zero(float4x4::zero()), "approximately_zero(zero())");
        suite.assert_false(approximately_zero(float4x4::identity()), "approximately_zero(identity()) returns false");

        // Approximately equal check
        {
            float4x4 mat1 = float4x4::identity();
            float4x4 mat2 = float4x4::identity();
            mat2(0, 0) = 1.000001f;

            suite.assert_true(approximately(mat1, mat2, 1e-4f), "approximately with epsilon");
            suite.assert_false(approximately(mat1, mat2, 1e-7f), "approximately with strict epsilon fails");

            // Check operators == and !=
            suite.assert_true(mat1 == mat1, "operator == for identical matrices");

            // For small differences operator == should return true (uses default epsilon)
            if (approximately(mat1, mat2)) {
                suite.assert_true(mat1 == mat2, "operator == returns true for approximately equal matrices");
                suite.assert_false(mat1 != mat2, "operator != returns false for approximately equal matrices");
            }

            // For clearly different matrices
            float4x4 mat3 = float4x4::scaling(2);
            suite.assert_true(mat1 != mat3, "operator != returns true for different matrices");
        }

        // ============================================================================
        // 9. Data conversions
        // ============================================================================
        suite.section("Data conversions");

        // to_row_major
        {
            float4x4 mat(
                1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );

            float rowMajor[16];
            mat.to_row_major(rowMajor);

            for (int i = 0; i < 16; ++i) {
                suite.assert_equal(rowMajor[i], static_cast<float>(i + 1),
                    "to_row_major element " + std::to_string(i));
            }
        }

        // to_column_major
        {
            float4x4 mat(
                1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );

            float colMajor[16];
            mat.to_column_major(colMajor);

            // Column-major order: all elements of first column, then second, etc.
            float expected[16] = { 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16 };
            for (int i = 0; i < 16; ++i) {
                suite.assert_equal(colMajor[i], expected[i],
                    "to_column_major element " + std::to_string(i));
            }
        }

        // to_string
        {
            float4x4 mat = float4x4::identity();
            std::string str = mat.to_string();

            // Check that string contains expected values
            suite.assert_true(str.find("1.0000") != std::string::npos, "to_string contains 1.0000");
            suite.assert_true(str.find("0.0000") != std::string::npos, "to_string contains 0.0000");
        }

        // ============================================================================
        // 10. Edge cases and special values
        // ============================================================================
        suite.section("Edge cases and special values");

        // Very small values
        {
            float epsilon = 1e-6f;
            float4x4 tinyMat(epsilon);

            suite.assert_true(approximately_zero(tinyMat, epsilon * 2),
                "approximately_zero with tiny values");
        }

        // Very large values
        {
            float large = 1e10f;
            float4x4 largeMat = float4x4::scaling(large);

            // Inverse matrix should have small values
            float4x4 invLarge = inverse(largeMat);
            float4x4 expected = float4x4::scaling(1.0f / large);
            suite.assert_approximately_equal(invLarge, expected,
                "inverse of large scaling matrix", 1e-5f);
        }

        // Degenerate matrix (zero scale)
        {
            float4x4 degenerate = float4x4::scaling(0, 1, 1);

            // Determinant should be 0
            suite.assert_approximately_equal(determinant(degenerate), 0.0f, "degenerate matrix has zero determinant");

            // Inverse matrix should return identity (as implemented for zero determinant)
            float4x4 invDegenerate = inverse(degenerate);
            suite.assert_true(is_identity(invDegenerate, 1e-5f), "degenerate matrix inverse returns identity");
        }

        // Zero rotation axis
        {
            float3 zeroAxis(0, 0, 0);
            float4x4 rot = rotation_axis(zeroAxis, 1.0f);
            // Should return identity matrix
            suite.assert_true(is_identity(rot, 1e-5f), "rotation_axis with zero axis returns identity");
        }

        // Zero rotation angle
        {
            float3 axis(1, 0, 0);
            float4x4 rot = rotation_axis(axis, 0.0f);
            suite.assert_true(is_identity(rot, 1e-5f), "rotation_axis with zero angle returns identity");
        }

        // Division by zero
        {
            float4x4 mat = float4x4::identity();

            try {
                mat /= 0.0f;
                // If no exception thrown, elements should be inf or nan
                // Check that matrix is invalid
                bool hasInfOrNaN = false;
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        if (!std::isfinite(mat(i, j))) {
                            hasInfOrNaN = true;
                            break;
                        }
                    }
                    if (hasInfOrNaN) break;
                }
                suite.assert_true(hasInfOrNaN, "division by zero produces inf/nan values");
            }
            catch (...) {
                suite.skip_test("Division by zero", "Exception thrown - implementation dependent");
            }
        }

        // ============================================================================
        // 11. Projection matrices (detailed tests)
        // ============================================================================
        suite.section("Projection matrices");

        // Perspective projection (left/right, zero/reverse depth)
        {
            float fov = PI / 3.0f;
            float aspect = 16.0f / 9.0f;
            float zNear = 0.1f;
            float zFar = 100.0f;

            // LH ZO (left, zero depth)
            float4x4 perspLHZO = float4x4::perspective_lh_zo(fov, aspect, zNear, zFar);

            // Check that near plane projects to 0
            float4 nearPoint(0, 0, zNear, 1);
            float4 projectedNear = transform_vector(perspLHZO, nearPoint);
            projectedNear /= projectedNear.w;
            suite.assert_approximately_equal(projectedNear.z, 0.0f, "LH ZO: near plane projects to 0", 1e-5f);

            // Check that far plane projects to 1
            float4 farPoint(0, 0, zFar, 1);
            float4 projectedFar = transform_vector(perspLHZO, farPoint);
            projectedFar /= projectedFar.w;
            suite.assert_approximately_equal(projectedFar.z, 1.0f, "LH ZO: far plane projects to 1", 1e-5f);
        }

        // Orthographic projection
        {
            float width = 800.0f;
            float height = 600.0f;
            float zNear = 0.1f;
            float zFar = 100.0f;

            float4x4 ortho = float4x4::orthographic(width, height, zNear, zFar);

            // Points on near and far planes should have same X,Y coordinates
            float4 nearPoint(-width / 2, -height / 2, zNear, 1);
            float4 farPoint(-width / 2, -height / 2, zFar, 1);

            float4 projectedNear = transform_vector(ortho, nearPoint);
            float4 projectedFar = transform_vector(ortho, farPoint);

            suite.assert_approximately_equal(projectedNear.x, -1.0f, "ortho: left edge projects to -1", 1e-5f);
            suite.assert_approximately_equal(projectedNear.y, -1.0f, "ortho: bottom edge projects to -1", 1e-5f);
            suite.assert_approximately_equal(projectedFar.z, 1.0f, "ortho: far plane projects to 1", 1e-5f);
        }
    }
}
