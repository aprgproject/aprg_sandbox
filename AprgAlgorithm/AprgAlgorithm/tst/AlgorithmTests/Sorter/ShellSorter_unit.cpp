#include <Algorithm/Sorter/ShellSorter.hpp>
#include <AlgorithmTests/Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

namespace algorithm
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

}
