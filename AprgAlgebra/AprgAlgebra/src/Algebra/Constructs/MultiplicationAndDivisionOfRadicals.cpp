#include "MultiplicationAndDivisionOfRadicals.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace alba::algebra::Simplification;
using namespace std;

namespace alba
{

namespace algebra
{

MultiplicationAndDivisionOfRadicals::MultiplicationAndDivisionOfRadicals()
{}

MultiplicationAndDivisionOfRadicals::MultiplicationAndDivisionOfRadicals(
        TermsWithDetails const& termsWithDetails)
    : m_termsWithDetails(termsWithDetails)
{}

Term MultiplicationAndDivisionOfRadicals::getCombinedTerm() const
{
    SimplificationOfExpression::ConfigurationDetails radicalSimplificationConfigurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    radicalSimplificationConfigurationDetails.shouldNotSimplifyByDistributingConstantExponentToEachBase = true;

    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(radicalSimplificationConfigurationDetails);

    Expression combinedExpression;
    combinedExpression.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    combinedExpression.putTermsWithDetails(m_termsWithDetails);
    Term combinedTerm(combinedExpression);
    combinedTerm.simplify();
    return combinedTerm;
}

TermsWithDetails const& MultiplicationAndDivisionOfRadicals::getTermsWithDetails() const
{
    return m_termsWithDetails;
}

void MultiplicationAndDivisionOfRadicals::simplify()
{
    SimplificationOfExpression::ConfigurationDetails radicalSimplificationConfigurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    radicalSimplificationConfigurationDetails.shouldNotSimplifyByDistributingConstantExponentToEachBase = true;

    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(radicalSimplificationConfigurationDetails);

    Monomial combinedMonomial(createMonomialFromNumber(1));
    RadicalDetails radicalDetails;
    TermsWithDetails remainingTerms;
    gatherDetails(radicalDetails, combinedMonomial, remainingTerms);

    AlbaNumber gcfOfExponents(getGcfOfExponents(radicalDetails));

    if(shouldBeCombined(radicalDetails, combinedMonomial, gcfOfExponents))
    {
        m_termsWithDetails.clear();
        combineMonomialAndRadicalsAndSave(radicalDetails, combinedMonomial, gcfOfExponents);
        saveRemainingTerms(remainingTerms);
    }
}

bool MultiplicationAndDivisionOfRadicals::shouldBeCombined(
        RadicalDetails const& radicalDetails,
        Monomial const& combinedMonomial,
        AlbaNumber const& gcfOfExponents)
{
    return gcfOfExponents != 1
            && !radicalDetails.empty()
            && isNotANegativeTermWithExponentDenominatorEven(combinedMonomial, gcfOfExponents);
}

bool MultiplicationAndDivisionOfRadicals::isNotANegativeTermWithExponentDenominatorEven(
        Monomial const& combinedMonomial,
        AlbaNumber const& gcfOfExponents)
{
    bool result(true);
    if(gcfOfExponents.isIntegerOrFractionType())
    {
        AlbaNumber::FractionData fractionData(gcfOfExponents.getFractionData());
        if(isEven(static_cast<unsigned int>(getAbsoluteValue<int>(fractionData.denominator))))
        {
            result = !isANegativeMonomial(combinedMonomial);
        }
    }
    return result;
}

void MultiplicationAndDivisionOfRadicals::gatherDetails(
        RadicalDetails & radicalDetails,
        Monomial & combinedMonomial,
        TermsWithDetails & remainingTerms)
{
    for(TermWithDetails const& termWithDetails : m_termsWithDetails)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(term));

        if(termRaiseToANumber.isRadical())
        {
            radicalDetails.emplace_back(RadicalDetail{termRaiseToANumber, termWithDetails.association});
        }
        else if(canBeConvertedToMonomial(term))
        {
            Monomial monomial(createMonomialIfPossible(term));
            if(termWithDetails.hasPositiveAssociation())
            {
                combinedMonomial.multiplyMonomial(monomial);
            }
            else
            {
                combinedMonomial.divideMonomial(monomial);
            }
        }
        else
        {
            remainingTerms.emplace_back(termWithDetails);
        }
    }
}

AlbaNumber MultiplicationAndDivisionOfRadicals::getGcfOfExponents(
        RadicalDetails const& radicalDetails)
{
    AlbaNumber gcfOfExponents(1);
    bool isFirst(true);
    for(RadicalDetail const& radicalDetail : radicalDetails)
    {
        TermRaiseToANumber const& radical(radicalDetail.radical);
        if(isFirst)
        {
            gcfOfExponents = radical.getExponent();
            isFirst = false;
        }
        else
        {
            gcfOfExponents = getGreatestCommonFactor(gcfOfExponents, radical.getExponent());
        }
    }
    return gcfOfExponents;
}

void MultiplicationAndDivisionOfRadicals::combineMonomialAndRadicalsAndSave(
        RadicalDetails const& radicalDetails,
        Monomial const& combinedMonomial,
        AlbaNumber const& gcfOfExponents)
{
    Monomial newMonomial(combinedMonomial);
    newMonomial.raiseToPowerNumber(AlbaNumber(1)/gcfOfExponents);
    TermsWithDetails newRadicalsWithDetails;
    for(RadicalDetail const& radicalDetail : radicalDetails)
    {
        TermRaiseToANumber newRadicalBaseAndExponent(radicalDetail.radical);
        newRadicalBaseAndExponent.setExponent(newRadicalBaseAndExponent.getExponent()/gcfOfExponents);
        Term newRadical(newRadicalBaseAndExponent.getCombinedTerm());
        if(canBeConvertedToMonomial(newRadical))
        {
            Monomial newRadicalMonomial(createMonomialIfPossible(newRadical));
            if(radicalDetail.association == TermAssociationType::Positive)
            {
                newMonomial.multiplyMonomial(newRadicalMonomial);
            }
            else
            {
                newMonomial.divideMonomial(newRadicalMonomial);
            }
        }
        else
        {
            newRadicalsWithDetails.emplace_back(newRadical, radicalDetail.association);
        }
    }
    Expression combinedExpression;
    combinedExpression.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    if(!isTheValue(newMonomial, 1))
    {
        combinedExpression.putTerm(Term(newMonomial), TermAssociationType::Positive);
    }
    combinedExpression.putTermsWithDetails(newRadicalsWithDetails);
    combinedExpression.putTermWithRaiseToPowerIfNeeded(Term(gcfOfExponents));
    m_termsWithDetails.emplace_back(Term(combinedExpression), TermAssociationType::Positive);
}

void MultiplicationAndDivisionOfRadicals::saveRemainingTerms(
        TermsWithDetails const& remainingTerms)
{
    for(TermWithDetails const& remainingTerm : remainingTerms)
    {
        m_termsWithDetails.emplace_back(remainingTerm);
    }
}

}

}
