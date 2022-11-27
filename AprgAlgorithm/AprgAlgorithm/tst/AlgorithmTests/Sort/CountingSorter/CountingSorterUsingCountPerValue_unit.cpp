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
using ArrayOfCountPerCharacter = array<unsigned int, 256>;
using ArrayOfCountPerSmallInteger = array<unsigned int, 21>;
using ArrayOfCountPerStabilityCheckObject = array<unsigned int, 256>;

using Characters = vector<char>;
using Integers = vector<int>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharacterSorter = CountingSorterUsingCountPerValue<Characters, ArrayOfCountPerCharacter>;
using SmallIntegerSorter = CountingSorterUsingCountPerValue<Integers, ArrayOfCountPerSmallInteger>;
using StabilityCheckSorter = CountingSorterUsingCountPerValue<StabilityCheckObjects, ArrayOfCountPerStabilityCheckObject>;
}

// index compressiontemplate<>
unsigned int CharacterSorter::convertValueToIndexableValue(char const& value) const
{
    return value & 0xFFU; // already converts to unsigned integer}

template<>
char CharacterSorter::convertIndexableValueToValue(unsigned int const indexableValue) const
{
    return static_cast<char>(indexableValue & 0xFFU);
}

template<>
unsigned int SmallIntegerSorter::convertValueToIndexableValue(int const& value) const
{
    // Input: {-5, -10, 0, -3, 8, 5, -1, 10}
    return static_cast<unsigned int>(10+value);
}

template<>
int SmallIntegerSorter::convertIndexableValueToValue(unsigned int const indexableValue) const
{
    // Input: {-5, -10, 0, -3, 8, 5, -1, 10}
    return static_cast<int>(indexableValue)-10;
}

template<>
unsigned int StabilityCheckSorter::convertValueToIndexableValue(StabilityCheckObject const& value) const
{
    return value.getPartOfLessThan() & 0xFFU; // there is some splicing here
}

template<>
StabilityCheckObject StabilityCheckSorter::convertIndexableValueToValue(unsigned int const indexableValue) const
{
    return StabilityCheckObject(indexableValue & 0xFFU, 0U);
}


TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingExample1)
{
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>();}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>();}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>();
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1)
{
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>();
}

}

}