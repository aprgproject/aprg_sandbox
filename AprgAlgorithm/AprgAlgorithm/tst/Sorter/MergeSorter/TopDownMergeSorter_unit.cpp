#include <Sorter/MergeSorter/TopDownMergeSorter.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

TEST(TopDownMergeSorterTest, SortWorksOnCharactersUsingExample1)
{
    TopDownMergeSorter<Characters> sorter;
    performSortTestUsingExample1(sorter);
}

TEST(TopDownMergeSorterTest, SortWorksOnCharactersUsingExample2)
{
    TopDownMergeSorter<Characters> sorter;
    performSortTestUsingExample2(sorter);
}

}
