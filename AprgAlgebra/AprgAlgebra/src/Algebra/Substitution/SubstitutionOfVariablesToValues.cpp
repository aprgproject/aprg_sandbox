#include "SubstitutionOfVariablesToValues.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;
using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace algebra
{

SubstitutionOfVariablesToValues::SubstitutionOfVariablesToValues()
{}

SubstitutionOfVariablesToValues::SubstitutionOfVariablesToValues(initializer_list<VariableValuePair> const& variablesWithValues)
{
    putVariablesWithValues(variablesWithValues);
}

SubstitutionOfVariablesToValues::SubstitutionOfVariablesToValues(VariablesToValuesMap const& variablesWithValues)
{
    putVariablesWithValues(variablesWithValues);
}

bool SubstitutionOfVariablesToValues::isEmpty() const
{
    return m_variableToValuesMap.empty();
}

bool SubstitutionOfVariablesToValues::isVariableFound(string const& variable) const
{
    return m_variableToValuesMap.find(variable) != m_variableToValuesMap.cend();
}

unsigned int SubstitutionOfVariablesToValues::getSize() const
{
    return m_variableToValuesMap.size();
}

AlbaNumber SubstitutionOfVariablesToValues::getValueForVariable(string const& variable) const
{
    AlbaNumber result;
    if(isVariableFound(variable))
    {
        result = m_variableToValuesMap.at(variable);
    }
    return result;
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Variable const& variable) const
{
    Term result;
    string variableName(variable.getVariableName());
    if(isVariableFound(variableName))
    {
        result = Term(getValueForVariable(variableName));
    }
    else
    {
        result = Term(variable);
    }
    return result;
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Monomial const& monomial) const
{
    return simplifyAndConvertMonomialToSimplestTerm(performSubstitutionForMonomial(monomial));
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Polynomial const& polynomial) const
{
    return simplifyAndConvertPolynomialToSimplestTerm(performSubstitutionForPolynomial(polynomial));
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Expression const& expression) const
{
    return simplifyAndConvertExpressionToSimplestTerm(performSubstitutionForExpression(expression));
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Function const& functionAsParameter) const
{
    return simplifyAndConvertFunctionToSimplestTerm(performSubstitutionForFunction(functionAsParameter));
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Term const& term) const
{
    Term newTerm(term);
    if(term.isVariable())
    {
        newTerm = performSubstitutionTo(term.getVariableConstReference());
    }
    else if(term.isMonomial())
    {
        newTerm = performSubstitutionTo(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        newTerm = performSubstitutionTo(term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        newTerm = performSubstitutionTo(term.getExpressionConstReference());
    }
    else if(term.isFunction())
    {
        newTerm = performSubstitutionTo(term.getFunctionConstReference());
    }
    return newTerm;
}

Equation SubstitutionOfVariablesToValues::performSubstitutionTo(
        Equation const& equation) const
{
    Equation simplifiedEquation(
                performSubstitutionTo(equation.getLeftHandTerm()),
                equation.getEquationOperator().getOperatorString(),
                performSubstitutionTo(equation.getRightHandTerm()));
    simplifiedEquation.simplify();
    return simplifiedEquation;
}

Monomial SubstitutionOfVariablesToValues::performSubstitutionForMonomial(Monomial const& monomial) const
{
    Monomial newMonomial(createMonomialFromConstant(monomial.getConstantConstReference()));
    Monomial::VariablesToExponentsMap previousVariableExponentMap(monomial.getVariablesToExponentsMapConstReference());
    for(auto const& variableExponentPair : previousVariableExponentMap)
    {
        if(isVariableFound(variableExponentPair.first))
        {
            newMonomial.setConstant(
                        newMonomial.getConstantConstReference()
                        * (getValueForVariable(variableExponentPair.first)^variableExponentPair.second));
        }
        else
        {
            newMonomial.putVariableWithExponent(variableExponentPair.first, variableExponentPair.second);
        }
    }
    return newMonomial;
}

Polynomial SubstitutionOfVariablesToValues::performSubstitutionForPolynomial(Polynomial const& polynomial) const
{
    Polynomial newPolynomial;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        newPolynomial.addMonomial(performSubstitutionForMonomial(monomial));
    }
    return newPolynomial;
}

Expression SubstitutionOfVariablesToValues::performSubstitutionForExpression(Expression const& expression) const
{
    Expression newExpression(expression);
    performSubstitutionForTermsWithAssociation(newExpression.getTermsWithAssociationReference());
    return newExpression;
}

Function SubstitutionOfVariablesToValues::performSubstitutionForFunction(Function const& functionAsParameter) const
{
    Function newFunction(functionAsParameter);
    getTermReferenceFromBaseTerm(newFunction.getInputTermReference())
            = performSubstitutionTo(functionAsParameter.getInputTermConstReference());
    return newFunction;
}

void SubstitutionOfVariablesToValues::performSubstitutionForTermsWithAssociation(TermsWithAssociation & termsWithAssociation) const
{
    for(TermWithDetails & termWithDetails : termsWithAssociation.getTermsWithDetailsReference())
    {
        Term & term(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        term = performSubstitutionTo(term);
    }
}

void SubstitutionOfVariablesToValues::putVariablesWithValues(initializer_list<VariableValuePair> const& variablesWithValues)
{
    for(VariableValuePair const& variableValuesPair : variablesWithValues)
    {
        putVariableWithValue(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfVariablesToValues::putVariablesWithValues(VariablesToValuesMap const& variablesWithValues)
{
    for(auto const& variableValuesPair : variablesWithValues)
    {
        putVariableWithValue(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfVariablesToValues::putVariableWithValue(string const& variable, AlbaNumber const& value)
{
    m_variableToValuesMap[variable]=value;
}

}

}
