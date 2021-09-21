#include "IsolationOfOneVariableOnEqualityEquation.hpp"

#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>

using namespace std;
namespace alba
{
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
        result = canBeIsolated(getSameVariableExponentIfPossible(polynomial, variableName));
    }
    return result;
}
AlbaNumber IsolationOfOneVariableOnEqualityEquation::getExponentOfIsolatedVariable(
        string const& variableName) const
{    AlbaNumber exponent(0);
    if(canBeConvertedToPolynomial(m_simplifiedLeftSideTerm))
    {
        Polynomial polynomial(createPolynomialIfPossible(m_simplifiedLeftSideTerm));
        exponent = getExponentOfIsolatedVariable(polynomial, variableName);
    }
    return exponent;
}

Equation IsolationOfOneVariableOnEqualityEquation::isolate(
        string const& variableName)
{
    Equation equationWithIsolatedVariable;
    if(canBeConvertedToPolynomial(m_simplifiedLeftSideTerm))
    {
        Polynomial polynomial(createPolynomialIfPossible(m_simplifiedLeftSideTerm));
        AlbaNumber sameVariableExponent(getSameVariableExponentIfPossible(polynomial, variableName));
        if(canBeIsolated(sameVariableExponent))
        {
            Monomials monomialsWithVariable;
            Monomials monomialsWithoutVariable;
            segregateMonomialsWithAndWithoutVariable(
                        polynomial.getMonomialsConstReference(),
                        variableName,
                        monomialsWithVariable,
                        monomialsWithoutVariable);
            Polynomial numerator(monomialsWithoutVariable);
            Polynomial denominator(monomialsWithVariable);
            numerator.multiplyNumber(-1);
            Monomial monomialToIsolate(1, {{variableName, sameVariableExponent}});
            denominator.divideMonomial(monomialToIsolate);
            Term leftHandSideTerm(createExpressionIfPossible({Term(numerator), Term("/"), Term(denominator)}));
            Term rightHandSideTerm(monomialToIsolate);
            leftHandSideTerm.simplify();
            rightHandSideTerm.simplify();            equationWithIsolatedVariable = Equation(leftHandSideTerm, "=", rightHandSideTerm);
        }
    }
    return equationWithIsolatedVariable;
}

AlbaNumber IsolationOfOneVariableOnEqualityEquation::getSameVariableExponentIfPossible(
        Polynomial const& polynomial,
        string const& variableName) const
{
    AlbaNumber variableExponent;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        AlbaNumber currentVariableExponent = monomial.getExponentForVariable(variableName);
        if(currentVariableExponent != 0)
        {
            if(variableExponent == 0)
            {
                variableExponent = currentVariableExponent;
            }
            else if(variableExponent != currentVariableExponent)
            {
                variableExponent = 0;
                break;
            }
        }
    }
    return variableExponent;
}

bool IsolationOfOneVariableOnEqualityEquation::canBeIsolated(
        AlbaNumber const& variableExponent) const
{
    return variableExponent != 0;
}

AlbaNumber IsolationOfOneVariableOnEqualityEquation::getExponentOfIsolatedVariable(
        Polynomial const& polynomial,
        string const& variableName) const{
    AlbaNumber exponent;
    unsigned int monomialCountWithVariable(0);
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())    {
        Monomial::VariablesToExponentsMap variableToExponentMap(
                    monomial.getVariablesToExponentsMapConstReference());
        Monomial::VariablesToExponentsMap::const_iterator it = variableToExponentMap.find(variableName);
        if(it != variableToExponentMap.cend())
        {
            monomialCountWithVariable++;
            exponent = it->second;
            if(monomialCountWithVariable >= 2)
            {
                break;
            }
        }
    }
    return exponent;
}

}

}
