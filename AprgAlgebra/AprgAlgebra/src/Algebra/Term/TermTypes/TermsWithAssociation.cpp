#include "TermsWithAssociation.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/EnumHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{


TermsWithAssociation::TermsWithAssociation()
{}

TermsWithAssociation::TermsWithAssociation(
        TermsWithAssociation const& termsWithAssociation)
    : m_termsWithDetails(termsWithAssociation.getTermsWithDetails())
{}

TermsWithAssociation::TermsWithAssociation(
        initializer_list<TermWithDetails> const& termsWithDetails)
{
    putTermsWithDetails(termsWithDetails);}

TermsWithAssociation::TermsWithAssociation(
        TermsWithDetails const& termsWithDetails)
    : m_termsWithDetails(termsWithDetails)
{}

TermsWithAssociation::~TermsWithAssociation()
{}

bool TermsWithAssociation::operator==(TermsWithAssociation const& second) const
{
    TermsWithDetails const& terms1(m_termsWithDetails);
    TermsWithDetails const& terms2(second.m_termsWithDetails);
    bool result(false);
    if(terms1.size() == terms2.size())
    {
        result=true;
        unsigned int commonSize = terms1.size();
        for(unsigned int i=0; i<commonSize; i++)
        {
            if(terms1.at(i) != terms2.at(i))
            {
                result=false;
                break;
            }
        }
    }
    return result;
}

bool TermsWithAssociation::operator!=(TermsWithAssociation const& second) const
{
    return !(operator==(second));
}

bool TermsWithAssociation::operator<(TermsWithAssociation const& second) const
{
    TermsWithDetails const& terms1(m_termsWithDetails);
    TermsWithDetails const& terms2(second.m_termsWithDetails);
    bool result(false);
    if(terms1.size() == terms2.size())
    {
        unsigned int size = terms1.size();
        for(unsigned int i = 0; i < size; i++)
        {
            TermWithDetails const& termWithDetails1(terms1.at(i));
            TermWithDetails const& termWithDetails2(terms2.at(i));
            if(termWithDetails1 != termWithDetails2)
            {
                result = termWithDetails1<termWithDetails2;
                break;
            }
        }
    }
    else
    {
        result =  terms1.size() < terms2.size();
    }
    return result;
}

bool TermsWithAssociation::isEmpty() const
{
    return m_termsWithDetails.empty();
}

unsigned int TermsWithAssociation::getSize() const
{
    return m_termsWithDetails.size();
}

BaseTerm const& TermsWithAssociation::getFirstTermConstReference() const
{
    return getBaseTermConstReferenceFromSharedPointer(m_termsWithDetails.front().baseTermSharedPointer);
}

TermAssociationType TermsWithAssociation::getFirstAssociationType() const
{
    return m_termsWithDetails.front().association;
}

TermsWithDetails const& TermsWithAssociation::getTermsWithDetails() const
{
    return m_termsWithDetails;
}

TermsWithDetails & TermsWithAssociation::getTermsWithDetailsReference()
{
    return m_termsWithDetails;
}

void TermsWithAssociation::clear()
{
    m_termsWithDetails.clear();
}

void TermsWithAssociation::sort()
{
    for(TermWithDetails & termWithDetails : m_termsWithDetails)
    {
        Term & term(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        term.sort();
    }
    stable_sort(m_termsWithDetails.begin(), m_termsWithDetails.end());
}

void TermsWithAssociation::putTermWithDetails(TermWithDetails const& termWithDetails)
{
    m_termsWithDetails.emplace_back(getBaseTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer), termWithDetails.association);
}

void TermsWithAssociation::putTermsWithDetails(initializer_list<TermWithDetails> const& termsWithDetails)
{
    m_termsWithDetails.reserve(m_termsWithDetails.size() + termsWithDetails.size());
    copy(termsWithDetails.begin(), termsWithDetails.end(), back_inserter(m_termsWithDetails));
}

void TermsWithAssociation::putTermsWithDetails(TermsWithDetails const& termsWithDetails)
{
    m_termsWithDetails.reserve(m_termsWithDetails.size() + termsWithDetails.size());
    copy(termsWithDetails.cbegin(), termsWithDetails.cend(), back_inserter(m_termsWithDetails));
}

void TermsWithAssociation::putTermWithAssociation(BaseTerm const& baseTerm, TermAssociationType const associationType)
{
    m_termsWithDetails.emplace_back(baseTerm, associationType);
}

void TermsWithAssociation::putTermWithPositiveAssociation(BaseTerm const& baseTerm)
{
    m_termsWithDetails.emplace_back(baseTerm, TermAssociationType::Positive);
}

void TermsWithAssociation::putTermWithNegativeAssociation(BaseTerm const& baseTerm)
{
    m_termsWithDetails.emplace_back(baseTerm, TermAssociationType::Negative);
}

void TermsWithAssociation::reverseTheAssociationOfTheTerms()
{
    for(TermWithDetails & termWithDetails : m_termsWithDetails)
    {
        termWithDetails.reverseAssociation();
    }
}

}

}
