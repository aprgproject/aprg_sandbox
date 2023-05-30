#include <Algorithm/Search/SingleValue/FibonacciSearch/FibonacciSearch.hpp>
#include <AlgorithmTests/Search/SingleValue/Utilities/CommonTestsWithSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using SearchForTest = FibonacciSearch<ValuesForTest>;
}  // namespace

TEST(FibonacciSearchTest, GetIndexOfValueWorksAndDoesNotCrashWhenEmpty) {
    testGetIndexOfValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(FibonacciSearchTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereIsOneValue) {
    testGetIndexOfValueWhenValueIsNotFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(FibonacciSearchTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereIsOneValue) {
    testGetIndexOfValueWhenValueIsFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(FibonacciSearchTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreDuplicateValues) {
    testGetIndexOfValueWhenValueIsNotFoundWithDuplicatesWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(FibonacciSearchTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreDuplicateValues) {
    ValuesForTest sortedValues{13, 13, 14, 33, 33, 33, 53, 53, 53, 72, 72, 72, 72, 96, 96};
    SearchForTest search(sortedValues);

    EXPECT_EQ(3, search.getIndexOfValue(33));
}

TEST(FibonacciSearchTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWhenValueIsNotFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(FibonacciSearchTest, GetIndexOfValueWorksWhenValueIsLessThanTheLowestValueAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWhenValueIsLessThanTheLowestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(FibonacciSearchTest, GetIndexOfValueWorksWhenValueIsLessThanTheHighestValueAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWhenValueIsGreaterThanTheHighestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(FibonacciSearchTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWhenValueIsFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

}  // namespace algorithm

}  // namespace alba
