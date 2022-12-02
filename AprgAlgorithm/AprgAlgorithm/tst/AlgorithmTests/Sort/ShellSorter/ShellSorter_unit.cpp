#include <Algorithm/Sort/ShellSorter/ShellSorter.hpp>
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
using CharacterSorter = ShellSorter<Characters>;
using IntegerSorter = ShellSorter<Integers>;
using DoubleSorter = ShellSorter<Doubles>;
using StringSorter = ShellSorter<Strings>;
using StabilityCheckSorter = ShellSorter<StabilityCheckObjects>;
}

TEST(ShellSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter;
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(ShellSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter;
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(ShellSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegerSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>(sorter);
}

TEST(ShellSorterTest, SortWorksOnDoublesUsingExample1)
{
    DoubleSorter sorter;
    testSortUsingExample1WithDoubleValues<DoubleSorter, Doubles>(sorter);
}

TEST(ShellSorterTest, SortWorksOnStringsUsingExample1)
{
    StringSorter sorter;
    testSortUsingExample1WithStrings<StringSorter, Strings>(sorter);
}

TEST(ShellSorterTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1) // NOT STABLE
{
    StabilityCheckSorter sorter;
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}

}

}
