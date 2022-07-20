#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/StringHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace booleanAlgebra
{

TEST(StringHelpersTest, IsOperatorWorks)
{
    EXPECT_FALSE(isOperator(""));
    EXPECT_TRUE(isOperator("~"));
    EXPECT_TRUE(isOperator("&"));
    EXPECT_TRUE(isOperator("|"));
    EXPECT_TRUE(isOperator("("));
    EXPECT_TRUE(isOperator(")"));
    EXPECT_FALSE(isOperator("notAnOperator"));
}

TEST(StringHelpersTest, GetOperatorTypeValueWorks)
{
    EXPECT_EQ(1U, getOperatorPriority("("));
    EXPECT_EQ(2U, getOperatorPriority(")"));
    EXPECT_EQ(3U, getOperatorPriority("~"));
    EXPECT_EQ(4U, getOperatorPriority("&"));
    EXPECT_EQ(5U, getOperatorPriority("|"));
    EXPECT_EQ(0U, getOperatorPriority("notAnOperator"));
}

TEST(StringHelpersTest, GetStringWorksForOperatorType)
{
    EXPECT_TRUE(getString(OperatorType::Unknown).empty());
    EXPECT_EQ("~", getString(OperatorType::Not));
    EXPECT_EQ("&", getString(OperatorType::And));
    EXPECT_EQ("|", getString(OperatorType::Or));
}

TEST(StringHelpersTest, GetStringWorksForOperatorLevel)
{
    EXPECT_TRUE(getString(OperatorLevel::Unknown).empty());
    EXPECT_EQ("&", getString(OperatorLevel::And));
    EXPECT_EQ("|", getString(OperatorLevel::Or));
}

TEST(StringHelpersTest, GetStringForWrappedTermWorks)
{
    WrappedTerm wrappedTerm(Term(true));

    EXPECT_EQ("{[true]}", getString(wrappedTerm));
}

TEST(StringHelpersTest, GetStringForWrappedTermsWorks)
{
    WrappedTerms wrappedTerms;
    wrappedTerms.emplace_back(Term(true));
    wrappedTerms.emplace_back(Term(true));

    EXPECT_EQ("{[true]}, {[true]}", getString(wrappedTerms));
}

TEST(StringHelpersTest, CreateVariableTermNameForSubstitutionWorks)
{
    Term term(createVariableTermNameForSubstitution(Term("x")));

    EXPECT_EQ("{{x}}", createVariableTermNameForSubstitution(term));
}

TEST(StringHelpersTest, ConstructTermFromStringWorks)
{
    Term termToVerify1(constructTermFromString("5xxx"));
    Term termToVerify2(constructTermFromString("x111"));
    Term termToVerify3(constructTermFromString("false"));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_TRUE(termToVerify1.getBooleanValue());
    ASSERT_EQ(TermType::VariableTerm, termToVerify2.getTermType());
    EXPECT_EQ("x111", termToVerify2.getVariableTermConstReference().getVariableTermName());
    ASSERT_EQ(TermType::Constant, termToVerify3.getTermType());
    EXPECT_FALSE(termToVerify3.getBooleanValue());
}

TEST(StringHelpersTest, BuildTermIfPossibleWorks)
{
    Term termToVerify(buildTermIfPossible("x&y"));

    Term termToExpect(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(StringHelpersTest, TokenizeToTermsWorks)
{
    Terms termsToVerify1(tokenizeToTerms(" 5yyy & x1 & y1 | ~20.15"));

    ASSERT_EQ(8U, termsToVerify1.size());
    ASSERT_EQ(TermType::Constant, termsToVerify1.at(0).getTermType());
    EXPECT_EQ(true, termsToVerify1.at(0).getBooleanValue());
    ASSERT_EQ(TermType::Operator, termsToVerify1.at(1).getTermType());
    EXPECT_EQ("&", termsToVerify1.at(1).getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::VariableTerm, termsToVerify1.at(2).getTermType());
    EXPECT_EQ("x1", termsToVerify1.at(2).getVariableTermConstReference().getVariableTermName());
    ASSERT_EQ(TermType::Operator, termsToVerify1.at(3).getTermType());
    EXPECT_EQ("&", termsToVerify1.at(3).getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::VariableTerm, termsToVerify1.at(4).getTermType());
    EXPECT_EQ("y1", termsToVerify1.at(4).getVariableTermConstReference().getVariableTermName());
    ASSERT_EQ(TermType::Operator, termsToVerify1.at(5).getTermType());
    EXPECT_EQ("|", termsToVerify1.at(5).getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Operator, termsToVerify1.at(6).getTermType());
    EXPECT_EQ("~", termsToVerify1.at(6).getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Constant, termsToVerify1.at(7).getTermType());
    EXPECT_TRUE(termsToVerify1.at(7).getBooleanValue());
}

TEST(StringHelpersTest, AddValueTermIfNotEmptyWorks)
{
    Terms termsToVerify1;

    addValueTermIfNotEmpty(termsToVerify1, "true");

    ASSERT_EQ(1U, termsToVerify1.size());
    ASSERT_EQ(TermType::Constant, termsToVerify1.at(0).getTermType());
    EXPECT_TRUE(termsToVerify1.at(0).getBooleanValue());
}

}

}
