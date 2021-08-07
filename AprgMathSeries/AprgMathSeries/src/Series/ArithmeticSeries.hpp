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
            double const valueAtIndex1,
            int const index1,
            double const valueAtIndex2,
            int const index2);

    double getValueAtIndex(int const index) const;
    double getSum(
            int const startingIndex,
            int const endingIndex);

private:
    double m_firstTerm;    double m_commonDifference;
};

}
}
