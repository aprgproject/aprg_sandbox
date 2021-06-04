#include "Utilities.hpp"

#include <algorithm>

using namespace std;

namespace alba{

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
    Monomial::VariablesToExponentsMap const& variableToExponentMap1(monomial1.getVariablesToExponentsMapConstReference());
    Monomial::VariablesToExponentsMap const& variableToExponentMap2(monomial2.getVariablesToExponentsMapConstReference());
    bool result(false);
    if(variableToExponentMap1.size() == variableToExponentMap2.size())
    {
        using MapConstIterator=Monomial::VariablesToExponentsMap::const_iterator;
        using MismatchResultType=pair<MapConstIterator, MapConstIterator>;
        MismatchResultType mismatchResult = mismatch(variableToExponentMap1.cbegin(), variableToExponentMap1.end(), variableToExponentMap2.cbegin());
        result = mismatchResult.first == variableToExponentMap1.cend();
    }
    return result;
}

bool canBeAddedOrSubtracted(Monomial const& monomial, Variable const& variable)
{
    Monomial::VariablesToExponentsMap const& variableToExponentMap(monomial.getVariablesToExponentsMapConstReference());
    string variableName(variable.getVariableName());
    bool result(false);
    if(variableToExponentMap.size() == 1)
    {
        if(variableToExponentMap.find(variableName) != variableToExponentMap.cend())
        {
            result = variableToExponentMap.at(variableName)==1;
        }
    }
    return result;
}

void performChangeForVariables(
        Monomial::VariablesToExponentsMap & variableToExponentMap,
        Monomial::ChangeExponentsForVariableFunction const& changeVariablesFunction)
{
    for(Monomial::VariablesToExponentsMap::iterator it=variableToExponentMap.begin(); it!=variableToExponentMap.end(); it++)
    {
        changeVariablesFunction(it->first, it->second);
    }
}

void wrapTerms(WrappedTerms & wrappedTerms, Terms const& terms)
{
    WrappedTerms::BaseTermPointers & baseTermPointers(wrappedTerms.getBaseTermPointersReference());    for(Term const& term : terms)
    {
        baseTermPointers.emplace_back(new Term(term));
    }}

Terms unwrapTermsAndReturnTerms(WrappedTerms const& wrappedTerms)
{
    WrappedTerms::BaseTermPointers const& baseTermPointers(wrappedTerms.getBaseTermPointersConstReference());
    Terms result;
    for(std::shared_ptr<BaseTerm> const& baseTermPointer : baseTermPointers)
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
