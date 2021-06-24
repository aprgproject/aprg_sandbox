#include <Equation/Constructs/AdditionAndSubtractionOfExpressions.hpp>
#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

TEST(AdditionAndSubtractionOfExpressionsTest, ConstructionWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;

    EXPECT_TRUE(additionAndSubtraction.getExpressions().empty());
    EXPECT_TRUE(additionAndSubtraction.getAssociations().empty());
}

TEST(AdditionAndSubtractionOfExpressionsTest, GetExpressionsWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression1(createExpressionIfPossible({Term("x")}));
    Expression expression2(createExpressionIfPossible({Term("y")}));
    additionAndSubtraction.putAsAddOrSubtraction(expression1, TermAssociationType::Positive);
    additionAndSubtraction.putAsAddOrSubtraction(expression2, TermAssociationType::Negative);

    Expressions expressions(additionAndSubtraction.getExpressions());

    ASSERT_EQ(2u, expressions.size());
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

    TermAssociationTypes associations(additionAndSubtraction.getAssociations());

    ASSERT_EQ(2u, associations.size());
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

    EXPECT_EQ(0u, additionAndSubtraction1.getSize());
    EXPECT_EQ(2u, additionAndSubtraction2.getSize());
}

TEST(AdditionAndSubtractionOfExpressionsTest, GetAsTermsWithDetailsWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression1(createExpressionIfPossible({Term("x")}));
    Expression expression2(createExpressionIfPossible({Term("y")}));
    additionAndSubtraction.putAsAddOrSubtraction(expression1, TermAssociationType::Positive);
    additionAndSubtraction.putAsAddOrSubtraction(expression2, TermAssociationType::Negative);

    TermsWithDetails termsWithDetails(additionAndSubtraction.getAsTermsWithDetails());

    ASSERT_EQ(2u, termsWithDetails.size());
    Term const& term1(getTermConstReferenceFromSharedPointer(termsWithDetails.at(0).baseTermSharedPointer));
    EXPECT_EQ(TermType::Variable, term1.getTermType());
    EXPECT_EQ("x", term1.getVariableConstReference().getVariableName());
    EXPECT_EQ(TermAssociationType::Positive, termsWithDetails.at(0).association);
    Term const& term2(getTermConstReferenceFromSharedPointer(termsWithDetails.at(1).baseTermSharedPointer));
    EXPECT_EQ(TermType::Variable, term2.getTermType());
    EXPECT_EQ("y", term2.getVariableConstReference().getVariableName());
    EXPECT_EQ(TermAssociationType::Negative, termsWithDetails.at(1).association);
}

TEST(AdditionAndSubtractionOfExpressionsTest, PutAsAdditionWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression(createExpressionIfPossible({Term("x")}));

    additionAndSubtraction.putAsAddition(expression);

    Expressions expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1u, expressions.size());
    EXPECT_EQ(expression, expressions.at(0));
    TermAssociationTypes associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1u, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
}

TEST(AdditionAndSubtractionOfExpressionsTest, PutAsSubtractionWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression(createExpressionIfPossible({Term("x")}));

    additionAndSubtraction.putAsSubtraction(expression);

    Expressions expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1u, expressions.size());
    EXPECT_EQ(expression, expressions.at(0));
    TermAssociationTypes associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1u, associations.size());
    EXPECT_EQ(TermAssociationType::Negative, associations.at(0));
}

TEST(AdditionAndSubtractionOfExpressionsTest, PutAsAddOrSubtractionWorks)
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    Expression expression(createExpressionIfPossible({Term("x")}));

    additionAndSubtraction.putAsAddOrSubtraction(expression, TermAssociationType::Negative);

    Expressions expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1u, expressions.size());
    EXPECT_EQ(expression, expressions.at(0));
    TermAssociationTypes associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1u, associations.size());
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

    Expressions expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2u, expressions.size());
    EXPECT_EQ(expression1, expressions.at(0));
    EXPECT_EQ(expression2, expressions.at(1));
    TermAssociationTypes associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2u, associations.size());
    EXPECT_EQ(TermAssociationType::Negative, associations.at(0));
    EXPECT_EQ(TermAssociationType::Positive, associations.at(1));
}

TEST(AdditionAndSubtractionOfExpressionsTest, CreateExpressionIfPossibleWorksOnAddingAndSubtractingRaiseToPowerExpressions)
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
    Expressions expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1u, expressions.size());
    EXPECT_EQ(expressionToExpect, expressions.at(0));
    TermAssociationTypes associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1u, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
}

TEST(AdditionAndSubtractionOfExpressionsTest, CreateExpressionIfPossibleWorksOnAddingAndSubtractingMultipleRaiseToPowerExpressions)
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
    Expressions expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2u, expressions.size());
    EXPECT_EQ(expressionToExpect1, expressions.at(0));
    EXPECT_EQ(expressionToExpect2, expressions.at(1));
    TermAssociationTypes associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2u, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
    EXPECT_EQ(TermAssociationType::Positive, associations.at(1));
}

TEST(AdditionAndSubtractionOfExpressionsTest, CreateExpressionIfPossibleWorksOnAddingAndSubtractingNonSortedRaiseToPowerExpressions)
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
    Expressions expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(1u, expressions.size());
    EXPECT_EQ(expressionToExpect, expressions.at(0));
    TermAssociationTypes associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1u, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
}

TEST(AdditionAndSubtractionOfExpressionsTest, CreateExpressionIfPossibleWorksOnAddingAndSubtractingRaiseToPowerExpressionsThatCannotBeAdded)
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
    Expressions expressions(additionAndSubtraction.getExpressions());
    ASSERT_EQ(2u, expressions.size());
    EXPECT_EQ(expressionToExpect1, expressions.at(0));
    EXPECT_EQ(expressionToExpect2, expressions.at(1));
    TermAssociationTypes associations(additionAndSubtraction.getAssociations());
    ASSERT_EQ(2u, associations.size());
    EXPECT_EQ(TermAssociationType::Positive, associations.at(0));
    EXPECT_EQ(TermAssociationType::Positive, associations.at(1));
}

}

}
