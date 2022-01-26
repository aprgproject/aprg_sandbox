#include <BinarySearch/BinarySearch.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba{

TEST(BinarySearchTest, BinarySearchCanBeCreatedUsingDefaultConstructor)
{    BinarySearch<unsigned int> binarySearch;
    EXPECT_EQ(0U, binarySearch.getHighestValue());
    EXPECT_EQ(0U, binarySearch.getMiddleValue());
    EXPECT_EQ(0U, binarySearch.getLowestValue());
}

TEST(BinarySearchTest, HighLowMiddleValuesCanFetchedInOneItem)
{
    BinarySearch<unsigned int> binarySearch;
    binarySearch.add(6);
    EXPECT_EQ(6U, binarySearch.getLowestValue());
    EXPECT_EQ(6U, binarySearch.getMiddleValue());
    EXPECT_EQ(6U, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, HighLowMiddleValuesCanFetchedInTwoItems)
{
    BinarySearch<unsigned int> binarySearch;
    binarySearch.add({6, 97});
    EXPECT_EQ(6U, binarySearch.getLowestValue());
    EXPECT_EQ(6U, binarySearch.getMiddleValue());
    EXPECT_EQ(97U, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, HighLowMiddleValuesCanFetchedInFourItems)
{
    BinarySearch<unsigned int> binarySearch;
    binarySearch.add({6, 13, 96, 97});
    EXPECT_EQ(6U, binarySearch.getLowestValue());
    EXPECT_EQ(13U, binarySearch.getMiddleValue());
    EXPECT_EQ(97U, binarySearch.getHighestValue());
}

TEST(BinarySearchTest, SuccessfulBinarySearchIsExecutedCorrectlyPerIteration)
{
    BinarySearch<unsigned int> binarySearch{72, 84, 93, 6, 13, 14, 25, 33, 43, 51, 53, 64, 95, 96, 97};
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

TEST(BinarySearchTest, UnsuccessfulBinarySearchWithLowerIsTheNearestValueIsExecutedPerIteration)
{
    BinarySearch<unsigned int> binarySearch{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
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

TEST(BinarySearchTest, UnsuccessfulBinarySearchWithHigherIsTheNearestValueIsExecutedPerIteration)
{
    BinarySearch<unsigned int> binarySearch{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
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

TEST(BinarySearchTest, SuccessfulBinarySearchIsExecuted)
{
    BinarySearch<unsigned int> binarySearch{72, 84, 93, 6, 13, 14, 25, 33, 43, 51, 53, 64, 95, 96, 97};
    EXPECT_EQ(33U, binarySearch.findNearestValue(33));
}

TEST(BinarySearchTest, UnsuccessfulBinarySearchWithLowerIsTheNearestValueIsExecuted)
{
    BinarySearch<unsigned int> binarySearch{72, 84, 93, 6, 13, 14, 25, 33, 43, 51, 53, 64, 95, 96, 97};
    EXPECT_EQ(33U, binarySearch.findNearestValue(34));
}

TEST(BinarySearchTest, UnsuccessfulBinarySearchWithHigherIsTheNearestValueIsExecuted)
{
    BinarySearch<unsigned int> binarySearch{72, 84, 93, 6, 13, 14, 25, 33, 43, 51, 53, 64, 95, 96, 97};
    EXPECT_EQ(43U, binarySearch.findNearestValue(42));
}

}
