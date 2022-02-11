#include <Common/Math/AlbaMathHelper.hpp>
#include <Geometry/TwoDimensions/Hyperbola.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace std;

namespace alba
{

namespace TwoDimensions
{

TEST(HyperbolaTest, EmptyHyperbola)
{
    Hyperbola hyperbola;

    EXPECT_EQ(Point(0,0), hyperbola.getCenter());
    EXPECT_DOUBLE_EQ(0, hyperbola.getAValue());
    EXPECT_DOUBLE_EQ(0, hyperbola.getBValue());
    EXPECT_DOUBLE_EQ(0, hyperbola.getCValue());
    EXPECT_NE(0, hyperbola.getEccentricity());
    EXPECT_NE(0, hyperbola.getSemiLactusRectum());

    Points points(hyperbola.getPointsForShape(1));
    ASSERT_TRUE(points.empty());
}

TEST(HyperbolaTest, HyperbolaAtOriginWithRadius)
{
    Hyperbola hyperbola(Point(0, 0), 3, 2);

    EXPECT_EQ(Point(0, 0), hyperbola.getCenter());
    EXPECT_DOUBLE_EQ(3, hyperbola.getAValue());
    EXPECT_DOUBLE_EQ(2, hyperbola.getBValue());
    EXPECT_DOUBLE_EQ(3.6055512754639891, hyperbola.getCValue());
    EXPECT_DOUBLE_EQ(1.2018504251546631, hyperbola.getEccentricity());
    EXPECT_DOUBLE_EQ(1.3333333333333333, hyperbola.getSemiLactusRectum());

    Points points(hyperbola.getPointsForShape(1));
    ASSERT_EQ(22U, points.size());
    EXPECT_EQ(Point(6,3.4641016151377543864), points.at(0));
    EXPECT_EQ(Point(5,2.6666666666666669627), points.at(1));
    EXPECT_EQ(Point(4.2426406871192856585,2), points.at(2));
    EXPECT_EQ(Point(4,1.7638342073763935147), points.at(3));
    EXPECT_EQ(Point(3.3541019662496847076,1), points.at(4));
    EXPECT_EQ(Point(3,0), points.at(5));
    EXPECT_EQ(Point(3.3541019662496847076,-1), points.at(6));
    EXPECT_EQ(Point(4,-1.7638342073763935147), points.at(7));
    EXPECT_EQ(Point(4.2426406871192856585,-2), points.at(8));
    EXPECT_EQ(Point(5,-2.6666666666666669627), points.at(9));
    EXPECT_EQ(Point(6,-3.4641016151377543864), points.at(10));
    EXPECT_EQ(Point(-6,3.4641016151377543864), points.at(11));
    EXPECT_EQ(Point(-5,2.6666666666666669627), points.at(12));
    EXPECT_EQ(Point(-4.2426406871192856585,2), points.at(13));
    EXPECT_EQ(Point(-4,1.7638342073763935147), points.at(14));
    EXPECT_EQ(Point(-3.3541019662496847076,1), points.at(15));
    EXPECT_EQ(Point(-3,0), points.at(16));
    EXPECT_EQ(Point(-3.3541019662496847076,-1), points.at(17));
    EXPECT_EQ(Point(-4,-1.7638342073763935147), points.at(18));
    EXPECT_EQ(Point(-4.2426406871192856585,-2), points.at(19));
    EXPECT_EQ(Point(-5,-2.6666666666666669627), points.at(20));
    EXPECT_EQ(Point(-6,-3.4641016151377543864), points.at(21));
}

TEST(HyperbolaTest, GetFociWorks)
{
    Hyperbola hyperbola1(Point(0, 0), 1, 1);
    Hyperbola hyperbola2(Point(0, 0), 3, 4);
    Hyperbola hyperbola3(Point(0, 0), -3, -4);

    Points foci1(hyperbola1.getFoci());
    Points foci2(hyperbola2.getFoci());
    Points foci3(hyperbola3.getFoci());

    ASSERT_EQ(2U, foci2.size());
    EXPECT_EQ(Point(1.41421356237309514547462185874, 0), foci1.at(0));
    EXPECT_EQ(Point(-1.41421356237309514547462185874, 0), foci1.at(1));
    ASSERT_EQ(2U, foci2.size());
    EXPECT_EQ(Point(5, 0), foci2.at(0));
    EXPECT_EQ(Point(-5, 0), foci2.at(1));
    ASSERT_EQ(2U, foci3.size());
    EXPECT_EQ(Point(0, 5), foci3.at(0));
    EXPECT_EQ(Point(0, -5), foci3.at(1));
}

TEST(HyperbolaTest, GetVerticesWorks)
{
    Hyperbola hyperbola1(Point(0, 0), 1, 1);
    Hyperbola hyperbola2(Point(0, 0), 3, 4);
    Hyperbola hyperbola3(Point(0, 0), -3, -4);

    Points vertices1(hyperbola1.getVertices());
    Points vertices2(hyperbola2.getVertices());
    Points vertices3(hyperbola3.getVertices());

    ASSERT_EQ(2U, vertices2.size());
    EXPECT_EQ(Point(1, 0), vertices1.at(0));
    EXPECT_EQ(Point(-1, 0), vertices1.at(1));
    ASSERT_EQ(2U, vertices2.size());
    EXPECT_EQ(Point(3, 0), vertices2.at(0));
    EXPECT_EQ(Point(-3, 0), vertices2.at(1));
    ASSERT_EQ(2U, vertices3.size());
    EXPECT_EQ(Point(0, 4), vertices3.at(0));
    EXPECT_EQ(Point(0, -4), vertices3.at(1));
}

TEST(HyperbolaTest, GetAsymptotesWorks)
{
    Hyperbola hyperbola1(Point(0, 0), 1, 1);
    Hyperbola hyperbola2(Point(0, 0), 3, 4);
    Hyperbola hyperbola3(Point(0, 0), -3, -4);

    Lines asymptotes1(hyperbola1.getAsymptotes());
    Lines asymptotes2(hyperbola2.getAsymptotes());
    Lines asymptotes3(hyperbola3.getAsymptotes());

    ASSERT_EQ(2U, asymptotes1.size());
    EXPECT_EQ(Line(1, 1, 0), asymptotes1.at(0));
    EXPECT_EQ(Line(1, -1, 0), asymptotes1.at(1));
    ASSERT_EQ(2U, asymptotes2.size());
    EXPECT_EQ(Line(4, 3, 0), asymptotes2.at(0));
    EXPECT_EQ(Line(4, -3, 0), asymptotes2.at(1));
    ASSERT_EQ(2U, asymptotes3.size());
    EXPECT_EQ(Line(-4, -3, 0), asymptotes3.at(0));
    EXPECT_EQ(Line(-4, 3, 0), asymptotes3.at(1));
}

TEST(HyperbolaTest, AreaTraversalIsCorrect)
{
    //traversal
}

}

}
