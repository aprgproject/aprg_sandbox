#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>

namespace alba
{

namespace algebra
{

class AlternatingSeries : public SeriesBasedOnSummation
{
public:
    AlternatingSeries(Term const& formulaForEachTermWithoutSign, std::string const& nameForVariableInFormula);

    bool isConvergent() const override;
    Term getRemainderAtIndex(int const index) const override;

private:
    Term getFormula(Term const& formulaForEachTermWithoutSign, std::string const& nameForVariableInFormula) const;
    Term m_formulaForEachTermWithoutSign;
};

}

}
