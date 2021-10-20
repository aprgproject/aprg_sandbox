#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Algebra/Solution/Solver/NewtonMethod.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/BaseOneEquationOneVariableSolver.hpp>

namespace alba
{

namespace algebra
{

class OneEquationOneVariableEqualitySolver : public BaseOneEquationOneVariableSolver
{
public:
    OneEquationOneVariableEqualitySolver();

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
    NewtonMethod::Function getFunctionToIterate(
            Term const& termToCheck,
            std::string const& variableNameForSubstitution);
    AlbaNumber getMoreAccurateValueFromNewtonMethod(
            Term const& termToCheck,
            std::string const& variableNameForSubstitution,
            AlbaNumber const& value);
};


}

}
