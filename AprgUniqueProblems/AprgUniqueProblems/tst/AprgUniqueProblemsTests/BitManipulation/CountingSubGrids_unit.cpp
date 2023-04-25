#include <AprgUniqueProblems/BitManipulation/CountingSubGrids.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(CountingSubGridsTest, CountSubGridsWithAllBlackCornersWorksWithExample1) {
    CountingSubGrids::BitGrid bitGrid(
        5U, 5U, {false, true,  false, false, true, false, true, true,  false, false, true,  false, false,
                 false, false, false, true,  true, false, true, false, false, false, false, false});
    CountingSubGrids countingSubGrids(bitGrid);

    EXPECT_EQ(2U, countingSubGrids.countSubGridsWithAllBlackCorners());
}

}  // namespace alba
