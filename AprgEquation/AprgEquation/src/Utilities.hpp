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

Monomial createMonomialConstant(AlbaNumber const& number);
Monomial createMonomialVariable(std::string const& variableName);
Expression createExpressionIfPossible(Terms const& terms);
Expression createExpressionFromTerm(Term const& term);
Expression createSimplifiedExpressionIfPossible(Terms const& terms);

Term convertExpressionToSimplestTerm(Expression const& expression);
Term convertPolynomialToSimplestTerm(Polynomial const& polynomial);
Term convertMonomialToSimplestTerm(Monomial const& monomial);

BaseTermSharedPointer createNewTermAndReturnSharedPointer(BaseTermSharedPointer const& sharedPointer);
BaseTermSharedPointer copyAndCreateNewTermAndReturnSharedPointer(Term const& term);
Term & getTermReferenceFromSharedPointer(BaseTermSharedPointer & sharedPointer);
Term const& getTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer);
BaseTermSharedPointer getSharedPointerFromTermReference(Term & term);

}
}
