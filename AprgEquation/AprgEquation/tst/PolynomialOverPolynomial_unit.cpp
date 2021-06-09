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

TEST(PolynomialOverPolynomialTest, SimplifyAndDivideWithNoRemainder)
{
    Polynomial numerator{Monomial(3, {{"x", 3}}), Monomial(-4, {{"x", 2}, {"y", 1}}), Monomial(5, {{"x", 1}, {"y", 2}}), Monomial(6, {{"y", 3}})};
    Polynomial denominator{Monomial(1, {{"x", 2}}), Monomial(-2, {{"x", 1}, {"y", 1}}), Monomial(3, {{"y", 2}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(polynomialOverPolynomial.simplifyAndDivide());

    EXPECT_EQ((Polynomial{Monomial(3, {{"x", 1}}), Monomial(2, {{"y", 1}})}), quotientAndRemainder.quotient);
    EXPECT_EQ((Polynomial{}), quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, SimplifyAndDivideWithRemainder)
{
    Polynomial numerator{Monomial(5, {{"x", 3}}), Monomial(-14, {{"x", 1}}), Monomial(3, {})};
    Polynomial denominator{Monomial(1, {{"x", 1}}), Monomial(-2, {})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(polynomialOverPolynomial.simplifyAndDivide());

    EXPECT_EQ((Polynomial{Monomial(5, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(6, {})}), quotientAndRemainder.quotient);
    EXPECT_EQ((Polynomial{Monomial(15, {})}), quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnConvertingFractionCoefficientsToInteger)
{
    Polynomial numerator{Monomial(AlbaNumber(1, 2), {{"x", 1}}), Monomial(AlbaNumber(1, 3), {{"y", 1}})};    Polynomial denominator{Monomial(AlbaNumber(1, 5), {{"x", 1}}), Monomial(AlbaNumber(1, 10), {{"y", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();
    EXPECT_EQ((Polynomial{Monomial(15, {{"x", 1}}), Monomial(10, {{"y", 1}})}), polynomialOverPolynomial.getNumerator());
    EXPECT_EQ((Polynomial{Monomial(6, {{"x", 1}}), Monomial(3, {{"y", 1}})}), polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnRemovingCommonFactorInCoefficients)
{
    Polynomial numerator{Monomial(0.3, {}), Monomial(2, {{"x", 1}}), Monomial(2, {{"y", 1}})};
    Polynomial denominator{Monomial(2, {{"y", 1}}), Monomial(2, {{"z", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    EXPECT_EQ((Polynomial{Monomial(0.15, {}), Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})}), polynomialOverPolynomial.getNumerator());
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

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnRemovingCommonFactorInVariableExponents)
{
    Polynomial numerator{Monomial(1, {{"x", 3}, {"y", 2}}), Monomial(1, {{"x", 2}, {"y", 3}})};
    Polynomial denominator{Monomial(1, {{"x", 2}, {"y", 2}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    EXPECT_EQ((Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})}), polynomialOverPolynomial.getNumerator());
    EXPECT_EQ((Polynomial{Monomial(1, {})}), polynomialOverPolynomial.getDenominator());
}

}

}
