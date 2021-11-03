#pragma once

#include <Algebra/Series/SeriesBasedOnTerm.hpp>

namespace alba
{

namespace algebra
{

class SeriesBasedOnSummation : public SeriesBasedOnTerm
{
public:
    SeriesBasedOnSummation(Term const& formulaForEachTermInSummation, std::string const& nameForVariableInFormula);

    bool hasAValidSummationModel() const;
    bool isConvergent() const override;

    Term getTermValueAtIndex(int const index) const;
    Term getFormulaForEachTermInSummation() const;

private:
    Term getFormulaForSummation(Term const& formulaForEachTermInSummation, std::string const& nameForVariableInFormula) const;
    Term m_formulaForEachTermInSummation;
    std::string m_nameForVariableInFormula;
    bool m_isSummationModelValid;
};

}

}
