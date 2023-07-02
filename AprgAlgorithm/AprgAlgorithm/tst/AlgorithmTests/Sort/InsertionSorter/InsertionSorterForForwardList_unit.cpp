#include <Algorithm/Sort/InsertionSorter/InsertionSorterForForwardList.hpp>
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
using CharactersSorter = InsertionSorterForForwardList<char>;
using IntegersSorter = InsertionSorterForForwardList<int>;
using DoublesSorter = InsertionSorterForForwardList<double>;
using StringsSorter = InsertionSorterForForwardList<string>;
using StabilityCheckObjectsSorter = InsertionSorterForForwardList<StabilityCheckObject>;
}  // namespace

TEST(InsertionSorterForForwardListTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(InsertionSorterForForwardListTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(InsertionSorterForForwardListTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(InsertionSorterForForwardListTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST

TEST(InsertionSorterForForwardListTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(InsertionSorterForForwardListTest, SortWorksOnDoublesUsingExample1) {
    DoublesSorter sorter;
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(InsertionSorterForForwardListTest, SortWorksOnStringsUsingExample1) {
    StringsSorter sorter;
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(InsertionSorterForForwardListTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)
{
    StabilityCheckObjectsSorter sorter;
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

}  // namespace algorithm

}  // namespace alba
