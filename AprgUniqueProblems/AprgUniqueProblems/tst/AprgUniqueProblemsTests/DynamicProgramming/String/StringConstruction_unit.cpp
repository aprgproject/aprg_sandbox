#include <AprgUniqueProblems/DynamicProgramming/String/StringConstruction.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(StringConstructionTest, GetCountWorksOnEmptyStrings)
{
    StringConstruction countToTest("", {"", "", ""});

    EXPECT_EQ(0U, countToTest.getCount());
}

TEST(StringConstructionTest, GetCountWorksOnExample1)
{
    StringConstruction countToTest("ABAB", {"A", "B", "AB"});

    EXPECT_EQ(4U, countToTest.getCount());
}

TEST(StringConstructionTest, GetCountSquareRootAlgorithmWorksOnEmptyStrings)
{
    StringConstruction countToTest("", {"", "", ""});

    EXPECT_EQ(0U, countToTest.getCountSquareRootAlgorithm());
}

TEST(StringConstructionTest, GetCountSquareRootAlgorithmWorksOnExample1)
{
    StringConstruction countToTest("ABAB", {"A", "B", "AB"});

    EXPECT_EQ(4U, countToTest.getCountSquareRootAlgorithm());
}

}
