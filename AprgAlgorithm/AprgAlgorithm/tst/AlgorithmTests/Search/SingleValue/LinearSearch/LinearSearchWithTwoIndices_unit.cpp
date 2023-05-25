#include <Algorithm/Search/SingleValue/LinearSearch/LinearSearchWithTwoIndices.hpp>
#include <AlgorithmTests/Search/SingleValue/Utilities/CommonTestsWithSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using SearchForTest = LinearSearchWithTwoIndices<ValuesForTest>;
}  // namespace

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfValueWorksAndDoesNotCrashWhenEmpty) {
    testGetIndexOfValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereIsOneValue) {
    testGetIndexOfValueWhenValueIsNotFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereIsOneValue) {
    testGetIndexOfValueWhenValueIsFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreDuplicateValues) {
    testGetIndexOfValueWhenValueIsNotFoundWithDuplicatesWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreDuplicateValues) {
    ValuesForTest unsortedValues{96, 96, 53, 53, 53, 72, 72, 72, 72, 14, 33, 33, 33, 13, 13};
    SearchForTest search(unsortedValues);

    EXPECT_EQ(12, search.getIndexOfValue(33));
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWhenValueIsNotFoundWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWhenValueIsFoundWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfValueWithIndicesWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWithIndicesWhenValueIsNotFoundWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfValueWithIndicesWorksWhenValueIsFoundAndWhenThereAreMultipleValues) {
    testGetIndexOfValueWithIndicesWhenValueIsFoundWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

}  // namespace algorithm

}  // namespace alba
