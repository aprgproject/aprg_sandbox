#pragma once

#include <Term.hpp>
#include <TermsWithAssociation.hpp>

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

    TermsWithAssociation::TermsWithDetails getNumeratorAndDenominatorAsTermWithDetails() const;

private:
    void removeSameTermsInNumeratorAndDenominator();
    bool areTermsEmptyOrValueOne(Terms const& terms) const;
    Terms m_numerators;
    Terms m_denominators;
};

}

}
