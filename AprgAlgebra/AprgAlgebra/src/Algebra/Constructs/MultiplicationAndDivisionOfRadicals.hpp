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
            TermsWithDetails const& termsWithDetails);

    Term getCombinedTerm() const;
    TermsWithDetails const& getTermsWithDetails() const;

    void simplify();

private:
    void combineRadicalsInMultiplicationAndDivision(
            TermsWithDetails & termsWithDetails);
    void combineMonomialAndFirstRadicalInMultiplicationAndDivision(
            TermsWithDetails & termsWithDetails);

    TermsWithDetails m_termsWithDetails;
};
}

}
