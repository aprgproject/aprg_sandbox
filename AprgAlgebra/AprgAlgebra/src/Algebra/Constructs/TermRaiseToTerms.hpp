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
            Terms const& exponents);
    TermRaiseToTerms(
            Term const& base,
            Term const& exponent);

    bool isEmpty() const;
    bool doesEvenExponentCancellationHappen() const;
    Term getCombinedTerm() const;
    Term getCombinedExponents() const;
    Term const& getBase() const;
    TermsWithDetails const& getExponents() const;

    Term & getBaseReference();

    void setBase(Term const& base);
    void setBaseAndExponent(Term const& base, Term const& exponent);
    void setAsShouldSimplifyToFactors(bool const shouldSimplifyToFactors);
    void setAsShouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(bool const shouldSimplify);
    void setAsShouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(bool const shouldSimplify);
    void simplify();

private:
    void simplifyByCheckingPolynomialRaiseToAnUnsignedIntIfNeeded();
    void simplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseIfNeeded();

    void simplifyBaseAndExponents();
    void simplifyConstantRaiseToFunction(Term & base, TermsWithDetails & exponents, Term const& exponentCombinedTerm);
    void simplifyMonomialRaiseToConstant(Term & base, Monomial const& monomialBase, AlbaNumber const& exponent);
    void simplifyPolynomialRaiseToPositiveInteger(Term & base, Polynomial const& polynomialBase, unsigned int const exponent);
    void simplifyAdditionAndSubtractionExpressionRaiseToPositiveInteger(Term & base, Expression const& expressionBase, unsigned int const exponent);
    void simplifyConstantRaiseToMultiplicationAndDivisionExpression(Term & base, TermsWithDetails & exponents, Term const& exponentCombinedTerm);

    void initializeUsingTermsInRaiseToPowerExpression(
            TermsWithDetails const& termsInRaiseToPowerExpression);
    void initializeExponentsInTerms(
            Terms const& exponents);
    Term getCombinedBaseAndExponents() const;

    Term m_base;
    TermsWithDetails m_exponents;
    bool m_shouldSimplifyToFactors;
    bool m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt;
    bool m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase;
};

}

}
