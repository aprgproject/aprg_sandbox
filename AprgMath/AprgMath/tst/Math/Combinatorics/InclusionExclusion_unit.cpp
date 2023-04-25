#include <Math/Combinatorics/InclusionExclusion.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace math {

TEST(InclusionExclusionTest, GetUnionCountOfTwoSetsWorks) { EXPECT_EQ(16U, getUnionCountOfTwoSets(10U, 11U, 5U)); }

TEST(InclusionExclusionTest, GetIntersectionCountOfTwoSetsWorks) {
    EXPECT_EQ(5U, getIntersectionCountOfTwoSets(10U, 11U, 16U));
}

TEST(InclusionExclusionTest, GetUnionCountOfThreeSetsWorks) {
    EXPECT_EQ(18U, getUnionCountOfThreeSets(10U, 11U, 12U, 5U, 6U, 7U, 3U));
}

TEST(InclusionExclusionTest, GetIntersectionCountOfThreeSetsWorks) {
    EXPECT_EQ(3U, getIntersectionCountOfThreeSets(10U, 11U, 12U, 5U, 6U, 7U, 18U));
}

}  // namespace math

}  // namespace alba
