#include <Sorter/MergeSorter/TopDownMergeSorter.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

TEST(TopDownMergeSorterTest, SortWorksOnCharactersUsingExample1)
{
    sortCharactersUsingExample1(make_unique<TopDownMergeSorter<Characters>>());
}

TEST(TopDownMergeSorterTest, SortWorksOnCharactersUsingExample2)
{
    sortCharactersUsingExample2(make_unique<TopDownMergeSorter<Characters>>());
}

}

