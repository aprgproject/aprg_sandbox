#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>

namespace alba {

namespace algebra {

class HarmonicSeries : public SeriesBasedOnSummation {
public:
    HarmonicSeries();

protected:
    Term getFormula() const;
};

}  // namespace algebra

}  // namespace alba
