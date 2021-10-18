#include "TermRaiseToTerms.hpp"

#include <Algebra/Constructs/PolynomialRaiseToAnUnsignedInt.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

TermRaiseToTerms::TermRaiseToTerms()
    : m_shouldSimplifyToFactors(false)
    , m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(false)
    , m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(false)
{}

TermRaiseToTerms::TermRaiseToTerms(
        TermsWithDetails const& termsInRaiseToPowerExpression)
    : m_shouldSimplifyToFactors(false)
    , m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(false)
    , m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(false)
{
    initializeUsingTermsInRaiseToPowerExpression(termsInRaiseToPowerExpression);
}

TermRaiseToTerms::TermRaiseToTerms(
        Term const& base,
        TermsWithDetails const& exponents)
    : m_base(base)
    , m_exponents(exponents)
    , m_shouldSimplifyToFactors(false)
    , m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(false)
    , m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(false)
{}

TermRaiseToTerms::TermRaiseToTerms(
        Term const& base,
        Terms const& exponents)
    : m_base(base)
    , m_exponents()
    , m_shouldSimplifyToFactors(false)
    , m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(false)
    , m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(false)
{
    initializeExponentsInTerms(exponents);
}

bool TermRaiseToTerms::doesEvenExponentCancellationHappen() const
{
    bool result(false);
    AlbaNumbers exponentValues;
    for(TermWithDetails const& exponentWithDetails : m_exponents)
    {
        Term const& exponent(getTermConstReferenceFromSharedPointer(exponentWithDetails.baseTermSharedPointer));
        AlbaNumber exponentValue(getConstantFactor(exponent));
        if(exponentWithDetails.hasNegativeAssociation())
        {
            exponentValue = exponentValue^-1;
        }
        exponentValues.emplace_back(exponentValue);
    }
    bool hasAnyNumeratorEven(false);
    bool hasAnyDenominatorEven(false);
    for(AlbaNumber const& exponentValue : exponentValues)
    {
        AlbaNumber::FractionData fractionData(exponentValue.getFractionData());
        hasAnyNumeratorEven = hasAnyNumeratorEven || isEven(getAbsoluteValue<int>(fractionData.numerator));
        hasAnyDenominatorEven = hasAnyDenominatorEven || isEven(fractionData.denominator);
    }
    result = hasAnyNumeratorEven && hasAnyDenominatorEven;
    return result;
}

Term TermRaiseToTerms::getCombinedTerm() const
{
    Term combinedTerm(combineBaseAndExponentsAndReturn());
    return combinedTerm;
}

Term const& TermRaiseToTerms::getBase() const
{
    return m_base;
}

TermsWithDetails const& TermRaiseToTerms::getExponents() const
{
    return m_exponents;
}

void TermRaiseToTerms::setBase(Term const& base)
{
    m_base = base;
}

void TermRaiseToTerms::setAsShouldSimplifyToFactors(
        bool const shouldSimplifyToFactors)
{
    m_shouldSimplifyToFactors = shouldSimplifyToFactors;
}

void TermRaiseToTerms::setAsShouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(
        bool const shouldSimplify)
{
    m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt = shouldSimplify;
}

void TermRaiseToTerms::setAsShouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(
        bool const shouldSimplify)
{
    m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase = shouldSimplify;
}

void TermRaiseToTerms::simplify()
{
    simplifyByCheckingPolynomialRaiseToAnUnsignedIntIfNeeded();
    simplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseIfNeeded();
    simplifyBaseAndExponents();
}

void TermRaiseToTerms::simplifyByCheckingPolynomialRaiseToAnUnsignedIntIfNeeded()
{
    if(m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt && canBeConvertedToPolynomial(m_base))
    {
        PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(createPolynomialIfPossible(m_base));
        if(!polynomialRaiseToAnUnsignedInt.isExponentOne())
        {
            m_base = polynomialRaiseToAnUnsignedInt.getBase();
            m_exponents.emplace(m_exponents.begin(), Term(polynomialRaiseToAnUnsignedInt.getExponent()), TermAssociationType::Positive);
        }
    }
}

void TermRaiseToTerms::simplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseIfNeeded()
{
    if(m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase
            && doesEvenExponentCancellationHappen())
    {
        m_base = simplifyAndConvertFunctionToSimplestTerm(Functions::abs(createOrCopyExpressionFromATerm(m_base)));
    }
}

void TermRaiseToTerms::simplifyBaseAndExponents()
{
    Term exponentCombinedTerm;
    accumulateTermsForMultiplicationAndDivision(exponentCombinedTerm, m_exponents);

    m_exponents.clear();

    if(m_base.isConstant() && m_base.getConstantValueConstReference() == 0)
    {}
    else if(m_base.isConstant() && m_base.getConstantValueConstReference() == 1)
    {}
    else if(exponentCombinedTerm.isEmpty())
    {}
    else if(exponentCombinedTerm.isConstant() && exponentCombinedTerm.getConstantValueConstReference() == 0)
    {
        m_base = Term(1);
    }
    else if(exponentCombinedTerm.isConstant() && exponentCombinedTerm.getConstantValueConstReference() == 1)
    {}
    else if(canBeConvertedToMonomial(m_base)  && exponentCombinedTerm.isConstant())
    {
        Monomial monomialBase(createMonomialIfPossible(m_base));
        monomialBase.raiseToPowerNumber(exponentCombinedTerm.getConstantValueConstReference());
        m_base = simplifyAndConvertMonomialToSimplestTerm(monomialBase);
    }
    else if(m_base.isPolynomial()
            && !m_shouldSimplifyToFactors
            && exponentCombinedTerm.isConstant()
            && exponentCombinedTerm.getConstantValueConstReference().isIntegerType()
            && exponentCombinedTerm.getConstantValueConstReference() >= 0)
    {
        Polynomial polynomialBase(createPolynomialIfPossible(m_base));
        polynomialBase.raiseToUnsignedInteger(
                    static_cast<unsigned int>(exponentCombinedTerm.getConstantValueConstReference().getInteger()));
        m_base = simplifyAndConvertPolynomialToSimplestTerm(polynomialBase);
    }
    else if(exponentCombinedTerm.isExpression()
            && OperatorLevel::MultiplicationAndDivision == exponentCombinedTerm.getExpressionConstReference().getCommonOperatorLevel())
    {
        m_exponents = exponentCombinedTerm.getExpressionConstReference().getTermsWithAssociation().getTermsWithDetails();
    }
    else
    {
        m_exponents.emplace_back(exponentCombinedTerm, TermAssociationType::Positive);
    }
}

void TermRaiseToTerms::initializeUsingTermsInRaiseToPowerExpression(
        TermsWithDetails const& termsInRaiseToPowerExpression)
{
    if(!termsInRaiseToPowerExpression.empty())
    {
        m_base = getTermConstReferenceFromSharedPointer(termsInRaiseToPowerExpression.at(0).baseTermSharedPointer);
        m_exponents.reserve(distance(termsInRaiseToPowerExpression.cbegin()+1, termsInRaiseToPowerExpression.cend()));
        copy(termsInRaiseToPowerExpression.cbegin()+1, termsInRaiseToPowerExpression.cend(), back_inserter(m_exponents));
    }
}

void TermRaiseToTerms::initializeExponentsInTerms(
        Terms const& exponents)
{
    transform(exponents.cbegin(), exponents.cend(), back_inserter(m_exponents), [](Term const& exponent)
    {
        return TermWithDetails(exponent, TermAssociationType::Positive);
    });
}

Term TermRaiseToTerms::combineBaseAndExponentsAndReturn() const
{
    Term combinedTerm;
    if(m_exponents.empty())
    {
        combinedTerm = m_base;
    }
    else
    {
        Term exponentCombinedTerm;
        accumulateTermsForMultiplicationAndDivision(exponentCombinedTerm, m_exponents);
        Expression raiseToPowerExpression(createOrCopyExpressionFromATerm(m_base));
        raiseToPowerExpression.putTermWithRaiseToPowerIfNeeded(exponentCombinedTerm);
        combinedTerm = Term(raiseToPowerExpression);
    }
    return combinedTerm;
}

}

}
