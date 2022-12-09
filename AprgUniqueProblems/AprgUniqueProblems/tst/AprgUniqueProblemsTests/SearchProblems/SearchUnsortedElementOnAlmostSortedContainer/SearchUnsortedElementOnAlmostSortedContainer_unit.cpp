#include <AprgUniqueProblems/SearchProblems/SearchUnsortedElementOnAlmostSortedContainer/SearchUnsortedElementOnAlmostSortedContainer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using SearchForTest = SearchUnsortedElementOnAlmostSortedContainer<ValuesForTest>;
constexpr SearchForTest::Index INVALID_INDEX = SearchForTest::INVALID_INDEX;

}

TEST(SearchUnsortedElementOnAlmostSortedContainerTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    ValuesForTest emptyValues;
    SearchForTest search(emptyValues);

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(33));
}

TEST(SearchUnsortedElementOnAlmostSortedContainerTest, GetIndexOfNearestValueWorksWhenThereIsOneValue)
{
    ValuesForTest oneValue{10};
    SearchForTest search(oneValue);

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(33));
}

TEST(SearchUnsortedElementOnAlmostSortedContainerTest, GetIndexOfNearestValueWorksWhenThereAreDuplicateValues)
{
    ValuesForTest duplicateValues{0, 0, 0, 0, 0};
    SearchForTest search(duplicateValues);

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(33));
}

TEST(SearchUnsortedElementOnAlmostSortedContainerTest, GetIndexOfNearestValueWorksWhenThereAreMultipleValues)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 43, 33, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(5U, search.getIndexOfValue(33));
}

TEST(SearchUnsortedElementOnAlmostSortedContainerTest, GetIndexOfNearestValueWorksWithIndexesWhenDistanceFromLowerToHigherIsOne)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 43, 33, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(5U, search.getIndexOfValue(5U, 6U, 33U));
}

TEST(SearchUnsortedElementOnAlmostSortedContainerTest, GetIndexOfNearestValueWorksWithIndexesWhenDistanceFromLowerToHigherIsTwo)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 43, 33, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(5U, search.getIndexOfValue(3U, 5U, 33U));
}

TEST(SearchUnsortedElementOnAlmostSortedContainerTest, GetIndexOfNearestValueWorksWithndexesWhenDistanceFromLowerToHigherIsOdd)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 43, 33, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(5U, search.getIndexOfValue(1U, 8U, 33U));
}

}

}
