#pragma once

#include <Equation/Term/Term.hpp>
#include <Equation/Term/TermsWithAssociation.hpp>

#include <string>
#include <vector>

namespace alba
{

namespace equation
{

class TermsOverTerms
{
public:
    TermsOverTerms(Terms const& numerators, Terms const& denominators);
    TermsOverTerms(TermsWithAssociation::TermsWithDetails const& numerators, TermsWithAssociation::TermsWithDetails const& denominators);

    Terms const& getNumerators() const;
    Terms const& getDenominators() const;
    TermsWithAssociation::TermsWithDetails getNumeratorAndDenominatorAsTermWithDetails() const;
    std::string getDisplayableString() const;

    void simplify();
    void simplifyToFactors();


private:
    void factorizeNumeratorsAndDenominators();
    void simplifyPolynomialsAndPutFactorsIfNeeded(bool const shouldFactorize);
    void removeSameTermsInNumeratorAndDenominator();
    void multiplyIfPolynomialElseEmplaceBack(
            Polynomial & polynomialResult,
            Terms & termsResult,
            Terms const& termsToCheck) const;
    void simplifyPolynomialNumeratorAndPolynomialDenominator(
            Polynomial & polynomialNumerator,
            Polynomial & polynomialDenominator) const;
    void emplaceAndFactorizeAllTermsIfNeeded(
            Terms & termsResult,
            Terms const& termsToCheck,
            bool const shouldFactorize) const;
    void emplaceAndFactorizeTermIfNeeded(
            Terms & termsResult,
            Term const& term,
            bool const shouldFactorize) const;
    void emplaceAndFactorizePolynomialIfNeeded(
            Terms & termsResult,
            Polynomial const& polynomialNumerator,
            bool const shouldFactorize) const;
    Terms m_numerators;
    Terms m_denominators;
};
using VectorOfTermsOverTerms = std::vector<TermsOverTerms>;

}
}
