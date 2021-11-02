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

    bool isConvergent() const;

    Term getValueAtIndex(int const index) const;
    Term getSum(int const startingIndex, int const endingIndex) const;
    Term getSumStartingAtIndexAndToInfinity(int const startingIndex) const;
    Term getValueAtInfinity() const;

private:
    Term m_formulaForSeries;
    std::string m_nameForVariableInFormula;
};

}

}
