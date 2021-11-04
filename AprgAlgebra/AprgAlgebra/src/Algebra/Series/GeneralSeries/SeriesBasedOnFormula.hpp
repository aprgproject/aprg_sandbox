#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

#include <string>

namespace alba
{

namespace algebra
{

class SeriesBasedOnFormula
{
public:

    SeriesBasedOnFormula(Term const& formulaForSeries, std::string const& nameForVariableInFormula);
    virtual bool isConvergent() const;
    virtual bool isIncreasing() const;
    virtual bool isDecreasing() const;
    virtual bool isMonotonic() const;
    virtual bool isBounded() const;

    virtual Term getFormulaForSeries() const;
    virtual Term getValueAtIndex(int const index) const;
    virtual Term getSum(int const startingIndex, int const endingIndex) const;
    virtual Term getSumStartingAtIndexAndToInfinity(int const startingIndex) const;
    virtual Term getValueAtInfinity() const;
    virtual Term getRemainderAtIndex(int const index) const;
    virtual AlbaNumberOptional getGreatestLowerBound() const;
    virtual AlbaNumberOptional getLeastUpperBound() const;

    virtual std::string getNameForVariableInFormula() const;

private:
    AlbaNumbers getBoundValues() const;
    AlbaNumbers getExtremaIndexes() const;
    Term getSignDerivativeForFiniteCalculus() const;
    Term m_formulaForSeries;
    std::string m_nameForVariableInFormula;
};

}

}
