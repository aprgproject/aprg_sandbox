#include <Algorithm/Sort/CountingSorter/CountingSorterUsingNewPositions.hpp>
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
using CharacterSorter = CountingSorterUsingNewPositions<Characters, ArrayOfCountPerCharacter>;
using SmallIntegerSorter = CountingSorterUsingNewPositions<Integers, ArrayOfCountPerSmallInteger>;
using StabilityCheckSorter = CountingSorterUsingNewPositions<StabilityCheckObjects, ArrayOfCountPerStabilityCheckObject>;

}

// index compressiontemplate<>
unsigned int CharacterSorter::convertValueToIndexableValue(char const& value) const
{
    return value & 0xFFU; // already converts to unsigned integer}

template<>
unsigned int SmallIntegerSorter::convertValueToIndexableValue(int const& value) const
{
    // Input: {-5, -10, 0, -3, 8, 5, -1, 10}
    return static_cast<unsigned int>(value+10);
}

template<>
unsigned int StabilityCheckSorter::convertValueToIndexableValue(StabilityCheckObject const& value) const
{
    return value.getPartOfLessThan() & 0xFFU; // there is some splicing here
}

TEST(CountingSorterUsingNewPositionsTest, SortWorksOnCharactersUsingExample1)
{
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>();}

TEST(CountingSorterUsingNewPositionsTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>();
}

TEST(CountingSorterUsingNewPositionsTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)
{
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>();
}

}
}