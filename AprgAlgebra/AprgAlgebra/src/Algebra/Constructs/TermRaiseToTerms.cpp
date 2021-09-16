#include "TermRaiseToTerms.hpp"

#include <Algebra/Constructs/PolynomialRaiseToANumber.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{
namespace algebra
{

TermRaiseToTerms::TermRaiseToTerms()
    : m_shouldSimplifyByCheckingPolynomialRaiseToANumber(false)
    , m_shouldSimplifyEvenExponentsCancellationWithAbsoluteValue(false)
{}

TermRaiseToTerms::TermRaiseToTerms(
        TermsWithDetails const& termsInRaiseToPowerExpression)
{
    processTermsInRaiseToPowerExpression(termsInRaiseToPowerExpression);
}

TermRaiseToTerms::TermRaiseToTerms(
        Term const& base,
        TermsWithDetails const& exponents)
    : m_base(base)
    , m_exponents(exponents)
    , m_shouldSimplifyByCheckingPolynomialRaiseToANumber(false)
    , m_shouldSimplifyEvenExponentsCancellationWithAbsoluteValue(false)
{
    //refactor simplify base
}

Term TermRaiseToTerms::getCombinedTerm() const
{
    Term combinedTerm(combineBaseAndExponentsAndReturn());
    return combinedTerm;
}

Term const& TermRaiseToTerms::getBase() const
{
    return m_base;}

TermsWithDetails const& TermRaiseToTerms::getExponents() const
{
    return m_exponents;
}

void TermRaiseToTerms::setBase(Term const& base)
{
    m_base = base;
}

void TermRaiseToTerms::setAsShouldSimplifyByCheckingPolynomialRaiseToANumber(
        bool const shouldSimplifyCondition)
{
    m_shouldSimplifyByCheckingPolynomialRaiseToANumber = shouldSimplifyCondition;
}

void TermRaiseToTerms::setAsShouldSimplifyEvenExponentsCancellationWithAbsoluteValue(
        bool const shouldSimplifyCondition)
{
    m_shouldSimplifyEvenExponentsCancellationWithAbsoluteValue = shouldSimplifyCondition;
}

void TermRaiseToTerms::simplify()
{
    // refactor: put polynomial expansion here: isPerfectNthPower

    if(m_shouldSimplifyByCheckingPolynomialRaiseToANumber && canBeConvertedToPolynomial(m_base))
    {
        PolynomialRaiseToANumber polynomialRaiseToANumber(createPolynomialIfPossible(m_base));
        if(!polynomialRaiseToANumber.isExponentOne())
        {
            m_base = polynomialRaiseToANumber.getBase();
            m_exponents.emplace(m_exponents.begin(), Term(polynomialRaiseToANumber.getExponent()), TermAssociationType::Positive);
        }
    }

    if(m_shouldSimplifyEvenExponentsCancellationWithAbsoluteValue
            && doesEvenExponentCancellationHappen())
    {
        m_base = simplifyAndConvertFunctionToSimplestTerm(Functions::abs(createOrCopyExpressionFromATerm(m_base)));
    }
}

void TermRaiseToTerms::processTermsInRaiseToPowerExpression(
        TermsWithDetails const& termsToProcess)
{
    if(!termsToProcess.empty())
    {
        m_base = getTermConstReferenceFromSharedPointer(termsToProcess.at(0).baseTermSharedPointer);
        //refactor simplify base -> checks as constant and polynomials
        if(isTheValue(m_base, 0))
        {
            m_base = Term(Constant(0));
        }
        else if(isTheValue(m_base, 1))
        {
            m_base = Term(1);
        }
        else
        {
            m_exponents.reserve(distance(termsToProcess.cbegin()+1, termsToProcess.cend()));
            copy(termsToProcess.cbegin()+1, termsToProcess.cend(), back_inserter(m_exponents));
        }
    }
}
bool TermRaiseToTerms::doesEvenExponentCancellationHappen() const
{
    bool result(false);
    Term previousAccumulatedExponentTerm(1);
    for(TermWithDetails const& exponentWithDetails : m_exponents)
    {
        Term const& currentExponent(getTermConstReferenceFromSharedPointer(exponentWithDetails.baseTermSharedPointer));
        // refactor instead of "combine" use currentAccumulatedExponentTerm
        Term currentAccumulatedExponentTerm = (TermAssociationType::Positive == exponentWithDetails.association) ?
                    previousAccumulatedExponentTerm * currentExponent :
                    previousAccumulatedExponentTerm / currentExponent;
        // refactor This is wrong: How about if monomial?
        if(previousAccumulatedExponentTerm.isConstant() && currentAccumulatedExponentTerm.isConstant())
        {
            AlbaNumber previousCombinedValue(previousAccumulatedExponentTerm.getConstantValueConstReference());            AlbaNumber currentExponentValue(currentExponent.getConstantValueConstReference());
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

Term TermRaiseToTerms::combineBaseAndExponentsAndReturn() const
{
    Term combinedTerm;
    Term exponentCombinedTerm;
    accumulateTermsForMultiplicationAndDivision(exponentCombinedTerm, m_exponents);
    //refactor simplify exponentCombinedTerm -> checks as constant and polynomials
    if(isTheValue(exponentCombinedTerm, 0))
    {
        combinedTerm = Term(1);
    }
    else if(isTheValue(exponentCombinedTerm, 1))
    {
        combinedTerm = m_base;
    }
    else if(canBeConvertedToMonomial(m_base)
            && exponentCombinedTerm.isConstant())
    {
        combinedTerm = m_base ^ exponentCombinedTerm;
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

}

}