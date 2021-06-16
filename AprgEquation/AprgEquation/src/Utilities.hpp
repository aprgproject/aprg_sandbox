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
bool canBeConvertedToPolynomial(Term const& term);
bool willHaveNoEffectOnAdditionOrSubtraction(Term const& term);
bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term const& term);

unsigned int getOperatorPriority(std::string const& operatorString);
unsigned int getAssociationPriority(TermAssociationType const association);
unsigned int getOperatorLevelInversePriority(OperatorLevel const operatorLevel);
unsigned int getTermTypePriorityValue(TermType const termType);

std::string getOperatingString(
        OperatorLevel const operatorLevel,
        TermAssociationType const association);
std::string getFirstStringIfNegativeAssociation(
        OperatorLevel const operatorLevel,
        TermAssociationType const association);
std::string getString(
        TermsWithAssociation::TermsWithDetails const& termsWithDetails);
std::string getString(
        TermsWithAssociation::TermWithDetails const& termWithDetails);
std::string getEnumShortString(TermType const termType);
std::string getEnumShortString(TermAssociationType const association);
std::string getEnumShortString(OperatorLevel const operatorLevel);

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

Monomial createMonomialFromConstant(Constant const& constant);
Monomial createMonomialFromVariable(Variable const& variable);
Polynomial createPolynomialFromConstant(Constant const& constant);
Polynomial createPolynomialFromVariable(Variable const& variable);
Polynomial createPolynomialFromMonomial(Monomial const& monomial);
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

void emplaceBackTermIfNotFound(Terms & terms, Term const& term);
void retrieveDenominatorTerms(Terms & terms, Expression const& expression);
Terms tokenizeToTerms(std::string const& inputString);
void addValueTermIfNotEmpty(Terms & terms, std::string const& valueTerm);
Term convertValueTermStringToTerm(std::string const& valueTerm);

Monomial getCommonMonomialInMonomials(Monomials const& monomials);
AlbaNumber getCommonCoefficientInMonomials(Monomials const& monomials);
Monomial getMonomialWithMinimumExponentsInMonomials(Monomials const& monomials);
AlbaNumber getCommonSignInMonomials(Monomials const& monomials);



}

}
