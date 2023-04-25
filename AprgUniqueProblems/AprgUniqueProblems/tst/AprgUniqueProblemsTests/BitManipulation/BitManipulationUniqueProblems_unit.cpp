#include <AprgUniqueProblems/BitManipulation/BitManipulationUniqueProblems.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace BitManipulation {

TEST(BitManipulationUniqueProblemsTest, ChangeKthBitToOneWorks) {
    EXPECT_EQ(2U, changeKthBitToOne(0U, 1U));
    EXPECT_EQ(3U, changeKthBitToOne(1U, 1U));
    EXPECT_EQ(2U, changeKthBitToOne(2U, 1U));
    EXPECT_EQ(3U, changeKthBitToOne(3U, 1U));
    EXPECT_EQ(6U, changeKthBitToOne(4U, 1U));
}

TEST(BitManipulationUniqueProblemsTest, ChangeKthBitToZeroWorks) {
    EXPECT_EQ(0U, changeKthBitToZero(0U, 1U));
    EXPECT_EQ(1U, changeKthBitToZero(1U, 1U));
    EXPECT_EQ(0U, changeKthBitToZero(2U, 1U));
    EXPECT_EQ(1U, changeKthBitToZero(3U, 1U));
    EXPECT_EQ(4U, changeKthBitToZero(4U, 1U));
}

TEST(BitManipulationUniqueProblemsTest, InvertKthBitWorks) {
    EXPECT_EQ(2U, invertKthBit(0U, 1U));
    EXPECT_EQ(3U, invertKthBit(1U, 1U));
    EXPECT_EQ(0U, invertKthBit(2U, 1U));
    EXPECT_EQ(1U, invertKthBit(3U, 1U));
    EXPECT_EQ(6U, invertKthBit(4U, 1U));
}

TEST(BitManipulationUniqueProblemsTest, ChangeLastOneToZeroWorks) {
    EXPECT_EQ(0U, changeLastOneToZero(0U));
    EXPECT_EQ(0U, changeLastOneToZero(1U));
    EXPECT_EQ(0U, changeLastOneToZero(2U));
    EXPECT_EQ(2U, changeLastOneToZero(3U));
    EXPECT_EQ(0U, changeLastOneToZero(4U));
}

TEST(BitManipulationUniqueProblemsTest, ChangeAllOnesToZeroExceptForLastWorks) {
    EXPECT_EQ(0U, changeAllOnesToZeroExceptForLast(0U));
    EXPECT_EQ(1U, changeAllOnesToZeroExceptForLast(1U));
    EXPECT_EQ(2U, changeAllOnesToZeroExceptForLast(2U));
    EXPECT_EQ(1U, changeAllOnesToZeroExceptForLast(3U));
    EXPECT_EQ(4U, changeAllOnesToZeroExceptForLast(4U));
}

TEST(BitManipulationUniqueProblemsTest, InvertAllBitsAfterTheLastOneWorks) {
    EXPECT_EQ(0xFFFFFFFFU, invertAllBitsAfterTheLastOne(0U));
    EXPECT_EQ(1U, invertAllBitsAfterTheLastOne(1U));
    EXPECT_EQ(3U, invertAllBitsAfterTheLastOne(2U));
    EXPECT_EQ(3U, invertAllBitsAfterTheLastOne(3U));
    EXPECT_EQ(7U, invertAllBitsAfterTheLastOne(4U));
}

}  // namespace BitManipulation

}  // namespace alba
