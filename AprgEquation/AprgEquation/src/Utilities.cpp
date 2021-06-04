#include "Utilities.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

namespace equation
{

bool isOperator(string const& variableOrOperator)
{
    return "+" == variableOrOperator ||
            "-" == variableOrOperator ||
            "*" == variableOrOperator ||
            "/" == variableOrOperator ||
            "^" == variableOrOperator;
}

bool isOperatorForMultipleTerms(string const& variableOrOperator)
{
    return "+" == variableOrOperator || "-" == variableOrOperator;
}

bool canBeAddedOrSubtracted(Monomial const& monomial1, Monomial const& monomial2)
{
    Monomial::VariablesToExponentsMap const& variablesMap1(monomial1.getVariablesToExponentsMapConstReference());
    Monomial::VariablesToExponentsMap const& variablesMap2(monomial2.getVariablesToExponentsMapConstReference());
    bool result(false);
    if(variablesMap1.size() == variablesMap2.size())
    {
        using MapConstIterator=Monomial::VariablesToExponentsMap::const_iterator;
        using MismatchResultType=pair<MapConstIterator, MapConstIterator>;
        MismatchResultType mismatchResult = mismatch(variablesMap1.cbegin(), variablesMap1.end(), variablesMap2.cbegin());
        result = mismatchResult.first == variablesMap1.cend();
    }
    return result;
}

bool canBeAddedOrSubtracted(Monomial const& monomial, Variable const& variable)
{
    Monomial::VariablesToExponentsMap const& variablesMap(monomial.getVariablesToExponentsMapConstReference());
    string variableName(variable.getVariableName());
    bool result(false);
    if(variablesMap.size() == 1)
    {
        if(variablesMap.find(variableName) != variablesMap.cend())
        {
            result = variablesMap.at(variableName)==1;
        }
    }
    return result;
}

void performChangeForVariables(
        Monomial::VariablesToExponentsMap & variablesMap,
        Monomial::ChangeExponentsForVariableFunction const& changeVariablesFunction)
{
    for(Monomial::VariablesToExponentsMap::iterator it=variablesMap.begin(); it!=variablesMap.end(); it++)
    {
        changeVariablesFunction(it->first, it->second);
    }
}

Monomial::VariablesToExponentsMap combineVariableExponentMapByMultiplication(
        Monomial::VariablesToExponentsMap const& variablesMap1,
        Monomial::VariablesToExponentsMap const& variablesMap2)
{
    Monomial::VariablesToExponentsMap newVariableMap;
    for(Monomial::VariableExponentPair const variableExponentPair : variablesMap1)
    {
        newVariableMap[variableExponentPair.first] = newVariableMap[variableExponentPair.first] + variableExponentPair.second;
    }
    for(Monomial::VariableExponentPair const variableExponentPair : variablesMap2)
    {
        newVariableMap[variableExponentPair.first] = newVariableMap[variableExponentPair.first] + variableExponentPair.second;
    }
    return newVariableMap;
}

Monomial::VariablesToExponentsMap combineVariableExponentMapByDivision(
        Monomial::VariablesToExponentsMap const& variablesMap1,
        Monomial::VariablesToExponentsMap const& variablesMap2)
{
    Monomial::VariablesToExponentsMap newVariableMap;
    for(Monomial::VariableExponentPair const variableExponentPair : variablesMap1)
    {
        newVariableMap[variableExponentPair.first] = newVariableMap[variableExponentPair.first] + variableExponentPair.second;
    }
    for(Monomial::VariableExponentPair const variableExponentPair : variablesMap2)
    {
        newVariableMap[variableExponentPair.first] = newVariableMap[variableExponentPair.first] - variableExponentPair.second;
    }
    return newVariableMap;
}

void wrapTerms(WrappedTerms & wrappedTerms, Terms const& terms)
{
    BaseTermSharedPointers & baseTermPointers(wrappedTerms.getBaseTermPointersReference());
    for(Term const& term : terms)
    {
        baseTermPointers.emplace_back(new Term(term));    }
}

Terms unwrapTermsAndReturnTerms(WrappedTerms const& wrappedTerms)
{
    BaseTermSharedPointers const& baseTermPointers(wrappedTerms.getBaseTermPointersConstReference());
    Terms result;
    for(BaseTermSharedPointer const& baseTermPointer : baseTermPointers)
    {
        Term const& term(*dynamic_cast<Term const * const>(baseTermPointer.get()));
        result.emplace_back(term);    }
    return result;
}
Expression createExpression(Terms const& terms)
{
    Expression result;
    wrapTerms(result.getWrappedTermsReference(), terms);
    return result;
}

Terms getTermsInAnExpression(Expression const& expression)
{
    return unwrapTermsAndReturnTerms(expression.getWrappedTermsConstReference());
}

}

}
