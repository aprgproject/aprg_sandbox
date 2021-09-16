#pragma once

#include <Algebra/Constructs/TermsOverTerms.hpp>
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
        bool shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase;
        bool shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision;
        bool shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt;
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
    bool shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase() const;
    bool shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision() const;
    bool shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt() const;
    bool shouldSimplifyByRationalizingNumerator() const;
    bool shouldSimplifyByRationalizingDenominator() const;
    bool isFurtherSimplificationNeeded(
            Expression const& beforeSimplify,
            Expression const& afterSimplify) const;

    void simplifyExpression();
    void simplifyToACommonDenominatorIfNeeded();

    void processTermsBaseOnOperatorLevel(
            TermsWithDetails const& termsToProcess,
            OperatorLevel const operatorLevel);
    void processAndSaveTermsForAdditionAndSubtraction(
            TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForMultiplicationAndDivision(
            TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForRaiseToPower(
            TermsWithDetails const& termsToProcess);

    //functions for addition/subtraction
    void addOrSubtractTermsWithExpressions(
            Term & combinedTerm,
            TermsWithDetails const& termsWithExpressions) const;

    //functions for multiplication/division
    void simplifyByCombiningRadicalsInMultiplicationAndDivisionIfNeeded(
            TermsWithDetails & numeratorsAndDenominators) const;
    Term getCombinedTermAndSimplifyByRationalizingNumeratorOrDenominatorIfNeeded(
            TermsOverTerms const& termsOverTerms) const;

    //functions for raise to power

    // other functions

    Expression m_expression;
};

}

}

}
