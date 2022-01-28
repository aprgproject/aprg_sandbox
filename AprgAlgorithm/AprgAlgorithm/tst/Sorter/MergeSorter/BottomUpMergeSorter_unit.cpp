#include <Sorter/MergeSorter/BottomUpMergeSorter.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

TEST(BottomUpMergeSorterTest, SortWorksOnCharactersUsingExample1)
{
    BottomUpMergeSorter<Characters> sorter;
    performSortTestUsingExample1(sorter);
}

TEST(BottomUpMergeSorterTest, SortWorksOnCharactersUsingExample2)
{
    BottomUpMergeSorter<Characters> sorter;
    performSortTestUsingExample2(sorter);
}

}
