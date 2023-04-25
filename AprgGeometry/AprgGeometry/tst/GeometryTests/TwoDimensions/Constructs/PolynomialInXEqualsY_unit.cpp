#include <Geometry/TwoDimensions/Constructs/PolynomialInXEqualsY.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace TwoDimensions {

TEST(PolynomialInXEqualsYTest, PolynomialInXEqualsYCanBeCreated) { PolynomialInXEqualsY<3>{1, 2, 3}; }

TEST(PolynomialInXEqualsYTest, GetPointsWorks) {
    PolynomialInXEqualsY<3> polynomial{1, 2, 3};
    Points points(polynomial.getPoints(-2, 2, 1));

    ASSERT_EQ(5U, points.size());
    EXPECT_EQ(Point(-2, 3), points.at(0));
    EXPECT_EQ(Point(-1, 2), points.at(1));
    EXPECT_EQ(Point(0, 3), points.at(2));
    EXPECT_EQ(Point(1, 6), points.at(3));
    EXPECT_EQ(Point(2, 11), points.at(4));
}

TEST(PolynomialInXEqualsYTest, CalculateYfromXWorks) {
    PolynomialInXEqualsY<3> polynomial{1, 2, 3};

    EXPECT_DOUBLE_EQ(38, polynomial.calculateYfromX(5));
}

TEST(PolynomialInXEqualsYTest, GetValueOfFirstDerivativeWorks) {
    PolynomialInXEqualsY<3> polynomial{1, 2, 3};

    EXPECT_DOUBLE_EQ(12, polynomial.getSlopeAt(5));
}

}  // namespace TwoDimensions

}  // namespace alba
