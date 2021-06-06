#include <Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;
using AssociationType=alba::equation::TermsWithPriorityAndAssociation::AssociationType;
using TermWithDetails=alba::equation::TermsWithPriorityAndAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithPriorityAndAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

TEST(UtilitiesTest, IsOperatorWorks)
{
    EXPECT_FALSE(isOperator(""));
    EXPECT_TRUE(isOperator("+"));
    EXPECT_TRUE(isOperator("-"));
    EXPECT_TRUE(isOperator("*"));
    EXPECT_TRUE(isOperator("/"));
    EXPECT_TRUE(isOperator("^"));
    EXPECT_FALSE(isOperator("add"));
}

TEST(UtilitiesTest, CanBeMergedByAdditionOrSubtractionForBothMonomialsWorks)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial monomial3(100, {{"x", 6}, {"y", -1.25}});
    Monomial monomial4(100, {{"x", 5}, {"y", -1}});
    Monomial monomial5(645, {{"i", 20}, {"y", 30}});

    EXPECT_TRUE(canBeMergedByAdditionOrSubtraction(monomial1, monomial1));
    EXPECT_TRUE(canBeMergedByAdditionOrSubtraction(monomial2, monomial2));
    EXPECT_TRUE(canBeMergedByAdditionOrSubtraction(monomial3, monomial3));
    EXPECT_TRUE(canBeMergedByAdditionOrSubtraction(monomial4, monomial4));
    EXPECT_TRUE(canBeMergedByAdditionOrSubtraction(monomial5, monomial5));
    EXPECT_FALSE(canBeMergedByAdditionOrSubtraction(monomial1, monomial2));
    EXPECT_TRUE(canBeMergedByAdditionOrSubtraction(monomial2, monomial3));
    EXPECT_FALSE(canBeMergedByAdditionOrSubtraction(monomial2, monomial4));
    EXPECT_FALSE(canBeMergedByAdditionOrSubtraction(monomial2, monomial5));
}

TEST(UtilitiesTest, CanBeMergedByAdditionOrSubtractionForMonomialAndVariableWorks)
{
    Monomial monomial1;
    Monomial monomial2(12, {{"x", 1}});
    Monomial monomial3(34, {{"x", 1.25}});
    Monomial monomial4(56, {{"x", 1}, {"y", 1}});
    Variable variable("x");

    EXPECT_FALSE(canBeMergedByAdditionOrSubtraction(monomial1, variable));
    EXPECT_TRUE(canBeMergedByAdditionOrSubtraction(monomial2, variable));
    EXPECT_FALSE(canBeMergedByAdditionOrSubtraction(monomial3, variable));
    EXPECT_FALSE(canBeMergedByAdditionOrSubtraction(monomial4, variable));
}

TEST(UtilitiesTest, GetOperatorLevelValueWorks)
{
    EXPECT_EQ(0u, getOperatorLevelInversePriority(OperatorLevel::Unknown));
    EXPECT_EQ(3u, getOperatorLevelInversePriority(OperatorLevel::AdditionAndSubtraction));
    EXPECT_EQ(2u, getOperatorLevelInversePriority(OperatorLevel::MultiplicationAndDivision));
    EXPECT_EQ(1u, getOperatorLevelInversePriority(OperatorLevel::RaiseToPower));
}

TEST(UtilitiesTest, GetTermPriorityValueWorks)
{
    EXPECT_EQ(1u, getTermTypePriorityValue(TermType::Operator));
    EXPECT_EQ(2u, getTermTypePriorityValue(TermType::Constant));
    EXPECT_EQ(3u, getTermTypePriorityValue(TermType::Variable));
    EXPECT_EQ(4u, getTermTypePriorityValue(TermType::Monomial));
    EXPECT_EQ(5u, getTermTypePriorityValue(TermType::Polynomial));
    EXPECT_EQ(6u, getTermTypePriorityValue(TermType::Expression));
}

TEST(UtilitiesTest, CreateMonomialConstantWorks)
{
    EXPECT_EQ(Monomial(5648, {}), createMonomialConstant(5648));
}

TEST(UtilitiesTest, CreateMonomialVariableWorks)
{
    EXPECT_EQ(Monomial(1, {{"weight", 1}}), createMonomialVariable("weight"));
}

TEST(UtilitiesTest, CreateExpressionInExpressionWorks)
{
    Expression expression1(createExpressionIfPossible(Terms{Term(254)}));
    Expression expression2(createExpressionIfPossible(Terms{Term(4752)}));

    Expression expressionToVerify1(createExpressionInAnExpression(expression1));
    Expression expressionToVerify2(createExpressionInAnExpression(createExpressionInAnExpression(expression2)));

    Expression expressionToExpect1(getBaseTermConstReferenceFromTerm(Term(expression1)));
    Expression expressionToExpect2(getBaseTermConstReferenceFromTerm(Term(Expression(getBaseTermConstReferenceFromTerm(Term(expression2))))));
    EXPECT_EQ(expressionToExpect1, expressionToVerify1);
    EXPECT_EQ(expressionToExpect2, expressionToVerify2);
}

TEST(UtilitiesTest, CreateAndWrapExpressionFromATermWorks)
{
    Expression expression1(createExpressionIfPossible(Terms{Term(254)}));
    Expression expression2(createExpressionIfPossible(Terms{Term(4752)}));

    Expression expressionToVerify1(createAndWrapExpressionFromATerm(Term(expression1)));
    Expression expressionToVerify2(createAndWrapExpressionFromATerm(Term(4752)));

    Expression expressionToExpect1(getBaseTermConstReferenceFromTerm(Term(expression1)));
    EXPECT_EQ(expressionToExpect1, expressionToVerify1);
    EXPECT_EQ(expression2, expressionToVerify2);
}

TEST(UtilitiesTest, CreateOrCopyExpressionFromATermWorks)
{
    Expression expression1(createExpressionIfPossible(Terms{Term(254)}));
    Expression expression2(createExpressionIfPossible(Terms{Term(4752)}));

    Expression expressionToVerify1(createOrCopyExpressionFromATerm(Term(expression1)));
    Expression expressionToVerify2(createOrCopyExpressionFromATerm(Term(4752)));

    EXPECT_EQ(expression1, expressionToVerify1);
    EXPECT_EQ(expression2, expressionToVerify2);
}

TEST(UtilitiesTest, CreateExpressionIfPossibleWorks)
{
    Expression expressionToTest(createExpressionIfPossible(Terms{Term(10), Term("/"), Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})})}));

    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTerms().getTermsWithDetails());
    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_EQ(AssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1(getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(Term(10), termToVerify1);
    EXPECT_EQ(AssociationType::Negative, termsToVerify.at(1).association);
    Term const& termToVerify2(getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}), termToVerify2);
}

TEST(UtilitiesTest, CreateExpressionIfPossibleDoesNotSimplifyExpressionInAExpression)
{
    Expression expression1(createExpressionIfPossible(Terms{Term(88)}));
    Expression expression2(createExpressionInAnExpression(expression1));
    Expression expression3(createExpressionInAnExpression(expression2));

    Expression expressionToTest1(createExpressionIfPossible(Terms{expression3}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest1.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify1(expressionToTest1.getTerms().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify1.size());
    EXPECT_EQ(AssociationType::Positive, termsToVerify1.at(0).association);
    Term const& termToVerify1(getTermConstReferenceFromSharedPointer(termsToVerify1.at(0).baseTermSharedPointer));
    ASSERT_TRUE(termToVerify1.isExpression());
    Expression expressionToTest2(termToVerify1.getExpressionConstReference());
    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest2.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify2(expressionToTest2.getTerms().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify2.size());
    EXPECT_EQ(AssociationType::Positive, termsToVerify2.at(0).association);
    Term const& termToVerify2(getTermConstReferenceFromSharedPointer(termsToVerify2.at(0).baseTermSharedPointer));
    ASSERT_TRUE(termToVerify2.isExpression());
    Expression expressionToTest3(termToVerify2.getExpressionConstReference());
    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest3.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify3(expressionToTest3.getTerms().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify3.size());
    EXPECT_EQ(AssociationType::Positive, termsToVerify3.at(0).association);
    Term const& termToVerify3(getTermConstReferenceFromSharedPointer(termsToVerify3.at(0).baseTermSharedPointer));
    ASSERT_TRUE(termToVerify3.isConstant());
    EXPECT_EQ(Constant(88), termToVerify3.getConstantConstReference());
}

TEST(UtilitiesTest, CreateExpressionIfPossibleDoesNotSimplify)
{
    Expression expressionToTest(createExpressionIfPossible(Terms{Term(7.625), Term("+"), Term(2.375)}));

    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTerms().getTermsWithDetails());
    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_EQ(AssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1(getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(Term(7.625), termToVerify1);
    EXPECT_EQ(AssociationType::Positive, termsToVerify.at(1).association);
    Term const& termToVerify2(getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(Term(2.375), termToVerify2);
}

TEST(UtilitiesTest, CreateExpressionIfPossibleReturnsEmptyIfListOfTermsAreWrong)
{
    Expression expressionToTest(createExpressionIfPossible(Terms{Term(7.625), Term("+"), Term("/"), Term(2.375)}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTerms().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify.empty());
}

TEST(UtilitiesTest, CreateSimplifiedExpressionIfPossibleWorks)
{
    Expression expressionToTest(createSimplifiedExpressionIfPossible(Terms{Term(7.625), Term("+"), Term(2.375)}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTerms().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(AssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1(getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));
    EXPECT_EQ(Term(10), termToVerify1);
}

TEST(UtilitiesTest, CreateSimplifiedExpressionIfPossibleReturnsEmptyIfListOfTermsAreWrong)
{
    Expression expressionToTest(createSimplifiedExpressionIfPossible(Terms{Term("+"), Term("+"), Term("+")}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTerms().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify.empty());
}

TEST(UtilitiesTest, SimplifyAndConvertExpressionToSimplestTermWorks)
{
    Expression expression1(createExpressionIfPossible(Terms{Term(88)}));
    Expression expression2(createExpressionInAnExpression(expression1));
    Expression expression3(createExpressionInAnExpression(expression2));
    Expression expression4(createExpressionInAnExpression(expression3));

    Term termToVerify1(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible(Terms{})));
    Term termToVerify2(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible(Terms{expression1})));
    Term termToVerify3(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible(Terms{expression2})));
    Term termToVerify4(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible(Terms{expression3})));
    Term termToVerify5(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible(Terms{expression4})));

    ASSERT_EQ(TermType::Empty, termToVerify1.getTermType());
    ASSERT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(88, termToVerify2.getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify3.getTermType());
    EXPECT_DOUBLE_EQ(88, termToVerify3.getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify4.getTermType());
    EXPECT_DOUBLE_EQ(88, termToVerify4.getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify5.getTermType());
    EXPECT_DOUBLE_EQ(88, termToVerify5.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(UtilitiesTest, SimplifyAndConvertPolynomialToSimplestTermWorks)
{
    Term termToVerify1(simplifyAndConvertPolynomialToSimplestTerm(Polynomial{}));
    Term termToVerify2(simplifyAndConvertPolynomialToSimplestTerm(Polynomial{Monomial(6, {})}));
    Term termToVerify3(simplifyAndConvertPolynomialToSimplestTerm(Polynomial{Monomial(6, {{"x", 1}}), Monomial(-6, {{"x", 1}})}));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify1.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Constant, termToVerify3.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify3.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(UtilitiesTest, SimplifyAndConvertMonomialToSimplestTermWorks)
{
    Term termToVerify1(simplifyAndConvertMonomialToSimplestTerm(Monomial()));
    Term termToVerify2(simplifyAndConvertMonomialToSimplestTerm(Monomial(6, {})));
    Term termToVerify3(simplifyAndConvertMonomialToSimplestTerm(Monomial(1, {{"x", 1}})));
    Term termToVerify4(simplifyAndConvertMonomialToSimplestTerm(Monomial(10, {{"x", 0}})));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify1.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Variable, termToVerify3.getTermType());
    EXPECT_EQ("x", termToVerify3.getVariableConstReference().getVariableName());
    ASSERT_EQ(TermType::Constant, termToVerify4.getTermType());
    EXPECT_DOUBLE_EQ(10, termToVerify4.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(UtilitiesTest, CreateNewTermAndReturnSharedPointerWorks)
{
    BaseTermSharedPointer sharedPointer(dynamic_cast<BaseTerm*>(new Term(9652)));

    BaseTermSharedPointer sharedPointerToVerify(createNewTermAndReturnSharedPointer(sharedPointer));

    Term const& termToVerify(getTermConstReferenceFromSharedPointer(sharedPointerToVerify));
    EXPECT_EQ(Term(9652), termToVerify);
    EXPECT_EQ(1, sharedPointerToVerify.use_count());
}

TEST(UtilitiesTest, CopyAndCreateNewTermAndReturnSharedPointerWorks)
{
    BaseTermSharedPointer sharedPointerToVerify(copyAndCreateNewTermAndReturnSharedPointer(Term(6415)));

    Term const& termToVerify(getTermConstReferenceFromSharedPointer(sharedPointerToVerify));
    EXPECT_EQ(Term(6415), termToVerify);
    EXPECT_EQ(1, sharedPointerToVerify.use_count());
}

TEST(UtilitiesTest, GetSharedPointerFromTermReferenceWorks)
{
    Term termToVerify(7896);

    BaseTermSharedPointer sharedPointer(getSharedPointerFromTermReference(termToVerify));
    Term & termToChange = *dynamic_cast<Term*>(sharedPointer.get());
    termToChange.getConstantReference().setNumber(1459);

    EXPECT_EQ(Term(1459), termToVerify);
    EXPECT_EQ(1, sharedPointer.use_count());
}

TEST(UtilitiesTest, GetTermConstReferenceFromBaseTermWorks)
{
    Term originalTerm(7896);

    Term const& termToVerify(getTermConstReferenceFromBaseTerm(dynamic_cast<BaseTerm const&>(originalTerm)));

    EXPECT_EQ(Term(7896), termToVerify);
}

TEST(UtilitiesTest, GetTermConstReferenceFromSharedPointerWorks)
{
    BaseTermSharedPointer sharedPointer(dynamic_cast<BaseTerm*>(new Term(9541)));

    Term const& termToVerify(getTermConstReferenceFromSharedPointer(sharedPointer));

    EXPECT_EQ(Term(9541), termToVerify);
    EXPECT_EQ(1, sharedPointer.use_count());
}

TEST(UtilitiesTest, GetTermReferenceFromBaseTermWorks)
{
    Term originalTerm(7896);

    Term & termToVerify(getTermReferenceFromBaseTerm(dynamic_cast<BaseTerm &>(originalTerm)));
    originalTerm = Term(854);

    EXPECT_EQ(Term(854), termToVerify);
}

TEST(UtilitiesTest, GetTermReferenceFromSharedPointerWorks)
{
    BaseTermSharedPointer sharedPointer(dynamic_cast<BaseTerm*>(new Term(9652)));

    Term & termToChange(getTermReferenceFromSharedPointer(sharedPointer));
    termToChange.getConstantReference().setNumber(763);

    Term const& termToVerify(getTermConstReferenceFromSharedPointer(sharedPointer));
    EXPECT_EQ(Term(763), termToVerify);
    EXPECT_EQ(1, sharedPointer.use_count());
}

TEST(UtilitiesTest, GetBaseTermConstReferenceFromTermWorks)
{
    Term originalTerm(7896);

    BaseTerm const& baseTerm(getBaseTermConstReferenceFromTerm(originalTerm));

    Term const& termToVerify(dynamic_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(7896), termToVerify);
}

TEST(UtilitiesTest, GetBaseTermConstReferenceFromSharedPointerWorks)
{
    BaseTermSharedPointer sharedPointer(copyAndCreateNewTermAndReturnSharedPointer(Term(6415)));

    BaseTerm const& baseTerm(getBaseTermConstReferenceFromSharedPointer(sharedPointer));

    Term const& termToVerify(dynamic_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(6415), termToVerify);
    EXPECT_EQ(1, sharedPointer.use_count());
}

TEST(UtilitiesTest, GetBaseTermReferenceFromTermWorks)
{
    Term originalTerm(7896);

    BaseTerm & baseTerm(getBaseTermReferenceFromTerm(originalTerm));
    Term & termToVerify(dynamic_cast<Term &>(baseTerm));
    originalTerm = Term(854);

    EXPECT_EQ(Term(854), termToVerify);
}

}

}
