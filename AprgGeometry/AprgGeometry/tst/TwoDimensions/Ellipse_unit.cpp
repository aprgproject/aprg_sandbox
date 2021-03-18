#include <TwoDimensions/Ellipse.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba;
using namespace std;


TEST(EllipseTest, EmptyEllipse)
{
    Ellipse ellipse;

    EXPECT_EQ(Point(0,0), ellipse.getCenter());
    EXPECT_DOUBLE_EQ(0, ellipse.getAValue());
    EXPECT_DOUBLE_EQ(0, ellipse.getBValue());
    EXPECT_DOUBLE_EQ(0, ellipse.getCValue());
    EXPECT_NE(0, ellipse.getEccentricity());
    EXPECT_NE(0, ellipse.getSemiLactusRectum());
    EXPECT_DOUBLE_EQ(0, ellipse.getArea());

    Points points(ellipse.getPointsForCircumference(1));
    ASSERT_TRUE(points.empty());
}

TEST(EllipseTest, EllipseAtOriginWithRadius)
{
    Ellipse ellipse(Point(0, 0), 3, 2);

    EXPECT_EQ(Point(0, 0), ellipse.getCenter());
    EXPECT_DOUBLE_EQ(3, ellipse.getAValue());
    EXPECT_DOUBLE_EQ(2, ellipse.getBValue());
    EXPECT_DOUBLE_EQ(2.2360679774997898, ellipse.getCValue());
    EXPECT_DOUBLE_EQ(0.7453559924999299, ellipse.getEccentricity());
    EXPECT_DOUBLE_EQ(1.3333333333333333, ellipse.getSemiLactusRectum());
    EXPECT_DOUBLE_EQ(18.849555921538759, ellipse.getArea());

    Points points(ellipse.getPointsForCircumference(1));
    ASSERT_EQ(16u, points.size());
    EXPECT_EQ(Point(3,0), points[0]);
    EXPECT_EQ(Point(2.5980762113533160118,1), points[1]);
    EXPECT_EQ(Point(2,1.490711984999859796), points[2]);
    EXPECT_EQ(Point(1,1.8856180831641267126), points[3]);
    EXPECT_EQ(Point(0,2), points[4]);
    EXPECT_EQ(Point(-1,1.8856180831641267126), points[5]);
    EXPECT_EQ(Point(-2,1.490711984999859796), points[6]);
    EXPECT_EQ(Point(-2.5980762113533160118,1), points[7]);
    EXPECT_EQ(Point(-3,0), points[8]);
    EXPECT_EQ(Point(-2.5980762113533160118,-1), points[9]);
    EXPECT_EQ(Point(-2,-1.490711984999859796), points[10]);
    EXPECT_EQ(Point(-1,-1.8856180831641267126), points[11]);
    EXPECT_EQ(Point(0,-2), points[12]);
    EXPECT_EQ(Point(1,-1.8856180831641267126), points[13]);
    EXPECT_EQ(Point(2,-1.490711984999859796), points[14]);
    EXPECT_EQ(Point(2.5980762113533160118,-1), points[15]);
}

TEST(EllipseTest, AreaTraversalIsCorrect)
{
    //traversal
}


