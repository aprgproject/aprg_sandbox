#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Equation/EquationOperator.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

namespace alba
{

namespace algebra
{
bool isEquationOperatorString(std::string const& stringToCheck);
bool isEquationOperatorCharacterString(std::string const& stringToCheck);
bool isEqual(Term const& leftTerm, Term const& rightTerm);
bool isNotEqual(Term const& leftTerm, Term const& rightTerm);
bool isLessThan(Term const& leftTerm, Term const& rightTerm);bool isGreaterThan(Term const& leftTerm, Term const& rightTerm);
bool isLessThanOrEqual(Term const& leftTerm, Term const& rightTerm);
bool isGreaterThanOrEqual(Term const& leftTerm, Term const& rightTerm);
bool isEquationOperationSatisfied(        EquationOperator const& operatorObject,
        Term const& leftTerm,
        Term const& rightTerm);
bool doesAllEquationsHaveEqualityOperator(Equations const& equations);

std::string getEquationOperatorCharacters();
Equation buildEquationIfPossible(std::string const& equationString);

VariableNamesSet retrieveAndReturnVariableNames(Equation const& equation);
void retrieveVariableNames(VariableNamesSet & variableNames, Equation const& equation);
void retrieveVariableNames(VariableNamesSet & variableNames, Equations const& equations);
}

}