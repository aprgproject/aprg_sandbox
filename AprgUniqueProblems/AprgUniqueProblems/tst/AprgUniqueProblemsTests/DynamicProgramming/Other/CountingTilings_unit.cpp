#include <AprgUniqueProblems/DynamicProgramming/Other/CountingTilings.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnExample1) {
    CountingTilings pathSearch(4, 2);

    EXPECT_EQ(5, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnExample2) {
    CountingTilings pathSearch(4, 3);

    EXPECT_EQ(11, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnExample3) {
    CountingTilings pathSearch(4, 4);

    EXPECT_EQ(36, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnExample4) {
    CountingTilings pathSearch(4, 5);

    EXPECT_EQ(95, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnExample5) {
    CountingTilings pathSearch(4, 6);

    EXPECT_EQ(281, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnExample6) {
    CountingTilings pathSearch(4, 7);

    EXPECT_EQ(781, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnPerfectSquare2) {
    CountingTilings pathSearch(2, 2);

    EXPECT_EQ(2, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnPerfectSquare3) {
    CountingTilings pathSearch(3, 3);

    EXPECT_EQ(0, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnPerfectSquare4) {
    CountingTilings pathSearch(4, 4);

    EXPECT_EQ(36, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnPerfectSquare6) {
    CountingTilings pathSearch(6, 6);

    EXPECT_EQ(6728, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, DISABLED_GetNumberOfSolutionsUsingDynamicProgrammingWorksOnStressTest) {
    CountingTilings pathSearch(16, 16);

    EXPECT_EQ(36, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnExample1) {
    CountingTilings pathSearch(4, 2);

    EXPECT_EQ(5, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnExample2) {
    CountingTilings pathSearch(4, 3);

    EXPECT_EQ(11, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnExample3) {
    CountingTilings pathSearch(4, 4);

    EXPECT_EQ(36, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnExample4) {
    CountingTilings pathSearch(4, 5);

    EXPECT_EQ(95, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnExample5) {
    CountingTilings pathSearch(4, 6);

    EXPECT_EQ(281, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnExample6) {
    CountingTilings pathSearch(4, 7);

    EXPECT_EQ(781, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnPerfectSquare2) {
    CountingTilings pathSearch(2, 2);

    EXPECT_EQ(2, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnPerfectSquare3) {
    CountingTilings pathSearch(3, 3);

    EXPECT_EQ(0, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnPerfectSquare4) {
    CountingTilings pathSearch(4, 4);

    EXPECT_EQ(36, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnPerfectSquare6) {
    CountingTilings pathSearch(6, 6);

    EXPECT_EQ(6728, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, DISABLED_GetNumberOfSolutionsUsingCompleteSearchWorksOnStressTest) {
    CountingTilings pathSearch(32, 32);

    EXPECT_EQ(36, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

}  // namespace alba
