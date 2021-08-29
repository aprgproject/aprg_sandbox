#include <Algebra/Factorization/FactorizationOfIncreasingAndDecreasingExponentForm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIncreasingAndDecreasingExponentsFormWorksWhenItCannotBeFactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsForm(polynomialToTest));

    ASSERT_EQ(1U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1(polynomialToTest);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIncreasingAndDecreasingExponentsFormWorksWhenItCanBeFactored)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 2}}), Monomial(-30, {{"x", 1}}), Monomial(25, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsForm(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
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

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionWithFractionFirstCoefficients)
{
    Polynomial polynomialToTest{
        Monomial(AlbaNumber::createFraction(1, 16), {{"x", 2}}),
                Monomial(AlbaNumber::createFraction(5, 2), {{"x", 1}}),
                Monomial(25, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    Polynomial polynomialToExpect3{Monomial(AlbaNumber::createFraction(1, 16), {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionWithFractionSecondCoefficients)
{
    Polynomial polynomialToTest{
        Monomial(25, {{"x", 2}}),
                Monomial(AlbaNumber::createFraction(5, 2), {{"x", 1}}),
                Monomial(AlbaNumber::createFraction(1, 16), {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(5, {{"x", 1}}), Monomial(AlbaNumber::createFraction(1, 4), {})};
    Polynomial polynomialToExpect2{Monomial(5, {{"x", 1}}), Monomial(AlbaNumber::createFraction(1, 4), {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionExample1)
{
    Polynomial polynomialToTest{Monomial(2, {{"x", 2}}), Monomial(-23, {{"x", 1}, {"y", 1}}), Monomial(-39, {{"y", 2}})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-13, {{"y", 1}})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 1}}), Monomial(3, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnCubicExpressionExample1)
{
    Polynomial polynomialToTest{Monomial(192, {{"x", 3}}), Monomial(200, {{"x", 2}}), Monomial(-298, {{"x", 1}}), Monomial(-315, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(6, {{"x", 1}}), Monomial(7, {})};
    Polynomial polynomialToExpect2{Monomial(8, {{"x", 1}}), Monomial(9, {})};
    Polynomial polynomialToExpect3{Monomial(4, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksOnQuadraticExpressionWithFirstCoefficientIsOne)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(-4, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksBigExponentDifferenceOfSquares)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 64}}), Monomial(-1, {{"y", 16}})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(2U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 32}}), Monomial(-1, {{"y", 8}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 32}}), Monomial(1, {{"y", 8}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizeIfPossibleWorksComplicatedPolynomial)
{
    Polynomial polynomialToTest{
        Monomial(2112, {{"x", 4}}),
                Monomial(-296, {{"x", 3}}),
                Monomial(-5878, {{"x", 2}}),
                Monomial(409, {{"x", 1}}),
                Monomial(4095, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToTest));

    ASSERT_EQ(4U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(6, {{"x", 1}}), Monomial(7, {})};
    Polynomial polynomialToExpect2{Monomial(8, {{"x", 1}}), Monomial(9, {})};
    Polynomial polynomialToExpect3{Monomial(11, {{"x", 1}}), Monomial(-13, {})};
    Polynomial polynomialToExpect4{Monomial(4, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify.at(3));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FactorizePolynomialFormWorks)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 3}}), Monomial(3, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(1, {})};
    AlbaNumbers coefficients({1, 3, 3, 1});

    Polynomials polynomialsToVerify(
                factorizePolynomialForm(
                    polynomialToTest,
                    coefficients,
                    Monomial::VariablesToExponentsMap{{"x", 1}},
                    Monomial::VariablesToExponentsMap{}));

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial polynomialToExpect{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    EXPECT_EQ(polynomialToExpect, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect, polynomialsToVerify.at(2));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, FixCoefficientsOfFactorsWorks)
{
    AlbaNumber aCoefficient1(11);
    AlbaNumber firstRoot1(12);
    AlbaNumber secondRoot1(13);
    AlbaNumber aCoefficient2(35);
    AlbaNumber firstRoot2(1);
    AlbaNumber secondRoot2(AlbaNumber::createFraction(1, 7));

    fixCoefficientsOfFactors(aCoefficient1, firstRoot1, secondRoot1);
    fixCoefficientsOfFactors(aCoefficient2, firstRoot2, secondRoot2);

    EXPECT_DOUBLE_EQ(11, aCoefficient1.getDouble());
    EXPECT_DOUBLE_EQ(12, firstRoot1.getDouble());
    EXPECT_DOUBLE_EQ(13, secondRoot1.getDouble());
    EXPECT_DOUBLE_EQ(5, aCoefficient2.getDouble());
    EXPECT_DOUBLE_EQ(7, firstRoot2.getDouble());
    EXPECT_DOUBLE_EQ(1, secondRoot2.getDouble());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, AreAllMonomialsFoundInMonomialsWithExponentsInOrderWorks)
{
    Monomials monomials1{Monomial(2, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(4, {})};
    Monomials monomials2{Monomial(6, {{"y", 2}}), Monomial(7, {{"y", 1}}), Monomial(8, {})};
    Monomials monomials3{Monomial(1, {{"x", 2}}), Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Monomials monomials4{Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 1}}), Monomial(1, {})};

    EXPECT_TRUE(areAllMonomialsFoundInMonomialsWithExponentsInOrder(monomials1, monomials1));
    EXPECT_FALSE(areAllMonomialsFoundInMonomialsWithExponentsInOrder(monomials1, monomials2));
    EXPECT_TRUE(areAllMonomialsFoundInMonomialsWithExponentsInOrder(monomials1, monomials3));
    EXPECT_FALSE(areAllMonomialsFoundInMonomialsWithExponentsInOrder(monomials1, monomials4));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, CalculateMaxExponentDivisorWorks)
{
    EXPECT_EQ(0U, calculateMaxExponentDivisor(Monomial(1, {}), Monomial(1, {})));
    EXPECT_EQ(7U, calculateMaxExponentDivisor(Monomial(1, {{"x", 7}}), Monomial(1, {{"y", 7}})));
    EXPECT_EQ(7U, calculateMaxExponentDivisor(Monomial(1, {{"x", 3}}), Monomial(1, {{"y", 7}})));
    EXPECT_EQ(9U, calculateMaxExponentDivisor(Monomial(1, {{"x", 9}}), Monomial(1, {{"y", 7}})));
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, GetCoefficientsInMonomialsWithExponentsInOrderWorks)
{
    Polynomial polynomial1{Monomial(1, {{"x", 3}}), Monomial(3, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(1, {})};
    Monomials monomials1{Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 2}}), Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomial2{Monomial(1, {{"y", 3}}), Monomial(3, {{"y", 2}}), Monomial(3, {{"x", 1}}), Monomial(1, {})};
    Monomials monomials2{Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 2}}), Monomial(1, {{"x", 1}}), Monomial(1, {})};

    AlbaNumbers coefficients1(getCoefficientsInMonomialsWithExponentsInOrder(Polynomial{}, Monomials{}));
    AlbaNumbers coefficients2(getCoefficientsInMonomialsWithExponentsInOrder(polynomial1, monomials1));
    AlbaNumbers coefficients3(getCoefficientsInMonomialsWithExponentsInOrder(polynomial2, monomials2));

    EXPECT_TRUE(coefficients1.empty());
    ASSERT_EQ(4U, coefficients2.size());
    EXPECT_DOUBLE_EQ(1, coefficients2.at(0).getDouble());
    EXPECT_DOUBLE_EQ(3, coefficients2.at(1).getDouble());
    EXPECT_DOUBLE_EQ(3, coefficients2.at(2).getDouble());
    EXPECT_DOUBLE_EQ(1, coefficients2.at(3).getDouble());
    ASSERT_EQ(4U, coefficients3.size());
    EXPECT_DOUBLE_EQ(0, coefficients3.at(0).getDouble());
    EXPECT_DOUBLE_EQ(0, coefficients3.at(1).getDouble());
    EXPECT_DOUBLE_EQ(3, coefficients3.at(2).getDouble());
    EXPECT_DOUBLE_EQ(1, coefficients3.at(3).getDouble());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, CalculatePolynomialRootsWorks)
{
    AlbaNumbers quadraticCoefficients{1, 2, 1};
    AlbaNumbers cubicCoefficients{1, 3, 3, 1};

    AlbaNumbers quadraticRoots(calculatePolynomialRoots(quadraticCoefficients));
    AlbaNumbers cubicRoots(calculatePolynomialRoots(cubicCoefficients));

    ASSERT_EQ(2U, quadraticRoots.size());
    EXPECT_DOUBLE_EQ(-1, quadraticRoots.at(0).getDouble());
    EXPECT_DOUBLE_EQ(-1, quadraticRoots.at(1).getDouble());
    ASSERT_EQ(3U, cubicRoots.size());
    EXPECT_DOUBLE_EQ(-1, cubicRoots.at(0).getDouble());
    EXPECT_DOUBLE_EQ(-1, cubicRoots.at(1).getDouble());
    EXPECT_DOUBLE_EQ(-1, cubicRoots.at(2).getDouble());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, CalculatePolynomialRootsUsingBrentMethodWorks)
{
    AlbaNumbers cubicCoefficients{1, 3, 3, 1};
    AlbaNumbers previousDerivativeCoefficients{3, 6, 3};

    AlbaNumbers roots(calculatePolynomialRootsUsingBrentMethod(previousDerivativeCoefficients, cubicCoefficients));

    ASSERT_EQ(1U, roots.size());
    EXPECT_DOUBLE_EQ(-1, roots.at(0).getDouble());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, GetMaxAbsoluteValueForRootFindingWorks)
{
    AlbaNumbers coefficients1{1, 2, 3, 4};
    AlbaNumbers coefficients2{4, 3, 2, 1};

    EXPECT_DOUBLE_EQ(4, getMaxAbsoluteValueForRootFinding(coefficients1).getDouble());
    EXPECT_DOUBLE_EQ(4, getMaxAbsoluteValueForRootFinding(coefficients2).getDouble());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, GetDerivativeCoefficientsWorks)
{
    AlbaNumbers cubicCoefficients{1, 3, 3, 1};

    AlbaNumbers derivativeCoefficients(getDerivativeCoefficients(cubicCoefficients));

    ASSERT_EQ(3U, derivativeCoefficients.size());
    EXPECT_DOUBLE_EQ(3, derivativeCoefficients.at(0).getDouble());
    EXPECT_DOUBLE_EQ(6, derivativeCoefficients.at(1).getDouble());
    EXPECT_DOUBLE_EQ(3, derivativeCoefficients.at(2).getDouble());
}

TEST(FactorizationOfIncreasingAndDecreasingExponentFormTest, GetMonomialsWithExponentsInOrderWorks)
{
    Monomials monomialsToVerify(getMonomialsWithExponentsInOrder(3, Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})));

    ASSERT_EQ(4U, monomialsToVerify.size());
    EXPECT_EQ(Monomial(1, {{"x", 3}}), monomialsToVerify.at(0));
    EXPECT_EQ(Monomial(1, {{"x", 2}, {"y", 1}}), monomialsToVerify.at(1));
    EXPECT_EQ(Monomial(1, {{"x", 1}, {"y", 2}}), monomialsToVerify.at(2));
    EXPECT_EQ(Monomial(1, {{"y", 3}}), monomialsToVerify.at(3));
}

}

}

}
