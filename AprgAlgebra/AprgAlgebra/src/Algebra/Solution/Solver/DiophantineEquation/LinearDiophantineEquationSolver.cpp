#include "LinearDiophantineEquationSolver.hpp"

#include <Algebra/Solution/Solver/DiophantineEquation/LinearDiophantineEquationCoefficientSolver.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;

namespace alba {

namespace algebra {

LinearDiophantineEquationSolver::LinearDiophantineEquationSolver() : BaseSolver(), m_calculatedValues() {}

MultipleVariableSolutionSet LinearDiophantineEquationSolver::calculateSolutionAndReturnSolutionSet(
    Equation const& equation) {
    MultipleVariableSolutionSet solutionSet;
    calculateSolution(solutionSet, equation);
    return solutionSet;
}

void LinearDiophantineEquationSolver::calculateSolution(
    MultipleVariableSolutionSet& solutionSet, Equation const& equation) {
    if (equation.getEquationOperator().isEqual()) {
        Equation simplifiedEquation(equation);
        simplifiedEquation.simplify();
        calculateForEquation(solutionSet, simplifiedEquation);
    }
}

void LinearDiophantineEquationSolver::calculateForEquation(
    MultipleVariableSolutionSet& solutionSet, Equation const& equation) {
    Term const& nonZeroLeftHandTerm(equation.getLeftHandTerm());
    if (canBeConvertedToPolynomial(nonZeroLeftHandTerm)) {
        Polynomial polynomial(createPolynomialIfPossible(nonZeroLeftHandTerm));
        bool isPatternRecognized(false);
        AlbaNumber a, b, c;
        string xName, yName;
        retrieveDetailsFromPolynomial(isPatternRecognized, a, b, c, xName, yName, polynomial);
        if (isPatternRecognized) {
            LinearDiophantineEquationCoefficientSolver solver(a, b, c);
            if (solver.isSolved()) {
                SolutionSet xSolution;
                SolutionSet ySolution;
                xSolution.addAcceptedValue(solver.getX());
                ySolution.addAcceptedValue(solver.getY());
                solutionSet.addSolutionSetForVariable(xName, xSolution);
                solutionSet.addSolutionSetForVariable(yName, ySolution);
                setAsIncompleteSolution();
            }
        }
    }
}

void LinearDiophantineEquationSolver::retrieveDetailsFromPolynomial(
    bool& isPatternRecognized, AlbaNumber& a, AlbaNumber& b, AlbaNumber& c, string& xName, string& yName,
    Polynomial const& polynomial) {
    Monomials const& monomials(polynomial.getMonomials());
    if (3 == monomials.size() && 1 == monomials[0].getVariablesToExponentsMap().size() &&
        1 == monomials[1].getVariablesToExponentsMap().size() &&
        monomials[2].getVariablesToExponentsMap().empty()) {
        a = monomials[0].getCoefficient();
        b = monomials[1].getCoefficient();
        c = -monomials[2].getCoefficient();
        xName = monomials[0].getVariablesToExponentsMap().cbegin()->first;
        yName = monomials[1].getVariablesToExponentsMap().cbegin()->first;
        isPatternRecognized = true;
    }
}

}  // namespace algebra

}  // namespace alba
