#include "ArithmeticSeries.hpp"

#include <Algebra/Series/SeriesUtilities.hpp>

namespace alba
{

namespace algebra
{

ArithmeticSeries::ArithmeticSeries(
        double const firstTerm,
        double const commonDifference)
    : m_firstTerm(firstTerm)
    , m_commonDifference(commonDifference)
{}

ArithmeticSeries::ArithmeticSeries(
        double const valueAtIndex1,
        int const index1,
        double const valueAtIndex2,
        int const index2)
{
    m_commonDifference = (valueAtIndex1 - valueAtIndex2)/(index1 - index2);
    m_firstTerm = valueAtIndex1 - index1*m_commonDifference;
}

double ArithmeticSeries::getValueAtIndex(int const index) const
{
    return m_firstTerm + index*m_commonDifference;
}

double ArithmeticSeries::getSum(
        int const startingIndex,
        int const endingIndex)
{
    return getSumOfArithmeticSeriesUsingFirstAndLastValue(
                getValueAtIndex(startingIndex),
                getValueAtIndex(endingIndex),
                endingIndex - startingIndex + 1);
}

}

}
