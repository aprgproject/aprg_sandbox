#include <Algorithm/Sorter/SelectionSorter.hpp>
#include <AlgorithmTests/Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

namespace algorithm
{

TEST(SelectionSorterTest, SortWorksOnCharactersUsingExample1)
{
    SelectionSorter<Characters> sorter;
    performSortTestUsingExample1(sorter);
}

TEST(SelectionSorterTest, SortWorksOnCharactersUsingExample2)
{
    SelectionSorter<Characters> sorter;
    performSortTestUsingExample2(sorter);
}

}

}

