#include <BinarySearch/BinarySearch.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba;
using namespace std;

TEST(BinarySearchTest, BinarySearchCanBeCreatedUsingDefaultConstructor)
{
    BinarySearch<unsigned int> binarySearch;
    EXPECT_EQ(0, binarySearch.getHighestValue());
    EXPECT_EQ(0, binarySearch.getMiddleValue());
    EXPECT_EQ(0, binarySearch.getLowestValue());
}

TEST(BinarySearchTest, HighLowMiddleValuesCanFetchedInOneItem)
{
    BinarySearch<unsigned int> binarySearch;
    binarySearch.add(6);
    EXPECT_EQ(6, binarySearch.getLowestValue());
    EXPECT_EQ(6, binarySearch.getMiddleValue());
    EXPECT_EQ(6, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, HighLowMiddleValuesCanFetchedInTwoItems)
{
    BinarySearch<unsigned int> binarySearch;
    binarySearch.add({6, 97});
    EXPECT_EQ(6, binarySearch.getLowestValue());
    EXPECT_EQ(6, binarySearch.getMiddleValue());
    EXPECT_EQ(97, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, HighLowMiddleValuesCanFetchedInFourItems)
{
    BinarySearch<unsigned int> binarySearch;
    binarySearch.add({6, 13, 96, 97});
    EXPECT_EQ(6, binarySearch.getLowestValue());
    EXPECT_EQ(13, binarySearch.getMiddleValue());
    EXPECT_EQ(97, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, SuccessfulBinarySearchIsExecutedCorrectlyPerIteration)
{
    BinarySearch<unsigned int> binarySearch{72, 84, 93, 6, 13, 14, 25, 33, 43, 51, 53, 64, 95, 96, 97};
    EXPECT_EQ(6, binarySearch.getLowestValue());
    EXPECT_EQ(53, binarySearch.getMiddleValue());
    EXPECT_EQ(97, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(33);
    EXPECT_EQ(6, binarySearch.getLowestValue());
    EXPECT_EQ(25, binarySearch.getMiddleValue());
    EXPECT_EQ(51, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(33);
    EXPECT_EQ(33, binarySearch.getLowestValue());
    EXPECT_EQ(43, binarySearch.getMiddleValue());
    EXPECT_EQ(51, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(33);
    EXPECT_EQ(33, binarySearch.getLowestValue());
    EXPECT_EQ(33, binarySearch.getMiddleValue());
    EXPECT_EQ(33, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, UnsuccessfulBinarySearchWithLowerIsTheNearestValueIsExecutedPerIteration)
{
    BinarySearch<unsigned int> binarySearch{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    EXPECT_EQ(6, binarySearch.getLowestValue());
    EXPECT_EQ(53, binarySearch.getMiddleValue());
    EXPECT_EQ(97, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(34);
    EXPECT_EQ(6, binarySearch.getLowestValue());
    EXPECT_EQ(25, binarySearch.getMiddleValue());
    EXPECT_EQ(51, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(34);
    EXPECT_EQ(33, binarySearch.getLowestValue());
    EXPECT_EQ(43, binarySearch.getMiddleValue());
    EXPECT_EQ(51, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(34);
    EXPECT_EQ(33, binarySearch.getLowestValue());
    EXPECT_EQ(33, binarySearch.getMiddleValue());
    EXPECT_EQ(33, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, UnsuccessfulBinarySearchWithHigherIsTheNearestValueIsExecutedPerIteration)
{
    BinarySearch<unsigned int> binarySearch{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    EXPECT_EQ(6, binarySearch.getLowestValue());
    EXPECT_EQ(53, binarySearch.getMiddleValue());
    EXPECT_EQ(97, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(42);
    EXPECT_EQ(6, binarySearch.getLowestValue());
    EXPECT_EQ(25, binarySearch.getMiddleValue());
    EXPECT_EQ(51, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(42);
    EXPECT_EQ(33, binarySearch.getLowestValue());
    EXPECT_EQ(43, binarySearch.getMiddleValue());
    EXPECT_EQ(51, binarySearch.getHighestValue());

    binarySearch.findValueForOneIteration(42);
    EXPECT_EQ(33, binarySearch.getLowestValue());
    EXPECT_EQ(33, binarySearch.getMiddleValue());
    EXPECT_EQ(33, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, SuccessfulBinarySearchIsExecuted)
{
    BinarySearch<unsigned int> binarySearch{72, 84, 93, 6, 13, 14, 25, 33, 43, 51, 53, 64, 95, 96, 97};
    EXPECT_EQ(33, binarySearch.findNearestValue(33));
}

TEST(BinarySearchTest, UnsuccessfulBinarySearchWithLowerIsTheNearestValueIsExecuted)
{
    BinarySearch<unsigned int> binarySearch{72, 84, 93, 6, 13, 14, 25, 33, 43, 51, 53, 64, 95, 96, 97};
    EXPECT_EQ(33, binarySearch.findNearestValue(34));
}

TEST(BinarySearchTest, UnsuccessfulBinarySearchWithHigherIsTheNearestValueIsExecuted)
{
    BinarySearch<unsigned int> binarySearch{72, 84, 93, 6, 13, 14, 25, 33, 43, 51, 53, 64, 95, 96, 97};
    EXPECT_EQ(43, binarySearch.findNearestValue(42));
}

