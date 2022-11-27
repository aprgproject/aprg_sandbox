#include <Algorithm/Sort/QuickSorter/QuickSorterWith3WayPartitioning.hpp>
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
using CharacterSorter = QuickSorterWith3WayPartitioning<Characters>;
using IntegerSorter = QuickSorterWith3WayPartitioning<Integers>;
using StabilityCheckSorter = QuickSorterWith3WayPartitioning<StabilityCheckObjects>;
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1){
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>();
}
TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>();
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>();
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1)
{
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>();
}

}

}