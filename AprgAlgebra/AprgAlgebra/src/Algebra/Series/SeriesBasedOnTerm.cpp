#include "SeriesBasedOnTerm.hpp"

#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Summation/Summation.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

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

}

}
