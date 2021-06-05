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

Term createTerm(BaseTermUniquePointer const& baseTerm)
{
    Term* termPointer = dynamic_cast<Term*>(baseTerm.get());
    return *termPointer;
}

BaseTermUniquePointer createBaseTermUniquePointer(Term const& term)
{
    BaseTermUniquePointer baseTerm(new Term(term));
    return move(baseTerm);
}

Term convertMonomialToSimplestTerm(Monomial const& monomial)
{
    Term newTerm(monomial);
    if(monomial.isZero())
    {
        newTerm = Term(Constant(0));
    }
    else if(monomial.isConstantOnly())
    {
        newTerm = Term(monomial.getConstantConstReference());
    }
    else if(monomial.isVariableOnly())
    {
        newTerm = Term(monomial.getFirstVariableName());
    }
    return newTerm;
}

Monomial addSameMonomials(Monomial const& monomial1, Monomial const& monomial2)
{
    Monomial newMonomial;
    if(canBeAddedOrSubtracted(monomial1, monomial2))
    {
        newMonomial = Monomial(
                    monomial1.getConstantConstReference() + monomial2.getConstantConstReference(),
                    removeZeroExponents(monomial1.getVariablesToExponentsMapConstReference()));
    }
    return newMonomial;
}

Monomial subtractSameMonomials(Monomial const& monomial1, Monomial const& monomial2)
{
    Monomial newMonomial;
    if(canBeAddedOrSubtracted(monomial1, monomial2))
    {
        newMonomial = Monomial(
                    monomial1.getConstantConstReference() - monomial2.getConstantConstReference(),
                    removeZeroExponents(monomial1.getVariablesToExponentsMapConstReference()));
    }
    return newMonomial;
}

Monomial multiplyMonomials(Monomial const& monomial1, Monomial const& monomial2)
{
    Monomial::VariablesToExponentsMap newVariablesMap(
                combineVariableExponentMapByMultiplication(
                    monomial1.getVariablesToExponentsMapConstReference(),
                    monomial2.getVariablesToExponentsMapConstReference()));
    return Monomial(monomial1.getConstantConstReference()*monomial2.getConstantConstReference(), newVariablesMap);
}

Monomial divideMonomials(Monomial const& monomial1, Monomial const& monomial2)
{
    Monomial::VariablesToExponentsMap newVariablesMap(
                combineVariableExponentMapByDivision(
                    monomial1.getVariablesToExponentsMapConstReference(),
                    monomial2.getVariablesToExponentsMapConstReference()));
    return Monomial(monomial1.getConstantConstReference()/monomial2.getConstantConstReference(), newVariablesMap);
}

Monomial::VariablesToExponentsMap removeZeroExponents(Monomial::VariablesToExponentsMap const& variablesMap)
{
    Monomial::VariablesToExponentsMap newVariableMap;
    for(Monomial::VariableExponentPair const variableExponentPair : variablesMap)
    {
        if(variableExponentPair.second != 0)
        {
            newVariableMap.emplace(variableExponentPair.first, variableExponentPair.second);
        }
    }
    return newVariableMap;
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
    return removeZeroExponents(newVariableMap);
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
    return removeZeroExponents(newVariableMap);
}

void wrapTerms(WrappedTerms & wrappedTerms, Terms const& terms)
{
    BaseTermSharedPointers & baseTermPointers(wrappedTerms.getBaseTermPointersReference());
    for(Term const& term : terms)
    {
        baseTermPointers.emplace_back(new Term(term));
    }
}

Terms unwrapTermsAndReturnTerms(WrappedTerms const& wrappedTerms)
{
    BaseTermSharedPointers const& baseTermPointers(wrappedTerms.getBaseTermPointersConstReference());
    Terms result;
    for(BaseTermSharedPointer const& baseTermPointer : baseTermPointers)
    {
        Term const& term(*dynamic_cast<Term const * const>(baseTermPointer.get()));
        result.emplace_back(term);
    }
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
