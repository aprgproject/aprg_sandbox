#include <AprgUniqueProblems/DynamicProgramming/Other/CountingTilings.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnExample1) {
    CountingTilings pathSearch(4U, 2U);

    EXPECT_EQ(5U, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnExample2) {
    CountingTilings pathSearch(4U, 3U);

    EXPECT_EQ(11U, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnExample3) {
    CountingTilings pathSearch(4U, 4U);

    EXPECT_EQ(36U, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnExample4) {
    CountingTilings pathSearch(4U, 5U);

    EXPECT_EQ(95U, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnExample5) {
    CountingTilings pathSearch(4U, 6U);

    EXPECT_EQ(281U, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnExample6) {
    CountingTilings pathSearch(4U, 7U);

    EXPECT_EQ(781U, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnPerfectSquare2) {
    CountingTilings pathSearch(2U, 2U);

    EXPECT_EQ(2U, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnPerfectSquare3) {
    CountingTilings pathSearch(3U, 3U);

    EXPECT_EQ(0U, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnPerfectSquare4) {
    CountingTilings pathSearch(4U, 4U);

    EXPECT_EQ(36U, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingDynamicProgrammingWorksOnPerfectSquare6) {
    CountingTilings pathSearch(6U, 6U);

    EXPECT_EQ(6728U, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, DISABLED_GetNumberOfSolutionsUsingDynamicProgrammingWorksOnStressTest) {
    CountingTilings pathSearch(16U, 16U);

    EXPECT_EQ(36U, pathSearch.getNumberOfSolutionsUsingDynamicProgramming());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnExample1) {
    CountingTilings pathSearch(4U, 2U);

    EXPECT_EQ(5U, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnExample2) {
    CountingTilings pathSearch(4U, 3U);

    EXPECT_EQ(11U, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnExample3) {
    CountingTilings pathSearch(4U, 4U);

    EXPECT_EQ(36U, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnExample4) {
    CountingTilings pathSearch(4U, 5U);

    EXPECT_EQ(95U, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnExample5) {
    CountingTilings pathSearch(4U, 6U);

    EXPECT_EQ(281U, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnExample6) {
    CountingTilings pathSearch(4U, 7U);

    EXPECT_EQ(781U, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnPerfectSquare2) {
    CountingTilings pathSearch(2U, 2U);

    EXPECT_EQ(2U, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnPerfectSquare3) {
    CountingTilings pathSearch(3U, 3U);

    EXPECT_EQ(0U, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnPerfectSquare4) {
    CountingTilings pathSearch(4U, 4U);

    EXPECT_EQ(36U, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, GetNumberOfSolutionsUsingCompleteSearchWorksOnPerfectSquare6) {
    CountingTilings pathSearch(6U, 6U);

    EXPECT_EQ(6728U, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

TEST(CountingTilingsTest, DISABLED_GetNumberOfSolutionsUsingCompleteSearchWorksOnStressTest) {
    CountingTilings pathSearch(32U, 32U);

    EXPECT_EQ(36U, pathSearch.getNumberOfSolutionsUsingCompleteSearch());
}

}  // namespace alba
