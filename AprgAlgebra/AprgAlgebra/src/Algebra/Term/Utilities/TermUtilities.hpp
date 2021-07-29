#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>
#include <Math/AlbaNumberTypes.hpp>

#include <functional>

namespace alba
{

namespace algebra
{

using FunctionCondition = std::function<bool(Function const&)>;

bool isOperator(std::string const& stringAsParameter);
bool isFunction(std::string const& stringAsParameter);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Term const& term1, Term const& term2);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial1, Monomial const& monomial2);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial, Variable const& variable);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Variable const& variable1, Variable const& variable2);
bool willHaveNoEffectOnAdditionOrSubtraction(Term const& term);
bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term const& term);
bool isNotANumber(Term const& term);
bool isNotANumber(Constant const& constant);
bool isNotANumber(Monomial const& monomial);
bool isNotANumber(Polynomial const& polynomial);
bool isNotANumber(Expression const& expression);
bool hasNotANumber(Term const& term);
bool hasNotANumber(Monomial const& monomial);
bool hasNotANumber(Polynomial const& polynomial);
bool hasNotANumber(Expression const& expression);
bool hasNotANumber(Function const& function);
bool isAFiniteValue(Term const& term);

unsigned int getOperatorPriority(std::string const& operatorString);
unsigned int getAssociationPriority(TermAssociationType const association);
unsigned int getOperatorLevelInversePriority(OperatorLevel const operatorLevel);
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
void retrieveNumbers(AlbaNumbersSet & numbers, Term const& term);
void retrieveNumbers(AlbaNumbersSet & numbers, Constant const& constant);
void retrieveNumbers(AlbaNumbersSet & numbers, Monomial const& monomial);
void retrieveNumbers(AlbaNumbersSet & numbers, Polynomial const& polynomial);
void retrieveNumbers(AlbaNumbersSet & numbers, Expression const& expression);
void retrieveNumbers(AlbaNumbersSet & numbers, Function const& functionObject);

VariableNamesSet getVariableNames(Term const& term);
void retrieveVariableNames(VariableNamesSet & variableNames, Term const& term);
void retrieveVariableNames(VariableNamesSet & variableNames, Variable const& variable);
void retrieveVariableNames(VariableNamesSet & variableNames, Monomial const& monomial);
void retrieveVariableNames(VariableNamesSet & variableNames, Polynomial const& polynomial);
void retrieveVariableNames(VariableNamesSet & variableNames, Expression const& expression);
void retrieveVariableNames(VariableNamesSet & variableNames, Function const& functionObject);

FunctionsSet getFunctionsWithCondition(Term const& term, FunctionCondition const& isFunctionIncluded);
void retrieveFunctionsWithCondition(FunctionsSet & functions, Term const& term, FunctionCondition const& isFunctionIncluded);
void retrieveFunctionsWithCondition(FunctionsSet & functions, Expression const& expression, FunctionCondition const& isFunctionIncluded);
void retrieveFunctionsWithCondition(FunctionsSet & functions, Function const& functionObject, FunctionCondition const& isFunctionIncluded);

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

AlbaNumberPairs getInputToOutputNumber(
        AlbaNumbers const& numbers,
        std::string const& variableName,
        Term const& term);

}

}
