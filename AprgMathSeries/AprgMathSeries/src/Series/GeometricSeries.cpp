#include "GeometricSeries.hpp"

#include <Series/Utilities.hpp>

#include <cmath>

namespace alba
{

namespace MathSeries
{

GeometricSeries::GeometricSeries(
        double const firstTerm,
        double const commonMultiplier)
    : m_firstTerm(firstTerm)
    , m_commonMultiplier(commonMultiplier)
{}

GeometricSeries::GeometricSeries(
        double const valueAtNthIndex1,
        int const nthIndex1,
        double const valueAtNthIndex2,
        int const nthIndex2)
{
    m_commonMultiplier = pow(valueAtNthIndex2/valueAtNthIndex1, 1/static_cast<double>(nthIndex2-nthIndex1));
    m_firstTerm = valueAtNthIndex1 / pow(m_commonMultiplier, nthIndex1);
}

double GeometricSeries::getValueAtIndex(int const nthIndex) const
{
    return m_firstTerm * pow(m_commonMultiplier, nthIndex);
}

double GeometricSeries::getSum(
        int const startingNthIndex,
        int const endingNthIndex)
{
    return getSumOfGeometricSeriesUsingFirstValueAndCommonMultiplier(
                getValueAtIndex(startingNthIndex),
                m_commonMultiplier,
                endingNthIndex - startingNthIndex + 1);
}

double GeometricSeries::getInfiniteSumIfMultiplierIsFractional(
        int const startingNthIndex)
{
    return getInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractional(
                getValueAtIndex(startingNthIndex),
                m_commonMultiplier);
}

}

}
