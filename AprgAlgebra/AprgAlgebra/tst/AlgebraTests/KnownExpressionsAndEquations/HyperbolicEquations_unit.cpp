#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/KnownExpressionsAndEquations/HyperbolicEquations.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

TEST(HyperbolicEquationsTest, GetEToTheXWorks) { EXPECT_EQ("((e)^x)", convertToString(getEToTheX("x"))); }

TEST(HyperbolicEquationsTest, GetEToTheNegativeXWorks) {
    EXPECT_EQ("((e)^-1[x])", convertToString(getEToTheNegativeX("x")));
}

TEST(HyperbolicEquationsTest, GetEToTheXPlusEToTheNegativeXWorks) {
    EXPECT_EQ("(((e)^x)+((e)^-1[x]))", convertToString(getEToTheXPlusEToTheNegativeX("x")));
}

TEST(HyperbolicEquationsTest, GetEToTheXMinusEToTheNegativeXWorks) {
    EXPECT_EQ("(((e)^x)-((e)^-1[x]))", convertToString(getEToTheXMinusEToTheNegativeX("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicSineDefinitionWorks) {
    EXPECT_EQ("sinh(x) = ((((e)^x)-((e)^-1[x]))/2)", convertToString(getHyperbolicSineDefinition("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicCosineDefinitionWorks) {
    EXPECT_EQ("cosh(x) = ((((e)^x)+((e)^-1[x]))/2)", convertToString(getHyperbolicCosineDefinition("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicTangentDefinitionWorks) {
    EXPECT_EQ(
        "tanh(x) = ((((e)^x)-((e)^-1[x]))/(((e)^x)+((e)^-1[x])))",
        convertToString(getHyperbolicTangentDefinition("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicCosecantDefinitionWorks) {
    EXPECT_EQ("csch(x) = (2/(((e)^x)-((e)^-1[x])))", convertToString(getHyperbolicCosecantDefinition("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicSecantDefinitionWorks) {
    EXPECT_EQ("sech(x) = (2/(((e)^x)+((e)^-1[x])))", convertToString(getHyperbolicSecantDefinition("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicCotangentDefinitionWorks) {
    EXPECT_EQ(
        "coth(x) = ((((e)^x)+((e)^-1[x]))/(((e)^x)-((e)^-1[x])))",
        convertToString(getHyperbolicCotangentDefinition("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicFunctionIdentityWorks) {
    EXPECT_EQ("((cosh(x)^2)-(sinh(x)^2)) = 1", convertToString(getHyperbolicFunctionIdentityEquation("x")));
}

TEST(HyperbolicEquationsTest, GetEToTheXFromHyperbolicFunctionsEquationWorks) {
    EXPECT_EQ("((e)^x) = (cosh(x)+sinh(x))", convertToString(getEToTheXFromHyperbolicFunctionsEquation("x")));
}

TEST(HyperbolicEquationsTest, GetEToTheNegativeXFromHyperbolicFunctionsEquationWorks) {
    EXPECT_EQ(
        "((e)^-1[x]) = (cosh(x)-sinh(x))", convertToString(getEToTheNegativeXFromHyperbolicFunctionsEquation("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicSineOfSumOfTwoTermsWorks) {
    EXPECT_EQ("((sinh(x)*cosh(y))+(cosh(x)*sinh(y)))", convertToString(getHyperbolicSineOfSumOfTwoTerms("x", "y")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicCosineOfSumOfTwoTermsWorks) {
    EXPECT_EQ("((cosh(x)*cosh(y))+(sinh(x)*sinh(y)))", convertToString(getHyperbolicCosineOfSumOfTwoTerms("x", "y")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicSineOfDoubledValueWorks) {
    EXPECT_EQ("(2*sinh(x)*cosh(x))", convertToString(getHyperbolicSineOfDoubledValue("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicCosineOfDoubledValueWorks) {
    EXPECT_EQ("((cosh(x)^2)+(sinh(x)^2))", convertToString(getHyperbolicCosineOfDoubledValue("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicSineOfHalvedValueWorks) {
    EXPECT_EQ("(((cosh(x)-1)/2)^(1/2))", convertToString(getHyperbolicSineOfHalvedValue("x", true)));
    EXPECT_EQ("(-1*(((cosh(x)-1)/2)^(1/2)))", convertToString(getHyperbolicSineOfHalvedValue("x", false)));
}

TEST(HyperbolicEquationsTest, GetHyperbolicCosineOfHalvedValueWorks) {
    EXPECT_EQ("(((cosh(x)+1)/2)^(1/2))", convertToString(getHyperbolicCosineOfHalvedValue("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicArcSineDefinitionWorks) {
    EXPECT_EQ("arcsinh(x) = ln((x+(((x^2)+1)^(1/2))))", convertToString(getHyperbolicArcSineDefinition("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicArcCosineDefinitionWorks) {
    EXPECT_EQ("arccosh(x) = ln((x+(((x^2)-1)^(1/2))))", convertToString(getHyperbolicArcCosineDefinition("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicArcTangentDefinitionWorks) {
    EXPECT_EQ("arctanh(x) = ((1/2)*ln(((1-x)/(1+x))))", convertToString(getHyperbolicArcTangentDefinition("x")));
}

TEST(HyperbolicEquationsTest, GetHyperbolicArcCotangentDefinitionWorks) {
    EXPECT_EQ("arccoth(x) = ((1/2)*ln(((x+1)/(x-1))))", convertToString(getHyperbolicArcCotangentDefinition("x")));
}

}  // namespace algebra

}  // namespace alba
