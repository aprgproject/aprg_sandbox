#include "LinearEquationsEqualitySolver.hpp"

#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Retrieval/ExponentsRetriever.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>

using namespace alba::matrix;
using namespace std;

namespace alba {

namespace algebra {

LinearEquationsEqualitySolver::LinearEquationsEqualitySolver() : BaseSolver() {}

MultipleVariableSolutionSet LinearEquationsEqualitySolver::calculateSolutionAndReturnSolutionSet(
    Equations const& equations) {
    MultipleVariableSolutionSet solutionSet;
    calculateSolution(solutionSet, equations);
    return solutionSet;
}

MultipleVariableSolutionSet LinearEquationsEqualitySolver::calculateSolutionAndReturnSolutionSet(
    Polynomials const& polynomials) {
    MultipleVariableSolutionSet solutionSet;
    calculateSolution(solutionSet, polynomials);
    return solutionSet;
}

void LinearEquationsEqualitySolver::calculateSolution(
    MultipleVariableSolutionSet& solutionSet, Equations const& equations) {
    if (doesAllEquationsHaveEqualityOperator(equations)) {
        Polynomials polynomials;
        for (Equation const& equation : equations) {
            Equation simplifiedEquation(equation);
            simplifiedEquation.simplify();
            Term const& nonZeroLeftHandTerm(simplifiedEquation.getLeftHandTerm());
            if (canBeConvertedToPolynomial(nonZeroLeftHandTerm)) {
                polynomials.emplace_back(createPolynomialIfPossible(nonZeroLeftHandTerm));
            }
        }
        calculateSolution(solutionSet, polynomials);
    }
}

void LinearEquationsEqualitySolver::calculateSolution(
    MultipleVariableSolutionSet& solutionSet, Polynomials const& polynomials) {
    ExponentsRetriever exponentsRetriever;
    VariableNamesRetriever variablesRetriever;
    exponentsRetriever.retrieveFromPolynomials(polynomials);
    variablesRetriever.retrieveFromPolynomials(polynomials);
    AlbaNumbersSet const& exponents(exponentsRetriever.getSavedData());
    VariableNamesSet const& variables(variablesRetriever.getSavedData());
    if (areExponentsEqualToOneAndZero(exponents) && variables.size() == polynomials.size()) {
        NumberMatrix coefficientsMatrix(variables.size() + 1, polynomials.size());
        setMatrixCoefficients(coefficientsMatrix, variables, polynomials);
        transformToReducedEchelonFormUsingGaussJordanReduction(coefficientsMatrix);
        if (isReducedRowEchelonForm(coefficientsMatrix)) {
            saveSolutionSetsFromTheCoefficientMatrix(solutionSet, coefficientsMatrix, variables);
            setAsCompleteSolution();
        }
    }
}

bool LinearEquationsEqualitySolver::areExponentsEqualToOneAndZero(AlbaNumbersSet const& exponents) const {
    return all_of(exponents.cbegin(), exponents.cend(), [](AlbaNumber const& exponent) {
        return exponent == 1 || exponent == 0;
    });
}

void LinearEquationsEqualitySolver::setMatrixCoefficients(
    NumberMatrix& coefficientsMatrix, VariableNamesSet const& variableNames, Polynomials const& polynomials) {
    int rowIndex = 0;
    for (Polynomial const& polynomial : polynomials) {
        int columnIndex = 0;
        VariableToValueMap variableToValueMap(getCoefficientsForVariablesOnly(polynomial));
        for (string const& variableName : variableNames) {
            VariableToValueMap::const_iterator it = variableToValueMap.find(variableName);
            if (it != variableToValueMap.cend()) {
                coefficientsMatrix.setEntry(columnIndex++, rowIndex, it->second);
            }
        }
        coefficientsMatrix.setEntry(columnIndex, rowIndex++, getCoefficientOfMonomialWithNoVariables(polynomial));
    }
}

void LinearEquationsEqualitySolver::saveSolutionSetsFromTheCoefficientMatrix(
    MultipleVariableSolutionSet& solutionSet, NumberMatrix const& coefficientsMatrix,
    VariableNamesSet const& variables) {
    int index = 0;
    int columnEndIndex = variables.size();
    for (string const& variableName : variables) {
        AlbaNumber identityDiagonalEntry(coefficientsMatrix.getEntry(index, index));
        if (identityDiagonalEntry == 1) {
            SolutionSet solutionSetForVariable;
            solutionSetForVariable.addAcceptedValue(-coefficientsMatrix.getEntry(columnEndIndex, index));
            solutionSet.addSolutionSetForVariable(variableName, solutionSetForVariable);
        }
        index++;
    }
}

}  // namespace algebra

}  // namespace alba
