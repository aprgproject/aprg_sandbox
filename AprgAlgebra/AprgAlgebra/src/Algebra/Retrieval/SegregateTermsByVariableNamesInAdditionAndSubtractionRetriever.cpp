#include "SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever.hpp"

#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Term/Utilities/EnumHelpers.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace algebra
{

SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever()
    : m_variableNameExpressionMap()
    , m_remainingTermsExpression(OperatorLevel::AdditionAndSubtraction, {})
{}

SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::VariableNameToExpressionMap const&
SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::getVariableNameToExpressionMap() const
{
    return m_variableNameExpressionMap;
}

Expression const& SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::getRemainingTermsExpression() const
{
    return m_remainingTermsExpression;
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::putVariableNamesToCheckInOrder(
        strings const& namesInOrder)
{
    for(string const& name : namesInOrder)
    {
        m_variableNameExpressionMap.emplace(name, Expression(OperatorLevel::AdditionAndSubtraction, {}));
    }
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromConstant(
        Constant const& constant)
{
    retrieveFromConstant(constant, TermAssociationType::Positive);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromVariable(
        Variable const& variable)
{
    retrieveFromVariable(variable, TermAssociationType::Positive);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromMonomial(
        Monomial const& monomial)
{
    retrieveFromMonomial(monomial, TermAssociationType::Positive);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromPolynomial(
        Polynomial const& polynomial)
{
    retrieveFromPolynomial(polynomial, TermAssociationType::Positive);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromExpression(
        Expression const& expression)
{
    retrieveFromExpression(expression, TermAssociationType::Positive);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromFunction(
        Function const& functionObject)
{
    retrieveFromFunction(functionObject, TermAssociationType::Positive);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromTerm(
        Term const& term)
{
    retrieveFromTerm(term, TermAssociationType::Positive);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromConstant(
        Constant const& constant,
        TermAssociationType const overallAssociation)
{
    m_remainingTermsExpression.putTerm(Term(constant), overallAssociation);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromVariable(
        Variable const& variable,
        TermAssociationType const overallAssociation)
{
    bool isFound(false);
    for(auto & variableNameExpression : m_variableNameExpressionMap)
    {
        string const& savedVariableName(variableNameExpression.first);
        Expression & savedExpression(variableNameExpression.second);
        if(savedVariableName == variable.getVariableName())
        {
            savedExpression.putTerm(Term(variable), overallAssociation);
            isFound=true;
            break;
        }
    }
    if(!isFound)
    {
        m_remainingTermsExpression.putTerm(Term(variable), overallAssociation);
    }
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromMonomial(
        Monomial const& monomial,
        TermAssociationType const overallAssociation)
{
    bool isFound(false);
    for(auto & variableNameExpression : m_variableNameExpressionMap)
    {
        string const& savedVariableName(variableNameExpression.first);
        Expression & savedExpression(variableNameExpression.second);
        if(monomial.getExponentForVariable(savedVariableName) != 0)
        {
            savedExpression.putTerm(Term(monomial), overallAssociation);
            isFound=true;
            break;
        }
    }
    if(!isFound)
    {
        m_remainingTermsExpression.putTerm(Term(monomial), overallAssociation);
    }
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromPolynomial(
        Polynomial const& polynomial,
        TermAssociationType const overallAssociation)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        retrieveFromMonomial(monomial, overallAssociation);
    }
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromExpression(
        Expression const& expression,
        TermAssociationType const overallAssociation)
{
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        for(TermWithDetails const& termWithDetails
            : expression.getTermsWithAssociation().getTermsWithDetails())
        {
            TermAssociationType termAssociation;
            if(termWithDetails.hasPositiveAssociation())
            {
                termAssociation = overallAssociation;
            }
            else
            {
                termAssociation = getReversedAssociationType(overallAssociation);
            }
            retrieveFromTerm(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer), termAssociation);
        }
    }
    else
    {
        bool isFound(false);
        VariableNamesRetriever variableNamesRetriever;
        variableNamesRetriever.retrieveFromExpression(expression);
        VariableNamesSet const& namesInExpression(variableNamesRetriever.getSavedData());
        for(auto & variableNameExpression : m_variableNameExpressionMap)
        {
            string const& savedVariableName(variableNameExpression.first);
            Expression & savedExpression(variableNameExpression.second);
            if(namesInExpression.find(savedVariableName) != namesInExpression.cend())
            {
                savedExpression.putTerm(Term(expression), overallAssociation);
                isFound=true;
            }
        }
        if(!isFound)
        {
            m_remainingTermsExpression.putTerm(Term(expression), overallAssociation);
        }
    }
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromFunction(
        Function const& functionObject,
        TermAssociationType const overallAssociation)
{
    bool isFound(false);
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromFunction(functionObject);
    VariableNamesSet const& namesInFunction(variableNamesRetriever.getSavedData());
    for(auto & variableNameExpression : m_variableNameExpressionMap)
    {
        string const& savedVariableName(variableNameExpression.first);
        Expression & savedExpression(variableNameExpression.second);
        if(namesInFunction.find(savedVariableName) != namesInFunction.cend())
        {
            savedExpression.putTerm(Term(functionObject), overallAssociation);
            isFound=true;
        }
    }
    if(!isFound)
    {
        m_remainingTermsExpression.putTerm(Term(functionObject), overallAssociation);
    }
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromTerm(
        Term const& term,
        TermAssociationType const overallAssociation)
{
    if(term.isConstant())
    {
        retrieveFromConstant(term.getConstantConstReference(), overallAssociation);
    }
    else if(term.isVariable())
    {
        retrieveFromVariable(term.getVariableConstReference(), overallAssociation);
    }
    else if(term.isMonomial())
    {
        retrieveFromMonomial(term.getMonomialConstReference(), overallAssociation);
    }
    else if(term.isPolynomial())
    {
        retrieveFromPolynomial(term.getPolynomialConstReference(), overallAssociation);
    }
    else if(term.isExpression())
    {
        retrieveFromExpression(term.getExpressionConstReference(), overallAssociation);
    }
    else if(term.isFunction())
    {
        retrieveFromFunction(term.getFunctionConstReference(), overallAssociation);
    }
}

}

}
