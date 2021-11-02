#pragma once

#include <Algebra/Constructs/TermsRaiseToNumbers.hpp>
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
    TermsRaiseToNumbers getTermsRaiseToNumbers() const;
    std::string getDisplayableString() const;

    void flip();

    void setDontRemoveRationalization(bool const dontFactorizeAtStartOfSimplify);
    void setAsShouldSimplifyToFactors(bool const shouldSimplifyToFactors);
    void setAsShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(
            bool const shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue);

    void simplify();

private:
    Terms factorizeTermsAsNeeded(Terms const& terms) const;
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
            int const signToBePutWithExponent) const;
    void putTermsOnNumeratorAndDenominatorFromBaseExponentMap(
            Terms & numeratorTerms,
            Terms & denominatorTerms,
            BaseToExponentMap const& baseToExponentMap);
    void putTermsOnNumeratorAndDenominatorBasedFromTermsRaiseToNumbers(
            Terms & numeratorTerms,
            Terms & denominatorTerms,
            TermsRaiseToNumbers const& termsRaiseToNumbers);
    void clearTermsThenEmplacePolynomialAndRemainingTerms(
            Polynomial const& polynomialNumerator,
            Terms const& remainingNumerators,
            Terms & termsToUpdate) const;
    void emplacePolynomialIfNeeded(Terms & termsResult, Polynomial const& polynomialNumerator) const;
    void retrievePolynomialAndNonPolynomialsTerms(
            Terms const& termsToCheck,
            Polynomial & polynomial,
            Terms & nonPolynomialTerms) const;
    void calculateBasesAndExponentsAndPutThatToNumeratorsAndDenominators(
            Terms & numeratorTerms,
            Terms & denominatorTerms);
    void handleZerosInNumeratorOrDenominator(
            Terms& denominators,
            Terms& numerators);
    void populateTermsWithBase(
            Terms & termsToUpdate,
            Term const& base,
            AlbaNumber const& exponent);
    bool hasZero(Terms & terms) const;
    void removeTermsThatHaveNoEffect(Terms & terms) const;
    void putTermsOnNumeratorAndDenominatorCorrectly(
            Terms & numerators,
            Terms & denominators);
    void putTermsToRetainAndOnTheOtherSide(
            Terms const& termsToSegregate,
            Terms & termsToRetain,
            Terms & termsToPutOnTheOtherSide) const;
    void putBaseWithExponentsInNumeratorsAndDenominators(
            BaseToExponentMap const& baseToExponentMap);
    void simplifyPolynomialNumeratorAndPolynomialDenominator(
            Polynomial & polynomialNumerator,
            Polynomial & polynomialDenominator) const;
    void simplifyMonomialsToPolynomialOverPolynomial();
    void simplifyPolynomialsToPolynomialOverPolynomial();
    bool isPolynomialAndhasDoubleValue(Term const& term) const;
    Terms m_numerators;
    Terms m_denominators;
    bool m_dontRemoveRationalization;
    bool m_shouldSimplifyToFactors;
    bool m_shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
};

using VectorOfTermsOverTerms = std::vector<TermsOverTerms>;

}

}
