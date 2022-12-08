#include <AprgUniqueProblems/SortProblems/SortAKSortedContainer/SortAKSortedContainer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Integers = vector<int>;
using IntegersSorter = SortAKSortedContainer<Integers>;
}

TEST(SortAKSortedContainerTest, SortWorksOnIntegersAndDoesNotCrashUsingEmptyExample)
{
    IntegersSorter sorter;
    Integers emptyContainer;

    sorter.sort(3U, emptyContainer);

    EXPECT_TRUE(emptyContainer.empty());
}

TEST(SortAKSortedContainerTest, SortWorksOnIntegersUsingOneValueExample)
{
    IntegersSorter sorter;
    Integers valuesToTest{5};

    sorter.sort(3U, valuesToTest);

    Integers valuesToExpect{5};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(SortAKSortedContainerTest, SortWorksOnIntegersUsingExample1)
{
    IntegersSorter sorter;
    Integers valuesToTest{6, 5, 3, 2, 8, 10, 9};

    sorter.sort(3U, valuesToTest);

    Integers valuesToExpect{2, 3, 5, 6, 8, 9, 10};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(SortAKSortedContainerTest, SortWorksOnIntegersUsingExample2)
{
    IntegersSorter sorter;
    Integers valuesToTest{10, 9, 8, 7, 4, 13, 12, 11};

    sorter.sort(4U, valuesToTest);

    Integers valuesToExpect{4, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

}

}
