#include "SeriesBasedOnTerm.hpp"

#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Summation/Summation.hpp>

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

Term SeriesBasedOnTerm::getValueAtIndex(int const index) const
{
    SubstitutionOfVariablesToValues substitution{{m_nameForVariableInFormula, index}};
    return substitution.performSubstitutionTo(m_formulaForSeries);
}

Term SeriesBasedOnTerm::getSum(
        int const startingIndex,
        int const endingIndex)
{
    Summation summation(m_formulaForSeries, m_nameForVariableInFormula);
    return summation.getSum(Term(startingIndex), Term(endingIndex));
}

Term SeriesBasedOnTerm::getSumStartingAtIndexAndToInfinity(
        int const startingIndex)
{
    Summation summation(m_formulaForSeries, m_nameForVariableInFormula);
    return summation.getSum(Term(startingIndex), Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)));
}

}

}
