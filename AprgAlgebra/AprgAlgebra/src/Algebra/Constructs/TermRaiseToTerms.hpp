#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>


namespace alba
{

namespace algebra
{

class TermRaiseToTerms
{
public:
    TermRaiseToTerms();
    TermRaiseToTerms(
            Term const& base,
            TermsWithAssociation::TermsWithDetails const& exponents);

    Term getCombinedTerm() const;
    Term const& getBase() const;
    TermsWithAssociation::TermsWithDetails const& getExponents() const;

    void setBase(Term const& base);
    void simplify();

private:
    bool doesEvenExponentCancellationHappen() const;

    bool m_shouldSimplifyEvenExponentsCancellationWithAbsoluteValue;
    Term m_base;
    TermsWithAssociation::TermsWithDetails m_exponents;
};

}

}
