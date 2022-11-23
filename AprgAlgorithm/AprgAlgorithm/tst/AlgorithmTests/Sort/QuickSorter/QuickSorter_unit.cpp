#include <Algorithm/Sort/QuickSorter/QuickSorter.hpp>
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
using CharacterSorter = QuickSorter<Characters>;
using IntegerSorter = QuickSorter<Integers>;
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1)
{
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>();
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>();
}

TEST(QuickSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>();
}

}

}
