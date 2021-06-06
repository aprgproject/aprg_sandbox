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

unsigned int getOperatorLevelInversePriority(OperatorLevel const operatorLevel);
unsigned int getTermPriorityValue(Term const& term);

std::string getOperatingString(
        OperatorLevel const operatorLevel,
        TermsWithPriorityAndAssociation::AssociationType const association);
std::string getFirstStringIfNegativeAssociation(
        OperatorLevel const operatorLevel,
        TermsWithPriorityAndAssociation::AssociationType const association);

Monomial createMonomialConstant(AlbaNumber const& number);
Monomial createMonomialVariable(std::string const& variableName);Expression createExpressionFromTerm(Term const& term);
Expression createExpressionFromTermAndSimplifyIfNeeded(Term const& term);
Expression createExpressionIfPossible(Terms const& terms);
Expression createSimplifiedExpressionIfPossible(Terms const& terms);

Term convertExpressionToSimplestTerm(Expression const& expression);
Term convertPolynomialToSimplestTerm(Polynomial const& polynomial);
Term convertMonomialToSimplestTerm(Monomial const& monomial);

BaseTermSharedPointer createNewTermAndReturnSharedPointer(BaseTermSharedPointer const& sharedPointer);
BaseTermSharedPointer copyAndCreateNewTermAndReturnSharedPointer(Term const& term);
BaseTermSharedPointer getSharedPointerFromTermReference(Term & term);
Term const& getTermConstReferenceFromBaseTerm(BaseTerm const& baseTerm);
Term const& getTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer);
Term & getTermReferenceFromBaseTerm(BaseTerm & baseTerm);
Term & getTermReferenceFromSharedPointer(BaseTermSharedPointer & sharedPointer);
BaseTerm const& getBaseTermConstReferenceFromTerm(Term const& term);
BaseTerm const& getBaseTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer);
BaseTerm & getBaseTermReferenceFromTerm(Term & term);
}

}