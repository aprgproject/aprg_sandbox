#pragma once

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Term/TermTypes/Expression.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Container/AlbaSingleton.hpp>

namespace alba
{

namespace algebra
{

namespace Simplification
{

class SimplificationOfExpression
{
public:

    struct ConfigurationDetails
    {
        bool shouldSimplifyToACommonDenominator;
        bool shouldSimplifyEvenExponentsCancellationWithAbsoluteValue;
        bool shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision;
        bool shouldSimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivision;
        bool shouldSimplifyByCheckingPolynomialRaiseToANumber;
        bool shouldSimplifyByRationalizingNumerator;
        bool shouldSimplifyByRationalizingDenominator;
    };

    class Configuration : public AlbaSingleton<Configuration>
    {
    public:
        Configuration();
        ConfigurationDetails const& getConfigurationDetails();

        void setConfigurationDetails(ConfigurationDetails const& configurationDetails);
        void setConfigurationToDefault();
    private:
        ConfigurationDetails m_configurationDetails;
    };

    class ScopeObject
    {
    public:
        ScopeObject();
        ~ScopeObject();
        void setInThisScopeThisConfiguration(ConfigurationDetails const& configurationDetails) const;
    private:
        void setInThisScopeTheValuesBack() const;
        ConfigurationDetails m_savedConfigurationDetails;
    };

    static ConfigurationDetails getDefaultConfigurationDetails();

    SimplificationOfExpression();
    SimplificationOfExpression(Expression const& expression);

    Expression getExpression() const;

    void setExpression(Expression const& expression);

    void simplify();

private:
    bool shouldSimplifyToACommonDenominator() const;
    bool shouldSimplifyEvenExponentsCancellationWithAbsoluteValue() const;
    bool shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision() const;
    bool shouldSimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivision() const;
    bool shouldSimplifyByCheckingPolynomialRaiseToANumber() const;
    bool shouldSimplifyByRationalizingNumerator() const;
    bool shouldSimplifyByRationalizingDenominator() const;
    bool isFurtherSimplificationNeeded(
            Expression const& beforeSimplify,
            Expression const& afterSimplify) const;
    bool doesEvenExponentCancellationHappen(
            TermsWithDetails const& exponents) const;
    void prepareToACommonDenominatorIfNeeded();
    void finalizeToACommonDenominatorIfNeeded();

    void simplifyExpression();
    void simplifyAndCopyTerms(
            TermsWithDetails & termsToUpdate,
            TermsWithDetails const& termsToCheck);
    void simplifyAndCopyTermsFromAnExpressionAndSetOperatorLevelIfNeeded(
            TermsWithDetails & termsToUpdate,
            Expression const& expression,
            TermAssociationType const association);
    bool simplifyToACommonDenominatorForExpressionAndReturnIfChanged(Expression & expression);
    void simplifyTermsWithDetailsInExpressionToACommonDenominator(Expression & expression);
    bool tryToAddSubtractTermsOverTermsAndReturnIfChanged(Expression & addSubtractExpression);
    void putTermsWithNegativeExponentsOnDenominator(Expression & expression);

    void processTermsBaseOnOperatorLevel(
            TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForAdditionAndSubtraction(
            TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForMultiplicationAndDivision(
            TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForRaiseToPower(
            TermsWithDetails const& termsToProcess);

    void putNumeratorsInExpression(
            Expression& expression,
            ListOfPolynomialOverPolynomial const& numeratorsAndDenominators);
    void putNumeratorsInExpression(
            Expression& expression,
            TermsWithDetails const& numerators);
    void putDenominatorsInExpression(
            Expression& expression,
            ListOfPolynomialOverPolynomial const& numeratorsAndDenominators);
    void putDenominatorsInExpression(
            Expression& expression,
            TermsWithDetails const& denominators);

    //functions for addition/subtraction
    void addOrSubtractTermsWithExpressions(
            Term & combinedTerm,
            TermsWithDetails const& termsWithExpressions) const;

    //functions for multiplication/division
    void combineRadicalsInMultiplicationAndDivision(
            TermsWithDetails & termsWithDetails);
    void combineMonomialAndFirstRadicalInMultiplicationAndDivision(
            TermsWithDetails & termsWithDetails);

    //functions for raise to power
    void saveBaseAndExponentsToTerm(
            Term & combinedTerm,
            Term const& baseOfRaiseToPower,
            TermsWithDetails const& exponents);

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
