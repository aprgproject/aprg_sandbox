#include "SimplificationUtilities.hpp"

#include <BooleanAlgebra/Operations/AccumulateOperations.hpp>
#include <BooleanAlgebra/Simplification/SimplificationOfExpression.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/TermUtilities.hpp>

#include <algorithm>



#include <Common/Debug/AlbaDebug.hpp>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

namespace Simplification
{

void simplifyTermByPriorityAndOperationThenOrOperation(Term & term)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyByDistributingAndOperandsToOrOperands = true;

    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    term.clearAllInnerSimplifiedFlags();
    term.simplify();
}

void simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
        WrappedTerms & newWrappedTerms,
        OperatorLevel & mainOperatorLevel,
        WrappedTerms const& oldWrappedTerms)
{
    for(WrappedTerm const& oldWrappedTerm : oldWrappedTerms)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(oldWrappedTerm.baseTermSharedPointer));
        if(term.isExpression())
        {
            Expression subExpression(term.getExpressionConstReference());
            subExpression.simplify();
            simplifyAndCopyTermsFromAnExpressionAndChangeOperatorLevelIfNeeded(
                        newWrappedTerms, mainOperatorLevel, subExpression);
        }
        else if(isNonEmptyOrNonOperatorType(term))
        {
            Term newTerm(term);
            newTerm.simplify();
            newWrappedTerms.emplace_back(newTerm);
        }
    }
}

void simplifyAndCopyTermsFromAnExpressionAndChangeOperatorLevelIfNeeded(
        WrappedTerms & newWrappedTerms,
        OperatorLevel & mainOperatorLevel,
        Expression const& subExpression)
{
    OperatorLevel subExpressionOperatorLevel(subExpression.getCommonOperatorLevel());
    if(subExpression.containsOnlyOneTerm()
            || OperatorLevel::Unknown == mainOperatorLevel
            || subExpressionOperatorLevel == mainOperatorLevel)
    {
        if(OperatorLevel::Unknown == mainOperatorLevel)
        {
            mainOperatorLevel = subExpressionOperatorLevel;
        }
        simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(newWrappedTerms, mainOperatorLevel, subExpression.getWrappedTerms());
    }
    else
    {
        newWrappedTerms.emplace_back(Term(subExpression));
    }
}

Terms createUniqueTerms(
        WrappedTerms const& terms)
{
    Terms result;
    result.reserve(terms.size());
    transform(terms.cbegin(), terms.cend(), back_inserter(result), [](WrappedTerm const& wrappedTerm)
    {
        return getTermConstReferenceFromSharedPointer(wrappedTerm.baseTermSharedPointer);
    });
    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()), result.end());
    return result;
}

void combineComplementaryTerms(
        Terms & termsToCombine,
        OperatorLevel const operatorLevel)
{
    // Convert complimentary terms
    // x & x’ = 0
    // x | x’ = 1
    Terms negatedTerms(termsToCombine);
    for(Term & negatedTerm : negatedTerms)
    {
        negatedTerm.negate();
    }
    for(unsigned int i=0; i<termsToCombine.size(); i++)
    {
        bool hasComplimentary(false);
        for(unsigned int j=i+1; j<termsToCombine.size(); j++)
        {
            if(termsToCombine.at(i) == negatedTerms.at(j))
            {
                termsToCombine.erase(termsToCombine.begin()+j);
                negatedTerms.erase(negatedTerms.begin()+j);
                hasComplimentary = true;
            }
        }
        if(hasComplimentary)
        {
            termsToCombine[i] = Term(getShortCircuitValueEffectInOperation(operatorLevel));
        }
    }
}

void combineTermsByCheckingTheCommonFactor(
        Terms & termsToCombine,
        OperatorLevel const operatorLevel)
{
    for(unsigned int i=0; i<termsToCombine.size(); i++)
    {
        for(unsigned int j=i+1; j<termsToCombine.size(); j++)
        {
            Term newTerm;
            combineUniqueTermsAndCommonFactorIfPossible(newTerm, termsToCombine.at(i), termsToCombine.at(j), operatorLevel);
            if(!newTerm.isEmpty())
            {
                termsToCombine[i] = newTerm;
                termsToCombine.erase(termsToCombine.begin()+j);
                i--;
                break;
            }
        }
    }
}

void combineUniqueTermsAndCommonFactorIfPossible(
        Term & outputTerm,
        Term const& term1,
        Term const& term2,
        OperatorLevel const operatorLevel)
{
    bool isOneOfTheTermANonExpression = !term1.isExpression() || !term2.isExpression();
    bool doesOperatorLevelMatchIfBothExpressions = term1.isExpression()
            && term2.isExpression()
            && term1.getExpressionConstReference().getCommonOperatorLevel() == term2.getExpressionConstReference().getCommonOperatorLevel();
    if(isOneOfTheTermANonExpression || doesOperatorLevelMatchIfBothExpressions)
    {
        Terms commonFactors;
        Terms uniqueTerms1(getTermOrSubTerms(term1));
        Terms uniqueTerms2(getTermOrSubTerms(term2));
        for(unsigned int i1=0; i1<uniqueTerms1.size(); i1++)
        {
            for(unsigned int i2=0; i2<uniqueTerms2.size(); i2++)
            {
                if(uniqueTerms1.at(i1) == uniqueTerms2.at(i2))
                {
                    commonFactors.emplace_back(uniqueTerms1.at(i1));
                    uniqueTerms1.erase(uniqueTerms1.begin()+i1);
                    uniqueTerms2.erase(uniqueTerms2.begin()+i2);
                    i1--;
                    break;
                }
            }
        }
        if(!commonFactors.empty())
        {
            OperatorLevel subOperatorLevel(getSubOperatorLevel(term1, term2));
            Term uniqueTerm1(getNoEffectValueInOperation(subOperatorLevel));
            Term uniqueTerm2(getNoEffectValueInOperation(subOperatorLevel));
            accumulateTerms(uniqueTerm1, uniqueTerms1, subOperatorLevel);
            accumulateTerms(uniqueTerm2, uniqueTerms2, subOperatorLevel);
            Term combinedUniqueTerm;
            accumulateTerms(combinedUniqueTerm, {uniqueTerm1, uniqueTerm2}, operatorLevel);
            combinedUniqueTerm.simplify();
            if(!combinedUniqueTerm.isExpression())
            {
                accumulateTerms(outputTerm, commonFactors, subOperatorLevel);
                accumulateTerms(outputTerm, {combinedUniqueTerm}, subOperatorLevel);
            }
        }
    }
}

Terms getTermOrSubTerms(Term const& term)
{
    Terms terms;
    if(term.isExpression())
    {
        for(WrappedTerm const& subTerm : term.getExpressionConstReference().getWrappedTerms())
        {
            terms.emplace_back(getTermConstReferenceFromSharedPointer(subTerm.baseTermSharedPointer));
        }
    }
    else
    {
        terms.emplace_back(term);
    }
    return terms;
}

OperatorLevel getSubOperatorLevel(
        Term const& term1,
        Term const& term2)
{
    OperatorLevel result(OperatorLevel::Unknown);
    if(term1.isExpression())
    {
        result = term1.getExpressionConstReference().getCommonOperatorLevel();
    }
    else if(term2.isExpression())
    {
        result = term2.getExpressionConstReference().getCommonOperatorLevel();
    }
    return result;
}

void distributeTermsIfNeeded(
        Term & outputTerm,
        Terms const& inputTerms,
        OperatorLevel const outerOperation,
        OperatorLevel const innerOperation)
{
    if(!inputTerms.empty())
    {
        bool didLevelMatch =
                (OperatorLevel::And == outerOperation
                 && OperatorLevel::Or == innerOperation
                 && SimplificationOfExpression::shouldSimplifyByDistributingAndOperandsToOrOperands())
                || (OperatorLevel::Or == outerOperation
                    && OperatorLevel::And == innerOperation
                    && SimplificationOfExpression::shouldSimplifyByDistributingOrOperandsToAndOperands());
        if(didLevelMatch)
        {
            Terms outerFactors;
            Expressions innerExpressions;
            for(Term const& inputTerm : inputTerms)
            {
                if(inputTerm.isExpression())
                {
                    Expression const& subExpression(inputTerm.getExpressionConstReference());
                    if(innerOperation == subExpression.getCommonOperatorLevel())
                    {
                        innerExpressions.emplace_back(subExpression);
                    }
                    else if(outerOperation == subExpression.getCommonOperatorLevel())
                    {
                        for(WrappedTerm const& subExpressionTerm : subExpression.getWrappedTerms())
                        {
                            outerFactors.emplace_back(getTermConstReferenceFromSharedPointer(subExpressionTerm.baseTermSharedPointer));
                        }
                    }
                }
                else
                {
                    outerFactors.emplace_back(inputTerm);
                }
            }
            if(!innerExpressions.empty())
            {
                Term outerFactor;
                accumulateTerms(outerFactor, outerFactors, outerOperation);
                Terms innerTermsCombinations;
                distributeTermsWithRecursion(outputTerm, innerTermsCombinations, innerExpressions, outerFactor, outerOperation, innerOperation, 0U);
            }
        }
    }
}

void distributeTermsWithRecursion(
        Term & outputTerm,
        Terms & innerTermsCombinations,
        Expressions const& innerExpressions,
        Term const& outerFactor,
        OperatorLevel const outerOperation,
        OperatorLevel const innerOperation,
        unsigned int const index)
{
    if(index < innerExpressions.size())
    {
        for(WrappedTerm const& subExpressionTerm : innerExpressions.at(index).getWrappedTerms())
        {
            innerTermsCombinations.emplace_back(getTermConstReferenceFromSharedPointer(subExpressionTerm.baseTermSharedPointer));
            distributeTermsWithRecursion(outputTerm, innerTermsCombinations, innerExpressions, outerFactor, outerOperation, innerOperation, index+1);
            innerTermsCombinations.pop_back();
        }
    }
    else
    {
        Term partialTerm(outerFactor);
        accumulateTerms(partialTerm, innerTermsCombinations, outerOperation);
        accumulateTerms(outputTerm, {partialTerm}, innerOperation);
    }
}

}

}

}
