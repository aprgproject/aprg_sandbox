#include "SignMutator.hpp"

#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

using namespace alba::algebra::Simplification;
using namespace alba::mathHelper;using namespace std;

namespace alba
{
namespace algebra
{

void SignMutator::mutateTerm(Term & term)
{
    if(term.isConstant())
    {
        mutateConstant(term.getConstantReference());
    }
    else if(term.isVariable())
    {
        term = getTermForMutationOfVariable(term.getVariableConstReference());
    }
    else if(term.isMonomial())
    {
        mutateMonomial(term.getMonomialReference());
    }
    else if(term.isPolynomial())
    {
        mutatePolynomial(term.getPolynomialReference());
    }
    else if(term.isExpression())
    {
        mutateExpression(term.getExpressionReference());
    }
    else if(term.isFunction())
    {
        term = getTermForMutationOfFunction(term.getFunctionConstReference());
    }
    term.simplify();
}

void SignMutator::mutateConstant(Constant & constant)
{
    constant.setNumber(getSign(constant.getNumberConstReference()));
}

void SignMutator::mutateVariable(Variable &)
{}

void SignMutator::mutateMonomial(Monomial & monomial)
{
    monomial = m_substitution.performSubstitutionForMonomial(monomial);
    monomial.simplify();
    monomial.setConstant(getSign(monomial.getConstantConstReference()));
}

void SignMutator::mutatePolynomial(Polynomial & polynomial)
{
    bool areAllTheValuesOne(true);
    bool areAllTheValuesNegativeOne(true);
    Monomials mutatedMonomials(polynomial.getMonomialsConstReference());
    for(Monomial & mutatedMonomial : mutatedMonomials)
    {
        mutateMonomial(mutatedMonomial);
        areAllTheValuesOne = areAllTheValuesOne && isTheValue(mutatedMonomial, 1);
        areAllTheValuesNegativeOne = areAllTheValuesNegativeOne && isTheValue(mutatedMonomial, -1);
        if(!areAllTheValuesOne && !areAllTheValuesNegativeOne)
        {
            break;
        }
    }
    if(areAllTheValuesOne)
    {
        polynomial = createPolynomialFromNumber(1);
    }
    else if(areAllTheValuesNegativeOne)
    {
        polynomial = createPolynomialFromNumber(-1);
    }
    else
    {
        polynomial = createPolynomialFromNumber(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
}

void SignMutator::mutateExpression(Expression & expression)
{
    Term simplifiedTerm(expression);
    simplifyTermToACommonDenominator(simplifiedTerm);
    if(simplifiedTerm.isExpression())
    {
        expression = simplifiedTerm.getExpressionConstReference();
        if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
        {
            mutateExpressionWithAdditionAndSubtraction(expression);
        }
        else if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
        {
            mutateExpressionWithMultiplicationAndDivision(expression);
        }
        else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
        {
            mutateExpressionWithRaiseToPower(expression);
        }
    }
    else
    {
        mutateTerm(simplifiedTerm);
        expression = Expression(createOrCopyExpressionFromATerm(simplifiedTerm));
    }
    expression.simplify();
}

void SignMutator::mutateFunction(Function &)
{}

void SignMutator::putVariableWithSign(
        string const& variableName,
        TermAssociationType const association)
{
    if(TermAssociationType::Positive == association)
    {
        m_substitution.putVariableWithValue(variableName, 1);
    }
    else
    {
        m_substitution.putVariableWithValue(variableName, -1);
    }
}

Term SignMutator::getTermForMutationOfVariable(
        Variable const& variable)
{
    Term result(m_substitution.performSubstitutionTo(variable));
    if(!isTheValue(result, 1) && !isTheValue(result, -1))
    {
        result = AlbaNumber(AlbaNumber::Value::NotANumber);
    }
    return result;
}

Term SignMutator::getTermForMutationOfFunction(
        Function const& functionObject)
{
    Term result(functionObject);
    result.simplify();
    if(result.isFunction())
    {
        Function const& simplifiedFunction(result.getFunctionConstReference());
        string const& simplifiedFunctionName(simplifiedFunction.getFunctionName());
        if("abs" == simplifiedFunctionName
                || "cosh" == simplifiedFunctionName
                || "sech" == simplifiedFunctionName
                || "arccosh" == simplifiedFunctionName
                || "arcsech" == simplifiedFunctionName)
        {
            result = 1;
        }
        else
        {
            result = AlbaNumber(AlbaNumber::Value::NotANumber);
        }
    }
    else if(!result.isConstant())
    {
        result = AlbaNumber(AlbaNumber::Value::NotANumber);
    }
    return result;
}

void SignMutator::mutateExpressionWithAdditionAndSubtraction(
        Expression & expression)
{
    bool areAllTheValuesOne(true);
    bool areAllTheValuesNegativeOne(true);
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term termValue(negateTermIfHasNegativeAssociation(termWithDetails));
        mutateTerm(termValue);
        areAllTheValuesOne = areAllTheValuesOne && isTheValue(termValue, 1);
        areAllTheValuesNegativeOne = areAllTheValuesNegativeOne && isTheValue(termValue, -1);
        if(!areAllTheValuesOne && !areAllTheValuesNegativeOne)
        {
            break;
        }
    }
    if(areAllTheValuesOne)
    {
        expression = createOrCopyExpressionFromATerm(1);
    }
    else if(areAllTheValuesNegativeOne)
    {
        expression = createOrCopyExpressionFromATerm(-1);
    }
    else
    {
        expression = createOrCopyExpressionFromATerm(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
}

void SignMutator::mutateExpressionWithMultiplicationAndDivision(
        Expression & expression)
{
    TermsWithDetails & termsWithDetails(expression.getTermsWithAssociationReference().getTermsWithDetailsReference());
    for(TermWithDetails & termWithDetails : termsWithDetails)
    {
        Term & term(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        mutateTerm(term);
    }
    expression.simplify();
    if(!isTheValue(expression, 1) && !isTheValue(expression, -1))
    {
        expression = createOrCopyExpressionFromATerm(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
}

void SignMutator::mutateExpressionWithRaiseToPower(
        Expression & expression)
{
    bool isExpressionSignKnown(false);
    TermRaiseToTerms termRaiseToTerms(expression.getTermsWithAssociation().getTermsWithDetails());
    Term mutatedBase(termRaiseToTerms.getBase());
    mutateTerm(mutatedBase);
    if(isTheValue(mutatedBase, 1))
    {
        expression = createOrCopyExpressionFromATerm(1);
        isExpressionSignKnown=true;
    }
    else if(isTheValue(mutatedBase, -1))
    {
        Term mutatedExponent(termRaiseToTerms.getCombinedExponents());
        mutatedExponent.simplify();
        if(mutatedExponent.isConstant())
        {
            AlbaNumber const& exponentValue(mutatedExponent.getConstantValueConstReference());
            expression = createOrCopyExpressionFromATerm(AlbaNumber(-1)^exponentValue);
        }
    }
    if(!isExpressionSignKnown)
    {
        expression = createOrCopyExpressionFromATerm(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
}

}

}
