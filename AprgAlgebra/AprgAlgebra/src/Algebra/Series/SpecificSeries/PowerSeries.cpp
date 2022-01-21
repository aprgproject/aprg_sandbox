#include "PowerSeries.hpp"

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableNonEqualitySolver.hpp>
#include <Algebra/Series/Utilities/SeriesUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <numeric>

using namespace alba::algebra::Functions;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

PowerSeries::PowerSeries(
        Term const& multiplierForEachTerm,
        string const& nName,
        string const& xName,
        AlbaNumber const& aValue)
    : SeriesBasedOnSummation(getFormula(multiplierForEachTerm, nName, xName, aValue), nName)
    , m_nName(nName)
    , m_xName(xName)
{}

AlbaNumberIntervals PowerSeries::getIntervalsOfConvergence() const
{
    Term limitForRatioTest(getLimitForRatioTest(dynamic_cast<SeriesBasedOnSummation const&>(*this), getNameForVariableInFormula()));
    Term limitWithAbsoluteValue(abs(limitForRatioTest));
    OneEquationOneVariableNonEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(limitWithAbsoluteValue, "<", 1)));
    return solutionSet.getAcceptedIntervals();
}

AlbaNumber PowerSeries::getRadiusOfConvergence() const
{
    AlbaNumberIntervals intervals(getIntervalsOfConvergence());
    AlbaNumber result = accumulate(intervals.cbegin(), intervals.cend(), AlbaNumber(), [](
                                   AlbaNumber const& partialSum,
                                   AlbaNumberInterval const& nextInterval)
    {
        return partialSum + getAbsoluteValueForAlbaNumber(nextInterval.getHigherEndpoint().getValue() - nextInterval.getLowerEndpoint().getValue());
    });
    result = result/static_cast<long long int>(intervals.size())/2;
    return result;
}

void PowerSeries::differentiate()
{
    Differentiation differentiation(m_xName);
    m_formulaForEachTermInSummation = differentiation.differentiate(m_formulaForEachTermInSummation);
    m_isSummationModelValid = false;
}

void PowerSeries::integrate()
{
    Integration integration(m_xName);
    m_formulaForEachTermInSummation = integration.integrate(m_formulaForEachTermInSummation);
    m_isSummationModelValid = false;
}

Term PowerSeries::getFormula(
        Term const& multiplierForEachTerm,
        string const& nName,
        string const& xName,
        AlbaNumber const& aValue) const
{
    Term subTerm(createExpressionIfPossible({Term(xName), Term("-"), Term(aValue)}));
    return Term(createExpressionIfPossible({multiplierForEachTerm, Term("*"), subTerm, Term("^"), Term(nName)}));
}

}

}
