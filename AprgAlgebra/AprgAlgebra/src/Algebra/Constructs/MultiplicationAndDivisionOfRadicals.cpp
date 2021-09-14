#include "MultiplicationAndDivisionOfRadicals.hpp"

using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace algebra
{

MultiplicationAndDivisionOfRadicals::MultiplicationAndDivisionOfRadicals()
{}

MultiplicationAndDivisionOfRadicals::MultiplicationAndDivisionOfRadicals(
        TermsWithAssociation::TermsWithDetails const& termsWithDetails)
    : m_termsWithDetails(termsWithDetails)
{}

Term MultiplicationAndDivisionOfRadicals::getCombinedTerm() const
{
    // put logic here
}

TermsWithDetails const& MultiplicationAndDivisionOfRadicals::getTermsWithDetails() const
{
    return m_termsWithDetails;
}

void MultiplicationAndDivisionOfRadicals::simplify()
{
    // refactor
}

}

}
