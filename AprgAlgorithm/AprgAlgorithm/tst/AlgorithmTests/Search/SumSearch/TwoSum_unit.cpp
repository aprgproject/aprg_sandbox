#include <Algorithm/Search/SumSearch/TwoSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValueForTest = unsigned int;
using SumSearch = TwoSum<ValueForTest>;
using ValuesForTest = SumSearch::Values;
using ValuesPairForTest = SumSearch::ValuesPair;
}

TEST(TwoSumTest, GetTwoValuesWithSumWorksOnExample1)
{
    SumSearch search({10U, 9U, 9U, 7U, 1U, 4U, 5U, 6U});

    ValuesPairForTest expectedPair{5U, 7U};
    EXPECT_EQ(expectedPair, search.getTwoValuesWithSum(12));
}

}

}
