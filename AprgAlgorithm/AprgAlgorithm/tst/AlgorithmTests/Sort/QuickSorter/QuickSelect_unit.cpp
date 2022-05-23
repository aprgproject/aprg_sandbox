#include <Algorithm/Sort/QuickSorter/QuickSelect.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<char>;
using SelectForTest = QuickSelect<ValuesForTest>;
}

TEST(QuickSelectTest, DoNthElementWorksOnCharactersUsingExample1)
{
    SelectForTest select;
    ValuesForTest valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    select.doNthElement(valuesToTest, 5);

    ValuesForTest valuesToExpect{'A', 'L', 'M', 'E', 'E', 'O', 'P', 'R', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(QuickSelectTest, GetNthSelectWorksOnCharactersUsingExample1)
{
    SelectForTest select;
    ValuesForTest valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    EXPECT_EQ('O', select.getNthSelect(valuesToTest, 5));
}

}

}
