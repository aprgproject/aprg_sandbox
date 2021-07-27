#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

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
    Expression expression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    Term expressionTerm(expression);

    PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(expressionTerm));

    EXPECT_FALSE(popOptional.hasContent());
}

}

}
