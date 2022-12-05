#include <Algorithm/Sort/UniqueProblems/SortNNumbersInRangeFromZeroToNSquaredMinus1InLinearTime/SortNNumbersInRangeFromZeroToNSquaredMinus1InLinearTime.hpp>
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
using CharactersSorter = SortNNumbersInRangeFromZeroToNSquaredMinus1InLinearTime<Characters>;
using SmallIntegerSorter = SortNNumbersInRangeFromZeroToNSquaredMinus1InLinearTime<Integers>;
}

TEST(SortNNumbersInRangeFromZeroToNSquaredMinus1InLinearTimeTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample)
{
    CharactersSorter sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(SortNNumbersInRangeFromZeroToNSquaredMinus1InLinearTimeTest, SortWorksOnCharactersUsingOneValueExample)
{
    CharactersSorter sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(SortNNumbersInRangeFromZeroToNSquaredMinus1InLinearTimeTest, SortWorksOnCharactersUsingExample1)
{
    CharactersSorter sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(SortNNumbersInRangeFromZeroToNSquaredMinus1InLinearTimeTest, SortWorksOnCharactersUsingExample2)
{
    CharactersSorter sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST, actually it might be possible if we change indexes to iterators
// CANNOT SORT POSITIVE AND NEGATIVE VALUES
// CANNOT SORT DOUBLE VALUES
// CANNOT SORT STRINGS
// CANNOT SORT STABILITY OBJECTS

}

}
