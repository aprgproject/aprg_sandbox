#include <Algorithm/Sort/MergeSorter/BottomUpMergeSorter.hpp>
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
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharacterSorter = BottomUpMergeSorter<Characters>;
using IntegerSorter = BottomUpMergeSorter<Integers>;
using StabilityCheckSorter = BottomUpMergeSorter<StabilityCheckObjects>;
}

TEST(BottomUpMergeSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter;
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(BottomUpMergeSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter;
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(BottomUpMergeSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegerSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>(sorter);
}

TEST(BottomUpMergeSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)
{
    StabilityCheckSorter sorter;
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}

}

}
