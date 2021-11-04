#include "SeriesBasedOnTerm.hpp"

#include <Algebra/Differentiation/DifferentiationForFiniteCalculus.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Mutation/SignMutator.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Summation/Summation.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <algorithm>

using namespace alba::algebra::Simplification;

namespace alba
{

namespace algebra
{

SeriesBasedOnTerm::SeriesBasedOnTerm(
        Term const& formulaForSeries,
        std::string const& nameForVariableInFormula)
    : m_formulaForSeries(formulaForSeries)
    , m_nameForVariableInFormula(nameForVariableInFormula)
{}

bool SeriesBasedOnTerm::isConvergent() const
{
    return isAFiniteConstant(getValueAtInfinity());
}

bool SeriesBasedOnTerm::isIncreasing() const
{
    Term sign(getSignDerivativeForFiniteCalculus());
    return isTheValue(sign, 1);
}

bool SeriesBasedOnTerm::isDecreasing() const
{
    Term sign(getSignDerivativeForFiniteCalculus());
    return isTheValue(sign, -1);
}

bool SeriesBasedOnTerm::isMonotonic() const
{
    Term sign(getSignDerivativeForFiniteCalculus());
    return isTheValue(sign, 1) || isTheValue(sign, -1);
}

bool SeriesBasedOnTerm::isBounded() const
{
    AlbaNumberOptional greatestLowerBound(getGreatestLowerBound());
    AlbaNumberOptional leastUpperBound(getLeastUpperBound());
    return greatestLowerBound.hasContent() && leastUpperBound.hasContent();
}

Term SeriesBasedOnTerm::getFormulaForSeries() const
{
    return m_formulaForSeries;
}

Term SeriesBasedOnTerm::getValueAtIndex(int const index) const
{
    SubstitutionOfVariablesToValues substitution{{m_nameForVariableInFormula, index}};
    return substitution.performSubstitutionTo(m_formulaForSeries);
}

Term SeriesBasedOnTerm::getSum(
        int const startingIndex,
        int const endingIndex) const
{
    Summation summation(m_formulaForSeries, m_nameForVariableInFormula);
    return summation.getSum(Term(startingIndex), Term(endingIndex));
}

Term SeriesBasedOnTerm::getSumStartingAtIndexAndToInfinity(
        int const startingIndex) const
{
    Summation summation(m_formulaForSeries, m_nameForVariableInFormula);
    return summation.getSum(Term(startingIndex), Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)));
}

Term SeriesBasedOnTerm::getValueAtInfinity() const
{
    return getLimit(m_formulaForSeries, m_nameForVariableInFormula, AlbaNumber(AlbaNumber::Value::PositiveInfinity));
}

AlbaNumberOptional SeriesBasedOnTerm::getGreatestLowerBound() const
{
    AlbaNumberOptional result;
    AlbaNumbers boundValues(getBoundValues());

    if(boundValues.size() >= 2)
    {
        auto it = min_element(boundValues.cbegin(), boundValues.cend());
        if(it != boundValues.cend())
        {
            result.setConstReference(*it);
        }
    }
    else if(boundValues.size() == 1)
    {
        if(isIncreasing())
        {
            result.setConstReference(boundValues.back());
        }
    }
    return result;
}

AlbaNumberOptional SeriesBasedOnTerm::getLeastUpperBound() const
{
    AlbaNumberOptional result;
    AlbaNumbers boundValues(getBoundValues());
    if(boundValues.size() >= 2)
    {
        auto it = max_element(boundValues.cbegin(), boundValues.cend());
        if(it != boundValues.cend())
        {
            result.setConstReference(*it);
        }
    }
    else if(boundValues.size() == 1)
    {
        if(isDecreasing())
        {
            result.setConstReference(boundValues.back());
        }
    }
    return result;
}

AlbaNumbers SeriesBasedOnTerm::getBoundValues() const
{
    DifferentiationForFiniteCalculus differentiation(m_nameForVariableInFormula);
    Term secondDerivative(differentiation.differentiateMultipleTimes(m_formulaForSeries, 2));

    AlbaNumbers boundValues;
    AlbaNumbers extremaIndexes(getExtremaIndexes());
    extremaIndexes.emplace_back(AlbaNumber(0));
    for(AlbaNumber const& extremumIndex : extremaIndexes)
    {
        SubstitutionOfVariablesToValues substitution{{m_nameForVariableInFormula, extremumIndex}};
        Term secondDerivativeAtExtrema(substitution.performSubstitutionTo(secondDerivative));
        if(secondDerivativeAtExtrema.isConstant())
        {
            boundValues.emplace_back(secondDerivativeAtExtrema.getConstantValueConstReference());
        }
    }
    Term valueTermAtInfinity(getValueAtInfinity());
    if(isAFiniteConstant(valueTermAtInfinity))
    {
        boundValues.emplace_back(valueTermAtInfinity.getConstantValueConstReference());
    }
    return boundValues;
}

AlbaNumbers SeriesBasedOnTerm::getExtremaIndexes() const
{
    DifferentiationForFiniteCalculus differentiation(m_nameForVariableInFormula);
    Term firstDerivative(differentiation.differentiate(m_formulaForSeries));
    OneEquationOneVariableEqualitySolver solver;
    simplifyTermToACommonDenominator(firstDerivative);
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(firstDerivative, "=", Term(Constant(0)))));
    return solutionSet.getAcceptedValues();
}

Term SeriesBasedOnTerm::getSignDerivativeForFiniteCalculus() const
{
    DifferentiationForFiniteCalculus differentiation(m_nameForVariableInFormula);
    Term derivative(differentiation.differentiate(m_formulaForSeries));
    SignMutator signMutator;
    signMutator.putVariableWithSign(m_nameForVariableInFormula, TermAssociationType::Positive);
    signMutator.mutateTerm(derivative);
    return derivative;
}

}

}
