#include <Algorithm/Search/SingleValue/InterpolationSearch/InterpolationSearch.hpp>
#include <AlgorithmTests/Search/SingleValue/Utilities/CommonTestsWithSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<unsigned int>;
using SearchForTest = InterpolationSearch<ValuesForTest>;
}  // namespace

TEST(InterpolationSearchTest, GetIndexOfValueWorksAndDoesNotCrashWhenEmpty) {
    testGetIndexOfValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereIsOneValue) {
    testGetIndexOfValueWhenValueIsNotFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereIsOneValue) {
    testGetIndexOfValueWhenValueIsFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreDuplicateValues) {
    testGetIndexOfValueWhenValueIsNotFoundWithDuplicatesWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreDuplicateValues) {
    testGetIndexOfValueWhenValueIsFoundWithDuplicatesWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWhenValueIsNotFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfValueWorksWhenValueIsLessThanTheLowestValueAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWhenValueIsLessThanTheLowestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfValueWorksWhenValueIsLessThanTheHighestValueAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWhenValueIsGreaterThanTheHighestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWhenValueIsFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfValueWithIndicesWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWithIndicesWhenValueIsNotFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfValueWithIndicesWorksWhenValueIsFoundAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWithIndicesWhenValueIsFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

}  // namespace algorithm

}  // namespace alba
