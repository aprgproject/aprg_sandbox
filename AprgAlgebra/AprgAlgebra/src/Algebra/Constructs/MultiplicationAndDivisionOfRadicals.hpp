#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>


namespace alba
{

namespace algebra
{

class MultiplicationAndDivisionOfRadicals
{
public:
    MultiplicationAndDivisionOfRadicals();
    MultiplicationAndDivisionOfRadicals(
            TermsWithAssociation::TermsWithDetails const& termsWithDetails);

    Term getCombinedTerm() const;
    TermsWithAssociation::TermsWithDetails const& getTermsWithDetails() const;

    void simplify();

private:

    TermsWithAssociation::TermsWithDetails m_termsWithDetails;
};

}

}
