#include <Algorithm/Sort/QuickSorter/QuickSorterWithIterativeApproach.hpp>
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
using CharactersSorter = QuickSorterWithIterativeApproach<Characters>;
using IntegersSorter = QuickSorterWithIterativeApproach<Integers>;
using DoublesSorter = QuickSorterWithIterativeApproach<Doubles>;
using StringsSorter = QuickSorterWithIterativeApproach<Strings>;
using StabilityCheckObjectsSorter = QuickSorterWithIterativeApproach<StabilityCheckObjects>;
}  // namespace

TEST(QuickSorterWithIterativeApproachTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWithIterativeApproachTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWithIterativeApproachTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWithIterativeApproachTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST, actually it might be possible if we change indexes to iterators

TEST(QuickSorterWithIterativeApproachTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(QuickSorterWithIterativeApproachTest, SortWorksOnDoublesUsingExample1) {
    DoublesSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(QuickSorterWithIterativeApproachTest, SortWorksOnStringsUsingExample1) {
    StringsSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(QuickSorterWithIterativeApproachTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1)  // NOT STABLE
{
    StabilityCheckObjectsSorter sorter(PivotType::LowestIndex);
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(
        sorter);
}

TEST(QuickSorterWithIterativeApproachTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtLowestIndex) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWithIterativeApproachTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtHighestIndex) {
    CharactersSorter sorter(PivotType::HighestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWithIterativeApproachTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtRandomIndex) {
    CharactersSorter sorter(PivotType::RandomIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWithIterativeApproachTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtMedianOfMedians) {
    CharactersSorter sorter(PivotType::MedianOfMedians);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

}  // namespace algorithm

}  // namespace alba
