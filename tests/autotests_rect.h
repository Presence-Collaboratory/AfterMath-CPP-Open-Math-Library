// Author: DeepSeek, NSDeathman
// Test suite for AfterMath::Rect (float2-based)

#include "AutotestCore.h"

namespace AfterMathTests
{
    void RunRectTests(TestSuite& suite)
    {
        using namespace AfterMath;

        const float EPSILON = 1e-6f;

        // ============================================================================
        // 1. Constructors
        // ============================================================================
        suite.section("Constructors");

        // Default constructor
        {
            Rect r;
            suite.assert_approximately_equal(r.position.x, 0.0f, "Default constructor position.x");
            suite.assert_approximately_equal(r.position.y, 0.0f, "Default constructor position.y");
            suite.assert_approximately_equal(r.size.x, 0.0f, "Default constructor size.x");
            suite.assert_approximately_equal(r.size.y, 0.0f, "Default constructor size.y");
        }

        // From vectors
        {
            float2 pos(1.0f, 2.0f);
            float2 dim(3.0f, 4.0f);
            Rect r(pos, dim);
            suite.assert_approximately_equal(r.position, pos, "Vector constructor position");
            suite.assert_approximately_equal(r.size, dim, "Vector constructor size");
        }

        // From individual coordinates
        {
            Rect r(10.0f, 20.0f, 100.0f, 200.0f);
            suite.assert_approximately_equal(r.left(), 10.0f, "Coordinate constructor left");
            suite.assert_approximately_equal(r.top(), 20.0f, "Coordinate constructor top");
            suite.assert_approximately_equal(r.width(), 100.0f, "Coordinate constructor width");
            suite.assert_approximately_equal(r.height(), 200.0f, "Coordinate constructor height");
        }

        // from_min_max
        {
            float2 min(5.0f, 5.0f);
            float2 max(15.0f, 25.0f);
            Rect r = Rect::from_min_max(min, max);
            suite.assert_approximately_equal(r.left(), 5.0f, "from_min_max left");
            suite.assert_approximately_equal(r.top(), 5.0f, "from_min_max top");
            suite.assert_approximately_equal(r.right(), 15.0f, "from_min_max right");
            suite.assert_approximately_equal(r.bottom(), 25.0f, "from_min_max bottom");
            suite.assert_approximately_equal(r.width(), 10.0f, "from_min_max width");
            suite.assert_approximately_equal(r.height(), 20.0f, "from_min_max height");
        }

        // from_center_extents
        {
            float2 center(50.0f, 60.0f);
            float2 half(5.0f, 10.0f);
            Rect r = Rect::from_center_extents(center, half);
            suite.assert_approximately_equal(r.center(), center, "from_center_extents center");
            suite.assert_approximately_equal(r.extent(), half, "from_center_extents extent");
            suite.assert_approximately_equal(r.left(), 45.0f, "from_center_extents left");
            suite.assert_approximately_equal(r.top(), 50.0f, "from_center_extents top");
            suite.assert_approximately_equal(r.width(), 10.0f, "from_center_extents width");
            suite.assert_approximately_equal(r.height(), 20.0f, "from_center_extents height");
        }

        // ============================================================================
        // 2. Basic Accessors
        // ============================================================================
        suite.section("Basic Accessors");

        Rect r(10.0f, 20.0f, 100.0f, 200.0f);

        suite.assert_approximately_equal(r.left(), 10.0f, "left()");
        suite.assert_approximately_equal(r.top(), 20.0f, "top()");
        suite.assert_approximately_equal(r.width(), 100.0f, "width()");
        suite.assert_approximately_equal(r.height(), 200.0f, "height()");
        suite.assert_approximately_equal(r.right(), 110.0f, "right() = left + width");
        suite.assert_approximately_equal(r.bottom(), 220.0f, "bottom() = top + height");

        suite.assert_approximately_equal(r.min(), float2(10.0f, 20.0f), "min() returns position");
        suite.assert_approximately_equal(r.max(), float2(110.0f, 220.0f), "max() returns position + size");

        suite.assert_approximately_equal(r.center(), float2(60.0f, 120.0f), "center()");
        suite.assert_approximately_equal(r.extent(), float2(50.0f, 100.0f), "extent() half size");

        // ============================================================================
        // 3. Derived Properties
        // ============================================================================
        suite.section("Derived Properties");

        {
            Rect r(0.0f, 0.0f, 5.0f, 10.0f);
            suite.assert_approximately_equal(r.area(), 50.0f, "area()");
            suite.assert_approximately_equal(r.aspect_ratio(), 0.5f, "aspect_ratio() 5/10");
        }

        // Zero height should give aspect ratio 0
        {
            Rect r(0.0f, 0.0f, 5.0f, 0.0f);
            suite.assert_approximately_equal(r.aspect_ratio(), 0.0f, "aspect_ratio() zero height");
        }

        // is_valid
        {
            Rect valid(0.0f, 0.0f, 10.0f, 10.0f);
            suite.assert_true(valid.is_valid(), "is_valid() positive size");

            Rect zero_size(0.0f, 0.0f, 0.0f, 0.0f);
            suite.assert_true(zero_size.is_valid(), "is_valid() zero size is valid");

            Rect negative_size(0.0f, 0.0f, -5.0f, 10.0f);
            suite.assert_false(negative_size.is_valid(), "is_valid() negative width invalid");

            Rect inf_size(0.0f, 0.0f, std::numeric_limits<float>::infinity(), 10.0f);
            suite.assert_false(inf_size.is_valid(), "is_valid() infinite size invalid");
        }

        // ============================================================================
        // 4. Containment & Overlap Tests
        // ============================================================================
        suite.section("Containment & Overlap");

        r = Rect(10.0f, 10.0f, 100.0f, 100.0f); // left=10, top=10, right=110, bottom=110

        // Point containment
        suite.assert_true(r.contains(float2(10.0f, 10.0f)), "contains() point at left-top edge (included)");
        suite.assert_true(r.contains(float2(50.0f, 50.0f)), "contains() point inside");
        suite.assert_false(r.contains(float2(110.0f, 110.0f)), "contains() point at right-bottom edge (excluded)");
        suite.assert_false(r.contains(float2(0.0f, 0.0f)), "contains() point outside");

        // Rect containment
        Rect inner(20.0f, 20.0f, 50.0f, 50.0f); // inside
        Rect edge_touch(10.0f, 10.0f, 100.0f, 100.0f); // exactly same
        Rect partially_out(100.0f, 100.0f, 50.0f, 50.0f); // overlaps right-bottom

        suite.assert_true(r.contains(inner), "contains() inner rect");
        suite.assert_true(r.contains(edge_touch), "contains() identical rect (edges allowed)");
        suite.assert_false(r.contains(partially_out), "contains() partially outside");

        // Overlap
        Rect a(0.0f, 0.0f, 10.0f, 10.0f);
        Rect b(5.0f, 5.0f, 10.0f, 10.0f); // overlaps
        Rect c(10.0f, 10.0f, 10.0f, 10.0f); // touches at right-bottom corner (open edge, so no overlap)
        Rect d(20.0f, 20.0f, 10.0f, 10.0f); // separate

        suite.assert_true(a.overlaps(b), "overlaps() overlapping");
        suite.assert_false(a.overlaps(c), "overlaps() touching at corner (open edge)");
        suite.assert_false(a.overlaps(d), "overlaps() separate");

        // ============================================================================
        // 5. Mutating Operations
        // ============================================================================
        suite.section("Mutating Operations");

        // intersected
        {
            Rect a(0.0f, 0.0f, 10.0f, 10.0f);
            Rect b(5.0f, 5.0f, 10.0f, 10.0f);
            Rect inter = a.intersected(b);
            suite.assert_approximately_equal(inter.left(), 5.0f, "intersected left");
            suite.assert_approximately_equal(inter.top(), 5.0f, "intersected top");
            suite.assert_approximately_equal(inter.right(), 10.0f, "intersected right");
            suite.assert_approximately_equal(inter.bottom(), 10.0f, "intersected bottom");
        }

        // intersected with no overlap -> empty rect
        {
            Rect a(0.0f, 0.0f, 10.0f, 10.0f);
            Rect b(20.0f, 20.0f, 10.0f, 10.0f);
            Rect empty = a.intersected(b);
            suite.assert_true(empty.position == float2(0.0f, 0.0f) && empty.size == float2(0.0f, 0.0f),
                "intersected no overlap returns zero rect");
            suite.assert_true(empty.is_valid(), "empty rect (zero size) is valid");
        }

        // united
        {
            Rect a(0.0f, 0.0f, 10.0f, 10.0f);
            Rect b(5.0f, 5.0f, 15.0f, 15.0f);
            Rect u = a.united(b);
            suite.assert_approximately_equal(u.left(), 0.0f, "united left");
            suite.assert_approximately_equal(u.top(), 0.0f, "united top");
            suite.assert_approximately_equal(u.right(), 20.0f, "united right");
            suite.assert_approximately_equal(u.bottom(), 20.0f, "united bottom");
        }

        // expanded (uniform)
        {
            Rect r(10.0f, 10.0f, 100.0f, 100.0f);
            Rect expanded = r.expanded(5.0f);
            suite.assert_approximately_equal(expanded.left(), 5.0f, "expanded uniform left");
            suite.assert_approximately_equal(expanded.top(), 5.0f, "expanded uniform top");
            suite.assert_approximately_equal(expanded.width(), 110.0f, "expanded uniform width (+10)");
            suite.assert_approximately_equal(expanded.height(), 110.0f, "expanded uniform height (+10)");
        }

        // expanded (vector)
        {
            Rect r(10.0f, 10.0f, 100.0f, 100.0f);
            Rect expanded = r.expanded(float2(2.0f, 4.0f));
            suite.assert_approximately_equal(expanded.left(), 8.0f, "expanded vector left");
            suite.assert_approximately_equal(expanded.top(), 6.0f, "expanded vector top");
            suite.assert_approximately_equal(expanded.width(), 104.0f, "expanded vector width (+4)");
            suite.assert_approximately_equal(expanded.height(), 108.0f, "expanded vector height (+8)");
        }

        // translated
        {
            Rect r(10.0f, 10.0f, 100.0f, 100.0f);
            Rect translated = r.translated(float2(5.0f, -5.0f));
            suite.assert_approximately_equal(translated.position, float2(15.0f, 5.0f), "translated position");
            suite.assert_approximately_equal(translated.size, r.size, "translated size unchanged");
        }

        // ============================================================================
        // 6. Comparison Operators
        // ============================================================================
        suite.section("Comparison");

        {
            Rect a(1.0f, 2.0f, 3.0f, 4.0f);
            Rect b(1.0f, 2.0f, 3.0f, 4.0f);
            Rect c(1.0f, 2.0f, 3.0f, 5.0f);

            suite.assert_true(a == b, "Equal rectangles");
            suite.assert_false(a != b, "Not unequal");
            suite.assert_false(a == c, "Unequal rectangles");
            suite.assert_true(a != c, "Unequal returns true");
        }

        // ============================================================================
        // 7. Global Functions
        // ============================================================================
        suite.section("Global Functions");

        // rect_from_min_max
        {
            float2 min(1.0f, 2.0f), max(5.0f, 6.0f);
            Rect r = rect_from_min_max(min, max);
            suite.assert_approximately_equal(r.left(), 1.0f, "rect_from_min_max left");
            suite.assert_approximately_equal(r.width(), 4.0f, "rect_from_min_max width");
        }

        // rect_from_center_extents
        {
            float2 center(0.0f, 0.0f), half(2.0f, 3.0f);
            Rect r = rect_from_center_extents(center, half);
            suite.assert_approximately_equal(r.extent(), half, "rect_from_center_extents");
        }

        // rect_intersection
        {
            Rect a(0.0f, 0.0f, 10.0f, 10.0f), b(5.0f, 5.0f, 10.0f, 10.0f);
            Rect inter = rect_intersection(a, b);
            suite.assert_approximately_equal(inter, a.intersected(b), "rect_intersection");
        }

        // rect_union
        {
            Rect a(0.0f, 0.0f, 10.0f, 10.0f), b(5.0f, 5.0f, 10.0f, 10.0f);
            Rect u = rect_union(a, b);
            suite.assert_approximately_equal(u, a.united(b), "rect_union");
        }

        // rect_contains
        {
            Rect r(0.0f, 0.0f, 10.0f, 10.0f);
            suite.assert_true(rect_contains(r, float2(5.0f, 5.0f)), "rect_contains point");
            suite.assert_true(rect_contains(r, Rect(2.0f, 2.0f, 5.0f, 5.0f)), "rect_contains rect");
        }

        // rect_overlaps
        {
            Rect a(0.0f, 0.0f, 10.0f, 10.0f);
            Rect b(5.0f, 5.0f, 10.0f, 10.0f);
            suite.assert_true(rect_overlaps(a, b), "rect_overlaps");
        }

        // rect_expand
        {
            Rect r(0.0f, 0.0f, 10.0f, 10.0f);
            suite.assert_approximately_equal(rect_expand(r, 2.0f), r.expanded(2.0f), "rect_expand uniform");
            suite.assert_approximately_equal(rect_expand(r, float2(1.0f, 2.0f)), r.expanded(float2(1.0f, 2.0f)), "rect_expand vector");
        }

        // rect_translate
        {
            Rect r(0.0f, 0.0f, 10.0f, 10.0f);
            suite.assert_approximately_equal(rect_translate(r, float2(5.0f, 5.0f)), r.translated(float2(5.0f, 5.0f)), "rect_translate");
        }

        // ============================================================================
        // 8. Constants
        // ============================================================================
        suite.section("Constants");

        suite.assert_approximately_equal(Rect_Zero, Rect(0.0f, 0.0f, 0.0f, 0.0f), "Rect_Zero");
        suite.assert_approximately_equal(Rect_Unit, Rect(0.0f, 0.0f, 1.0f, 1.0f), "Rect_Unit");

        // ============================================================================
        // 9. Edge Cases
        // ============================================================================
        suite.section("Edge Cases");

        // Expanding a zero-sized rectangle
        {
            Rect zero;
            Rect expanded = zero.expanded(5.0f);
            suite.assert_approximately_equal(expanded, Rect(-5.0f, -5.0f, 10.0f, 10.0f), "Expand zero rect");
        }

        // Intersection of rectangles with one completely inside the other
        {
            Rect outer(0.0f, 0.0f, 10.0f, 10.0f);
            Rect inner(2.0f, 2.0f, 5.0f, 5.0f);
            Rect inter = outer.intersected(inner);
            suite.assert_approximately_equal(inter, inner, "Intersection when one inside the other");
        }

        // Union of overlapping rectangles already tested, additional test: union with empty rect
        {
            Rect a(1.0f, 2.0f, 3.0f, 4.0f);
            Rect empty;
            Rect u = a.united(empty);
            suite.assert_approximately_equal(u, a, "Union with empty rect");
        }
    }
}
