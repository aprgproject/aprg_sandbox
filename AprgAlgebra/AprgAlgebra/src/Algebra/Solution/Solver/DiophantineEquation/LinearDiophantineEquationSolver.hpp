#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/MultipleVariableSolutionSet.hpp>
#include <Algebra/Solution/Solver/BaseSolver.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba {

namespace algebra {

class LinearDiophantineEquationSolver : public BaseSolver {
public:
    // A Linear Diophantine Equation is an equation of the form ax+by = c

    LinearDiophantineEquationSolver();

    MultipleVariableSolutionSet calculateSolutionAndReturnSolutionSet(Equation const& equation);

protected:
    void calculateSolution(MultipleVariableSolutionSet& solutionSet, Equation const& equation);
    void calculateForEquation(MultipleVariableSolutionSet& solutionSet, Equation const& equation);
    void retrieveDetailsFromPolynomial(
        bool& isPatternRecognized, AlbaNumber& a, AlbaNumber& b, AlbaNumber& c, std::string& xName, std::string& yName,
        Polynomial const& polynomial);
    AlbaNumbers m_calculatedValues;
};

}  // namespace algebra

}  // namespace alba
