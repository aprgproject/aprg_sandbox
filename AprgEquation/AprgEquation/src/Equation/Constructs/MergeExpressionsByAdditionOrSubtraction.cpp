#include "MergeExpressionsByAdditionOrSubtraction.hpp"

#include <AccumulateOperations.hpp>
#include <TermOperators.hpp>
#include <Utilities.hpp>

using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

Term getResultOfAddingAndSubtractingOfTermsWithExpressions(
        TermsWithDetails const& termsWithExpressions)
{
    Term combinedTerm;
    TermsWithDetails newTermsWithExpressions(termsWithExpressions);
    for(TermsWithDetails::iterator first = newTermsWithExpressions.begin();
        first != newTermsWithExpressions.end();
        first++)
    {
        TermsWithDetails::iterator second=first;
        second++;
        for(;second != newTermsWithExpressions.end();  second++)
        {
            if(mergeForAdditionAndSubtractionAndReturnIfMerged(*first, *second))
            {
                newTermsWithExpressions.erase(second);
                second=first;
            }
        }
    }
    accumulateTermsForAdditionAndSubtraction(combinedTerm, newTermsWithExpressions);
    return combinedTerm;
}

bool mergeForAdditionAndSubtractionAndReturnIfMerged(
        TermWithDetails & termExpressionWithDetails1,
        TermWithDetails & termExpressionWithDetails2)
{
    bool isMerged(false);
    Expression uniqueExpression1, uniqueExpression2;
    Term mergeTerm1, mergeTerm2;
    retrieveUniqueExpressionsAndMergeTerms(uniqueExpression1, uniqueExpression2, mergeTerm1, mergeTerm2, termExpressionWithDetails1, termExpressionWithDetails2);
    if(canBeMergedForAdditionAndSubtraction(uniqueExpression1, uniqueExpression2, mergeTerm1, mergeTerm2))
    {
        Term resultMergeTerm;
        TermsWithDetails termsToMerge;
        termsToMerge.emplace_back(getBaseTermConstReferenceFromTerm(mergeTerm1), termExpressionWithDetails1.association);
        termsToMerge.emplace_back(getBaseTermConstReferenceFromTerm(mergeTerm2), termExpressionWithDetails2.association);
        accumulateTermsForAdditionAndSubtraction(resultMergeTerm, termsToMerge);
        termExpressionWithDetails1 = TermWithDetails(
                    getBaseTermConstReferenceFromTerm(resultMergeTerm*Term(uniqueExpression1)),
                    TermAssociationType::Positive);
        termExpressionWithDetails2.clear();
        isMerged = true;
    }
    return isMerged;
}

void retrieveUniqueExpressionsAndMergeTerms(
        Expression & uniqueExpression1,
        Expression & uniqueExpression2,
        Term & mergeTerm1,
        Term & mergeTerm2,
        TermWithDetails const& termExpressionWithDetails1,
        TermWithDetails const& termExpressionWithDetails2)
{
    Term const& termExpression1(getTermConstReferenceFromSharedPointer(termExpressionWithDetails1.baseTermSharedPointer));
    Term const& termExpression2(getTermConstReferenceFromSharedPointer(termExpressionWithDetails2.baseTermSharedPointer));
    Expression expression1(createOrCopyExpressionFromATerm(termExpression1));
    Expression expression2(createOrCopyExpressionFromATerm(termExpression2));
    uniqueExpression1 = getUniqueExpressionForAdditionOrSubtractionMergeChecking(expression1);
    uniqueExpression2 = getUniqueExpressionForAdditionOrSubtractionMergeChecking(expression2);
    uniqueExpression1.sort();
    uniqueExpression2.sort();
    accumulateMergeTermForAdditionOrSubtractionMergeChecking(mergeTerm1, expression1);
    accumulateMergeTermForAdditionOrSubtractionMergeChecking(mergeTerm2, expression2);
}

Expression getUniqueExpressionForAdditionOrSubtractionMergeChecking(Expression const& expression)
{
    Expression result;
    if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        TermsWithAssociation uniqueExpressions(
                    expression.getTermsWithDetailsThatSatisfiesCondition(
                        [](TermWithDetails const& termWithDetails) -> bool {
                        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
                        return termWithDetails.hasNegativeAssociation() || term.isExpression();
                    }));
        result.set(OperatorLevel::MultiplicationAndDivision, uniqueExpressions);
        result.simplify();
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        result = expression;
    }
    return result;
}

void accumulateMergeTermForAdditionOrSubtractionMergeChecking(Term & combinedTerm, Expression const& expression)
{
    if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        TermsWithAssociation termsToBeMerged(
                    expression.getTermsWithDetailsThatSatisfiesCondition(
                        [](TermWithDetails const& termWithDetails) -> bool {
                        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
                        return !(termWithDetails.hasNegativeAssociation() || term.isExpression());
                    }));
        accumulateTermsForAdditionAndSubtraction(combinedTerm, termsToBeMerged.getTermsWithDetails());
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        combinedTerm = Term(1);
    }
}

bool canBeMergedForAdditionAndSubtraction(
        Expression const& uniqueExpression1,
        Expression const& uniqueExpression2,
        Term const& mergeTerm1,
        Term const& mergeTerm2)
{
    return uniqueExpression1 == uniqueExpression2 && canBeMergedByAdditionOrSubtraction(mergeTerm1, mergeTerm2);
}

}

}
