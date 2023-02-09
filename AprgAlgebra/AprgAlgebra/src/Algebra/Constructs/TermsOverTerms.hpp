#pragma once

#include <Algebra/Constructs/TermsRaiseToNumbers.hpp>
#include <Algebra/Constructs/TermsRaiseToTerms.hpp>
#include <Algebra/Factorization/FactorizationConfiguration.hpp>

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
    TermsOverTerms(TermsWithDetails const& termsInMultiplicationAndDivision);
    TermsOverTerms(Terms const& numerators, Terms const& denominators);

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
    TermsRaiseToTerms getTermsRaiseToTerms() const;

    void flip();

    void setAsShouldSimplifyToFactors(bool const shouldSimplifyToFactors);
    void setFactorizationConfigurationDetails(Factorization::ConfigurationDetails const& configurationDetails);

    void simplify();

private:
    Terms factorizeIfNeeded(Terms const& terms) const;
    Terms factorize(Terms const& terms) const;
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
    void putTermsOnNumeratorAndDenominatorBasedFromTermsRaiseToTerms(
            Terms & numeratorTerms,
            Terms & denominatorTerms,
            TermsRaiseToTerms const& termsRaiseToTerms);
    void putTermsOnNumeratorAndDenominatorBasedFromTermsRaiseToNumbers(
            Terms & numeratorTerms,
            Terms & denominatorTerms,
            TermsRaiseToNumbers const& termsRaiseToNumbers);
    void handleZerosInNumeratorOrDenominator(
            Terms& denominators,
            Terms& numerators);
    void populateTermsWithBase(
            Terms & termsToUpdate,
            Term const& base,
            AlbaNumber const& exponent);
    void removeTermsThatHaveNoEffect(Terms & terms) const;
    void putTermsOnNumeratorAndDenominatorCorrectly(
            Terms & numerators,
            Terms & denominators);
    void putTermsToRetainAndOnTheOtherSide(
            Terms const& termsToCheck,
            Terms & termsToRetain,
            Terms & termsToPutOnTheOtherSide) const;
    void simplifyPolynomialNumeratorAndPolynomialDenominator(
            Polynomial & polynomialNumerator,
            Polynomial & polynomialDenominator) const;
    void simplifyMonomialsToPolynomialOverPolynomial();
    void simplifyPolynomialsToPolynomialOverPolynomial();

    friend std::ostream & operator<<(std::ostream & out, TermsOverTerms const& termsOverTerms);

    Terms m_numerators;
    Terms m_denominators;
    bool m_shouldSimplifyToFactors;
    Factorization::ConfigurationDetails m_factorizationConfiguration;
};

using VectorOfTermsOverTerms = std::vector<TermsOverTerms>;

}

}
