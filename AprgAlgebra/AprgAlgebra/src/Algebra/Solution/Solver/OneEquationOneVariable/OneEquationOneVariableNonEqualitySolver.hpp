#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/BaseOneEquationOneVariableSolver.hpp>

namespace alba {

namespace algebra {

class OneEquationOneVariableNonEqualitySolver : public BaseOneEquationOneVariableSolver {
public:
    OneEquationOneVariableNonEqualitySolver();

private:
    void calculateSolution(SolutionSet& solutionSet, Equation const& equation);
    void calculateForEquation(SolutionSet& solutionSet, Equation const& equation);
    void calculateForTermAndVariable(Term const& term, std::string const&);
    void addIntervalsToSolutionSetIfNeeded(
        SolutionSet& solutionSet, Equation const& equation, std::string const& variableName);
    AlbaNumbers m_calculatedValues;
};

}  // namespace algebra

}  // namespace alba
