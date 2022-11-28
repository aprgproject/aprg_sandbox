#include <Algorithm/Sort/InsertionSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

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
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharacterSorter = InsertionSorter<Characters>;
using IntegerSorter = InsertionSorter<Integers>;
using StringSorter = InsertionSorter<Strings>;
using StabilityCheckSorter = InsertionSorter<StabilityCheckObjects>;
}
TEST(InsertionSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter;    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(InsertionSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter;
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(InsertionSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegerSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>(sorter);
}

TEST(InsertionSorterTest, SortWorksOnStringsUsingExample1)
{
    StringSorter sorter;
    testSortUsingExample1WithStrings<StringSorter, Strings>(sorter);
}

TEST(InsertionSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)
{
    StabilityCheckSorter sorter;    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}

}
}
