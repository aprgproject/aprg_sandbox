#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>

namespace alba {

namespace algebra {

class AlternatingSeries : public SeriesBasedOnSummation {
public:
    AlternatingSeries(Term const& formulaForEachTermWithoutSign, std::string const& variableName);

    bool isConvergent() const override;
    Term getRemainderAtIndex(int const index) const override;

protected:
    Term getFormula(Term const& formulaForEachTermWithoutSign, std::string const& variableName) const;
    Term m_formulaForEachTermWithoutSign;
};

}  // namespace algebra

}  // namespace alba
