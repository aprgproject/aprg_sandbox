#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(PolynomialOverPolynomialTest, ConstructionWorks)
{
    PolynomialOverPolynomial();
    PolynomialOverPolynomial(Polynomial(), Polynomial());
    PolynomialOverPolynomial((Polynomial{Monomial(10, {})}), (Polynomial{Monomial(100, {})}));
}

TEST(PolynomialOverPolynomialTest, IsEmptyWorks)
{
    PolynomialOverPolynomial actual1;
    PolynomialOverPolynomial actual2(Polynomial{}, Polynomial{});
    PolynomialOverPolynomial actual3(Polynomial{}, (Polynomial{Monomial(100, {})}));
    PolynomialOverPolynomial actual4((Polynomial{Monomial(10, {})}), (Polynomial{Monomial(100, {})}));

    EXPECT_TRUE(actual1.isEmpty());
    EXPECT_TRUE(actual2.isEmpty());
    EXPECT_FALSE(actual3.isEmpty());
    EXPECT_FALSE(actual4.isEmpty());
}

TEST(PolynomialOverPolynomialTest, SimplifyAndDivideWithNoRemainder)
{
    Polynomial numerator{Monomial(3, {{"x", 3}}), Monomial(-4, {{"x", 2}, {"y", 1}}), Monomial(5, {{"x", 1}, {"y", 2}}), Monomial(6, {{"y", 3}})};
    Polynomial denominator{Monomial(1, {{"x", 2}}), Monomial(-2, {{"x", 1}, {"y", 1}}), Monomial(3, {{"y", 2}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(polynomialOverPolynomial.simplifyAndDivide());

    Polynomial quotientToExpect{Monomial(3, {{"x", 1}}), Monomial(2, {{"y", 1}})};
    Polynomial remainderToExpect{};
    EXPECT_EQ(quotientToExpect, quotientAndRemainder.quotient);
    EXPECT_EQ(remainderToExpect, quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, SimplifyAndDivideOnAQuarticWithNoRemainder)
{
    Polynomial numerator{Monomial(2112, {{"x", 4}}), Monomial(-296, {{"x", 3}}), Monomial(-5878, {{"x", 2}}), Monomial(409, {{"x", 1}}), Monomial(4095, {})};
    Polynomial denominator{Monomial(11, {{"x", 1}}), Monomial(-13, {})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(polynomialOverPolynomial.simplifyAndDivide());

    Polynomial quotientToExpect{Monomial(192, {{"x", 3}}), Monomial(200, {{"x", 2}}), Monomial(-298, {{"x", 1}}), Monomial(-315, {})};
    Polynomial remainderToExpect{};
    EXPECT_EQ(quotientToExpect, quotientAndRemainder.quotient);
    EXPECT_EQ(remainderToExpect, quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, SimplifyAndDivideWithRemainder)
{
    Polynomial numerator{Monomial(5, {{"x", 3}}), Monomial(-8, {{"x", 2}}), Monomial(6, {{"x", 1}}), Monomial(4, {})};
    Polynomial denominator{Monomial(1, {{"x", 1}}), Monomial(-2, {})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(polynomialOverPolynomial.simplifyAndDivide());

    Polynomial quotientToExpect{Monomial(5, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(10, {})};
    Polynomial remainderToExpect{Monomial(24, {})};
    EXPECT_EQ(quotientToExpect, quotientAndRemainder.quotient);
    EXPECT_EQ(remainderToExpect, quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnConvertingFractionCoefficientsToInteger)
{
    Polynomial numerator{Monomial(AlbaNumber(1, 2), {{"x", 1}}), Monomial(AlbaNumber(1, 3), {{"y", 1}})};    Polynomial denominator{Monomial(AlbaNumber(1, 5), {{"x", 1}}), Monomial(AlbaNumber(1, 10), {{"y", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();
    Polynomial numeratorToExpect{Monomial(15, {{"x", 1}}), Monomial(10, {{"y", 1}})};
    Polynomial denominatorToExpect{Monomial(6, {{"x", 1}}), Monomial(3, {{"y", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnRemovingCommonFactorInCoefficients)
{
    Polynomial numerator{Monomial(0.3, {}), Monomial(2, {{"x", 1}}), Monomial(2, {{"y", 1}})};
    Polynomial denominator{Monomial(2, {{"y", 1}}), Monomial(2, {{"z", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial numeratorToExpect{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}}), Monomial(0.15, {})};
    Polynomial denominatorToExpect{Monomial(1, {{"y", 1}}), Monomial(1, {{"z", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnConvertingNegativeExponentsToPositive)
{
    Polynomial numerator{Monomial(1, {{"x", 1}, {"y", -1}}), Monomial(2, {{"x", -1}, {"y", 1}})};
    Polynomial denominator{Monomial(3, {{"y", 1}}), Monomial(4, {{"z", -1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial numeratorToExpect{Monomial(1, {{"x", 2}, {"z", 1}}), Monomial(2, {{"y", 2}, {"z", 1}})};
    Polynomial denominatorToExpect{Monomial(3, {{"x", 1}, {"y", 2}, {"z", 1}}), Monomial(4, {{"x", 1}, {"y", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCommonNegativeSignInNumerator)
{
    Polynomial numerator{Monomial(-1, {{"x", 1}}), Monomial(-1, {{"y", 1}})};
    Polynomial denominator{Monomial(-1, {{"a", 1}}), Monomial(1, {{"b", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial numeratorToExpect{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    Polynomial denominatorToExpect{Monomial(1, {{"a", 1}}), Monomial(-1, {{"b", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCommonNegativeSignInDenominator)
{
    Polynomial numerator{Monomial(-1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    Polynomial denominator{Monomial(-1, {{"a", 1}}), Monomial(-1, {{"b", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial numeratorToExpect{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})};
    Polynomial denominatorToExpect{Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCommonNegativeSignInNumeratorAndDenominator)
{
    Polynomial numerator{Monomial(-1, {{"x", 1}}), Monomial(-1, {{"y", 1}})};
    Polynomial denominator{Monomial(-1, {{"a", 1}}), Monomial(-1, {{"b", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial numeratorToExpect{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    Polynomial denominatorToExpect{Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCancellingFactorsExample1)
{
    Polynomial numerator{Monomial(4, {{"x", 2}}), Monomial(-9, {{"y", 2}})};
    Polynomial denominator{Monomial(2, {{"x", 1}}), Monomial(-3, {{"y", 1}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial numeratorToExpect{Monomial(2, {{"x", 1}}), Monomial(3, {{"y", 1}})};
    Polynomial denominatorToExpect{Monomial(1, {})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCancellingFactorsExample2)
{
    Polynomial numerator{Monomial(2, {{"x", 2}}), Monomial(-14, {{"x", 1}}), Monomial(20, {})};
    Polynomial denominator{Monomial(-2, {{"x", 2}}), Monomial(7, {{"x", 1}}), Monomial(-6, {})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial numeratorToExpect{Monomial(-2, {{"x", 1}}), Monomial(10, {})};
    Polynomial denominatorToExpect{Monomial(2, {{"x", 1}}), Monomial(-3, {})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCancellingFactorsExample3)
{
    Polynomial numerator{Monomial(1, {{"a", 1}, {"b", -1}}), Monomial(1, {{"c", 1}, {"d", -1}})};
    Polynomial denominator{Monomial(1, {})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial numeratorToExpect{Monomial(1, {{"a", 1}, {"d", 1}}), Monomial(1, {{"b", 1}, {"c", 1}})};
    Polynomial denominatorToExpect{Monomial(1, {{"b", 1}, {"d", 1}})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, SimplifyWorksOnCancellingFactorsExample4)
{
    Polynomial numerator{
        Monomial(15, {{"a", 1}, {"b", 1}}),
                Monomial(-20, {{"a", 1}}),
                Monomial(-21, {{"b", 1}}),
                Monomial(28, {})};
    Polynomial denominator{
        Monomial(21, {}),
                Monomial(-1, {{"a", 1}}),
                Monomial(-10, {{"a", 2}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    polynomialOverPolynomial.simplify();

    Polynomial numeratorToExpect{Monomial(3, {{"b", 1}}), Monomial(-4, {})};
    Polynomial denominatorToExpect{Monomial(-2, {{"a", 1}}), Monomial(-3, {})};
    EXPECT_EQ(numeratorToExpect, polynomialOverPolynomial.getNumerator());
    EXPECT_EQ(denominatorToExpect, polynomialOverPolynomial.getDenominator());
}

TEST(PolynomialOverPolynomialTest, DivideWithNoRemainder)
{
    Polynomial numerator{Monomial(3, {{"x", 3}}), Monomial(-4, {{"x", 2}, {"y", 1}}), Monomial(5, {{"x", 1}, {"y", 2}}), Monomial(6, {{"y", 3}})};
    Polynomial denominator{Monomial(1, {{"x", 2}}), Monomial(-2, {{"x", 1}, {"y", 1}}), Monomial(3, {{"y", 2}})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(polynomialOverPolynomial.divide());

    Polynomial quotientToExpect{Monomial(3, {{"x", 1}}), Monomial(2, {{"y", 1}})};
    Polynomial remainderToExpect{};
    EXPECT_EQ(quotientToExpect, quotientAndRemainder.quotient);
    EXPECT_EQ(remainderToExpect, quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, DivideOnAQuarticWithNoRemainder)
{
    Polynomial numerator{Monomial(2112, {{"x", 4}}), Monomial(-296, {{"x", 3}}), Monomial(-5878, {{"x", 2}}), Monomial(409, {{"x", 1}}), Monomial(4095, {})};
    Polynomial denominator{Monomial(11, {{"x", 1}}), Monomial(-13, {})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(polynomialOverPolynomial.divide());

    Polynomial quotientToExpect{Monomial(192, {{"x", 3}}), Monomial(200, {{"x", 2}}), Monomial(-298, {{"x", 1}}), Monomial(-315, {})};
    Polynomial remainderToExpect{};
    EXPECT_EQ(quotientToExpect, quotientAndRemainder.quotient);
    EXPECT_EQ(remainderToExpect, quotientAndRemainder.remainder);
}

TEST(PolynomialOverPolynomialTest, DivideWithRemainder)
{
    Polynomial numerator{Monomial(5, {{"x", 3}}), Monomial(-14, {{"x", 1}}), Monomial(3, {})};
    Polynomial denominator{Monomial(1, {{"x", 1}}), Monomial(-2, {})};
    PolynomialOverPolynomial polynomialOverPolynomial(numerator, denominator);

    PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(polynomialOverPolynomial.divide());

    Polynomial quotientToExpect{Monomial(5, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(6, {})};
    Polynomial remainderToExpect{Monomial(15, {})};
    EXPECT_EQ(quotientToExpect, quotientAndRemainder.quotient);
    EXPECT_EQ(remainderToExpect, quotientAndRemainder.remainder);
}

}

}
