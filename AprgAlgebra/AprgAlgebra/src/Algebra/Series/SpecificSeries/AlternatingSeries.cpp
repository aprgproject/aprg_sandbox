#include "AlternatingSeries.hpp"

#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

AlternatingSeries::AlternatingSeries(Term const& formulaForEachTermWithoutSign, string const& nameForVariableInFormula)
    : SeriesBasedOnSummation(getFormula(formulaForEachTermWithoutSign, nameForVariableInFormula), nameForVariableInFormula)
    , m_formulaForEachTermWithoutSign(formulaForEachTermWithoutSign)
{}

bool AlternatingSeries::isConvergent() const
{
    Term limit(getLimit(m_formulaForEachTermWithoutSign, getNameForVariableInFormula(), AlbaNumber(AlbaNumber::Value::PositiveInfinity)));
    return isTheValue(limit, 0);
}

Term AlternatingSeries::getRemainderAtIndex(int const index) const
{
    Term result;
    if(isConvergent())
    {
        result = getValueAtIndex(index);
    }
    else
    {
        result = SeriesBasedOnTerm::getRemainderAtIndex(index);
    }
    return result;
}

Term AlternatingSeries::getFormula(Term const& formulaForEachTermWithoutSign, string const& nameForVariableInFormula) const
{
    Term sign(createExpressionIfPossible({Term(-1), Term("^"), Term(nameForVariableInFormula)}));
    return Term(createExpressionIfPossible({sign, Term("*"), formulaForEachTermWithoutSign}));
}

}

}
