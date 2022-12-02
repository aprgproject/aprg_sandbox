#include <Algorithm/Sort/QuickSorter/QuickSorterWith3WayPartitioning.hpp>
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
using CharacterSorter = QuickSorterWith3WayPartitioning<Characters>;
using IntegerSorter = QuickSorterWith3WayPartitioning<Integers>;
using DoubleSorter = QuickSorterWith3WayPartitioning<Doubles>;
using StringSorter = QuickSorterWith3WayPartitioning<Strings>;
using StabilityCheckSorter = QuickSorterWith3WayPartitioning<StabilityCheckObjects>;
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter;
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter;
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegerSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnDoublesUsingExample1)
{
    DoubleSorter sorter;
    testSortUsingExample1WithDoubleValues<DoubleSorter, Doubles>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnStringsUsingExample1)
{
    StringSorter sorter;
    testSortUsingExample1WithStrings<StringSorter, Strings>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1) // NOT STABLE
{
    StabilityCheckSorter sorter;
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}

}

}
