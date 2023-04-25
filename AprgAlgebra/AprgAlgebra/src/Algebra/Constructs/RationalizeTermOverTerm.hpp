#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace algebra {

class RationalizeTermOverTerm {
public:
    struct RationalizationDetails {
        bool canBeRationalized;
        Term termToRationalize;
        Term otherTerm;
    };
    RationalizeTermOverTerm();
    RationalizeTermOverTerm(Term const& numerator, Term const& denominator);

    Term const& getNumerator() const;
    Term const& getDenominator() const;
    Term getCombinedTerm() const;

    void rationalizeNumerator();
    void rationalizeDenominator();

private:
    void rationalize(Term& termToRationalize, Term& otherTerm);
    void simplifyForRationalize(Term& term);
    void retrieveTermsForRationalization(Term& rationalizedTerm, Term& multiplier, Term const& term) const;
    void retrieveTermsForRationalizationForPolynomial(
        Term& rationalizedTerm, Term& multiplier, Polynomial const& polynomial) const;
    void retrieveTermsForRationalizationForPolynomial(
        Term& rationalizedTerm, Term& multiplier, Monomial const& firstMonomial, Monomial const& secondMonomial) const;
    void retrieveTermsForRationalizationForPolynomialWhenExponentIsDivisibleByTwo(
        Term& rationalizedTerm, Term& multiplier, Monomial const& firstMonomial, Monomial const& secondMonomial) const;
    void retrieveTermsForRationalizationForPolynomialWhenExponentIsDivisibleByThree(
        Term& rationalizedTerm, Term& multiplier, Monomial const& firstMonomial, Monomial const& secondMonomial) const;
    void retrieveTermsForRationalizationForExpression(
        Term& rationalizedTerm, Term& multiplier, Expression const& expression) const;
    void retrieveTermsForRationalizationForExpression(
        Term& rationalizedTerm, Term& multiplier, TermWithDetails const& firstTermWithDetails,
        TermWithDetails const& secondTermWithDetails) const;
    void retrieveTermsForRationalizationForExpressionWhenExponentIsDivisibleByTwo(
        Term& rationalizedTerm, Term& multiplier, TermWithDetails const& firstTermWithDetails,
        TermWithDetails const& secondTermWithDetails) const;
    void retrieveTermsForRationalizationForExpressionWhenExponentIsDivisibleByThree(
        Term& rationalizedTerm, Term& multiplier, TermWithDetails const& firstTermWithDetails,
        TermWithDetails const& secondTermWithDetails) const;
    Term m_numerator;
    Term m_denominator;
};

}  // namespace algebra

}  // namespace alba
