#include <TermsAggregator.hpp>

#include <Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(TermsAggregatorTest, ThreeTermExpressionCanBeBuilt)
{
    TermsAggregator aggregator(Terms{Term("x"), Term("+"), Term("x")});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Expression, termsToVerify.at(0).getTermType());
    EXPECT_EQ(createExpressionIfPossible(Terms{Term("x"), Term("+"), Term("x")}), termsToVerify.at(0).getExpressionConstReference());
}

TEST(TermsAggregatorTest, ThreeTermsCanBeSimplified)
{
    TermsAggregator aggregator(Terms{Term(5), Term("+"), Term(2)});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(7, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

}

}
