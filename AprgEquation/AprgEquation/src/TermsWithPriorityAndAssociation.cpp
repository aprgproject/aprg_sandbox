#include "TermsWithPriorityAndAssociation.hpp"

#include <Term.hpp>
#include <Utilities.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace equation
{

TermsWithPriorityAndAssociation::TermWithDetails::TermWithDetails(
        BaseTerm const& baseTerm,
        TermsWithPriorityAndAssociation::AssociationType const associationParameter)
    : baseTermSharedPointer(copyAndCreateNewTermAndReturnSharedPointer(getTermConstReferenceFromBaseTerm(baseTerm)))
    , association(associationParameter)
{}

TermsWithPriorityAndAssociation::TermWithDetails::TermWithDetails(TermWithDetails const& termWithDetails)
    : baseTermSharedPointer(createNewTermAndReturnSharedPointer(termWithDetails.baseTermSharedPointer))
    , association(termWithDetails.association)
{}

bool TermsWithPriorityAndAssociation::TermWithDetails::operator==(TermWithDetails const& second) const
{
    Term const& term1(getTermConstReferenceFromSharedPointer(baseTermSharedPointer));
    Term const& term2(getTermConstReferenceFromSharedPointer(second.baseTermSharedPointer));
    return term1 == term2 && association == second.association;
}

bool TermsWithPriorityAndAssociation::TermWithDetails::operator!=(TermWithDetails const& second) const
{
    return !(operator==(second));
}

bool TermsWithPriorityAndAssociation::TermWithDetails::operator<(TermWithDetails const& second) const
{
    bool result(false);
    if(association == second.association)
    {
        Term const& term1(getTermConstReferenceFromSharedPointer(baseTermSharedPointer));
        Term const& term2(getTermConstReferenceFromSharedPointer(second.baseTermSharedPointer));
        result = term1 < term2;
    }
    else
    {
        result = getAssociationPriority() < second.getAssociationPriority();
    }
    return result;
}

bool TermsWithPriorityAndAssociation::TermWithDetails::hasPositiveAssociation() const
{
    return AssociationType::Positive == association;
}

bool TermsWithPriorityAndAssociation::TermWithDetails::hasNegativeAssociation() const
{
    return AssociationType::Negative == association;
}

unsigned int TermsWithPriorityAndAssociation::TermWithDetails::getAssociationPriority() const
{
    return equation::getAssociationPriority(association);
}

void TermsWithPriorityAndAssociation::TermWithDetails::clear()
{
    baseTermSharedPointer.reset();
    association=AssociationType::Positive;
}

TermsWithPriorityAndAssociation::TermsWithPriorityAndAssociation()
{}

TermsWithPriorityAndAssociation::~TermsWithPriorityAndAssociation()
{}

bool TermsWithPriorityAndAssociation::operator==(TermsWithPriorityAndAssociation const& second) const
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

bool TermsWithPriorityAndAssociation::operator!=(TermsWithPriorityAndAssociation const& second) const
{
    return !(operator==(second));
}

bool TermsWithPriorityAndAssociation::operator<(TermsWithPriorityAndAssociation const& second) const
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

bool TermsWithPriorityAndAssociation::isEmpty() const
{
    return m_termsWithDetails.empty();
}

unsigned int TermsWithPriorityAndAssociation::getSize() const
{
    return m_termsWithDetails.size();
}

BaseTerm const& TermsWithPriorityAndAssociation::getFirstTermConstReference() const
{
    return getBaseTermConstReferenceFromSharedPointer(m_termsWithDetails.front().baseTermSharedPointer);
}

TermsWithPriorityAndAssociation::TermsWithDetails const& TermsWithPriorityAndAssociation::getTermsWithDetails() const
{
    return m_termsWithDetails;
}

void TermsWithPriorityAndAssociation::clear()
{
    m_termsWithDetails.clear();
}

void TermsWithPriorityAndAssociation::sort()
{
    for(TermWithDetails & termWithDetails : m_termsWithDetails)
    {
        Term & term(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        term.sort();
    }
    stable_sort(m_termsWithDetails.begin(), m_termsWithDetails.end());
}

void TermsWithPriorityAndAssociation::putTermWithDetails(TermWithDetails const& termWithDetails)
{
    m_termsWithDetails.emplace_back(getBaseTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer), termWithDetails.association);
}

void TermsWithPriorityAndAssociation::putTermWithPositiveAssociation(BaseTerm const& baseTerm)
{
    m_termsWithDetails.emplace_back(baseTerm, AssociationType::Positive);
}

void TermsWithPriorityAndAssociation::putTermWithNegativeAssociation(BaseTerm const& baseTerm)
{
    m_termsWithDetails.emplace_back(baseTerm, AssociationType::Negative);
}

void TermsWithPriorityAndAssociation::reverseTheAssociationOfTheTerms()
{
    for(TermWithDetails & termWithDetails : m_termsWithDetails)
    {
        if(termWithDetails.hasPositiveAssociation())
        {
            termWithDetails.association = AssociationType::Negative;
        }
        else if(termWithDetails.hasNegativeAssociation())
        {
            termWithDetails.association = AssociationType::Positive;
        }
    }
}

}

}
