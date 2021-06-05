#include <Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(UtilitiesTest, IsOperatorWorksCorrectly)
{
    EXPECT_FALSE(isOperator(""));
    EXPECT_TRUE(isOperator("+"));
    EXPECT_TRUE(isOperator("-"));
    EXPECT_TRUE(isOperator("*"));
    EXPECT_TRUE(isOperator("/"));
    EXPECT_TRUE(isOperator("^"));
    EXPECT_FALSE(isOperator("add"));
}

TEST(UtilitiesTest, IsOperatorForMultipleTermsWorksCorrectly)
{
    EXPECT_FALSE(isOperatorForMultipleTerms(""));
    EXPECT_TRUE(isOperatorForMultipleTerms("+"));
    EXPECT_TRUE(isOperatorForMultipleTerms("-"));
    EXPECT_FALSE(isOperatorForMultipleTerms("*"));
    EXPECT_FALSE(isOperatorForMultipleTerms("/"));
    EXPECT_FALSE(isOperatorForMultipleTerms("^"));
    EXPECT_FALSE(isOperatorForMultipleTerms("add"));
}

TEST(UtilitiesTest, CanBeAddedOrSubtractedForBothMonomialsWorksCorrectly)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial monomial3(100, {{"x", 6}, {"y", -1.25}});
    Monomial monomial4(100, {{"x", 5}, {"y", -1}});
    Monomial monomial5(645, {{"i", 20}, {"y", 30}});

    EXPECT_TRUE(canBeAddedOrSubtracted(monomial1, monomial1));
    EXPECT_TRUE(canBeAddedOrSubtracted(monomial2, monomial2));
    EXPECT_TRUE(canBeAddedOrSubtracted(monomial3, monomial3));
    EXPECT_TRUE(canBeAddedOrSubtracted(monomial4, monomial4));
    EXPECT_TRUE(canBeAddedOrSubtracted(monomial5, monomial5));
    EXPECT_FALSE(canBeAddedOrSubtracted(monomial1, monomial2));
    EXPECT_TRUE(canBeAddedOrSubtracted(monomial2, monomial3));
    EXPECT_FALSE(canBeAddedOrSubtracted(monomial2, monomial4));
    EXPECT_FALSE(canBeAddedOrSubtracted(monomial2, monomial5));
}

TEST(UtilitiesTest, CanBeAddedOrSubtractedForMonomialAndVariableWorksCorrectly)
{
    Monomial monomial1;
    Monomial monomial2(12, {{"x", 1}});
    Monomial monomial3(34, {{"x", 1.25}});
    Monomial monomial4(56, {{"x", 1}, {"y", 1}});
    Variable variable("x");

    EXPECT_FALSE(canBeAddedOrSubtracted(monomial1, variable));
    EXPECT_TRUE(canBeAddedOrSubtracted(monomial2, variable));
    EXPECT_FALSE(canBeAddedOrSubtracted(monomial3, variable));
    EXPECT_FALSE(canBeAddedOrSubtracted(monomial4, variable));
}

TEST(UtilitiesTest, PerformChangeForVariablesWorksAsExpected)
{
    Monomial::VariablesToExponentsMap variablesToExponents{{"x", 1}, {"y", 2}, {"z", 3}};

    performChangeForVariables(variablesToExponents, [](string const &, AlbaNumber & exponent)
    {
        exponent=exponent*3;
    });

    ASSERT_EQ(3u, variablesToExponents.size());
    EXPECT_DOUBLE_EQ(3, variablesToExponents.at("x").getDouble());
    EXPECT_DOUBLE_EQ(6, variablesToExponents.at("y").getDouble());
    EXPECT_DOUBLE_EQ(9, variablesToExponents.at("z").getDouble());
}

TEST(UtilitiesTest, WrappingTermsWorksCorrectly)
{
    WrappedTerms wrappedTerms;

    wrapTerms(wrappedTerms, Terms{Term(5), Term("+"), Term("interest")});

    BaseTermSharedPointers & baseTermPointersToVerify(wrappedTerms.getBaseTermPointersReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(5, term1.getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("+", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("interest", term3.getVariableConstReference().getVariableName());
}

TEST(UtilitiesTest, UnwrappingTermsWorksCorrectly)
{
    WrappedTerms wrappedTerms;
    wrapTerms(wrappedTerms, Terms{Term(-5), Term("-"), Term("count")});

    Terms termsToVerify(unwrapTermsAndReturnTerms(wrappedTerms));

    ASSERT_EQ(3u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(-5, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Operator, termsToVerify.at(1).getTermType());
    EXPECT_EQ("-", termsToVerify.at(1).getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, termsToVerify.at(2).getTermType());
    EXPECT_EQ("count", termsToVerify.at(2).getVariableConstReference().getVariableName());
}

TEST(UtilitiesTest, CreateExpressionWorksCorrectly)
{
    Expression expressionToTest(createExpression(Terms{Term(7.625), Term("-"), Term("compoundinterest")}));

    BaseTermSharedPointers & baseTermPointersToVerify(expressionToTest.getWrappedTermsReference().getBaseTermPointersReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(7.625, term1.getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("-", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("compoundinterest", term3.getVariableConstReference().getVariableName());
}

TEST(UtilitiesTest, GetTermsInAnExpressionWorksCorrectly)
{
    Expression expression(createExpression(Terms{Term(-54654.25), Term("+"), Term("x"), Term("*"), Term("y")}));

    Terms termsToVerify(getTermsInAnExpression(expression));

    ASSERT_EQ(5u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(-54654.25, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Operator, termsToVerify.at(1).getTermType());
    EXPECT_EQ("+", termsToVerify.at(1).getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, termsToVerify.at(2).getTermType());
    EXPECT_EQ("x", termsToVerify.at(2).getVariableConstReference().getVariableName());
    ASSERT_EQ(TermType::Operator, termsToVerify.at(3).getTermType());
    EXPECT_EQ("*", termsToVerify.at(3).getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, termsToVerify.at(4).getTermType());
    EXPECT_EQ("y", termsToVerify.at(4).getVariableConstReference().getVariableName());
}

}

}
