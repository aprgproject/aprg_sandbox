#include "RemoveMonomialsWithNegativeExponentMutator.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

RemoveMonomialsWithNegativeExponentMutator::RemoveMonomialsWithNegativeExponentMutator(
        string const& variableName)
    : m_variableName(variableName)
{}

void RemoveMonomialsWithNegativeExponentMutator::mutateTerm(Term & term) const
{
    BaseMutator::mutateTerm(term);
    term.simplify();
}

void RemoveMonomialsWithNegativeExponentMutator::mutateMonomial(Monomial & monomial) const
{
    if(isMonomialToBeRemoved(monomial))
    {
        monomial.clear();
    }
}

void RemoveMonomialsWithNegativeExponentMutator::mutatePolynomial(Polynomial & polynomial) const
{
    Monomials & monomials(polynomial.getMonomialsReference());
    monomials.erase(remove_if(
                        monomials.begin(), monomials.end(), [&](Monomial const& monomial)
    {
                        return isMonomialToBeRemoved(monomial);
                    }), monomials.end());
}

void RemoveMonomialsWithNegativeExponentMutator::mutateExpression(Expression & expression) const
{
    BaseMutator::mutateExpression(expression);
    expression.simplify();
}

void RemoveMonomialsWithNegativeExponentMutator::mutateFunction(Function & functionObject) const
{
    BaseMutator::mutateFunction(functionObject);
    functionObject.simplify();
}

bool RemoveMonomialsWithNegativeExponentMutator::isMonomialToBeRemoved(Monomial const& monomial) const
{
    bool result(false);
    if(monomial.hasASingleVariable()
            && monomial.getExponentForVariable(m_variableName) < 0)
    {
        result=true;
    }
    return result;
}

}

}
