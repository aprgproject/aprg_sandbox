#include "AdditionAndSubtractionOfExpressions.hpp"

#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/EnumHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

namespace
{

ConditionFunctionForTermsWithDetails isUniquePartOfTerm
= [](TermWithDetails const& termWithDetails) -> bool
{
    Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
    return termWithDetails.hasNegativeAssociation() || term.isExpression()  || term.isFunction();
};

ConditionFunctionForTermsWithDetails isNotUniquePartOfTerm
= [](TermWithDetails const& termWithDetails) -> bool
{
    return !isUniquePartOfTerm(termWithDetails);
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
    {        Term resultMergeTerm;
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
    if(OperatorLevel::RaiseToPower != uniqueExpression1.getCommonOperatorLevel())
    {
        uniqueExpression1.sort();
    }
    if(OperatorLevel::RaiseToPower != uniqueExpression1.getCommonOperatorLevel())
    {
        uniqueExpression2.sort();
    }
    accumulateMergeTermForAdditionOrSubtractionMergeChecking(mergeTerm1, expression1);
    accumulateMergeTermForAdditionOrSubtractionMergeChecking(mergeTerm2, expression2);
}

Expression AdditionAndSubtractionOfExpressions::getUniqueExpressionForAdditionOrSubtractionMergeChecking(Expression const& expression)
{
    Expression result;
    if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        TermsWithDetails uniqueExpressions
                = retrieveTermsWithDetailsThatSatisfiesCondition(
                    expression.getTermsWithAssociation().getTermsWithDetails(),
                    isUniquePartOfTerm);
        result.set(OperatorLevel::MultiplicationAndDivision, uniqueExpressions);
        result.simplify();
    }    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        result = expression;
    }
    return result;
}

void AdditionAndSubtractionOfExpressions::accumulateMergeTermForAdditionOrSubtractionMergeChecking(Term & combinedTerm, Expression const& expression)
{
    if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        combinedTerm = Term(1);
        TermsWithDetails termsToBeMerged
                = retrieveTermsWithDetailsThatSatisfiesCondition(
                    expression.getTermsWithAssociation().getTermsWithDetails(),
                    isNotUniquePartOfTerm);

        accumulateTermsForMultiplicationAndDivision(combinedTerm, termsToBeMerged);
    }    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
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
