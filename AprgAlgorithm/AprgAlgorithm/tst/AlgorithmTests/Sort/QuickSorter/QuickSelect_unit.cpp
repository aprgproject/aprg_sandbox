#include <Algorithm/Sort/QuickSorter/QuickSelect.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Characters = vector<char>;
using Integers = vector<int>;
using CharacterSelect = QuickSelect<Characters>;
using IntegerSelect = QuickSelect<Integers>;
}

TEST(QuickSelectTest, DoNthElementWorksOnCharactersUsingExample1)
{
    CharacterSelect select;
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    select.doNthElement(valuesToTest, 5);

    Characters valuesToExpect{'A', 'L', 'M', 'E', 'E', 'O', 'P', 'R', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(QuickSelectTest, GetNthSelectWorksOnCharactersUsingExample1)
{
    CharacterSelect select;
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    EXPECT_EQ('O', select.getNthSelect(valuesToTest, 5));
}

TEST(QuickSelectTest, GetNthSelectWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegerSelect select;
    Integers valuesToTest{-5, -10, 0, -3, 8, 5, -1, 10};

    EXPECT_EQ(-1, select.getNthSelect(valuesToTest, 3));
}

}

}
