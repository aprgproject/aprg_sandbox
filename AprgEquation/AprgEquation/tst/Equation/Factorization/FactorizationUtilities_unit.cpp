#include <Equation/Factorization/FactorizationUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

namespace Factorization
{


TEST(FactorizationUtilitiesTest, FactorizePolynomialsWorksWhenPolynomialsCannotBeFactorized)
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

TEST(FactorizationUtilitiesTest, FactorizePolynomialsWorksWhenPolynomialsCanBeFactorized)
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

TEST(FactorizationUtilitiesTest, ReturnPolynomialsOrSinglePolynomialIfEmptyWorksWhenPolynomialsIsNotEmpty)
{
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(11, {})};
    Polynomial polynomial2{Monomial(1, {{"y", 1}}), Monomial(13, {})};
    Polynomial polynomial3{Monomial(1, {{"z", 1}}), Monomial(17, {})};
    Polynomial singlePolynomial{Monomial(1, {{"a", 1}}), Monomial(23, {})};
    Polynomials polynomials{polynomial1, polynomial2, polynomial3};

    Polynomials polynomialsToVerify(returnPolynomialsOrSinglePolynomialIfEmpty(polynomials, singlePolynomial));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1(polynomial1);
    Polynomial polynomialToExpect2(polynomial2);
    Polynomial polynomialToExpect3(polynomial3);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationUtilitiesTest, ReturnPolynomialsOrSinglePolynomialIfEmptyWorksWhenPolynomialsIsEmpty)
{
    Polynomial singlePolynomial{Monomial(1, {{"a", 1}}), Monomial(23, {})};
    Polynomials polynomials;

    Polynomials polynomialsToVerify(returnPolynomialsOrSinglePolynomialIfEmpty(polynomials, singlePolynomial));

    ASSERT_EQ(1u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1(singlePolynomial);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
}

TEST(FactorizationUtilitiesTest, FactorizeCommonMonomialWorksWhenItCannotBeFactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeCommonMonomial(polynomialToTest));

    ASSERT_EQ(1u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1(polynomialToTest);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
}

TEST(FactorizationUtilitiesTest, FactorizeCommonMonomialWorksWhenItCanBeFactored)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 1}, {"y", 2}}), Monomial(6, {{"x", 3}})};

    Polynomials polynomialsToVerify(factorizeCommonMonomial(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 2}}), Monomial(3, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationUtilitiesTest, FactorizeCommonMonomialIfPossible_IsEmptyWhenItCannotBeRefactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};

    Polynomials polynomialsToVerify(factorizeCommonMonomialIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationUtilitiesTest, FactorizeCommonMonomialIfPossible_IsEmptyWhenItsOneMonomial)
{
    Polynomial polynomialToTest{Monomial(7, {{"x", 7}})};

    Polynomials polynomialsToVerify(factorizeCommonMonomialIfPossible(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationUtilitiesTest, FactorizeCommonMonomialIfPossible_WorksWhenGettingTheGcfMonomial)
{
    Polynomial polynomialToTest{Monomial(9, {{"x", 1}, {"y", 2}}), Monomial(6, {{"x", 3}})};

    Polynomials polynomialsToVerify(factorizeCommonMonomialIfPossible(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(3, {{"x", 1}})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 2}}), Monomial(3, {{"y", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationUtilitiesTest, IsPerfectSquareWorks)
{
    Monomial monomial1;
    Monomial monomial2(25, {{"x", 8}});
    Monomial monomial3(26, {{"x", 8}});
    Monomial monomial4(25, {{"x", 9}});

    EXPECT_TRUE(isPerfectSquare(monomial1));
    EXPECT_TRUE(isPerfectSquare(monomial2));
    EXPECT_FALSE(isPerfectSquare(monomial3));
    EXPECT_FALSE(isPerfectSquare(monomial4));
}

TEST(FactorizationUtilitiesTest, IsPerfectCubeWorks)
{
    Monomial monomial1;
    Monomial monomial2(125, {{"x", 6}});
    Monomial monomial3(126, {{"x", 6}});
    Monomial monomial4(125, {{"x", 7}});

    EXPECT_TRUE(isPerfectCube(monomial1));
    EXPECT_TRUE(isPerfectCube(monomial2));
    EXPECT_FALSE(isPerfectCube(monomial3));
    EXPECT_FALSE(isPerfectCube(monomial4));
}

TEST(FactorizationUtilitiesTest, IsPerfectNthPowerWorks)
{
    Monomial monomial1;
    Monomial monomial2(16, {{"x", 4}});
    Monomial monomial3(17, {{"x", 4}});
    Monomial monomial4(16, {{"x", 5}});

    EXPECT_TRUE(isPerfectNthPower(monomial1, 4));
    EXPECT_TRUE(isPerfectNthPower(monomial2, 4));
    EXPECT_FALSE(isPerfectNthPower(monomial3, 4));
    EXPECT_FALSE(isPerfectNthPower(monomial4, 4));
}

TEST(FactorizationUtilitiesTest, AreExponentsDivisibleWorks)
{
    Monomial monomial1;
    Monomial monomial2(4, {{"x", 4}});
    Monomial monomial3(2, {{"x", 4}});
    Monomial monomial4(2, {{"x", 5}});

    EXPECT_TRUE(areExponentsDivisible(monomial1, 4));
    EXPECT_TRUE(areExponentsDivisible(monomial2, 4));
    EXPECT_TRUE(areExponentsDivisible(monomial3, 4));
    EXPECT_FALSE(areExponentsDivisible(monomial4, 4));
}

TEST(FactorizationUtilitiesTest, SimplifyPolynomialThenEmplaceBackIfNotEmptyWorksIfNotEmpty)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(2, {{"x", 1}})};

    Polynomials polynomialsToVerify;
    simplifyPolynomialThenEmplaceBackIfNotEmpty(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(1u, polynomialsToVerify.size());
    Polynomial polynomialToExpect{Monomial(3, {{"x", 1}})};    EXPECT_EQ(polynomialToExpect, polynomialsToVerify.at(0));
}

TEST(FactorizationUtilitiesTest, SimplifyPolynomialThenEmplaceBackIfNotEmptyWorksIfEmpty)
{
    Polynomial polynomialToTest;

    Polynomials polynomialsToVerify;
    simplifyPolynomialThenEmplaceBackIfNotEmpty(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationUtilitiesTest, EmplaceBackIfNotEmptyWorksIfNotEmpty)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(2, {{"x", 1}})};

    Polynomials polynomialsToVerify;
    emplaceBackIfNotEmpty(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(1u, polynomialsToVerify.size());
    Polynomial polynomialToExpect{Monomial(1, {{"x", 1}}), Monomial(2, {{"x", 1}})};
    EXPECT_EQ(polynomialToExpect, polynomialsToVerify.at(0));
}

TEST(FactorizationUtilitiesTest, EmplaceBackIfNotEmptyWorksIfEmpty)
{
    Polynomial polynomialToTest;

    Polynomials polynomialsToVerify;
    emplaceBackIfNotEmpty(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

}

}

}