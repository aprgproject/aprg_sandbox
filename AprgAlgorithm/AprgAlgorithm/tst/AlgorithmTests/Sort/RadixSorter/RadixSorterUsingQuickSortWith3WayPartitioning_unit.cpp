#include <Algorithm/Sort/RadixSorter/RadixSorterUsingQuickSortWith3WayPartitioning.hpp>
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
using Characters = vector<char>;
using Integers = vector<int>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = RadixSorterUsingQuickSortWith3WayPartitioning<Characters, unsigned int>;
using SmallIntegerSorter = RadixSorterUsingQuickSortWith3WayPartitioning<Integers, unsigned int>;
using StringsSorter = RadixSorterUsingQuickSortWith3WayPartitioning<Strings, char>;
using StabilityCheckObjectsSorter = RadixSorterUsingQuickSortWith3WayPartitioning<StabilityCheckObjects, unsigned int>;

CharactersSorter::GetDigitAtFunction getNibbleAtForCharacter = [](char const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    return (value >> ((1U-mostSignificantDigitIndex)*4U)) & 0xFU;
};
CharactersSorter::IsDigitFunction isNibbleDigitValidForCharacter = [](char const&, unsigned int const digitIndex) -> unsigned int
{
    return digitIndex < 2U;
};

SmallIntegerSorter::GetDigitAtFunction getNibbleAtForSmallInteger = [](int const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    return ((value+10) >> ((7U-mostSignificantDigitIndex)*4U)) & 0xFU;
};
SmallIntegerSorter::IsDigitFunction isNibbleDigitValidForSmallInteger = [](int const&, unsigned int const digitIndex) -> unsigned int
{
    return digitIndex < 8U;
};

StringsSorter::GetDigitAtFunction getCharacterAtForString = [](string const& value, unsigned int const mostSignificantDigitIndex) -> char
{
    char digitValue{};
    if(mostSignificantDigitIndex < value.length())
    {
        digitValue = value.at(mostSignificantDigitIndex);
    }
    return digitValue;
};
StringsSorter::IsDigitFunction isDigitValidForString = [](string const& value, unsigned int const digitIndex) -> unsigned int
{
    return digitIndex < value.length();
};

StabilityCheckObjectsSorter::GetDigitAtFunction getNibbleAtForStabilityCheckObject
= [](StabilityCheckObject const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    return (value.getVisiblePart() >> ((1U-mostSignificantDigitIndex)*4U)) & 0xFU;
};
StabilityCheckObjectsSorter::IsDigitFunction isNibbleDigitValidForStabilityCheckObject
= [](StabilityCheckObject const&, unsigned int const digitIndex) -> unsigned int
{
    return digitIndex < 2U;
};
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample)
{
    CharactersSorter sorter(getNibbleAtForCharacter, isNibbleDigitValidForCharacter);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortWorksOnCharactersUsingOneValueExample)
{
    CharactersSorter sorter(getNibbleAtForCharacter, isNibbleDigitValidForCharacter);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1)
{
    CharactersSorter sorter(getNibbleAtForCharacter, isNibbleDigitValidForCharacter);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortWorksOnCharactersUsingExample2)
{
    CharactersSorter sorter(getNibbleAtForCharacter, isNibbleDigitValidForCharacter);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST, actually it might be possible if we change indexes to iterators

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    SmallIntegerSorter sorter(getNibbleAtForSmallInteger, isNibbleDigitValidForSmallInteger);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

// CANNOT SORT DOUBLE VALUES

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortWorksOnStringsUsingExample1)
{
    StringsSorter sorter(getCharacterAtForString, isDigitValidForString);
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1) // STABLE
{
    StabilityCheckObjectsSorter sorter(getNibbleAtForStabilityCheckObject, isNibbleDigitValidForStabilityCheckObject);
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortStartingAtMostSignificantDigitWorksWithDigitThatExistsInAllStrings)
{
    StringsSorter sorter(getCharacterAtForString, isDigitValidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2U, 5U, 1U);

    Strings expectedStrings{"spongebob", "patrick", "sandy", "squidward", "mr. crabs", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortStartingAtMostSignificantDigitWorksWithDigitThatExistsInSomeOfTheStrings)
{
    StringsSorter sorter(getCharacterAtForString, isDigitValidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2U, 5U, 6U);

    Strings expectedStrings{"spongebob", "patrick", "sandy", "mr. crabs", "squidward", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortStartingAtMostSignificantDigitWorksWithDigitThatDoesNotExistInOfTheStrings)
{
    StringsSorter sorter(getCharacterAtForString, isDigitValidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2U, 5U, 9U);

    Strings expectedStrings{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

}

}
