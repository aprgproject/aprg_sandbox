#include <Algebra/Constructs/TermsAggregator.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
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
    TermsAggregator aggregator({"-", "x"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Expression, termsToVerify.at(0).getTermType());
    Expression expressionToExpect(createExpressionIfPossible({"-", "x"}));
    Expression expressionToVerify(termsToVerify.at(0).getExpressionConstReference());
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithBinaryOperation)
{
    TermsAggregator aggregator({"x", "+", "x"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Expression, termsToVerify.at(0).getTermType());
    Expression expressionToExpect(createExpressionIfPossible({"x", "+", "x"}));
    Expression expressionToVerify(termsToVerify.at(0).getExpressionConstReference());
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithDifferentOperationLevels)
{
    TermsAggregator aggregator(
    {"a", "+", "b", "*", "c", "^", "d"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Expression, termsToVerify.at(0).getTermType());
    Expression subExpression1(createExpressionIfPossible({"c", "^", "d"}));
    Expression subExpression2(createExpressionIfPossible({"b", "*", subExpression1}));
    Expression subExpression3(createExpressionIfPossible({"a", "+", subExpression2}));
    Expression expressionToExpect(subExpression3);
    Expression expressionToVerify(termsToVerify.at(0).getExpressionConstReference());
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithParenthesis)
{
    TermsAggregator aggregator(
    {"(", "(", "(", "a", "+", "b", ")", "*", "c", ")", "^", "d", ")"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Expression, termsToVerify.at(0).getTermType());
    Expression subExpression1(createExpressionIfPossible({"a", "+", "b"}));
    Expression subExpression2(createExpressionIfPossible({subExpression1, "*", "c"}));
    Expression subExpression3(createExpressionIfPossible({subExpression2, "^", "d"}));
    Expression expressionToExpect(subExpression3);
    Expression expressionToVerify(termsToVerify.at(0).getExpressionConstReference());
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(TermsAggregatorTest, BuildExpressionFromTermsWorksOnNegativeFractionInParenthesis)
{
    TermsAggregator aggregator({"(", "-", 1, "/", 3, ")"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Expression, termsToVerify.at(0).getTermType());
    Expression subExpression1(createExpressionIfPossible({"-", 1}));
    Expression expressionToExpect(createExpressionIfPossible({subExpression1, "/", 3}));
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
    TermsAggregator aggregator({"-", 14});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(-14, termsToVerify.at(0).getConstantValueConstReference().getDouble());
}

TEST(TermsAggregatorTest, SimplifyWorksWithBinaryOperation)
{
    TermsAggregator aggregator({2, "+", 3});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(5, termsToVerify.at(0).getConstantValueConstReference().getDouble());
}

TEST(TermsAggregatorTest, SimplifyWorksWithDifferentOperationLevels)
{
    TermsAggregator aggregator(
    {2, "+", 3, "*", 4, "^", 5});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(3074, termsToVerify.at(0).getConstantValueConstReference().getDouble());
}

TEST(TermsAggregatorTest, SimplifyWorksWithParenthesis)
{
    TermsAggregator aggregator(
    {"(", "(", "(", 2, "+", 3, ")", "*", 4, ")", "^", 5, ")"});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(3200000, termsToVerify.at(0).getConstantValueConstReference().getDouble());
}

TEST(TermsAggregatorTest, SimplifyWorksWithNegativeValues)
{
    TermsAggregator aggregator(tokenizeToTerms("x^2*y^-3*z^4"));

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial monomialToExpect(1, {{"x", 2}, {"y", -3}, {"z", 4}});
    Monomial monomialToVerify(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_EQ(monomialToExpect, monomialToVerify);
}

TEST(TermsAggregatorTest, SimplifyWorksWithFunction)
{
    TermsAggregator aggregator(tokenizeToTerms("abs(5)"));

    aggregator.simplifyTerms();

    Function functionToExpect(Functions::abs(5));
    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Function, termsToVerify.at(0).getTermType());
    EXPECT_EQ(functionToExpect, termsToVerify.at(0).getFunctionConstReference());
}


}

}
