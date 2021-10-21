#include "Integration.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Functions/FunctionUtilities.hpp>
#include <Algebra/Integration/IntegrationUtilities.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Substitution/SubstitutionOfTermsToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>


#include <Debug/AlbaDebug.hpp>

using namespace alba::algebra::Functions;
using namespace alba::algebra::Simplification;
using namespace std;
namespace alba
{
namespace algebra
{

Integration::Integration(
        string const& nameOfVariableToIntegrate)
    : m_nameOfVariableToIntegrate(nameOfVariableToIntegrate)
    , m_isIntegrationUsingSubstitutionAllowed(true)
    , m_isIntegrationByPartsAllowed(true)
{}

Term Integration::integrate(
        Term const& term) const
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

Term Integration::integrate(        Constant const& constant) const
{
    return Term(integrateConstant(constant));
}

Term Integration::integrate(
        Variable const& variable) const
{
    Term result(integrateVariable(variable));
    result.simplify();
    return result;
}

Term Integration::integrate(
        Monomial const& monomial) const
{
    Term result(integrateMonomial(monomial));
    result.simplify();
    return result;
}

Term Integration::integrate(
        Polynomial const& polynomial) const
{
    Term result(integratePolynomial(polynomial));
    result.simplify();
    return result;
}

Term Integration::integrate(
        Expression const& expression) const
{
    return integrateExpression(expression);
}

Term Integration::integrate(
        Function const& functionObject) const
{
    return integrateFunction(functionObject);
}

Term Integration::integrateWithPlusC(
        Term const& term) const
{
    Term result(createExpressionIfPossible({integrate(term), Term("+"), Term(C)}));
    finalizeTermForIntegration(result);
    return result;
}
Term Integration::integrateWithDefiniteValues(
        Term const& term,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval) const
{
    return substituteValuesAndGetDifference(
                integrate(term),
                m_nameOfVariableToIntegrate,
                lowerValueInInterval,
                higherValueInInterval);
}

Monomial Integration::integrateConstant(
        Constant const& constant) const
{    return Monomial(constant.getNumberConstReference(), {{m_nameOfVariableToIntegrate, 1}});
}

Monomial Integration::integrateVariable(
        Variable const& variable) const
{
    Monomial result;
    string const& nameOfVariable(variable.getVariableName());
    if(isVariableToIntegrate(nameOfVariable))
    {
        result = Monomial(AlbaNumber::createFraction(1, 2), {{variable.getVariableName(), 2}});
    }
    else
    {
        result = Monomial(1, {{variable.getVariableName(), 1}, {m_nameOfVariableToIntegrate, 1}});
    }
    return result;
}

Term Integration::integrateMonomial(
        Monomial const& monomial) const
{
    Term result;
    AlbaNumber exponentForVariable = monomial.getExponentForVariable(m_nameOfVariableToIntegrate);
    if(exponentForVariable == -1)
    {
        result = Term(integrateMonomialWhenExponentIsNegativeOne(monomial));
    }
    else
    {
        result = Term(integrateMonomialWhenExponentIsNotNegativeOne(monomial));
    }
    result.simplify();
    return result;
}

Term Integration::integratePolynomial(
        Polynomial const& polynomial) const
{
    Term result;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        result = result + integrateMonomial(monomial);
    }
    result.simplify();
    return result;
}

Term Integration::integrateExpression(
        Expression const& expression) const
{
    Term result(integrateAsTermOrExpressionIfNeeded(expression));
    finalizeTermForIntegration(result);
    return result;
}
Term Integration::integrateFunction(
        Function const& functionObject) const
{
    Term result(integrateFunctionOnly(functionObject));
    finalizeTermForIntegration(result);
    return result;
}
Term Integration::integrateMonomialWhenExponentIsNegativeOne(
        Monomial const& monomial) const
{
    Monomial retainedMonomial(monomial);
    retainedMonomial.putVariableWithExponent(m_nameOfVariableToIntegrate, 0);
    Term result = retainedMonomial * getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(m_nameOfVariableToIntegrate));
    return result;
}

Monomial Integration::integrateMonomialWhenExponentIsNotNegativeOne(
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
    return result;
}

Term Integration::integrateFunctionOnly(
        Function const& functionObject) const
{
    Term result;
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    if(wouldDifferentiationYieldToAConstant(inputTerm))
    {
        if("abs" == functionObject.getFunctionName())
        {
            result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
        }
        else if("sin" == functionObject.getFunctionName())
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(createExpressionIfPossible({Term(-1), Term("*"), cos(inputTerm)})), inputTerm);
        }
        else if("cos" == functionObject.getFunctionName())
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(sin(inputTerm)), inputTerm);
        }
        else if("tan" == functionObject.getFunctionName())
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(sec(inputTerm)));
        }
        else if("csc" == functionObject.getFunctionName())
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(csc(inputTerm)) - Term(cot(inputTerm)));
        }
        else if("sec" == functionObject.getFunctionName())
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(sec(inputTerm)) + Term(tan(inputTerm)));
        }
        else if("cot" == functionObject.getFunctionName())
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(sin(inputTerm)));
        }
        else if("sinh" == functionObject.getFunctionName())
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(cosh(inputTerm)), inputTerm);
        }
        else if("cosh" == functionObject.getFunctionName())
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(sinh(inputTerm)), inputTerm);
        }
    }
    if(result.isEmpty())
    {
        integrateTermUsingSubstitutionWithMaxDepth(result, Term(functionObject), getConfigurationWithFactors());
    }
    if(result.isEmpty())
    {
        integrateUsingIntegrationByParts(result, Term(functionObject));
    }
    if(result.isEmpty())
    {
        result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
    return result;
}

void Integration::integrateRecognizedFunctionsSquared(
        Term & result,
        Term const& functionTerm) const
{
    Function const& functionObject(functionTerm.getFunctionConstReference());
    Term const& inputOfFunctionTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    if(wouldDifferentiationYieldToAConstant(inputOfFunctionTerm))
    {
        if(functionObject.getFunctionName() == "sec")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(tan(inputOfFunctionTerm)), inputOfFunctionTerm);
        }
        else if(functionObject.getFunctionName() == "csc")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(createExpressionIfPossible(
            {Term(cot(inputOfFunctionTerm)), Term("*"), Term(-1)}), inputOfFunctionTerm);
        }
        else if(functionObject.getFunctionName() == "sech")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(tanh(inputOfFunctionTerm)), inputOfFunctionTerm);
        }
        else if(functionObject.getFunctionName() == "csch")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(createExpressionIfPossible(
            {Term(coth(inputOfFunctionTerm)), Term("*"), Term(-1)}), inputOfFunctionTerm);
        }
    }
}

Term Integration::integrateAsTermOrExpressionIfNeeded(
        Expression const& expression) const
{
    Term result;
    Configurations configurations{getConfigurationWithFactors(), getConfigurationWithCommonDenominator()};
    for(Configuration const& configuration : configurations)
    {
        Term simplifiedTerm(expression);
        simplifyForIntegration(simplifiedTerm, configuration);
        if(simplifiedTerm.isExpression())
        {
            integrateSimplifiedExpressionOnly(result, simplifiedTerm.getExpressionConstReference(), configuration);
        }
        else
        {
            result = integrate(simplifiedTerm);
        }
        if(!result.isEmpty())
        {
            break;
        }
    }
    if(result.isEmpty())
    {
        result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
    return result;
}

void Integration::integrateSimplifiedExpressionOnly(
        Term & result,
        Expression const& expression,
        Configuration const& configuration) const
{
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        integrateTermsInAdditionOrSubtraction(result, termsWithDetails);
    }
    else if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        integrateTermsInMultiplicationOrDivision(result, termsWithDetails);
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        integrateTermsInRaiseToPower(result, termsWithDetails);
    }
    if(result.isEmpty())
    {
        integrateTermUsingSubstitutionWithMaxDepth(result, Term(expression), configuration);
    }
    if(result.isEmpty())
    {
        integrateUsingIntegrationByParts(result, Term(expression));
    }
}

void Integration::integrateTermsInAdditionOrSubtraction(
        Term & result,
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
    result = Term(accumulatedExpression);
}

void Integration::integrateTermsInMultiplicationOrDivision(
        Term & result,
        TermsWithDetails const& termsWithDetails) const
{
    integrateByProcessingAsPolynomialsOverPolynomials(
                result,
                Term(Expression(OperatorLevel::MultiplicationAndDivision, termsWithDetails)));
    integrateByTryingTwoTermsInMultiplicationAndDivision(result, termsWithDetails);
}

void Integration::integrateTermsInRaiseToPower(
        Term & result,
        TermsWithDetails const& termsWithDetails) const
{
    TermRaiseToTerms termRaiseToTerms(termsWithDetails);
    termRaiseToTerms.simplify();
    Term firstTerm(termRaiseToTerms.getBase());
    Term secondTerm(termRaiseToTerms.getCombinedExponents());
    if(firstTerm.isConstant())
    {
        integrateConstantRaiseToTerm(result, firstTerm.getConstantValueConstReference(), secondTerm);
    }
    else if(secondTerm.isConstant())
    {
        integrateTermRaiseToConstant(result, firstTerm, secondTerm.getConstantValueConstReference());
    }
    else
    {
        integrateTermRaiseToTerm(result, firstTerm, secondTerm);
    }
}

void Integration::integrateConstantRaiseToTerm(
        Term & result,
        AlbaNumber const& base,
        Term const& exponent) const
{
    if(wouldDifferentiationYieldToAConstant(exponent))
    {
        result = divideFirstTermAndDerivativeOfSecondTerm(Term(createExpressionIfPossible(
        {Term(base), Term("^"), exponent, Term("/"), Term(ln(Term(base)))})), exponent);
    }
}

void Integration::integrateTermRaiseToConstant(
        Term & result,
        Term const& base,
        AlbaNumber const& exponent) const
{
    if(wouldDifferentiationYieldToAConstant(base))
    {
        result = divideFirstTermAndDerivativeOfSecondTerm(Term(createExpressionIfPossible(
        {base, Term("^"), Term(exponent+1), Term("/"), Term(exponent+1)})), base);
    }
    else if(base.isFunction() && exponent == 2)
    {
        integrateRecognizedFunctionsSquared(result, base);
    }
}

void Integration::integrateTermRaiseToTerm(
        Term & result,
        Term const& ,
        Term const& ) const
{
    result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
}

void Integration::integrateTermUsingSubstitutionWithMaxDepth(
        Term & result,
        Term const& term,
        Configuration const& configuration) const
{
    if(m_isIntegrationUsingSubstitutionAllowed)
    {
        constexpr unsigned int MAX_DEPTH=2;
        static unsigned int depth=0;
        depth++;
        if(depth <= MAX_DEPTH)
        {
            integrateTermUsingSubstitution(result, term, configuration);
        }
        depth--;
    }
}

void Integration::integrateTermUsingSubstitution(
        Term & result,
        Term const& term,
        Configuration const& configuration) const
{
    Term simplifiedTerm(term);
    simplifyForIntegration(simplifiedTerm, configuration);
    Terms subTerms(retrieveSubTerms(simplifiedTerm));
    for(Term const& subTerm : subTerms)
    {
        if(!subTerm.isConstant() && !subTerm.isVariable())
        {
            integrateBySubstitutionAndUsingANewVariable(result, simplifiedTerm, subTerm, configuration);
            if(!result.isEmpty())
            {
                break;
            }
        }
    }
}

void Integration::integrateBySubstitutionAndUsingANewVariable(
        Term & result,
        Term const& mainTerm,
        Term const& termToSubstituteToVariable,
        Configuration const& configuration) const
{
    Differentiation differentiation(m_nameOfVariableToIntegrate);
    Term firstDerivative(differentiation.differentiate(termToSubstituteToVariable));
    Term termToIntegrate = mainTerm/firstDerivative;
    Term termToIntegrateWithNewVariable(getTermWithNewVariableSubstitution(termToIntegrate, termToSubstituteToVariable));
    simplifyForIntegration(termToIntegrateWithNewVariable, configuration);
    if(isVariableToIntegrateNotFoundInTerm(termToIntegrateWithNewVariable))
    {
        string newVariableName(createVariableNameForSubstitution(termToSubstituteToVariable));
        Integration integrationWithNewVariable(newVariableName);
        Term integratedTermWithNewVariable(integrationWithNewVariable.integrate(termToIntegrateWithNewVariable));
        SubstitutionOfVariablesToTerms substitutionVariableToTerm({{newVariableName, termToSubstituteToVariable}});
        Term integratedTerm(substitutionVariableToTerm.performSubstitutionTo(integratedTermWithNewVariable));
        if(!isNotANumber(integratedTerm))        {
            result = integratedTerm;
        }
    }
}

Term Integration::getTermWithNewVariableSubstitution(
        Term const& mainTerm,
        Term const& termToSubstituteWithVariable) const
{
    string newVariableName(createVariableNameForSubstitution(termToSubstituteWithVariable));
    Term newVariable(newVariableName);
    SubstitutionOfTermsToTerms substitutionTermToNewVariable({{termToSubstituteWithVariable, newVariable}});
    Term termWithNewVariable(substitutionTermToNewVariable.performSubstitutionTo(mainTerm));

    if(termToSubstituteWithVariable.isPolynomial()
            || termToSubstituteWithVariable.isExpression()
            || termToSubstituteWithVariable.isFunction())
    {
        Term leftHandSide(newVariable);
        Term rightHandSide(termToSubstituteWithVariable);
        if(rightHandSide.isFunction() && isLogarithmicFunction(rightHandSide.getFunctionConstReference()))
        {
            Function const& functionObject(rightHandSide.getFunctionConstReference());
            if("log" == functionObject.getFunctionName())
            {
                leftHandSide = Term(createExpressionIfPossible({Term(10), Term("^"), leftHandSide}));
            }
            else if("ln" == functionObject.getFunctionName())
            {
                leftHandSide = Term(createExpressionIfPossible({getEAsTerm(), Term("^"), leftHandSide}));
            }
            rightHandSide = getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference());
        }
        IsolationOfOneVariableOnEqualityEquation isolation(Equation(leftHandSide, "=", rightHandSide));
        Term termWithOldVariable;
        Term termWithWithoutOldVariable;
        isolation.isolateTermWithVariable(m_nameOfVariableToIntegrate, termWithOldVariable, termWithWithoutOldVariable);        if(canBeConvertedToMonomial(termWithOldVariable))
        {
            Monomial monomialWithOldVariable(createMonomialIfPossible(termWithOldVariable));
            AlbaNumber exponentForOldVariable(monomialWithOldVariable.getExponentForVariable(m_nameOfVariableToIntegrate));
            monomialWithOldVariable.putVariableWithExponent(m_nameOfVariableToIntegrate, AlbaNumber(0));
            Term isolatedTermWithNewVariable((termWithWithoutOldVariable/monomialWithOldVariable)^(AlbaNumber(1)/exponentForOldVariable));
            SubstitutionOfVariablesToTerms substitutionVariableToTerm({{m_nameOfVariableToIntegrate, isolatedTermWithNewVariable}});
            termWithNewVariable = substitutionVariableToTerm.performSubstitutionTo(termWithNewVariable);
        }
    }
    return termWithNewVariable;
}

void Integration::integrateByTryingTwoTermsInMultiplicationAndDivision(
        Term & result,
        TermsWithDetails const& termsWithDetailsInMultiplicationAndDivision) const
{
    unsigned int numberOfTerms(termsWithDetailsInMultiplicationAndDivision.size());
    for(unsigned int i=0; result.isEmpty() && i<numberOfTerms; i++)
    {
        TermsWithDetails termsInFirstTerms(termsWithDetailsInMultiplicationAndDivision);
        termsInFirstTerms.erase(termsInFirstTerms.cbegin() + i);
        Term firstTerm(Expression(OperatorLevel::MultiplicationAndDivision, termsInFirstTerms));
        Term secondTerm(Expression(OperatorLevel::MultiplicationAndDivision, {termsWithDetailsInMultiplicationAndDivision.at(i)}));
        Term innerTermInFirstTerm;
        firstTerm.simplify();
        secondTerm.simplify();
        if(!firstTerm.isConstant() && !secondTerm.isConstant())
        {
            findInnerAndOuterTermForChainRule(innerTermInFirstTerm, firstTerm);
            if(!innerTermInFirstTerm.isEmpty())
            {
                integrateUsingChainRuleInReverseIfPossible(result, firstTerm, innerTermInFirstTerm, secondTerm);
            }
        }
    }
}

void Integration::integrateUsingChainRuleInReverseIfPossible(
        Term & result,
        Term const& firstOuterTerm,
        Term const& firstInnerTerm,
        Term const& secondTerm) const
{
    Differentiation differentiation(m_nameOfVariableToIntegrate);
    Term firstTermDerivative(differentiation.differentiate(firstInnerTerm));
    Term quotientOfDerivatives = firstTermDerivative/secondTerm;
    if(quotientOfDerivatives.isConstant())
    {
        string newVariableToIntegrate(createVariableNameForSubstitution(firstInnerTerm));
        SubstitutionOfTermsToTerms substitutionTermToVariable({{firstInnerTerm, Term(newVariableToIntegrate)}});
        Term newFirstOuterTerm(substitutionTermToVariable.performSubstitutionTo(firstOuterTerm));
        Integration integrationWithNewVariable(newVariableToIntegrate);
        Term integratedOuterTermInNewVariable(integrationWithNewVariable.integrate(newFirstOuterTerm));
        SubstitutionOfVariablesToTerms substitutionVariableToTerm({{newVariableToIntegrate, firstInnerTerm}});
        Term integratedOuterTerm(substitutionVariableToTerm.performSubstitutionTo(integratedOuterTermInNewVariable));
        result = integratedOuterTerm / quotientOfDerivatives;    }
}

void Integration::findInnerAndOuterTermForChainRule(
        Term & innerTerm,
        Term & outerTerm) const
{
    if(outerTerm.isFunction())
    {
        innerTerm = getTermConstReferenceFromBaseTerm(outerTerm.getFunctionConstReference().getInputTermConstReference());
    }
    else if(outerTerm.isExpression())
    {
        Expression const& expression(outerTerm.getExpressionConstReference());
        if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
        {
            TermRaiseToTerms termRaiseToTerms(expression.getTermsWithAssociation().getTermsWithDetails());
            Term base(termRaiseToTerms.getBase());
            Term exponent(termRaiseToTerms.getCombinedExponents());
            Term combinedBaseAndExponent(termRaiseToTerms.getCombinedTerm());
            if(exponent.isConstant())
            {
                outerTerm = combinedBaseAndExponent;
                innerTerm = base;
            }
            else if(base.isConstant())
            {
                outerTerm = combinedBaseAndExponent;
                innerTerm = exponent;
            }
        }
        else
        {
            TermRaiseToANumber oldTermRaiseToANumber(createTermRaiseToANumberFromExpression(expression));
            if(oldTermRaiseToANumber.getExponent() != 1)
            {
                outerTerm = oldTermRaiseToANumber.getCombinedTerm();
                innerTerm = oldTermRaiseToANumber.getBase();
            }
        }
    }
}

Term Integration::divideFirstTermAndDerivativeOfSecondTerm(
        Term const& firstTerm,
        Term const& secondTerm) const
{
    Differentiation differentiation(m_nameOfVariableToIntegrate);
    return Term(createExpressionIfPossible({firstTerm, Term("/"), differentiation.differentiate(secondTerm)}));
}

void Integration::integrateByProcessingAsPolynomialsOverPolynomials(
        Term & result,
        Term const& term) const
{
    PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(term));
    if(popOptional.hasContent())
    {
        PolynomialOverPolynomial & pop(popOptional.getReference());
        PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(pop.simplifyAndDivide());
        if(!quotientAndRemainder.quotient.isEmpty()
                && !hasNegativeExponentsWithVariable(quotientAndRemainder.quotient, m_nameOfVariableToIntegrate))
        {
            result = integrate(quotientAndRemainder.quotient)
                    + integrate(Term(quotientAndRemainder.remainder / pop.getDenominator()));
        }
    }
}

void Integration::integrateUsingIntegrationByParts(
        Term & result,
        Term const& term) const
{
    if(m_isIntegrationByPartsAllowed)
    {
        integrateUsingIntegrationByPartsByTermAndOne(result, term);
        if(result.isEmpty())
        {
            integrateUsingIntegrationByPartsByTryingTwoTerms(result, term);
        }
    }
}

void Integration::integrateUsingIntegrationByPartsByTermAndOne(
        Term & result,
        Term const& term) const
{
    bool isAnInverseTrigonometricFunction = term.isFunction()
            && isInverseTrigonometricFunction(term.getFunctionConstReference());
    if(isAnInverseTrigonometricFunction)
    {
        integrateUsingIntegrationByParts(result, term, term, Term(1));
    }
}

void Integration::integrateUsingIntegrationByPartsByTryingTwoTerms(
        Term & result,
        Term const& term) const
{
    if(term.isExpression())
    {
        Expression const& expression(term.getExpressionConstReference());
        if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
        {
            TermsWithDetails const& termsWithDetailsInMultiplicationAndDivision(expression.getTermsWithAssociation().getTermsWithDetails());
            unsigned int numberOfTerms(termsWithDetailsInMultiplicationAndDivision.size());
            for(unsigned int i=0; result.isEmpty() && i<numberOfTerms; i++)
            {
                TermsWithDetails termsInFirstTerms(termsWithDetailsInMultiplicationAndDivision);
                termsInFirstTerms.erase(termsInFirstTerms.cbegin() + i);
                Term firstTerm(Expression(OperatorLevel::MultiplicationAndDivision, termsInFirstTerms));
                Term secondTerm(Expression(OperatorLevel::MultiplicationAndDivision, {termsWithDetailsInMultiplicationAndDivision.at(i)}));
                firstTerm.simplify();
                secondTerm.simplify();
                if(!firstTerm.isConstant() && !secondTerm.isConstant())
                {
                    if(result.isEmpty())
                    {
                        integrateUsingIntegrationByPartsByTryingTwoTermsWithDifferentOrder(result, term, firstTerm, secondTerm);
                    }
                }
            }
        }
    }
}

void Integration::integrateUsingIntegrationByPartsByTryingTwoTermsWithDifferentOrder(
        Term & result,
        Term const& term,
        Term const& firstTerm,
        Term const& secondTerm) const
{
    integrateUsingIntegrationByParts(result, term, firstTerm, secondTerm);
    if(result.isEmpty())
    {
        integrateUsingIntegrationByParts(result, term, secondTerm, firstTerm);
    }
}

void Integration::integrateUsingIntegrationByParts(
        Term & result,
        Term const& term,
        Term const& u,
        Term const& dv) const
{
    // use static equations here to solve when recursion happens
    // use static depth here to determine when to clear
    static ListOfIntegrationByPartsTerms listOfIntegrationByPartsTerms;
    static unsigned int depth=0;
    depth++;


    constexpr unsigned int MAX_SIZE=5;
    if(listOfIntegrationByPartsTerms.size() == MAX_SIZE){return;}

    integrateUsingPreviousIntegrationByPartsTerms(result, listOfIntegrationByPartsTerms, term);
    if(!result.isEmpty()){return;}

    Integration integration(m_nameOfVariableToIntegrate);
    if(!hasExponentialExpression(u))
    {
        Term v(integration.integrate(dv));
        if(!isNotANumber(v))        {
            Differentiation differentiation(m_nameOfVariableToIntegrate);
            Term du(differentiation.differentiate(u));
            if(!isNotANumber(du))
            {
                Term uTimesV(u*v);
                Term vTimesDu(v*du);
                uTimesV.simplify();
                vTimesDu.simplify();
                listOfIntegrationByPartsTerms.emplace_back(IntegrationByPartsTerms{term, uTimesV, vTimesDu});
                Term integratedVTimesDu(integration.integrate(vTimesDu));
                if(!isNotANumber(integratedVTimesDu))
                {
                    result = uTimesV - integratedVTimesDu;
                }
            }
        }
    }


    depth--;
    if(depth == 0)
    {
        listOfIntegrationByPartsTerms.clear();
    }
}

void Integration::integrateUsingPreviousIntegrationByPartsTerms(
        Term & result,
        ListOfIntegrationByPartsTerms const& listOfIntegrationByPartsTerms,
        Term const& termToIntegrate) const
{
    Term currentTermToIntegrate(termToIntegrate);
    ListOfIntegrationByPartsTerms termsToAnalyze(listOfIntegrationByPartsTerms);
    Term accumulatedUTimesV;
    AlbaNumber accumulatedCoefficient(1);
    bool didAccumulationUpdated(false);
    bool isChanged(true);
    while(isChanged)
    {
        isChanged = false;
        for(unsigned int i=0; i<termsToAnalyze.size(); i++)
        {
            IntegrationByPartsTerms const& integrationByPartsTerms(termsToAnalyze.at(i));
            Term quotient(currentTermToIntegrate/integrationByPartsTerms.vTimesDuToIntegrate);
            quotient.simplify();
            if(quotient.isConstant())
            {
                currentTermToIntegrate = integrationByPartsTerms.uTimesDvToIntegrate;
                accumulatedUTimesV = integrationByPartsTerms.uTimesV - (quotient * accumulatedUTimesV);
                accumulatedCoefficient = AlbaNumber(-1) * quotient.getConstantValueConstReference() * accumulatedCoefficient;
                isChanged = true;
                didAccumulationUpdated = true;
                termsToAnalyze.erase(termsToAnalyze.begin()+i);
                break;
            }
        }
    }
    Term ratio(termToIntegrate/currentTermToIntegrate);
    ratio.simplify();
    if(didAccumulationUpdated && ratio.isConstant())
    {
        result = accumulatedUTimesV * ratio / Term(accumulatedCoefficient+1);
        result.simplify();
    }
}

void Integration::setIsIntegrationUsingSubstitutionAllowed(
        bool const isIntegrationUsingSubstitutionAllowed)
{
    m_isIntegrationUsingSubstitutionAllowed = isIntegrationUsingSubstitutionAllowed;
}

void Integration::setIsIntegrationByPartsAllowed(
        bool const isIntegrationByPartsAllowed)
{
    m_isIntegrationByPartsAllowed = isIntegrationByPartsAllowed;
}

void Integration::simplifyForIntegration(
        Term & term,
        Configuration const& configuration) const
{
    term.simplify();
    {
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configuration);

        term.simplify();
    }
}

void Integration::finalizeTermForIntegration(
        Term & term) const
{
    simplifyForIntegration(term, getConfigurationWithFactors());
}

Integration::Configuration Integration::getConfigurationWithFactors() const
{
    Configuration configurationDetails(                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyToFactors = true;
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    return configurationDetails;
}

Integration::Configuration Integration::getConfigurationWithCommonDenominator() const
{
    Configuration configurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyToFactors = true;
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    return configurationDetails;
}

bool Integration::isVariableToIntegrate(string const& variableName) const
{
    return variableName == m_nameOfVariableToIntegrate;
}

bool Integration::isVariableToIntegrateNotFoundInTerm(Term const& term) const
{
    return !isVariableFoundInTerm(term, m_nameOfVariableToIntegrate);
}

bool Integration::wouldDifferentiationYieldToAConstant(        Term const& term) const
{
    bool result(0);
    if(term.isVariable() && isVariableToIntegrate(term.getVariableConstReference().getVariableName()))
    {
        result = true;
    }
    else if(term.isMonomial())
    {
        result = term.getMonomialConstReference().getExponentForVariable(m_nameOfVariableToIntegrate) == 1;
    }
    else if(term.isPolynomial())
    {
        result = term.getPolynomialConstReference().getDegreeForVariable(m_nameOfVariableToIntegrate) == 1;
    }
    return result;
}

}

}
