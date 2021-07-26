#include "ConstructUtilities.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;
using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace algebra
{

PolynomialOverPolynomial createPolynomialOverPolynomialFromTermIfPossible(
        Term const& term)
{
    PolynomialOverPolynomial result(createPolynomialFromConstant(1), createPolynomialFromConstant(1));
    Term simplifiedTerm(term);
    simplifiedTerm.simplify();
    if(canBeConvertedToPolynomial(simplifiedTerm))
    {
        result=PolynomialOverPolynomial(
                    createPolynomialIfPossible(simplifiedTerm),
                    createPolynomialFromConstant(1));
    }
    else if(simplifiedTerm.isExpression())
    {
        Expression expression(simplifiedTerm.getExpressionConstReference());
        if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
        {
            bool canBeConvertedToPolynomialOverPolynomial(true);
            Polynomial numerator(createPolynomialFromConstant(1));
            Polynomial denominator(createPolynomialFromConstant(1));
            for(TermWithDetails const& termWithDetails
                : expression.getTermsWithAssociation().getTermsWithDetails())
            {
                Term const& termInExpression(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
                if(canBeConvertedToPolynomial(termInExpression))
                {
                    if(termWithDetails.hasPositiveAssociation())
                    {
                        numerator.multiplyPolynomial(createPolynomialIfPossible(termInExpression));
                    }
                    else
                    {
                        denominator.multiplyPolynomial(createPolynomialIfPossible(termInExpression));
                    }
                }
                else
                {
                    canBeConvertedToPolynomialOverPolynomial=false;
                    break;
                }
            }
            if(canBeConvertedToPolynomialOverPolynomial)
            {
                result=PolynomialOverPolynomial(numerator, denominator);
            }
        }
    }
    return result;
}

}

}
