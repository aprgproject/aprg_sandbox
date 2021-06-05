#pragma once

#include <BaseTermPointers.hpp>
#include <Expression.hpp>
#include <Term.hpp>

#include <string>

namespace alba
{

namespace equation
{

bool isOperator(std::string const& variableOrOperator);
bool canBeAddedOrSubtracted(Monomial const& monomial1, Monomial const& monomial2);
bool canBeAddedOrSubtracted(Monomial const& monomial, Variable const& variable);

unsigned int getOperatorLevelValue(OperatorLevel const operatorLevel);
unsigned int getTermPriorityValue(Term const& term);

Term convertExpressionToSimplestTerm(Expression const& expression);

Term convertPolynomialToSimplestTerm(Polynomial const& polynomial);
Polynomial createSimplifiedPolynomial(Polynomial const& polynomial);

Term convertMonomialToSimplestTerm(Monomial const& monomial);
Monomial createSimplifiedMonomial(Monomial const& variablesMap);
Monomial multiplyMonomials(Monomial const& monomial1, Monomial const& monomial2);
Monomial divideMonomials(Monomial const& monomial1, Monomial const& monomial2);
Monomial::VariablesToExponentsMap createVariableMapAndRemoveZeroExponents(Monomial::VariablesToExponentsMap const& variablesMap);
void performChangeForVariables(
        Monomial::VariablesToExponentsMap & variablesMap,
        Monomial::ChangeExponentsForVariableFunction const& changeVariablesFunction);
Monomial::VariablesToExponentsMap combineVariableExponentMapByMultiplication(
        Monomial::VariablesToExponentsMap const& variablesMap1,
        Monomial::VariablesToExponentsMap const& variablesMap2);
Monomial::VariablesToExponentsMap combineVariableExponentMapByDivision(
        Monomial::VariablesToExponentsMap const& variablesMap1,
        Monomial::VariablesToExponentsMap const& variablesMap2);

BaseTermSharedPointer createBaseTermSharedPointer(BaseTermSharedPointer const& baseTerm);
BaseTermSharedPointer createBaseTermSharedPointerFromTerm(Term const& term);
BaseTermSharedPointer createBaseTermSharedPointerFromTermReference(Term& term);

Expression createExpression(Terms const& terms);
Expression convertTermToExpression(Term const& term);
Expression createSimplifiedExpression(Terms const& terms);

}

}
