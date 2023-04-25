#include <AprgUniqueProblems/DynamicProgramming/Other/CountPossibleWaysToConstructBuildings.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(CountPossibleWaysToConstructBuildingsTest, GetNumberOfWaysWorksOZeroSections) {
    CountPossibleWaysToConstructBuildings queryForTest(0);

    EXPECT_EQ(1U, queryForTest.getNumberOfWaysUsingCountOfBuildingAndSpaces());
    EXPECT_EQ(1U, queryForTest.getNumberOfWaysUsingFibonacciNumber());
    EXPECT_EQ(1U, queryForTest.getNumberOfWaysUsingCombinations());
}

TEST(CountPossibleWaysToConstructBuildingsTest, GetNumberOfWaysWorksOnExample1) {
    CountPossibleWaysToConstructBuildings queryForTest(1);

    EXPECT_EQ(4U, queryForTest.getNumberOfWaysUsingCountOfBuildingAndSpaces());
    EXPECT_EQ(4U, queryForTest.getNumberOfWaysUsingFibonacciNumber());
    EXPECT_EQ(4U, queryForTest.getNumberOfWaysUsingCombinations());
}

TEST(CountPossibleWaysToConstructBuildingsTest, GetNumberOfWaysWorksOnExample2) {
    CountPossibleWaysToConstructBuildings queryForTest(2);

    EXPECT_EQ(9U, queryForTest.getNumberOfWaysUsingCountOfBuildingAndSpaces());
    EXPECT_EQ(9U, queryForTest.getNumberOfWaysUsingFibonacciNumber());
    EXPECT_EQ(9U, queryForTest.getNumberOfWaysUsingCombinations());
}

TEST(CountPossibleWaysToConstructBuildingsTest, GetNumberOfWaysWorksOnExample3) {
    CountPossibleWaysToConstructBuildings queryForTest(3);

    EXPECT_EQ(25U, queryForTest.getNumberOfWaysUsingCountOfBuildingAndSpaces());
    EXPECT_EQ(25U, queryForTest.getNumberOfWaysUsingFibonacciNumber());
    EXPECT_EQ(25U, queryForTest.getNumberOfWaysUsingCombinations());
}

TEST(CountPossibleWaysToConstructBuildingsTest, GetNumberOfWaysWorksOnExample4) {
    CountPossibleWaysToConstructBuildings queryForTest(4);

    EXPECT_EQ(64U, queryForTest.getNumberOfWaysUsingCountOfBuildingAndSpaces());
    EXPECT_EQ(64U, queryForTest.getNumberOfWaysUsingFibonacciNumber());
    EXPECT_EQ(64U, queryForTest.getNumberOfWaysUsingCombinations());
}

TEST(CountPossibleWaysToConstructBuildingsTest, GetNumberOfWaysWorksOnExample5) {
    CountPossibleWaysToConstructBuildings queryForTest(5);

    EXPECT_EQ(169U, queryForTest.getNumberOfWaysUsingCountOfBuildingAndSpaces());
    EXPECT_EQ(169U, queryForTest.getNumberOfWaysUsingFibonacciNumber());
    EXPECT_EQ(169U, queryForTest.getNumberOfWaysUsingCombinations());
}

}  // namespace alba
