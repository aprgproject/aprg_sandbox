#include "ArithmeticSeries.hpp"

#include <Utilities.hpp>

namespace alba
{

namespace MathSeries
{

ArithmeticSeries::ArithmeticSeries(
        double const firstTerm,
        double const commonDifference)
    : m_firstTerm(firstTerm)
    , m_commonDifference(commonDifference)
{}

ArithmeticSeries::ArithmeticSeries(
        double const valueAtNthIndex1,
        int const nthIndex1,
        double const valueAtNthIndex2,
        int const nthIndex2)
{
    m_commonDifference = (valueAtNthIndex1 - valueAtNthIndex2)/(nthIndex1 - nthIndex2);
    m_firstTerm = valueAtNthIndex1 - (nthIndex1 - 1)*m_commonDifference;
}

double ArithmeticSeries::getValueAt(int const nthIndex) const
{
    return m_firstTerm + (nthIndex - 1)*m_commonDifference;
}

double ArithmeticSeries::getSum(
        int const startingNthIndex,
        int const endingNthIndex)
{
    return getSumOfArithmeticSeriesUsingFirstAndLastTerm(
                getValueAt(startingNthIndex),
                getValueAt(endingNthIndex),
                endingNthIndex - startingNthIndex + 1);}

}
}
