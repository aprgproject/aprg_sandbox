#include <AprgUniqueProblems/DynamicProgramming/MatrixMultiplicationOrder.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(MatrixMultiplicationOrderTest, GetMinimumNumberOfOperationsWorksOnExample1)
{
    MatrixMultiplicationOrder queryForTest({40U, 20U, 30U, 10U, 30U});

    EXPECT_EQ(26000U, queryForTest.getMinimumNumberOfOperationsUsingNaiveRecursion());
    EXPECT_EQ(26000U, queryForTest.getMinimumNumberOfOperationsUsingTabularDP());
    EXPECT_EQ(26000U, queryForTest.getMinimumNumberOfOperationsUsingMemoizationDP());
}

TEST(MatrixMultiplicationOrderTest, GetMinimumNumberOfOperationsWorksOnExample2)
{
    MatrixMultiplicationOrder queryForTest({10U, 20U, 30U, 40U, 30U});

    EXPECT_EQ(30000U, queryForTest.getMinimumNumberOfOperationsUsingNaiveRecursion());
    EXPECT_EQ(30000U, queryForTest.getMinimumNumberOfOperationsUsingTabularDP());
    EXPECT_EQ(30000U, queryForTest.getMinimumNumberOfOperationsUsingMemoizationDP());
}

TEST(MatrixMultiplicationOrderTest, GetMinimumNumberOfOperationsWorksOnExample3)
{
    MatrixMultiplicationOrder queryForTest({10U, 20U, 30U});

    EXPECT_EQ(6000U, queryForTest.getMinimumNumberOfOperationsUsingNaiveRecursion());
    EXPECT_EQ(6000U, queryForTest.getMinimumNumberOfOperationsUsingTabularDP());
    EXPECT_EQ(6000U, queryForTest.getMinimumNumberOfOperationsUsingMemoizationDP());
}

}
