#include "AdditionAndSubtractionOfExpressions.hpp"

#include <Equation/Operations/AccumulateOperations.hpp>
#include <Equation/Term/TermOperators.hpp>
#include <Equation/Utilities.hpp>

#include <algorithm>

using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

AdditionAndSubtractionOfExpressions::AdditionAndSubtractionOfExpressions()
{}

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
                        getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer)),
                    termWithDetails.association);
    }
}

void AdditionAndSubtractionOfExpressions::combineExpressionsIfPossible()
{
    unsigned int size = getSize();
    for(unsigned int firstIndex=0; firstIndex<size; firstIndex++)
    {
        for(unsigned int secondIndex=firstIndex+1; secondIndex<size; secondIndex++)
        {
            if(mergeForAdditionAndSubtractionAndReturnIfMerged(firstIndex, secondIndex))
            {
                m_expressions.erase(m_expressions.begin()+secondIndex);
                m_associations.erase(m_associations.begin()+secondIndex);
                size = getSize();
                m_associations[firstIndex]=TermAssociationType::Positive;
                secondIndex=firstIndex;
            }
        }
    }
}

bool AdditionAndSubtractionOfExpressions::mergeForAdditionAndSubtractionAndReturnIfMerged(
        unsigned int const index1,
        unsigned int const index2)
{
    bool isMerged(false);
    Expression & expression1(m_expressions.at(index1));
    Expression & expression2(m_expressions.at(index2));
    Expression uniqueExpression1, uniqueExpression2;
    Term mergeTerm1, mergeTerm2;
    retrieveUniqueExpressionsAndMergeTerms(uniqueExpression1, uniqueExpression2, mergeTerm1, mergeTerm2, expression1, expression2);
    if(canBeMergedForAdditionAndSubtraction(uniqueExpression1, uniqueExpression2, mergeTerm1, mergeTerm2))
    {
        Term resultMergeTerm;
        TermsWithDetails termsToMerge;
        termsToMerge.emplace_back(mergeTerm1, m_associations.at(index1));
        termsToMerge.emplace_back(mergeTerm2, m_associations.at(index2));
        accumulateTermsForAdditionAndSubtraction(resultMergeTerm, termsToMerge);
        expression1 = createOrCopyExpressionFromATerm(resultMergeTerm*Term(uniqueExpression1));
        expression2.clear();

        isMerged = true;
    }
    return isMerged;
}

void AdditionAndSubtractionOfExpressions::retrieveUniqueExpressionsAndMergeTerms(
        Expression & uniqueExpression1,
        Expression & uniqueExpression2,
        Term & mergeTerm1,
        Term & mergeTerm2,
        Expression const& expression1,
        Expression const& expression2)
{
    uniqueExpression1 = getUniqueExpressionForAdditionOrSubtractionMergeChecking(expression1);
    uniqueExpression2 = getUniqueExpressionForAdditionOrSubtractionMergeChecking(expression2);
    uniqueExpression1.sort();
    uniqueExpression2.sort();
    accumulateMergeTermForAdditionOrSubtractionMergeChecking(mergeTerm1, expression1);
    accumulateMergeTermForAdditionOrSubtractionMergeChecking(mergeTerm2, expression2);
}

Expression AdditionAndSubtractionOfExpressions::getUniqueExpressionForAdditionOrSubtractionMergeChecking(Expression const& expression)
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

void AdditionAndSubtractionOfExpressions::accumulateMergeTermForAdditionOrSubtractionMergeChecking(Term & combinedTerm, Expression const& expression)
{
    if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        TermsWithAssociation termsToBeMerged(
                    expression.getTermsWithDetailsThatSatisfiesCondition(
                        [](TermWithDetails const& termWithDetails) -> bool {
                        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
                        return !(termWithDetails.hasNegativeAssociation() || term.isExpression());
                    }));
        accumulateTermsForMultiplicationAndDivision(combinedTerm, termsToBeMerged.getTermsWithDetails());
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        combinedTerm = Term(1);
    }
}

bool AdditionAndSubtractionOfExpressions::canBeMergedForAdditionAndSubtraction(
        Expression const& uniqueExpression1,
        Expression const& uniqueExpression2,
        Term const& mergeTerm1,
        Term const& mergeTerm2)
{
    return uniqueExpression1 == uniqueExpression2 && canBeMergedInAMonomialByAdditionOrSubtraction(mergeTerm1, mergeTerm2);
}

void AdditionAndSubtractionOfExpressions::putItem(Expression const& expression, TermAssociationType const association)
{
    m_expressions.emplace_back(expression);
    m_associations.emplace_back(association);
}

}

}
