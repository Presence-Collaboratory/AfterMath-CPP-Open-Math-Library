// Author: DeepSeek, NSDeathman
// Test suite for AfterMath::Rect (template version)

#include "AutotestCore.h"

namespace AfterMathTests
{
    void RunRectTests(TestSuite& suite)
    {
        using namespace AfterMath;

        const float EPSILON = 1e-6f;

        // ============================================================================
        // 1. Constructors (float)
        // ============================================================================
        suite.section("Constructors (float)");

        // Default constructor
        {
            fRect r;
            suite.assert_approximately_equal(r.position.x, 0.0f, "fRect default pos.x");
            suite.assert_approximately_equal(r.position.y, 0.0f, "fRect default pos.y");
            suite.assert_approximately_equal(r.size.x, 0.0f, "fRect default size.x");
            suite.assert_approximately_equal(r.size.y, 0.0f, "fRect default size.y");
        }

        // From vectors
        {
            float2 pos(1.0f, 2.0f);
            float2 dim(3.0f, 4.0f);
            fRect r(pos, dim);
            suite.assert_approximately_equal(r.position, pos, "fRect vector constructor position");
            suite.assert_approximately_equal(r.size, dim, "fRect vector constructor size");
        }

        // From individual coordinates
        {
            fRect r(10.0f, 20.0f, 100.0f, 200.0f);
            suite.assert_approximately_equal(r.left(), 10.0f, "fRect coord constructor left");
            suite.assert_approximately_equal(r.top(), 20.0f, "fRect coord constructor top");
            suite.assert_approximately_equal(r.width(), 100.0f, "fRect coord constructor width");
            suite.assert_approximately_equal(r.height(), 200.0f, "fRect coord constructor height");
        }

        // from_min_max
        {
            float2 min(5.0f, 5.0f);
            float2 max(15.0f, 25.0f);
            fRect r = fRect::from_min_max(min, max);
            suite.assert_approximately_equal(r.left(), 5.0f, "fRect from_min_max left");
            suite.assert_approximately_equal(r.top(), 5.0f, "fRect from_min_max top");
            suite.assert_approximately_equal(r.right(), 15.0f, "fRect from_min_max right");
            suite.assert_approximately_equal(r.bottom(), 25.0f, "fRect from_min_max bottom");
            suite.assert_approximately_equal(r.width(), 10.0f, "fRect from_min_max width");
            suite.assert_approximately_equal(r.height(), 20.0f, "fRect from_min_max height");
        }

        // from_center_extents
        {
            float2 center(50.0f, 60.0f);
            float2 half(5.0f, 10.0f);
            fRect r = fRect::from_center_extents(center, half);
            suite.assert_approximately_equal(r.center(), center, "fRect from_center_extents center");
            suite.assert_approximately_equal(r.extent(), half, "fRect from_center_extents extent");
            suite.assert_approximately_equal(r.left(), 45.0f, "fRect from_center_extents left");
            suite.assert_approximately_equal(r.top(), 50.0f, "fRect from_center_extents top");
            suite.assert_approximately_equal(r.width(), 10.0f, "fRect from_center_extents width");
            suite.assert_approximately_equal(r.height(), 20.0f, "fRect from_center_extents height");
        }

        // ============================================================================
        // 1b. Constructors (uint)
        // ============================================================================
        suite.section("Constructors (uint)");

        // Default constructor
        {
            Rect r;
            suite.assert_equal(r.position.x, 0u, "Rect default pos.x");
            suite.assert_equal(r.position.y, 0u, "Rect default pos.y");
            suite.assert_equal(r.size.x, 0u, "Rect default size.x");
            suite.assert_equal(r.size.y, 0u, "Rect default size.y");
        }

        // From vectors
        {
            uint2 pos(1, 2);
            uint2 dim(3, 4);
            Rect r(pos, dim);
            suite.assert_equal(r.position, pos, "Rect vector constructor position");
            suite.assert_equal(r.size, dim, "Rect vector constructor size");
        }

        // From individual coordinates
        {
            Rect r(10, 20, 100, 200);
            suite.assert_equal(r.left(), 10u, "Rect coord constructor left");
            suite.assert_equal(r.top(), 20u, "Rect coord constructor top");
            suite.assert_equal(r.width(), 100u, "Rect coord constructor width");
            suite.assert_equal(r.height(), 200u, "Rect coord constructor height");
        }

        // from_min_max
        {
            uint2 min(5, 5);
            uint2 max(15, 25);
            Rect r = Rect::from_min_max(min, max);
            suite.assert_equal(r.left(), 5u, "Rect from_min_max left");
            suite.assert_equal(r.top(), 5u, "Rect from_min_max top");
            suite.assert_equal(r.right(), 15u, "Rect from_min_max right");
            suite.assert_equal(r.bottom(), 25u, "Rect from_min_max bottom");
            suite.assert_equal(r.width(), 10u, "Rect from_min_max width");
            suite.assert_equal(r.height(), 20u, "Rect from_min_max height");
        }

        // from_center_extents (even sizes give exact division)
        {
            uint2 center(50, 60);
            uint2 half(5, 10);
            Rect r = Rect::from_center_extents(center, half);
            suite.assert_equal(r.center(), center, "Rect from_center_extents center");
            suite.assert_equal(r.extent(), half, "Rect from_center_extents extent");
            suite.assert_equal(r.left(), 45u, "Rect from_center_extents left");
            suite.assert_equal(r.top(), 50u, "Rect from_center_extents top");
            suite.assert_equal(r.width(), 10u, "Rect from_center_extents width");
            suite.assert_equal(r.height(), 20u, "Rect from_center_extents height");
        }

        // from_center_extents (odd half extents -> truncation)
        {
            // half = (3, 3) -> size = (6, 6), center = (10, 10) -> left/top = 10-3=7
            uint2 center(10, 10);
            uint2 half(3, 3);
            Rect r = Rect::from_center_extents(center, half);
            suite.assert_equal(r.left(), 7u, "Rect odd half left truncated");
            suite.assert_equal(r.top(), 7u, "Rect odd half top truncated");
            suite.assert_equal(r.width(), 6u, "Rect odd half width");
            suite.assert_equal(r.height(), 6u, "Rect odd half height");
            // center() returns (7+6/2)= (7+3)=10, correct
            suite.assert_equal(r.center(), center, "Rect odd half center recovery");
        }

        // ============================================================================
        // 2. Basic Accessors (float + uint)
        // ============================================================================
        suite.section("Basic Accessors");

        // float
        {
            fRect r(10.0f, 20.0f, 100.0f, 200.0f);
            suite.assert_approximately_equal(r.left(), 10.0f, "fRect left()");
            suite.assert_approximately_equal(r.top(), 20.0f, "fRect top()");
            suite.assert_approximately_equal(r.right(), 110.0f, "fRect right()");
            suite.assert_approximately_equal(r.bottom(), 220.0f, "fRect bottom()");
            suite.assert_approximately_equal(r.min(), float2(10.0f, 20.0f), "fRect min()");
            suite.assert_approximately_equal(r.max(), float2(110.0f, 220.0f), "fRect max()");
            suite.assert_approximately_equal(r.center(), float2(60.0f, 120.0f), "fRect center()");
            suite.assert_approximately_equal(r.extent(), float2(50.0f, 100.0f), "fRect extent()");
        }

        // uint
        {
            Rect r(10, 20, 100, 200);
            suite.assert_equal(r.left(), 10u, "Rect left()");
            suite.assert_equal(r.top(), 20u, "Rect top()");
            suite.assert_equal(r.right(), 110u, "Rect right()");
            suite.assert_equal(r.bottom(), 220u, "Rect bottom()");
            suite.assert_equal(r.min(), uint2(10, 20), "Rect min()");
            suite.assert_equal(r.max(), uint2(110, 220), "Rect max()");
            suite.assert_equal(r.center(), uint2(60, 120), "Rect center()");
            suite.assert_equal(r.extent(), uint2(50, 100), "Rect extent()");
        }

        // ============================================================================
        // 3. Derived Properties
        // ============================================================================
        suite.section("Derived Properties");

        // Area (float)
        {
            fRect r(0.0f, 0.0f, 5.0f, 10.0f);
            suite.assert_approximately_equal(r.area(), 50.0f, "fRect area()");
        }
        // Area (uint)
        {
            Rect r(0, 0, 5, 10);
            suite.assert_equal(r.area(), 50u, "Rect area()");
        }

        // Aspect ratio (float)
        {
            fRect r(0.0f, 0.0f, 5.0f, 10.0f);
            suite.assert_approximately_equal(r.aspect_ratio(), 0.5f, "fRect aspect_ratio() 5/10");
        }
        {
            fRect r(0.0f, 0.0f, 5.0f, 0.0f);
            suite.assert_approximately_equal(r.aspect_ratio(), 0.0f, "fRect aspect_ratio() zero height");
        }
        // Aspect ratio (uint) – same float result
        {
            Rect r(0, 0, 5, 10);
            suite.assert_approximately_equal(r.aspect_ratio(), 0.5f, "Rect aspect_ratio() 5/10");
        }
        {
            Rect r(0, 0, 5, 0);
            suite.assert_approximately_equal(r.aspect_ratio(), 0.0f, "Rect aspect_ratio() zero height");
        }

        // is_valid (float)
        {
            fRect valid(0.0f, 0.0f, 10.0f, 10.0f);
            suite.assert_true(valid.is_valid(), "fRect is_valid() positive size");

            fRect zero_size(0.0f, 0.0f, 0.0f, 0.0f);
            suite.assert_true(zero_size.is_valid(), "fRect is_valid() zero size is valid");

            fRect negative_size(0.0f, 0.0f, -5.0f, 10.0f);
            suite.assert_false(negative_size.is_valid(), "fRect is_valid() negative width invalid");

            fRect inf_size(0.0f, 0.0f, std::numeric_limits<float>::infinity(), 10.0f);
            suite.assert_false(inf_size.is_valid(), "fRect is_valid() infinite size invalid");
        }

        // is_valid (uint)
        {
            Rect valid(0, 0, 10, 10);
            suite.assert_true(valid.is_valid(), "Rect is_valid() positive size");

            Rect zero_size(0, 0, 0, 0);
            suite.assert_true(zero_size.is_valid(), "Rect is_valid() zero size is valid");

            // negative width can't be constructed with uint (underflow not tested here)
            // No infinite/NaN for integers
        }

        // ============================================================================
        // 4. Containment & Overlap Tests
        // ============================================================================
        suite.section("Containment & Overlap");

        // float
        {
            fRect r(10.0f, 10.0f, 100.0f, 100.0f);
            suite.assert_true(r.contains(float2(10.0f, 10.0f)), "fRect contains left-top edge");
            suite.assert_true(r.contains(float2(50.0f, 50.0f)), "fRect contains interior");
            suite.assert_false(r.contains(float2(110.0f, 110.0f)), "fRect excludes right-bottom edge");
            suite.assert_false(r.contains(float2(0.0f, 0.0f)), "fRect outside");

            fRect inner(20.0f, 20.0f, 50.0f, 50.0f);
            fRect edge_touch(10.0f, 10.0f, 100.0f, 100.0f);
            fRect partially_out(100.0f, 100.0f, 50.0f, 50.0f);
            suite.assert_true(r.contains(inner), "fRect contains inner");
            suite.assert_true(r.contains(edge_touch), "fRect contains identical");
            suite.assert_false(r.contains(partially_out), "fRect partially outside");

            fRect a(0.0f, 0.0f, 10.0f, 10.0f);
            fRect b(5.0f, 5.0f, 10.0f, 10.0f);
            fRect c(10.0f, 10.0f, 10.0f, 10.0f);
            fRect d(20.0f, 20.0f, 10.0f, 10.0f);
            suite.assert_true(a.overlaps(b), "fRect overlaps");
            suite.assert_false(a.overlaps(c), "fRect touching corner no overlap");
            suite.assert_false(a.overlaps(d), "fRect separate");
        }

        // uint
        {
            Rect r(10, 10, 100, 100);
            suite.assert_true(r.contains(uint2(10, 10)), "Rect contains left-top edge");
            suite.assert_true(r.contains(uint2(50, 50)), "Rect contains interior");
            suite.assert_false(r.contains(uint2(110, 110)), "Rect excludes right-bottom edge");
            suite.assert_false(r.contains(uint2(0, 0)), "Rect outside");

            Rect inner(20, 20, 50, 50);
            Rect edge_touch(10, 10, 100, 100);
            Rect partially_out(100, 100, 50, 50);
            suite.assert_true(r.contains(inner), "Rect contains inner");
            suite.assert_true(r.contains(edge_touch), "Rect contains identical");
            suite.assert_false(r.contains(partially_out), "Rect partially outside");

            Rect a(0, 0, 10, 10);
            Rect b(5, 5, 10, 10);
            Rect c(10, 10, 10, 10);
            Rect d(20, 20, 10, 10);
            suite.assert_true(a.overlaps(b), "Rect overlaps");
            suite.assert_false(a.overlaps(c), "Rect touching corner no overlap");
            suite.assert_false(a.overlaps(d), "Rect separate");
        }

        // ============================================================================
        // 5. Mutating Operations
        // ============================================================================
        suite.section("Mutating Operations");

        // intersected (float)
        {
            fRect a(0.0f, 0.0f, 10.0f, 10.0f);
            fRect b(5.0f, 5.0f, 10.0f, 10.0f);
            fRect inter = a.intersected(b);
            suite.assert_approximately_equal(inter.left(), 5.0f, "fRect intersected left");
            suite.assert_approximately_equal(inter.top(), 5.0f, "fRect intersected top");
            suite.assert_approximately_equal(inter.right(), 10.0f, "fRect intersected right");
            suite.assert_approximately_equal(inter.bottom(), 10.0f, "fRect intersected bottom");
        }
        // intersected (uint)
        {
            Rect a(0, 0, 10, 10);
            Rect b(5, 5, 10, 10);
            Rect inter = a.intersected(b);
            suite.assert_equal(inter.left(), 5u, "Rect intersected left");
            suite.assert_equal(inter.top(), 5u, "Rect intersected top");
            suite.assert_equal(inter.right(), 10u, "Rect intersected right");
            suite.assert_equal(inter.bottom(), 10u, "Rect intersected bottom");
        }

        // intersected with no overlap -> empty rect
        {
            fRect a(0.0f, 0.0f, 10.0f, 10.0f);
            fRect b(20.0f, 20.0f, 10.0f, 10.0f);
            fRect empty = a.intersected(b);
            suite.assert_true(empty.position == float2(0.0f, 0.0f) && empty.size == float2(0.0f, 0.0f),
                "fRect intersected no overlap returns zero rect");
        }
        {
            Rect a(0, 0, 10, 10);
            Rect b(20, 20, 10, 10);
            Rect empty = a.intersected(b);
            suite.assert_equal(empty.position, uint2(0, 0), "Rect intersected no overlap pos");
            suite.assert_equal(empty.size, uint2(0, 0), "Rect intersected no overlap size");
        }

        // united
        {
            fRect a(0.0f, 0.0f, 10.0f, 10.0f);
            fRect b(5.0f, 5.0f, 15.0f, 15.0f);
            fRect u = a.united(b);
            suite.assert_approximately_equal(u.left(), 0.0f, "fRect united left");
            suite.assert_approximately_equal(u.top(), 0.0f, "fRect united top");
            suite.assert_approximately_equal(u.right(), 20.0f, "fRect united right");
            suite.assert_approximately_equal(u.bottom(), 20.0f, "fRect united bottom");
        }
        {
            Rect a(0, 0, 10, 10);
            Rect b(5, 5, 15, 15);
            Rect u = a.united(b);
            suite.assert_equal(u.left(), 0u, "Rect united left");
            suite.assert_equal(u.top(), 0u, "Rect united top");
            suite.assert_equal(u.right(), 20u, "Rect united right");
            suite.assert_equal(u.bottom(), 20u, "Rect united bottom");
        }

        // expanded uniform
        {
            fRect r(10.0f, 10.0f, 100.0f, 100.0f);
            fRect expanded = r.expanded(5.0f);
            suite.assert_approximately_equal(expanded.left(), 5.0f, "fRect expanded uniform left");
            suite.assert_approximately_equal(expanded.top(), 5.0f, "fRect expanded uniform top");
            suite.assert_approximately_equal(expanded.width(), 110.0f, "fRect expanded uniform width");
            suite.assert_approximately_equal(expanded.height(), 110.0f, "fRect expanded uniform height");
        }
        {
            Rect r(10, 10, 100, 100);
            Rect expanded = r.expanded(5u);
            suite.assert_equal(expanded.left(), 5u, "Rect expanded uniform left");
            suite.assert_equal(expanded.top(), 5u, "Rect expanded uniform top");
            suite.assert_equal(expanded.width(), 110u, "Rect expanded uniform width");
            suite.assert_equal(expanded.height(), 110u, "Rect expanded uniform height");
        }

        // expanded vector
        {
            fRect r(10.0f, 10.0f, 100.0f, 100.0f);
            fRect expanded = r.expanded(float2(2.0f, 4.0f));
            suite.assert_approximately_equal(expanded.left(), 8.0f, "fRect expanded vector left");
            suite.assert_approximately_equal(expanded.top(), 6.0f, "fRect expanded vector top");
            suite.assert_approximately_equal(expanded.width(), 104.0f, "fRect expanded vector width");
            suite.assert_approximately_equal(expanded.height(), 108.0f, "fRect expanded vector height");
        }
        {
            Rect r(10, 10, 100, 100);
            Rect expanded = r.expanded(uint2(2, 4));
            suite.assert_equal(expanded.left(), 8u, "Rect expanded vector left");
            suite.assert_equal(expanded.top(), 6u, "Rect expanded vector top");
            suite.assert_equal(expanded.width(), 104u, "Rect expanded vector width");
            suite.assert_equal(expanded.height(), 108u, "Rect expanded vector height");
        }

        // translated
        {
            fRect r(10.0f, 10.0f, 100.0f, 100.0f);
            fRect translated = r.translated(float2(5.0f, -5.0f));
            suite.assert_approximately_equal(translated.position, float2(15.0f, 5.0f), "fRect translated position");
            suite.assert_approximately_equal(translated.size, r.size, "fRect translated size unchanged");
        }
        {
            Rect r(10, 10, 100, 100);
            // uint can't be negative, so translate by (5, 5)
            Rect translated = r.translated(uint2(5, 5));
            suite.assert_equal(translated.position, uint2(15, 15), "Rect translated position");
            suite.assert_equal(translated.size, r.size, "Rect translated size unchanged");
        }

        // ============================================================================
        // 6. Comparison Operators
        // ============================================================================
        suite.section("Comparison");

        // float
        {
            fRect a(1.0f, 2.0f, 3.0f, 4.0f);
            fRect b(1.0f, 2.0f, 3.0f, 4.0f);
            fRect c(1.0f, 2.0f, 3.0f, 5.0f);
            suite.assert_true(a == b, "fRect equal");
            suite.assert_false(a != b, "fRect not unequal");
            suite.assert_false(a == c, "fRect unequal");
            suite.assert_true(a != c, "fRect unequal returns true");
        }
        // uint
        {
            Rect a(1, 2, 3, 4);
            Rect b(1, 2, 3, 4);
            Rect c(1, 2, 3, 5);
            suite.assert_true(a == b, "Rect equal");
            suite.assert_false(a != b, "Rect not unequal");
            suite.assert_false(a == c, "Rect unequal");
            suite.assert_true(a != c, "Rect unequal returns true");
        }

        // ============================================================================
        // 7. Global Functions
        // ============================================================================
        suite.section("Global Functions");

        // rect_from_min_max
        {
            float2 fmin(1.0f, 2.0f), fmax(5.0f, 6.0f);
            fRect fr = rect_from_min_max(fmin, fmax);
            suite.assert_approximately_equal(fr.left(), 1.0f, "fRect global from_min_max left");
            suite.assert_approximately_equal(fr.width(), 4.0f, "fRect global from_min_max width");

            uint2 umin(1, 2), umax(5, 6);
            Rect ur = rect_from_min_max(umin, umax);
            suite.assert_equal(ur.left(), 1u, "Rect global from_min_max left");
            suite.assert_equal(ur.width(), 4u, "Rect global from_min_max width");
        }

        // rect_from_center_extents
        {
            float2 center(0.0f, 0.0f), half(2.0f, 3.0f);
            fRect fr = rect_from_center_extents(center, half);
            suite.assert_approximately_equal(fr.extent(), half, "fRect global from_center_extents");

            uint2 ucenter(0, 0), uhalf(2, 3);
            Rect ur = rect_from_center_extents(ucenter, uhalf);
            suite.assert_equal(ur.extent(), uhalf, "Rect global from_center_extents");
        }

        // rect_intersection
        {
            fRect a(0.0f, 0.0f, 10.0f, 10.0f), b(5.0f, 5.0f, 10.0f, 10.0f);
            suite.assert_approximately_equal(rect_intersection(a, b), a.intersected(b), "fRect global rect_intersection");

            Rect ua(0, 0, 10, 10), ub(5, 5, 10, 10);
            suite.assert_equal(rect_intersection(ua, ub), ua.intersected(ub), "Rect global rect_intersection");
        }

        // rect_union
        {
            fRect a(0.0f, 0.0f, 10.0f, 10.0f), b(5.0f, 5.0f, 10.0f, 10.0f);
            suite.assert_approximately_equal(rect_union(a, b), a.united(b), "fRect global rect_union");

            Rect ua(0, 0, 10, 10), ub(5, 5, 10, 10);
            suite.assert_equal(rect_union(ua, ub), ua.united(ub), "Rect global rect_union");
        }

        // rect_contains
        {
            fRect r(0.0f, 0.0f, 10.0f, 10.0f);
            suite.assert_true(rect_contains(r, float2(5.0f, 5.0f)), "fRect global rect_contains point");
            suite.assert_true(rect_contains(r, fRect(2.0f, 2.0f, 5.0f, 5.0f)), "fRect global rect_contains rect");

            Rect ur(0, 0, 10, 10);
            suite.assert_true(rect_contains(ur, uint2(5, 5)), "Rect global rect_contains point");
            suite.assert_true(rect_contains(ur, Rect(2, 2, 5, 5)), "Rect global rect_contains rect");
        }

        // rect_overlaps
        {
            fRect a(0.0f, 0.0f, 10.0f, 10.0f), b(5.0f, 5.0f, 10.0f, 10.0f);
            suite.assert_true(rect_overlaps(a, b), "fRect global rect_overlaps");

            Rect ua(0, 0, 10, 10), ub(5, 5, 10, 10);
            suite.assert_true(rect_overlaps(ua, ub), "Rect global rect_overlaps");
        }

        // rect_expand
        {
            fRect r(0.0f, 0.0f, 10.0f, 10.0f);
            suite.assert_approximately_equal(rect_expand(r, 2.0f), r.expanded(2.0f), "fRect global rect_expand uniform");
            suite.assert_approximately_equal(rect_expand(r, float2(1.0f, 2.0f)), r.expanded(float2(1.0f, 2.0f)), "fRect global rect_expand vector");

            Rect ur(0, 0, 10, 10);
            suite.assert_equal(rect_expand(ur, 2u), ur.expanded(2u), "Rect global rect_expand uniform");
            suite.assert_equal(rect_expand(ur, uint2(1, 2)), ur.expanded(uint2(1, 2)), "Rect global rect_expand vector");
        }

        // rect_translate
        {
            fRect r(0.0f, 0.0f, 10.0f, 10.0f);
            suite.assert_approximately_equal(rect_translate(r, float2(5.0f, 5.0f)), r.translated(float2(5.0f, 5.0f)), "fRect global rect_translate");

            Rect ur(0, 0, 10, 10);
            suite.assert_equal(rect_translate(ur, uint2(5, 5)), ur.translated(uint2(5, 5)), "Rect global rect_translate");
        }

        // ============================================================================
        // 8. Constants
        // ============================================================================
        suite.section("Constants");

        suite.assert_approximately_equal(Rect_Zero<float>, fRect(0.0f, 0.0f, 0.0f, 0.0f), "fRect Rect_Zero");
        suite.assert_approximately_equal(Rect_Unit<float>, fRect(0.0f, 0.0f, 1.0f, 1.0f), "fRect Rect_Unit");

        suite.assert_equal(Rect_Zero<uint>, Rect(0u, 0u, 0u, 0u), "Rect Rect_Zero");
        suite.assert_equal(Rect_Unit<uint>, Rect(0u, 0u, 1u, 1u), "Rect Rect_Unit");

        // ============================================================================
        // 9. Edge Cases
        // ============================================================================
        suite.section("Edge Cases");

        // Expand zero rect (float)
        {
            fRect zero;
            fRect expanded = zero.expanded(5.0f);
            suite.assert_approximately_equal(expanded, fRect(-5.0f, -5.0f, 10.0f, 10.0f), "fRect Expand zero rect");
        }
        // Expand zero rect (uint) – underflow not possible, so test with nonzero position
        {
            Rect zero(5, 5, 0, 0);
            Rect expanded = zero.expanded(5u);
            suite.assert_equal(expanded.position, uint2(0, 0), "Rect Expand zero rect position");
            suite.assert_equal(expanded.size, uint2(10, 10), "Rect Expand zero rect size");
        }

        // Intersection with one inside the other
        {
            fRect outer(0.0f, 0.0f, 10.0f, 10.0f);
            fRect inner(2.0f, 2.0f, 5.0f, 5.0f);
            fRect inter = outer.intersected(inner);
            suite.assert_approximately_equal(inter, inner, "fRect intersection when one inside the other");
        }
        {
            Rect outer(0, 0, 10, 10);
            Rect inner(2, 2, 5, 5);
            Rect inter = outer.intersected(inner);
            suite.assert_equal(inter, inner, "Rect intersection when one inside the other");
        }

        // Union with empty rect
        {
            fRect a(1.0f, 2.0f, 3.0f, 4.0f);
            fRect empty;
            fRect u = a.united(empty);
            suite.assert_approximately_equal(u, a, "fRect union with empty rect");
        }
        {
            Rect a(1, 2, 3, 4);
            Rect empty;
            Rect u = a.united(empty);
            suite.assert_equal(u, a, "Rect union with empty rect");
        }

        // String representation (smoke test)
        {
            fRect fr(1.0f, 2.0f, 3.0f, 4.0f);
            std::string s = fr.to_string();
            suite.assert_true(s.find("Rect") != std::string::npos, "fRect to_string contains Rect");
            suite.assert_true(s.find("W:3") != std::string::npos, "fRect to_string contains width");
        }
        {
            Rect ur(1, 2, 3, 4);
            std::string s = ur.to_string();
            suite.assert_true(s.find("Rect") != std::string::npos, "Rect to_string contains Rect");
            suite.assert_true(s.find("W:3") != std::string::npos, "Rect to_string contains width");
        }
    }
}
