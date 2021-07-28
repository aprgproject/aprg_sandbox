#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/AlbaNumberTypes.hpp>
#include <String/AlbaStringHelper.hpp>

#include <set>
#include <string>

namespace alba
{

namespace algebra
{

using AlbaNumbersSet = std::set<AlbaNumber>;
using VariableNamesSet = std::set<std::string>;

bool isOperator(std::string const& stringAsParameter);
bool isFunction(std::string const& stringAsParameter);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Term const& term1, Term const& term2);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial1, Monomial const& monomial2);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial, Variable const& variable);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Variable const& variable1, Variable const& variable2);
bool willHaveNoEffectOnAdditionOrSubtraction(Term const& term);
bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term const& term);
bool isNotANumber(Term const& term);
bool isNotANumber(Expression const& expression);
bool hasNotANumber(Term const& term);
bool hasNotANumber(Expression const& expression);
bool hasNotANumber(Function const& function);
bool isAFiniteValue(Term const& term);

unsigned int getOperatorPriority(std::string const& operatorString);
unsigned int getAssociationPriority(TermAssociationType const association);unsigned int getOperatorLevelInversePriority(OperatorLevel const operatorLevel);
unsigned int getTermTypePriorityValue(TermType const termType);

AlbaNumbers getRoots(Polynomial const& polynomial);
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

AlbaNumbersSet getNumbers(Term const& term);
void retrieveNumbers(Term const& term, AlbaNumbersSet & numbers);
void retrieveNumbers(Constant const& constant, AlbaNumbersSet & numbers);
void retrieveNumbers(Monomial const& monomial, AlbaNumbersSet & numbers);
void retrieveNumbers(Polynomial const& polynomial, AlbaNumbersSet & numbers);
void retrieveNumbers(Expression const& expression, AlbaNumbersSet & numbers);
void retrieveNumbers(Function const& functionTerm, AlbaNumbersSet & numbers);

VariableNamesSet getVariableNames(Term const& term);
void retrieveVariableNames(Term const& term, VariableNamesSet & variableNames);
void retrieveVariableNames(Variable const& variable, VariableNamesSet & variableNames);
void retrieveVariableNames(Monomial const& monomial, VariableNamesSet & variableNames);
void retrieveVariableNames(Polynomial const& polynomial, VariableNamesSet & variableNames);
void retrieveVariableNames(Expression const& expression, VariableNamesSet & variableNames);
void retrieveVariableNames(Function const& functionTerm, VariableNamesSet & variableNames);

AlbaNumber getGcfCoefficientInMonomials(Monomials const& monomials);
AlbaNumber getLcmCoefficientInMonomials(Monomials const& monomials);
AlbaNumber getCommonSignInMonomials(Monomials const& monomials);
Monomial getGcfMonomialInMonomials(Monomials const& monomials);
Monomial getLcmMonomialInMonomials(Monomials const& monomials);
Monomial compareMonomialsAndSaveMinimumExponentsForEachVariable(Monomial const& firstMonomial, Monomial const& secondMonomial);
Monomial compareMonomialsAndSaveMaximumExponentsForEachVariable(Monomial const& firstMonomial, Monomial const& secondMonomial);
Monomial getMonomialWithMinimumExponentsInMonomials(Monomials const& monomials);
Monomial getMonomialWithMaximumExponentsInMonomials(Monomials const& monomials);

Terms tokenizeToTerms(std::string const& inputString);
void addValueTermIfNotEmpty(Terms & terms, std::string const& valueTerm);

}

}
