#include <Algorithm/Sort/CountingSorter/CountingSorterUsingCountPerValue.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>

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

using Characters = vector<char>;
using Integers = vector<int>;
using CharacterSorter = CountingSorterUsingCountPerValue<Characters, ArrayOfCountPerCharacter>;
using SmallIntegerSorter = CountingSorterUsingCountPerValue<Integers, ArrayOfCountPerSmallInteger>;
}

// index compression
template<>
unsigned int CharacterSorter::convertValueToIndexableValue(char const& value) const
{
    return value & 0xFFU; // already converts to unsigned integer
}

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


TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingExample1)
{
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>();
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>();
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>();
}

}

}
