#include "FactorizationOfExpression.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Factorization/FactorizationOfTerm.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>

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
    retrieveConstantAndNonConstantFactors(nonConstantFactorsPerAddends, constantFactorsPerAddends, expression);

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

    OperatorLevel operatorLevelOfBase(OperatorLevel::Unknown);
    bool hasEvenDenominatorExponents(false);

    if(base.isExpression())
    {
        operatorLevelOfBase = base.getExpressionConstReference().getCommonOperatorLevel();
    }
    if(exponent.isFractionType())
    {
        hasEvenDenominatorExponents = isEven(exponent.getFractionData().denominator);
    }

    if(OperatorLevel::RaiseToPower == operatorLevelOfBase
            || (isANegativeTerm(base) && hasEvenDenominatorExponents))
    {
        result.setBaseAndExponent(base, mainBaseToExponent.getExponent());
    }
    else
    {
        Terms factorizedBases(factorizeTerm(base));
        result.putTerms(factorizedBases, TermAssociationType::Positive);
        result.multiplyNumberToExponents(mainBaseToExponent.getExponent());
    }
    return result;
}

void retrieveConstantAndNonConstantFactors(
        vector<TermsRaiseToNumbers> & nonConstantFactorsPerAddends,
        AlbaNumbers & constantFactors,
        Expression const& expression)
{
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
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
    bool isFirst(true);
    for(AlbaNumber const& constantFactor : constantFactorsPerAddends)
    {
        if(isFirst)
        {
            constantGcf = constantFactor;
            isFirst=false;
        }
        else
        {
            constantGcf = getGreatestCommonFactorForAlbaNumber(constantGcf, constantFactor);
        }
    }
    return constantGcf;
}

void retrieveCommonNonConstantFactors(
        TermsRaiseToNumbers & commonNonConstantFactors,
        vector<TermsRaiseToNumbers> const& nonConstantFactorsPerAddends)
{
    bool isFirst(true);
    for(TermsRaiseToNumbers const& factorsAtAddend : nonConstantFactorsPerAddends)
    {
        if(isFirst)
        {
            commonNonConstantFactors = factorsAtAddend;
            isFirst = false;
        }
        else
        {
            for(auto const& commonFactorBaseExponentPair : commonNonConstantFactors.getBaseToExponentMap())
            {
                Term const& base(commonFactorBaseExponentPair.first);
                AlbaNumber const& exponentAtCommonFactor(commonFactorBaseExponentPair.second);
                AlbaNumber exponentAtAddend(factorsAtAddend.getExponentOfBase(base));
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

}

}

}
