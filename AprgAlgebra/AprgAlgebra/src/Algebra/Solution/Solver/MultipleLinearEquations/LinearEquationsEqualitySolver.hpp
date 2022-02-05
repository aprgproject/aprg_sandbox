#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/MultipleVariableSolutionSet.hpp>
#include <Algebra/Solution/Solver/BaseSolver.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba
{
namespace algebra
{
class LinearEquationsEqualitySolver : public BaseSolver
{
public:
    using NumberMatrix=AlbaMatrix<AlbaNumber>;
    LinearEquationsEqualitySolver();

    MultipleVariableSolutionSet calculateSolutionAndReturnSolutionSet(Equations const& equations);
    MultipleVariableSolutionSet calculateSolutionAndReturnSolutionSet(Polynomials const& polynomials);

private:
    void calculateSolution(MultipleVariableSolutionSet & solutionSet, Equations const& equations);
    void calculateSolution(MultipleVariableSolutionSet & solutionSet, Polynomials const& polynomials);
    bool areExponentsEqualToOneAndZero(AlbaNumbersSet const& exponents) const;
    void setMatrixCoefficients(
            NumberMatrix & coefficientsMatrix,
            VariableNamesSet const& variableNames,
            Polynomials const& polynomials);
    void saveSolutionSetsFromTheCoefficientMatrix(
            MultipleVariableSolutionSet & solutionSet,
            NumberMatrix const& coefficientsMatrix,
            VariableNamesSet const& variables);
};


}

}
