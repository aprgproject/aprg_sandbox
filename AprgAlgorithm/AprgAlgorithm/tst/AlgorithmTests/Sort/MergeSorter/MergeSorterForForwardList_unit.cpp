#include <Algorithm/Sort/MergeSorter/MergeSorterForForwardList.hpp>
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
using Characters = forward_list<char>;
using Integers = forward_list<int>;
using Doubles = forward_list<double>;
using Strings = forward_list<string>;
using StabilityCheckObjects = forward_list<StabilityCheckObject>;
using CharactersSorter = MergeSorterForForwardList<char>;
using IntegersSorter = MergeSorterForForwardList<int>;
using DoublesSorter = MergeSorterForForwardList<double>;
using StringsSorter = MergeSorterForForwardList<string>;
using StabilityCheckObjectsSorter = MergeSorterForForwardList<StabilityCheckObject>;
}

TEST(MergeSorterForForwardListTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample)
{
    CharactersSorter sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(MergeSorterForForwardListTest, SortWorksOnCharactersUsingOneValueExample)
{
    CharactersSorter sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(MergeSorterForForwardListTest, SortWorksOnCharactersUsingExample1)
{
    CharactersSorter sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(MergeSorterForForwardListTest, SortWorksOnCharactersUsingExample2)
{
    CharactersSorter sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST

TEST(MergeSorterForForwardListTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegersSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(MergeSorterForForwardListTest, SortWorksOnDoublesUsingExample1)
{
    DoublesSorter sorter;
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(MergeSorterForForwardListTest, SortWorksOnStringsUsingExample1)
{
    StringsSorter sorter;
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(MergeSorterForForwardListTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) // STABLE
{
    StabilityCheckObjectsSorter sorter;
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

}

}
