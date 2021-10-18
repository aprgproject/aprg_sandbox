#include "ConstructUtilities.hpp"

#include <Algebra/Constructs/PolynomialRaiseToAnUnsignedInt.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <Optional/AlbaOptional.hpp>

using namespace alba::algebra::Simplification;
using namespace alba::mathHelper;
using namespace std;

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
        Expression const& expression(simplifiedTerm.getExpressionConstReference());
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
        Expression const& expression(simplifiedTerm.getExpressionConstReference());
        if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
        {
            result = TermsOverTerms(expression.getTermsWithAssociation().getTermsWithDetails());
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

    if(term.isMonomial())
    {
        result = createTermRaiseToANumberFromMonomial(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        result = createTermRaiseToANumberFromPolynomial(term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        result = createTermRaiseToANumberFromExpression(term.getExpressionConstReference());
    }
    if(result.isEmpty())
    {
        result = TermRaiseToANumber(term, 1);
    }
    result.getBaseReference().simplify();
    return result;
}

TermRaiseToANumber createTermRaiseToANumberFromMonomial(Monomial const& monomial)
{
    Monomial newMonomial(monomial);
    Monomial::VariablesToExponentsMap const& variablesToExponentsMap(
                newMonomial.getVariablesToExponentsMapConstReference());
    AlbaNumber exponent = (variablesToExponentsMap.size() == 1)
            ? (variablesToExponentsMap.cbegin())->second
            : getGcfOfExponentsInMonomial(newMonomial);
    newMonomial.raiseToPowerNumber(AlbaNumber(1)/exponent);
    return TermRaiseToANumber(Term(newMonomial), exponent);
}

TermRaiseToANumber createTermRaiseToANumberFromPolynomial(Polynomial const& polynomial)
{
    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomial);
    return TermRaiseToANumber(Term(polynomialRaiseToAnUnsignedInt.getBase()), polynomialRaiseToAnUnsignedInt.getExponent());
}

TermRaiseToANumber createTermRaiseToANumberFromExpression(Expression const& expression)
{
    TermRaiseToANumber result;
    if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        createTermRaiseToANumberFromRaiseToPowerExpression(result, expression);
    }
    else if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        createTermRaiseToANumberFromMultiplicationAndDivisionExpression(result, expression);
    }
    return result;
}

void createTermRaiseToANumberFromRaiseToPowerExpression(
        TermRaiseToANumber & result,
        Expression const& expression)
{
    TermsWithDetails raiseToPowerTerms(expression.getTermsWithAssociation().getTermsWithDetails());
    if(raiseToPowerTerms.size() == 1)
    {
        Term const& base(getTermConstReferenceFromSharedPointer(raiseToPowerTerms.back().baseTermSharedPointer));
        result = TermRaiseToANumber(base, 1);
    }
    else if(raiseToPowerTerms.size() >= 2)
    {
        AlbaNumber combinedExponentValue(1);
        bool isFirst(true);
        for(TermWithDetails & raiseToPowerTerm : raiseToPowerTerms)
        {
            if(isFirst)
            {
               isFirst = false;
            }
            else
            {
                Term & exponentTerm(getTermReferenceFromSharedPointer(raiseToPowerTerm.baseTermSharedPointer));
                if(exponentTerm.isConstant())
                {
                    combinedExponentValue = combinedExponentValue * exponentTerm.getConstantValueConstReference();
                    exponentTerm.getConstantReference().setNumber(1);
                }
                else if(exponentTerm.isMonomial())
                {
                    combinedExponentValue = combinedExponentValue * exponentTerm.getMonomialConstReference().getConstantConstReference();
                    exponentTerm.getMonomialReference().setConstant(1);
                }
            }
        }

        Expression newBaseExpression;
        newBaseExpression.setCommonOperatorLevel(OperatorLevel::RaiseToPower);
        newBaseExpression.putTermsWithDetails(raiseToPowerTerms);
        Term newBase(newBaseExpression);
        newBase.simplify();
        result = TermRaiseToANumber(newBase, combinedExponentValue);
        // how about if exponent is polynomial or expression? how do we extract constant? should we introduce factorization here?
    }
}

void createTermRaiseToANumberFromMultiplicationAndDivisionExpression(
        TermRaiseToANumber & result,
        Expression const& expression)
{
    TermsOverTerms originalTot(createTermsOverTermsFromTerm(Term(expression)));
    originalTot.setAsShouldSimplifyToFactors(true);
    originalTot.setAsShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(true);
    TermsOverTerms::BaseToExponentMap baseToExponentMap;
    TermsOverTerms::BaseToExponentMap newBaseToExponentMap;
    originalTot.retrieveBaseToExponentMap(baseToExponentMap);

    AlbaNumber commonExponent;
    bool isFirst(true);
    for(auto const& baseExponentPair : baseToExponentMap)
    {
        Term const& term(baseExponentPair.first);
        AlbaNumber const& exponent(baseExponentPair.second);
        if(term.isMonomial())
        {
            TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromMonomial(term.getMonomialConstReference()));
            newBaseToExponentMap.emplace(termRaiseToANumber.getBase(), termRaiseToANumber.getExponent());
        }
        else
        {
            newBaseToExponentMap.emplace(term, exponent);
        }
    }
    bool areAllExponentsNegative(true);
    for(auto const& baseExponentPair : newBaseToExponentMap)
    {
        AlbaNumber const& exponent(baseExponentPair.second);
        if(exponent > 0)
        {
            areAllExponentsNegative = false;
        }
        if(isFirst)
        {
            commonExponent = exponent;
            isFirst=false;
        }
        else
        {
            commonExponent = getGreatestCommonFactorForAlbaNumber(commonExponent, exponent);
        }
    }
    if(areAllExponentsNegative && commonExponent > 0)
    {
        commonExponent *= -1;
    }
    for(auto & baseExponentPair : newBaseToExponentMap)
    {
        baseExponentPair.second = baseExponentPair.second/commonExponent;
    }
    TermsOverTerms totWithoutCommonExponent;
    totWithoutCommonExponent.setAsShouldSimplifyToFactors(true);
    totWithoutCommonExponent.setAsShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(true);
    totWithoutCommonExponent.saveBaseToExponentMap(newBaseToExponentMap);
    result = TermRaiseToANumber(totWithoutCommonExponent.getCombinedTerm(), commonExponent);
}

}

}
