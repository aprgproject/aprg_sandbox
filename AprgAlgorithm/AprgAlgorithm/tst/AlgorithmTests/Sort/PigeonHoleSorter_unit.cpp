#include <Algorithm/Sort/PigeonholeSorter.hpp>
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
using Doubles = vector<double>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharacterSorter = PigeonholeSorter<Characters>;
using IntegerSorter = PigeonholeSorter<Integers>;
using DoubleSorter = PigeonholeSorter<Doubles>;
using StringSorter = PigeonholeSorter<Strings>;
using StabilityCheckSorter = PigeonholeSorter<StabilityCheckObjects>;
}

TEST(PigeonholeSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter;
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(PigeonholeSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter;
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(PigeonholeSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegerSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>(sorter);
}

// CANNOT SORT DOUBLE VALUES

// CANNOT SORT STRINGS

TEST(PigeonholeSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) // STABLE
{
    StabilityCheckSorter sorter;
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}

}

}
