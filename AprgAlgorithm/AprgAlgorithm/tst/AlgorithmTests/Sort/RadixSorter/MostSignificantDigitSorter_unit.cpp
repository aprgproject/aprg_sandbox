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
using CharacterSorter = MostSignificantDigitSorter<Characters, MAX_NUMBER_OF_NIBBLES>;
using SmallIntegerSorter = MostSignificantDigitSorter<Integers, MAX_NUMBER_OF_NIBBLES>;
using StringSorter = MostSignificantDigitSorter<Strings, MAX_NUMBER_OF_CHARACTERS>;
using StabilityCheckSorter = MostSignificantDigitSorter<StabilityCheckObjects, MAX_NUMBER_OF_NIBBLES>;

CharacterSorter::GetDigitAtFunction getNibbleAtForCharacter = [](char const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    return (value >> ((1U-mostSignificantDigitIndex)*4U)) & 0xFU;
};
CharacterSorter::IsDigitFunction isNibbleDigitInvalidForCharacter = [](char const&, unsigned int const digitIndex) -> unsigned int
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

StringSorter::GetDigitAtFunction getCharacterAtForString = [](string const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    unsigned int digitValue{};
    if(mostSignificantDigitIndex < value.length())
    {
        digitValue = value.at(mostSignificantDigitIndex);
    }
    return digitValue;
};
StringSorter::IsDigitFunction isDigitInvalidForString = [](string const& value, unsigned int const digitIndex) -> unsigned int
{
    return digitIndex >= value.length();
};

StabilityCheckSorter::GetDigitAtFunction getNibbleAtForStabilityCheckObject
= [](StabilityCheckObject const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    return (value.getVisiblePart() >> ((1U-mostSignificantDigitIndex)*4U)) & 0xFU;
};
StabilityCheckSorter::IsDigitFunction isNibbleDigitInvalidForStabilityCheckObject
= [](StabilityCheckObject const&, unsigned int const digitIndex) -> unsigned int
{
    return digitIndex >= 2U;
};
}

TEST(MostSignificantDigitSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter(getNibbleAtForCharacter, isNibbleDigitInvalidForCharacter);
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter(getNibbleAtForCharacter, isNibbleDigitInvalidForCharacter);
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    SmallIntegerSorter sorter(getNibbleAtForSmallInteger, isNibbleDigitInvalidForSmallInteger);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortWorksOnStringsUsingExample1)
{
    StringSorter sorter(getCharacterAtForString, isDigitInvalidForString);
    testSortUsingExample1WithStrings<StringSorter, Strings>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)
{
    StabilityCheckSorter sorter(getNibbleAtForStabilityCheckObject, isNibbleDigitInvalidForStabilityCheckObject);
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}

TEST(MostSignificantDigitSorterTest, SortStartingAtMostSignificantDigitWorksWithDigitThatExistsInAllStrings)
{
    StringSorter sorter(getCharacterAtForString, isDigitInvalidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2U, 5U, 1U);

    Strings expectedStrings{"spongebob", "patrick", "sandy", "squidward", "mr. crabs", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(MostSignificantDigitSorterTest, SortStartingAtMostSignificantDigitWorksWithDigitThatExistsInSomeOfTheStrings)
{
    StringSorter sorter(getCharacterAtForString, isDigitInvalidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2U, 5U, 6U);

    Strings expectedStrings{"spongebob", "patrick", "sandy", "mr. crabs", "squidward", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(MostSignificantDigitSorterTest, SortStartingAtMostSignificantDigitWorksWithDigitThatDoesNotExistInOfTheStrings)
{
    StringSorter sorter(getCharacterAtForString, isDigitInvalidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2U, 5U, 9U);

    Strings expectedStrings{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

}

}
