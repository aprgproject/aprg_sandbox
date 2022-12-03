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
constexpr unsigned int MAX_NUMBER_OF_CHARACTERS=256U;
using Characters = vector<char>;
using Integers = vector<int>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = RadixSorterUsingCountingSorter<Characters, MAX_NUMBER_OF_NIBBLES>;
using SmallIntegerSorter = RadixSorterUsingCountingSorter<Integers, MAX_NUMBER_OF_NIBBLES>;
using StringsSorter = RadixSorterUsingCountingSorter<Strings, MAX_NUMBER_OF_CHARACTERS>;
using StabilityCheckObjectsSorter = RadixSorterUsingCountingSorter<StabilityCheckObjects, MAX_NUMBER_OF_NIBBLES>;

CharactersSorter::GetNumberOfDigitsFunction getNumberOfNibblesForCharacter = [](Characters const&) -> unsigned int
{
    return 2U;
};
CharactersSorter::GetDigitAtFunction getNibbleAtForCharacter = [](char const& value, unsigned int const digitIndex) -> unsigned int
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
StringsSorter::GetNumberOfDigitsFunction getNumberOfCharactersForStrings = [](Strings const& strings) -> unsigned int
{
    s_maxNumberOfCharacters=0U;
    for(string const& stringObject : strings)
    {
        s_maxNumberOfCharacters = max(s_maxNumberOfCharacters, stringObject.length());
    }
    return s_maxNumberOfCharacters;
};
StringsSorter::GetDigitAtFunction getCharacterAtForString = [](string const& value, unsigned int const leastSignificantDigitIndex) -> unsigned int
{
    unsigned int digitValue{};
    if(leastSignificantDigitIndex < s_maxNumberOfCharacters)
    {
        unsigned int mostSignificantDigitIndex = s_maxNumberOfCharacters-leastSignificantDigitIndex-1U;
        if(mostSignificantDigitIndex < value.length())
        {
            digitValue = value.at(mostSignificantDigitIndex) & 0xFF;
        }
    }
    return digitValue;
};

StabilityCheckObjectsSorter::GetNumberOfDigitsFunction getNumberOfNibblesForStabilityCheckObject = [](StabilityCheckObjects const&) -> unsigned int
{
    return 2U;
};
StabilityCheckObjectsSorter::GetDigitAtFunction getNibbleAtForStabilityCheckObject = [](StabilityCheckObject const& value, unsigned int const digitIndex) -> unsigned int
{
    return (value.getVisiblePart() >> (digitIndex*4U)) & 0xFU;
};
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample)
{
    CharactersSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnCharactersUsingOneValueExample)
{
    CharactersSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharactersSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnCharactersUsingExample2){
    CharactersSorter sorter(getNumberOfNibblesForCharacter, getNibbleAtForCharacter);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST, because CountingSorterUsingNewPositions is used in RadixSorter

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    SmallIntegerSorter sorter(getNumberOfNibblesForInteger, getNibbleAtForSmallInteger);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

// CANNOT SORT DOUBLE VALUES

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnStringsUsingExample1)
{
    StringsSorter sorter(getNumberOfCharactersForStrings, getCharacterAtForString);
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) // STABLE
{
    StabilityCheckObjectsSorter sorter(getNumberOfNibblesForStabilityCheckObject, getNibbleAtForStabilityCheckObject);
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

}

}
