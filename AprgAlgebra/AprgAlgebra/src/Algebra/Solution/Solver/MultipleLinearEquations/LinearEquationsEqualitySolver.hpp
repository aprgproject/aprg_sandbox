#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Algebra/Solution/Solver/BaseSolver.hpp>
#include <Algebra/Term/TermTypes/Polynomial.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>
#include <Math/AlbaMatrix.hpp>

namespace alba
{
namespace algebra
{

class LinearEquationsEqualitySolver : public BaseSolver
{
public:
    using NumberMatrix=AlbaMatrix<AlbaNumber>;
    LinearEquationsEqualitySolver();

    VariableNameToSolutionSetMap calculateSolutionAndReturnSolutionSet(Equations const& equations);    VariableNameToSolutionSetMap calculateSolutionAndReturnSolutionSet(Polynomials const& polynomials);

private:
    void calculateSolution(VariableNameToSolutionSetMap & solutionSets, Equations const& equations);    void calculateSolution(VariableNameToSolutionSetMap & solutionSets, Polynomials const& polynomials);
    bool areExponentsEqualToOneAndZero(AlbaNumbersSet const& exponents) const;
    void setMatrixCoefficients(
            NumberMatrix & coefficientsMatrix,
            VariableNamesSet const& variableNames,
            Polynomials const& polynomials);
    void saveSolutionSetsFromTheCoefficientMatrix(
            VariableNameToSolutionSetMap & solutionSets,
            NumberMatrix const& coefficientsMatrix,
            VariableNamesSet const& variables);
};


}

}
