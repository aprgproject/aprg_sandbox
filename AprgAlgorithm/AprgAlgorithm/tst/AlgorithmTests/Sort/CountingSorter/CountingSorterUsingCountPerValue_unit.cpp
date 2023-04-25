#include <Algorithm/Sort/CountingSorter/CountingSorterUsingCountPerValue.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

#include <list>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
constexpr unsigned int MAX_NUMBER_OF_CHARACTERS = 256U;
constexpr unsigned int MAX_NUMBER_OF_SMALL_INTS = 21U;
using Characters = vector<char>;
using ListOfCharacters = list<char>;
using Integers = vector<int>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = CountingSorterUsingCountPerValue<Characters, MAX_NUMBER_OF_CHARACTERS>;
using ListOfCharactersSorter = CountingSorterUsingCountPerValue<ListOfCharacters, MAX_NUMBER_OF_CHARACTERS>;
using SmallIntegerSorter = CountingSorterUsingCountPerValue<Integers, MAX_NUMBER_OF_SMALL_INTS>;
using StabilityCheckObjectsSorter = CountingSorterUsingCountPerValue<StabilityCheckObjects, MAX_NUMBER_OF_CHARACTERS>;

CharactersSorter::ValueToIndexableValueFunction characterToIndexableValueFunction =
    [](char const& value) -> unsigned int {
    return value & 0xFFU;  // already converts to unsigned integer
};
CharactersSorter::IndexableValueToValueFunction indexableValueToCharacterFunction =
    [](unsigned int const indexableValue) -> char { return static_cast<char>(indexableValue & 0xFFU); };

SmallIntegerSorter::ValueToIndexableValueFunction smallIntToIndexableValueFunction =
    [](int const& value) -> unsigned int {
    // Input: {-5, -10, 0, -3, 8, 5, -1, 10}
    return static_cast<unsigned int>(10 + value);
};
SmallIntegerSorter::IndexableValueToValueFunction indexableValueToSmallIntFunction =
    [](unsigned int const indexableValue) -> int {
    // Input: {-5, -10, 0, -3, 8, 5, -1, 10}
    return static_cast<int>(indexableValue) - 10;
};

StabilityCheckObjectsSorter::ValueToIndexableValueFunction stabilityCheckObjectToIndexableValueFunction =
    [](StabilityCheckObject const& value) -> unsigned int {
    return value.getVisiblePart() & 0xFFU;  // there is some splicing here
};
StabilityCheckObjectsSorter::IndexableValueToValueFunction indexableValueToStabilityCheckObjectFunction =
    [](unsigned int const indexableValue) -> StabilityCheckObject {
    return StabilityCheckObject(static_cast<char>(indexableValue & 0xFFU), 0U);
};

}  // namespace

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter(characterToIndexableValueFunction, indexableValueToCharacterFunction);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter(characterToIndexableValueFunction, indexableValueToCharacterFunction);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter(characterToIndexableValueFunction, indexableValueToCharacterFunction);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter(characterToIndexableValueFunction, indexableValueToCharacterFunction);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnListOfCharactersUsingExample1) {
    ListOfCharactersSorter sorter(characterToIndexableValueFunction, indexableValueToCharacterFunction);
    testSortUsingExample1WithCharacters<ListOfCharactersSorter, ListOfCharacters>(sorter);
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    SmallIntegerSorter sorter(smallIntToIndexableValueFunction, indexableValueToSmallIntFunction);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

// CANNOT SORT DOUBLE VALUES

// CANNOT SORT STRINGS

TEST(CountingSorterUsingCountPerValueTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1)  // NOT STABLE
{
    StabilityCheckObjectsSorter sorter(
        stabilityCheckObjectToIndexableValueFunction, indexableValueToStabilityCheckObjectFunction);
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(
        sorter);
}

}  // namespace algorithm

}  // namespace alba
