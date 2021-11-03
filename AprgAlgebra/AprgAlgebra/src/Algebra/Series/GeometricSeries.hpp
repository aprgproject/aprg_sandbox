#pragma once

#include <Algebra/Series/SeriesBasedOnTerm.hpp>

namespace alba
{

namespace algebra
{

class GeometricSeries : public SeriesBasedOnTerm
{
public:
    GeometricSeries(
            AlbaNumber const& firstValue,
            AlbaNumber const& commonMultiplier);
    GeometricSeries(
            AlbaNumber const& valueAtNthIndex1,
            int const nthIndex1,            AlbaNumber const& valueAtNthIndex2,
            int const nthIndex2);

    Term getInfiniteSumStartingFrom(
            int const startingNthIndex);

private:
    Term getFormula(AlbaNumber const& firstValue, AlbaNumber const& commonMultiplier) const;
    Term getFormula(AlbaNumber const& valueAtNthIndex1, int const nthIndex1, AlbaNumber const& valueAtNthIndex2, int const nthIndex2) const;
};

}
}