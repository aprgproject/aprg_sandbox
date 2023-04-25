#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Simplification/SimplificationOfFunctionToTerm.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba {

namespace algebra {

namespace Simplification {

TEST(SimplificationOfFunctionToTermTest, SimplifyWorksWhenInputIsConstant) {
    SimplificationOfFunctionToTerm simplification;

    Term termToVerify1(simplification.simplifyToTerm(Functions::abs(-5)));
    Term termToVerify2(simplification.simplifyToTerm(Functions::abs(-5)));

    Term termToExpect1(5);
    Term termToExpect2(5);
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(
    SimplificationOfFunctionToTermTest,
    SimplifyOfTrigonometricFunctionsWorksWhenShouldSimplifyTrigonometricFunctionsToSinAndCosIsFalse) {
    SimplificationOfFunctionToTerm::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfFunctionToTerm::ConfigurationDetails>());
    configurationDetails.shouldSimplifyTrigonometricFunctionsToSinAndCos = false;
    SimplificationOfFunctionToTerm::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    SimplificationOfFunctionToTerm simplification;

    Term termToVerify1(simplification.simplifyToTerm(sin("x")));
    Term termToVerify2(simplification.simplifyToTerm(cos("x")));
    Term termToVerify3(simplification.simplifyToTerm(tan("x")));
    Term termToVerify4(simplification.simplifyToTerm(csc("x")));
    Term termToVerify5(simplification.simplifyToTerm(sec("x")));
    Term termToVerify6(simplification.simplifyToTerm(cot("x")));

    Term termToExpect1(sin("x"));
    Term termToExpect2(cos("x"));
    Term termToExpect3(tan("x"));
    Term termToExpect4(csc("x"));
    Term termToExpect5(sec("x"));
    Term termToExpect6(cot("x"));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
}

TEST(
    SimplificationOfFunctionToTermTest,
    SimplifyOfTrigonometricFunctionsWorksWhenShouldSimplifyTrigonometricFunctionsToSinAndCosIsTrue) {
    SimplificationOfFunctionToTerm::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfFunctionToTerm::ConfigurationDetails>());
    configurationDetails.shouldSimplifyTrigonometricFunctionsToSinAndCos = true;
    SimplificationOfFunctionToTerm::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    SimplificationOfFunctionToTerm simplification;

    Term termToVerify1(simplification.simplifyToTerm(sin("x")));
    Term termToVerify2(simplification.simplifyToTerm(cos("x")));
    Term termToVerify3(simplification.simplifyToTerm(tan("x")));
    Term termToVerify4(simplification.simplifyToTerm(csc("x")));
    Term termToVerify5(simplification.simplifyToTerm(sec("x")));
    Term termToVerify6(simplification.simplifyToTerm(cot("x")));

    Term termToExpect1(sin("x"));
    Term termToExpect2(cos("x"));
    Term termToExpect3(createExpressionIfPossible({sin("x"), "/", cos("x")}));
    Term termToExpect4(createExpressionIfPossible({1, "/", sin("x")}));
    Term termToExpect5(createExpressionIfPossible({1, "/", cos("x")}));
    Term termToExpect6(createExpressionIfPossible({cos("x"), "/", sin("x")}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
}

TEST(
    SimplificationOfFunctionToTermTest,
    SimplifyOfLogarithmicFunctionsWorksWhenShouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevelFalse) {
    SimplificationOfFunctionToTerm::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfFunctionToTerm::ConfigurationDetails>());
    configurationDetails.shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel = false;
    SimplificationOfFunctionToTerm::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    SimplificationOfFunctionToTerm simplification;
    Term addAndSubtractExpression(createExpressionIfPossible({"x", "+", "y", "-", "z"}));
    Term multiplicationAndDivisionExpression(createExpressionIfPossible({"x", "*", "y", "/", "z"}));
    Term raiseToPowerExpression(createExpressionIfPossible({"x", "^", "y", "^", "z"}));

    Term termToVerify1(simplification.simplifyToTerm(ln("x")));
    Term termToVerify2(simplification.simplifyToTerm(ln(addAndSubtractExpression)));
    Term termToVerify3(simplification.simplifyToTerm(ln(multiplicationAndDivisionExpression)));
    Term termToVerify4(simplification.simplifyToTerm(ln(raiseToPowerExpression)));
    Term termToVerify5(simplification.simplifyToTerm(log("x")));
    Term termToVerify6(simplification.simplifyToTerm(log(addAndSubtractExpression)));
    Term termToVerify7(simplification.simplifyToTerm(log(multiplicationAndDivisionExpression)));
    Term termToVerify8(simplification.simplifyToTerm(log(raiseToPowerExpression)));

    Term termToExpect1(ln("x"));
    Term termToExpect2(ln(addAndSubtractExpression));
    Term termToExpect3(createExpressionIfPossible({ln("x"), "+", ln("y"), "-", ln("z")}));
    Term termToExpect4(createExpressionIfPossible({Monomial(1, {{"y", 1}, {"z", 1}}), "*", ln("x")}));
    Term termToExpect5(log("x"));
    Term termToExpect6(log(addAndSubtractExpression));
    Term termToExpect7(createExpressionIfPossible({log("x"), "+", log("y"), "-", log("z")}));
    Term termToExpect8(createExpressionIfPossible({Monomial(1, {{"y", 1}, {"z", 1}}), "*", log("x")}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
    EXPECT_EQ(termToExpect7, termToVerify7);
    EXPECT_EQ(termToExpect8, termToVerify8);
}

TEST(
    SimplificationOfFunctionToTermTest,
    SimplifyOfLogarithmicFunctionsWorksWhenShouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevelTrue) {
    SimplificationOfFunctionToTerm::ConfigurationDetails configurationDetails(
        getDefaultConfigurationDetails<SimplificationOfFunctionToTerm::ConfigurationDetails>());
    configurationDetails.shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel = true;
    SimplificationOfFunctionToTerm::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    SimplificationOfFunctionToTerm simplification;
    Term addAndSubtractExpression(createExpressionIfPossible({"x", "+", "y", "-", "z"}));
    Term multiplicationAndDivisionExpression(createExpressionIfPossible({"x", "*", "y", "/", "z"}));
    Term raiseToPowerExpression(createExpressionIfPossible({"x", "^", "y", "^", "z"}));

    Term termToVerify1(simplification.simplifyToTerm(ln("x")));
    Term termToVerify2(simplification.simplifyToTerm(ln(addAndSubtractExpression)));
    Term termToVerify3(simplification.simplifyToTerm(ln(multiplicationAndDivisionExpression)));
    Term termToVerify4(simplification.simplifyToTerm(ln(raiseToPowerExpression)));
    Term termToVerify5(simplification.simplifyToTerm(log("x")));
    Term termToVerify6(simplification.simplifyToTerm(log(addAndSubtractExpression)));
    Term termToVerify7(simplification.simplifyToTerm(log(multiplicationAndDivisionExpression)));
    Term termToVerify8(simplification.simplifyToTerm(log(raiseToPowerExpression)));

    Term termToExpect1(ln("x"));
    Term termToExpect2(ln(addAndSubtractExpression));
    Term termToExpect3(ln(multiplicationAndDivisionExpression));
    Term termToExpect4(ln(raiseToPowerExpression));
    Term termToExpect5(log("x"));
    Term termToExpect6(log(addAndSubtractExpression));
    Term termToExpect7(log(multiplicationAndDivisionExpression));
    Term termToExpect8(log(raiseToPowerExpression));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
    EXPECT_EQ(termToExpect7, termToVerify7);
    EXPECT_EQ(termToExpect8, termToVerify8);
}

}  // namespace Simplification

}  // namespace algebra

}  // namespace alba
