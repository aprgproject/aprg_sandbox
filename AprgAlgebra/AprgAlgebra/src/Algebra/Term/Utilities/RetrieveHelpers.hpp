#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

#include <functional>
#include <map>

namespace alba
{

namespace algebra
{

using FunctionCondition = std::function<bool(Function const&)>;
using VariableToValueMap = std::map<std::string, AlbaNumber>;

AlbaNumber getCoefficientWithNoVariables(
        Polynomial const& polynomial);
AlbaNumber getCoefficientForVariableOnly(
        std::string const& variableName,
        Polynomial const& polynomial);
VariableToValueMap getCoefficientsForVariablesOnly(
        Polynomial const& polynomial);

AlbaNumbersSet retrieveAndReturnExponents(Term const& term);
void retrieveExponents(AlbaNumbersSet & numbers, Term const& term);
void retrieveExponents(AlbaNumbersSet & numbers, Monomial const& monomial);
void retrieveExponents(AlbaNumbersSet & numbers, Polynomial const& polynomial);
void retrieveExponents(AlbaNumbersSet & numbers, Expression const& expression);
void retrieveExponents(AlbaNumbersSet & numbers, Function const& functionObject);
void retrieveExponents(AlbaNumbersSet & numbers, Polynomials const& polynomials);

AlbaNumbersSet retrieveAndReturnNumbers(Term const& term);
void retrieveNumbers(AlbaNumbersSet & numbers, Term const& term);
void retrieveNumbers(AlbaNumbersSet & numbers, Constant const& constant);
void retrieveNumbers(AlbaNumbersSet & numbers, Monomial const& monomial);
void retrieveNumbers(AlbaNumbersSet & numbers, Polynomial const& polynomial);
void retrieveNumbers(AlbaNumbersSet & numbers, Expression const& expression);
void retrieveNumbers(AlbaNumbersSet & numbers, Function const& functionObject);

VariableNamesSet retrieveAndReturnVariableNames(Term const& term);
void retrieveVariableNames(VariableNamesSet & variableNames, Term const& term);
void retrieveVariableNames(VariableNamesSet & variableNames, Variable const& variable);
void retrieveVariableNames(VariableNamesSet & variableNames, Monomial const& monomial);
void retrieveVariableNames(VariableNamesSet & variableNames, Polynomial const& polynomial);
void retrieveVariableNames(VariableNamesSet & variableNames, Expression const& expression);
void retrieveVariableNames(VariableNamesSet & variableNames, Function const& functionObject);
void retrieveVariableNames(VariableNamesSet & variableNames, Polynomials const& polynomials);

FunctionsSet retrieveAndReturnFunctionsWithCondition(Term const& term, FunctionCondition const& isFunctionIncluded);
void retrieveFunctionsWithCondition(FunctionsSet & functions, Term const& term, FunctionCondition const& isFunctionIncluded);
void retrieveFunctionsWithCondition(FunctionsSet & functions, Expression const& expression, FunctionCondition const& isFunctionIncluded);
void retrieveFunctionsWithCondition(FunctionsSet & functions, Function const& functionObject, FunctionCondition const& isFunctionIncluded);

}

}
