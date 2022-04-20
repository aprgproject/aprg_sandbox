#include <BitmapManipulator/Traversal/OutwardSnakeLikeTraversal.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace AprgBitmap
{

TEST(OutwardSnakeLikeTraversalTest, ConstructionWorks)
{
    OutwardSnakeLikeTraversal(
                BitmapXY(12,34),
                OutwardSnakeLikeTraversal::Direction::Up,
                0, 50, 0, 100);
}

TEST(OutwardSnakeLikeTraversalTest, TraversalOnCenterWorks)
{
    OutwardSnakeLikeTraversal traversal(
                BitmapXY(8,8),
                OutwardSnakeLikeTraversal::Direction::Up,
                6, 10, 6, 10);

    EXPECT_EQ(BitmapXY(8,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,7), traversal.getNextPoint());
    EXPECT_FALSE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
}

TEST(OutwardSnakeLikeTraversalTest, TraversalOffCenter1Works)
{
    OutwardSnakeLikeTraversal traversal(
                BitmapXY(7,7),
                OutwardSnakeLikeTraversal::Direction::Up,
                6, 10, 6, 10);

    EXPECT_EQ(BitmapXY(7,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,7), traversal.getNextPoint());
    EXPECT_FALSE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
}

TEST(OutwardSnakeLikeTraversalTest, TraversalOffCenter2Works)
{
    OutwardSnakeLikeTraversal traversal(
                BitmapXY(9,7),
                OutwardSnakeLikeTraversal::Direction::Up,
                6, 10, 6, 10);

    EXPECT_EQ(BitmapXY(9,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,10), traversal.getNextPoint());
    EXPECT_FALSE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
}

TEST(OutwardSnakeLikeTraversalTest, TraversalOffCenter3Works)
{
    OutwardSnakeLikeTraversal traversal(
                BitmapXY(7,9),
                OutwardSnakeLikeTraversal::Direction::Up,
                6, 10, 6, 10);

    EXPECT_EQ(BitmapXY(7,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,7), traversal.getNextPoint());
    EXPECT_FALSE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
}

TEST(OutwardSnakeLikeTraversalTest, TraversalOffCenter4Works)
{
    OutwardSnakeLikeTraversal traversal(
                BitmapXY(9,9),
                OutwardSnakeLikeTraversal::Direction::Up,
                6, 10, 6, 10);

    EXPECT_EQ(BitmapXY(9,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,9), traversal.getNextPoint());
    EXPECT_FALSE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
}

TEST(OutwardSnakeLikeTraversalTest, TraversalAtTheCorner1Works)
{
    OutwardSnakeLikeTraversal traversal(
                BitmapXY(6,6),
                OutwardSnakeLikeTraversal::Direction::Up,
                6, 10, 6, 10);

    EXPECT_EQ(BitmapXY(6,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,7), traversal.getNextPoint());
    EXPECT_FALSE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
}

TEST(OutwardSnakeLikeTraversalTest, TraversalAtTheCorner2Works)
{
    OutwardSnakeLikeTraversal traversal(
                BitmapXY(10,6),
                OutwardSnakeLikeTraversal::Direction::Up,
                6, 10, 6, 10);

    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,10), traversal.getNextPoint());
    EXPECT_FALSE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
}

TEST(OutwardSnakeLikeTraversalTest, TraversalAtTheCorner3Works)
{
    OutwardSnakeLikeTraversal traversal(
                BitmapXY(6,10),
                OutwardSnakeLikeTraversal::Direction::Up,
                6, 10, 6, 10);

    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,7), traversal.getNextPoint());
    EXPECT_FALSE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
}

TEST(OutwardSnakeLikeTraversalTest, TraversalAtTheCorner4Works)
{
    OutwardSnakeLikeTraversal traversal(
                BitmapXY(10,10),
                OutwardSnakeLikeTraversal::Direction::Up,
                6, 10, 6, 10);

    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,9), traversal.getNextPoint());
    EXPECT_FALSE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
}

TEST(OutwardSnakeLikeTraversalTest, TraversalAtOutOfRangeIsCorrected)
{
    OutwardSnakeLikeTraversal traversal(
                BitmapXY(100,100),
                OutwardSnakeLikeTraversal::Direction::Up,
                6, 10, 6, 10);

    EXPECT_EQ(BitmapXY(10,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,9), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,10), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(10,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(9,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(8,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(7,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,6), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,7), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,8), traversal.getNextPoint());
    EXPECT_EQ(BitmapXY(6,9), traversal.getNextPoint());
    EXPECT_FALSE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
    EXPECT_EQ(BitmapXY(6,10), traversal.getNextPoint());
    EXPECT_TRUE(traversal.isTraversalFinished());
}

}

}
