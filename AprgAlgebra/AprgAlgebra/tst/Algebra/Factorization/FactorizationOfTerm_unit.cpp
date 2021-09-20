#include <Algebra/Factorization/FactorizationOfTerm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

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

TEST(FactorizationOfTermTest, FactorizeTermsWorks)
{
    Terms terms{Term(5), Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})})};

    Terms factorizedTerms(factorizeTerms(terms));

    EXPECT_EQ(3U, factorizedTerms.size());
    EXPECT_EQ(Term(5), factorizedTerms.at(0));
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}), factorizedTerms.at(1));
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}), factorizedTerms.at(2));
}

}

}

}
