#include <Sorter/QuickSorter/QuickSorter.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1)
{
    sortCharactersUsingExample1(make_unique<QuickSorter<Characters>>());
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample2)
{
    sortCharactersUsingExample2(make_unique<QuickSorter<Characters>>());
}

}


