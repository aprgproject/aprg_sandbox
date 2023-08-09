#include "IntegrationForFiniteCalculus.hpp"

#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/IntegrationUtilities.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace alba::algebra::Functions;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{
namespace algebra
{

IntegrationForFiniteCalculus::IntegrationForFiniteCalculus(
        string const& nameOfVariableToIntegrate)
    : m_nameOfVariableToIntegrate(nameOfVariableToIntegrate)
{}

Term IntegrationForFiniteCalculus::integrate(
        Term const& term) const
{
    return integrateTerm(term);
}

Term IntegrationForFiniteCalculus::integrate(
        Constant const& constant) const
{
    return Term(integrateConstant(constant));
}

Term IntegrationForFiniteCalculus::integrate(
        Variable const& variable) const
{
    Term result(integrateVariable(variable));
    result.simplify();
    return result;
}

Term IntegrationForFiniteCalculus::integrate(
        Monomial const& monomial) const
{
    Term result(integrateMonomial(monomial));
    result.simplify();
    return result;
}

Term IntegrationForFiniteCalculus::integrate(
        Polynomial const& polynomial) const
{
    Term result(integratePolynomial(polynomial));
    result.simplify();
    return result;
}

Term IntegrationForFiniteCalculus::integrate(
        Expression const& expression) const
{
    return integrateExpression(expression);
}

Term IntegrationForFiniteCalculus::integrate(
        Function const& functionObject) const
{
    return integrateFunction(functionObject);
}

Term IntegrationForFiniteCalculus::integrateWithPlusC(
        Term const& term) const
{
    Term result(createExpressionIfPossible({integrateTerm(term), Term("+"), Term(C)}));
    result.simplify();
    return result;
}

Term IntegrationForFiniteCalculus::integrateAtDefiniteValues(
        Term const& term,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval) const
{
    return evaluateValuesAndGetDifference(
                integrateTerm(term),
                m_nameOfVariableToIntegrate,
                lowerValueInInterval,
                higherValueInInterval);
}

Term IntegrationForFiniteCalculus::integrateTerm(Term const& term) const
{
    Term result;
    if(term.isConstant())
    {
        result = integrate(term.getConstantConstReference());
    }
    else if(term.isVariable())
    {
        result = integrate(term.getVariableConstReference());
    }
    else if(term.isMonomial())
    {
        result = integrate(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        result = integrate(term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        result = integrate(term.getExpressionConstReference());
    }
    else if(term.isFunction())
    {
        result = integrate(term.getFunctionConstReference());
    }
    return result;
}

Monomial IntegrationForFiniteCalculus::integrateConstant(
        Constant const& constant) const
{
    return Monomial(constant.getNumberConstReference(), {{m_nameOfVariableToIntegrate, 1}});
}

Polynomial IntegrationForFiniteCalculus::integrateVariable(
        Variable const& variable) const
{
    Polynomial result;
    string const& nameOfVariable(variable.getVariableName());
    if(isVariableToIntegrate(nameOfVariable))
    {
        result = Polynomial
        {Monomial(AlbaNumber::createFraction(1, 2), {{variable.getVariableName(), 2}}),
                Monomial(AlbaNumber::createFraction(-1, 2), {{variable.getVariableName(), 1}})};
    }
    else
    {
        result = Polynomial{Monomial(1, {{variable.getVariableName(), 1}, {m_nameOfVariableToIntegrate, 1}})};
    }
    return result;
}

Term IntegrationForFiniteCalculus::integrateMonomial(
        Monomial const& monomial) const
{
    Term result;
    AlbaNumber exponent(monomial.getExponentForVariable(m_nameOfVariableToIntegrate));
    if(exponent.isIntegerType())
    {
        int exponentInteger(exponent.getInteger());
        if(exponentInteger >= 0)
        {
            Polynomial polynomialInFallingPower(
                        convertMonomialWithPositiveExponentsFromRegularPowerToFallingPower(monomial));
            Polynomial integratedPolynomialInFallingPower(integratePolynomialInFallingPower(polynomialInFallingPower));
            Polynomial integratedPolynomial(convertPolynomialWithPositiveExponentsFromFallingPowerToRegularPower(integratedPolynomialInFallingPower));
            result = Term(integratedPolynomial);
        }
        else if(exponentInteger == -1)
        {
            // this is special case
            // in infinite calculus this ln(x), but in finite calculus its the summation of 1/x (this is called the harmonic number)
            // for the proof, consider doing the derivative of this

            Monomial retainedMonomial(monomial);
            retainedMonomial.putVariableWithExponent(m_nameOfVariableToIntegrate, 0);
            result = Term(createExpressionIfPossible(
            {Term(retainedMonomial), Term("*"), Term(harmonicNumber(Term(m_nameOfVariableToIntegrate)))}));
            result.simplify();
        }
        else
        {
            AlbaNumber exponentAbsoluteValue(getAbsoluteValueForAlbaNumber(exponent));
            Monomial monomialWithOneLessExponent(monomial);
            monomialWithOneLessExponent.putVariableWithExponent(m_nameOfVariableToIntegrate, exponentAbsoluteValue-1);
            Polynomial denominatorInFallingPower(
                        convertMonomialWithPositiveExponentsFromRegularPowerToFallingPower(monomialWithOneLessExponent));
            Term termToIntegrate(createExpressionIfPossible({Term(1), Term("/"), Term(denominatorInFallingPower)}));
            Term integratedTermInFallingPower(integrateTerm(termToIntegrate));
            if(!isNotANumber(integratedTermInFallingPower)
                    && canBeConvertedToPolynomial(integratedTermInFallingPower))
            {
                Polynomial integratedPolynomial(
                            convertPolynomialWithPositiveExponentsFromFallingPowerToRegularPower(
                                createPolynomialIfPossible(integratedTermInFallingPower)));
                result = Term(integratedPolynomial);
            }
            else
            {
                result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
            }
        }
    }
    else
    {
        result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
    return result;
}

Term IntegrationForFiniteCalculus::integratePolynomial(
        Polynomial const& polynomial) const
{
    Term result;
    bool isFirst(true);
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        if(isFirst)
        {
            result = integrateMonomial(monomial);
            isFirst = false;
        }
        else
        {
            result = result + integrateMonomial(monomial);
        }
    }
    result.simplify();
    return result;
}

Term IntegrationForFiniteCalculus::integrateExpression(
        Expression const& expression) const
{
    return integrateAsTermOrExpressionIfNeeded(expression);
}

Term IntegrationForFiniteCalculus::integrateFunction(
        Function const& ) const
{
    return Term(AlbaNumber(AlbaNumber::Value::NotANumber));
}

Monomial IntegrationForFiniteCalculus::integrateMonomialInFallingPower(
        Monomial const& monomial) const
{
    Monomial result(monomial);
    bool hasVariabletoIntegrate(false);
    for(auto const& variableExponentPair :
        monomial.getVariablesToExponentsMapConstReference())
    {
        string const& variableName(variableExponentPair.first);
        AlbaNumber const& exponent(variableExponentPair.second);
        if(isVariableToIntegrate(variableName))
        {
            result.putVariableWithExponent(variableName, exponent+1);
            result.divideNumber(exponent+1);
            hasVariabletoIntegrate = true;
        }
    }
    if(!hasVariabletoIntegrate)
    {
        result.putVariableWithExponent(m_nameOfVariableToIntegrate, 1);
    }
    result.simplify();
    return result;
}

Polynomial IntegrationForFiniteCalculus::integratePolynomialInFallingPower(
        Polynomial const& polynomial) const
{
    Polynomial result;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        result.addMonomial(integrateMonomialInFallingPower(monomial));
    }
    result.simplify();
    return result;
}

Polynomial IntegrationForFiniteCalculus::convertMonomialWithPositiveExponentsFromRegularPowerToFallingPower(
        Monomial const& monomial) const
{
    Polynomial result;
    int exponent(monomial.getExponentForVariable(m_nameOfVariableToIntegrate).getInteger());
    if(exponent >= 0)
    {
        unsigned int exponentUnsigned = static_cast<unsigned int>(exponent);
        Monomial retainedMonomial(monomial);
        retainedMonomial.putVariableWithExponent(m_nameOfVariableToIntegrate, 0);
        for(unsigned int i=0; i<=exponentUnsigned; i++)
        {
            result.addMonomial(Monomial(getStirlingNumberOfTheSecondKind(exponentUnsigned, i), {{m_nameOfVariableToIntegrate, i}}));
        }
        result.multiplyMonomial(retainedMonomial);
    }
    result.simplify();
    return result;
}

Polynomial IntegrationForFiniteCalculus::convertMonomialWithPositiveExponentsFromFallingPowerToRegularPower(
        Monomial const& monomial) const
{
    Polynomial result;
    int exponent(monomial.getExponentForVariable(m_nameOfVariableToIntegrate).getInteger());
    if(exponent > 0)
    {
        unsigned int exponentUnsigned = static_cast<unsigned int>(exponent);
        result = createPolynomialFromConstant(1);
        Monomial retainedMonomial(monomial);
        retainedMonomial.putVariableWithExponent(m_nameOfVariableToIntegrate, 0);
        for(unsigned int i=0; i<exponentUnsigned; i++)
        {
            result.multiplyPolynomial(Polynomial
            {Monomial(1, {{m_nameOfVariableToIntegrate, 1}}), Monomial(-AlbaNumber(i), {})});
        }
        result.multiplyMonomial(retainedMonomial);
    }
    result.simplify();
    return result;
}

Polynomial IntegrationForFiniteCalculus::convertPolynomialWithPositiveExponentsFromRegularPowerToFallingPower(
        Polynomial const& polynomial) const
{
    Polynomial result;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        result.addPolynomial(convertMonomialWithPositiveExponentsFromRegularPowerToFallingPower(monomial));
    }
    result.simplify();
    return result;
}

Polynomial IntegrationForFiniteCalculus::convertPolynomialWithPositiveExponentsFromFallingPowerToRegularPower(
        Polynomial const& polynomial) const
{
    Polynomial result;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        result.addPolynomial(convertMonomialWithPositiveExponentsFromFallingPowerToRegularPower(monomial));
    }
    result.simplify();
    return result;
}

Term IntegrationForFiniteCalculus::integrateAsTermOrExpressionIfNeeded(
        Expression const& expression) const
{
    Term result;
    Term simplifiedTerm(expression);
    simplifiedTerm.simplify();
    if(simplifiedTerm.isExpression())
    {
        result = integrateSimplifiedExpressionOnly(simplifiedTerm.getExpressionConstReference());
    }
    else
    {
        result = integrate(simplifiedTerm);
    }
    return result;
}

Term IntegrationForFiniteCalculus::integrateSimplifiedExpressionOnly(
        Expression const& expression) const
{
    Term result;
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        result = integrateTermsInAdditionOrSubtraction(expression.getTermsWithAssociation().getTermsWithDetails());
    }
    else if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        result = integrateTermsInMultiplicationOrDivision(expression.getTermsWithAssociation().getTermsWithDetails());
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        result = integrateTermsInRaiseToPower(expression.getTermsWithAssociation().getTermsWithDetails());
    }
    if(result.isEmpty())
    {
        result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
    return result;
}

Term IntegrationForFiniteCalculus::integrateTermsInAdditionOrSubtraction(
        TermsWithDetails const& termsWithDetails) const
{
    Expression accumulatedExpression(createOrCopyExpressionFromATerm(Constant(0)));
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& currentTerm(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        Term integratedTerm(integrate(currentTerm));
        if(termWithDetails.hasPositiveAssociation())
        {
            accumulatedExpression.putTermWithAdditionIfNeeded(integratedTerm);
        }
        else
        {
            accumulatedExpression.putTermWithSubtractionIfNeeded(integratedTerm);
        }
    }
    return Term(accumulatedExpression);
}

Term IntegrationForFiniteCalculus::integrateTermsInMultiplicationOrDivision(
        TermsWithDetails const& ) const
{
    // no impl
    return Term(AlbaNumber(AlbaNumber::Value::NotANumber));
}

Term IntegrationForFiniteCalculus::integrateTermsInRaiseToPower(
        TermsWithDetails const& termsWithDetails) const
{
    Term result;
    TermRaiseToTerms termRaiseToTerms(termsWithDetails);
    termRaiseToTerms.simplify();
    Term firstTerm(termRaiseToTerms.getBase());
    Term secondTerm(termRaiseToTerms.getCombinedExponents());
    bool isFirstAChangingTerm = isChangingTerm(firstTerm);
    bool isSecondAChangingTerm = isChangingTerm(secondTerm);
    if(!isFirstAChangingTerm && !isSecondAChangingTerm)
    {
        result = termRaiseToTerms.getCombinedTerm() * Term(m_nameOfVariableToIntegrate);
    }
    else if(!isFirstAChangingTerm && isSecondAChangingTerm)
    {
        result = integrateNonChangingTermRaiseToChangingTerm(firstTerm, secondTerm);
    }
    else if(isFirstAChangingTerm && !isSecondAChangingTerm)
    {
        result = integrateChangingTermRaiseToNonChangingTerm(firstTerm, secondTerm);
    }
    else
    {
        result = integrateChangingTermRaiseToChangingTerm(firstTerm, secondTerm);
    }
    return result;
}

Term IntegrationForFiniteCalculus::integrateNonChangingTermRaiseToChangingTerm(
        Term const& base,
        Term const& exponent) const
{
    Term result(AlbaNumber(AlbaNumber::Value::NotANumber));
    if(exponent.isVariable())
    {
        result = Term(createExpressionIfPossible({base, Term("^"), exponent, Term("/"), Term(base-Term(1))}));
    }
    return result;
}

Term IntegrationForFiniteCalculus::integrateChangingTermRaiseToNonChangingTerm(
        Term const& ,
        Term const& ) const
{
    return Term(AlbaNumber(AlbaNumber::Value::NotANumber));
}

Term IntegrationForFiniteCalculus::integrateChangingTermRaiseToChangingTerm(
        Term const& ,
        Term const& ) const
{
    return Term(AlbaNumber(AlbaNumber::Value::NotANumber));
}

bool IntegrationForFiniteCalculus::isVariableToIntegrate(
        string const& variableName) const
{
    return variableName == m_nameOfVariableToIntegrate;
}

bool IntegrationForFiniteCalculus::isChangingTerm(
        Term const& term) const
{
    VariableNamesRetriever retriever;
    retriever.retrieveFromTerm(term);
    VariableNamesSet const& variableNames(retriever.getSavedData());
    return any_of(variableNames.cbegin(), variableNames.cend(),
                  [&](string const& variableName)
    {
        return isVariableToIntegrate(variableName);
    });
}


}

}
