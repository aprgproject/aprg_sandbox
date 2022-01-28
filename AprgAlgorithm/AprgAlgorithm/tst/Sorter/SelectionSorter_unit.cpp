#include <Sorter/SelectionSorter.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

TEST(SelectionSorterTest, SortWorksOnCharactersUsingExample1)
{
    sortCharactersUsingExample1(make_unique<SelectionSorter<Characters>>());
}

TEST(SelectionSorterTest, SortWorksOnCharactersUsingExample2)
{
    sortCharactersUsingExample2(make_unique<SelectionSorter<Characters>>());
}

}

