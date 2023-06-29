#include <Algorithm/Sort/RadixSorter/LeastSignificantDigitSorter.hpp>
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
using CharactersSorter = LeastSignificantDigitSorter<Characters, MAX_NUMBER_OF_NIBBLES>;
using SmallIntegerSorter = LeastSignificantDigitSorter<Integers, MAX_NUMBER_OF_NIBBLES>;
using StringsSorter = LeastSignificantDigitSorter<Strings, MAX_NUMBER_OF_CHARACTERS>;
using StabilityCheckObjectsSorter = LeastSignificantDigitSorter<StabilityCheckObjects, MAX_NUMBER_OF_NIBBLES>;

CharactersSorter::GetNumberOfDigitsFunction getNumberOfNibblesForCharacter = [](Characters const&) -> int { return 2; };
CharactersSorter::GetDigitAtFunction getNibbleAtForCharacter = [](char const& value,
                                                                  int const mostSignificantDigitIndex) -> int {
    return (value >> ((1 - mostSignificantDigitIndex) * 4)) & 0xF;
};

SmallIntegerSorter::GetNumberOfDigitsFunction getNumberOfNibblesForInteger = [](Integers const&) -> int { return 8; };
SmallIntegerSorter::GetDigitAtFunction getNibbleAtForSmallInteger = [](int const& value,
                                                                       int const mostSignificantDigitIndex) -> int {
    return ((value + 10) >> ((7 - mostSignificantDigitIndex) * 4)) & 0xF;
};

StringsSorter::GetNumberOfDigitsFunction getNumberOfCharactersForStrings = [](Strings const& strings) -> int {
    int maxNumberOfCharacters(0);
    for (string const& stringObject : strings) {
        maxNumberOfCharacters = max(maxNumberOfCharacters, static_cast<int>(stringObject.length()));
    }
    return maxNumberOfCharacters;
};
StringsSorter::GetDigitAtFunction getCharacterAtForString = [](string const& value,
                                                               int const mostSignificantDigitIndex) -> int {
    int digitValue{};
    if (mostSignificantDigitIndex < static_cast<int>(value.length())) {
        digitValue = value[mostSignificantDigitIndex];
    }
    return digitValue;
};

StabilityCheckObjectsSorter::GetNumberOfDigitsFunction getNumberOfNibblesForStabilityCheckObject =
    [](StabilityCheckObjects const&) -> int { return 2; };
StabilityCheckObjectsSorter::GetDigitAtFunction getNibbleAtForStabilityCheckObject =
    [](StabilityCheckObject const& value, int const mostSignificantDigitIndex) -> int {
    return (value.getVisiblePart() >> ((1 - mostSignificantDigitIndex) * 4)) & 0xF;
};
}  // namespace

TEST(LeastSignificantDigitSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(LeastSignificantDigitSorterTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(LeastSignificantDigitSorterTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(LeastSignificantDigitSorterTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST

TEST(LeastSignificantDigitSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    SmallIntegerSorter sorter(getNumberOfNibblesForInteger, getNibbleAtForSmallInteger);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

// CANNOT SORT DOUBLE VALUES

TEST(LeastSignificantDigitSorterTest, SortWorksOnStringsUsingExample1) {
    StringsSorter sorter(getNumberOfCharactersForStrings, getCharacterAtForString);
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(LeastSignificantDigitSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)
{
    StabilityCheckObjectsSorter sorter(getNumberOfNibblesForStabilityCheckObject, getNibbleAtForStabilityCheckObject);
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);}

TEST(LeastSignificantDigitSorterTest, SortAtLeastSignificantDigitWorksWithDigitThatExistsInAllStrings) {
    StringsSorter sorter(getNumberOfCharactersForStrings, getCharacterAtForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy",
                          "ms. puff",  "pearl",   "larry",     "plankton"};

    sorter.sortAtLeastSignificantDigit(stringsToTest, 1);

    Strings expectedStrings{"patrick",   "sandy",     "larry",     "pearl",   "plankton",
                            "spongebob", "squidward", "mr. crabs", "ms. puff"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(LeastSignificantDigitSorterTest, SortAtLeastSignificantDigitWorksWithDigitThatExistsInSomeOfTheStrings) {
    StringsSorter sorter(getNumberOfCharactersForStrings, getCharacterAtForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy",
                          "ms. puff",  "pearl",   "larry",     "plankton"};

    sorter.sortAtLeastSignificantDigit(stringsToTest, 6);

    Strings expectedStrings{"sandy",     "pearl",    "larry",   "mr. crabs", "squidward",
                            "spongebob", "ms. puff", "patrick", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(LeastSignificantDigitSorterTest, SortAtLeastSignificantDigitWorksWithDigitThatDoesNotExistInOfTheStrings) {
    StringsSorter sorter(getNumberOfCharactersForStrings, getCharacterAtForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy",
                          "ms. puff",  "pearl",   "larry",     "plankton"};

    sorter.sortAtLeastSignificantDigit(stringsToTest, 9);

    Strings expectedStrings{"spongebob", "patrick", "mr. crabs", "squidward", "sandy",
                            "ms. puff",  "pearl",   "larry",     "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

}  // namespace algorithm

}  // namespace alba
