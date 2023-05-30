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
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    EXPECT_EQ(0, getPivotIndex(valuesToTest, 0, valuesToTest.size() - 1, PivotType::LowestIndex));
    EXPECT_EQ(10, getPivotIndex(valuesToTest, 0, valuesToTest.size() - 1, PivotType::HighestIndex));
    EXPECT_EQ(0, getPivotIndex(valuesToTest, 0, valuesToTest.size() - 1, PivotType::MedianOfLowMidHighIndexes));
    EXPECT_EQ(2, getPivotIndex(valuesToTest, 0, valuesToTest.size() - 1, PivotType::MedianNinther));
    EXPECT_EQ(7, getPivotIndex(valuesToTest, 0, valuesToTest.size() - 1, PivotType::MedianOfMedians));
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIndexWorksWithLowestIndex) {
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIndex =
        partitionAndGetPartitionIndex(valuesToTest, 0, valuesToTest.size() - 1, PivotType::LowestIndex);

    Characters valuesToExpect{'P', 'O', 'R', 'E', 'E', 'L', 'A', 'M', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
    EXPECT_EQ(8, partitionIndex);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIndexWorksWithHighestIndex) {
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIndex =
        partitionAndGetPartitionIndex(valuesToTest, 0, valuesToTest.size() - 1, PivotType::HighestIndex);

    Characters valuesToExpect{'E', 'A', 'E', 'T', 'R', 'X', 'O', 'M', 'P', 'L', 'S'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
    EXPECT_EQ(2, partitionIndex);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIndexWorksWithMedianOfLowMidHighIndexes) {
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIndex =
        partitionAndGetPartitionIndex(valuesToTest, 0, valuesToTest.size() - 1, PivotType::MedianOfLowMidHighIndexes);

    Characters valuesToExpect{'P', 'O', 'R', 'E', 'E', 'L', 'A', 'M', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
    EXPECT_EQ(8, partitionIndex);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIndexWorksWithMedianNinther) {
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIndex =
        partitionAndGetPartitionIndex(valuesToTest, 0, valuesToTest.size() - 1, PivotType::MedianNinther);

    Characters valuesToExpect{'M', 'O', 'E', 'L', 'E', 'P', 'A', 'R', 'X', 'T', 'S'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
    EXPECT_EQ(7, partitionIndex);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIndexWorksWithMedianOfMedians) {
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIndex =
        partitionAndGetPartitionIndex(valuesToTest, 0, valuesToTest.size() - 1, PivotType::MedianOfMedians);

    Characters valuesToExpect{'E', 'E', 'L', 'A', 'M', 'X', 'T', 'S', 'P', 'R', 'O'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
    EXPECT_EQ(4, partitionIndex);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIndexUsingLomutoWorks) {
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIndex =
        partitionAndGetPartitionIndexUsingLomuto(valuesToTest, 0, valuesToTest.size() - 1, PivotType::MedianOfMedians);

    Characters valuesToExpect{'E', 'E', 'A', 'L', 'M', 'X', 'R', 'S', 'P', 'T', 'O'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
    EXPECT_EQ(4, partitionIndex);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIteratorInTwoDirectionsWorks) {
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIterator =
        partitionAndGetPartitionIteratorInTwoDirections<Characters>(valuesToTest.begin(), prev(valuesToTest.end()));

    Characters valuesToExpect{'P', 'O', 'R', 'E', 'E', 'L', 'A', 'M', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
    EXPECT_EQ('S', *partitionIterator);
}

TEST(QuickSorterUtilitiesTest, PartitionAndGetPartitionIteratorInOneDirectionWorks) {
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    auto partitionIterator =
        partitionAndGetPartitionIteratorInOneDirection<Characters>(valuesToTest.begin(), valuesToTest.end());

    Characters valuesToExpect{'E', 'O', 'R', 'E', 'A', 'M', 'P', 'L', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
    EXPECT_EQ('S', *partitionIterator);
}

}  // namespace algorithm

}  // namespace alba
