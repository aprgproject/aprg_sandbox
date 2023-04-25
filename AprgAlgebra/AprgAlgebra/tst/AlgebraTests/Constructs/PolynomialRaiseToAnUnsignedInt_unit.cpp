#include <Algebra/Constructs/PolynomialRaiseToAnUnsignedInt.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algebra {

TEST(PolynomialRaiseToAnUnsignedIntTest, ConstructionWorks) {
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomial);

    EXPECT_EQ(polynomial, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(1U, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, GetBaseWorks) {
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomial);

    EXPECT_EQ(polynomial, polynomialRaiseToAnUnsignedInt.getBase());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, GetExponentWorks) {
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomial);

    EXPECT_EQ(1U, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, IsExponentOneWorks) {
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomial);

    EXPECT_TRUE(polynomialRaiseToAnUnsignedInt.isExponentOne());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithCommonMonomialAndFactorsButExponentIsStillOneWorks) {
    Polynomial polynomial{Monomial(5, {{"x", 1}}), Monomial(-20, {})};
    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomial);

    EXPECT_EQ(polynomial, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(1U, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithPerfectSquare) {
    Polynomial polynomial{Monomial(1, {{"x", 2}}), Monomial(4, {{"x", 1}}), Monomial(4, {})};
    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomial);

    Polynomial expectedBase{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    EXPECT_EQ(expectedBase, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(2U, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithPerfectSquareWithNegativeConstant) {
    Polynomial polynomial{Monomial(-7, {{"x", 2}}), Monomial(-28, {{"x", 1}}), Monomial(-28, {})};
    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomial);

    Polynomial expectedBase(polynomial);
    EXPECT_EQ(expectedBase, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(1U, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithPerfectSquareAndCommonFactor) {
    Polynomial polynomial{
        Monomial(4, {{"x", 6}, {"y", 2}}), Monomial(16, {{"x", 5}, {"y", 2}}), Monomial(16, {{"x", 4}, {"y", 2}})};
    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomial);

    Polynomial expectedBase{Monomial(2, {{"x", 3}, {"y", 1}}), Monomial(4, {{"x", 2}, {"y", 1}})};
    EXPECT_EQ(expectedBase, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(2U, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithPerfectCube) {
    Polynomial polynomial{Monomial(1, {{"x", 3}}), Monomial(3, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(1, {})};
    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomial);

    Polynomial expectedBase{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    EXPECT_EQ(expectedBase, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(3U, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithPerfectCubeAndCommonFactor) {
    Polynomial polynomial{Monomial(8, {{"x", 3}}), Monomial(24, {{"x", 2}}), Monomial(24, {{"x", 1}}), Monomial(8, {})};
    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomial);

    Polynomial expectedBase{Monomial(2, {{"x", 1}}), Monomial(2, {})};
    EXPECT_EQ(expectedBase, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(3U, polynomialRaiseToAnUnsignedInt.getExponent());
}

TEST(PolynomialRaiseToAnUnsignedIntTest, PolynomialWithPerfectSquaresAndPerfect4thPowerAndCommonFactor) {
    Polynomial commonFactor{Monomial(256, {{"y", 4}})};
    Polynomial perfectSquare{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    perfectSquare.raiseToUnsignedInteger(2);
    Polynomial perfect4thPower{Monomial(1, {{"x", 1}}), Monomial(4, {})};
    perfect4thPower.raiseToUnsignedInteger(4);
    Polynomial polynomialToTest(commonFactor);
    polynomialToTest.multiplyPolynomial(perfectSquare);
    polynomialToTest.multiplyPolynomial(perfect4thPower);
    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomialToTest);

    Polynomial expectedBase{
        Monomial(16, {{"x", 3}, {"y", 2}}), Monomial(160, {{"x", 2}, {"y", 2}}), Monomial(512, {{"x", 1}, {"y", 2}}),
        Monomial(512, {{"y", 2}})};
    EXPECT_EQ(expectedBase, polynomialRaiseToAnUnsignedInt.getBase());
    EXPECT_EQ(2U, polynomialRaiseToAnUnsignedInt.getExponent());
}

}  // namespace algebra

}  // namespace alba
