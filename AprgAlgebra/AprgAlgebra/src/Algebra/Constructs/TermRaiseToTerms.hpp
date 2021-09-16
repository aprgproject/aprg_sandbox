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
            TermsWithDetails const& termsInRaiseToPowerExpression);
    TermRaiseToTerms(
            Term const& base,
            TermsWithDetails const& exponents);
    Term getCombinedTerm() const;
    Term const& getBase() const;
    TermsWithDetails const& getExponents() const;

    void setBase(Term const& base);
    void setAsShouldSimplifyByCheckingPolynomialRaiseToANumber(bool const shouldSimplifyCondition);
    void setAsShouldSimplifyEvenExponentsCancellationWithAbsoluteValue(bool const shouldSimplifyCondition);
    void simplify();

private:
    void processTermsInRaiseToPowerExpression(
            TermsWithDetails const& termsToProcess);
    bool doesEvenExponentCancellationHappen() const;
    Term combineBaseAndExponentsAndReturn() const;

    Term m_base;
    TermsWithDetails m_exponents;
    bool m_shouldSimplifyByCheckingPolynomialRaiseToANumber;
    bool m_shouldSimplifyEvenExponentsCancellationWithAbsoluteValue;
};

}
}
