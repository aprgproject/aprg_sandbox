#include "MultiplicationAndDivisionOfRadicals.hpp"

namespace alba
{

namespace algebra
{

MultiplicationAndDivisionOfRadicals::MultiplicationAndDivisionOfRadicals()
{}

MultiplicationAndDivisionOfRadicals::MultiplicationAndDivisionOfRadicals(
        TermsWithDetails const& termsWithDetails)
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
