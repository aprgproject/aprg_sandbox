#include <Algorithm/Sort/SelectionSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Characters = vector<char>;
using Integers = vector<int>;
using CharacterSorter = SelectionSorter<Characters>;
using IntegerSorter = SelectionSorter<Integers>;
}

TEST(SelectionSorterTest, SortWorksOnCharactersUsingExample1)
{
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>();
}

TEST(SelectionSorterTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>();
}

TEST(SelectionSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>();
}

}

}
