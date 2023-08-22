#include <UniqueProblems/SearchProblems/CountOnesInASortedBinaryContainer.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
namespace algorithm {

namespace {
using ValuesForTest = vector<bool>;
using QueryForTest = CountOnesInASortedBinaryContainer<ValuesForTest>;
}  // namespace

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnEmpty) {
    ValuesForTest valuesForTest;
    QueryForTest query;

    EXPECT_EQ(0, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnOneValue) {
    ValuesForTest valuesForTest{true};
    QueryForTest query;

    EXPECT_EQ(1, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnWhenAllZeroes) {
    ValuesForTest valuesForTest{false, false, false, false, false, false, false};
    QueryForTest query;

    EXPECT_EQ(0, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnWhenAllOnes) {
    ValuesForTest valuesForTest{true, true, true, true, true, true, true};
    QueryForTest query;

    EXPECT_EQ(7, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnExample1) {
    ValuesForTest valuesForTest{false, false, false, true, true, true, true};
    QueryForTest query;

    EXPECT_EQ(4, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

}  // namespace algorithm

}  // namespace alba
