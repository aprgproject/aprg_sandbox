#include "ArithmeticSeries.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

namespace alba
{

namespace algebra
{

ArithmeticSeries::ArithmeticSeries(
        AlbaNumber const& firstValue,
        AlbaNumber const& commonDifference)
    : SeriesBasedOnTerm(getFormula(firstValue, commonDifference), N)
{}

ArithmeticSeries::ArithmeticSeries(
        AlbaNumber const& valueAtIndex1,
        int const index1,
        AlbaNumber const& valueAtIndex2,
        int const index2)
    : SeriesBasedOnTerm(getFormula(valueAtIndex1, index1, valueAtIndex2, index2), N)
{}

Term ArithmeticSeries::getFormula(
        AlbaNumber const& firstValue,
        AlbaNumber const& commonDifference) const
{
    return Term(firstValue) + Term(commonDifference)*Term(N);
}

Term ArithmeticSeries::getFormula(
        AlbaNumber const& valueAtIndex1,
        int const index1,
        AlbaNumber const& valueAtIndex2,
        int const index2) const
{
    AlbaNumber commonDifference = (valueAtIndex1 - valueAtIndex2)/(index1 - index2);
    AlbaNumber firstValue = valueAtIndex1 - commonDifference*index1;
    return getFormula(firstValue, commonDifference);
}

}

}
