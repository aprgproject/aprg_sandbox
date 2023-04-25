#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnFormula.hpp>

namespace alba {

namespace algebra {

class GeometricSeries : public SeriesBasedOnFormula {
public:
    GeometricSeries(AlbaNumber const& firstValue, AlbaNumber const& commonMultiplier);

    GeometricSeries(
        AlbaNumber const& valueAtNthIndex1, int const nthIndex1, AlbaNumber const& valueAtNthIndex2,
        int const nthIndex2);

    Term getInfiniteSumStartingFrom(int const startingNthIndex);

protected:
    Term getFormula(AlbaNumber const& firstValue, AlbaNumber const& commonMultiplier) const;
    Term getFormula(
        AlbaNumber const& valueAtNthIndex1, int const nthIndex1, AlbaNumber const& valueAtNthIndex2,
        int const nthIndex2) const;
};

}  // namespace algebra

}  // namespace alba
