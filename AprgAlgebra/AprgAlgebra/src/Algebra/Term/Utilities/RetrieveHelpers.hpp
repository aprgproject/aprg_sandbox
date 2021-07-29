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

}

}
