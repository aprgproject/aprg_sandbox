#include <Sorter/MergeSorter/BottomUpMergeSorter.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

TEST(BottomUpMergeSorterTest, SortWorksOnCharactersUsingExample1)
{
    sortCharactersUsingExample1(make_unique<BottomUpMergeSorter<Characters>>());
}

TEST(BottomUpMergeSorterTest, SortWorksOnCharactersUsingExample2)
{
    sortCharactersUsingExample2(make_unique<BottomUpMergeSorter<Characters>>());
}

}
