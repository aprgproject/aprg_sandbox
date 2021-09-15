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
        TermsWithDetails & termsToPut,
        Polynomial const& polynomial,
        TermAssociationType const overallAssociation);
void factorizePolynomialAndEmplaceInTermsWithDetails(
        TermsWithDetails & factorizedTermsWithDetails,
        Polynomial const& polynomial,
        TermAssociationType const overallAssociation);
}

}

}
