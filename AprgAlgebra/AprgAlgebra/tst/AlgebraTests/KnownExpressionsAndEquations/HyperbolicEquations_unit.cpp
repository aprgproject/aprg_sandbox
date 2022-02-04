#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/KnownExpressionsAndEquations/HyperbolicEquations.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(HyperbolicEquationsTest, GetEToTheXWorks)
{
    EXPECT_EQ("((e)^x)", getEToTheX("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetEToTheNegativeXWorks)
{
    EXPECT_EQ("((e)^-1[x])", getEToTheNegativeX("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetEToTheXPlusEToTheNegativeXWorks)
{
    EXPECT_EQ("(((e)^x)+((e)^-1[x]))", getEToTheXPlusEToTheNegativeX("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetEToTheXMinusEToTheNegativeXWorks)
{
    EXPECT_EQ("(((e)^x)-((e)^-1[x]))", getEToTheXMinusEToTheNegativeX("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicSineDefinitionWorks)
{
    EXPECT_EQ("sinh(x) = ((((e)^x)-((e)^-1[x]))/2)", getHyperbolicSineDefinition("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicCosineDefinitionWorks)
{
    EXPECT_EQ("cosh(x) = ((((e)^x)+((e)^-1[x]))/2)", getHyperbolicCosineDefinition("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicTangentDefinitionWorks)
{
    EXPECT_EQ("tanh(x) = ((((e)^x)-((e)^-1[x]))/(((e)^x)+((e)^-1[x])))", getHyperbolicTangentDefinition("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicCosecantDefinitionWorks)
{
    EXPECT_EQ("csch(x) = (2/(((e)^x)-((e)^-1[x])))", getHyperbolicCosecantDefinition("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicSecantDefinitionWorks)
{
    EXPECT_EQ("sech(x) = (2/(((e)^x)+((e)^-1[x])))", getHyperbolicSecantDefinition("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicCotangentDefinitionWorks)
{
    EXPECT_EQ("coth(x) = ((((e)^x)+((e)^-1[x]))/(((e)^x)-((e)^-1[x])))", getHyperbolicCotangentDefinition("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicFunctionIdentityWorks)
{
    EXPECT_EQ("((cosh(x)^2)-(sinh(x)^2)) = 1", getHyperbolicFunctionIdentityEquation("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetEToTheXFromHyperbolicFunctionsEquationWorks)
{
    EXPECT_EQ("((e)^x) = (cosh(x)+sinh(x))", getEToTheXFromHyperbolicFunctionsEquation("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetEToTheNegativeXFromHyperbolicFunctionsEquationWorks)
{
    EXPECT_EQ("((e)^-1[x]) = (cosh(x)-sinh(x))", getEToTheNegativeXFromHyperbolicFunctionsEquation("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicSineOfSumOfTwoTermsWorks)
{
    EXPECT_EQ("((sinh(x)*cosh(y))+(cosh(x)*sinh(y)))", getHyperbolicSineOfSumOfTwoTerms("x", "y").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicCosineOfSumOfTwoTermsWorks)
{
    EXPECT_EQ("((cosh(x)*cosh(y))+(sinh(x)*sinh(y)))", getHyperbolicCosineOfSumOfTwoTerms("x", "y").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicSineOfDoubledValueWorks)
{
    EXPECT_EQ("(2*sinh(x)*cosh(x))", getHyperbolicSineOfDoubledValue("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicCosineOfDoubledValueWorks)
{
    EXPECT_EQ("((cosh(x)^2)+(sinh(x)^2))", getHyperbolicCosineOfDoubledValue("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicSineOfHalvedValueWorks)
{
    EXPECT_EQ("(((cosh(x)-1)/2)^(1/2))", getHyperbolicSineOfHalvedValue("x", true).getDisplayableString());
    EXPECT_EQ("(-1*(((cosh(x)-1)/2)^(1/2)))", getHyperbolicSineOfHalvedValue("x", false).getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicCosineOfHalvedValueWorks)
{
    EXPECT_EQ("(((cosh(x)+1)/2)^(1/2))", getHyperbolicCosineOfHalvedValue("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicArcSineDefinitionWorks)
{
    EXPECT_EQ("arcsinh(x) = ln((x+(((x^2)+1)^(1/2))))", getHyperbolicArcSineDefinition("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicArcCosineDefinitionWorks)
{
    EXPECT_EQ("arccosh(x) = ln((x+(((x^2)-1)^(1/2))))", getHyperbolicArcCosineDefinition("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicArcTangentDefinitionWorks)
{
    EXPECT_EQ("arctanh(x) = ((1/2)*ln(((1-x)/(1+x))))", getHyperbolicArcTangentDefinition("x").getDisplayableString());
}

TEST(HyperbolicEquationsTest, GetHyperbolicArcCotangentDefinitionWorks)
{
    EXPECT_EQ("arccoth(x) = ((1/2)*ln(((x+1)/(x-1))))", getHyperbolicArcCotangentDefinition("x").getDisplayableString());
}


}

}
