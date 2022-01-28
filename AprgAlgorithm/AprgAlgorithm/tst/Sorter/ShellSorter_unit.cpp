#include <Sorter/ShellSorter.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

TEST(ShellSorterTest, SortWorksOnCharactersUsingExample1)
{
    ShellSorter<Characters> sorter;
    performSortTestUsingExample1(sorter);
}

TEST(ShellSorterTest, SortWorksOnCharactersUsingExample2)
{
    ShellSorter<Characters> sorter;
    performSortTestUsingExample2(sorter);
}

}
