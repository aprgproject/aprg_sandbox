#include "LinearDiophantineEquationSolver.hpp"

#include <Algebra/Solution/Solver/DiophantineEquation/LinearDiophantineEquationCoefficientSolver.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

LinearDiophantineEquationSolver::LinearDiophantineEquationSolver()
    : BaseSolver()
    , m_calculatedValues()
{}

MultipleVariableSolutionSet LinearDiophantineEquationSolver::calculateSolutionAndReturnSolutionSet(
        Equation const& equation)
{
    MultipleVariableSolutionSet solutionSet;
    calculateSolution(solutionSet, equation);
    return solutionSet;
}

void LinearDiophantineEquationSolver::calculateSolution(
        MultipleVariableSolutionSet & solutionSet,
        Equation const& equation)
{
    if(equation.getEquationOperator().isEqual())
    {
        Equation simplifiedEquation(equation);
        simplifiedEquation.simplify();
        calculateForEquation(solutionSet, simplifiedEquation);
    }
}

void LinearDiophantineEquationSolver::calculateForEquation(
        MultipleVariableSolutionSet & solutionSet,
        Equation const& equation)
{
    Term const& nonZeroLeftHandTerm(equation.getLeftHandTerm());
    if(canBeConvertedToPolynomial(nonZeroLeftHandTerm))
    {
        Polynomial polynomial(createPolynomialIfPossible(nonZeroLeftHandTerm));
        bool isPatternRecognized(false);
        AlbaNumber a, b, c;
        string xName, yName;
        retrieveDetailsFromPolynomial(isPatternRecognized, a, b, c, xName, yName, polynomial);
        if(isPatternRecognized)
        {
            LinearDiophantineEquationCoefficientSolver solver(a, b, c);
            if(solver.isSolved())
            {
                SolutionSet xSolution;
                SolutionSet ySolution;
                xSolution.addAcceptedValue(solver.getX());
                ySolution.addAcceptedValue(solver.getY());
                solutionSet.addSolutionSetForVariable(xName, xSolution);
                solutionSet.addSolutionSetForVariable(yName, ySolution);
                setAsIncompleteSolution();
            }
        }
    }
}

void LinearDiophantineEquationSolver::retrieveDetailsFromPolynomial(
        bool & isPatternRecognized, AlbaNumber & a, AlbaNumber & b, AlbaNumber & c, string & xName, string & yName, Polynomial const& polynomial)
{
    Monomials const& monomials(polynomial.getMonomialsConstReference());
    if(3U == monomials.size()
             && 1U==monomials.at(0).getVariablesToExponentsMapConstReference().size()
             && 1U==monomials.at(1).getVariablesToExponentsMapConstReference().size()
             && monomials.at(2).getVariablesToExponentsMapConstReference().empty())
    {
        a = monomials.at(0).getConstantConstReference();
        b = monomials.at(1).getConstantConstReference();        c = -monomials.at(2).getConstantConstReference();
        xName = monomials.at(0).getVariablesToExponentsMapConstReference().cbegin()->first;
        yName = monomials.at(1).getVariablesToExponentsMapConstReference().cbegin()->first;
        isPatternRecognized = true;    }
}

}

}
