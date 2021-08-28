#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

void segregateMonomialsAndNonMonomials(
        Terms const& termsToSegregate,
        Terms & monomials,
        Terms & nonMonomials);
void segregateMonomialsAndNonMonomials(
        TermsWithAssociation::TermsWithDetails const& termsToSegregate,
        TermsWithAssociation::TermsWithDetails & monomials,
        TermsWithAssociation::TermsWithDetails & nonMonomials);
void segregatePolynomialAndNonPolynomials(
        Terms const& termsToSegregate,
        Terms & polynomials,
        Terms & nonPolynomials);
void segregateNonExpressionsAndExpressions(
        TermsWithAssociation::TermsWithDetails const& termsToSegregate,
        TermsWithAssociation::TermsWithDetails & termsWithNonExpressions,
        TermsWithAssociation::TermsWithDetails & termsWithExpressions);
void segregateTermsWithPositiveAndNegativeAssociations(
        TermsWithAssociation::TermsWithDetails const& termsToSegregate,
        TermsWithAssociation::TermsWithDetails & termsWithPositiveAssociation,
        TermsWithAssociation::TermsWithDetails & termsWithNegativeAssociation);

}

}
