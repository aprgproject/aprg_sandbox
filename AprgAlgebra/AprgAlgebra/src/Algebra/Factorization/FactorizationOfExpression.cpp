#include "FactorizationOfExpression.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Factorization/FactorizationOfTerm.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

Terms factorizeAnExpression(Expression const& expression)
{
    TermsRaiseToNumbers termsRaiseToNumbers(factorizeToTermsRaiseToNumbers(expression));
    return termsRaiseToNumbers.getTermsInMultiplicationOperation();
}

Terms factorizeAnExpressionWithConfigurationChanged(
        Expression const& expression)
{
    ConfigurationDetails configurationDetails(
                Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    return factorizeAnExpression(expression);
}

TermsRaiseToNumbers factorizeToTermsRaiseToNumbers(Expression const& expression)
{
    TermsRaiseToNumbers result;
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        result = factorizeToTermsRaiseToNumbersForAdditionAndSubtraction(expression);
    }
    else if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        result = factorizeToTermsRaiseToNumbersForMultiplicationAndDivision(expression);
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        result = factorizeToTermsRaiseToNumbersForRaiseToPower(expression);
    }
    else
    {
        result.putTerm(convertExpressionToSimplestTerm(expression), TermAssociationType::Positive);
    }
    return result;
}

TermsRaiseToNumbers factorizeToTermsRaiseToNumbersForAdditionAndSubtraction(
        Expression const& expression)
{
    TermsRaiseToNumbers result;
    vector<TermsRaiseToNumbers> nonConstantFactorsPerAddends;
    AlbaNumbers constantFactorsPerAddends;
    TermsWithDetails const& originalTermsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    retrieveConstantAndNonConstantFactors(nonConstantFactorsPerAddends, constantFactorsPerAddends, originalTermsWithDetails);

    AlbaNumber constantGcf(getGcfOfConstants(constantFactorsPerAddends));

    TermsRaiseToNumbers commonNonConstantFactors;
    retrieveCommonNonConstantFactors(commonNonConstantFactors, nonConstantFactorsPerAddends);

    result = getFactorizedItemsForAdditionAndSubtraction(expression, constantFactorsPerAddends, nonConstantFactorsPerAddends, constantGcf, commonNonConstantFactors);

    return result;
}

TermsRaiseToNumbers factorizeToTermsRaiseToNumbersForMultiplicationAndDivision(
        Expression const& expression)
{
    TermsRaiseToNumbers result;
    for(TermWithDetails const& termWithDetails : expression.getTermsWithAssociation().getTermsWithDetails())
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        Terms factorizedTerms(factorizeTerm(term));
        result.putTerms(factorizedTerms, termWithDetails.association);
    }
    return result;
}

TermsRaiseToNumbers factorizeToTermsRaiseToNumbersForRaiseToPower(
        Expression const& expression)
{
    TermsRaiseToNumbers result;
    TermRaiseToANumber mainBaseToExponent(createTermRaiseToANumberFromExpression(expression));
    Term const& base(mainBaseToExponent.getBase());
    AlbaNumber const& exponent(mainBaseToExponent.getExponent());

    if(dontFactorizeBaseBecauseBaseIsARaiseToPowerExpression(base)
            || dontFactorizeBecauseThereIsSquareRootOfNegativeNumber(base, exponent))
    {
        result.setBaseAndExponent(base, mainBaseToExponent.getExponent());
    }
    else
    {
        Terms factorizedBases(factorizeTerm(base));
        result.putTerms(factorizedBases, TermAssociationType::Positive);
        result.multiplyToExponents(mainBaseToExponent.getExponent());
    }
    return result;
}

void retrieveConstantAndNonConstantFactors(
        vector<TermsRaiseToNumbers> & nonConstantFactorsPerAddends,
        AlbaNumbers & constantFactors,
        TermsWithDetails const& originalTermsWithDetails)
{
    for(TermWithDetails const& originalTermWithDetails : originalTermsWithDetails)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(originalTermWithDetails.baseTermSharedPointer));
        Terms factors(factorizeTerm(term));

        AlbaNumber constantFactor(1);
        TermsRaiseToNumbers nonConstantRaiseToExponent;
        for(Term const& factor : factors)
        {
            if(factor.isConstant())
            {
                constantFactor *= factor.getConstantValueConstReference();
            }
            else
            {
                nonConstantRaiseToExponent.putTerm(factor, TermAssociationType::Positive);
            }
        }
        constantFactors.emplace_back(constantFactor);
        nonConstantFactorsPerAddends.emplace_back(nonConstantRaiseToExponent);
    }
}

AlbaNumber getGcfOfConstants(AlbaNumbers const& constantFactorsPerAddends)
{
    AlbaNumber constantGcf;
    if(!constantFactorsPerAddends.empty())
    {
        constantGcf = constantFactorsPerAddends.front();
        for(auto it=constantFactorsPerAddends.cbegin()+1; it!=constantFactorsPerAddends.cend(); it++)
        {
            constantGcf = getGreatestCommonFactor(constantGcf, *it);
        }
    }
    return constantGcf;
}

void retrieveCommonNonConstantFactors(
        TermsRaiseToNumbers & commonNonConstantFactors,
        vector<TermsRaiseToNumbers> const& nonConstantFactorsPerAddends)
{
    if(!nonConstantFactorsPerAddends.empty())
    {
        commonNonConstantFactors = nonConstantFactorsPerAddends.front();
        for(auto it=nonConstantFactorsPerAddends.cbegin()+1; it!=nonConstantFactorsPerAddends.cend(); it++)
        {
            for(auto const& commonFactorBaseExponentPair : commonNonConstantFactors.getBaseToExponentMap())
            {
                Term const& base(commonFactorBaseExponentPair.first);
                AlbaNumber const& exponentAtCommonFactor(commonFactorBaseExponentPair.second);
                AlbaNumber exponentAtAddend(it->getExponentOfBase(base));
                if(exponentAtAddend > 0)
                {
                    commonNonConstantFactors.setBaseAndExponent(base, min(exponentAtCommonFactor, exponentAtAddend));
                }
                else if(exponentAtAddend < 0)
                {
                    commonNonConstantFactors.setBaseAndExponent(base, max(exponentAtCommonFactor, exponentAtAddend));
                }
                else
                {
                    commonNonConstantFactors.setBaseAndExponent(base, 0);
                }
            }
            commonNonConstantFactors.simplify();
            if(commonNonConstantFactors.getBaseToExponentMap().empty())
            {
                break;
            }
        }
    }
}

TermsRaiseToNumbers getFactorizedItemsForAdditionAndSubtraction(
        Expression const& expression,
        AlbaNumbers const& constantFactorsPerAddends,
        vector<TermsRaiseToNumbers> const& nonConstantFactorsPerAddends,
        AlbaNumber const& constantGcf,
        TermsRaiseToNumbers const& commonNonConstantFactors)
{
    TermsWithDetails outerAddends;
    TermsWithDetails const& originalAddends(expression.getTermsWithAssociation().getTermsWithDetails());
    for(unsigned int i=0; i<constantFactorsPerAddends.size() && i<nonConstantFactorsPerAddends.size() && i<originalAddends.size(); i++)
    {
        TermsWithDetails innerMultipliers;
        putRemainingConstantFactorAsAnInnerMultiplier(innerMultipliers, constantFactorsPerAddends.at(i), constantGcf);
        putRemainingNonConstantFactorsAsInnerMultipliers(innerMultipliers, nonConstantFactorsPerAddends.at(i), commonNonConstantFactors);
        putRemainingInnerMultipliersAsOuterAddend(outerAddends, innerMultipliers, originalAddends.at(i));
    }
    return getFactorizedItemsBasedFromCollectedData(constantGcf, commonNonConstantFactors, outerAddends);
}

void putRemainingConstantFactorAsAnInnerMultiplier(
        TermsWithDetails & innerMultipliers,
        AlbaNumber const& constantFactorOfOriginalAddend,
        AlbaNumber const& constantGcf)
{
    AlbaNumber remainingConstant(constantFactorOfOriginalAddend/constantGcf);
    if(remainingConstant != 1)
    {
        innerMultipliers.emplace_back(Term(remainingConstant), TermAssociationType::Positive);
    }
}

void putRemainingNonConstantFactorsAsInnerMultipliers(
        TermsWithDetails & innerMultipliers,
        TermsRaiseToNumbers const& nonConstantFactorsOfOriginalAddend,
        TermsRaiseToNumbers const& commonNonConstantFactors)
{
    TermsRaiseToNumbers remainingNonConstantFactors(nonConstantFactorsOfOriginalAddend);
    remainingNonConstantFactors.subtractExponents(commonNonConstantFactors);
    remainingNonConstantFactors.simplify();
    TermsWithDetails remainingNonConstantFactorsWithDetails(remainingNonConstantFactors.getTermWithDetailsInMultiplicationAndDivisionOperation());
    innerMultipliers.reserve(innerMultipliers.size() + remainingNonConstantFactorsWithDetails.size());
    copy(remainingNonConstantFactorsWithDetails.cbegin(), remainingNonConstantFactorsWithDetails.cend(), back_inserter(innerMultipliers));
}

void putRemainingInnerMultipliersAsOuterAddend(
        TermsWithDetails & outerAddends,
        TermsWithDetails const& innerMultipliers,
        TermWithDetails const& originalAddend)
{
    Term combinedInnerTerm(createTermWithMultiplicationAndDivisionTermsWithDetails(innerMultipliers));
    outerAddends.emplace_back(combinedInnerTerm, originalAddend.association);
}

TermsRaiseToNumbers getFactorizedItemsBasedFromCollectedData(
        AlbaNumber const& constantGcf,
        TermsRaiseToNumbers const& commonNonConstantFactors,
        TermsWithDetails const& outerAddends)
{
    TermsRaiseToNumbers result;
    result = commonNonConstantFactors;
    if(constantGcf != 1)
    {
        result.putTerm(Term(constantGcf), TermAssociationType::Positive);
    }
    if(!outerAddends.empty())
    {
        Term nonFactoredTerm(createTermWithAdditionAndSubtractionTermsWithDetails(outerAddends));
        nonFactoredTerm.simplify();
        result.putTerm(nonFactoredTerm, TermAssociationType::Positive);
    }
    return result;
}

bool dontFactorizeBaseBecauseBaseIsARaiseToPowerExpression(
        Term const& base)
{
    bool result(false);
    if(base.isExpression())
    {
        result = OperatorLevel::RaiseToPower == base.getExpressionConstReference().getCommonOperatorLevel();
    }
    return result;
}

bool dontFactorizeBecauseThereIsSquareRootOfNegativeNumber(
        Term const& base,
        AlbaNumber const& exponent)
{
    bool hasEvenDenominatorExponents(false);
    if(exponent.isFractionType())
    {
        hasEvenDenominatorExponents = isEven(exponent.getFractionData().denominator);
    }
    return hasEvenDenominatorExponents && isANegativeTerm(base);
}

}

}

}
