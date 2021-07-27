#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>

namespace alba
{

namespace algebra
{

class OneEquationOneUnknownNonEqualitySolver
{
public:
    OneEquationOneUnknownNonEqualitySolver(Equation const& equation);

    SolutionSet calculateSolutionAndReturnSolutionSet();

private:
    void addIntervalWhenEquationIsAlwaysSatisfied(SolutionSet & result);
    void calculateWhenEquationIsSometimesSatisfied(SolutionSet & result);
    void performNewtonMethodToFindSolution(
            SolutionSet & result,
            Term const& termToCheck,
            std::string const& variableNameForSubstitution);
    Equation m_equation;
};


}

}
