#pragma once

#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Constructs/TermsOverTerms.hpp>
#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Container/AlbaConfigurationHolder.hpp>

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
        bool shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase;
        bool shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision;
        bool shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt;
        bool shouldSimplifyByRationalizingNumerator;
        bool shouldSimplifyByRationalizingDenominator;
        bool shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables;
        bool shouldSimplifyToFactors;
        bool shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
        bool shouldNotSimplifyExpressionRaiseToAConstantByDistributingConstantToEachBase;
        bool shouldPerformDebug;
    };

    class Configuration
            : public AlbaConfigurationHolder<ConfigurationDetails>
    {};

    class ScopeObject : public AlbaConfigurationScopeObject<ConfigurationDetails>
    {};

    SimplificationOfExpression();
    SimplificationOfExpression(Expression const& expression);

    static bool shouldSimplifyToACommonDenominator();
    static bool shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase();
    static bool shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision();
    static bool shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt();
    static bool shouldSimplifyByRationalizingNumerator();
    static bool shouldSimplifyByRationalizingDenominator();
    static bool shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables();
    static bool shouldSimplifyToFactors();
    static bool shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue();
    static bool shouldNotSimplifyExpressionRaiseToAConstantByDistributingConstantToEachBase();
    static bool shouldPerformDebug();

    Expression getExpression() const;

    void setExpression(Expression const& expression);

    void simplify();

private:
    bool isChangeDetected(
            Expression const& expression1,
            Expression const& expression2) const;

    void simplifyExpressionUntilNoChange();
    void simplifyExpression(Expression & expression);
    void simplifyExpressionUntilNoChangeInitiallyIfNeeded();
    void simplifyToACommonDenominatorIfNeeded();
    void simplifyBySubstitutingExpressionAndFunctionsToVariablesIfNeeded();

    void processTermsBaseOnOperatorLevel(
            Expression & expression,
            TermsWithDetails const& termsToProcess,
            OperatorLevel const operatorLevel);
    void processAndSaveTermsForAdditionAndSubtraction(
            Expression & expression,
            TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForMultiplicationAndDivision(
            Expression & expression,
            TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForRaiseToPower(
            Expression & expression,
            TermsWithDetails const& termsToProcess);

    //functions for addition/subtraction
    void addOrSubtractTermsWithExpressions(
            Term & combinedTerm,
            TermsWithDetails const& termsWithExpressions) const;

    //functions for multiplication/division
    void simplifyByCombiningRadicalsInMultiplicationAndDivisionIfNeeded(
            TermsWithDetails & termsInMultiplicationAndDivision) const;
    Term getCombinedTermAndSimplifyByRationalizingNumeratorOrDenominatorIfNeeded(
            TermsOverTerms const& termsOverTerms) const;

    //functions for raise to power
    Term getCombinedTermUsingTermsRaiseToTerms(
            TermRaiseToTerms const& termRaiseToTerms);
    Term getEachBasesRaisedToConstantIfPossible(
            TermRaiseToTerms const& termRaiseToTerms);

    // other functions
    bool shouldDistributeExponentConstantToEachBase() const;
    Factorization::ConfigurationDetails getFactorizationConfiguration() const;
    bool tryToSubstituteSubExpressionOrSubFunctionAndReturnIfContinue(Expression const& expression);
    Expression getNewExpressionWithSubstitutedVariableForTerm(Term const& mainExpression, Term const& termToSubstitute);
    void convertPolynomialOverPolynomialIfNeeded();
    void convertPolynomialToPolynomialOverPolynomial(Term & term);
    void convertPolynomialToPolynomialOverPolynomial(Expression & expression);

    Expression m_expression;
};

}

}

template <>
algebra::Simplification::SimplificationOfExpression::ConfigurationDetails
getDefaultConfigurationDetails<algebra::Simplification::SimplificationOfExpression::ConfigurationDetails>();

}
