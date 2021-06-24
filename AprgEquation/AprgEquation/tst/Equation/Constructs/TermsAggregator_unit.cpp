#include <Equation/Constructs/TermsAggregator.hpp>
#include <Equation/Functions/CommonFunctionLibrary.hpp>
#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithNoTerms)
{
    TermsAggregator aggregator({});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_TRUE(termsToVerify.empty());
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithUnaryOperation)
{
    TermsAggregator aggregator({Term("-"), Term("x")});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Expression, termsToVerify.at(0).getTermType());
    Expression expressionToExpect(createExpressionIfPossible({Term("-"), Term("x")}));
    Expression expressionToVerify(termsToVerify.at(0).getExpressionConstReference());
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithBinaryOperation)
{
    TermsAggregator aggregator({Term("x"), Term("+"), Term("x")});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Expression, termsToVerify.at(0).getTermType());
    Expression expressionToExpect(createExpressionIfPossible({Term("x"), Term("+"), Term("x")}));
    Expression expressionToVerify(termsToVerify.at(0).getExpressionConstReference());
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithDifferentOperationLevels)
{
    TermsAggregator aggregator({Term("a"), Term("+"), Term("b"),
                                     Term("*"), Term("c"),
                                     Term("^"), Term("d")});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Expression, termsToVerify.at(0).getTermType());
    Expression subExpression1(createExpressionIfPossible({Term("c"), Term("^"), Term("d")}));
    Expression subExpression2(createExpressionIfPossible({Term("b"), Term("*"), Term(subExpression1)}));
    Expression subExpression3(createExpressionIfPossible({Term("a"), Term("+"), Term(subExpression2)}));
    Expression expressionToExpect(subExpression3);
    Expression expressionToVerify(termsToVerify.at(0).getExpressionConstReference());
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithParenthesis)
{
    TermsAggregator aggregator({Term("("), Term("("),
                                     Term("("), Term("a"), Term("+"), Term("b"), Term(")"),
                                     Term("*"), Term("c"), Term(")"),
                                     Term("^"), Term("d"), Term(")")});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Expression, termsToVerify.at(0).getTermType());
    Expression subExpression1(createExpressionIfPossible({Term("a"), Term("+"), Term("b")}));
    Expression subExpression2(createExpressionIfPossible({Term(subExpression1), Term("*"), Term("c")}));
    Expression subExpression3(createExpressionIfPossible({Term(subExpression2), Term("^"), Term("d")}));
    Expression expressionToExpect(subExpression3);
    Expression expressionToVerify(termsToVerify.at(0).getExpressionConstReference());
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(TermsAggregatorTest, SimplifyWorksWithNoTerms)
{
    TermsAggregator aggregator({});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_TRUE(termsToVerify.empty());
}

TEST(TermsAggregatorTest, SimplifyWorksWithUnaryOperation)
{
    TermsAggregator aggregator({Term("-"), Term(14)});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(-14, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermsAggregatorTest, SimplifyWorksWithBinaryOperation)
{
    TermsAggregator aggregator({Term(2), Term("+"), Term(3)});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(5, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermsAggregatorTest, SimplifyWorksWithDifferentOperationLevels)
{
    TermsAggregator aggregator({Term(2), Term("+"), Term(3),
                                     Term("*"), Term(4),
                                     Term("^"), Term(5)});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(3074, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermsAggregatorTest, SimplifyWorksWithParenthesis)
{
    TermsAggregator aggregator({Term("("), Term("("),
                                     Term("("), Term(2), Term("+"), Term(3), Term(")"),
                                     Term("*"), Term(4), Term(")"),
                                     Term("^"), Term(5), Term(")")});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(3200000, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermsAggregatorTest, SimplifyWorksWithNegativeValues)
{
    TermsAggregator aggregator(tokenizeToTerms("x^2*y^-3*z^4"));

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial monomialToExpect(1, {{"x", 2}, {"y", -3}, {"z", 4}});
    Monomial monomialToVerify(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_EQ(monomialToExpect, monomialToVerify);
}

TEST(TermsAggregatorTest, SimplifyWorksWithFunction)
{
    TermsAggregator aggregator(tokenizeToTerms("abs(5)"));

    aggregator.simplifyTerms();

    Function functionToExpect(Functions::abs(createOrCopyExpressionFromATerm(Term(5))));
    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Function, termsToVerify.at(0).getTermType());
    EXPECT_EQ(functionToExpect, termsToVerify.at(0).getFunctionConstReference());
}


}

}
