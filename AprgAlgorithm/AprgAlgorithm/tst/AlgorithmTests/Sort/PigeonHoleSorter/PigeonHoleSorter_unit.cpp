#include <Algorithm/Sort/PigeonHoleSorter/PigeonHoleSorter.hpp>
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
using CharactersSorter = PigeonHoleSorter<Characters>;
using ListOfCharactersSorter = PigeonHoleSorter<ListOfCharacters>;
using IntegersSorter = PigeonHoleSorter<Integers>;
using DoublesSorter = PigeonHoleSorter<Doubles>;
using StringsSorter = PigeonHoleSorter<Strings>;
using StabilityCheckObjectsSorter = PigeonHoleSorter<StabilityCheckObjects>;
}  // namespace

TEST(PigeonHoleSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(PigeonHoleSorterTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(PigeonHoleSorterTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(PigeonHoleSorterTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(PigeonHoleSorterTest, SortWorksOnListOfCharactersUsingExample1) {
    ListOfCharactersSorter sorter;
    testSortUsingExample1WithCharacters<ListOfCharactersSorter, ListOfCharacters>(sorter);
}

TEST(PigeonHoleSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

// CANNOT SORT DOUBLE VALUES

// CANNOT SORT STRINGS

TEST(PigeonHoleSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)
{
    StabilityCheckObjectsSorter sorter;
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

TEST(PigeonHoleSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingOneValueExample) {
    CharactersSorter sorter;
    Characters oneCharacter{'J'};

    sorter.sort(oneCharacter);

    Characters expectedOneCharacter{'J'};
    EXPECT_EQ(expectedOneCharacter, oneCharacter);
}

}  // namespace algorithm

}  // namespace alba
