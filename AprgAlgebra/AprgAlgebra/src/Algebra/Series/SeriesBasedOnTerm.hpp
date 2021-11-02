#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba
{

namespace algebra
{

class SeriesBasedOnTerm
{
public:

    SeriesBasedOnTerm(Term const& formulaForSeries, std::string const& nameForVariableInFormula);

    Term getValueAtIndex(int const index) const;
    Term getSum(
            int const startingIndex,
            int const endingIndex);
    Term getSumStartingAtIndexAndToInfinity(int const startingIndex);

private:
    Term m_formulaForSeries;
    std::string m_nameForVariableInFormula;
};

}

}
