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

TEST(UtilitiesTest, WrappingTermsWorksCorrectly)
{
    WrappedTerms wrappedTerms;

    wrapTerms(wrappedTerms, Terms{Term(5), Term("+"), Term("interest")});

    WrappedTerms::BaseTermPointers & baseTermPointersToVerify(wrappedTerms.getBaseTermPointersReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    EXPECT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(5, term1.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("+", term2.getOperatorConstReference().getOperatorString());
    EXPECT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("interest", term3.getVariableConstReference().getVariableName());
}

TEST(UtilitiesTest, UnwrappingTermsWorksCorrectly)
{
    WrappedTerms wrappedTerms;
    wrapTerms(wrappedTerms, Terms{Term(-5), Term("-"), Term("count")});

    Terms termsToVerify(unwrapTermsAndReturnTerms(wrappedTerms));

    ASSERT_EQ(3u, termsToVerify.size());
    EXPECT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(-5, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Operator, termsToVerify.at(1).getTermType());
    EXPECT_EQ("-", termsToVerify.at(1).getOperatorConstReference().getOperatorString());
    EXPECT_EQ(TermType::Variable, termsToVerify.at(2).getTermType());
    EXPECT_EQ("count", termsToVerify.at(2).getVariableConstReference().getVariableName());
}

TEST(UtilitiesTest, CreateExpressionWorksCorrectly)
{
    Expression expressionToTest(createExpression(Terms{Term(7.625), Term("-"), Term("compoundinterest")}));

    WrappedTerms::BaseTermPointers & baseTermPointersToVerify(expressionToTest.getWrappedTermsReference().getBaseTermPointersReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    EXPECT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(7.625, term1.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("-", term2.getOperatorConstReference().getOperatorString());
    EXPECT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("compoundinterest", term3.getVariableConstReference().getVariableName());
}

TEST(UtilitiesTest, GetTermsInAnExpressionWorksCorrectly)
{
    Expression expression(createExpression(Terms{Term(-54654.25), Term("+"), Term("x"), Term("*"), Term("y")}));

    Terms termsToVerify(getTermsInAnExpression(expression));

    ASSERT_EQ(5u, termsToVerify.size());
    EXPECT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(-54654.25, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Operator, termsToVerify.at(1).getTermType());
    EXPECT_EQ("+", termsToVerify.at(1).getOperatorConstReference().getOperatorString());
    EXPECT_EQ(TermType::Variable, termsToVerify.at(2).getTermType());
    EXPECT_EQ("x", termsToVerify.at(2).getVariableConstReference().getVariableName());
    EXPECT_EQ(TermType::Operator, termsToVerify.at(3).getTermType());
    EXPECT_EQ("*", termsToVerify.at(3).getOperatorConstReference().getOperatorString());
    EXPECT_EQ(TermType::Variable, termsToVerify.at(4).getTermType());
    EXPECT_EQ("y", termsToVerify.at(4).getVariableConstReference().getVariableName());
}

}

}
