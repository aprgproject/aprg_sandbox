#include "TermsWithAssociation.hpp"

#include <Equation/Term/Term.hpp>
#include <Equation/Utilities.hpp>

#include <algorithm>
using namespace std;

namespace alba{

namespace equation
{

TermsWithAssociation::TermWithDetails::TermWithDetails(
        BaseTerm const& baseTerm,
        TermAssociationType const associationParameter)
    : baseTermSharedPointer(copyAndCreateNewTermAndReturnSharedPointer(getTermConstReferenceFromBaseTerm(baseTerm)))
    , association(associationParameter)
{}

TermsWithAssociation::TermWithDetails::TermWithDetails(TermWithDetails const& termWithDetails)
    : baseTermSharedPointer(createNewTermAndReturnSharedPointer(termWithDetails.baseTermSharedPointer))
    , association(termWithDetails.association)
{}

bool TermsWithAssociation::TermWithDetails::operator==(TermWithDetails const& second) const
{
    Term const& term1(getTermConstReferenceFromSharedPointer(baseTermSharedPointer));
    Term const& term2(getTermConstReferenceFromSharedPointer(second.baseTermSharedPointer));
    return term1 == term2 && association == second.association;
}

bool TermsWithAssociation::TermWithDetails::operator!=(TermWithDetails const& second) const
{
    return !(operator==(second));
}

bool TermsWithAssociation::TermWithDetails::operator<(TermWithDetails const& second) const
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

bool TermsWithAssociation::TermWithDetails::hasPositiveAssociation() const
{
    return TermAssociationType::Positive == association;
}

bool TermsWithAssociation::TermWithDetails::hasNegativeAssociation() const
{
    return TermAssociationType::Negative == association;
}

unsigned int TermsWithAssociation::TermWithDetails::getAssociationPriority() const
{
    return equation::getAssociationPriority(association);
}

void TermsWithAssociation::TermWithDetails::clear()
{
    baseTermSharedPointer.reset();
    association=TermAssociationType::Positive;
}

TermsWithAssociation::TermsWithAssociation()
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

TermsWithAssociation::TermsWithDetails const& TermsWithAssociation::getTermsWithDetails() const
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

void TermsWithAssociation::substituteVariablesToValues(VariablesToValuesMap const& variableValueMap)
{
    for(TermWithDetails & termWithDetails : m_termsWithDetails)
    {
        Term & term(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        term.substituteVariablesToValues(variableValueMap);
    }
}

void TermsWithAssociation::putTermWithDetails(TermWithDetails const& termWithDetails)
{
    m_termsWithDetails.emplace_back(getBaseTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer), termWithDetails.association);
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
        if(termWithDetails.hasPositiveAssociation())
        {
            termWithDetails.association = TermAssociationType::Negative;
        }
        else if(termWithDetails.hasNegativeAssociation())
        {
            termWithDetails.association = TermAssociationType::Positive;
        }
    }
}

}

}
