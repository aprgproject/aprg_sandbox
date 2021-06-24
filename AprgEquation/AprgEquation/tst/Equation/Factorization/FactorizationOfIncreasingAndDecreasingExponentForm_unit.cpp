#include <Equation/Factorization/FactorizationOfIncreasingAndDecreasingExponentForm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

namespace Factorization
{

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIncreasingAndDecreasingExponentsFormWorksWhenItCannotBeFactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};
    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsForm(polynomialToTest));

    ASSERT_EQ(1u, polynomialsToVerify.size());    Polynomial polynomialToExpect1(polynomialToTest);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIncreasingAndDecreasingExponentsFormWorksWhenItCanBeFactored)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 2}}), Monomial(-30, {{"x", 1}}), Monomial(25, {})};
    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsForm(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleIsEmptyWhenItCannotBeRefactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}
TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleIsEmptyWhenItsSingleMonomial)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}
TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleIsEmptyWhenExponentsAreNotDivisible)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 13}}), Monomial(1, {{"x", 17}}),};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}
TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleIsEmptyWhenSomeVariablesAreDifferentFromStartAndEndMonomials)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}}), Monomial(144, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}
TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionWithFirstCoefficientIsNotOne)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 2}}), Monomial(-30, {{"x", 1}}), Monomial(25, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}}), Monomial(-5, {})};    Polynomial polynomialToExpect2{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionWithFractionFirstCoefficients)
{
    Polynomial polynomialToTest{Monomial(AlbaNumber(1, 16), {{"x", 2}}), Monomial(AlbaNumber(5, 2), {{"x", 1}}), Monomial(25, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(20, {})};    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    Polynomial polynomialToExpect3{Monomial(AlbaNumber(1, 16), {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionWithFractionSecondCoefficients)
{
    Polynomial polynomialToTest{Monomial(25, {{"x", 2}}), Monomial(AlbaNumber(5, 2), {{"x", 1}}), Monomial(AlbaNumber(1, 16), {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(5, {{"x", 1}}), Monomial(AlbaNumber(1, 4), {})};    Polynomial polynomialToExpect2{Monomial(5, {{"x", 1}}), Monomial(AlbaNumber(1, 4), {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionExample1)
{
    Polynomial polynomialToTest{Monomial(2, {{"x", 2}}), Monomial(-23, {{"x", 1}, {"y", 1}}), Monomial(-39, {{"y", 2}})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-13, {{"y", 1}})};    Polynomial polynomialToExpect2{Monomial(2, {{"x", 1}}), Monomial(3, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnCubicExpressionExample1)
{
    Polynomial polynomialToTest{Monomial(192, {{"x", 3}}), Monomial(200, {{"x", 2}}), Monomial(-298, {{"x", 1}}), Monomial(-315, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    //ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(6, {{"x", 1}}), Monomial(7, {})};    Polynomial polynomialToExpect2{Monomial(8, {{"x", 1}}), Monomial(9, {})};
    Polynomial polynomialToExpect3{Monomial(4, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionWithFirstCoefficientIsOne)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(-4, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-1, {})};    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksBigExponentDifferenceOfSquares)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 64}}), Monomial(-1, {{"y", 16}})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 32}}), Monomial(-1, {{"y", 8}})};    Polynomial polynomialToExpect2{Monomial(1, {{"x", 32}}), Monomial(1, {{"y", 8}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksComplicatedPolynomial)
{
    Polynomial polynomialToTest{
        Monomial(2112, {{"x", 4}}),
                Monomial(-296, {{"x", 3}}),                Monomial(-5878, {{"x", 2}}),
                Monomial(409, {{"x", 1}}),
                Monomial(4095, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(4u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(6, {{"x", 1}}), Monomial(7, {})};    Polynomial polynomialToExpect2{Monomial(8, {{"x", 1}}), Monomial(9, {})};
    Polynomial polynomialToExpect3{Monomial(11, {{"x", 1}}), Monomial(-13, {})};
    Polynomial polynomialToExpect4{Monomial(4, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify.at(3));
}

}

}

}
