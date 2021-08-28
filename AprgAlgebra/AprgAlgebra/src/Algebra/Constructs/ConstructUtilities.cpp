#include "ConstructUtilities.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>

using namespace std;
using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace algebra
{

PolynomialOverPolynomialOptional createPolynomialOverPolynomialFromTermIfPossible(
        Term const& term)
{
    PolynomialOverPolynomialOptional result;
    Term simplifiedTerm(term);
    simplifiedTerm.simplify();

    if(canBeConvertedToPolynomial(simplifiedTerm))
    {
        result.setConstReference(PolynomialOverPolynomial(createPolynomialIfPossible(simplifiedTerm), createPolynomialFromConstant(1)));
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
                result.setConstReference(PolynomialOverPolynomial(numerator, denominator));
            }
        }
    }
    if(result.hasContent())
    {
        result.getReference().simplify();
    }
    return result;
}

TermsOverTerms createTermsOverTermsFromTerm(Term const& term)
{
    TermsOverTerms result;
    Term simplifiedTerm(term);
    simplifiedTerm.simplify();

    bool isResultUpdatedWithContent(false);
    if(simplifiedTerm.isExpression())
    {
        Expression expression(simplifiedTerm.getExpressionConstReference());
        if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
        {
            TermsWithDetails numerators;
            TermsWithDetails denominators;
            segregateTermsWithPositiveAndNegativeAssociations(expression.getTermsWithAssociation().getTermsWithDetails(), numerators, denominators);
            result = TermsOverTerms(numerators, denominators);
            isResultUpdatedWithContent=true;
        }
    }
    if(!isResultUpdatedWithContent)
    {
        result = TermsOverTerms({simplifiedTerm}, {Term(1)});
    }
    result.simplify();
    return result;
}

TermRaiseToANumber createTermRaiseToANumberFromTerm(Term const& term)
{
    TermRaiseToANumber result;
    Term simplifiedTerm(term);
    simplifiedTerm.simplify();

    bool isResultUpdatedWithContent(false);
    if(simplifiedTerm.isMonomial())
    {
        Monomial newMonomial(simplifiedTerm.getMonomialConstReference());
        AlbaNumber exponent(getGcfOfExponentsInMonomial(newMonomial));
        newMonomial.raiseToPowerNumber(AlbaNumber(1)/exponent);
        result = TermRaiseToANumber(Term(newMonomial), exponent);
        isResultUpdatedWithContent=true;
    }
    else if(simplifiedTerm.isExpression())
    {
        Expression const& expression(simplifiedTerm.getExpressionConstReference());
        if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
        {
            TermsWithDetails raiseToPowerTerms(expression.getTermsWithAssociation().getTermsWithDetails());
            if(raiseToPowerTerms.size() == 1)
            {
                result = TermRaiseToANumber(getTermConstReferenceFromSharedPointer(raiseToPowerTerms.back().baseTermSharedPointer), 1);
                isResultUpdatedWithContent=true;
            }
            else if(raiseToPowerTerms.size() >= 2)
            {
                Term const& exponent(getTermConstReferenceFromSharedPointer(raiseToPowerTerms.back().baseTermSharedPointer));
                if(exponent.isConstant())
                {
                    Term const& base(getTermConstReferenceFromSharedPointer(raiseToPowerTerms.front().baseTermSharedPointer));
                    result = TermRaiseToANumber(base, exponent.getConstantConstReference().getNumberConstReference());
                    isResultUpdatedWithContent=true;
                }
                else if(exponent.isMonomial())
                {
                    Monomial oldExponentMonomial(exponent.getMonomialConstReference());
                    AlbaNumber newExponentValue(oldExponentMonomial.getConstantConstReference());
                    raiseToPowerTerms.pop_back();
                    Expression newBaseExpression;
                    newBaseExpression.setCommonOperatorLevel(OperatorLevel::RaiseToPower);
                    newBaseExpression.putTermsWithDetails(raiseToPowerTerms);
                    oldExponentMonomial.setConstant(1);
                    newBaseExpression.putTermWithRaiseToPowerIfNeeded(Term(oldExponentMonomial));
                    Term newBaseExpressionTerm(newBaseExpression);
                    newBaseExpressionTerm.simplify();
                    result = TermRaiseToANumber(newBaseExpressionTerm, newExponentValue);
                    isResultUpdatedWithContent=true;
                }
                // how about if exponent is polynomial or expression? should we introduce facorization here?
            }
        }
    }
    if(!isResultUpdatedWithContent)
    {
        result = TermRaiseToANumber(simplifiedTerm, 1);
    }
    return result;
}

}

}
