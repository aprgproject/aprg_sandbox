#include <TwoDimensions/Parabola.hpp>
#include <TwoDimensions/Polynomial.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace TwoDimensions
{

TEST(PolynomialTest, PolynomialCanBeCreated)
{
    Polynomial<3> polynomial{3,2,1};
}

TEST(ParabolaTest, ParabolaCanBeCreated)
{
    Parabola parabola{1,2,3};
}

TEST(ParabolaTest, GetPointsAreCorrect)
{
    Parabola parabola{1,2,3};
    Points points(parabola.getPoints(-2, 2, 1));

    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(-2,3), points[0]);
    EXPECT_EQ(Point(-1,2), points[1]);
    EXPECT_EQ(Point(0,3), points[2]);
    EXPECT_EQ(Point(1,6), points[3]);
    EXPECT_EQ(Point(2,11), points[4]);
}

TEST(ParabolaTest, GetPointsAreCorrectWhenBoundariesAreReversed)
{
    Parabola parabola{1,2,3};
    Points points(parabola.getPoints(2, -2, 1));

    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(2,11), points[0]);
    EXPECT_EQ(Point(1,6), points[1]);
    EXPECT_EQ(Point(0,3), points[2]);
    EXPECT_EQ(Point(-1,2), points[3]);
    EXPECT_EQ(Point(-2,3), points[4]);
}

TEST(ParabolaTest, GetSlopeIsCorrect)
{
    Parabola parabola{1,2,3};

    EXPECT_EQ(-198, parabola.getSlopeAt(-100));
    EXPECT_EQ(-18, parabola.getSlopeAt(-10));
    EXPECT_EQ(0, parabola.getSlopeAt(-1));
    EXPECT_EQ(2, parabola.getSlopeAt(0));
    EXPECT_EQ(4, parabola.getSlopeAt(1));
    EXPECT_EQ(22, parabola.getSlopeAt(10));
    EXPECT_EQ(202, parabola.getSlopeAt(100));
}

}

}
