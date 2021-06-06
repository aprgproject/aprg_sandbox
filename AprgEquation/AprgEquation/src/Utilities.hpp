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
bool willHaveNoEffectOnAdditionOrSubtraction(Term const& term);
bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term const& term);

unsigned int getOperatorLevelInversePriority(OperatorLevel const operatorLevel);
unsigned int getTermPriorityValue(Term const& term);

std::string getOperatingString(
        OperatorLevel const operatorLevel,
        TermsWithPriorityAndAssociation::AssociationType const association);std::string getFirstStringIfNegativeAssociation(
        OperatorLevel const operatorLevel,
        TermsWithPriorityAndAssociation::AssociationType const association);
std::string getEnumShortString(TermsWithPriorityAndAssociation::AssociationType const association);
std::string getEnumShortString(OperatorLevel const operatorLevel);

Monomial createMonomialConstant(AlbaNumber const& number);
Monomial createMonomialVariable(std::string const& variableName);
Expression createExpressionInAnExpression(Expression const& expression);
Expression createAndWrapExpressionFromATerm(Term const& term);
Expression createOrCopyExpressionFromATerm(Term const& term);
Expression createExpressionIfPossible(Terms const& terms);
Expression createSimplifiedExpressionIfPossible(Terms const& terms);

Term simplifyAndConvertExpressionToSimplestTerm(Expression const& expression);
Term simplifyAndConvertPolynomialToSimplestTerm(Polynomial const& polynomial);
Term simplifyAndConvertMonomialToSimplestTerm(Monomial const& monomial);

BaseTermSharedPointer createNewTermAndReturnSharedPointer(BaseTermSharedPointer const& sharedPointer);
BaseTermSharedPointer copyAndCreateNewTermAndReturnSharedPointer(Term const& term);
BaseTermSharedPointer getSharedPointerFromTermReference(Term & term);
Term const& getTermConstReferenceFromBaseTerm(BaseTerm const& baseTerm);
Term const& getTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer);
Term & getTermReferenceFromBaseTerm(BaseTerm & baseTerm);Term & getTermReferenceFromSharedPointer(BaseTermSharedPointer & sharedPointer);
BaseTerm const& getBaseTermConstReferenceFromTerm(Term const& term);
BaseTerm const& getBaseTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer);
BaseTerm & getBaseTermReferenceFromTerm(Term & term);
}

}
