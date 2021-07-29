#pragma once

namespace alba
{

namespace MathSeries
{

class ArithmeticSeries
{
public:

    ArithmeticSeries(
            double const firstTerm,
            double const commonDifference);

    ArithmeticSeries(
            double const valueAtNthIndex1,
            int const nthIndex1,
            double const valueAtNthIndex2,
            int const nthIndex2);

    double getValueAt(int const nthIndex) const;
    double getSum(
            int const startingNthIndex,
            int const endingNthIndex);

private:
    double m_firstTerm;
    double m_commonDifference;
};

}

}
