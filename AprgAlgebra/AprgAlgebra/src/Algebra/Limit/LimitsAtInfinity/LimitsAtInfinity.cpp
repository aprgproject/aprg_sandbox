#include "LimitsAtInfinity.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace alba::algebra::Simplification;
using namespace std;

namespace alba
{

namespace algebra
{

LimitsAtInfinity::LimitsAtInfinity(
        Term const& term,
        string const& variableName)
    : m_simplifiedTermAtInfinity(term)
    , m_variableName(variableName)
    , m_isSimplifiedDenominatorZero(false)
    , m_degreeOnlyMutator(variableName)
    , m_removeMonomialsWithNegativeExponentMutator(variableName)
{
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
    if(!isNotANumber(m_simplifiedTermAtInfinity))
    {
        simplifyAsTermsOverTermsIfPossible();
        if(!isNotANumber(m_simplifiedTermAtInfinity))
        {
            simplifyPolynomialToMaxDegreeMonomialOnly();
        }
    }
}

void LimitsAtInfinity::simplifyAsATerm(){
    m_simplifiedTermAtInfinity.simplify();
    m_removeMonomialsWithNegativeExponentMutator.mutateTerm(m_simplifiedTermAtInfinity);
}
void LimitsAtInfinity::simplifyAsTermsOverTermsIfPossible()
{
    TermsOverTerms currentTermsOverTerms(createTermsOverTermsFromTerm(m_simplifiedTermAtInfinity));
    Term numerator(currentTermsOverTerms.getCombinedNumerator());
    Term denominator(currentTermsOverTerms.getCombinedDenominator());
    AlbaNumber numeratorDegree(getMaxDegree(numerator));
    AlbaNumber denominatorDegree(getMaxDegree(denominator));
    AlbaNumber degreeToRemove(getDegreeToRemove(numeratorDegree, denominatorDegree));
    Term termToDivide(Monomial(1, {{m_variableName, degreeToRemove}}));
    numerator = numerator/termToDivide;
    numerator.simplify();
    denominator = denominator/termToDivide;
    denominator.simplify();
    simplifyByCombiningRadicals(numerator);
    simplifyByCombiningRadicals(denominator);
    m_removeMonomialsWithNegativeExponentMutator.mutateTerm(numerator);
    m_removeMonomialsWithNegativeExponentMutator.mutateTerm(denominator);
    m_simplifiedTermAtInfinity = numerator/denominator;
}

void LimitsAtInfinity::simplifyByCombiningRadicals(Term & term) const
{
    SimplificationOfExpression::ConfigurationDetails limitAtInfinityConfigurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    limitAtInfinityConfigurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;

    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(limitAtInfinityConfigurationDetails);

    term.simplify();
}

void LimitsAtInfinity::simplifyPolynomialToMaxDegreeMonomialOnly()
{
    if(m_simplifiedTermAtInfinity.isPolynomial())
    {
        Polynomial newPolynomial(m_simplifiedTermAtInfinity.getPolynomialConstReference());
        AlbaNumber maxDegree(getMaxDegree(m_simplifiedTermAtInfinity));
        Monomial monomialWithMaxDegree(1, {{m_variableName, maxDegree}});
        newPolynomial.divideMonomial(monomialWithMaxDegree);
        m_removeMonomialsWithNegativeExponentMutator.mutatePolynomial(newPolynomial);
        newPolynomial.multiplyMonomial(monomialWithMaxDegree);
        m_simplifiedTermAtInfinity = Term(newPolynomial);
        m_simplifiedTermAtInfinity.simplify();
    }
}

AlbaNumber LimitsAtInfinity::getMaxDegree(Term const& term)
{
    Term degreeOnlyTerm(term);
    m_degreeOnlyMutator.mutateTerm(degreeOnlyTerm);
    AlbaNumber degree;
    if(canBeConvertedToMonomial(degreeOnlyTerm))
    {
        degree = createMonomialIfPossible(degreeOnlyTerm).getDegree();
    }
    return degree;
}

AlbaNumber LimitsAtInfinity::getDegreeToRemove(
        AlbaNumber const& numeratorDegree,
        AlbaNumber const& denominatorDegree)
{
    AlbaNumber degreeToRemove;
    if(numeratorDegree == denominatorDegree)
    {
        degreeToRemove = numeratorDegree;
    }
    else if(numeratorDegree > denominatorDegree)
    {
        degreeToRemove = min(numeratorDegree, denominatorDegree);
    }
    else if(numeratorDegree < denominatorDegree)
    {
        degreeToRemove = max(numeratorDegree, denominatorDegree);
    }
    return degreeToRemove;
}

}

}
