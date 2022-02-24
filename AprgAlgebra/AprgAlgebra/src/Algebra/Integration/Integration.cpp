#include "Integration.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Functions/FunctionUtilities.hpp>
#include <Algebra/Integration/IntegrationUtilities.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/KnownExpressionsAndEquations/TrigonometricEquations.hpp>
#include <Algebra/Retrieval/SubTermsRetriever.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfTermsToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>
#include <Common/Math/AlbaMathHelper.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::algebra::Factorization;
using namespace alba::algebra::Functions;
using namespace alba::algebra::Simplification;
using namespace alba::mathHelper;
using namespace alba::matrix;
using namespace alba::stringHelper;
using namespace std;
namespace alba
{
namespace algebra{

Integration::Integration(
        string const& nameOfVariableToIntegrate)
    : m_variablesToIntegrate({nameOfVariableToIntegrate})
    , m_history()
{}

bool Integration::isConvergent(
        Term const& term,
        AlbaNumber const& lowerEnd,
        AlbaNumber const& higherEnd)
{
    Term integratedTerm(integrateAtDefiniteValues(term, lowerEnd, higherEnd));
    return isARealFiniteConstant(integratedTerm);
}

Term Integration::integrate(
        Term const& term)
{
    return integrateIntenally(term);
}

Term Integration::integrate(
        Constant const& constant)
{
    return integrateConstant(constant);
}

Term Integration::integrate(
        Variable const& variable)
{
    Term result(integrateVariable(variable));
    result.simplify();
    return result;
}

Term Integration::integrate(
        Monomial const& monomial)
{
    Term result(integrateMonomial(monomial));
    result.simplify();
    return result;
}

Term Integration::integrate(
        Polynomial const& polynomial)
{
    Term result(integratePolynomial(polynomial));
    result.simplify();
    return result;
}

Term Integration::integrate(
        Expression const& expression)
{
    return integrateExpression(expression);
}

Term Integration::integrate(
        Function const& functionObject)
{
    return integrateFunction(functionObject);
}

Term Integration::integrateWithPlusC(
        Term const& term)
{
    Term result(createExpressionIfPossible({integrateIntenally(term), "+", C}));
    finalizeTermForIntegration(result);
    return result;
}

Term Integration::integrateAtDefiniteValues(
        Term const& term,
        AlbaNumber const& lowerEnd,
        AlbaNumber const& higherEnd)
{
    return evaluateValuesAndGetDifference(
                integrateIntenally(term),
                getCurrentVariableToIntegrate(),
                lowerEnd,
                higherEnd);
}

Term Integration::integrateAtDefiniteTerms(
        Term const& term,
        Term const& lowerEnd,
        Term const& higherEnd)
{
    return evaluateTermsAndGetDifference(
                integrateIntenally(term),
                getCurrentVariableToIntegrate(),
                lowerEnd,
                higherEnd);
}

Monomial Integration::integrateConstant(
        Constant const& constant)
{
    return Monomial(constant.getNumberConstReference(), {{getCurrentVariableToIntegrate(), 1}});
}

Monomial Integration::integrateVariable(
        Variable const& variable)
{
    Monomial result;
    string const& nameOfVariable(variable.getVariableName());
    if(isVariableToIntegrate(nameOfVariable))
    {
        result = Monomial(AlbaNumber::createFraction(1, 2), {{variable.getVariableName(), 2}});
    }
    else
    {
        result = Monomial(1, {{variable.getVariableName(), 1}, {getCurrentVariableToIntegrate(), 1}});
    }
    return result;
}

Term Integration::integrateMonomial(
        Monomial const& monomial)
{
    Term result;
    AlbaNumber exponentForVariable = monomial.getExponentForVariable(getCurrentVariableToIntegrate());
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
        Polynomial const& polynomial)
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
        Expression const& expression)
{
    Term result(integrateAsTermOrExpressionIfNeeded(expression));
    finalizeTermForIntegration(result);
    return result;
}

Term Integration::integrateFunction(
        Function const& functionObject)
{
    Term result(integrateFunctionInternally(functionObject));
    finalizeTermForIntegration(result);
    return result;
}

Term Integration::integrateIntenally(
        Term const& term)
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

Term Integration::integrateInternallyWithPurpose(
        Term const& term,
        IntegrationPurpose const purpose)
{
    m_history.performStepsBeforeIntegration(term, purpose);
    Term integratedTerm(integrateIntenally(term));
    m_history.performStepsAfterIntegration(term, purpose, integratedTerm);
    return integratedTerm;
}

Term Integration::integrateIntenallyWithNewVariable(
        Term const& term,
        IntegrationPurpose const purpose,
        string const& newVariable)
{
    m_variablesToIntegrate.emplace_back(newVariable);
    Term integratedTerm(integrateInternallyWithPurpose(term, purpose));
    m_variablesToIntegrate.pop_back();
    return integratedTerm;
}

Term Integration::integrateMonomialWhenExponentIsNegativeOne(
        Monomial const& monomial) const
{
    Monomial retainedMonomial(monomial);
    retainedMonomial.putVariableWithExponent(getCurrentVariableToIntegrate(), 0);
    Term result = retainedMonomial * getNaturalLogarithmOfTheAbsoluteValueOfTerm(getCurrentVariableToIntegrate());
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
        result.putVariableWithExponent(getCurrentVariableToIntegrate(), 1);
    }
    return result;
}

Term Integration::integrateAsTermOrExpressionIfNeeded(
        Expression const& expression)
{
    Term result;
    Configurations configurations{getConfigurationWithFactors(), getConfigurationWithCommonDenominator(), getConfigurationWithoutFactors()};
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
            result = integrateInternallyWithPurpose(simplifiedTerm, IntegrationPurpose::NoChange);
        }
        if(!result.isEmpty())
        {
            break;
        }
    }
    if(result.isEmpty())
    {
        result = AlbaNumber(AlbaNumber::Value::NotANumber);
    }
    return result;
}

void Integration::integrateSimplifiedExpressionOnly(
        Term & result,
        Expression const& expression,
        Configuration const& configuration)
{
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        integrateTermsInAdditionOrSubtraction(result, expression);
    }
    else if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        integrateTermsInMultiplicationOrDivision(result, expression);
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        integrateTermsInRaiseToPower(result, expression);
    }
    if(result.isEmpty())
    {
        integrateAsPolynomialOverPolynomialIfPossible(result, expression, true);
    }
    if(result.isEmpty())
    {
        integrateTermUsingTrigonometricSubstitution(result, expression);
    }
    if(result.isEmpty())
    {
        integrateTermUsingSubstitutionWithMaxDepth(result, expression, configuration);
    }
    if(result.isEmpty())
    {
        integrateByTryingIntegrationByParts(result, expression);
    }
}

void Integration::integrateTermsInAdditionOrSubtraction(
        Term & result,
        Expression const& expression)
{
    Expression accumulatedExpression(createOrCopyExpressionFromATerm(0));
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& currentTerm(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        Term integratedTerm(integrateInternallyWithPurpose(currentTerm, IntegrationPurpose::NoChange));
        if(termWithDetails.hasPositiveAssociation())
        {
            accumulatedExpression.putTermWithAdditionIfNeeded(integratedTerm);
        }
        else
        {
            accumulatedExpression.putTermWithSubtractionIfNeeded(integratedTerm);
        }
    }
    result = accumulatedExpression;
}

void Integration::integrateTermsInMultiplicationOrDivision(
        Term & result,
        Expression const& expression)
{
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    integrateAsPolynomialOverPolynomialIfPossible(result, expression, false);
    integrateNonChangingAndChangingTermsInMultiplicationOrDivision(result, termsWithDetails);
}

void Integration::integrateTermsInRaiseToPower(
        Term & result,
        Expression const& expression)
{
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    TermRaiseToTerms termRaiseToTerms(termsWithDetails);
    termRaiseToTerms.simplify();
    Term firstTerm(termRaiseToTerms.getBase());
    Term secondTerm(termRaiseToTerms.getCombinedExponents());
    bool isFirstAChangingTerm = isChangingTerm(firstTerm);
    bool isSecondAChangingTerm = isChangingTerm(secondTerm);
    if(!isFirstAChangingTerm && !isSecondAChangingTerm)
    {
        result = termRaiseToTerms.getCombinedTerm() * getCurrentVariableToIntegrate();
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

Term Integration::integrateFunctionInternally(
        Function const& functionObject)
{
    Term result;
    integrateFunctionOnly(result, functionObject);
    if(result.isEmpty())
    {
        integrateTermUsingSubstitutionWithMaxDepth(result, functionObject, getConfigurationWithFactors());
    }
    if(result.isEmpty())
    {
        integrateByTryingIntegrationByParts(result, functionObject);
    }
    if(result.isEmpty())
    {
        result = AlbaNumber(AlbaNumber::Value::NotANumber);
    }
    return result;
}

void Integration::integrateFunctionOnly(
        Term & result,
        Function const& functionObject) const
{
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    if(wouldDifferentiationYieldToAConstant(inputTerm))
    {
        string const& functionName(functionObject.getFunctionName());
        if("abs" == functionName)
        {
            result = AlbaNumber(AlbaNumber::Value::NotANumber);
        }
        else if("sin" == functionName)
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(createExpressionIfPossible({-1, "*", cos(inputTerm)}), inputTerm);
        }
        else if("cos" == functionName)
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(sin(inputTerm), inputTerm);
        }
        else if("tan" == functionName)
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(sec(inputTerm));
        }
        else if("csc" == functionName)
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(csc(inputTerm) - cot(inputTerm));
        }
        else if("sec" == functionName)
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(sec(inputTerm) + tan(inputTerm));
        }
        else if("cot" == functionName)
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(sin(inputTerm));
        }
        else if("sinh" == functionName)
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(cosh(inputTerm), inputTerm);
        }
        else if("cosh" == functionName)
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(sinh(inputTerm), inputTerm);
        }
    }
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
            result = divideFirstTermAndDerivativeOfSecondTerm(tan(inputOfFunctionTerm), inputOfFunctionTerm);
        }
        else if(functionName == "csc")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(createExpressionIfPossible(
            {-1, "*", cot(inputOfFunctionTerm)}), inputOfFunctionTerm);
        }
        else if(functionName == "sech")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(tanh(inputOfFunctionTerm), inputOfFunctionTerm);
        }
        else if(functionName == "csch")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(createExpressionIfPossible(
            {-1, "*", coth(inputOfFunctionTerm)}), inputOfFunctionTerm);
        }
    }
}

void Integration::integrateNonChangingAndChangingTermsInMultiplicationOrDivision(
        Term& result,
        TermsWithDetails const& termsWithDetails)
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
        Term nonChangingTermCombined(createTermWithMultiplicationAndDivisionTermsWithDetails(nonChangingTerms));
        Term changingTermCombined(createTermWithMultiplicationAndDivisionTermsWithDetails(changingTerms));
        Term integratedChangingTerm(integrateInternallyWithPurpose(changingTermCombined, IntegrationPurpose::NoChange));
        if(isNotANumber(integratedChangingTerm))
        {
            result = AlbaNumber(AlbaNumber::Value::NotANumber);
        }
        else
        {
            result = nonChangingTermCombined * integratedChangingTerm;
        }
    }
}

void Integration::integrateChangingTermsInMultiplicationOrDivision(
        Term& result,
        TermsWithDetails const& changingTerms)
{
    TermsOverTerms termsOverTerms(changingTerms);
    TermsRaiseToNumbers termsWithExponentsToCheck(termsOverTerms.getTermsRaiseToNumbers());

    InputTermToTrigonometryFunctionExponentsMap trigFunctionsInputTermToExponents;
    TermsRaiseToNumbers remainingTermsWithExponents;
    retrieveInputTermsAndTrigonometricExponents(trigFunctionsInputTermToExponents, remainingTermsWithExponents, termsWithExponentsToCheck);
    integrateTrigonometricCombinationsIfPossible(result, remainingTermsWithExponents, trigFunctionsInputTermToExponents);

    if(result.isEmpty())
    {
        integrateInMultiplicationOrDivisionByTryingReverseChainRule(result, changingTerms);
    }
}

void Integration::integrateNonChangingTermRaiseToChangingTerm(
        Term & result,
        Term const& base,
        Term const& exponent)
{
    if(wouldDifferentiationYieldToAConstant(exponent))
    {
        result = divideFirstTermAndDerivativeOfSecondTerm(
                    createExpressionIfPossible({base, "^", exponent, "/", ln(base)}),
                    exponent);
    }
}

void Integration::integrateChangingTermRaiseToNonChangingTerm(
        Term & result,
        Term const& base,
        Term const& exponent)
{
    if(wouldDifferentiationYieldToAConstant(base))
    {
        result = divideFirstTermAndDerivativeOfSecondTerm(
                    createExpressionIfPossible({base, "^", exponent+1, "/", exponent+1}),
                    base);
    }
    else
    {
        if(result.isEmpty() && base.isFunction() &&  Term(2) == exponent)
        {
            integrateRecognizedFunctionsSquared(result, base);
        }
        if(result.isEmpty() && base.isFunction() && exponent.isConstant())
        {
            Function const& functionObject(base.getFunctionConstReference());
            Term const& functionInputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
            AlbaNumber const& exponentValue(exponent.getConstantValueConstReference());
            string const& functionName(functionObject.getFunctionName());
            bool isExponentGreaterThan1 = exponentValue.isIntegerType() && exponentValue > 1;
            if(functionName == "sin" && isExponentGreaterThan1)
            {
                integrateSinRaiseToAnIntegerGreaterThanOne(result, functionInputTerm, static_cast<unsigned int>(exponentValue.getInteger()));
            }
            else if(functionName == "cos" && isExponentGreaterThan1)
            {
                integrateCosRaiseToAnIntegerGreaterThanOne(result, functionInputTerm, static_cast<unsigned int>(exponentValue.getInteger()));
            }
            else if(functionName == "tan" && isExponentGreaterThan1)
            {
                integrateTanRaiseToAnIntegerGreaterThanOne(result, functionInputTerm, static_cast<unsigned int>(exponentValue.getInteger()));
            }
            else if(functionName == "csc" && isExponentGreaterThan1)
            {
                integrateCscRaiseToAnIntegerGreaterThanOne(result, functionInputTerm, static_cast<unsigned int>(exponentValue.getInteger()));
            }
            else if(functionName == "sec" && isExponentGreaterThan1)
            {
                integrateSecRaiseToAnIntegerGreaterThanOne(result, functionInputTerm, static_cast<unsigned int>(exponentValue.getInteger()));
            }
            else if(functionName == "cot" && isExponentGreaterThan1)
            {
                integrateCotRaiseToAnIntegerGreaterThanOne(result, functionInputTerm, static_cast<unsigned int>(exponentValue.getInteger()));
            }
        }
    }
}

void Integration::integrateChangingTermRaiseToChangingTerm(
        Term & result,
        Term const& ,
        Term const& )
{
    result = AlbaNumber(AlbaNumber::Value::NotANumber);
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

void Integration::integrateTermUsingSubstitutionWithMaxDepth(
        Term & result,
        Term const& term,
        Configuration const& configuration)
{
    if(isIntegrationUsingSubstitutionAllowed(term))
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
        Configuration const& configuration)
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
        Term const& termForNewVariable,
        Configuration const& configuration)
{
    Term termToIntegrateWithNewVariable(substituteToNewVariable(mainTerm, termForNewVariable));
    simplifyForIntegration(termToIntegrateWithNewVariable, configuration);
    if(!isChangingTerm(termToIntegrateWithNewVariable))
    {
        string newVariableName(createVariableNameForSubstitution(termForNewVariable));
        Term integratedTermWithNewVariable(integrateIntenallyWithNewVariable(termToIntegrateWithNewVariable, IntegrationPurpose::Substitution, newVariableName));
        if(!isNotANumber(integratedTermWithNewVariable))
        {
            result = substituteBackToOldVariable(integratedTermWithNewVariable, newVariableName, termForNewVariable);
        }
    }
}

Term Integration::substituteToNewVariable(
        Term const& mainTerm,
        Term const& termForNewVariable) const
{
    Differentiation differentiation(getCurrentVariableToIntegrate());
    Term derivative(differentiation.differentiate(termForNewVariable));
    Term termForSubstitution = mainTerm/derivative;
    string newVariableName(createVariableNameForSubstitution(termForNewVariable));
    Term newVariable(newVariableName);
    SubstitutionOfTermsToTerms substitutionOfNewVariableDirectMatch({{termForNewVariable, newVariable}});
    Term result(substitutionOfNewVariableDirectMatch.performSubstitutionTo(termForSubstitution));
    if(termForNewVariable.isPolynomial()
            || termForNewVariable.isExpression()
            || termForNewVariable.isFunction())
    {
        IsolationOfOneVariableOnEqualityEquation isolationForOldVariable(Equation(newVariable, "=", termForNewVariable));
        Term termWithOldVariable;
        Term newVariableInTermsOfOldVariable;
        isolationForOldVariable.isolateTermWithVariable(getCurrentVariableToIntegrate(), termWithOldVariable, newVariableInTermsOfOldVariable);
        if(canBeConvertedToMonomial(termWithOldVariable))
        {
            Monomial monomialWithOldVariable(createMonomialIfPossible(termWithOldVariable));
            AlbaNumber exponentForOldVariable(monomialWithOldVariable.getExponentForVariable(getCurrentVariableToIntegrate()));
            monomialWithOldVariable.putVariableWithExponent(getCurrentVariableToIntegrate(), AlbaNumber(0));
            Term isolatedTermWithNewVariable((newVariableInTermsOfOldVariable/monomialWithOldVariable)^(AlbaNumber(1)/exponentForOldVariable));
            isolatedTermWithNewVariable.simplify();
            SubstitutionOfVariablesToTerms substitutionFromOldVariableToNewVariable({{getCurrentVariableToIntegrate(), isolatedTermWithNewVariable}});
            result = substitutionFromOldVariableToNewVariable.performSubstitutionTo(result);
        }
    }
    return result;
}

Term Integration::substituteBackToOldVariable(
        Term const& mainTerm,
        string const& newVariableName,
        Term const& termForNewVariable) const
{
    SubstitutionOfVariablesToTerms substitutionVariableToTerm({{newVariableName, termForNewVariable}});
    return substitutionVariableToTerm.performSubstitutionTo(mainTerm);
}

void Integration::integrateTermUsingTrigonometricSubstitution(
        Term & result,
        Term const& term)
{
    if(isTrigonometricSubstitutionAllowed())
    {
        Term simplifiedTerm(term);
        simplifyForIntegration(simplifiedTerm, getConfigurationWithCombiningRadicals());
        Terms subTerms(retrieveSubTerms(simplifiedTerm));
        for(Term const& subTerm : subTerms)
        {
            if(!subTerm.isConstant() && !subTerm.isVariable() && isChangingTerm(subTerm))
            {
                integrateUsingTrigonometricSubstitutionByFindingTwoTerms(result, simplifiedTerm, subTerm);
                if(!result.isEmpty())
                {
                    break;
                }
            }
        }
    }
}

void Integration::integrateUsingTrigonometricSubstitutionByFindingTwoTerms(
        Term & result,
        Term const& mainTerm,
        Term const& termToSubstitute)
{
    bool shouldProceedToTrigSub(false);
    Term commonFactor;
    Term firstAndSecondTerm;
    Term firstTerm;
    Term secondTerm;

    if(termToSubstitute.isExpression())
    {
        retrieveImportantTermsForTrigonometricSubstitutionInExpression(
                    shouldProceedToTrigSub, commonFactor, firstAndSecondTerm, firstTerm, secondTerm, termToSubstitute.getExpressionConstReference());
    }
    else if(termToSubstitute.isPolynomial())
    {
        retrieveImportantTermsForTrigonometricSubstitutionInPolynomial(
                    shouldProceedToTrigSub, commonFactor, firstAndSecondTerm, firstTerm, secondTerm, termToSubstitute.getPolynomialConstReference());
    }
    if(shouldProceedToTrigSub)
    {
        shouldProceedToTrigSub = false;
        if(!isChangingTerm(firstTerm) && isChangingTerm(secondTerm))
        {
            shouldProceedToTrigSub = true;
        }
        else if(isChangingTerm(firstTerm) && !isChangingTerm(secondTerm))
        {
            swap(firstTerm, secondTerm);
            shouldProceedToTrigSub = true;
        }
    }
    if(shouldProceedToTrigSub)
    {
        string firstAndSecondTermVariableName(createVariableNameForSubstitution(firstAndSecondTerm));
        Term firstAndSecondTermVariable(firstAndSecondTermVariableName);
        Term newTermToSubstitute(createExpressionIfPossible({commonFactor, "*", firstAndSecondTermVariable}));
        SubstitutionOfTermsToTerms substitution{{termToSubstitute, newTermToSubstitute}};
        Term newMainTerm(substitution.performSubstitutionTo(mainTerm));
        integrateUsingTrigonometricSubstitutionWithDeterminedTerms(result, newMainTerm, firstAndSecondTermVariableName, firstAndSecondTerm, firstTerm, secondTerm);
    }
}

void Integration::integrateUsingTrigonometricSubstitutionWithDeterminedTerms(
        Term & result,
        Term const& mainTerm,
        string const& aSquaredAndUSquaredName,
        Term const& aSquaredAndUSquared,
        Term const& aSquaredWithSign,
        Term const& uSquaredWithSign)
{
    bool isANegative(isANegativeTerm(aSquaredWithSign));
    bool isUNegative(isANegativeTerm(uSquaredWithSign));
    Term const& aSquared = convertPositiveTermIfNegative(aSquaredWithSign);
    Term const& uSquared = convertPositiveTermIfNegative(uSquaredWithSign);

    TermRaiseToANumber uToANumber(createTermRaiseToANumberFromTerm(uSquared));
    if(AlbaNumber(2) == uToANumber.getExponent())
    {
        Term a(createExpressionIfPossible({aSquared, "^", AlbaNumber::createFraction(1, 2)}));
        Term const& u(uToANumber.getBase());
        a.simplify();

        TrigonometricSubstitutionDetails details(calculateTrigonometricSubstitutionDetails(a, u, aSquaredAndUSquaredName, aSquaredAndUSquared, isANegative, isUNegative));
        if(details.isTrigonometricSubstitutionPossible)
        {
            Term termToIntegrateWithTrigSub(substituteToTrigonometricFunctions(mainTerm, details));
            if(!termToIntegrateWithTrigSub.isEmpty())
            {
                simplifyForIntegration(termToIntegrateWithTrigSub, getConfigurationWithCommonDenominator());
                if(!isChangingTerm(termToIntegrateWithTrigSub))
                {
                    Term integratedTermWithTrigSub(integrateIntenallyWithNewVariable(termToIntegrateWithTrigSub, IntegrationPurpose::TrigonometricSubstitution, details.thetaName));
                    if(!isNotANumber(integratedTermWithTrigSub))
                    {
                        result = substituteFromTrigonometricFunctionsBackToNormal(integratedTermWithTrigSub, details);
                    }
                }
            }
        }
    }
}

void Integration::retrieveImportantTermsForTrigonometricSubstitutionInExpression(
        bool & shouldProceedToTrigSub,
        Term & commonFactor,
        Term & firstAndSecondTerm,
        Term & firstTerm,
        Term & secondTerm,
        Expression const& expression)  const
{
    TermsWithDetails const& expressionTerms(expression.getTermsWithAssociation().getTermsWithDetails());
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel() && 2 == expressionTerms.size())
    {
        commonFactor = 1;
        firstAndSecondTerm = expression;
        firstTerm = negateTermIfHasNegativeAssociation(expressionTerms.at(0));
        secondTerm = negateTermIfHasNegativeAssociation(expressionTerms.at(1));
        shouldProceedToTrigSub = true;
    }
}

void Integration::retrieveImportantTermsForTrigonometricSubstitutionInPolynomial(
        bool & shouldProceedToTrigSub,
        Term & commonFactor,
        Term & firstAndSecondTerm,
        Term & firstTerm,
        Term & secondTerm,
        Polynomial const& polynomial)  const
{
    Polynomials factorizedPolynomials(factorizeCommonMonomial(polynomial));
    if(factorizedPolynomials.size() == 1)
    {
        commonFactor = 1;
        Polynomial const& onlyPolynomial(factorizedPolynomials.at(0));
        Monomials const& onlyMonomials(factorizedPolynomials.at(0).getMonomialsConstReference());
        if(2 == onlyMonomials.size())
        {
            commonFactor = 1;
            firstAndSecondTerm = onlyPolynomial;
            firstTerm = onlyMonomials.at(0);
            secondTerm = onlyMonomials.at(1);
            shouldProceedToTrigSub = true;
        }
    }
    else if(factorizedPolynomials.size() == 2)
    {
        Polynomial const& firstPolynomial(factorizedPolynomials.at(0));
        Polynomial const& secondPolynomial(factorizedPolynomials.at(1));
        Monomials const& firstMonomials(firstPolynomial.getMonomialsConstReference());
        Monomials const& secondMonomials(secondPolynomial.getMonomialsConstReference());
        if(1 == firstMonomials.size() || 2 == secondMonomials.size())
        {
            commonFactor = firstMonomials.at(0);
            firstAndSecondTerm = secondPolynomial;
            firstTerm = secondMonomials.at(0);
            secondTerm = secondMonomials.at(1);
            if(isANegativeTerm(commonFactor))
            {
                commonFactor = negateTerm(commonFactor);
                firstAndSecondTerm = negateTerm(firstAndSecondTerm);
                firstTerm = negateTerm(firstTerm);
                secondTerm = negateTerm(secondTerm);
            }
            shouldProceedToTrigSub = true;
        }
    }
}

Integration::TrigonometricSubstitutionDetails Integration::calculateTrigonometricSubstitutionDetails(
        Term const& a,
        Term const& u,
        string const& aSquaredAndUSquaredName,
        Term const& aSquaredAndUSquared,
        bool const isANegative,
        bool const isUNegative) const
{
    TrigonometricSubstitutionDetails result;
    result.a = a;
    result.u = u;
    result.aSquaredAndUSquaredName = aSquaredAndUSquaredName;
    result.aSquaredAndUSquared = aSquaredAndUSquared;
    result.thetaName = createVariableNameForSubstitution(u);
    result.theta=result.thetaName;
    if(!isANegative && !isUNegative)
    {
        // use tan
        result.isTrigonometricSubstitutionPossible = true;
        result.uEquivalent = createExpressionIfPossible({a, "*", tan(result.theta)});
        result.aSquaredAndUSquaredEquivalent = createExpressionIfPossible({a, "^", 2, "*", sec(result.theta), "^", 2});
        result.thetaEquivalent = arctan(u/a);
        result.opposite = u;
        result.adjacent = a;
        Term hypotenuseSquared(createExpressionIfPossible({a, "^", 2, "+", u, "^", 2}));
        result.hypotenuse = createExpressionIfPossible({hypotenuseSquared, "^", AlbaNumber::createFraction(1, 2)});
    }
    else if(!isANegative && isUNegative)
    {
        //use sin
        result.isTrigonometricSubstitutionPossible = true;
        result.uEquivalent = createExpressionIfPossible({a, "*", sin(result.theta)});
        result.aSquaredAndUSquaredEquivalent = createExpressionIfPossible({a, "^", 2, "*", cos(result.theta), "^", 2});
        result.thetaEquivalent = arcsin(u/a);
        result.opposite = u;
        Term adjacentSquared(createExpressionIfPossible({a, "^", 2, "-", u, "^", 2}));
        result.adjacent = createExpressionIfPossible({adjacentSquared, "^", AlbaNumber::createFraction(1, 2)});
        result.hypotenuse = a;
    }
    else if(isANegative && !isUNegative)
    {
        //use sec
        result.isTrigonometricSubstitutionPossible = true;
        result.uEquivalent = createExpressionIfPossible({a, "*", sec(result.theta)});
        result.aSquaredAndUSquaredEquivalent = createExpressionIfPossible({a, "^", 2, "*", tan(result.theta), "^", 2});
        result.thetaEquivalent = arcsec(u/a);
        Term oppositeSquared(createExpressionIfPossible({u, "^", 2, "-", a, "^", 2}));
        result.opposite = createExpressionIfPossible({oppositeSquared, "^", AlbaNumber::createFraction(1, 2)});
        result.adjacent = a;
        result.hypotenuse = u;
    }
    else
    {
        result.isTrigonometricSubstitutionPossible = false;
    }
    return result;
}

Term Integration::substituteToTrigonometricFunctions(
        Term const& mainTerm,
        TrigonometricSubstitutionDetails const& details) const
{
    Term result;
    Differentiation differentiation(details.thetaName);
    Term duEquivalent(differentiation.differentiate(details.uEquivalent));
    IsolationOfOneVariableOnEqualityEquation isolation(Equation(details.u, "=", details.uEquivalent));
    Term termWithU;
    Term termWithWithoutU;
    isolation.isolateTermWithVariable(getCurrentVariableToIntegrate(), termWithU, termWithWithoutU);
    if(canBeConvertedToMonomial(termWithU))
    {
        Monomial monomialWithOldVariable(createMonomialIfPossible(termWithU));
        AlbaNumber exponentForOldVariable(monomialWithOldVariable.getExponentForVariable(getCurrentVariableToIntegrate()));
        monomialWithOldVariable.putVariableWithExponent(getCurrentVariableToIntegrate(), AlbaNumber(0));
        Term isolatedTermWithTheta((termWithWithoutU/monomialWithOldVariable)^(AlbaNumber(1)/exponentForOldVariable));
        isolatedTermWithTheta.simplify();
        SubstitutionOfTermsToTerms substitutionUToThetaForTermToTerm({{details.aSquaredAndUSquared, details.aSquaredAndUSquaredEquivalent}});
        SubstitutionOfVariablesToTerms substitutionUToThetaForVariableToTerm(
        {{getCurrentVariableToIntegrate(), isolatedTermWithTheta}, {details.aSquaredAndUSquaredName, details.aSquaredAndUSquaredEquivalent}});
        result = substitutionUToThetaForVariableToTerm.performSubstitutionTo(
                    substitutionUToThetaForTermToTerm.performSubstitutionTo(mainTerm)) * duEquivalent;
    }
    return result;
}

Term Integration::substituteFromTrigonometricFunctionsBackToNormal(
        Term const& mainTerm,
        TrigonometricSubstitutionDetails const& details) const
{
    SubstitutionOfTermsToTerms substitutionThetaToUForTermToTerm;
    substitutionThetaToUForTermToTerm.putTermToTermMapping(sin(details.theta), details.opposite/details.hypotenuse);
    substitutionThetaToUForTermToTerm.putTermToTermMapping(cos(details.theta), details.adjacent/details.hypotenuse);
    substitutionThetaToUForTermToTerm.putTermToTermMapping(tan(details.theta), details.opposite/details.adjacent);
    substitutionThetaToUForTermToTerm.putTermToTermMapping(csc(details.theta), details.hypotenuse/details.opposite);
    substitutionThetaToUForTermToTerm.putTermToTermMapping(sec(details.theta), details.hypotenuse/details.adjacent);
    substitutionThetaToUForTermToTerm.putTermToTermMapping(cot(details.theta), details.adjacent/details.opposite);
    SubstitutionOfVariablesToTerms substitutionThetaToUForVariableToTerm({{details.thetaName, details.thetaEquivalent}});
    return substitutionThetaToUForVariableToTerm.performSubstitutionTo(
                substitutionThetaToUForTermToTerm.performSubstitutionTo(mainTerm));
}

void Integration::integrateInMultiplicationOrDivisionByTryingReverseChainRule(
        Term & result,
        TermsWithDetails const& termsWithDetailsInMultiplicationOrDivision)
{
    unsigned int numberOfTerms(termsWithDetailsInMultiplicationOrDivision.size());
    for(unsigned int i=0; result.isEmpty() && i<numberOfTerms; i++)
    {
        TermsWithDetails termsInFirstTerms(termsWithDetailsInMultiplicationOrDivision);
        termsInFirstTerms.erase(termsInFirstTerms.cbegin() + i);
        Term firstTerm(createTermWithMultiplicationAndDivisionTermsWithDetails(termsInFirstTerms));
        Term secondTerm(createTermWithMultiplicationAndDivisionTermsWithDetails({termsWithDetailsInMultiplicationOrDivision.at(i)}));
        Term innerTermInFirstTerm;
        firstTerm.simplify();
        secondTerm.simplify();
        findInnerAndOuterTermForChainRule(innerTermInFirstTerm, firstTerm);
        if(!innerTermInFirstTerm.isEmpty())
        {
            integrateUsingReverseChainRule(result, firstTerm, innerTermInFirstTerm, secondTerm);
        }
    }
}

void Integration::integrateUsingReverseChainRule(
        Term & result,
        Term const& firstOuterTerm,
        Term const& firstInnerTerm,
        Term const& secondTerm)
{
    Differentiation differentiation(getCurrentVariableToIntegrate());
    Term firstTermDerivative(differentiation.differentiate(firstInnerTerm));
    Term quotientOfDerivatives = firstTermDerivative/secondTerm;
    if(!isChangingTerm(quotientOfDerivatives))
    {
        string newVariableToIntegrate(createVariableNameForSubstitution(firstInnerTerm));
        SubstitutionOfTermsToTerms substitutionTermToVariable({{firstInnerTerm, newVariableToIntegrate}});
        Term newFirstOuterTerm(substitutionTermToVariable.performSubstitutionTo(firstOuterTerm));
        Term integratedOuterTermInNewVariable(integrateIntenallyWithNewVariable(newFirstOuterTerm, IntegrationPurpose::NoChange, newVariableToIntegrate));
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
            Term const& base(termRaiseToTerms.getBase());
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
    Differentiation differentiation(getCurrentVariableToIntegrate());
    return createExpressionIfPossible({firstTerm, "/", differentiation.differentiate(secondTerm)});
}

void Integration::integrateAsPolynomialOverPolynomialIfPossible(
        Term & result,
        Term const& term,
        bool const canProceedToPartialPolynomialFractions)
{
    VariableNamesRetriever retriever;
    retriever.retrieveFromTerm(term);

    VariableNamesSet const& variableNames(retriever.getSavedData());
    if(variableNames.size() == 1)
    {
        Term simplifiedTerm(term);
        simplifiedTerm.clearAllInnerSimplifiedFlags();
        simplifiedTerm.simplify();
        PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(simplifiedTerm));
        if(popOptional.hasContent())
        {
            integrateAsPolynomialOverPolynomial(result, popOptional.getConstReference(), *(variableNames.begin()), canProceedToPartialPolynomialFractions);
        }
    }
}

void Integration::integrateAsPolynomialOverPolynomial(
        Term & result,
        PolynomialOverPolynomial const& polynomialOverPolynomial,
        string const& variableName,
        bool const canProceedToPartialPolynomialFractions)
{
    PolynomialOverPolynomial pop(polynomialOverPolynomial);
    pop.setAsShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(true);
    Term wholePartResult;
    Polynomial remainingNumerator(pop.getNumerator());
    Polynomial remainingDenominator(pop.getDenominator());

    PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(pop.simplifyAndDivide());
    if(!quotientAndRemainder.quotient.isEmpty()
            && !hasNegativeExponentsWithVariable(quotientAndRemainder.quotient, getCurrentVariableToIntegrate()))
    {
        wholePartResult = integrateInternallyWithPurpose(quotientAndRemainder.quotient, IntegrationPurpose::NoChange);
        remainingNumerator = quotientAndRemainder.remainder;
        remainingDenominator = pop.getDenominator();
    }

    Term fractionalPartResult;
    if(canProceedToPartialPolynomialFractions)
    {
        integrateUsingPartialFractionPolynomials(fractionalPartResult, variableName, remainingNumerator, remainingDenominator);
    }
    else if(!wholePartResult.isEmpty())
    {
        fractionalPartResult = integrateInternallyWithPurpose(remainingNumerator/remainingDenominator, IntegrationPurpose::NoChange);
        if(isNotANumber(fractionalPartResult))
        {
            fractionalPartResult.clear();
        }
    }
    if(!fractionalPartResult.isEmpty())
    {
        result = wholePartResult + fractionalPartResult;
    }
}

void Integration::integrateUsingPartialFractionPolynomials(
        Term & result,
        string const& originalVariableName,
        Polynomial const& numerator,
        Polynomial const& denominator)
{
    // this can only be used if exponents are not fractional
    if(isIntegrationByPartialFractionAllowed())
    {
        TermsOverTerms oneOverDenominator({1}, {denominator});
        oneOverDenominator.setAsShouldSimplifyToFactors(true);
        oneOverDenominator.simplify();

        if(oneOverDenominator.getDenominators().size() > 1)
        {
            TermsRaiseToNumbers factorsWithExponents(oneOverDenominator.getTermsRaiseToNumbers());

            Polynomials partialNumerators;
            Polynomials partialDenominators;
            retrievePartialFractions(partialNumerators, partialDenominators, originalVariableName, factorsWithExponents);

            Polynomial numeratorWithNewVariables(getTotalNumeratorWithNewVariables(denominator, partialNumerators, partialDenominators));
            VariableNamesSet newVariableNames(getNamesOfNewVariablesForPartialFraction(originalVariableName, numeratorWithNewVariables));
            AlbaNumbersSet exponents(getExponentsForPartialFraction(originalVariableName, numeratorWithNewVariables));
            if(newVariableNames.size() == exponents.size())
            {
                AlbaMatrix<AlbaNumber> matrixForPartialFractions(newVariableNames.size()+1, exponents.size());
                fillInMatrixForPartialFractions(matrixForPartialFractions, originalVariableName, newVariableNames, exponents, numerator, numeratorWithNewVariables);

                transformToReducedEchelonFormUsingGaussJordanReduction(matrixForPartialFractions);

                if(isReducedRowEchelonForm(matrixForPartialFractions))
                {
                    integratePartialFractionsBasedOnSolvedMatrix(result, matrixForPartialFractions, newVariableNames, partialNumerators, partialDenominators);
                }            }
        }
    }
}
void Integration::retrievePartialFractions(
        Polynomials & partialNumerators,
        Polynomials & partialDenominators,
        string const& originalVariableName,
        TermsRaiseToNumbers const& factorsWithExponents) const
{
    for(auto const& factorExponentPair : factorsWithExponents.getBaseToExponentMap())
    {
        Term const& factor(factorExponentPair.first);
        TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(factor));
        AlbaNumber const& negatedExponent(factorExponentPair.second * -1 * termRaiseToANumber.getExponent());
        Term const& factorsToProcess(termRaiseToANumber.getBase());
        if(negatedExponent.isIntegerType() && negatedExponent > 0 && canBeConvertedToPolynomial(factorsToProcess))
        {
            Polynomial polynomialFactor(createPolynomialIfPossible(factorsToProcess));
            unsigned int maxDegreeOfFactor = static_cast<unsigned int>(getMaxDegree(polynomialFactor).getInteger());
            unsigned int denominatorExponent = static_cast<unsigned int>(negatedExponent.getInteger());
            for(unsigned int i=1; i<=denominatorExponent; i++)
            {
                Polynomial partialDenominator(polynomialFactor);
                partialDenominator.raiseToUnsignedInteger(i);
                partialDenominators.emplace_back(partialDenominator);
                partialNumerators.emplace_back(getPartialNumeratorForPartialFractions(maxDegreeOfFactor, originalVariableName));
            }
        }
    }
}

Polynomial Integration::getTotalNumeratorWithNewVariables(
        Polynomial const& originalDenominator,
        Polynomials const& partialNumerators,
        Polynomials const& partialDenominators) const
{
    Polynomial numeratorWithNewVariables;
    for(unsigned int i=0; i<partialDenominators.size(); i++)
    {
        Term currentNumeratorTerm = originalDenominator / partialDenominators.at(i) * partialNumerators.at(i);
        currentNumeratorTerm.simplify();
        if(canBeConvertedToPolynomial(currentNumeratorTerm))
        {
            numeratorWithNewVariables.addPolynomial(createPolynomialIfPossible(currentNumeratorTerm));
        }
    }
    numeratorWithNewVariables.simplify();
    return numeratorWithNewVariables;
}

VariableNamesSet Integration::getNamesOfNewVariablesForPartialFraction(
        string const& originalVariableName,
        Polynomial const& numeratorWithNewVariables) const
{
    VariableNamesRetriever namesRetriever;
    namesRetriever.retrieveFromPolynomial(numeratorWithNewVariables);
    VariableNamesSet newVariableNames(namesRetriever.getSavedData());
    VariableNamesSet::iterator itToRemove = newVariableNames.find(originalVariableName);
    if(itToRemove != newVariableNames.end())
    {
        newVariableNames.erase(itToRemove);
    }
    return newVariableNames;
}

AlbaNumbersSet Integration::getExponentsForPartialFraction(
        string const& originalVariableName,
        Polynomial const& numeratorWithNewVariables) const
{
    AlbaNumbersSet exponents;
    for(Monomial const& monomialWithNewVariable : numeratorWithNewVariables.getMonomialsConstReference())
    {
        exponents.emplace(monomialWithNewVariable.getExponentForVariable(originalVariableName));
    }
    return exponents;
}

void Integration::fillInMatrixForPartialFractions(
        AlbaMatrix<AlbaNumber> & matrixWithNewVariables,
        string const& originalVariableName,
        VariableNamesSet const& newVariableNames,
        AlbaNumbersSet const& exponents,
        Polynomial const& originalNumerator,
        Polynomial const& numeratorWithNewVariables) const
{
    fillInMatrixForPartialFractionsWithVariableValues(matrixWithNewVariables, originalVariableName, newVariableNames, exponents, numeratorWithNewVariables);
    fillInMatrixForPartialFractionsWithOutputValues(matrixWithNewVariables, originalVariableName, newVariableNames, exponents, originalNumerator);
}

void Integration::fillInMatrixForPartialFractionsWithVariableValues(
        AlbaMatrix<AlbaNumber> & matrixWithNewVariables,
        string const& originalVariableName,
        VariableNamesSet const& newVariableNames,
        AlbaNumbersSet const& exponents,
        Polynomial const& numeratorWithNewVariables) const
{
    for(Monomial const& monomialWithNewVariable : numeratorWithNewVariables.getMonomialsConstReference())
    {
        bool isVariablePositionFound;
        unsigned int exponentPosition(0);
        unsigned int variablePosition(0);
        for(auto const& variableExponentPair : monomialWithNewVariable.getVariablesToExponentsMapConstReference())
        {
            string const& variableName(variableExponentPair.first);
            AlbaNumber const& exponent(variableExponentPair.second);
            if(variableName == originalVariableName)
            {
                AlbaNumbersSet::const_iterator itPosition = exponents.find(exponent);
                if(itPosition != exponents.cend())
                {
                    exponentPosition = distance(exponents.cbegin(), itPosition);
                }
            }
            else
            {
                VariableNamesSet::const_iterator itPosition = newVariableNames.find(variableName);
                if(itPosition != newVariableNames.cend())
                {
                    variablePosition = distance(newVariableNames.cbegin(), itPosition);
                    isVariablePositionFound = true;
                }
            }
        }
        if(isVariablePositionFound)
        {
            matrixWithNewVariables.setEntry(variablePosition, exponentPosition, monomialWithNewVariable.getConstantConstReference());
        }
    }
}

void Integration::fillInMatrixForPartialFractionsWithOutputValues(
        AlbaMatrix<AlbaNumber> & matrixWithNewVariables,
        string const& originalVariableName,
        VariableNamesSet const& newVariableNames,
        AlbaNumbersSet const& exponents,
        Polynomial const& originalNumerator) const
{
    for(Monomial const& numeratorMonomial : originalNumerator.getMonomialsConstReference())
    {
        unsigned int exponentPosition(0);
        for(auto const& variableExponentPair : numeratorMonomial.getVariablesToExponentsMapConstReference())
        {
            string const& variableName(variableExponentPair.first);
            AlbaNumber const& exponent(variableExponentPair.second);
            if(variableName == originalVariableName)
            {
                AlbaNumbersSet::const_iterator itPosition = exponents.find(exponent);
                if(itPosition != exponents.cend())
                {
                    exponentPosition = distance(exponents.cbegin(), itPosition);
                }
            }
        }
        matrixWithNewVariables.setEntry(newVariableNames.size(), exponentPosition, numeratorMonomial.getConstantConstReference());
    }
}

void Integration::integratePartialFractionsBasedOnSolvedMatrix(
        Term & result,
        AlbaMatrix<AlbaNumber> const& solvedMatrix,
        VariableNamesSet const& newVariableNames,
        Polynomials const& partialNumerators,
        Polynomials const& partialDenominators)
{
    SubstitutionOfVariablesToTerms substitution;
    VariableNamesSet::const_iterator it = newVariableNames.cbegin();
    for(unsigned int i=0; i<solvedMatrix.getNumberOfRows() && it!=newVariableNames.cend(); i++)
    {
        substitution.putVariableWithTerm(*it, solvedMatrix.getEntry(newVariableNames.size(), i));
        it++;    }
    Term partialResult;
    for(unsigned int i=0; i<partialNumerators.size(); i++)
    {        Polynomial const& partialNumerator(partialNumerators.at(i));
        Polynomial const& partialDenominator(partialDenominators.at(i));
        Term termToIntegrate = substitution.performSubstitutionTo(partialNumerator)/partialDenominator;
        termToIntegrate.simplify();
        Term integratedTerm(integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::PartialFraction));
        partialResult = partialResult + integratedTerm;
    }
    result = partialResult;
}

Polynomial Integration::getPartialNumeratorForPartialFractions(
        unsigned int const degree,
        string const& variableName) const
{
    Polynomial result;
    for(unsigned int i=0; i<degree; i++)
    {
        result.addMonomial(Monomial(1, {{variableName, i}, {getNewVariableNameForPartialFractions(), 1}}));
    }
    result.simplify();
    return result;
}

string Integration::getNewVariableNameForPartialFractions() const
{
    static unsigned int variableCount(0);
    variableCount++;
    if(variableCount>999)
    {
        variableCount=0;
    }

    static bool isFirst(true);
    static NumberToStringConverter converter;

    if(isFirst)
    {
        converter.setFieldWidth(3);
        converter.setFillCharacter('0');
        isFirst=false;
    }

    return string("v") + converter.convert(variableCount);
}

void Integration::integrateByTryingIntegrationByParts(
        Term & result,
        Term const& term)
{
    if(isIntegrationByPartsAllowed(term))
    {
        integrateUsingIntegrationByPartsByOneTermAndOne(result, term);
        if(result.isEmpty())
        {
            integrateUsingIntegrationByPartsByTryingTwoTerms(result, term);
        }
    }
}

void Integration::integrateUsingIntegrationByPartsByOneTermAndOne(
        Term & result,
        Term const& term)
{
    bool isAnInverseTrigonometricFunction = term.isFunction()
            && isInverseTrigonometricFunction(term.getFunctionConstReference());
    if(isAnInverseTrigonometricFunction)
    {
        integrateUsingIntegrationByPartsAndCheckingPreviousValues(result, term, term, 1);
    }
}

void Integration::integrateUsingIntegrationByPartsByTryingTwoTerms(
        Term & result,
        Term const& term)
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
                Term firstTerm(createTermWithMultiplicationAndDivisionTermsWithDetails(termsInFirstTerms));
                Term secondTerm(createTermWithMultiplicationAndDivisionTermsWithDetails({termsWithDetailsInMultiplicationAndDivision.at(i)}));
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
        Term const& secondTerm)
{
    integrateUsingIntegrationByPartsAndCheckingPreviousValues(result, term, firstTerm, secondTerm);
    if(result.isEmpty())
    {
        integrateUsingIntegrationByPartsAndCheckingPreviousValues(result, term, secondTerm, firstTerm);
    }
}

void Integration::integrateUsingIntegrationByPartsAndCheckingPreviousValues(
        Term & result,
        Term const& term,
        Term const& u,
        Term const& dv)
{
    // use static equations here to solve when recursion happens
    // use static depth here to determine when to clear
    static ListOfIntegrationByPartsTerms listOfIntegrationByPartsTerms;
    constexpr unsigned int MAX_DEPTH=5;
    constexpr unsigned int MAX_SIZE=5;
    static unsigned int depth=0;
    depth++;

    if(depth < MAX_DEPTH)
    {
        if(listOfIntegrationByPartsTerms.size() < MAX_SIZE)
        {
            integrateUsingPreviousIntegrationByPartsTerms(result, listOfIntegrationByPartsTerms, term);
            if(result.isEmpty())
            {
                integrateUsingIntegrationByParts(result, listOfIntegrationByPartsTerms, term, u, dv);
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
        Term const& termToIntegrate)
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
        result = accumulatedUTimesV * ratio / (accumulatedCoefficient+1);
        result.simplify();
    }
}

void Integration::integrateUsingIntegrationByParts(
        Term & result,
        ListOfIntegrationByPartsTerms & listOfIntegrationByPartsTerms,
        Term const& term,
        Term const& u,
        Term const& dv)
{
    if(!hasNonChangingTermRaiseToChangingTerm(u))
    {
        Term v(integrateInternallyWithPurpose(dv, IntegrationPurpose::IntegrationByParts));
        if(!isNotANumber(v))
        {
            Differentiation differentiation(getCurrentVariableToIntegrate());
            Term du(differentiation.differentiate(u));
            if(!isNotANumber(du))
            {
                Term uTimesV(u*v);
                Term vTimesDu(v*du);
                uTimesV.simplify();
                vTimesDu.simplify();
                listOfIntegrationByPartsTerms.emplace_back(IntegrationByPartsTerms{term, uTimesV, vTimesDu});
                Term integratedVTimesDu(integrateInternallyWithPurpose(vTimesDu, IntegrationPurpose::IntegrationByParts));
                if(!isNotANumber(integratedVTimesDu))
                {
                    result = uTimesV - integratedVTimesDu;
                }
            }
        }
    }
}

void Integration::retrieveInputTermsAndTrigonometricExponents(
        InputTermToTrigonometryFunctionExponentsMap & trigFunctionsInputTermToExponents,
        TermsRaiseToNumbers & remainingTermsWithExponents,
        TermsRaiseToNumbers const& termsWithExponentsToCheck) const
{
    for(auto const& termExponentPair : termsWithExponentsToCheck.getBaseToExponentMap())
    {
        Term const& base(termExponentPair.first);
        AlbaNumber const& exponent(termExponentPair.second);
        if(base.isFunction() && isTrigonometricFunction(base.getFunctionConstReference()))
        {
            Function const& functionObject(base.getFunctionConstReference());
            Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
            string const& functionName(functionObject.getFunctionName());
            if("sin" == functionName)
            {
                trigFunctionsInputTermToExponents[inputTerm].sinExponent += exponent;
            }
            else if("cos" == functionName)
            {
                trigFunctionsInputTermToExponents[inputTerm].cosExponent += exponent;
            }
            else if("tan" == functionName)
            {
                trigFunctionsInputTermToExponents[inputTerm].tanExponent += exponent;
            }
            else if("csc" == functionName)
            {
                trigFunctionsInputTermToExponents[inputTerm].cscExponent += exponent;
            }
            else if("sec" == functionName)
            {
                trigFunctionsInputTermToExponents[inputTerm].secExponent += exponent;
            }
            else if("cot" == functionName)
            {
                trigFunctionsInputTermToExponents[inputTerm].cotExponent += exponent;
            }
        }
        else
        {
            remainingTermsWithExponents.setBaseAndExponent(base, exponent);
        }
    }
}

void Integration::integrateTrigonometricCombinationsIfPossible(
        Term& result,
        TermsRaiseToNumbers const& remainingTerms,
        InputTermToTrigonometryFunctionExponentsMap const& inputTermToExponents)
{
    if(remainingTerms.getBaseToExponentMap().empty() && inputTermToExponents.size() == 1)
    {
        Term const& inputTerm(inputTermToExponents.begin()->first);
        TrigonometryFunctionExponents exponents(inputTermToExponents.begin()->second);
        integrateUsingKnownTrigonometricCombinations(result, exponents, inputTerm);
    }
}

void Integration::integrateUsingKnownTrigonometricCombinations(
        Term& result,
        TrigonometryFunctionExponents const& exponents,
        Term const& functionInputTerm)
{
    if(exponents.sinExponent.isIntegerType() && exponents.sinExponent > 1
            && exponents.cosExponent.isIntegerType() && exponents.cosExponent > 1
            && exponents.tanExponent == 0
            && exponents.cscExponent == 0
            && exponents.secExponent == 0
            && exponents.cotExponent == 0)
    {
        integrateSinAndCosCombinationWithExponentsGreaterThanOne(
                    result,
                    functionInputTerm,
                    static_cast<unsigned int>(exponents.sinExponent.getInteger()),
                    static_cast<unsigned int>(exponents.cosExponent.getInteger()));
    }
    else if(exponents.sinExponent == 0
            && exponents.cosExponent == 0
            && exponents.tanExponent == 0
            && exponents.cscExponent.isIntegerType() && exponents.cscExponent > 2
            && exponents.secExponent == 0
            && exponents.cotExponent.isIntegerType() && exponents.cotExponent > 1)
    {
        integrateCscAndCotCombinationWithExponentsGreaterThanOne(
                    result,
                    functionInputTerm,
                    static_cast<unsigned int>(exponents.cscExponent.getInteger()),
                    static_cast<unsigned int>(exponents.cotExponent.getInteger()));
    }
    else if(exponents.sinExponent == 0
            && exponents.cosExponent == 0
            && exponents.tanExponent.isIntegerType() && exponents.tanExponent > 1
            && exponents.cscExponent == 0
            && exponents.secExponent.isIntegerType() && exponents.secExponent > 2
            && exponents.cotExponent == 0)
    {
        integrateSecAndTanCombinationWithExponentsGreaterThanOne(
                    result,
                    functionInputTerm,
                    static_cast<unsigned int>(exponents.secExponent.getInteger()),
                    static_cast<unsigned int>(exponents.tanExponent.getInteger()));
    }
}

void Integration::integrateSinRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const exponent)
{
    if(isEven(exponent))
    {
        Term termToIntegrate(1);
        putReducedSineSquaredToDoubleAngleCosineTerms(termToIntegrate, functionInputTerm, exponent);
        result = integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::Trigonometric);
    }
    else
    {
        Term termWithExponent(createExpressionIfPossible({getSineSquaredInCosine(functionInputTerm), "^", exponent/2}));
        Term termToIntegrate(createExpressionIfPossible({termWithExponent, "*", sin(functionInputTerm)}));
        result = integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::Trigonometric);
    }
}

void Integration::integrateCosRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const exponent)
{
    if(isEven(exponent))
    {
        Term termToIntegrate(1);
        putReducedCosineSquaredToDoubleAngleCosineTerms(termToIntegrate, functionInputTerm, exponent);
        result = integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::Trigonometric);
    }
    else
    {
        Term termWithExponent(createExpressionIfPossible({getCosineSquaredInSine(functionInputTerm), "^", exponent/2}));
        Term termToIntegrate(createExpressionIfPossible({termWithExponent, "*", cos(functionInputTerm)}));
        result = integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::Trigonometric);
    }
}

void Integration::integrateTanRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const exponent)
{
    Term tanRaiseToExponentMinus2(createExpressionIfPossible({tan(functionInputTerm), "^", exponent-2}));
    Term termToIntegrate = getTangentSquaredInSecant(functionInputTerm) * tanRaiseToExponentMinus2;
    result = integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::Trigonometric);
}

void Integration::integrateCscRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const exponent)
{
    if(isEven(exponent))
    {
        Term termToIntegrate(getCosecantSquared(functionInputTerm));
        putCosecantSquaredToCotangentSquaredTerms(termToIntegrate, functionInputTerm, exponent-2);
        result = integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::Trigonometric);
    }
    else
    {
        unsigned int const exponentMinus1 = exponent-1;
        unsigned int const exponentMinus2 = exponent-2;
        Term cscRaiseToExponentMinus2(createExpressionIfPossible({csc(functionInputTerm), "^", exponentMinus2}));
        Term nonIntegralTerm(createExpressionIfPossible({-1, "*", cscRaiseToExponentMinus2, "*", cot(functionInputTerm)}));
        result = (nonIntegralTerm + exponentMinus2 * integrateInternallyWithPurpose(cscRaiseToExponentMinus2, IntegrationPurpose::Trigonometric))
                / exponentMinus1;
    }
}

void Integration::integrateSecRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const exponent)
{
    if(isEven(exponent))
    {
        Term termToIntegrate(getSecantSquared(functionInputTerm));
        putSecantSquaredToTangentSquaredTerms(termToIntegrate, functionInputTerm, exponent-2);
        result = integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::Trigonometric);
    }
    else
    {
        unsigned int const exponentMinus1 = exponent-1;
        unsigned int const exponentMinus2 = exponent-2;
        Term secRaiseToExponentMinus2(createExpressionIfPossible({sec(functionInputTerm), "^", exponentMinus2}));
        Term nonIntegralTerm(createExpressionIfPossible({secRaiseToExponentMinus2, "*", tan(functionInputTerm)}));
        result = (nonIntegralTerm + exponentMinus2 * integrateInternallyWithPurpose(secRaiseToExponentMinus2, IntegrationPurpose::Trigonometric))
                / exponentMinus1;
    }
}

void Integration::integrateCotRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const exponent)
{
    Term tanRaiseToExponentMinus2(createExpressionIfPossible({cot(functionInputTerm), "^", exponent-2}));
    Term termToIntegrate = getCotangentSquaredInCosecant(functionInputTerm) * tanRaiseToExponentMinus2;
    result = integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::Trigonometric);
}

void Integration::integrateSinAndCosCombinationWithExponentsGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const sinExponent,
        unsigned int const cosExponent)
{
    Term termToIntegrate(1);
    if(isEven(sinExponent) && isEven(cosExponent))
    {
        putReducedSineSquaredToDoubleAngleCosineTerms(termToIntegrate, functionInputTerm, sinExponent);
        putReducedCosineSquaredToDoubleAngleCosineTerms(termToIntegrate, functionInputTerm, cosExponent);
    }
    else if(isOdd(sinExponent) && isEven(cosExponent))
    {
        termToIntegrate = termToIntegrate * createExpressionIfPossible({getSineSquaredInCosine(functionInputTerm), "^", sinExponent/2});
        termToIntegrate = termToIntegrate * sin(functionInputTerm);
        termToIntegrate = termToIntegrate * createExpressionIfPossible({cos(functionInputTerm), "^", cosExponent});
    }
    else if(isEven(sinExponent) && isOdd(cosExponent))
    {
        termToIntegrate = termToIntegrate * createExpressionIfPossible({getCosineSquaredInSine(functionInputTerm), "^", cosExponent/2});
        termToIntegrate = termToIntegrate * cos(functionInputTerm);
        termToIntegrate = termToIntegrate * createExpressionIfPossible({sin(functionInputTerm), "^", sinExponent});
    }
    else if(isOdd(sinExponent) && isOdd(cosExponent))
    {
        //This can be also be expressed in cosine.
        termToIntegrate = termToIntegrate * createExpressionIfPossible({getSineSquaredInCosine(functionInputTerm), "^", cosExponent/2});
        termToIntegrate = termToIntegrate * cos(functionInputTerm);
        termToIntegrate = termToIntegrate * createExpressionIfPossible({sin(functionInputTerm), "^", sinExponent});
    }
    result = integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::Trigonometric);
}

void Integration::integrateCscAndCotCombinationWithExponentsGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const cscExponent,
        unsigned int const cotExponent)
{
    if(isEven(cscExponent))
    {
        Term termToIntegrate(createExpressionIfPossible({cot(functionInputTerm), "^", cotExponent, "*", csc(functionInputTerm), "^", 2}));
        putCosecantSquaredToCotangentSquaredTerms(termToIntegrate, functionInputTerm, cscExponent-2);
        result = integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::Trigonometric);
    }
    else
    {
        Term termToIntegrate(createExpressionIfPossible({csc(functionInputTerm), "^", cscExponent, "*", cot(functionInputTerm)}));
        putCotangentSquaredToCosecantSquaredTerms(termToIntegrate, functionInputTerm, cotExponent-1);
        result = integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::Trigonometric);
        // what if cotExponent is even, then squareroot will happen, this is still not solved
    }
}

void Integration::integrateSecAndTanCombinationWithExponentsGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const secExponent,
        unsigned int const tanExponent)
{
    if(isEven(secExponent))
    {
        Term termToIntegrate(createExpressionIfPossible({tan(functionInputTerm), "^", tanExponent, "*", sec(functionInputTerm), "^", 2}));
        putSecantSquaredToTangentSquaredTerms(termToIntegrate, functionInputTerm, secExponent-2);
        result = integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::Trigonometric);
    }
    else
    {
        Term termToIntegrate(createExpressionIfPossible({sec(functionInputTerm), "^", secExponent, "*", tan(functionInputTerm)}));
        putTangentSquaredToSecantSquaredTerms(termToIntegrate, functionInputTerm, tanExponent-1);
        result = integrateInternallyWithPurpose(termToIntegrate, IntegrationPurpose::Trigonometric);
        // what if tanExponent is even, then squareroot will happen, this is still not solved
    }
}

Integration::TrigonometryFunctionExponents Integration::getTrigonometricExponentsSuitableForIntegration(
        TrigonometryFunctionExponents const& oldExponents) const
{
    TrigonometryFunctionExponents newExponents;
    TrigonometryFunctionExponents exponents;

    exponents.sinExponent = oldExponents.sinExponent;
    exponents.cosExponent = oldExponents.cosExponent;

    //tan change to sin and cos
    exponents.sinExponent += oldExponents.tanExponent;
    exponents.cosExponent += oldExponents.tanExponent*-1;
    exponents.tanExponent = 0;

    //csc change to sin and cos
    exponents.sinExponent += oldExponents.cscExponent*-1;
    exponents.cscExponent = 0;

    //sec change to sin and cos
    exponents.cosExponent += oldExponents.secExponent*-1;
    exponents.secExponent = 0;

    //cot change to sin and cos
    exponents.sinExponent += oldExponents.cotExponent*-1;
    exponents.cosExponent += oldExponents.cotExponent;
    exponents.cotExponent = 0;

    if(exponents.sinExponent >= 0 && exponents.cosExponent <= 0)
    {
        AlbaNumber cosPositiveExponents(getAbsoluteValueForAlbaNumber(exponents.cosExponent));
        if(exponents.sinExponent <= cosPositiveExponents)
        {
            exponents.secExponent = cosPositiveExponents - exponents.sinExponent;
            exponents.tanExponent = exponents.sinExponent;
            exponents.sinExponent = 0;
            exponents.cosExponent = 0;
            exponents.cscExponent = 0;
            exponents.cotExponent = 0;
        }
        newExponents = exponents;
    }
    else if(exponents.sinExponent <= 0 && exponents.cosExponent >= 0)
    {
        AlbaNumber sinPositiveExponents(getAbsoluteValueForAlbaNumber(exponents.sinExponent));
        if(exponents.cosExponent <= sinPositiveExponents)
        {
            exponents.cscExponent = sinPositiveExponents - exponents.cosExponent;
            exponents.cotExponent = exponents.cosExponent;
            exponents.sinExponent = 0;
            exponents.cosExponent = 0;
            exponents.tanExponent = 0;
            exponents.secExponent = 0;
        }
        newExponents = exponents;
    }
    else
    {
        newExponents = oldExponents;
    }
    return newExponents;
}

void Integration::putReducedSineSquaredToDoubleAngleCosineTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term inputTimes2(inputTerm*2);
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
    Term inputTimes2(inputTerm*2);
    Term equivalentToCosineSquared(getCosineSquaredOfHalvedValue(inputTimes2));
    for(unsigned int i=0; i<exponent; i+=2)
    {
        outputTerm = outputTerm * equivalentToCosineSquared;
    }
}

void Integration::putTangentSquaredToSecantSquaredTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term termToMultiply(createExpressionIfPossible({getTangentSquaredInSecant(inputTerm), "^", AlbaNumber(exponent)/2}));
    outputTerm = outputTerm * termToMultiply;
}

void Integration::putCosecantSquaredToCotangentSquaredTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term termToMultiply(createExpressionIfPossible({getCosecantSquaredInCotangent(inputTerm), "^", AlbaNumber(exponent)/2}));
    outputTerm = outputTerm * termToMultiply;
}

void Integration::putSecantSquaredToTangentSquaredTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term termToMultiply(createExpressionIfPossible({getSecantSquaredInTangent(inputTerm), "^", AlbaNumber(exponent)/2}));
    outputTerm = outputTerm * termToMultiply;
}

void Integration::putCotangentSquaredToCosecantSquaredTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term termToMultiply(createExpressionIfPossible({getCotangentSquaredInCosecant(inputTerm), "^", AlbaNumber(exponent)/2}));
    outputTerm = outputTerm * termToMultiply;
}

Integration::Configuration Integration::getConfigurationWithFactors() const
{
    Configuration configuration{};
    configuration.shouldFixTrigonometricFunctions = true;
    configuration.expressionSimplification = SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails();
    configuration.expressionSimplification.shouldSimplifyToFactors = true;
    configuration.expressionSimplification.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    return configuration;
}

Integration::Configuration Integration::getConfigurationWithCommonDenominator() const
{
    Configuration configuration{};
    configuration.shouldFixTrigonometricFunctions = true;
    configuration.expressionSimplification = SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails();
    configuration.expressionSimplification.shouldSimplifyToFactors = true;
    configuration.expressionSimplification.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    configuration.expressionSimplification.shouldSimplifyToACommonDenominator = true;
    return configuration;
}

Integration::Configuration Integration::getConfigurationWithoutFactors() const
{
    Configuration configuration{};
    configuration.shouldFixTrigonometricFunctions = true;
    configuration.expressionSimplification = SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails();
    configuration.expressionSimplification.shouldSimplifyToFactors = false;
    configuration.expressionSimplification.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    configuration.expressionSimplification.shouldSimplifyToACommonDenominator = false;
    return configuration;
}

Integration::Configuration Integration::getConfigurationWithCombiningRadicals() const
{
    Configuration configuration{};
    configuration.shouldFixTrigonometricFunctions = true;
    configuration.expressionSimplification = SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails();
    configuration.expressionSimplification.shouldSimplifyToFactors = false;
    configuration.expressionSimplification.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    configuration.expressionSimplification.shouldSimplifyToACommonDenominator = false;
    configuration.expressionSimplification.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;
    return configuration;
}

void Integration::simplifyForIntegration(
        Term & term,
        Configuration const& configuration) const
{
    simplifyAndFixTrigonometricFunctions(term, configuration.shouldFixTrigonometricFunctions);
    term.clearAllInnerSimplifiedFlags();
    term.simplify();
    {
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configuration.expressionSimplification);
        term.clearAllInnerSimplifiedFlags();
        term.simplify();
    }
}

void Integration::simplifyAndFixTrigonometricFunctions(
        Term & term,
        bool const shouldFixTrigonometricFunctions) const
{
    if(shouldFixTrigonometricFunctions)
    {
        TermsOverTerms termsOverTerms(createTermsOverTermsFromTerm(term));
        TermsRaiseToNumbers termsWithExponentsToCheck(termsOverTerms.getTermsRaiseToNumbers());

        InputTermToTrigonometryFunctionExponentsMap trigFunctionsInputTermToExponents;
        TermsRaiseToNumbers remainingTermsWithExponents;

        retrieveInputTermsAndTrigonometricExponents(trigFunctionsInputTermToExponents, remainingTermsWithExponents, termsWithExponentsToCheck);
        fixTrigonometricFunctionsBasedFromExponents(term, trigFunctionsInputTermToExponents, remainingTermsWithExponents);
    }
}

void Integration::fixTrigonometricFunctionsBasedFromExponents(
        Term & term,
        InputTermToTrigonometryFunctionExponentsMap const& trigFunctionsInputTermToExponents,
        TermsRaiseToNumbers const& remainingTermsWithExponents) const
{
    if(!trigFunctionsInputTermToExponents.empty())
    {
        InputTermToTrigonometryFunctionExponentsMap newTrigFunctionsInputTermToExponents(trigFunctionsInputTermToExponents);
        bool isChanged(false);
        for(auto & inputTermExponentsPair : newTrigFunctionsInputTermToExponents)
        {
            TrigonometryFunctionExponents & exponents(inputTermExponentsPair.second);
            TrigonometryFunctionExponents newExponents(getTrigonometricExponentsSuitableForIntegration(exponents));
            isChanged = isChanged || !areExponentsSame(exponents, newExponents);
            exponents = newExponents;
        }
        if(isChanged)
        {
            TermsRaiseToNumbers newTerms(remainingTermsWithExponents);
            for(auto const& inputTermExponentsPair : newTrigFunctionsInputTermToExponents)
            {
                Term const& inputTerm(inputTermExponentsPair.first);
                TrigonometryFunctionExponents const& exponents(inputTermExponentsPair.second);
                putTrigonometricFunctionsWithExponents(newTerms, inputTerm, exponents);
            }
            TermsOverTerms termsOverTerms(newTerms.getTermWithDetailsInMultiplicationAndDivisionOperation());
            term = termsOverTerms.getCombinedTerm();
        }
    }
}

void Integration::putTrigonometricFunctionsWithExponents(
        TermsRaiseToNumbers & newTerms,
        Term const& inputTerm,
        TrigonometryFunctionExponents const& exponents) const
{
    if(exponents.sinExponent != 0)
    {
        newTerms.setBaseAndExponent(sin(inputTerm), exponents.sinExponent);
    }
    if(exponents.cosExponent != 0)
    {
        newTerms.setBaseAndExponent(cos(inputTerm), exponents.cosExponent);
    }
    if(exponents.tanExponent != 0)
    {
        newTerms.setBaseAndExponent(tan(inputTerm), exponents.tanExponent);
    }
    if(exponents.cscExponent != 0)
    {
        newTerms.setBaseAndExponent(csc(inputTerm), exponents.cscExponent);
    }
    if(exponents.secExponent != 0)
    {
        newTerms.setBaseAndExponent(sec(inputTerm), exponents.secExponent);
    }
    if(exponents.cotExponent != 0)
    {
        newTerms.setBaseAndExponent(cot(inputTerm), exponents.cotExponent);
    }
}

void Integration::finalizeTermForIntegration(
        Term & term) const
{
    simplifyForIntegration(term, getConfigurationWithFactors());
}

bool Integration::isVariableToIntegrate(
        string const& variableName) const
{
    return variableName == getCurrentVariableToIntegrate();
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

bool Integration::hasNonChangingTermRaiseToChangingTerm(Term const& term) const
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
                result = !isChangingTerm(termRaiseToTerms.getBase()) && isChangingTerm(termRaiseToTerms.getCombinedExponents());
                break;
            }
        }
    }
    return result;
}

bool Integration::wouldDifferentiationYieldToAConstant(
        Term const& term) const
{
    bool result(false);
    if(term.isVariable() && isVariableToIntegrate(term.getVariableConstReference().getVariableName()))
    {
        result = true;
    }
    else if(term.isMonomial())
    {
        result = term.getMonomialConstReference().getExponentForVariable(getCurrentVariableToIntegrate()) == 1;
    }
    else if(term.isPolynomial())
    {
        result = getDegreeForVariable(term.getPolynomialConstReference(), getCurrentVariableToIntegrate()) == 1;
    }
    return result;
}

bool Integration::areExponentsSame(
        TrigonometryFunctionExponents const& exponents1,
        TrigonometryFunctionExponents const& exponents2) const
{
    return exponents1.sinExponent == exponents2.sinExponent
            && exponents1.cosExponent == exponents2.cosExponent
            && exponents1.tanExponent == exponents2.tanExponent
            && exponents1.cscExponent == exponents2.cscExponent
            && exponents1.secExponent == exponents2.secExponent
            && exponents1.cotExponent == exponents2.cotExponent;
}

bool Integration::isIntegrationUsingSubstitutionAllowed(
        Term const& term) const
{
    return IntegrationPurpose::Substitution != m_history.getLastIntegrationPurpose() || hasAnyTrigonometricFunctions(term);
}

bool Integration::isIntegrationByPartsAllowed(
        Term const& term) const
{
    return IntegrationPurpose::Substitution != m_history.getLastIntegrationPurpose() || hasAnyTrigonometricFunctions(term);
}

bool Integration::isTrigonometricSubstitutionAllowed() const
{
    return true;
}

bool Integration::isIntegrationByPartialFractionAllowed() const
{
    return IntegrationPurpose::PartialFraction != m_history.getLastIntegrationPurpose();
}

string Integration::getCurrentVariableToIntegrate() const
{
    string result;
    if(!m_variablesToIntegrate.empty())
    {
        result = m_variablesToIntegrate.back();
    }
    return result;
}

}

}
