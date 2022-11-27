#include <Algorithm/Sort/CountingSorter/CountingSorterUsingCountPerValue.hpp>
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
constexpr unsigned int MAX_NUMBER_OF_CHARS=256U;
constexpr unsigned int MAX_NUMBER_OF_SMALL_INTS=21U;
using Characters = vector<char>;
using Integers = vector<int>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharacterSorter = CountingSorterUsingCountPerValue<Characters, MAX_NUMBER_OF_CHARS>;
using SmallIntegerSorter = CountingSorterUsingCountPerValue<Integers, MAX_NUMBER_OF_SMALL_INTS>;
using StabilityCheckSorter = CountingSorterUsingCountPerValue<StabilityCheckObjects, MAX_NUMBER_OF_CHARS>;

CharacterSorter::ValueToIndexableValueFunction characterToIndexableValueFunction = [](char const& value) -> unsigned int
{
    return value & 0xFFU; // already converts to unsigned integer
};
CharacterSorter::IndexableValueToValueFunction indexableValueToCharacterFunction = [](unsigned int const indexableValue) -> char
{
    return static_cast<char>(indexableValue & 0xFFU);
};

SmallIntegerSorter::ValueToIndexableValueFunction smallIntToIndexableValueFunction = [](int const& value) -> unsigned int
{
    // Input: {-5, -10, 0, -3, 8, 5, -1, 10}
    return static_cast<unsigned int>(10+value);
};
SmallIntegerSorter::IndexableValueToValueFunction indexableValueToSmallIntFunction = [](unsigned int const indexableValue) -> int
{
    // Input: {-5, -10, 0, -3, 8, 5, -1, 10}
    return static_cast<int>(indexableValue)-10;
};

StabilityCheckSorter::ValueToIndexableValueFunction stabilityCheckObjectToIndexableValueFunction = [](StabilityCheckObject const& value) -> unsigned int
{
    return value.getVisiblePart() & 0xFFU; // there is some splicing here
};
StabilityCheckSorter::IndexableValueToValueFunction indexableValueToStabilityCheckObjectFunction = [](unsigned int const indexableValue) -> StabilityCheckObject
{
    return StabilityCheckObject(indexableValue & 0xFFU, 0U);
};

}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter(characterToIndexableValueFunction, indexableValueToCharacterFunction);
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter(characterToIndexableValueFunction, indexableValueToCharacterFunction);
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    SmallIntegerSorter sorter(smallIntToIndexableValueFunction, indexableValueToSmallIntFunction);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1)
{
    StabilityCheckSorter sorter(stabilityCheckObjectToIndexableValueFunction, indexableValueToStabilityCheckObjectFunction);
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}

}

}
