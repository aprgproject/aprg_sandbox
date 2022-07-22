#include "SimplificationOfExpression.hpp"

#include <BooleanAlgebra/Operations/AccumulateOperations.hpp>
#include <BooleanAlgebra/Simplification/SimplificationUtilities.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>

using namespace std;

namespace alba
{

namespace booleanAlgebra
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

bool SimplificationOfExpression::shouldSimplifyWithOuterOrAndInnerAnd()
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyWithOuterOrAndInnerAnd;
}

bool SimplificationOfExpression::shouldSimplifyWithOuterAndAndInnerOr()
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyWithOuterAndAndInnerOr;
}

bool SimplificationOfExpression::shouldSimplifyByQuineMcKluskey()
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByQuineMcKluskey;
}

Expression SimplificationOfExpression::getExpression() const
{
    return m_expression;
}

void SimplificationOfExpression::simplify()
{
    if(shouldSimplifyByQuineMcKluskey())
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
                    SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyByQuineMcKluskey = false;

        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        Term quineTerm(m_expression);
        simplifyByQuineMcKluskey(quineTerm);
        m_expression.setTerm(quineTerm);

        simplifyExpressionUntilNoChange();
    }
    else
    {        simplifyExpressionUntilNoChange();
    }
}
bool SimplificationOfExpression::isChangeDetected(
        Expression const& expression1,
        Expression const& expression2) const
{
    return expression1 != expression2;
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
    WrappedTerms newWrappedTerms;
    OperatorLevel newOperatorLevel(expression.getCommonOperatorLevel());
    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
                newWrappedTerms,
                newOperatorLevel,
                expression.getWrappedTerms());

    // is clearing the expression and then copying simplified terms the most efficient way?
    expression.clear();
    processTermsBaseOnOperatorLevel(expression, newWrappedTerms, newOperatorLevel);
}

void SimplificationOfExpression::processTermsBaseOnOperatorLevel(
        Expression & expression,
        WrappedTerms const& termsToProcess,
        OperatorLevel const operatorLevel)
{
    switch(operatorLevel)
    {
    case OperatorLevel::Unknown:
    {
        expression.putWrappedTerms(termsToProcess);
        break;
    }
    case OperatorLevel::And:
    {
        processAndSaveTermsForAndOperation(expression, termsToProcess);
        break;
    }
    case OperatorLevel::Or:
    {
        processAndSaveTermsForOrOperation(expression, termsToProcess);
        break;
    }
    }
}

void SimplificationOfExpression::processAndSaveTermsForAndOperation(
        Expression & expression,
        WrappedTerms const& termsToProcess)
{
    Term combinedTerm;
    Terms newTerms(createUniqueTerms(termsToProcess));
    combineComplementaryTerms(newTerms, OperatorLevel::And);
    combineTermsByCheckingCommonFactor(newTerms, OperatorLevel::And);
    distributeTermsIfNeeded(combinedTerm, newTerms, OperatorLevel::And, OperatorLevel::Or);
    if(combinedTerm.isEmpty())
    {
        accumulateTermsWithAndOperation(combinedTerm, newTerms);
    }
    expression.setTerm(combinedTerm);
}

void SimplificationOfExpression::processAndSaveTermsForOrOperation(
        Expression & expression,
        WrappedTerms const& termsToProcess)
{
    Term combinedTerm;
    Terms newTerms(createUniqueTerms(termsToProcess));
    combineComplementaryTerms(newTerms, OperatorLevel::Or);
    combineTermsByCheckingCommonFactor(newTerms, OperatorLevel::Or);
    distributeTermsIfNeeded(combinedTerm, newTerms, OperatorLevel::Or, OperatorLevel::And);
    if(combinedTerm.isEmpty())
    {
        accumulateTermsWithOrOperation(combinedTerm, newTerms);
    }
    expression.setTerm(combinedTerm);
}

}

}

template <>
booleanAlgebra::Simplification::SimplificationOfExpression::ConfigurationDetails
getDefaultConfigurationDetails<alba::booleanAlgebra::Simplification::SimplificationOfExpression::ConfigurationDetails>()
{
    return booleanAlgebra::Simplification::SimplificationOfExpression::ConfigurationDetails
    {false, false, true};
}

}
