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
    ASSERT_EQ(2, monomials2.size());
    EXPECT_EQ(6, monomials2[0].getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomials2[1].getVariablesToExponentsMapConstReference());
    ASSERT_EQ(3u, variableMap.size());
    EXPECT_EQ(2, variableMap.at("x").getDouble());
    EXPECT_EQ(3, variableMap.at("y").getDouble());
    EXPECT_EQ(4, variableMap.at("z").getDouble());

}

}

}