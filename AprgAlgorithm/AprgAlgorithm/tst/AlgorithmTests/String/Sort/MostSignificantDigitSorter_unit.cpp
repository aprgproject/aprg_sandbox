#include <Algorithm/String/Sort/MostSignificantDigitSorter.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

TEST(MostSignificantDigitSorterTest, SortByMostSignificantDigitWorksWithDigitThatExistsInAllStrings)
{
    MostSignificantDigitSorter<unsigned int> sorter;
    stringHelper::strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortByMostSignificantDigit(stringsToTest, 2U, 5U, 1U);

    stringHelper::strings expectedStrings{"spongebob", "patrick", "sandy", "squidward", "mr. crabs", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(MostSignificantDigitSorterTest, SortByMostSignificantDigitWorksWithDigitThatExistsInSomeOfTheStrings)
{
    MostSignificantDigitSorter<unsigned int> sorter;
    stringHelper::strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortByMostSignificantDigit(stringsToTest, 2U, 5U, 6U);

    stringHelper::strings expectedStrings{"spongebob", "patrick", "sandy", "mr. crabs", "squidward", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(MostSignificantDigitSorterTest, SortByMostSignificantDigitWorksWithDigitThatDoesNotExistInOfTheStrings)
{
    MostSignificantDigitSorter<unsigned int> sorter;
    stringHelper::strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortByMostSignificantDigit(stringsToTest, 2U, 5U, 9U);

    stringHelper::strings expectedStrings{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(MostSignificantDigitSorterTest, SortByMostSignificantDigitWorks)
{
    MostSignificantDigitSorter<unsigned int> sorter;
    stringHelper::strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortByMostSignificantDigit(stringsToTest);

    stringHelper::strings expectedStrings{"larry", "mr. crabs", "ms. puff", "patrick", "pearl", "plankton", "sandy", "spongebob", "squidward"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

}

}
