#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace algebra {

class TaylorSeries {
public:
    TaylorSeries(Term const& formulaForTaylorSeries, std::string const& variableName);

    Term getFormulaForTaylorSeries() const;
    Term getValueAtIndex(int const index, Term const& startingValue) const;
    Term getValueForMaclaurinSeriesAtIndex(int const index) const;

protected:
    Term m_formulaForTaylorSeries;
    std::string m_variableName;
};

}  // namespace algebra

}  // namespace alba
