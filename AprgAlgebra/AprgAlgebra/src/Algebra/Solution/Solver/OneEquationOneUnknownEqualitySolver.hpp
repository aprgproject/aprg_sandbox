#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>

namespace alba
{
namespace algebra
{
class OneEquationOneUnknownEqualitySolver
{
public:
    OneEquationOneUnknownEqualitySolver(Equation const& equation);

    SolutionSet calculateSolutionAndReturnSolutionSet();

private:
    void performNewtonMethodToFindSolution(
            SolutionSet & result,
            Term const& termToCheck,
            std::string const& variableNameForSubstitution);
    Equation m_equation;
};

}

}