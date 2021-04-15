#include <TwoDimensions/Hyperbola.hpp>
#include <Math/AlbaMathHelper.hpp>

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
    ASSERT_EQ(22u, points.size());
    EXPECT_EQ(Point(6,3.4641016151377543864), points[0]);
    EXPECT_EQ(Point(5,2.6666666666666669627), points[1]);
    EXPECT_EQ(Point(4.2426406871192856585,2), points[2]);
    EXPECT_EQ(Point(4,1.7638342073763935147), points[3]);
    EXPECT_EQ(Point(3.3541019662496847076,1), points[4]);
    EXPECT_EQ(Point(3,0), points[5]);
    EXPECT_EQ(Point(3.3541019662496847076,-1), points[6]);
    EXPECT_EQ(Point(4,-1.7638342073763935147), points[7]);
    EXPECT_EQ(Point(4.2426406871192856585,-2), points[8]);
    EXPECT_EQ(Point(5,-2.6666666666666669627), points[9]);
    EXPECT_EQ(Point(6,-3.4641016151377543864), points[10]);
    EXPECT_EQ(Point(-6,3.4641016151377543864), points[11]);
    EXPECT_EQ(Point(-5,2.6666666666666669627), points[12]);
    EXPECT_EQ(Point(-4.2426406871192856585,2), points[13]);
    EXPECT_EQ(Point(-4,1.7638342073763935147), points[14]);
    EXPECT_EQ(Point(-3.3541019662496847076,1), points[15]);
    EXPECT_EQ(Point(-3,0), points[16]);
    EXPECT_EQ(Point(-3.3541019662496847076,-1), points[17]);
    EXPECT_EQ(Point(-4,-1.7638342073763935147), points[18]);
    EXPECT_EQ(Point(-4.2426406871192856585,-2), points[19]);
    EXPECT_EQ(Point(-5,-2.6666666666666669627), points[20]);
    EXPECT_EQ(Point(-6,-3.4641016151377543864), points[21]);
}

TEST(HyperbolaTest, AreaTraversalIsCorrect)
{
    //traversal
}

}

}
