#include <PolynomialOverPolynomial.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(PolynomialOverPolynomialTest, ConstructionWorks)
{
    PolynomialOverPolynomial(Polynomial(), Polynomial());
    PolynomialOverPolynomial((Polynomial{Monomial(10, {})}), (Polynomial{Monomial(100, {})}));
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnConvertingFractionCoefficientsToInteger)
{
    Polynomial numerator{Monomial(AlbaNumber(1, 2), {{"x", 1}}), Monomial(AlbaNumber(1, 3), {{"y", 1}})};
    Polynomial denominator{Monomial(AlbaNumber(1, 5), {{"x", 1}}), Monomial(AlbaNumber(1, 10), {{"y", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    EXPECT_EQ((Polynomial{Monomial(15, {{"x", 1}}), Monomial(10, {{"y", 1}})}), polynomialOverPolynomial.getNumerator());
    EXPECT_EQ((Polynomial{Monomial(6, {{"x", 1}}), Monomial(3, {{"y", 1}})}), polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnRemovingCommonFactorInCoefficients)
{
    Polynomial numerator{Monomial(2, {{"x", 1}}), Monomial(2, {{"y", 1}})};
    Polynomial denominator{Monomial(2, {{"y", 1}}), Monomial(2, {{"z", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    EXPECT_EQ((Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})}), polynomialOverPolynomial.getNumerator());
    EXPECT_EQ((Polynomial{Monomial(1, {{"y", 1}}), Monomial(1, {{"z", 1}})}), polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnConvertingNegativeExponentsToPositive)
{
    Polynomial numerator{Monomial(1, {{"x", 1}, {"y", -1}}), Monomial(2, {{"x", -1}, {"y", 1}})};
    Polynomial denominator{Monomial(3, {{"y", 1}}), Monomial(4, {{"z", -1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    EXPECT_EQ((Polynomial{Monomial(1, {{"x", 2}, {"z", 1}}), Monomial(2, {{"y", 2}, {"z", 1}})}), polynomialOverPolynomial.getNumerator());
    EXPECT_EQ((Polynomial{Monomial(3, {{"x", 1}, {"y", 2}, {"z", 1}}), Monomial(4, {{"x", 1}, {"y", 1}})}), polynomialOverPolynomial.getDenominator());
}

}

}
