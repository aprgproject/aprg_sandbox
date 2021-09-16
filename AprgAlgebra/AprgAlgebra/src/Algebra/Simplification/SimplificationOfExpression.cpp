#include "SimplificationOfExpression.hpp"

#include <Algebra/Constructs/AdditionAndSubtractionOfExpressions.hpp>
#include <Algebra/Constructs/AdditionAndSubtractionOfTermsOverTerms.hpp>
#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Constructs/MultiplicationAndDivisionOfRadicals.hpp>
#include <Algebra/Constructs/PolynomialRaiseToANumber.hpp>
#include <Algebra/Constructs/RationalizeTermOverTerm.hpp>
#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace alba::mathHelper;
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
    return SimplificationOfExpression::ConfigurationDetails{false, false, false, false, false, false};
}

SimplificationOfExpression::SimplificationOfExpression()    : m_expression()
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
    simplifyExpression();
}

bool SimplificationOfExpression::shouldSimplifyToACommonDenominator() const{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyToACommonDenominator;
}

bool SimplificationOfExpression::shouldSimplifyEvenExponentsCancellationWithAbsoluteValue() const
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyEvenExponentsCancellationWithAbsoluteValue;
}

bool SimplificationOfExpression::shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision() const
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision;
}

bool SimplificationOfExpression::shouldSimplifyByCheckingPolynomialRaiseToANumber() const
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByCheckingPolynomialRaiseToANumber;}

bool SimplificationOfExpression::shouldSimplifyByRationalizingNumerator() const
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByRationalizingNumerator;
}

bool SimplificationOfExpression::shouldSimplifyByRationalizingDenominator() const
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByRationalizingDenominator;
}

bool SimplificationOfExpression::isFurtherSimplificationNeeded(
        Expression const& beforeSimplify,
        Expression const& afterSimplify) const
{
    return beforeSimplify != afterSimplify && !hasNotANumber(afterSimplify);
}

void SimplificationOfExpression::simplifyExpression()
{
    Expression beforeSimplify;    do
    {
        beforeSimplify=m_expression;
        TermsWithDetails termsToUpdate;
        TermsWithAssociation & termsWithAssociation(m_expression.getTermsWithAssociationReference());
        simplifyAndCopyTermsAndDetermineOperatorLevel(termsToUpdate, termsWithAssociation.getTermsWithDetails());
        termsWithAssociation.clear();
        processTermsBaseOnOperatorLevel(termsToUpdate);
    }
    while(isFurtherSimplificationNeeded(beforeSimplify, m_expression));
}

void SimplificationOfExpression::simplifyAndCopyTermsAndDetermineOperatorLevel(
        TermsWithDetails & termsToUpdate,
        TermsWithDetails const& termsToCheck)
{    for(TermWithDetails const& termWithDetails : termsToCheck)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(term.isExpression())
        {
            Expression subExpression(term.getExpressionConstReference());
            subExpression.simplify();
            TermAssociationType subExpressionAssociation(termWithDetails.association);
            simplifyAndCopyTermsFromAnExpressionAndSetOperatorLevelIfNeeded(termsToUpdate, subExpression, subExpressionAssociation);
        }
        else if(isNonEmptyOrNonOperatorType(term))
        {            Term newTerm(term);
            newTerm.simplify();
            termsToUpdate.emplace_back(newTerm, termWithDetails.association);
        }
    }
}

void SimplificationOfExpression::simplifyAndCopyTermsFromAnExpressionAndSetOperatorLevelIfNeeded(
        TermsWithDetails & termsToUpdate,
        Expression const& subExpression,
        TermAssociationType const subExpressionAssociation)
{
    OperatorLevel subExpressionOperatorLevel(subExpression.getCommonOperatorLevel());
    if(subExpression.containsOnlyOnePositivelyAssociatedTerm()
            || OperatorLevel::Unknown == m_expression.getCommonOperatorLevel()
            || (subExpressionOperatorLevel == m_expression.getCommonOperatorLevel()
                && OperatorLevel::AdditionAndSubtraction == m_expression.getCommonOperatorLevel()
                && OperatorLevel::MultiplicationAndDivision == m_expression.getCommonOperatorLevel()))
    {
        m_expression.setCommonOperatorLevelIfStillUnknown(subExpression.getCommonOperatorLevel());
        TermsWithAssociation termsWithAssociation(getTermsWithAssociationAndReverseIfNeeded(subExpression, subExpressionAssociation));
        simplifyAndCopyTermsAndDetermineOperatorLevel(termsToUpdate, termsWithAssociation.getTermsWithDetails());
    }
    else
    {
        termsToUpdate.emplace_back(Term(subExpression), subExpressionAssociation);
    }
}

void SimplificationOfExpression::simplifyToACommonDenominatorIfNeeded()
{
    if(shouldSimplifyToACommonDenominator())
    {
        simplifyToACommonDenominatorForExpressionAndReturnIfChanged(m_expression);
    }
}
void SimplificationOfExpression::processTermsBaseOnOperatorLevel(
        TermsWithDetails const& termsToProcess)
{
    switch(m_expression.getCommonOperatorLevel())
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
    termRaiseToTerms.setAsShouldSimplifyByCheckingPolynomialRaiseToANumber(shouldSimplifyByCheckingPolynomialRaiseToANumber());
    termRaiseToTerms.setAsShouldSimplifyEvenExponentsCancellationWithAbsoluteValue(shouldSimplifyEvenExponentsCancellationWithAbsoluteValue());
    termRaiseToTerms.simplify();
    Term combinedTerm(termRaiseToTerms.getCombinedTerm());
    m_expression.setTerm(combinedTerm);
}

void SimplificationOfExpression::addOrSubtractTermsWithExpressions(        Term & combinedTerm,
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

TermsWithAssociation SimplificationOfExpression::getTermsWithAssociationAndReverseIfNeeded(        Expression const& expression,
        TermAssociationType const association)
{
    TermsWithAssociation termsWithAssociation(expression.getTermsWithAssociation());
    if(TermAssociationType::Negative == association)
    {
        termsWithAssociation.reverseTheAssociationOfTheTerms();
    }
    return termsWithAssociation;
}

}

}
}
