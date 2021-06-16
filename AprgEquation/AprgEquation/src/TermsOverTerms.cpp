#include "TermsOverTerms.hpp"

#include <Utilities.hpp>

using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

TermsOverTerms::TermsOverTerms(Terms const& numerators, Terms const& denominators)
    : m_numerators(numerators)
    , m_denominators(denominators)
{}

TermsOverTerms::TermsOverTerms(
        TermsWithDetails const& numeratorsWithDetails,
        TermsWithDetails const& denominatorsWithDetails)
{
    for(TermWithDetails const& numeratorWithDetails : numeratorsWithDetails)
    {
        m_numerators.emplace_back(getTermConstReferenceFromSharedPointer(numeratorWithDetails.baseTermSharedPointer));
    }
    for(TermWithDetails const& denominatorWithDetails : denominatorsWithDetails)
    {
        m_denominators.emplace_back(getTermConstReferenceFromSharedPointer(denominatorWithDetails.baseTermSharedPointer));
    }
}

TermsWithDetails TermsOverTerms::getNumeratorAndDenominatorAsTermWithDetails() const
{
    TermsWithDetails result;
    if(areTermsEmptyOrValueOne(m_numerators) && areTermsEmptyOrValueOne(m_denominators))
    {
        result.emplace_back(getBaseTermConstReferenceFromTerm(Term(1)), TermAssociationType::Positive);
    }
    else
    {
        for(Term const& numerator : m_numerators)
        {
            result.emplace_back(getBaseTermConstReferenceFromTerm(numerator), TermAssociationType::Positive);
        }
        for(Term const& denominator : m_denominators)
        {
            result.emplace_back(getBaseTermConstReferenceFromTerm(denominator), TermAssociationType::Negative);
        }
    }
    return result;
}

void TermsOverTerms::removeSameTermsInNumeratorAndDenominator()
{
    for(Terms::iterator numeratorIt = m_numerators.begin();
        numeratorIt != m_numerators.end();
        numeratorIt++)
    {
        for(Terms::iterator denominatorIt = m_denominators.begin();
            denominatorIt != m_denominators.end();
            denominatorIt++)
        {
            Term const& term1(*numeratorIt);
            Term const& term2(*denominatorIt);
            if(term1 == term2)
            {
                m_numerators.erase(numeratorIt);
                m_denominators.erase(denominatorIt);
                numeratorIt--;
                denominatorIt--;
            }
        }
    }
}

bool TermsOverTerms::areTermsEmptyOrValueOne(Terms const& terms) const
{
    bool result(false);
    if(terms.empty())
    {
        result = true;
    }
    else
    {
        result = terms.at(0).isTheValueOne();
    }
    return result;

}

}

}
