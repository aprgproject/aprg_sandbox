#include <Sorter/InsertionSorter.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

TEST(InsertionSorterTest, SortWorks)
{
    using Values=vector<char>;
    Values valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    InsertionSorter<Values> sorter;

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

}
