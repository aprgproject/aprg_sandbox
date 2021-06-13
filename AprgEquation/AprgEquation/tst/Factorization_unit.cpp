#include <Factorization.hpp>

#include <gtest/gtest.h>

#include <Debug/AlbaDebug.hpp>

using namespace std;

namespace alba
{

namespace equation
{

namespace Factorization
{

TEST(FactorizationTest, CommonMonomialCanBeFactored)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 1}, {"y", 2}}), Monomial(6, {{"x", 3}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));
    ASSERT_EQ(2, polynomialsToVerify.size());
    EXPECT_EQ((Polynomial{Monomial(3, {{"x", 1}})}), polynomialsToVerify.at(0));
    EXPECT_EQ((Polynomial{Monomial(3, {{"y", 2}}), Monomial(2, {{"x", 2}})}), polynomialsToVerify.at(1));
}

TEST(FactorizationTest, DifferenceOfSquaresCanBeFactored)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 8}, {"y", 2}}), Monomial(-16, {{"z", 4}})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));
    ASSERT_EQ(2, polynomialsToVerify.size());
    ALBA_PRINT1(polynomialsToVerify.at(0).getDisplayableString());
    ALBA_PRINT1(polynomialsToVerify.at(1).getDisplayableString());
    EXPECT_EQ((Polynomial{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(4, {{"z", 2}})}), polynomialsToVerify.at(0));
    EXPECT_EQ((Polynomial{Monomial(3, {{"x", 4}, {"y", 1}}), Monomial(-4, {{"z", 2}})}), polynomialsToVerify.at(1));
}

}
}

}
