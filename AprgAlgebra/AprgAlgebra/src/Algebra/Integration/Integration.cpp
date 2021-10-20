#include "Integration.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/IntegrationUtilities.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfTermsToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

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
{}

Term Integration::integrate(
        Term const& term) const
{
    return integrateTerm(term);
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
    Term result(createExpressionIfPossible({integrateTerm(term), Term("+"), Term(C)}));
    simplifyForIntegration(result, getConfigurationWithFactors());
    return result;
}
Term Integration::integrateWithDefiniteValues(
        Term const& term,
        AlbaNumber const& lowerValueInInterval,        AlbaNumber const& higherValueInInterval) const
{
    return substituteValuesAndGetDifference(
                integrateTerm(term),
                m_nameOfVariableToIntegrate,
                lowerValueInInterval,
                higherValueInInterval);
}

Term Integration::integrateTerm(
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

Monomial Integration::integrateMonomial(
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

Polynomial Integration::integratePolynomial(
        Polynomial const& polynomial) const
{
    Polynomial result;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        result.addMonomial(integrateMonomial(monomial));
    }
    result.simplify();
    return result;
}

Term Integration::integrateExpression(
        Expression const& expression) const
{
    Term result(integrateAsTermOrExpressionIfNeeded(expression));
    simplifyForIntegration(result, getConfigurationWithFactors());
    return result;
}
Term Integration::integrateFunction(
        Function const& functionObject) const
{
    Term result(integrateFunctionOnly(functionObject));
    simplifyForIntegration(result, getConfigurationWithFactors());
    return result;
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
}

void Integration::integrateTermsInAdditionOrSubtraction(
        Term & result,
        TermsWithDetails const& termsWithDetails) const
{
    Expression accumulatedExpression(createOrCopyExpressionFromATerm(Constant(0)));    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& currentTerm(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        Term integratedTerm(integrate(currentTerm));        if(termWithDetails.hasPositiveAssociation())
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
    integrateRecognizedFunctionsIfPossible(result, termsWithDetails);
    integrateUsingChainRuleInReverseIfPossible(result, termsWithDetails);
}

void Integration::integrateTermsInRaiseToPower(
        Term & result,
        TermsWithDetails const& termsWithDetails) const
{
    if(termsWithDetails.size() == 2)
    {
        Term const& firstTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.at(0).baseTermSharedPointer));        Term const& secondTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.at(1).baseTermSharedPointer));
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
}

void Integration::integrateConstantRaiseToTerm(
        Term & result,
        AlbaNumber const& ,
        Term const& ) const
{
    //implement this
    result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
}

void Integration::integrateTermRaiseToConstant(
        Term & result,
        Term const& base,
        AlbaNumber const& exponent) const
{
    if(wouldDifferentiationYieldToAConstant(base))
    {
        result = divideFirstTermAndDerivativeOfSecondTerm(Term(createExpressionIfPossible(        {base, Term("^"), Term(exponent+1), Term("/"), Term(exponent+1)})), base);
    }
    else if(base.isFunction())
    {        Function const& functionTerm(base.getFunctionConstReference());
        Term const& inputOfFunctionTerm(getTermConstReferenceFromBaseTerm(functionTerm.getInputTermConstReference()));
        if(exponent == 2
                && functionTerm.getFunctionName() == "sec"
                && wouldDifferentiationYieldToAConstant(inputOfFunctionTerm))
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(tan(inputOfFunctionTerm)), inputOfFunctionTerm);
        }
        else if(exponent == 2
                && functionTerm.getFunctionName() == "csc"
                && wouldDifferentiationYieldToAConstant(inputOfFunctionTerm))
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(createExpressionIfPossible(
            {Term(cot(inputOfFunctionTerm)), Term("*"), Term(-1)}), inputOfFunctionTerm);
        }
    }
}

void Integration::integrateTermRaiseToTerm(
        Term & result,
        Term const& ,
        Term const& ) const
{
    result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
}

Term Integration::integrateFunctionOnly(        Function const& functionObject) const
{
    Term result;
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));    if(wouldDifferentiationYieldToAConstant(inputTerm))
    {
        if("sin" == functionObject.getFunctionName())
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(createExpressionIfPossible({Term(-1), Term("*"), cos(inputTerm)})), inputTerm);
        }
        else if("cos" == functionObject.getFunctionName())
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(sin(inputTerm)), inputTerm);
        }
        /*else if("tan" == functionObject.getFunctionName())
        {
            integrationOfFunction = Term(createExpressionIfPossible({sec(inputTerm), Term("^"), Term(2)}));
        }
        else if("csc" == functionObject.getFunctionName())
        {
            integrationOfFunction = Term(createExpressionIfPossible({Term(-1), Term("*"), csc(inputTerm), Term("*"), cot(inputTerm)}));
        }
        else if("sec" == functionObject.getFunctionName())
        {
            integrationOfFunction = Term(createExpressionIfPossible({sec(inputTerm), Term("*"), tan(inputTerm)}));
        }
        else if("cot" == functionObject.getFunctionName())
        {
            integrationOfFunction = Term(createExpressionIfPossible({Term(-1), Term("*"), csc(inputTerm), Term("^"), Term(2)}));
        }*/
    }
    if(result.isEmpty())
    {
        integrateTermUsingSubstitutionWithMaxDepth(result, Term(functionObject), getConfigurationWithFactors());
    }
    if(result.isEmpty())
    {        result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
    return result;
}

void Integration::integrateTermUsingSubstitutionWithMaxDepth(
        Term & result,
        Term const& term,
        Configuration const& configuration) const
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
                break;            }
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
        string newVariableName(createVariableNameForSubstitution(termToSubstituteToVariable));        Integration integrationWithNewVariable(newVariableName);
        Term integratedTermWithNewVariable(integrationWithNewVariable.integrateTerm(termToIntegrateWithNewVariable));
        SubstitutionOfVariablesToTerms substitutionVariableToTerm({{newVariableName, termToSubstituteToVariable}});
        Term integratedTerm(substitutionVariableToTerm.performSubstitutionTo(integratedTermWithNewVariable));        if(!isNotANumber(integratedTerm))
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
        IsolationOfOneVariableOnEqualityEquation isolation(Equation(newVariable, "=", termToSubstituteWithVariable));
        Equation equationWithIsolatedOldVariable(isolation.isolate(m_nameOfVariableToIntegrate));
        Term const& termWithOldVariableFromIsolation(equationWithIsolatedOldVariable.getRightHandTerm());
        Term const& termWithNewVariableFromIsolation(equationWithIsolatedOldVariable.getLeftHandTerm());
        if(canBeConvertedToMonomial(termWithOldVariableFromIsolation))
        {
            Monomial monomialWithOldVariable(createMonomialIfPossible(termWithOldVariableFromIsolation));
            AlbaNumber exponentForOldVariable(monomialWithOldVariable.getExponentForVariable(m_nameOfVariableToIntegrate));
            monomialWithOldVariable.putVariableWithExponent(m_nameOfVariableToIntegrate, AlbaNumber(0));
            Term isolatedTermWithNewVariable((termWithNewVariableFromIsolation/monomialWithOldVariable)^(AlbaNumber(1)/exponentForOldVariable));
            SubstitutionOfVariablesToTerms substitutionVariableToTerm({{m_nameOfVariableToIntegrate, isolatedTermWithNewVariable}});
            termWithNewVariable = substitutionVariableToTerm.performSubstitutionTo(termWithNewVariable);
        }
    }
    return termWithNewVariable;
}

void Integration::integrateUsingChainRuleInReverseIfPossible(
        Term & result,
        TermsWithDetails const& termsWithDetailsInMultiplicationAndDivision) const
{
    unsigned int numberOfTerms(termsWithDetailsInMultiplicationAndDivision.size());
    for(unsigned int i=0; result.isEmpty() && i<numberOfTerms; i++)
    {
        TermsWithDetails termsInFirstTerms(termsWithDetailsInMultiplicationAndDivision);
        termsInFirstTerms.erase(termsInFirstTerms.cbegin() + i);
        Term firstTerm(simplifyAndConvertToTerm(OperatorLevel::MultiplicationAndDivision, termsInFirstTerms));
        Term secondTerm(simplifyAndConvertToTerm(OperatorLevel::MultiplicationAndDivision, termsWithDetailsInMultiplicationAndDivision.at(i)));
        Term innerTermInfirstTerm;
        findInnerAndOuterTermForChainRule(innerTermInfirstTerm, firstTerm);
        if(!innerTermInfirstTerm.isEmpty())
        {
            integrateUsingChainRuleInReverseIfPossible(result, firstTerm, innerTermInfirstTerm, secondTerm);
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
        Term integratedOuterTermInNewVariable(integrationWithNewVariable.integrateTerm(newFirstOuterTerm));
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
            TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
            if(termsWithDetails.size() == 2)
            {
                Term const& firstTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.at(0).baseTermSharedPointer));
                Term const& secondTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.at(1).baseTermSharedPointer));
                TermRaiseToANumber oldTermRaiseToANumber;
                if(firstTerm.isConstant())
                {
                    oldTermRaiseToANumber = TermRaiseToANumber(secondTerm, firstTerm.getConstantValueConstReference());
                }
                else if(secondTerm.isConstant())
                {
                    oldTermRaiseToANumber = TermRaiseToANumber(firstTerm, secondTerm.getConstantValueConstReference());
                }
                Term simplifiedBase(oldTermRaiseToANumber.getBase());
                simplifiedBase.simplify();
                TermRaiseToANumber newTermRaiseToANumber(simplifiedBase, oldTermRaiseToANumber.getExponent());
                innerTerm = newTermRaiseToANumber.getBase();
                outerTerm = newTermRaiseToANumber.getCombinedTerm();
            }
        }
        else
        {
            TermRaiseToANumber oldTermRaiseToANumber(createTermRaiseToANumberFromExpression(expression));
            Term simplifiedBase(oldTermRaiseToANumber.getBase());
            simplifiedBase.simplify();
            TermRaiseToANumber newTermRaiseToANumber(simplifiedBase, oldTermRaiseToANumber.getExponent());
            innerTerm = newTermRaiseToANumber.getBase();
            outerTerm = newTermRaiseToANumber.getCombinedTerm();
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

void Integration::integrateRecognizedFunctionsIfPossible(
        Term & result,
        TermsWithDetails const& termsWithDetails) const
{
    if(result.isEmpty() && termsWithDetails.size() == 2)
    {
        Term const& firstTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.at(0).baseTermSharedPointer));
        Term const& secondTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.at(1).baseTermSharedPointer));
        if(firstTerm.isFunction()
                && termsWithDetails.at(0).hasPositiveAssociation()
                && secondTerm.isFunction()
                && termsWithDetails.at(1).hasPositiveAssociation())
        {
            Function const& firstFunction(firstTerm.getFunctionConstReference());
            Function const& secondFunction(secondTerm.getFunctionConstReference());
            Term const& firstInputOfFunctionTerm(getTermConstReferenceFromBaseTerm(firstFunction.getInputTermConstReference()));
            Term const& secondInputOfFunctionTerm(getTermConstReferenceFromBaseTerm(secondFunction.getInputTermConstReference()));
            if(firstInputOfFunctionTerm == secondInputOfFunctionTerm)
            {
                if(firstFunction.getFunctionName() == "sec" && secondFunction.getFunctionName() == "tan")
                {
                    result = divideFirstTermAndDerivativeOfSecondTerm(sec(firstInputOfFunctionTerm), firstInputOfFunctionTerm);
                }
                else if(firstFunction.getFunctionName() == "csc" && secondFunction.getFunctionName() == "cot")
                {
                    result = divideFirstTermAndDerivativeOfSecondTerm(createExpressionIfPossible(
                    {Term(csc(firstInputOfFunctionTerm)), Term("*"), Term(-1)}), firstInputOfFunctionTerm);
                }
            }
        }
    }
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

bool Integration::isVariableToIntegrate(string const& variableName) const
{
    return variableName == m_nameOfVariableToIntegrate;}

bool Integration::isVariableToIntegrateNotFoundInTerm(Term const& term) const
{
    VariableNamesRetriever retriever;    retriever.retrieveFromTerm(term);
    VariableNamesSet const& variableNames(retriever.getSavedData());
    return variableNames.find(m_nameOfVariableToIntegrate) == variableNames.cend();
}

bool Integration::wouldDifferentiationYieldToAConstant(
        Term const& term) const
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