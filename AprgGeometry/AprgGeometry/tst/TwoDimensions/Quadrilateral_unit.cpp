#include <TwoDimensions/Quadrilateral.hpp>

#include <gtest/gtest.h>

using namespace alba::Dimensionless;
using namespace std;

namespace alba
{

namespace TwoDimensions
{

TEST(QuadrilateralTest, QuadilateralCanBeCreated)
{
    Quadrilateral quadrilateral(Point(1,1), Point(2,3), Point(0,17), Point(-100, 4));
}

TEST(QuadrilateralTest, GetPointsAreCorrect)
{
    Quadrilateral quadrilateral(Point(-2,0), Point(0,-2), Point(2,0), Point(0,2));
    Points points(quadrilateral.getPoints(1));

    ASSERT_EQ(8u, points.size());
    EXPECT_EQ(Point(-2,0), points[0]);
    EXPECT_EQ(Point(-1,-1), points[1]);
    EXPECT_EQ(Point(0,-2), points[2]);
    EXPECT_EQ(Point(1,-1), points[3]);
    EXPECT_EQ(Point(2,0), points[4]);
    EXPECT_EQ(Point(1,1), points[5]);
    EXPECT_EQ(Point(0,2), points[6]);
    EXPECT_EQ(Point(-1,1), points[7]);
}

TEST(QuadrilateralTest, DISABLED_PointsInQuadilateralAreCorrectWhenOutOfOrderVerticesAreUsed)
{
    //how can this be done?
    Quadrilateral quadrilateral(Point(-2,0), Point(2,0), Point(0,2), Point(0,-2));
    Points points(quadrilateral.getPoints(1));

    ASSERT_EQ(8u, points.size());
    EXPECT_EQ(Point(-2,0), points[0]);
    EXPECT_EQ(Point(-1,-1), points[1]);
    EXPECT_EQ(Point(0,-2), points[2]);
    EXPECT_EQ(Point(1,-1), points[3]);
    EXPECT_EQ(Point(2,0), points[4]);
    EXPECT_EQ(Point(1,1), points[5]);
    EXPECT_EQ(Point(0,2), points[6]);
    EXPECT_EQ(Point(-1,1), points[7]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor1YGroup)
{
    Quadrilateral quadrilateral(Point(1,1), Point(2,1), Point(4,1), Point(5,1));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea)
    {
        pointsInAreaTraversal.emplace_back(pointInArea);
    });

    ASSERT_EQ(5u, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(1,1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(2,1), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(3,1), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(4,1), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(5,1), pointsInAreaTraversal[4]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor2YGroupsInFirstPattern)
{
    Quadrilateral quadrilateral(Point(3,1), Point(1,3), Point(3,3), Point(5,3));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea)
    {
        pointsInAreaTraversal.emplace_back(pointInArea);
    });

    ASSERT_EQ(9u, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(3,1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(2,2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(3,2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(4,2), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(1,3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(2,3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(3,3), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(4,3), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(5,3), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor2YGroupsInSecondPattern)
{
    Quadrilateral quadrilateral(Point(2,2), Point(2,4), Point(4,2), Point(4,4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea)
    {
        pointsInAreaTraversal.emplace_back(pointInArea);
    });

    ASSERT_EQ(9u, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(2,2), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(3,2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(4,2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(2,3), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(3,3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(4,3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(2,4), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(3,4), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(4,4), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor2YGroupsInThirdPattern)
{
    Quadrilateral quadrilateral(Point(3,5), Point(1,3), Point(3,3), Point(5,3));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea)
    {
        pointsInAreaTraversal.emplace_back(pointInArea);
    });

    ASSERT_EQ(9u, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(1,3), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(2,3), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(3,3), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(4,3), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(5,3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(2,4), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(3,4), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(4,4), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(3,5), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInFirstPattern)
{
    Quadrilateral quadrilateral(Point(2,1), Point(4,3), Point(2,4), Point(4,4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea)
    {
        pointsInAreaTraversal.emplace_back(pointInArea);
    });

    ASSERT_EQ(9u, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(2,1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(2,2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(3,2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(2,3), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(3,3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(4,3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(2,4), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(3,4), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(4,4), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInSecondPattern)
{
    Quadrilateral quadrilateral(Point(4,1), Point(2,3), Point(2,4), Point(4,4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea)
    {
        pointsInAreaTraversal.emplace_back(pointInArea);
    });

    ASSERT_EQ(9u, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(4,1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(3,2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(4,2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(2,3), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(3,3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(4,3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(2,4), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(3,4), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(4,4), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInThirdPattern)
{
    Quadrilateral quadrilateral(Point(3,1), Point(1,2), Point(5,2), Point(3,3));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea)
    {
        pointsInAreaTraversal.emplace_back(pointInArea);
    });

    ASSERT_EQ(7u, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(3,1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(1,2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(2,2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(3,2), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(4,2), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(5,2), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(3,3), pointsInAreaTraversal[6]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInFourthPattern)
{
    Quadrilateral quadrilateral(Point(2,3), Point(4,5), Point(2,2), Point(4,2));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea)
    {
        pointsInAreaTraversal.emplace_back(pointInArea);
    });

    ASSERT_EQ(9u, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(2,2), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(3,2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(4,2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(2,3), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(3,3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(4,3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(3,4), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(4,4), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(4,5), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInFifthPattern)
{
    Quadrilateral quadrilateral(Point(2,5), Point(4,3), Point(2,2), Point(4,2));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea)
    {
        pointsInAreaTraversal.emplace_back(pointInArea);
    });

    ASSERT_EQ(9u, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(2,2), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(3,2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(4,2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(2,3), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(3,3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(4,3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(2,4), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(3,4), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(2,5), pointsInAreaTraversal[8]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor4YGroupsFirstPattern)
{
    Quadrilateral quadrilateral(Point(3,1), Point(2,2), Point(4,3), Point(3,4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea)
    {
        pointsInAreaTraversal.emplace_back(pointInArea);
    });

    ASSERT_EQ(8u, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(3,1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(2,2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(3,2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(3.5,2), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(2.5,3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(3.5,3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(4,3), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(3,4), pointsInAreaTraversal[7]);
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor4YGroupsSecondPattern)
{
    Quadrilateral quadrilateral(Point(3,1), Point(2,3), Point(4,2), Point(3,4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea)
    {
        pointsInAreaTraversal.emplace_back(pointInArea);
    });

    ASSERT_EQ(8u, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(3,1), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(2.5,2), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(3.5,2), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(4,2), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(2,3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(3,3), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(3.5,3), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(3,4), pointsInAreaTraversal[7]);
}


}

}
