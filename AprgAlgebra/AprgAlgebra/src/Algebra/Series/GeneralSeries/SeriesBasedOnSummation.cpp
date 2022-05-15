#include "SeriesBasedOnSummation.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

SeriesBasedOnSummation::SeriesBasedOnSummation(
        Term const& formulaForEachTermInSummation,
        string const& nameForVariableInFormula)
    : SeriesBasedOnFormula(getFormulaForSummation(formulaForEachTermInSummation, nameForVariableInFormula), nameForVariableInFormula)
    , m_formulaForEachTermInSummation(formulaForEachTermInSummation)
    , m_nameForVariableInFormula(nameForVariableInFormula)
    , m_summation(getSummation(formulaForEachTermInSummation, nameForVariableInFormula))
    , m_isSummationModelValid(!isNan(getFormulaForSeries()))
{}

bool SeriesBasedOnSummation::isSummationModelValid() const{
    return m_isSummationModelValid;
}
bool SeriesBasedOnSummation::isConvergent() const
{
    bool result(false);
    if(m_isSummationModelValid)
    {
        result = SeriesBasedOnFormula::isConvergent();
    }
    else
    {
        result = getLimit(m_formulaForEachTermInSummation, m_nameForVariableInFormula, AlbaNumber(AlbaNumber::Value::PositiveInfinity)) == 0;
    }
    return result;
}

Term SeriesBasedOnSummation::getValueAtIndex(int const index) const
{
    Term result;
    if(m_isSummationModelValid)
    {
        result = SeriesBasedOnFormula::getValueAtIndex(index);
    }
    else
    {
        result = m_summation.getSum(0, index);
    }
    return result;
}

bool SeriesBasedOnSummation::isAbsolutelyConvergent() const
{
    SeriesBasedOnSummation summation(
                abs(m_formulaForEachTermInSummation),
                m_nameForVariableInFormula);
    return summation.isConvergent();
}

bool SeriesBasedOnSummation::isConditionallyConvergent() const
{
    return !isAbsolutelyConvergent() || isConvergent();
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

Summation SeriesBasedOnSummation::getSummation(
        Term const& formulaForEachTermInSummation,
        string const& nameForVariableInFormula) const
{
    Summation summation(formulaForEachTermInSummation, nameForVariableInFormula);
    return summation;
}

Term SeriesBasedOnSummation::getFormulaForSummation(
        Term const& formulaForEachTermInSummation,
        string const& nameForVariableInFormula) const
{
    return getSummation(formulaForEachTermInSummation, nameForVariableInFormula).getSummationModelWithKnownConstant(0);
}

}

}
