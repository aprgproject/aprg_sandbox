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
        BaseTermSharedPointer const& baseTermSharedPointerParameter,
        TermsWithPriorityAndAssociation::AssociationType const associationParameter)
    : baseTermSharedPointer(baseTermSharedPointerParameter)
    , association(associationParameter)
{}

TermsWithPriorityAndAssociation::TermWithDetails::TermWithDetails(TermWithDetails const& termWithDetails)
    : baseTermSharedPointer(createBaseTermSharedPointer(termWithDetails.baseTermSharedPointer))
    , association(termWithDetails.association)
{}

bool TermsWithPriorityAndAssociation::TermWithDetails::operator==(TermWithDetails const& second) const
{
    Term const& term1 = *dynamic_cast<Term const*const>(baseTermSharedPointer.get());
    Term const& term2 = *dynamic_cast<Term const*const>(second.baseTermSharedPointer.get());
    return term1 == term2;
}

bool TermsWithPriorityAndAssociation::TermWithDetails::hasPositiveAssociation() const
{
    return AssociationType::Positive == association;
}

bool TermsWithPriorityAndAssociation::TermWithDetails::hasNegativeAssociation() const
{
    return AssociationType::Positive == association;
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
        using TermsWithDetailsIterator=TermsWithDetails::const_iterator;
        using MismatchResultType=pair<TermsWithDetailsIterator, TermsWithDetailsIterator>;
        MismatchResultType mismatchResult = mismatch(terms1.cbegin(), terms1.end(), terms2.cbegin());
        result = mismatchResult.first == terms1.cend();
    }
    return result;
}

unsigned int TermsWithPriorityAndAssociation::getSize() const
{
    return m_termsWithDetails.size();
}

BaseTermSharedPointer const& TermsWithPriorityAndAssociation::getFirstTermConstReference() const
{
    return m_termsWithDetails.front().baseTermSharedPointer;
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
    m_termsWithDetails.emplace_back(createBaseTermSharedPointer(termWithDetails.baseTermSharedPointer), termWithDetails.association);
}

void TermsWithPriorityAndAssociation::putTermWithPositiveAssociation(BaseTermSharedPointer const& baseTermSharedPointer)
{
    m_termsWithDetails.emplace_back(createBaseTermSharedPointer(baseTermSharedPointer), AssociationType::Positive);
}

void TermsWithPriorityAndAssociation::putTermWithNegativeAssociation(BaseTermSharedPointer const& baseTermSharedPointer)
{
    m_termsWithDetails.emplace_back(createBaseTermSharedPointer(baseTermSharedPointer), AssociationType::Negative);
}

void TermsWithPriorityAndAssociation::performFunctionOnAllTerms(TermsWithDetailsFunction const& functionToPerform) const
{
    for(TermWithDetails const& termWithDetails : m_termsWithDetails)
    {
        functionToPerform(termWithDetails);
    }
}



}

}
