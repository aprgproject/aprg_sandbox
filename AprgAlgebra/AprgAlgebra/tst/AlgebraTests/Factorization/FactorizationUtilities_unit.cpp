#include <Algebra/Factorization/FactorizationUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algebra {

namespace Factorization {

TEST(FactorizationUtilitiesTest, AreExponentsDivisibleWorks) {
    Monomial monomial1;
    Monomial monomial2(4, {{"x", 4}});
    Monomial monomial3(2, {{"x", 4}});
    Monomial monomial4(2, {{"x", 5}});

    EXPECT_TRUE(areExponentsDivisible(monomial1, 4));
    EXPECT_TRUE(areExponentsDivisible(monomial2, 4));
    EXPECT_TRUE(areExponentsDivisible(monomial3, 4));
    EXPECT_FALSE(areExponentsDivisible(monomial4, 4));
}

TEST(FactorizationUtilitiesTest, IsPerfectSquareWorks) {
    Monomial monomial1;
    Monomial monomial2(25, {{"x", 8}});
    Monomial monomial3(26, {{"x", 8}});
    Monomial monomial4(25, {{"x", 9}});

    EXPECT_TRUE(isPerfectSquare(monomial1));
    EXPECT_TRUE(isPerfectSquare(monomial2));
    EXPECT_FALSE(isPerfectSquare(monomial3));
    EXPECT_FALSE(isPerfectSquare(monomial4));
}

TEST(FactorizationUtilitiesTest, IsPerfectCubeWorks) {
    Monomial monomial1;
    Monomial monomial2(125, {{"x", 6}});
    Monomial monomial3(126, {{"x", 6}});
    Monomial monomial4(125, {{"x", 7}});

    EXPECT_TRUE(isPerfectCube(monomial1));
    EXPECT_TRUE(isPerfectCube(monomial2));
    EXPECT_FALSE(isPerfectCube(monomial3));
    EXPECT_FALSE(isPerfectCube(monomial4));
}

TEST(FactorizationUtilitiesTest, IsPerfectNthPowerWorks) {
    Monomial monomial1;
    Monomial monomial2(16, {{"x", 4}});
    Monomial monomial3(17, {{"x", 4}});
    Monomial monomial4(16, {{"x", 5}});

    EXPECT_TRUE(isPerfectNthPower(monomial1, 4));
    EXPECT_TRUE(isPerfectNthPower(monomial2, 4));
    EXPECT_FALSE(isPerfectNthPower(monomial3, 4));
    EXPECT_FALSE(isPerfectNthPower(monomial4, 4));
}

TEST(FactorizationUtilitiesTest, DoesNotNeedToBeFactorizedWorks) {
    EXPECT_TRUE(doesNotNeedToBeFactorized(Polynomial{Monomial(1, {{"x", 4}})}));
    EXPECT_TRUE(doesNotNeedToBeFactorized(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}));
    EXPECT_TRUE(doesNotNeedToBeFactorized(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 1}})}));
    EXPECT_TRUE(doesNotNeedToBeFactorized(Polynomial{Monomial(1, {{"x", 1}}), Monomial(NAN, {})}));
    EXPECT_FALSE(doesNotNeedToBeFactorized(Polynomial{Monomial(1, {{"x", 1}}), Monomial(0.5, {})}));
    EXPECT_FALSE(doesNotNeedToBeFactorized(Polynomial{Monomial(2, {{"x", 1}}), Monomial(3, {})}));
    EXPECT_FALSE(doesNotNeedToBeFactorized(Polynomial{Monomial(1, {{"x", 0.5}}), Monomial(2, {})}));
    EXPECT_FALSE(doesNotNeedToBeFactorized(Polynomial{Monomial(1, {{"x", 1}, {"y", 1}}), Monomial(2, {})}));
    EXPECT_FALSE(doesNotNeedToBeFactorized(
        Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(2, {{"z", 1}})}));
}

TEST(FactorizationUtilitiesTest, DoesContainOnlyConstantsWorks) {
    EXPECT_FALSE(doesContainOnlyConstants({Polynomial{Monomial(1, {})}, Polynomial{Monomial(2, {{"x", 3}})}}));
    EXPECT_TRUE(doesContainOnlyConstants(
        {Polynomial{Monomial(1, {})}, Polynomial{Monomial(2, {})}, Polynomial{Monomial(3, {})}}));
}

TEST(FactorizationUtilitiesTest, DoesContainConstantsOrOnlyOneNonConstantWorks) {
    EXPECT_FALSE(IsEmptyOrContainConstantsOrOneNonConstant(
        {Polynomial{Monomial(1, {})}, Polynomial{Monomial(2, {{"x", 3}})}, Polynomial{Monomial(4, {{"y", 5}})}}));
    EXPECT_TRUE(
        IsEmptyOrContainConstantsOrOneNonConstant({Polynomial{Monomial(1, {})}, Polynomial{Monomial(2, {{"x", 3}})}}));
    EXPECT_TRUE(IsEmptyOrContainConstantsOrOneNonConstant(
        {Polynomial{Monomial(1, {})}, Polynomial{Monomial(2, {})}, Polynomial{Monomial(3, {})}}));
}

TEST(FactorizationUtilitiesTest, SimplifyThenEmplaceBackIfPolynomialIsNotEmptyWorksIfNotEmpty) {
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(2, {{"x", 1}})};

    Polynomials polynomialsToVerify;
    simplifyThenEmplaceBackIfPolynomialIsNotEmpty(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(1U, polynomialsToVerify.size());
    Polynomial polynomialToExpect{Monomial(3, {{"x", 1}})};
    EXPECT_EQ(polynomialToExpect, polynomialsToVerify.at(0));
}

TEST(FactorizationUtilitiesTest, SimplifyThenEmplaceBackIfPolynomialIsNotEmptyWorksIfEmpty) {
    Polynomial polynomialToTest;

    Polynomials polynomialsToVerify;
    simplifyThenEmplaceBackIfPolynomialIsNotEmpty(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationUtilitiesTest, EmplaceBackIfPolynomialIsNotEmptyWorksIfNotEmpty) {
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(2, {{"x", 1}})};

    Polynomials polynomialsToVerify;
    emplaceBackIfPolynomialIsNotEmpty(polynomialsToVerify, polynomialToTest);

    ASSERT_EQ(1U, polynomialsToVerify.size());
    Polynomial polynomialToExpect{Monomial(1, {{"x", 1}}), Monomial(2, {{"x", 1}})};
    EXPECT_EQ(polynomialToExpect, polynomialsToVerify.at(0));
}

TEST(FactorizationUtilitiesTest, EmplaceBackIfPolynomialIsNotEmptyWorksIfEmpty) {
    Polynomial polynomialToTest;

    Polynomials polynomialsToVerify;
    emplaceBackIfPolynomialIsNotEmpty(polynomialsToVerify, polynomialToTest);

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationUtilitiesTest, SimplifyAndEmplacePolynomialIfListIsEmptyWorksWhenPolynomialsIsNotEmpty) {
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(11, {})};
    Polynomial polynomial2{Monomial(1, {{"y", 1}}), Monomial(13, {})};
    Polynomial polynomial3{Monomial(1, {{"z", 1}}), Monomial(17, {})};
    Polynomial singlePolynomial{Monomial(1, {{"a", 1}}), Monomial(23, {})};
    Polynomials polynomialsToVerify{polynomial1, polynomial2, polynomial3};

    simplifyAndEmplaceBackPolynomialIfListIsEmpty(polynomialsToVerify, singlePolynomial);

    ASSERT_EQ(3U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1(polynomial1);
    Polynomial polynomialToExpect2(polynomial2);
    Polynomial polynomialToExpect3(polynomial3);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationUtilitiesTest, SimplifyAndEmplacePolynomialIfListIsEmptyWorksWhenPolynomialsIsEmpty) {
    Polynomial singlePolynomial{Monomial(1, {{"a", 1}}), Monomial(23, {})};
    Polynomials polynomialsToVerify;

    simplifyAndEmplaceBackPolynomialIfListIsEmpty(polynomialsToVerify, singlePolynomial);

    ASSERT_EQ(1U, polynomialsToVerify.size());
    Polynomial polynomialToExpect1(singlePolynomial);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
}

}  // namespace Factorization

}  // namespace algebra

}  // namespace alba
