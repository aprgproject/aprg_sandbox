#include "TermRaiseToTerms.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace algebra
{

TermRaiseToTerms::TermRaiseToTerms()
    : m_shouldSimplifyEvenExponentsCancellationWithAbsoluteValue(false)
{}

TermRaiseToTerms::TermRaiseToTerms(
        Term const& base,
        TermsWithAssociation::TermsWithDetails const& exponents)
    : m_shouldSimplifyEvenExponentsCancellationWithAbsoluteValue(false)
    , m_base(base)
    , m_exponents(exponents)
{}

Term TermRaiseToTerms::getCombinedTerm() const
{
    Term combinedTerm;
    Term exponentCombinedTerm;
    accumulateTermsForMultiplicationAndDivision(exponentCombinedTerm, m_exponents);
    if(isTheValue(exponentCombinedTerm, 0))
    {
        combinedTerm = Term(1);
    }
    else if(isTheValue(exponentCombinedTerm, 1))
    {
        combinedTerm = m_base;
    }
    else if(canBeConvertedToPolynomial(m_base)
            && exponentCombinedTerm.isConstant()
            && exponentCombinedTerm.getConstantValueConstReference().isIntegerType())
    {
        combinedTerm = m_base ^ exponentCombinedTerm;
    }
    else
    {
        Expression raiseToPowerExpression(createOrCopyExpressionFromATerm(m_base));
        raiseToPowerExpression.putTermWithRaiseToPowerIfNeeded(exponentCombinedTerm);
        combinedTerm = Term(raiseToPowerExpression);
    }
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

void TermRaiseToTerms::simplify()
{
    // refactor: put polynomial expansion here: isPerfectNthPower
    if(m_shouldSimplifyEvenExponentsCancellationWithAbsoluteValue
            && doesEvenExponentCancellationHappen())
    {
        m_base=simplifyAndConvertFunctionToSimplestTerm(Functions::abs(createOrCopyExpressionFromATerm(m_base)));
    }
}

bool TermRaiseToTerms::doesEvenExponentCancellationHappen() const
{
    bool result(false);
    Term previousAccumulatedExponentTerm(1);
    for(TermWithDetails const& exponentWithDetails : m_exponents)
    {
        Term const& currentExponent(getTermConstReferenceFromSharedPointer(exponentWithDetails.baseTermSharedPointer));
        Term currentAccumulatedExponentTerm = (TermAssociationType::Positive == exponentWithDetails.association) ?
                    previousAccumulatedExponentTerm*currentExponent :
                    previousAccumulatedExponentTerm/currentExponent;
        //This is wrong: How about if monomial?
        if(previousAccumulatedExponentTerm.isConstant() && currentAccumulatedExponentTerm.isConstant())
        {
            AlbaNumber previousCombinedValue(previousAccumulatedExponentTerm.getConstantValueConstReference());
            AlbaNumber currentExponentValue(currentExponent.getConstantValueConstReference());
            if((previousCombinedValue.isIntegerType() || previousCombinedValue.isFractionType())
                    && (currentExponentValue.isIntegerType() || currentExponentValue.isFractionType()))
            {
                bool isPreviousCombinedValueNumeratorEven(isEven(static_cast<unsigned int>(previousCombinedValue.getFractionData().numerator)));
                bool isExponentValueDenominatorEven(isEven(static_cast<unsigned int>(currentExponentValue.getFractionData().denominator)));
                result = isPreviousCombinedValueNumeratorEven && isExponentValueDenominatorEven;
            }
        }
        else
        {
            break;
        }
        previousAccumulatedExponentTerm = currentAccumulatedExponentTerm;
    }
    return result;
}

}

}
