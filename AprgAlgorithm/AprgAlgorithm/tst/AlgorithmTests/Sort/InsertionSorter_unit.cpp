#include <Algorithm/Sort/InsertionSorter.hpp>
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
using CharacterSorter = InsertionSorter<Characters>;
using IntegerSorter = InsertionSorter<Integers>;
}

TEST(InsertionSorterTest, SortWorksOnCharactersUsingExample1)
{
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>();
}

TEST(InsertionSorterTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>();
}

TEST(InsertionSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>();
}

}

}
