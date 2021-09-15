#include "FactorizationOfExpression.hpp"

#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

void factorizeAnExpression(Expression & expression)
{
    TermsWithDetails termsToPut;
    TermsWithDetails & termsWithDetails(expression.getTermsWithAssociationReference().getTermsWithDetailsReference());
    for(TermsWithDetails::iterator it=termsWithDetails.begin(); it!=termsWithDetails.end(); it++)
    {
        Term & term(getTermReferenceFromSharedPointer(it->baseTermSharedPointer));
        if(term.isExpression())
        {
            Expression & subExpression(term.getExpressionReference());
            factorizeAnExpression(subExpression);
        }
        else if(term.isPolynomial())
        {
            factorizePolynomialAndUpdate(expression, termsToPut, term.getPolynomialConstReference(), it->association);
            termsWithDetails.erase(it);
            it--;
        }
    }
    expression.putTermsWithDetails(termsToPut);
}

void factorizePolynomialAndUpdate(
        Expression & expression,
        TermsWithDetails & termsToPut,
        Polynomial const& polynomial,
        TermAssociationType const overallAssociation)
{
    if(OperatorLevel::Unknown == expression.getCommonOperatorLevel())
    {
        expression.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    }
    if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        TermsWithDetails factorizedTermsWithDetails;
        factorizePolynomialAndEmplaceInTermsWithDetails(factorizedTermsWithDetails, polynomial, overallAssociation);
        termsToPut.reserve(factorizedTermsWithDetails.size());
        copy(factorizedTermsWithDetails.cbegin(), factorizedTermsWithDetails.cend(), back_inserter(termsToPut));
    }
    else
    {
        TermsWithDetails factorizedTermsWithDetails;
        factorizePolynomialAndEmplaceInTermsWithDetails(factorizedTermsWithDetails, polynomial, TermAssociationType::Positive);
        Expression newSubExpression;
        newSubExpression.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
        newSubExpression.putTermsWithDetails(factorizedTermsWithDetails);
        termsToPut.emplace_back(Term(newSubExpression), overallAssociation);
    }
}

void factorizePolynomialAndEmplaceInTermsWithDetails(
        TermsWithDetails & factorizedTermsWithDetails,
        Polynomial const& polynomial,
        TermAssociationType const overallAssociation)
{
    Polynomials factorizedPolynomials(factorizeAPolynomial(polynomial));
    for(Polynomial const& factorizedPolynomial : factorizedPolynomials)
    {
        factorizedTermsWithDetails.emplace_back(Term(factorizedPolynomial), overallAssociation);
    }
}

}

}

}
