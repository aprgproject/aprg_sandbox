#include "Utilities.hpp"

#include <Macros/AlbaMacros.hpp>
#include <TermOperators.hpp>
#include <TermsAggregator.hpp>

#include <algorithm>

using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

bool isOperator(string const& variableOrOperator)
{
    return "+" == variableOrOperator ||
            "-" == variableOrOperator ||
            "*" == variableOrOperator ||
            "/" == variableOrOperator ||
            "^" == variableOrOperator;
}

bool canBeMergedByAdditionOrSubtraction(Term const& term1, Term const& term2)
{
    bool result(false);
    if(term1.isConstant() && term2.isConstant())
    {
        result = true;
    }
    if(term1.isVariable() && term2.isVariable())
    {
        result = canBeMergedByAdditionOrSubtraction(term1.getVariableConstReference(), term2.getVariableConstReference());
    }
    if(term1.isMonomial() && term2.isMonomial())
    {
        result = canBeMergedByAdditionOrSubtraction(term1.getMonomialConstReference(), term2.getMonomialConstReference());
    }
    if(term1.isMonomial() && term2.isVariable())
    {
        result = canBeMergedByAdditionOrSubtraction(term1.getMonomialConstReference(), term2.getVariableConstReference());
    }
    if(term1.isVariable() && term2.isMonomial())
    {
        result = canBeMergedByAdditionOrSubtraction(term2.getMonomialConstReference(), term1.getVariableConstReference());
    }
    return result;
}

bool canBeMergedByAdditionOrSubtraction(Monomial const& monomial1, Monomial const& monomial2)
{
    Monomial::VariablesToExponentsMap const& variablesMap1(monomial1.getVariablesToExponentsMapConstReference());
    Monomial::VariablesToExponentsMap const& variablesMap2(monomial2.getVariablesToExponentsMapConstReference());
    bool result(false);
    if(variablesMap1.size() == variablesMap2.size())
    {
        using MapConstIterator=Monomial::VariablesToExponentsMap::const_iterator;
        using MismatchResultType=pair<MapConstIterator, MapConstIterator>;
        MismatchResultType mismatchResult = mismatch(variablesMap1.cbegin(), variablesMap1.end(), variablesMap2.cbegin());
        result = mismatchResult.first == variablesMap1.cend();
    }
    return result;
}

bool canBeMergedByAdditionOrSubtraction(Monomial const& monomial, Variable const& variable)
{
    Monomial::VariablesToExponentsMap const& variablesMap(monomial.getVariablesToExponentsMapConstReference());
    string variableName(variable.getVariableName());
    bool result(false);
    if(variablesMap.size() == 1)
    {
        if(variablesMap.find(variableName) != variablesMap.cend())
        {
            result = variablesMap.at(variableName)==1;
        }
    }
    return result;
}

bool canBeMergedByAdditionOrSubtraction(Variable const& variable1, Variable const& variable2)
{
    return variable1.getVariableName() == variable2.getDisplayableString();
}

bool willHaveNoEffectOnAdditionOrSubtraction(Term const& term)
{
    return term.isEmpty() || term.isTheValueZero();
}

bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term const& term)
{
    return term.isEmpty() || term.isTheValueOne();
}

unsigned int getOperatorPriority(std::string const& operatorString)
{
    unsigned int result=0;
    if("+" == operatorString)
    {
        result=1;
    }
    else if("-" == operatorString)
    {
        result=2;
    }
    else if("*" == operatorString)
    {
        result=3;
    }
    else if("/" == operatorString)
    {
        result=4;
    }
    else if("^" == operatorString)
    {
        result=5;
    }
    return result;
}

unsigned int getAssociationPriority(TermAssociationType const association)
{
    unsigned int result(0);
    switch(association)
    {
    case TermAssociationType::Positive:
        result=1;
        break;
    case TermAssociationType::Negative:
        result=2;
        break;
    }
    return result;
}

unsigned int getOperatorLevelInversePriority(OperatorLevel const operatorLevel)
{
    unsigned int result(0);
    switch(operatorLevel)
    {
    case OperatorLevel::Unknown:
        result=0;
        break;
    case OperatorLevel::AdditionAndSubtraction:
        result=3;
        break;
    case OperatorLevel::MultiplicationAndDivision:
        result=2;
        break;
    case OperatorLevel::RaiseToPower:
        result=1;
        break;
    }
    return result;
}

unsigned int getTermTypePriorityValue(TermType const termType)
{
    unsigned int result(0);
    if(TermType::Operator == termType)
    {
        result=1;
    }
    else if(TermType::Constant == termType)
    {
        result=2;
    }
    else if(TermType::Variable == termType)
    {
        result=3;
    }
    else if(TermType::Monomial == termType)
    {
        result=4;
    }
    else if(TermType::Polynomial == termType)
    {
        result=5;
    }
    else if(TermType::Expression == termType)
    {
        result=6;
    }
    return result;
}

string getOperatingString(
        OperatorLevel const operatorLevel,
        TermAssociationType const association)
{
    string result;
    if(TermAssociationType::Positive == association)
    {
        switch(operatorLevel)
        {
        case OperatorLevel::AdditionAndSubtraction:
            result = "+";
            break;
        case OperatorLevel::MultiplicationAndDivision:
            result = "*";
            break;
        case OperatorLevel::RaiseToPower:
            result = "^";
            break;
        default:
            break;
        }
    }
    else if(TermAssociationType::Negative == association)
    {
        switch(operatorLevel)
        {
        case OperatorLevel::AdditionAndSubtraction:
            result = "-";
            break;
        case OperatorLevel::MultiplicationAndDivision:
            result = "/";
            break;
        default:
            break;
        }
    }
    return result;
}

string getFirstStringIfNegativeAssociation(
        OperatorLevel const operatorLevel,
        TermAssociationType const association)
{
    string result;
    if(TermAssociationType::Negative == association)
    {
        if(OperatorLevel::AdditionAndSubtraction == operatorLevel)
        {
            result = "-";
        }
        else if(OperatorLevel::MultiplicationAndDivision == operatorLevel)
        {
            result = "1/";
        }
    }
    return result;
}

string getString(TermsWithDetails const& termsWithDetails)
{
    string result;
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        result += getString(termWithDetails);
    }
    return result;
}

string getString(TermWithDetails const& termWithDetails)
{
    return string("[")+termWithDetails.baseTermSharedPointer->getDisplayableString()
            +"]["+getEnumShortString(termWithDetails.association)+"]";
}

string getEnumShortString(TermType const termType)
{
    switch(termType)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Empty, "Empty")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Constant, "Constant")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Variable, "Variable")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Operator, "Operator")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Monomial, "Monomial")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Polynomial, "Polynomial")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermType::Expression, "Expression")
            default:
        return "default";
    }
}

string getEnumShortString(TermAssociationType const association)
{
    switch(association)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermAssociationType::Positive, "<POS>")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(TermAssociationType::Negative, "<NEG>")
            default:
        return "default";
    }
}

string getEnumShortString(OperatorLevel const operatorLevel)
{
    switch(operatorLevel)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::Unknown, "<?>")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::AdditionAndSubtraction, "<+->")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::MultiplicationAndDivision, "<*/>")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(OperatorLevel::RaiseToPower, "<^>")
            default:
        return "default";
    }
}

Monomial createMonomialConstant(AlbaNumber const& number)
{
    return Monomial(number, {});
}

Monomial createMonomialVariable(string const& variableName)
{
    return Monomial(1, {{variableName, 1}});
}

Polynomial createPolynomialIfPossible(Term const& term)
{
    Polynomial result;
    if(term.isConstant())
    {
        result = Polynomial{createMonomialConstant(term.getConstantConstReference().getNumberConstReference())};
    }
    else if(term.isVariable())
    {
        result = Polynomial{createMonomialVariable(term.getVariableConstReference().getVariableName())};
    }
    else if(term.isMonomial())
    {
        result = Polynomial{term.getMonomialConstReference()};
    }
    else if(term.isPolynomial())
    {
        result = term.getPolynomialConstReference();
    }
    return result;
}

Expression createExpressionInAnExpression(Expression const& expression)
{
    return Expression(getBaseTermConstReferenceFromTerm(Term(expression)));
}

Expression createAndWrapExpressionFromATerm(Term const& term)
{
    return Expression(getBaseTermConstReferenceFromTerm(term));
}

Expression createOrCopyExpressionFromATerm(Term const& term)
{
    Expression result;
    if(!term.isEmpty())
    {
        if(term.isExpression())
        {
            result=term.getExpressionConstReference();
        }
        else
        {
            result=Expression(getBaseTermConstReferenceFromTerm(term));
        }
    }
    return result;
}

Expression createExpressionIfPossible(Terms const& terms)
{
    Expression result;
    TermsAggregator aggregator(terms);
    aggregator.buildExpressionFromTerms();
    Terms const& builtTerms(aggregator.getTermsConstReference());
    if(builtTerms.size() == 1)
    {
        result = createOrCopyExpressionFromATerm(builtTerms.at(0));
    }
    return result;
}

Expression createSimplifiedExpressionIfPossible(Terms const& terms)
{
    Expression result;
    TermsAggregator aggregator(terms);
    aggregator.simplifyTerms();
    Terms const& simplifiedTerms(aggregator.getTermsConstReference());
    if(simplifiedTerms.size() == 1)
    {
        result = createOrCopyExpressionFromATerm(simplifiedTerms.at(0));
    }
    return result;
}

Term convertExpressionToSimplestTerm(Expression const& expression)
{
    Term newTerm(expression);
    if(expression.isEmpty())
    {
        newTerm = Term();
    }
    else if(expression.containsOnlyOneTerm())
    {
        Term const& term = dynamic_cast<Term const&>(expression.getFirstTermConstReference());
        newTerm = term;
    }
    return newTerm;
}

Term simplifyAndConvertExpressionToSimplestTerm(Expression const& expression)
{
    Expression newExpression(expression);
    newExpression.simplify();
    return convertExpressionToSimplestTerm(newExpression);
}

Term simplifyAndConvertPolynomialToSimplestTerm(Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.simplify();
    Term newTerm;
    if(newPolynomial.isZero())
    {
        newTerm = Term(Constant(0));
    }
    else if(newPolynomial.isOneMonomial())
    {
        newTerm = simplifyAndConvertMonomialToSimplestTerm(newPolynomial.getFirstMonomial());
    }
    else
    {
        newTerm = Term(newPolynomial);
    }
    return newTerm;
}

Term simplifyAndConvertMonomialToSimplestTerm(Monomial const& monomial)
{
    Monomial newMonomial(monomial);
    newMonomial.simplify();
    Term newTerm(newMonomial);
    if(newMonomial.isZero())
    {
        newTerm = Term(Constant(0));
    }
    else if(newMonomial.isConstantOnly())
    {
        newTerm = Term(newMonomial.getConstantConstReference());
    }
    else if(newMonomial.isVariableOnly())
    {
        newTerm = Term(newMonomial.getFirstVariableName());
    }
    else
    {
        newTerm = Term(newMonomial);
    }
    return newTerm;
}

BaseTermSharedPointer createNewTermAndReturnSharedPointer(BaseTermSharedPointer const& sharedPointer)
{
    return move(BaseTermSharedPointer(
                    dynamic_cast<BaseTerm*>(
                        new Term(*dynamic_cast<Term*>(sharedPointer.get())))));
}

BaseTermSharedPointer copyAndCreateNewTermAndReturnSharedPointer(Term const& term)
{
    return move(BaseTermSharedPointer(
                    dynamic_cast<BaseTerm*>(
                        new Term(term))));
}

BaseTermSharedPointer getSharedPointerFromTermReference(Term & term)
{
    return move(BaseTermSharedPointer(dynamic_cast<BaseTerm*>(&term)));
}

Term const& getTermConstReferenceFromBaseTerm(BaseTerm const& baseTerm)
{
    return dynamic_cast<Term const&>(baseTerm);
}

Term const& getTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer)
{
    return dynamic_cast<Term const&>(*sharedPointer.get());
}

Term & getTermReferenceFromBaseTerm(BaseTerm & baseTerm)
{
    return dynamic_cast<Term &>(baseTerm);
}

Term & getTermReferenceFromSharedPointer(BaseTermSharedPointer & sharedPointer)
{
    return *dynamic_cast<Term*>(sharedPointer.get());
}

BaseTerm const& getBaseTermConstReferenceFromTerm(Term const& term)
{
    return dynamic_cast<BaseTerm const&>(term);
}

BaseTerm const& getBaseTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer)
{
    return dynamic_cast<BaseTerm const&>(*sharedPointer.get());
}

BaseTerm & getBaseTermReferenceFromTerm(Term & term)
{
    return dynamic_cast<BaseTerm &>(term);
}

}

}
