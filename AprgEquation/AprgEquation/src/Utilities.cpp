#include "Utilities.hpp"

#include <TermsAggregator.hpp>

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
    Polynomial newPolynomial(polynomial);
    newPolynomial.simplify();
    Term newTerm;
    if(newPolynomial.isZero())
    {
        newTerm = Term(Constant(0));
    }
    else if(newPolynomial.isOneMonomial())
    {
        newTerm = convertMonomialToSimplestTerm(newPolynomial.getFirstMonomial());
    }
    else
    {
        newTerm = Term(newPolynomial);
    }
    return newTerm;
}

Term convertMonomialToSimplestTerm(Monomial const& monomial)
{
    Monomial newMonomial(monomial);
    newMonomial.simplify();
    Term newTerm(newMonomial);
    if(newMonomial.isZero())
    {
        newTerm = Term(Constant(0));
    }
    else if(newMonomial.isConstantOnly())
    {
        newTerm = Term(newMonomial.getConstantConstReference());
    }
    else if(newMonomial.isVariableOnly())
    {
        newTerm = Term(newMonomial.getFirstVariableName());
    }
    else
    {
        newTerm = Term(newMonomial);
    }
    return newTerm;
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

Monomial createMonomialConstant(AlbaNumber const& number)
{
    return Monomial(number, {});
}

Monomial createMonomialVariable(string const& variableName)
{
    return Monomial(1, {{variableName, 1}});
}

Expression createExpression(Terms const& terms)
{
    Expression result;
    TermsAggregator aggregator(terms);
    aggregator.buildExpressionFromTerms();
    Terms const& builtTerms(aggregator.getTermsConstReference());
    if(builtTerms.size() == 1)
    {
        result = convertTermToExpression(builtTerms.at(0));
    }
    return result;
}

Expression createSimplifiedExpression(Terms const& terms)
{
    Expression result;
    TermsAggregator aggregator(terms);
    aggregator.simplifyTerms();
    Terms const& simplifiedTerms(aggregator.getTermsConstReference());
    if(simplifiedTerms.size() == 1)
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
