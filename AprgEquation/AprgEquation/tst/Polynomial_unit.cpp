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

}

}
