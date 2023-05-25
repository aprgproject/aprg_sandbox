#include <Algorithm/Sort/RadixSorter/RadixSorterUsingCountingSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
constexpr int MAX_NUMBER_OF_NIBBLES = 16;
constexpr int MAX_NUMBER_OF_CHARACTERS = 256;
using Characters = vector<char>;
using Integers = vector<int>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = RadixSorterUsingCountingSorter<Characters, MAX_NUMBER_OF_NIBBLES>;
using SmallIntegerSorter = RadixSorterUsingCountingSorter<Integers, MAX_NUMBER_OF_NIBBLES>;
using StringsSorter = RadixSorterUsingCountingSorter<Strings, MAX_NUMBER_OF_CHARACTERS>;
using StabilityCheckObjectsSorter = RadixSorterUsingCountingSorter<StabilityCheckObjects, MAX_NUMBER_OF_NIBBLES>;

CharactersSorter::GetNumberOfDigitsFunction getNumberOfNibblesForCharacter = [](Characters const&) -> int { return 2; };
CharactersSorter::GetDigitAtFunction getNibbleAtForCharacter = [](char const& value, int const digitIndex) -> int {
    return (value >> (digitIndex * 4)) & 0xF;
};

SmallIntegerSorter::GetNumberOfDigitsFunction getNumberOfNibblesForInteger = [](Integers const&) -> int { return 8; };
SmallIntegerSorter::GetDigitAtFunction getNibbleAtForSmallInteger = [](int const& value, int const digitIndex) -> int {
    return ((value + 10) >> (digitIndex * 4)) & 0xF;
};

int s_maxNumberOfCharacters{};
StringsSorter::GetNumberOfDigitsFunction getNumberOfCharactersForStrings = [](Strings const& strings) -> int {
    s_maxNumberOfCharacters = 0;
    for (string const& stringObject : strings) {
        s_maxNumberOfCharacters = max(s_maxNumberOfCharacters, static_cast<int>(stringObject.length()));
    }
    return s_maxNumberOfCharacters;
};
StringsSorter::GetDigitAtFunction getCharacterAtForString = [](string const& value,
                                                               int const leastSignificantDigitIndex) -> int {
    int digitValue{};
    if (leastSignificantDigitIndex < s_maxNumberOfCharacters) {
        int mostSignificantDigitIndex = s_maxNumberOfCharacters - leastSignificantDigitIndex - 1;
        if (mostSignificantDigitIndex < static_cast<int>(value.length())) {
            digitValue = value.at(mostSignificantDigitIndex) & 0xFF;
        }
    }
    return digitValue;
};

StabilityCheckObjectsSorter::GetNumberOfDigitsFunction getNumberOfNibblesForStabilityCheckObject =
    [](StabilityCheckObjects const&) -> int { return 2; };
StabilityCheckObjectsSorter::GetDigitAtFunction getNibbleAtForStabilityCheckObject =
    [](StabilityCheckObject const& value, int const digitIndex) -> int {
    return (value.getVisiblePart() >> (digitIndex * 4)) & 0xF;
};
}  // namespace

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST, because CountingSorterUsingNewPositions is used in RadixSorter

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    SmallIntegerSorter sorter(getNumberOfNibblesForInteger, getNibbleAtForSmallInteger);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

// CANNOT SORT DOUBLE VALUES

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnStringsUsingExample1) {
    StringsSorter sorter(getNumberOfCharactersForStrings, getCharacterAtForString);
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)  // STABLE
{
    StabilityCheckObjectsSorter sorter(getNumberOfNibblesForStabilityCheckObject, getNibbleAtForStabilityCheckObject);
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

}  // namespace algorithm

}  // namespace alba
