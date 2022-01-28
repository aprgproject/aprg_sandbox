#include <Sorter/HeapSorter.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

TEST(HeapSorterTest, SortWorksOnCharactersUsingExample1)
{
    sortCharactersUsingExample1(make_unique<HeapSorter<Characters>>());
}

TEST(HeapSorterTest, SortWorksOnCharactersUsingExample2)
{
    sortCharactersUsingExample2(make_unique<HeapSorter<Characters>>());
}

}
