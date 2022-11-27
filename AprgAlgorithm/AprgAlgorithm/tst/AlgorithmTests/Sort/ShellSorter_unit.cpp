#include <Algorithm/Sort/ShellSorter.hpp>
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
using CharacterSorter = ShellSorter<Characters>;
using IntegerSorter = ShellSorter<Integers>;
using StabilityCheckSorter = ShellSorter<StabilityCheckObjects>;
}

TEST(ShellSorterTest, SortWorksOnCharactersUsingExample1){
    testSortUsingExample1WithCharacters<CharacterSorter, Characters>();
}
TEST(ShellSorterTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>();
}

TEST(ShellSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>();
}

TEST(ShellSorterTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1)
{
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>();
}

}

}