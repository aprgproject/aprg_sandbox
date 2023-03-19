#include "AdditionAndSubtractionOfExpressions.hpp"

#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/EnumHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

namespace
{

ConditionFunctionForTermsWithDetails isCommonPart
= [](TermWithDetails const& termWithDetails) -> bool
{
    Term const& term(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));
    return termWithDetails.hasNegativeAssociation() || term.isExpression()  || term.isFunction();
};

ConditionFunctionForTermsWithDetails isMergePart
= [](TermWithDetails const& termWithDetails) -> bool
{
    return !isCommonPart(termWithDetails);
};

}

AdditionAndSubtractionOfExpressions::AdditionAndSubtractionOfExpressions()
{}

AdditionAndSubtractionOfExpressions::AdditionAndSubtractionOfExpressions(
        TermsWithDetails const& termsWithDetails)
{
    putTermsWithDetails(termsWithDetails);
}

Expressions const& AdditionAndSubtractionOfExpressions::getExpressions() const
{
    return m_expressions;
}

TermAssociationTypes const& AdditionAndSubtractionOfExpressions::getAssociations() const
{
    return m_associations;
}

unsigned int AdditionAndSubtractionOfExpressions::getSize() const
{
    return min(m_expressions.size(), m_associations.size());
}

TermsWithDetails AdditionAndSubtractionOfExpressions::getAsTermsWithDetails() const
{
    TermsWithDetails result;
    unsigned int size = getSize();
    for(unsigned int index=0; index<size; index++)
    {
        result.emplace_back(convertExpressionToSimplestTerm(m_expressions.at(index)), m_associations.at(index));
    }
    return result;
}

Term AdditionAndSubtractionOfExpressions::getCombinedTerm()
{
    Term combinedTerm;
    combineExpressionsIfPossible();
    accumulateTermsForAdditionAndSubtraction(combinedTerm, getAsTermsWithDetails());
    return combinedTerm;
}

void AdditionAndSubtractionOfExpressions::putAsAddition(Expression const& expression)
{
    putItem(expression, TermAssociationType::Positive);
}

void AdditionAndSubtractionOfExpressions::putAsSubtraction(Expression const& expression)
{
    putItem(expression, TermAssociationType::Negative);
}

void AdditionAndSubtractionOfExpressions::putAsAddOrSubtraction(
        Expression const& expression,
        TermAssociationType const association)
{
    putItem(expression, association);
}

void AdditionAndSubtractionOfExpressions::putTermsWithDetails(TermsWithDetails const& termsWithDetails)
{
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        putAsAddOrSubtraction(
                    createOrCopyExpressionFromATerm(
                        getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer)),
                    termWithDetails.association);
    }
}

void AdditionAndSubtractionOfExpressions::combineExpressionsIfPossible()
{
    Terms mergeParts;
    Terms commonParts;
    retrieveMergeParts(mergeParts);
    retrieveCommonParts(commonParts);
    if(doAllSizesMatch(mergeParts, commonParts))
    {
        prepareCommonParts(commonParts);
        mergeExpressionsByCheckingTwoTermsAtATime(mergeParts, commonParts);
    }
}

void AdditionAndSubtractionOfExpressions::mergeExpressionsByCheckingTwoTermsAtATime(
        Terms & mergeParts,
        Terms & commonParts)
{
    unsigned int size = mergeParts.size();
    for(unsigned int i=0; i<size; i++)
    {
        for(unsigned int j=i+1; j<size; j++)
        {
            //quadratic time: think on how this can be better
            if(canBeMerged(mergeParts.at(i), mergeParts.at(j), commonParts.at(i), commonParts.at(j)))
            {
                Term mergedTerm(mergeTerms(mergeParts.at(i), mergeParts.at(j), m_associations.at(i), m_associations.at(j)));
                Term const& commonPart(commonParts.at(i));
                mergeParts[i] = mergedTerm;
                m_expressions[i] = createOrCopyExpressionFromATerm(mergedTerm*commonPart);
                m_associations[i] = TermAssociationType::Positive;

                mergeParts.erase(mergeParts.begin()+j);
                commonParts.erase(commonParts.begin()+j);
                m_expressions.erase(m_expressions.begin()+j);
                m_associations.erase(m_associations.begin()+j);

                size = mergeParts.size();
                j=i;
            }
        }
    }
}

Term AdditionAndSubtractionOfExpressions::mergeTerms(
        Term const& mergePart1,
        Term const& mergePart2,
        TermAssociationType const association1,
        TermAssociationType const association2)
{
    Term result;
    TermsWithDetails termsWithDetailsToMerge;
    termsWithDetailsToMerge.emplace_back(mergePart1, association1);
    termsWithDetailsToMerge.emplace_back(mergePart2, association2);
    accumulateTermsForAdditionAndSubtraction(result, termsWithDetailsToMerge);
    return result;
}

void AdditionAndSubtractionOfExpressions::prepareCommonParts(
        Terms & commonParts)
{
    for(Term & commonPart : commonParts)
    {
        commonPart.simplify();
        if(commonPart.isExpression())
        {
            commonPart.getExpressionReference().sort();
        }
    }
}

void AdditionAndSubtractionOfExpressions::retrieveMergeParts(
        Terms & mergeParts)
{
    for(Expression const& expression : m_expressions)
    {
        mergeParts.emplace_back();
        retrieveMergePart(mergeParts.back(), expression);
    }
}

void AdditionAndSubtractionOfExpressions::retrieveCommonParts(
        Terms & commonParts)
{
    for(Expression const& expression : m_expressions)
    {
        commonParts.emplace_back();
        retrieveCommonPart(commonParts.back(), expression);
    }
}

void AdditionAndSubtractionOfExpressions::retrieveMergePart(
        Term & mergePart,
        Expression const& expression)
{
    if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        mergePart = 1;
        TermsWithDetails termsToBeMerged
                = retrieveTermsWithDetailsThatSatisfiesCondition(
                    expression.getTermsWithAssociation().getTermsWithDetails(),
                    isMergePart);

        accumulateTermsForMultiplicationAndDivision(mergePart, termsToBeMerged);
    }
    else
    {
        mergePart = 1;
    }
}

void AdditionAndSubtractionOfExpressions::retrieveCommonPart(
        Term & commonPart,
        Expression const& expression)
{
    if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        commonPart = 1;
        TermsWithDetails termsToBeMerged
                = retrieveTermsWithDetailsThatSatisfiesCondition(
                    expression.getTermsWithAssociation().getTermsWithDetails(),
                    isCommonPart);

        accumulateTermsForMultiplicationAndDivision(commonPart, termsToBeMerged);
    }
    else
    {
        commonPart = convertExpressionToSimplestTerm(expression);
    }
}

bool AdditionAndSubtractionOfExpressions::doAllSizesMatch(
        Terms const& mergeParts,
        Terms const& commonParts) const
{
    return mergeParts.size() == commonParts.size()
                && mergeParts.size() == m_expressions.size()
                && mergeParts.size() == m_associations.size();
}

bool AdditionAndSubtractionOfExpressions::canBeMerged(
        Term const& mergePart1,
        Term const& mergePart2,
        Term const& commonPart1,
        Term const& commonPart2)
{
    return commonPart1 == commonPart2 && canBeMergedInAMonomialByAdditionOrSubtraction(mergePart1, mergePart2);
}

void AdditionAndSubtractionOfExpressions::putItem(Expression const& expression, TermAssociationType const association)
{
    Expression correctedExpression(expression);
    TermAssociationType correctedAssociation(association);
    if(isANegativeExpression(expression))
    {
        correctedExpression = negateExpression(expression);
        correctedAssociation = getReversedAssociationType(association);
    }
    correctedExpression.simplify();
    m_expressions.emplace_back(correctedExpression);
    m_associations.emplace_back(correctedAssociation);
}

}

}
