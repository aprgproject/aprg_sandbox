#include "SummationSeriesOfGeometricSeries.hpp"

#include <Algebra/Series/GeometricSeries.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

namespace alba
{

namespace algebra
{

SummationSeriesOfGeometricSeries::SummationSeriesOfGeometricSeries(
        AlbaNumber const& firstValue,
        AlbaNumber const& commonMultiplier)
    : SeriesBasedOnSummation(
          GeometricSeries(firstValue, commonMultiplier).getFormulaForSeries(),
          n)
{}

SummationSeriesOfGeometricSeries::SummationSeriesOfGeometricSeries(
        AlbaNumber const& valueAtNthIndex1,
        int const nthIndex1,
        AlbaNumber const& valueAtNthIndex2,
        int const nthIndex2)
    : SeriesBasedOnSummation(
          GeometricSeries(valueAtNthIndex1, nthIndex1, valueAtNthIndex2, nthIndex2).getFormulaForSeries(),
          n)
{}

}

}
