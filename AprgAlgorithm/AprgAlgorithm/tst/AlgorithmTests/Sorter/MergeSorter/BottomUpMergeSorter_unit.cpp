#include <Algorithm/Sorter/MergeSorter/BottomUpMergeSorter.hpp>
#include <AlgorithmTests/Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

namespace algorithm
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

}
