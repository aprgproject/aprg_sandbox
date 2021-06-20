#include <Equation/Constructs/FactorizationOfIncreasingAndDecreasingExponentForm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

namespace Factorization
{

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleIsEmptyWhenItCannotBeRefactored)
{
    FactorizationOfIncreasingAndDecreasingExponentForm factorization;
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorization.factorizeIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleIsEmptyWhenItsSingleMonomial)
{
    FactorizationOfIncreasingAndDecreasingExponentForm factorization;
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}})};

    Polynomials polynomialsToVerify(factorization.factorizeIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleIsEmptyWhenExponentsAreNotDivisible)
{
    FactorizationOfIncreasingAndDecreasingExponentForm factorization;
    Polynomial polynomialToTest{Monomial(1, {{"x", 13}}), Monomial(1, {{"x", 17}}),};

    Polynomials polynomialsToVerify(factorization.factorizeIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleIsEmptyWhenSomeVariablesAreDifferentFromStartAndEndMonomials)
{
    FactorizationOfIncreasingAndDecreasingExponentForm factorization;
    Polynomial polynomialToTest{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}}), Monomial(144, {})};

    Polynomials polynomialsToVerify(factorization.factorizeIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionWithFirstCoefficientIsNotOne)
{
    FactorizationOfIncreasingAndDecreasingExponentForm factorization;
    Polynomial polynomialToTest{Monomial(9, {{"x", 2}}), Monomial(-30, {{"x", 1}}), Monomial(25, {})};

    Polynomials polynomialsToVerify(factorization.factorizeIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionWithFractionFirstCoefficients)
{
    FactorizationOfIncreasingAndDecreasingExponentForm factorization;
    Polynomial polynomialToTest{Monomial(AlbaNumber(1, 16), {{"x", 2}}), Monomial(AlbaNumber(5, 2), {{"x", 1}}), Monomial(25, {})};

    Polynomials polynomialsToVerify(factorization.factorizeIfPossible(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(AlbaNumber(1, 16), {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    Polynomial polynomialToExpect3{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionWithFractionSecondCoefficients)
{
    FactorizationOfIncreasingAndDecreasingExponentForm factorization;
    Polynomial polynomialToTest{Monomial(25, {{"x", 2}}), Monomial(AlbaNumber(5, 2), {{"x", 1}}), Monomial(AlbaNumber(1, 16), {})};

    Polynomials polynomialsToVerify(factorization.factorizeIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(5, {{"x", 1}}), Monomial(AlbaNumber(1, 4), {})};
    Polynomial polynomialToExpect2{Monomial(5, {{"x", 1}}), Monomial(AlbaNumber(1, 4), {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionExample1)
{
    FactorizationOfIncreasingAndDecreasingExponentForm factorization;
    Polynomial polynomialToTest{Monomial(2, {{"x", 2}}), Monomial(-23, {{"x", 1}, {"y", 1}}), Monomial(-39, {{"y", 2}})};

    Polynomials polynomialsToVerify(factorization.factorizeIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-13, {{"y", 1}})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 1}}), Monomial(3, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnCubicExpressionExample1)
{
    FactorizationOfIncreasingAndDecreasingExponentForm factorization;
    Polynomial polynomialToTest{Monomial(192, {{"x", 3}}), Monomial(200, {{"x", 2}}), Monomial(-298, {{"x", 1}}), Monomial(-315, {})};

    Polynomials polynomialsToVerify(factorization.factorizeIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(4, {{"x", 1}}), Monomial(-5, {})};
    Polynomial polynomialToExpect2{Monomial(48, {{"x", 2}}), Monomial(110, {{"x", 1}}), Monomial(63, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionWithFirstCoefficientIsOne)
{
    FactorizationOfIncreasingAndDecreasingExponentForm factorization;
    Polynomial polynomialToTest{Monomial(1, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(-4, {})};

    Polynomials polynomialsToVerify(factorization.factorizeIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

}

}

}
