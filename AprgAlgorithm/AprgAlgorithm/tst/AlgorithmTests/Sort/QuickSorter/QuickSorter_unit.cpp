#include <Algorithm/Sort/QuickSorter/QuickSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Characters = vector<char>;
using Integers = vector<int>;
using Doubles = vector<double>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = QuickSorter<Characters>;
using IntegersSorter = QuickSorter<Integers>;
using DoublesSorter = QuickSorter<Doubles>;
using StringsSorter = QuickSorter<Strings>;
using StabilityCheckObjectsSorter = QuickSorter<StabilityCheckObjects>;
}  // namespace

TEST(QuickSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST, actually it might be possible if we change indexes to iterators

TEST(QuickSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(QuickSorterTest, SortWorksOnDoublesUsingExample1) {
    DoublesSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(QuickSorterTest, SortWorksOnStringsUsingExample1) {
    StringsSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(QuickSorterTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1)
{
    StabilityCheckObjectsSorter sorter(PivotType::LowestIndex);
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(
        sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtLowestIndex) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtHighestIndex) {
    CharactersSorter sorter(PivotType::HighestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtRandomIndex) {
    CharactersSorter sorter(PivotType::RandomIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtMedianOfMedians) {
    CharactersSorter sorter(PivotType::MedianOfMedians);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

}  // namespace algorithm

}  // namespace alba
