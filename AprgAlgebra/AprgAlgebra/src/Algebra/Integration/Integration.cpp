#include "Integration.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Functions/FunctionUtilities.hpp>
#include <Algebra/KnownExpressionsAndEquations/TrigonometricEquations.hpp>
#include <Algebra/Integration/IntegrationUtilities.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Retrieval/SubTermsRetriever.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfTermsToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace alba::algebra::Functions;
using namespace alba::algebra::Simplification;
using namespace alba::mathHelper;
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

Term Integration::integrate(
        Constant const& constant) const
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
{
    return Monomial(constant.getNumberConstReference(), {{m_nameOfVariableToIntegrate, 1}});
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
        string const& functionName(functionObject.getFunctionName());
        if("abs" == functionName)
        {
            result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
        }
        else if("sin" == functionName)
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(createExpressionIfPossible({Term(-1), Term("*"), cos(inputTerm)})), inputTerm);
        }
        else if("cos" == functionName)
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(sin(inputTerm)), inputTerm);
        }
        else if("tan" == functionName)
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(sec(inputTerm)));
        }
        else if("csc" == functionName)
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(csc(inputTerm)) - Term(cot(inputTerm)));
        }
        else if("sec" == functionName)
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(sec(inputTerm)) + Term(tan(inputTerm)));
        }
        else if("cot" == functionName)
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(sin(inputTerm)));
        }
        else if("sinh" == functionName)
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(cosh(inputTerm)), inputTerm);
        }
        else if("cosh" == functionName)
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
        string const& functionName(functionObject.getFunctionName());
        if(functionName == "sec")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(tan(inputOfFunctionTerm)), inputOfFunctionTerm);
        }
        else if(functionName == "csc")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(createExpressionIfPossible(
            {Term(cot(inputOfFunctionTerm)), Term("*"), Term(-1)}), inputOfFunctionTerm);
        }
        else if(functionName == "sech")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(tanh(inputOfFunctionTerm)), inputOfFunctionTerm);
        }
        else if(functionName == "csch")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(createExpressionIfPossible(
            {Term(coth(inputOfFunctionTerm)), Term("*"), Term(-1)}), inputOfFunctionTerm);
        }
    }
}

void Integration::integrateSinRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Function const& baseTrigFunction,
        unsigned int const exponent) const
{
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(baseTrigFunction.getInputTermConstReference()));
    if(isEven(exponent))
    {
        Term termToIntegrate(1);
        putReducedSineSquaredToDoubleAngleCosineTerms(termToIntegrate, inputTerm, exponent);
        result = integrate(termToIntegrate);
    }
    else
    {
        Term termWithExponent(createExpressionIfPossible({getSineSquaredInCosine(inputTerm), Term("^"), Term(exponent/2)}));
        Term termToIntegrate(createExpressionIfPossible({termWithExponent, Term("*"), Term(baseTrigFunction)}));
        result = integrate(termToIntegrate);
    }
}

void Integration::integrateCosRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Function const& baseTrigFunction,
        unsigned int const exponent) const
{
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(baseTrigFunction.getInputTermConstReference()));
    if(isEven(exponent))
    {
        Term termToIntegrate(1);
        putReducedCosineSquaredToDoubleAngleCosineTerms(termToIntegrate, inputTerm, exponent);
        result = integrate(termToIntegrate);
    }
    else
    {
        Term termWithExponent(createExpressionIfPossible({getCosineSquaredInSine(inputTerm), Term("^"), Term(exponent/2)}));
        Term termToIntegrate(createExpressionIfPossible({termWithExponent, Term("*"), Term(baseTrigFunction)}));
        result = integrate(termToIntegrate);
    }
}

void Integration::integrateCscRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Function const& baseTrigFunction,
        unsigned int const exponent) const
{
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(baseTrigFunction.getInputTermConstReference()));
    if(isEven(exponent))
    {
        Term termToIntegrate(getCosecantSquared(inputTerm));
        putCosecantSquaredToCotangentSquaredTerms(termToIntegrate, inputTerm, exponent-2);
        result = integrate(termToIntegrate);
    }
    else
    {
        unsigned int const exponentMinus1 = exponent-1;
        unsigned int const exponentMinus2 = exponent-2;
        Term cscRaiseToExponentMinus2(createExpressionIfPossible({Term(csc(inputTerm)), Term("^"), Term(exponentMinus2)}));
        Term nonIntegralTerm(createExpressionIfPossible({cscRaiseToExponentMinus2, Term("*"), Term(cot(inputTerm)), Term("*"), Term(-1)}));
        result = (nonIntegralTerm - Term(exponentMinus2)*integrate(cscRaiseToExponentMinus2))/exponentMinus1;
    }
}

void Integration::integrateSecRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Function const& baseTrigFunction,
        unsigned int const exponent) const
{
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(baseTrigFunction.getInputTermConstReference()));
    if(isEven(exponent))
    {
        Term termToIntegrate(getSecantSquared(inputTerm));
        putSecantSquaredToTangentSquaredTerms(termToIntegrate, inputTerm, exponent-2);
        result = integrate(termToIntegrate);
    }
    else
    {
        unsigned int const exponentMinus1 = exponent-1;
        unsigned int const exponentMinus2 = exponent-2;
        Term secRaiseToExponentMinus2(createExpressionIfPossible({Term(sec(inputTerm)), Term("^"), Term(exponentMinus2)}));
        Term nonIntegralTerm(createExpressionIfPossible({secRaiseToExponentMinus2, Term("*"), Term(tan(inputTerm))}));
        result = (nonIntegralTerm - Term(exponentMinus2) * integrate(secRaiseToExponentMinus2))/exponentMinus1;
    }
}

void Integration::integrateInMultiplicationOrDivisionIfTrigonometricCombination(
        Term & result,
        TermsWithDetails const& termsWithDetails) const
{
    InputTermToTrigonometryFunctionExponentsMap inputTermToExponents;
    TermsOverTerms::BaseToExponentMap remainingTerms;

    TermsOverTerms termsOverTerms(termsWithDetails);
    TermsOverTerms::BaseToExponentMap baseToExponentMap;
    termsOverTerms.retrieveBaseToExponentMap(baseToExponentMap);

    for(auto const& baseToExponentPair : baseToExponentMap)
    {
        Term const& base(baseToExponentPair.first);
        AlbaNumber const& exponent(baseToExponentPair.second);
        if(base.isFunction() && isTrigonometricFunction(base.getFunctionConstReference()))
        {
            Function const& functionObject(base.getFunctionConstReference());
            Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
            string const& functionName(functionObject.getFunctionName());
            if("sin" == functionName)
            {
                inputTermToExponents[inputTerm].sinExponent += exponent;
            }
            else if("cos" == functionName)
            {
                inputTermToExponents[inputTerm].cosExponent += exponent;
            }
            else if("tan" == functionName)
            {
                inputTermToExponents[inputTerm].tanExponent += exponent;
            }
            else if("csc" == functionName)
            {
                inputTermToExponents[inputTerm].cscExponent += exponent;
            }
            else if("sec" == functionName)
            {
                inputTermToExponents[inputTerm].secExponent += exponent;
            }
            else if("cot" == functionName)
            {
                inputTermToExponents[inputTerm].cotExponent += exponent;
            }
        }
        else
        {
            remainingTerms.emplace(base, exponent);
        }
    }

    if(remainingTerms.empty() && inputTermToExponents.size() == 1)
    {
        Term const& inputTerm(inputTermToExponents.begin()->first);
        TrigonometryFunctionExponents const& exponents(inputTermToExponents.begin()->second);
        if(exponents.sinExponent.isIntegerType() && exponents.sinExponent > 1
                && exponents.cosExponent.isIntegerType() && exponents.cosExponent > 1
                && exponents.tanExponent == 0
                && exponents.cscExponent == 0
                && exponents.secExponent == 0
                && exponents.cotExponent == 0)
        {
            integrateSinAndCosCombinationWithExponentsGreaterThanOne(
                        result,
                        inputTerm,
                        static_cast<unsigned int>(exponents.sinExponent.getInteger()),
                        static_cast<unsigned int>(exponents.cosExponent.getInteger()));
        }
        else if(exponents.sinExponent == 0
                && exponents.cosExponent == 0
                && exponents.tanExponent == 0
                && exponents.cscExponent.isIntegerType() && exponents.cscExponent > 0
                && exponents.secExponent == 0
                && exponents.cotExponent.isIntegerType() && exponents.cotExponent > 0)
        {
            /*integrateCscAndCotCombinationWithPositiveExponents(
                        result,
                        inputTerm,
                        static_cast<unsigned int>(exponents.cscExponent.getInteger()),
                        static_cast<unsigned int>(exponents.cotExponent.getInteger()));*/
        }
    }
}

void Integration::integrateSinAndCosCombinationWithExponentsGreaterThanOne(
        Term & result,
        Term const& inputTerm,
        unsigned int const sinExponent,        unsigned int const cosExponent) const
{
    Term termToIntegrate(1);
    if(isEven(sinExponent) && isEven(cosExponent))    {
        putReducedSineSquaredToDoubleAngleCosineTerms(termToIntegrate, inputTerm, sinExponent);
        putReducedCosineSquaredToDoubleAngleCosineTerms(termToIntegrate, inputTerm, cosExponent);
    }
    else if(isOdd(sinExponent) && isEven(cosExponent))
    {
        termToIntegrate = termToIntegrate * Term(createExpressionIfPossible({getSineSquaredInCosine(inputTerm), Term("^"), Term(sinExponent/2)}));
        termToIntegrate = termToIntegrate * Term(sin(inputTerm));
        termToIntegrate = termToIntegrate * Term(createExpressionIfPossible({cos(inputTerm), Term("^"), Term(cosExponent)}));
    }
    else if(isEven(sinExponent) && isOdd(cosExponent))
    {
        termToIntegrate = termToIntegrate * Term(createExpressionIfPossible({getCosineSquaredInSine(inputTerm), Term("^"), Term(cosExponent/2)}));
        termToIntegrate = termToIntegrate * Term(cos(inputTerm));
        termToIntegrate = termToIntegrate * Term(createExpressionIfPossible({sin(inputTerm), Term("^"), Term(sinExponent)}));
    }
    else if(isOdd(sinExponent) && isOdd(cosExponent))
    {
        //This is also can be expressed in cosine.
        termToIntegrate = termToIntegrate * Term(createExpressionIfPossible({getSineSquaredInCosine(inputTerm), Term("^"), Term(cosExponent/2)}));
        termToIntegrate = termToIntegrate * Term(cos(inputTerm));
        termToIntegrate = termToIntegrate * Term(createExpressionIfPossible({sin(inputTerm), Term("^"), Term(sinExponent)}));
    }
    result = integrate(termToIntegrate);
}

void Integration::integrateCscAndCotCombinationWithPositiveExponents(
        Term & result,
        Term const& inputTerm,
        unsigned int const cscExponent,
        unsigned int const cotExponent) const
{
    if(isEven(cotExponent))
    {
        Term termToIntegrate(createExpressionIfPossible({csc(inputTerm), Term("^"), Term(cscExponent)}));
        putCotangentSquaredToCosecantSquaredTerms(termToIntegrate, inputTerm, cotExponent);
        result = integrate(termToIntegrate);
    }
    else
    {
        Term termToIntegrate(createExpressionIfPossible({csc(inputTerm), Term("^"), Term(cscExponent)}));
        putCotangentSquaredToCosecantSquaredTerms(termToIntegrate, inputTerm, cotExponent-1);
        termToIntegrate = termToIntegrate * Term(cot(inputTerm));
        result = integrate(termToIntegrate);
    }
}

Term Integration::integrateAsTermOrExpressionIfNeeded(
        Expression const& expression) const
{    Term result;
    Configurations configurations{getConfigurationWithFactors(), getConfigurationWithCommonDenominator()};
    for(Configuration const& configuration : configurations)
    {        Term simplifiedTerm(expression);
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
    integrateNonChangingAndChangingTermsInMultiplicationOrDivision(result, termsWithDetails);
}

void Integration::integrateTermsInRaiseToPower(
        Term & result,
        TermsWithDetails const& termsWithDetails) const
{
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
        integrateNonChangingTermRaiseToChangingTerm(result, firstTerm, secondTerm);
    }
    else if(isFirstAChangingTerm && !isSecondAChangingTerm)
    {
        integrateChangingTermRaiseToNonChangingTerm(result, firstTerm, secondTerm);
    }
    else
    {
        integrateChangingTermRaiseToChangingTerm(result, firstTerm, secondTerm);
    }
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
        if(!subTerm.isConstant() && !subTerm.isVariable() && isChangingTerm(subTerm))
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
    if(!isChangingTerm(termToIntegrateWithNewVariable))
    {
        string newVariableName(createVariableNameForSubstitution(termToSubstituteToVariable));
        Integration integrationWithNewVariable(newVariableName);
        Term integratedTermWithNewVariable(integrationWithNewVariable.integrate(termToIntegrateWithNewVariable));
        SubstitutionOfVariablesToTerms substitutionVariableToTerm({{newVariableName, termToSubstituteToVariable}});
        Term integratedTerm(substitutionVariableToTerm.performSubstitutionTo(integratedTermWithNewVariable));
        if(!isNotANumber(integratedTerm))
        {
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
        isolation.isolateTermWithVariable(m_nameOfVariableToIntegrate, termWithOldVariable, termWithWithoutOldVariable);
        if(canBeConvertedToMonomial(termWithOldVariable))
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

void Integration::integrateNonChangingAndChangingTermsInMultiplicationOrDivision(
        Term& result,
        TermsWithDetails const& termsWithDetails) const
{
    TermsWithDetails nonChangingTerms;
    TermsWithDetails changingTerms;
    segregateNonChangingAndChangingTerms(termsWithDetails, nonChangingTerms, changingTerms);
    if(nonChangingTerms.empty())
    {
        integrateChangingTermsInMultiplicationOrDivision(result, changingTerms);
    }
    else
    {
        Term nonChangingTermCombined(Expression(OperatorLevel::MultiplicationAndDivision, nonChangingTerms));
        Term changingTermCombined(1);
        if(!changingTerms.empty())
        {
            changingTermCombined = Term(Expression(OperatorLevel::MultiplicationAndDivision, changingTerms));
        }
        Term integratedChangingTerm(integrate(changingTermCombined));
        if(isNotANumber(integratedChangingTerm))
        {
            result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
        }
        else
        {
            result = nonChangingTermCombined * integratedChangingTerm;
        }
    }
}

void Integration::integrateChangingTermsInMultiplicationOrDivision(
        Term& result,
        TermsWithDetails const& changingTerms) const
{
    integrateInMultiplicationOrDivisionIfTrigonometricCombination(result, changingTerms);
    if(result.isEmpty())
    {
        integrateByTryingTwoTermsInMultiplicationAndDivision(result, changingTerms);    }
}

void Integration::integrateByTryingTwoTermsInMultiplicationAndDivision(        Term & result,
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
        findInnerAndOuterTermForChainRule(innerTermInFirstTerm, firstTerm);
        if(!innerTermInFirstTerm.isEmpty())
        {
            integrateUsingChainRuleInReverseIfPossible(result, firstTerm, innerTermInFirstTerm, secondTerm);
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
    if(!isChangingTerm(quotientOfDerivatives))
    {
        string newVariableToIntegrate(createVariableNameForSubstitution(firstInnerTerm));
        SubstitutionOfTermsToTerms substitutionTermToVariable({{firstInnerTerm, Term(newVariableToIntegrate)}});
        Term newFirstOuterTerm(substitutionTermToVariable.performSubstitutionTo(firstOuterTerm));
        Integration integrationWithNewVariable(newVariableToIntegrate);
        Term integratedOuterTermInNewVariable(integrationWithNewVariable.integrate(newFirstOuterTerm));
        SubstitutionOfVariablesToTerms substitutionVariableToTerm({{newVariableToIntegrate, firstInnerTerm}});
        Term integratedOuterTerm(substitutionVariableToTerm.performSubstitutionTo(integratedOuterTermInNewVariable));
        result = integratedOuterTerm / quotientOfDerivatives;
    }
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
            if(!isChangingTerm(exponent))
            {
                outerTerm = combinedBaseAndExponent;
                innerTerm = base;
            }
            else if(!isChangingTerm(base))
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
                if(result.isEmpty())
                {
                    integrateUsingIntegrationByPartsByTryingTwoTermsWithDifferentOrder(result, term, firstTerm, secondTerm);
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
        if(!isNotANumber(v))
        {
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
    bool isFirstRelationshipFound(true);
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
                if(isFirstRelationshipFound)
                {
                    accumulatedCoefficient = quotient.getConstantValueConstReference();
                    isFirstRelationshipFound = false;
                }
                else
                {
                    accumulatedCoefficient = AlbaNumber(-1) * quotient.getConstantValueConstReference() * accumulatedCoefficient;
                }
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

void Integration::integrateNonChangingTermRaiseToChangingTerm(
        Term & result,
        Term const& base,
        Term const& exponent) const
{
    if(wouldDifferentiationYieldToAConstant(exponent))
    {
        result = divideFirstTermAndDerivativeOfSecondTerm(Term(createExpressionIfPossible(
        {base, Term("^"), exponent, Term("/"), Term(ln(base))})), exponent);
    }
}

void Integration::integrateChangingTermRaiseToNonChangingTerm(
        Term & result,
        Term const& base,
        Term const& exponent) const
{
    if(wouldDifferentiationYieldToAConstant(base))
    {
        result = divideFirstTermAndDerivativeOfSecondTerm(Term(createExpressionIfPossible(
        {base, Term("^"), Term(exponent+1), Term("/"), Term(exponent+1)})), base);
    }
    else
    {
        if(result.isEmpty() && base.isFunction() && exponent == Term(2))
        {
            integrateRecognizedFunctionsSquared(result, base);
        }
        if(result.isEmpty() && base.isFunction() && exponent.isConstant())
        {
            Function const& functionObject(base.getFunctionConstReference());
            AlbaNumber const& exponentValue(exponent.getConstantValueConstReference());
            string const& functionName(functionObject.getFunctionName());
            bool isExponentAPositiveInteger = exponentValue.isIntegerType() && exponentValue > 1;
            if(functionName == "sin" && isExponentAPositiveInteger)
            {
                integrateSinRaiseToAnIntegerGreaterThanOne(result, base.getFunctionConstReference(), static_cast<unsigned int>(exponentValue.getInteger()));
            }
            else if(functionName == "cos" && isExponentAPositiveInteger)
            {
                integrateCosRaiseToAnIntegerGreaterThanOne(result, base.getFunctionConstReference(), static_cast<unsigned int>(exponentValue.getInteger()));
            }
            else if(functionName == "csc" && isExponentAPositiveInteger)
            {
                integrateCscRaiseToAnIntegerGreaterThanOne(result, base.getFunctionConstReference(), static_cast<unsigned int>(exponentValue.getInteger()));
            }
            else if(functionName == "sec" && isExponentAPositiveInteger)
            {
                integrateSecRaiseToAnIntegerGreaterThanOne(result, base.getFunctionConstReference(), static_cast<unsigned int>(exponentValue.getInteger()));
            }
        }
    }
}
void Integration::integrateChangingTermRaiseToChangingTerm(
        Term & result,
        Term const& ,        Term const& ) const
{
    result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
}

void Integration::segregateNonChangingAndChangingTerms(
        TermsWithDetails const& termsToSegregate,
        TermsWithDetails & nonChangingTerms,
        TermsWithDetails & changingTerms) const
{
    for(TermWithDetails const& termToSegregate : termsToSegregate)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termToSegregate.baseTermSharedPointer));
        if(isChangingTerm(term))
        {
            changingTerms.emplace_back(termToSegregate);
        }
        else
        {
            nonChangingTerms.emplace_back(termToSegregate);
        }
    }
}

void Integration::putReducedSineSquaredToDoubleAngleCosineTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term inputTimes2(inputTerm*Term(2));
    Term equivalentToSineSquared(getSineSquaredOfHalvedValue(inputTimes2));
    for(unsigned int i=0; i<exponent; i+=2)
    {
        outputTerm = outputTerm * equivalentToSineSquared;
    }
}

void Integration::putReducedCosineSquaredToDoubleAngleCosineTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term inputTimes2(inputTerm*Term(2));
    Term equivalentToCosineSquared(getCosineSquaredOfHalvedValue(inputTimes2));
    for(unsigned int i=0; i<exponent; i+=2)
    {
        outputTerm = outputTerm * equivalentToCosineSquared;
    }
}

void Integration::putCosecantSquaredToCotangentSquaredTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term equivalentToSecantSquared(getCosecantSquaredInCotangent(inputTerm));
    for(unsigned int i=0; i<exponent; i+=2)
    {
        outputTerm = outputTerm * equivalentToSecantSquared;
    }
}

void Integration::putSecantSquaredToTangentSquaredTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term equivalentToSecantSquared(getSecantSquaredInTangent(inputTerm));
    for(unsigned int i=0; i<exponent; i+=2)
    {
        outputTerm = outputTerm * equivalentToSecantSquared;
    }
}

void Integration::putCotangentSquaredToCosecantSquaredTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term equivalentToCotangentSquared(getCotangentSquaredInCosecant(inputTerm));
    for(unsigned int i=0; i<exponent; i+=2)
    {
        outputTerm = outputTerm * equivalentToCotangentSquared;
    }
}

void Integration::setIsIntegrationUsingSubstitutionAllowed(
        bool const isIntegrationUsingSubstitutionAllowed)
{    m_isIntegrationUsingSubstitutionAllowed = isIntegrationUsingSubstitutionAllowed;
}

void Integration::setIsIntegrationByPartsAllowed(        bool const isIntegrationByPartsAllowed)
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

Integration::Configuration Integration::getConfigurationWithoutFactors() const
{
    Configuration configurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyToFactors = false;
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    configurationDetails.shouldSimplifyToACommonDenominator = false;
    return configurationDetails;
}

Integration::Configuration Integration::getConfigurationWithFactors() const
{
    Configuration configurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
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

bool Integration::isVariableToIntegrate(
        string const& variableName) const
{
    return variableName == m_nameOfVariableToIntegrate;
}

bool Integration::isChangingTerm(
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

bool Integration::hasExponentialExpression(Term const& term) const
{
    SubTermsRetriever retriever;
    retriever.retrieveFromTerm(term);
    bool result(false);
    for(Term const& retrievedTerm : retriever.getSavedData())
    {
        if(retrievedTerm.isExpression())
        {
            Expression const& expression(retrievedTerm.getExpressionConstReference());
            if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
            {
                TermRaiseToTerms termRaiseToTerms(expression.getTermsWithAssociation().getTermsWithDetails());
                result = isChangingTerm(termRaiseToTerms.getCombinedExponents());
                break;
            }
        }
    }
    return result;
}

bool Integration::wouldDifferentiationYieldToAConstant(
        Term const& term) const
{    bool result(0);
    if(term.isVariable() && isVariableToIntegrate(term.getVariableConstReference().getVariableName()))
    {
        result = true;    }
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
