#include <Geometry/TwoDimensions/Constructs/PolynomialInYEqualsX.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba
{

namespace TwoDimensions
{

TEST(PolynomialInYEqualsXTest, PolynomialInYEqualsXCanBeCreated)
{
    PolynomialInYEqualsX<3>{1,2,3};
}

TEST(PolynomialInYEqualsXTest, GetPointsWorks)
{
    PolynomialInYEqualsX<3> polynomial{1,2,3};
    Points points(polynomial.getPoints(-2, 2, 1));

    ASSERT_EQ(5U, points.size());
    EXPECT_EQ(Point(3,-2), points.at(0));
    EXPECT_EQ(Point(2,-1), points.at(1));
    EXPECT_EQ(Point(3,0), points.at(2));
    EXPECT_EQ(Point(6,1), points.at(3));
    EXPECT_EQ(Point(11,2), points.at(4));
}

TEST(PolynomialInYEqualsXTest, CalculateYfromXWorks)
{
    PolynomialInYEqualsX<3> polynomial{1,2,3};

    EXPECT_DOUBLE_EQ(38, polynomial.calculateXfromY(5));
}

TEST(PolynomialInYEqualsXTest, GetValueOfFirstDerivativeWorks)
{
    PolynomialInYEqualsX<3> polynomial{1,2,3};

    EXPECT_DOUBLE_EQ(0.25, polynomial.getSlopeAt(1));
}

}

}
