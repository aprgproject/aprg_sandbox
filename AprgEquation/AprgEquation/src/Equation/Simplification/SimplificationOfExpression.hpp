#pragma once

#include <Equation/Constructs/PolynomialOverPolynomial.hpp>
#include <Equation/Term/Expression.hpp>
#include <Equation/Term/Term.hpp>

namespace alba
{

namespace equation
{

namespace Simplification
{

class SimplificationOfExpression
{
public:
    SimplificationOfExpression(Expression const& expression);

    Expression getExpression() const;

    void simplify();
    void simplifyToACommonDenominator();

private:
    void simplifyAndCopyTerms(
            TermsWithAssociation::TermsWithDetails & termsToUpdate,
            TermsWithAssociation::TermsWithDetails const& termsToCheck);
    void simplifyAndCopyTermsFromAnExpressionAndSetOperatorLevelIfNeeded(
            TermsWithAssociation::TermsWithDetails & termsToUpdate,
            Expression const& expression,
            TermAssociationType const association);
    void simplifyFurtherIfNeeded(Expression const& beforeSimplify, Expression const& afterSimplify);
    bool simplifyToACommonDenominatorForExpressionAndReturnIfChanged(Expression & expression);
    void simplifyTermsWithDetailsInExpressionToACommonDenominator(Expression & expression);
    bool tryToAddSubtractTermsOverTermsAndReturnIfChanged(Expression & addSubtractExpression);
    void putNegativeExponentsOnDenominator(Expression & expression);

    void processTermsBaseOnOperatorLevel(
            TermsWithAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForAdditionAndSubtraction(
            TermsWithAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForMultiplicationAndDivision(
            TermsWithAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForRaiseToPower(
            TermsWithAssociation::TermsWithDetails const& termsToProcess);

    void putListOfPolynomialOverPolynomialInExpression(
            Expression& expression,
            ListOfPolynomialOverPolynomial const& numeratorsAndDenominators);
    void putPolynomialOverPolynomialInExpression(
            Expression & expression,
            PolynomialOverPolynomial const& numeratorAndDenominator);

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
};

}

}

}
