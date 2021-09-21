#include "SimplificationOfExpression.hpp"

#include <Algebra/Constructs/AdditionAndSubtractionOfExpressions.hpp>
#include <Algebra/Constructs/MultiplicationAndDivisionOfRadicals.hpp>
#include <Algebra/Constructs/RationalizeTermOverTerm.hpp>
#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Retrieval/ExpressionAndFunctionsRetriever.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>#include <Algebra/Substitution/SubstitutionOfTermsToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>#include <Algebra/Term/Utilities/SegregateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

SimplificationOfExpression::SimplificationOfExpression()
    : m_expression()
{}

SimplificationOfExpression::SimplificationOfExpression(
        Expression const& expression)
    : m_expression(expression)
{}

bool SimplificationOfExpression::shouldSimplifyToACommonDenominator()
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyToACommonDenominator;
}

bool SimplificationOfExpression::shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase()
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase;
}

bool SimplificationOfExpression::shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision()
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision;
}

bool SimplificationOfExpression::shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt()
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt;
}

bool SimplificationOfExpression::shouldSimplifyByRationalizingNumerator()
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByRationalizingNumerator;
}

bool SimplificationOfExpression::shouldSimplifyByRationalizingDenominator()
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByRationalizingDenominator;
}

bool SimplificationOfExpression::shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables()
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables;
}

bool SimplificationOfExpression::shouldNotSimplifyExpressionRaiseToAConstantByDistributingConstantToEachBase()
{
    return Configuration::getInstance().getConfigurationDetails().shouldNotSimplifyExpressionRaiseToAConstantByDistributingConstantToEachBase;
}

bool SimplificationOfExpression::shouldPerformDebug()
{
    return Configuration::getInstance().getConfigurationDetails().shouldPerformDebug;}

Expression SimplificationOfExpression::getExpression() const
{
    return m_expression;}

void SimplificationOfExpression::setExpression(
        Expression const& expression)
{
    m_expression = expression;
}

void SimplificationOfExpression::simplify()
{
    simplifyExpressionUntilNoChangeInitiallyIfNeeded();
    simplifyBySubstitutingExpressionAndFunctionsToVariablesIfNeeded();
    simplifyToACommonDenominatorIfNeeded();
    simplifyExpressionUntilNoChange();
}

bool SimplificationOfExpression::isChangeDetected(
        Expression const& expression1,
        Expression const& expression2) const
{
    return expression1 != expression2 && !hasNotANumber(expression2);
}

void SimplificationOfExpression::simplifyExpressionUntilNoChange()
{
    Expression beforeSimplify;
    do
    {
        beforeSimplify=m_expression;
        simplifyExpression(m_expression);
    }
    while(isChangeDetected(beforeSimplify, m_expression));
}

void SimplificationOfExpression::simplifyExpression(
        Expression & expression)
{
    TermsWithDetails newTermsWithDetails;
    OperatorLevel newOperatorLevel(expression.getCommonOperatorLevel());
    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
                newTermsWithDetails,
                newOperatorLevel,
                expression.getTermsWithAssociation().getTermsWithDetails());

    expression.clear();
    processTermsBaseOnOperatorLevel(expression, newTermsWithDetails, newOperatorLevel);
}

void SimplificationOfExpression::simplifyExpressionUntilNoChangeInitiallyIfNeeded()
{
    if(shouldSimplifyToACommonDenominator() || shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables())
    {
        simplifyExpressionUntilNoChange();
    }
}

void SimplificationOfExpression::simplifyToACommonDenominatorIfNeeded()
{
    if(shouldSimplifyToACommonDenominator())
    {
        simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(m_expression);
    }
}

void SimplificationOfExpression::simplifyBySubstitutingExpressionAndFunctionsToVariablesIfNeeded()
{
    if(shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables())
    {
        SimplificationOfExpression::ConfigurationDetails substitutionSimplificationConfigurationDetails(
                    Configuration::getInstance().getConfigurationDetails());
        substitutionSimplificationConfigurationDetails.shouldSimplifyToACommonDenominator = true;
        substitutionSimplificationConfigurationDetails.shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables = false;

        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(substitutionSimplificationConfigurationDetails);

        while(tryToSubstituteSubExpressionOrSubFunctionAndReturnIfContinue(m_expression));
    }
}
void SimplificationOfExpression::processTermsBaseOnOperatorLevel(
        Expression & expression,
        TermsWithDetails const& termsToProcess,        OperatorLevel const operatorLevel)
{
    switch(operatorLevel)
    {
    case OperatorLevel::Unknown:
    {
        expression.putTermsWithDetails(termsToProcess);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    {
        processAndSaveTermsForAdditionAndSubtraction(expression, termsToProcess);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    {
        processAndSaveTermsForMultiplicationAndDivision(expression, termsToProcess);
        break;
    }
    case OperatorLevel::RaiseToPower:
    {
        processAndSaveTermsForRaiseToPower(expression,termsToProcess);
        break;
    }
    }
}

void SimplificationOfExpression::processAndSaveTermsForAdditionAndSubtraction(
        Expression & expression,
        TermsWithDetails const& termsToProcess)
{
    Term combinedTerm;
    TermsWithDetails termsWithNonExpressions;
    TermsWithDetails termsWithExpressions;
    segregateNonExpressionsAndExpressions(termsToProcess, termsWithNonExpressions, termsWithExpressions);
    accumulateTermsForAdditionAndSubtraction(combinedTerm, termsWithNonExpressions);
    addOrSubtractTermsWithExpressions(combinedTerm, termsWithExpressions);
    expression.setTerm(combinedTerm);
}

void SimplificationOfExpression::processAndSaveTermsForMultiplicationAndDivision(
        Expression & expression,
        TermsWithDetails const& termsToProcess)
{
    TermsWithDetails termsInMultiplicationAndDivision(termsToProcess);
    simplifyByCombiningRadicalsInMultiplicationAndDivisionIfNeeded(termsInMultiplicationAndDivision);

    TermsOverTerms termsOverTerms(termsInMultiplicationAndDivision);
    termsOverTerms.simplify();

    Term combinedTerm(getCombinedTermAndSimplifyByRationalizingNumeratorOrDenominatorIfNeeded(termsOverTerms));
    expression.setTerm(combinedTerm);
}

void SimplificationOfExpression::processAndSaveTermsForRaiseToPower(
        Expression & expression,
        TermsWithDetails const& termsToProcess)
{
    TermRaiseToTerms termRaiseToTerms(termsToProcess);
    termRaiseToTerms.setAsShouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(
                shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt());
    termRaiseToTerms.setAsShouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(
                shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase());
    termRaiseToTerms.simplify();
    expression.setTerm(getCombinedTermUsingTermsRaiseToTerms(termRaiseToTerms));
}

void SimplificationOfExpression::addOrSubtractTermsWithExpressions(        Term & combinedTerm,
        TermsWithDetails const& termsWithExpressions) const
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction(termsWithExpressions);    additionAndSubtraction.combineExpressionsIfPossible();
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

Term SimplificationOfExpression::getCombinedTermUsingTermsRaiseToTerms(
        TermRaiseToTerms const& termRaiseToTerms)
{
    Term combinedTerm;
    Term eachBasesRaisedToConstant(getEachBasesRaisedToConstantIfPossible(termRaiseToTerms));
    if(!eachBasesRaisedToConstant.isEmpty())
    {
        combinedTerm = eachBasesRaisedToConstant;
    }
    else
    {
        combinedTerm = termRaiseToTerms.getCombinedTerm();
    }
    return combinedTerm;
}

Term SimplificationOfExpression::getEachBasesRaisedToConstantIfPossible(
        TermRaiseToTerms const& termRaiseToTerms)
{
    Term result;
    if(!shouldNotSimplifyExpressionRaiseToAConstantByDistributingConstantToEachBase())
    {
        Term const& base(termRaiseToTerms.getBase());
        TermsWithDetails const& exponents(termRaiseToTerms.getExponents());
        if(base.isExpression() && exponents.size() == 1)
        {
            Expression const& baseExpression(base.getExpressionConstReference());
            Term const& exponentTerm(getTermConstReferenceFromSharedPointer(exponents.front().baseTermSharedPointer));
            if(baseExpression.getCommonOperatorLevel() == OperatorLevel::MultiplicationAndDivision
                    && exponentTerm.isConstant())
            {
                Expression subBasesEachRaiseToConstant;
                subBasesEachRaiseToConstant.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
                for(TermWithDetails const& subBaseWithDetails
                    : baseExpression.getTermsWithAssociation().getTermsWithDetails())
                {
                    Term const& subBase(getTermConstReferenceFromSharedPointer(subBaseWithDetails.baseTermSharedPointer));
                    Term newSubBase(createExpressionIfPossible({subBase, Term("^"), exponentTerm}));
                    subBasesEachRaiseToConstant.putTerm(newSubBase, subBaseWithDetails.association);
                }
                result = Term(subBasesEachRaiseToConstant);
            }
        }
    }
    return result;
}

bool SimplificationOfExpression::tryToSubstituteSubExpressionOrSubFunctionAndReturnIfContinue(
        Expression const& expression)
{
    bool continueToTryToSubstitute = false;
    unsigned int oldNumberOfTerms = expression.getTermsWithAssociation().getTermsWithDetails().size();
    Terms expressionAndFunctionTerms(getSubExpressionsAndSubFunctions(expression));
    for(Term const& expressionOrFunctionTerm : expressionAndFunctionTerms)
    {
        Expression newExpression(getNewExpressionWithSubstitutedTerms(expressionOrFunctionTerm));
        unsigned int newNumberOfTerms = newExpression.getTermsWithAssociation().getTermsWithDetails().size();
        if(expression.getCommonOperatorLevel() != newExpression.getCommonOperatorLevel()
                || oldNumberOfTerms != newNumberOfTerms)
        {
            m_expression = newExpression;
            continueToTryToSubstitute = true;
            break;
        }
    }
    return continueToTryToSubstitute;
}

Expression SimplificationOfExpression::getNewExpressionWithSubstitutedTerms(
        Term const& expressionOrFunctionTerm)
{
    string variableNameForSubstitution(createVariableNameForSubstitution(expressionOrFunctionTerm));
    SubstitutionOfTermsToTerms substitutionToVariable{{expressionOrFunctionTerm, variableNameForSubstitution}};
    Term termWithNewVariable(substitutionToVariable.performSubstitutionTo(m_expression));
    SubstitutionOfVariablesToTerms substitutionFromVariable{{variableNameForSubstitution, expressionOrFunctionTerm}};
    Term termWithoutNewVariable(substitutionFromVariable.performSubstitutionTo(termWithNewVariable));
    return createOrCopyExpressionFromATerm(termWithoutNewVariable);
}

Terms SimplificationOfExpression::getSubExpressionsAndSubFunctions(
        Expression const& expression)
{    ExpressionAndFunctionsRetriever retriever;
    TermsWithDetails const& termsWithDetails(
                expression.getTermsWithAssociation().getTermsWithDetails());
    if(termsWithDetails.size() > 1)    {
        for(TermWithDetails const& termWithDetails : termsWithDetails)
        {
            retriever.retrieveFromTerm(
                        getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        }
    }
    Terms result;
    for(Term const& retrievedTerms : retriever.getSavedData())
    {
        if(shouldBeIncludedFromSubExpressionsAndSubFunctions(retrievedTerms))
        {
            result.emplace_back(retrievedTerms);
        }
    }
    return result;
}

bool SimplificationOfExpression::shouldBeIncludedFromSubExpressionsAndSubFunctions(
        Term const& term)
{
    bool result(false);
    if(term.isExpression())
    {
        Expression const& expression(term.getExpressionConstReference());
        result = OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel();
    }
    else if(term.isFunction())
    {
        result = true;
    }
    return result;
}

}

}

template <>
algebra::Simplification::SimplificationOfExpression::ConfigurationDetails
getDefaultConfigurationDetails<alba::algebra::Simplification::SimplificationOfExpression::ConfigurationDetails>()
{
    return algebra::Simplification::SimplificationOfExpression::ConfigurationDetails
    {false, false, false, false, false, false, false, false, false};
}

}