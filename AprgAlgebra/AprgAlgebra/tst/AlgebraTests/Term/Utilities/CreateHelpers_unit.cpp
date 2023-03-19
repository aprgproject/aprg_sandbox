#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(CreateHelpersTest, CreateMonomialFromNumberWorks)
{
    EXPECT_EQ(Monomial(5648, {}), createMonomialFromNumber(5648));
}

TEST(CreateHelpersTest, CreateMonomialFromVariableWorks)
{
    EXPECT_EQ(Monomial(1, {{"weight", 1}}), createMonomialFromVariable(Variable("weight")));
}

TEST(CreateHelpersTest, CreateMonomialIfPossibleWorks)
{
    EXPECT_EQ(Monomial(0, {}), createMonomialIfPossible(Term{}));
    EXPECT_EQ(Monomial(42, {}), createMonomialIfPossible(42));
    EXPECT_EQ(Monomial(1, {{"weight", 1}}), createMonomialIfPossible("weight"));
    EXPECT_EQ(Monomial(0, {}), createMonomialIfPossible("+"));
    EXPECT_EQ(Monomial(-1.5, {{"r", -3.75}}), createMonomialIfPossible(Monomial(-1.5, {{"r", -3.75}})));
    EXPECT_EQ(Monomial(0, {}), createMonomialIfPossible(Polynomial{Monomial(3, {}), Monomial(-1.5, {{"distance", -3.75}, {"power", 4.5}})}));
    EXPECT_EQ(Monomial(0, {}), createMonomialIfPossible(createExpressionIfPossible({5, "+", "interest"})));
}

TEST(CreateHelpersTest, CreatePolynomialFromNumberWorks)
{
    EXPECT_EQ(Polynomial{Monomial(5648, {})}, createPolynomialFromNumber(5648));
}

TEST(CreateHelpersTest, CreatePolynomialFromVariableWorks)
{
    EXPECT_EQ(Polynomial{Monomial(1, {{"weight", 1}})}, createPolynomialFromVariable(Variable("weight")));
}

TEST(CreateHelpersTest, CreatePolynomialFromMonomialWorks)
{
    EXPECT_EQ(Polynomial{Monomial(2, {{"weight", 3}})}, createPolynomialFromMonomial(Monomial(2, {{"weight", 3}})));
}

TEST(CreateHelpersTest, CreatePolynomialIfPossibleWorks)
{
    EXPECT_EQ((Polynomial{}), createPolynomialIfPossible(Term{}));
    EXPECT_EQ((Polynomial{Monomial(97, {})}), createPolynomialIfPossible(97));
    EXPECT_EQ((Polynomial{Monomial(1, {{"weight", 1}})}), createPolynomialIfPossible("weight"));
    EXPECT_EQ((Polynomial{Monomial(24, {{"i", 5}})}), createPolynomialIfPossible(Monomial(24, {{"i", 5}})));
    EXPECT_EQ((Polynomial{Monomial(39, {{"r", 7}})}), createPolynomialIfPossible(Polynomial{Monomial(39, {{"r", 7}})}));
    EXPECT_EQ((Polynomial{}), createPolynomialIfPossible(createExpressionIfPossible({5, "+", "interest"})));
}

TEST(CreateHelpersTest, CreateExpressionInExpressionWorks)
{
    Expression expression1(createExpressionIfPossible({254}));
    Expression expression2(createExpressionIfPossible({4752}));

    Expression expressionToVerify1(createExpressionInAnExpression(expression1));
    Expression expressionToVerify2(createExpressionInAnExpression(createExpressionInAnExpression(expression2)));

    Expression expressionToExpect1(getBaseTermConstReferenceFromTerm(expression1));
    Expression expressionToExpect2(getBaseTermConstReferenceFromTerm(Expression(Term(expression2))));
    EXPECT_EQ(expressionToExpect1, expressionToVerify1);
    EXPECT_EQ(expressionToExpect2, expressionToVerify2);
}

TEST(CreateHelpersTest, CreateAndWrapExpressionFromATermWorks)
{
    Expression expression1(createExpressionIfPossible({254}));
    Expression expression2(createExpressionIfPossible({4752}));

    Expression expressionToVerify1(createAndWrapExpressionFromATerm(expression1));
    Expression expressionToVerify2(createAndWrapExpressionFromATerm(4752));

    Expression expressionToExpect1(getBaseTermConstReferenceFromTerm(expression1));
    EXPECT_EQ(expressionToExpect1, expressionToVerify1);
    EXPECT_EQ(expression2, expressionToVerify2);
}

TEST(CreateHelpersTest, CreateOrCopyExpressionFromATermWorks)
{
    Expression expression1(createExpressionIfPossible({254}));
    Expression expression2(createExpressionIfPossible({4752}));

    Expression expressionToVerify1(createOrCopyExpressionFromATerm(expression1));
    Expression expressionToVerify2(createOrCopyExpressionFromATerm(4752));

    EXPECT_EQ(expression1, expressionToVerify1);
    EXPECT_EQ(expression2, expressionToVerify2);
}

TEST(CreateHelpersTest, CreateExpressionIfPossibleWorks)
{
    Expression expressionToTest(createExpressionIfPossible({10, "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));

    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1(getTermConstReferenceFromUniquePointer(termsToVerify.at(0).baseTermPointer));
    EXPECT_EQ(Term(10), termToVerify1);
    EXPECT_EQ(TermAssociationType::Negative, termsToVerify.at(1).association);
    Term const& termToVerify2(getTermConstReferenceFromUniquePointer(termsToVerify.at(1).baseTermPointer));
    EXPECT_EQ(Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}), termToVerify2);
}

TEST(CreateHelpersTest, CreateExpressionIfPossibleDoesNotSimplifyExpressionInAExpression)
{
    Expression expression1(createExpressionIfPossible({88}));
    Expression expression2(createExpressionInAnExpression(expression1));
    Expression expression3(createExpressionInAnExpression(expression2));

    Expression expressionToTest1(createExpressionIfPossible({expression3}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest1.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify1(expressionToTest1.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify1.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify1.at(0).association);
    Term const& termToVerify1(getTermConstReferenceFromUniquePointer(termsToVerify1.at(0).baseTermPointer));
    ASSERT_TRUE(termToVerify1.isExpression());
    Expression const& expressionToTest2(termToVerify1.getExpressionConstReference());
    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest2.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify2(expressionToTest2.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify2.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify2.at(0).association);
    Term const& termToVerify2(getTermConstReferenceFromUniquePointer(termsToVerify2.at(0).baseTermPointer));
    ASSERT_TRUE(termToVerify2.isExpression());
    Expression const& expressionToTest3(termToVerify2.getExpressionConstReference());
    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest3.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify3(expressionToTest3.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify3.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify3.at(0).association);
    Term const& termToVerify3(getTermConstReferenceFromUniquePointer(termsToVerify3.at(0).baseTermPointer));
    ASSERT_TRUE(termToVerify3.isConstant());
    EXPECT_EQ(Constant(88), termToVerify3.getConstantConstReference());
}

TEST(CreateHelpersTest, CreateExpressionIfPossibleDoesNotSimplify)
{
    Expression expressionToTest(createExpressionIfPossible({7.625, "+", 2.375}));

    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1(getTermConstReferenceFromUniquePointer(termsToVerify.at(0).baseTermPointer));
    EXPECT_EQ(Term(7.625), termToVerify1);
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(1).association);
    Term const& termToVerify2(getTermConstReferenceFromUniquePointer(termsToVerify.at(1).baseTermPointer));
    EXPECT_EQ(Term(2.375), termToVerify2);
}

TEST(CreateHelpersTest, CreateExpressionIfPossibleReturnsEmptyIfListOfTermsAreWrong)
{
    Expression expressionToTest(createExpressionIfPossible({7.625, "+", "/", 2.375}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify.empty());
}

TEST(CreateHelpersTest, CreateSimplifiedExpressionIfPossibleWorks)
{
    Expression expressionToTest(createSimplifiedExpressionIfPossible({7.625, "+", 2.375}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1(getTermConstReferenceFromUniquePointer(termsToVerify.at(0).baseTermPointer));
    EXPECT_EQ(Term(10), termToVerify1);
}

TEST(CreateHelpersTest, CreateSimplifiedExpressionIfPossibleReturnsEmptyIfListOfTermsAreWrong)
{
    Expression expressionToTest(createSimplifiedExpressionIfPossible({"+", "+", "+"}));

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify(expressionToTest.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify.empty());
}

TEST(CreateHelpersTest, CreateFunctionWithEmptyInputExpressionWorks)
{
    Function absoluteValueFunction(createFunctionWithEmptyInputExpression("abs"));

    EXPECT_EQ("abs", absoluteValueFunction.getFunctionName());
    EXPECT_TRUE(getTermConstReferenceFromBaseTerm(absoluteValueFunction.getInputTermConstReference()).isEmpty());
}

TEST(CreateHelpersTest, CreateFunctionInAnFunctionWorks)
{
    Function absFunction(Functions::abs(-5));
    Function absInAbsFunction(Functions::abs(absFunction));
    Function absInAbsInAbsFunction(Functions::abs(absInAbsFunction));

    Function functionToVerify1(createFunctionInAnFunction(absFunction));
    Function functionToVerify2(createFunctionInAnFunction(absInAbsFunction));

    EXPECT_EQ(absInAbsFunction, functionToVerify1);
    EXPECT_EQ(absInAbsInAbsFunction, functionToVerify2);
}

TEST(CreateHelpersTest, CreateTermWithAdditionAndSubtractionTermsWithDetailsWorksWithASingleTerm)
{
    TermsWithDetails termsWithDetails{{Term("x"), TermAssociationType::Positive}};

    Term termToExpect(createTermWithAdditionAndSubtractionTermsWithDetails(termsWithDetails));

    Term termToVerify("x");
    EXPECT_EQ(termToVerify, termToExpect);
}

TEST(CreateHelpersTest, CreateTermWithAdditionAndSubtractionTermsWithDetailsWorksWithMultipleTerms)
{
    TermsWithDetails termsWithDetails
    {{Term("x"), TermAssociationType::Positive},
    {Term("y"), TermAssociationType::Negative},
    {Term("z"), TermAssociationType::Positive}};

    Term termToExpect(createTermWithAdditionAndSubtractionTermsWithDetails(termsWithDetails));

    Term termToVerify(createExpressionIfPossible({"x", "-", "y", "+", "z"}));
    EXPECT_EQ(termToVerify, termToExpect);
}

TEST(CreateHelpersTest, CreateTermWithMultiplicationAndDivisionTermsWithDetailsWorksWithASingleTerm)
{
    TermsWithDetails termsWithDetails{{Term("x"), TermAssociationType::Positive}};

    Term termToExpect(createTermWithMultiplicationAndDivisionTermsWithDetails(termsWithDetails));

    Term termToVerify("x");
    EXPECT_EQ(termToVerify, termToExpect);
}

TEST(CreateHelpersTest, CreateTermWithMultiplicationAndDivisionTermsWithDetailsWorksWithMultipleTerms)
{
    TermsWithDetails termsWithDetails
    {{Term("x"), TermAssociationType::Positive},
    {Term("y"), TermAssociationType::Negative},
    {Term("z"), TermAssociationType::Positive}};

    Term termToExpect(createTermWithMultiplicationAndDivisionTermsWithDetails(termsWithDetails));

    Term termToVerify(createExpressionIfPossible({"x", "/", "y", "*", "z"}));
    EXPECT_EQ(termToVerify, termToExpect);
}

TEST(CreateHelpersTest, CreateTermWithRaiseToPowerTermsWithDetailsWorksWithASingleTerm)
{
    TermsWithDetails termsWithDetails{{Term("x"), TermAssociationType::Positive}};

    Term termToExpect(createTermWithRaiseToPowerTermsWithDetails(termsWithDetails));

    Term termToVerify("x");
    EXPECT_EQ(termToVerify, termToExpect);
}

TEST(CreateHelpersTest, CreateTermWithRaiseToPowerTermsWithDetailsWorksWithMultipleTerms)
{
    TermsWithDetails termsWithDetails
    {{Term("x"), TermAssociationType::Positive},
    {Term("y"), TermAssociationType::Positive},
    {Term("z"), TermAssociationType::Positive}};

    Term termToExpect(createTermWithRaiseToPowerTermsWithDetails(termsWithDetails));

    Term termToVerify(createExpressionIfPossible({"x", "^", "y", "^", "z"}));
    EXPECT_EQ(termToVerify, termToExpect);
}

}

}
