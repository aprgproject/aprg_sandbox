#include <Algorithm/Sort/RadixSorter/LeastSignificantDigitSorter.hpp>
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
using CharactersSorter = LeastSignificantDigitSorter<Characters, MAX_NUMBER_OF_NIBBLES>;
using SmallIntegerSorter = LeastSignificantDigitSorter<Integers, MAX_NUMBER_OF_NIBBLES>;
using StringsSorter = LeastSignificantDigitSorter<Strings, MAX_NUMBER_OF_CHARACTERS>;
using StabilityCheckObjectsSorter = LeastSignificantDigitSorter<StabilityCheckObjects, MAX_NUMBER_OF_NIBBLES>;

CharactersSorter::GetDigitAtFunction getNibbleAtForCharacter = [](char const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    return (value >> ((1U-mostSignificantDigitIndex)*4U)) & 0xFU;
};

SmallIntegerSorter::GetDigitAtFunction getNibbleAtForSmallInteger = [](int const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    return ((value+10) >> ((7U-mostSignificantDigitIndex)*4U)) & 0xFU;
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

StabilityCheckObjectsSorter::GetDigitAtFunction getNibbleAtForStabilityCheckObject
= [](StabilityCheckObject const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    return (value.getVisiblePart() >> ((1U-mostSignificantDigitIndex)*4U)) & 0xFU;
};
}

TEST(LeastSignificantDigitSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample)
{
    CharactersSorter sorter(getNibbleAtForCharacter);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(LeastSignificantDigitSorterTest, SortWorksOnCharactersUsingOneValueExample)
{
    CharactersSorter sorter(getNibbleAtForCharacter);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(LeastSignificantDigitSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharactersSorter sorter(getNibbleAtForCharacter);    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(LeastSignificantDigitSorterTest, SortWorksOnCharactersUsingExample2){
    CharactersSorter sorter(getNibbleAtForCharacter);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST

TEST(LeastSignificantDigitSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    SmallIntegerSorter sorter(getNibbleAtForSmallInteger);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

// CANNOT SORT DOUBLE VALUES

TEST(LeastSignificantDigitSorterTest, SortWorksOnStringsUsingExample1)
{
    StringsSorter sorter(getCharacterAtForString);
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(LeastSignificantDigitSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) // STABLE
{
    StabilityCheckObjectsSorter sorter(getNibbleAtForStabilityCheckObject);
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

TEST(LeastSignificantDigitSorterTest, SortAtLeastSignificantDigitWorksWithDigitThatExistsInAllStrings)
{
    StringsSorter sorter(getCharacterAtForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortAtLeastSignificantDigit(stringsToTest, 1U);

    Strings expectedStrings{"patrick", "sandy", "larry", "pearl", "plankton", "spongebob", "squidward", "mr. crabs", "ms. puff"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(LeastSignificantDigitSorterTest, SortAtLeastSignificantDigitWorksWithDigitThatExistsInSomeOfTheStrings)
{
    StringsSorter sorter(getCharacterAtForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortAtLeastSignificantDigit(stringsToTest, 6U);

    Strings expectedStrings{"sandy", "pearl", "larry", "mr. crabs", "squidward", "spongebob", "ms. puff", "patrick", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(LeastSignificantDigitSorterTest, SortAtLeastSignificantDigitWorksWithDigitThatDoesNotExistInOfTheStrings)
{
    StringsSorter sorter(getCharacterAtForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortAtLeastSignificantDigit(stringsToTest, 9U);

    Strings expectedStrings{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

}

}
