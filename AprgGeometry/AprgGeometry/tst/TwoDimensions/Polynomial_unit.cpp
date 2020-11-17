#include <TwoDimensions/Parabola.hpp>
#include <TwoDimensions/Polynomial.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba;
using namespace std;

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
    ASSERT_EQ(11u, points.size());
    EXPECT_EQ(Point(-2,3), points[0]);
    EXPECT_EQ(Point(-1,2), points[1]);
    EXPECT_EQ(Point(0,3), points[2]);
    EXPECT_EQ(Point((double)1/3,4), points[3]);
    EXPECT_EQ(Point((double)2/3,5), points[4]);
    EXPECT_EQ(Point(1,6), points[5]);
    EXPECT_EQ(Point(1.2,7), points[6]);
    EXPECT_EQ(Point(1.4,8), points[7]);
    EXPECT_EQ(Point(1.6,9), points[8]);
    EXPECT_EQ(Point(1.8,10), points[9]);
    EXPECT_EQ(Point(2,11), points[10]);
}

TEST(ParabolaTest, GetPointsAreCorrectWhenBoundariesAreReversed)
{
    Parabola parabola{1,2,3};

    Points points(parabola.getPoints(2, -2, 1));
    ASSERT_EQ(11u, points.size());
    EXPECT_EQ(Point(2,11), points[0]);
    EXPECT_EQ(Point(1.8,10), points[1]);
    EXPECT_EQ(Point(1.6,9), points[2]);
    EXPECT_EQ(Point(1.4,8), points[3]);
    EXPECT_EQ(Point(1.2,7), points[4]);
    EXPECT_EQ(Point(1,6), points[5]);
    EXPECT_EQ(Point((double)2/3,5), points[6]);
    EXPECT_EQ(Point((double)1/3,4), points[7]);
    EXPECT_EQ(Point(0,3), points[8]);
    EXPECT_EQ(Point(-1,2), points[9]);
    EXPECT_EQ(Point(-2,3), points[10]);
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

TEST(ParabolaTest, GetTangentLineIsCorrect)
{
    Parabola parabola{1,2,3};

    Line expectedLine1(parabola.getTangentLineAt(-1));
    Line expectedLine2(parabola.getTangentLineAt(0));
    Line expectedLine3(parabola.getTangentLineAt(1));

    EXPECT_EQ(LineType::Horizontal, expectedLine1.getType());
    EXPECT_EQ(2, expectedLine1.getYIntercept());
    EXPECT_EQ(0, expectedLine1.getXIntercept());
    EXPECT_EQ(0, expectedLine1.getSlope());

    EXPECT_EQ(LineType::WithPositiveSlope, expectedLine2.getType());
    EXPECT_EQ(3, expectedLine2.getYIntercept());
    EXPECT_EQ(-1.5, expectedLine2.getXIntercept());
    EXPECT_EQ(2, expectedLine2.getSlope());

    EXPECT_EQ(LineType::WithPositiveSlope, expectedLine3.getType());
    EXPECT_EQ(2, expectedLine3.getYIntercept());
    EXPECT_EQ(-0.5, expectedLine3.getXIntercept());
    EXPECT_EQ(4, expectedLine3.getSlope());
}
