#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba
{

namespace algebra
{

void reduceEquationsBySubstitution(Equations & substitutedEquations, VariableNamesSet const& variableNamesToIgnore);
void selectVariableNameAndEquationNumber(bool & areVariableAndEquationSelected, std::string & selectedVariableName, unsigned int & selectedEquationIndex, Equations const& equations, VariableNamesSet const& variableNamesToIgnore);
void substituteEquationForSelectedEquationIndex(Equations & substitutedEquations, bool const areVariableAndEquationSelected, std::string const& selectedVariableName, unsigned int const selectedEquationIndex);
void removeEquationsWithoutUnknowns(Equations& substitutedEquations);
VariableNamesSet getVariablesNamesToCheck(Equations const& equations, VariableNamesSet const& variableNamesToIgnore);

}

}
