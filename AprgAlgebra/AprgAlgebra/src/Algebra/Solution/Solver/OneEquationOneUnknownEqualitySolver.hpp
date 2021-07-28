#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Algebra/Solution/Solver/BaseOneEquationOneUnknownSolver.hpp>

namespace alba
{

namespace algebra
{

class OneEquationOneUnknownEqualitySolver : public BaseOneEquationOneUnknownSolver
{
public:
    OneEquationOneUnknownEqualitySolver();

private:
    void calculateSolution(SolutionSet & solutionSet, Equation const& equation);
    void calculateForEquation(SolutionSet & solutionSet, Equation const& equation);
    void calculateForTermAndVariable(Term const& term, std::string const& variableName);
    void addValuesToSolutionSetIfNeeded(
            SolutionSet& solutionSet,
            Term const& term,
            std::string const& variableName);
    void performNewtonMethodToFindSolution(
            Term const& termToCheck,
            std::string const& variableNameForSubstitution);
};


}

}
