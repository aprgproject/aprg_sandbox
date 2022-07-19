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
    Term termToExpect(createExpressionIfPossible({"-", "x"}));
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithBinaryOperation)
{
    TermsAggregator aggregator({"x", "+", "x"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term termToExpect(createExpressionIfPossible({"x", "+", "x"}));
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
}

TEST(TermsAggregatorTest, ExpressionCanBeBuiltWithDifferentOperationLevels)
{
    TermsAggregator aggregator(
    {"a", "+", "b", "*", "c", "^", "d"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Expression subExpression1(createExpressionIfPossible({"c", "^", "d"}));
    Expression subExpression2(createExpressionIfPossible({"b", "*", subExpression1}));
    Expression subExpression3(createExpressionIfPossible({"a", "+", subExpression2}));
    Term termToExpect(subExpression3);
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
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
    Term termToExpect(subExpression3);
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
}

TEST(TermsAggregatorTest, BuildExpressionFromTermsWorksOnNegativeFractionInParenthesis)
{
    TermsAggregator aggregator({"(", "-", 1, "/", 3, ")"});

    aggregator.buildExpressionFromTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Expression, termsToVerify.at(0).getTermType());
    Expression subExpression1(createExpressionIfPossible({"-", 1}));
    Term termToExpect(createExpressionIfPossible({subExpression1, "/", 3}));
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
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
    EXPECT_EQ(Term(-14), termsToVerify.at(0));
}

TEST(TermsAggregatorTest, SimplifyWorksWithBinaryOperation)
{
    TermsAggregator aggregator({2, "+", 3});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(5), termsToVerify.at(0));
}

TEST(TermsAggregatorTest, SimplifyWorksWithDifferentOperationLevels)
{
    TermsAggregator aggregator(
    {2, "+", 3, "*", 4, "^", 5});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(3074), termsToVerify.at(0));
}

TEST(TermsAggregatorTest, SimplifyWorksWithParenthesis)
{
    TermsAggregator aggregator(
    {"(", "(", "(", 2, "+", 3, ")", "*", 4, ")", "^", 5, ")"});

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(Term(3200000), termsToVerify.at(0));
}

TEST(TermsAggregatorTest, SimplifyWorksWithNegativeValues)
{
    TermsAggregator aggregator(tokenizeToTerms("x^2*y^-3*z^4"));

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Term termToExpect(Monomial(1, {{"x", 2}, {"y", -3}, {"z", 4}}));
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
}

TEST(TermsAggregatorTest, SimplifyWorksWithFunction)
{
    TermsAggregator aggregator(tokenizeToTerms("abs(5)"));

    aggregator.simplifyTerms();

    Terms termsToVerify(aggregator.getTermsConstReference());
    ASSERT_EQ(1U, termsToVerify.size());
    Term termToExpect(Functions::abs(5));
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
}

}

}
