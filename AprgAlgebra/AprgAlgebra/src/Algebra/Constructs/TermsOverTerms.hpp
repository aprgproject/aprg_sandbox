#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

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
    TermsOverTerms(TermsWithDetails const& numerators, TermsWithDetails const& denominators);

    Terms const& getNumerators() const;
    Terms const& getDenominators() const;
    TermsWithDetails getNumeratorAndDenominatorAsTermWithDetails() const;
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
    Polynomial multiplyPolynomialTerms(Terms const& polynomialTerms) const;
    bool removeTermsIfNeededAndReturnIfSomeTermsAreRemoved(
            Terms & numerators,
            Terms & denominators);
    void clearTermsThenEmplacePolynomialAndRemainingTerms(
            Polynomial const& polynomialNumerator,
            Terms const& remainingNumerators,
            Terms & termsToUpdate) const;
    void emplacePolynomialIfNeeded(Terms & termsResult, Polynomial const& polynomialNumerator) const;
    void retrievePolynomialAndNonPolynomialsTerms(
            Terms const& termsToCheck,
            Polynomial & polynomial,
            Terms & nonPolynomialTerms) const;
    void removeSameTermsInNumeratorAndDenominator(
            Terms & numeratorTerms,
            Terms & denominatorTerms);
    void removeTermsThatHaveNoEffect(Terms & terms) const;
    void simplifyPolynomialNumeratorAndPolynomialDenominator(
            Polynomial & polynomialNumerator,
            Polynomial & polynomialDenominator) const;    void simplifyMonomialsToPolynomialsOverPolynomials();
    void simplifyPolynomialsToPolynomialsOverPolynomials();
    Terms m_numerators;
    Terms m_denominators;};

using VectorOfTermsOverTerms = std::vector<TermsOverTerms>;

}

}
