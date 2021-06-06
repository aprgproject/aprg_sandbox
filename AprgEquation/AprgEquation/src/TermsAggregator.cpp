#include "TermsAggregator.hpp"

#include <PerformOperation.hpp>
#include <Utilities.hpp>

using namespace std;

namespace alba
{

namespace equation
{

TermsAggregator::TermsAggregator(Terms const& terms)
    : m_terms(terms)
{}

Terms const& TermsAggregator::getTermsConstReference() const
{
    return m_terms;
}

void TermsAggregator::buildExpressionFromTerms()
{
    bool continueToSimplify(true);
    while(continueToSimplify)
    {
        AlbaOptional<unsigned int> nextOperatorIndexOptional(getNextOperatorIndexToPerform());
        continueToSimplify = nextOperatorIndexOptional.hasContent();
        if(nextOperatorIndexOptional.hasContent())
        {
            unsigned int nextOperatorIndex = nextOperatorIndexOptional.get();
            continueToSimplify = buildExpressionWithBinaryOperationAndReturnIfBuilt(nextOperatorIndex);
            if(!continueToSimplify)
            {
                continueToSimplify = buildExpressionWithUnaryOperationAndReturnIfBuilt(nextOperatorIndex);
            }
        }
    }
}

void TermsAggregator::simplifyTerms()
{
    bool continueToSimplify(true);
    while(continueToSimplify)
    {
        AlbaOptional<unsigned int> nextOperatorIndexOptional(getNextOperatorIndexToPerform());
        continueToSimplify = nextOperatorIndexOptional.hasContent();
        if(nextOperatorIndexOptional.hasContent())
        {
            unsigned int nextOperatorIndex = nextOperatorIndexOptional.get();
            continueToSimplify = simplifyBinaryOperationAndReturnIfSimplified(nextOperatorIndex);
            if(!continueToSimplify)
            {
                continueToSimplify=simplifyUnaryOperationAndReturnIfSimplified(nextOperatorIndex);
            }
        }
    }
}

AlbaOptional<unsigned int> TermsAggregator::getNextOperatorIndexToPerform() const
{
    AlbaOptional<unsigned int> operatorIndexOptional;
    multimap<unsigned int, unsigned int> operatorLevelToIndexMap;
    for(unsigned int i=0; i<m_terms.size(); i++)
    {
        Term const& term(m_terms[i]);
        if(term.isOperator())
        {
            operatorLevelToIndexMap.emplace(getOperatorLevelInversePriority(term.getOperatorConstReference().getOperatorLevel()), i);
        }
    }
    if(!operatorLevelToIndexMap.empty())
    {
        pair<unsigned int, unsigned int> operatorLevelToIndexPair(*operatorLevelToIndexMap.begin());
        operatorIndexOptional.setValue(operatorLevelToIndexPair.second);
    }
    return operatorIndexOptional;
}

bool TermsAggregator::buildExpressionWithBinaryOperationAndReturnIfBuilt(unsigned int const index)
{
    bool isSimplified(false);
    if(index>0 && index+1 < m_terms.size())
    {
        Term const& term1(m_terms[index-1]);
        Term const& term2(m_terms[index]);
        Term const& term3(m_terms[index+1]);
        if(term1.isValueTerm() && term2.isOperator() && term3.isValueTerm())
        {
            Expression newExpression(createOrCopyExpressionFromATerm(term1));
            Operator const& operatorTerm(term2.getOperatorConstReference());
            if(operatorTerm.isAddition())
            {
                newExpression.addTerm(getBaseTermConstReferenceFromTerm(term3));
            }
            else if(operatorTerm.isSubtraction())
            {                newExpression.subtractTerm(getBaseTermConstReferenceFromTerm(term3));
            }
            else if(operatorTerm.isMultiplication())
            {
                newExpression.multiplyTerm(getBaseTermConstReferenceFromTerm(term3));
            }
            else if(operatorTerm.isDivision())
            {
                newExpression.divideTerm(getBaseTermConstReferenceFromTerm(term3));
            }
            else if(operatorTerm.isRaiseToPower())
            {
                newExpression.raiseToPowerTerm(getBaseTermConstReferenceFromTerm(term3));
            }
            Term newTerm(newExpression);
            eraseTermsInclusive(index-1, index+1);
            insertTerm(index-1, newTerm);
            isSimplified=true;
        }
    }
    return isSimplified;
}

bool TermsAggregator::buildExpressionWithUnaryOperationAndReturnIfBuilt(unsigned int const index)
{
    bool isSimplified(false);
    if(index>0 && index+1 < m_terms.size())
    {
        Term const& term1(m_terms[index]);
        Term const& term2(m_terms[index+1]);
        if(term1.isOperator() && term2.isValueTerm() &&
                OperatorLevel::AdditionAndSubtraction == term1.getOperatorConstReference().getOperatorLevel())
        {
            Expression newExpression;
            Operator const& operatorTerm(term1.getOperatorConstReference());
            if(operatorTerm.isAddition())
            {
                newExpression.addTerm(getBaseTermConstReferenceFromTerm(term2));
            }
            else if(operatorTerm.isSubtraction())
            {
                newExpression.subtractTerm(getBaseTermConstReferenceFromTerm(term2));
            }
            Term newTerm(newExpression);
            eraseTermsInclusive(index, index+1);
            insertTerm(index, newTerm);
            isSimplified=true;
        }
    }
    return isSimplified;
}

bool TermsAggregator::simplifyBinaryOperationAndReturnIfSimplified(unsigned int const index)
{
    bool isSimplified(false);
    if(index>0 && index+1 < m_terms.size())
    {
        Term const& term1(m_terms[index-1]);
        Term const& term2(m_terms[index]);
        Term const& term3(m_terms[index+1]);
        if(term1.isValueTerm() && term2.isOperator() && term3.isValueTerm())
        {
            Term newTerm = performOperation(term2.getOperatorConstReference(), term1, term3);
            eraseTermsInclusive(index-1, index+1);
            insertTerm(index-1, newTerm);
            isSimplified=true;
        }
    }
    return isSimplified;
}

bool TermsAggregator::simplifyUnaryOperationAndReturnIfSimplified(unsigned int const index)
{
    bool isSimplified(false);
    if(index>0 && index+1 < m_terms.size())
    {
        Term const& term1(m_terms[index]);
        Term const& term2(m_terms[index+1]);
        if(term1.isOperator() && term2.isValueTerm() &&
                OperatorLevel::AdditionAndSubtraction == term1.getOperatorConstReference().getOperatorLevel())
        {
            Term newTerm = performOperation(term1.getOperatorConstReference(), term1);
            eraseTermsInclusive(index, index+1);
            insertTerm(index, newTerm);
            isSimplified=true;
        }
    }
    return isSimplified;
}

void TermsAggregator::eraseTermsInclusive(
        unsigned int const firstIndex,
        unsigned int const secondIndex)
{
    m_terms.erase(m_terms.cbegin()+firstIndex, m_terms.cbegin()+secondIndex+1);
}

void TermsAggregator::insertTerm(
        unsigned int const index,
        Term const& term)
{
    m_terms.emplace(m_terms.cbegin()+index, term);
}

}

}
