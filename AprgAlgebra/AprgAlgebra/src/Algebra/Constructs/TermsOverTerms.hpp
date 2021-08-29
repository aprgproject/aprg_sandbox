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
    TermsOverTerms();
    TermsOverTerms(Terms const& numerators, Terms const& denominators);
    TermsOverTerms(TermsWithAssociation::TermsWithDetails const& numerators, TermsWithAssociation::TermsWithDetails const& denominators);

    Terms const& getNumerators() const;
    Terms const& getDenominators() const;
    TermsWithAssociation::TermsWithDetails getNumeratorAndDenominatorAsTermWithDetails() const;
    Term getCombinedTerm() const;
    Term getCombinedNumerator() const;
    Term getCombinedDenominator() const;
    void retrievePolynomialAndNonPolynomialNumerators(
            Polynomial & polynomialNumerator,
            Terms & nonPolynomialNumerators) const;
    void retrievePolynomialAndNonPolynomialsDenominators(
            Polynomial & polynomialDenominator,
            Terms & nonPolynomialDenominators) const;
    std::string getDisplayableString() const;

    void simplify();
    void simplifyToFactors();

private:
    void retrievePolynomialAndNonPolynomialsTerms(
            Terms const& termsToCheck,
            Polynomial & polynomial,
            Terms & nonPolynomialTerms) const;
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
