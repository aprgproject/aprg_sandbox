#include "TaylorSeries.hpp"

#include <Algebra/Differentiation/DifferentiationUtilities.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

TaylorSeries::TaylorSeries(Term const& formulaForTaylorSeries, string const& variableName)
    : m_formulaForTaylorSeries(formulaForTaylorSeries)
    , m_variableName(variableName)
{}

Term TaylorSeries::getFormulaForTaylorSeries() const
{
    return m_formulaForTaylorSeries;
}

Term TaylorSeries::getValueAtIndex(int const index, Term const& startingValue) const
{
    Term result;
    if(index >= 0)
    {
        unsigned int positiveIndex(static_cast<unsigned int>(index));
        result = getApproximationUsingTaylorsFormula(
                    m_formulaForTaylorSeries, m_variableName, startingValue, Term(m_variableName), positiveIndex);
    }
    return result;
}

Term TaylorSeries::getValueForMaclaurinSeriesAtIndex(int const index) const
{
    return getValueAtIndex(index, 0);
}


}

}
