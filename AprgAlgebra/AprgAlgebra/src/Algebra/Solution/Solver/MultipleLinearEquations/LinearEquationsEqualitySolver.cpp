#include "LinearEquationsEqualitySolver.hpp"

#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

LinearEquationsEqualitySolver::LinearEquationsEqualitySolver()
    : BaseSolver()
{}

MultipleVariableSolutionSet LinearEquationsEqualitySolver::calculateSolutionAndReturnSolutionSet(
        Equations const& equations)
{
    MultipleVariableSolutionSet solutionSet;
    calculateSolution(solutionSet, equations);
    return solutionSet;
}

MultipleVariableSolutionSet LinearEquationsEqualitySolver::calculateSolutionAndReturnSolutionSet(
        Polynomials const& polynomials)
{
    MultipleVariableSolutionSet solutionSet;
    calculateSolution(solutionSet, polynomials);
    return solutionSet;
}

void LinearEquationsEqualitySolver::calculateSolution(
        MultipleVariableSolutionSet & solutionSet,
        Equations const& equations)
{
    if(doesAllEquationsHaveEqualityOperator(equations))
    {
        Polynomials polynomials;
        for(Equation const& equation : equations)
        {
            Equation simplifiedEquation(equation);
            simplifiedEquation.simplify();
            Term const& nonZeroLeftHandTerm(simplifiedEquation.getLeftHandTerm());
            if(canBeConvertedToPolynomial(nonZeroLeftHandTerm))
            {
                polynomials.emplace_back(createPolynomialIfPossible(nonZeroLeftHandTerm));
            }
        }
        calculateSolution(solutionSet, polynomials);
    }
}

void LinearEquationsEqualitySolver::calculateSolution(
        MultipleVariableSolutionSet & solutionSet,
        Polynomials const& polynomials)
{
    VariableNamesSet variables;
    AlbaNumbersSet exponents;
    retrieveExponents(exponents, polynomials);
    retrieveVariableNames(variables, polynomials);
    if(areExponentsEqualToOneAndZero(exponents)
            && variables.size() == polynomials.size())
    {
        NumberMatrix coefficientsMatrix(variables.size()+1, polynomials.size());
        setMatrixCoefficients(coefficientsMatrix, variables, polynomials);
        coefficientsMatrix.transformToReducedEchelonFormUsingGaussJordanReduction();
        if(coefficientsMatrix.isReducedRowEchelonForm())
        {
            saveSolutionSetsFromTheCoefficientMatrix(solutionSet, coefficientsMatrix, variables);
            setAsCompleteSolution();
        }
    }
}

bool LinearEquationsEqualitySolver::areExponentsEqualToOneAndZero(
        AlbaNumbersSet const& exponents) const
{
    return all_of(exponents.cbegin(), exponents.cend(), [](AlbaNumber const& exponent)
    {
        return exponent == 1 || exponent == 0;
    });
}

void LinearEquationsEqualitySolver::setMatrixCoefficients(
        LinearEquationsEqualitySolver::NumberMatrix & coefficientsMatrix,
        VariableNamesSet const& variableNames,
        Polynomials const& polynomials)
{
    unsigned int rowIndex=0;
    for(Polynomial const& polynomial : polynomials)
    {
        unsigned int columnIndex=0;
        VariableToValueMap variableToValueMap(getCoefficientsForVariablesOnly(polynomial));
        for(string const& variableName : variableNames)
        {
            VariableToValueMap::const_iterator it = variableToValueMap.find(variableName);
            if(it != variableToValueMap.cend())
            {
                coefficientsMatrix.setEntry(columnIndex++, rowIndex, it->second);
            }
        }
        coefficientsMatrix.setEntry(columnIndex, rowIndex++, getCoefficientWithNoVariables(polynomial));
    }
}

void LinearEquationsEqualitySolver::saveSolutionSetsFromTheCoefficientMatrix(
        MultipleVariableSolutionSet & solutionSet,
        NumberMatrix const& coefficientsMatrix,
        VariableNamesSet const& variables)
{
    unsigned int index=0;
    unsigned int columnEndIndex = variables.size();
    for(string const& variableName : variables)
    {
        AlbaNumber identityDiagonalEntry(coefficientsMatrix.getEntry(index, index));
        if(identityDiagonalEntry == 1)
        {
            SolutionSet solutionSetForVariable;
            solutionSetForVariable.addAcceptedValue(-coefficientsMatrix.getEntry(columnEndIndex, index));
            solutionSet.addSolutionSetForVariable(variableName, solutionSetForVariable);
        }
        index++;
    }
}

}

}
