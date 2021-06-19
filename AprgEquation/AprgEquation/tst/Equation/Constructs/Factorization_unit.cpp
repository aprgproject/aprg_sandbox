#include <Equation/Constructs/Factorization.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace equation
{

namespace Factorization
{

TEST(FactorizationTest, CommonConstantCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(4, {{"x", 1}}), Monomial(20, {})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(4, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, CommonMonomialCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 1}, {"y", 2}}), Monomial(6, {{"x", 3}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 2}}), Monomial(3, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, DifferenceOfSquaresCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, DifferenceOfSquaresInReverseCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(-9, {{"x", 8}, {"y", 2}}), Monomial(16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, DifferenceOfSquaresWithNegativeExponentsCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", -4}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", -2}})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", -2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, DifferenceOfCubesCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, DifferenceOfCubesInReverseCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, DifferenceOfCubesWithNegativeExponentsCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 3}}), Monomial(-8, {{"y", -3}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}}), Monomial(-2, {{"y", -1}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 2}}), Monomial(6, {{"x", 1}, {"y", -1}}), Monomial(4, {{"y", -2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, SumOfCubesCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, SumOfCubesInReverseCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, SumOfCubesWithNegativeExponentsCanBeFactored_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 3}}), Monomial(8, {{"y", -3}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}}), Monomial(2, {{"y", -1}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 2}}), Monomial(-6, {{"x", 1}, {"y", -1}}), Monomial(4, {{"y", -2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, QuadraticExpressionWithFirstCoefficientIsOne_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(-4, {})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, QuadraticExpressionWithFirstCoefficientIsNotOne_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 2}}), Monomial(-30, {{"x", 1}}), Monomial(25, {})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, QuadraticExpressionWithFractionFirstCoefficients_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(AlbaNumber(1, 16), {{"x", 2}}), Monomial(AlbaNumber(5, 2), {{"x", 1}}), Monomial(25, {})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(AlbaNumber(1, 16), {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    Polynomial polynomialToExpect3{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, QuadraticExpressionWithFractionSecondCoefficients_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(25, {{"x", 2}}), Monomial(AlbaNumber(5, 2), {{"x", 1}}), Monomial(AlbaNumber(1, 16), {})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(AlbaNumber(1, 16), {})};
    Polynomial polynomialToExpect2{Monomial(20, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect3{Monomial(20, {{"x", 1}}), Monomial(1, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, QuadraticExpressionExample1_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(2, {{"x", 2}}), Monomial(-23, {{"x", 1}, {"y", 1}}), Monomial(-39, {{"y", 2}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-13, {{"y", 1}})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 1}}), Monomial(3, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, CubicExpressionExample1_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(192, {{"x", 3}}), Monomial(200, {{"x", 2}}), Monomial(-298, {{"x", 1}}), Monomial(-315, {})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(4, {{"x", 1}}), Monomial(-5, {})};
    Polynomial polynomialToExpect2{Monomial(8, {{"x", 1}}), Monomial(9, {})};
    Polynomial polynomialToExpect3{Monomial(6, {{"x", 1}}), Monomial(7, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, AXPlusBTimesCXPlusD_FactorizeWorks)
{
    Polynomial polynomialToTest{
        Monomial(1, {{"a", 1}, {"c", 1}, {"x", 2}}),
                Monomial(1, {{"a", 1}, {"d", 1}, {"x", 1}}),
                Monomial(1, {{"b", 1}, {"c", 1}, {"x", 1}}),
                Monomial(1, {{"b", 1}, {"d", 1}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"c", 1}, {"x", 1}}), Monomial(1, {{"d", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, Example1_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(2, {{"x", 3}}), Monomial(28, {{"x", 2}}), Monomial(98, {{"x", 1}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(2, {{"x", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    Polynomial polynomialToExpect3{Monomial(1, {{"x", 1}}), Monomial(7, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, Example2_FactorizeWorks)
{
    Polynomial polynomialToTest{Monomial(4, {{"x", 3}}), Monomial(-12, {{"x", 2}}), Monomial(-1, {{"x", 1}}), Monomial(3, {})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-3, {})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect3{Monomial(2, {{"x", 1}}), Monomial(-1, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, CommonMonomialCanBeFactored_FactorizeCommonMonomialWorks)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 1}, {"y", 2}}), Monomial(6, {{"x", 3}})};

    Polynomials polynomialsToVerify(factorizeCommonMonomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 2}}), Monomial(3, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, DifferenceOfSquaresCanBeFactored_FactorizeDifferenceOfSquaresWorks)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfSquares(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, DifferenceOfSquaresInReverseCanBeFactored_FactorizeDifferenceOfSquaresWorks)
{
    Polynomial polynomialToTest{Monomial(-9, {{"x", 8}, {"y", 2}}), Monomial(16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfSquares(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, DifferenceOfCubesCanBeFactored_FactorizeDifferenceOfCubesWorks)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfCubes(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, DifferenceOfCubesInReverseCanBeFactored_FactorizeDifferenceOfCubesWorks)
{
    Polynomial polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeDifferenceOfCubes(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, SumOfCubesCanBeFactored_FactorizeSumOfCubesWorks)
{
    Polynomial polynomialToTest{Monomial(27, {{"x", 12}, {"y", 3}}), Monomial(64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeSumOfCubes(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect2{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, SumOfCubesInReverseCanBeFactored_FactorizeSumOfCubesWorks)
{
    Polynomial polynomialToTest{Monomial(-27, {{"x", 12}, {"y", 3}}), Monomial(-64, {{"z", 6}})};

    Polynomials polynomialsToVerify(factorizeSumOfCubes(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})};
    Polynomial polynomialToExpect3{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-12, {{"x", 4}, {"y", 1}, {"z", 2}}), Monomial(16, {{"z", 4}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, QuadraticExpressionWithFirstCoefficientIsOne_FactorizeIncreasingAndDecreasingExponentsFormWorks)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 2}}), Monomial(3, {{"x", 1}}), Monomial(-4, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsForm(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, QuadraticExpressionWithFirstCoefficientIsNotOne_FactorizeIncreasingAndDecreasingExponentsFormWorks)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 2}}), Monomial(-30, {{"x", 1}}), Monomial(25, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsForm(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 1}}), Monomial(-5, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, QuadraticExpressionWithFractionFirstCoefficients_FactorizeIncreasingAndDecreasingExponentsFormWorks)
{
    Polynomial polynomialToTest{Monomial(AlbaNumber(1, 16), {{"x", 2}}), Monomial(AlbaNumber(5, 2), {{"x", 1}}), Monomial(25, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsForm(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(AlbaNumber(1, 16), {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    Polynomial polynomialToExpect3{Monomial(1, {{"x", 1}}), Monomial(20, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, QuadraticExpressionWithFractionSecondCoefficients_FactorizeIncreasingAndDecreasingExponentsFormWorks)
{
    Polynomial polynomialToTest{Monomial(25, {{"x", 2}}), Monomial(AlbaNumber(5, 2), {{"x", 1}}), Monomial(AlbaNumber(1, 16), {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsForm(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(5, {{"x", 1}}), Monomial(AlbaNumber(1, 4), {})};
    Polynomial polynomialToExpect2{Monomial(5, {{"x", 1}}), Monomial(AlbaNumber(1, 4), {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, QuadraticExpressionExample1_FactorizeIncreasingAndDecreasingExponentsFormWorks)
{
    Polynomial polynomialToTest{Monomial(2, {{"x", 2}}), Monomial(-23, {{"x", 1}, {"y", 1}}), Monomial(-39, {{"y", 2}})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsForm(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"x", 1}}), Monomial(-13, {{"y", 1}})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 1}}), Monomial(3, {{"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, CubicExpressionExample1_FactorizeIncreasingAndDecreasingExponentsFormWorks)
{
    Polynomial polynomialToTest{Monomial(192, {{"x", 3}}), Monomial(200, {{"x", 2}}), Monomial(-298, {{"x", 1}}), Monomial(-315, {})};

    Polynomials polynomialsToVerify(factorizeIncreasingAndDecreasingExponentsForm(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(4, {{"x", 1}}), Monomial(-5, {})};
    Polynomial polynomialToExpect2{Monomial(48, {{"x", 2}}), Monomial(110, {{"x", 1}}), Monomial(63, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationTest, AXPlusBTimesCXPlusD_FactorizeBySplittingSmallerPolynomialsWorks)
{
    Polynomial polynomialToTest{
        Monomial(1, {{"a", 1}, {"c", 1}, {"x", 2}}),
                Monomial(1, {{"a", 1}, {"d", 1}, {"x", 1}}),
                Monomial(1, {{"b", 1}, {"c", 1}, {"x", 1}}),
                Monomial(1, {{"b", 1}, {"d", 1}})};

    Polynomials polynomialsToVerify(factorizeBySplittingSmallerPolynomials(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"c", 1}, {"x", 1}}), Monomial(1, {{"d", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

}

}

}
