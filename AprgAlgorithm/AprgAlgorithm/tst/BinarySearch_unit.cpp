#include <BinarySearch/BinarySearch.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba
{

TEST(BinarySearchTest, BinarySearchCanBeCreatedUsingDefaultConstructor)
{
    BinarySearch<unsigned int> binarySearch;    EXPECT_EQ(0u, binarySearch.getHighestValue());
    EXPECT_EQ(0u, binarySearch.getMiddleValue());
    EXPECT_EQ(0u, binarySearch.getLowestValue());
}
TEST(BinarySearchTest, HighLowMiddleValuesCanFetchedInOneItem)
{
    BinarySearch<unsigned int> binarySearch;
    binarySearch.add(6);
    EXPECT_EQ(6u, binarySearch.getLowestValue());
    EXPECT_EQ(6u, binarySearch.getMiddleValue());
    EXPECT_EQ(6u, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, HighLowMiddleValuesCanFetchedInTwoItems)
{
    BinarySearch<unsigned int> binarySearch;
    binarySearch.add({6, 97});
    EXPECT_EQ(6u, binarySearch.getLowestValue());
    EXPECT_EQ(6u, binarySearch.getMiddleValue());
    EXPECT_EQ(97u, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, HighLowMiddleValuesCanFetchedInFourItems)
{
    BinarySearch<unsigned int> binarySearch;
    binarySearch.add({6, 13, 96, 97});
    EXPECT_EQ(6u, binarySearch.getLowestValue());
    EXPECT_EQ(13u, binarySearch.getMiddleValue());
    EXPECT_EQ(97u, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, SuccessfulBinarySearchIsExecutedCorrectlyPerIteration)
{
    BinarySearch<unsigned int> binarySearch{72, 84, 93, 6, 13, 14, 25, 33, 43, 51, 53, 64, 95, 96, 97};
    EXPECT_EQ(6u, binarySearch.getLowestValue());
    EXPECT_EQ(53u, binarySearch.getMiddleValue());
    EXPECT_EQ(97u, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(33);
    EXPECT_EQ(6u, binarySearch.getLowestValue());
    EXPECT_EQ(25u, binarySearch.getMiddleValue());
    EXPECT_EQ(51u, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(33);
    EXPECT_EQ(33u, binarySearch.getLowestValue());
    EXPECT_EQ(43u, binarySearch.getMiddleValue());
    EXPECT_EQ(51u, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(33);
    EXPECT_EQ(33u, binarySearch.getLowestValue());
    EXPECT_EQ(33u, binarySearch.getMiddleValue());
    EXPECT_EQ(33u, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, UnsuccessfulBinarySearchWithLowerIsTheNearestValueIsExecutedPerIteration)
{
    BinarySearch<unsigned int> binarySearch{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    EXPECT_EQ(6u, binarySearch.getLowestValue());
    EXPECT_EQ(53u, binarySearch.getMiddleValue());
    EXPECT_EQ(97u, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(34);
    EXPECT_EQ(6u, binarySearch.getLowestValue());
    EXPECT_EQ(25u, binarySearch.getMiddleValue());
    EXPECT_EQ(51u, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(34);
    EXPECT_EQ(33u, binarySearch.getLowestValue());
    EXPECT_EQ(43u, binarySearch.getMiddleValue());
    EXPECT_EQ(51u, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(34);
    EXPECT_EQ(33u, binarySearch.getLowestValue());
    EXPECT_EQ(33u, binarySearch.getMiddleValue());
    EXPECT_EQ(33u, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, UnsuccessfulBinarySearchWithHigherIsTheNearestValueIsExecutedPerIteration)
{
    BinarySearch<unsigned int> binarySearch{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    EXPECT_EQ(6u, binarySearch.getLowestValue());
    EXPECT_EQ(53u, binarySearch.getMiddleValue());
    EXPECT_EQ(97u, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(42);
    EXPECT_EQ(6u, binarySearch.getLowestValue());
    EXPECT_EQ(25u, binarySearch.getMiddleValue());
    EXPECT_EQ(51u, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(42);
    EXPECT_EQ(33u, binarySearch.getLowestValue());
    EXPECT_EQ(43u, binarySearch.getMiddleValue());
    EXPECT_EQ(51u, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(42);
    EXPECT_EQ(33u, binarySearch.getLowestValue());
    EXPECT_EQ(33u, binarySearch.getMiddleValue());
    EXPECT_EQ(33u, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, SuccessfulBinarySearchIsExecuted)
{
    BinarySearch<unsigned int> binarySearch{72, 84, 93, 6, 13, 14, 25, 33, 43, 51, 53, 64, 95, 96, 97};
    EXPECT_EQ(33u, binarySearch.findNearestValue(33));
}

TEST(BinarySearchTest, UnsuccessfulBinarySearchWithLowerIsTheNearestValueIsExecuted)
{
    BinarySearch<unsigned int> binarySearch{72, 84, 93, 6, 13, 14, 25, 33, 43, 51, 53, 64, 95, 96, 97};
    EXPECT_EQ(33u, binarySearch.findNearestValue(34));
}

TEST(BinarySearchTest, UnsuccessfulBinarySearchWithHigherIsTheNearestValueIsExecuted)
{
    BinarySearch<unsigned int> binarySearch{72, 84, 93, 6, 13, 14, 25, 33, 43, 51, 53, 64, 95, 96, 97};
    EXPECT_EQ(43u, binarySearch.findNearestValue(42));
}

}