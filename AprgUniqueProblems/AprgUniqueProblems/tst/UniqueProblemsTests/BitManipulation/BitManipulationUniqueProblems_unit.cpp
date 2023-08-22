#include <UniqueProblems/BitManipulation/BitManipulationUniqueProblems.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
namespace BitManipulation {

TEST(BitManipulationUniqueProblemsTest, ChangeKthBitToOneWorks) {
    EXPECT_EQ(2U, changeKthBitToOne(0, 1));
    EXPECT_EQ(3U, changeKthBitToOne(1, 1));
    EXPECT_EQ(2U, changeKthBitToOne(2, 1));
    EXPECT_EQ(3U, changeKthBitToOne(3, 1));
    EXPECT_EQ(6U, changeKthBitToOne(4, 1));
}

TEST(BitManipulationUniqueProblemsTest, ChangeKthBitToZeroWorks) {
    EXPECT_EQ(0U, changeKthBitToZero(0, 1));
    EXPECT_EQ(1U, changeKthBitToZero(1, 1));
    EXPECT_EQ(0U, changeKthBitToZero(2, 1));
    EXPECT_EQ(1U, changeKthBitToZero(3, 1));
    EXPECT_EQ(4U, changeKthBitToZero(4, 1));
}

TEST(BitManipulationUniqueProblemsTest, InvertKthBitWorks) {
    EXPECT_EQ(2U, invertKthBit(0, 1));
    EXPECT_EQ(3U, invertKthBit(1, 1));
    EXPECT_EQ(0U, invertKthBit(2, 1));
    EXPECT_EQ(1U, invertKthBit(3, 1));
    EXPECT_EQ(6U, invertKthBit(4, 1));
}

TEST(BitManipulationUniqueProblemsTest, ChangeLastOneToZeroWorks) {
    EXPECT_EQ(0U, changeLastOneToZero(0));
    EXPECT_EQ(0U, changeLastOneToZero(1));
    EXPECT_EQ(0U, changeLastOneToZero(2));
    EXPECT_EQ(2U, changeLastOneToZero(3));
    EXPECT_EQ(0U, changeLastOneToZero(4));
}

TEST(BitManipulationUniqueProblemsTest, ChangeAllOnesToZeroExceptForLastWorks) {
    EXPECT_EQ(0U, changeAllOnesToZeroExceptForLast(0));
    EXPECT_EQ(1U, changeAllOnesToZeroExceptForLast(1));
    EXPECT_EQ(2U, changeAllOnesToZeroExceptForLast(2));
    EXPECT_EQ(1U, changeAllOnesToZeroExceptForLast(3));
    EXPECT_EQ(4U, changeAllOnesToZeroExceptForLast(4));
}

TEST(BitManipulationUniqueProblemsTest, InvertAllBitsAfterTheLastOneWorks) {
    EXPECT_EQ(0xFFFFFFFFFFFFFFFFU, invertAllBitsAfterTheLastOne(0));
    EXPECT_EQ(1U, invertAllBitsAfterTheLastOne(1));
    EXPECT_EQ(3U, invertAllBitsAfterTheLastOne(2));
    EXPECT_EQ(3U, invertAllBitsAfterTheLastOne(3));
    EXPECT_EQ(7U, invertAllBitsAfterTheLastOne(4));
}

}  // namespace BitManipulation

}  // namespace alba
