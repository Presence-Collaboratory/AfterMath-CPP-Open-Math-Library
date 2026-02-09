// Author: DeepSeek, NSDeathman
// Test suite for AfterMath::half3 class

#include "AutotestCore.h"
#include "../AfterMath/math_constants.h"

namespace AfterMathTests
{
    void RunHalf3Tests()
    {
        TestSuite suite("half3 Tests", true);
        suite.header();

        using namespace AfterMath;

        // Константы для half-тестов
        constexpr float HALF_EPSILON = 0.002f;        // Общая точность half
        constexpr float HALF_MATH_EPSILON = 2e-3f;   // Математические функции
        constexpr float HALF_ANGLE_EPSILON = 0.2f;   // Тригонометрия
        constexpr float HALF_LARGE_EPSILON = 0.5f;   // Большие значения

        // ============================================================================
        // 1. Конструкторы
        // ============================================================================
        suite.section("Конструкторы");

        // Тест конструктора по умолчанию
        {
            half3 v;
            suite.assert_approximately_equal(float(v.x), 0.0f, "Default constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 0.0f, "Default constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 0.0f, "Default constructor z", HALF_EPSILON);
        }

        // Тест конструктора с half компонентами
        {
            half3 v(half(1.5f), half(2.5f), half(3.5f));
            suite.assert_approximately_equal(float(v.x), 1.5f, "Half component constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Half component constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.5f, "Half component constructor z", HALF_EPSILON);
        }

        // Тест конструктора с float компонентами
        {
            half3 v(1.5f, 2.5f, 3.5f);
            suite.assert_approximately_equal(float(v.x), 1.5f, "Float component constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Float component constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.5f, "Float component constructor z", HALF_EPSILON);
        }

        // Тест конструктора со скаляром (half)
        {
            half3 v(half(3.0f));
            suite.assert_approximately_equal(float(v.x), 3.0f, "Half scalar constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Half scalar constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "Half scalar constructor z", HALF_EPSILON);
        }

        // Тест конструктора со скаляром (float)
        {
            half3 v(3.0f);
            suite.assert_approximately_equal(float(v.x), 3.0f, "Float scalar constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 3.0f, "Float scalar constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "Float scalar constructor z", HALF_EPSILON);
        }

        // Тест конструктора из float3
        {
            float3 fv(4.0f, 5.0f, 6.0f);
            half3 v(fv);
            suite.assert_approximately_equal(float(v.x), 4.0f, "float3 constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 5.0f, "float3 constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 6.0f, "float3 constructor z", HALF_EPSILON);
        }

        // Тест конструктора из half2 и z компонента
        {
            half2 xy(1.0f, 2.0f);
            half3 v(xy, half(3.0f));
            suite.assert_approximately_equal(float(v.x), 1.0f, "half2 + z constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.0f, "half2 + z constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "half2 + z constructor z", HALF_EPSILON);
        }

        // Тест конструктора из float2 и z компонента
        {
            float2 xy(1.0f, 2.0f);
            half3 v(xy, 3.0f);
            suite.assert_approximately_equal(float(v.x), 1.0f, "float2 + z constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.0f, "float2 + z constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "float2 + z constructor z", HALF_EPSILON);
        }

        // Тест копирующего конструктора
        {
            half3 original(6.0f, 7.0f, 8.0f);
            half3 copy(original);
            suite.assert_approximately_equal(float(copy.x), 6.0f, "Copy constructor x", HALF_EPSILON);
            suite.assert_approximately_equal(float(copy.y), 7.0f, "Copy constructor y", HALF_EPSILON);
            suite.assert_approximately_equal(float(copy.z), 8.0f, "Copy constructor z", HALF_EPSILON);
        }

        // Тест статических конструкторов
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
        // 2. Операторы присваивания
        // ============================================================================
        suite.section("Операторы присваивания");

        // Тест присваивания half скаляра
        {
            half3 v;
            v = half(2.5f);
            suite.assert_approximately_equal(float(v.x), 2.5f, "Half scalar assignment x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Half scalar assignment y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 2.5f, "Half scalar assignment z", HALF_EPSILON);
        }

        // Тест присваивания float скаляра
        {
            half3 v;
            v = 2.5f;
            suite.assert_approximately_equal(float(v.x), 2.5f, "Float scalar assignment x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 2.5f, "Float scalar assignment y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 2.5f, "Float scalar assignment z", HALF_EPSILON);
        }

        // Тест присваивания float3
        {
            half3 v;
            float3 fv(3.5f, 4.5f, 5.5f);
            v = fv;
            suite.assert_approximately_equal(float(v.x), 3.5f, "float3 assignment x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.5f, "float3 assignment y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 5.5f, "float3 assignment z", HALF_EPSILON);
        }

        // Тест составных операторов присваивания (half3)
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

        // Тест составных операторов присваивания (скаляры)
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
        // 3. Бинарные операторы
        // ============================================================================
        suite.section("Бинарные операторы");

        // Тест сложения
        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 b(3.0f, 4.0f, 5.0f);
            half3 result = a + b;
            suite.assert_approximately_equal(float(result.x), 4.0f, "Operator + x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 6.0f, "Operator + y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 8.0f, "Operator + z", HALF_EPSILON);
        }

        // Тест вычитания
        {
            half3 a(5.0f, 6.0f, 7.0f);
            half3 b(2.0f, 3.0f, 4.0f);
            half3 result = a - b;
            suite.assert_approximately_equal(float(result.x), 3.0f, "Operator - x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 3.0f, "Operator - y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 3.0f, "Operator - z", HALF_EPSILON);
        }

        // Тест унарных операторов
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

        // Тест скалярных операций (half)
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

        // Тест скалярных операций (float)
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

        // Тест операций с float3
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
        // 4. Операторы доступа и преобразования
        // ============================================================================
        suite.section("Операторы доступа и преобразования");

        // Тест оператора индексации
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

        // Тест преобразования в float3
        {
            half3 v(1.5f, 2.5f, 3.5f);
            float3 fv = float3(v);
            suite.assert_approximately_equal(fv.x, 1.5f, "Conversion to float3 x", HALF_EPSILON);
            suite.assert_approximately_equal(fv.y, 2.5f, "Conversion to float3 y", HALF_EPSILON);
            suite.assert_approximately_equal(fv.z, 3.5f, "Conversion to float3 z", HALF_EPSILON);
        }

        // Тест to_float3 функции
        {
            half3 v(3.0f, 4.0f, 5.0f);
            float3 fv = to_float3(v);
            suite.assert_approximately_equal(fv.x, 3.0f, "to_float3 x", HALF_EPSILON);
            suite.assert_approximately_equal(fv.y, 4.0f, "to_float3 y", HALF_EPSILON);
            suite.assert_approximately_equal(fv.z, 5.0f, "to_float3 z", HALF_EPSILON);
        }

        // Тест to_half3 функции
        {
            float3 fv(3.0f, 4.0f, 5.0f);
            half3 v = to_half3(fv);
            suite.assert_approximately_equal(float(v.x), 3.0f, "to_half3 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 4.0f, "to_half3 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 5.0f, "to_half3 z", HALF_EPSILON);
        }

        // ============================================================================
        // 5. Математические функции
        // ============================================================================
        suite.section("Математические функции");

        // Тест длины
        {
            half3 v(2.0f, 3.0f, 6.0f);
            half len = v.length();
            half len_sq = v.length_sq();

            // sqrt(4 + 9 + 36) = sqrt(49) = 7
            suite.assert_approximately_equal(float(len), 7.0f, "length()", HALF_EPSILON);
            suite.assert_approximately_equal(float(len_sq), 49.0f, "length_sq()", HALF_EPSILON);

            half3 zero(0.0f, 0.0f, 0.0f);
            suite.assert_approximately_equal(float(zero.length()), 0.0f, "length() of zero vector", HALF_EPSILON);
        }

        // Тест нормализации
        {
            half3 v(2.0f, 3.0f, 6.0f);
            half3 normalized = v.normalize();
            float normalized_len = float(normalized.length());

            // (2/7, 3/7, 6/7) ≈ (0.2857, 0.4286, 0.8571)
            suite.assert_approximately_equal(normalized_len, 1.0f, "normalize() length", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.x), 2.0f / 7.0f, "normalize() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.y), 3.0f / 7.0f, "normalize() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.z), 6.0f / 7.0f, "normalize() z", HALF_EPSILON);

            // Тест нормализации нулевого вектора
            half3 zero(0.0f, 0.0f, 0.0f);
            half3 zero_norm = zero.normalize();
            suite.assert_approximately_equal(float(zero_norm.x), 0.0f, "normalize() zero vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero_norm.y), 0.0f, "normalize() zero vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(zero_norm.z), 0.0f, "normalize() zero vector z", HALF_EPSILON);
        }

        // Тест скалярного произведения
        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 b(4.0f, 5.0f, 6.0f);
            half dot_result = a.dot(b);
            suite.assert_approximately_equal(float(dot_result), 32.0f, "dot()", HALF_EPSILON);

            // Статический метод dot
            half static_dot = half3::dot(a, b);
            suite.assert_approximately_equal(float(static_dot), 32.0f, "half3::dot()", HALF_EPSILON);

            // Глобальная функция dot
            half global_dot = dot(a, b);
            suite.assert_approximately_equal(float(global_dot), 32.0f, "global dot()", HALF_EPSILON);

            // Ортогональные векторы
            half3 orth1(1.0f, 0.0f, 0.0f);
            half3 orth2(0.0f, 1.0f, 0.0f);
            half orth_dot = orth1.dot(orth2);
            suite.assert_approximately_equal(float(orth_dot), 0.0f, "dot() orthogonal vectors", HALF_EPSILON);
        }

        // Тест векторного произведения
        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 b(4.0f, 5.0f, 6.0f);
            half3 cross_result = a.cross(b);

            // (2*6 - 3*5, 3*4 - 1*6, 1*5 - 2*4) = (12-15, 12-6, 5-8) = (-3, 6, -3)
            suite.assert_approximately_equal(float(cross_result.x), -3.0f, "cross() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_result.y), 6.0f, "cross() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_result.z), -3.0f, "cross() z", HALF_EPSILON);

            // Статический метод cross
            half3 static_cross = half3::cross(a, b);
            suite.assert_approximately_equal(float(static_cross.x), -3.0f, "half3::cross() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(static_cross.y), 6.0f, "half3::cross() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(static_cross.z), -3.0f, "half3::cross() z", HALF_EPSILON);

            // Глобальная функция cross
            half3 global_cross = cross(a, b);
            suite.assert_approximately_equal(float(global_cross.x), -3.0f, "global cross() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_cross.y), 6.0f, "global cross() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_cross.z), -3.0f, "global cross() z", HALF_EPSILON);
        }

        // Тест расстояния
        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 b(4.0f, 6.0f, 8.0f);
            half dist = a.distance(b);
            half dist_sq = a.distance_sq(b);

            // (4-1)² + (6-2)² + (8-3)² = 9 + 16 + 25 = 50
            suite.assert_approximately_equal(float(dist), std::sqrt(50.0f), "distance()", HALF_EPSILON);
            suite.assert_approximately_equal(float(dist_sq), 50.0f, "distance_sq()", HALF_EPSILON);

            // Глобальные функции distance и distance_sq
            half global_distance = distance(a, b);
            half global_distance_sq = distance_sq(a, b);
            suite.assert_approximately_equal(float(global_distance), std::sqrt(50.0f), "global distance()", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_distance_sq), 50.0f, "global distance_sq()", HALF_EPSILON);
        }

        // ============================================================================
        // 6. HLSL-подобные функции
        // ============================================================================
        suite.section("HLSL-подобные функции");

        // Тест abs
        {
            half3 v(-1.5f, 2.5f, -3.5f);
            half3 result = v.abs();
            half3 global_result = abs(v);

            suite.assert_approximately_equal(float(result.x), 1.5f, "abs() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 2.5f, "abs() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 3.5f, "abs() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.x), 1.5f, "global abs() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.y), 2.5f, "global abs() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.z), 3.5f, "global abs() z", HALF_EPSILON);
        }

        // Тест sign
        {
            half3 v(-2.0f, 0.0f, 3.0f);
            half3 result = v.sign();
            half3 global_result = sign(v);

            suite.assert_approximately_equal(float(result.x), -1.0f, "sign() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.0f, "sign() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 1.0f, "sign() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.x), -1.0f, "global sign() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.y), 0.0f, "global sign() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.z), 1.0f, "global sign() z", HALF_EPSILON);
        }

        // Тест floor
        {
            half3 v(1.7f, -2.3f, 3.1f);
            half3 result = v.floor();
            half3 global_result = floor(v);

            suite.assert_approximately_equal(float(result.x), 1.0f, "floor() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), -3.0f, "floor() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 3.0f, "floor() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.x), 1.0f, "global floor() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.y), -3.0f, "global floor() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.z), 3.0f, "global floor() z", HALF_EPSILON);
        }

        // Тест ceil
        {
            half3 v(1.2f, -2.7f, 3.9f);
            half3 result = v.ceil();
            half3 global_result = ceil(v);

            suite.assert_approximately_equal(float(result.x), 2.0f, "ceil() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), -2.0f, "ceil() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 4.0f, "ceil() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.x), 2.0f, "global ceil() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.y), -2.0f, "global ceil() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.z), 4.0f, "global ceil() z", HALF_EPSILON);
        }

        // Тест round
        {
            half3 v(1.4f, 1.6f, -1.5f);
            half3 result = v.round();
            half3 global_result = round(v);

            suite.assert_approximately_equal(float(result.x), 1.0f, "round() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 2.0f, "round() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), -2.0f, "round() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.x), 1.0f, "global round() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.y), 2.0f, "global round() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.z), -2.0f, "global round() z", HALF_EPSILON);
        }

        // Тест frac (HLSL-семантика)
        {
            half3 v(1.7f, -2.3f, 3.0f);
            half3 result = v.frac();
            half3 global_result = frac(v);

            // HLSL: frac(x) = x - floor(x)
            // frac(1.7) = 1.7 - 1.0 = 0.7
            // frac(-2.3) = -2.3 - (-3.0) = 0.7
            // frac(3.0) = 3.0 - 3.0 = 0.0
            suite.assert_approximately_equal(float(result.x), 0.7f, "frac() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.7f, "frac() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 0.0f, "frac() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.x), 0.7f, "global frac() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.y), 0.7f, "global frac() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.z), 0.0f, "global frac() z", HALF_EPSILON);
        }

        // Тест saturate
        {
            half3 v(-0.5f, 0.5f, 1.5f);
            half3 result = v.saturate();
            half3 static_result = half3::saturate(v);
            half3 global_result = saturate(v);

            suite.assert_approximately_equal(float(result.x), 0.0f, "saturate() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.5f, "saturate() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 1.0f, "saturate() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(static_result.x), 0.0f, "half3::saturate() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(static_result.y), 0.5f, "half3::saturate() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(static_result.z), 1.0f, "half3::saturate() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.x), 0.0f, "global saturate() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.y), 0.5f, "global saturate() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.z), 1.0f, "global saturate() z", HALF_EPSILON);
        }

        // Тест step
        {
            half3 v(0.5f, 1.0f, 1.5f);
            half3 result = v.step(half(1.0f));
            half3 global_result = step(half(1.0f), v);

            suite.assert_approximately_equal(float(result.x), 0.0f, "step() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 1.0f, "step() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 1.0f, "step() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.x), 0.0f, "global step() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.y), 1.0f, "global step() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_result.z), 1.0f, "global step() z", HALF_EPSILON);
        }

        // Тест smoothstep
        {
            half3 v(0.5f, 1.5f, 2.5f);
            half3 result = smoothstep(half(0.0f), half(2.0f), v);

            // Для t=0.25: 3t² - 2t³ = 3*0.0625 - 2*0.015625 = 0.1875 - 0.03125 = 0.15625
            // Для t=0.75: 3*0.5625 - 2*0.421875 = 1.6875 - 0.84375 = 0.84375
            // Для t=1.25: clamp до [0,1], но t>1 => 1.0
            suite.assert_approximately_equal(float(result.x), 0.15625f, "smoothstep() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), 0.84375f, "smoothstep() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), 1.0f, "smoothstep() z", HALF_EPSILON);
        }

        // Тест min/max
        {
            half3 a(1.0f, 3.0f, 5.0f);
            half3 b(2.0f, 2.0f, 6.0f);

            half3 min_result = half3::min(a, b);
            half3 max_result = half3::max(a, b);
            half3 global_min = min(a, b);
            half3 global_max = max(a, b);

            suite.assert_approximately_equal(float(min_result.x), 1.0f, "half3::min() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(min_result.y), 2.0f, "half3::min() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(min_result.z), 5.0f, "half3::min() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(max_result.x), 2.0f, "half3::max() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(max_result.y), 3.0f, "half3::max() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(max_result.z), 6.0f, "half3::max() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_min.x), 1.0f, "global min() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_min.y), 2.0f, "global min() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_min.z), 5.0f, "global min() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_max.x), 2.0f, "global max() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_max.y), 3.0f, "global max() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_max.z), 6.0f, "global max() z", HALF_EPSILON);
        }

        // Тест clamp
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
        // 7. Геометрические операции
        // ============================================================================
        suite.section("Геометрические операции");

        // Тест отражения
        {
            half3 incident(1.0f, -1.0f, 0.0f);
            half3 normal(0.0f, 1.0f, 0.0f);
            half3 reflected = incident.reflect(normal);
            half3 static_reflected = half3::reflect(incident, normal);
            half3 global_reflected = reflect(incident, normal);

            // Ожидаем (1.0f, 1.0f, 0.0f) для зеркального отражения
            suite.assert_approximately_equal(float(reflected.x), 1.0f, "reflect() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(reflected.y), 1.0f, "reflect() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(reflected.z), 0.0f, "reflect() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(static_reflected.x), 1.0f, "half3::reflect() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(static_reflected.y), 1.0f, "half3::reflect() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(static_reflected.z), 0.0f, "half3::reflect() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_reflected.x), 1.0f, "global reflect() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_reflected.y), 1.0f, "global reflect() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_reflected.z), 0.0f, "global reflect() z", HALF_EPSILON);
        }

        // Тест преломления
        {
            half3 incident(1.0f, -1.0f, 0.0f);
            half3 normal(0.0f, 1.0f, 0.0f);
            half eta(0.9f);  // Коэффициент преломления меньше 1

            half3 refracted = incident.refract(normal, eta);
            half3 static_refracted = half3::refract(incident, normal, eta);
            half3 global_refracted = refract(incident, normal, eta);

            // Проверяем, что результат имеет ожидаемое направление
            // (точные значения могут зависеть от реализации)
            suite.assert_true(refracted.is_finite(), "refract() returns finite vector");
            suite.assert_true(static_refracted.is_finite(), "half3::refract() returns finite vector");
            suite.assert_true(global_refracted.is_finite(), "global refract() returns finite vector");
        }

        // Тест проекции
        {
            half3 v(3.0f, 4.0f, 0.0f);
            half3 onto(1.0f, 0.0f, 0.0f);
            half3 projected = v.project(onto);
            half3 global_projected = project(v, onto);

            // Проекция (3,4,0) на (1,0,0) = (3,0,0)
            suite.assert_approximately_equal(float(projected.x), 3.0f, "project() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.y), 0.0f, "project() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.z), 0.0f, "project() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_projected.x), 3.0f, "global project() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_projected.y), 0.0f, "global project() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_projected.z), 0.0f, "global project() z", HALF_EPSILON);
        }

        // Тест отклонения
        {
            half3 v(3.0f, 4.0f, 0.0f);
            half3 from(1.0f, 0.0f, 0.0f);
            half3 rejected = v.reject(from);
            half3 global_rejected = reject(v, from);

            // Отклонение (3,4,0) от (1,0,0) = (0,4,0)
            suite.assert_approximately_equal(float(rejected.x), 0.0f, "reject() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(rejected.y), 4.0f, "reject() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(rejected.z), 0.0f, "reject() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_rejected.x), 0.0f, "global reject() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_rejected.y), 4.0f, "global reject() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_rejected.z), 0.0f, "global reject() z", HALF_EPSILON);
        }

        // Тест угла между векторами
        {
            half3 a(1.0f, 0.0f, 0.0f);
            half3 b(0.0f, 1.0f, 0.0f);
            half angle = angle_between(a, b);

            // Угол между (1,0,0) и (0,1,0) = 90 градусов = π/2 радиан
            suite.assert_approximately_equal(float(angle), Constants::Constants<float>::Pi / 2.0f,
                "angle_between() 90 degrees", HALF_ANGLE_EPSILON);
        }

        // ============================================================================
        // 8. Цветовые операции
        // ============================================================================
        suite.section("Цветовые операции");

        // Тест яркости
        {
            half3 color(0.5f, 0.3f, 0.2f);
            half luma = color.luminance();
            half global_luma = luminance(color);

            // 0.2126*0.5 + 0.7152*0.3 + 0.0722*0.2 = 0.1063 + 0.21456 + 0.01444 = 0.3353
            float expected = 0.2126f * 0.5f + 0.7152f * 0.3f + 0.0722f * 0.2f;
            suite.assert_approximately_equal(float(luma), expected, "luminance()", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_luma), expected, "global luminance()", HALF_EPSILON);
        }

        // Тест преобразования в градации серого
        {
            half3 color(0.5f, 0.3f, 0.2f);
            half3 grayscale = color.rgb_to_grayscale();
            half3 global_grayscale = rgb_to_grayscale(color);

            float expected = 0.2126f * 0.5f + 0.7152f * 0.3f + 0.0722f * 0.2f;
            suite.assert_approximately_equal(float(grayscale.x), expected, "rgb_to_grayscale() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(grayscale.y), expected, "rgb_to_grayscale() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(grayscale.z), expected, "rgb_to_grayscale() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_grayscale.x), expected, "global rgb_to_grayscale() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_grayscale.y), expected, "global rgb_to_grayscale() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_grayscale.z), expected, "global rgb_to_grayscale() z", HALF_EPSILON);
        }

        // Тест гамма-коррекции
        {
            half3 color(0.25f, 0.5f, 0.75f);
            half gamma(2.0f);
            half3 corrected = color.gamma_correct(gamma);
            half3 global_corrected = gamma_correct(color, gamma);

            // gamma_correct(x) = pow(x, gamma)
            suite.assert_approximately_equal(float(corrected.x), 0.0625f, "gamma_correct() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(corrected.y), 0.25f, "gamma_correct() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(corrected.z), 0.5625f, "gamma_correct() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_corrected.x), 0.0625f, "global gamma_correct() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_corrected.y), 0.25f, "global gamma_correct() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_corrected.z), 0.5625f, "global gamma_correct() z", HALF_EPSILON);
        }

        // Тест преобразования sRGB <-> линейное
        {
            half3 srgb(0.5f, 0.5f, 0.5f);
            half3 linear = srgb.srgb_to_linear();
            half3 global_linear = srgb_to_linear(srgb);

            // Для значения 0.5 в sRGB: 0.5 <= 0.04045 ? 0.5/12.92 : pow((0.5+0.055)/1.055, 2.4)
            // 0.5 > 0.04045, поэтому: pow((0.5+0.055)/1.055, 2.4) ≈ pow(0.526, 2.4) ≈ 0.214
            float expected = std::pow((0.5f + 0.055f) / 1.055f, 2.4f);
            suite.assert_approximately_equal(float(linear.x), expected, "srgb_to_linear() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(linear.y), expected, "srgb_to_linear() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(linear.z), expected, "srgb_to_linear() z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_linear.x), expected, "global srgb_to_linear() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_linear.y), expected, "global srgb_to_linear() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_linear.z), expected, "global srgb_to_linear() z", HALF_EPSILON);

            // Обратное преобразование
            half3 back_to_srgb = linear.linear_to_srgb();
            half3 global_back_to_srgb = linear_to_srgb(linear);

            // Проверяем, что преобразование обратимо с некоторой точностью
            suite.assert_approximately_equal(float(back_to_srgb.x), 0.5f, "linear_to_srgb() round-trip x", HALF_EPSILON);
            suite.assert_approximately_equal(float(back_to_srgb.y), 0.5f, "linear_to_srgb() round-trip y", HALF_EPSILON);
            suite.assert_approximately_equal(float(back_to_srgb.z), 0.5f, "linear_to_srgb() round-trip z", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_back_to_srgb.x), 0.5f, "global linear_to_srgb() round-trip x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_back_to_srgb.y), 0.5f, "global linear_to_srgb() round-trip y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_back_to_srgb.z), 0.5f, "global linear_to_srgb() round-trip z", HALF_EPSILON);
        }

        // ============================================================================
        // 9. Swizzle операции
        // ============================================================================
        suite.section("Swizzle операции");

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

        // Цветовые swizzles
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
        // 10. Утилитарные методы
        // ============================================================================
        suite.section("Утилитарные методы");

        // Тест isValid
        {
            half3 valid(1.0f, 2.0f, 3.0f);
            suite.assert_true(valid.is_valid(), "is_valid() for valid vector");
            suite.assert_true(is_valid(valid), "global is_valid() for valid vector");
        }

        // Тест approximately
        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 b(1.001f, 2.001f, 3.001f);
            half3 c(1.1f, 2.1f, 3.1f);

            suite.assert_true(a.approximately(b, 0.01f), "approximately() within epsilon");
            suite.assert_false(a.approximately(c, 0.01f), "approximately() outside epsilon");

            bool global_approx = approximately(a, b, 0.01f);
            suite.assert_true(global_approx, "global approximately() within epsilon");
        }

        // Тест approximately_zero
        {
            half3 zero(0.0f, 0.0f, 0.0f);
            half3 near_zero(0.001f, 0.001f, 0.001f);
            half3 not_zero(0.1f, 0.1f, 0.1f);

            suite.assert_true(zero.approximately_zero(0.01f), "approximately_zero() for zero");
            suite.assert_true(near_zero.approximately_zero(0.01f), "approximately_zero() for near zero");
            suite.assert_false(not_zero.approximately_zero(0.01f), "approximately_zero() for non-zero");
        }

        // Тест is_normalized
        {
            half3 normalized(0.26726124f, 0.53452248f, 0.80178373f); // (1,2,3) нормализованный
            half3 not_normalized(1.0f, 2.0f, 3.0f);

            suite.assert_true(normalized.is_normalized(0.01f), "is_normalized() for normalized vector");
            suite.assert_false(not_normalized.is_normalized(0.01f), "is_normalized() for non-normalized");

            bool global_normalized = is_normalized(normalized, 0.01f);
            suite.assert_true(global_normalized, "global is_normalized() for normalized vector");
        }

        // Тест to_string
        {
            half3 v(1.5f, 2.5f, 3.5f);
            std::string str = v.to_string();

            // Проверяем наличие ожидаемых значений в строке
            suite.assert_true(str.find("1.5") != std::string::npos || str.find("1.500") != std::string::npos,
                "to_string() contains x value");
            suite.assert_true(str.find("2.5") != std::string::npos || str.find("2.500") != std::string::npos,
                "to_string() contains y value");
            suite.assert_true(str.find("3.5") != std::string::npos || str.find("3.500") != std::string::npos,
                "to_string() contains z value");
        }

        // Тест data()
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

        // Тест set_xy
        {
            half3 v(1.0f, 2.0f, 3.0f);
            half2 xy(4.0f, 5.0f);
            v.set_xy(xy);

            suite.assert_approximately_equal(float(v.x), 4.0f, "set_xy() x", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.y), 5.0f, "set_xy() y", HALF_EPSILON);
            suite.assert_approximately_equal(float(v.z), 3.0f, "set_xy() preserves z", HALF_EPSILON);
        }

        // Тест ensure_normalized
        {
            half3 normal(1.0f, 2.0f, 3.0f);
            half3 fallback(0.0f, 0.0f, 1.0f);
            half3 ensured = ensure_normalized(normal, fallback);

            // ensure_normalized должен нормализовать вектор
            float length = float(ensured.length());
            suite.assert_approximately_equal(length, 1.0f, "ensure_normalized() length", HALF_EPSILON);

            // Тест с нулевым вектором (должен вернуть fallback)
            half3 zero(0.0f, 0.0f, 0.0f);
            half3 zero_ensured = ensure_normalized(zero, fallback);
            suite.assert_true(zero_ensured == fallback, "ensure_normalized() returns fallback for zero vector");
        }

        // ============================================================================
        // 11. Операторы сравнения
        // ============================================================================
        suite.section("Операторы сравнения");

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
        // 12. Специальные значения
        // ============================================================================
        suite.section("Специальные значения");

        // Тест с нулями
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

        // Тест с бесконечностями
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

        // Тест с NaN
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

        // Тест с конечными значениями
        {
            half3 finite(1.0f, 2.0f, 3.0f);

            suite.assert_true(finite.is_finite(), "is_finite() for finite vector");
            suite.assert_true(finite.is_all_finite(), "is_all_finite() for finite vector");

            bool global_finite = is_finite(finite);
            bool global_all_finite = is_all_finite(finite);
            suite.assert_true(global_finite, "global is_finite()");
            suite.assert_true(global_all_finite, "global is_all_finite()");
        }

        // Тест с положительными/отрицательными значениями
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

        // Тест с положительными/отрицательными нулями
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
        // 13. Линейная интерполяция
        // ============================================================================
        suite.section("Линейная интерполяция");

        {
            half3 a(0.0f, 0.0f, 0.0f);
            half3 b(10.0f, 20.0f, 30.0f);

            half3 lerp_result = half3::lerp(a, b, half(0.5f));
            suite.assert_approximately_equal(float(lerp_result.x), 5.0f, "half3::lerp() at 0.5 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_result.y), 10.0f, "half3::lerp() at 0.5 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_result.z), 15.0f, "half3::lerp() at 0.5 z", HALF_EPSILON);

            half3 lerp_float = half3::lerp(a, b, 0.5f);
            suite.assert_approximately_equal(float(lerp_float.x), 5.0f, "half3::lerp() with float at 0.5 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_float.y), 10.0f, "half3::lerp() with float at 0.5 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(lerp_float.z), 15.0f, "half3::lerp() with float at 0.5 z", HALF_EPSILON);

            half3 global_lerp = lerp(a, b, half(0.5f));
            suite.assert_approximately_equal(float(global_lerp.x), 5.0f, "global lerp() at 0.5 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_lerp.y), 10.0f, "global lerp() at 0.5 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_lerp.z), 15.0f, "global lerp() at 0.5 z", HALF_EPSILON);

            half3 global_lerp_float = lerp(a, b, 0.5f);
            suite.assert_approximately_equal(float(global_lerp_float.x), 5.0f, "global lerp() with float at 0.5 x", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_lerp_float.y), 10.0f, "global lerp() with float at 0.5 y", HALF_EPSILON);
            suite.assert_approximately_equal(float(global_lerp_float.z), 15.0f, "global lerp() with float at 0.5 z", HALF_EPSILON);

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
        // 14. Глобальные константы
        // ============================================================================
        suite.section("Глобальные константы");

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
        // 15. Граничные случаи
        // ============================================================================
        suite.section("Граничные случаи");

        // Тест с очень маленькими значениями
        {
            half3 tiny(1e-6f, 1e-6f, 1e-6f);
            suite.assert_true(tiny.approximately_zero(1e-3f), "Tiny values approximately_zero");
        }

        // Тест с очень большими значениями
        {
            half3 huge(50000.0f, 50000.0f, 50000.0f);
            suite.assert_false(huge.approximately_zero(), "Huge values not approximately_zero");

            // Нормализация больших значений
            half3 normalized_huge = huge.normalize();
            float normalized_len = float(normalized_huge.length());
            suite.assert_approximately_equal(normalized_len, 1.0f, "Normalize huge values length", HALF_EPSILON);
        }

        // Тест деления на ноль (векторное)
        {
            half3 a(1.0f, 2.0f, 3.0f);
            half3 zero_vec(0.0f, 0.0f, 0.0f);

            half3 result = a / zero_vec;
            suite.assert_true(result.x.is_inf() || result.x.is_nan(), "Division by zero vector x produces non-finite");
            suite.assert_true(result.y.is_inf() || result.y.is_nan(), "Division by zero vector y produces non-finite");
            suite.assert_true(result.z.is_inf() || result.z.is_nan(), "Division by zero vector z produces non-finite");
        }

        // Тест деления на ноль (скалярное)
        {
            half3 v(1.0f, 2.0f, 3.0f);
            half3 result = v / 0.0f;

            suite.assert_true(result.x.is_inf() || result.x.is_nan(), "Division by zero scalar x produces non-finite");
            suite.assert_true(result.y.is_inf() || result.y.is_nan(), "Division by zero scalar y produces non-finite");
            suite.assert_true(result.z.is_inf() || result.z.is_nan(), "Division by zero scalar z produces non-finite");
        }

        // Тест нормализации очень маленького вектора
        {
            half3 tiny(1e-20f, 1e-20f, 1e-20f);
            half3 normalized = tiny.normalize();

            // Должен вернуть нулевой вектор, так как длина меньше epsilon
            suite.assert_approximately_equal(float(normalized.x), 0.0f, "Normalize tiny vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.y), 0.0f, "Normalize tiny vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(normalized.z), 0.0f, "Normalize tiny vector z", HALF_EPSILON);
        }

        // Тест smoothstep с edge0 = edge1
        {
            half3 v(0.5f, 1.5f, 2.5f);
            half3 result = smoothstep(half(1.0f), half(1.0f), v);
            // При edge0 = edge1 используется step(edge0)
            half3 step_result = step(half(1.0f), v);
            suite.assert_approximately_equal(float(result.x), float(step_result.x), "smoothstep() with equal edges x", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.y), float(step_result.y), "smoothstep() with equal edges y", HALF_EPSILON);
            suite.assert_approximately_equal(float(result.z), float(step_result.z), "smoothstep() with equal edges z", HALF_EPSILON);
        }

        // Тест скалярного произведения с самим собой
        {
            half3 v(3.0f, 4.0f, 5.0f);
            half dot_self = v.dot(v);
            half expected = v.length_sq();
            suite.assert_approximately_equal(float(dot_self), float(expected), "Dot product with self equals length squared", HALF_EPSILON);
        }

        // Тест векторного произведения с самим собой
        {
            half3 v(2.0f, 3.0f, 4.0f);
            half3 cross_self = v.cross(v);
            // Векторное произведение вектора с самим собой = нулевой вектор
            suite.assert_approximately_equal(float(cross_self.x), 0.0f, "Cross product with self x", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_self.y), 0.0f, "Cross product with self y", HALF_EPSILON);
            suite.assert_approximately_equal(float(cross_self.z), 0.0f, "Cross product with self z", HALF_EPSILON);
        }

        // Тест is_normalized для нулевого вектора
        {
            half3 zero(0.0f, 0.0f, 0.0f);
            suite.assert_false(zero.is_normalized(), "Zero vector is not normalized");
        }

        // Тест с числами, близкими к максимальному значению half
        {
            float max_half_val = float(half::max_value());
            half3 max_vec(max_half_val, max_half_val, max_half_val);

            // Убедимся, что значения не стали NaN или Inf
            suite.assert_true(max_vec.is_finite(), "Vector with max half values is finite");

            // Нормализация вектора с максимальными значениями
            half3 normalized = max_vec.normalize();
            float normalized_len = float(normalized.length());
            suite.assert_approximately_equal(normalized_len, 1.0f, "Normalize max values length", HALF_EPSILON);
        }

        // Тест с денормализованными числами
        {
            half min_denorm = half::min_denormal_value();
            half3 denorm_vec(min_denorm, min_denorm, min_denorm);

            suite.assert_true(denorm_vec.is_finite(), "Vector with denormalized values is finite");

            // Умножение денормализованных чисел
            half3 multiplied = denorm_vec * half(2.0f);
            suite.assert_true(multiplied.is_finite(), "Multiplication of denormalized values is finite");
        }

        // Тест насыщения с отрицательными числами
        {
            half3 v(-2.0f, 0.5f, 1.5f);
            half3 saturated = v.saturate();

            suite.assert_approximately_equal(float(saturated.x), 0.0f, "saturate() negative value", HALF_EPSILON);
            suite.assert_approximately_equal(float(saturated.y), 0.5f, "saturate() positive value < 1", HALF_EPSILON);
            suite.assert_approximately_equal(float(saturated.z), 1.0f, "saturate() positive value > 1", HALF_EPSILON);
        }

        // Тест округления граничных значений
        {
            half3 v1(1.4999f, 1.5001f, -1.4999f);
            half3 rounded1 = v1.round();
            suite.assert_approximately_equal(float(rounded1.x), 1.0f, "round() 1.4999", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded1.y), 2.0f, "round() 1.5001", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded1.z), -1.0f, "round() -1.4999", HALF_EPSILON);

            half3 v2(-1.5001f, 2.4999f, 2.5001f);
            half3 rounded2 = v2.round();
            suite.assert_approximately_equal(float(rounded2.x), -2.0f, "round() -1.5001", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded2.y), 2.0f, "round() 2.4999", HALF_EPSILON);
            suite.assert_approximately_equal(float(rounded2.z), 3.0f, "round() 2.5001", HALF_EPSILON);
        }

        // Тест floor/ceil граничных значений
        {
            half3 v(1.5f, -1.5f, 2.3f);

            half3 floored = v.floor();
            suite.assert_approximately_equal(float(floored.x), 1.0f, "floor() 1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(floored.y), -2.0f, "floor() -1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(floored.z), 2.0f, "floor() 2.3", HALF_EPSILON);

            half3 ceiled = v.ceil();
            suite.assert_approximately_equal(float(ceiled.x), 2.0f, "ceil() 1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(ceiled.y), -1.0f, "ceil() -1.5", HALF_EPSILON);
            suite.assert_approximately_equal(float(ceiled.z), 3.0f, "ceil() 2.3", HALF_EPSILON);
        }

        // Тест рефракции с полным внутренним отражением
        {
            half3 incident(0.7071f, -0.7071f, 0.0f); // Направлен под углом 45°
            half3 normal(0.0f, 1.0f, 0.0f); // Нормаль вверх
            half eta(2.0f); // Коэффициент преломления > 1 (из более плотной в менее плотную среду)

            half3 refracted = refract(incident, normal, eta);

            // При eta > 1 и определенных углах происходит полное внутреннее отражение
            // Должен вернуться нулевой вектор
            suite.assert_approximately_equal(float(refracted.x), 0.0f, "refract() total internal reflection x", HALF_EPSILON);
            suite.assert_approximately_equal(float(refracted.y), 0.0f, "refract() total internal reflection y", HALF_EPSILON);
            suite.assert_approximately_equal(float(refracted.z), 0.0f, "refract() total internal reflection z", HALF_EPSILON);
        }

        // Тест проекции нулевого вектора
        {
            half3 zero(0.0f, 0.0f, 0.0f);
            half3 onto(1.0f, 0.0f, 0.0f);
            half3 projected = zero.project(onto);

            suite.assert_approximately_equal(float(projected.x), 0.0f, "project() zero vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.y), 0.0f, "project() zero vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.z), 0.0f, "project() zero vector z", HALF_EPSILON);
        }

        // Тест проекции на нулевой вектор
        {
            half3 v(1.0f, 2.0f, 3.0f);
            half3 zero(0.0f, 0.0f, 0.0f);
            half3 projected = v.project(zero);

            suite.assert_approximately_equal(float(projected.x), 0.0f, "project() onto zero vector x", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.y), 0.0f, "project() onto zero vector y", HALF_EPSILON);
            suite.assert_approximately_equal(float(projected.z), 0.0f, "project() onto zero vector z", HALF_EPSILON);
        }

        // Тест отклонения от самого себя
        {
            half3 v(1.0f, 2.0f, 3.0f);
            half3 rejected = v.reject(v);

            // Отклонение вектора от самого себя должно дать нулевой вектор
            suite.assert_approximately_equal(float(rejected.x), 0.0f, "reject() from self x", HALF_EPSILON);
            suite.assert_approximately_equal(float(rejected.y), 0.0f, "reject() from self y", HALF_EPSILON);
            suite.assert_approximately_equal(float(rejected.z), 0.0f, "reject() from self z", HALF_EPSILON);
        }

        // Тест угла между параллельными векторами
        {
            half3 a(1.0f, 0.0f, 0.0f);
            half3 b(2.0f, 0.0f, 0.0f); // Параллелен a
            half angle = angle_between(a, b);

            suite.assert_approximately_equal(float(angle), 0.0f, "angle_between() parallel vectors", HALF_ANGLE_EPSILON);
        }

        // Тест угла между противоположными векторами
        {
            half3 a(1.0f, 0.0f, 0.0f);
            half3 b(-1.0f, 0.0f, 0.0f); // Противоположен a
            half angle = angle_between(a, b);

            suite.assert_approximately_equal(float(angle), Constants::Constants<float>::Pi,
                "angle_between() opposite vectors", HALF_ANGLE_EPSILON);
        }

        // Тест угла с нулевым вектором
        {
            half3 a(1.0f, 0.0f, 0.0f);
            half3 zero(0.0f, 0.0f, 0.0f);
            half angle = angle_between(a, zero);

            // Угол с нулевым вектором не определен, но реализация возвращает 0
            suite.assert_approximately_equal(float(angle), 0.0f, "angle_between() with zero vector", HALF_ANGLE_EPSILON);
        }

        suite.footer();
    }
} // namespace AfterMathTests
