#include <Sorter/SelectionSorter.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
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

