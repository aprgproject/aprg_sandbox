#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>
using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;
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

TEST(UtilitiesTest, CanBeMergedByAdditionOrSubtractionForTermsWorks)
{
    EXPECT_TRUE(canBeMergedByAdditionOrSubtraction(Term(73), Term(84)));
    EXPECT_TRUE(canBeMergedByAdditionOrSubtraction(Term(Variable("x")), Term(Variable("x"))));
    EXPECT_TRUE(canBeMergedByAdditionOrSubtraction(Term(Monomial(96, {{"x", 1}})), Term(Monomial(96, {{"x", 1}}))));
    EXPECT_TRUE(canBeMergedByAdditionOrSubtraction(Term(Monomial(96, {{"x", 1}})), Term(Variable("x"))));
    EXPECT_TRUE(canBeMergedByAdditionOrSubtraction(Term(Variable("x")), Term(Monomial(96, {{"x", 1}}))));
    EXPECT_FALSE(canBeMergedByAdditionOrSubtraction(Term(Variable("x")), Term(Variable("y"))));
    EXPECT_FALSE(canBeMergedByAdditionOrSubtraction(Term(Monomial(96, {{"x", 1}})), Term(Monomial(96, {{"x", 5}}))));
    EXPECT_FALSE(canBeMergedByAdditionOrSubtraction(Term(Monomial(96, {{"a", 1}})), Term(Variable("x"))));
    EXPECT_FALSE(canBeMergedByAdditionOrSubtraction(Term(Variable("x")), Term(Monomial(96, {{"a", 1}}))));
    EXPECT_FALSE(canBeMergedByAdditionOrSubtraction(Term(Expression()), Term(Expression())));
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

TEST(UtilitiesTest, CanBeMergedByAdditionOrSubtractionForBothVariablesWorks)
{
    EXPECT_TRUE(canBeMergedByAdditionOrSubtraction(Variable("x"), Variable("x")));
    EXPECT_FALSE(canBeMergedByAdditionOrSubtraction(Variable("x"), Variable("w")));
    EXPECT_FALSE(canBeMergedByAdditionOrSubtraction(Variable("w"), Variable("x")));
}

TEST(UtilitiesTest, CanBeConvertedToMonomialWorks)
{
    EXPECT_FALSE(canBeConvertedToMonomial(Term()));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(Constant(0))));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(15)));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(Variable("x"))));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(canBeConvertedToMonomial(Term(Polynomial{Monomial(96, {{"x", 1}}), Monomial(73, {{"y", 1}})})));
    EXPECT_FALSE(canBeConvertedToMonomial(Term(createExpressionIfPossible(Terms{Term(254)}))));
    EXPECT_FALSE(canBeConvertedToMonomial(Term(Expression())));
}

TEST(UtilitiesTest, CanBeConvertedToPolynomialWorks)
{
    EXPECT_FALSE(canBeConvertedToPolynomial(Term()));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(Constant(0))));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(15)));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(Variable("x"))));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(canBeConvertedToPolynomial(Term(createExpressionIfPossible(Terms{Term(254)}))));
    EXPECT_FALSE(canBeConvertedToPolynomial(Term(Expression())));
}

TEST(UtilitiesTest, WillHaveNoEffectOnAdditionOrSubtractionWorks)
{
    EXPECT_TRUE(willHaveNoEffectOnAdditionOrSubtraction(Term()));
    EXPECT_TRUE(willHaveNoEffectOnAdditionOrSubtraction(Term(Constant(0))));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(15)));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(Variable("x"))));    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(createExpressionIfPossible(Terms{Term(254)}))));
    EXPECT_TRUE(willHaveNoEffectOnAdditionOrSubtraction(Term(Expression())));}

TEST(UtilitiesTest, WillHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPowerWorks)
{
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term()));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Constant(0))));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(15)));
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(1)));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Variable("x"))));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Monomial(1, {}))));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(createExpressionIfPossible(Terms{Term(254)}))));
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Expression())));
}

TEST(UtilitiesTest, GetOperatorLevelValueWorks)
{
    EXPECT_EQ(1u, getOperatorPriority("+"));
    EXPECT_EQ(2u, getOperatorPriority("-"));
    EXPECT_EQ(3u, getOperatorPriority("*"));
    EXPECT_EQ(4u, getOperatorPriority("/"));
    EXPECT_EQ(5u, getOperatorPriority("^"));
    EXPECT_EQ(0u, getOperatorPriority("operator"));
}

TEST(UtilitiesTest, GetAssociationPriorityWorks)
{
    EXPECT_EQ(1u, getAssociationPriority(TermAssociationType::Positive));
    EXPECT_EQ(2u, getAssociationPriority(TermAssociationType::Negative));
}

TEST(UtilitiesTest, GetOperatorLevelInversePriorityWorks)
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

TEST(UtilitiesTest, CreateMonomialConstantWorks)
{
    EXPECT_EQ(Monomial(5648, {}), createMonomialFromConstant(Constant(5648)));
}

TEST(UtilitiesTest, CreateMonomialVariableWorks)
{
    EXPECT_EQ(Monomial(1, {{"weight", 1}}), createMonomialFromVariable(Variable("weight")));
}

TEST(UtilitiesTest, CreatePolynomialIfPossibleWorks)
{
    EXPECT_EQ((Polynomial{Monomial(97, {})}), createPolynomialIfPossible(Term(97)));
    EXPECT_EQ((Polynomial{Monomial(1, {{"weight", 1}})}), createPolynomialIfPossible(Term("weight")));
    EXPECT_EQ((Polynomial{Monomial(24, {{"i", 5}})}), createPolynomialIfPossible(Term(Monomial(24, {{"i", 5}}))));
    EXPECT_EQ((Polynomial{Monomial(39, {{"r", 7}})}), createPolynomialIfPossible(Term(Polynomial{Monomial(39, {{"r", 7}})})));
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
    TermsWithDetails const& termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1(getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));    EXPECT_EQ(Term(10), termToVerify1);
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(1).association);
    Term const& termToVerify2(getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}), termToVerify2);}

TEST(UtilitiesTest, CreateExpressionIfPossibleDoesNotSimplifyExpressionInAExpression)
{
    Expression expression1(createExpressionIfPossible(Terms{Term(88)}));
    Expression expression2(createExpressionInAnExpression(expression1));
    Expression expression3(createExpressionInAnExpression(expression2));

    Expression expressionToTest1(createExpressionIfPossible(Terms{expression3}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest1.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify1(expressionToTest1.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify1.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify1.at(0).association);
    Term const& termToVerify1(getTermConstReferenceFromSharedPointer(termsToVerify1.at(0).baseTermSharedPointer));    ASSERT_TRUE(termToVerify1.isExpression());
    Expression expressionToTest2(termToVerify1.getExpressionConstReference());
    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest2.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify2(expressionToTest2.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify2.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify2.at(0).association);
    Term const& termToVerify2(getTermConstReferenceFromSharedPointer(termsToVerify2.at(0).baseTermSharedPointer));    ASSERT_TRUE(termToVerify2.isExpression());
    Expression expressionToTest3(termToVerify2.getExpressionConstReference());
    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest3.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify3(expressionToTest3.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify3.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify3.at(0).association);
    Term const& termToVerify3(getTermConstReferenceFromSharedPointer(termsToVerify3.at(0).baseTermSharedPointer));    ASSERT_TRUE(termToVerify3.isConstant());
    EXPECT_EQ(Constant(88), termToVerify3.getConstantConstReference());
}
TEST(UtilitiesTest, CreateExpressionIfPossibleDoesNotSimplify)
{
    Expression expressionToTest(createExpressionIfPossible(Terms{Term(7.625), Term("+"), Term(2.375)}));

    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1(getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));    EXPECT_EQ(Term(7.625), termToVerify1);
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(1).association);
    Term const& termToVerify2(getTermConstReferenceFromSharedPointer(termsToVerify.at(1).baseTermSharedPointer));
    EXPECT_EQ(Term(2.375), termToVerify2);}

TEST(UtilitiesTest, CreateExpressionIfPossibleReturnsEmptyIfListOfTermsAreWrong)
{
    Expression expressionToTest(createExpressionIfPossible(Terms{Term(7.625), Term("+"), Term("/"), Term(2.375)}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify.empty());
}
TEST(UtilitiesTest, CreateSimplifiedExpressionIfPossibleWorks)
{
    Expression expressionToTest(createSimplifiedExpressionIfPossible(Terms{Term(7.625), Term("+"), Term(2.375)}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1(getTermConstReferenceFromSharedPointer(termsToVerify.at(0).baseTermSharedPointer));    EXPECT_EQ(Term(10), termToVerify1);
}

TEST(UtilitiesTest, CreateSimplifiedExpressionIfPossibleReturnsEmptyIfListOfTermsAreWrong){
    Expression expressionToTest(createSimplifiedExpressionIfPossible(Terms{Term("+"), Term("+"), Term("+")}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify.empty());
}
TEST(UtilitiesTest, ConvertExpressionToSimplestTermWorks)
{
    Term termToVerify1(convertExpressionToSimplestTerm(createExpressionIfPossible(Terms{})));    Term termToVerify2(convertExpressionToSimplestTerm(createExpressionIfPossible(Terms{Term(156)})));

    ASSERT_EQ(Term(), termToVerify1);
    ASSERT_EQ(Term(156), termToVerify2);
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

TEST(UtilitiesTest, TokenizeToTermsWorks)
{
    Terms termsToVerify1(tokenizeToTerms(" 5yyy + x1*y1^20.15"));
    ASSERT_EQ(7u, termsToVerify1.size());
    EXPECT_EQ(TermType::Constant, termsToVerify1.at(0).getTermType());
    EXPECT_DOUBLE_EQ(5, termsToVerify1.at(0).getConstantConstReference().getNumberConstReference().getDouble());    EXPECT_EQ(TermType::Operator, termsToVerify1.at(1).getTermType());
    EXPECT_EQ("+", termsToVerify1.at(1).getOperatorConstReference().getOperatorString());
    EXPECT_EQ(TermType::Variable, termsToVerify1.at(2).getTermType());
    EXPECT_EQ("x1", termsToVerify1.at(2).getVariableConstReference().getVariableName());
    EXPECT_EQ(TermType::Operator, termsToVerify1.at(3).getTermType());
    EXPECT_EQ("*", termsToVerify1.at(3).getOperatorConstReference().getOperatorString());
    EXPECT_EQ(TermType::Variable, termsToVerify1.at(4).getTermType());
    EXPECT_EQ("y1", termsToVerify1.at(4).getVariableConstReference().getVariableName());
    EXPECT_EQ(TermType::Operator, termsToVerify1.at(5).getTermType());
    EXPECT_EQ("^", termsToVerify1.at(5).getOperatorConstReference().getOperatorString());
    EXPECT_EQ(TermType::Constant, termsToVerify1.at(6).getTermType());
    EXPECT_DOUBLE_EQ(20.15, termsToVerify1.at(6).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(UtilitiesTest, AddValueTermIfNotEmptyWorks)
{
    Terms termsToVerify1;

    addValueTermIfNotEmpty(termsToVerify1, "5");

    ASSERT_EQ(1u, termsToVerify1.size());
    EXPECT_EQ(TermType::Constant, termsToVerify1.at(0).getTermType());
    EXPECT_DOUBLE_EQ(5, termsToVerify1.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(UtilitiesTest, ConvertValueTermStringToTermWorks)
{
    Term termToVerify1(convertValueTermStringToTerm("5xxx"));
    Term termToVerify2(convertValueTermStringToTerm("x111"));

    EXPECT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(5, termToVerify1.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Variable, termToVerify2.getTermType());
    EXPECT_EQ("x111", termToVerify2.getVariableConstReference().getVariableName());
}

TEST(UtilitiesTest, GetCommonMonomialInMonomialsWorks)
{
    Monomial monomialToVerify1(getGcfMonomialInMonomials({Monomial(2, {{"x", 3}}), Monomial(2, {{"x", 7}})}));
    Monomial monomialToVerify2(getGcfMonomialInMonomials({Monomial(4, {{"x", 3}}), Monomial(8, {{"y", 7}})}));
    Monomial monomialToVerify3(getGcfMonomialInMonomials({Monomial(1, {{"x", 1}}), Monomial(4, {})}));
    Monomial monomialToVerify4(getGcfMonomialInMonomials({Monomial(AlbaNumber(1, 4), {{"x", 1}}), Monomial(5, {})}));
    Monomial monomialToVerify5(getGcfMonomialInMonomials({Monomial(0.33, {{"x", 1}}), Monomial(5, {})}));
    Monomial monomialToVerify6(getGcfMonomialInMonomials({Monomial(6, {}), Monomial(9, {})}));

    Monomial monomialToExpect1(2, {{"x", 3}});
    Monomial monomialToExpect2(4, {});
    Monomial monomialToExpect3(1, {});
    Monomial monomialToExpect4(AlbaNumber(1, 4), {});
    Monomial monomialToExpect5(5, {});
    Monomial monomialToExpect6(3, {});
    EXPECT_EQ(monomialToExpect1, monomialToVerify1);
    EXPECT_EQ(monomialToExpect2, monomialToVerify2);
    EXPECT_EQ(monomialToExpect3, monomialToVerify3);
    EXPECT_EQ(monomialToExpect4, monomialToVerify4);
    EXPECT_EQ(monomialToExpect5, monomialToVerify5);
    EXPECT_EQ(monomialToExpect6, monomialToVerify6);
}



}

}
