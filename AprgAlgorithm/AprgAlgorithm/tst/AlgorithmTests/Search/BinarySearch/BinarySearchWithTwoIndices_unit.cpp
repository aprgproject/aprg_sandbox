#include <Algorithm/Search/BinarySearch/BinarySearchWithTwoIndices.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Objects = vector<unsigned int>;
using SearchForTest = BinarySearchWithTwoIndices<Objects>;
}

TEST(BinarySearchWithTwoIndicesTest, HighLowMiddleValuesCanFetchedInOneItem)
{
    SearchForTest binarySearch({6});
    EXPECT_EQ(6U, binarySearch.getLowestObject());
    EXPECT_EQ(6U, binarySearch.getMiddleObject());
    EXPECT_EQ(6U, binarySearch.getHighestObject());
}

TEST(BinarySearchWithTwoIndicesTest, HighLowMiddleValuesCanFetchedInTwoItems)
{
    SearchForTest binarySearch({6, 97});
    EXPECT_EQ(6U, binarySearch.getLowestObject());
    EXPECT_EQ(6U, binarySearch.getMiddleObject());
    EXPECT_EQ(97U, binarySearch.getHighestObject());
}

TEST(BinarySearchWithTwoIndicesTest, HighLowMiddleValuesCanFetchedInFourItems)
{
    SearchForTest binarySearch({6, 13, 96, 97});
    EXPECT_EQ(6U, binarySearch.getLowestObject());
    EXPECT_EQ(13U, binarySearch.getMiddleObject());
    EXPECT_EQ(97U, binarySearch.getHighestObject());
}

TEST(BinarySearchWithTwoIndicesTest, SuccessfulBinarySearchWithTwoIndicesIsExecutedCorrectlyPerIteration)
{
    SearchForTest binarySearch({6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97});
    EXPECT_EQ(6U, binarySearch.getLowestObject());
    EXPECT_EQ(53U, binarySearch.getMiddleObject());
    EXPECT_EQ(97U, binarySearch.getHighestObject());

    binarySearch.findValueForOneIteration(33);
    EXPECT_EQ(6U, binarySearch.getLowestObject());
    EXPECT_EQ(25U, binarySearch.getMiddleObject());
    EXPECT_EQ(51U, binarySearch.getHighestObject());

    binarySearch.findValueForOneIteration(33);
    EXPECT_EQ(33U, binarySearch.getLowestObject());
    EXPECT_EQ(43U, binarySearch.getMiddleObject());
    EXPECT_EQ(51U, binarySearch.getHighestObject());

    binarySearch.findValueForOneIteration(33);
    EXPECT_EQ(33U, binarySearch.getLowestObject());
    EXPECT_EQ(33U, binarySearch.getMiddleObject());
    EXPECT_EQ(33U, binarySearch.getHighestObject());
}

TEST(BinarySearchWithTwoIndicesTest, UnsuccessfulBinarySearchWithTwoIndicesWithLowerIsTheNearestValueIsExecutedPerIteration)
{
    SearchForTest binarySearch({6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97});
    EXPECT_EQ(6U, binarySearch.getLowestObject());
    EXPECT_EQ(53U, binarySearch.getMiddleObject());
    EXPECT_EQ(97U, binarySearch.getHighestObject());

    binarySearch.findValueForOneIteration(34);
    EXPECT_EQ(6U, binarySearch.getLowestObject());
    EXPECT_EQ(25U, binarySearch.getMiddleObject());
    EXPECT_EQ(51U, binarySearch.getHighestObject());

    binarySearch.findValueForOneIteration(34);
    EXPECT_EQ(33U, binarySearch.getLowestObject());
    EXPECT_EQ(43U, binarySearch.getMiddleObject());
    EXPECT_EQ(51U, binarySearch.getHighestObject());

    binarySearch.findValueForOneIteration(34);
    EXPECT_EQ(33U, binarySearch.getLowestObject());
    EXPECT_EQ(33U, binarySearch.getMiddleObject());
    EXPECT_EQ(33U, binarySearch.getHighestObject());
}

TEST(BinarySearchWithTwoIndicesTest, UnsuccessfulBinarySearchWithTwoIndicesWithHigherIsTheNearestValueIsExecutedPerIteration)
{
    SearchForTest binarySearch({6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97});
    EXPECT_EQ(6U, binarySearch.getLowestObject());
    EXPECT_EQ(53U, binarySearch.getMiddleObject());
    EXPECT_EQ(97U, binarySearch.getHighestObject());

    binarySearch.findValueForOneIteration(42);
    EXPECT_EQ(6U, binarySearch.getLowestObject());
    EXPECT_EQ(25U, binarySearch.getMiddleObject());
    EXPECT_EQ(51U, binarySearch.getHighestObject());

    binarySearch.findValueForOneIteration(42);
    EXPECT_EQ(33U, binarySearch.getLowestObject());
    EXPECT_EQ(43U, binarySearch.getMiddleObject());
    EXPECT_EQ(51U, binarySearch.getHighestObject());

    binarySearch.findValueForOneIteration(42);
    EXPECT_EQ(33U, binarySearch.getLowestObject());
    EXPECT_EQ(33U, binarySearch.getMiddleObject());
    EXPECT_EQ(33U, binarySearch.getHighestObject());
}

TEST(BinarySearchWithTwoIndicesTest, SuccessfulBinarySearchWithTwoIndicesIsExecuted)
{
    SearchForTest binarySearch({6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97});
    EXPECT_EQ(33U, binarySearch.findNearestValue(33));
}

TEST(BinarySearchWithTwoIndicesTest, UnsuccessfulBinarySearchWithTwoIndicesWithLowerIsTheNearestValueIsExecuted)
{
    SearchForTest binarySearch({6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97});
    EXPECT_EQ(33U, binarySearch.findNearestValue(34));
}

TEST(BinarySearchWithTwoIndicesTest, UnsuccessfulBinarySearchWithTwoIndicesWithHigherIsTheNearestValueIsExecuted)
{
    SearchForTest binarySearch({6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97});
    EXPECT_EQ(43U, binarySearch.findNearestValue(42));
}

}

}
