#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationOfExpression.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

namespace Factorization {

TEST(FactorizationOfExpressionTest, FactorizeAnExpressionWorksOnMultiplicationAndDivisionExpression) {
    Polynomial polynomial({Monomial(1, {{"x", 2}}), Monomial(-4, {})});
    Expression expressionToTest(createExpressionIfPossible({polynomial, "*", ln("x"), "/", sin("x")}));

    Terms termsToVerify(factorizeAnExpression(expressionToTest));

    Term termToExpect1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term termToExpect2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    Term termToExpect3(ln("x"));
    Term termToExpect4(createExpressionIfPossible({sin("x"), "^", -1}));
    ASSERT_EQ(4U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify[0]);
    EXPECT_EQ(termToExpect2, termsToVerify[1]);
    EXPECT_EQ(termToExpect3, termsToVerify[2]);
    EXPECT_EQ(termToExpect4, termsToVerify[3]);
}

TEST(FactorizationOfExpressionTest, FactorizeAnExpressionWorksOnAdditionAndSubtractionExpression) {    ConfigurationDetails configurationDetails(Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    Term part1(createExpressionIfPossible({Monomial(12, {{"x", 5}}), "*", sin("x")}));
    Term part2(createExpressionIfPossible({Monomial(4, {{"x", 7}}), "*", sin("x"), "*", cos("x")}));
    Term part3(createExpressionIfPossible({Monomial(8, {{"x", 9}}), "*", sin("x"), "*", sin("x")}));
    Expression expressionToTest(createExpressionIfPossible({part1, "+", part2, "-", part3}));

    Terms termsToVerify(factorizeAnExpression(expressionToTest));

    Term termToExpect1(4);
    Term termToExpect2(Monomial(1, {{"x", 5}}));
    Term termToExpect3(createExpressionIfPossible(
        {3, "+", Monomial(1, {{"x", 2}}), "*", cos("x"), "-", Monomial(2, {{"x", 4}}), "*", sin("x")}));
    Term termToExpect4(sin("x"));
    ASSERT_EQ(4U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify[0]);
    EXPECT_EQ(termToExpect2, termsToVerify[1]);
    EXPECT_EQ(termToExpect3, termsToVerify[2]);
    EXPECT_EQ(termToExpect4, termsToVerify[3]);
}

TEST(FactorizationOfExpressionTest, FactorizeAnExpressionWorksOnRaiseToPowerExpression) {    ConfigurationDetails configurationDetails(Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    Term base(createExpressionIfPossible({sin("x"), "*", cos("x")}));
    Expression expressionToTest(createExpressionIfPossible({base, "^", 17}));

    Terms termsToVerify(factorizeAnExpression(expressionToTest));

    Term termToExpect1(createExpressionIfPossible({cos("x"), "^", 17}));
    Term termToExpect2(createExpressionIfPossible({sin("x"), "^", 17}));
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify[0]);
    EXPECT_EQ(termToExpect2, termsToVerify[1]);
}

TEST(FactorizationOfExpressionTest, FactorizeAnExpressionWorksOnXToTheX) {    ConfigurationDetails configurationDetails(Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    Expression expressionToTest(createExpressionIfPossible({"x", "^", "x"}));

    Terms termsToVerify(factorizeAnExpression(expressionToTest));

    Term termToExpect(createExpressionIfPossible({"x", "^", "x"}));
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify[0]);
}

TEST(FactorizationOfExpressionTest, FactorizeAnExpressionWorksDerivativeDefinition) {    ConfigurationDetails configurationDetails(Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    Term deltaX("deltaX");
    Term deltaXPlusX(Polynomial{Monomial(1, {{"deltaX", 1}}), Monomial(1, {{"x", 1}})});
    Term part1(Monomial(1, {{"deltaX", 1}, {"x", AlbaNumber::createFraction(1, 3)}}));
    Term addend1(Monomial(1, {{"deltaX", 1}, {"x", AlbaNumber::createFraction(2, 3)}}));
    Term addend2(createExpressionIfPossible({part1, "*", deltaXPlusX, "^", AlbaNumber::createFraction(1, 3)}));
    Term addend3(createExpressionIfPossible({deltaX, "*", deltaXPlusX, "^", AlbaNumber::createFraction(2, 3)}));
    Expression expressionToTest(createExpressionIfPossible({addend1, "+", addend2, "+", addend3}));

    Terms termsToVerify(factorizeAnExpression(expressionToTest));

    string stringToExpect1("deltaX");
    string stringToExpect2("(1[x^(2/3)]+(1[x^(1/3)]*((1[deltaX] + 1[x])^(1/3)))+((1[deltaX] + 1[x])^(2/3)))");
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(stringToExpect1, convertToString(termsToVerify[0]));
    EXPECT_EQ(stringToExpect2, convertToString(termsToVerify[1]));
}

TEST(FactorizationOfExpressionTest, FactorizeAnExpressionWorksWhenSomeAddendsAreSame) {    ConfigurationDetails configurationDetails(Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);
    Term twoX(Monomial(2, {{"x", 1}}));
    Term cos2X(cos(twoX));
    Term addend1(createExpressionIfPossible({3, "*", cos2X, "^", 2}));
    Term addend2(createExpressionIfPossible({cos2X, "^", 3}));
    Expression expressionToTest(
        createExpressionIfPossible({1, "+", cos2X, "+", cos2X, "+", cos2X, "+", addend1, "+", addend2}));

    Terms termsToVerify(factorizeAnExpression(expressionToTest));

    string stringToExpect1("(1+cos(2[x])+cos(2[x])+cos(2[x])+(3*cos(2[x])*cos(2[x]))+(cos(2[x])^3))");
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(stringToExpect1, convertToString(termsToVerify[0]));
}

}  // namespace Factorization
}  // namespace algebra

}  // namespace alba