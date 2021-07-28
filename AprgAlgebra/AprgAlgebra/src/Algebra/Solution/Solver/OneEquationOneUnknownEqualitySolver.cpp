#include "OneEquationOneUnknownEqualitySolver.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Solution/SolutionUtilities.hpp>
#include <Algebra/Solution/Solver/NewtonMethod.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

OneEquationOneUnknownEqualitySolver::OneEquationOneUnknownEqualitySolver()
    : BaseOneEquationOneUnknownSolver()
{}

void OneEquationOneUnknownEqualitySolver::calculateSolution(
        SolutionSet & solutionSet,
        Equation const& equation)
{
    if(equation.getEquationOperator().isEqual())
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

void OneEquationOneUnknownEqualitySolver::calculateForEquation(
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
        addValuesToSolutionSetIfNeeded(solutionSet, nonZeroLeftHandTerm, variableName);
    }
}

void OneEquationOneUnknownEqualitySolver::calculateForTermAndVariable(
        Term const& term,
        string const& variableName)
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
    else
    {
        performNewtonMethodToFindSolution(term, variableName);
    }
}

void OneEquationOneUnknownEqualitySolver::addValuesToSolutionSetIfNeeded(
        SolutionSet& solutionSet,
        Term const& term,
        string const& variableName)
{
    if(!m_calculatedValues.empty())
    {
        SubstitutionOfVariablesToValues substitution;
        for(AlbaNumber const& value : m_calculatedValues)
        {
            substitution.putVariableWithValue(variableName, value);
            Term substitutedResult(substitution.performSubstitutionTo(term));
            if(substitutedResult.isConstant())
            {
                AlbaNumber const& computedValue(
                            substitutedResult.getConstantConstReference().getNumberConstReference());
                if(!computedValue.isAFiniteValue())
                {
                    solutionSet.addRejectedValue(value);
                }
                else if(computedValue == 0)
                {
                    solutionSet.addAcceptedValue(value);
                }
            }
        }
    }
}

void OneEquationOneUnknownEqualitySolver::performNewtonMethodToFindSolution(
        Term const& termToCheck,
        string const& variableNameForSubstitution)
{
    SubstitutionOfVariablesToValues substitution;
    NewtonMethod newtonMethod(
                getInitialValueForNewtonMethod(termToCheck),
                [&](AlbaNumber const& value)
    {
        substitution.putVariableWithValue(variableNameForSubstitution, value);
        Term substitutedTerm(substitution.performSubstitutionTo(termToCheck));
        AlbaNumber computedValue;
        if(substitutedTerm.isConstant())
        {
            computedValue = substitutedTerm.getConstantConstReference().getNumberConstReference();
        }
        return computedValue;
    });

    newtonMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    if(newtonMethod.isSolved())
    {
        m_calculatedValues.emplace_back(newtonMethod.getCurrentComputedValue());
        setAsIncompleteSolution();
    }
}

}

}
