#include <Algorithm/Sort/QuickSorter/QuickSorterUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Characters = vector<char>;
using Integers = vector<int>;
}  // namespace

TEST(QuickSorterUtilitiesTest, GetPivotValueWorks) {
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    EXPECT_EQ(0, getPivotIndex(valuesToSort, 0, valuesToSort.size() - 1, PivotType::LowestIndex));
    EXPECT_EQ(10, getPivotIndex(valuesToSort, 0, valuesToSort.size() - 1, PivotType::HighestIndex));
    EXPECT_EQ(0, getPivotIndex(valuesToSort, 0, valuesToSort.size() - 1, PivotType::MedianOfLowMidHighIndexes));
    EXPECT_EQ(2, getPivotIndex(valuesToSort, 0, valuesToSort.size() - 1, PivotType::MedianNinther));
    EXPECT_EQ(7, getPivotIndex(valuesToSort, 0, valuesToSort.size() - 1, PivotType::MedianOfMedians));
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIndexWorksWithLowestIndex) {
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIndex =
        partitionAndGetPartitionIndex(valuesToSort, 0, valuesToSort.size() - 1, PivotType::LowestIndex);

    Characters valuesToExpect{'E', 'O', 'R', 'L', 'E', 'P', 'A', 'M', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
    EXPECT_EQ(8, partitionIndex);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIndexWorksWithHighestIndex) {
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIndex =
        partitionAndGetPartitionIndex(valuesToSort, 0, valuesToSort.size() - 1, PivotType::HighestIndex);

    Characters valuesToExpect{'A', 'E', 'E', 'T', 'O', 'X', 'R', 'M', 'P', 'L', 'S'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
    EXPECT_EQ(2, partitionIndex);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIndexWorksWithMedianOfLowMidHighIndexes) {
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIndex =
        partitionAndGetPartitionIndex(valuesToSort, 0, valuesToSort.size() - 1, PivotType::MedianOfLowMidHighIndexes);

    Characters valuesToExpect{'E', 'O', 'R', 'L', 'E', 'P', 'A', 'M', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
    EXPECT_EQ(8, partitionIndex);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIndexWorksWithMedianNinther) {
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIndex =
        partitionAndGetPartitionIndex(valuesToSort, 0, valuesToSort.size() - 1, PivotType::MedianNinther);

    Characters valuesToExpect{'E', 'O', 'L', 'P', 'E', 'M', 'A', 'R', 'T', 'S', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
    EXPECT_EQ(7, partitionIndex);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIndexWorksWithMedianOfMedians) {
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIndex =
        partitionAndGetPartitionIndex(valuesToSort, 0, valuesToSort.size() - 1, PivotType::MedianOfMedians);

    Characters valuesToExpect{'E', 'L', 'A', 'E', 'M', 'X', 'R', 'S', 'P', 'O', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
    EXPECT_EQ(4, partitionIndex);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIndexUsingLomutoWorks) {
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIndex =
        partitionAndGetPartitionIndexUsingLomuto(valuesToSort, 0, valuesToSort.size() - 1, PivotType::MedianOfMedians);

    Characters valuesToExpect{'E', 'A', 'E', 'L', 'M', 'X', 'O', 'R', 'P', 'T', 'S'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
    EXPECT_EQ(4, partitionIndex);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIteratorInTwoDirectionsWorks) {
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIterator =
        partitionAndGetPartitionIteratorInTwoDirections<Characters>(valuesToSort.begin(), prev(valuesToSort.end()));

    Characters valuesToExpect{'P', 'O', 'R', 'E', 'E', 'L', 'A', 'M', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
    EXPECT_EQ('S', *partitionIterator);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIteratorInOneDirectionWorks) {
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIterator =
        partitionAndGetPartitionIteratorInOneDirection<Characters>(valuesToSort.begin(), valuesToSort.end());

    Characters valuesToExpect{'E', 'O', 'R', 'E', 'A', 'M', 'P', 'L', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
    EXPECT_EQ('S', *partitionIterator);
}

}  // namespace algorithm

}  // namespace alba
