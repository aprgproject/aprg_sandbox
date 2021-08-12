#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{


TEST(FactorizationOfPolynomialsTest, CommonConstantCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(4, {{"x", 1}}), Monomial(20, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(4, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfPolynomialsTest, CommonMonomialCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 1}, {"y", 2}}), Monomial(6, {{"x", 3}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 2}}), Monomial(3, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfSquaresCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfSquaresInReverseCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(-9, {{"x", 8}, {"y", 2}}), Monomial(16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfSquaresWithNegativeExponentsCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", -4}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"z", -4}})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(+4, {})};
    Polynomial polynomialToExpect3{Monomial(3, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(-4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfSquaresWithBigExponent)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 64}}),  Monomial(-1, {{"y", 16}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(5u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 32}}), Monomial(1, {{"y", 8}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 16}}), Monomial(1, {{"y", 4}})};
    Polynomial polynomialToExpect3{Monomial(1, {{"x", 8}}), Monomial(1, {{"y", 2}})};
    Polynomial polynomialToExpect4{Monomial(1, {{"x", 4}}), Monomial(1, {{"y", 1}})};
    Polynomial polynomialToExpect5{Monomial(1, {{"x", 4}}), Monomial(-1, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify.at(3));
    EXPECT_EQ(polynomialToExpect5, polynomialsToVerify.at(4));
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfCubesCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfCubesInReverseCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfPolynomialsTest, DifferenceOfCubesWithNegativeExponentsCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 3}}), Monomial(-8, {{"y", -3}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"y", -3}})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 1}, {"y", 1}}), Monomial(-2, {})};
    Polynomial polynomialToExpect3{Monomial(9, {{"x", 2}, {"y", 2}}), Monomial(6, {{"x", 1}, {"y", 1}}), Monomial(4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfPolynomialsTest, SumOfCubesCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfPolynomialsTest, SumOfCubesInReverseCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfPolynomialsTest, SumOfCubesWithNegativeExponentsCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 3}}), Monomial(8, {{"y", -3}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"y", -3}})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 1}, {"y", 1}}), Monomial(2, {})};
    Polynomial polynomialToExpect3{Monomial(9, {{"x", 2}, {"y", 2}}), Monomial(-6, {{"x", 1}, {"y", 1}}), Monomial(4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfPolynomialsTest, QuadraticExpressionWithFirstCoefficientIsOne_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(-4, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfPolynomialsTest, QuadraticExpressionWithFirstCoefficientIsNotOne_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 2}}), Monomial(-30, {{"x", 1}}), Monomial(25, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfPolynomialsTest, QuadraticExpressionWithFractionFirstCoefficients_FactorizeWorks)
{
    Polynomial polynomialToTest{
        Monomial(AlbaNumber::createFraction(1, 16), {{"x", 2}}),
                Monomial(AlbaNumber::createFraction(5, 2), {{"x", 1}}),
                Monomial(25, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(AlbaNumber::createFraction(1, 16), {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    Polynomial polynomialToExpect3{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfPolynomialsTest, QuadraticExpressionWithFractionSecondCoefficients_FactorizeWorks)
{
    Polynomial polynomialToTest{
        Monomial(25, {{"x", 2}}),
                Monomial(AlbaNumber::createFraction(5, 2), {{"x", 1}}),
                Monomial(AlbaNumber::createFraction(1, 16), {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(AlbaNumber::createFraction(1, 16), {})};
    Polynomial polynomialToExpect2{Monomial(20, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect3{Monomial(20, {{"x", 1}}), Monomial(1, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfPolynomialsTest, QuadraticExpressionExample1_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(2, {{"x", 2}}), Monomial(-23, {{"x", 1}, {"y", 1}}), Monomial(-39, {{"y", 2}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-13, {{"y", 1}})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 1}}), Monomial(3, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfPolynomialsTest, CubicExpressionExample1_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(192, {{"x", 3}}), Monomial(200, {{"x", 2}}), Monomial(-298, {{"x", 1}}), Monomial(-315, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(6, {{"x", 1}}), Monomial(7, {})};
    Polynomial polynomialToExpect2{Monomial(8, {{"x", 1}}), Monomial(9, {})};
    Polynomial polynomialToExpect3{Monomial(4, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfPolynomialsTest, FactorizeWorksBySplittingByPolynomialDegree)
{
    Polynomial polynomialToTest{
        Monomial(25, {{"x", 2}}),
                Monomial(30, {{"x", 1}, {"y", 1}}),
                Monomial(9, {{"y", 2}}),
                Monomial(15, {{"x", 1}}),
                Monomial(9, {{"y", 1}}),
                Monomial(2, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(5, {{"x", 1}}), Monomial(3, {{"y", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect2{Monomial(5, {{"x", 1}}), Monomial(3, {{"y", 1}}), Monomial(2, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfPolynomialsTest, FactorizeWorksBySplittingByDivisibilityOfExponents)
{
    Polynomial polynomialToTest{
        Monomial(1, {{"x", 2}}),
                Monomial(2, {{"x", 1}, {"y", 1}}),
                Monomial(-1, {{"z", 2}}),
                Monomial(-2, {{"y", 1}, {"z", 1}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(1, {{"z", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-1, {{"z", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfPolynomialsTest, FactorizeWorksBySplittingByFirstVariable)
{
    Polynomial polynomialToTest{
        Monomial(1, {{"a", 1}, {"x", 1}}),
                Monomial(-1, {{"a", 1}, {"y", 1}}),
                Monomial(-1, {{"b", 1}, {"y", 1}}),
                Monomial(1, {{"b", 1}, {"x", 1}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfPolynomialsTest, AXPlusBTimesCXPlusD_FactorizeWorks)
{
    Polynomial polynomialToTest{
        Monomial(1, {{"a", 1}, {"c", 1}, {"x", 2}}),
                Monomial(1, {{"a", 1}, {"d", 1}, {"x", 1}}),
                Monomial(1, {{"b", 1}, {"c", 1}, {"x", 1}}),
                Monomial(1, {{"b", 1}, {"d", 1}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"c", 1}, {"x", 1}}), Monomial(1, {{"d", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfPolynomialsTest, Example1_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(2, {{"x", 3}}), Monomial(28, {{"x", 2}}), Monomial(98, {{"x", 1}})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(2, {{"x", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    Polynomial polynomialToExpect3{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfPolynomialsTest, Example2_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(4, {{"x", 3}}), Monomial(-12, {{"x", 2}}), Monomial(-1, {{"x", 1}}), Monomial(3, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(2, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 1}}), Monomial(-1, {})};
    Polynomial polynomialToExpect3{Monomial(1, {{"x", 1}}), Monomial(-3, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfPolynomialsTest, Example3_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(3, {{"x", 4}}), Monomial(-32, {{"x", 2}}), Monomial(-80, {{"x", 1}}), Monomial(-12, {})};

    Polynomials polynomialsToVerify(factorizeAPolynomial(polynomialToTest));

    ASSERT_EQ(4u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(0.160246899469294, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-4.16024689946928, {})};
    Polynomial polynomialToExpect3{Monomial(3, {})};
    Polynomial polynomialToExpect4{Monomial(1, {{"x", 2}}), Monomial(4, {{"x", 1}}), Monomial(6, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify.at(3));
}

TEST(FactorizationOfPolynomialsTest, FactorizePolynomialsWorksWhenPolynomialsCannotBeFactorized)
{
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(11, {})};
    Polynomial polynomial2{Monomial(1, {{"y", 1}}), Monomial(13, {})};
    Polynomial polynomial3{Monomial(1, {{"z", 1}}), Monomial(17, {})};
    Polynomials polynomials{polynomial1, polynomial2, polynomial3};

    Polynomials polynomialsToVerify(factorizePolynomials(polynomials));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1(polynomial1);
    Polynomial polynomialToExpect2(polynomial2);
    Polynomial polynomialToExpect3(polynomial3);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationOfPolynomialsTest, FactorizePolynomialsWorksWhenPolynomialsCanBeFactorized)
{
    Polynomial polynomial1{Monomial(1, {{"x", 2}}), Monomial(-1, {})};
    Polynomial polynomial2{Monomial(1, {{"y", 2}}), Monomial(-1, {})};
    Polynomials polynomials{polynomial1, polynomial2};

    Polynomials polynomialsToVerify(factorizePolynomials(polynomials));

    ASSERT_EQ(4u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Polynomial polynomialToExpect3{Monomial(1, {{"y", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect4{Monomial(1, {{"y", 1}}), Monomial(-1, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
    EXPECT_EQ(polynomialToExpect4, polynomialsToVerify.at(3));
}

TEST(FactorizationOfPolynomialsTest, FactorizeCommonMonomialWorksWhenItCannotBeFactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeCommonMonomial(polynomialToTest));

    ASSERT_EQ(1u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1(polynomialToTest);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
}

TEST(FactorizationOfPolynomialsTest, FactorizeCommonMonomialWorksWhenItCanBeFactored)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 1}, {"y", 2}}), Monomial(6, {{"x", 3}})};

    Polynomials polynomialsToVerify(factorizeCommonMonomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 2}}), Monomial(3, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationOfPolynomialsTest, FactorizeCommonMonomialIfPossible_IsEmptyWhenItCannotBeRefactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeCommonMonomialIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationOfPolynomialsTest, FactorizeCommonMonomialIfPossible_IsEmptyWhenItsOneMonomial)
{
    Polynomial polynomialToTest{Monomial(7, {{"x", 7}})};

    Polynomials polynomialsToVerify(factorizeCommonMonomialIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationOfPolynomialsTest, FactorizeCommonMonomialIfPossible_WorksWhenGettingTheGcfMonomial)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 1}, {"y", 2}}), Monomial(6, {{"x", 3}})};

    Polynomials polynomialsToVerify(factorizeCommonMonomialIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 2}}), Monomial(3, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

}

}

}
