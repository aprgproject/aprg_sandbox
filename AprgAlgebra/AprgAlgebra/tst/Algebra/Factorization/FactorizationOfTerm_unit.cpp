#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationOfTerm.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba{

namespace algebra
{
namespace Factorization
{

TEST(FactorizationOfTermTest, FactorizeTermWorksOnNonPolynomialTerm)
{
    Terms factorizedTerms(factorizeTerm(Term(5)));

    EXPECT_EQ(1U, factorizedTerms.size());
    EXPECT_EQ(Term(5), factorizedTerms.at(0));
}

TEST(FactorizationOfTermTest, FactorizeTermWorksOnPolynomialTerm)
{
    Terms factorizedTerms(factorizeTerm(Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})})));

    EXPECT_EQ(2U, factorizedTerms.size());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}), factorizedTerms.at(0));
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}), factorizedTerms.at(1));
}

TEST(FactorizationOfTermTest, FactorizeTermWorksOnExpressionTermWhenshouldSimplifyExpressionsToFactorsAsDefault)
{
    Term x("x");
    Expression expressionToTest(createExpressionIfPossible({Term(cos(x)), Term("*"), Term(sin(x)), Term("*"), Term(tan(x))}));

    Terms factorizedTerms(factorizeTerm(expressionToTest));

    Term termToExpect1(createExpressionIfPossible({Term(cos(x)), Term("*"), Term(sin(x)), Term("*"), Term(tan(x))}));
    EXPECT_EQ(1U, factorizedTerms.size());
    EXPECT_EQ(termToExpect1, factorizedTerms.at(0));
}

TEST(FactorizationOfTermTest, FactorizeTermWorksOnExpressionTermWhenShouldSimplifyExpressionsToFactorsIsTrue)
{
    ConfigurationDetails configurationDetails(
                Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term x("x");
    Expression expressionToTest(createExpressionIfPossible({Term(cos(x)), Term("*"), Term(sin(x)), Term("*"), Term(tan(x))}));

    Terms factorizedTerms(factorizeTerm(expressionToTest));

    EXPECT_EQ(3U, factorizedTerms.size());
    EXPECT_EQ(Term(cos(x)), factorizedTerms.at(0));
    EXPECT_EQ(Term(sin(x)), factorizedTerms.at(1));
    EXPECT_EQ(Term(tan(x)), factorizedTerms.at(2));
}

TEST(FactorizationOfTermTest, FactorizeTermsWorks)
{
    Terms terms{Term(5), Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})})};
    Terms factorizedTerms(factorizeTerms(terms));

    EXPECT_EQ(3U, factorizedTerms.size());    EXPECT_EQ(Term(5), factorizedTerms.at(0));
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}), factorizedTerms.at(1));
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}), factorizedTerms.at(2));
}

}

}

}
