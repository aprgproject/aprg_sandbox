#include <Algorithm/String/Sorter/LeastSignificantDigitSorter.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

TEST(LeastSignificantDigitSorterTest, SortByLeastSignificantDigitWorksWithDigitThatExistsInAllStrings)
{
    LeastSignificantDigitSorter<unsigned int> sorter;
    stringHelper::strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortByLeastSignificantDigit(stringsToTest, 1U);

    stringHelper::strings expectedStrings{"patrick", "sandy", "larry", "pearl", "plankton", "spongebob", "squidward", "mr. crabs", "ms. puff"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(LeastSignificantDigitSorterTest, SortByLeastSignificantDigitWorksWithDigitThatExistsInSomeOfTheStrings)
{
    LeastSignificantDigitSorter<unsigned int> sorter;
    stringHelper::strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortByLeastSignificantDigit(stringsToTest, 6U);

    stringHelper::strings expectedStrings{"sandy", "pearl", "larry", "mr. crabs", "squidward", "spongebob", "ms. puff", "patrick", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(LeastSignificantDigitSorterTest, SortByLeastSignificantDigitWorksWithDigitThatDoesNotExistInOfTheStrings)
{
    LeastSignificantDigitSorter<unsigned int> sorter;
    stringHelper::strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortByLeastSignificantDigit(stringsToTest, 9U);

    stringHelper::strings expectedStrings{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

TEST(LeastSignificantDigitSorterTest, SortByLeastSignificantDigitsWorks)
{
    LeastSignificantDigitSorter<unsigned int> sorter;
    stringHelper::strings stringsToTest{"spongebob", "patrick", "mr. crabs", "squidward", "sandy", "ms. puff", "pearl", "larry", "plankton"};

    sorter.sortByLeastSignificantDigits(stringsToTest, 0U, 9U);

    stringHelper::strings expectedStrings{"larry", "mr. crabs", "ms. puff", "patrick", "pearl", "plankton", "sandy", "spongebob", "squidward"};
    EXPECT_EQ(expectedStrings, stringsToTest);
}

}

}
