#include "OneEquationOneVariableNonEqualitySolver.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

OneEquationOneVariableNonEqualitySolver::OneEquationOneVariableNonEqualitySolver()
    : BaseOneEquationOneVariableSolver()
{}

void OneEquationOneVariableNonEqualitySolver::calculateSolution(
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

void OneEquationOneVariableNonEqualitySolver::calculateForEquation(
        SolutionSet & solutionSet,
        Equation const& equation)
{
    Term const& nonZeroLeftHandTerm(equation.getLeftHandTerm());
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromTerm(nonZeroLeftHandTerm);
    VariableNamesSet const& variableNames(variableNamesRetriever.getSavedData());
    if(variableNames.size() == 1)
    {
        string variableName = *variableNames.cbegin();
        calculateForTermAndCheckAbsoluteValueFunctions(nonZeroLeftHandTerm, variableName);
        sortAndRemoveDuplicateCalculatedValues();
        addIntervalsToSolutionSetIfNeeded(solutionSet, equation, variableName);
    }
}

void OneEquationOneVariableNonEqualitySolver::calculateForTermAndVariable(
        Term const& term,
        string const& )
{
    PolynomialOverPolynomialOptional popOptional(
                createPolynomialOverPolynomialFromTermIfPossible(term));
    if(popOptional.hasContent())
    {
        PolynomialOverPolynomial const& pop(popOptional.getConstReference());
        AlbaNumbers numeratorRoots(getRoots(RootType::RealAndImaginaryRoots, pop.getNumerator()));
        AlbaNumbers denominatorRoots(getRoots(RootType::RealAndImaginaryRoots, pop.getDenominator()));
        m_calculatedValues.reserve(numeratorRoots.size() + denominatorRoots.size());
        copy(numeratorRoots.cbegin(), numeratorRoots.cend(), back_inserter(m_calculatedValues));
        copy(denominatorRoots.cbegin(), denominatorRoots.cend(), back_inserter(m_calculatedValues));
        setAsCompleteSolution();
    }
}

void OneEquationOneVariableNonEqualitySolver::addIntervalsToSolutionSetIfNeeded(
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
            return isARealFiniteConstant(substitutedEquation.getLeftHandTerm())
                    && isARealFiniteConstant(substitutedEquation.getRightHandTerm())
                    && substitutedEquation.isEquationSatisfied();
        });
        setAsCompleteSolution();    }
}

}
}
