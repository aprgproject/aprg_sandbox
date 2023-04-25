#include "SummationSeriesOfArithmeticSeries.hpp"

#include <Algebra/Series/SpecificSeries/ArithmeticSeries.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

namespace alba {

namespace algebra {

SummationSeriesOfArithmeticSeries::SummationSeriesOfArithmeticSeries(
    AlbaNumber const& firstValue, AlbaNumber const& commonDifference)
    : SeriesBasedOnSummation(ArithmeticSeries(firstValue, commonDifference).getFormulaForSeries(), n) {}

SummationSeriesOfArithmeticSeries::SummationSeriesOfArithmeticSeries(
    AlbaNumber const& valueAtNthIndex1, int const nthIndex1, AlbaNumber const& valueAtNthIndex2, int const nthIndex2)
    : SeriesBasedOnSummation(
          ArithmeticSeries(valueAtNthIndex1, nthIndex1, valueAtNthIndex2, nthIndex2).getFormulaForSeries(), n) {}

}  // namespace algebra

}  // namespace alba
