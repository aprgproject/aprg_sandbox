#include "TermWithDetails.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/EnumHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

TermWithDetails::TermWithDetails(
        BaseTerm const& baseTerm,
        TermAssociationType const associationParameter)
    : baseTermSharedPointer(copyAndCreateNewTermAndReturnSharedPointer(getTermConstReferenceFromBaseTerm(baseTerm)))
    , association(associationParameter)
{}

TermWithDetails::TermWithDetails(TermWithDetails const& termWithDetails)
    : baseTermSharedPointer(createNewTermAndReturnSharedPointer(termWithDetails.baseTermSharedPointer))
    , association(termWithDetails.association)
{}

bool TermWithDetails::operator==(TermWithDetails const& second) const
{
    Term const& term1(getTermConstReferenceFromSharedPointer(baseTermSharedPointer));
    Term const& term2(getTermConstReferenceFromSharedPointer(second.baseTermSharedPointer));
    return term1 == term2 && association == second.association;
}

bool TermWithDetails::operator!=(TermWithDetails const& second) const
{
    return !(operator==(second));
}

bool TermWithDetails::operator<(TermWithDetails const& second) const
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

bool TermWithDetails::hasPositiveAssociation() const
{
    return TermAssociationType::Positive == association;
}

bool TermWithDetails::hasNegativeAssociation() const
{
    return TermAssociationType::Negative == association;
}

unsigned int TermWithDetails::getAssociationPriority() const
{
    return algebra::getAssociationPriority(association);
}

void TermWithDetails::clear()
{
    baseTermSharedPointer.reset();    association = TermAssociationType::Positive;
}

void TermWithDetails::reverseAssociation()
{
    association = getReversedAssociationType(association);
}

}

}