#pragma once

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Term/TermTypes/Expression.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

namespace Simplification
{

class SimplificationOfExpression
{
public:
    SimplificationOfExpression(Expression const& expression);

    Expression getExpression() const;

    void setAsShouldSimplifyToACommonDenominator(
            bool const shouldSimplifyToACommonDenominator);
    void setAsShouldSimplifyEvenExponentsCancellationWithAbsoluteValue(
            bool const shouldSimplifyEvenExponentsCancellationWithAbsoluteValue);
    void simplify();

private:
    bool isFurtherSimplificationNeeded(
            Expression const& beforeSimplify,
            Expression const& afterSimplify) const;
    bool didEvenExponentCancellationHappened(
            TermsWithAssociation::TermsWithDetails const& exponents) const;
    void prepareToACommonDenominatorIfNeeded();    void finalizeToACommonDenominatorIfNeeded();

    void simplifyExpression();
    void simplifyAndCopyTerms(            TermsWithAssociation::TermsWithDetails & termsToUpdate,
            TermsWithAssociation::TermsWithDetails const& termsToCheck);
    void simplifyAndCopyTermsFromAnExpressionAndSetOperatorLevelIfNeeded(
            TermsWithAssociation::TermsWithDetails & termsToUpdate,
            Expression const& expression,
            TermAssociationType const association);
    bool simplifyToACommonDenominatorForExpressionAndReturnIfChanged(Expression & expression);
    void simplifyTermsWithDetailsInExpressionToACommonDenominator(Expression & expression);
    bool tryToAddSubtractTermsOverTermsAndReturnIfChanged(Expression & addSubtractExpression);    void putNegativeExponentsOnDenominator(Expression & expression);

    void processTermsBaseOnOperatorLevel(
            TermsWithAssociation::TermsWithDetails const& termsToProcess);    void processAndSaveTermsForAdditionAndSubtraction(
            TermsWithAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForMultiplicationAndDivision(
            TermsWithAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForRaiseToPower(
            TermsWithAssociation::TermsWithDetails const& termsToProcess);

    void putNumeratorsInExpression(
            Expression& expression,
            ListOfPolynomialOverPolynomial const& numeratorsAndDenominators);
    void putNumeratorsInExpression(
            Expression& expression,
            TermsWithAssociation::TermsWithDetails const& numerators);
    void putDenominatorsInExpression(
            Expression& expression,
            ListOfPolynomialOverPolynomial const& numeratorsAndDenominators);
    void putDenominatorsInExpression(
            Expression& expression,
            TermsWithAssociation::TermsWithDetails const& denominators);


    //functions for addition
    void addOrSubtractTermsWithExpressions(
            Term & combinedTerm,
            TermsWithAssociation::TermsWithDetails const& termsWithExpressions) const;

    //functions for multiplication
    void processNumeratorsAndDenominators(
            Term & combinedTerm,
            TermsWithAssociation::TermsWithDetails const& numerators,
            TermsWithAssociation::TermsWithDetails const& denominators) const;

    //functions for raise to power
    void saveBaseAndExponentsToTerm(
            Term & combinedTerm,
            Term const& baseOfRaiseToPower,
            TermsWithAssociation::TermsWithDetails const& exponents);

    // other functions
    TermsWithAssociation getTermsWithAssociationAndReverseIfNeeded(
            Expression const& expression,
            TermAssociationType const association);
    void emplaceToNumeratorsAndDenominators(
            ListOfPolynomialOverPolynomial & numeratorsAndDenominators,
            Polynomial const& polynomial,
            TermAssociationType const termAssociationType);

    Expression m_expression;
    bool m_shouldSimplifyToACommonDenominator;
    bool m_shouldSimplifyEvenExponentsCancellationWithAbsoluteValue;
};

}

}

}
