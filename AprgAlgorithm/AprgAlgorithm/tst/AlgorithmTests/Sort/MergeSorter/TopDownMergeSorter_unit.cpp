#include <Algorithm/Sort/MergeSorter/TopDownMergeSorter.hpp>
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
using CharacterSorter = TopDownMergeSorter<Characters>;
using IntegerSorter = TopDownMergeSorter<Integers>;
using StabilityCheckSorter = TopDownMergeSorter<StabilityCheckObjects>;
}

TEST(TopDownMergeSorterTest, SortWorksOnCharactersUsingExample1){
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>();
}
TEST(TopDownMergeSorterTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>();
}

TEST(TopDownMergeSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>();
}

TEST(TopDownMergeSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)
{
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>();
}

}

}