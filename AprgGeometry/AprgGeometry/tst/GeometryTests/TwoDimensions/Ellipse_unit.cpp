#include <Common/Math/AlbaMathHelper.hpp>
#include <Geometry/TwoDimensions/Ellipse.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace std;

namespace alba
{

namespace TwoDimensions
{


TEST(EllipseTest, EmptyEllipse)
{
    Ellipse ellipse;

    EXPECT_EQ(Point(0,0), ellipse.getCenter());
    EXPECT_DOUBLE_EQ(0, ellipse.getAValue());
    EXPECT_DOUBLE_EQ(0, ellipse.getBValue());
    EXPECT_DOUBLE_EQ(1, ellipse.getCValue());
    EXPECT_NE(0, ellipse.getEccentricity());
    EXPECT_NE(0, ellipse.getSemiLatusRectum());
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
    EXPECT_DOUBLE_EQ(1.3333333333333333, ellipse.getSemiLatusRectum());
    EXPECT_DOUBLE_EQ(18.849555921538759, ellipse.getArea());

    Points points(ellipse.getPointsForCircumference(1));
    ASSERT_EQ(16U, points.size());
    EXPECT_EQ(Point(3,0), points.at(0));
    EXPECT_EQ(Point(2.5980762113533160118,1), points.at(1));
    EXPECT_EQ(Point(2,1.490711984999859796), points.at(2));
    EXPECT_EQ(Point(1,1.8856180831641267126), points.at(3));
    EXPECT_EQ(Point(0,2), points.at(4));
    EXPECT_EQ(Point(-1,1.8856180831641267126), points.at(5));
    EXPECT_EQ(Point(-2,1.490711984999859796), points.at(6));
    EXPECT_EQ(Point(-2.5980762113533160118,1), points.at(7));
    EXPECT_EQ(Point(-3,0), points.at(8));
    EXPECT_EQ(Point(-2.5980762113533160118,-1), points.at(9));
    EXPECT_EQ(Point(-2,-1.490711984999859796), points.at(10));
    EXPECT_EQ(Point(-1,-1.8856180831641267126), points.at(11));
    EXPECT_EQ(Point(0,-2), points.at(12));
    EXPECT_EQ(Point(1,-1.8856180831641267126), points.at(13));
    EXPECT_EQ(Point(2,-1.490711984999859796), points.at(14));
    EXPECT_EQ(Point(2.5980762113533160118,-1), points.at(15));
}

TEST(EllipseTest, IsInsideWorks)
{
    Ellipse ellipse(Point(0, 0), 5, 4);

    EXPECT_TRUE(ellipse.isInside(Point(0, 0)));
    EXPECT_FALSE(ellipse.isInside(Point(5, 5)));
}

TEST(EllipseTest, GetFociWorks)
{
    Ellipse ellipse1(Point(0, 0), 1, 1);
    Ellipse ellipse2(Point(0, 0), 4, 5);
    Ellipse ellipse3(Point(0, 0), 5, 4);

    Points foci1(ellipse1.getFoci());
    Points foci2(ellipse2.getFoci());
    Points foci3(ellipse3.getFoci());

    ASSERT_EQ(1U, foci1.size());
    EXPECT_EQ(Point(0, 0), foci1.at(0));
    ASSERT_EQ(2U, foci2.size());
    EXPECT_EQ(Point(0, 3), foci2.at(0));
    EXPECT_EQ(Point(0, -3), foci2.at(1));
    ASSERT_EQ(2U, foci3.size());
    EXPECT_EQ(Point(3, 0), foci3.at(0));
    EXPECT_EQ(Point(-3, 0), foci3.at(1));
}

TEST(EllipseTest, GetMajorVerticesWorks)
{
    Ellipse ellipse1(Point(0, 0), 1, 1);
    Ellipse ellipse2(Point(0, 0), 4, 5);
    Ellipse ellipse3(Point(0, 0), 5, 4);

    Points majorVertices1(ellipse1.getMajorVertices());
    Points majorVertices2(ellipse2.getMajorVertices());
    Points majorVertices3(ellipse3.getMajorVertices());

    EXPECT_TRUE(majorVertices1.empty());
    ASSERT_EQ(2U, majorVertices2.size());
    EXPECT_EQ(Point(0, 5), majorVertices2.at(0));
    EXPECT_EQ(Point(0, -5), majorVertices2.at(1));
    ASSERT_EQ(2U, majorVertices3.size());
    EXPECT_EQ(Point(5, 0), majorVertices3.at(0));
    EXPECT_EQ(Point(-5, 0), majorVertices3.at(1));
}

TEST(EllipseTest, GetMinorVerticesWorks)
{
    Ellipse ellipse1(Point(0, 0), 1, 1);
    Ellipse ellipse2(Point(0, 0), 4, 5);
    Ellipse ellipse3(Point(0, 0), 5, 4);

    Points minorVertices1(ellipse1.getMinorVertices());
    Points minorVertices2(ellipse2.getMinorVertices());
    Points minorVertices3(ellipse3.getMinorVertices());

    EXPECT_TRUE(minorVertices1.empty());
    ASSERT_EQ(2U, minorVertices2.size());
    EXPECT_EQ(Point(4, 0), minorVertices2.at(0));
    EXPECT_EQ(Point(-4, 0), minorVertices2.at(1));
    ASSERT_EQ(2U, minorVertices3.size());
    EXPECT_EQ(Point(0, 4), minorVertices3.at(0));
    EXPECT_EQ(Point(0, -4), minorVertices3.at(1));
}

TEST(EllipseTest, GetMajorAxisWorks)
{
    Ellipse ellipse1(Point(0, 0), 1, 1);
    Ellipse ellipse2(Point(0, 0), 4, 5);
    Ellipse ellipse3(Point(0, 0), 5, 4);

    Line majorAxis1(ellipse1.getMajorAxis());
    Line majorAxis2(ellipse2.getMajorAxis());
    Line majorAxis3(ellipse3.getMajorAxis());

    EXPECT_EQ(Line(), majorAxis1);
    EXPECT_EQ(Line(10, 0, 0), majorAxis2);
    EXPECT_EQ(Line(0, 10, 0), majorAxis3);
}

TEST(EllipseTest, GetMinorAxisWorks)
{
    Ellipse ellipse1(Point(0, 0), 1, 1);
    Ellipse ellipse2(Point(0, 0), 4, 5);
    Ellipse ellipse3(Point(0, 0), 5, 4);

    Line minorAxis1(ellipse1.getMinorAxis());
    Line minorAxis2(ellipse2.getMinorAxis());
    Line minorAxis3(ellipse3.getMinorAxis());

    EXPECT_EQ(Line(), minorAxis1);
    EXPECT_EQ(Line(0, 8, 0), minorAxis2);
    EXPECT_EQ(Line(-8, 0, 0), minorAxis3);
}

TEST(EllipseTest, AreaTraversalIsCorrect)
{
    //traversal
}

}

}
