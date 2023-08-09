#include <Algorithm/Sorter/HeapSorter.hpp>
#include <AlgorithmTests/Sorter/Utilities/CommonTestsWithSorter.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = std::vector<char>;
using SorterForTest = HeapSorter<ValuesForTest>;
}

TEST(HeapSorterTest, SortWorksOnCharactersUsingExample1)
{
    testSortUsingExample1WithCharacters<SorterForTest, ValuesForTest>();
}

TEST(HeapSorterTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<SorterForTest, ValuesForTest>();
}

}

}
