#include "TermsSimplificator.hpp"

#include <PerformOperation.hpp>
#include <Utilities.hpp>

using namespace std;

namespace alba
{

namespace equation
{

TermsSimplificator::TermsSimplificator(Terms const& terms)
    : m_terms(terms)
{}

Terms const& TermsSimplificator::getTermsConstReference() const
{
    return m_terms;
}

void TermsSimplificator::simplify()
{
    unsigned int previousTermSize = m_terms.size();
    for(unsigned int index=0; index<m_terms.size(); )
    {
        simplify(index);
        unsigned int currentTermSize = m_terms.size();
        if(previousTermSize == currentTermSize)
        {
            index++;
        }
        previousTermSize=currentTermSize;
    }
}

void TermsSimplificator::simplify(unsigned int const index)
{
    simplifyThreeTerms(index);
}

void TermsSimplificator::simplifyThreeTerms(unsigned int const index)
{
    if(index+2 < m_terms.size())
    {
        Term const& term1(m_terms[index]);
        Term const& term2(m_terms[index+1]);
        Term const& term3(m_terms[index+2]);
        AlbaOptional<Term> newTermOptional(getNewTermFromThreeTerms(term1, term2, term3));
        if(newTermOptional.hasContent())
        {
            eraseTermsInclusive(index, index+2);
            insertTerm(index, newTermOptional.getConstReference());
        }
    }
}

AlbaOptional<Term> TermsSimplificator::getNewTermFromThreeTerms(
        Term const& term1,
        Term const& term2,
        Term const& term3) const
{
    AlbaOptional<Term> result;
    if(term2.isOperator())
    {
        result.setValue(performOperation(term2.getOperatorConstReference(), term1, term3));
    }
    return result;
}

void TermsSimplificator::eraseTermsInclusive(
        unsigned int const firstIndex,
        unsigned int const secondIndex)
{
    m_terms.erase(m_terms.cbegin()+firstIndex, m_terms.cbegin()+secondIndex+1);
}

void TermsSimplificator::insertTerm(
        unsigned int const index,
        Term const& term)
{
    m_terms.emplace(m_terms.cbegin()+index, term);
}

}

}
