#include <Algorithm/Sort/QuickSorter/QuickSorterForForwardList.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Characters = forward_list<char>;
using Integers = forward_list<int>;
using Doubles = forward_list<double>;
using Strings = forward_list<string>;
using StabilityCheckObjects = forward_list<StabilityCheckObject>;
using CharactersSorter = QuickSorterForForwardList<char>;
using IntegersSorter = QuickSorterForForwardList<int>;
using DoublesSorter = QuickSorterForForwardList<double>;
using StringsSorter = QuickSorterForForwardList<string>;
using StabilityCheckObjectsSorter = QuickSorterForForwardList<StabilityCheckObject>;
}  // namespace

TEST(QuickSorterForForwardListTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterForForwardListTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterForForwardListTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterForForwardListTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST

TEST(QuickSorterForForwardListTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(QuickSorterForForwardListTest, SortWorksOnDoublesUsingExample1) {
    DoublesSorter sorter;
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(QuickSorterForForwardListTest, SortWorksOnStringsUsingExample1) {
    StringsSorter sorter;
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(QuickSorterForForwardListTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1)  // NOT STABLE
{
    StabilityCheckObjectsSorter sorter;
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(
        sorter);
}

}  // namespace algorithm

}  // namespace alba
