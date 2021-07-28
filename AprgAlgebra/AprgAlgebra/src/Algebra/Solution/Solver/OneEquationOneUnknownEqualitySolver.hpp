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

    bool isSolved() const;
    bool isACompleteSolution() const;

    SolutionSet calculateSolutionAndReturnSolutionSet();

private:
    void setAsCompleteSolution();
    void setAsIncompleteSolution();
    void processWhenEquationIsAlwaysSatisfied(SolutionSet & result);
    void calculateWhenEquationIsSometimesSatisfied(SolutionSet & result);
    void performNewtonMethodToFindSolution(
            SolutionSet & result,
            Term const& termToCheck,
            std::string const& variableNameForSubstitution);
    bool m_isSolved;
    bool m_isACompleteSolution;
    Equation m_equation;
};

}

}