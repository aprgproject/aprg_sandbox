#include <Algorithm/Sort/BucketSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

#include <limits>

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
using CharacterSorter = BucketSorter<Characters, 10U>;
using IntegerSorter = BucketSorter<Integers, 10U>;
using DoubleSorter = BucketSorter<Doubles, 10U>;
using StringSorter = BucketSorter<Strings, 10U>;
using StabilityCheckSorter = BucketSorter<StabilityCheckObjects, 10U>;
}

TEST(BucketSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter('A', 'Z');
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(BucketSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter('A', 'Z');
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(BucketSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    // Input is {-5, -10, 0, -3, 8, 5, -1, 10}

    IntegerSorter sorter(-10, 10);
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>(sorter);
}

TEST(BucketSorterTest, SortWorksOnDoublesUsingExample1)
{
    // Input is {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};

    DoubleSorter sorter(0, 1);
    testSortUsingExample1WithDoubleValues<DoubleSorter, Doubles>(sorter);
}

// CANNOT SORT STRINGS

TEST(BucketSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) // NOT REALLY STABLE
{
    // Not really stable but samples are too few

    StabilityCheckSorter sorter(StabilityCheckObject('A', 0U), StabilityCheckObject('Z', 0U));
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}

}

}
