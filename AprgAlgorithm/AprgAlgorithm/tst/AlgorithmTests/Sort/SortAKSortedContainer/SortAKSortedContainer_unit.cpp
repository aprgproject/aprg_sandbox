#include <Algorithm/Sort/SortAKSortedContainer/SortAKSortedContainer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Characters = vector<char>;
using CharactersSorter = SortAKSortedContainer<Characters>;
}

TEST(SortAKSortedContainerTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample)
{
    CharactersSorter sorter;
    Characters emptyContainer;

    sorter.sort(3U, emptyContainer);

    EXPECT_TRUE(emptyContainer.empty());
}

TEST(SortAKSortedContainerTest, SortWorksOnCharactersUsingOneValueExample)
{
    CharactersSorter sorter;
    Characters valuesToTest{'E'};

    sorter.sort(3U, valuesToTest);

    Characters valuesToExpect{'E'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(SortAKSortedContainerTest, SortWorksOnCharactersUsingExample1)
{
    CharactersSorter sorter;
    Characters valuesToTest{'F', 'E', 'C', 'B', 'H', 'J', 'I'};

    sorter.sort(3U, valuesToTest);

    Characters valuesToExpect{'B', 'C', 'E', 'F', 'H', 'I', 'J'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(SortAKSortedContainerTest, SortWorksOnCharactersUsingExample2)
{
    CharactersSorter sorter;
    Characters valuesToTest{'J', 'I', 'H', 'G', 'D', 'M', 'L', 'K'};

    sorter.sort(4U, valuesToTest);

    Characters valuesToExpect{'D', 'G', 'H', 'I', 'J', 'K', 'L', 'M'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

}

}
