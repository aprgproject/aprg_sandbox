#include <Sorter/InsertionSorter.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

TEST(InsertionSorterTest, SortWorksOnCharactersUsingExample1)
{
    InsertionSorter<Characters> sorter;
    performSortTestUsingExample1(sorter);
}

TEST(InsertionSorterTest, SortWorksOnCharactersUsingExample2)
{
    InsertionSorter<Characters> sorter;
    performSortTestUsingExample2(sorter);
}

}