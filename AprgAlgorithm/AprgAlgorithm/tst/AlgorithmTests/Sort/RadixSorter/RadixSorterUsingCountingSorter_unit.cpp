#include <Algorithm/Sort/RadixSorter/RadixSorterUsingCountingSorter.hpp>
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
constexpr unsigned int MAX_NUMBER_OF_CHARS=256U;
using Characters = vector<char>;
using Integers = vector<int>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharacterSorter = RadixSorterUsingCountingSorter<Characters, MAX_NUMBER_OF_NIBBLES>;
using SmallIntegerSorter = RadixSorterUsingCountingSorter<Integers, MAX_NUMBER_OF_NIBBLES>;
using StringSorter = RadixSorterUsingCountingSorter<Strings, MAX_NUMBER_OF_CHARS>;
using StabilityCheckSorter = RadixSorterUsingCountingSorter<StabilityCheckObjects, MAX_NUMBER_OF_NIBBLES>;

CharacterSorter::GetNumberOfDigitsFunction getNumberOfNibblesForCharacter = [](Characters const&) -> unsigned int
{
    return 2U;
};
CharacterSorter::GetDigitAtFunction getNibbleAtForCharacter = [](char const& value, unsigned int const digitIndex) -> unsigned int
{
    return (value >> (digitIndex*4U)) & 0xFU;
};

SmallIntegerSorter::GetNumberOfDigitsFunction getNumberOfNibblesForInteger = [](Integers const&) -> unsigned int
{
    return 8U;
};
SmallIntegerSorter::GetDigitAtFunction getNibbleAtForSmallInteger = [](int const& value, unsigned int const digitIndex) -> unsigned int
{
    return ((value+10) >> (digitIndex*4U)) & 0xFU;
};

unsigned int s_maxNumberOfCharacters{};
StringSorter::GetNumberOfDigitsFunction getNumberOfCharactersForStrings = [](Strings const& strings) -> unsigned int
{
    s_maxNumberOfCharacters=0U;
    for(string const& stringObject : strings)
    {
        s_maxNumberOfCharacters = max(s_maxNumberOfCharacters, stringObject.length());
    }
    return s_maxNumberOfCharacters;
};
StringSorter::GetDigitAtFunction getCharacterAtForString = [](string const& value, unsigned int const leastSignificantDigitIndex) -> unsigned int
{
    unsigned int characterValue{};
    if(leastSignificantDigitIndex < s_maxNumberOfCharacters)
    {
        unsigned int mostSignificantDigitIndex = s_maxNumberOfCharacters-leastSignificantDigitIndex-1U;
        if(mostSignificantDigitIndex < value.length())
        {
            characterValue = value.at(mostSignificantDigitIndex) & 0xFF;
        }
    }
    return characterValue;
};

StabilityCheckSorter::GetNumberOfDigitsFunction getNumberOfNibblesForStabilityCheckObject = [](StabilityCheckObjects const&) -> unsigned int
{
    return 2U;
};
StabilityCheckSorter::GetDigitAtFunction getNibbleAtForStabilityCheckObject = [](StabilityCheckObject const& value, unsigned int const digitIndex) -> unsigned int
{
    return (value.getVisiblePart() >> (digitIndex*4U)) & 0xFU;
};
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    SmallIntegerSorter sorter(getNumberOfNibblesForInteger, getNibbleAtForSmallInteger);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnStringsUsingExample1)
{
    StringSorter sorter(getNumberOfCharactersForStrings, getCharacterAtForString);
    testSortUsingExample1WithStrings<StringSorter, Strings>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)
{
    StabilityCheckSorter sorter(getNumberOfNibblesForStabilityCheckObject, getNibbleAtForStabilityCheckObject);
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}
}

}