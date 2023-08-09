#include <Algebra/Solution/SolutionUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(SolutionUtilitiesTest, GetPositiveLogarithmOfLargestNumberWorks)
{
    EXPECT_EQ(AlbaNumber(6.90775527898214), getPositiveLogarithmOfLargestNumber(Term(1000)));
    EXPECT_EQ(AlbaNumber(0), getPositiveLogarithmOfLargestNumber(Term("x")));
}

TEST(SolutionUtilitiesTest, GetValuesForDomainSearchingWorks)
{
    AlbaNumbers actualValues(getValuesForDomainSearching(Term(Monomial(123, {{"x", 456}}))));

    ASSERT_EQ(8u, actualValues.size());
    EXPECT_DOUBLE_EQ(-456, actualValues.at(0).getDouble());
    EXPECT_DOUBLE_EQ(-123, actualValues.at(1).getDouble());
    EXPECT_DOUBLE_EQ(-6.1224928095143865, actualValues.at(2).getDouble());
    EXPECT_DOUBLE_EQ(-4.8121843553724171, actualValues.at(3).getDouble());
    EXPECT_DOUBLE_EQ(4.8121843553724171, actualValues.at(4).getDouble());
    EXPECT_DOUBLE_EQ(6.1224928095143865, actualValues.at(5).getDouble());
    EXPECT_DOUBLE_EQ(123, actualValues.at(6).getDouble());
    EXPECT_DOUBLE_EQ(456, actualValues.at(7).getDouble());
}


}

}