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
constexpr unsigned int MAX_NUMBER_OF_BITS=256U;
using Characters = vector<char>;
using Integers = vector<int>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharacterSorter = RadixSorterUsingCountingSorter<Characters, MAX_NUMBER_OF_BITS>;
using SmallIntegerSorter = RadixSorterUsingCountingSorter<Integers, MAX_NUMBER_OF_BITS>;
using StabilityCheckSorter = RadixSorterUsingCountingSorter<StabilityCheckObjects, MAX_NUMBER_OF_BITS>;

CharacterSorter::GetNumberOfDigitsFunction getNumberOfBitsForCharacter = [](Characters const&) -> unsigned int
{
    return 8U;
};
CharacterSorter::GetDigitAtFunction getBitAtForCharacter = [](char const& value, unsigned int const digitIndex) -> unsigned int
{
    return (value >> digitIndex) & 1U;
};
SmallIntegerSorter::GetNumberOfDigitsFunction getNumberOfBitsForInteger = [](Integers const&) -> unsigned int
{
    return 32U;
};
SmallIntegerSorter::GetDigitAtFunction getBitAtForSmallInteger = [](int const& value, unsigned int const digitIndex) -> unsigned int
{
    return ((value+10) >> digitIndex) & 1U;
};
StabilityCheckSorter::GetNumberOfDigitsFunction getNumberOfBitsForStabilityCheckObject = [](StabilityCheckObjects const&) -> unsigned int
{
    return 8U;
};
StabilityCheckSorter::GetDigitAtFunction getBitAtForStabilityCheckObject = [](StabilityCheckObject const& value, unsigned int const digitIndex) -> unsigned int
{
    return (value.getVisiblePart() >> digitIndex) & 1U;
};
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter(getNumberOfBitsForCharacter, getBitAtForCharacter);
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter(getNumberOfBitsForCharacter, getBitAtForCharacter);
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    SmallIntegerSorter sorter(getNumberOfBitsForInteger, getBitAtForSmallInteger);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

TEST(RadixSorterUsingCountingSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)
{
    StabilityCheckSorter sorter(getNumberOfBitsForStabilityCheckObject, getBitAtForStabilityCheckObject);
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}

}

}
