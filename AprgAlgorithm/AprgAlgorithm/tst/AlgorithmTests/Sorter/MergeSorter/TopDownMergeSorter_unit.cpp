#include <Algorithm/Sorter/MergeSorter/TopDownMergeSorter.hpp>
#include <AlgorithmTests/Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

namespace algorithm
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

}
