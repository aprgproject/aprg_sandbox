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
            TermsWithDetails const& exponents);

    Term getCombinedTerm() const;
    Term const& getBase() const;
    TermsWithDetails const& getExponents() const;

    void setBase(Term const& base);
    void simplify();

private:
    bool doesEvenExponentCancellationHappen() const;

    bool m_shouldSimplifyEvenExponentsCancellationWithAbsoluteValue;
    Term m_base;
    TermsWithDetails m_exponents;
};

}

}
