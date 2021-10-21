#include "SegregateHelpers.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace std;
namespace alba
{

namespace algebra
{

void segregateMonomialsWithAndWithoutVariable(
        Monomials const& monomialsToSegregate,
        string const& variableName,
        Monomials & monomialsWithVariable,
        Monomials & monomialsWithoutVariable)
{
    for(Monomial const& monomial : monomialsToSegregate)
    {
        if(monomial.getExponentForVariable(variableName) != 0)
        {
            monomialsWithVariable.emplace_back(monomial);
        }
        else
        {
            monomialsWithoutVariable.emplace_back(monomial);
        }
    }
}

void segregateMonomialsAndNonMonomials(
        Terms const& termsToSegregate,
        Terms & monomials,        Terms & nonMonomials)
{
    for(Term const& termToSegregate : termsToSegregate)
    {
        if(canBeConvertedToMonomial(termToSegregate))
        {
            monomials.emplace_back(termToSegregate);
        }
        else
        {
            nonMonomials.emplace_back(termToSegregate);
        }
    }
}

void segregateMonomialsAndNonMonomials(
        TermsWithDetails const& termsToSegregate,
        TermsWithDetails & monomials,
        TermsWithDetails & nonMonomials)
{
    for(TermWithDetails const& termToSegregate : termsToSegregate)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termToSegregate.baseTermSharedPointer));
        if(canBeConvertedToMonomial(term))
        {
            monomials.emplace_back(termToSegregate);
        }
        else
        {
            nonMonomials.emplace_back(termToSegregate);
        }
    }
}

void segregatePolynomialAndNonPolynomials(
        Terms const& termsToSegregate,
        Terms & polynomials,
        Terms & nonPolynomials)
{
    for(Term const& termToSegregate : termsToSegregate)
    {
        if(canBeConvertedToPolynomial(termToSegregate))
        {
            polynomials.emplace_back(termToSegregate);
        }
        else
        {
            nonPolynomials.emplace_back(termToSegregate);
        }
    }
}

void segregateNonExpressionsAndExpressions(
        TermsWithDetails const& termsToSegregate,
        TermsWithDetails & termsWithNonExpressions,
        TermsWithDetails & termsWithExpressions)
{
    for(TermWithDetails const& termToSegregate : termsToSegregate)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termToSegregate.baseTermSharedPointer));
        if(term.isExpression())
        {
            termsWithExpressions.emplace_back(termToSegregate);
        }
        else if(isNonEmptyOrNonOperatorOrNonExpressionType(term))
        {
            termsWithNonExpressions.emplace_back(termToSegregate);
        }
    }
}

void segregateTermsWithPositiveAndNegativeAssociations(
        TermsWithDetails const& termsToSegregate,
        TermsWithDetails & termsWithPositiveAssociation,
        TermsWithDetails & termsWithNegativeAssociation)
{
    for(TermWithDetails const& termToSegregate : termsToSegregate)
    {
        if(termToSegregate.hasPositiveAssociation())
        {
            termsWithPositiveAssociation.emplace_back(termToSegregate);
        }
        else
        {
            termsWithNegativeAssociation.emplace_back(termToSegregate);
        }
    }
}

void segregateTermsWithAndWithoutVariable(
        TermsWithDetails const& termsToSegregate,
        std::string const& variableName,
        TermsWithDetails & termsWithVariable,
        TermsWithDetails & termsWithoutVariable)
{
    for(TermWithDetails const& termToSegregate : termsToSegregate)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termToSegregate.baseTermSharedPointer));
        if(isVariableFoundInTerm(term, variableName))
        {
            termsWithVariable.emplace_back(termToSegregate);
        }
        else
        {
            termsWithoutVariable.emplace_back(termToSegregate);
        }
    }
}

}

}