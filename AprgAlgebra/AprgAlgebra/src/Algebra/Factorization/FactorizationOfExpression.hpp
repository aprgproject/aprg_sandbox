#pragma once

#include <Algebra/Term/TermTypes/Expression.hpp>
#include <Algebra/Term/TermTypes/Polynomial.hpp>

namespace alba
{

namespace algebra
{

namespace Factorization
{

void factorizeAnExpression(Expression & expression);
void factorizePolynomialAndUpdate(
        Expression & expression,
        TermsWithAssociation::TermsWithDetails & termsToPut,
        Polynomial const& polynomial,
        TermAssociationType const overallAssociation);
void factorizePolynomialAndEmplaceInTermsWithDetails(
        TermsWithAssociation::TermsWithDetails & factorizedTermsWithDetails,
        Polynomial const& polynomial,
        TermAssociationType const overallAssociation);
}

}

}
