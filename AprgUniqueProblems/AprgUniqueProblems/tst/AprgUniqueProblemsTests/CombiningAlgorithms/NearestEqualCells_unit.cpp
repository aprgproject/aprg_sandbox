#include <AprgUniqueProblems/CombiningAlgorithms/NearestEqualCells.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using ValueMatrix = NearestEqualCells::ValueMatrix;
using CoordinatePair = NearestEqualCells::CoordinatePair;
}  // namespace

TEST(NearestEqualCellsTest, GetNearestEqualPairWorks) {
    ValueMatrix valueMatrix(4U, 4U, {1U, 6U, 2U, 1U, 3U, 5U, 7U, 5U, 2U, 4U, 1U, 6U, 1U, 3U, 2U, 4U});
    NearestEqualCells nearestEqualCells(valueMatrix);

    CoordinatePair expectedCoordinatePair{{2U, 0U}, {2U, 3U}};
    EXPECT_EQ(expectedCoordinatePair, nearestEqualCells.getNearestEqualPair(2U));
}

TEST(NearestEqualCellsTest, GetNearestEqualPairByCheckingAllPairsWorks) {
    ValueMatrix valueMatrix(4U, 4U, {1U, 6U, 2U, 1U, 3U, 5U, 7U, 5U, 2U, 4U, 1U, 6U, 1U, 3U, 2U, 4U});
    NearestEqualCells nearestEqualCells(valueMatrix);

    CoordinatePair expectedCoordinatePair{{2U, 0U}, {2U, 3U}};
    EXPECT_EQ(expectedCoordinatePair, nearestEqualCells.getNearestEqualPairByCheckingAllPairs(2U));
}

TEST(NearestEqualCellsTest, GetNearestEqualPairUsingBfsWorks) {
    ValueMatrix valueMatrix(4U, 4U, {1U, 6U, 2U, 1U, 3U, 5U, 7U, 5U, 2U, 4U, 1U, 6U, 1U, 3U, 2U, 4U});
    NearestEqualCells nearestEqualCells(valueMatrix);

    CoordinatePair expectedCoordinatePair{{0U, 2U}, {2U, 3U}};
    EXPECT_EQ(expectedCoordinatePair, nearestEqualCells.getNearestEqualPairUsingBfs(2U));
}

}  // namespace alba
