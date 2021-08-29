#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Simplification/SimplificationOfFunction.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

TEST(SimplificationOfFunctionTest, SimplifyWorksOnAbsoluteValueExpressionWithPositiveFirstCoefficient)
{
    SimplificationOfFunction simplification(
                Functions::abs(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}));

    simplification.simplify();

    Function actualEquation(simplification.getFunction());
    Function expectedFunction(Functions::abs(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}));
    EXPECT_EQ(expectedFunction, actualEquation);
}

TEST(SimplificationOfFunctionTest, SimplifyWorksOnAbsoluteValueExpressionWithNegativeFirstCoefficient)
{
    SimplificationOfFunction simplification(
                Functions::abs(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(1, {{"y", 1}})}));

    simplification.simplify();

    Function actualEquation(simplification.getFunction());
    Function expectedFunction(Functions::abs(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}));
    EXPECT_EQ(expectedFunction, actualEquation);
}

}

}

}
