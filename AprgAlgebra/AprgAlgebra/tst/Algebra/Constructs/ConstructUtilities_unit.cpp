#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(ConstructUtilitiesTest, CreatePolynomialOverPolynomialFromTermIfPossibleWorksForTermThatCanBeConvertedToPolynomial)
{
    Polynomial polynomial{Monomial(3, {{"x", 3}}), Monomial(6, {{"y", 3}})};
    Term polynomialTerm(polynomial);

    PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(polynomialTerm));

    ASSERT_TRUE(popOptional.hasContent());
    PolynomialOverPolynomial const& pop(popOptional.getConstReference());
    EXPECT_EQ(polynomial, pop.getNumerator());
    EXPECT_EQ(createPolynomialFromConstant(1), pop.getDenominator());
}

TEST(ConstructUtilitiesTest, CreatePolynomialOverPolynomialFromTermIfPossibleWorksForExpressionThatHaveMonomialsOnMultiplyAndDivide)
{
    Expression expression(
                createExpressionIfPossible({
                                               Term(Monomial(1, {{"x", 9}})),
                                               Term("*"),
                                               Term(Monomial(2, {{"y", 8}})),
                                               Term("/"),
                                               Term(Monomial(3, {{"z", 7}}))
                                           }));
    Term expressionTerm(expression);

    PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(expressionTerm));

    Polynomial expectedNumerator{Monomial(2, {{"x", 9}, {"y", 8}})};
    Polynomial expectedDenominator{Monomial(3, {{"z", 7}})};
    ASSERT_TRUE(popOptional.hasContent());
    PolynomialOverPolynomial const& pop(popOptional.getConstReference());
    EXPECT_EQ(expectedNumerator, pop.getNumerator());
    EXPECT_EQ(expectedDenominator, pop.getDenominator());
}

TEST(ConstructUtilitiesTest, CreatePolynomialOverPolynomialFromTermIfPossibleWorksForExpressionThatHavePolynomialsOnMultiplyAndDivide)
{
    Expression expression(
                createExpressionIfPossible({
                                               Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}),
                                               Term("*"),
                                               Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}),
                                               Term("/"),
                                               Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(3, {})})
                                           }));
    Term expressionTerm(expression);

    PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(expressionTerm));

    Polynomial expectedNumerator{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})};
    Polynomial expectedDenominator{Monomial(2, {{"x", 1}}), Monomial(3, {})};
    ASSERT_TRUE(popOptional.hasContent());
    PolynomialOverPolynomial const& pop(popOptional.getConstReference());
    EXPECT_EQ(expectedNumerator, pop.getNumerator());
    EXPECT_EQ(expectedDenominator, pop.getDenominator());
}

TEST(ConstructUtilitiesTest, CreatePolynomialOverPolynomialFromTermIfPossibleWorksAsEmptyWhenThereIsNoPolynomial)
{
    Term x("x");
    Expression expression(createExpressionIfPossible({x, Term("^"), x}));
    Term expressionTerm(expression);

    PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(expressionTerm));

    EXPECT_FALSE(popOptional.hasContent());
}

TEST(ConstructUtilitiesTest, CreateTermsOverTermsFromTermWorksForNonExpression)
{
    Term x("x");
    Term nonExpressionTerm(x);

    TermsOverTerms termsOverTerms(createTermsOverTermsFromTerm(nonExpressionTerm));

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(x, numeratorsToVerify.at(0));
    Terms const& denominatorsToVerify(termsOverTerms.getDenominators());
    EXPECT_TRUE(denominatorsToVerify.empty());
}

TEST(ConstructUtilitiesTest, CreateTermsOverTermsFromTermWorksForNonMultiplicationDivisionExpression)
{
    Term x("x");
    Term nonMultiplicationDivisionExpressionTerm(createExpressionIfPossible({x, Term("^"), x}));

    TermsOverTerms termsOverTerms(createTermsOverTermsFromTerm(nonMultiplicationDivisionExpressionTerm));

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(nonMultiplicationDivisionExpressionTerm, numeratorsToVerify.at(0));
    Terms const& denominatorsToVerify(termsOverTerms.getDenominators());
    EXPECT_TRUE(denominatorsToVerify.empty());
}

TEST(ConstructUtilitiesTest, CreateTermsOverTermsFromTermWorksForMultiplicationDivisionExpression)
{
    Term x("x");
    Term y("y");
    Term multiplicationDivisionExpressionTerm(createExpressionIfPossible({x, Term("/"), y}));

    TermsOverTerms termsOverTerms(createTermsOverTermsFromTerm(multiplicationDivisionExpressionTerm));

    Terms numeratorsToVerify(termsOverTerms.getNumerators());
    ASSERT_EQ(1U, numeratorsToVerify.size());
    EXPECT_EQ(x, numeratorsToVerify.at(0));
    Terms const& denominatorsToVerify(termsOverTerms.getDenominators());
    ASSERT_EQ(1U, denominatorsToVerify.size());
    EXPECT_EQ(Term("y"), denominatorsToVerify.at(0));
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForNonMonomialOrExpression)
{
    Term x("x");
    Term nonMonomialOrExpressionTerm(x);

    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(nonMonomialOrExpressionTerm));

    EXPECT_EQ(x, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForMonomialWithSingleVariable)
{
    Term x("x");
    Term monomialTerm(Monomial(1, {{"x", 1.78}}));

    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(monomialTerm));

    EXPECT_EQ(x, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1.78), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForMonomialWithMultipleVariables)
{
    Term monomialTerm(Monomial(1,
    {{"x", AlbaNumber::createFraction(1, 2)},
     {"y", AlbaNumber::createFraction(2, 7)},
     {"z", AlbaNumber::createFraction(9, 5)}}));

    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(monomialTerm));

    Term baseToExpect(Monomial(1,
    {{"x", 35},
     {"y", 20},
     {"z", 126}}));
    EXPECT_EQ(baseToExpect, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber::createFraction(1, 70), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForNonRaiseToPowerExpression)
{
    Term x("x");
    Term y("y");
    Term nonRaiseToPowerExpressionTerm(createExpressionIfPossible({x, Term("+"), y}));

    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(nonRaiseToPowerExpressionTerm));

    Term baseToExpect(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    EXPECT_EQ(baseToExpect, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForRaiseToPowerExpressionWithOneTerm)
{
    Term x("x");
    Expression raiseToPowerExpression(x);
    raiseToPowerExpression.setCommonOperatorLevel(OperatorLevel::RaiseToPower);
    Term raiseToPowerExpressionTerm(raiseToPowerExpression);

    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(raiseToPowerExpressionTerm));

    EXPECT_EQ(x, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForRaiseToPowerExpressionWithTwoTerms)
{
    Term baseTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    Term raiseToPowerExpressionTerm(createExpressionIfPossible({baseTerm, Term("^"), Term(1.79)}));

    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(raiseToPowerExpressionTerm));

    EXPECT_EQ(baseTerm, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1.79), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForRaiseToPowerExpressionWithThreeTerms)
{
    Term baseTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    Term raiseToPowerExpressionTerm(createExpressionIfPossible({baseTerm, Term("^"), Term(1.79), Term("^"), Term("y")}));

    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(raiseToPowerExpressionTerm));

    Term baseToExpect(createExpressionIfPossible({baseTerm, Term("^"), Term("y")}));
    EXPECT_EQ(baseToExpect, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1.79), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromTermWorksForRaiseToPowerExpressionWithMonomialExponent)
{
    Term baseTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    Term exponentTerm(Monomial(2.84, {{"x", 2}, {"y", 3}}));
    Term raiseToPowerExpressionTerm(createExpressionIfPossible({baseTerm, Term("^"), exponentTerm}));

    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(raiseToPowerExpressionTerm));

    Term exponentInBaseToExpect(Monomial(1, {{"x", 2}, {"y", 3}}));
    Term baseToExpect(createExpressionIfPossible({baseTerm, Term("^"), exponentInBaseToExpect}));
    EXPECT_EQ(baseToExpect, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(2.84), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromMonomialWorks)
{
    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromMonomial(Monomial(64, {{"x", 18}, {"y", 12}})));

    Term baseToExpect(Monomial(2, {{"x", 3}, {"y", 2}}));
    EXPECT_EQ(baseToExpect, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(6), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromPolynomialWorks)
{
    TermRaiseToANumber termRaiseToANumber(
                createTermRaiseToANumberFromPolynomial(Polynomial
    {Monomial(1, {{"x", 2}}),
     Monomial(2, {{"x", 1}}),
     Monomial(1, {})}));

    Term baseToExpect(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    EXPECT_EQ(baseToExpect, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(2), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromExpressionWorks_WithAdditionAndSubtractionOperation)
{
    Term x("x");
    Expression additionAndSubtractionExpression(createExpressionIfPossible({Term(abs(x)), Term("+"), Term(100)}));

    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromExpression(additionAndSubtractionExpression));

    Term expectedBase(additionAndSubtractionExpression);
    EXPECT_EQ(expectedBase, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(1), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromExpressionWorks_WithMultiplicationAndDivisionOperation)
{
    Term x("x");
    Monomial numerator(32, {{"x", 5}});
    Polynomial polynomialForDenominator{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    Expression denominator(createExpressionIfPossible({Term(polynomialForDenominator), Term("^"), Term(10)}));
    Expression multiplicationAndDivisionExpression(createExpressionIfPossible({Term(numerator), Term("/"), Term(denominator)}));

    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromExpression(multiplicationAndDivisionExpression));

    Term expectedBase(createExpressionIfPossible({Term(2), Term("*"), x, Term("/"), Term(polynomialForDenominator), Term("^"), Term(2)}));
    EXPECT_EQ(expectedBase, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(5), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromExpressionWorks_WithRaiseToPowerOperation)
{
    Term x("x");
    Expression raiseToPowerExpression(createExpressionIfPossible({Term(abs(x)), Term("^"), Term(100)}));

    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromExpression(raiseToPowerExpression));

    EXPECT_EQ(Term(abs(x)), termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(100), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromExpressionWorks_WithRaiseToPowerOperationAndMultipleExponents)
{
    Term x("x");
    Expression raiseToPowerExpression(createExpressionIfPossible({Term(abs(x)), Term("^"), Term(10), Term("^"), Term(20), Term("^"), Term(Monomial(30, {{"x", 1}}))}));

    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromExpression(raiseToPowerExpression));

    Term expectedBase(createExpressionIfPossible({Term(abs(x)), Term("^"), x}));
    EXPECT_EQ(expectedBase, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(6000), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromExpressionWorks_WithDivisionOperationOnly)
{
    Polynomial polynomial1ForDenominator{Monomial(1, {{"x", 1}}), Monomial(5, {})};
    Polynomial polynomial2ForDenominator{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    Expression denominator(createExpressionIfPossible(
    {Term(polynomial1ForDenominator), Term("^"), Term(2), Term("*"),
     Term(polynomial2ForDenominator), Term("^"), Term(4)}));
    Expression multiplicationAndDivisionExpression(createExpressionIfPossible({Term(1), Term("/"), Term(denominator)}));

    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromExpression(multiplicationAndDivisionExpression));

    Term expectedBase(createExpressionIfPossible(
    {Term(polynomial1ForDenominator), Term("*"), Term(polynomial2ForDenominator), Term("^"), Term(2)}));
    EXPECT_EQ(expectedBase, termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(-2), termRaiseToANumber.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromRaiseToPowerExpressionWorks)
{
    Term x("x");
    Expression raiseToPowerExpression(createExpressionIfPossible({Term(abs(x)), Term("^"), Term(100)}));

    TermRaiseToANumber result;
    createTermRaiseToANumberFromRaiseToPowerExpression(result, raiseToPowerExpression);

    EXPECT_EQ(Term(abs(x)), result.getBase());
    EXPECT_EQ(AlbaNumber(100), result.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToANumberFromMultiplicationAndDivisionExpressionWorks)
{
    Term x("x");
    Monomial numerator(32, {{"x", 5}});
    Polynomial polynomialForDenominator{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    Expression denominator(createExpressionIfPossible({Term(polynomialForDenominator), Term("^"), Term(10)}));
    Expression multiplicationAndDivisionExpression(createExpressionIfPossible({Term(numerator), Term("/"), Term(denominator)}));

    TermRaiseToANumber result;
    createTermRaiseToANumberFromMultiplicationAndDivisionExpression(result, multiplicationAndDivisionExpression);

    Term expectedBase(createExpressionIfPossible({Term(2), Term("*"), x, Term("/"), Term(polynomialForDenominator), Term("^"), Term(2)}));
    EXPECT_EQ(expectedBase, result.getBase());
    EXPECT_EQ(AlbaNumber(5), result.getExponent());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForNonMonomialOrExpression)
{
    Term x("x");
    Term nonMonomialOrExpressionTerm(x);

    TermRaiseToTerms termRaiseToTerms(createTermRaiseToTermsFromTerm(nonMonomialOrExpressionTerm));

    EXPECT_EQ(x, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(1), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForMonomialWithSingleVariable)
{
    Term x("x");
    Term monomialTerm(Monomial(1, {{"x", 1.78}}));

    TermRaiseToTerms termRaiseToTerms(createTermRaiseToTermsFromTerm(monomialTerm));

    EXPECT_EQ(x, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(1.78), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForMonomialWithMultipleVariables)
{
    Term monomialTerm(Monomial(1,
    {{"x", AlbaNumber::createFraction(1, 2)},
     {"y", AlbaNumber::createFraction(2, 7)},
     {"z", AlbaNumber::createFraction(9, 5)}}));

    TermRaiseToTerms termRaiseToTerms(createTermRaiseToTermsFromTerm(monomialTerm));

    Term baseToExpect(Monomial(1,
    {{"x", 35},
     {"y", 20},
     {"z", 126}}));
    EXPECT_EQ(baseToExpect, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 70)), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForNonRaiseToPowerExpression)
{
    Term x("x");
    Term y("y");
    Term nonRaiseToPowerExpressionTerm(createExpressionIfPossible({x, Term("+"), y}));

    TermRaiseToTerms termRaiseToTerms(createTermRaiseToTermsFromTerm(nonRaiseToPowerExpressionTerm));

    Term baseToExpect(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    EXPECT_EQ(baseToExpect, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(1), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForRaiseToPowerExpressionWithOneTerm)
{
    Term x("x");
    Expression raiseToPowerExpression(x);
    raiseToPowerExpression.setCommonOperatorLevel(OperatorLevel::RaiseToPower);
    Term raiseToPowerExpressionTerm(raiseToPowerExpression);

    TermRaiseToTerms termRaiseToTerms(createTermRaiseToTermsFromTerm(raiseToPowerExpressionTerm));

    EXPECT_EQ(x, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(1), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForRaiseToPowerExpressionWithTwoTerms)
{
    Term baseTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    Term raiseToPowerExpressionTerm(createExpressionIfPossible({baseTerm, Term("^"), Term(1.79)}));

    TermRaiseToTerms termRaiseToTerms(createTermRaiseToTermsFromTerm(raiseToPowerExpressionTerm));

    EXPECT_EQ(baseTerm, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(1.79), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForRaiseToPowerExpressionWithThreeTerms)
{
    Term baseTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    Term raiseToPowerExpressionTerm(createExpressionIfPossible({baseTerm, Term("^"), Term(1.79), Term("^"), Term("y")}));

    TermRaiseToTerms termRaiseToTerms(createTermRaiseToTermsFromTerm(raiseToPowerExpressionTerm));

    Term expectedExponent(Monomial(1.79, {{"y", 1}}));
    EXPECT_EQ(baseTerm, termRaiseToTerms.getBase());
    EXPECT_EQ(expectedExponent, termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromTermWorksForRaiseToPowerExpressionWithMonomialExponent)
{
    Term baseTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})});
    Term exponentTerm(Monomial(2.84, {{"x", 2}, {"y", 3}}));
    Term raiseToPowerExpressionTerm(createExpressionIfPossible({baseTerm, Term("^"), exponentTerm}));

    TermRaiseToTerms termRaiseToTerms(createTermRaiseToTermsFromTerm(raiseToPowerExpressionTerm));

    EXPECT_EQ(baseTerm, termRaiseToTerms.getBase());
    EXPECT_EQ(exponentTerm, termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromExpressionWorks_WithAdditionAndSubtractionOperation)
{
    Term x("x");
    Expression additionAndSubtractionExpression(createExpressionIfPossible({Term(abs(x)), Term("+"), Term(100)}));

    TermRaiseToTerms termRaiseToTerms(createTermRaiseToTermsFromExpression(additionAndSubtractionExpression));

    Term expectedBase(additionAndSubtractionExpression);
    EXPECT_EQ(expectedBase, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(1), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromExpressionWorks_WithMultiplicationAndDivisionOperation)
{
    Monomial numerator(32, {{"x", 5}});
    Polynomial polynomialForDenominator{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    Expression denominator(createExpressionIfPossible({Term(polynomialForDenominator), Term("^"), Term(10)}));
    Expression multiplicationAndDivisionExpression(createExpressionIfPossible({Term(numerator), Term("/"), Term(denominator)}));

    TermRaiseToTerms termRaiseToTerms(createTermRaiseToTermsFromExpression(multiplicationAndDivisionExpression));

    Term expectedNumerator(Monomial(2, {{"x", 1}}));
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(14, {{"x", 1}}), Monomial(49, {})});
    Term expectedBase(createExpressionIfPossible({Term(expectedNumerator), Term("/"), Term(expectedDenominator)}));
    EXPECT_EQ(expectedBase, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(5), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromExpressionWorks_WithRaiseToPowerOperation)
{
    Term x("x");
    Expression raiseToPowerExpression(createExpressionIfPossible({Term(abs(x)), Term("^"), Term(100)}));

    TermRaiseToTerms termRaiseToTerms(createTermRaiseToTermsFromExpression(raiseToPowerExpression));

    EXPECT_EQ(Term(abs(x)), termRaiseToTerms.getBase());
    EXPECT_EQ(Term(100), termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromExpressionWorks_WithRaiseToPowerOperationAndMultipleExponents)
{
    Term x("x");
    Expression raiseToPowerExpression(createExpressionIfPossible({Term(abs(x)), Term("^"), Term(10), Term("^"), Term(20), Term("^"), Term(Monomial(30, {{"x", 1}}))}));

    TermRaiseToTerms termRaiseToTerms(createTermRaiseToTermsFromExpression(raiseToPowerExpression));

    Term expectedBase(abs(x));
    Term expectedExponent(Monomial(6000, {{"x", 1}}));
    EXPECT_EQ(expectedBase, termRaiseToTerms.getBase());
    EXPECT_EQ(expectedExponent, termRaiseToTerms.getCombinedExponents());
}

TEST(ConstructUtilitiesTest, CreateTermRaiseToTermsFromExpressionWorks_WithDivisionOperationOnly)
{
    Polynomial polynomial1ForDenominator{Monomial(1, {{"x", 1}}), Monomial(5, {})};
    Polynomial polynomial2ForDenominator{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    Expression denominator(createExpressionIfPossible(
    {Term(polynomial1ForDenominator), Term("^"), Term(2), Term("*"),
     Term(polynomial2ForDenominator), Term("^"), Term(4)}));
    Expression multiplicationAndDivisionExpression(createExpressionIfPossible({Term(1), Term("/"), Term(denominator)}));

    TermRaiseToTerms termRaiseToTerms(createTermRaiseToTermsFromExpression(multiplicationAndDivisionExpression));

    Term expectedBase(Polynomial{Monomial(1, {{"x", 3}}), Monomial(19, {{"x", 2}}), Monomial(119, {{"x", 1}}), Monomial(245, {})});
    EXPECT_EQ(expectedBase, termRaiseToTerms.getBase());
    EXPECT_EQ(Term(-2), termRaiseToTerms.getCombinedExponents());
}

}

}
