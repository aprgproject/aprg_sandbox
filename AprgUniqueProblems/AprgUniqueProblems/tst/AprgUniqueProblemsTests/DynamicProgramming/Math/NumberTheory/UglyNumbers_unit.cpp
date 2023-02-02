#include <AprgUniqueProblems/DynamicProgramming/Math/NumberTheory/UglyNumbers.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

TEST(UglyNumbersTest, GetNthUglyNumberOnExample1)
{
    UglyNumbers queryForTest(0);

    EXPECT_EQ(0U, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingTabularDP());
    EXPECT_EQ(0U, queryForTest.getNthUglyNumberByMultiplesUsingTabularDP());
}

TEST(UglyNumbersTest, GetNthUglyNumberOnExample2)
{
    UglyNumbers queryForTest(1);

    EXPECT_EQ(1U, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingTabularDP());
    EXPECT_EQ(1U, queryForTest.getNthUglyNumberByMultiplesUsingTabularDP());
}

TEST(UglyNumbersTest, GetNthUglyNumberOnExample3)
{
    UglyNumbers queryForTest(7);

    EXPECT_EQ(8U, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingTabularDP());
    EXPECT_EQ(8U, queryForTest.getNthUglyNumberByMultiplesUsingTabularDP());
}

TEST(UglyNumbersTest, GetNthUglyNumberOnExample4)
{
    UglyNumbers queryForTest(15);

    EXPECT_EQ(24U, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingTabularDP());
    EXPECT_EQ(24U, queryForTest.getNthUglyNumberByMultiplesUsingTabularDP());
}

TEST(UglyNumbersTest, GetNthUglyNumberOnExample5)
{
    UglyNumbers queryForTest(150);

    EXPECT_EQ(5832U, queryForTest.getNthUglyNumberByCheckingPreviousUglyNumbersUsingTabularDP());
    EXPECT_EQ(5832U, queryForTest.getNthUglyNumberByMultiplesUsingTabularDP());
}

}
