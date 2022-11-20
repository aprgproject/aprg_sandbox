#include <Algorithm/Sort/CountingSorter/CountingSorterUsingCountPerValue.hpp>
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
using SorterForTest = CountingSorterUsingCountPerValue<ValuesForTest, ArrayOfCountPerCharacter>;
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingExample1)
{
    testSortUsingExample1WithCharacters<SorterForTest, ValuesForTest>();
}

TEST(CountingSorterUsingCountPerValueTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<SorterForTest, ValuesForTest>();
}

}

}
