#pragma once

#include <Algebra/Term/Expression.hpp>
#include <Algebra/Term/Polynomial.hpp>

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
