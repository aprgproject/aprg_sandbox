#include "LimitsAtInfinity.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>

using namespace alba::algebra::Simplification;
using namespace std;

namespace alba
{

namespace algebra
{

LimitsAtInfinity::LimitsAtInfinity(
        Term const& term,
        std::string const& variableName)
    : m_simplifiedTermAtInfinity(term)
    , m_variableName(variableName)
    , m_degreeReductionMutator(variableName)
    , m_removeMonomialsWithNegativeExponentMutator(variableName)
    , m_simplificationMutator()
{
    SimplificationOfExpression simplification;
    simplification.setAsShouldSimplifyByCombiningMonomialAndRadicalExpressions(true);
    m_simplificationMutator.putSimplification(simplification);
    simplify();
}

Term LimitsAtInfinity::getSimplifiedTermAtInfinity() const
{
    return m_simplifiedTermAtInfinity;
}

Term LimitsAtInfinity::getValueAtInfinity(
        AlbaNumber::Value const infinityValue) const
{
    SubstitutionOfVariablesToValues substitution{{m_variableName, AlbaNumber(infinityValue)}};
    return substitution.performSubstitutionTo(m_simplifiedTermAtInfinity);
}

void LimitsAtInfinity::simplify()
{
    simplifyAsATerm();
    simplifyAsTermsOverTermsIfPossible();
}

void LimitsAtInfinity::simplifyAsATerm()
{
    m_simplifiedTermAtInfinity.simplify();
    m_removeMonomialsWithNegativeExponentMutator.mutateTerm(m_simplifiedTermAtInfinity);
}

void LimitsAtInfinity::simplifyAsTermsOverTermsIfPossible()
{
    TermsOverTerms currentTermsOverTerms(createTermsOverTermsFromTerm(m_simplifiedTermAtInfinity));
    Term numerator(currentTermsOverTerms.getCombinedNumerator());
    Term denominator(currentTermsOverTerms.getCombinedDenominator());
    AlbaNumber maxExponentInBoth = getMaxDegreeInNumeratorAndDenominator(numerator, denominator);
    Term termToDivide(Monomial(1, {{m_variableName, maxExponentInBoth}}));
    numerator = numerator/termToDivide;
    numerator.simplify();
    denominator = denominator/termToDivide;
    denominator.simplify();
    m_simplificationMutator.mutateTerm(numerator);
    m_simplificationMutator.mutateTerm(denominator);
    m_removeMonomialsWithNegativeExponentMutator.mutateTerm(numerator);
    m_removeMonomialsWithNegativeExponentMutator.mutateTerm(denominator);
    m_simplifiedTermAtInfinity = numerator/denominator;
    m_simplifiedTermAtInfinity.simplify();
}

AlbaNumber LimitsAtInfinity::getMaxDegreeInNumeratorAndDenominator(
        Term const& numerator,
        Term const& denominator)
{
    Term reducedNumerator(numerator);
    Term reducedDenominator(denominator);
    m_degreeReductionMutator.mutateTerm(reducedNumerator);
    m_degreeReductionMutator.mutateTerm(reducedDenominator);
    AlbaNumber maxExponentInNumerator;
    if(canBeConvertedToMonomial(reducedNumerator))
    {
        maxExponentInNumerator = createMonomialIfPossible(reducedNumerator).getDegree();
    }
    AlbaNumber maxExponentInDenominator;
    if(canBeConvertedToMonomial(reducedDenominator))
    {
        maxExponentInDenominator = createMonomialIfPossible(reducedDenominator).getDegree();
    }
    return max(maxExponentInNumerator, maxExponentInDenominator);
}

}

}
