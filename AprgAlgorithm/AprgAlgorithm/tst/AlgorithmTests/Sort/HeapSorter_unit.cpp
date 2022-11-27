#include <Algorithm/Sort/HeapSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>
#include <vector>

using namespace alba::algorithm::CommonTestsWithSorter;using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Characters = vector<char>;
using Integers = vector<int>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharacterSorter = HeapSorter<Characters>;
using IntegerSorter = HeapSorter<Integers>;
using StabilityCheckSorter = HeapSorter<StabilityCheckObjects>;
}

TEST(HeapSorterTest, SortWorksOnCharactersUsingExample1){
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>();
}
TEST(HeapSorterTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>();
}

TEST(HeapSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>();
}

TEST(HeapSorterTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1)
{
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>();
}

}

}