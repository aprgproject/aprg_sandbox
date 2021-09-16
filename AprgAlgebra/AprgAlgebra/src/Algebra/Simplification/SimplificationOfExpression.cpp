#include "SimplificationOfExpression.hpp"

#include <Algebra/Constructs/AdditionAndSubtractionOfExpressions.hpp>
#include <Algebra/Constructs/MultiplicationAndDivisionOfRadicals.hpp>
#include <Algebra/Constructs/RationalizeTermOverTerm.hpp>
#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

SimplificationOfExpression::Configuration::Configuration()
    : m_configurationDetails{getDefaultConfigurationDetails()}
{}

SimplificationOfExpression::ConfigurationDetails const&
SimplificationOfExpression::Configuration::getConfigurationDetails()
{
    return m_configurationDetails;
}

void SimplificationOfExpression::Configuration::setConfigurationDetails(
        ConfigurationDetails const& configurationDetails)
{
    m_configurationDetails = configurationDetails;
}

void SimplificationOfExpression::Configuration::setConfigurationToDefault()
{
    setConfigurationDetails(SimplificationOfExpression::getDefaultConfigurationDetails());
}

SimplificationOfExpression::ScopeObject::ScopeObject()
    : m_savedConfigurationDetails(Configuration::getInstance().getConfigurationDetails())
{}

SimplificationOfExpression::ScopeObject::~ScopeObject()
{
    setInThisScopeTheValuesBack();
}

void SimplificationOfExpression::ScopeObject::setInThisScopeThisConfiguration(
        SimplificationOfExpression::ConfigurationDetails const& configurationDetails) const
{
    SimplificationOfExpression::Configuration::getInstance().setConfigurationDetails(configurationDetails);
}

void SimplificationOfExpression::ScopeObject::setInThisScopeTheValuesBack() const
{
    SimplificationOfExpression::Configuration::getInstance().setConfigurationDetails(m_savedConfigurationDetails);
}

SimplificationOfExpression::ConfigurationDetails SimplificationOfExpression::getDefaultConfigurationDetails()
{
    return SimplificationOfExpression::ConfigurationDetails{false, false, false, false, false, false, false};
}

SimplificationOfExpression::SimplificationOfExpression()
    : m_expression()
{}

SimplificationOfExpression::SimplificationOfExpression(
        Expression const& expression)
    : m_expression(expression)
{}

Expression SimplificationOfExpression::getExpression() const
{
    return m_expression;
}

void SimplificationOfExpression::setExpression(
        Expression const& expression)
{
    m_expression = expression;
}

void SimplificationOfExpression::simplify()
{
    simplifyToACommonDenominatorIfNeeded();
    simplifyExpressionUntilNoChange();
}

bool SimplificationOfExpression::shouldSimplifyToACommonDenominator() const
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyToACommonDenominator;
}

bool SimplificationOfExpression::shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase() const
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase;
}

bool SimplificationOfExpression::shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision() const
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision;
}

bool SimplificationOfExpression::shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt() const
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt;
}

bool SimplificationOfExpression::shouldSimplifyByRationalizingNumerator() const
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByRationalizingNumerator;
}

bool SimplificationOfExpression::shouldSimplifyByRationalizingDenominator() const
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByRationalizingDenominator;
}

bool SimplificationOfExpression::shouldPerformDebug() const
{
    return Configuration::getInstance().getConfigurationDetails().shouldPerformDebug;
}

bool SimplificationOfExpression::isChangeDetected(
        Expression const& beforeSimplify,
        Expression const& afterSimplify) const
{
    return beforeSimplify != afterSimplify && !hasNotANumber(afterSimplify);
}

void SimplificationOfExpression::simplifyExpressionUntilNoChange()
{
    Expression beforeSimplify;
    do
    {
        beforeSimplify=m_expression;
        simplifyExpression();
    }
    while(isChangeDetected(beforeSimplify, m_expression));
}

void SimplificationOfExpression::simplifyExpression()
{
    TermsWithDetails newTermsWithDetails;
    OperatorLevel newOperatorLevel(m_expression.getCommonOperatorLevel());
    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
                newTermsWithDetails,
                newOperatorLevel,
                m_expression.getTermsWithAssociation().getTermsWithDetails());

    m_expression.clear();
    processTermsBaseOnOperatorLevel(newTermsWithDetails, newOperatorLevel);
}

void SimplificationOfExpression::simplifyToACommonDenominatorIfNeeded()
{
    if(shouldSimplifyToACommonDenominator())
    {
        simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(m_expression);
    }
}

void SimplificationOfExpression::processTermsBaseOnOperatorLevel(
        TermsWithDetails const& termsToProcess,
        OperatorLevel const operatorLevel)
{
    switch(operatorLevel)
    {
    case OperatorLevel::Unknown:
    {
        m_expression.putTermsWithDetails(termsToProcess);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    {
        processAndSaveTermsForAdditionAndSubtraction(termsToProcess);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    {
        processAndSaveTermsForMultiplicationAndDivision(termsToProcess);
        break;
    }
    case OperatorLevel::RaiseToPower:
    {
        processAndSaveTermsForRaiseToPower(termsToProcess);
        break;
    }
    }
}

void SimplificationOfExpression::processAndSaveTermsForAdditionAndSubtraction(
        TermsWithDetails const& termsToProcess)
{
    Term combinedTerm;
    TermsWithDetails termsWithNonExpressions;
    TermsWithDetails termsWithExpressions;
    segregateNonExpressionsAndExpressions(termsToProcess, termsWithNonExpressions, termsWithExpressions);
    accumulateTermsForAdditionAndSubtraction(combinedTerm, termsWithNonExpressions);
    addOrSubtractTermsWithExpressions(combinedTerm, termsWithExpressions);
    m_expression.setTerm(combinedTerm);
}

void SimplificationOfExpression::processAndSaveTermsForMultiplicationAndDivision(
        TermsWithDetails const& termsToProcess)
{
    TermsWithDetails termsInMultiplicationAndDivision(termsToProcess);
    simplifyByCombiningRadicalsInMultiplicationAndDivisionIfNeeded(termsInMultiplicationAndDivision);

    TermsWithDetails numerators;
    TermsWithDetails denominators;
    segregateTermsWithPositiveAndNegativeAssociations(termsInMultiplicationAndDivision, numerators, denominators);
    TermsOverTerms termsOverTerms(numerators, denominators);
    termsOverTerms.simplify();

    Term combinedTerm(getCombinedTermAndSimplifyByRationalizingNumeratorOrDenominatorIfNeeded(termsOverTerms));
    m_expression.setTerm(combinedTerm);
}

void SimplificationOfExpression::processAndSaveTermsForRaiseToPower(
        TermsWithDetails const& termsToProcess)
{
    TermRaiseToTerms termRaiseToTerms(termsToProcess);
    termRaiseToTerms.setAsShouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt());
    termRaiseToTerms.setAsShouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase());
    termRaiseToTerms.simplify();
    Term combinedTerm(termRaiseToTerms.getCombinedTerm());
    m_expression.setTerm(combinedTerm);
}

void SimplificationOfExpression::addOrSubtractTermsWithExpressions(
        Term & combinedTerm,
        TermsWithDetails const& termsWithExpressions) const
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    additionAndSubtraction.putTermsWithDetails(termsWithExpressions);
    additionAndSubtraction.combineExpressionsIfPossible();
    accumulateTermsForAdditionAndSubtraction(combinedTerm, additionAndSubtraction.getAsTermsWithDetails());
}

void SimplificationOfExpression::simplifyByCombiningRadicalsInMultiplicationAndDivisionIfNeeded(
        TermsWithDetails & termsInMultiplicationAndDivision) const
{
    if(shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision())
    {
        MultiplicationAndDivisionOfRadicals multiplicationAndDivisionOfRadicals(termsInMultiplicationAndDivision);
        multiplicationAndDivisionOfRadicals.simplify();
        termsInMultiplicationAndDivision = multiplicationAndDivisionOfRadicals.getTermsWithDetails();
    }
}

Term SimplificationOfExpression::getCombinedTermAndSimplifyByRationalizingNumeratorOrDenominatorIfNeeded(
        TermsOverTerms const& termsOverTerms) const
{
    Term combinedTerm;
    if(shouldSimplifyByRationalizingNumerator())
    {
        RationalizeTermOverTerm rationalizeTermOverTerm(
                    termsOverTerms.getCombinedNumerator(), termsOverTerms.getCombinedDenominator());
        rationalizeTermOverTerm.rationalizeNumerator();
        combinedTerm = rationalizeTermOverTerm.getCombinedTerm();
    }
    else if(shouldSimplifyByRationalizingDenominator())
    {
        RationalizeTermOverTerm rationalizeTermOverTerm(
                    termsOverTerms.getCombinedNumerator(), termsOverTerms.getCombinedDenominator());
        rationalizeTermOverTerm.rationalizeDenominator();
        combinedTerm = rationalizeTermOverTerm.getCombinedTerm();
    }
    else
    {
        combinedTerm = termsOverTerms.getCombinedTerm();
    }
    return combinedTerm;
}

}

}

}
