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
    TermRaiseToTerms(
            Term const& base,
            Terms const& exponents);

    bool doesEvenExponentCancellationHappen() const;
    Term getCombinedTerm() const;
    Term const& getBase() const;
    TermsWithDetails const& getExponents() const;

    void setBase(Term const& base);
    void setAsShouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(bool const shouldSimplify);
    void setAsShouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(bool const shouldSimplify);
    void simplify();
    
private:
    void simplifyByCheckingPolynomialRaiseToAnUnsignedIntIfNeeded();
    void simplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseIfNeeded();
    void simplifyBaseAndExponents();
    void initializeUsingTermsInRaiseToPowerExpression(
            TermsWithDetails const& termsInRaiseToPowerExpression);
    void initializeExponentsInTerms(
            Terms const& exponents);
    Term combineBaseAndExponentsAndReturn() const;

    Term m_base;
    TermsWithDetails m_exponents;
    bool m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt;
    bool m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase;
};

}

}
