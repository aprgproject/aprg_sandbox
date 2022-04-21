#include <Algorithm/Sorter/QuickSorter/QuickSorter.hpp>
#include <AlgorithmTests/Sorter/Utilities/CommonTestsWithSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba{

namespace algorithm
{

namespace
{
using ValuesForTest = std::vector<char>;
using SorterForTest = QuickSorter<ValuesForTest>;
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1)
{
    testSortUsingExample1WithCharacters<SorterForTest, ValuesForTest>();
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<SorterForTest, ValuesForTest>();
}

}
}