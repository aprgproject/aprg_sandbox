#include <AprgUniqueProblems/SearchProblems/BinarySearchProblems/BinarySearchProblems.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValueForTest = unsigned int;
using ValuesForTest = vector<ValueForTest>;
using QueryForTest = BinarySearchProblems<ValuesForTest>;
}  // namespace

TEST(BinarySearchProblemsTest, GetNearestFloorWorks) {
    ValuesForTest valuesForTest{1, 2, 3, 5, 6, 8, 9, 10};
    QueryForTest query;

    EXPECT_EQ(6U, query.getNearestFloor(valuesForTest, 7U));
}

TEST(BinarySearchProblemsTest, GetNearestCeilWorks) {
    ValuesForTest valuesForTest{1, 2, 3, 5, 6, 8, 9, 10};
    QueryForTest query;

    EXPECT_EQ(8U, query.getNearestCeil(valuesForTest, 7U));
}

TEST(BinarySearchProblemsTest, GetNumberOfDuplicatesWorks) {
    ValuesForTest valuesForTest{1, 2, 3, 5, 6, 7, 7, 7, 8, 9, 10};
    QueryForTest query;

    EXPECT_EQ(3U, query.getNumberOfDuplicates(valuesForTest, 7U));
}

TEST(BinarySearchProblemsTest, GetPositionOfRotationWorks) {
    ValuesForTest valuesForTest{6, 7, 8, 9, 10, 1, 2, 3, 4, 5};
    QueryForTest query;

    EXPECT_EQ(5U, query.getPositionOfRotation(valuesForTest));
}

}  // namespace algorithm

}  // namespace alba
