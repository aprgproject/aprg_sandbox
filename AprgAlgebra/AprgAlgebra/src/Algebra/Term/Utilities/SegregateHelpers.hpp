#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

void segregateMonomialsWithAndWithoutVariable(
        Monomials const& monomialsToSegregate,
        std::string const& variableName,
        Monomials & monomialsWithVariable,
        Monomials & monomialsWithoutVariable);

void segregateMonomialsAndNonMonomials(
        Terms const& termsToSegregate,
        Terms & monomials,
        Terms & nonMonomials);

void segregateMonomialsAndNonMonomials(
        TermsWithDetails const& termsToSegregate,
        TermsWithDetails & monomials,
        TermsWithDetails & nonMonomials);

void segregatePolynomialAndNonPolynomials(
        Terms const& termsToSegregate,
        Terms & polynomials,
        Terms & nonPolynomials);

void segregateNonExpressionsAndExpressions(
        TermsWithDetails const& termsToSegregate,
        TermsWithDetails & termsWithNonExpressions,
        TermsWithDetails & termsWithExpressions);

void segregateTermsWithPositiveAndNegativeAssociations(
        TermsWithDetails const& termsToSegregate,
        TermsWithDetails & termsWithPositiveAssociation,
        TermsWithDetails & termsWithNegativeAssociation);

void segregateTermsWithAndWithoutVariable(
        TermsWithDetails const& termsToSegregate,
        std::string const& variableName,
        TermsWithDetails & termsWithVariable,
        TermsWithDetails & termsWithoutVariable);

}

}