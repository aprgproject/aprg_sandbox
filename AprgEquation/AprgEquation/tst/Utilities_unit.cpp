#include <Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(UtilitiesTest, IsOperatorWorks)
{
    EXPECT_FALSE(isOperator(""));
    EXPECT_TRUE(isOperator("+"));    EXPECT_TRUE(isOperator("-"));
    EXPECT_TRUE(isOperator("*"));
    EXPECT_TRUE(isOperator("/"));
    EXPECT_TRUE(isOperator("^"));
    EXPECT_FALSE(isOperator("add"));
}

TEST(UtilitiesTest, CanBeAddedOrSubtractedForBothMonomialsWorks)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x", 6}, {"y", -1.25}});    Monomial monomial3(100, {{"x", 6}, {"y", -1.25}});
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

TEST(UtilitiesTest, CanBeAddedOrSubtractedForMonomialAndVariableWorks)
{
    Monomial monomial1;
    Monomial monomial2(12, {{"x", 1}});    Monomial monomial3(34, {{"x", 1.25}});
    Monomial monomial4(56, {{"x", 1}, {"y", 1}});
    Variable variable("x");
    EXPECT_FALSE(canBeAddedOrSubtracted(monomial1, variable));
    EXPECT_TRUE(canBeAddedOrSubtracted(monomial2, variable));
    EXPECT_FALSE(canBeAddedOrSubtracted(monomial3, variable));
    EXPECT_FALSE(canBeAddedOrSubtracted(monomial4, variable));
}

TEST(UtilitiesTest, ConvertPolynomialToSimplestTermWorks)
{
    Term termToVerify1(convertPolynomialToSimplestTerm(Polynomial{}));
    Term termToVerify2(convertPolynomialToSimplestTerm(Polynomial{Monomial(6, {})}));    Term termToVerify3(convertPolynomialToSimplestTerm(Polynomial{Monomial(6, {{"x", 1}}), Monomial(-6, {{"x", 1}})}));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify1.getConstantConstReference().getNumberConstReference().getDouble());    EXPECT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Constant, termToVerify3.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify3.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(UtilitiesTest, ConvertMonomialToSimplestTermWorks)
{
    Term termToVerify1(convertMonomialToSimplestTerm(Monomial()));
    Term termToVerify2(convertMonomialToSimplestTerm(Monomial(6, {})));    Term termToVerify3(convertMonomialToSimplestTerm(Monomial(1, {{"x", 1}})));
    Term termToVerify4(convertMonomialToSimplestTerm(Monomial(10, {{"x", 0}})));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());    EXPECT_DOUBLE_EQ(0, termToVerify1.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Variable, termToVerify3.getTermType());
    EXPECT_EQ("x", termToVerify3.getVariableConstReference().getVariableName());
    ASSERT_EQ(TermType::Constant, termToVerify4.getTermType());
    EXPECT_DOUBLE_EQ(10, termToVerify4.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(UtilitiesTest, CreateExpressionWorks)
{
    Expression expressionToTest(createExpression(Terms{Term(10), Term("/"), Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})})}));

    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, expressionToTest.getCommonOperatorLevel());
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsToVerify(expressionToTest.getTerms().getTermsWithDetails());
    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1 = *dynamic_cast<Term const*const>(termsToVerify.at(0).baseTermSharedPointer.get());    EXPECT_EQ(Term(10), termToVerify1);
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Negative, termsToVerify.at(1).association);
    Term const& termToVerify2 = *dynamic_cast<Term const*const>(termsToVerify.at(1).baseTermSharedPointer.get());
    EXPECT_EQ(Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}), termToVerify2);}

TEST(UtilitiesTest, CreateExpressionDoesNotSimplify)
{
    Expression expressionToTest(createExpression(Terms{Term(7.625), Term("+"), Term(2.375)}));

    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expressionToTest.getCommonOperatorLevel());
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsToVerify(expressionToTest.getTerms().getTermsWithDetails());
    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1 = *dynamic_cast<Term const*const>(termsToVerify.at(0).baseTermSharedPointer.get());    EXPECT_EQ(Term(7.625), termToVerify1);
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsToVerify.at(1).association);
    Term const& termToVerify2 = *dynamic_cast<Term const*const>(termsToVerify.at(1).baseTermSharedPointer.get());
    EXPECT_EQ(Term(2.375), termToVerify2);}

TEST(UtilitiesTest, CreateExpressionReturnsEmptyIfListOfTermsAreWrong)
{
    Expression expressionToTest(createExpression(Terms{Term(7.625), Term("+"), Term("/"), Term(2.375)}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsToVerify(expressionToTest.getTerms().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify.empty());
}

TEST(UtilitiesTest, CreateSimplifiedExpressionWorks)
{
    Expression expressionToTest(createSimplifiedExpression(Terms{Term(7.625), Term("+"), Term(2.375)}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsToVerify(expressionToTest.getTerms().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1 = *dynamic_cast<Term const*const>(termsToVerify.at(0).baseTermSharedPointer.get());    EXPECT_EQ(Term(10), termToVerify1);
}

TEST(UtilitiesTest, CreateSimplifiedExpressionReturnsEmptyIfListOfTermsAreWrong){
    Expression expressionToTest(createExpression(Terms{Term(7.625), Term("+"), Term("/"), Term(2.375)}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsToVerify(expressionToTest.getTerms().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify.empty());
}
}

}