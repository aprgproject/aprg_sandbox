#include <Algorithm/String/Sorter/StringQuickSorterWith3WayPartitioning.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

TEST(StringQuickSorterWith3WayPartitioningTest, SortByMostSignificantDigitWorksWithDigitThatExistsInAllStrings)
{
    StringQuickSorterWith3WayPartitioning sorter;
    stringHelper::strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sort(stringsToTest, 2U, 5U, 1U);

    stringHelper::strings expectedStrings{"spongebob", "patrick", "sandy", "squidward", "mr. crabs", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(StringQuickSorterWith3WayPartitioningTest, SortByMostSignificantDigitWorksWithDigitThatExistsInSomeOfTheStrings)
{
    StringQuickSorterWith3WayPartitioning sorter;
    stringHelper::strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sort(stringsToTest, 2U, 5U, 6U);

    stringHelper::strings expectedStrings{"spongebob", "patrick", "sandy", "mr. crabs", "squidward", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(StringQuickSorterWith3WayPartitioningTest, SortByMostSignificantDigitWorksWithDigitThatDoesNotExistInOfTheStrings)
{
    StringQuickSorterWith3WayPartitioning sorter;
    stringHelper::strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sort(stringsToTest, 2U, 5U, 9U);

    stringHelper::strings expectedStrings{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(StringQuickSorterWith3WayPartitioningTest, SortByMostSignificantDigitWorks)
{
    StringQuickSorterWith3WayPartitioning sorter;
    stringHelper::strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sort(stringsToTest);

    stringHelper::strings expectedStrings{"larry", "mr. crabs", "ms. puff", "patrick", "pearl", "plankton", "sandy", "spongebob", "squidward"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

}

}
