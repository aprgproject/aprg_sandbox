#pragma once

#include <Equation/Term/BaseTermPointers.hpp>
#include <Equation/Term/Term.hpp>
#include <Optional/AlbaOptional.hpp>
#include <String/AlbaStringHelper.hpp>

#include <string>

namespace alba
{

namespace equation
{

bool isOperator(std::string const& stringAsParameter);
bool isFunction(std::string const& stringAsParameter);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Term const& term1, Term const& term2);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial1, Monomial const& monomial2);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial, Variable const& variable);bool canBeMergedInAMonomialByAdditionOrSubtraction(Variable const& variable1, Variable const& variable2);
bool canBeConvertedToMonomial(Term const& term);
bool canBeConvertedToPolynomial(Term const& term);
bool willHaveNoEffectOnAdditionOrSubtraction(Term const& term);bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term const& term);

unsigned int getOperatorPriority(std::string const& operatorString);
unsigned int getAssociationPriority(TermAssociationType const association);
unsigned int getOperatorLevelInversePriority(OperatorLevel const operatorLevel);
unsigned int getTermTypePriorityValue(TermType const termType);

std::string getEnumShortString(TermType const termType);
std::string getEnumShortString(TermAssociationType const association);
std::string getEnumShortString(OperatorLevel const operatorLevel);
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
std::string createVariableNameForSubstitution(Polynomial const& polynomial);

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
Monomial createMonomialIfPossible(Term const& term);
Polynomial createPolynomialFromConstant(Constant const& constant);
Polynomial createPolynomialFromVariable(Variable const& variable);
Polynomial createPolynomialFromMonomial(Monomial const& monomial);
Polynomial createPolynomialIfPossible(Term const& term);
Expression createExpressionInAnExpression(Expression const& expression);
Expression createAndWrapExpressionFromATerm(Term const& term);
Expression createOrCopyExpressionFromATerm(Term const& term);
Expression createExpressionIfPossible(Terms const& terms);
Expression createSimplifiedExpressionIfPossible(Terms const& terms);
Function createFunctionWithEmptyInputExpression(std::string const& functionName);

Term simplifyAndConvertMonomialToSimplestTerm(Monomial const& monomial);
Term simplifyAndConvertPolynomialToSimplestTerm(Polynomial const& polynomial);
Term simplifyAndConvertExpressionToSimplestTerm(Expression const& expression);
Term simplifyAndConvertFunctionToSimplestTerm(Function const& functionAsParameter);
Term convertExpressionToSimplestTerm(Expression const& expression);
Term convertFunctionToSimplestTerm(Function const& functionAsParameter);
Term convertValueTermStringToTerm(std::string const& valueTerm);

AlbaNumber getGcfCoefficientInMonomials(Monomials const& monomials);
AlbaNumber getLcmCoefficientInMonomials(Monomials const& monomials);
AlbaNumber getCommonSignInMonomials(Monomials const& monomials);
Monomial getGcfMonomialInMonomials(Monomials const& monomials);
Monomial getLcmMonomialInMonomials(Monomials const& monomials);
void collectVariableNames(stringHelper::strings & variableNames, Monomial const& monomial);
Monomial compareMonomialsAndSaveMinimumExponentsForEachVariable(Monomial const& firstMonomial, Monomial const& secondMonomial);
Monomial compareMonomialsAndSaveMaximumExponentsForEachVariable(Monomial const& firstMonomial, Monomial const& secondMonomial);
Monomial getMonomialWithMinimumExponentsInMonomials(Monomials const& monomials);
Monomial getMonomialWithMaximumExponentsInMonomials(Monomials const& monomials);

void segregateMonomialsAndNonMonomials(
        Terms const& termsToSegregate,
        Terms & monomials,
        Terms & nonMonomials);
void segregatePolynomialAndNonPolynomials(
        Terms const& termsToSegregate,
        Terms & polynomials,
        Terms & nonPolynomials);
void segregateNonExpressionsAndExpressions(
        TermsWithAssociation::TermsWithDetails const& termsToSegregate,
        TermsWithAssociation::TermsWithDetails & termsWithNonExpressions,
        TermsWithAssociation::TermsWithDetails & termsWithExpressions);
void segregateTermsWithPositiveAndNegativeAssociations(
        TermsWithAssociation::TermsWithDetails const& termsToSegregate,
        TermsWithAssociation::TermsWithDetails & termsWithPositiveAssociation,
        TermsWithAssociation::TermsWithDetails & termsWithNegativeAssociation);

Terms tokenizeToTerms(std::string const& inputString);
void addValueTermIfNotEmpty(Terms & terms, std::string const& valueTerm);

}

}
