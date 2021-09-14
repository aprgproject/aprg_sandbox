#pragma once

#include <Algebra/Limit/LimitsAtInfinity/DegreeOnlyMutator.hpp>
#include <Algebra/Limit/LimitsAtInfinity/RemoveMonomialsWithNegativeExponentMutator.hpp>
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
    void simplifyByCombiningRadicals(Term & term) const;
    void simplifyPolynomialToMaxDegreeMonomialOnly();
    AlbaNumber getMaxDegree(Term const& term);
    AlbaNumber getDegreeToRemove(            AlbaNumber const& numeratorDegree,
            AlbaNumber const& denominatorDegree);

    Term m_simplifiedTermAtInfinity;    std::string m_variableName;
    bool m_isSimplifiedDenominatorZero;
    DegreeOnlyMutator m_degreeOnlyMutator;
    RemoveMonomialsWithNegativeExponentMutator m_removeMonomialsWithNegativeExponentMutator;
};

}
}