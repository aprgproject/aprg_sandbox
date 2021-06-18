#pragma once

#include <Term.hpp>
#include <TermsWithAssociation.hpp>

#include <string>

namespace alba
{
namespace equation
{
class TermsOverTerms
{
public:
    TermsOverTerms(Terms const& numerators, Terms const& denominators);
    TermsOverTerms(TermsWithAssociation::TermsWithDetails const& numerators, TermsWithAssociation::TermsWithDetails const& denominators);

    void simplify();
    void simplifyToFactors();

    TermsWithAssociation::TermsWithDetails getNumeratorAndDenominatorAsTermWithDetails() const;
    Terms getNumerators() const;
    Terms getDenominators() const;

    std::string getDisplayableString() const;

private:
    void simplifyPolynomialsAndShouldFactorize(bool const shouldFactorize);
    void removeSameTermsInNumeratorAndDenominator();    bool areTermsEmptyOrValueOne(Terms const& terms) const;
    Terms m_numerators;
    Terms m_denominators;
};
}

}
