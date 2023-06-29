#include <Algorithm/Sort/BubbleSorter/CocktailShakerSorter.hpp>
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
using CharactersSorter = CocktailShakerSorter<Characters>;
using ListOfCharactersSorter = CocktailShakerSorter<ListOfCharacters>;
using IntegersSorter = CocktailShakerSorter<Integers>;
using DoublesSorter = CocktailShakerSorter<Doubles>;
using StringsSorter = CocktailShakerSorter<Strings>;
using StabilityCheckObjectsSorter = CocktailShakerSorter<StabilityCheckObjects>;
}  // namespace

TEST(CocktailShakerSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CocktailShakerSorterTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CocktailShakerSorterTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CocktailShakerSorterTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST
// The implementation uses indexes so list is not compatible, but this can be changed.

TEST(CocktailShakerSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter sorter;    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(CocktailShakerSorterTest, SortWorksOnDoublesUsingExample1) {
    DoublesSorter sorter;
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(CocktailShakerSorterTest, SortWorksOnStringsUsingExample1) {
    StringsSorter sorter;
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(CocktailShakerSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) {
    StabilityCheckObjectsSorter sorter;
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}
}  // namespace algorithm

}  // namespace alba
