#include "FactorizationOfExpression.hpp"

#include <Equation/Factorization/FactorizationOfPolynomial.hpp>
#include <Equation/Term/Term.hpp>
#include <Equation/Utilities.hpp>
using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace equation
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
        else if(term.isFunction())
        {
            Expression & inputExpression(term.getFunctionReference().getInputExpressionReference());
            factorizeAnExpression(inputExpression);
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