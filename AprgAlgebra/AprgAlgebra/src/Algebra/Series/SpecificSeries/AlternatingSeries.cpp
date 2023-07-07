#include "AlternatingSeries.hpp"

#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

using namespace alba::AlbaNumberConstants;
using namespace std;

namespace alba {

namespace algebra {

AlternatingSeries::AlternatingSeries(Term const& formulaForEachTermWithoutSign, string const& variableName)
    : SeriesBasedOnSummation(
          getFormula(formulaForEachTermWithoutSign, variableName), variableName),
      m_formulaForEachTermWithoutSign(formulaForEachTermWithoutSign) {}

bool AlternatingSeries::isConvergent() const {    Term limit(getLimit(m_formulaForEachTermWithoutSign, getNameForVariableInFormula(), ALBA_NUMBER_POSITIVE_INFINITY));
    return isTheValue(limit, 0);
}
Term AlternatingSeries::getRemainderAtIndex(int const index) const {
    Term result;
    if (isConvergent()) {
        result = getValueAtIndex(index);
    } else {
        result = SeriesBasedOnFormula::getRemainderAtIndex(index);
    }
    return result;
}

Term AlternatingSeries::getFormula(
    Term const& formulaForEachTermWithoutSign, string const& variableName) const {
    Term sign(createExpressionIfPossible({-1, "^", variableName}));
    return createExpressionIfPossible({sign, "*", formulaForEachTermWithoutSign});
}
}  // namespace algebra

}  // namespace alba