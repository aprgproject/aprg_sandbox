#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnFormula.hpp>
#include <Algebra/Summation/Summation.hpp>

namespace alba
{

namespace algebra
{

class SeriesBasedOnSummation : public SeriesBasedOnFormula
{
public:
    SeriesBasedOnSummation(Term const& formulaForEachTermInSummation, std::string const& nameForVariableInFormula);

    bool isSummationModelValid() const;
    bool isConvergent() const override;
    Term getValueAtIndex(int const index) const override;

    bool isAbsolutelyConvergent() const;
    bool isConditionallyConvergent() const;

    Term getTermValueAtIndex(int const index) const;
    Term getFormulaForEachTermInSummation() const;

protected:
    Summation getSummation(Term const& formulaForEachTermInSummation, std::string const& nameForVariableInFormula) const;
    Term getFormulaForSummation(Term const& formulaForEachTermInSummation, std::string const& nameForVariableInFormula) const;
    Term m_formulaForEachTermInSummation;    std::string m_nameForVariableInFormula;
    Summation m_summation;
    bool m_isSummationModelValid;
};
}

}
