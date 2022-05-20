#include <Algorithm/Sorter/MergeSorter/TopDownMergeSorter.hpp>
#include <AlgorithmTests/Sorter/Utilities/CommonTestsWithSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<char>;
using SorterForTest = TopDownMergeSorter<ValuesForTest>;
}

TEST(TopDownMergeSorterTest, SortWorksOnCharactersUsingExample1)
{
    testSortUsingExample1WithCharacters<SorterForTest, ValuesForTest>();
}

TEST(TopDownMergeSorterTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<SorterForTest, ValuesForTest>();
}

}

}
