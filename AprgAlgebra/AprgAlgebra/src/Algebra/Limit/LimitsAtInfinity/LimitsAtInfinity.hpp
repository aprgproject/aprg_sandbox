#pragma once

#include <Algebra/Limit/LimitsAtInfinity/DegreeOnlyMutator.hpp>
#include <Algebra/Limit/LimitsAtInfinity/RemoveMonomialsWithNegativeExponentMutator.hpp>
#include <Algebra/Simplification/SimplificationMutator.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba
{

namespace algebra
{

class LimitsAtInfinity
{
public:
    LimitsAtInfinity(
            Term const& term,
            std::string const& variableName);

    Term getSimplifiedTermAtInfinity() const;
    Term getValueAtInfinity(AlbaNumber::Value const infinityValue) const;

private:
    void simplify();
    void simplifyAsATerm();
    void simplifyAsTermsOverTermsIfPossible();
    AlbaNumber getMaxDegreeInNumeratorAndDenominator(
            Term const& numerator,
            Term const& denominator);

    Term m_simplifiedTermAtInfinity;
    std::string m_variableName;
    DegreeOnlyMutator m_degreeReductionMutator;
    RemoveMonomialsWithNegativeExponentMutator m_removeMonomialsWithNegativeExponentMutator;
    Simplification::SimplificationMutator m_simplificationMutator;
};

}

}
