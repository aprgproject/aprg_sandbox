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
constexpr unsigned int MAX_NUMBER_OF_CHARACTERS=256U;
constexpr unsigned int MAX_NUMBER_OF_SMALL_INTS=21U;
using Characters = vector<char>;
using Integers = vector<int>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = CountingSorterUsingNewPositions<Characters, MAX_NUMBER_OF_CHARACTERS>;
using SmallIntegerSorter = CountingSorterUsingNewPositions<Integers, MAX_NUMBER_OF_SMALL_INTS>;
using StabilityCheckObjectsSorter = CountingSorterUsingNewPositions<StabilityCheckObjects, MAX_NUMBER_OF_CHARACTERS>;

CharactersSorter::ValueToIndexableValueFunction characterToIndexableValueFunction = [](char const& value) -> unsigned int
{
    return value & 0xFFU; // already converts to unsigned integer
};

SmallIntegerSorter::ValueToIndexableValueFunction smallIntToIndexableValueFunction = [](int const& value) -> unsigned int
{
    // Input: {-5, -10, 0, -3, 8, 5, -1, 10}
    return static_cast<unsigned int>(10+value);
};

StabilityCheckObjectsSorter::ValueToIndexableValueFunction stabilityCheckObjectToIndexableValueFunction = [](StabilityCheckObject const& value) -> unsigned int
{
    return value.getVisiblePart() & 0xFFU; // there is some splicing here
};
}

TEST(CountingSorterUsingNewPositionsTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample)
{
    CharactersSorter sorter(characterToIndexableValueFunction);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CountingSorterUsingNewPositionsTest, SortWorksOnCharactersUsingOneValueExample)
{
    CharactersSorter sorter(characterToIndexableValueFunction);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CountingSorterUsingNewPositionsTest, SortWorksOnCharactersUsingExample1)
{
    CharactersSorter sorter(characterToIndexableValueFunction);    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(CountingSorterUsingNewPositionsTest, SortWorksOnCharactersUsingExample2){
    CharactersSorter sorter(characterToIndexableValueFunction);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST

TEST(CountingSorterUsingNewPositionsTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    SmallIntegerSorter sorter(smallIntToIndexableValueFunction);
    testSortUsingExample1WithPositiveAndNegativeIntegers<SmallIntegerSorter, Integers>(sorter);
}

// CANNOT SORT DOUBLE VALUES

// CANNOT SORT STRINGS

TEST(CountingSorterUsingNewPositionsTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) // STABLE
{
    StabilityCheckObjectsSorter sorter(stabilityCheckObjectToIndexableValueFunction);
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

}

}
