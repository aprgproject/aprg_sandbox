#include <Algebra/Constructs/AdditionAndSubtractionOfExpressions.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(AdditionAndSubtractionOfExpressionsTest, DefaultConstructionWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;

    EXPECT_TRUE(additionAndSubtraction.getExpressions().empty());
    EXPECT_TRUE(additionAndSubtraction.getAssociations().empty());
}

TEST(AdditionAndSubtractionOfExpressionsTest, TermsWithDetailsConstructionWorks)
{
    Expression expression1(createExpressionIfPossible({Term("x")}));
    Expression expression2(createExpressionIfPossible({Term("y")}));
    TermWithDetails termWithDetails1(Term(expression1), TermAssociationType::Negative);
    TermWithDetails termWithDetails2(Term(expression2), TermAssociationType::Positive);
    TermsWithDetails termsWithDetails{termWithDetails1, termWithDetails2};
    AdditionAndSubtractionOfExpressions additionAndSubtraction(termsWithDetails);

    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(expression1, expressions.at(0));
    EXPECT_EQ(expression2, expressions.at(1));
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Negative, associations.at(0));
    EXPECT_EQ(TermAssociationType::Positive, associations.at(1));
}

TEST(AdditionAndSubtractionOfExpressionsTest, GetExpressionsWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression1(createExpressionIfPossible({Term("x")}));
    Expression expression2(createExpressionIfPossible({Term("y")}));
    additionAndSubtraction.putAsAddOrSubtraction(expression1, TermAssociationType::Positive);
    additionAndSubtraction.putAsAddOrSubtraction(expression2, TermAssociationType::Negative);

    Expressions const& expressions(additionAndSubtraction.getExpressions());

    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(expression1, expressions.at(0));
    EXPECT_EQ(expression2, expressions.at(1));
}

TEST(AdditionAndSubtractionOfExpressionsTest, GetAssociationsWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression1(createExpressionIfPossible({Term("x")}));
    Expression expression2(createExpressionIfPossible({Term("y")}));
    additionAndSubtraction.putAsAddOrSubtraction(expression1, TermAssociationType::Positive);
    additionAndSubtraction.putAsAddOrSubtraction(expression2, TermAssociationType::Negative);

    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());

    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
    EXPECT_EQ(TermAssociationType::Negative, associations.at(1));
}

TEST(AdditionAndSubtractionOfExpressionsTest, GetSizeWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction1;
    AdditionAndSubtractionOfExpressions additionAndSubtraction2;
    Expression expression1(createExpressionIfPossible({Term("x")}));
    Expression expression2(createExpressionIfPossible({Term("y")}));
    additionAndSubtraction2.putAsAddOrSubtraction(expression1, TermAssociationType::Positive);
    additionAndSubtraction2.putAsAddOrSubtraction(expression2, TermAssociationType::Negative);

    EXPECT_EQ(0U, additionAndSubtraction1.getSize());
    EXPECT_EQ(2U, additionAndSubtraction2.getSize());
}

TEST(AdditionAndSubtractionOfExpressionsTest, GetAsTermsWithDetailsWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression1(createExpressionIfPossible({Term("x")}));
    Expression expression2(createExpressionIfPossible({Term("y")}));
    additionAndSubtraction.putAsAddOrSubtraction(expression1, TermAssociationType::Positive);
    additionAndSubtraction.putAsAddOrSubtraction(expression2, TermAssociationType::Negative);

    TermsWithDetails termsWithDetails(additionAndSubtraction.getAsTermsWithDetails());

    ASSERT_EQ(2U, termsWithDetails.size());
    Term const& term1(getTermConstReferenceFromSharedPointer(termsWithDetails.at(0).baseTermSharedPointer));
    ASSERT_EQ(TermType::Variable, term1.getTermType());
    EXPECT_EQ("x", term1.getVariableConstReference().getVariableName());
    EXPECT_EQ(TermAssociationType::Positive, termsWithDetails.at(0).association);
    Term const& term2(getTermConstReferenceFromSharedPointer(termsWithDetails.at(1).baseTermSharedPointer));
    ASSERT_EQ(TermType::Variable, term2.getTermType());
    EXPECT_EQ("y", term2.getVariableConstReference().getVariableName());
    EXPECT_EQ(TermAssociationType::Negative, termsWithDetails.at(1).association);
}

TEST(AdditionAndSubtractionOfExpressionsTest, PutAsAdditionWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression(createExpressionIfPossible({Term("x")}));

    additionAndSubtraction.putAsAddition(expression);

    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1U, expressions.size());
    EXPECT_EQ(expression, expressions.at(0));
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
}

TEST(AdditionAndSubtractionOfExpressionsTest, PutAsSubtractionWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression(createExpressionIfPossible({Term("x")}));

    additionAndSubtraction.putAsSubtraction(expression);

    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1U, expressions.size());
    EXPECT_EQ(expression, expressions.at(0));
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, associations.size());
    EXPECT_EQ(TermAssociationType::Negative, associations.at(0));
}

TEST(AdditionAndSubtractionOfExpressionsTest, PutAsAddOrSubtractionWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression(createExpressionIfPossible({Term("x")}));

    additionAndSubtraction.putAsAddOrSubtraction(expression, TermAssociationType::Negative);

    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1U, expressions.size());
    EXPECT_EQ(expression, expressions.at(0));
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, associations.size());
    EXPECT_EQ(TermAssociationType::Negative, associations.at(0));
}

TEST(AdditionAndSubtractionOfExpressionsTest, PutTermsWithDetailsWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression1(createExpressionIfPossible({Term("x")}));
    Expression expression2(createExpressionIfPossible({Term("y")}));
    TermWithDetails termWithDetails1(Term(expression1), TermAssociationType::Negative);
    TermWithDetails termWithDetails2(Term(expression2), TermAssociationType::Positive);
    TermsWithDetails termsWithDetails{termWithDetails1, termWithDetails2};

    additionAndSubtraction.putTermsWithDetails(termsWithDetails);

    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(expression1, expressions.at(0));
    EXPECT_EQ(expression2, expressions.at(1));
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Negative, associations.at(0));
    EXPECT_EQ(TermAssociationType::Positive, associations.at(1));
}

TEST(AdditionAndSubtractionOfExpressionsTest, CombineExpressionIfPossibleWorksOnAddingAndSubtractingRaiseToPowerExpressions)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression1(createExpressionIfPossible({Term(5), Term("*"), Term("y"), Term("^"), Term("y")}));
    Expression expression2(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression expression3(createExpressionIfPossible({Term(3), Term("*"), Term("y"), Term("^"), Term("y")}));
    additionAndSubtraction.putAsAddition(expression1);
    additionAndSubtraction.putAsAddition(expression2);
    additionAndSubtraction.putAsSubtraction(expression3);

    additionAndSubtraction.combineExpressionsIfPossible();

    Expression subExpression(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression expressionToExpect(createExpressionIfPossible({Term(3), Term("*"), Term(subExpression)}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1U, expressions.size());
    EXPECT_EQ(expressionToExpect, expressions.at(0));
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
}

TEST(AdditionAndSubtractionOfExpressionsTest, CombineExpressionIfPossibleWorksOnAddingAndSubtractingMultipleRaiseToPowerExpressions)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression1(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));
    Expression expression2(createExpressionIfPossible({Term(2), Term("*"), Term("y"), Term("^"), Term("y")}));
    Expression expression3(createExpressionIfPossible({Term(3), Term("*"), Term("x"), Term("^"), Term("y")}));
    Expression expression4(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression expression5(createExpressionIfPossible({Term(4), Term("*"), Term("x"), Term("^"), Term("y")}));
    Expression expression6(createExpressionIfPossible({Term(5), Term("*"), Term("y"), Term("^"), Term("y")}));
    additionAndSubtraction.putAsAddition(expression1);
    additionAndSubtraction.putAsSubtraction(expression2);
    additionAndSubtraction.putAsSubtraction(expression3);
    additionAndSubtraction.putAsAddition(expression4);
    additionAndSubtraction.putAsAddition(expression5);
    additionAndSubtraction.putAsAddition(expression6);

    additionAndSubtraction.combineExpressionsIfPossible();

    Expression subExpression1(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term(2), Term("*"), Term(subExpression1)}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(4), Term("*"), Term(subExpression2)}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(expressionToExpect1, expressions.at(0));
    EXPECT_EQ(expressionToExpect2, expressions.at(1));
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
    EXPECT_EQ(TermAssociationType::Positive, associations.at(1));
}

TEST(AdditionAndSubtractionOfExpressionsTest, CombineExpressionIfPossibleWorksOnAddingAndSubtractingNonSortedRaiseToPowerExpressions)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression1(createExpressionIfPossible({Term(100), Term("*"), Term("y"), Term("^"), Term("y"), Term("*"), Term("x"), Term("^"), Term("x")}));
    Expression expression2(createExpressionIfPossible({Term(10), Term("*"), Term("x"), Term("^"), Term("x"), Term("*"), Term("y"), Term("^"), Term("y")}));
    additionAndSubtraction.putAsAddition(expression1);
    additionAndSubtraction.putAsSubtraction(expression2);

    additionAndSubtraction.combineExpressionsIfPossible();

    Expression subExpression1(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    Expression subExpression2(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression subExpression3(createExpressionIfPossible({Term(subExpression1), Term("*"), Term(subExpression2)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(90), Term("*"), Term(subExpression3)}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1U, expressions.size());
    EXPECT_EQ(expressionToExpect, expressions.at(0));
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
}

TEST(AdditionAndSubtractionOfExpressionsTest, CombineExpressionIfPossibleWorksOnAddingAndSubtractingRaiseToPowerExpressionsThatCannotBeAdded)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression1(createExpressionIfPossible({Term(10), Term("*"), Term("y"), Term("^"), Term("y")}));
    Expression expression2(createExpressionIfPossible({Term("x"), Term("*"), Term("y"), Term("^"), Term("y")}));
    Expression expression3(createExpressionIfPossible({Term(8), Term("*"), Term("y"), Term("^"), Term("y")}));
    Expression expression4(createExpressionIfPossible({Term(6), Term("*"), Term("x"), Term("*"), Term("y"), Term("^"), Term("y")}));
    additionAndSubtraction.putAsAddition(expression1);
    additionAndSubtraction.putAsAddition(expression2);
    additionAndSubtraction.putAsSubtraction(expression3);
    additionAndSubtraction.putAsSubtraction(expression4);

    additionAndSubtraction.combineExpressionsIfPossible();

    Expression subExpression1(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression expressionToExpect1(createExpressionIfPossible({Term(2), Term("*"), Term(subExpression1)}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(Monomial(-5, {{"x", 1}})), Term("*"), Term(subExpression1)}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(expressionToExpect1, expressions.at(0));
    EXPECT_EQ(expressionToExpect2, expressions.at(1));
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
    EXPECT_EQ(TermAssociationType::Positive, associations.at(1));
}

TEST(AdditionAndSubtractionOfExpressionsTest, CombineExpressionIfPossibleWorksAndSquareRootExpressionAreAddedCorrectly)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression squareRootOfXPlusOne(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    additionAndSubtraction.putAsAddition(squareRootOfXPlusOne);
    additionAndSubtraction.putAsAddition(squareRootOfXPlusOne);

    additionAndSubtraction.combineExpressionsIfPossible();

    Expression expressionToExpect(createExpressionIfPossible({Term(2), Term("*"), Term(squareRootOfXPlusOne)}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1U, expressions.size());
    EXPECT_EQ(expressionToExpect, expressions.at(0));
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
}

TEST(AdditionAndSubtractionOfExpressionsTest, CombineExpressionIfPossibleWorksWithNegativeTermWithTrigonometricFunctions)
{
    Term x("x");
    Expression positiveCosX(createExpressionIfPossible({cos(x)}));
    Expression negativeSinX(createExpressionIfPossible({Term(-1), Term("*"), sin(x)}));
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    additionAndSubtraction.putAsAddition(positiveCosX);
    additionAndSubtraction.putAsAddition(negativeSinX);

    additionAndSubtraction.combineExpressionsIfPossible();

    Expression cosX(createExpressionIfPossible({cos(x)}));
    Expression sinX(createExpressionIfPossible({sin(x)}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(cosX, expressions.at(0));
    EXPECT_EQ(sinX, expressions.at(1));
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
    EXPECT_EQ(TermAssociationType::Negative, associations.at(1));
}

TEST(AdditionAndSubtractionOfExpressionsTest, CombineExpressionIfPossibleWorksWithEToTheXWithTrigonometricEquations)
{
    Term x("x");
    Term eToTheX(createExpressionIfPossible({getEAsTerm(), Term("^"), x}));
    Term eToTheXTimesSinX(createExpressionIfPossible({eToTheX, Term("*"), Term(sin(x))}));
    Term eToTheXTimesCosX(createExpressionIfPossible({eToTheX, Term("*"), Term(cos(x))}));
    Term eToTheXTimesSinXTimes2(createExpressionIfPossible({Term(2), Term("*"), eToTheXTimesSinX}));
    Term eToTheXTimesCosXTimes2(createExpressionIfPossible({Term(2), Term("*"), eToTheXTimesCosX}));
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    additionAndSubtraction.putAsAddition(eToTheXTimesSinXTimes2);
    additionAndSubtraction.putAsSubtraction(eToTheXTimesCosXTimes2);
    additionAndSubtraction.putAsSubtraction(eToTheXTimesSinX);
    additionAndSubtraction.putAsAddition(eToTheXTimesCosX);

    additionAndSubtraction.combineExpressionsIfPossible();

    Term negativeEToTheXTimesCosX(createExpressionIfPossible({Term(-1), Term("*"), eToTheXTimesCosX}));
    Expressions const& expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2U, expressions.size());
    EXPECT_EQ(eToTheXTimesSinX, expressions.at(0));
    EXPECT_EQ(negativeEToTheXTimesCosX, expressions.at(1));
    TermAssociationTypes const& associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2U, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
    EXPECT_EQ(TermAssociationType::Positive, associations.at(1));
}

}

}
