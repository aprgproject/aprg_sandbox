#pragma once

#include <Term.hpp>
#include <Optional/AlbaOptional.hpp>

namespace alba
{

namespace equation
{

class TermsSimplificator
{
public:
    TermsSimplificator(Terms const& terms);

    Terms const& getTermsConstReference() const;

    void simplify();
    void simplify(unsigned int const index);
    void simplifyThreeTerms(unsigned int const index);

    AlbaOptional<Term> getNewTermFromThreeTerms(
            Term const& term1,
            Term const& term2,
            Term const& term3) const;

    void eraseTermsInclusive(
            unsigned int const firstIndex,
            unsigned int const secondIndex);
    void insertTerm(
            unsigned int const index,
            Term const& term);


private:
    Terms m_terms;
};

}

}
