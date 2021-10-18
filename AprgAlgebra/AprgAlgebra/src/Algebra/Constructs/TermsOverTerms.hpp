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
    using BaseToExponentMap = std::map<Term, AlbaNumber>;
    TermsOverTerms();
    TermsOverTerms(TermsWithDetails const& termsInMultiplicationAndDivision);
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

    void setAsShouldSimplifyToFactors(bool const shouldSimplifyToFactors);

    void simplify();

private:
    Term getCombinedTermAsFactors(
            TermsWithDetails const& termsWithDetails) const;
    void continueToSimplifyToFactors(
            Terms & factorizedNumerators,
            Terms & factorizedDenominators);
    void continueToSimplifyAndCombineFactors(
            Terms & factorizedNumerators,
            Terms & factorizedDenominators);
    Polynomial multiplyPolynomialTerms(Terms const& polynomialTerms) const;
    bool removeTermsIfNeededAndReturnIfSomeTermsAreRemoved(
            Terms & numerators,
            Terms & denominators);
    void updateBaseToExponentMap(
            BaseToExponentMap & baseToExponentMap,
            Terms const& termsToCheck,
            int const signToBePutWithExponent);
    void putTermsOnNumeratorAndDenominatorFromBaseExponentMap(
            Terms & numeratorTerms,
            Terms & denominatorTerms,
            BaseToExponentMap const& baseToExponentMap);
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
    void populateTermsWithBase(
            Terms & termsToUpdate,
            Term const& base,
            AlbaNumber const& exponent);
    void removeTermsThatHaveNoEffect(Terms & terms) const;
    void putTermsOnNumeratorAndDenominatorCorrectly(
            Terms & numerators,
            Terms & denominators);
    void putTermsToRetainAndOnTheOtherSide(
            Terms const& termsToSegregate,
            Terms & termsToRetain,
            Terms & termsToPutOnTheOtherSide) const;
    void simplifyPolynomialNumeratorAndPolynomialDenominator(
            Polynomial & polynomialNumerator,
            Polynomial & polynomialDenominator) const;
    void simplifyMonomialsToPolynomialOverPolynomial();
    void simplifyPolynomialsToPolynomialOverPolynomial();
    Terms m_numerators;
    Terms m_denominators;
    bool m_shouldSimplifyToFactors;
};

using VectorOfTermsOverTerms = std::vector<TermsOverTerms>;

}

}
