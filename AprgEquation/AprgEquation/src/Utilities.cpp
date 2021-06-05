#include "Utilities.hpp"

#include <TermsSimplificator.hpp>

#include <algorithm>


#include <Debug/AlbaDebug.hpp>

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

unsigned int getOperatorLevelValue(OperatorLevel const operatorLevel)
{
    unsigned int result(0);
    switch(operatorLevel)
    {
    case OperatorLevel::Unknown:
        result=0;
        break;
    case OperatorLevel::AdditionAndSubtraction:
        result=1;
        break;
    case OperatorLevel::MultiplicationAndDivision:
        result=2;
        break;
    case OperatorLevel::RaiseToPower:
        result=3;
        break;
    }
    return result;
}

unsigned int getTermPriorityValue(Term const& term)
{
    unsigned int result(0);
    if(term.isExpression())
    {
        result=1;
    }
    else if(term.isPolynomial())
    {
        result=2;
    }
    else if(term.isMonomial())
    {
        result=3;
    }
    else if(term.isOperator())
    {
        result=4;
    }
    else if(term.isVariable())
    {
        result=5;
    }
    else if(term.isConstant())
    {
        result=6;
    }
    return result;
}

Term convertExpressionToSimplestTerm(Expression const& expression)
{
    Expression newExpression(expression);
    newExpression.simplify();
    Term newTerm(newExpression);
    if(newExpression.containsOnlyOneTerm())
    {
        Term const& term = *dynamic_cast<Term const*const>(newExpression.getFirstTermConstReference().get());
        newTerm = term;
    }
    return newTerm;
}

Term convertPolynomialToSimplestTerm(Polynomial const& polynomial)
{
    Polynomial simplifiedPolynomial(createSimplifiedPolynomial(polynomial));
    Term newTerm(simplifiedPolynomial);
    if(simplifiedPolynomial.isZero())
    {
        newTerm = Term(Constant(0));
    }
    else if(simplifiedPolynomial.isOneMonomial())
    {
        newTerm = convertMonomialToSimplestTerm(simplifiedPolynomial.getFirstMonomial());
    }
    return newTerm;
}

Polynomial createSimplifiedPolynomial(Polynomial const& polynomial)
{
    Polynomial simplifiedPolynomial;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        if(!monomial.isZero())
        {
            simplifiedPolynomial.addMonomial(monomial);
        }
    }
    return simplifiedPolynomial;
}

Term convertMonomialToSimplestTerm(Monomial const& monomial)
{
    Monomial simplifiedMonomial(createSimplifiedMonomial(monomial));
    Term newTerm(simplifiedMonomial);
    if(simplifiedMonomial.isZero())
    {
        newTerm = Term(Constant(0));
    }
    else if(simplifiedMonomial.isConstantOnly())
    {
        newTerm = Term(simplifiedMonomial.getConstantConstReference());
    }
    else if(simplifiedMonomial.isVariableOnly())
    {
        newTerm = Term(simplifiedMonomial.getFirstVariableName());
    }
    return newTerm;
}

Monomial createSimplifiedMonomial(Monomial const& monomial)
{
    return Monomial(
                monomial.getConstantConstReference(),
                createVariableMapAndRemoveZeroExponents(monomial.getVariablesToExponentsMapConstReference()));
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

Monomial::VariablesToExponentsMap createVariableMapAndRemoveZeroExponents(Monomial::VariablesToExponentsMap const& variablesMap)
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

BaseTermSharedPointer createBaseTermSharedPointer(BaseTermSharedPointer const& baseTerm)
{
    return BaseTermSharedPointer(
                dynamic_cast<BaseTerm*>(
                    new Term(*dynamic_cast<Term*>(baseTerm.get()))));
}

BaseTermSharedPointer createBaseTermSharedPointerFromTerm(Term const& term)
{
    return BaseTermSharedPointer(
                dynamic_cast<BaseTerm*>(
                    new Term(term)));
}

BaseTermSharedPointer createBaseTermSharedPointerFromTermReference(Term& term)
{
    return BaseTermSharedPointer(dynamic_cast<BaseTerm*>(&term));
}

Expression createExpression(Terms const& terms)
{
    Expression result;
    ALBA_PRINT1(terms.size());
    for(Term const& term : terms)
    {
        ALBA_PRINT2(getTermPriorityValue(term), term.getDisplayableString());
    }
    TermsSimplificator simplificator(terms);
    simplificator.buildExpressionFromTerms();
    Terms const& simplifiedTerms(simplificator.getTermsConstReference());
    ALBA_PRINT1(simplifiedTerms.size());
    for(Term const& simplifiedTerm : simplifiedTerms)
    {
        ALBA_PRINT2(getTermPriorityValue(simplifiedTerm), simplifiedTerm.getDisplayableString());
    }
    if(!simplifiedTerms.empty())
    {
        result = convertTermToExpression(simplifiedTerms.at(0));
    }
    return result;
}

Expression createSimplifiedExpression(Terms const& terms)
{
    Expression result;
    ALBA_PRINT1(terms.size());
    for(Term const& term : terms)
    {
        ALBA_PRINT2(getTermPriorityValue(term), term.getDisplayableString());
    }
    TermsSimplificator simplificator(terms);
    simplificator.simplifyTerms();
    Terms const& simplifiedTerms(simplificator.getTermsConstReference());
    ALBA_PRINT1(simplifiedTerms.size());
    for(Term const& simplifiedTerm : simplifiedTerms)
    {
        ALBA_PRINT2(getTermPriorityValue(simplifiedTerm), simplifiedTerm.getDisplayableString());
    }
    if(!simplifiedTerms.empty())
    {
        result = convertTermToExpression(simplifiedTerms.at(0));
    }
    return result;
}

Expression convertTermToExpression(Term const& term)
{
    Expression result;
    if(term.isExpression())
    {
        result=term.getExpressionConstReference();
    }
    else
    {
        result=Expression(createBaseTermSharedPointerFromTerm(term));
    }
    return result;
}

}

}
