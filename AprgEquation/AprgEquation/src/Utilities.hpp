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
Term convertMonomialToSimplestTerm(Monomial const& monomial);

BaseTermSharedPointer createBaseTermSharedPointer(BaseTermSharedPointer const& baseTerm);
BaseTermSharedPointer createBaseTermSharedPointerFromTerm(Term const& term);
BaseTermSharedPointer createBaseTermSharedPointerFromTermReference(Term& term);

Monomial createMonomialConstant(AlbaNumber const& number);
Monomial createMonomialVariable(std::string const& variableName);

Expression createExpression(Terms const& terms);
Expression convertTermToExpression(Term const& term);
Expression createSimplifiedExpression(Terms const& terms);

}

}
