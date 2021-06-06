#include "TermsWithPriorityAndAssociation.hpp"

#include <Term.hpp>
#include <Utilities.hpp>

#include <algorithm>

using namespace std;

namespace alba{

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
    Term const& term1(getTermConstReferenceFromBaseTerm(getBaseTermConstReferenceFromSharedPointer(baseTermSharedPointer)));
    Term const& term2(getTermConstReferenceFromBaseTerm(getBaseTermConstReferenceFromSharedPointer(second.baseTermSharedPointer)));
    return term1 == term2 && association == second.association;
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
    unsigned int result(0);
    switch(association)
    {
    case AssociationType::Negative:
        result=0;
        break;
    case AssociationType::Positive:
        result=1;
        break;
    }
    return result;
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
        using TermsWithDetailsIterator=TermsWithDetails::const_iterator;        using MismatchResultType=pair<TermsWithDetailsIterator, TermsWithDetailsIterator>;
        MismatchResultType mismatchResult = mismatch(terms1.cbegin(), terms1.end(), terms2.cbegin());
        result = mismatchResult.first == terms1.cend();
    }
    return result;
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
