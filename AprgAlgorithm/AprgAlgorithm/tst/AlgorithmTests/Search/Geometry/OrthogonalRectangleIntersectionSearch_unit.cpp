#include <Algorithm/Search/Geometry/OrthogonalRectangleIntersectionSearch.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SearchForTest = OrthogonalRectangleIntersectionSearch<double>;
}

TEST(OrthogonalRectangleIntersectionSearchTest, GetIntersectingPointsWorksWhen2RectanglesAreInACross) {
    SearchForTest search;
    search.addRectangle({{-2, -1}, {2, 1}});
    search.addRectangle({{-1, -2}, {1, 2}});

    auto rectanglesToVerify(search.getIntersectingRectangles());

    SearchForTest::Rectangles rectanglesToExpect{{{-2, -1}, {2, 1}}, {{-1, -2}, {1, 2}}};
    EXPECT_EQ(rectanglesToExpect, rectanglesToVerify);
}

TEST(OrthogonalRectangleIntersectionSearchTest, GetIntersectingPointsWorksOnComplicatedExample) {
    SearchForTest search;
    search.addRectangle({{0, -1}, {7, 1}});
    search.addRectangle({{1, -3}, {5, -2}});
    search.addRectangle({{2, 2}, {6, 4}});
    search.addRectangle({{3, 0}, {4, 5}});

    auto rectanglesToVerify(search.getIntersectingRectangles());

    SearchForTest::Rectangles rectanglesToExpect{{{0, -1}, {7, 1}}, {{2, 2}, {6, 4}}, {{3, 0}, {4, 5}}};
    EXPECT_EQ(rectanglesToExpect, rectanglesToVerify);
}

}  // namespace algorithm

}  // namespace alba
