#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnFormula.hpp>

namespace alba
{

namespace algebra
{

class ArithmeticSeries : public SeriesBasedOnFormula
{
public:
    ArithmeticSeries(
            AlbaNumber const& firstValue,
            AlbaNumber const& commonDifference);

    ArithmeticSeries(
            AlbaNumber const& valueAtIndex1,
            int const index1,
            AlbaNumber const& valueAtIndex2,
            int const index2);
private:
    Term getFormula(AlbaNumber const& firstValue, AlbaNumber const& commonDifference) const;
    Term getFormula(AlbaNumber const& valueAtIndex1, int const index1, AlbaNumber const& valueAtIndex2, int const index2) const;

};

}

}
