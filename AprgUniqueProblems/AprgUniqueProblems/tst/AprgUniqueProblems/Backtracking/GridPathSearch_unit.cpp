#include <AprgUniqueProblems/Backtracking/GridPathSearch.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba
{

TEST(SampleTest, CountPathWorksWhenGridSideIs3)
{
    GridPathSearch pathSearch(3);

    EXPECT_EQ(2U, pathSearch.countPaths());
}

TEST(SampleTest, CountPathWorksWhenGridSideIs4)
{
    GridPathSearch pathSearch(4);

    EXPECT_EQ(0U, pathSearch.countPaths()); // if side is even the paths are zero
}

TEST(SampleTest, CountPathWorksWhenGridSideIs5)
{
    GridPathSearch pathSearch(5);

    EXPECT_EQ(104U, pathSearch.countPaths());
}

TEST(SampleTest, DISABLED_CountPathWorksWhenGridSideIs7)
{
    GridPathSearch pathSearch(7);

    EXPECT_EQ(111712U, pathSearch.countPaths());
}

}