#include <UniqueProblems/DynamicProgramming/Math/MatrixMultiplicationOrder.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(MatrixMultiplicationOrderTest, GetMinimumNumberOfOperationsWorksOnExample1) {
    MatrixMultiplicationOrder queryForTest({40, 20, 30, 10, 30});

    EXPECT_EQ(26000, queryForTest.getMinimumNumberOfOperationsUsingNaiveRecursion());
    EXPECT_EQ(26000, queryForTest.getMinimumNumberOfOperationsUsingMemoizationDP());
    EXPECT_EQ(26000, queryForTest.getMinimumNumberOfOperationsUsingIterativeDP());
}

TEST(MatrixMultiplicationOrderTest, GetMinimumNumberOfOperationsWorksOnExample2) {
    MatrixMultiplicationOrder queryForTest({10, 20, 30, 40, 30});

    EXPECT_EQ(30000, queryForTest.getMinimumNumberOfOperationsUsingNaiveRecursion());
    EXPECT_EQ(30000, queryForTest.getMinimumNumberOfOperationsUsingMemoizationDP());
    EXPECT_EQ(30000, queryForTest.getMinimumNumberOfOperationsUsingIterativeDP());
}

TEST(MatrixMultiplicationOrderTest, GetMinimumNumberOfOperationsWorksOnExample3) {
    MatrixMultiplicationOrder queryForTest({10, 20, 30});

    EXPECT_EQ(6000, queryForTest.getMinimumNumberOfOperationsUsingNaiveRecursion());
    EXPECT_EQ(6000, queryForTest.getMinimumNumberOfOperationsUsingMemoizationDP());
    EXPECT_EQ(6000, queryForTest.getMinimumNumberOfOperationsUsingIterativeDP());
}

}  // namespace alba
