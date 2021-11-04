#include "SeriesBasedOnSummation.hpp"

#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Summation/Summation.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

SeriesBasedOnSummation::SeriesBasedOnSummation(
        Term const& formulaForEachTermInSummation,
        string const& nameForVariableInFormula)
    : SeriesBasedOnTerm(getFormulaForSummation(formulaForEachTermInSummation, nameForVariableInFormula), nameForVariableInFormula)
    , m_formulaForEachTermInSummation(formulaForEachTermInSummation)
    , m_nameForVariableInFormula(nameForVariableInFormula)
    , m_isSummationModelValid(!isNotANumber(getFormulaForSeries()))
{}

bool SeriesBasedOnSummation::hasAValidSummationModel() const
{
    return m_isSummationModelValid;
}

bool SeriesBasedOnSummation::isConvergent() const
{
    bool result(false);
    if(m_isSummationModelValid)
    {
        result = SeriesBasedOnTerm::isConvergent();
    }
    else
    {
        result = getLimit(m_formulaForEachTermInSummation, m_nameForVariableInFormula, AlbaNumber(AlbaNumber::Value::PositiveInfinity)) == Term(Constant(0));
    }
    return result;
}

Term SeriesBasedOnSummation::getTermValueAtIndex(int const index) const
{
    SubstitutionOfVariablesToValues substitution{{m_nameForVariableInFormula, index}};
    return substitution.performSubstitutionTo(m_formulaForEachTermInSummation);
}

Term SeriesBasedOnSummation::getFormulaForEachTermInSummation() const
{
    return m_formulaForEachTermInSummation;
}

Term SeriesBasedOnSummation::getFormulaForSummation(
        Term const& formulaForEachTermInSummation,
        string const& nameForVariableInFormula) const
{
    Summation summation(formulaForEachTermInSummation, nameForVariableInFormula);
    return summation.getSummationModelWithKnownConstant(0);
}

}

}
