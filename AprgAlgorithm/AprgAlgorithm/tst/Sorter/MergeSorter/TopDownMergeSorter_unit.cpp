#include <Sorter/MergeSorter/TopDownMergeSorter.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

TEST(TopDownMergeSorterTest, SortWorksOnExample1)
{
    using Values=vector<char>;
    Values valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    TopDownMergeSorter<Values> sorter;

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(TopDownMergeSorterTest, SortWorksOnExample2)
{
    using Values=vector<char>;
    Values valuesToTest{'M', 'E', 'R', 'G', 'E', 'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    TopDownMergeSorter<Values> sorter;

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'E', 'E', 'E', 'E', 'G', 'L', 'M', 'M', 'O', 'P', 'R', 'R', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

}
