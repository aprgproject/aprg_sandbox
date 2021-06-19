#include "AdditionAndSubtractionOfTermsOverTerms.hpp"

#include <Equation/Term/TermOperators.hpp>
#include <Equation/Utilities.hpp>

#include <algorithm>
namespace alba
{
namespace equation
{

AdditionAndSubtractionOfTermsOverTerms::AdditionAndSubtractionOfTermsOverTerms()
{}

void AdditionAndSubtractionOfTermsOverTerms::putAsAddOrSubtraction(
        TermsOverTerms const& item,
        TermAssociationType const associationType)
{
    if(TermAssociationType::Positive == associationType)
    {
        putAsAddition(item);
    }
    else
    {
        putAsSubtraction(item);
    }
}

void AdditionAndSubtractionOfTermsOverTerms::putAsAddition(TermsOverTerms const& addend)
{
    TermsOverTerms addendSimplified(addend);
    addendSimplified.simplifyToFactors();
    m_items.emplace_back(addendSimplified);
    m_associations.emplace_back(TermAssociationType::Positive);
}

void AdditionAndSubtractionOfTermsOverTerms::putAsSubtraction(TermsOverTerms const& subtrahend)
{
    TermsOverTerms subtrahendSimplified(subtrahend);
    subtrahendSimplified.simplifyToFactors();
    m_items.emplace_back(subtrahendSimplified);
    m_associations.emplace_back(TermAssociationType::Negative);
}

Expression AdditionAndSubtractionOfTermsOverTerms::getCombinedExpression() const
{
    Terms lcmDenominatorTerms(getLcmOfDenominatorTerms());
    unsigned int numberOfItems = m_items.size();
    Expression combinedNumerator;
    for(unsigned int numeratorIndex=0; numeratorIndex<numberOfItems; numeratorIndex++)
    {
        Expression combinedNumeratorOnIndex;
        Terms numeratorTermsOnIndex(getNewNumeratorTermsOnLcm(numeratorIndex, lcmDenominatorTerms));
        for(Term const& numeratorTermOnIndex : numeratorTermsOnIndex)
        {
            combinedNumeratorOnIndex.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(numeratorTermOnIndex));
        }
        if(m_associations.at(numeratorIndex) == TermAssociationType::Positive)
        {
            combinedNumerator.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(combinedNumeratorOnIndex));
        }
        else
        {
            combinedNumerator.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(combinedNumeratorOnIndex));
        }
    }
    Expression combinedDenominator;
    for(Term const& denominatorTerm : lcmDenominatorTerms)
    {
        combinedDenominator.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(denominatorTerm));
    }
    Expression combinedTerm;
    combinedTerm.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(combinedNumerator)));
    combinedTerm.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(combinedDenominator)));
    return combinedTerm;
}

Terms AdditionAndSubtractionOfTermsOverTerms::getNewNumeratorTermsOnLcm(
        unsigned int numeratorIndex,
        Terms const& lcmOfDenominatorTerms) const
{
    Terms numeratorTerms;
    if(numeratorIndex < m_items.size())
    {
        Terms multipliers(lcmOfDenominatorTerms);
        Terms monomialMultiplierTerms;
        Terms nonMonomialMultiplierTerms;
        segregateMonomialsAndNonMonomials(monomialMultiplierTerms, nonMonomialMultiplierTerms, multipliers);
        Monomials monomialMultipliers;
        for(Term const& monomialMultiplierTerm : monomialMultiplierTerms)
        {
            monomialMultipliers.emplace_back(createMonomialIfPossible(monomialMultiplierTerm));
        }
        Monomial monomialMultiplier(getLcmMonomialInMonomials(monomialMultipliers));
        for(Term const& denominatorTerm : m_items.at(numeratorIndex).getDenominators())
        {
            if(canBeConvertedToMonomial(denominatorTerm))
            {
                monomialMultiplier = getGcfMonomialInMonomials({monomialMultiplier, createMonomialIfPossible(denominatorTerm)});
            }
            else
            {
                Terms::iterator multiplierIterator = find(nonMonomialMultiplierTerms.begin(), nonMonomialMultiplierTerms.end(), denominatorTerm);
                if(multiplierIterator != nonMonomialMultiplierTerms.end())
                {
                    nonMonomialMultiplierTerms.erase(multiplierIterator);
                }
            }
        }
        for(Term const& numeratorTerm : m_items.at(numeratorIndex).getNumerators())
        {
            numeratorTerms.emplace_back(numeratorTerm);
        }
        if(!monomialMultiplier.isOne())
        {
            numeratorTerms.emplace_back(Term(monomialMultiplier));
        }
        for(Term const& numeratorTerm : nonMonomialMultiplierTerms)
        {
            numeratorTerms.emplace_back(numeratorTerm);
        }
    }
    return numeratorTerms;
}

Terms AdditionAndSubtractionOfTermsOverTerms::getLcmOfDenominatorTerms() const
{
    Terms denominators;
    Monomials denominatorMonomials;
    for(TermsOverTerms const& item : m_items)
    {
        Terms denominatorsToCheck = denominators;
        for(Term const& denominatorTerm : item.getDenominators())
        {
            if(!denominatorTerm.isTheValueOne())
            {
                if(canBeConvertedToMonomial(denominatorTerm))
                {
                    denominatorMonomials.emplace_back(createMonomialIfPossible(denominatorTerm));
                }
                else
                {
                    Terms::iterator matchedTermIterator = find(denominatorsToCheck.begin(), denominatorsToCheck.end(), denominatorTerm);
                    if(matchedTermIterator == denominatorsToCheck.end())
                    {
                        denominators.emplace_back(denominatorTerm);
                    }
                    else
                    {
                        denominatorsToCheck.erase(matchedTermIterator);
                    }
                }
            }
        }
    }
    Monomial lcmMonomial(getLcmMonomialInMonomials(denominatorMonomials));
    if(!lcmMonomial.isOne())
    {
        denominators.emplace(denominators.begin(), lcmMonomial);
    }
    return denominators;
}

}

}
