#include <AprgUniqueProblems/DynamicProgramming/Math/NumberTheory/UglyNumbers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(UglyNumbersTest, GetNthUglyNumberOnExample1)
{
    UglyNumbers queryForTest(0);

    EXPECT_EQ(0U, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingIterativeDP());
    EXPECT_EQ(0U, queryForTest.getNthUglyNumberByMultiplesUsingIterativeDP());
}

TEST(UglyNumbersTest, GetNthUglyNumberOnExample2)
{
    UglyNumbers queryForTest(1);

    EXPECT_EQ(1U, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingIterativeDP());
    EXPECT_EQ(1U, queryForTest.getNthUglyNumberByMultiplesUsingIterativeDP());
}

TEST(UglyNumbersTest, GetNthUglyNumberOnExample3)
{
    UglyNumbers queryForTest(7);

    EXPECT_EQ(8U, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingIterativeDP());
    EXPECT_EQ(8U, queryForTest.getNthUglyNumberByMultiplesUsingIterativeDP());
}

TEST(UglyNumbersTest, GetNthUglyNumberOnExample4)
{
    UglyNumbers queryForTest(15);

    EXPECT_EQ(24U, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingIterativeDP());
    EXPECT_EQ(24U, queryForTest.getNthUglyNumberByMultiplesUsingIterativeDP());
}

TEST(UglyNumbersTest, GetNthUglyNumberOnExample5)
{
    UglyNumbers queryForTest(150);

    EXPECT_EQ(5832U, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingIterativeDP());
    EXPECT_EQ(5832U, queryForTest.getNthUglyNumberByMultiplesUsingIterativeDP());
}

}
