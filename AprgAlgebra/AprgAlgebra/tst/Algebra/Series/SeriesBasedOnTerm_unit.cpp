#include <Algebra/Series/SeriesBasedOnTerm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(SeriesBasedOnTermTest, ConstructionWorks)
{
    SeriesBasedOnTerm series(Term("x"), "x");
}

TEST(SeriesBasedOnTermTest, GetValueAtIndexWorks)
{
    SeriesBasedOnTerm series(Term("x"), "x");

    EXPECT_EQ(Term(-5), series.getValueAtIndex(-5));
    EXPECT_EQ(Term(Constant(0)), series.getValueAtIndex(0));
    EXPECT_EQ(Term(5), series.getValueAtIndex(5));
}

TEST(SeriesBasedOnTermTest, GetSumWorks)
{
    SeriesBasedOnTerm series(Term("x"), "x");

    EXPECT_EQ(Term(55), series.getSum(0, 10));
}

}

}
