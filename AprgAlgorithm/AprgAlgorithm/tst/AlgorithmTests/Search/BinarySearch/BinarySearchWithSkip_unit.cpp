#include <Algorithm/Search/BinarySearch/BinarySearchWithSkip.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using SearchForTest = BinarySearchWithSkip<ValuesForTest>;
}

TEST(BinarySearchWithSkipTest, SuccessfulBinarySearchWithSkipIsExecuted)
{
    SearchForTest binarySearch;
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};

    EXPECT_EQ(33U, binarySearch.findNearestValue(sortedValues, 33));
}

TEST(BinarySearchWithSkipTest, UnsuccessfulBinarySearchWithSkipWithLowerIsTheNearestValueIsExecuted)
{
    SearchForTest binarySearch;
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};

    EXPECT_EQ(33U, binarySearch.findNearestValue(sortedValues, 34));
}

TEST(BinarySearchWithSkipTest, UnsuccessfulBinarySearchWithSkipWithHigherIsTheNearestValueIsExecuted)
{
    SearchForTest binarySearch;
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};

    EXPECT_EQ(43U, binarySearch.findNearestValue(sortedValues, 42));
}

}

}
