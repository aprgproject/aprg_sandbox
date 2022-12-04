#include <Algorithm/Sort/RadixSorter/MostSignificantDigitSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
constexpr unsigned int MAX_NUMBER_OF_NIBBLES=16U;
constexpr unsigned int MAX_NUMBER_OF_CHARACTERS=256U;
using Characters = vector<char>;
using Integers = vector<int>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = MostSignificantDigitSorter<Characters, MAX_NUMBER_OF_NIBBLES>;
using SmallIntegerSorter = MostSignificantDigitSorter<Integers, MAX_NUMBER_OF_NIBBLES>;
using StringsSorter = MostSignificantDigitSorter<Strings, MAX_NUMBER_OF_CHARACTERS>;
using StabilityCheckObjectsSorter = MostSignificantDigitSorter<StabilityCheckObjects, MAX_NUMBER_OF_NIBBLES>;

CharactersSorter::GetDigitAtFunction getNibbleAtForCharacter = [](char const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    return (value >> ((1U-mostSignificantDigitIndex)*4U)) & 0xFU;
};
CharactersSorter::IsDigitFunction isNibbleDigitInvalidForCharacter = [](char const&, unsigned int const digitIndex) -> unsigned int
{
    return digitIndex >= 2U;
};

SmallIntegerSorter::GetDigitAtFunction getNibbleAtForSmallInteger = [](int const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    return ((value+10) >> ((7U-mostSignificantDigitIndex)*4U)) & 0xFU;
};
SmallIntegerSorter::IsDigitFunction isNibbleDigitInvalidForSmallInteger = [](int const&, unsigned int const digitIndex) -> unsigned int
{
    return digitIndex >= 8U;
};

StringsSorter::GetDigitAtFunction getCharacterAtForString = [](string const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    unsigned int digitValue{};
    if(mostSignificantDigitIndex < value.length())
    {
        digitValue = value.at(mostSignificantDigitIndex);
    }
    return digitValue;
};
StringsSorter::IsDigitFunction isDigitInvalidForString = [](string const& value, unsigned int const digitIndex) -> unsigned int
{
    return digitIndex >= value.length();
};

StabilityCheckObjectsSorter::GetDigitAtFunction getNibbleAtForStabilityCheckObject
= [](StabilityCheckObject const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    return (value.getVisiblePart() >> ((1U-mostSignificantDigitIndex)*4U)) & 0xFU;
};
StabilityCheckObjectsSorter::IsDigitFunction isNibbleDigitInvalidForStabilityCheckObject
= [](StabilityCheckObject const&, unsigned int const digitIndex) -> unsigned int
{
    return digitIndex >= 2U;
};
}

TEST(MostSignificantDigitSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample)
{
    CharactersSorter sorter(getNibbleAtForCharacter, isNibbleDigitInvalidForCharacter);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortWorksOnCharactersUsingOneValueExample)
{
    CharactersSorter sorter(getNibbleAtForCharacter, isNibbleDigitInvalidForCharacter);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharactersSorter sorter(getNibbleAtForCharacter, isNibbleDigitInvalidForCharacter);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharactersSorter sorter(getNibbleAtForCharacter, isNibbleDigitInvalidForCharacter);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST

TEST(MostSignificantDigitSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    SmallIntegerSorter sorter(getNibbleAtForSmallInteger, isNibbleDigitInvalidForSmallInteger);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

// CANNOT SORT DOUBLE VALUES

TEST(MostSignificantDigitSorterTest, SortWorksOnStringsUsingExample1)
{
    StringsSorter sorter(getCharacterAtForString, isDigitInvalidForString);
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) // STABLE
{
    StabilityCheckObjectsSorter sorter(getNibbleAtForStabilityCheckObject, isNibbleDigitInvalidForStabilityCheckObject);
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortStartingAtMostSignificantDigitWorksWithDigitThatExistsInAllStrings)
{
    StringsSorter sorter(getCharacterAtForString, isDigitInvalidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2U, 5U, 1U);

    Strings expectedStrings{"spongebob", "patrick", "sandy", "squidward", "mr. crabs", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(MostSignificantDigitSorterTest, SortStartingAtMostSignificantDigitWorksWithDigitThatExistsInSomeOfTheStrings)
{
    StringsSorter sorter(getCharacterAtForString, isDigitInvalidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2U, 5U, 6U);

    Strings expectedStrings{"spongebob", "patrick", "sandy", "mr. crabs", "squidward", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(MostSignificantDigitSorterTest, SortStartingAtMostSignificantDigitWorksWithDigitThatDoesNotExistInOfTheStrings)
{
    StringsSorter sorter(getCharacterAtForString, isDigitInvalidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2U, 5U, 9U);

    Strings expectedStrings{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

}

}
