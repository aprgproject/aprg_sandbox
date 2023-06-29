#include <Algorithm/Sort/MergeSorter/MergeSorterForList.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Characters = list<char>;
using Integers = list<int>;
using Doubles = list<double>;
using Strings = list<string>;
using StabilityCheckObjects = list<StabilityCheckObject>;
using CharactersSorter = MergeSorterForList<char>;
using IntegersSorter = MergeSorterForList<int>;
using DoublesSorter = MergeSorterForList<double>;
using StringsSorter = MergeSorterForList<string>;
using StabilityCheckObjectsSorter = MergeSorterForList<StabilityCheckObject>;
}  // namespace

TEST(MergeSorterForListTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(MergeSorterForListTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(MergeSorterForListTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(MergeSorterForListTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(MergeSorterForListTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(MergeSorterForListTest, SortWorksOnDoublesUsingExample1) {
    DoublesSorter sorter;
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(MergeSorterForListTest, SortWorksOnStringsUsingExample1) {
    StringsSorter sorter;
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(MergeSorterForListTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)
{
    StabilityCheckObjectsSorter sorter;
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);}

}  // namespace algorithm

}  // namespace alba
