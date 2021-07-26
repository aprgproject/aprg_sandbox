#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermsWithAssociation.hpp>

#include <string>
#include <vector>

namespace alba
{

namespace algebra
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
    void clearThenEmplacePolynomialAndRemainingTerms(
            Polynomial const& polynomialNumerator,
            Terms const& remainingNumerators,
            Terms & termsToUpdate) const;
    void factorizeNumeratorsAndDenominators();
    void emplaceAndFactorizeAllTerms(Terms & termsResult, Terms const& termsToCheck) const;
    void emplaceAndFactorizeTerm(Terms & termsResult, Term const& term) const;
    void emplaceAndFactorizePolynomialIfNeeded(Terms & termsResult, Polynomial const& polynomial) const;
    void emplacePolynomialIfNeeded(Terms & termsResult, Polynomial const& polynomialNumerator) const;
    Polynomial multiplyPolynomialTerms(Terms const& polynomialTerms) const;
    void removeTermsThatHasNoEffectInNumeratorAndDenominator();
    void removeSameTermsInNumeratorAndDenominator();
    void removeTermsThatHaveNoEffect(Terms & terms) const;
    void splitTermsToCombinedPolynomialAndRemainingTerms(
            Polynomial & combinedPolynomial,
            Terms & remainingTerms,
            Terms const& termsToCheck) const;
    void simplifyPolynomialNumeratorAndPolynomialDenominator(
            Polynomial & polynomialNumerator,
            Polynomial & polynomialDenominator) const;
    void simplifyMonomialsToPolynomialsOverPolynomials();
    void simplifyPolynomialsToPolynomialsOverPolynomials();
    Terms m_numerators;
    Terms m_denominators;
};

using VectorOfTermsOverTerms = std::vector<TermsOverTerms>;

}

}
