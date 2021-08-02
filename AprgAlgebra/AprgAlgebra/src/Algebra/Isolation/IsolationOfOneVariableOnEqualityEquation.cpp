#include "IsolationOfOneVariableOnEqualityEquation.hpp"

#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

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
        result = canBeIsolated(polynomial, variableName);
    }
    return result;
}

AlbaNumber IsolationOfOneVariableOnEqualityEquation::getExponentOfIsolatedVariable(
        string const& variableName) const
{
    AlbaNumber exponent(0);
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
        if(canBeIsolated(polynomial, variableName))
        {
            AlbaNumber variableExponent;
            Monomial monomialToIsolate;
            for(Monomial const& monomial : polynomial.getMonomialsConstReference())
            {
                Monomial::VariablesToExponentsMap variableToExponentMap(
                            monomial.getVariablesToExponentsMapConstReference());
                Monomial::VariablesToExponentsMap::const_iterator it
                        = variableToExponentMap.find(variableName);
                if(it != variableToExponentMap.cend())
                {
                    variableExponent = it->second;
                    monomialToIsolate = monomial;
                    break;
                }
            }
            Polynomial polynomialWithoutVariable(polynomial);
            polynomialWithoutVariable.multiplyNumber(-1);
            Monomial monomialToSubtract(monomialToIsolate);
            polynomialWithoutVariable.addMonomial(monomialToSubtract);
            Monomial monomialToDivide(monomialToIsolate);
            monomialToDivide.putVariableWithExponent(variableName, 0);
            polynomialWithoutVariable.divideMonomial(monomialToDivide);
            monomialToIsolate = Monomial(1, {{variableName, variableExponent}});
            Term leftHandSideTerm(polynomialWithoutVariable);
            Term rightHandSideTerm(monomialToIsolate);
            leftHandSideTerm.simplify();
            rightHandSideTerm.simplify();
            equationWithIsolatedVariable = Equation(leftHandSideTerm, "=", rightHandSideTerm);
        }
    }
    return equationWithIsolatedVariable;
}

bool IsolationOfOneVariableOnEqualityEquation::canBeIsolated(
        Polynomial const& polynomial,
        string const& variableName) const
{
    unsigned int monomialCountWithVariable(0);
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        Monomial::VariablesToExponentsMap variableToExponentMap(
                    monomial.getVariablesToExponentsMapConstReference());
        Monomial::VariablesToExponentsMap::const_iterator it = variableToExponentMap.find(variableName);
        if(it != variableToExponentMap.cend())
        {
            monomialCountWithVariable++;
            if(monomialCountWithVariable >= 2)
            {
                break;
            }
        }
    }
    return monomialCountWithVariable == 1;
}

AlbaNumber IsolationOfOneVariableOnEqualityEquation::getExponentOfIsolatedVariable(
        Polynomial const& polynomial,
        string const& variableName) const
{
    AlbaNumber exponent;
    unsigned int monomialCountWithVariable(0);
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
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
