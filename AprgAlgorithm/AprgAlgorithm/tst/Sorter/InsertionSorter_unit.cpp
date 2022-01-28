#include <Sorter/InsertionSorter.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

TEST(InsertionSorterTest, SortWorksOnCharactersUsingExample1)
{
    sortCharactersUsingExample1(make_unique<InsertionSorter<Characters>>());
}

TEST(InsertionSorterTest, SortWorksOnCharactersUsingExample2)
{
    sortCharactersUsingExample2(make_unique<InsertionSorter<Characters>>());
}

}
