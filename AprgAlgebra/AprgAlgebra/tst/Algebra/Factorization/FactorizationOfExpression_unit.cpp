#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationOfExpression.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

TEST(FactorizationOfExpressionTest, FactorizeAnExpressionWorksOnMultiplicationAndDivisionExpression)
{
    Term x("x");
    Polynomial polynomial({Monomial(1, {{"x", 2}}), Monomial(-4, {})});
    Expression expressionToTest(createExpressionIfPossible({Term(polynomial), Term("*"), Term(ln(x)), Term("/"), Term(sin(x))}));

    Terms termsToVerify(factorizeAnExpression(expressionToTest));

    Term termToExpect1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term termToExpect2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    Term termToExpect3(ln(x));
    Term termToExpect4(createExpressionIfPossible({Term(sin(x)), Term("^"), Term(-1)}));
    ASSERT_EQ(4U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
    EXPECT_EQ(termToExpect2, termsToVerify.at(1));
    EXPECT_EQ(termToExpect3, termsToVerify.at(2));
    EXPECT_EQ(termToExpect4, termsToVerify.at(3));
}

TEST(FactorizationOfExpressionTest, FactorizeAnExpressionWorksOnAdditionAndSubtractionExpression)
{
    ConfigurationDetails configurationDetails(
                Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term x("x");
    Term part1(createExpressionIfPossible({Term(Monomial(12, {{"x", 5}})), Term("*"), Term(sin(x))}));
    Term part2(createExpressionIfPossible({Term(Monomial(4, {{"x", 7}})), Term("*"), Term(sin(x)), Term("*"), Term(cos(x))}));
    Term part3(createExpressionIfPossible({Term(Monomial(8, {{"x", 9}})), Term("*"), Term(sin(x)), Term("*"), Term(sin(x))}));
    Expression expressionToTest(createExpressionIfPossible({part1, Term("+"), part2, Term("-"), part3}));

    Terms termsToVerify(factorizeAnExpression(expressionToTest));

    Term termToExpect1(4);
    Term termToExpect2(Monomial(1, {{"x", 5}}));
    Term termToExpect3(createExpressionIfPossible(
    {Term(3), Term("+"), Term(Monomial(1, {{"x", 2}})), Term("*"), Term(cos(x)), Term("-"), Term(Monomial(2, {{"x", 4}})), Term("*"), Term(sin(x))}));
    Term termToExpect4(sin(x));
    ASSERT_EQ(4U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
    EXPECT_EQ(termToExpect2, termsToVerify.at(1));
    EXPECT_EQ(termToExpect3, termsToVerify.at(2));
    EXPECT_EQ(termToExpect4, termsToVerify.at(3));
}

TEST(FactorizationOfExpressionTest, FactorizeAnExpressionWorksOnRaiseToPowerExpression)
{
    ConfigurationDetails configurationDetails(
                Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term x("x");
    Term base(createExpressionIfPossible({Term(sin(x)), Term("*"), Term(cos(x))}));
    Expression expressionToTest(createExpressionIfPossible({base, Term("^"), Term(17)}));

    Terms termsToVerify(factorizeAnExpression(expressionToTest));

    Term termToExpect1(createExpressionIfPossible({Term(cos(x)), Term("^"), Term(17)}));
    Term termToExpect2(createExpressionIfPossible({Term(sin(x)), Term("^"), Term(17)}));
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
    EXPECT_EQ(termToExpect2, termsToVerify.at(1));
}

TEST(FactorizationOfExpressionTest, FactorizeAnExpressionWorksOnXToTheX)
{
    ConfigurationDetails configurationDetails(
                Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term x("x");
    Expression expressionToTest(createExpressionIfPossible({x, Term("^"), x}));

    Terms termsToVerify(factorizeAnExpression(expressionToTest));

    Term termToExpect(createExpressionIfPossible({x, Term("^"), x}));
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
}

TEST(FactorizationOfExpressionTest, FactorizeAnExpressionWorksDerivativeDefinition)
{
    ConfigurationDetails configurationDetails(
                Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term deltaX("deltaX");
    Term deltaXPlusX(Polynomial{Monomial(1, {{"deltaX", 1}}), Monomial(1, {{"x", 1}})});
    Term part1(Monomial(1, {{"deltaX", 1}, {"x", AlbaNumber::createFraction(1, 3)}}));
    Term addend1(Monomial(1, {{"deltaX", 1}, {"x", AlbaNumber::createFraction(2, 3)}}));
    Term addend2(createExpressionIfPossible({part1, Term("*"), deltaXPlusX, Term("^"), Term(AlbaNumber::createFraction(1, 3))}));
    Term addend3(createExpressionIfPossible({deltaX, Term("*"), deltaXPlusX, Term("^"), Term(AlbaNumber::createFraction(2, 3))}));
    Expression expressionToTest(createExpressionIfPossible({addend1, Term("+"), addend2, Term("+"), addend3}));

    Terms termsToVerify(factorizeAnExpression(expressionToTest));

    string stringToExpect1("deltaX");
    string stringToExpect2("(1[x^(2/3)]+(1[x^(1/3)]*((1[deltaX] + 1[x])^(1/3)))+((1[deltaX] + 1[x])^(2/3)))");
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(stringToExpect1, termsToVerify.at(0).getDisplayableString());
    EXPECT_EQ(stringToExpect2, termsToVerify.at(1).getDisplayableString());
}

TEST(FactorizationOfExpressionTest, FactorizeAnExpressionWorksWhenSomeAddendsAreSame)
{
    ConfigurationDetails configurationDetails(
                Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term twoX(Monomial(2, {{"x", 1}}));
    Term cos2X(cos(twoX));
    Term addend1(createExpressionIfPossible({Term(3), Term("*"), cos2X, Term("^"), Term(2)}));
    Term addend2(createExpressionIfPossible({cos2X, Term("^"), Term(3)}));
    Expression expressionToTest(createExpressionIfPossible(
    {Term(1), Term("+"), cos2X, Term("+"), cos2X, Term("+"), cos2X, Term("+"), addend1, Term("+"), addend2}));

    Terms termsToVerify(factorizeAnExpression(expressionToTest));

    string stringToExpect1("(1+cos(2[x])+cos(2[x])+cos(2[x])+(3*cos(2[x])*cos(2[x]))+(cos(2[x])^3))");
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(stringToExpect1, termsToVerify.at(0).getDisplayableString());
}

}

}

}
