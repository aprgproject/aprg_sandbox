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

void AdditionAndSubtractionOfTermsOverTerms::putAsAddition(TermsOverTerms const& addend)
{
    putItem(getSimplifiedTermsOverTerms(addend), TermAssociationType::Positive);
}

void AdditionAndSubtractionOfTermsOverTerms::putAsSubtraction(TermsOverTerms const& subtrahend)
{
    putItem(getSimplifiedTermsOverTerms(subtrahend), TermAssociationType::Negative);
}

void AdditionAndSubtractionOfTermsOverTerms::putAsAddOrSubtraction(
        TermsOverTerms const& item,
        TermAssociationType const association)
{
    putItem(getSimplifiedTermsOverTerms(item), association);
}

VectorOfTermsOverTerms const& AdditionAndSubtractionOfTermsOverTerms::getItems() const
{
    return m_items;
}

TermAssociationTypes const& AdditionAndSubtractionOfTermsOverTerms::getAssociations() const
{
    return m_associations;
}

Expression AdditionAndSubtractionOfTermsOverTerms::getCombinedExpression() const
{
    Terms lcmDenominatorTerms(getLcmOfDenominatorTerms());
    Expression combinedNumerator = getCombinedNumeratorExpression(lcmDenominatorTerms);
    Expression combinedDenominator = getCombinedDenominatorExpression(lcmDenominatorTerms);
    Expression combinedExpression;
    combinedExpression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(combinedNumerator)));
    combinedExpression.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(combinedDenominator)));
    return combinedExpression;
}

Terms AdditionAndSubtractionOfTermsOverTerms::getRevisedNumeratorTermsBasedOnLcmOnIndex(
        unsigned int itemIndex,
        Terms const& lcmOfDenominatorTerms) const
{
    Terms numeratorTerms;
    if(itemIndex < m_items.size())
    {
        Terms multipliers(lcmOfDenominatorTerms);
        Terms monomialMultiplierTerms;
        Terms nonMonomialMultiplierTerms;
        segregateMonomialsAndNonMonomials(multipliers, monomialMultiplierTerms, nonMonomialMultiplierTerms);
        Monomial monomialMultiplier(getCombinedMonomialMultiplier(monomialMultiplierTerms));
        updateMonomialAndNonMonomialMultipliersBasedOnDenominatorOnIndex(itemIndex, monomialMultiplier, nonMonomialMultiplierTerms);
        emplaceExistingNumeratorTerms(numeratorTerms, itemIndex);
        emplaceMonomialMultiplierIfNeeded(numeratorTerms, monomialMultiplier);
        emplaceNonMonomialMultipliers(numeratorTerms, nonMonomialMultiplierTerms);
    }
    return numeratorTerms;
}

Terms AdditionAndSubtractionOfTermsOverTerms::getLcmOfDenominatorTerms() const
{
    Terms lcmTerms;
    Monomials lcmMonomials;
    for(TermsOverTerms const& item : m_items)
    {
        Terms currentCommonFactors = lcmTerms;
        for(Term const& denominatorTerm : item.getDenominators())
        {
            if(!(denominatorTerm.isTheValueOne() || denominatorTerm.isEmpty()))
            {
                if(canBeConvertedToMonomial(denominatorTerm))
                {
                    lcmMonomials.emplace_back(createMonomialIfPossible(denominatorTerm));
                }
                else
                {
                    eraseCommonFactorOrAddDistinctFactor(denominatorTerm, currentCommonFactors, lcmTerms);
                }
            }
        }
    }
    Monomial lcmMonomial(getLcmMonomialInMonomials(lcmMonomials));
    if(!lcmMonomial.isOne())
    {
        lcmTerms.emplace(lcmTerms.begin(), lcmMonomial);
    }
    if(lcmTerms.empty())
    {
        lcmTerms.emplace_back(Term(1));
    }
    return lcmTerms;
}

void AdditionAndSubtractionOfTermsOverTerms::eraseCommonFactorOrAddDistinctFactor(
        Term const& termToCheck,
        Terms & commonFactors,
        Terms & outputFactors) const
{
    Terms::iterator matchedTermIterator = find(commonFactors.begin(), commonFactors.end(), termToCheck);
    if(matchedTermIterator == commonFactors.end())
    {
        outputFactors.emplace_back(termToCheck);
    }
    else
    {
        commonFactors.erase(matchedTermIterator);
    }
}

Monomial AdditionAndSubtractionOfTermsOverTerms::getCombinedMonomialMultiplier(Terms const& monomialMultiplierTerms) const
{
    Monomials monomialMultipliers;
    for(Term const& monomialMultiplierTerm : monomialMultiplierTerms)
    {
        monomialMultipliers.emplace_back(createMonomialIfPossible(monomialMultiplierTerm));
    }
    Monomial monomialMultiplier(getLcmMonomialInMonomials(monomialMultipliers));

    return monomialMultiplier;
}

void AdditionAndSubtractionOfTermsOverTerms::updateMonomialAndNonMonomialMultipliersBasedOnDenominatorOnIndex(
        unsigned int itemIndex,
        Monomial & monomialMultiplier,
        Terms & nonMonomialMultiplierTerms) const
{
    for(Term const& denominatorTerm : m_items.at(itemIndex).getDenominators())
    {
        if(canBeConvertedToMonomial(denominatorTerm))
        {
            monomialMultiplier.divideMonomial(createMonomialIfPossible(denominatorTerm));
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
}

void AdditionAndSubtractionOfTermsOverTerms::emplaceExistingNumeratorTerms(
        Terms & numeratorTerms,
        unsigned int itemIndex) const
{
    for(Term const& numeratorTerm : m_items.at(itemIndex).getNumerators())
    {
        numeratorTerms.emplace_back(numeratorTerm);
    }
}

void AdditionAndSubtractionOfTermsOverTerms::emplaceMonomialMultiplierIfNeeded(
        Terms & numeratorTerms,
        Monomial const& monomialMultiplier) const
{
    if(!monomialMultiplier.isOne())
    {
        numeratorTerms.emplace_back(Term(monomialMultiplier));
    }
}

void AdditionAndSubtractionOfTermsOverTerms::emplaceNonMonomialMultipliers(
        Terms & numeratorTerms,
        Terms const& nonMonomialMultiplierTerms) const
{
    for(Term const& numeratorTerm : nonMonomialMultiplierTerms)
    {
        numeratorTerms.emplace_back(numeratorTerm);
    }
}

Expression AdditionAndSubtractionOfTermsOverTerms::getCombinedNumeratorExpression(Terms const& lcmDenominatorTerms) const
{
    Expression combinedNumerator;
    unsigned int numberOfItems = m_items.size();
    for(unsigned int numeratorIndex=0; numeratorIndex<numberOfItems; numeratorIndex++)
    {
        Expression combinedNumeratorOnIndex(getCombinedExpressionForNumeratorOnIndex(numeratorIndex, lcmDenominatorTerms));
        combineExpressionAsAddOrSubtract(combinedNumerator, combinedNumeratorOnIndex, m_associations.at(numeratorIndex));
    }
    return combinedNumerator;
}

Expression AdditionAndSubtractionOfTermsOverTerms::getCombinedDenominatorExpression(Terms const& lcmDenominatorTerms) const
{
    Expression combinedDenominator;
    for(Term const& denominatorTerm : lcmDenominatorTerms)
    {
        combinedDenominator.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(denominatorTerm));
    }
    return combinedDenominator;
}

Expression AdditionAndSubtractionOfTermsOverTerms::getCombinedExpressionForNumeratorOnIndex(
        unsigned int numeratorIndex,
        Terms const& lcmDenominatorTerms) const
{
    Expression combinedNumeratorOnIndex;
    Terms numeratorTermsOnIndex(getRevisedNumeratorTermsBasedOnLcmOnIndex(numeratorIndex, lcmDenominatorTerms));
    for(Term const& numeratorTermOnIndex : numeratorTermsOnIndex)
    {
        combinedNumeratorOnIndex.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(numeratorTermOnIndex));
    }
    return combinedNumeratorOnIndex;
}

void AdditionAndSubtractionOfTermsOverTerms::combineExpressionAsAddOrSubtract(
        Expression & combinedExpression,
        Expression const& expression,
        TermAssociationType const association) const
{
    if(TermAssociationType::Positive == association)
    {
        combinedExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(expression));
    }
    else
    {
        combinedExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(expression));
    }
}

TermsOverTerms AdditionAndSubtractionOfTermsOverTerms::getSimplifiedTermsOverTerms(TermsOverTerms const& termsOverTerms)
{
    TermsOverTerms termsOverTermsSimplified(termsOverTerms);
    termsOverTermsSimplified.simplifyToFactors();
    return termsOverTermsSimplified;
}

void AdditionAndSubtractionOfTermsOverTerms::putItem(TermsOverTerms const& item, TermAssociationType const association)
{
    m_items.emplace_back(item);
    m_associations.emplace_back(association);
}

}
}
