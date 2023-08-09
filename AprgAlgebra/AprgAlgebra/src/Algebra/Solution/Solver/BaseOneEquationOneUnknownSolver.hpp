#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Algebra/Solution/Solver/BaseSolver.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

namespace alba
{

namespace algebra
{

class BaseOneEquationOneUnknownSolver : public BaseSolver
{
public:
    BaseOneEquationOneUnknownSolver();

    SolutionSet calculateSolutionAndReturnSolutionSet(Equation const& equation);

protected:
    virtual void calculateSolution(SolutionSet & solutionSet, Equation const& equation) = 0;
    void processWhenEquationIsAlwaysSatisfied(SolutionSet & solutionSet);
    void calculateWhenEquationIsSometimesSatisfied(
            SolutionSet & solutionSet,
            Equation const& equation);
    virtual void calculateForEquation(
            SolutionSet & solutionSet,
            Equation const& equation) = 0;
    void sortCalculatedValues();
    void calculateForTermAndCheckAbsoluteValueFunctions(
            Term const& nonZeroLeftHandTerm,
            std::string const& variableName);
    void calculateAndSubstituteAbsoluteValueFunctions(
            FunctionsSet const& absFunctions,
            Term const& term,
            std::string const& variableName);
    virtual void calculateForTermAndVariable(
            Term const& term,
            std::string const& variableName) = 0;
    void addValuesToSolutionSetIfNeeded(
            SolutionSet& solutionSet,
            Term const& term,
            std::string const& variableName);
    AlbaNumbers m_calculatedValues;
};


}

}
