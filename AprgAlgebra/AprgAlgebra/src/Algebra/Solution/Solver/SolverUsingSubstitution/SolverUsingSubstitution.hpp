#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/MultipleVariableSolutionSet.hpp>
#include <Algebra/Solution/Solver/BaseSolver.hpp>
#include <Algebra/Term/TermTypes/Polynomial.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>
#include <Math/AlbaMatrix.hpp>

namespace alba
{

namespace algebra
{

class SolverUsingSubstitution : public BaseSolver
{
public:
    using NumberMatrix=AlbaMatrix<AlbaNumber>;
    SolverUsingSubstitution();

    MultipleVariableSolutionSet calculateSolutionAndReturnSolutionSet(Equations const& equations);


private:
    void calculateSolutionForAllVariables(
            MultipleVariableSolutionSet & multipleVariableSolutionSet,
            Equations const& equations);
    void calculateSolutionForOneVariable(
            MultipleVariableSolutionSet & multipleVariableSolutionSet,
            Equations const& equations);
    void substituteSolutionSetValuesToEquations(
            Equations & substitutedEquations,
            MultipleVariableSolutionSet const& multipleVariableSolutionSet);
    void isolateAndSubstituteUntilOneUnknown(Equations & substitutedEquations);
    void solveUsingOneUnknownAndAddToSolutionSet(
            MultipleVariableSolutionSet & multipleVariableSolutionSet,
            Equations const& substitutedEquations);
    void selectVariableNameAndEquationNumber(
            bool & isFound,
            std::string & selectedVariableName,
            unsigned int & selectedEquationIndex,
            Equations const& equations);
    void substituteEquationForSelectedEquationIndex(
            Equations & substitutedEquations,
            bool const areVariableAndEquationSelected,
            std::string const& selectedVariableName,
            unsigned int const selectedEquationIndex);
    void removeEquationsWithoutUnknowns(Equations& substitutedEquations);
};


}

}
