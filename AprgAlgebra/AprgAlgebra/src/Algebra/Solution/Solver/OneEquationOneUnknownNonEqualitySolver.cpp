#include "OneEquationOneUnknownNonEqualitySolver.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

OneEquationOneUnknownNonEqualitySolver::OneEquationOneUnknownNonEqualitySolver()
    : BaseOneEquationOneUnknownSolver()
{}

void OneEquationOneUnknownNonEqualitySolver::calculateSolution(
        SolutionSet & solutionSet,
        Equation const& equation)
{
    if(!equation.getEquationOperator().isEqual())
    {
        Equation simplifiedEquation(equation);
        simplifiedEquation.simplify();
        if(simplifiedEquation.isEquationSatisfied())
        {
            processWhenEquationIsAlwaysSatisfied(solutionSet);
        }
        else
        {
            calculateWhenEquationIsSometimesSatisfied(solutionSet, simplifiedEquation);
        }
    }
}

void OneEquationOneUnknownNonEqualitySolver::calculateForEquation(
        SolutionSet & solutionSet,
        Equation const& equation)
{
    Term const& nonZeroLeftHandTerm(equation.getLeftHandTerm());
    VariableNamesSet variableNames(getVariableNames(nonZeroLeftHandTerm));
    if(variableNames.size() == 1)
    {
        string variableName = *variableNames.cbegin();
        calculateForTermAndCheckAbsoluteValueFunctions(nonZeroLeftHandTerm, variableName);
        sortCalculatedValues();
        addIntervalsToSolutionSetIfNeeded(solutionSet, equation, variableName);
    }
}

void OneEquationOneUnknownNonEqualitySolver::calculateForTermAndVariable(
        Term const& term,
        string const& )
{
    PolynomialOverPolynomialOptional popOptional(
                createPolynomialOverPolynomialFromTermIfPossible(term));
    if(popOptional.hasContent())
    {
        PolynomialOverPolynomial const& pop(popOptional.getConstReference());
        AlbaNumbers numeratorRoots(getRoots(pop.getNumerator()));
        AlbaNumbers denominatorRoots(getRoots(pop.getDenominator()));
        m_calculatedValues.reserve(numeratorRoots.size() + denominatorRoots.size());
        copy(numeratorRoots.cbegin(), numeratorRoots.cend(), back_inserter(m_calculatedValues));
        copy(denominatorRoots.cbegin(), denominatorRoots.cend(), back_inserter(m_calculatedValues));
        setAsCompleteSolution();
    }
}

void OneEquationOneUnknownNonEqualitySolver::addIntervalsToSolutionSetIfNeeded(
        SolutionSet& solutionSet,
        Equation const& equation,
        string const& variableName)
{
    if(!m_calculatedValues.empty() && isACompleteSolution())
    {
        SubstitutionOfVariablesToValues substitution;
        solutionSet.determineAndAddAcceptedIntervals(m_calculatedValues, [&](AlbaNumber const& value)
        {
            substitution.putVariableWithValue(variableName, value);
            Equation substitutedEquation(substitution.performSubstitutionTo(equation));
            return substitutedEquation.isEquationSatisfied()
                    && isAFiniteValue(substitutedEquation.getLeftHandTerm())
                    && isAFiniteValue(substitutedEquation.getRightHandTerm());
        });
        setAsCompleteSolution();
    }
}

}

}
