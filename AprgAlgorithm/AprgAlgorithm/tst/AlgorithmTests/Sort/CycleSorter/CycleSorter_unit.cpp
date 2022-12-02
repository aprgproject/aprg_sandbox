#include <Algorithm/Sort/CycleSorter/CycleSorter.hpp>
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
using Doubles = vector<double>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharacterSorter = CycleSorter<Characters>;
using IntegerSorter = CycleSorter<Integers>;
using DoubleSorter = CycleSorter<Doubles>;
using StringSorter = CycleSorter<Strings>;
using StabilityCheckSorter = CycleSorter<StabilityCheckObjects>;
}

TEST(CycleSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter;
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(CycleSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter;
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(CycleSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegerSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>(sorter);
}

TEST(CycleSorterTest, SortWorksOnDoublesUsingExample1)
{
    DoubleSorter sorter;
    testSortUsingExample1WithDoubleValues<DoubleSorter, Doubles>(sorter);
}

TEST(CycleSorterTest, SortWorksOnStringsUsingExample1)
{
    StringSorter sorter;
    testSortUsingExample1WithStrings<StringSorter, Strings>(sorter);
}

TEST(CycleSorterTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1) // NOT STABLE
{
    StabilityCheckSorter sorter;
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}

}

}
