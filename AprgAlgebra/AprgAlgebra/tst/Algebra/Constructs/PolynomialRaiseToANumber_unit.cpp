#include <Algebra/Constructs/PolynomialRaiseToANumber.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(PolynomialRaiseToANumberTest, ConstructionWorks)
{
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToANumber polynomialRaiseToANumber(polynomial);

    EXPECT_EQ(polynomial, polynomialRaiseToANumber.getBase());
    EXPECT_EQ(1U, polynomialRaiseToANumber.getExponent());
}

TEST(PolynomialRaiseToANumberTest, GetBaseWorks)
{
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToANumber polynomialRaiseToANumber(polynomial);

    EXPECT_EQ(polynomial, polynomialRaiseToANumber.getBase());
}

TEST(PolynomialRaiseToANumberTest, GetExponentWorks)
{
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToANumber polynomialRaiseToANumber(polynomial);

    EXPECT_EQ(1U, polynomialRaiseToANumber.getExponent());
}

TEST(PolynomialRaiseToANumberTest, IsExponentOneWorks)
{
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToANumber polynomialRaiseToANumber(polynomial);

    EXPECT_TRUE(polynomialRaiseToANumber.isExponentOne());
}

TEST(PolynomialRaiseToANumberTest, PolynomialWithCommonMonomialAndFactorsButExponentIsStillOneWorks)
{
    Polynomial polynomial{Monomial(5, {{"x", 1}}), Monomial(-20, {})};
    PolynomialRaiseToANumber polynomialRaiseToANumber(polynomial);

    EXPECT_EQ(polynomial, polynomialRaiseToANumber.getBase());
    EXPECT_EQ(1U, polynomialRaiseToANumber.getExponent());
}

TEST(PolynomialRaiseToANumberTest, PolynomialWithPerfectSquare)
{
    Polynomial polynomial{Monomial(1, {{"x", 2}}), Monomial(4, {{"x", 1}}), Monomial(4, {})};
    PolynomialRaiseToANumber polynomialRaiseToANumber(polynomial);

    Polynomial expectedBase{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    EXPECT_EQ(expectedBase, polynomialRaiseToANumber.getBase());
    EXPECT_EQ(2U, polynomialRaiseToANumber.getExponent());
}

TEST(PolynomialRaiseToANumberTest, PolynomialWithPerfectSquareAndCommonFactor)
{
    Polynomial polynomial{Monomial(4, {{"x", 6}, {"y", 2}}), Monomial(16, {{"x", 5}, {"y", 2}}), Monomial(16, {{"x", 4}, {"y", 2}})};
    PolynomialRaiseToANumber polynomialRaiseToANumber(polynomial);

    Polynomial expectedBase{Monomial(2, {{"x", 3}, {"y", 1}}), Monomial(4, {{"x", 2}, {"y", 1}})};
    EXPECT_EQ(expectedBase, polynomialRaiseToANumber.getBase());
    EXPECT_EQ(2U, polynomialRaiseToANumber.getExponent());
}

TEST(PolynomialRaiseToANumberTest, PolynomialWithPerfectCube)
{
    Polynomial polynomial{Monomial(1, {{"x", 3}}), Monomial(3, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToANumber polynomialRaiseToANumber(polynomial);

    Polynomial expectedBase{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    EXPECT_EQ(expectedBase, polynomialRaiseToANumber.getBase());
    EXPECT_EQ(3U, polynomialRaiseToANumber.getExponent());
}

TEST(PolynomialRaiseToANumberTest, PolynomialWithPerfectCubeAndCommonFactor)
{
    Polynomial polynomial{Monomial(8, {{"x", 3}}), Monomial(24, {{"x", 2}}), Monomial(24, {{"x", 1}}), Monomial(8, {})};
    PolynomialRaiseToANumber polynomialRaiseToANumber(polynomial);

    Polynomial expectedBase{Monomial(2, {{"x", 1}}), Monomial(2, {})};
    EXPECT_EQ(expectedBase, polynomialRaiseToANumber.getBase());
    EXPECT_EQ(3U, polynomialRaiseToANumber.getExponent());
}

TEST(PolynomialRaiseToANumberTest, PolynomialWithPerfectSquaresAndPerfect4thPowerAndCommonFactor)
{
    Polynomial commonFactor{Monomial(256, {{"y", 4}})};
    Polynomial perfectSquare{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    perfectSquare.raiseToUnsignedInteger(2);
    Polynomial perfect4thPower{Monomial(1, {{"x", 1}}), Monomial(4, {})};
    perfect4thPower.raiseToUnsignedInteger(4);
    Polynomial polynomialToTest(commonFactor);
    polynomialToTest.multiplyPolynomial(perfectSquare);
    polynomialToTest.multiplyPolynomial(perfect4thPower);
    PolynomialRaiseToANumber polynomialRaiseToANumber(polynomialToTest);

    Polynomial expectedBase
    {Monomial(16, {{"x", 3}, {"y", 2}}), Monomial(160, {{"x", 2}, {"y", 2}}), Monomial(512, {{"x", 1}, {"y", 2}}), Monomial(512, {{"y", 2}})};
    EXPECT_EQ(expectedBase, polynomialRaiseToANumber.getBase());
    EXPECT_EQ(2U, polynomialRaiseToANumber.getExponent());
}

}

}
