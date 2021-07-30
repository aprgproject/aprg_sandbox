#include <TwoDimensions/Parabola.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace TwoDimensions
{

TEST(ParabolaTest, ParabolaCanBeCreated)
{
    Parabola{1,2,3};
}

TEST(ParabolaTest, GetPointsAreCorrect)
{
    Parabola parabola{1,2,3};
    Points points(parabola.getPoints(-2, 2, 1));

    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(-2,3), points.at(0));
    EXPECT_EQ(Point(-1,2), points.at(1));
    EXPECT_EQ(Point(0,3), points.at(2));
    EXPECT_EQ(Point(1,6), points.at(3));
    EXPECT_EQ(Point(2,11), points.at(4));
}

TEST(ParabolaTest, GetPointsAreCorrectWhenBoundariesAreReversed){
    Parabola parabola{1,2,3};
    Points points(parabola.getPoints(2, -2, 1));

    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(2,11), points.at(0));
    EXPECT_EQ(Point(1,6), points.at(1));
    EXPECT_EQ(Point(0,3), points.at(2));
    EXPECT_EQ(Point(-1,2), points.at(3));
    EXPECT_EQ(Point(-2,3), points.at(4));
}

TEST(ParabolaTest, GetSlopeIsCorrect){
    Parabola parabola{1,2,3};

    EXPECT_DOUBLE_EQ(-198, parabola.getSlopeAt(-100));    EXPECT_DOUBLE_EQ(-18, parabola.getSlopeAt(-10));
    EXPECT_DOUBLE_EQ(0, parabola.getSlopeAt(-1));
    EXPECT_DOUBLE_EQ(2, parabola.getSlopeAt(0));
    EXPECT_DOUBLE_EQ(4, parabola.getSlopeAt(1));
    EXPECT_DOUBLE_EQ(22, parabola.getSlopeAt(10));
    EXPECT_DOUBLE_EQ(202, parabola.getSlopeAt(100));
}

TEST(ParabolaTest, GetCoefficientsWorks)
{
    Parabola parabola{1,2,3};

    EXPECT_DOUBLE_EQ(1, parabola.getA());
    EXPECT_DOUBLE_EQ(2, parabola.getB());
    EXPECT_DOUBLE_EQ(3, parabola.getC());
}

TEST(ParabolaTest, GetVertexWorks)
{
    Parabola parabola1{1,2,4};
    Parabola parabola2{1,-1,-6};

    EXPECT_EQ(Point(-1, 3), parabola1.getVertex());
    EXPECT_EQ(Point(0.5, -6.25), parabola2.getVertex());
}

}

}
