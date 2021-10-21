#include "DegreeOnlyMutator.hpp"

using namespace std;

namespace alba
{

namespace algebra
{

DegreeOnlyMutator::DegreeOnlyMutator(
        string const& variableName)
    : m_variableName(variableName)
{}

void DegreeOnlyMutator::mutateTerm(Term & term)
{
    Term beforeMutation;
    do    {
        beforeMutation = term;
        BaseMutator::mutateTerm(term);
        term.simplify();
    }
    while(beforeMutation != term);
}

void DegreeOnlyMutator::mutateMonomial(Monomial & monomial)
{
    AlbaNumber degreeForVariable(monomial.getExponentForVariable(m_variableName));
    monomial = getReducedMonomialWithDegree(degreeForVariable);
}

void DegreeOnlyMutator::mutatePolynomial(Polynomial & polynomial)
{
    bool isFirst(true);
    AlbaNumber maxDegreeForVariable;    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        AlbaNumber currentDegreeForVariable(monomial.getExponentForVariable(m_variableName));
        if(isFirst)
        {
            maxDegreeForVariable = currentDegreeForVariable;
            isFirst = false;
        }
        else if(maxDegreeForVariable < currentDegreeForVariable)
        {
            maxDegreeForVariable = currentDegreeForVariable;
        }
    }
    polynomial.clear();
    polynomial.addMonomial(getReducedMonomialWithDegree(maxDegreeForVariable));
}

void DegreeOnlyMutator::mutateExpression(Expression & expression)
{
    Expression beforeMutation;
    do    {
        beforeMutation = expression;
        BaseMutator::mutateExpression(expression);
        expression.simplify();
    }
    while(beforeMutation != expression);
}

Monomial DegreeOnlyMutator::getReducedMonomialWithDegree(AlbaNumber const& degree) const
{
    Monomial result(1, {{m_variableName, degree}});
    if(degree == 0)
    {
        result = Monomial(1, {});
    }
    return result;
}

}

}
