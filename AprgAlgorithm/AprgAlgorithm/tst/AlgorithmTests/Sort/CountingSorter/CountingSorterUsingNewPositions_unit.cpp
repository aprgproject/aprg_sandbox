#include <Algorithm/Sort/CountingSorter/CountingSorterUsingNewPositions.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>

#include <gtest/gtest.h>
using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<char>;
using ArrayOfCountPerCharacter = array<unsigned int, 256>;
using SorterForTest = CountingSorterUsingNewPositions<ValuesForTest, ArrayOfCountPerCharacter>;
}

TEST(CountingSorterUsingNewPositionsTest, SortWorksOnCharactersUsingExample1)
{
    testSortUsingExample1WithCharacters<SorterForTest, ValuesForTest>();
}

TEST(CountingSorterUsingNewPositionsTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<SorterForTest, ValuesForTest>();
}
}

}
