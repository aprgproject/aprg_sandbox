#include <Algorithm/Search/BinarySearch/BinarySearchWithTwoIndices.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using SearchForTest = BinarySearchWithTwoIndices<ValuesForTest>;
}

TEST(BinarySearchWithTwoIndicesTest, HighLowMiddleValuesCanFetchedInOneItem)
{
    ValuesForTest valuesForTest{6};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(6U, binarySearch.getLowestValue());
    EXPECT_EQ(6U, binarySearch.getMiddleValue());
    EXPECT_EQ(6U, binarySearch.getHighestValue());
}

TEST(BinarySearchWithTwoIndicesTest, HighLowMiddleValuesCanFetchedInTwoItems)
{
    ValuesForTest valuesForTest{6, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(6U, binarySearch.getLowestValue());
    EXPECT_EQ(6U, binarySearch.getMiddleValue());
    EXPECT_EQ(97U, binarySearch.getHighestValue());
}

TEST(BinarySearchWithTwoIndicesTest, HighLowMiddleValuesCanFetchedInFourItems)
{
    ValuesForTest valuesForTest{6, 13, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(6U, binarySearch.getLowestValue());
    EXPECT_EQ(13U, binarySearch.getMiddleValue());
    EXPECT_EQ(97U, binarySearch.getHighestValue());
}

TEST(BinarySearchWithTwoIndicesTest, SuccessfulBinarySearchIsExecutedCorrectlyPerIteration)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(6U, binarySearch.getLowestValue());
    EXPECT_EQ(53U, binarySearch.getMiddleValue());
    EXPECT_EQ(97U, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(33);
    EXPECT_EQ(6U, binarySearch.getLowestValue());
    EXPECT_EQ(25U, binarySearch.getMiddleValue());
    EXPECT_EQ(51U, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(33);
    EXPECT_EQ(33U, binarySearch.getLowestValue());
    EXPECT_EQ(43U, binarySearch.getMiddleValue());
    EXPECT_EQ(51U, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(33);
    EXPECT_EQ(33U, binarySearch.getLowestValue());
    EXPECT_EQ(33U, binarySearch.getMiddleValue());
    EXPECT_EQ(33U, binarySearch.getHighestValue());
}

TEST(BinarySearchWithTwoIndicesTest, UnsuccessfulBinarySearchWithLowerIsTheNearestValueIsExecutedPerIteration)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(6U, binarySearch.getLowestValue());
    EXPECT_EQ(53U, binarySearch.getMiddleValue());
    EXPECT_EQ(97U, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(34);
    EXPECT_EQ(6U, binarySearch.getLowestValue());
    EXPECT_EQ(25U, binarySearch.getMiddleValue());
    EXPECT_EQ(51U, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(34);
    EXPECT_EQ(33U, binarySearch.getLowestValue());
    EXPECT_EQ(43U, binarySearch.getMiddleValue());
    EXPECT_EQ(51U, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(34);
    EXPECT_EQ(33U, binarySearch.getLowestValue());
    EXPECT_EQ(33U, binarySearch.getMiddleValue());
    EXPECT_EQ(33U, binarySearch.getHighestValue());
}

TEST(BinarySearchWithTwoIndicesTest, UnsuccessfulBinarySearchWithHigherIsTheNearestValueIsExecutedPerIteration)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(6U, binarySearch.getLowestValue());
    EXPECT_EQ(53U, binarySearch.getMiddleValue());
    EXPECT_EQ(97U, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(42);
    EXPECT_EQ(6U, binarySearch.getLowestValue());
    EXPECT_EQ(25U, binarySearch.getMiddleValue());
    EXPECT_EQ(51U, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(42);
    EXPECT_EQ(33U, binarySearch.getLowestValue());
    EXPECT_EQ(43U, binarySearch.getMiddleValue());
    EXPECT_EQ(51U, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(42);
    EXPECT_EQ(33U, binarySearch.getLowestValue());
    EXPECT_EQ(33U, binarySearch.getMiddleValue());
    EXPECT_EQ(33U, binarySearch.getHighestValue());
}

TEST(BinarySearchWithTwoIndicesTest, SuccessfulBinarySearchIsExecuted)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(33U, binarySearch.findNearestValue(33));
}

TEST(BinarySearchWithTwoIndicesTest, UnsuccessfulBinarySearchWithLowerIsTheNearestValueIsExecuted)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(33U, binarySearch.findNearestValue(34));
}

TEST(BinarySearchWithTwoIndicesTest, UnsuccessfulBinarySearchWithHigherIsTheNearestValueIsExecuted)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(43U, binarySearch.findNearestValue(42));
}

TEST(BinarySearchWithTwoIndicesTest, SuccessfulBinarySearchWhenIndexWithLowestAndIndexWithHighestAreGiven)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(3U, 5U, valuesForTest);

    EXPECT_EQ(33U, binarySearch.findNearestValue(33));
}

TEST(BinarySearchWithTwoIndicesTest, UnsuccessfulBinarySearchWhenIndexWithLowestAndIndexWithHighestAreGiven)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(5U, 6U, valuesForTest);

    EXPECT_EQ(43U, binarySearch.findNearestValue(33));
}

}

}
