#include <Algorithm/Search/BinarySearch/BinarySearchWithSkip.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Objects = vector<unsigned int>;
using SearchForTest = BinarySearchWithSkip<Objects>;
}

TEST(BinarySearchWithSkipTest, SuccessfulBinarySearchWithSkipIsExecuted)
{
    SearchForTest binarySearch;
    Objects sortedObjects{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};

    EXPECT_EQ(33U, binarySearch.findNearestValue(sortedObjects, 33));
}

TEST(BinarySearchWithSkipTest, UnsuccessfulBinarySearchWithSkipWithLowerIsTheNearestValueIsExecuted)
{
    SearchForTest binarySearch;
    Objects sortedObjects{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};

    EXPECT_EQ(33U, binarySearch.findNearestValue(sortedObjects, 34));
}

TEST(BinarySearchWithSkipTest, UnsuccessfulBinarySearchWithSkipWithHigherIsTheNearestValueIsExecuted)
{
    SearchForTest binarySearch;
    Objects sortedObjects{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};

    EXPECT_EQ(43U, binarySearch.findNearestValue(sortedObjects, 42));
}

}

}
