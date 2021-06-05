#include <Polynomial.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(PolynomialTest, PolynomialsAreConstructedCorrectly)
{
    Polynomial polynomial1;
    Polynomial polynomial2({Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})});

    Monomials const& monomials1(polynomial1.getMonomialsConstReference());
    ASSERT_TRUE(monomials1.empty());

    Monomials const& monomials2(polynomial2.getMonomialsConstReference());
    ASSERT_EQ(2u, monomials2.size());
    EXPECT_DOUBLE_EQ(6, monomials2.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials2.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(-7, monomials2.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials2.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(3u, variableMap2.size());
    EXPECT_DOUBLE_EQ(2, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(3, variableMap2.at("y").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap2.at("z").getDouble());
}

TEST(PolynomialTest, EqualityOperatorWorks)
{
    Polynomial polynomial1;
    Polynomial polynomial2({Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})});
    Polynomial polynomial3({Monomial(6, {}), Monomial(68, {{"x", 2}, {"y", 3}, {"z", 4}})});
    Polynomial polynomial4({Monomial(6, {})});
    Polynomial polynomial5({Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})});

    EXPECT_TRUE(polynomial1==polynomial1);
    EXPECT_FALSE(polynomial1==polynomial2);
    EXPECT_TRUE(polynomial2==polynomial2);
    EXPECT_FALSE(polynomial2==polynomial3);
    EXPECT_FALSE(polynomial2==polynomial4);
    EXPECT_TRUE(polynomial2==polynomial5);
}

TEST(PolynomialTest, IsZeroWorksCorrectly)
{
    Polynomial polynomial1;
    Polynomial polynomial2({Monomial(6, {})});
    Polynomial polynomial3({Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})});

    EXPECT_TRUE(polynomial1.isZero());
    EXPECT_FALSE(polynomial2.isZero());
    EXPECT_FALSE(polynomial3.isZero());
}

TEST(PolynomialTest, IsOneMonomialWorksCorrectly)
{
    Polynomial polynomial1;
    Polynomial polynomial2({Monomial(6, {})});
    Polynomial polynomial3({Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})});

    EXPECT_FALSE(polynomial1.isOneMonomial());
    EXPECT_TRUE(polynomial2.isOneMonomial());
    EXPECT_FALSE(polynomial3.isOneMonomial());
}

TEST(PolynomialTest, GetFirstMonomialWorksCorrectly)
{
    Polynomial polynomial1;
    Polynomial polynomial2({Monomial(6, {})});
    Polynomial polynomial3({Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})});

    Monomial monomial1(polynomial1.getFirstMonomial());
    Monomial monomial2(polynomial2.getFirstMonomial());
    Monomial monomial3(polynomial3.getFirstMonomial());

    EXPECT_DOUBLE_EQ(0, monomial1.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial1.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());

    EXPECT_DOUBLE_EQ(6, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap2.empty());

    EXPECT_DOUBLE_EQ(6, monomial3.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3(monomial3.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap3.empty());
}

}

}
