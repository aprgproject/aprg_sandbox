#include <Algorithm/Search/SingleValue/BinarySearch/FindSmallestValueWithTrue.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValueForTest = unsigned int;
using SearchForTest = FindSmallestValueWithTrue<ValueForTest>;
}

TEST(FindSmallestValueWithTrueTest, GetNearestValueWorksWhenThereAreMultipleValues)
{
    SearchForTest binarySearch([](ValueForTest const value)
    {        return value>=111U;
    });

    EXPECT_EQ(111U, binarySearch.getSmallestValueWithTrue(45U, 500U));}

}

}
