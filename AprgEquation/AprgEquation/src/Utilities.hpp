#pragma once

#include <BaseTermPointers.hpp>
#include <Optional/AlbaOptional.hpp>
#include <Term.hpp>

#include <string>

namespace alba
{

namespace equation
{

bool isOperator(std::string const& variableOrOperator);
bool canBeMergedByAdditionOrSubtraction(Term const& term1, Term const& term2);
bool canBeMergedByAdditionOrSubtraction(Monomial const& monomial1, Monomial const& monomial2);
bool canBeMergedByAdditionOrSubtraction(Monomial const& monomial, Variable const& variable);
bool canBeMergedByAdditionOrSubtraction(Variable const& variable1, Variable const& variable2);
bool willHaveNoEffectOnAdditionOrSubtraction(Term const& term);
bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term const& term);

unsigned int getOperatorPriority(std::string const& operatorString);
unsigned int getAssociationPriority(TermsWithPriorityAndAssociation::AssociationType const association);
unsigned int getOperatorLevelInversePriority(OperatorLevel const operatorLevel);
unsigned int getTermTypePriorityValue(TermType const termType);

std::string getOperatingString(
        OperatorLevel const operatorLevel,
        TermsWithPriorityAndAssociation::AssociationType const association);
std::string getFirstStringIfNegativeAssociation(
        OperatorLevel const operatorLevel,
        TermsWithPriorityAndAssociation::AssociationType const association);
std::string getString(
        TermsWithPriorityAndAssociation::TermsWithDetails const& termsWithDetails);
std::string getString(
        TermsWithPriorityAndAssociation::TermWithDetails const& termWithDetails);
std::string getEnumShortString(TermType const termType);
std::string getEnumShortString(TermsWithPriorityAndAssociation::AssociationType const association);
std::string getEnumShortString(OperatorLevel const operatorLevel);

Monomial createMonomialConstant(AlbaNumber const& number);
Monomial createMonomialVariable(std::string const& variableName);
Polynomial createPolynomialIfPossible(Term const& term);
Expression createExpressionInAnExpression(Expression const& expression);
Expression createAndWrapExpressionFromATerm(Term const& term);
Expression createOrCopyExpressionFromATerm(Term const& term);
Expression createExpressionIfPossible(Terms const& terms);
Expression createSimplifiedExpressionIfPossible(Terms const& terms);

Term convertExpressionToSimplestTerm(Expression const& expression);
Term simplifyAndConvertExpressionToSimplestTerm(Expression const& expression);
Term simplifyAndConvertPolynomialToSimplestTerm(Polynomial const& polynomial);
Term simplifyAndConvertMonomialToSimplestTerm(Monomial const& monomial);

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
