#include <Algebra/Integration/IntegrationUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(IntegrationUtilitiesTest, IsTheIntegralDefinitionForFiniteCalculusIsTrueWorks)
{
    Term termToTest1(Monomial(1, {{"x", 1}}));
    Term termToTest2(Monomial(1, {{"x", 2}}));
    Term termToTest3(Monomial(1, {{"x", 3}}));

    EXPECT_TRUE(isTheIntegralDefinitionForFiniteCalculusIsTrue(termToTest1, "x", 5, 10));
    EXPECT_TRUE(isTheIntegralDefinitionForFiniteCalculusIsTrue(termToTest2, "x", 5, 10));
    EXPECT_TRUE(isTheIntegralDefinitionForFiniteCalculusIsTrue(termToTest3, "x", 5, 10));
}

}

}
