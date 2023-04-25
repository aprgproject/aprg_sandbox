#include "HarmonicSeries.hpp"

#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

namespace alba {

namespace algebra {

HarmonicSeries::HarmonicSeries() : SeriesBasedOnSummation(getFormula(), n) {}

Term HarmonicSeries::getFormula() const {
    Term denominator(Polynomial{Monomial(1, {{n, 1}}), Monomial(1, {})});
    return Term(createExpressionIfPossible({1, "/", denominator}));
}

}  // namespace algebra

}  // namespace alba
