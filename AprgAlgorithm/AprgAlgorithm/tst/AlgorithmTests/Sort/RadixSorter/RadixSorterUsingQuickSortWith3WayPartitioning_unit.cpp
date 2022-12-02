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
using CharacterSorter = RadixSorterUsingQuickSortWith3WayPartitioning<Characters, unsigned int>;
using SmallIntegerSorter = RadixSorterUsingQuickSortWith3WayPartitioning<Integers, unsigned int>;
using StringSorter = RadixSorterUsingQuickSortWith3WayPartitioning<Strings, char>;
using StabilityCheckSorter = RadixSorterUsingQuickSortWith3WayPartitioning<StabilityCheckObjects, unsigned int>;

CharacterSorter::GetDigitAtFunction getNibbleAtForCharacter = [](char const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    return (value >> ((1U-mostSignificantDigitIndex)*4U)) & 0xFU;
};
CharacterSorter::IsDigitFunction isNibbleDigitValidForCharacter = [](char const&, unsigned int const digitIndex) -> unsigned int
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

StringSorter::GetDigitAtFunction getCharacterAtForString = [](string const& value, unsigned int const mostSignificantDigitIndex) -> char
{
    char digitValue{};
    if(mostSignificantDigitIndex < value.length())
    {
        digitValue = value.at(mostSignificantDigitIndex);
    }
    return digitValue;
};
StringSorter::IsDigitFunction isDigitValidForString = [](string const& value, unsigned int const digitIndex) -> unsigned int
{
    return digitIndex < value.length();
};

StabilityCheckSorter::GetDigitAtFunction getNibbleAtForStabilityCheckObject
= [](StabilityCheckObject const& value, unsigned int const mostSignificantDigitIndex) -> unsigned int
{
    return (value.getVisiblePart() >> ((1U-mostSignificantDigitIndex)*4U)) & 0xFU;
};
StabilityCheckSorter::IsDigitFunction isNibbleDigitValidForStabilityCheckObject
= [](StabilityCheckObject const&, unsigned int const digitIndex) -> unsigned int
{
    return digitIndex < 2U;
};
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter(getNibbleAtForCharacter, isNibbleDigitValidForCharacter);
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter(getNibbleAtForCharacter, isNibbleDigitValidForCharacter);
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    SmallIntegerSorter sorter(getNibbleAtForSmallInteger, isNibbleDigitValidForSmallInteger);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

// CANNOT SORT DOUBLE VALUES

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortWorksOnStringsUsingExample1)
{
    StringSorter sorter(getCharacterAtForString, isDigitValidForString);
    testSortUsingExample1WithStrings<StringSorter, Strings>(sorter);
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1) // STABLE
{
    StabilityCheckSorter sorter(getNibbleAtForStabilityCheckObject, isNibbleDigitValidForStabilityCheckObject);
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortStartingAtMostSignificantDigitWorksWithDigitThatExistsInAllStrings)
{
    StringSorter sorter(getCharacterAtForString, isDigitValidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2U, 5U, 1U);

    Strings expectedStrings{"spongebob", "patrick", "sandy", "squidward", "mr. crabs", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortStartingAtMostSignificantDigitWorksWithDigitThatExistsInSomeOfTheStrings)
{
    StringSorter sorter(getCharacterAtForString, isDigitValidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2U, 5U, 6U);

    Strings expectedStrings{"spongebob", "patrick", "sandy", "mr. crabs", "squidward", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(RadixSorterUsingQuickSortWith3WayPartitioningTest, SortStartingAtMostSignificantDigitWorksWithDigitThatDoesNotExistInOfTheStrings)
{
    StringSorter sorter(getCharacterAtForString, isDigitValidForString);
    Strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortStartingAtMostSignificantDigit(stringsToTest, 2U, 5U, 9U);

    Strings expectedStrings{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

}

}
