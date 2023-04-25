#include <Algorithm/Sort/BucketSorter/BucketSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

#include <list>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Characters = vector<char>;
using ListOfCharacters = list<char>;
using Integers = vector<int>;
using Doubles = vector<double>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = BucketSorter<Characters, 10U>;
using ListOfCharactersSorter = BucketSorter<ListOfCharacters, 10U>;
using IntegersSorter = BucketSorter<Integers, 10U>;
using DoublesSorter = BucketSorter<Doubles, 10U>;
using StringsSorter = BucketSorter<Strings, 10U>;
using StabilityCheckObjectsSorter = BucketSorter<StabilityCheckObjects, 10U>;
}  // namespace

TEST(BucketSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter('A', 'Z');
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(BucketSorterTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter('A', 'Z');
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(BucketSorterTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter('A', 'Z');
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(BucketSorterTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter('A', 'Z');
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(BucketSorterTest, SortWorksOnListOfCharactersUsingExample1) {
    ListOfCharactersSorter sorter('A', 'Z');
    testSortUsingExample1WithCharacters<ListOfCharactersSorter, ListOfCharacters>(sorter);
}

TEST(BucketSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    // Input is {-5, -10, 0, -3, 8, 5, -1, 10}

    IntegersSorter sorter(-10, 10);
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(BucketSorterTest, SortWorksOnDoublesUsingExample1) {
    // Input is {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};

    DoublesSorter sorter(0, 1);
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

// CANNOT SORT STRINGS

TEST(BucketSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)  // NOT REALLY STABLE
{
    // Not really stable but samples are too few

    StabilityCheckObjectsSorter sorter(StabilityCheckObject('A', 0U), StabilityCheckObject('Z', 0U));
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

}  // namespace algorithm

}  // namespace alba
