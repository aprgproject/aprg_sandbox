#include "PSeries.hpp"

#include <Algebra/Utilities/KnownNames.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

namespace alba
{

namespace algebra
{

PSeries::PSeries(AlbaNumber const& power)
    : SeriesBasedOnSummation(getFormula(power), n)
{}

Term PSeries::getFormula(AlbaNumber const& power) const
{
    Term denominatorBase(Polynomial{Monomial(1, {{n, 1}}), Monomial(1, {})});
    Term denominator(createExpressionIfPossible({denominatorBase, Term("^"), Term(power)}));
    return Term(createExpressionIfPossible({Term(1), Term("/"), denominator}));
}

}

}
