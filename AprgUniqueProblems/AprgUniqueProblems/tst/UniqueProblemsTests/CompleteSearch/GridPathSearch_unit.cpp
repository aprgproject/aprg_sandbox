#include <UniqueProblems/CompleteSearch/GridPathSearch.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(GridPathSearchTest, CountPathWorksWhenGridSideIs3) {
    GridPathSearch pathSearch(3);

    EXPECT_EQ(2, pathSearch.countPaths());
}

TEST(GridPathSearchTest, CountPathWorksWhenGridSideIs4) {
    GridPathSearch pathSearch(4);

    EXPECT_EQ(0, pathSearch.countPaths());  // if side is even the paths are zero
}

TEST(GridPathSearchTest, CountPathWorksWhenGridSideIs5) {
    GridPathSearch pathSearch(5);

    EXPECT_EQ(104, pathSearch.countPaths());
}

TEST(GridPathSearchTest, DISABLED_CountPathWorksWhenGridSideIs7) {
    GridPathSearch pathSearch(7);

    EXPECT_EQ(111712, pathSearch.countPaths());
}

}  // namespace alba
