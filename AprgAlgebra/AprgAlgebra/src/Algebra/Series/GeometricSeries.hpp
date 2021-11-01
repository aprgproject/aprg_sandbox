#pragma once

namespace alba
{

namespace algebra
{

class GeometricSeries
{
public:

    GeometricSeries(
            double const firstTerm,
            double const commonMultiplier);

    GeometricSeries(
            double const valueAtNthIndex1,
            int const nthIndex1,
            double const valueAtNthIndex2,
            int const nthIndex2);

    double getValueAtIndex(int const nthIndex) const;
    double getSum(
            int const startingNthIndex,
            int const endingNthIndex);
    double getInfiniteSumIfMultiplierIsFractional(
            int const startingNthIndex);

private:
    double m_firstTerm;
    double m_commonMultiplier;
};

}

}
