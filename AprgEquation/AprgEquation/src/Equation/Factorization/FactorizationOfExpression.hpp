#pragma once

#include <Equation/Term/Expression.hpp>
#include <Equation/Term/Polynomial.hpp>

namespace alba
{

namespace equation
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
