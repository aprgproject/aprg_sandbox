#include "IsolationOfOneVariableOnEqualityEquation.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
using namespace std;

namespace alba{

namespace algebra
{

IsolationOfOneVariableOnEqualityEquation::IsolationOfOneVariableOnEqualityEquation(
        Equation const& equation)
{
    if(equation.getEquationOperator().isEqual())
    {
        Equation simplifiedEquation(equation);
        simplifiedEquation.simplify();
        m_simplifiedLeftSideTerm = simplifiedEquation.getLeftHandTerm();
    }
}

bool IsolationOfOneVariableOnEqualityEquation::canBeIsolated(
        string const& variableName) const
{
    bool result(false);
    if(canBeConvertedToPolynomial(m_simplifiedLeftSideTerm))
    {
        Polynomial polynomial(createPolynomialIfPossible(m_simplifiedLeftSideTerm));
        result = canBeIsolated(getIdenticalExponentForVariableIfPossible(variableName, polynomial));
    }
    return result;
}

AlbaNumber IsolationOfOneVariableOnEqualityEquation::getIdenticalExponentForVariableIfPossible(
        string const& variableName) const
{
    AlbaNumber exponent(0);    if(canBeConvertedToPolynomial(m_simplifiedLeftSideTerm))
    {
        Polynomial polynomial(createPolynomialIfPossible(m_simplifiedLeftSideTerm));
        exponent = getIdenticalExponentForVariableIfPossible(variableName, polynomial);
    }
    return exponent;
}

Equation IsolationOfOneVariableOnEqualityEquation::isolateTermWithVariableOnLeftSideOfEquation(
        string const& variableName) const
{
    Term termWithVariable;
    Term termWithWithoutVariable;
    isolateTermWithVariable(variableName, termWithVariable, termWithWithoutVariable);
    return Equation(termWithVariable, "=", termWithWithoutVariable);
}

Equation IsolationOfOneVariableOnEqualityEquation::isolateTermWithVariableOnRightSideOfEquation(
        string const& variableName) const
{
    Term termWithVariable;
    Term termWithWithoutVariable;
    isolateTermWithVariable(variableName, termWithVariable, termWithWithoutVariable);
    return Equation(termWithWithoutVariable, "=", termWithVariable);
}

Term IsolationOfOneVariableOnEqualityEquation::getTermByIsolatingVariable(
        string const& variableName) const
{
    Term result;
    Term termWithVariable;
    Term termWithWithoutVariable;
    isolateTermWithVariable(variableName, termWithVariable, termWithWithoutVariable);
    if(termWithVariable.isVariable())
    {
        result = termWithWithoutVariable;
    }
    else if(termWithVariable.isMonomial())
    {
        Monomial const& monomialWithVariable(termWithVariable.getMonomialConstReference());
        AlbaNumber exponent(monomialWithVariable.getExponentForVariable(variableName));
        exponent = exponent^(-1);
        result = termWithWithoutVariable^Term(exponent);
    }
    return result;
}

void IsolationOfOneVariableOnEqualityEquation::isolateTermWithVariable(
        string const& variableName,
        Term & termWithVariable,
        Term & termWithWithoutVariable) const
{
    if(canBeConvertedToPolynomial(m_simplifiedLeftSideTerm))
    {
        Polynomial polynomial(createPolynomialIfPossible(m_simplifiedLeftSideTerm));
        AlbaNumber identicalExponentForVariable(getIdenticalExponentForVariableIfPossible(variableName, polynomial));
        if(canBeIsolated(identicalExponentForVariable))
        {
            Monomials monomialsWithVariable;
            Monomials monomialsWithoutVariable;            segregateMonomialsWithAndWithoutVariable(
                        polynomial.getMonomialsConstReference(),
                        variableName,
                        monomialsWithVariable,                        monomialsWithoutVariable);
            Polynomial numerator(monomialsWithoutVariable);
            Polynomial denominator(monomialsWithVariable);
            numerator.multiplyNumber(-1);
            Monomial monomialWithIsolatedVariable(1, {{variableName, identicalExponentForVariable}});
            denominator.divideMonomial(monomialWithIsolatedVariable);
            termWithVariable = monomialWithIsolatedVariable;
            termWithWithoutVariable = Term(numerator)/Term(denominator);
            termWithVariable.simplify();
            termWithWithoutVariable.simplify();
        }
    }
}

bool IsolationOfOneVariableOnEqualityEquation::canBeIsolated(
        AlbaNumber const& identicalExponentForVariable) const
{
    return identicalExponentForVariable != 0;
}

AlbaNumber IsolationOfOneVariableOnEqualityEquation::getIdenticalExponentForVariableIfPossible(
        string const& variableName,
        Polynomial const& polynomial) const
{
    AlbaNumber exponent;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        AlbaNumber currentExponent = monomial.getExponentForVariable(variableName);
        if(currentExponent != 0)
        {
            if(exponent == 0)
            {
                exponent = currentExponent;
            }
            else if(exponent != currentExponent)
            {
                exponent = 0;
                break;
            }
        }    }
    return exponent;
}
}

}
