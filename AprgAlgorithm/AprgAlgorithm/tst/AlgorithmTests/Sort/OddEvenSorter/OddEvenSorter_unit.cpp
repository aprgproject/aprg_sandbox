#include <Algorithm/Sort/OddEvenSorter/OddEvenSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

#include <list>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Characters = vector<char>;
using ListOfCharacters = list<char>;
using Integers = vector<int>;
using Doubles = vector<double>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = OddEvenSorter<Characters>;
using ListOfCharactersSorter = OddEvenSorter<ListOfCharacters>;
using IntegersSorter = OddEvenSorter<Integers>;
using DoublesSorter = OddEvenSorter<Doubles>;
using StringsSorter = OddEvenSorter<Strings>;
using StabilityCheckObjectsSorter = OddEvenSorter<StabilityCheckObjects>;
}  // namespace

TEST(OddEvenSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(OddEvenSorterTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(OddEvenSorterTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(OddEvenSorterTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST
// The implementation uses indexes so list is not compatible, but this can be changed.

TEST(OddEvenSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter sorter;    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(OddEvenSorterTest, SortWorksOnDoublesUsingExample1) {
    DoublesSorter sorter;
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(OddEvenSorterTest, SortWorksOnStringsUsingExample1) {
    StringsSorter sorter;
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(OddEvenSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) {
    StabilityCheckObjectsSorter sorter;
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}
}  // namespace algorithm

}  // namespace alba
