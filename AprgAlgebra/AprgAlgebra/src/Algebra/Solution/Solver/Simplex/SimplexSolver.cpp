#include "SimplexSolver.hpp"

#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Common/Math/Matrix/Utilities/Simplex.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::matrix;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

SimplexSolver::SimplexSolver(Equations const& constraints, Polynomial const& objectiveFunction) {
    intialize(constraints, objectiveFunction);
    solve();
}

bool SimplexSolver::isOptimized() const { return isOptimal(m_simplexTable); }

AlbaNumber SimplexSolver::getOptimizedObjectiveValue() const {
    return m_simplexTable.getEntry(m_simplexTable.getNumberOfColumns() - 1, m_simplexTable.getNumberOfRows() - 1) * -1;
}

Equations SimplexSolver::getSolutionEquations() const {
    Equations result;
    int lastX = m_simplexTable.getNumberOfColumns() - 1;
    for (int y = 0; y < static_cast<int>(m_simplexTable.getNumberOfRows()) - 1; y++) {
        Polynomial solutionPolynomial;
        for (int x = 0; x < static_cast<int>(m_inputVariables.size()); x++) {
            AlbaNumber coefficient(m_simplexTable.getEntry(x, y));
            if (coefficient != 0) {
                solutionPolynomial.addMonomial(Monomial(coefficient, {{m_inputVariables[x], 1}}));
            }
        }
        if (!solutionPolynomial
                 .isEmpty())  // only consider solutions with input coefficients (dont consider slack variables)
        {
            solutionPolynomial.addMonomial(Monomial(m_simplexTable.getEntry(lastX, y) * -1, {}));  // put constant
            Equation solutionEquation(solutionPolynomial, "=", 0);
            solutionEquation.simplify();
            result.emplace_back(solutionEquation);
        }
    }
    return result;
}

void SimplexSolver::intialize(Equations const& constraints, Polynomial const& objectiveFunction) {
    if (isPolynomialLinear(objectiveFunction)) {
        Polynomials constraintsInStandardForm;
        VariableNamesRetriever inputVariablesRetriever;
        set<int> indicesWithSlackVariables;
        processConstraints(constraints, constraintsInStandardForm, inputVariablesRetriever, indicesWithSlackVariables);
        VariableNamesSet const& inputVariableNames(inputVariablesRetriever.getSavedData());

        saveInputVariables(inputVariableNames);

        initializeSimplexTable(
            objectiveFunction, constraintsInStandardForm, inputVariableNames, indicesWithSlackVariables);
    }
}

void SimplexSolver::solve() { solveSimplexTable(m_simplexTable); }

void SimplexSolver::processConstraints(
    Equations const& constraints, Polynomials& constraintsInStandardForm,
    VariableNamesRetriever& inputVariablesRetriever, set<int>& indicesWithSlackVariables) {
    int index(0);
    for (Equation const& constraint : constraints) {
        Equation simplifiedEquation(constraint);
        simplifiedEquation.simplify();
        Term const& leftHandTerm(simplifiedEquation.getLeftHandTerm());
        if (canBeConvertedToPolynomial(leftHandTerm)) {
            Polynomial constraint(createPolynomialIfPossible(leftHandTerm));
            inputVariablesRetriever.retrieveFromPolynomial(constraint);
            if (isPolynomialLinear(constraint)) {
                EquationOperator const& equationOperator(simplifiedEquation.getEquationOperator());
                bool shouldIncludeConstraint(false);
                if (equationOperator.isEqual()) {
                    shouldIncludeConstraint = true;
                } else if (equationOperator.isALessThanVariant()) {
                    indicesWithSlackVariables.emplace(index);
                    shouldIncludeConstraint = true;
                } else if (equationOperator.isAGreaterThanVariant()) {
                    indicesWithSlackVariables.emplace(index);
                    constraint.multiplyNumber(-1);
                    shouldIncludeConstraint = true;
                }
                if (shouldIncludeConstraint) {
                    constraintsInStandardForm.emplace_back(constraint);
                    index++;
                }
            }
        }
    }
}

void SimplexSolver::saveInputVariables(VariableNamesSet const& inputVariableNames) {
    m_inputVariables.reserve(inputVariableNames.size());
    copy(inputVariableNames.cbegin(), inputVariableNames.cend(), back_inserter(m_inputVariables));
}

void SimplexSolver::initializeSimplexTable(
    Polynomial const& objectiveFunction, Polynomials const& constraintsInStandardForm,
    VariableNamesSet const& inputVariableNames, set<int> const& indicesWithSlackVariables) {
    m_simplexTable = SimplexMatrix(
        inputVariableNames.size() + indicesWithSlackVariables.size() + 1, constraintsInStandardForm.size() + 1);

    map<string, int> variableNameToIndexMap;
    int i = 0;
    for (string const& inputVariableName : inputVariableNames) {
        variableNameToIndexMap.emplace(inputVariableName, i++);
    }

    int lastX = m_simplexTable.getNumberOfColumns() - 1;
    int slackColumn = inputVariableNames.size();
    for (int y = 0; y < static_cast<int>(constraintsInStandardForm.size()); y++) {
        Polynomial const& standardFormConstraint(constraintsInStandardForm[y]);
        for (Monomial const& monomial : standardFormConstraint.getMonomialsConstReference()) {
            string variableName(getFirstVariableName(monomial));
            if (variableName.empty()) {
                m_simplexTable.setEntry(lastX, y, monomial.getConstantConstReference() * -1);  // put constant
            } else {
                m_simplexTable.setEntry(
                    variableNameToIndexMap[variableName], y,
                    monomial.getConstantConstReference());  // put variable coefficient
            }
        }
        if (indicesWithSlackVariables.find(y) != indicesWithSlackVariables.cend()) {
            m_simplexTable.setEntry(slackColumn++, y, 1);  // put 1 for slack variable
        }
    }

    int lastY(m_simplexTable.getNumberOfRows() - 1);
    for (Monomial const& monomial : objectiveFunction.getMonomialsConstReference()) {
        string variableName(getFirstVariableName(monomial));
        if (variableName.empty()) {
            m_simplexTable.setEntry(
                lastX, lastY, monomial.getConstantConstReference() * -1);  // put objective function constant
        } else {
            auto it = variableNameToIndexMap.find(variableName);
            if (it != variableNameToIndexMap.cend()) {
                m_simplexTable.setEntry(
                    it->second, lastY,
                    monomial.getConstantConstReference());  // put objective function variable coefficient
            }
        }
    }
}

}  // namespace algebra

}  // namespace alba
