#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Simplification/SimplificationOfFunctionToTerm.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

TEST(SimplificationOfFunctionToTermTest, SimplifyWorksWhenInputIsConstant)
{
    SimplificationOfFunctionToTerm simplification;

    Term termToVerify1(simplification.simplifyToTerm(abs(Term(-5))));
    Term termToVerify2(simplification.simplifyToTerm(abs(Term(-5))));

    Term termToExpect1(Term(5));
    Term termToExpect2(Term(5));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(SimplificationOfFunctionToTermTest, SimplifyOfTrigonometricFunctionsWorksWhenShouldSimplifyTrigonometricFunctionsToSinAndCosIsFalse)
{
    SimplificationOfFunctionToTerm::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfFunctionToTerm::ConfigurationDetails>());
    configurationDetails.shouldSimplifyTrigonometricFunctionsToSinAndCos = false;
    SimplificationOfFunctionToTerm::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    SimplificationOfFunctionToTerm simplification;
    Term x("x");

    Term termToVerify1(simplification.simplifyToTerm(sin(x)));
    Term termToVerify2(simplification.simplifyToTerm(cos(x)));
    Term termToVerify3(simplification.simplifyToTerm(tan(x)));
    Term termToVerify4(simplification.simplifyToTerm(csc(x)));
    Term termToVerify5(simplification.simplifyToTerm(sec(x)));
    Term termToVerify6(simplification.simplifyToTerm(cot(x)));

    Term termToExpect1(Term(sin(x)));
    Term termToExpect2(Term(cos(x)));
    Term termToExpect3(Term(tan(x)));
    Term termToExpect4(Term(csc(x)));
    Term termToExpect5(Term(sec(x)));
    Term termToExpect6(Term(cot(x)));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
}

TEST(SimplificationOfFunctionToTermTest, SimplifyOfTrigonometricFunctionsWorksWhenShouldSimplifyTrigonometricFunctionsToSinAndCosIsTrue)
{
    SimplificationOfFunctionToTerm::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfFunctionToTerm::ConfigurationDetails>());
    configurationDetails.shouldSimplifyTrigonometricFunctionsToSinAndCos = true;
    SimplificationOfFunctionToTerm::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    SimplificationOfFunctionToTerm simplification;
    Term x("x");

    Term termToVerify1(simplification.simplifyToTerm(sin(x)));
    Term termToVerify2(simplification.simplifyToTerm(cos(x)));
    Term termToVerify3(simplification.simplifyToTerm(tan(x)));
    Term termToVerify4(simplification.simplifyToTerm(csc(x)));
    Term termToVerify5(simplification.simplifyToTerm(sec(x)));
    Term termToVerify6(simplification.simplifyToTerm(cot(x)));

    Term termToExpect1(Term(sin(x)));
    Term termToExpect2(Term(cos(x)));
    Term termToExpect3(Term(createExpressionIfPossible({Term(sin(x)), Term("/"), Term(cos(x))})));
    Term termToExpect4(Term(createExpressionIfPossible({Term(1), Term("/"), Term(sin(x))})));
    Term termToExpect5(Term(createExpressionIfPossible({Term(1), Term("/"), Term(cos(x))})));
    Term termToExpect6(Term(createExpressionIfPossible({Term(cos(x)), Term("/"), Term(sin(x))})));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
}

TEST(SimplificationOfFunctionToTermTest, SimplifyOfLogarithmicFunctionsWorksWhenShouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevelFalse)
{
    SimplificationOfFunctionToTerm::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfFunctionToTerm::ConfigurationDetails>());
    configurationDetails.shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel = false;
    SimplificationOfFunctionToTerm::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    SimplificationOfFunctionToTerm simplification;
    Term x("x");
    Term y("y");
    Term z("z");
    Term addAndSubtractExpression(createExpressionIfPossible({x, Term("+"), y, Term("-"), z}));
    Term multiplicationAndDivisionExpression(createExpressionIfPossible({x, Term("*"), y, Term("/"), z}));
    Term raiseToPowerExpression(createExpressionIfPossible({x, Term("^"), y, Term("^"), z}));

    Term termToVerify1(simplification.simplifyToTerm(ln(x)));
    Term termToVerify2(simplification.simplifyToTerm(ln(addAndSubtractExpression)));
    Term termToVerify3(simplification.simplifyToTerm(ln(multiplicationAndDivisionExpression)));
    Term termToVerify4(simplification.simplifyToTerm(ln(raiseToPowerExpression)));
    Term termToVerify5(simplification.simplifyToTerm(log(x)));
    Term termToVerify6(simplification.simplifyToTerm(log(addAndSubtractExpression)));
    Term termToVerify7(simplification.simplifyToTerm(log(multiplicationAndDivisionExpression)));
    Term termToVerify8(simplification.simplifyToTerm(log(raiseToPowerExpression)));

    Term termToExpect1(Term(ln(x)));
    Term termToExpect2(Term(ln(addAndSubtractExpression)));
    Term termToExpect3(createExpressionIfPossible({Term(ln(x)), Term("+"), Term(ln(y)), Term("-"), Term(ln(z))}));
    Term termToExpect4(createExpressionIfPossible({Term(Monomial(1, {{"y", 1}, {"z", 1}})), Term("*"), Term(ln(x))}));
    Term termToExpect5(Term(log(x)));
    Term termToExpect6(Term(log(addAndSubtractExpression)));
    Term termToExpect7(createExpressionIfPossible({Term(log(x)), Term("+"), Term(log(y)), Term("-"), Term(log(z))}));
    Term termToExpect8(createExpressionIfPossible({Term(Monomial(1, {{"y", 1}, {"z", 1}})), Term("*"), Term(log(x))}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
    EXPECT_EQ(termToExpect7, termToVerify7);
    EXPECT_EQ(termToExpect8, termToVerify8);
}

TEST(SimplificationOfFunctionToTermTest, SimplifyOfLogarithmicFunctionsWorksWhenShouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevelTrue)
{
    SimplificationOfFunctionToTerm::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfFunctionToTerm::ConfigurationDetails>());
    configurationDetails.shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel = true;
    SimplificationOfFunctionToTerm::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    SimplificationOfFunctionToTerm simplification;
    Term x("x");
    Term y("y");
    Term z("z");
    Term addAndSubtractExpression(createExpressionIfPossible({x, Term("+"), y, Term("-"), z}));
    Term multiplicationAndDivisionExpression(createExpressionIfPossible({x, Term("*"), y, Term("/"), z}));
    Term raiseToPowerExpression(createExpressionIfPossible({x, Term("^"), y, Term("^"), z}));

    Term termToVerify1(simplification.simplifyToTerm(ln(x)));
    Term termToVerify2(simplification.simplifyToTerm(ln(addAndSubtractExpression)));
    Term termToVerify3(simplification.simplifyToTerm(ln(multiplicationAndDivisionExpression)));
    Term termToVerify4(simplification.simplifyToTerm(ln(raiseToPowerExpression)));
    Term termToVerify5(simplification.simplifyToTerm(log(x)));
    Term termToVerify6(simplification.simplifyToTerm(log(addAndSubtractExpression)));
    Term termToVerify7(simplification.simplifyToTerm(log(multiplicationAndDivisionExpression)));
    Term termToVerify8(simplification.simplifyToTerm(log(raiseToPowerExpression)));

    Term termToExpect1(Term(ln(x)));
    Term termToExpect2(Term(ln(addAndSubtractExpression)));
    Term termToExpect3(Term(ln(multiplicationAndDivisionExpression)));
    Term termToExpect4(Term(ln(raiseToPowerExpression)));
    Term termToExpect5(Term(log(x)));
    Term termToExpect6(Term(log(addAndSubtractExpression)));
    Term termToExpect7(Term(log(multiplicationAndDivisionExpression)));
    Term termToExpect8(Term(log(raiseToPowerExpression)));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
    EXPECT_EQ(termToExpect7, termToVerify7);
    EXPECT_EQ(termToExpect8, termToVerify8);
}

}

}

}
